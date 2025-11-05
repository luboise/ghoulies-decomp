#pragma once

#include <map>

#include "objects/avatar/background.hpp"
#include "types.hpp"

namespace ghoulies
{

struct GameContext : Singleton<GameContext>
{
  bool move_on {false};

  AssetAID background_model_aid {};

  Registry<objects::Background> backgrounds {};

  std::map<std::string, BNLFile> bnl_files;

  // TODO: Move this somewhere else
  SDL_GPUDevice* sdl_device;

  const Asset* GetAsset(std::string_view asset_name)
  {
    for (const auto& [filename, bnl_file] : this->bnl_files) {
      if (const auto* ptr {bnl_file.GetAsset(asset_name)}; ptr != nullptr) {
        return ptr;
      }
    }

    return nullptr;
  };
};

}  // namespace ghoulies
