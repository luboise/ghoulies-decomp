use std::sync::Arc;

use vulkano::{
    DeviceSize, Validated, ValidationError, VulkanError, VulkanLibrary,
    buffer::{BufferCreateInfo, BufferUsage, Subbuffer},
    command_buffer::{
        AutoCommandBufferBuilder, CommandBufferUsage, CopyBufferToImageInfo, RenderPassBeginInfo,
        SubpassBeginInfo, SubpassContents, SubpassEndInfo,
        allocator::{StandardCommandBufferAllocator, StandardCommandBufferAllocatorCreateInfo},
    },
    descriptor_set::{WriteDescriptorSet, allocator::StandardDescriptorSetAllocator},
    device::{
        self, Device, DeviceCreateInfo, DeviceExtensions, QueueCreateInfo, QueueFlags,
        physical::PhysicalDevice,
    },
    image::{ImageUsage, view::ImageView},
    instance::{Instance, InstanceCreateInfo, InstanceExtensions},
    memory::allocator::{
        AllocationCreateInfo, FreeListAllocator, GenericMemoryAllocator, MemoryAllocator,
        MemoryTypeFilter, StandardMemoryAllocator,
    },
    pipeline::{
        GraphicsPipeline, Pipeline, PipelineLayout, PipelineShaderStageCreateInfo,
        graphics::{
            GraphicsPipelineCreateInfo,
            color_blend::{ColorBlendAttachmentState, ColorBlendState},
            input_assembly::InputAssemblyState,
            multisample::MultisampleState,
            rasterization::RasterizationState,
            vertex_input::{Vertex, VertexDefinition},
            viewport::{Viewport, ViewportState},
        },
        layout::PipelineDescriptorSetLayoutCreateInfo,
    },
    render_pass::{Framebuffer, FramebufferCreateInfo, RenderPass, Subpass},
    shader::ShaderModule,
    swapchain::{self, Surface, Swapchain, SwapchainCreateInfo, SwapchainPresentInfo},
    sync::{self, GpuFuture},
};

use crate::graphics::RendererRes;
pub use crate::graphics::vulkan::commands::VulkanCommandsCtx;

use super::{CreationError, RenderError, RenderIndex, RendererOk, types::Vertex3D};

pub use vs_pbr::Skeleton;
pub use vs_pbr::ViewUniforms;

pub use buffer::{BufferType, VulkanBuffer};

pub mod buffer;

mod commands;

#[derive(Debug)]
pub(super) struct VulkanContext {
    // Instances
    library: Arc<VulkanLibrary>,
    instance: Arc<Instance>,
    physical_device: Arc<PhysicalDevice>,
    device: Arc<Device>,
    // Queues
    graphics_queue: Arc<device::Queue>,
    // Allocators
    memory_allocator: Arc<GenericMemoryAllocator<FreeListAllocator>>,
    command_buffer_allocator: Arc<StandardCommandBufferAllocator>,
    descriptor_set_allocator: Arc<StandardDescriptorSetAllocator>,
    // pbr_render_pass: Arc<RenderPass>,
    // pbr_subpass: Arc<Subpass>,
}

/*
#[derive(Debug)]
pub struct VulkanRenderContext {
    render_pass: Arc<RenderPass>,
    command_buffers: Vec<CommandBuffer>
}
*/

#[derive(Debug)]
pub struct VulkanSurfaceContext {
    window: Arc<winit::window::Window>,

    recreate_swapchain: bool,

    surface: Arc<Surface>,
    swapchain: Arc<Swapchain>,
    images: Vec<Arc<vulkano::image::Image>>,

    render_pass: Arc<RenderPass>,
    subpass: Subpass,

    framebuffers: Vec<Arc<Framebuffer>>,
    // render_contexts: Vec<VulkanRenderContext>
}

impl VulkanSurfaceContext {
    pub fn get_extents(&self) -> [u32; 2] {
        let size = self.window.inner_size();
        [size.width, size.height]
    }
}

#[derive(Debug)]
pub struct VulkanRenderer {
    vk: VulkanContext,

    surface_ctx: Option<VulkanSurfaceContext>,

    pipeline: Arc<GraphicsPipeline>,

    // pipelines: Vec<Arc<GraphicsPipeline>>,
    // current_pipeline_index: RenderIndex,

    // current_vertex_buffer_index: RenderIndex,
    // current_index_buffer_index: RenderIndex,
    default_texture: RenderIndex,
    // pbr_pipeline: Arc<GraphicsPipeline>,
    window: Option<Arc<winit::window::Window>>,
}

type VkBuffer = vulkano::buffer::Buffer;

impl From<ValidationError> for CreationError {
    fn from(value: ValidationError) -> Self {
        CreationError(format!("{:?}", value))
    }
}

mod vs_pbr {
    vulkano_shaders::shader! {
        ty: "vertex",
        // path: "src/rendering/default_shaders/default_3d.vert"
        path: "resources/shaders/pbr.vert",
        custom_derives: [Debug, Clone, Copy]
    }
}

mod vs_test {
    vulkano_shaders::shader! {
        ty: "vertex",
        path: "src/graphics/default_shaders/test_3d.vert"
    }
}

mod fs_pbr {
    vulkano_shaders::shader! {
        ty: "fragment",
        path: "src/graphics/default_shaders/default_3d.frag"
    }
}

mod fs_test {
    vulkano_shaders::shader! {
        ty: "fragment",
        path: "src/graphics/default_shaders/test_3d.frag"
    }
}

pub fn get_required_extensions(
    event_loop: Option<&dyn winit::raw_window_handle::HasDisplayHandle>,
) -> InstanceExtensions {
    // TODO: Double check this unwrap
    let mut extensions = match event_loop {
        Some(event_loop) => Surface::required_extensions(&event_loop).unwrap(),
        None => InstanceExtensions::empty(),
    };

    extensions.khr_surface = true;
    extensions.khr_xlib_surface = true;

    extensions
}

impl VulkanRenderer {
    pub fn new(
        event_loop: &winit::event_loop::ActiveEventLoop,
        window: &Arc<winit::window::Window>,
    ) -> RendererRes<VulkanRenderer> {
        (|| -> Result<VulkanRenderer, Box<dyn std::error::Error>> {
            let library = VulkanLibrary::new()?;

            // TODO: Make this try X11 if wayland fails
            let required_extensions = get_required_extensions(Some(event_loop));

            let instance = Instance::new(
                library.clone(),
                InstanceCreateInfo {
                    enabled_extensions: required_extensions,
                    ..InstanceCreateInfo::application_from_cargo_toml()
                },
            )?;

            let device_extensions = DeviceExtensions {
                khr_swapchain: true,
                ..DeviceExtensions::empty()
            };

            // Get the first Vulkan capable device
            let physical_device = instance
                .enumerate_physical_devices()?
                .find(|pd| pd.supported_extensions().contains(&device_extensions))
                .ok_or(CreationError("no devices available".to_string()))?;

            for family in physical_device.queue_family_properties() {
                println!(
                    "Found a queue family with {:?} queue(s)",
                    family.queue_count
                );
            }

            let queue_family_index = physical_device
                .queue_family_properties()
                .iter()
                .enumerate()
                .position(|(_queue_family_index, queue_family_properties)| {
                    queue_family_properties
                        .queue_flags
                        .contains(QueueFlags::GRAPHICS)
                })
                .expect("couldn't find a graphical queue family")
                as u32;

            let (device, mut queues) = Device::new(
                physical_device.clone(),
                DeviceCreateInfo {
                    // here we pass the desired queue family to use by index
                    queue_create_infos: vec![QueueCreateInfo {
                        queue_family_index,
                        ..Default::default()
                    }],
                    enabled_extensions: device_extensions,
                    ..Default::default()
                },
            )
            .expect("failed to create device");

            // Assumed only a single queue, the graphics queue
            let queue = queues.next().ok_or(CreationError(
                "Unable to get first device queue.".to_string(),
            ))?;

            let memory_allocator = Arc::new(StandardMemoryAllocator::new_default(device.clone()));
            let command_buffer_allocator = Arc::new(StandardCommandBufferAllocator::new(
                device.clone(),
                StandardCommandBufferAllocatorCreateInfo::default(),
            ));

            /*
            let render_pass = RenderPass::new(
                device.clone(),
                RenderPassCreateInfo {
                    subpasses: vec![SubpassDescription {
                        color_attachments: vec![Some(AttachmentReference {
                            attachment: todo!(),
                            layout: todo!(),
                            stencil_layout: todo!(),
                            aspects: todo!(),
                            _ne: todo!(),
                        })],
                        ..Default::default()
                    }],
                    ..Default::default()
                },
            )?;
            */

            // TODO: Implement an actual default texture here
            let default_texture = 0;

            let default_pipeline = {
                let surface = Surface::from_window(instance.clone(), window.clone())
                    .map_err(|e| RenderError::Creation(format!("{:?}", e)).to_string())?;

                let caps = physical_device
                    .surface_capabilities(&surface, Default::default())
                    .expect("failed to get surface capabilities");

                let (width, height) = {
                    let size = window.inner_size();
                    (size.width, size.height)
                };

                let composite_alpha = caps.supported_composite_alpha.into_iter().next().unwrap();
                let image_format = physical_device
                    .surface_formats(&surface, Default::default())
                    .unwrap()[0]
                    .0;

                let (swapchain, images) = Swapchain::new(
                    device.clone(),
                    surface.clone(),
                    SwapchainCreateInfo {
                        min_image_count: caps.min_image_count + 1,
                        image_format,
                        image_extent: [width, height],
                        image_usage: ImageUsage::COLOR_ATTACHMENT,
                        composite_alpha,
                        ..Default::default()
                    },
                )
                .unwrap();

                let render_pass =
                    get_render_pass(&device, &swapchain).map_err(|e| e.to_string())?;
                let subpass: Subpass = Subpass::from(render_pass.clone(), 0)
                    .ok_or(CreationError("Unable to create subpass 0.".to_string()))?;

                let framebuffers = get_framebuffers(&images, &render_pass);

                /*

                let vs_3d: Arc<ShaderModule> =
                    vs_pbr::load(self.vk.device.clone()).expect("Unable to compile PBR Vertex Shader.");
                let fs_3d: Arc<ShaderModule> =
                    fs_pbr::load(self.vk.device.clone()).expect("Unable to compile PBR Fragment Shader.");
                */

                let vs_3d: Arc<ShaderModule> =
                    vs_pbr::load(device.clone()).expect("Unable to compile PBR Vertex Shader.");
                let fs_3d: Arc<ShaderModule> =
                    fs_pbr::load(device.clone()).expect("Unable to compile PBR Fragment Shader.");

                create_pipeline(&device.clone(), subpass.clone(), &vs_3d, &fs_3d)?
            };

            let descriptor_set_allocator = Arc::new(StandardDescriptorSetAllocator::new(
                device.clone(),
                Default::default(),
            ));

            let mut vulkan_renderer = VulkanRenderer {
                vk: VulkanContext {
                    library,
                    instance,
                    physical_device,
                    device,
                    graphics_queue: queue,
                    memory_allocator,
                    command_buffer_allocator,
                    descriptor_set_allocator,
                    // pbr_render_pass: render_pass,
                    // pbr_subpass: subpass.into(),
                },
                pipeline: default_pipeline,
                surface_ctx: None,
                // current_pipeline_index: 0,
                default_texture,
                window: None,
            };

            vulkan_renderer
                .set_window(window.clone())
                .map_err(|e| e.to_string())?;
            Ok(vulkan_renderer)
        })()
        .map_err(|e| RenderError::Creation(format!("{:?}", e)))
    }

    fn set_window(&mut self, window: Arc<winit::window::Window>) -> RendererOk {
        println!("Setting the window in the renderer.");
        if self.surface_ctx.is_some() {
            return Err(RenderError::Creation(
                "Unable to bind new surface to renderer without unbinding the existing one.".into(),
            ));
        }

        let surface = Surface::from_window(self.vk.instance.clone(), window.clone())
            .map_err(|e| RenderError::Creation(format!("{:?}", e)))?;

        let caps = self
            .vk
            .physical_device
            .surface_capabilities(&surface, Default::default())
            .expect("failed to get surface capabilities");

        let (width, height) = {
            let size = window.inner_size();
            (size.width, size.height)
        };

        let composite_alpha = caps.supported_composite_alpha.into_iter().next().unwrap();
        let image_format = self
            .vk
            .physical_device
            .surface_formats(&surface, Default::default())
            .unwrap()[0]
            .0;

        let (swapchain, images) = Swapchain::new(
            self.vk.device.clone(),
            surface.clone(),
            SwapchainCreateInfo {
                min_image_count: caps.min_image_count + 1,
                image_format,
                image_extent: [width, height],
                image_usage: ImageUsage::COLOR_ATTACHMENT,
                composite_alpha,
                ..Default::default()
            },
        )
        .unwrap();

        let render_pass = get_render_pass(&self.vk.device, &swapchain)?;
        let subpass: Subpass = Subpass::from(render_pass.clone(), 0)
            .ok_or(CreationError("Unable to create subpass 0.".to_string()))?;

        let framebuffers = get_framebuffers(&images, &render_pass);

        /*

        let vs_3d: Arc<ShaderModule> =
            vs_pbr::load(self.vk.device.clone()).expect("Unable to compile PBR Vertex Shader.");
        let fs_3d: Arc<ShaderModule> =
            fs_pbr::load(self.vk.device.clone()).expect("Unable to compile PBR Fragment Shader.");
        */

        let vs_3d: Arc<ShaderModule> =
            vs_pbr::load(self.vk.device.clone()).expect("Unable to compile PBR Vertex Shader.");
        let fs_3d: Arc<ShaderModule> =
            fs_pbr::load(self.vk.device.clone()).expect("Unable to compile PBR Fragment Shader.");

        let pbr_pipeline =
            create_pipeline(&self.vk.device.clone(), subpass.clone(), &vs_3d, &fs_3d)?;

        self.surface_ctx = Some(VulkanSurfaceContext {
            window,
            surface,
            swapchain,
            images,
            recreate_swapchain: false,
            render_pass,
            framebuffers,
            subpass,
        });
        self.pipeline = pbr_pipeline;

        Ok(())
    }

    pub fn begin_frame(&mut self) -> RendererOk {
        Ok(())
    }

    pub fn end_frame(&mut self) -> RendererOk {
        Ok(())
    }

    pub fn bind_pipeline(&mut self, pipeline_index: RenderIndex) -> RendererOk {
        todo!()
    }

    pub fn create_buffer<V: vulkano::buffer::BufferContents>(
        &self,
        buffer_type: buffer::BufferType,
        length: usize,
    ) -> RendererRes<buffer::VulkanBuffer<V>> {
        let subbuffer: Subbuffer<[V]> = vulkano::buffer::Buffer::new_slice::<V>(
            self.vk.memory_allocator.clone(),
            BufferCreateInfo {
                usage: buffer_type.usage(),
                ..Default::default()
            },
            AllocationCreateInfo {
                // TODO: Make this prefer device, and add a staging buffer
                memory_type_filter: buffer_type.memory_type_filter(),
                ..Default::default()
            },
            (length * size_of::<V>()) as DeviceSize,
        )?;

        Ok(buffer::VulkanBuffer {
            buffer_type,
            subbuffer,
            length,
        })
    }

    // This should return a result
    pub fn create_image(
        &mut self,
        params: super::ImageParams,
    ) -> Result<Arc<vulkano::image::Image>, crate::Error> {
        use vulkano::image::*;

        let image = Image::new(
            self.vk.memory_allocator.clone(),
            ImageCreateInfo {
                image_type: ImageType::Dim2d,
                format: match params.colour_format {
                    crate::graphics::ColourFormat::RGB => {
                        vulkano::format::Format::BC1_RGB_SRGB_BLOCK
                    }
                    crate::graphics::ColourFormat::RGBA => {
                        vulkano::format::Format::BC1_RGBA_SRGB_BLOCK
                    }
                },
                extent: [params.width as u32, params.height as u32, 1],
                usage: ImageUsage::TRANSFER_DST,
                ..Default::default()
            },
            AllocationCreateInfo {
                memory_type_filter: MemoryTypeFilter::PREFER_DEVICE,
                ..Default::default()
            },
        )?;

        self.write_image(image.clone(), &params.data)?;

        Ok(image)
    }

    pub fn write_image(
        &self,
        image: Arc<vulkano::image::Image>,
        data: &[u8],
    ) -> Result<(), crate::Error> {
        let staging_buffer = create_staging_buffer(self.vk.memory_allocator.clone(), data)?;

        let mut builder = AutoCommandBufferBuilder::primary(
            self.vk.command_buffer_allocator.clone(),
            self.vk.graphics_queue.queue_family_index(),
            CommandBufferUsage::OneTimeSubmit,
        )
        .map_err(|_| RenderError::Draw("Failed to create command buffer.".into()))?;

        builder.copy_buffer_to_image(CopyBufferToImageInfo::buffer_image(staging_buffer, image))?;
        let command_buffer = builder.build()?;

        let future = sync::now(self.vk.device.clone())
            .then_execute(self.vk.graphics_queue.clone(), command_buffer)?
            .then_signal_fence_and_flush()?;

        future.wait(None);

        Ok(())
    }

    pub fn default_texture(&self) -> RenderIndex {
        self.default_texture
    }

    pub fn run_commands<F>(&mut self, mut f: F) -> Result<(), crate::Error>
    where
        F: FnMut(&mut VulkanCommandsCtx) -> Result<(), crate::Error>,
    {
        let current_pipeline = self
            .current_pipeline()
            .expect("Failed to get current pipeline");
        let surface_ctx = self.surface_ctx.as_mut().ok_or(RenderError::Draw(
            "No surface to draw onto registered in Vulkan renderer.".into(),
        ))?;

        let (image_index, suboptimal, acquire_future) =
            match swapchain::acquire_next_image(surface_ctx.swapchain.clone(), None)
                .map_err(Validated::unwrap)
            {
                Ok(r) => r,
                Err(VulkanError::OutOfDate) => {
                    surface_ctx.recreate_swapchain = true;
                    return Ok(());
                }
                Err(e) => return Err(RenderError::Draw(format!("Unexpected error: {e}")).into()),
            };

        // dbg!("Current swapchain index: {}", image_index);

        if suboptimal {
            surface_ctx.recreate_swapchain = true
        }

        if surface_ctx.recreate_swapchain {
            let extents = surface_ctx.get_extents();

            dbg!("Recreating swapchain with extents {}", &extents);

            surface_ctx
                .swapchain
                .recreate(SwapchainCreateInfo {
                    image_extent: extents,
                    ..surface_ctx.swapchain.create_info()
                })
                .expect("Failed to recreate swapchain.");

            return Ok(());
        }

        let mut ctx = VulkanCommandsCtx {
            builder: AutoCommandBufferBuilder::primary(
                self.vk.command_buffer_allocator.clone(),
                self.vk.graphics_queue.queue_family_index(),
                CommandBufferUsage::OneTimeSubmit,
            )
            .map_err(|_| RenderError::Draw("Failed to create command buffer.".into()))?,
            current_pipeline,
        };

        ctx.builder
            .begin_render_pass(
                RenderPassBeginInfo {
                    clear_values: vec![Some([0.0, 0.0, 1.0, 1.0].into())],
                    ..RenderPassBeginInfo::framebuffer(
                        surface_ctx.framebuffers[image_index as usize].clone(),
                    )
                },
                SubpassBeginInfo {
                    contents: SubpassContents::Inline,
                    ..Default::default()
                },
            )
            .map_err(|_| RenderError::Draw("Failed to begin render pass.".into()))?;

        ctx.builder
            .bind_pipeline_graphics(self.pipeline.clone())
            .map_err(|_| RenderError::Draw("Failed to bind PBR pipeline.".into()))?;

        f(&mut ctx)?;

        let VulkanCommandsCtx {
            mut builder,
            current_pipeline: _,
        } = ctx;

        builder
            .end_render_pass(SubpassEndInfo::default())
            .map_err(|_| RenderError::Draw("Unable to end render pass".to_string()))?;

        let command_buffer = builder
            .build()
            .map_err(|_| RenderError::Draw("Unable to build command buffer.".to_string()))?;

        let execution = sync::now(self.vk.device.clone())
            .join(acquire_future)
            .then_execute(self.vk.graphics_queue.clone(), command_buffer.clone())
            .unwrap()
            .then_swapchain_present(
                self.vk.graphics_queue.clone(),
                SwapchainPresentInfo::swapchain_image_index(
                    surface_ctx.swapchain.clone(),
                    image_index,
                ),
            )
            .then_signal_fence_and_flush();

        match execution.map_err(Validated::unwrap) {
            Ok(future) => {
                // Wait for the GPU to finish.
                future.wait(None).unwrap();
            }
            Err(VulkanError::OutOfDate) => {
                surface_ctx.recreate_swapchain = true;
            }
            Err(e) => {
                println!("failed to flush future: {e}");
            }
        };

        Ok(())
    }

    pub fn create_descriptor_set<V: vulkano::buffer::BufferContents>(
        &self,
        buffer: &buffer::VulkanBuffer<V>,
        set: usize,
        set_binding: u32,
    ) -> Result<Arc<vulkano::descriptor_set::DescriptorSet>, Box<dyn std::error::Error>> {
        let descriptor_set = vulkano::descriptor_set::DescriptorSet::new(
            self.vk.descriptor_set_allocator.clone(),
            self.current_pipeline()
                .ok_or_else(|| format!("Failed to get set {set} from current pipeline"))?
                .layout()
                .set_layouts()
                .get(set)
                .ok_or_else(|| {
                    format!(
                        "Failed to get binding {set_binding} in set {set} from current pipeline"
                    )
                })?
                .clone(),
            [WriteDescriptorSet::buffer(
                set_binding,
                buffer.subbuffer.clone(),
            )], // 0 is the binding
            [],
        )?;

        Ok(descriptor_set)
    }

    fn current_pipeline(&self) -> Option<Arc<GraphicsPipeline>> {
        Some(self.pipeline.clone())
    }
}

fn create_pipeline(
    device: &Arc<Device>,
    subpass: Subpass,
    vertex_shader: &Arc<ShaderModule>,
    fragment_shader: &Arc<ShaderModule>,
) -> Result<Arc<GraphicsPipeline>, CreationError> {
    let pbr_vs = vertex_shader.entry_point("main").ok_or(CreationError(
        "Failed to get entry point main of PBR vertex shader.".to_string(),
    ))?;

    let pbr_fs = fragment_shader.entry_point("main").ok_or(CreationError(
        "Failed to get entry point main of PBR fragment shader.".to_string(),
    ))?;

    let pbr_vertex_input = Vertex3D::per_vertex().definition(&pbr_vs).map_err(|e| {
        CreationError(format!(
            "Unable to get vertex definition for PBR vertex shader. Error: {}",
            e
        ))
    })?;

    let stages = [
        PipelineShaderStageCreateInfo::new(pbr_vs),
        PipelineShaderStageCreateInfo::new(pbr_fs),
        // PipelineShaderStageCreateInfo::new(pbr_vs),
        // PipelineShaderStageCreateInfo::new(pbr_fs),
    ];

    let layout = PipelineLayout::new(
        device.clone(),
        PipelineDescriptorSetLayoutCreateInfo::from_stages(&stages)
            .into_pipeline_layout_create_info(device.clone())
            .map_err(|e| CreationError(e.to_string()))?,
    )
    .map_err(|e| CreationError(e.to_string()))?;

    let viewport = Viewport {
        offset: [0f32, 0f32],
        extent: [1280.0, 720.0],
        depth_range: 0.0..=1.0,
    };

    GraphicsPipeline::new(
        device.clone(),
        None,
        GraphicsPipelineCreateInfo {
            stages: stages.into_iter().collect(),
            vertex_input_state: Some(pbr_vertex_input),
            // Can manually specify draw type
            input_assembly_state: Some(InputAssemblyState {
                topology:
                    vulkano::pipeline::graphics::input_assembly::PrimitiveTopology::TriangleStrip,
                ..Default::default()
            }),

            viewport_state: Some(ViewportState {
                viewports: [viewport].into_iter().collect(),
                ..Default::default()
            }),

            rasterization_state: Some(RasterizationState::default()),
            multisample_state: Some(MultisampleState::default()),
            color_blend_state: Some(ColorBlendState::with_attachment_states(
                subpass.num_color_attachments(),
                ColorBlendAttachmentState::default(),
            )),

            subpass: Some(subpass.into()),
            ..GraphicsPipelineCreateInfo::layout(layout)
        },
    )
    .map_err(|e| CreationError(format!("{:?}", e)))
}

fn get_render_pass(
    device: &Arc<Device>,
    swapchain: &Arc<Swapchain>,
) -> RendererRes<Arc<RenderPass>> {
    vulkano::single_pass_renderpass!(
        device.clone(),
        attachments: {
            color: {
                // Set the format the same as the swapchain.
                format: swapchain.image_format(),
                samples: 1,
                load_op: Clear,
                store_op: Store,
            },
        },
        pass: {
            color: [color],
            depth_stencil: {},
        },
    )
    .map_err(|_| RenderError::Creation("Failed to create render pass.".into()))
}

fn create_staging_buffer(
    allocator: Arc<impl MemoryAllocator>,
    data: &[u8],
) -> Result<Subbuffer<[u8]>, crate::Error> {
    let buffer = vulkano::buffer::Buffer::from_iter(
        allocator.clone(),
        BufferCreateInfo {
            usage: BufferUsage::TRANSFER_SRC,
            ..Default::default()
        },
        AllocationCreateInfo {
            memory_type_filter: MemoryTypeFilter::PREFER_HOST
                | MemoryTypeFilter::HOST_SEQUENTIAL_WRITE,
            ..Default::default()
        },
        data.to_vec().into_iter(),
    )?;

    Ok(buffer)
}

fn get_framebuffers(
    images: &[Arc<vulkano::image::Image>],
    render_pass: &Arc<RenderPass>,
) -> Vec<Arc<Framebuffer>> {
    images
        .iter()
        .map(|image| {
            let view = ImageView::new_default(image.clone()).unwrap();

            Framebuffer::new(
                render_pass.clone(),
                FramebufferCreateInfo {
                    attachments: vec![view],
                    ..Default::default()
                },
            )
            .unwrap()
        })
        .collect::<Vec<_>>()
}
