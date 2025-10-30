#pragma once

#include <glm/glm.hpp>

#include "model.hpp"

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

  glm::float32_t fov_h;
  glm::float32_t near;
  glm::float32_t far;

  glm::uint32_t viewport_width;
  glm::uint32_t viewport_height;

  [[nodiscard]] glm::mat4 ModelMatrix() const;
  [[nodiscard]] glm::mat4 ViewMatrix() const;
  [[nodiscard]] glm::mat4 ProjectionMatrix() const;

  [[nodiscard]] glm::mat4 RotationMatrix() const;

  [[nodiscard]] glm::float32_t AspectRatio() const;

  Camera()
      : Camera({0, 0, 0}, {0, 0, 0}, {1, 1, 1})
  {
  }

  Camera(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
      : position(position)
      , rotation(rotation)
      , scale(scale)
      , fov_h(90)
      , near(0.01F)
      , far(1000.0F)
      , viewport_width(1280)
      , viewport_height(720)
  {
  }

  [[nodiscard]] glm::vec3 Left() const;
  [[nodiscard]] glm::vec3 Forwards() const;
};

}  // namespace graphics
