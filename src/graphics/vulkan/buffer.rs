use vulkano::{
    Validated,
    buffer::{AllocateBufferError, BufferContents, Subbuffer},
    sync::HostAccessError,
};

use crate::graphics;

use super::{Index, RenderError, Vertex};

impl From<HostAccessError> for RenderError {
    fn from(value: HostAccessError) -> Self {
        RenderError::Memory(value.to_string())
    }
}

impl From<AllocateBufferError> for RenderError {
    fn from(value: AllocateBufferError) -> Self {
        RenderError::Memory(value.to_string())
    }
}

impl<E: Into<RenderError>> From<Validated<E>> for RenderError {
    fn from(value: Validated<E>) -> Self {
        value.unwrap().into()
    }
}

impl<V: BufferContents + Clone> graphics::Buffer<V> for Subbuffer<[V]> {
    fn len(&self) -> usize {
        self.len() as usize
    }

    fn write_values(&mut self, values: &[V], start_index: usize) -> super::RendererOk {
        if !self.can_write(values, start_index) {
            return Err(RenderError::Memory(format!(
                "Invalid write attempted to range [{}, {}] to buffer with length {}.",
                start_index,
                start_index + values.len(),
                self.len()
            )));
        }

        let mut content = Subbuffer::write(self)?;

        values
            .iter()
            .enumerate()
            .for_each(|(i, val)| content[start_index + i] = val.clone());

        Ok(())
    }
}

#[derive(Debug)]
pub struct VulkanVertexBuffer<V: Vertex> {
    pub(crate) subbuffer: Subbuffer<[V]>,
}

impl<V: graphics::BufferValue> graphics::Buffer<V> for VulkanVertexBuffer<V> {
    fn len(&self) -> usize {
        self.subbuffer.len() as usize
    }

    fn write_values(&mut self, values: &[V], start_index: usize) -> super::RendererOk {
        self.subbuffer.write_values(values, start_index)
    }
}

#[derive(Debug)]
pub struct VulkanIndexBuffer {
    pub(crate) subbuffer: Subbuffer<[graphics::Index]>,
}

impl graphics::Buffer<graphics::Index> for VulkanIndexBuffer {
    fn len(&self) -> usize {
        self.subbuffer.len() as usize
    }

    fn write_values(&mut self, values: &[Index], start_index: usize) -> super::RendererOk {
        self.subbuffer.write_values(values, start_index)
    }
}
