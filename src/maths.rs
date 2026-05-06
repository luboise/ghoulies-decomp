use cgmath::{EuclideanSpace, Rotation, Rotation3, SquareMatrix};

pub type Vec2 = cgmath::Vector2<f32>;
pub type Vec3 = cgmath::Vector3<f32>;
pub type Vec4 = cgmath::Vector4<f32>;

const _: () = assert!(size_of::<Vec2>() == 8);
const _: () = assert!(size_of::<Vec3>() == 12);
const _: () = assert!(size_of::<Vec4>() == 16);

pub type Mat2 = cgmath::Matrix2<f32>;
pub type Mat3 = cgmath::Matrix3<f32>;
pub type Mat4 = cgmath::Matrix4<f32>;

const _: () = assert!(size_of::<Mat2>() == 4 * 4);
const _: () = assert!(size_of::<Mat3>() == 9 * 4);
const _: () = assert!(size_of::<Mat4>() == 16 * 4);

pub type Quat = cgmath::Quaternion<f32>;
const _: () = assert!(size_of::<Quat>() == 16);

#[derive(Debug, Clone)]
pub struct AffineTransform {
    r1: Vec4,
    r2: Vec4,
    r3: Vec4,
}

impl Default for AffineTransform {
    fn default() -> Self {
        Self {
            r1: Vec4::new(1.0, 0.0, 0.0, 0.0),
            r2: Vec4::new(0.0, 1.0, 0.0, 0.0),
            r3: Vec4::new(0.0, 0.0, 1.0, 0.0),
        }
    }
}

impl From<AffineTransform> for Mat4 {
    fn from(value: AffineTransform) -> Self {
        Mat4::from_cols(value.r1, value.r2, value.r3, [0.0, 0.0, 0.0, 1.0].into())
    }
}

#[derive(Debug, Clone)]
pub struct Transform {
    pub position: Vec3,
    pub rotation: Quat,
    pub scale: Vec3,
}

impl Default for Transform {
    fn default() -> Self {
        Self::identity()
    }
}

impl Transform {
    pub const fn identity() -> Self {
        Self {
            position: Vec3::new(0.0, 0.0, 0.0),
            rotation: Quat::new(0.0, 0.0, 0.0, 1.0),
            scale: Vec3::new(1.0, 1.0, 1.0),
        }
    }

    pub fn translated(self, pos: impl Into<Vec3>) -> Self {
        Self {
            position: self.position + pos.into(),
            rotation: self.rotation,
            scale: self.scale,
        }
    }

    pub fn rotated(self, rot: impl Into<Vec3>) -> Self {
        let Vec3 { x, y, z } = rot.into();

        let rot_x = Quat::from_angle_x(cgmath::Rad(x));
        let rot_y = Quat::from_angle_y(cgmath::Rad(y));
        let rot_z = Quat::from_angle_z(cgmath::Rad(z));

        Self {
            position: self.position,
            rotation: rot_z * rot_y * rot_x * self.rotation,
            scale: self.scale,
        }
    }

    pub fn scaled(self, uniform_scale: f32) -> Self {
        Self {
            position: self.position,
            rotation: self.rotation,
            scale: self.scale * uniform_scale,
        }
    }

    pub fn model_matrix(&self) -> Mat4 {
        Mat4::from_translation(self.position)
            * Mat4::from(self.rotation)
            * Mat4::from(self.scale_matrix())
    }

    pub fn view_matrix(&self) -> Mat4 {
        self.model_matrix().invert().unwrap()
    }

    pub fn scale_matrix(&self) -> Mat3 {
        let mut m = Mat3::identity();
        m[0][0] = self.scale.x;
        m[1][1] = self.scale.y;
        m[2][2] = self.scale.z;
        m
    }

    pub fn up(&self) -> Vec3 {
        self.rotation.rotate_vector(Vec3::unit_y())
    }

    #[inline]
    pub fn down(&self) -> Vec3 {
        -self.up()
    }
    pub fn left(&self) -> Vec3 {
        self.rotation.rotate_vector(-Vec3::unit_x())
    }
    #[inline]
    pub fn right(&self) -> Vec3 {
        -self.left()
    }

    pub fn forwards(&self) -> Vec3 {
        self.rotation.rotate_vector(-Vec3::unit_z())
    }

    #[inline]
    pub fn backwards(&self) -> Vec3 {
        -self.forwards()
    }
}
