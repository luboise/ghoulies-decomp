use crate::graphics;

#[derive(Debug)]
pub struct ImportedTexture {
    pub width: usize,
    pub height: usize,
    pub colour_format: graphics::ColourFormat,
    pub data: Vec<u8>,
}

impl From<ImportedTexture> for graphics::ImageParams {
    fn from(value: ImportedTexture) -> Self {
        Self {
            width: value.width,
            height: value.height,
            colour_format: value.colour_format,
            data: value.data,
        }
    }
}
