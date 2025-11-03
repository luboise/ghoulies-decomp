#include <expected>
#include <string>
#include <vector>

#include "../graphics/graphics.hpp"
#include "nd.hpp"

namespace ghoulies
{

struct Asset;
struct MeshHeader;

struct ModelAsset
{
  std::vector<std::shared_ptr<NdNode>> root_nodes;
  std::vector<graphics::TextureAsset> textures;

  static std::expected<ModelAsset, std::string> FromAsset(const Asset& asset);
};

}  // namespace ghoulies
