use std::sync::Arc;

use vulkano::VulkanLibrary;
use vulkano::instance::{Instance, InstanceCreateFlags, InstanceCreateInfo};

pub struct GraphicsCtx {
    vulkan_library: Arc<VulkanLibrary>,
    vulkan_instance: Arc<Instance>,
}

impl GraphicsCtx {
    pub fn new() -> Result<Self, Box<dyn std::error::Error>> {
        let vulkan_library = VulkanLibrary::new()?;
        let vulkan_instance = Instance::new(
            vulkan_library.clone(),
            InstanceCreateInfo {
                flags: InstanceCreateFlags::ENUMERATE_PORTABILITY,
                ..Default::default()
            },
        )?;
        Ok(Self {
            vulkan_library,
            vulkan_instance,
        })
    }
}
