#include <expected>
#include <string>
#include <vector>

#include "../graphics/graphics.hpp"
#include "nd.hpp"

namespace ghoulies
{

using ::graphics::TextureAsset;

struct Asset;
struct MeshHeader;

struct ModelAsset
{
  std::vector<std::shared_ptr<NdNode>> root_nodes;
  std::vector<TextureAsset> textures;

  std::string model_aid;

  static std::expected<ModelAsset, std::string> FromAsset(const Asset& asset);
};

}  // namespace ghoulies
