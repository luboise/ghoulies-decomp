use vulkano::{
    Validated, buffer::AllocateBufferError, memory::allocator::MemoryTypeFilter,
    sync::HostAccessError,
};

use crate::graphics::types::BufferType;

use super::RenderError;

pub struct WgpuBuffer<V> {
    pub buffer_type: BufferType,
    pub buffer: wgpu::Buffer,
    pub length: usize,

    // Need to enforce type on buffer
    pub marker: std::marker::PhantomData<V>,
}

impl<V> WgpuBuffer<V> {
    pub fn len(&self) -> usize {
        self.length
    }

    pub fn is_empty(&self) -> bool {
        self.len() == 0
    }
}

impl<V: crate::graphics::BufferValue> crate::graphics::Buffer<V> for WgpuBuffer<V> {
    fn len(&self) -> usize {
        self.length
    }

    fn write_values(&mut self, _values: &[V], _start_index: usize) -> Result<(), crate::Error> {
        todo!("write values not implemented since wgpu buffers are async");
        // *self
        //     .buffer
        //     .get_mapped_range_mut(..)
        //     .copy_from_slice(&bytemuck::cast_slice(values));
        // Ok(())
    }
}

impl From<BufferType> for wgpu::BufferUsages {
    fn from(value: BufferType) -> Self {
        match value {
            BufferType::Vertex => wgpu::BufferUsages::VERTEX,
            BufferType::Index => wgpu::BufferUsages::INDEX,
            BufferType::Uniform => wgpu::BufferUsages::UNIFORM,
        }
    }
}

impl BufferType {
    pub fn memory_type_filter(&self) -> MemoryTypeFilter {
        match self {
            BufferType::Vertex => {
                MemoryTypeFilter::PREFER_HOST | MemoryTypeFilter::HOST_SEQUENTIAL_WRITE
            }
            BufferType::Index => {
                MemoryTypeFilter::PREFER_HOST | MemoryTypeFilter::HOST_SEQUENTIAL_WRITE
            }
            BufferType::Uniform => {
                MemoryTypeFilter::PREFER_HOST | MemoryTypeFilter::HOST_SEQUENTIAL_WRITE
            }
        }
    }
}

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
