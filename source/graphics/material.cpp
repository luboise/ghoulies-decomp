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
      this->diffuse_texture_ =
          std::make_shared<Texture>(device, diffuse_params);
    } catch (std::runtime_error& e) {
      throw e;
    }
  }
}

void PBRMaterial::Bind(SDL_GPURenderPass* render_pass) const
{
  const auto* diffuse {this->DiffuseTexture()};

  if (diffuse != nullptr) {
    std::array bindings {diffuse->SDLBinding()};
    SDL_BindGPUFragmentSamplers(
        render_pass, 0, bindings.data(), bindings.size());
  }
}

PBRMaterial::PBRMaterial(SDL_GPUDevice* device,
                         std::shared_ptr<Texture> diffuse_texture)
    : diffuse_texture_(std::move(diffuse_texture))
{
  this->base_colour_ = glm::vec4 {1, 1, 1, 1};
}

}  // namespace graphics
