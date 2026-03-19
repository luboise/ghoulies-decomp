use std::ptr::read_unaligned;

#[derive(Debug)]
pub struct XBEFile {
    bytes: Vec<u8>,
    header: xbpatch_core::xbe::XBEHeader,
    memory_map: xbpatch_core::memory::MemoryMap,
}

impl XBEFile {
    pub fn new(path: impl AsRef<std::path::Path>) -> Result<Self, Box<dyn std::error::Error>> {
        let bytes = std::fs::read(&path)?;
        let header = xbpatch_core::xbe::XBEHeader::from_file(&mut std::fs::File::open(&path)?)?;
        let memory_map = xbpatch_core::memory::MemoryMap::from_xbe_header(&header);

        Ok(Self {
            bytes,
            header,
            memory_map,
        })
    }

    pub fn get<T: Sized>(&self, offset: u32) -> Result<T, Box<dyn std::error::Error>> {
        let start_offset = self.memory_map.get_raw_offset(offset)? as usize;
        let end_offset = start_offset + size_of::<T>();

        if start_offset >= self.bytes.len() || end_offset >= self.bytes.len() {
            return Err("Invalid access into XBE.".into());
        }

        let ptr = self.bytes[start_offset..].as_ptr() as *const T;
        unsafe { Ok(read_unaligned(ptr)) }
    }
}
