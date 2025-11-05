#include "../actor.hpp"
#include "actorstate.hpp"

namespace ghoulies::objects
{

class EntityStatePickup : public ActorState
{
public:
  struct EntityStatePickupParams : ActorStateParams
  {
  };

  explicit EntityStatePickup(const EntityStatePickupParams& params)
      : ActorState(params)
  {
  }

private:
  uint32_t actorstate_uint32_0x18_ {};
  float actorstate_float_0x1c_ {};
  uint8_t actorstate_uint8_0x20_ {};
  uint8_t actorstate_uint8_0x21_ {};
  uint8_t actorstate_uint8_0x22_ {};
  uint8_t actorstate_uint8_0x23_ {};
  float actorstate_float_0x24_ {};
  float actorstate_float_0x28_ {};
};

}  // namespace ghoulies::objects
