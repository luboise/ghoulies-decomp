#include <optional>

#include <SDL3/SDL_gpu.h>

#include "graphics.hpp"

namespace graphics
{

struct PBRMaterialParams
{
  std::optional<glm::vec4> base_colour;
  std::optional<TextureAsset> diffuse_texture;
};

class PBRMaterial
{
public:
  /// Throws std::runtime_error on failure, initialises a new material on
  /// success
  PBRMaterial(SDL_GPUDevice* device, PBRMaterialParams params);
  PBRMaterial(SDL_GPUDevice* device, std::shared_ptr<Texture> diffuse_texture);

  [[nodiscard]] glm::vec4 BaseColour() const { return this->base_colour_; }

  [[nodiscard]] const Texture* DiffuseTexture() const
  {
    return this->diffuse_texture_ != nullptr ? diffuse_texture_.get() : nullptr;
  }

  void Bind(SDL_GPURenderPass* render_pass) const;

private:
  glm::vec4 base_colour_;
  std::shared_ptr<Texture> diffuse_texture_;
};

}  // namespace graphics
