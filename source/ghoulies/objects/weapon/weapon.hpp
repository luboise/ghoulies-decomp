#include "../avatar.hpp"

namespace ghoulies::objects
{

class Weapon : public Avatar
{
public:
  struct WeaponParams : Avatar::AvatarParams
  {
    ushort num_callouts {0};

    UNKNOWN_FIELD(0x336, 0x33f);
    float random_threshold {0};

    UNKNOWN_FIELD(0x344, 0x457);
    int num_hitboxes {0};
    struct WeaponHitboxParams* weapon_hitboxes {nullptr};

    UNKNOWN_FIELD(0x460, 0x5f7);
  };

  explicit Weapon(const WeaponParams& params);

  bool Draw(::graphics::DrawContext& ctx) override;

private:
};

}  // namespace ghoulies::objects
