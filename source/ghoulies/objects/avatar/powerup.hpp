#pragma once

#include "../avatar.hpp"

namespace ghoulies::objects
{

class Powerup : public Avatar
{
public:
  struct PowerupParamsRaw : AvatarParamsRaw
  {
    UNKNOWN_FIELD(0x334, 0x33f);
    AssetAID powerup_texture {};
    UNKNOWN_FIELD(0x3c0, 0x3c3);
  };

  static_assert(sizeof(PowerupParamsRaw) == 0x3c4);

  struct PowerupParams : AvatarParams
  {
    AssetAID powerup_texture {};

    static PowerupParams FromRaw(PowerupParamsRaw raw);
  };

  /// Throws std::runtime_error if fails to be created.
  explicit Powerup(const PowerupParams& params);

private:
  std::shared_ptr<graphics::Texture> powerup_texture_;
};

}  // namespace ghoulies::objects
