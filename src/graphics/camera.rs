use cgmath::SquareMatrix as _;

use crate::graphics::ViewUniforms;

#[derive(Default, Clone)]
pub struct Camera {
    pub transform: crate::maths::Transform,
}

impl From<Camera> for ViewUniforms {
    fn from(value: Camera) -> Self {
        Self {
            view: value.transform.model_matrix().into(),
            // TODO: Put the projection matrix on the camera
            projection: crate::maths::Mat4::identity().into(),
        }
    }
}
