#include "../avatar.hpp"

namespace ghoulies::objects
{

class Background : public Avatar
{
public:
  using BackgroundParams = AvatarParams;

  explicit Background(const BackgroundParams& params)
      : Avatar(params)
  {
  }

  struct BackgroundInner
  {
    UNKNOWN_FIELD(0x00, 0x9b);
  };

private:
  struct BackgroundEntityNode
  {
    BackgroundEntityNode* prev_node;
    Background* head;
  };

  BackgroundEntityNode* prev_entity_node_ {};
  BackgroundEntityNode* next_entity_node_ {};
  uint32_t aid_was_found_ {};  // bool
  UNKNOWN_FIELD(0x940, 0x94b);
  BackgroundInner* inners_ {};
  UNKNOWN_FIELD(0x950, 0x9e7);
};

}  // namespace ghoulies::objects
