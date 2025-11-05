#include "../object.hpp"

namespace ghoulies::objects
{

class ActorBody;

class ActorState : public Object
{
public:
  struct ActorStateParams : Object::ObjectParams
  {
    ActorBody* parent_body;
  };

protected:
  explicit ActorState(const ActorStateParams& params)
      : Object(params) {};

private:
  ActorBody* parent_body_ {};

  uint16_t func6ret_ {};
  uint8_t field3_0xe_ {};
  uint8_t field4_0xf_ {};
  float t_ {};
  float field6_0x14_ {};
};

}  // namespace ghoulies::objects
