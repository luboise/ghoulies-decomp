use crate::{objects::Object, utility::EmbeddedNode};

#[derive(Debug)]
pub struct SceneControlObj {
    object: Object,
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

impl AsRef<Object> for SceneControlObj {
    fn as_ref(&self) -> &Object {
        &self.object
    }
}

impl AsMut<Object> for SceneControlObj {
    fn as_mut(&mut self) -> &mut Object {
        &mut self.object
    }
}
