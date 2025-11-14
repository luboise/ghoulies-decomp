#pragma once

#include <cstdint>
#include <span>

#include <SDL3/SDL_gpu.h>

#include "../ghoulies/model.hpp"
#include "../ghoulies/nd.hpp"
#include "ghoulies/d3d.hpp"
#include "graphics.hpp"
#include "material.hpp"

namespace physics
{
struct Collider0x4;

}  // namespace physics

namespace graphics
{

/*
struct ModelParams
{
std::vector<PBRVertex> vertices;
std::vector<Index> indices;
d3d::D3DPrimitiveType primitive_type;
std::shared_ptr<PBRMaterial> material;
};
*/

struct ModelParams
{
  std::vector<PBRVertex> pbr_vertices;
  std::size_t current_vertex_count {0};

  std::vector<Index> pbr_indices;
  std::size_t current_index_count {0};

  std::vector<DrawCommand> draw_commands;
};

class Model
{
public:
  /// Throws std::runtime_error on fail, creates Model otherwise
  explicit Model(SDL_GPUDevice* device, const ghoulies::ModelAsset&);
  explicit Model(SDL_GPUDevice* device,
                 const ModelParams& params,
                 std::span<std::shared_ptr<PBRMaterial>> materials);

  ~Model();

  Model& operator=(const Model&) = delete;
  Model(const Model&) = delete;
  Model(Model&&) = delete;
  Model& operator=(Model&&) = delete;

  void DrawBasic(SDL_GPURenderPass* render_pass);
  void DrawWithTransform(DrawContext& ctx, const Transform& transform) const;

private:
  SDL_GPUDevice* device_;

  ghoulies::ModelDescriptor descriptor_;
  std::span<uint8_t> span_;

  Buffer<PBRVertex> vertex_buffer_;
  Buffer<Index> index_buffer_;
  std::vector<DrawCommand> draw_commands_;

  std::vector<std::shared_ptr<PBRMaterial>> materials_;

  float collider0x4s_float_ {0};
  std::vector<physics::Collider0x4> collider0x4s_;
};

}  // namespace graphics
