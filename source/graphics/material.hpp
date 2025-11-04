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

  [[nodiscard]] glm::vec4 BaseColour() const { return this->base_colour_; }

  [[nodiscard]] const Texture* DiffuseTexture() const
  {
    return this->diffuse_texture_.has_value() ? &(*diffuse_texture_) : nullptr;
  }

private:
  glm::vec4 base_colour_;
  std::optional<Texture> diffuse_texture_;
};

}  // namespace graphics
