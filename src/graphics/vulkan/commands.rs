use std::sync::Arc;

use vulkano::{
    command_buffer::{AutoCommandBufferBuilder, PrimaryAutoCommandBuffer},
    descriptor_set::DescriptorSet,
    pipeline::{GraphicsPipeline, Pipeline},
};

use crate::graphics::{DrawCall, RenderError, RendererOk};

pub struct VulkanCommandsCtx {
    pub(crate) builder: AutoCommandBufferBuilder<PrimaryAutoCommandBuffer>,
    pub(crate) current_pipeline: Arc<GraphicsPipeline>,
}

impl VulkanCommandsCtx {
    pub fn set_vertex_buffer<V: crate::graphics::BufferValue>(
        &mut self,
        buffer: &super::buffer::VulkanBuffer<V>,
    ) -> RendererOk {
        self.builder
            .bind_vertex_buffers(0, buffer.subbuffer.clone())
            .map_err(|_| RenderError::ResourceMissing("Bad draw".to_string()))?;

        Ok(())
    }

    pub fn set_index_buffer(
        &mut self,
        buffer: &super::buffer::VulkanBuffer<crate::graphics::Index>,
    ) -> RendererOk {
        self.builder
            .bind_index_buffer(buffer.subbuffer.clone())
            .map_err(|_| RenderError::ResourceMissing("Bad draw".to_string()))?;

        Ok(())
    }

    pub fn set_view_uniforms(
        &mut self,
        descriptor_set: Arc<DescriptorSet>,
    ) -> Result<(), Box<dyn std::error::Error>> {
        self.builder
            .bind_descriptor_sets(
                vulkano::pipeline::PipelineBindPoint::Graphics,
                self.current_pipeline.layout().clone(),
                1,
                descriptor_set,
            )
            .map_err(|e| e.to_string())?;
        Ok(())
    }

    pub fn set_descriptor_set(
        &mut self,
        set: u32,
        descriptor_set: Arc<DescriptorSet>,
    ) -> Result<(), Box<dyn std::error::Error>> {
        self.builder
            .bind_descriptor_sets(
                vulkano::pipeline::PipelineBindPoint::Graphics,
                self.current_pipeline.layout().clone(),
                set,
                descriptor_set,
            )
            .map_err(|e| e.to_string())?;
        Ok(())
    }

    pub fn draw(&mut self, draw_call: DrawCall) -> RendererOk {
        // println!("Drawing one thing.");

        unsafe {
            self.builder
                .draw_indexed(
                    draw_call.num_indices as u32,
                    1,
                    draw_call.start_offset as u32,
                    0,
                    0,
                )
                .map_err(|e| {
                    eprintln!("{e}");
                    RenderError::Draw(format!("{:?}", e))
                })?;
        };

        Ok(())
    }
}
