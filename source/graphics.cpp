#include "graphics.hpp"

#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/glm.hpp>
#include <glm/matrix.hpp>

namespace graphics
{

glm::mat4 Camera::GetViewMatrix() const
{
  glm::mat4 matrix(1.0F);

  matrix = glm::scale(matrix, this->scale);

  matrix = glm::rotate(matrix, this->position[0], {1, 0, 0});
  matrix = glm::rotate(matrix, this->position[1], {0, 1, 0});
  matrix = glm::rotate(matrix, this->position[2], {0, 0, 1});

  matrix = glm::translate(matrix, this->position);

  matrix = glm::inverse(matrix);

  return matrix;
};

}  // namespace graphics
