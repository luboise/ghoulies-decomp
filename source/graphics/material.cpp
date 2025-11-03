#include <stdexcept>

#include "material.hpp"

#include <SDL3/SDL_gpu.h>

namespace graphics
{

PBRMaterial::PBRMaterial(SDL_GPUDevice* device, PBRMaterialParams params)
    : base_colour_ {1.0, 1.0, 1.0, 1.0}
{
  if (params.diffuse_texture.has_value()) {
    const auto& diffuse_params {params.diffuse_texture.value()};

    try {
      this->diffuse_texture_.emplace(device, diffuse_params);
    } catch (std::runtime_error& e) {
      throw e;
    }
  }
}

}  // namespace graphics
