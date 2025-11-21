#include "../avatar.hpp"

namespace ghoulies::objects
{

class Weapon : public Avatar
{
public:
  struct WeaponParamsRaw : Avatar::AvatarParamsRaw
  {
    std::uint16_t num_callouts {0};

    UNKNOWN_FIELD(0x336, 0x33f);
    float random_threshold {0};

    UNKNOWN_FIELD(0x344, 0x457);
    int num_hitboxes {0};
    std::uint32_t weapon_hitboxes_ptr_stub;  // WeaponHitboxParams*

    UNKNOWN_FIELD(0x460, 0x5f7);
  };

  static_assert(sizeof(WeaponParamsRaw) == 0x5f8);

  struct WeaponParams : Avatar::AvatarParams
  {
    std::uint16_t num_callouts {0};

    UNKNOWN_FIELD(0x336, 0x33f);
    float random_threshold {0};

    UNKNOWN_FIELD(0x344, 0x457);
    int num_hitboxes {0};
    struct WeaponHitboxParams* weapon_hitboxes {nullptr};

    UNKNOWN_FIELD(0x460, 0x5f7);

    static WeaponParams FromRaw(const WeaponParamsRaw& raw);

    WeaponParams() = default;
    WeaponParams(AvatarParams base,
                 std::uint16_t num_callouts,
                 float random_threshold,
                 int num_hitboxes,
                 struct WeaponHitboxParams* weapon_hitboxes);
  };

  explicit Weapon(const WeaponParams& params);

  bool Draw(::graphics::DrawContext& ctx) override;

private:
};

}  // namespace ghoulies::objects
