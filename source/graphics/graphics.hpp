#pragma once

#include <SDL3/SDL_gpu.h>
#include <glm/glm.hpp>

#include "../ghoulies/bnl.hpp"
#include "model.hpp"

namespace graphics
{

using ghoulies::Asset;

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

struct TextureParams
{
  uint32_t width;
  uint32_t height;
  std::vector<std::byte> data;
};

class Texture
{
public:
  /// Throws std::runtime_error on failure, creates a texture otherwise.
  Texture(struct SDL_GPUDevice* device, TextureParams params);
  ~Texture();

  [[nodiscard]] auto Width() const { return params_.width; }

  [[nodiscard]] auto Height() const { return params_.height; }

  [[nodiscard]] const auto& Params() const { return this->params_; }

private:
  TextureParams params_;

  SDL_GPUDevice* device_;
  SDL_GPUTexture* handle_;
};

}  // namespace graphics
