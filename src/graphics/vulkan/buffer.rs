use vulkano::{
    Validated,
    buffer::{AllocateBufferError, BufferUsage, Subbuffer},
    memory::allocator::MemoryTypeFilter,
    sync::HostAccessError,
};

use super::RenderError;

pub struct VulkanBuffer<V> {
    pub buffer_type: BufferType,
    pub subbuffer: Subbuffer<[V]>,
    pub length: usize,
}

impl<V> VulkanBuffer<V> {
    pub fn len(&self) -> usize {
        self.length
    }

    pub fn is_empty(&self) -> bool {
        self.len() == 0
    }
}

impl<V: crate::graphics::BufferValue> crate::graphics::Buffer<V> for VulkanBuffer<V> {
    fn len(&self) -> usize {
        self.subbuffer.len() as usize
    }

    fn write_values(&mut self, values: &[V], start_index: usize) -> super::RendererOk {
        self.subbuffer.write_values(values, start_index)
    }
}

pub enum BufferType {
    Vertex,
    Index,
    Uniform,
}

impl BufferType {
    pub fn usage(&self) -> BufferUsage {
        match self {
            Self::Vertex => BufferUsage::VERTEX_BUFFER,
            Self::Index => BufferUsage::INDEX_BUFFER,
            Self::Uniform => BufferUsage::UNIFORM_BUFFER,
        }
    }

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
