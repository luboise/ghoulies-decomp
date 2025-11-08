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

struct GameContext
{
  bool move_on {false};

  bool draw_backgrounds {true};
  std::string background_model_aid;

  std::list<std::shared_ptr<objects::Weapon>> weapons;
  std::list<std::shared_ptr<objects::Background>> backgrounds;

  std::expected<void, std::string> InitialiseFromMarker(const Marker& marker);

  void Clear();
};

}  // namespace ghoulies
