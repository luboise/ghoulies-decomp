pub mod actor;

pub mod scene_control_obj;
pub use scene_control_obj::SceneControlObj;

use crate::utility::Ptr;

pub trait Params {
    type Params;
}

impl Params for ObjectData {
    type Params = ObjectParams;
}

#[derive(Debug, Default)]
pub struct ObjectDatabase {
    scene_controls: Vec<Ptr<SceneControlObj>>,
}

impl ObjectDatabase {
    pub fn scene_controls(&self) -> &Vec<Ptr<SceneControlObj>> {
        &self.scene_controls
    }
}

/*
pub trait ObjectLike {
    const OBJECT_SIZE: usize;
    const PARAMS_SIZE: usize;

    fn new(params: &Self::Params) -> Result<Self, crate::Error>;
}
*/

#[repr(C)]
pub struct ObjectParams {
    size: u16,
    obj_init_value: u16,
    type_index: u16,
    some_u16: u16,
}

#[derive(Debug)]
pub struct ObjectData {
    size: u16,
    obj_init_value: u16,
    type_index: u16,
    some_u16: u16,
}

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

pub trait Object {
    fn ctor() -> Result<Box<Self>, crate::Error>;
    fn dtor(self) -> Result<Box<Self>, crate::Error>;
}

pub trait Avatar: Object {
    fn a(&self);
}

#[derive(Debug)]
pub struct AvatarData {
    obj: ObjectData,
}

impl AsRef<ObjectData> for AvatarData {
    fn as_ref(&self) -> &ObjectData {
        &self.obj
    }
}
impl AsMut<ObjectData> for AvatarData {
    fn as_mut(&mut self) -> &mut ObjectData {
        &mut self.obj
    }
}
