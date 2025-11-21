#include <utility>

#include "weapon.hpp"

#include "ghoulies/objects/avatar.hpp"

namespace ghoulies::objects
{

Weapon::Weapon(const WeaponParams& params)
    : Avatar(params)
{
}

bool Weapon::Draw(::graphics::DrawContext& ctx)
{
  return Avatar::Draw(ctx);
}

Weapon::WeaponParams Weapon::WeaponParams::FromRaw(const WeaponParamsRaw& raw)
{
  Avatar::AvatarParams base {Avatar::AvatarParams::FromRaw(raw)};

  return WeaponParams {
      base, raw.num_callouts, raw.random_threshold, raw.num_hitboxes, nullptr};
}

Weapon::WeaponParams::WeaponParams(AvatarParams base,
                                   std::uint16_t num_callouts,
                                   float random_threshold,
                                   int num_hitboxes,
                                   struct WeaponHitboxParams* weapon_hitboxes)
    : Avatar::AvatarParams(std::move(base))
    , num_callouts(num_callouts)
    , random_threshold(random_threshold)
    , num_hitboxes(num_hitboxes)
{
  // TODO: Handle weapon hitbox params
}

}  // namespace ghoulies::objects
