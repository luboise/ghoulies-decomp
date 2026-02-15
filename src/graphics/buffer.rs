use crate::graphics::{RendererOk, Vertex};

pub type Index = u32;

pub trait Buffer<T> {
    /// Maximum number of T this buffer can hold
    fn len(&self) -> usize;
    fn write_values(&mut self, values: &[T], start_index: usize) -> RendererOk;

    /// Number of bytes allocated to this buffer
    fn capacity_bytes(&self) -> usize {
        self.len() * size_of::<T>()
    }

    fn can_write(&self, data: &[T], start_index: usize) -> bool {
        data.len() != 0
            && start_index < self.len()
            && start_index.checked_add(data.len()).unwrap_or(usize::MAX) <= self.len()
    }
}

pub trait VertexBuffer<V: Vertex>: Buffer<V> {}

/*
pub struct VertexBuffer<V: Vertex, B: Buffer<V: Vertex>> {
    num_vertices: usize,
    buffer: B,
}
*/

/*

impl<V: Vertex, B: Buffer<V>> Buffer<V> for VertexBuffer<V, B> {
    fn capacity(&self) -> usize {
        self.num_vertices
    }

    fn capacity_bytes(&self) -> usize {
        self.num_vertices * size_of::<V>()
    }

    fn write(&mut self, vertices: &[V], start_index: usize) -> RendererOk {
        self.buffer.write(vertices, start_index)
    }
}

pub struct IndexBuffer<B: Buffer<Index>> {
    num_indices: usize,
    buffer: B,
}

impl<B: Buffer<Index>> Buffer<Index> for IndexBuffer<B> {
    /// Maximum number of vertices this buffer can hold
    fn capacity(&self) -> usize {
        self.num_indices
    }

    fn capacity_bytes(&self) -> usize {
        self.num_vertices * size_of::<V>()
    }

    fn write(&mut self, vertices: &[V], start_index: usize) -> RendererOk {
        self.buffer.write(vertices, start_index)
    }
}
*/
