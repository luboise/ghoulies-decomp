#pragma once

#include "objects/avatar/background.hpp"
#include "types.hpp"

namespace ghoulies
{

struct GameContext : Singleton<GameContext>
{
  bool move_on {false};

  AssetAID background_model_aid {};

  Registry<objects::Background> backgrounds {};
};

}  // namespace ghoulies
