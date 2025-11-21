#pragma once

#include <memory>

#include "../../graphics/model.hpp"
#include "../../graphics/types.hpp"
#include "../events/message.hpp"
#include "object.hpp"

namespace graphics
{

struct DrawContext;
struct Transform;

}  // namespace graphics

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

  struct AvatarParamsRaw : Object::ObjectParams
  {
    std::array<float, 3> pos;
    std::array<float, 3> rot_euler;
    float scale {1};
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

  static_assert(sizeof(AvatarParamsRaw) == 0x334);

  struct AvatarParams : Object::ObjectParams
  {
    glm::vec3 pos {0, 0, 0};
    glm::vec3 rot_euler {0, 0, 0};
    float scale {1};
    float unknown_float;
    std::string model_aid;
    std::string stand_animation_aid;
    std::string animtable_aid;
    std::string callout_aid;
    std::string some_asset_name;
    uint32_t field10_0x2a8;
    uint32_t field11_0x2ac;
    float field12_0x2b0;
    std::string shadow_model_aid;

    static AvatarParams FromRaw(const AvatarParamsRaw& raw);
  };

  virtual void SetModel(std::string_view model_aid);

  [[nodiscard]] graphics::Transform& GetTransform() { return this->transform_; }

  [[nodiscard]] glm::vec3 GetWorldPosition() const;
  [[nodiscard]] glm::vec3 GetWorldRotation() const;

  void UpdateRecursive();

  [[nodiscard]] auto GetFreezeTimer() const { return this->freeze_timer_; }

  [[nodiscard]] auto GetActionSpeed() const { return this->action_speed_; }

  // From ghidra makeshift VTable
  // 0x00 = getAllocDetails
  // 0x04 = ctor
  // 0x08 = dtor
  // 0x0c = onMessage
  virtual void OnMessage(events::Message& msg);
  // 0x10 = update
  virtual void Update();
  // 0x14 = draw
  virtual bool Draw(::graphics::DrawContext& ctx);
  // 0x18 = func6
  // 0x1c = runPhysics
  virtual bool RunPhysics();

  // 0x20 = runDeltaPhysics
  // 0x24 = handleWallCollisions
  // 0x28 = func10 (checkCollisions2)
  // 0x2c = func11 (checkForHitByWeapon)
  // 0x30 = func12
  // 0x34 = func13 (updatePositionsAndBlendTargets)
  // 0x38 = func14 (unknown)

protected:
  explicit Avatar(const AvatarParams& params);

private:
  /*
  glm::vec3 pos_ {};
  glm::vec3 rot_euler_ {};
  glm::quat rot_quaterion_ {};
  glm::vec3 scale_ {};
  */

  graphics::Transform transform_ {};

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
  // struct ModelDescriptor* model_resource_ {};
  std::shared_ptr<::graphics::Model> model_;
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
  UNKNOWN_FIELD(0x618, 0x907);

  bool skip_update_ {false};

  UNKNOWN_FIELD(0x09c, 0x907);

  int* int_or_struct_ptr_ {};

  EmbeddedNode<Avatar*> node0x918_;
  EntityStatePickup* state_pick_up_ {nullptr};
  float field1577_0x924_ {};
  UNKNOWN_FIELD(0x928, 0x92b);
  uint8_t field1578_0x928_ {};
  uint8_t field1579_0x929_ {};
  uint8_t field1580_0x92a_ {};
  uint8_t field1581_0x92b_ {};
  float action_speed_ {};
  float freeze_timer_ {};
};

}  // namespace ghoulies::objects
