mod vulkan;
use std::{error::Error, fmt::Display, sync::Arc};

pub use vulkan::*;

pub mod types;

mod pipeline;
pub use pipeline::*;

/*
mod registry;
pub use registry::RenderRegistry;
*/

pub use vulkano::pipeline::graphics::vertex_input::Vertex;

pub mod buffer;
pub use buffer::*;

use types::*;

mod texture;
pub use texture::ColourFormat;

use PrimitiveType;

pub type RenderIndex = usize;

#[derive(Debug)]
pub enum RenderError {
    Memory(String),
    Creation(String),
    ResourceMissing(String),
    Draw(String),
}

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
pub type RendererOk = RendererRes<()>;

pub trait Draw {
    fn draw<R: Render>(&self, renderer: &mut R) -> RendererOk;
}

// renderer.set_shader(self.shader_index);
// self.constants.iter().for_each(|constant|{
// renderer.set_constant(index, value);
// renderer.draw();
// });
// renderer.(self.shader_index);

#[derive(Debug)]
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

pub trait BufferValue: Vertex + Clone {}

pub trait CommandSubmit<R>
where
    R: Render,
{
    // fn vertex_buffers(&mut self) -> RendererRes<&[R::VertexBufferType<V>]>;
    fn set_vertex_buffer<V: BufferValue>(&mut self, buffer: &R::VertexBufferType<V>) -> RendererOk;
    // fn set_vertex_buffers(&mut self, vertex_buffers: &[R::VertexBufferType<V>]);

    // fn index_buffer(&self, buffer_index: &R::IndexBufferType) -> Option<R::IndexBufferType>;
    fn set_index_buffer(&mut self, buffer: &R::IndexBufferType) -> RendererOk;

    fn draw(&mut self, draw_call: DrawCall) -> RendererOk;
}

pub trait Render: Sized {
    type VertexBufferType<V: BufferValue>: Buffer<V>;
    type IndexBufferType: Buffer<buffer::Index>;

    type CommandsCtx: CommandSubmit<Self>;

    // type CommandsCtx<V: BufferValue>: CommandSubmit<Self::VertexBufferType<V>, Self::IndexBufferType>;

    fn set_window(&mut self, window: Arc<winit::window::Window>) -> RendererOk;

    fn begin_frame(&mut self) -> RendererOk;
    fn end_frame(&mut self) -> RendererOk;

    fn bind_pipeline(&mut self, pipeline_index: RenderIndex) -> RendererOk;
    // fn shader(&mut self) -> Shader;

    fn pipeline(&self) -> &Pipeline;
    fn pipeline_mut(&mut self) -> &mut Pipeline;

    fn pipelines(&self) -> &[Pipeline];

    fn create_vertex_buffer<V: BufferValue>(
        &mut self,
        capacity: usize,
    ) -> RendererRes<Self::VertexBufferType<V>>;

    fn create_index_buffer(&mut self, capacity: usize) -> RendererRes<Self::IndexBufferType>;

    // TODO: Implement multi set
    // fn set_vertex_buffers(&mut self, buffer_index: &[RenderIndex]) -> Result<(), RenderError>;

    fn set_view_uniforms(&mut self, view_uniforms: ViewUniforms);

    fn create_image(&mut self, params: ImageParams) -> Arc<crate::graphics::texture::ImageHandle>;
    // TODO: Implement rewriting images after they've been created
    // fn write_image(&mut self, handle: Arc<ImageHandle>);

    fn default_texture(&self) -> RenderIndex;

    fn run_commands<F>(&mut self, f: F) -> RendererOk
    where
        F: FnMut(&mut Self::CommandsCtx) -> RendererOk;
}

#[derive(Debug)]
pub struct Texture {
    pub(crate) width: usize,
    pub(crate) height: usize,

    // TODO: Implement colour formats and such things
    // tex_type: TextureType,
    pub(crate) image_handle: Arc<crate::graphics::texture::ImageHandle>,
}

impl Texture {
    pub fn from_image_params<R: Render, IP: Into<ImageParams>>(
        renderer: &mut R,
        params: IP,
    ) -> RendererRes<Self> {
        let img = renderer.create_image(params.into());

        Ok(Self {
            width: img.width(),
            height: img.height(),
            image_handle: img,
        })
    }
}
