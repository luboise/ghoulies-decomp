#pragma once

#include "avatar.hpp"

namespace ghoulies::assets
{
struct DerivedMarkerValue;
}  // namespace ghoulies::assets

namespace ghoulies::objects
{

class ActorStrategy;
class ActorMind;
class ActorBody;
class ActorState;

struct ActorDroneData;

struct ActorAttribsResource;

class Actor : public Avatar
{
public:
  enum ActorType : uint16_t
  {
    Ghoulie = 1,
    NPC = 5
  };

  struct ActorParams : AvatarParams
  {
    uint16_t field1_0x334;
    uint16_t field2_0x336;
    uint16_t field3_0x338;
    AssetAID strategy_obj_params_aid;
    AssetAID ai_mind_obj_params_aid;
    AssetAID body_obj_params_aid;
    AssetAID starting_weapon_aid;

    /* eg:
                             "aid_ghoulybox_powerups_bonusbooks_chapter3a_scene10",
                             vampire spawns book on death */
    AssetAID ghouly_box_aid;
    AssetAID actor_attribs_defaults_aid;
    uint8_t field10_0x63a;
    uint8_t field11_0x63b;
    uint8_t field12_0x63c;
    uint8_t field13_0x63d;
    uint8_t field14_0x63e;
    uint8_t field15_0x63f;
  };

  explicit Actor(const ActorParams& params)
      : Avatar(params)
  {
  }

private:
  // struct Node<actor @0x934> node0x934;
  // struct Node<actor @0x93c> node0x93c;
  uint32_t field3_0x944_ {};
  uint32_t* field4_0x948_ {};
  uint32_t field5_0x94c_ {};
  uint32_t* field6_0x950_ {};
  ActorStrategy* strategy_ {};
  ActorMind* mind_ {};
  ActorBody* body_ {};
  struct ScriptType1* script_type1_ {};
  ActorAttribsResource* attribs_ {};
  uint8_t field12_0x968_ {};
  uint8_t rand6_ {};
  uint8_t field14_0x96a_ {};
  uint8_t field15_0x96b_ {};
  uint8_t rand5_ {};
  bool rand2_ {};
  uint8_t rand1_ {};
  uint8_t rand3_ {};
  bool rand4_ {};
  UNKNOWN_FIELD(0x971, 0x973);
  float actor_float_1_ {};
  float actor_float_2_ {};
  ushort obj_tag_type_index_ {};
  ushort obj_tag_type_index2_ {};
  ActorDroneData* drone_data_ {};
  uint not_droning_ {};  // bool
  UNKNOWN_FIELD(0x988, 0x98a);
  bool drone_bool_ {};
  assets::DerivedMarkerValue* derived_marker_value_ {};
  uint16_t actor_ushort_0x990_ {};
  uint8_t actor_uchar_0x992_ {};
  uint8_t actor_uchar_0x993_ {};
  float actor_rand_float_ {};
  UNKNOWN_FIELD(0x998, 0xb97);
  void* ghouly_box_ {};
  UNKNOWN_FIELD(0xb9c, 0xb9f);
  uint8_t ghouly_box_reset_value_ {};

  UNKNOWN_FIELD(0xba1, 0xc9f);
  uint32_t skip_object_type_lookup_ {};  // bool
                                         //
  UNKNOWN_FIELD(0xca4, 0xcab);
  glm::vec3 some_vec3_ {};

  UNKNOWN_FIELD(0xcb8, 0xcbf);
  glm::vec3 v1_ {};
  glm::vec3 v2_ {};

  UNKNOWN_FIELD(0xcd8, 0xcdb);
  ActorType actor_type_;
  uint16_t actor_ushort_0xcde_ {};
  UNKNOWN_FIELD(0xce0, 0xcf3);
  uint16_t statsheet_index_ {};
  ObjectTag tag_;
};

}  // namespace ghoulies::objects
