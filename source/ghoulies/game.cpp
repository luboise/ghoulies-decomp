#include <algorithm>

#include "game.hpp"

#include "../lib.hpp"
#include "ghoulies/executable/executable.hpp"
#include "ghoulies/objects/avatar/powerup.hpp"

namespace ghoulies
{

std::expected<void, std::string> GameContext::LoadAvatarsFromMarker(
    const Marker& marker)
{
  auto& lib {GhouliesLib::Instance()};

  static const auto kVisitor = Overload {
      [&, this](const WeaponMarker& weapon_marker)
      {
        std::string weapon_aid {weapon_marker.objparams_aid.data()};

        std::cout << "Loading weapon \"" << weapon_aid << "\" from marker.\n";

        const auto* res = lib.ExecutableData().GetResource(weapon_aid);
        if (res == nullptr) {
          std::cerr << "Failed to get resource with id \"" << weapon_aid
                    << "\"\n";
          return;
        }

        auto objparams_opt {res->AsType<objects::Weapon::WeaponParamsRaw>()};
        if (!objparams_opt.has_value()) {
          std::cerr << "Failed to convert resource \"" << weapon_aid
                    << "\" to objparams.\n";
          return;
        }

        try {
          auto params {objects::Weapon::WeaponParams::FromRaw(
              std::move(objparams_opt).value())};

          params.pos = weapon_marker.header.pos;
          params.rot_euler = weapon_marker.header.rot_euler;
          params.scale = weapon_marker.header.scale;

          this->weapons.push_back(std::make_shared<objects::Weapon>(params));
        } catch (std::runtime_error& e) {
          std::cerr << "Failed to create weapon from AID " << weapon_aid
                    << ". Error: " << e.what() << "\n";
        }
      },

      [&, this](const PowerupMarker& powerup_marker)
      {
        std::string powerup_aid {powerup_marker.objparams_aid.data()};

        std::cout << "Loading powerup \"" << powerup_aid << "\" from marker.\n";

        const auto* res = lib.ExecutableData().GetResource(powerup_aid);
        if (res == nullptr) {
          std::cerr << "Failed to get resource with id \"" << powerup_aid
                    << "\"\n";
          return;
        }

        auto objparams_opt {res->AsType<objects::Powerup::PowerupParamsRaw>()};
        if (!objparams_opt.has_value()) {
          std::cerr << "Failed to convert resource \"" << powerup_aid
                    << "\" to objparams.\n";
          return;
        }

        try {
          auto params {objects::Powerup::PowerupParams::FromRaw(
              std::move(objparams_opt).value())};

          params.pos = powerup_marker.header.pos;
          params.rot_euler = powerup_marker.header.rot_euler;
          params.scale = powerup_marker.header.scale;

          this->powerups.push_back(std::make_shared<objects::Powerup>(params));
        } catch (std::runtime_error& e) {
          std::cerr << "Failed to create weapon from AID " << powerup_aid
                    << ". Error: " << e.what() << "\n";
        }
      },
      [](const RawMarkerEntry&) {},
  };

  for (const MarkerEntry& entry : marker.Entries()) {
    std::visit(kVisitor, entry);
  }

  return {};
}

void GameContext::Clear()
{
  this->weapons.clear();
  this->player.reset();
}

}  // namespace ghoulies
