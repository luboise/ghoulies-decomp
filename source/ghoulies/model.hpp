#include <expected>
#include <optional>
#include <string>
#include <vector>

#include "nd.hpp"
#include "texture.hpp"

namespace ghoulies
{

struct Asset;
struct MeshHeader;

struct ModelAsset
{
  std::vector<std::shared_ptr<NdNode>> root_nodes;
  std::vector<TextureAsset> textures;

  static std::expected<ModelAsset, std::string> FromAsset(const Asset& asset);
};

}  // namespace ghoulies
