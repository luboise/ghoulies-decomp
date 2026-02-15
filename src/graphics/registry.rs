use std::sync::Arc;

use crate::{
    assets::{ImportedPBRMaterial, PBRMaterial, Texture},
    rendering::{ImageParams, RendererRes, VulkanRenderer},
};

/// Helper struct which manages materials and textures for you granted that you give it a renderer
/// to keep. All behaviour that this has can be achieved manually by invoking those commands
/// yourself on the renderer, and this is only for utility.
#[derive(Debug)]
pub struct RenderRegistry {
    renderer: VulkanRenderer,

    materials: Vec<Arc<PBRMaterial>>,
    textures: Vec<Arc<Texture>>,
}

impl RenderRegistry {
    pub fn new(renderer: VulkanRenderer) -> RendererRes<Self> {
        Ok(Self {
            renderer,

            materials: vec![],
            textures: vec![],
        })
    }

    pub fn renderer(&self) -> &VulkanRenderer {
        &self.renderer
    }
    pub fn renderer_mut(&mut self) -> &mut VulkanRenderer {
        &mut self.renderer
    }

    /*
    pub fn add_material(&mut self, material: ImportedPBRMaterial) -> RendererRes<&PBRMaterial> {
        let tex_handle = match material.colour_texture_index {
            Some(tex) => {
                let params = ImageParams {
                    width: tex.width,
                    height: tex.height,
                    data: tex.data.clone(),
                };

                let new_texture = Arc::new(Texture::new(&mut self.renderer, params)?);

                self.textures.push(new_texture.clone());
                Some(new_texture)
            }
            None => None,
        };

        let base_colour = match material.base_colour {
            Some(col) => Some([col.x, col.y, col.z, col.w]),
            None => None,
        };

        let new_index = self.materials.len();
        self.materials.push(PBRMaterial {
            colour_texture: tex_handle,
            base_colour,
            metallic: material.metallic,
            roughness: material.roughness,
        });

        Ok(self
            .materials
            .get(new_index)
            .expect("Unable to get new material which was just pushed."))
    }
    */

    pub fn materials(&self) -> &Vec<PBRMaterial> {
        &self.materials
    }
    pub fn materials_mut(&mut self) -> &mut Vec<PBRMaterial> {
        &mut self.materials
    }

    pub fn textures(&self) -> &Vec<Arc<Texture>> {
        &self.textures
    }
    pub fn textures_mut(&mut self) -> &mut Vec<Arc<Texture>> {
        &mut self.textures
    }
}
