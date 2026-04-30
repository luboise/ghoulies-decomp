use std::{marker::PhantomData, sync::Arc};

use cgmath::SquareMatrix;
use wgpu::util::DeviceExt;

use crate::graphics::types::Vertex3D;

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

#[repr(C)]
#[derive(Debug, Clone, Copy, bytemuck::Pod, bytemuck::Zeroable)]
pub struct BindGroup0 {
    pub view_uniforms: ViewUniforms,
    pub model_matrix: [[f32; 4]; 4],
}
impl super::BufferValue for BindGroup0 {}

impl Default for BindGroup0 {
    fn default() -> Self {
        Self {
            view_uniforms: Default::default(),
            model_matrix: cgmath::Matrix4::identity().into(),
        }
    }
}

pub use buffer::WgpuBuffer;

pub mod buffer;

#[derive(Debug)]
pub struct WgpuRenderer {
    // Wgpu context
    pub(super) queue: wgpu::Queue,
    pub(super) device: wgpu::Device,
    pub(super) surface: wgpu::Surface<'static>,
    surface_config: wgpu::SurfaceConfiguration,
    surface_configured: bool,

    // Everything else

    // surface_ctx: Option<VulkanSurfaceContext>,
    default_pipeline: ::wgpu::RenderPipeline,

    // pipelines: Vec<wgpu::RenderPipeline>,
    // current_pipeline_index: RenderIndex,

    // current_vertex_buffer_index: RenderIndex,
    // current_index_buffer_index: RenderIndex,
    default_texture: RenderIndex,
    // pbr_pipeline: wgpu::RenderPipeline,
    window: Option<Arc<winit::window::Window>>,
}

impl WgpuRenderer {
    pub(super) fn device(&self) -> &wgpu::Device {
        &self.device
    }

    pub(super) fn device_mut(&mut self) -> &mut wgpu::Device {
        &mut self.device
    }

    pub fn resize(&mut self, width: u32, height: u32) -> Result<(), crate::Error> {
        if width > 0 && height > 0 {
            self.surface_config.width = width;
            self.surface_config.height = height;
            self.surface.configure(&self.device, &self.surface_config);
            self.surface_configured = true;
        }

        Ok(())
    }

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
                required_features: wgpu::Features::TEXTURE_COMPRESSION_BC,
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

        let surface_config = wgpu::SurfaceConfiguration {
            usage: wgpu::TextureUsages::RENDER_ATTACHMENT,
            format: texture_format,
            width,
            height,
            present_mode: surface_capabilities.present_modes[0],
            desired_maximum_frame_latency: 1,
            alpha_mode: surface_capabilities.alpha_modes[0],
            view_formats: Vec::default(),
        };

        // TODO: Implement an actual default texture here
        let default_texture = 0;

        let shader =
            device.create_shader_module(wgpu::include_wgsl!("../default_shaders/wgpu_pbr.wgsl"));

        let default_pipeline_layout =
            device.create_pipeline_layout(&wgpu::PipelineLayoutDescriptor {
                label: Some("default pipeline layout"),
                bind_group_layouts: &[Some(&device.create_bind_group_layout(
                    &wgpu::BindGroupLayoutDescriptor {
                        label: Some("camera bind group layout"),
                        entries: &[
                            // Matrix uniforms
                            wgpu::BindGroupLayoutEntry {
                                binding: 0,
                                visibility: wgpu::ShaderStages::VERTEX,
                                ty: wgpu::BindingType::Buffer {
                                    ty: wgpu::BufferBindingType::Uniform,
                                    has_dynamic_offset: false,
                                    min_binding_size: None,
                                },
                                count: None,
                            },
                            // Model matrix
                            wgpu::BindGroupLayoutEntry {
                                binding: 1,
                                visibility: wgpu::ShaderStages::VERTEX,
                                ty: wgpu::BindingType::Buffer {
                                    ty: wgpu::BufferBindingType::Uniform,
                                    has_dynamic_offset: false,
                                    min_binding_size: None,
                                },
                                count: None,
                            },
                        ],
                    },
                ))],
                immediate_size: 0,
            });

        let default_pipeline = device.create_render_pipeline(&wgpu::RenderPipelineDescriptor {
            label: Some("Default pipeline"),
            layout: Some(&default_pipeline_layout),
            vertex: wgpu::VertexState {
                module: &shader,
                entry_point: Some("vs_main"),
                buffers: &[wgpu::VertexBufferLayout {
                    array_stride: size_of::<Vertex3D>().try_into()?,
                    step_mode: wgpu::VertexStepMode::Vertex,
                    attributes: &[
                        wgpu::VertexAttribute {
                            format: wgpu::VertexFormat::Float32x3,
                            offset: 0,
                            shader_location: 0,
                        },
                        wgpu::VertexAttribute {
                            format: wgpu::VertexFormat::Float32x3,
                            offset: 12,
                            shader_location: 1,
                        },
                        wgpu::VertexAttribute {
                            format: wgpu::VertexFormat::Float32x3,
                            offset: 24,
                            shader_location: 2,
                        },
                        wgpu::VertexAttribute {
                            format: wgpu::VertexFormat::Float32x2,
                            offset: 36,
                            shader_location: 3,
                        },
                        wgpu::VertexAttribute {
                            format: wgpu::VertexFormat::Uint32x4,
                            offset: 44,
                            shader_location: 4,
                        },
                        wgpu::VertexAttribute {
                            format: wgpu::VertexFormat::Float32x4,
                            offset: 60,
                            shader_location: 5,
                        },
                    ],
                }],
                compilation_options: wgpu::PipelineCompilationOptions::default(),
            },
            fragment: Some(wgpu::FragmentState {
                module: &shader,
                entry_point: Some("fs_main"),
                compilation_options: wgpu::PipelineCompilationOptions::default(),
                targets: &[Some(wgpu::ColorTargetState {
                    format: surface_config.format,
                    blend: Some(wgpu::BlendState::REPLACE),
                    write_mask: wgpu::ColorWrites::ALL,
                })],
            }),
            primitive: wgpu::PrimitiveState {
                topology: wgpu::PrimitiveTopology::TriangleStrip,
                strip_index_format: Some(wgpu::IndexFormat::Uint32),
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
            surface,
            surface_config,
            surface_configured: false,
            device,
            queue,
            default_pipeline,
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

    pub fn create_static_buffer<V: bytemuck::Pod + bytemuck::Zeroable>(
        &self,
        buffer_type: super::BufferType,
        data: &[V],
    ) -> Result<buffer::WgpuBuffer<V>, crate::Error> {
        if data.is_empty() || size_of::<V>() == 0 {
            return Err(format!(
                "bad buffer data: len {}  V size: {}",
                data.len(),
                size_of::<V>()
            )
            .into());
        }

        let buffer = self
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

    // This should return a result
    pub fn create_image(
        &mut self,
        params: super::ImageParams,
    ) -> Result<wgpu::Texture, crate::Error> {
        assert!(params.data.len() >= params.expected_size()?);

        let width = params.width as u32 / 16;
        let height = params.width as u32 / 16;

        Ok(self.device.create_texture_with_data(
            &self.queue,
            &wgpu::TextureDescriptor {
                label: Some("Some Texture"),
                size: wgpu::Extent3d {
                    width,
                    height,
                    depth_or_array_layers: 1,
                },
                mip_level_count: 1,
                sample_count: 1,
                dimension: wgpu::TextureDimension::D2,
                format: wgpu::TextureFormat::Bc1RgbaUnormSrgb,
                usage: wgpu::TextureUsages::TEXTURE_BINDING,
                view_formats: &[wgpu::TextureFormat::Bc1RgbaUnormSrgb],
            },
            wgpu::wgt::TextureDataOrder::LayerMajor,
            &params.data,
        ))
    }

    pub fn default_texture(&self) -> RenderIndex {
        self.default_texture
    }

    pub fn default_pipeline(&self) -> &::wgpu::RenderPipeline {
        &self.default_pipeline
    }

    pub fn surface_configured(&self) -> bool {
        self.surface_configured
    }

    pub fn begin_render_pass<'a>(
        &'a self,
        encoder: &'a mut ::wgpu::CommandEncoder,
    ) -> Result<(::wgpu::SurfaceTexture, ::wgpu::RenderPass<'a>), crate::Error> {
        let surface: &'a wgpu::Surface<'a> = &self.surface;
        let surface_texture = match surface.get_current_texture() {
            wgpu::CurrentSurfaceTexture::Timeout
            | wgpu::CurrentSurfaceTexture::Occluded
            | wgpu::CurrentSurfaceTexture::Outdated
            | wgpu::CurrentSurfaceTexture::Lost
            | wgpu::CurrentSurfaceTexture::Validation => return Err("bad surface".into()),
            wgpu::CurrentSurfaceTexture::Success(surface_texture)
            | wgpu::CurrentSurfaceTexture::Suboptimal(surface_texture) => surface_texture,
        };

        let view = surface_texture
            .texture
            .create_view(&wgpu::wgt::TextureViewDescriptor::default());

        let render_pass = encoder.begin_render_pass(&wgpu::RenderPassDescriptor {
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
        });

        Ok((surface_texture, render_pass))
    }
}
