#include "graphics.hpp"

#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/glm.hpp>
#include <glm/matrix.hpp>

#include "bits/stdc++.h"

namespace graphics
{

glm::mat4 Camera::ModelMatrix() const
{
  glm::mat4 matrix(1.0F);

  matrix = glm::scale(matrix, this->scale);

  matrix = this->RotationMatrix() * matrix;

  matrix = glm::translate(matrix, this->position);

  return matrix;
}

glm::mat4 Camera::ViewMatrix() const
{
  return glm::inverse(this->ModelMatrix());
}

glm::vec3 Camera::Left() const
{
  return this->RotationMatrix() * glm::vec4 {glm::vec3 {-1, 0, 0}, 1};
  // return glm::vec4 {0, 0, 1, 1};
}

glm::vec3 Camera::Forwards() const
{
  return this->ViewMatrix() * glm::vec4 {glm::vec3 {0, 0, 1}, 1};
  // return glm::vec4 {0, 0, 1, 1};
}

glm::mat4 Camera::ProjectionMatrix() const
{
  const float fov_v =
      2 * std::atan(1 / this->AspectRatio() * std::tan(this->fov_h / 2));

  return glm::perspectiveFov(fov_v,
                             static_cast<float>(this->viewport_width),
                             static_cast<float>(this->viewport_height),
                             this->near,
                             this->far);
}

glm::float32_t Camera::AspectRatio() const
{
  return static_cast<glm::float32_t>(this->viewport_width)
      / static_cast<glm::float32_t>(this->viewport_height);
}

glm::mat4 Camera::RotationMatrix() const
{
  glm::mat4 matrix(1.0F);

  matrix = glm::rotate(matrix, this->rotation[0], {1, 0, 0});
  matrix = glm::rotate(matrix, this->rotation[1], {0, 1, 0});
  matrix = glm::rotate(matrix, this->rotation[2], {0, 0, 1});

  return matrix;
};

}  // namespace graphics
