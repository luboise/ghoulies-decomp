use crate::{objects::ObjectData, utility::EmbeddedNode};

#[derive(Debug)]
pub struct SceneControlObj {
    object: ObjectData,
    node: EmbeddedNode<Self>,
    // TODO: Figure out unknown 8 bytes here
    pad: [u8; 8],
    node_2: EmbeddedNode<Self>,
    time_elapsed: f32,
}

impl SceneControlObj {
    pub fn node_mut(&mut self) -> &mut EmbeddedNode<SceneControlObj> {
        &mut self.node
    }
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
