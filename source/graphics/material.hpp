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

private:
  glm::vec4 base_colour_;
  std::optional<Texture> diffuse_texture_;
};

}  // namespace graphics
