#pragma once

#include <cstdint>
#include <span>

#include <SDL3/SDL_gpu.h>

#include "../ghoulies/model.hpp"
#include "../ghoulies/nd.hpp"
#include "graphics.hpp"
#include "material.hpp"

namespace physics
{
struct Collider0x4;

}  // namespace physics

namespace graphics
{

class Model
{
public:
  /// Throws std::runtime_error on fail, creates Model otherwise
  explicit Model(SDL_GPUDevice* device, const ghoulies::ModelAsset&);
  ~Model();

  Model& operator=(const Model&) = delete;
  Model(const Model&) = delete;
  Model(Model&&) = delete;
  Model& operator=(Model&&) = delete;

  void DrawBasic(SDL_GPURenderPass* render_pass);
  void DrawWithTransform(DrawContext& ctx, const Transform& transform);

private:
  SDL_GPUDevice* device_;

  ghoulies::ModelDescriptor descriptor_;
  std::span<uint8_t> span_;

  Buffer<PBRVertex> vertex_buffer_;
  Buffer<Index> index_buffer_;
  std::vector<DrawCommand> draw_commands_;

  std::vector<PBRMaterial> materials_;

  float collider0x4s_float_;
  std::vector<physics::Collider0x4> collider0x4s_;
};

}  // namespace graphics
