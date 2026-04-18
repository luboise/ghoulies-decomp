use bnl::asset::AssetName;

use crate::{
    maths::Vec3,
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

#[derive(Debug)]
pub struct Avatar {
    object: Object,
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

    fn ctor(
        create_ctx: &mut ObjectCreateContext,
        params: &Self::Params,
    ) -> Result<Self, crate::Error> {
        Ok(Self {
            object: Object::ctor(create_ctx, &params.obj_params)?,
        })
    }

    fn dtor(self) -> Result<(), crate::Error> {
        todo!()
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
        create_ctx: &mut super::ObjectCreateContext,
        params: &Self::Params,
    ) -> Result<Self, crate::Error> {
        Ok(Self {
            avatar: Avatar::ctor(create_ctx, &params.avatar_params)?,
        })
    }

    fn dtor(self) -> Result<(), crate::Error> {
        todo!()
    }
}
