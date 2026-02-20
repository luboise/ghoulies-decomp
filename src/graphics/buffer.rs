use vulkano::pipeline::graphics::vertex_input::Vertex;

use crate::graphics::{RenderError, RendererOk};

pub trait BufferValue: Vertex + Clone + Copy {}

pub type Index = u32;

pub trait Buffer<T> {
    /// Maximum number of T this buffer can hold
    fn len(&self) -> usize;
    fn is_empty(&self) -> bool {
        self.len() == 0
    }

    fn write_values(&mut self, values: &[T], start_index: usize) -> RendererOk;

    /// Number of bytes allocated to this buffer
    fn capacity_bytes(&self) -> usize {
        self.len() * size_of::<T>()
    }

    fn can_write(&self, data: &[T], start_index: usize) -> bool {
        !data.is_empty()
            && start_index < self.len()
            && start_index.checked_add(data.len()).unwrap_or(usize::MAX) <= self.len()
    }
}

impl<V: vulkano::buffer::BufferContents + Copy> crate::graphics::Buffer<V>
    for vulkano::buffer::Subbuffer<[V]>
{
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

        let mut content = vulkano::buffer::Subbuffer::write(self)?;

        content[start_index..start_index + values.len()].copy_from_slice(values);

        Ok(())
    }
}
