#include "../actor.hpp"

#include "ghoulies/events/input_handler.hpp"
#include "ghoulies/types.hpp"
#include "runtime/random.hpp"
#include "runtime/runtime.hpp"

namespace ghoulies::objects
{

Actor::Actor(const ActorParams& params)
    : Avatar(params)
{
  /*
this->actor_type_ = params->field1_0x334;
this->field828_0xcde = params->field2_0x336;
tag = params->field3_0x338;
this->tag = tag;
if (tag != Null) {
uVar1 = FUN_00133a50(tag);
this->statsheetIndex = uVar1;
this->tag = tag;
}
*/

  this->world_pos_ = this->GetWorldPosition();

  this->world_rot_ = this->GetWorldRotation();

  // this->field35_0x990 = *(undefined2*)&params->field_0x63a;
  float rand_value {GetRandomValue()};

  this->actor_rand_float_ = (rand_value - 1.0F) * 0.5F;

  // initialiseAttribs(this, params);
  // initGhoulyBox(this, params);

  this->SetBody(params.body_obj_params_aid);
  this->SetMind(params.ai_mind_obj_params_aid);

  this->input_handler_ = std::make_shared<InputHandler>();
  /*
  Scripting::CreateScriptType1((ScriptType1**)&act);
  this->input_handler_ = (ScriptType1*)act;
  */

  this->SetStrategy(params.strategy_obj_params_aid);

  /*
  if (*(int*)&body->field_0xfc != 0) {
    // this->body_->field_0x90 = 2;
    // this->body_->field_0x91 = 0;
    // this->body_->field_0x92 = 2;
    this->body_->rand_value_ = 2.0;

    this->body_->rand_value_ = GetRandomValue() - 1.0F;

    runtime::rand = runtime::rand * 0x19660d + 0x3c6ef35f;
    act = (actor*)(runtime::rand & 0x7fffff | 0x3f800000);
    body->randValue = (float)act - 1.0;
  }
  */

  /*
  weapon = NULL;
  if (*(int*)params->startingWeaponAID == 0x5f646961) {
    weapon = handleWeaponSetup(this, 0, params->startingWeaponAID);
  }
  if (((this->actorType == Ghoulie) && (DAT_00510578 += 1, weapon != NULL))
      && (((byte)DAT_0050ea98 & 0x10) != 0))
  {
    weapon->field1077_0xda0 = 1;
  }
  */

  // TODO: Add this in Avatar
  // this->has_actor_ = true;

  // TODO: Init the ghoulybox
  // createOnDeathObjects(&this->avatar, 0);
}

void Actor::Update()
{
  // pSVar5 = (ScriptType2*)this->input_handler_;
  bool update_mind_and_strategy {/* this->num_somethings_ > 0 */ false};

  // msg.msgId = update_mind_and_strategy;
  /*
  if ((pSVar5->header).type == TYPE_1) {
    ClearScriptType1((ScriptType1*)pSVar5);
  } else if ((pSVar5->header).active != 0) {
    pDVar6 = this->droneData;
    if (pDVar6 != NULL) {
      if (pDVar6->index2 == pDVar6->capacity) {
        pDVar13 = NULL;
      } else {
        pDVar13 = (DroneActionId*)((int)&pDVar6->entries->actionId
                                   + (uint)pDVar6->someCount2
                                       * (uint)pDVar6->valueSize);
      }
      if (*pDVar13 != InvalidAction) {
        processInputStateInner(pSVar5);
        goto LAB_0002c321;
      }
    }
    FUN_00109470(pSVar5);
  }
  if (!update_mind_and_strategy == 0) {
    strategy = this->strategy;
    if (strategy != NULL) {

      (*(code*)((strategy->object).vtable)->update)(strategy);
    }
    paVar7 = this->mind;
    if (paVar7 != NULL) {
      (*(code*)paVar7->vtable->update)(paVar7, this->input_handler_);
    }
  }
        */

  this->body_->Update(this->input_handler_.get());

  /*
  paVar8 = this->body->flagSet->flags;
  speed = 0.0;
  paVar8->flag1 = paVar8->flag1 & ~AttackFinished;
  paVar8 = this->body->flagSet->flags;
  paVar8->flag1 = paVar8->flag1 & 0xf7;
  if (Game::DXTimer <= 0.0) {
    delta = System::DeltaTime * System::TimeScale;
  } else {
    delta = 0.0;
  }
  if ((this->avatar).movementFreezeTimer <= 0.0) {
    speed = (this->avatar).actionSpeed;
  }
  kfc = (this->avatar).keyframeContext;
  if (kfc != NULL) {
    KeyframeContext::updateFromAvatar(kfc,
                                      (this->avatar).modelInstance,
                                      (uint)((this->avatar).someU16 == 0),
                                      speed * delta);
  }
  (*(code*)((this->body->object).vtable)->enterState)(this->body);
  kfc = (this->avatar).keyframeContext;
  if (kfc != NULL) {
    KeyframeContext::updateBones(
        (uint)((this->avatar).someU16 == 0),
        kfc,
        (this->avatar).modelInstance,
        (SomeAnimationStruct*)(this->avatar).someAnimationBoneStruct);
  }
  */

  /*
  paVar8 = this->body->flagSet->flags;
  paVar8->flag1 = paVar8->flag1 & 0xfd;
  if (update_mind_and_strategy == 0) {
    if (this->body->field397_0x258 == 0) {
      CVar9 = (this->avatar).collisionMask;
      (this->avatar).collisionMask = ~Everything;
      act = (actor*)(this->avatar).has0x4flag4;
      (this->avatar).has0x4flag4 = 0;
      avatar::updateMorphTargetsOrSomething(&this->avatar);
      // Update body collision
      actorBody::runCollisions(this->body);
      avatar::getWorldPosition(&this->avatar, (vec3*)&msg.someActor);
      body = this->body;
      (body->previousPos).x = (float)msg.someActor;
      (body->previousPos).y = fStack_20;
      (body->previousPos).z = fStack_1c;
      // Update body (position and state)
      astar_layer_changed =
          (*(code*)((this->body->object).vtable)->runPhysics)(this->body);
      if (astar_layer_changed == 0) {
        paVar8 = this->body->flagSet->flags;
        aVar12 = paVar8->flag2 | 0x10;
      } else {
        paVar8 = this->body->flagSet->flags;
        aVar12 = paVar8->flag2 & 0xef;
      }
      paVar8->flag2 = aVar12;
      (this->avatar).collisionMask = CVar9;
      (this->avatar).has0x4flag4 = (uint)act;
      avatar::updateMorphTargetsOrSomething(&this->avatar);
      update_mind_and_strategy = msg.msgId;
    } else {
      this->body->field_0x716 = 0;
      body = this->body;
      msg.someActor = (actor*)(body->currentPos).x;
      speed = (body->currentPos).y;
      delta = (body->currentPos).z;
      avatar::getWorldPosition(&this->avatar, &vStack_18);
      fVar15 = (float)msg.someActor - vStack_18.x;
      body = this->body;
      speed = speed - vStack_18.y;
      delta = delta - vStack_18.z;
      vStack_c.x = fVar15;
      vStack_c.y = speed;
      vStack_c.z = delta;
      FUN_00025a30();
      (body->v1).x = fVar15;
      (body->v1).y = speed;
      (body->v1).z = delta;
      avatar::updatePosition(&this->avatar, (vec3*)&msg.someActor);
      avatar::getWorldPosition(&this->body->actor->avatar,
                               &this->body->currentPos);
    }
  }
  Entity::UpdateAvatarRenderMats(&this->avatar);
  astar_layer_changed = *(int*)&(this->avatar).field_0x1d8;
  while (astar_layer_changed != 0) {
    iVar10 = *(int*)(astar_layer_changed + 4);
    (**(code**)(*(int*)(astar_layer_changed + -8) + 0x10))(
        astar_layer_changed + -8, this);
    astar_layer_changed = iVar10;
  }
  avatar::updateFx(&this->avatar);
  speed = (this->avatar).smoothedTargetPos.z;
  delta = (this->avatar).smoothedTargetPos.y;
  fVar15 = (this->avatar).smoothedTargetPos.x;
  if (Game::UseMovementSmoothing != 0) {
    fVar2 = (this->avatar).smoothedCurrentPos.x;
    fVar3 = (this->avatar).smoothedCurrentPos.y;
    fVar4 = (this->avatar).smoothedCurrentPos.z;
    fVar15 = (fVar15 - fVar2) * 0.1 + fVar2;
    delta = (delta - fVar3) * 0.1 + fVar3;
    speed = (speed - fVar4) * 0.1 + fVar4;
  }
  (this->avatar).smoothedCurrentPos.x = fVar15;
  (this->avatar).smoothedCurrentPos.y = delta;
  (this->avatar).smoothedCurrentPos.z = speed;
  instance = (this->avatar).modelInstance;
  if ((instance != NULL)
      && (pMVar11 = instance->field381_0x29c, pMVar11 != NULL))
  {
    background::updateModelChildren ? (pMVar11, 1.0);
  }
  // Breaks camera and enemy targeting
  (*(code*)((this->body->object).vtable)->leaveState)(this->body);
  if (update_mind_and_strategy == Null) {
    allocd = this->body->mallocedValueFromActor;
    if (allocd != NULL) {
      FUN_0013f2c0(allocd, this->body->actor, FUN_0001f8c0);
    }
  }
  body = this->body;
  if (body->actorState == NULL) {
    desiredState = Unknown0x00;
  } else {
    desiredState = (*(code*)((body->actorState->object).vtable)->runPhysics)(
        body->actorState, body->actor->input_handler_);
  }
  body = this->body;
  // Update actor state
  if (((desiredState != Unknown0x00)
       && (statetable = body->statetableRes, statetable != NULL))
      && (entry = FindFirstStateEntryWithMinValue(
              statetable, (Asset**)&act, desiredState),
          entry != NULL))
  {
    actorBody::updateStatesFromEntry(body, (objParamsLocator*)act, entry);
  }
  */
  /*
this->body_->current_pos_ = this->body_->actor_->avatar_.GetWorldPosition();

auto body = this->body_;

// Reset velocity
(body->somePos).z = 0.0;
(body->somePos).y = 0.0;
(body->somePos).x = 0.0;
*(float*)&this->body->field_0x33c = (this->body->actor->avatar).rotEuler.y;
avatar::calculateUpdatedAngles(&this->body->actor->avatar,
                         &this->body->updatedRot);
updateGhoulieTimers(this);
updateExclusionRanges(this);
if (BackgroundCollisionThings[0] != NULL) {
avatar::getWorldPosition(&this->avatar, &vStack_c);
instance = (this->avatar).modelInstance;
if ((instance == NULL) || (instance->descriptor == NULL)) {
act = NULL;
} else {
act = (actor*)((this->body->actor->avatar).someFloatScalar
             * this->body->field600_0x888);
}
if (this->mind == NULL) {
uVar14 = 0;
} else {
uVar14 = *(undefined4*)&this->mind->field_0x1c;
}
puVar1 = &this->field_0xce8;
astar_layer_changed = FUN_00110c90(
&vStack_c, &this->backgroundCollisionIndex, puVar1, uVar14);
if (astar_layer_changed != 0) {
msg.msgId = Actor_AStarLayerChanged;
(*(code*)((this->avatar).object.vtable)->onMessage)(this, &msg);
}
if (NAN((float)act) == ((float)act == 0.0)) {
runBroadPhaseTests(puVar1,
                 &vStack_c,
                 this->backgroundCollisionIndex,
                 act,
                 *(undefined4*)&this->field_0xcf0);
} else if (*(int*)puVar1 != 0) {
FUN_001108b0();
}
}
checkStillInBounds(this);
if ((UINT_0050e768 == 0) && ("\x01"[Game::CheckMoveOn] != '\0')) {
if (Game::DXTimer <= 0.0) {
speed = System::DeltaTime * System::TimeScale;
} else {
speed = 0.0;
}
delta = (this->avatar).movementFreezeTimer;
if ((0.0 < delta)
&& (delta = delta - speed,
    (this->avatar).movementFreezeTimer = delta,
    delta <= 0.0))
{
(this->avatar).movementFreezeTimer = 0.0;
}
}
speed = 0.0;
if (Game::DXTimer <= 0.0) {
delta = System::DeltaTime * System::TimeScale;
} else {
delta = 0.0;
}
if ((this->avatar).movementFreezeTimer <= 0.0) {
speed = (this->avatar).actionSpeed;
}
  (this->avatar).timeAlive = speed * delta + (this->avatar).timeAlive;
  (this->avatar).timesUpdated = (this->avatar).timesUpdated + 1;
*/
}

ActorBody::ActorBody(ActorBodyParams& params)
    : Object(params)
{
}

void ActorBody::Update(InputHandler* handler)
{
  if (this->actor_state_ != nullptr) {
    this->actor_state_->Update(handler);
  }
  if (this->actor_move_ != nullptr) {
    this->actor_move_->Update(handler);
  }
}

void ActorState::Update(InputHandler* /* input_handler */)
{
  float speed {0.0};
  std::shared_ptr<Actor> actor {this->parent_body_.lock()->GetActor()};

  float delta {runtime::GetDeltaFromDxTimer()};

  if (actor->GetFreezeTimer() <= 0.0F) {
    speed = actor->GetActionSpeed();
  }

  this->t_ = (speed * delta) + this->t_;
}

void ActorMove::Update(InputHandler* /* input_handler */)
{
  float speed {0.0};
  std::shared_ptr<Actor> actor {this->parent_body_.lock()->GetActor()};

  float delta {runtime::GetDeltaFromDxTimer()};

  if (actor->GetFreezeTimer() <= 0.0F) {
    speed = actor->GetActionSpeed();
  }

  this->t_ = (speed * delta) + this->t_;
}

std::shared_ptr<Actor> ActorBody::GetActor()
{
  assert(!this->parent_actor_.expired());

  return this->parent_actor_.lock();
}

void Actor::SetBody(std::string_view body_aid)
{
  this->body_.reset();

  if (IsValidAssetAID(body_aid)) {
    // std::shared_ptr<ActorBody> params{Assets::GetObjParams(body_aid)};

    // TODO: Implement objparams lookup
    ActorBody::ActorBodyParams params {};

    params.parent_actor = shared_from_this();
    // std::shared_ptr<ActorBody> body =
    // (actorBody*)Assets::CreateEntityFromParams((objParams*)params);
    std::shared_ptr<ActorBody> new_body {nullptr};
    this->body_ = new_body;
  }
}

void Actor::SetMind(std::string_view mind_aid)
{
  this->mind_.reset();
  // Assets::DeleteResource(this->mind_);

  if (IsValidAssetAID(mind_aid)) {
    // std::shared_ptr<ActorMind> params{Assets::GetObjParams(mind_aid)};

    // TODO: Implement objparams lookup
    ActorMind::ActorMindParams params {};

    params.parent_actor = shared_from_this();
    // std::shared_ptr<ActorMind> body =
    // Assets::CreateEntityFromParams((objParams*)params);
    std::shared_ptr<ActorMind> new_mind {nullptr};
    this->mind_ = new_mind;
  }
}

void Actor::SetStrategy(std::string_view strategy_aid)
{
  /*
actorStrategyState aVar1;
actorStrategyParams* params;
actorStrategy* new_strat;
actorStrategyState new_state;
actorStrategy* strategy;

if (actor->strategy != NULL) {
Assets::DeleteResource ? (actor->strategy);
actor->strategy = NULL;
}
if (actor->mind != NULL) {
actorMind::removeGoals ? (actor->mind);
}
if ((strategyAID != NULL) && (*(int*)strategyAID == 0x5f646961)) {
params = (actorStrategyParams*)Assets::GetObjParams(strategyAID);
params->parent = actor;
// Leads to actorStrategy::ctor
new_strat =
  (actorStrategy*)Assets::CreateEntityFromParams((objParams*)params);
actor->strategy = new_strat;
free(params);
strategy = actor->strategy;
if (strategy != NULL) {
new_state = strategy->resetState;
(*(code*)((strategy->object).vtable)->leaveState)(
    strategy, strategy->status, new_state);
aVar1 = strategy->status;
strategy->status = new_state;
actorMind::removeGoals ? (strategy->parentActor->mind);
(*(code*)((strategy->object).vtable)->enterState)(
    strategy, new_state, aVar1);
}
}
return;
*/
}

Actor::ActorParams Actor::ActorParams::FromRaw(const ActorParamsRaw& raw)
{
  return ActorParams {
      AvatarParams::FromRaw(raw),
      .strategy_obj_params_aid = raw.strategy_obj_params_aid.data(),
      .ai_mind_obj_params_aid = raw.ai_mind_obj_params_aid.data(),
      .body_obj_params_aid = raw.body_obj_params_aid.data(),
      .starting_weapon_aid = raw.starting_weapon_aid.data(),
      .ghouly_box_aid = raw.ghouly_box_aid.data(),
      .actor_attribs_defaults_aid = raw.actor_attribs_defaults_aid.data(),

  };
}

}  // namespace ghoulies::objects
