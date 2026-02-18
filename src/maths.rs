use cgmath::{Matrix, SquareMatrix};

pub type Vec2 = cgmath::Vector2<f32>;
pub type Vec3 = cgmath::Vector3<f32>;
pub type Vec4 = cgmath::Vector4<f32>;

pub type Mat2 = cgmath::Matrix2<f32>;
pub type Mat3 = cgmath::Matrix3<f32>;
pub type Mat4 = cgmath::Matrix4<f32>;

pub type Quat = cgmath::Quaternion<f32>;

#[derive(Debug, Clone)]
pub struct Transform {
    pub position: Vec3,
    pub rotation: Vec3,
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
            rotation: Vec3::new(0.0, 0.0, 0.0),
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
        Self {
            position: self.position,
            rotation: self.rotation + rot.into(),
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
        let mut mat: Mat4 = self.rotation_matrix().into();

        mat.w[0] = self.position.x;
        mat.w[1] = self.position.y;
        mat.w[2] = self.position.z;

        Mat4::from(self.scale_matrix()) * mat
    }

    pub fn view_matrix(&self) -> Mat4 {
        self.model_matrix().transpose()
    }

    pub fn rotation_matrix(&self) -> Mat3 {
        rotation_matrix_z(self.rotation.z)
            * (rotation_matrix_x(self.rotation.x)
                * (rotation_matrix_y(self.rotation.y) * Mat3::identity()))
    }

    pub fn scale_matrix(&self) -> Mat3 {
        let mut m = Mat3::identity();
        m[0][0] = self.scale.x;
        m[1][1] = self.scale.y;
        m[2][2] = self.scale.z;
        m
    }

    pub fn up(&self) -> Vec3 {
        self.rotation_matrix() * Vec3::new(0.0, 1.0, 0.0)
    }

    #[inline]
    pub fn down(&self) -> Vec3 {
        -self.up()
    }
    pub fn left(&self) -> Vec3 {
        self.rotation_matrix() * Vec3::new(-1.0, 0.0, 0.0)
    }
    #[inline]
    pub fn right(&self) -> Vec3 {
        -self.left()
    }

    pub fn forwards(&self) -> Vec3 {
        self.rotation_matrix() * Vec3::new(0.0, 0.0, -1.0)
    }

    #[inline]
    pub fn backwards(&self) -> Vec3 {
        -self.forwards()
    }

    /*
    Transform& Translate(glm::vec3 translation);
    Transform& Scale(float amount);

    Transform& RotateX(float degrees);
    Transform& RotateY(float degrees);
    Transform& RotateZ(float degrees);

    [[nodiscard]] glm::mat4 ModelMatrix() const;
    [[nodiscard]] glm::mat4 RotationMatrix() const;

    [[nodiscard]] glm::vec3 Left() const;
    [[nodiscard]] glm::vec3 Forwards() const;
    [[nodiscard]] glm::vec3 Up() const;
    */
}

pub fn rotation_matrix_x(radians: f32) -> Mat3 {
    let st = radians.sin();
    let ct = radians.cos();

    // Column major order
    Mat3 {
        x: Vec3::new(1.0, 0.0, 0.0),
        y: Vec3::new(0.0, ct, -st),
        z: Vec3::new(0.0, st, ct),
    }
    .transpose()
}

pub fn rotation_matrix_y(radians: f32) -> Mat3 {
    let st = radians.sin();
    let ct = radians.cos();

    // Column major order
    Mat3 {
        x: Vec3::new(ct, 0.0, st),
        y: Vec3::new(0.0, 1.0, 0.0),
        z: Vec3::new(-st, 0.0, ct),
    }
    .transpose()
}

pub fn rotation_matrix_z(radians: f32) -> Mat3 {
    let st = radians.sin();
    let ct = radians.cos();

    // Column major order
    Mat3 {
        x: Vec3::new(ct, -st, 0.0),
        y: Vec3::new(st, ct, 0.0),
        z: Vec3::new(0.0, 0.0, 1.0),
    }
    .transpose()
}
