#[derive(Debug, Clone, Copy)]
pub enum BufferType {
    Vertex,
    Index,
    Uniform,
}

pub type Vec2 = [f32; 2];
pub type Vec3 = [f32; 3];
pub type Vec4 = [f32; 4];

pub type Mat2 = [Vec2; 2];
pub type Mat3 = [Vec3; 3];
pub type Mat4 = [Vec4; 4];

// #[derive(Debug, Clone, Copy, BufferContents, Vertex)]
#[derive(Debug, Clone, Copy, bytemuck::Pod, bytemuck::Zeroable)]
#[repr(C, packed)]
pub struct Vertex3D {
    // #[name("a_position")]
    // #[format(R32G32B32_SFLOAT)]
    pub position: Vec3,

    // #[name("a_colour")]
    // #[format(R32G32B32_SFLOAT)]
    pub colour: Vec3,

    // #[name("a_normal")]
    // #[format(R32G32B32_SFLOAT)]
    pub normal: Vec3,

    // #[name("a_texcoords")]
    // #[format(R32G32_SFLOAT)]
    pub tex_coords: Vec2,

    // #[name("a_skin_indices")]
    // #[format(R32G32B32A32_UINT)]
    pub skin_indices: [u32; 4],

    // #[name("a_skin_weights")]
    // #[format(R32G32B32A32_SFLOAT)]
    pub skin_weights: Vec4,
}

impl Default for Vertex3D {
    fn default() -> Self {
        Self {
            position: [0f32, 0f32, 0f32],
            colour: [1f32, 1f32, 1f32],
            normal: Default::default(),
            tex_coords: Default::default(),
            skin_indices: [0, 0, 0, 0],
            skin_weights: [1.0, 0.0, 0.0, 0.0],
        }
    }
}

#[derive(Debug, Clone, Copy, bytemuck::Pod, bytemuck::Zeroable)]
#[repr(C)]
pub(crate) struct VertexTest {
    // #[name("a_position")]
    // #[format(R32G32B32_SFLOAT)]
    pub position: Vec3,
}

impl Default for VertexTest {
    fn default() -> Self {
        Self {
            position: [0f32, 0f32, 0f32],
        }
    }
}

#[derive(Debug, Clone)]
pub enum PrimitiveType {
    PointList = 0,
    LineList = 1,
    LineStrip = 2,

    TriangleList = 3,
    TriangleStrip = 4,
    TriangleFan = 5,

    LineListWithAdjacency = 6,
    LineStripWithAdjacency = 7,
    TriangleListWithAdjacency = 8,
    TriangleStripWithAdjacency = 9,
    // PatchList = 10
}

impl From<bnl::D3DPrimitiveType> for PrimitiveType {
    fn from(value: bnl::D3DPrimitiveType) -> Self {
        use bnl::D3DPrimitiveType;

        match value {
            D3DPrimitiveType::None => todo!(),
            D3DPrimitiveType::PointList => Self::PointList,
            D3DPrimitiveType::LineList => Self::LineList,
            D3DPrimitiveType::LineStrip => Self::LineStrip,
            D3DPrimitiveType::TriangleList => Self::TriangleList,
            D3DPrimitiveType::TriangleStrip => Self::TriangleStrip,
            D3DPrimitiveType::TriangleFan => Self::TriangleFan,
            // Unhandled/unsupported
            D3DPrimitiveType::LineLoop
            | D3DPrimitiveType::QuadList
            | D3DPrimitiveType::QuadStrip
            | D3DPrimitiveType::Polygon
            | D3DPrimitiveType::Max
            | D3DPrimitiveType::Invalid => Self::TriangleList,
        }
    }
}
