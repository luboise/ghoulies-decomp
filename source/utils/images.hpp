#include <optional>
#include <string_view>

#include "graphics/model.hpp"

namespace utils
{

/// Returns a TextureAsset from a given file path, or std::nullopt if unable to.
/// This function does not throw any exceptions, and bundles all suboptimal
/// behaviour behind the null return.
std::optional<ghoulies::TextureAsset> LoadTexture(
    std::string_view texture_path);

}  // namespace utils
