#pragma once

#include <list>

#include "ghoulies/assets/marker.hpp"
#include "ghoulies/objects/avatar/powerup.hpp"
#include "ghoulies/objects/weapon/weapon.hpp"
#include "graphics/graphics.hpp"
#include "objects/actor.hpp"

namespace ghoulies
{

struct GameContext
{
  // TODO: Upgrade this later to match the camera system that the game uses
  graphics::Camera active_camera;

  bool move_on {false};

  bool draw_backgrounds {true};
  bool draw_colliders {false};
  std::string background_model_aid;

  std::shared_ptr<objects::Actor> player;
  std::list<std::shared_ptr<objects::Weapon>> weapons;
  std::list<std::shared_ptr<objects::Powerup>> powerups;

  std::expected<void, std::string> LoadAvatarsFromMarker(const Marker& marker);
  void Clear();
};

}  // namespace ghoulies
