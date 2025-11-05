#pragma once

#include "../../graphics/types.hpp"
#include "object.hpp"

namespace ghoulies::objects
{

class EntityStatePickup;

#define UNKNOWN_FIELD(start, end) \
  std::array<uint8_t, (end) - (start) + 1> unknown_##start##_##end##_ {}

using graphics::AffineTransform;

class Avatar : public Object
{
public:
  struct AvatarCollider
  {
    AvatarCollider* prev;
    AvatarCollider* next;
  };

  struct AvatarInfoLL
  {
    AvatarInfoLL* next;
    struct DataForInfoFromBackground* prev;
  };

  struct AvatarParams : Object::ObjectParams
  {
    glm::vec3 pos;
    glm::vec3 rot_euler;
    float scale;
    float unknown_float;
    AssetAID model_aid;
    AssetAID stand_animation_aid;
    AssetAID animtable_aid;
    AssetAID callout_aid;
    AssetAID some_asset_name;
    uint32_t field10_0x2a8;
    uint32_t field11_0x2ac;
    float field12_0x2b0;
    AssetAID shadow_model_aid;
  };

protected:
  explicit Avatar(const AvatarParams& params)
      : Object(params)
  {
  }

private:
  glm::vec3 pos_ {};
  glm::vec3 rot_euler_ {};
  glm::quat rot_quaterion_ {};
  glm::vec3 scale_ {};
  float field5_0x3c_ {};
  float t_ {};
  float field7_0x44_ {};
  struct AnimtableResource* anim_table_ {};
  uint8_t anim_table_unloaded_ {};  // Possibly bool
  uint8_t field10_0x4d_ {};
  uint8_t field11_0x4e_ {};
  uint8_t field12_0x4f_ {};
  struct KeyframeContext* keyframe_context_ {};
  UNKNOWN_FIELD(0x54, 0x83);
  uint8_t needs_anim_mapping_ {};  // 4 byte bool
  struct AvatarPhysicsContext* physics_ctx_ {};
  struct CalloutDescriptor* callout_ {}; /* Created by retype action */
  AssetAID callout_aid_ {};
  UNKNOWN_FIELD(0x110, 0x11f);
  bool damage_flag_ {};
  UNKNOWN_FIELD(0x121, 0x1a3);
  void* texture_callback_ {};
  UNKNOWN_FIELD(0x1a8, 0x1bf);
  float some_float_ {};
  float mult_z_ {};
  float field241_0x1c8_ {};
  float field242_0x1cc_ {};
  UNKNOWN_FIELD(0x1d0, 0x1df);
  AvatarCollider avatar_collider_ {};
  UNKNOWN_FIELD(0x1e8, 0x1ef);
  uint32_t collision_whitelist_ {};
  AvatarInfoLL info_list_ {};
  uint8_t field270_0x1fc_ {};
  uint8_t field271_0x1fd_ {};
  uint16_t some_ushort_ {};
  float base_scale_ {};
  struct ModelDescriptor* model_resource_ {};
  AssetAID model_aid_ {};
  struct OnDeathObject* child_transform_ {};
  uint32_t num_matrices_ {};

  UNKNOWN_FIELD(0x290, 0x297);
  bool has_actor_ {};
  UNKNOWN_FIELD(0x299, 0x2a7);
  uint32_t scale_is_calculated_ {};
  AffineTransform camera_affine_ {};
  AffineTransform some_affine_ {};
  UNKNOWN_FIELD(0x30c, 0x317);
  glm::vec3 v1_ {};
  glm::vec3 v2_ {};
  UNKNOWN_FIELD(0x330, 0x3fb);
  AudioID finisher_audio_id_ {};

  UNKNOWN_FIELD(0x47c, 0x56b);
  AudioID footstep_audio_id_ {};

  UNKNOWN_FIELD(0x5ec, 0x613);

  struct astruct_25* field805_0x614_ {};
  UNKNOWN_FIELD(0x618, 0x917);
  int* int_or_struct_ptr_ {};
  // avatarOffsetPtr* nextAvatar; // TODO: Figure out how to map to this engine
  EntityStatePickup* state_pick_up_ {nullptr};
  float field1577_0x924_ {};
  UNKNOWN_FIELD(0x928, 0x92b);
  uint8_t field1578_0x928_ {};
  uint8_t field1579_0x929_ {};
  uint8_t field1580_0x92a_ {};
  uint8_t field1581_0x92b_ {};
  float action_speed_ {};
  float movement_freeze_timer_ {};
};

}  // namespace ghoulies::objects
