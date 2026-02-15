use crate::graphics::{RenderIndex, RendererOk};

#[derive(Debug)]
pub struct Pipeline {}

impl Pipeline {
    pub fn set<T: ShaderConstant>(&mut self, index: RenderIndex, value: T) -> RendererOk {
        todo!();
    }

    pub fn set_texture(&mut self, index: RenderIndex, value: &[u8]) -> RendererOk {
        todo!();
    }

    pub fn set_sampler(&mut self, index: RenderIndex, value: &[u8]) -> RendererOk {
        todo!();
    }
}

pub trait ShaderConstant: Sized {
    const SIZE: usize = size_of::<Self>();

    fn as_shader_bytes(&self) -> Vec<u8>;
}

macro_rules! impl_shader_constant {
    ($t:ty) => {
        impl ShaderConstant for $t {
            fn as_shader_bytes(&self) -> Vec<u8> {
                self.to_le_bytes().to_vec()
            }
        }
    };
}

impl_shader_constant!(u8);
impl_shader_constant!(u16);
impl_shader_constant!(u32);
impl_shader_constant!(u64);

impl_shader_constant!(i8);
impl_shader_constant!(i16);
impl_shader_constant!(i32);
impl_shader_constant!(i64);

impl_shader_constant!(f32);
impl_shader_constant!(f64);
