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

/*
trait FromImport<R: Render> {
    pub fn from_import(renderer: &mut R, import: Self) -> Result<Self, Box<dyn std::error::Error>>;
}

impl FromImport for crate::graphics::texture::Texture {}

pub fn from_import<R: Render>(renderer: &mut R, import: ImportedTexture) -> RendererRes<Self> {
    Self::from_image_params(renderer, import)
}

impl Texture {
    pub fn from_image_params<R: Render, IP: Into<ImageParams>>(
        renderer: &mut R,
        params: IP,
    ) -> RendererRes<Self> {
        let img = renderer.create_image(params.into());

        Ok(Self {
            width: img.width(),
            height: img.height(),
            image_handle: img,
        })
    }

    pub fn from_import<R: Render>(
        renderer: &mut R,
        import: ImportedTexture,
    ) -> super::RendererRes<Self> {
        Self::from_image_params(renderer, import)
    }
}
*/
