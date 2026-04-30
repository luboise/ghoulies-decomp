use crate::graphics::{self};

#[derive(Debug)]
pub struct ImportedTexture {
    pub width: usize,
    pub height: usize,
    pub d3d_format: bnl::D3DFormat,
    pub data: Vec<u8>,
}

impl TryFrom<ImportedTexture> for graphics::ImageParams {
    type Error = crate::Error;

    fn try_from(value: ImportedTexture) -> Result<Self, Self::Error> {
        Ok(Self {
            width: value.width,
            height: value.height,
            colour_format: crate::graphics::d3d_to_wgpu_texformat(value.d3d_format)
                .ok_or_else(|| format!("unrecognised d3d format: {:?}", value.d3d_format))?,
            data: value.data,
        })
    }
}
