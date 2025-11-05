#include <algorithm>

#include "game.hpp"

namespace ghoulies
{

[[nodiscard]] const Asset* GameContext::GetPlaycamScript() const
{
  const auto& playcam {std::ranges::find_if(
      this->bnl_files,
      [](const auto& pair) { return pair.first.contains("playcam"); })};

  if (playcam == this->bnl_files.end()) {
    return nullptr;
  }

  return playcam->second.GetFirstAssetByType(AssetType::ResScript);
}

}  // namespace ghoulies
