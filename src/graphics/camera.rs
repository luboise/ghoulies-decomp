use cgmath::SquareMatrix as _;

#[derive(Debug, Default, Clone)]
pub struct Camera {
    pub transform: crate::maths::Transform,
}

impl From<Camera> for super::ViewUniforms {
    fn from(value: Camera) -> Self {
        // TODO: Put these values as fields on the camera
        Self {
            view: value.transform.view_matrix().into(),
            projection: cgmath::perspective(cgmath::Deg(90.0), 16.0 / 9.0, 0.1, 1000.0).into(),
        }
    }
}
