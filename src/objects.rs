pub mod actor;
pub mod avatar;
pub mod scene_control_obj;

pub use scene_control_obj::SceneControlObj;
use std::collections::VecDeque;

use crate::{objects::avatar::Avatar, utility::Ptr};

pub trait Params {
    type Params;
}

impl Params for Object {
    type Params = ObjectParams;
}

#[derive(Default)]
pub struct ObjectDatabase {
    pub new_scene_controls: VecDeque<Ptr<SceneControlObj>>,
    pub scene_controls: VecDeque<Ptr<SceneControlObj>>,
    pub new_avatars: VecDeque<Ptr<Avatar>>,
    pub avatars: VecDeque<Ptr<Avatar>>,
}

/*
pub trait ObjectLike {
    const OBJECT_SIZE: usize;
    const PARAMS_SIZE: usize;

    fn new(params: &Self::Params) -> Result<Self, crate::Error>;
}
*/

/*
impl ObjectLike for Object {
    type Params = ObjectParams;
    const OBJECT_SIZE: usize = 8;
    const PARAMS_SIZE: usize = 8;

    fn new(params: &Self::Params) -> Result<Self, crate::Error> {
        Ok(Self {
            size: params.size,
            obj_init_value: params.obj_init_value,
            type_index: params.type_index,
            some_u16: params.some_u16,
        })
    }
}
*/

type ObjectCreateContext = crate::App;
// pub struct ObjectCreateContext {
//     asset_database: &crate::assets::AssetDatabase
// }

pub trait ObjectLike: Sized {
    type Params;

    fn ctor(ctx: &mut ObjectCreateContext, params: &Self::Params) -> Result<Self, crate::Error>;
    fn dtor(self) -> Result<(), crate::Error>;
}

const _: () = assert!(size_of::<ObjectParams>() == 8);
#[repr(C)]
#[derive(Debug, Clone)]
pub struct ObjectParams {
    size: u16,
    obj_init_value: u16,
    type_index: u16,
    some_u16: u16,
}

impl ObjectLike for Object {
    type Params = ObjectParams;

    fn ctor(ctx: &mut ObjectCreateContext, params: &Self::Params) -> Result<Self, crate::Error> {
        Ok(Self {
            size: params.size,
            obj_init_value: params.obj_init_value,
            type_index: params.type_index,
            some_u16: params.some_u16,
        })
    }

    fn dtor(self) -> Result<(), crate::Error> {
        todo!()
    }
}

#[derive(Debug)]
pub struct Object {
    size: u16,
    obj_init_value: u16,
    type_index: u16,
    some_u16: u16,
}
