use std::{error::Error, fmt::Display};

use cgmath::SquareMatrix;
use derive_more::Debug;

pub use types::BufferType;

mod wgpu;
pub use wgpu::*;

pub mod types;

pub mod renderer;

mod pipeline;
pub use pipeline::*;

pub mod camera;

pub mod model;
pub use model::Model;

pub mod buffer;

use types::*;

mod texture;
pub use texture::ColourFormat;

use PrimitiveType;

pub use buffer::{Buffer, BufferValue, Index};
pub use camera::Camera;

pub use ::wgpu::{CommandEncoder as Encoder, RenderPass};

use crate::{graphics::wgpu::buffer::WgpuBuffer, maths::AffineTransform};

pub type RenderIndex = usize;

#[derive(Debug)]
pub enum RenderError {
    Memory(String),
    Creation(String),
    ResourceMissing(String),
    Draw(String),
}

impl std::error::Error for RenderError {}

impl Display for RenderError {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        write!(
            f,
            "{}",
            match &self {
                RenderError::Memory(s) => s,
                RenderError::Creation(s) => s,
                RenderError::ResourceMissing(s) => s,
                RenderError::Draw(s) => s,
            }
        )
    }
}

#[derive(Debug)]
pub struct CreationError(String);

impl Error for CreationError {}

impl Display for CreationError {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        write!(f, "{}", &self.0)
    }
}

impl From<CreationError> for RenderError {
    fn from(value: CreationError) -> Self {
        RenderError::Creation(value.0)
    }
}

pub type RendererRes<T> = Result<T, RenderError>;

pub trait Render {
    fn draw(&self, renderer: &mut WgpuRenderer) -> Result<(), crate::Error>;
}

// renderer.set_shader(self.shader_index);
// self.constants.iter().for_each(|constant|{
// renderer.set_constant(index, value);
// renderer.draw();
// });
// renderer.(self.shader_index);

#[derive(Debug, Clone)]
pub struct DrawCall {
    pub num_indices: usize,
    pub start_offset: usize,

    pub primitive_type: PrimitiveType,
}

#[derive(Debug)]
pub struct ImageParams {
    pub width: usize,
    pub height: usize,

    pub colour_format: ::wgpu::TextureFormat,

    #[debug(skip)]
    pub data: Vec<u8>,
}

impl ImageParams {
    pub fn extents(&self) -> Result<::wgpu::Extent3d, crate::Error> {
        Ok(::wgpu::Extent3d {
            width: self.width.try_into()?,
            height: self.height.try_into()?,
            depth_or_array_layers: 1,
        })
    }

    pub fn expected_size(&self) -> Result<usize, crate::Error> {
        let extents = match self.colour_format {
            ::wgpu::TextureFormat::Bc1RgbaUnorm | ::wgpu::TextureFormat::Bc1RgbaUnormSrgb => {
                ::wgpu::Extent3d {
                    width: (4 * ((self.width + 2) / 4)).try_into()?,
                    height: (4 * ((self.height + 2) / 4)).try_into()?,
                    depth_or_array_layers: 1,
                }
            }
            _ => self.extents()?,
        };

        self.colour_format
            .theoretical_memory_footprint(extents)
            .try_into()
            .map_err(crate::Error::from)
    }
}

pub fn d3d_to_wgpu_texformat(d3d: bnl::D3DFormat) -> Option<::wgpu::TextureFormat> {
    use ::wgpu::TextureFormat;
    use bnl::d3d::*;

    let x = match d3d {
        D3DFormat::Swizzled(_) => return None,
        /*
        D3DFormat::Swizzled(swizzled) => match swizzled {
            Swizzled::A8R8G8B8 => TextureFormat::Rgba8Uint
            Swizzled::X8R8G8B8 => todo!(),
            Swizzled::R5G6B5 => todo!(),
            Swizzled::R6G5B5 => todo!(),
            Swizzled::X1R5G5B5 => todo!(),
            Swizzled::A1R5G5B5 => todo!(),
            Swizzled::A8 => todo!(),
            Swizzled::A8B8G8R8 => todo!(),
            Swizzled::B8G8R8A8 => todo!(),
            Swizzled::R8G8B8A8 => TextureFormat::Rgba8Uint,
            Swizzled::R8B8 => TextureFormat::Rg8Uint,
            Swizzled::G8B8 => TextureFormat::Rg8Uint,
            // Unhandled cases
            Swizzled::A4R4G4B4 | Swizzled::R5G5B5A1 | Swizzled::R4G4B4A4 => return None,
        },
        */
        D3DFormat::Luminance(linear_luminance) => {
            return None;
        }
        D3DFormat::Standard(standard_format) => match standard_format {
            StandardFormat::Unknown => todo!(),
            StandardFormat::P8 => todo!(),
            StandardFormat::L8 => todo!(),
            StandardFormat::A8L8 => todo!(),
            StandardFormat::AL8 => todo!(),
            StandardFormat::L16 => todo!(),
            StandardFormat::V8U8 => todo!(),
            StandardFormat::L6V5U5 => todo!(),
            StandardFormat::X8L8V8U8 => todo!(),
            StandardFormat::Q8W8V8U8 => todo!(),
            StandardFormat::V16U16 => todo!(),
            StandardFormat::D16 => todo!(),
            StandardFormat::D24S8 => todo!(),
            StandardFormat::F16 => todo!(),
            StandardFormat::F24S8 => todo!(),
            StandardFormat::YUY2 => todo!(),
            StandardFormat::UYVY => todo!(),
            StandardFormat::DXT1 => TextureFormat::Bc1RgbaUnormSrgb,
            StandardFormat::DXT2Or3 => TextureFormat::Bc3RgbaUnormSrgb,
            StandardFormat::DXT4Or5 => TextureFormat::Bc5RgUnorm,
        },
        D3DFormat::Linear(linear_colour) => match linear_colour {
            LinearColour::A8B8G8R8
            | LinearColour::A8R8G8B8
            | LinearColour::B8G8R8A8
            | LinearColour::R8G8B8A8
            | LinearColour::X8R8G8B8 => TextureFormat::Rgba8Uint,
            LinearColour::A1R5G5B5
            | LinearColour::A4R4G4B4
            | LinearColour::A8
            | LinearColour::G8B8
            | LinearColour::R4G4B4A4
            | LinearColour::R5G5B5A1
            | LinearColour::R5G6B5
            | LinearColour::R6G5B5
            | LinearColour::X1R5G5B5
            | LinearColour::R8B8 => return None,
        },
        D3DFormat::VertexData | D3DFormat::Index16 | D3DFormat::ForceDWORD => return None,
    };

    Some(x)
}

#[derive(Debug)]
pub struct Texture {
    pub(crate) width: usize,
    pub(crate) height: usize,

    // TODO: Implement colour formats and such things
    // tex_type: TextureType,
    pub(crate) image_handle: ::wgpu::Texture,
}

impl Texture {
    pub fn from_image_params<IP: Into<ImageParams>>(
        renderer: &mut WgpuRenderer,
        params: IP,
    ) -> Result<Self, crate::Error> {
        let params = params.into();
        let width = params.width;
        let height = params.width;

        let image_handle = renderer.create_image(params)?;

        Ok(Self {
            width,
            height,
            image_handle,
        })
    }
}

const NUM_CAMERAS: usize = 4;

#[repr(u8)]
pub enum RenderPassType {
    PBR,
}

pub struct RenderContext {
    pub renderer: WgpuRenderer,
    pub encoder: Option<::wgpu::CommandEncoder>,

    pub cameras: [Camera; NUM_CAMERAS],
    pub view_bind_groups: [::wgpu::BindGroup; NUM_CAMERAS],
    pub view_bind_group_buffers: [WgpuBuffer<BindGroup0>; NUM_CAMERAS],
    pub draw_affine: AffineTransform,
}

impl RenderContext {
    pub fn new(mut renderer: WgpuRenderer) -> Result<Self, Box<dyn std::error::Error>> {
        let layout = &renderer.default_pipeline().get_bind_group_layout(0);

        let view_bind_group_buffers = std::array::from_fn(|_| {
            // TODO: Remove this expect
            renderer
                .create_static_buffer(BufferType::Uniform, &[BindGroup0::default()])
                .expect("unable to create render context")
        });

        let view_bind_groups = {
            let device = renderer.device_mut();

            std::array::from_fn(|i| {
                device.create_bind_group(&::wgpu::BindGroupDescriptor {
                    label: Some(&format!("Default Bind Group 0 ({i})",)),
                    layout,
                    entries: &[
                        ::wgpu::BindGroupEntry {
                            binding: 0,
                            resource: view_bind_group_buffers[i].buffer.as_entire_binding(),
                        },
                        ::wgpu::BindGroupEntry {
                            binding: 1,
                            resource: view_bind_group_buffers[i].buffer.as_entire_binding(),
                        },
                    ],
                })
            })
        };

        Ok(Self {
            renderer,
            cameras: Default::default(),
            draw_affine: AffineTransform::default(),
            encoder: None,
            view_bind_groups,
            view_bind_group_buffers,
        })
    }

    pub fn use_camera(
        &mut self,
        render_pass: &mut RenderPass,
        index: usize,
    ) -> Result<(), crate::Error> {
        let camera = self
            .cameras
            .get(index)
            .ok_or_else(|| RenderError::Memory(format!("Invalid camera index: {index}")))?
            .clone();

        // TODO: Keep the original model matrix
        self.view_bind_group_buffers[index].write(
            &self.renderer.queue,
            BindGroup0 {
                view_uniforms: ViewUniforms::from(camera),
                model_matrix: crate::maths::Mat4::identity().into(),
            },
        );

        render_pass.set_bind_group(0, &self.view_bind_groups[index], &[]);

        Ok(())
    }

    pub fn set_camera(
        &mut self,
        index: usize,
        camera: Camera,
    ) -> Result<(), Box<dyn std::error::Error>> {
        *self
            .cameras
            .get_mut(index)
            .ok_or_else(|| format!("Failed to get camera {index} from camera list."))? = camera;
        Ok(())
    }

    pub fn update_camera<F: FnMut(&mut Camera)>(
        &mut self,
        index: usize,
        mut f: F,
    ) -> Result<(), Box<dyn std::error::Error>> {
        f(self
            .cameras
            .get_mut(index)
            .ok_or_else(|| format!("Failed to get camera {index} from camera list."))?);
        Ok(())
    }

    pub fn run_commands<F>(
        &mut self,
        render_pass_type: RenderPassType,
        mut f: F,
    ) -> Result<(), crate::Error>
    where
        F: FnMut(&mut Self, &mut RenderPass) -> Result<(), crate::Error>,
    {
        if !self.renderer.surface_configured() {
            eprintln!("surface not configured");
            return Ok(());
        }

        let mut encoder =
            self.renderer
                .device()
                .create_command_encoder(&::wgpu::wgt::CommandEncoderDescriptor {
                    label: Some("Main Encoder"),
                });

        let (surface_texture, render_pass) = match render_pass_type {
            RenderPassType::PBR => self.renderer.begin_render_pass(&mut encoder)?,
        };

        // Drop render pass when done using it
        {
            let mut render_pass = render_pass.forget_lifetime();
            render_pass.set_pipeline(self.renderer.default_pipeline());
            f(self, &mut render_pass)?;
        }

        self.renderer
            .queue
            .submit(std::iter::once(encoder.finish()));
        surface_texture.present();

        Ok(())
    }
}

pub trait Draw {
    fn draw(&self, render_pass: &mut RenderPass) -> Result<(), crate::Error>;
}

#[cfg(test)]
mod test {
    use super::*;

    #[test]
    fn dxt1_size() {
        let mut params = ImageParams {
            width: 256,
            height: 256,
            colour_format: ::wgpu::TextureFormat::Bc1RgbaUnormSrgb,
            data: vec![],
        };

        assert_eq!(params.expected_size().unwrap(), 32768);

        params.height = 2;

        assert_eq!(params.expected_size().unwrap(), 512);

        params.width = 128;
        params.height = 128;

        assert_eq!(params.expected_size().unwrap(), 8192);
    }
}
