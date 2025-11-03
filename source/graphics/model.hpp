#pragma once

#include <cstdint>
#include <span>

#include <SDL3/SDL_gpu.h>

#include "../ghoulies/model.hpp"
#include "../ghoulies/nd.hpp"

namespace graphics
{

class Model
{
public:
  /// Throws std::runtime_error on fail, creates Model otherwise
  explicit Model(SDL_GPUDevice* device, const ghoulies::ModelAsset&);
  ~Model();
  Model& operator=(const Model&) = default;

  Model(const Model&) = delete;
  Model(Model&&) = delete;
  Model& operator=(Model&&) = delete;

private:
  SDL_GPUDevice* device_;

  ghoulies::ModelDescriptor descriptor_;
  std::span<uint8_t> span_;
};

}  // namespace graphics
