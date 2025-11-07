#include "weapon.hpp"

namespace ghoulies::objects
{

Weapon::Weapon(const WeaponParams& params)
    : Avatar(params) {

    };

bool Weapon::Draw(::graphics::DrawContext& ctx)
{
  return Avatar::Draw(ctx);
}

}  // namespace ghoulies::objects
