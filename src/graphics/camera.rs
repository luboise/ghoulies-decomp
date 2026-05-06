use cgmath::SquareMatrix as _;

#[derive(Debug, Default, Clone)]
pub struct Camera {
    pub transform: crate::maths::Transform,
}

impl From<Camera> for super::ViewUniforms {
    fn from(value: Camera) -> Self {
        let flip_m = {
            let mut m = crate::maths::Mat4::identity();
            m[0][0] = -1.0;
            m
        };

        // TODO: Put these values as fields on the camera
        let proj = cgmath::perspective(cgmath::Deg(90.0), 16.0 / 9.0, 0.1, 1000.0);

        Self {
            view: value.transform.model_matrix().into(),
            projection: (flip_m * proj).into(),
        }
    }
}
