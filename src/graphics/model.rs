use bnl::asset::model::{
    ModelDescriptor,
    nd::{NdType, get_vertex_positions},
};

use crate::graphics::types::Vertex3D;

use super::BufferType;

pub struct Model {
    descriptor: ModelDescriptor,
    resource: Vec<u8>,

    vertex_buffer: super::WgpuBuffer<Vertex3D>,
    index_buffer: super::WgpuBuffer<super::Index>,
    textures: Vec<super::Texture>,
    // TODO: skeleton2: Skeleton,
    // TODO: skeleton: Skeleton,
    // TODO: bone_indices: [u32; 20],
}

impl super::Draw for Model {
    fn draw(&self, ctx: &mut crate::graphics::RenderPass) -> Result<(), crate::Error> {
        /*
        vec3 translation;

        translation.x = affine->m[0][3];
        translation.y = affine->m[1][3];
        translation.z = affine->m[2][3];
                          /* If it has Model subres 0x3 */
        if ((~(instance->descriptor->flags >> 1) & 1) != 0) {
          Graphics::SetModelSubres0x3Values(&translation);
          setTextures(instance);
          DrawTheThing(instance,affine,param_3);
          return;
        }
                          /* RGBA */
        Graphics::SetRoomLighting(0x3f800000,0x3f800000,0x3f800000,0x3f800000);
        ClearBinaryEntry();
                          /* Disable for chrome effect */
        Graphics::UpdateMatrices(&translation,false);
        */
        // TODO: Load all of the textures in
        // (could skip in favour keeping Vec<VkImage>)

        self.draw_with_affine(ctx)
    }
}

impl Model {
    pub fn new(
        ctx: &mut crate::graphics::RenderContext,
        descriptor: &ModelDescriptor,
        resource: &[u8],
        _has_skeleton: bool,
        _has_0x3: bool,
    ) -> Result<Self, crate::Error> {
        let model = descriptor
            .model_subresource
            .as_ref()
            .ok_or_else(|| "CAN'T DRAW MODEL WITHOUT DESCRIPTOR MODELS".to_owned())?;

        let textures = descriptor
            .texture_subresource
            .iter()
            .enumerate()
            .map(|(i, descriptor)| {
                let start = descriptor.texture_offset() as usize;
                let end = start + descriptor.texture_size() as usize;
                let data = resource[start..end].to_vec();

                let image_params = super::ImageParams {
                    width: descriptor.width().into(),
                    height: descriptor.height().into(),
                    colour_format: super::d3d_to_wgpu_texformat(descriptor.format()).ok_or_else(
                        || {
                            format!(
                                "texture {i}: unrecognised texture format {format:?}",
                                format = descriptor.format(),
                            )
                        },
                    )?,
                    data,
                };

                super::Texture::from_image_params(&mut ctx.renderer, image_params)
            })
            .collect::<Result<Vec<_>, _>>()?;

        println!("loaded {} textures", textures.len());

        #[expect(clippy::never_loop)]
        // TODO: Refactor this garbage
        // (buffers just for testing, need proper node traversal)
        for node in model.primitives() {
            let vb_node = node
                .heirarchy()
                .find(|nd| nd.nd_type() == NdType::VertexBuffer)
                .ok_or("no ndVertexBuffer")?;

            let vertex_buffer = {
                match &*vb_node.data {
                    bnl::asset::model::nd::NdData::VertexBuffer {
                        resource_views_ptr: _,
                        num_resource_views: _,
                        resource_views,
                    } => {
                        // TODO: Make this safer (i am lazy)
                        let vertices = get_vertex_positions(resource, resource_views)
                            .ok_or_else(|| "no vertex positions available".to_owned())?
                            .into_iter()
                            .map(|position| Vertex3D {
                                position,
                                ..Default::default()
                            })
                            .collect::<Vec<_>>();

                        ctx.renderer
                            .create_static_buffer::<super::types::Vertex3D>(
                                BufferType::Vertex,
                                &vertices,
                            )?
                    }
                    _ => return Err("ndVertexBuffer did not match nd type".into()),
                }
            };

            let indices = vb_node
                .heirarchy()
                .filter_map(|nd| match &*nd.data {
                    bnl::asset::model::nd::NdData::PushBuffer(nd_push_buffer_data) => Some({
                        nd_push_buffer_data
                            .indices()
                            .into_iter()
                            .map(u32::from)
                            .collect::<Vec<_>>()
                    }),
                    _ => None,
                })
                .flatten()
                .collect::<Vec<_>>();

            let index_buffer = ctx
                .renderer
                .create_static_buffer::<crate::graphics::Index>(BufferType::Index, &indices)?;

            return Ok(Self {
                descriptor: descriptor.clone(),
                resource: resource.to_owned(),
                vertex_buffer,
                index_buffer,
                textures,
            });
        }

        Err("unable to get buffers from primitives".into())
    }

    fn draw_with_affine(&self, render_pass: &mut ::wgpu::RenderPass) -> Result<(), crate::Error> {
        /* TODO: Bind skeleton
          Skeleton *skeleton_instance;
          Graphics::SomeModelContext = param_3;
          Graphics::SetSomePtr1(&instance->globalUintsFlags);
          skeleton_instance = instance->skeleton;
          if (skeleton_instance == NULL) {
            skeleton_instance = instance->skeleton2;
          }
          Skeleton::bindFromModelInstance(instance,skeleton_instance);
          g_avatarTransform.m[0][0] = affine->m[0][0];
          g_avatarTransform.m[0][1] = affine->m[1][0];
          g_avatarTransform.m[0][2] = affine->m[2][0];
          g_avatarTransform.m[1][0] = affine->m[0][1];
          g_avatarTransform.m[1][1] = affine->m[1][1];
          g_avatarTransform.m[1][2] = affine->m[2][1];
          g_avatarTransform.m[2][0] = affine->m[0][2];
          g_avatarTransform.m[2][1] = affine->m[1][2];
          g_avatarTransform.m[2][2] = affine->m[2][2];
          g_avatarTransform.m[3][0] = affine->m[0][3];
          g_avatarTransform.m[3][1] = affine->m[1][3];
          g_avatarTransform.m[3][2] = affine->m[2][3];
          g_avatarTransform.m[2][3] = 0.0;
          g_avatarTransform.m[1][3] = 0.0;
          g_avatarTransform.m[0][3] = 0.0;
          g_avatarTransform.m[3][3] = 1.0;
        */

        // Graphics::GetWorldTransform(&g_avatarTransform);
        // DAT_005079ec = instance;

        // TODO: Draw from root node all the way out
        // println!("drawing root node");

        // ??? Forgor what this is
        // DAT_005079e4 = 0;

        /*
        if self.textures.len() >= 2 {
            ctx.set_textures(Some(
                self.textures.first().unwrap().image_handle.clone(),
                self.textures.iter().nth(1).unwrap().clone(),
            ));
        }
        */

        render_pass.set_vertex_buffer(0, self.vertex_buffer.buffer.slice(..));
        render_pass.set_index_buffer(
            self.index_buffer.buffer.slice(..),
            match size_of::<super::Index>() {
                2 => wgpu::IndexFormat::Uint16,
                4 => wgpu::IndexFormat::Uint32,
                _ => panic!(
                    "unknown index format of size {} bytes",
                    size_of::<super::Index>()
                ),
            },
        );

        let draw_call = super::DrawCall {
            num_indices: self.index_buffer.len(),
            start_offset: 0,
            primitive_type: super::types::PrimitiveType::TriangleStrip,
        };

        const BASE_VERTEX: i32 = 0;

        let first_idx = draw_call.start_offset.try_into()?;
        let last_idx = first_idx + draw_call.num_indices as u32;

        render_pass.draw_indexed(first_idx..last_idx, BASE_VERTEX, 0..1);

        Ok(())
    }
}
