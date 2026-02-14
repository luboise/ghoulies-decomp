struct MemoryMap {}

pub struct XBEFile {
    memory_map: MemoryMap,
}

impl XBEFile {
    pub fn new(path: impl AsRef<std::path::Path>) -> Result<Self, Box<dyn std::error::Error>> {
        Ok(Self {
            memory_map: MemoryMap {},
        })
    }
}
