use vulkano::command_buffer::{AutoCommandBufferBuilder, PrimaryAutoCommandBuffer};

use crate::graphics::{
    BufferValue, CommandSubmit, DrawCall, Render, RenderError, RendererOk, VulkanRenderer,
};

pub struct VulkanCommandsCtx {
    pub(crate) builder: AutoCommandBufferBuilder<PrimaryAutoCommandBuffer>,
}

/*
pub trait CommandSubmit<VB, IB> where VB: VertexBuffer, IB: IndexBuffer {
    fn set_index_buffer(&mut self, buffer_index: RenderIndex) -> RendererOk;


    fn vertex_buffers(&mut self) -> RendererRes<&[VertexBuffer]>;
    fn set_vertex_buffer(&mut self, buffer_index: RenderIndex) -> RendererOk;



    fn set_vertex_buffers(&mut self, vertex_buffers: &[VB]);

    fn index_buffer(&self, buffer_index: RenderIndex) -> Option<IndexBuffer>;

    fn set_index_buffer(&mut self, index_buffer: &IB);

    fn draw(&mut self, DrawCall{ num_indices, start_offset })

}

*/

impl CommandSubmit<VulkanRenderer> for VulkanCommandsCtx {
    fn set_vertex_buffer<V: BufferValue>(
        &mut self,
        buffer: &<VulkanRenderer as Render>::VertexBufferType<V>,
    ) -> RendererOk {
        self.builder
            .bind_vertex_buffers(0, buffer.subbuffer.clone())
            .map_err(|_| RenderError::ResourceMissing("Bad draw".to_string()))?;

        Ok(())
    }

    fn set_index_buffer(
        &mut self,
        buffer: &<VulkanRenderer as Render>::IndexBufferType,
    ) -> RendererOk {
        self.builder
            .bind_index_buffer(buffer.subbuffer.clone())
            .map_err(|_| RenderError::ResourceMissing("Bad draw".to_string()))?;

        Ok(())
    }

    fn draw(&mut self, draw_call: DrawCall) -> RendererOk {
        println!("Drawing one thing.");

        unsafe {
            self.builder
                .draw_indexed(
                    draw_call.num_indices as u32,
                    1,
                    draw_call.start_offset as u32,
                    0,
                    0,
                )
                .map_err(|e| RenderError::Draw(format!("{:?}", e)))?;
        };

        Ok(())
    }
}
