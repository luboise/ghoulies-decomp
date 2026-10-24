/* actor_move.c - Actor movement (crane, XZ gravity, alert) */
#include "actor_move.h"

ObjectFullVTable * actorMove::GetVTable(void)

{
  _g_actorMoveVTable = getAllocDetails;
  _DAT_004dd718 = actorState::ctor;
  _DAT_004dd71c = switchD_000d4179::EmptyFunction;
  _DAT_004dd720 = switchD_000d4179::EmptyFunction;
  _DAT_004dd724 = update;
  _DAT_004dd728 = updateLaunchedPos;
  return (ObjectFullVTable *)&g_actorMoveVTable;
}




void actorMove::update(actorMove *move)

{
  float speed_;
  float delta;
  actor *actor;
  
  speed_ = 0.0;
  actor = move->body->actor;
  if (runtime::dx_timer <= 0.0) {
    delta = runtime::DeltaTime * runtime::TimeScale;
  }
  else {
    delta = 0.0;
  }
  if ((actor->avatar).movementFreezeTimer <= 0.0) {
    speed_ = (actor->avatar).actionSpeed;
  }
  move->t = speed_ * delta + move->t;
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields
// Disabling this function makes cameras unable to move?


void actorMove::updateLaunchedPos(actorMove *this)

{
  AnimInstance *pAVar1;
  float10 extraout_ST0;
  float10 fVar2;
  float delta;
  float fVar3;
  float fVar4;
  vec3 local_18;
  float local_8;
  actor *actor;
  actorBody *body;
  KeyframeContext *kfc;
  float y1;
  float z1;
  
  fVar4 = 0.0;
  body = this->body;
  actor = body->actor;
  if (runtime::dx_timer <= 0.0) {
    delta = runtime::DeltaTime * runtime::TimeScale;
  }
  else {
    delta = 0.0;
  }
  if ((actor->avatar).movementFreezeTimer <= 0.0) {
    fVar4 = (actor->avatar).actionSpeed;
  }
  fVar3 = (body->worldPosition).x;
  y1 = (body->worldPosition).y;
  z1 = (body->worldPosition).z;
  kfc = (actor->avatar).keyframeContext;
  fVar4 = fVar4 * delta;
  if (((kfc == (KeyframeContext *)0x0) ||
      (pAVar1 = kfc->kfcAnims->animInstance, pAVar1 == (AnimInstance *)0x0)) ||
     (pAVar1->cValsPtr == 0)) {
    local_8 = (actor->avatar).physicsPos.y;
    fVar3 = (actor->avatar).physicsPos.x * fVar4 + fVar3;
                    // If it doesn't have an animation, update the physics ctx instead
    z1 = (actor->avatar).physicsPos.z * fVar4 + z1;
  }
  else {
    delta = (actor->avatar).uniformScale * (actor->avatar).scale.z *
            (kfc->kfHeaderPtr->floatSet).pos.z;
    local_8 = (actor->avatar).physicsPos.y;
    avatar::getWorldRotation(&actor->avatar,&local_18);
    sin(local_18.y);
    fVar3 = (float)(extraout_ST0 * (float10)delta + (float10)fVar3);
    fVar2 = (float10)cos(local_18.y);
    z1 = (float)(fVar2 * (float10)delta + (float10)z1);
  }
  body = this->body;
  (body->worldPosition).x = fVar3;
  (body->worldPosition).y = local_8 * fVar4 + y1;
  (body->worldPosition).z = z1;
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void actorMove::processMovement(entityMoveXZGravity *move,int param_2,int alert)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  KeyframeContext *pKVar5;
  AnimInstance *pAVar6;
  bool bVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  float10 fVar11;
  float delta;
  float speed;
  float fVar12;
  float fVar13;
  float fVar14;
  float local_4c;
  float local_48;
  float local_44;
  vec3 velocity;
  vec3 physics_pos;
  vec3 curr_pos;
  vec3 local_c;
  actorWrapper *paVar6;
  actor *actor;
  actorBody *body;
  
  speed = 0.0;
  body = (move->actorMove).body;
  fVar1 = (body->worldPosition).x;
  fVar2 = (body->worldPosition).y;
  fVar3 = (body->worldPosition).z;
  actor = body->actor;
  physics_pos.x = (actor->avatar).physicsPos.x;
  physics_pos.y = (actor->avatar).physicsPos.y;
  physics_pos.z = (actor->avatar).physicsPos.z;
  if (runtime::dx_timer <= 0.0) {
    delta = runtime::DeltaTime * runtime::TimeScale;
  }
  else {
    delta = 0.0;
  }
  if ((actor->avatar).movementFreezeTimer <= 0.0) {
    speed = (actor->avatar).actionSpeed;
  }
  pKVar5 = (actor->avatar).keyframeContext;
  delta = delta * speed;
                    // Forcing this branch makes cooper walk in place?
  if (((pKVar5 != (KeyframeContext *)0x0) &&
      (pAVar6 = pKVar5->kfcAnims->animInstance, pAVar6 != (AnimInstance *)0x0)) &&
     (pAVar6->cValsPtr != 0)) {
    speed = (actor->avatar).uniformScale * (actor->avatar).scale.z;
    fVar12 = speed * (pKVar5->kfHeaderPtr->floatSet).pos.x;
    speed = speed * (pKVar5->kfHeaderPtr->floatSet).pos.z;
    local_4c = modf(body->speed,6.2831855);
    if (local_4c < -3.1415927) {
      local_4c = local_4c + 6.2831855;
    }
    if (3.1415927 <= local_4c) {
      local_4c = local_4c - 6.2831855;
    }
    local_44 = local_4c;
    if (alert != 0) {
      local_48 = modf(local_4c - (actor->avatar).rotEuler.y,6.2831855);
      if (local_48 < -3.1415927) {
        local_48 = local_48 + 6.2831855;
      }
      if (3.1415927 <= local_48) {
        local_48 = local_48 - 6.2831855;
      }
      fVar11 = abs_float(local_48);
      if ((float10)1.5707964 < fVar11) {
        local_44 = local_4c - 3.1415927;
      }
    }
    velocity.y = 0.0;
    local_c.x = 0.0;
    local_c.y = local_44;
    local_c.z = 0.0;
    velocity.x = fVar12;
    velocity.z = speed;
    FUN_00106770(fVar12,0.0,speed,&local_c,&velocity);
    velocity.y = physics_pos.y * delta + velocity.y;
    goto LAB_ProcessEarly;
  }
  speed = (body->actor->avatar).physicsPos.x;
  fVar12 = (body->actor->avatar).physicsPos.z;
  fVar11 = scaled_invsqrt(speed * speed + fVar12 * fVar12);
  speed = actorBody::getMovespeed(body);
  speed = (float)fVar11 / speed;
  if (1.0 <= speed) {
    speed = 1.0;
  }
  speed = 0.5 - speed * 0.45;
  SpeedMapping_ARRAY_00339900[0].field1_0x4 = 1.0 - speed;
  SpeedMapping_ARRAY_00339900[1].field1_0x4 = speed + 1.0;
  pKVar5 = (actor->avatar).keyframeContext;
  if ((pKVar5 == (KeyframeContext *)0x0) ||
     (pAVar6 = pKVar5->kfcAnims->animInstance, pAVar6 == (AnimInstance *)0x0)) {
    speed = 0.0;
  }
  else {
    speed = pAVar6->t;
  }
  iVar9 = 0;
  iVar10 = 3;
  if (SpeedMapping_ARRAY_00339900[0].field0_0x0 <= speed) {
    if (speed <= SpeedMapping_ARRAY_00339900[3].field0_0x0) {
      do {
        iVar8 = (iVar10 - iVar9) / 2 + iVar9;
        bVar7 = SpeedMapping_ARRAY_00339900[iVar8].field0_0x0 <= speed;
        if (bVar7) {
          iVar9 = iVar8;
        }
        if (!bVar7) {
          iVar10 = iVar8;
        }
      } while (iVar9 + 1 < iVar10);
      fVar12 = SpeedMapping_ARRAY_00339900[iVar9].field0_0x0;
      fVar14 = SpeedMapping_ARRAY_00339900[iVar10].field0_0x0;
    }
    else {
      iVar9 = 3;
      iVar10 = 0;
      fVar14 = SpeedMapping_ARRAY_00339900[0].field0_0x0 + 1.0;
      fVar12 = SpeedMapping_ARRAY_00339900[3].field0_0x0;
    }
  }
  else {
    iVar9 = 3;
    iVar10 = 0;
    fVar12 = SpeedMapping_ARRAY_00339900[3].field0_0x0 - 1.0;
    fVar14 = SpeedMapping_ARRAY_00339900[0].field0_0x0;
  }
  fVar13 = (float)SpeedMapping_ARRAY_00339900[iVar10].field1_0x4;
  fVar4 = (float)SpeedMapping_ARRAY_00339900[iVar9].field1_0x4;
  if (fVar14 != fVar12) {
    speed = ((speed - fVar12) / (fVar14 - fVar12)) * (fVar13 - fVar4) + fVar4;
    if (fVar13 <= fVar4) {
      if ((fVar13 <= speed) && (fVar13 = fVar4, speed <= fVar4)) goto LAB_0002b269;
    }
    else if ((speed <= fVar13) && (fVar13 = fVar4, fVar4 <= speed)) {
LAB_0002b269:
      fVar13 = speed;
    }
  }
  velocity.x = fVar13 * physics_pos.x * delta;
  velocity.y = physics_pos.y * delta;
  velocity.z = fVar13 * physics_pos.z * delta;
  SpeedMapping_ARRAY_00339900[2].field1_0x4 = SpeedMapping_ARRAY_00339900[0].field1_0x4;
  SpeedMapping_ARRAY_00339900[3].field1_0x4 = SpeedMapping_ARRAY_00339900[1].field1_0x4;
LAB_ProcessEarly:
  if (param_2 != 0) {
    actorBody::moveInDirection(body,&velocity);
  }
                    // Update player's position
  (body->worldPosition).x = velocity.x + fVar1;
  (body->worldPosition).y = fVar2 + velocity.y;
  (body->worldPosition).z = velocity.z + fVar3;
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void actorMove::getAllocDetails(ObjectAllocDetails *param_1)

{
  param_1->entitySize = 0x10;
  param_1->paramsSize = 0xc;
  return;
}



// WARNING: Globals starting with '_' overlap smaller symbols at the same address
// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void entityMoveXZGravity::update(entityMoveXZGravity *move)

{
  float speed;
  float delta;
  actorBody *body;
  
  body = (move->actorMove).body;
  speed = 0.0;
  if (runtime::dx_timer <= 0.0) {
    delta = runtime::DeltaTime * runtime::TimeScale;
  }
  else {
    delta = 0.0;
  }
  if ((body->actor->avatar).movementFreezeTimer <= 0.0) {
    speed = (body->actor->avatar).actionSpeed;
  }
  (move->actorMove).t = speed * delta + (move->actorMove).t;
                    // Actually update the position
  actorBody::updateBodyPositionFromMoveZX(body);
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void entityMoveAlert::func5(entityMoveXZGravity *param_1)

{
  actorMove::processMovement(param_1,1,1);
  return;
}




void entityMoveCrane::getAllocDetails(undefined4 *param_1)

{
  *param_1 = 0x3c;
  param_1[1] = 0xc;
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


undefined ** entityMoveCrane::getVTable(void)

{
  vtable[0] = getAllocDetails;
  vtable[1] = ctor;
  vtable[2] = switchD_000d4179::EmptyFunction;
  vtable[3] = onMessage;
  vtable[4] = update;
  vtable[5] = func5;
  return vtable;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void entityMoveCrane::ctor(entityMoveCrane *param_1)

{
  param_1->followsPlayer_ = 1;
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void entityMoveCrane::onMessage(entityMoveCrane *param_1,Message *param_2)

{
  ObjMsgID OVar1;
  actor *av;
  actorBody *paVar2;
  
  OVar1 = (param_2->header).msgId;
  if (OVar1 != General_Reset) {
    if (OVar1 != Avatar_ResetPos) {
      return;
    }
    av = ((param_1->actorMove).body)->actor;
    avatar::setPosition(&av->avatar,(vec3 *)&(param_2->header).someActor);
    paVar2 = av->body;
    avatar::getWorldPosition(&paVar2->actor->avatar,&paVar2->worldPosition);
  }
  param_1->followsPlayer_ = 1;
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void entityMoveCrane::update(entityMoveCrane *move)

{
  actorBody *body;
  uint uVar1;
  actor *paVar2;
  float fVar3;
  float fVar4;
  actorMind *mind;
  
  body = (move->actorMove).body;
  if (runtime::dx_timer <= 0.0) {
    fVar4 = runtime::DeltaTime * runtime::TimeScale;
  }
  else {
    fVar4 = 0.0;
  }
  fVar3 = 0.0;
  if ((body->actor->avatar).movementFreezeTimer <= 0.0) {
    fVar3 = (body->actor->avatar).actionSpeed;
  }
  uVar1 = move->followsPlayer_;
  (move->actorMove).t = fVar3 * fVar4 + (move->actorMove).t;
  if (uVar1 != 0) {
    mind = body->actor->mind;
    fVar4 = (mind->evasionPos).y;
    fVar3 = (mind->evasionPos).z;
    (body->worldPosition).x = (mind->evasionPos).x;
    (body->worldPosition).y = fVar4;
    (body->worldPosition).z = fVar3;
    paVar2 = body->actor;
    (paVar2->avatar).physicsPos.x = 0.0;
    (paVar2->avatar).physicsPos.y = 0.0;
    (paVar2->avatar).physicsPos.z = 0.0;
    if (body->field_0x308 != '\0') {
      (move->v1).x = (body->camPos).x;
      (move->v1).y = (body->camPos).y;
      (move->v1).z = (body->camPos).z;
    }
    (move->v2).z = 0.0;
    (move->v2).y = 0.0;
    (move->v2).x = 0.0;
    return;
  }
  ResetCameraAndRecalculate(body);
  UpdateCameraTarget_(move);
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void entityMoveCrane::func5(entityMoveCrane *param_1)

{
  actorBody *paVar1;
  bool bVar2;
  float fVar3;
  float fVar4;
  
  actorMove::updateLaunchedPos(&param_1->actorMove);
  paVar1 = (param_1->actorMove).body;
  fVar3 = 0.0;
  if (runtime::dx_timer <= 0.0) {
    fVar4 = runtime::DeltaTime * runtime::TimeScale;
  }
  else {
    fVar4 = 0.0;
  }
  if ((paVar1->actor->avatar).movementFreezeTimer <= 0.0) {
    fVar3 = (paVar1->actor->avatar).actionSpeed;
  }
  bVar2 = DAT_004275cc != 0;
  fVar3 = fVar3 * fVar4;
  (param_1->v1).x = (param_1->v2).x * fVar3 + (param_1->v1).x;
  (param_1->v1).y = (param_1->v2).y * fVar3 + (param_1->v1).y;
  (param_1->v1).z = (param_1->v2).z * fVar3 + (param_1->v1).z;
  if ((bVar2) && (paVar1->field_0x308 != '\0')) {
    fVar3 = (paVar1->camPos).z;
    (param_1->v1).x = (paVar1->camPos).x;
    (param_1->v1).z = fVar3;
  }
  (paVar1->camPos).x = (param_1->v1).x;
  (paVar1->camPos).y = (param_1->v1).y;
  (paVar1->camPos).z = (param_1->v1).z;
  paVar1->field_0x308 = 1;
  param_1->followsPlayer_ = 0;
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


actorMoveVTable * entityMoveXZGravity::getVTable(void)

{
  vtable.onMessage = switchD_000d4179::EmptyFunction;
  vtable.getAllocDetails = actorMove::getAllocDetails;
  vtable.ctor = obj::returnOne;
  vtable.dtor = switchD_000d4179::EmptyFunction;
  vtable.update = update;
  vtable.applyMovement = applyMovement;
  return &vtable;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void entityMoveXZGravity::applyMovement(entityMoveXZGravity *param_1)

{
  actorMove::processMovement(param_1,1,0);
  return;
}




void EntityMoveContext::updateXY(EntityMoveContext *ctx,vec3 *velocity)

{
  float fVar1;
  vec3 accumulator;
  vec3 vel;
  
  fVar1 = (ctx->pos).y;
  vel.x = velocity->x;
  vel.y = velocity->y;
  vel.z = velocity->z;
  accumulator.z = 0.0;
  accumulator.y = 0.0;
  accumulator.x = 0.0;
                    // 4th param is 1/300
                    // 
                    // Stores but doesn't use accumulator
  calculatePhysicsWithCallbacks
            (&vel,&ctx->pos,&accumulator,&ctx->pos,&accumulator,0.0033333334,g_ticksToRun,
             FUN_00140700,FUN_00140770,switchD_000d4179::EmptyFunction);
                    // Reset y
  (ctx->pos).y = fVar1;
  return;
}




