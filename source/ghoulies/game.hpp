#pragma once

#include <list>
#include <map>

#include "ghoulies/assets/marker.hpp"
#include "ghoulies/bnl.hpp"
#include "ghoulies/objects/weapon/weapon.hpp"
#include "objects/avatar/background.hpp"
#include "types.hpp"

namespace ghoulies
{

struct GameContext : Singleton<GameContext>
{
  bool move_on {false};

  bool draw_backgrounds {true};
  std::string background_model_aid;
  Registry<objects::Background> backgrounds {};

  std::list<std::shared_ptr<objects::Weapon>> weapons;

  std::map<std::string, BNLFile> bnl_files;

  // TODO: Move this somewhere else
  SDL_GPUDevice* sdl_device;

  [[nodiscard]] const Asset* GetAsset(std::string_view asset_name) const
  {
    for (const auto& [filename, bnl_file] : this->bnl_files) {
      if (const auto* ptr {bnl_file.GetAsset(asset_name)}; ptr != nullptr) {
        return ptr;
      }
    }

    return nullptr;
  }

  [[nodiscard]] const Asset* GetPlaycamScript() const;

  [[nodiscard]] const Asset* GetFirstAssetByType(AssetType asset_type) const
  {
    for (const auto& [filename, bnl_file] : this->bnl_files) {
      if (const auto* ptr {bnl_file.GetFirstAssetByType(asset_type)};
          ptr != nullptr)
      {
        return ptr;
      }
    }

    return nullptr;
  }

  std::expected<void, std::string> InitialiseFromMarker(const Marker& marker);

  void Clear();
};

}  // namespace ghoulies
