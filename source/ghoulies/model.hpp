#include <expected>
#include <string>
#include <vector>

#include "../graphics/graphics.hpp"
#include "../physics/collider.hpp"
#include "nd.hpp"

namespace ghoulies
{

using ::graphics::TextureAsset;
using ::physics::Collider0x4;

struct Asset;
struct MeshHeader;

struct ModelAsset
{
  std::vector<std::shared_ptr<NdNode>> root_nodes;
  std::vector<TextureAsset> textures;

  float colliders_0x4_float {};
  std::vector<Collider0x4> colliders_0x4;

  std::string model_aid;

  static std::expected<ModelAsset, std::string> FromAsset(const Asset& asset);
};

}  // namespace ghoulies
