use crate::graphics::types::BufferType;

pub struct WgpuBuffer<V: bytemuck::Pod + bytemuck::Zeroable> {
    pub buffer_type: BufferType,
    pub buffer: wgpu::Buffer,
    pub length: usize,

    // Need to enforce type on buffer
    pub marker: std::marker::PhantomData<V>,
}

impl<V: bytemuck::Pod + bytemuck::Zeroable> WgpuBuffer<V> {
    pub fn len(&self) -> usize {
        self.length
    }

    pub fn is_empty(&self) -> bool {
        self.len() == 0
    }

    pub fn write(&self, queue: &::wgpu::Queue, v: V) {
        queue.write_buffer(&self.buffer, 0, bytemuck::bytes_of(&v));
    }
}

impl<V: bytemuck::Pod + bytemuck::Zeroable> crate::graphics::Buffer<V> for WgpuBuffer<V> {
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
            BufferType::Uniform => wgpu::BufferUsages::UNIFORM | wgpu::BufferUsages::COPY_DST,
        }
    }
}
