#pragma once

#include <memory>

#include "avatar.hpp"
#include "ghoulies/events/input_handler.hpp"

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
class ActorMove;

struct ActorDroneData;

struct ActorAttribsResource;

class Actor
    : public Avatar
    , public std::enable_shared_from_this<Actor>
{
public:
  enum ActorType : uint16_t
  {
    Ghoulie = 1,
    NPC = 5
  };

  struct ActorParamsRaw : AvatarParamsRaw
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

  static_assert(sizeof(ActorParamsRaw) == 0x640);

  struct ActorParams : AvatarParams
  {
    // uint16_t field1_0x334;
    // uint16_t field2_0x336;
    // uint16_t field3_0x338;
    std::string strategy_obj_params_aid;
    std::string ai_mind_obj_params_aid;
    std::string body_obj_params_aid;
    std::string starting_weapon_aid;

    /* eg:
                             "aid_ghoulybox_powerups_bonusbooks_chapter3a_scene10",
                             vampire spawns book on death */
    std::string ghouly_box_aid;
    std::string actor_attribs_defaults_aid;
    // uint8_t field10_0x63a;
    // uint8_t field11_0x63b;
    // uint8_t field12_0x63c;
    // uint8_t field13_0x63d;
    // uint8_t field14_0x63e;
    // uint8_t field15_0x63f;

    static ActorParams FromRaw(const ActorParamsRaw& raw);
  };

  explicit Actor(const ActorParams& params);

  void SetBody(std::string_view body_aid);
  void SetMind(std::string_view mind_aid);
  void SetStrategy(std::string_view strategy_aid);

  void Update() override;

private:
  // struct Node<actor @0x934> node0x934;
  // struct Node<actor @0x93c> node0x93c;
  uint32_t field3_0x944_ {};
  uint32_t* field4_0x948_ {};
  uint32_t field5_0x94c_ {};
  uint32_t* field6_0x950_ {};
  std::shared_ptr<ActorStrategy> strategy_ {nullptr};
  std::shared_ptr<ActorMind> mind_ {nullptr};
  std::shared_ptr<ActorBody> body_ {nullptr};
  std::shared_ptr<InputHandler> input_handler_ {nullptr};
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
  glm::vec3 world_pos_ {};
  glm::vec3 world_rot_ {};

  UNKNOWN_FIELD(0xcd8, 0xcdb);
  ActorType actor_type_;
  uint16_t actor_ushort_0xcde_ {};
  UNKNOWN_FIELD(0xce0, 0xcf3);
  uint16_t statsheet_index_ {};
  ObjectTag tag_;
};

class ActorBody : public Object
{
public:
  struct ActorBodyParams : ObjectParams
  {
    AssetAID attack_data_aid;
    AssetAID statetable_aid;
    AssetAID hit_reaction_aid;
    std::uint8_t default_animation_index;
    std::uint8_t unknown_u8_1;
    std::uint8_t unknown_u8_2;
    std::uint8_t unknown_u8_3;
    float scale;
    float camera_offset_vertical;
    float unknown_f32_1;
    std::array<float, 3> some_v;
    ushort unknown_u16_1;
    UNKNOWN_FIELD(0x1a6, 0x1a9);
    std::uint8_t some_count_not_flag;
    std::uint8_t unknown_u8_4;
    std::uint32_t unknown_u32_1;
    std::weak_ptr<Actor> parent_actor;
    UNKNOWN_FIELD(0x1b4, 0x1c1);

    AssetAID burn_fx_obj_params_aid;
    AssetAID invulnerable_fx_obj_params_aid;
    std::uint8_t unknown_u8_5;
    std::uint8_t unknown_u8_6;
    float unknown_f32_2;
    AssetAID unknown_aid_1;
    AssetAID unknown_aid_2;
    AssetAID unknown_aid_3;
    AssetAID unknown_aid_4;
    AssetAID unknown_aid_5;
    AssetAID unknown_aid_6;
    AssetAID unknown_aid_7;
    AssetAID unknown_aid_8;
    AssetAID unknown_aid_9;
    AssetAID unknown_aid_10;
  };

  explicit ActorBody(ActorBodyParams& params);

  virtual void Update(InputHandler* handler);

  std::shared_ptr<Actor> GetActor();

private:
  std::weak_ptr<Actor> parent_actor_;

  std::shared_ptr<ActorState> actor_state_;
  std::shared_ptr<ActorMove> actor_move_;
};

class ActorMind : public Object
{
public:
  struct ActorMindParams : ObjectParams
  {
    std::weak_ptr<Actor> parent_actor;
  };
};

class ActorState : public Object
{
public:
  virtual void Update(InputHandler* input_handler);

private:
  std::weak_ptr<ActorBody> parent_body_;
  std::uint16_t func6_ret_;
  // std::uint8_t unknown_u8_1;
  // std::uint8_t unknown_u8_2;

  float t_ {0.0F};
};

class ActorMove : public Object
{
public:
  virtual void Update(InputHandler* input_handler);

private:
  std::weak_ptr<ActorBody> parent_body_;
  float t_ {0.0F};
};

}  // namespace ghoulies::objects
