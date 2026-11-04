use cgmath::{InnerSpace, num_traits::Float};

use crate::maths::{Mat3, Mat4, Vec3};

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
    fn up(&self) -> Vec3 {
        Vec3::unit_y()
    }
    fn right(&self) -> Vec3 {
        let (yaw_sin, yaw_cos) = self.yaw.0.sin_cos();
        Vec3::new(yaw_cos, 0.0, yaw_sin).normalize()
    }
    fn forwards(&self) -> Vec3 {
        (Mat3::from_angle_y(self.yaw) * Vec3::unit_z()).normalize()
    }
}

impl From<Camera> for super::ViewUniforms {
    fn from(camera: Camera) -> Self {
        let view = {
            let (sin_pitch, cos_pitch) = camera.pitch.0.sin_cos();
            let (sin_yaw, cos_yaw) = camera.yaw.0.sin_cos();

            // let direction =
            //     crate::maths::Vec3::new(cos_pitch * cos_yaw, sin_pitch, cos_pitch * sin_yaw);

            let direction = Vec3::new(sin_yaw * cos_pitch, sin_pitch, cos_yaw * cos_pitch);

            Mat4::look_to_lh(camera.position, direction.normalize(), Vec3::unit_y())
        };

        const NEAR: f32 = 0.1;
        const FAR: f32 = 1000.0;

        let projection = cgmath::perspective(cgmath::Deg(67.0), 16.0 / 9.0, NEAR, FAR);

        // let projection = flip_z * projection;

        // z [-1, 1] => z [0, 1]
        let projection = OPENGL_TO_WGPU_MATRIX * projection;

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

        let mut cam = DEFAULT_CAMERA;
        cam.yaw += Deg(90.0).into();

        assert!((cam.forwards() - Vec3::unit_x()).magnitude() <= 0.1);
    }
}
