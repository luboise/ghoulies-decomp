use cgmath::{InnerSpace, Matrix, num_traits::Float};

#[derive(Debug, Clone)]
pub struct Camera {
    pub position: cgmath::Point3<f32>,
    pub yaw: cgmath::Rad<f32>,
    pub pitch: cgmath::Rad<f32>,
}

impl Default for Camera {
    fn default() -> Self {
        Self {
            position: cgmath::Point3::new(0.0, 0.0, 0.0),
            yaw: cgmath::Rad(0.0),
            pitch: cgmath::Rad(0.0),
        }
    }
}

const OPENGL_TO_WGPU_MATRIX: cgmath::Matrix4<f32> = cgmath::Matrix4::from_cols(
    cgmath::Vector4::new(1.0, 0.0, 0.0, 0.0),
    cgmath::Vector4::new(0.0, 1.0, 0.0, 0.0),
    cgmath::Vector4::new(0.0, 0.0, 0.5, 0.0),
    cgmath::Vector4::new(0.0, 0.0, 0.5, 1.0),
);

impl crate::maths::VecDirections for Camera {
    fn up(&self) -> crate::maths::Vec3 {
        crate::maths::Vec3::unit_y()
    }
    fn right(&self) -> crate::maths::Vec3 {
        let (yaw_sin, yaw_cos) = self.yaw.0.sin_cos();
        crate::maths::Vec3::new(yaw_cos, 0.0, yaw_sin).normalize()
    }
    fn forwards(&self) -> crate::maths::Vec3 {
        let (yaw_sin, yaw_cos) = self.yaw.0.sin_cos();
        crate::maths::Vec3::new(-yaw_sin, 0.0, yaw_cos).normalize()
    }
}

impl From<Camera> for super::ViewUniforms {
    fn from(camera: Camera) -> Self {
        let view = {
            let (sin_pitch, cos_pitch) = camera.pitch.0.sin_cos();
            let (sin_yaw, cos_yaw) = camera.yaw.0.sin_cos();

            // let direction =
            //     crate::maths::Vec3::new(cos_pitch * cos_yaw, sin_pitch, cos_pitch * sin_yaw);

            let direction =
                crate::maths::Vec3::new(sin_yaw * cos_pitch, sin_pitch, cos_yaw * cos_pitch);

            crate::maths::Mat4::look_to_lh(
                camera.position,
                direction.normalize(),
                crate::maths::Vec3::unit_y(),
            )
        };

        const NEAR: f32 = 0.1;
        const FAR: f32 = 1000.0;

        let projection = {
            let fov_y: f32 = 90.0.to_radians();
            let scale_factor = 1.0 / ((fov_y / 2.0).tan());

            crate::maths::Mat4::from_cols(
                crate::maths::Vec4::new(scale_factor, 0.0, 0.0, 0.0),
                crate::maths::Vec4::new(0.0, scale_factor, 0.0, 0.0),
                crate::maths::Vec4::new(
                    0.0,
                    0.0,
                    -(FAR / (FAR - NEAR)),
                    -(FAR * NEAR / (FAR - NEAR)),
                ),
                crate::maths::Vec4::new(0.0, 0.0, -1.0, 0.0),
            )
        }
        .transpose();

        // OPENGL_TO_WGPU_MATRIX
        //                     * cgmath::perspective(cgmath::Deg(60.0), 16.0 / 9.0, 0.1, 1000.0)
        // * cgmath::ortho(-16.0, 16.0, -9.0, 9.0, 0.1, 4000.0)

        Self {
            view: view.into(),
            projection: projection.into(),
        }
    }
}

#[cfg(test)]
mod test {
    use cgmath::Zero;

    use super::*;
    use crate::maths::*;
    use cgmath::*;

    const DEFAULT_CAMERA: Camera = Camera {
        position: Point3::new(0.0, 0.0, 0.0),
        yaw: Rad(0.0),
        pitch: Rad(0.0),
    };

    #[test]
    fn up() {
        assert_eq!(DEFAULT_CAMERA.up(), Vec3::new(0.0, 1.0, 0.0));
    }

    #[test]
    fn right() {
        assert_eq!(DEFAULT_CAMERA.right(), Vec3::new(1.0, 0.0, 0.0));
    }

    #[test]
    fn forwards() {
        assert_eq!(DEFAULT_CAMERA.forwards(), Vec3::new(0.0, 0.0, 1.0));
    }
}
