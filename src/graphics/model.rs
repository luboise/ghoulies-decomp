use bnl::asset::model::ModelDescriptor;

#[derive(Debug)]
pub struct Model {
    descriptor: ModelDescriptor,
    // TODO: skeleton2: Skeleton,
    // TODO: skeleton: Skeleton,
    // TODO: bone_indices: [u32; 20],
}

impl super::Draw for Model {
    fn draw(&self, ctx: &mut crate::graphics::RenderContext) -> Result<(), crate::Error> {
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
        descriptor: &ModelDescriptor,
        has_skeleton: bool,
        has_0x3: bool,
    ) -> Result<Self, crate::Error> {
        // TODO: Create the model
        Ok(Self {
            descriptor: descriptor.clone(),
        })
    }

    fn draw_with_affine(
        &self,
        ctx: &mut crate::graphics::RenderContext,
    ) -> Result<(), crate::Error> {
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

        Ok(())
    }
}
