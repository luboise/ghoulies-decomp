#pragma once

#include <cstdint>
#include <span>

#include <SDL3/SDL_gpu.h>

#include "../ghoulies/model.hpp"
#include "../ghoulies/nd.hpp"
#include "graphics.hpp"

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

private:
  SDL_GPUDevice* device_;

  ghoulies::ModelDescriptor descriptor_;
  std::span<uint8_t> span_;

  Buffer<PBRVertex> vertex_buffer_;
  Buffer<Index> index_buffer_;
};

}  // namespace graphics
