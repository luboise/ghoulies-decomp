#pragma once

#include <glm/glm.hpp>

namespace graphics
{

struct PBRVertex
{
  glm::vec3 a_position {0, 0, 0};
  glm::vec3 a_colour {0, 0, 1};
  glm::vec3 a_normal {0, 1, 0};
  glm::vec2 a_texcoords {0, 0};
};

struct ViewUniforms
{
  glm::mat4 model;
  glm::mat4 view;
  glm::mat4 projection;
};

struct Camera
{
  glm::vec3 position;
  glm::vec3 rotation;
  glm::vec3 scale;

  [[nodiscard]] glm::mat4 GetViewMatrix() const;

  Camera()
      : Camera({0, 0, 0}, {0, 0, 0}, {1, 1, 1})
  {
  }

  Camera(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
      : position(position)
      , rotation(rotation)
      , scale(scale)
  {
  }
};

}  // namespace graphics
