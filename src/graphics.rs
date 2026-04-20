// mod vulkan;
// pub use vulkan::*;

use std::{error::Error, fmt::Display, sync::Arc};

use cgmath::SquareMatrix as _;

pub use types::BufferType;

mod wgpu;
pub use wgpu::*;

pub use wgpu::WgpuCommandsCtx as CommandsCtx;

pub mod types;

pub mod renderer;

mod pipeline;
pub use pipeline::*;

pub mod camera;

pub mod model;
pub use model::Model;

/*
mod registry;
pub use registry::RenderRegistry;
*/

pub use vulkano::pipeline::graphics::vertex_input::Vertex;

pub mod buffer;

use types::*;

mod texture;
pub use texture::ColourFormat;

use PrimitiveType;

pub use buffer::{Buffer, BufferValue, Index};
pub use camera::Camera;

use crate::maths::AffineTransform;

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

pub struct ImageParams {
    pub width: usize,
    pub height: usize,

    pub colour_format: texture::ColourFormat,

    pub data: Vec<u8>,
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

pub struct RenderContext {
    pub renderer: WgpuRenderer,

    current_camera: usize,

    pub cameras: [Camera; NUM_CAMERAS],
    camera_uniform_buffer: wgpu::buffer::WgpuBuffer<ViewUniforms>,

    pub draw_affine: AffineTransform,
}

impl RenderContext {
    pub fn new(renderer: WgpuRenderer) -> Result<Self, Box<dyn std::error::Error>> {
        let camera_uniform_buffer = renderer
            .create_static_buffer(BufferType::Uniform, &[ViewUniforms::default()])
            .map_err(|e| e.to_string())?;

        // let camera_descriptor_set = renderer.create_descriptor_set(&camera_uniform_buffer, 1, 0)?;

        Ok(Self {
            renderer,
            current_camera: 0,
            cameras: Default::default(),
            camera_uniform_buffer,
            draw_affine: AffineTransform::default(),
        })
    }

    pub fn use_camera(&mut self, index: usize) -> Result<(), crate::Error> {
        let camera = self
            .cameras
            .get(index)
            .ok_or_else(|| RenderError::Memory(format!("Invalid camera index: {index}")))?
            .clone();

        todo!();

        /*
        // TODO: Make it so this doesn't need access to the subbuffer
        self.camera_uniform_buffer.subbuffer.write_values(
            &[ViewUniforms {
                view: camera.transform.model_matrix().into(),
                projection: crate::maths::Mat4::identity().into(),
            }],
            index,
        )?;

        // TODO: Bind the descriptor set here

        self.current_camera = index;

        Ok(())
        */
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
}

pub trait Draw {
    fn draw(&self, ctx: &mut WgpuCommandsCtx) -> Result<(), crate::Error>;
}
