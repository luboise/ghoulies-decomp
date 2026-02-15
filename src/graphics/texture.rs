use std::sync::Arc;

#[derive(Debug)]
pub enum ColourFormat {
    RGB,
    RGBA,
}

impl ColourFormat {
    const fn get_pixel_stride(&self) -> usize {
        8 * self.num_channels()
    }

    const fn num_channels(&self) -> usize {
        match self {
            ColourFormat::RGB => 3,
            ColourFormat::RGBA => 4,
        }
    }
}

#[derive(Debug)]
pub struct Texture {
    pub(crate) width: usize,
    pub(crate) height: usize,

    // TODO: Implement colour formats and such things
    // tex_type: TextureType,
    pub(crate) image_handle: Arc<ImageHandle>,
}

#[derive(Debug)]
pub struct ImageHandle {
    width: usize,
    height: usize,
    internal_index: super::RenderIndex,
}

impl ImageHandle {
    pub fn width(&self) -> usize {
        self.width
    }

    pub fn height(&self) -> usize {
        self.height
    }
}
