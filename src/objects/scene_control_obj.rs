use crate::objects::ObjectData;

#[derive(Debug)]
pub struct SceneControlObj {
    object: ObjectData,
    node: crate::utility::EmbeddedNode<Self>,
    // TODO: Figure out unknown 8 bytes here
    pad: [u8; 8],
    node_2: crate::utility::EmbeddedNode<Self>,
    time_elapsed: f32,
}

impl AsRef<ObjectData> for SceneControlObj {
    fn as_ref(&self) -> &ObjectData {
        &self.object
    }
}

impl AsMut<ObjectData> for SceneControlObj {
    fn as_mut(&mut self) -> &mut ObjectData {
        &mut self.object
    }
}
