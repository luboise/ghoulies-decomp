#pragma once

#include "../avatar.hpp"

namespace ghoulies::objects
{

class Background : public Avatar
{
public:
  using BackgroundParams = AvatarParams;

  /// Throws std::runtime_error if fails to be created.
  explicit Background(const BackgroundParams& params);

  auto& Node0x934() { return node0x934_; }

  struct BackgroundInner
  {
    UNKNOWN_FIELD(0x00, 0x9b);
  };

private:
  EmbeddedNode<std::weak_ptr<Background>> node0x934_;

  uint32_t aid_was_found_ {};  // bool
  UNKNOWN_FIELD(0x940, 0x94b);
  BackgroundInner* inners_ {};
  UNKNOWN_FIELD(0x950, 0x9e7);
};

}  // namespace ghoulies::objects
