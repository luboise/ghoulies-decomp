use crate::graphics::DrawCall;

pub struct WgpuCommandsCtx<'a> {
    pub encoder: wgpu::CommandEncoder,
    pub render_pass: wgpu::RenderPass<'a>,
}

impl<'a> WgpuCommandsCtx<'a> {
    pub fn set_vertex_buffer<V: crate::graphics::BufferValue>(
        &mut self,
        buffer: &super::buffer::WgpuBuffer<V>,
    ) -> Result<(), crate::Error> {
        self.render_pass
            .set_vertex_buffer(0, buffer.buffer.slice(..));

        Ok(())
    }

    pub fn set_index_buffer(
        &mut self,
        buffer: &super::buffer::WgpuBuffer<crate::graphics::Index>,
    ) -> Result<(), crate::Error> {
        self.render_pass.set_index_buffer(
            buffer.buffer.slice(..),
            match size_of::<crate::graphics::Index>() {
                16 => wgpu::IndexFormat::Uint16,
                32 => wgpu::IndexFormat::Uint32,
                _ => panic!("bad index size: {}", size_of::<crate::graphics::Index>()),
            },
        );
        Ok(())
    }

    pub fn set_view_uniforms(
        &mut self,
        descriptor_set: std::sync::Arc<vulkano::descriptor_set::DescriptorSet>,
    ) -> Result<(), Box<dyn std::error::Error>> {
        todo!();
        Ok(())
    }

    pub fn set_descriptor_set(
        &mut self,
        set: u32,
        // descriptor_set: Arc<DescriptorSet>,
    ) -> Result<(), Box<dyn std::error::Error>> {
        Ok(())
    }

    pub fn draw(&mut self, draw_call: &DrawCall) -> Result<(), crate::Error> {
        const BASE_VERTEX: i32 = 0;

        let first_idx = draw_call.start_offset.try_into()?;
        let last_idx = first_idx + draw_call.num_indices as u32;

        self.render_pass
            .draw_indexed(first_idx..last_idx, BASE_VERTEX, 0..1);

        Ok(())
    }
}
