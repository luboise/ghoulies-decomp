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

impl TryFrom<bnl::D3DFormat> for ColourFormat {
    type Error = crate::Error;

    fn try_from(value: bnl::D3DFormat) -> Result<Self, Self::Error> {
        use bnl::d3d::{D3DFormat, LinearColour, StandardFormat};

        match value {
            D3DFormat::Standard(standard) => match standard {
                StandardFormat::Unknown
                | StandardFormat::P8
                | StandardFormat::L8
                | StandardFormat::A8L8
                | StandardFormat::AL8
                | StandardFormat::L16
                | StandardFormat::V8U8
                | StandardFormat::L6V5U5
                | StandardFormat::X8L8V8U8
                | StandardFormat::Q8W8V8U8
                | StandardFormat::V16U16
                | StandardFormat::D16
                | StandardFormat::D24S8
                | StandardFormat::F16
                | StandardFormat::F24S8
                | StandardFormat::YUY2
                | StandardFormat::UYVY => (),
                StandardFormat::DXT1 | StandardFormat::DXT2Or3 | StandardFormat::DXT4Or5 => {
                    return Ok(ColourFormat::RGBA);
                }
            },
            D3DFormat::Linear(linear_colour) => match linear_colour {
                LinearColour::A1R5G5B5
                | LinearColour::A4R4G4B4
                | LinearColour::A8B8G8R8
                | LinearColour::A8R8G8B8
                | LinearColour::B8G8R8A8
                | LinearColour::R4G4B4A4
                | LinearColour::R5G5B5A1
                | LinearColour::R8G8B8A8 => return Ok(ColourFormat::RGBA),

                LinearColour::A8
                | LinearColour::G8B8
                | LinearColour::R5G6B5
                | LinearColour::R6G5B5
                | LinearColour::R8B8
                | LinearColour::X1R5G5B5
                | LinearColour::X8R8G8B8 => (),
            },
            D3DFormat::VertexData
            | D3DFormat::Index16
            | D3DFormat::Swizzled(_)
            | D3DFormat::Luminance(_)
            | D3DFormat::ForceDWORD => (),
        }

        Err("unimplemented conversion for D3DFormat {value}".into())
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
