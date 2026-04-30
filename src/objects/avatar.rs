use bnl::asset::{AssetDescriptor, AssetName};
use cgmath::Zero;

use crate::{
    maths::{AffineTransform, Quat, Vec3},
    objects::{Object, ObjectCreateContext, ObjectLike, ObjectParams},
};

// pub trait AvatarLike: ObjectLike {
//     fn on_message(&mut self, message: &mut crate::events::Message);
// }

const _: () = assert!(size_of::<AvatarParams>() == 0x334);
#[repr(C)]
#[derive(Debug, Clone)]
pub struct AvatarParams {
    obj_params: ObjectParams,
    position: Vec3,
    rotation_euler: Vec3,
    scale: f32,
    unknown_f32: f32,
    model_aid: AssetName,
    initial_animation_aid: AssetName,
    anim_table_aid: AssetName,
    callout_aid: AssetName,
    fx_emitter_impact_flash_aid: AssetName,
    impact_id: u32,
    ghoulybox_id_2: u16,
    unknown_u16: u16,
    has_shadow: u32,
    shadow_model_aid: AssetName,
}

pub struct Avatar {
    object: Object,
    position: Vec3,
    rotation_euler: Vec3,
    rotation_quaternion: Quat,
    scale: Vec3,
    physics_position: Vec3,
    // TODO: anim_table: AnimTable
    // TODO: anim_table_handled: u32
    // TODO: anim_ctx: AnimContext
    // TODO: bones: Box<Vec<Bone>>
    uniform_scale: f32,
    model: Option<crate::graphics::Model>,
    model_aid: String,

    draw_affine: AffineTransform,
}

/*
impl AsRef<Object> for Avatar {
    fn as_ref(&self) -> &Object {
        &self.obj
    }
}
impl AsMut<Object> for Avatar {
    fn as_mut(&mut self) -> &mut Object {
        &mut self.obj
    }
}
*/

impl ObjectLike for Avatar {
    type Params = AvatarParams;

    fn ctor(ctx: &mut ObjectCreateContext, params: &Self::Params) -> Result<Self, crate::Error> {
        let model: Option<crate::graphics::Model> = if params.model_aid[0] != 0 {
            let aid = String::from_utf8_lossy(&params.model_aid)
                .trim_matches('\0')
                .to_owned();

            let raw_asset = ctx.asset_database.get_raw_asset(&aid).ok_or_else(|| {
                format!(
                    "unable to get {}",
                    String::from_utf8_lossy(&params.model_aid).trim_matches('\0')
                )
            })?;

            let descriptor =
                bnl::asset::model::ModelDescriptor::from_bytes(raw_asset.descriptor_bytes())?;

            println!("loading avatar model {aid}");
            Some(crate::graphics::Model::new(
                ctx.render_context_mut(),
                &descriptor,
                &raw_asset
                    .resource_chunks()
                    .cloned()
                    .expect("no resource chunks")
                    .into_iter()
                    .flatten()
                    .collect::<Vec<_>>(),
                false,
                false,
            )?)
        } else {
            None
        };

        // TODO: Un-default these
        Ok(Self {
            object: Object::ctor(ctx, &params.obj_params)?,
            position: Vec3::zero(),
            rotation_euler: Vec3::zero(),
            rotation_quaternion: Quat::new(0.0, 0.0, 0.0, 1.0),
            scale: Vec3::new(1.0, 1.0, 1.0),
            physics_position: Vec3::zero(),
            uniform_scale: 1.0,
            model,
            model_aid: String::from_utf8_lossy(&params.model_aid)
                .trim_matches('\0')
                .into(),
            draw_affine: AffineTransform::default(),
        })
    }

    fn dtor(self) -> Result<(), crate::Error> {
        todo!()
    }
}

impl crate::graphics::Draw for Avatar {
    fn draw(&self, ctx: &mut crate::graphics::RenderPass) -> Result<(), crate::Error> {
        // ctx.draw_affine = self.draw_affine.clone();
        let Some(model) = &self.model else {
            // Original game allows for failure
            return Ok(());
        };

        model.draw(ctx)?;

        // For node in node tree:
        //     draw node with render context

        // let vb = self.vb.clone().unwrap();
        // let ib = self.ib.clone().unwrap();
        // let draw_calls = self.draw_calls.clone();

        // Draw everything
        // ctx.renderer
        //     .run_commands(|cmd| {
        //         cmd.set_vertex_buffer(&vb)?;
        //         cmd.set_index_buffer(&ib)?;
        //
        //         // cmd.set_view_uniforms(camera_descriptor_set.clone())
        //         //     .map_err(|e| graphics::RenderError::Draw(e.to_string()))?;
        //
        //         for draw_call in &draw_calls {
        //             ctx.draw(draw_call)?;
        //         }
        //         Ok(())
        //     })
        //     .map_err(|e| e.to_string())

        Ok(())
    }
}

#[repr(u32)]
#[derive(Debug, Clone)]
pub enum PowerupId {
    Null = 0,
    Book = 1,
    DizzyReaper = 2,
    EnergyBoost = 3,
    EnergyRobber = 4,
    EventComplete = 5,
    ExtraTime = 6,
    GhoulyFreeze = 7,
    InstantDeath = 8,
    Invisibility = 9,
    Invulnerability = 10,
    KnockDownMania = 11,
    MiniCooper = 12,
    PermanentWeaponBoost = 13,
    PlayerSlowDown = 14,
    PlayerSpeedUp = 15,
    RandomNasty = 16,
    ReverseControls = 17,
    ShockerBlocker = 18,
    TraitorFever = 19,
}

const _: () = assert!(size_of::<PowerupParams>() == 0x3c4);
#[derive(Debug, Clone)]
#[repr(C)]
pub struct PowerupParams {
    avatar_params: AvatarParams,
    powerup_id: PowerupId,
    unknown_u32_1: u32,
    unknown_u32_2: u32,
    powerup_texture_aid: AssetName,
    unknown_u32_3: u32,
}

pub struct Powerup {
    avatar: Avatar,
}

impl super::ObjectLike for Powerup {
    type Params = PowerupParams;

    fn ctor(
        ctx: &mut super::ObjectCreateContext,
        params: &Self::Params,
    ) -> Result<Self, crate::Error> {
        Ok(Self {
            avatar: Avatar::ctor(ctx, &params.avatar_params)?,
        })
    }

    fn dtor(self) -> Result<(), crate::Error> {
        todo!()
    }
}

impl crate::graphics::Draw for Powerup {
    fn draw(&self, ctx: &mut crate::graphics::RenderPass) -> Result<(), crate::Error> {
        self.avatar.draw(ctx)?;

        // TODO: Draw and update the texture here

        Ok(())
    }
}

const _: () = assert!(size_of::<ActorParams>() == 0x63c);
#[repr(C)]
#[derive(Debug, Clone)]
pub struct ActorParams {
    avatar_params: AvatarParams,
    unknown_i16_1: i16,
    unknown_u16_1: u16,
    unknown_u16_2: u16,
    strategy_objparams_aid: AssetName,
    ai_mind_objectparams_aid: AssetName,
    body_objparams_aid: AssetName,
    starting_weapon_aid: AssetName,
    ghoulybox_aid: AssetName,
    actor_attribs_aid: AssetName,
    unknown_u16_3: u16,
}
pub struct Actor {
    avatar: Avatar,
}

impl super::ObjectLike for Actor {
    type Params = ActorParams;

    fn ctor(ctx: &mut ObjectCreateContext, params: &Self::Params) -> Result<Self, crate::Error> {
        let avatar = Avatar::ctor(ctx, &params.avatar_params)?;
        Ok(Self { avatar })
    }

    fn dtor(self) -> Result<(), crate::Error> {
        todo!()
    }
}

impl crate::graphics::Draw for Actor {
    fn draw(&self, render_pass: &mut crate::graphics::RenderPass) -> Result<(), crate::Error> {
        self.avatar.draw(render_pass)?;

        // TODO: Draw and update the texture here

        Ok(())
    }
}
