use std::{marker::PhantomData, sync::Arc};

use cgmath::SquareMatrix;
use wgpu::util::DeviceExt;

pub use crate::graphics::wgpu::commands::WgpuCommandsCtx;

use super::{RenderError, RenderIndex};

#[repr(C)]
#[derive(Debug, Clone, Copy, bytemuck::Pod, bytemuck::Zeroable)]
pub struct ViewUniforms {
    pub view: [[f32; 4]; 4],
    pub projection: [[f32; 4]; 4],
}

impl Default for ViewUniforms {
    fn default() -> Self {
        Self {
            view: crate::maths::Mat4::identity().into(),
            projection: crate::maths::Mat4::identity().into(),
        }
    }
}

pub use buffer::WgpuBuffer;

pub mod buffer;

mod commands;

#[derive(Debug)]
pub(super) struct WgpuContext {
    surface: wgpu::Surface<'static>,
    surface_config: wgpu::SurfaceConfiguration,
    surface_configured: bool,
    device: wgpu::Device,
    queue: wgpu::Queue,
}

impl WgpuContext {
    pub async fn new(window: &Arc<winit::window::Window>) -> Result<Self, crate::Error> {
        let winit::dpi::PhysicalSize::<u32> { width, height } = window.inner_size();

        // TODO: Make this bind to a display based on some heuristic
        let instance = wgpu::Instance::new(wgpu::InstanceDescriptor {
            backends: wgpu::Backends::PRIMARY,
            flags: Default::default(),
            memory_budget_thresholds: Default::default(),
            backend_options: Default::default(),
            display: None,
        });

        let surface = instance.create_surface(window.clone())?;

        // Adapter = gpu
        let adapter = instance
            .request_adapter(&wgpu::RequestAdapterOptions {
                power_preference: wgpu::PowerPreference::HighPerformance,
                compatible_surface: Some(&surface),
                force_fallback_adapter: false,
            })
            .await?;

        let (device, queue) = adapter
            .request_device(&wgpu::DeviceDescriptor {
                label: None,
                required_features: wgpu::Features::empty(),
                experimental_features: wgpu::ExperimentalFeatures::disabled(),
                required_limits: wgpu::Limits::default(),
                memory_hints: Default::default(),
                trace: wgpu::Trace::Off,
            })
            .await?;

        let surface_capabilities = surface.get_capabilities(&adapter);
        let texture_format = surface_capabilities
            .formats
            .iter()
            .find(|format| format.is_srgb())
            .copied()
            .unwrap_or(surface_capabilities.formats[0]);

        let config = wgpu::SurfaceConfiguration {
            usage: wgpu::TextureUsages::RENDER_ATTACHMENT,
            format: texture_format,
            width,
            height,
            present_mode: surface_capabilities.present_modes[0],
            desired_maximum_frame_latency: 1,
            alpha_mode: surface_capabilities.alpha_modes[0],
            view_formats: Vec::default(),
        };

        Ok(Self {
            surface,
            surface_config: config,
            surface_configured: true,
            device,
            queue,
        })
    }
}

/*
#[derive(Debug)]
pub struct VulkanRenderContext {
    render_pass: Arc<RenderPass>,
    command_buffers: Vec<CommandBuffer>
}
*/

/*
#[derive(Debug)]
pub struct VulkanSurfaceContext {
    window: Arc<winit::window::Window>,

    recreate_swapchain: bool,

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
*/

#[derive(Debug)]
pub struct WgpuRenderer {
    ctx: WgpuContext,

    // surface_ctx: Option<VulkanSurfaceContext>,
    pipeline: wgpu::RenderPipeline,

    // pipelines: Vec<wgpu::RenderPipeline>,
    // current_pipeline_index: RenderIndex,

    // current_vertex_buffer_index: RenderIndex,
    // current_index_buffer_index: RenderIndex,
    default_texture: RenderIndex,
    // pbr_pipeline: wgpu::RenderPipeline,
    window: Option<Arc<winit::window::Window>>,
}

impl WgpuRenderer {
    pub fn resize(&mut self, width: u32, height: u32) -> Result<(), crate::Error> {
        if width > 0 && height > 0 {
            self.ctx.surface_config.width = width;
            self.ctx.surface_config.height = height;

            self.ctx
                .surface
                .configure(&self.ctx.device, &self.ctx.surface_config);
            self.ctx.surface_configured = true;
        }

        Ok(())
    }

    pub async fn new(window: &Arc<winit::window::Window>) -> Result<Self, crate::Error> {
        let winit::dpi::PhysicalSize::<u32> { width, height } = window.inner_size();

        let ctx = WgpuContext::new(window).await?;

        // TODO: Implement an actual default texture here
        let default_texture = 0;

        let shader = ctx
            .device
            .create_shader_module(wgpu::include_wgsl!("../default_shaders/wgpu_pbr.wgsl"));

        let default_pipeline_layout =
            ctx.device
                .create_pipeline_layout(&wgpu::PipelineLayoutDescriptor {
                    label: Some("default pipeline layout"),
                    bind_group_layouts: &[],
                    immediate_size: 0,
                });

        let default_pipeline = ctx
            .device
            .create_render_pipeline(&wgpu::RenderPipelineDescriptor {
                label: Some("Default pipeline"),
                layout: Some(&default_pipeline_layout),
                vertex: wgpu::VertexState {
                    module: &shader,
                    entry_point: Some("vs_main"),
                    buffers: &[],
                    compilation_options: wgpu::PipelineCompilationOptions::default(),
                },
                fragment: Some(wgpu::FragmentState {
                    module: &shader,
                    entry_point: Some("vs_main"),
                    compilation_options: wgpu::PipelineCompilationOptions::default(),
                    targets: &[Some(wgpu::ColorTargetState {
                        format: ctx.surface_config.format,
                        blend: Some(wgpu::BlendState::REPLACE),
                        write_mask: wgpu::ColorWrites::ALL,
                    })],
                }),
                primitive: wgpu::PrimitiveState {
                    topology: wgpu::PrimitiveTopology::TriangleStrip,
                    strip_index_format: None,
                    front_face: wgpu::FrontFace::Ccw,
                    cull_mode: Some(wgpu::Face::Back),
                    unclipped_depth: false,
                    polygon_mode: wgpu::PolygonMode::Fill,
                    conservative: false,
                },
                depth_stencil: None,
                multisample: wgpu::MultisampleState {
                    count: 1,
                    mask: !0,
                    alpha_to_coverage_enabled: false,
                },
                multiview_mask: None,
                cache: None,
            });

        Ok(Self {
            ctx,
            pipeline: default_pipeline,
            default_texture,
            window: None,
        })
    }

    pub fn begin_frame(&mut self) -> Result<(), crate::Error> {
        Ok(())
    }

    pub fn end_frame(&mut self) -> Result<(), crate::Error> {
        Ok(())
    }

    pub fn bind_pipeline(&mut self, pipeline_index: RenderIndex) -> Result<(), crate::Error> {
        todo!()
    }

    pub fn create_static_buffer<V: bytemuck::Pod + bytemuck::Zeroable>(
        &self,
        buffer_type: super::BufferType,
        data: &[V],
    ) -> Result<buffer::WgpuBuffer<V>, crate::Error> {
        let buffer = self
            .ctx
            .device
            .create_buffer_init(&wgpu::util::BufferInitDescriptor {
                label: Some("Buffer"),
                contents: bytemuck::cast_slice(data),
                usage: buffer_type.into(),
            });

        Ok(buffer::WgpuBuffer::<V> {
            buffer_type,
            buffer,
            length: data.len(),
            marker: PhantomData,
        })
    }

    /*
    pub fn create_buffer<V: vulkano::buffer::BufferContents>(
        &self,
        buffer_type: buffer::BufferType,
        length: usize,
    ) -> Result<buffer::WgpuBuffer<V>, crate::Error> {
        let buffer = self.ctx.device.create_buffer(&wgpu::wgt::BufferDescriptor {
            label: Some("Vertex Buffer"),
            size: (length * size_of::<V>()).try_into()?,
            usage: match buffer_type {
                BufferType::Vertex => wgpu::BufferUsages::VERTEX,
                BufferType::Index => wgpu::BufferUsages::INDEX,
                BufferType::Uniform => wgpu::BufferUsages::UNIFORM,
            },
            mapped_at_creation: false,
        });

        Ok(buffer::WgpuBuffer {
            buffer_type,
            buffer,
            length,
        })
    }
    */

    // This should return a result
    pub fn create_image(
        &mut self,
        params: super::ImageParams,
    ) -> Result<wgpu::Texture, crate::Error> {
        Ok(self.ctx.device.create_texture_with_data(
            &self.ctx.queue,
            &wgpu::TextureDescriptor {
                label: todo!(),
                size: todo!(),
                mip_level_count: todo!(),
                sample_count: todo!(),
                dimension: todo!(),
                format: todo!(),
                usage: todo!(),
                view_formats: todo!(),
            },
            wgpu::wgt::TextureDataOrder::LayerMajor,
            &params.data,
        ))
    }

    /*
    pub fn write_image(
        &self,
        image: Arc<vulkano::image::Image>,
        data: &[u8],
    ) -> Result<(), crate::Error> {
        let staging_buffer = create_staging_buffer(self.ctx.memory_allocator.clone(), data)?;

        let mut builder = AutoCommandBufferBuilder::primary(
            self.ctx.command_buffer_allocator.clone(),
            self.ctx.graphics_queue.queue_family_index(),
            CommandBufferUsage::OneTimeSubmit,
        )
        .map_err(|_| RenderError::Draw("Failed to create command buffer.".into()))?;

        builder.copy_buffer_to_image(CopyBufferToImageInfo::buffer_image(staging_buffer, image))?;
        let command_buffer = builder.build()?;

        let future = sync::now(self.ctx.device.clone())
            .then_execute(self.ctx.graphics_queue.clone(), command_buffer)?
            .then_signal_fence_and_flush()?;

        future.wait(None);

        Ok(())
    }
    */

    pub fn default_texture(&self) -> RenderIndex {
        self.default_texture
    }

    pub fn run_commands<F>(&mut self, mut f: F) -> Result<(), crate::Error>
    where
        F: FnMut(&mut WgpuCommandsCtx) -> Result<(), crate::Error>,
    {
        todo!();
        /*
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
                self.ctx.command_buffer_allocator.clone(),
                self.ctx.graphics_queue.queue_family_index(),
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

        let execution = sync::now(self.ctx.device.clone())
            .join(acquire_future)
            .then_execute(self.ctx.graphics_queue.clone(), command_buffer.clone())
            .unwrap()
            .then_swapchain_present(
                self.ctx.graphics_queue.clone(),
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
            */
    }

    /*
    pub fn create_descriptor_set<V: vulkano::buffer::BufferContents>(
        &self,
        buffer: &buffer::WgpuBuffer<V>,
        set: usize,
        set_binding: u32,
    ) -> Result<Arc<vulkano::descriptor_set::DescriptorSet>, Box<dyn std::error::Error>> {
        let descriptor_set = vulkano::descriptor_set::DescriptorSet::new(
            self.ctx.descriptor_set_allocator.clone(),
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
                buffer.buffer.clone(),
            )], // 0 is the binding
            [],
        )?;

        Ok(descriptor_set)
    }
    */

    fn current_pipeline(&self) -> Option<wgpu::RenderPipeline> {
        Some(self.pipeline.clone())
    }
}

type VkBuffer = vulkano::buffer::Buffer;

/*
fn create_pipeline(
    device: &wgpu::Device,
    vertex_shader: &wgpu::ShaderModule,
    fragment_shader: &wgpu::ShaderModule,
) -> Result<wgpu::RenderPipeline, CreationError> {
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

    device.create_render_pipeline(&wgpu::RenderPipelineDescriptor {
        label: (),
        layout: (),
        vertex: (),
        primitive: (),
        depth_stencil: (),
        multisample: (),
        fragment: (),
        multiview_mask: (),
        cache: (),
    })
    /*
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
        */
}
*/

fn get_render_pass<'a>(
    surface: &'a wgpu::Surface<'a>,
    encoder: &'a mut wgpu::CommandEncoder,
    // device: &wgpu::Device,
    // swapchain: &wgpu::Swapchain,
) -> Result<wgpu::RenderPass<'a>, crate::Error> {
    let surface_texture = match surface.get_current_texture() {
        wgpu::CurrentSurfaceTexture::Timeout
        | wgpu::CurrentSurfaceTexture::Occluded
        | wgpu::CurrentSurfaceTexture::Outdated
        | wgpu::CurrentSurfaceTexture::Lost
        | wgpu::CurrentSurfaceTexture::Validation => panic!("bad surface"),
        wgpu::CurrentSurfaceTexture::Success(surface_texture)
        | wgpu::CurrentSurfaceTexture::Suboptimal(surface_texture) => surface_texture,
    };

    let view = surface_texture
        .texture
        .create_view(&wgpu::wgt::TextureViewDescriptor::default());

    Ok(encoder.begin_render_pass(&wgpu::RenderPassDescriptor {
        label: Some("Render pass"),
        color_attachments: &[Some(wgpu::RenderPassColorAttachment {
            view: &view,
            depth_slice: None,
            resolve_target: None,
            ops: wgpu::Operations {
                load: wgpu::LoadOp::Clear(wgpu::Color::GREEN),
                store: wgpu::StoreOp::Store,
            },
        })],
        depth_stencil_attachment: None,
        timestamp_writes: None,
        occlusion_query_set: None,
        multiview_mask: None,
    }))
}
