/* entity_body.c - Body entity subclasses (human/camera/player) */
#include "entity_body.h"

void entityBodyHuman::onActorBiteMessage(actorBody *param_1,Actor_BiteMessage *msg)

{
  actor *av;
  int iVar1;
  HitContext *pHVar2;
  HitParam1 local_78;
  HitContext hitCtx;
  
  av = (msg->field0_0x0).someActor;
  pHVar2 = &hitCtx;
  for (iVar1 = 0x1a; iVar1 != 0; iVar1 = iVar1 + -1) {
    pHVar2->type1 = '\0';
    pHVar2->field1_0x1 = '\0';
    pHVar2->field2_0x2 = '\0';
    pHVar2->field3_0x3 = '\0';
    pHVar2 = (HitContext *)&pHVar2->field4_0x4;
  }
  hitCtx.type1 = '\x01';
  hitCtx.field1_0x1 = 'E';
  hitCtx.field2_0x2 = 'd';
  hitCtx.field3_0x3 = '\x0e';
  hitCtx.field4_0x4 = 1;
  avatar::getWorldPosition(&av->avatar,&hitCtx.attackerPos);
  hitCtx.statsheetIndex = av->statsheetIndex;
  hitCtx.hittee = (actor *)0x1;
  hitCtx.field16_0x24.x = 0.0;
  hitCtx.field16_0x24.y = 1.0;
  hitCtx.field16_0x24.z = 0.0;
  hitCtx.someV.z = 0.0;
  hitCtx.someV.y = 0.0;
  hitCtx.someV.x = 0.0;
  hitCtx.otherV.z = 0.0;
  hitCtx.otherV.y = 0.0;
  hitCtx.otherV.x = 0.0;
  hitCtx.attacker = av;
  hitCtx.attacker2 = av;
  hitCtx.attacker3 = av;
  actorBody::handleHit(param_1,&hitCtx,&local_78,av,param_1);
  FUN_0001f0b0(local_78.field0_0x0 == 0);
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void entityBodyHuman::onHitByPropMessage(entityBodyHuman *body,Avatar_HitByPropMessage *msg)

{
  actor *paVar1;
  ushort uVar1;
  undefined2 extraout_var;
  int i;
  HitContext *puVar2;
  vec3 local_8c;
  actor *local_80;
  undefined4 local_7c;
  HitContext local_78;
  HitParam1 local_10;
  char *iVar1;
  
  local_80 = (body->body).actor;
  iVar1 = (char *)((body->body).flagSet)->flags;
  if (((((iVar1[2] & 2U) == 0) && ((iVar1[4] & 0x10U) == 0)) ||
      (*(int *)&(body->body).field_0x26c != *(int *)&msg->field_0x8)) && ((iVar1[3] & 0x10U) == 0))
  {
    uVar1 = nameFromObjectTag(MiscProp);
    local_7c = CONCAT22(extraout_var,uVar1);
    puVar2 = &local_78;
    for (i = uVar3; i != 0; i = i + -1) {
      puVar2->type1 = '\0';
      puVar2->field1_0x1 = '\0';
      puVar2->field2_0x2 = '\0';
      puVar2->field3_0x3 = '\0';
      puVar2 = (HitContext *)&puVar2->field4_0x4;
    }
    if (((iVar1[4] & uVar2) == 0) && ((body->body).health != 0)) {
      local_78.type1 = '\x01';
      local_78.field2_0x2 = 'e';
    }
    else {
      local_78.attacker3 = *(actor **)&(body->body).field_0x274;
      local_78.type1 = '\x03';
      local_78.field2_0x2 = 'h';
      local_78._8_4_ = 1;
    }
    local_78.hcDetails = *(HitContextDetails **)&msg->field_0x10;
    local_78.attackerPos.x = *(float *)&msg->field_0x14;
    local_78.field3_0x3 = *(uint8_t *)((local_78.hcDetails)->field3_0x4 + 0x24);
    local_78.attackerPos.y = *(float *)&msg->field_0x18;
    local_78.attackerPos.z = *(float *)&msg->field_0x1c;
    local_78.field1_0x1 = 'F';
    local_78.field4_0x4 = 0x20;
    FUN_000fca60(&local_78.field16_0x24,&(local_78.hcDetails)->field0_0x0);
    paVar1 = local_80;
    local_78.attacker = *(actor **)&msg->field_0x8;
    local_78.someV.z = 0.0;
    local_78.someV.y = 0.0;
    local_78.someV.x = 0.0;
    avatar::getWorldPosition(&local_80->avatar,&local_8c);
    local_78.field23_0x58 = *(int *)&msg->field_0xc;
    local_78.otherV.x = 0.0 - (*(float *)&msg->field_0x14 - local_8c.x);
    local_78.otherV.y = 0.0 - (*(float *)&msg->field_0x18 - local_8c.y);
    local_78.otherV.z = 0.0 - (*(float *)&msg->field_0x1c - local_8c.z);
    local_78.statsheetIndex = (ushort)local_7c;
    local_78.hittee = (actor *)0x1;
    actorBody::handleHit(&body->body,&local_78,&local_10,paVar1,&local_8c);
    FUN_00021010();
    FUN_0001f150();
    (msg->field0_0x0).someActor = (actor *)local_10.actorWasHit;
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void entityBodyHuman::onHitByFurnaceMessage(actorBody *param_1,Avatar_HitByFurnaceMessage *msg)

{
  CalloutDescriptor **ppCVar1;
  float fVar2;
  actor *av;
  uint uVar3;
  int iVar4;
  HitContext *pHVar5;
  HitParam1 local_78;
  HitContext local_68;
  
  if (((param_1->flagSet->flags->attackFlags_ & 0x40000000) == Null) &&
     (iVar4 = FUN_0001f750(), iVar4 == 0)) {
    av = param_1->actor;
    fVar2 = (msg->furnacePos).x;
    pHVar5 = &local_68;
    for (iVar4 = 0x1a; iVar4 != 0; iVar4 = iVar4 + -1) {
      pHVar5->type1 = '\0';
      pHVar5->field1_0x1 = '\0';
      pHVar5->field2_0x2 = '\0';
      pHVar5->field3_0x3 = '\0';
      pHVar5 = (HitContext *)&pHVar5->field4_0x4;
    }
    local_68.hcDetails = *(HitContextDetails **)&msg->field_0xc;
    local_68.attackerPos.y = (msg->furnacePos).y;
    local_68.field3_0x3 = *(uint8_t *)((local_68.hcDetails)->field3_0x4 + 0x24);
    local_68.attackerPos.z = (msg->furnacePos).z;
    local_68.type1 = '\x13';
    local_68.field1_0x1 = '2';
    local_68.field2_0x2 = 'd';
    local_68.field4_0x4 = 1;
    local_68.attackerPos.x = fVar2;
    FUN_000fca60(&local_68.field16_0x24,&(local_68.hcDetails)->field0_0x0);
    local_68.attacker = *(actor **)&msg->field_0x8;
    if (*(int *)&param_1->field_0x278 == 0) {
      local_68.attacker2 = *(actor **)&param_1->field_0x270;
      local_68.attacker3 = *(actor **)&param_1->field_0x274;
    }
    local_68.someV.z = 0.0;
    local_68.someV.y = 0.0;
    local_68.someV.x = 0.0;
    avatar::getWorldPosition(&av->avatar,(vec3 *)&local_78);
    local_68.field23_0x58 = 1;
    local_68.hittee = (actor *)0x1;
    local_68.otherV.x = 0.0 - ((msg->furnacePos).x - (float)local_78.field0_0x0);
    local_68.otherV.y = 0.0 - ((msg->furnacePos).y - (float)local_78.actorWasHit);
    local_68.otherV.z = 0.0 - ((msg->furnacePos).z - (float)local_78.field2_0x8);
    local_68.statsheetIndex = 0;
    actorBody::handleHit(param_1,&local_68,&local_78,av,&local_78);
    uVar3 = local_78.actorWasHit;
    if ((actor *)local_78.actorWasHit != (actor *)0x0) {
      FUN_00021010();
      someFxPos.x = (float)local_78.field0_0x0;
      ppCVar1 = &(param_1->actor->avatar).callout;
      someFxPos.y = (float)local_78.actorWasHit;
      someFxPos.z = (float)local_78.field2_0x8;
      DAT_004e1c5c = 1;
      if (ppCVar1 != (CalloutDescriptor **)0x0) {
        ::actor::executeCalloutInDescriptor
                  (*ppCVar1,ActorBaddieHitPlayer,(CalloutCallback *)0x0,0x4e1c5c,param_1->actor,
                   (entityBodyPlayer_0x924)0x0);
      }
    }
    (msg->field0_0x0).someActor = (actor *)uVar3;
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields

void entityBodyHuman::onHitByKnockDownSphereMessage
               (entityBodyHuman *param_1,Avatar_HitByKnockDownSphereMessage *msg)

{
  CalloutDescriptor **ppCVar1;
  float fVar2;
  actor *paVar3;
  uint uVar4;
  int iVar5;
  HitContext *pHVar6;
  HitParam1 local_78;
  HitContext local_68;
  
  if ((((param_1->body).flagSet)->flags->attackFlags_ & 0x40000000) == Null) {
    paVar3 = (param_1->body).actor;
    fVar2 = (msg->spherePos).x;
    pHVar6 = &local_68;
    for (iVar5 = 0x1a; iVar5 != 0; iVar5 = iVar5 + -1) {
      pHVar6->type1 = '\0';
      pHVar6->field1_0x1 = '\0';
      pHVar6->field2_0x2 = '\0';
      pHVar6->field3_0x3 = '\0';
      pHVar6 = (HitContext *)&pHVar6->field4_0x4;
    }
    local_68.hcDetails = *(HitContextDetails **)&msg->field_0xc;
    local_68.attackerPos.y = (msg->spherePos).y;
    local_68.field3_0x3 = *(uint8_t *)((local_68.hcDetails)->field3_0x4 + 0x24);
    local_68.field9_0xc = 1;
    local_68.field4_0x4 = 1;
    local_68.field10_0x10 = 1;
    local_68.attackerPos.z = (msg->spherePos).z;
    local_68.type1 = '\x05';
    local_68.field1_0x1 = '2';
    local_68.field2_0x2 = 'h';
    local_68.attackerPos.x = fVar2;
    FUN_000fca60(&local_68.field16_0x24,&(local_68.hcDetails)->field0_0x0);
    local_68.attacker = *(actor **)&msg->field_0x8;
    local_68.someV.z = 0.0;
    local_68.someV.y = 0.0;
    local_68.someV.x = 0.0;
    avatar::getWorldPosition(&paVar3->avatar,(vec3 *)&local_78);
    local_68.otherV.x = 0.0 - ((msg->spherePos).x - (float)local_78.field0_0x0);
    local_68.otherV.y = 0.0 - ((msg->spherePos).y - (float)local_78.actorWasHit);
    local_68.otherV.z = 0.0 - ((msg->spherePos).z - (float)local_78.field2_0x8);
    local_68.statsheetIndex = 0;
    local_68.hittee = (actor *)0x1;
    actorBody::handleHit(&param_1->body,&local_68,&local_78,paVar3,&local_78);
    uVar4 = local_78.actorWasHit;
    if ((actor *)local_78.actorWasHit != (actor *)0x0) {
      FUN_00021010();
      paVar3 = (param_1->body).actor;
      someFxPos.x = (float)local_78.field0_0x0;
      ppCVar1 = &(paVar3->avatar).callout;
      someFxPos.y = (float)local_78.actorWasHit;
      someFxPos.z = (float)local_78.field2_0x8;
      DAT_004e1c5c = 1;
      if (ppCVar1 != (CalloutDescriptor **)0x0) {
        ::actor::executeCalloutInDescriptor
                  (*ppCVar1,ActorBaddieHitPlayer,(CalloutCallback *)0x0,0x4e1c5c,paVar3,
                   (entityBodyPlayer_0x924)0x0);
      }
    }
    (msg->field0_0x0).someActor = (actor *)uVar4;
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void avatarSetupBasic::spawnFromMarker(short index,int *param_2)

{
  uint uVar1;
  uint unaff_EBX;
  Marker *pMVar2;
  MessageHeader local_24;
  
  local_24.msgId = Actor_SetDroneAction;
  if (index != 0) {
    do {
      pMVar2 = (Game::GameState.markerInstance)->marker;
      uVar1 = 0;
      if ((Game::GameState.markerInstance)->numMarkers != 0) {
        do {
          if (pMVar2->id == index) goto LAB_00069f92;
          uVar1 = uVar1 + 1;
          pMVar2 = (Marker *)((int)&pMVar2->size + pMVar2->size);
        } while (uVar1 < (Game::GameState.markerInstance)->numMarkers);
      }
      pMVar2 = (Marker *)0x0;
LAB_00069f92:
      local_24.someActor = (actor *)(unaff_EBX & 0xffff);
      (**(code **)(*param_2 + 0xc))(param_2,&local_24);
      index = pMVar2->runtimeId;
    } while (index != 0);
  }
  return;
}



void FUN_0006a010(undefined2 param_1,ushort param_2,undefined4 param_3,undefined4 param_4,
                 float param_5,undefined2 param_6,undefined4 *param_7,undefined4 param_8,
                 undefined4 param_9,char *param_10,char *param_11,undefined4 param_12,
                 undefined4 param_13,undefined4 param_14,undefined4 param_15)

{
  char cVar1;
  int iVar2;
  float *unaff_EBX;
  avatarParams *unaff_ESI;
  float *unaff_EDI;
  
  avatarParams::init(unaff_ESI);
  (unaff_ESI->pos).x = *unaff_EBX;
  (unaff_ESI->pos).y = unaff_EBX[1];
  (unaff_ESI->pos).z = unaff_EBX[2];
  (unaff_ESI->rotEuler).x = *unaff_EDI;
  (unaff_ESI->rotEuler).y = unaff_EDI[1];
  (unaff_ESI->rotEuler).z = unaff_EDI[2];
  unaff_ESI->ghoulyboxId2 = param_2;
  *(undefined2 *)((int)&unaff_ESI->impactId + 2) = param_1;
  *(undefined4 *)(unaff_ESI[1].calloutAID + 0x68) = param_8;
  unaff_ESI[1].objParams.paramsSize = (undefined2)param_3;
  unaff_ESI[1].objParams.objInitValue = param_3._2_2_;
  unaff_ESI[1].objParams.typeIndex = (undefined2)param_4;
  unaff_ESI[1].objParams.field3_0x6 = param_4._2_2_;
  *(undefined2 *)&unaff_ESI[1].pos.y = param_6;
  iVar2 = 0x54c - (int)param_10;
  (unaff_ESI->objParams).paramsSize = 0x65c;
  (unaff_ESI->objParams).objInitValue = 0x6e;
  (unaff_ESI->objParams).typeIndex = 0x23;
  unaff_ESI[1].pos.x = param_5;
  *(undefined4 *)(unaff_ESI[1].calloutAID + 0x6c) = param_9;
  do {
    cVar1 = *param_10;
    param_10[(int)unaff_ESI + iVar2] = cVar1;
    param_10 = param_10 + 1;
  } while (cVar1 != '\0');
  iVar2 = 0x5cc - (int)param_11;
  do {
    cVar1 = *param_11;
    param_11[(int)unaff_ESI + iVar2] = cVar1;
    param_11 = param_11 + 1;
  } while (cVar1 != '\0');
  *(undefined4 *)(unaff_ESI[1].shadowModelAID + 100) = param_12;
  *(undefined4 *)(unaff_ESI[1].shadowModelAID + 0x68) = param_13;
  *(undefined4 *)(unaff_ESI[1].shadowModelAID + 0x6c) = param_14;
  FUN_000280d0(param_7,(int)((int)&unaff_ESI[1].pos.y + 2));
  *(undefined4 *)(unaff_ESI[1].shadowModelAID + 0x70) = param_15;
  return;
}



void entityAvatarGhoulySetupBgBreak::copyBoxAIDAndActorAttribsAID
               (entityAvatarGhoulySetupBgBreak *param_1,
               entityAvatarGhoulySetupBgBreakParams *param_2)

{
  char cVar1;
  int iVar2;
  char *pcVar3;
  
  pcVar3 = param_2->ghoulyBoxAID;
  iVar2 = 0x934 - (int)pcVar3;
  do {
    cVar1 = *pcVar3;
    pcVar3[(int)param_1 + iVar2] = cVar1;
    pcVar3 = pcVar3 + 1;
  } while (cVar1 != '\0');
  pcVar3 = param_2->actorAttribsAID;
  iVar2 = 0x9b4 - (int)pcVar3;
  do {
    cVar1 = *pcVar3;
    pcVar3[(int)param_1 + iVar2] = cVar1;
    pcVar3 = pcVar3 + 1;
  } while (cVar1 != '\0');
  *(undefined4 *)&param_1->field_0xa40 = 1;
  *(undefined4 *)&param_1->field_0xa44 = *(undefined4 *)&param_2->field_0x44c;
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void entityBodyCamera::updatePosAndRot(entityBodyCamera *this)

{
  actor *av;
  vec3 local_18;
  vec3 local_c;
  
  updateRotation(this);
  av = (this->body).actor;
  avatar::getWorldPosition(&av->avatar,&local_18);
  avatar::getWorldRotation(&av->avatar,&local_c);
  (this->config).pos.x = local_18.x;
  (this->config).pos.y = local_18.y;
  (this->config).pos.z = local_18.z;
  (this->config).rotQuat.x = local_c.x;
  (this->config).rotQuat.y = local_c.y;
  (this->config).rotQuat.z = local_c.z;
  actorBody::updatePosAndRot(&this->body);
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void entityBodyCamera::updateRotation(entityBodyCamera *this)

{
  actor *av;
  float fVar1;
  float local_1c;
  vec3 worldPos;
  vec3 local_c;
  entityBodyCamera *cam;
  
  cam = this;
  av = (this->body).actor;
  avatar::getWorldPosition(&av->avatar,&worldPos);
  if ((cam->body).field_0x308 != '\0') {
    fVar1 = 0.0;
    if (Game::CurrentPlayerCameraIndex != 4) {
                    // set to 6
      fVar1 = 6.0;
    }
    local_c.x = (cam->body).camPos.x - worldPos.x;
    local_c.z = (cam->body).camPos.z - worldPos.z;
    local_c.y = (fVar1 + (cam->body).camPos.y) - worldPos.y;
    FUN_00105e20(&local_c,&local_1c,(float *)&this);
    local_c.x = 0.0 - ((float)this + -0.034906585);
    local_c.y = local_1c + 3.1415927;
    local_c.z = cam->cameraZAngle;
    Maths::NormaliseAngles2PI(&local_c,&(av->avatar).rotEuler);
    (av->avatar).anglesCalculated = 0;
    avatar::getWorldRotation(&av->body->actor->avatar,&av->body->rotation);
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


bool entityBodyCamera::func7(entityBodyCamera *this)

{
  byte *pbVar1;
  actorBodyFlags *paVar2;
  bool bVar3;
  bool bVar4;
  undefined1 *collisionFunction;
  BOOL BVar5;
  int iVar6;
  byte bVar7;
  actor *av;
  int iVar8;
  float10 fVar9;
  float fVar10;
  int local_1dc;
  vec3 v;
  vec3 pos;
  actor *local_1c0;
  vec3 new_pos;
  float local_1b0;
  float local_1ac;
  uint someFlagIsActive;
  Collision0x54 collisions [2];
  float fStack_f0;
  float fStack_ec;
  float fStack_e8;
  Collision0x54Data local_d4 [4];
  
  paVar2 = ((this->body).flagSet)->flags;
  av = (this->body).actor;
  someFlagIsActive = (*(byte *)((int)&paVar2->flag1 + 2) & 0b00100000) >> 5;
  pbVar1 = (byte *)((int)&paVar2->flag1 + 1);
  *pbVar1 = *pbVar1 & 0xdf;
  local_1c0 = av;
  avatar::getWorldPosition(&av->avatar,&new_pos);
  v.x = (this->body).worldPosition.x;
  v.y = (this->body).worldPosition.y;
  v.z = (this->body).worldPosition.z;
  iVar8 = 0;
  bVar4 = false;
  if (FLOAT_004274c8 == 0.0) {
    local_1dc = 3;
  }
  else {
    local_1dc = 0;
    pos.x = v.x;
    pos.y = v.y;
    pos.z = v.z;
  }
  bVar3 = FLOAT_004274c8 != 0.0;
  if (local_1dc != 0) {
    do {
      pos.x = v.x;
      pos.y = v.y;
      pos.z = v.z;
      collisionFunction = actorBody::getCollisionDrone(&this->body);
      BVar5 = Collision::runCollisionFunctionWithAllAvatars
                        (&pos,&new_pos,FLOAT_004274b8,Walls,collisionFunction);
      if (BVar5 == 0) {
        bVar3 = true;
        av = local_1c0;
        if (!bVar4) goto LAB_0007312a;
        goto LAB_00073010;
      }
      resolveCollision((Physics::CollisionContexts[0].ctx)->head,collisions + iVar8);
      bVar4 = true;
      if ((iVar8 == 2) &&
         (iVar6 = Collision0x54Data::AreColliding(local_d4,&collisions[0].data), iVar6 != 0)) {
        fStack_f0 = fStack_f0 + collisions[1].velocity.x;
        fStack_ec = fStack_ec + collisions[1].velocity.y;
        fStack_e8 = fStack_e8 + collisions[1].velocity.z;
        local_1ac = fStack_f0 * fStack_f0 + fStack_ec * fStack_ec + fStack_e8 * fStack_e8;
        if (local_1ac != 0.0) {
          fVar9 = (float10)invsqrt(local_1ac);
          fStack_f0 = (float)(fVar9 * (float10)fStack_f0);
          fStack_ec = (float)(fVar9 * (float10)fStack_ec);
          fStack_e8 = (float)(fVar9 * (float10)fStack_e8);
        }
        paVar2 = ((this->body).flagSet)->flags;
        local_1dc = 5;
        *(byte *)((int)&paVar2->flag1 + 1) = *(byte *)((int)&paVar2->flag1 + 1) | 0x20;
      }
      resolveCollision(collisions + iVar8,&(this->body).field_0x1cc);
      if ((iVar8 == 0) && (fVar9 = abs_float(collisions[0].velocity.y), fVar9 < (float10)1.0)) {
        collisions[0].velocity.y = 0.0;
        local_1b0 = collisions[0].velocity.x * collisions[0].velocity.x + 0.0 +
                    collisions[0].velocity.z * collisions[0].velocity.z;
        if (local_1b0 != 0.0) {
          fVar9 = (float10)invsqrt(local_1b0);
          collisions[0].velocity.x = (float)(fVar9 * (float10)collisions[0].velocity.x);
          collisions[0].velocity.y = (float)(fVar9 * (float10)collisions[0].velocity.y);
          collisions[0].velocity.z = (float)(fVar9 * (float10)collisions[0].velocity.z);
        }
      }
      fVar10 = 0.0 - (collisions[iVar8].velocity.x * ((v.x - new_pos.x) - (pos.x - new_pos.x)) +
                      ((v.z - new_pos.z) - (pos.z - new_pos.z)) * collisions[iVar8].velocity.z +
                     ((v.y - new_pos.y) - (pos.y - new_pos.y)) * collisions[iVar8].velocity.y);
      if (0.05 <= fVar10) {
        if (0.0 <= fVar10) goto LAB_00072fbd;
      }
      else {
        fVar10 = 0.05;
LAB_00072fbd:
        v.x = collisions[iVar8].velocity.x * fVar10 + v.x;
        v.y = fVar10 * collisions[iVar8].velocity.y + v.y;
        v.z = fVar10 * collisions[iVar8].velocity.z + v.z;
      }
      iVar8 = iVar8 + 1;
    } while (iVar8 < local_1dc);
    if (!bVar3) goto LAB_000730da;
LAB_00073010:
    bVar4 = true;
    fVar10 = (pos.z - new_pos.z) * ((this->body).worldPosition.z - new_pos.z) +
             (pos.y - new_pos.y) * ((this->body).worldPosition.y - new_pos.y) +
             ((this->body).worldPosition.x - new_pos.x) * (pos.x - new_pos.x);
    if ((fVar10 < 0.0) || (this->someCameraTimer_ <= 0.0 && this->someCameraTimer_ != 0.0)) {
      bVar3 = false;
    }
    this->someCameraTimer_ = fVar10;
    av = local_1c0;
  }
  if (bVar3 != false) {
    if (bVar4) {
      paVar2 = ((this->body).flagSet)->flags;
      bVar7 = *(byte *)((int)&paVar2->flag1 + 2) | 0x20;
    }
    else {
LAB_0007312a:
      paVar2 = ((this->body).flagSet)->flags;
      bVar7 = *(byte *)((int)&paVar2->flag1 + 2) & 0xdf;
    }
    *(byte *)((int)&paVar2->flag1 + 2) = bVar7;
    avatar::setPosition(&av->avatar,&pos);
    avatar::getWorldPosition(&av->body->actor->avatar,&av->body->worldPosition);
    return bVar3;
  }
LAB_000730da:
  if (someFlagIsActive == 0) {
    paVar2 = ((this->body).flagSet)->flags;
    *(byte *)((int)&paVar2->flag1 + 2) = *(byte *)((int)&paVar2->flag1 + 2) & 0xdf;
    return false;
  }
  paVar2 = ((this->body).flagSet)->flags;
  *(byte *)((int)&paVar2->flag1 + 2) = *(byte *)((int)&paVar2->flag1 + 2) | 0x20;
  return false;
}




void entityBodyCamera::getAllocDetails(ObjectAllocDetails *param_1)

{
  param_1->entitySize = 0x914;
  param_1->paramsSize = 0x7c8;
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void entityBodyCamera::getVTable(void)

{
  actorBody::makeActorBodyVTable(&actorBodyVTable_00504f80);
  actorBodyVTable_00504f80.getAllocDetails = getAllocDetails;
  actorBodyVTable_00504f80.ctor = ctor;
  actorBodyVTable_00504f80.dtor = dtor;
  actorBodyVTable_00504f80.onMessage = onMessage;
  actorBodyVTable_00504f80.update = actorBody::update;
  actorBodyVTable_00504f80.updateMovement = actorBody::updateMovement;
  actorBodyVTable_00504f80.updatePosAndRot = updatePosAndRot;
  actorBodyVTable_00504f80.computeMovementAndCollisions = func7;
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


undefined4 entityBodyCamera::ctor(entityBodyCamera *camera)

{
  CameraLLNode *curr;
  vec3 pos_;
  vec3 rot_;
  CameraLLNode *next;
  actor *actor;
  Camera *data;
  actorBodyFlags *iVar1;
  Camera *projectionSet;
  
  iVar1 = ((camera->body).flagSet)->flags;
  Game::GameState.cameraActor = (camera->body).actor;
  *(byte *)((int)&iVar1->flag1 + 3) = *(byte *)((int)&iVar1->flag1 + 3) & 0xdf;
  projectionSet = &camera->config;
  Camera::ctor(projectionSet,"cameron",(ProjectionSetBitField)0x1);
  curr = Camera::AvailableConfigs;
  next = (CameraLLNode *)Camera::AvailableConfigs[0].head;
  while ((Camera *)next != (Camera *)0x0) {
    curr = (CameraLLNode *)((Camera *)curr)->next;
    next = (CameraLLNode *)((Camera *)curr)->next;
  }
  data = ((Camera *)curr)->prev;
  ((Camera *)curr)->prev = projectionSet;
  projectionSet->next = (Camera *)curr;
  (camera->config).prev = data;
  if (data != (Camera *)0x0) {
    data->next = projectionSet;
  }
  if (Camera::ActiveConfigs[0] == (Camera *)0x0) {
    Camera::SetActiveCameraConfig(0,(camera->config).name);
  }
  Camera::SetActiveCameraConfig(0,"cameron");
  actor = (camera->body).actor;
  avatar::getWorldPosition(&actor->avatar,&pos_);
  avatar::getWorldRotation(&actor->avatar,&rot_);
  (camera->config).pos.x = pos_.x;
  (camera->config).pos.y = pos_.y;
  (camera->config).pos.z = pos_.z;
  (camera->config).rotQuat.x = rot_.x;
  (camera->config).rotQuat.y = rot_.y;
  (camera->config).rotQuat.z = rot_.z;
  return 1;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void entityBodyCamera::dtor(int param_1)

{
  Camera::setActiveCamera(param_1 + 0x894);
  Game::GameState.cameraActor = (actor *)0x0;
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void entityBodyCamera::onMessage(actorBody *param_1,Message *param_2)

{
  float fVar1;
  float fVar2;
  float fVar3;
  int iVar4;
  vec3 local_38;
  vec3 local_2c;
  CollisionContext local_20;
  
  if ((param_2->header).msgId != ActorBody_SolidDeflectPole) {
    actorBody::onMessage(param_1,param_2);
    return;
  }
  local_38.z = 0.0;
  local_38.y = 0.0;
  local_38.x = 0.0;
  fVar1 = (param_1->worldPosition).x;
  fVar2 = (param_1->worldPosition).y;
  fVar3 = (param_1->worldPosition).z;
  FUN_0013d2c0(param_1->actor->mind->targetActor,&local_20);
  iVar4 = runCollisionTest(&local_38,&local_2c,&local_20,(int)&(param_2->header).someActor);
  if (iVar4 != 0) {
    (param_1->worldPosition).x = local_2c.x + fVar1;
    (param_1->worldPosition).y = local_2c.y + fVar2;
    (param_1->worldPosition).z = local_2c.z + fVar3;
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


actorBodyVTable * entityBodyHuman::GetVTable(void)

{
  actorBodyVTable *extraout_EAX;
  
  actorBody::makeActorBodyVTable(&g_entityBodyHumanVTable);
  g_entityBodyHumanVTable.getAllocDetails = getAllocDetails;
  g_entityBodyHumanVTable.ctor = ctor;
  g_entityBodyHumanVTable.dtor = dtor;
  g_entityBodyHumanVTable.onMessage = onMessage;
  g_entityBodyHumanVTable.update = update;
  g_entityBodyHumanVTable.updateMovement = actorBody::updateMovement;
  g_entityBodyHumanVTable.updatePosAndRot = actorBody::updatePosAndRot;
  g_entityBodyHumanVTable.computeMovementAndCollisions = computeMovementAndCollisions;
  return extraout_EAX;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


undefined4 entityBodyHuman::ctor(entityBodyHuman *human,entityBodyHumanParams *params)

{
  uint *puVar1;
  
  human->someFloat2 = params->someFloat;
  human->physicsScalar = params->field2_0x7cc;
  createRigidSkin(human,params);
  loadCollisionFromSubres0x4(human);
  if (params->someFloat == 0.0) {
    puVar1 = &(human->body).field302_0x258;
    *puVar1 = *puVar1 + 1;
  }
  return 1;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void entityBodyHuman::dtor(entityBodyHuman *param_1)

{
  if (param_1->animCollidersData != (HumanAnimColliderData *)0x0) {
    free(param_1->animCollidersData);
    param_1->animCollidersData = (HumanAnimColliderData *)0x0;
  }
  if (param_1->animColliders != (AnimCollisionSubresourceEntry **)0x0) {
    free(param_1->animColliders);
    param_1->animColliders = (AnimCollisionSubresourceEntry **)0x0;
  }
  destroyRigidBones(param_1);
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void entityBodyHuman::createRigidSkin(entityBodyHuman *human,entityBodyHumanParams *params)

{
  undefined2 *puVar1;
  entityBodyHumanBoneThing_ptr_8_undefined4 puVar2;
  uint32_t num_rigid_bones;
  RigidBone *pRVar2;
  int i;
  HeapTableEntry *pHVar3;
  float acc2;
  float acc1;
  RigidBone *rigid_bones;
  
  puVar2 = &(human->rigid1).field5_0x8;
  i = 6;
  do {
    ADJ(puVar2)->field1_0x4 = '\0';
    ADJ(puVar2)->field5_0x8 = 0;
    puVar2 = puVar2 + 5;
    i = i + -1;
  } while (i != 0);
  num_rigid_bones = getNumberRigidBones(human,params);
  if (num_rigid_bones != 0) {
    if (g_HeapTableBase[runtime::CurrentHeapToAllocateFrom].heapHandle == (HANDLE)0x0) {
      pHVar3 = (HeapTableEntry *)0x0;
    }
    else {
      pHVar3 = g_HeapTableBase + runtime::CurrentHeapToAllocateFrom;
    }
    rigid_bones = (RigidBone *)
                  runtime::AllocateOnHeap(pHVar3->heapHandle,0,num_rigid_bones * 0x30 + 4);
    if (rigid_bones != (RigidBone *)0x0) {
      i = FUN_0014ded0(pHVar3->heapHandle,0,rigid_bones);
      puVar1 = (undefined2 *)(i + -4 + (int)rigid_bones);
      *puVar1 = 0x1234;
      *(undefined1 *)(puVar1 + 1) = *(undefined1 *)&pHVar3->field32_0x20;
    }
    acc2 = 0.0;
    acc1 = 0.0;
    human->flags = (params->rigid2).flags + (params->rigid1).flags + (params->rigid3).flags +
                   (params->rigid4).flags + (params->rigid6).flags;
    pRVar2 = RigidEntry::initFromEntityBodyHuman
                       (&params->rigid1,human,&rigid_bones,&acc1,&acc2,
                        params->rigidBoneScalar1 * 0.1,params->rigidBoneScalar2 * 0.1);
    (human->rigid1).rigidBone = pRVar2;
    pRVar2 = RigidEntry::initFromEntityBodyHuman
                       (&params->rigid2,human,&rigid_bones,&acc1,&acc2,
                        params->rigidBoneScalar1 * 0.2,params->rigidBoneScalar2 * 0.2);
    (human->rigid2).rigidBone = pRVar2;
    pRVar2 = RigidEntry::initFromEntityBodyHuman
                       (&params->rigid3,human,&rigid_bones,&acc1,&acc2,
                        params->rigidBoneScalar1 * 0.7,params->rigidBoneScalar2 * 0.7);
    (human->rigid3).rigidBone = pRVar2;
    pRVar2 = RigidEntry::initFromEntityBodyHuman
                       (&params->rigid4,human,&rigid_bones,&acc1,&acc2,
                        params->rigidBoneScalar1 * 0.7,params->rigidBoneScalar2 * 0.7);
    (human->rigid4).rigidBone = pRVar2;
    pRVar2 = RigidEntry::initFromEntityBodyHuman
                       (&params->rigid5,human,&rigid_bones,&acc1,&acc2,params->rigidBoneScalar1,
                        params->rigidBoneScalar2);
    (human->rigid5).rigidBone = pRVar2;
    pRVar2 = RigidEntry::initFromEntityBodyHuman
                       (&params->rigid6,human,&rigid_bones,&acc1,&acc2,params->rigidBoneScalar1,
                        params->rigidBoneScalar2);
    (human->rigid6).rigidBone = pRVar2;
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void entityBodyHuman::destroyRigidBones(entityBodyHuman *param_1)

{
  RigidBone *pRVar1;
  undefined4 uVar2;
  int iVar3;
  HeapTableEntry *pHVar4;
  RigidBone *mem;
  
  pRVar1 = (param_1->rigid6).rigidBone;
  mem = (RigidBone *)0x0;
  if (pRVar1 != (RigidBone *)0x0) {
    (param_1->rigid6).rigidBone = (RigidBone *)0x0;
    mem = pRVar1;
  }
  pRVar1 = (param_1->rigid5).rigidBone;
  if (pRVar1 != (RigidBone *)0x0) {
    (param_1->rigid5).rigidBone = (RigidBone *)0x0;
    mem = pRVar1;
  }
  pRVar1 = (param_1->rigid4).rigidBone;
  if (pRVar1 != (RigidBone *)0x0) {
    (param_1->rigid4).rigidBone = (RigidBone *)0x0;
    mem = pRVar1;
  }
  pRVar1 = (param_1->rigid3).rigidBone;
  if (pRVar1 != (RigidBone *)0x0) {
    (param_1->rigid3).rigidBone = (RigidBone *)0x0;
    mem = pRVar1;
  }
  pRVar1 = (param_1->rigid2).rigidBone;
  if (pRVar1 != (RigidBone *)0x0) {
    (param_1->rigid2).rigidBone = (RigidBone *)0x0;
    mem = pRVar1;
  }
  pRVar1 = (param_1->rigid1).rigidBone;
  if (pRVar1 != (RigidBone *)0x0) {
    (param_1->rigid1).rigidBone = (RigidBone *)0x0;
    mem = pRVar1;
  }
  if (mem != (RigidBone *)0x0) {
    iVar3 = FindHeapOf(mem);
    uVar2 = runtime::CurrentHeapToAllocateFrom;
    if (g_HeapTableBase[iVar3].heapHandle == (HANDLE)0x0) {
      pHVar4 = (HeapTableEntry *)0x0;
    }
    else {
      pHVar4 = g_HeapTableBase + iVar3;
    }
    runtime::CurrentHeapToAllocateFrom = iVar3;
    XAPILIB::HeapFree(pHVar4->heapHandle,0,mem);
    runtime::CurrentHeapToAllocateFrom = uVar2;
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void entityBodyHuman::updateMentalFocus(entityBodyHuman *body)

{
  float fVar1;
  uint16_t boneIndex;
  actorBodyFlags *paVar2;
  actor *rootActor;
  RigidBone *pRVar3;
  int i;
  entityBodyHumanBoneThing *bonething;
  uint32_t in_XMM0_Da;
  int local_10;
  vec3 transformed;
  
  paVar2 = ((body->body).flagSet)->flags;
  *(undefined1 *)&paVar2->attackFlags_ = (char)paVar2->attackFlags_ & 0xbf;
  if (*(int *)&(body->body).field_0x310 == 0) {
    rootActor = (body->body).actor;
    i = 0;
    bonething = &body->rigid1;
    do {
      if ((bonething->rigidBone != (RigidBone *)0x0) &&
         (boneIndex = bonething->rigidBone->boneIndex, boneIndex != 0)) {
        ::actor::getTransformedBonePos(rootActor,&Game::someGlobalPos,boneIndex,&transformed);
                    // Update the way the head is facing
        FUN_00073c30(rootActor,i,&body->body,&transformed,&local_10);
        if (local_10 != 0) {
          paVar2 = ((body->body).flagSet)->flags;
          *(undefined1 *)&paVar2->attackFlags_ = (char)paVar2->attackFlags_ | WaitingForFollowUp;
        }
        pRVar3 = bonething->rigidBone;
        fVar1 = (float)bonething->field7_0x10;
        if ((pRVar3 != (RigidBone *)0x0) && (pRVar3->boneIndex != 0)) {
          if (pRVar3->acc1 != -1.0) {
            pRVar3->field10_0x20 = (float)bonething->field6_0xc;
          }
          if (pRVar3->acc2 != -1.0) {
            pRVar3->field6_0x10 = fVar1;
          }
          pRVar3->field5_0xc = in_XMM0_Da;
        }
      }
      i = i + 1;
      bonething = bonething + 1;
    } while (i < 6);
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


uint32_t entityBodyHuman::getNumberRigidBones(entityBodyHuman *human,entityBodyHumanParams *params)

{
  uint32_t uVar1;
  Model *pMVar2;
  byte bVar3;
  uint8_t model_index;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  uint uVar9;
  actor *act;
  ModelDescriptor *model;
  
  act = (human->body).actor;
  uVar1 = (params->rigid1).rigidIndex;
  if (((uVar1 == 0xffffffff) || (pMVar2 = (act->avatar).model, pMVar2 == (Model *)0x0)) ||
     (model = pMVar2->descriptor, model == (ModelDescriptor *)0x0)) {
LAB_00073953:
    uVar4 = 0xffffffff;
  }
  else {
    bVar3 = ModelDescriptor::getBoneIdxFromRigid(model,(short)uVar1);
    uVar4 = (uint)bVar3;
    if (uVar4 == 0xff) goto LAB_00073953;
  }
  uVar1 = (params->rigid2).rigidIndex;
  if (((uVar1 == 0xffffffff) || (pMVar2 = (act->avatar).model, pMVar2 == (Model *)0x0)) ||
     (model = pMVar2->descriptor, model == (ModelDescriptor *)0x0)) {
LAB_0007398e:
    uVar5 = 0xffffffff;
  }
  else {
    model_index = ModelDescriptor::getBoneIdxFromRigid(model,(short)uVar1);
    uVar5 = (uint)model_index;
    if (uVar5 == 0xff) goto LAB_0007398e;
  }
  uVar1 = (params->rigid3).rigidIndex;
  if (((uVar1 == 0xffffffff) || (pMVar2 = (act->avatar).model, pMVar2 == (Model *)0x0)) ||
     (model = pMVar2->descriptor, model == (ModelDescriptor *)0x0)) {
LAB_000739c9:
    uVar6 = 0xffffffff;
  }
  else {
    bVar3 = ModelDescriptor::getBoneIdxFromRigid(model,(short)uVar1);
    uVar6 = (uint)bVar3;
    if (uVar6 == 0xff) goto LAB_000739c9;
  }
  uVar1 = (params->rigid4).rigidIndex;
  if (((uVar1 == 0xffffffff) || (pMVar2 = (act->avatar).model, pMVar2 == (Model *)0x0)) ||
     (model = pMVar2->descriptor, model == (ModelDescriptor *)0x0)) {
LAB_00073a04:
    uVar7 = 0xffffffff;
  }
  else {
    bVar3 = ModelDescriptor::getBoneIdxFromRigid(model,(short)uVar1);
    uVar7 = (uint)bVar3;
    if (uVar7 == 0xff) goto LAB_00073a04;
  }
  uVar1 = (params->rigid5).rigidIndex;
  if (((uVar1 == 0xffffffff) || (pMVar2 = (act->avatar).model, pMVar2 == (Model *)0x0)) ||
     (model = pMVar2->descriptor, model == (ModelDescriptor *)0x0)) {
LAB_00073a3f:
    uVar8 = 0xffffffff;
  }
  else {
    bVar3 = ModelDescriptor::getBoneIdxFromRigid(model,(short)uVar1);
    uVar8 = (uint)bVar3;
    if (uVar8 == 0xff) goto LAB_00073a3f;
  }
  uVar1 = (params->rigid6).rigidIndex;
  if (((uVar1 != 0xffffffff) && (pMVar2 = (act->avatar).model, pMVar2 != (Model *)0x0)) &&
     (model = pMVar2->descriptor, model != (ModelDescriptor *)0x0)) {
    bVar3 = ModelDescriptor::getBoneIdxFromRigid(model,(short)uVar1);
    uVar9 = (uint)bVar3;
    if (uVar9 != 0xff) goto LAB_00073a7d;
  }
  uVar9 = 0xffffffff;
LAB_00073a7d:
  return (uint)(uVar9 != 0xffffffff) +
         (uint)(uVar4 != 0xffffffff) + (uint)(uVar5 != 0xffffffff) + (uint)(uVar6 != 0xffffffff) +
         (uint)(uVar7 != 0xffffffff) + (uint)(uVar8 != 0xffffffff);
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields

RigidBone *
RigidEntry::initFromEntityBodyHuman
          (RigidEntry *param_1,entityBodyHuman *human,RigidBone **rigidBone,float *acc1,float *acc2,
          float scalar1,float scalar2)

{
  Model *pMVar1;
  ModelDescriptor *modelRes;
  uint8_t bone_index;
  BoneList *update_data;
  float fVar2;
  float fVar3;
  float a1;
  float fVar4;
  float a2;
  actor *act;
  RigidBone *rigid_bone;
  uint32_t rigid_index;
  
  a2 = param_1->field1_0x4;
  a1 = param_1->flags;
  fVar3 = -1.0;
  rigid_index = param_1->rigidIndex;
  if (a2 != -1.0) {
    *acc1 = *acc1 + a2;
  }
  if (a1 != -1.0) {
    *acc2 = *acc2 + a1;
  }
  act = (human->body).actor;
  if (((rigid_index != 0xffffffff) && (pMVar1 = (act->avatar).model, pMVar1 != (Model *)0x0)) &&
     (modelRes = pMVar1->descriptor, modelRes != (ModelDescriptor *)0x0)) {
    fVar2 = a2;
    fVar4 = a1;
    bone_index = ModelDescriptor::getBoneIdxFromRigid(modelRes,(short)rigid_index);
    if ((bone_index != 0xff) && (bone_index != 0xffffffff)) {
      if ((act->avatar).boneList == (BoneList *)0x0) {
        update_data = malloc_(0x10);
        fVar3 = -1.0;
        update_data->ids = (Buffer<uint16_t> *)0x0;
        update_data->boneParentCallbacks = (Buffer<> *)0x0;
        update_data->bone0x10s = (Buffer<Bone0x10> *)0x0;
        update_data->numBones = 0;
        (act->avatar).boneList = update_data;
        (act->avatar).boneList2 = update_data;
        *(undefined4 *)&(act->avatar).field_0x60 = 0;
        fVar2 = a2;
        fVar4 = a1;
      }
      update_data = (act->avatar).boneList;
      rigid_bone = *rigidBone;
      a1 = fVar2;
      a2 = fVar4;
      if (fVar2 != fVar3) {
        a1 = *acc1;
        a2 = *acc2;
      }
      rigid_bone->acc1 = a1;
      rigid_bone->scalar1 = scalar1;
      rigid_bone->field12_0x28 = 0.0;
      rigid_bone->field11_0x24 = 0.0;
      rigid_bone->field10_0x20 = 0.0;
      rigid_bone->field8_0x18 = 0.0;
      rigid_bone->field7_0x14 = 0.0;
      rigid_bone->field6_0x10 = 0.0;
      rigid_bone->acc2 = a2;
      rigid_bone->scalar2 = scalar2;
      rigid_bone->boneIndex = (ushort)bone_index;
      rigid_bone->field5_0xc = 0;
      *rigidBone = rigid_bone + 1;
      if (fVar2 != fVar3) {
        *acc1 = 0.0;
      }
      if (fVar4 != fVar3) {
        *acc2 = 0.0;
      }
      BoneList::addRigidByBoneIndex(update_data,(ushort)bone_index,bones::get_transform,rigid_bone);
      return rigid_bone;
    }
  }
  return (RigidBone *)0x0;
}



// WARNING: Unable to use type for symbol paVar2
// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields

void FUN_00073c30(actor *rootActor,int lookupIndex,actorBody *body,vec3 *transformedPos,
                 uint *param_5)

{
  char cVar1;
  actorBodyVTable **ppaVar2;
  bool bVar3;
  float10 fVar4;
  float fVar5;
  float fVar6;
  uint local_30;
  float local_2c;
  actorBody *local_28;
  vec3 local_24;
  vec3 local_18;
  vec3 local_c;
  actorBody *paVar2;
  
  paVar2 = body;
  bVar3 = body->field_0x308 != '\0';
  if (bVar3) {
    local_24.x = (body->camPos).x;
    local_24.y = (body->camPos).y;
    local_24.z = (body->camPos).z;
  }
  if ((bVar3) &&
     (*(char *)((int)body->bigVec3Set + (MindTargetLookupList[lookupIndex] - 0x3b)) == '\0')) {
    avatar::getWorldRotation(&rootActor->avatar,&local_c);
    local_18.x = local_24.x - transformedPos->x;
    local_18.y = local_24.y - transformedPos->y;
    local_18.z = local_24.z - transformedPos->z;
    FUN_00105e20(&local_18,(float *)&local_28,&local_2c);
    local_2c = modf(local_2c - local_c.x,6.2831855);
    if (local_2c < -3.1415927) {
      local_2c = local_2c + 6.2831855;
    }
    if (3.1415927 <= local_2c) {
      local_2c = local_2c - 6.2831855;
    }
    body = (actorBody *)modf((float)local_28 - local_c.y,6.2831855);
    if ((float)body < -3.1415927) {
      body = (actorBody *)((float)body + 6.2831855);
    }
    if (3.1415927 <= (float)body) {
      body = (actorBody *)((float)body - 6.2831855);
    }
    local_28 = body;
    fVar4 = abs_float((float)body);
    local_30 = (uint)(fVar4 <= (float10)(float)paVar2[1].largeProjectile + (float10)0.34906587);
  }
  else {
    local_30 = 0;
  }
  *param_5 = local_30;
  if (local_30 == 0) {
    ppaVar2 = &paVar2->vtable + lookupIndex * 5;
    cVar1 = *(char *)(ppaVar2 + 0x22c);
    if (cVar1 == '\x01') {
      if (runtime::dx_timer <= 0.0) {
        fVar5 = runtime::DeltaTime * runtime::TimeScale;
      }
      else {
        fVar5 = 0.0;
      }
      fVar6 = 0.0;
      if ((rootActor->avatar).movementFreezeTimer <= 0.0) {
        fVar6 = (rootActor->avatar).actionSpeed;
      }
      fVar5 = (float)ppaVar2[0x22d] - fVar6 * fVar5;
      ppaVar2[0x22d] = (actorBodyVTable *)fVar5;
      if (fVar5 <= 0.0) {
        ppaVar2[0x22d] = (actorBodyVTable *)0x0;
        *(undefined1 *)(ppaVar2 + 0x22c) = 0;
      }
      goto LAB_00073fbe;
    }
    if (cVar1 != '\x02') {
      if (cVar1 == '\x03') {
        *(undefined1 *)(ppaVar2 + 0x22c) = 1;
        ppaVar2[0x22d] = (actorBodyVTable *)0.3;
      }
      goto LAB_00073fbe;
    }
    fVar5 = ((float)ppaVar2[0x22d] - 0.2) * -5.0 * 0.3;
    *(undefined1 *)(ppaVar2 + 0x22c) = 1;
    if (0.3 < fVar5) {
      ppaVar2[0x22d] = (actorBodyVTable *)0.3;
      goto LAB_00073fbe;
    }
  }
  else {
    cVar1 = *(char *)((int)&paVar2[1].worldPosition + lookupIndex * 0x14 + 4);
    ppaVar2 = &paVar2->vtable + lookupIndex * 5;
    if (cVar1 == '\0') {
      *(undefined1 *)(ppaVar2 + 0x22c) = 2;
      ppaVar2[0x22d] = (actorBodyVTable *)0x3e4ccccd;
      goto LAB_00073fbe;
    }
    if (cVar1 != '\x01') {
      if (cVar1 == '\x02') {
        if (runtime::dx_timer <= 0.0) {
          fVar5 = runtime::DeltaTime * runtime::TimeScale;
        }
        else {
          fVar5 = 0.0;
        }
        fVar6 = 0.0;
        if ((rootActor->avatar).movementFreezeTimer <= 0.0) {
          fVar6 = (rootActor->avatar).actionSpeed;
        }
        fVar5 = (float)ppaVar2[0x22d] - fVar6 * fVar5;
        ppaVar2[0x22d] = (actorBodyVTable *)fVar5;
        if (fVar5 <= 0.0) {
          ppaVar2[0x22d] = (actorBodyVTable *)0x0;
          *(undefined1 *)(ppaVar2 + 0x22c) = 3;
        }
      }
      goto LAB_00073fbe;
    }
    fVar5 = ((float)ppaVar2[0x22d] - 0.3) * -3.3333333 * 0.2;
    *(undefined1 *)(ppaVar2 + 0x22c) = 2;
    if (0.2 < fVar5) {
      ppaVar2[0x22d] = (actorBodyVTable *)0x3e4ccccd;
      goto LAB_00073fbe;
    }
  }
  if (fVar5 < 0.0) {
    fVar5 = 0.0;
  }
  ppaVar2[0x22d] = (actorBodyVTable *)fVar5;
LAB_00073fbe:
  switch(*(undefined1 *)(ppaVar2 + 0x22c)) {
  case 1:
    break;
  case 2:
    break;
  case 3:
  }
  if (local_30 != 0) {
    ppaVar2[0x22e] = (actorBodyVTable *)local_2c;
    ppaVar2[0x22f] = (actorBodyVTable *)local_28;
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void entityBodyHuman::onMessage(entityBodyHuman *human,Message *msg)

{
  actor *av;
  actorBodyStateId sVar1;
  int iVar2;
  actor *uVar3;
  vec3 local_c;
  
  av = (human->body).actor;
  switch((msg->header).msgId) {
  case Avatar_DeflectedByActor:
    FUN_000229f0(human,(Avatar_DeflectedByActorMessage *)msg);
    return;
  case Avatar_HitByActor:
                    // During enemy attack windup
                    // 
                    // Also happens when enemy hits player
    actorBody::onMessage(&human->body,msg);
    actorBody::onHitByActor(human,(Avatar_HitByActorMessage *)msg);
    return;
  case Avatar_HitByFurnace:
    actorBody::onMessage(&human->body,msg);
    onHitByFurnaceMessage(human,(Avatar_HitByFurnaceMessage *)msg);
    return;
  case Avatar_HitByKnockDownSphere:
    actorBody::onMessage(&human->body,msg);
    onHitByKnockDownSphereMessage(human,(Avatar_HitByKnockDownSphereMessage *)msg);
    return;
  case Avatar_HitByGunshot:
                    // Spraying fire?
    actorBody::onMessage(&human->body,msg);
    FUN_00022cf0((Object *)human,msg);
    return;
  case Avatar_HitByProjectile:
                    // Throwable plant collided with TV (chapter 8)
    actorBody::onMessage(&human->body,msg);
    FUN_00022e40(human,msg);
    return;
  case Avatar_HitByProp:
                    // Walked into spiked door, but NOT on imp damage
    actorBody::onMessage(&human->body,msg);
                    // Skipping this entirely skips the damage i should've taken
    onHitByPropMessage(human,(Avatar_HitByPropMessage *)msg);
    return;
  case Avatar_HitBySSS:
                    // Passed Super Scary Shock
    actorBody::onMessage(&human->body,msg);
    SetShockPassType(human,msg);
    return;
  case Avatar_HitByWeapon:
                    // Triggers
                    // - Billiard table collide with skeleton during cutscene
                    // - Killing skeleton with painting (hallway chapter 7)
                    // - Table colliding with skeleton (hallway chapter 7)
                    // - Mummy hits player with tool (player launched)
                    // 
                    // Possibilities
                    // - Weapon damage dealt**
                    // - Object launched *
                    // 
                    // - Dealt weapon damage
                    // 
                    // Possibly event for
                    // - neutral collision (eg. painting + enemy, mummy weapon + player)
                    // 
    actorBody::onMessage(&human->body,msg);
    FUN_000240c0(human,(Avatar_HitByWeaponMessage *)msg);
    return;
  case Avatar_SceneInsert:
                    // On load?
    actorBody::onMessage(&human->body,msg);
    if ((human->body).field302_0x258 == 0) {
      handlePushOut(human);
    }
    FUN_0003e8c0();
    return;
  case Actor_ActionEnd:
                    // Walk into cutscene activation trigger (Walked into pot)
                    // 
                    // Also triggered automatically during cutscene
    iVar2 = FUN_000743e0();
    if ((iVar2 != 0) &&
       (sVar1 = (*((human->body).vtable)->getStandingState)(&human->body),
       sVar1 != (human->body).stateId)) {
      actorBody::setState(&human->body,sVar1);
      return;
    }
    break;
  case Actor_Bite:
    actorBody::onMessage(&human->body,msg);
    onActorBiteMessage(&human->body,(Actor_BiteMessage *)msg);
    return;
  case Actor_Die:
    FUN_00134e50();
    return;
  case Actor_EscapedBackground:
                    // Onload???
    avatar::getWorldPosition(&av->avatar,&local_c);
    onEscapeBackground(0,av);
    return;
  case Actor_Grabbed:
    FUN_000209e0(msg);
    return;
  case Actor_JumpedOff:
    if ((actor *)msg[1].header.msgId == av) {
      actorBody::disableFlagByIndex(0x28,&human->body);
    }
  default:
    actorBody::onMessage(&human->body,msg);
    break;
  case Actor_JumpedOn:
    actorBody::onMessage(&human->body,msg);
    if ((actor *)msg[1].header.msgId == av) {
      FUN_00020920();
      actorBody::setFlag(&human->body,0x28);
      return;
    }
    break;
  case Actor_KnockBackContact:
                    // Happened on uppercutting skeleton near other skeleton
    onActorKnockBackContactMessage
              (&human->body,(int)msg[1].header.someActor,&msg[3].header.someActor,
               (uint)*(byte *)((int)&msg[5].header.msgId + 1),
               (char)*(undefined2 *)((int)&msg[5].header.msgId + 2),(float *)(msg + 1),
               (int)(msg + 2));
    (msg->header).someActor = uVar3;
    return;
  case Actor_PushOut:
                    // Tripped on
                    // - Skeleton spawned out of vase, hallway chapter 7
                    // - Skeleton landing
                    // - Spider spawned out of vase
                    // - Spider landing
                    // - Dust particles
                    // 
                    // - Dust spawning/despawning
                    // - Camera going in wall
    if ((human->body).field302_0x258 == 0) {
      handlePushOut(human);
      return;
    }
    break;
  case Actor_Scooped:
    FUN_00020980();
    return;
  case ActorBody_AttackBoost:
                    // During gameplay, while turning camera, stopped moving
    FUN_00024ba0();
    return;
  case Weapon_PushOutDelta:
                    // Swinging painting towards skeleton with weird camera angle
                    // 
                    // Maybe on skeleton hitting me?
                    // Definitely on skeleton hitting me
                    // - Causes yellow flash effect
                    // 
                    // Happens on me hitting skeleton?
                    // - Red flash effect
                    // 
                    // Could possible trigger on spawning a new entity? (skeleton splits into
                    // multiple pieces)
    FUN_00075120((Message *)human,(vec3 *)&(msg->header).someActor);
    return;
  }
  return;
}




void entityBodyHuman::update(entityBodyHuman *bodyHuman)

{
  actorState *paVar1;
  actorMove *paVar2;
  
  paVar1 = (bodyHuman->body).actorState;
  if (paVar1 != (actorState *)0x0) {
    (*paVar1->vtable->update)(paVar1);
  }
  paVar2 = (bodyHuman->body).actorMove;
  if (paVar2 != (actorMove *)0x0) {
    (*paVar2->vtable->update)(paVar2);
  }
  actorBody::updateRotationFromActor(&bodyHuman->body);
  updateMentalFocus(bodyHuman);
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void entityBodyHuman::handlePushOut(entityBodyHuman *body)

{
  actor *actt;
  actorBodyFlags *paVar1;
  undefined1 *puVar2;
  int needsPushOut;
  void *ptr;
  float fVar3;
  float maxHeight;
  vec3 local_24;
  vec3 local_18;
  float local_c;
  float local_8;
  float local_4;
  
  local_24.y = (body->body).worldPosition.y;
  local_24.x = (body->body).worldPosition.x;
  local_24.z = (body->body).worldPosition.z;
  actt = (body->body).actor;
  fVar3 = (actt->avatar).scale.z;
  maxHeight = body->someFloat2 * fVar3;
  fVar3 = body->physicsScalar * fVar3 + maxHeight + 0.5;
  local_18.y = local_24.y + fVar3;
  local_18.x = local_24.x;
  local_18.z = local_24.z;
  puVar2 = actorBody::getCollisionDrone(&body->body);
  needsPushOut = Collision::runWeaponCollision(&local_18,maxHeight,Walls,puVar2);
  if (0 < needsPushOut) {
    ptr = (void *)FUN_00122310();
    FUN_000fc3f0(ptr,&local_18,maxHeight);
    free(ptr);
    local_24.x = (local_c - local_18.x) + local_24.x;
    local_24.y = (local_8 - local_18.y) + local_24.y;
    local_24.z = (local_4 - local_18.z) + local_24.z;
    avatar::setPosition(&actt->avatar,&local_24);
    avatar::getWorldPosition(&actt->body->actor->avatar,&actt->body->worldPosition);
    testCollisionWithBackground(body,&local_24,actt,&local_24,&local_18,maxHeight,fVar3);
    paVar1 = ((body->body).flagSet)->flags;
    *(byte *)((int)&paVar1->flag1 + 2) = *(byte *)((int)&paVar1->flag1 + 2) | 0x20;
    return;
  }
  paVar1 = ((body->body).flagSet)->flags;
  *(byte *)((int)&paVar1->flag1 + 2) = *(byte *)((int)&paVar1->flag1 + 2) & 0xdf;
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


undefined4 entityBodyHuman::computeMovementAndCollisions(entityBodyHuman *this)

{
  vec3 *pvVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  undefined1 uVar7;
  actorBodyFlags *paVar8;
  AvatarPhysicsContext *mem;
  avatar_0x918 pEVar9;
  actorBody *paVar10;
  undefined4 uVar11;
  char cVar12;
  Draw2D *door;
  undefined1 *collisionFunction;
  BOOL collisionsOccurred;
  int iVar13;
  int iVar14;
  byte bVar15;
  Collision0x54_0x8 col_somethings;
  HeapTableEntry *pHVar16;
  Collision0x54 *collider;
  bool bVar17;
  float10 fVar18;
  float fVar19;
  float speed;
  float delta;
  vec3 pos2;
  vec3 aim;
  vec3 local_70;
  vec3 pos1;
  vec3 local_58;
  float some_float_scalar;
  actor *someActor;
  int i;
  float yOffset;
  undefined4 local_3c;
  int local_38;
  int numCollisionChecks;
  uint local_30;
  vec3 local_2c;
  BOOL bg_col;
  float local_1c;
  float local_18;
  float local_14;
  uint local_10;
  float local_8;
  vec3 *pfVar14;
  BackgroundCollisionThing *bg_col_thing;
  actor *actorr;
  int somethingsIndex;
  
  paVar8 = ((this->body).flagSet)->flags;
  uVar7 = (this->body).movementIndex;
  actorr = (this->body).actor;
  numCollisionChecks = 3;
  local_30 = *(byte *)((int)&paVar8->attackFlags_ + 1) >> 1 & 1;
  local_10 = (*(byte *)((int)&paVar8->flag1 + 2) & 0x20) >> 5;
  someActor = actorr;
  if (game::doors != (Buffer<Draw2D> *)0x0) {
    for (door = game::doors->head; door < game::doors->tail; door = door + 1) {
      if (door->active != 0) {
        updateAvatarAgainstDoor(&actorr->avatar,this);
        break;
      }
    }
  }
  avatar::getWorldPosition(&actorr->avatar,&pos1);
  some_float_scalar = (actorr->avatar).scale.z;
  aim.x = (this->body).worldPosition.x;
  aim.y = (this->body).worldPosition.y;
  aim.z = (this->body).worldPosition.z;
  updateColliderPositions(this,&actorr->avatar,&aim);
  local_18 = this->someFloat2 * some_float_scalar;
  yOffset = this->physicsScalar * some_float_scalar + local_18 + 0.5;
  local_2c.x = pos1.x;
  local_2c.z = pos1.z;
  (this->body).movementIndex = 0;
  local_2c.y = pos1.y + yOffset;
  paVar8 = ((this->body).flagSet)->flags;
  *(byte *)((int)&paVar8->flag1 + 1) = *(byte *)((int)&paVar8->flag1 + 1) & 0xdf;
  some_float_scalar = 0.0;
  local_3c = 0;
  i = 0;
  do {
    delta = local_18;
    somethingsIndex = i;
    actorr = someActor;
    local_70.x = aim.x;
    local_70.y = aim.y + yOffset;
    collider = Globals::ColliderSomethings + i;
    local_70.z = aim.z;
    bg_col = testCollisionWithBackground(this,&pos1,someActor,&aim,&local_70,local_18,yOffset);
    collisionFunction = actorBody::getCollisionDrone(&this->body);
    collisionsOccurred =
         Collision::runCollisionFunctionWithAllAvatars
                   (&local_70,&local_2c,delta,Walls,collisionFunction);
                    // If no broad phase collisions occurred
    if (collisionsOccurred == 0) {
      iVar14 = 1;
      Globals::ColliderSomethings[somethingsIndex].field_0x26 = 0;
      local_3c = 1;
      if (some_float_scalar == 0.0) {
        paVar8 = ((this->body).flagSet)->flags;
        bVar15 = *(byte *)((int)&paVar8->flag1 + 2) & 0xdf;
        goto LAB_00074e05;
      }
      if (i < 2) goto LAB_00074bd1;
      col_somethings = &Globals::ColliderSomethings[1].velocity.z;
      goto LAB_00074b94;
    }
    resolveCollision((Physics::CollisionContexts[0].ctx)->head,collider);
    iVar14 = i;
    some_float_scalar = 1.4013e-45;
    if ((i == 0) && ((local_30 == 0 || (local_38 = 1, bg_col == 0)))) {
      local_38 = 0;
    }
    iVar13 = UpdateEntityHumanState(&aim,&pos1,this,&local_2c,&local_70,collider);
    bVar17 = iVar13 == 0;
    if ((iVar14 == 2) &&
       (iVar13 = Collision0x54Data::AreColliding
                           (&Globals::ColliderSomethings[2].data,
                            &Globals::ColliderSomethings[0].data), iVar13 != 0)) {
      Globals::ColliderSomethings[somethingsIndex].velocity.x =
           Globals::ColliderSomethings[1].velocity.x +
           Globals::ColliderSomethings[somethingsIndex].velocity.x;
      Globals::ColliderSomethings[somethingsIndex].velocity.y =
           Globals::ColliderSomethings[1].velocity.y +
           Globals::ColliderSomethings[somethingsIndex].velocity.y;
      fVar19 = Globals::ColliderSomethings[1].velocity.z +
               Globals::ColliderSomethings[somethingsIndex].velocity.z;
      Globals::ColliderSomethings[somethingsIndex].velocity.z = fVar19;
      delta = Globals::ColliderSomethings[somethingsIndex].velocity.y;
      speed = Globals::ColliderSomethings[somethingsIndex].velocity.x;
      local_1c = speed * speed + delta * delta + fVar19 * fVar19;
      if (local_1c != 0.0) {
        fVar18 = (float10)invsqrt(local_1c);
        Globals::ColliderSomethings[somethingsIndex].velocity.x =
             (float)(fVar18 * (float10)Globals::ColliderSomethings[somethingsIndex].velocity.x);
        Globals::ColliderSomethings[somethingsIndex].velocity.y =
             (float)(fVar18 * (float10)Globals::ColliderSomethings[somethingsIndex].velocity.y);
        Globals::ColliderSomethings[somethingsIndex].velocity.z =
             (float)(fVar18 * (float10)Globals::ColliderSomethings[somethingsIndex].velocity.z);
      }
      paVar8 = ((this->body).flagSet)->flags;
      numCollisionChecks = 5;
      bVar17 = true;
      *(byte *)((int)&paVar8->flag1 + 1) = *(byte *)((int)&paVar8->flag1 + 1) | 0x20;
    }
    resolveCollision(collider,&(this->body).field_0x1cc);
    if (bVar17) {
      if (local_38 != 0) {
        local_14 = Globals::ColliderSomethings[somethingsIndex].velocity.y;
        fVar18 = abs_float(local_14);
        if ((float10)2e-07 < fVar18) {
          Globals::ColliderSomethings[somethingsIndex].velocity.y = 0.0;
          delta = Globals::ColliderSomethings[somethingsIndex].velocity.z;
          speed = Globals::ColliderSomethings[somethingsIndex].velocity.x;
          delta = speed * speed + 0.0 + delta * delta;
          if (delta != 0.0) {
            fVar18 = (float10)invsqrt(delta);
            Globals::ColliderSomethings[somethingsIndex].velocity.x =
                 (float)(fVar18 * (float10)Globals::ColliderSomethings[somethingsIndex].velocity.x);
            Globals::ColliderSomethings[somethingsIndex].velocity.y =
                 (float)(fVar18 * (float10)Globals::ColliderSomethings[somethingsIndex].velocity.y);
            Globals::ColliderSomethings[somethingsIndex].velocity.z =
                 (float)(fVar18 * (float10)Globals::ColliderSomethings[somethingsIndex].velocity.z);
          }
        }
      }
      delta = 0.0 - (Globals::ColliderSomethings[somethingsIndex].velocity.x *
                     ((aim.x - pos1.x) - (local_70.x - local_2c.x)) +
                     ((aim.z - pos1.z) - (local_70.z - local_2c.z)) *
                     Globals::ColliderSomethings[somethingsIndex].velocity.z +
                    ((aim.y - pos1.y) - (local_70.y - local_2c.y)) *
                    Globals::ColliderSomethings[somethingsIndex].velocity.y);
      if (delta < 0.05) {
        delta = 0.05;
      }
      else if (delta < 0.0) goto LAB_00074b2a;
      aim.x = Globals::ColliderSomethings[somethingsIndex].velocity.x * delta + aim.x;
      aim.z = delta * Globals::ColliderSomethings[somethingsIndex].velocity.z + aim.z;
      aim.y = delta * Globals::ColliderSomethings[somethingsIndex].velocity.y + aim.y;
    }
    else {
      aim.y = local_70.y - yOffset;
      aim.x = local_70.x;
      aim.z = local_70.z;
    }
LAB_00074b2a:
    i = iVar14 + 1;
  } while (i < numCollisionChecks);
LAB_00074d4f:
  pos2.x = pos1.x;
  pos2.y = pos1.y;
  pos2.z = pos1.z;
  if (local_30 == 0) {
    paVar8 = ((this->body).flagSet)->flags;
    bVar15 = *(byte *)((int)&paVar8->attackFlags_ + 1) & 0xfd;
  }
  else {
    paVar8 = ((this->body).flagSet)->flags;
    bVar15 = *(byte *)((int)&paVar8->attackFlags_ + 1) | 2;
  }
  *(byte *)((int)&paVar8->attackFlags_ + 1) = bVar15;
  if (local_10 == 0) {
    paVar8 = ((this->body).flagSet)->flags;
    bVar15 = *(byte *)((int)&paVar8->flag1 + 2) & 0xdf;
  }
  else {
    paVar8 = ((this->body).flagSet)->flags;
    bVar15 = *(byte *)((int)&paVar8->flag1 + 2) | 0x20;
  }
  *(byte *)((int)&paVar8->flag1 + 2) = bVar15;
  paVar8 = ((this->body).flagSet)->flags;
  *(byte *)((int)&paVar8->flag1 + 1) = *(byte *)((int)&paVar8->flag1 + 1) & 0xdf;
  (this->body).movementIndex = uVar7;
  goto LAB_00074ed8;
  while( true ) {
    iVar14 = iVar14 + 1;
    col_somethings = col_somethings + 0x15;
    if (i <= iVar14) break;
LAB_00074b94:
    delta = Globals::ColliderSomethings[0].velocity.x - ADJ(col_somethings).v.x;
    if (((((delta < -0.01) || (0.01 < delta)) ||
         (delta = Globals::ColliderSomethings[0].velocity.y - ADJ(col_somethings).v.y, delta < -0.01
         )) || ((0.01 < delta ||
                (delta = Globals::ColliderSomethings[0].velocity.z - ADJ(col_somethings).v.z,
                delta < -0.01)))) || (0.01 < delta)) {
                    // Doesn't seem to run under normal circumstances?
      local_58.x = (this->body).worldPosition.x - pos1.x;
      local_58.z = (this->body).worldPosition.z - pos1.z;
      delta = local_70.x - pos1.x;
      speed = local_70.z - pos1.z;
      fVar19 = local_58.x * local_58.x + local_58.z * local_58.z;
      pos2.y = 0.0;
      local_58.y = 0.0;
      if (fVar19 != 0.0) {
        fVar18 = (float10)invsqrt(fVar19);
        local_58.x = (float)((float10)local_58.x * fVar18);
        local_58.y = (float)((float10)0.0 * fVar18);
        local_58.z = (float)((float10)local_58.z * fVar18);
      }
      fVar19 = delta * delta + speed * speed;
      if (fVar19 != 0.0) {
        fVar18 = (float10)invsqrt(fVar19);
        delta = (float)((float10)delta * fVar18);
        pos2.y = (float)((float10)0.0 * fVar18);
        speed = (float)((float10)speed * fVar18);
      }
      if (delta * local_58.x + speed * local_58.z + local_58.y * pos2.y < 0.0) {
        local_3c = 0;
        goto LAB_00074d4f;
      }
      break;
    }
  }
LAB_00074bd1:
  paVar8 = ((this->body).flagSet)->flags;
  bVar15 = *(byte *)((int)&paVar8->flag1 + 2) | 0x20;
LAB_00074e05:
  speed = local_70.z;
  delta = local_70.x;
  *(byte *)((int)&paVar8->flag1 + 2) = bVar15;
  mem = (actorr->avatar).physicsCtx;
  pos2.y = local_70.y - yOffset;
  pos2.x = local_70.x;
  pos2.z = local_70.z;
  if (mem == (AvatarPhysicsContext *)0x0) {
LAB_00074ea3:
    (actorr->avatar).pos.x = delta;
    (actorr->avatar).pos.y = pos2.y;
    (actorr->avatar).pos.z = speed;
  }
  else {
    if ((mem->actor == (actor *)0x0) &&
       ((pEVar9 = (actorr->avatar).node0x918.prev, pEVar9 == (avatar_0x918)0x0 ||
        (pEVar9->prev == (avatar_0x918)0x0)))) {
      somethingsIndex = FindHeapOf(mem);
      uVar11 = runtime::CurrentHeapToAllocateFrom;
      if (g_HeapTableBase[somethingsIndex].heapHandle == (HANDLE)0x0) {
        pHVar16 = (HeapTableEntry *)0x0;
      }
      else {
        pHVar16 = g_HeapTableBase + somethingsIndex;
      }
      runtime::CurrentHeapToAllocateFrom = somethingsIndex;
      XAPILIB::HeapFree(pHVar16->heapHandle,0,mem);
      runtime::CurrentHeapToAllocateFrom = uVar11;
      (someActor->avatar).physicsCtx = (AvatarPhysicsContext *)0x0;
      actorr = someActor;
      goto LAB_00074ea3;
    }
    delta = (mem->yRow).y;
    speed = (mem->yRow).x;
    fVar19 = (mem->yRow).z;
    fVar2 = (mem->zRow).x;
    fVar3 = mem->yOffset;
    fVar4 = (mem->zRow).y;
    fVar5 = (mem->zRow).z;
    fVar6 = mem->zOffset;
    (actorr->avatar).pos.x =
         (mem->xRow).y * pos2.y + (mem->xRow).z * local_70.z + (mem->xRow).x * local_70.x +
         mem->xOffset;
    (actorr->avatar).pos.y = speed * local_70.x + delta * pos2.y + fVar19 * local_70.z + fVar3;
    (actorr->avatar).pos.z = fVar2 * local_70.x + fVar4 * pos2.y + fVar5 * local_70.z + fVar6;
  }
  paVar10 = actorr->body;
  (actorr->avatar).anglesCalculated = 0;
                    // Updates players position when coming to a stop
  avatar::getWorldPosition(&paVar10->actor->avatar,&paVar10->worldPosition);
LAB_00074ed8:
  actorr = someActor;
  if (((((this->body).flagSet)->flags->attackFlags_ & 0x200) == Null) &&
     ((this->body).field_0x19e != '\0')) {
    local_8 = (this->body).dir1.y;
    avatar::getWorldPosition(&someActor->avatar,&local_58);
    if (local_58.y <= local_8 + 5.0) {
      bg_col_thing = BackgroundCollisionThings[actorr->backgroundCollisionIndex];
      if ((bg_col_thing == (BackgroundCollisionThing *)0x0) ||
         (somethingsIndex =
               Background::isCollisionThings(actorr->backgroundCollisionIndex,&local_58),
         somethingsIndex == -1)) {
        cVar12 = '\0';
      }
      else {
        cVar12 = *(char *)(bg_col_thing->field10_0x10 + 0xb + somethingsIndex * 0x12);
        if (cVar12 == '\0') {
          cVar12 = *(char *)(bg_col_thing->field10_0x10 + somethingsIndex * 0x12 + 10);
        }
      }
      (this->body).movementIndex = cVar12;
    }
  }
  actorr = (this->body).actor;
  if (runtime::dx_timer <= 0.0) {
    delta = runtime::DeltaTime * runtime::TimeScale;
  }
  else {
    delta = 0.0;
  }
  speed = 0.0;
  if ((actorr->avatar).movementFreezeTimer <= 0.0) {
    speed = (actorr->avatar).actionSpeed;
  }
  pfVar14 = (this->body).bigVec3Set + (this->body).bigVec3SetIndex;
  pfVar14->x = pos2.x - pos1.x;
  pfVar14->y = pos2.y - pos1.y;
  pfVar14->z = pos2.z - pos1.z;
  if (0.0 < speed * delta) {
    delta = 1.0 / (speed * delta);
    pvVar1 = (this->body).bigVec3Set + (this->body).bigVec3SetIndex;
    pvVar1->x = delta * pvVar1->x;
    pvVar1->y = delta * pvVar1->y;
    pvVar1->z = delta * pvVar1->z;
  }
  (this->body).bigVec3SetIndex = ((this->body).bigVec3SetIndex + 1) % 0x50;
  (this->body).v1.x = pos2.x - pos1.x;
  (this->body).v1.y = pos2.y - pos1.y;
  (this->body).v1.z = pos2.z - pos1.z;
  return local_3c;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void entityBodyHuman::loadCollisionFromSubres0x4(entityBodyHuman *human)

{
  Model *pMVar1;
  ModelDescriptor *pMVar2;
  uint uVar3;
  AnimCollisionSubresourceEntry **pcVar4;
  HumanAnimColliderData *pHVar4;
  ModelFooterEntry *pMVar5;
  int i;
  AnimCollisionSubresourceEntry *entry;
  uint size;
  int local_4;
  AnimCollisionSubresource *anim_collisions;
  
  pMVar1 = (((human->body).actor)->avatar).model;
  size = 0;
  if ((pMVar1 != (Model *)0x0) && (pMVar2 = pMVar1->descriptor, pMVar2 != (ModelDescriptor *)0x0)) {
    uVar3 = 0;
    if (pMVar2->numFooterEntries != 0) {
      pMVar5 = pMVar2->footerEntries;
      while (pMVar5->subresourceType != AnimColliders) {
        uVar3 = uVar3 + 1;
        pMVar5 = pMVar5 + 1;
        if (pMVar2->numFooterEntries <= uVar3) {
          return;
        }
      }
      anim_collisions = (AnimCollisionSubresource *)pMVar2->footerEntries[uVar3].offset;
      if (anim_collisions != (AnimCollisionSubresource *)0x0) {
        i = 0;
        local_4 = 0;
        for (entry = anim_collisions->entries; entry != (AnimCollisionSubresourceEntry *)0x0;
            entry = (AnimCollisionSubresourceEntry *)(&entry->colliderType + (byte)entry->size)) {
          if (((entry->collisionMask & Walls) != Nothing) && (entry->colliderType < Box)) {
            if (i == local_4) {
              local_4 = local_4 + 4;
              size = size + 0x10;
              if (human->animColliders == (AnimCollisionSubresourceEntry **)0x0) {
                pcVar4 = malloc_(size);
              }
              else {
                pcVar4 = (AnimCollisionSubresourceEntry **)
                         AllocateMoreAStruct_33(size,human->animColliders);
              }
              human->animColliders = pcVar4;
            }
            human->animColliders[i] = entry;
            i = i + 1;
          }
          if (entry->size == 0) break;
        }
        human->numAnimColliders = i;
        if (i != 0) {
                    // * 32
          pHVar4 = malloc_(i << 5);
          human->animCollidersData = pHVar4;
        }
      }
    }
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields

BOOL entityBodyHuman::testCollisionWithBackground
               (entityBodyHuman *body,vec3 *maxV,actor *actt,vec3 *v,vec3 *param_5,float maxHeight,
               float param_7)

{
  vec3 *smth2;
  actorBodyFlags *paVar1;
  BackgroundCollisionThing *pBVar2;
  int iVar3;
  char cVar4;
  undefined1 *collisionFunction;
  int collisionOccurred;
  float fVar5;
  float fVar6;
  float act_x;
  float act_y;
  vec3 sphereStart;
  vec3 local_18;
  vec3 sphereEnd;
  actor *act;
  
  fVar5 = v->y;
  if (v->y <= maxV->y) {
    fVar5 = maxV->y;
  }
  sphereStart.x = v->x;
  sphereStart.z = v->z;
  fVar5 = fVar5 + (((body->body).actor)->avatar).scale.y * body->physicsScalar;
  sphereStart.y = param_5->y - maxHeight;
  if (sphereStart.y < fVar5) {
    sphereStart.y = fVar5;
  }
  sphereEnd.y = sphereStart.y - (param_7 + 50.0);
  paVar1 = ((body->body).flagSet)->flags;
  *(byte *)((int)&paVar1->attackFlags_ + 1) = *(byte *)((int)&paVar1->attackFlags_ + 1) & 0xfd;
  smth2 = &(body->body).dir1;
  sphereEnd.x = sphereStart.x;
  sphereEnd.z = sphereStart.z;
  collisionFunction = actorBody::getCollisionDrone(&body->body);
                    // Test against background
  collisionOccurred =
       Collision::checkAvatarsWithCollisionInScene(&sphereStart,&sphereEnd,Ground,collisionFunction)
  ;
  if (collisionOccurred != 0) {
    resolveCollision((Physics::CollisionContexts[0].ctx)->head,smth2);
    local_18.x = smth2->x;
    local_18.z = (body->body).dir1.z;
    act = (body->body).actor;
    act_x = (act->avatar).physicsPos.x;
    act_y = (act->avatar).physicsPos.z;
    local_18.y = (body->body).dir1.y;
    fVar6 = v->y - local_18.y;
    if (fVar5 < local_18.y) {
      paVar1 = ((body->body).flagSet)->flags;
      *(byte *)((int)&paVar1->attackFlags_ + 1) = *(byte *)((int)&paVar1->attackFlags_ + 1) | 2;
      pBVar2 = BackgroundCollisionThings[actt->backgroundCollisionIndex];
      if ((pBVar2 == (BackgroundCollisionThing *)0x0) ||
         (collisionOccurred =
               Background::isCollisionThings(actt->backgroundCollisionIndex,&local_18),
         collisionOccurred == -1)) {
        cVar4 = '\0';
      }
      else {
        iVar3 = pBVar2->field10_0x10;
        cVar4 = *(char *)(iVar3 + 0xb + collisionOccurred * 0x12);
        if (cVar4 == '\0') {
          cVar4 = *(char *)(iVar3 + collisionOccurred * 0x12 + 10);
        }
      }
      (body->body).movementIndex = cVar4;
      param_5->y = fVar5 + param_7;
      act = (body->body).actor;
      (act->avatar).physicsPos.y = 0.0;
      (act->avatar).physicsPos.x = act_x;
      (act->avatar).physicsPos.z = act_y;
      return 1;
    }
    fVar5 = 0.0;
    if (((fVar6 < 0.0) || ((-0.001 <= fVar6 && (fVar6 <= 0.001)))) &&
       ((act->avatar).physicsPos.y <= 0.0)) {
      paVar1 = ((body->body).flagSet)->flags;
      *(byte *)((int)&paVar1->attackFlags_ + 1) = *(byte *)((int)&paVar1->attackFlags_ + 1) | 2;
      cVar4 = FUN_001117a0(actt->backgroundCollisionIndex,&local_18);
      (body->body).movementIndex = cVar4;
      param_5->y = local_18.y + param_7;
      act = (body->body).actor;
      (act->avatar).physicsPos.y = fVar5;
      (act->avatar).physicsPos.x = act_x;
      (act->avatar).physicsPos.z = act_y;
    }
    return 1;
  }
  (body->body).field_0x19e = 0;
  return 0;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void entityBodyHuman::onMessage(entityBodyHuman *human,Message *msg)

{
  onMessage(human,msg);
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void entityBodyPlayer::getAllocDetails(ObjectAllocDetails *param_1)

{
  param_1->entitySize = 0x950;
  param_1->paramsSize = 0x820;
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void entityBodyPlayer::getVTable(void)

{
  actorBody::makeActorBodyVTable(&vtable);
  vtable.update = entityBodyHuman::update;
  vtable.updateMovement = actorBody::updateMovement;
  vtable.updatePosAndRot = actorBody::updatePosAndRot;
  vtable.computeMovementAndCollisions = entityBodyHuman::computeMovementAndCollisions;
  vtable.getAllocDetails = getAllocDetails;
  vtable.ctor = obj::returnOne;
  vtable.dtor = switchD_000d4179::EmptyFunction;
  vtable.onMessage = onMessage;
  vtable.getStandingState = getStandingState;
  vtable.getWalkState = getWalkState;
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields
// Disabling this prevents the player from hitting other things, including
// - punching ghoulie
// - punching environment
// - hitting with weapons (but can still pick them up)
// 
// Tested on scullery 1
// 
// 
// 
// 
// If condition 1 is forced,
// - Player not spotted by spider on wall
// 
// - Player can't hit ghoulies
// - Ghoulies can't hit player
// 
// - Grim reaper can't see player????
//  - Won't chase
//  - Won't even kill if you walk up to him
//  - Does turn head towards player though
// 
// - Picked up throwables break instantly once their pickup animation ends
//  - Probs not re-parented properly [1]
// 
// WHAT THIS DOESN'T BREAK
// - Player can still trigger challenge start
// - Can still pick up soups
// - Can still pick up weapons
// - Still shocked by broom woman
// 
// 
// [1]
// The weapon code probably looks something like
// 
// If in animation:
//  wait
// if not in animation:
//  If not parented to anything:
//   break
// 
// If condition 2 is forced
// 
// 
// 
// This function doesn't run during level opening cutscene


void entityBodyPlayer::onMessage(entityBodyPlayer *body,Scene_PowerupActivatedMessage *param_2)

{
  ObjMsgID OVar1;
  
  OVar1 = (param_2->header).msgId;
                    // Skipping both of these causes crash instantly when not in level start
                    // cutscene
  if (OVar1 == Scene_PowerupActivated) {
                    // Skipping this function call directly instead of the entire first condition
                    // changes nothing changes nothing???
    onPowerupActivated(body,param_2);
    return;
  }
                    // Major event handler
  if (OVar1 != Scene_PowerupDeactivated) {
                    // Type is 0x87
    entityBodyHuman::onMessage(&body->human,(Message *)param_2);
    return;
  }
                    // Handles New_Name_(135) ONLY
  resolveSoupEnding(body,(Message *)param_2);
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


actorBodyStateId entityBodyPlayer::getStandingState(actorBody *body)

{
  Buffer<> *pBVar1;
  actorBody *body_00;
  actorBodyStateId aVar2;
  StatetableEntry *pSVar3;
  actorDroneActionId *paVar4;
  
  body_00 = body;
  if ((body->health == 0) && (body->statetableRes != (StatetableResource *)0x0)) {
    pSVar3 = binarySearchStateTable(body->statetableRes,(Asset **)&body,FaintFromStanding);
    if (pSVar3 != (StatetableEntry *)0x0) {
      return FaintFromStanding;
    }
  }
  if ((body_00->flagSet->flags->attackFlags_ & 0x1000) != Null) {
    return ScareStand;
  }
  pBVar1 = body_00->actor->droneActionsBuf;
  if (pBVar1 != (Buffer<> *)0x0) {
    if (pBVar1->size == pBVar1->endOfQueue) {
      paVar4 = (actorDroneActionId *)0x0;
    }
    else {
      paVar4 = (actorDroneActionId *)
               ((int)&pBVar1->entries->actionId +
               (uint)pBVar1->currentDroneAction * (uint)pBVar1->valueSize);
    }
    if (*paVar4 == StandNervously) {
      aVar2 = (*body_00->vtable->getNervousState)(body_00);
      return aVar2;
    }
  }
  aVar2 = actorBody::getStandingState(body_00);
  return aVar2;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


actorBodyStateId entityBodyPlayer::getWalkState(actorBody *param_1)

{
  actorBodyStateId aVar1;
  
  if ((param_1->flagSet->flags->attackFlags_ & 0x1000) != Null) {
    return ScareStagger;
  }
  aVar1 = actorBody::getWalkState(param_1);
  return aVar1;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields
// Doesn't handle challenge complete

void __fastcall
entityBodyPlayer::onPowerupActivated
          (entityBodyPlayer *playerBody,Scene_PowerupActivatedMessage *msg)

{
  undefined1 *puVar1;
  actor *act;
  ushort uVar2;
  ushort curr_health;
  
  act = (playerBody->human).body.actor;
  if ((msg->header).someActor == act) {
    switch(msg->powerupType) {
    case EnergyBoost:
      curr_health = (playerBody->human).body.health;
      uVar2 = (playerBody->human).body.maxHealth + (short)msg->healthIncrease;
      (playerBody->human).body.health = uVar2;
      (playerBody->human).body.maxHealth = uVar2;
      (playerBody->human).body.health = (short)msg->healthIncrease + curr_health;
      if (playerBody->energySapped_ != 0) {
        playerBody->storedHealth = playerBody->storedHealth + msg->healthIncrease;
        return;
      }
      break;
    case EnergyRobber:
      curr_health = (playerBody->human).body.health;
      if (curr_health != 0) {
        if (playerBody->energySapped_ == 0) {
          playerBody->storedHealth = (uint)curr_health;
          playerBody->energySapped_ = 1;
        }
        (playerBody->human).body.health = 1;
        return;
      }
      playerBody->storedHealth = 0;
      return;
    case InstantDeath:
      if (*(int *)&msg->field_0x10 == 0) {
        FUN_0013b7e0(act,&playerBody->someU32,GrimReaper);
        return;
      }
      break;
    case Invisibility:
      if (*(int *)&msg->field_0x10 == 0) {
        puVar1 = &(act->avatar).field_0x197;
        *puVar1 = *puVar1 + '\x01';
        FUN_0003ef40(act);
        ::actor::executeCallout(act,0,InvisibilityBegin);
        if ((act->avatar).as23ptr != (astruct_23 *)0x0) {
          FUN_0012b1a0();
          return;
        }
      }
      break;
    case Invulnerability:
      actorBody::setFlag((actorBody *)playerBody,7);
      return;
    case PlayerSlowDown:
      (act->avatar).actionSpeed = 0.5;
      return;
    case PlayerSpeedUp:
      (act->avatar).actionSpeed = 1.5;
    }
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void entityBodyHuman::getAllocDetails(undefined4 *param_1)

{
  *param_1 = 0x924;
  param_1[1] = 0x820;
  return;
}



// WARNING: Globals starting with '_' overlap smaller symbols at the same address
// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void entityBodyHuman::onEscapeBackground(int param_1,actor *actor)

{
  actorBody *body;
  HitReactionResource *assetName;
  objParams *params;
  MessageHeader local_14;
  vec3 local_c;
  
  body = actor->body;
  FUN_00134ef0();
  if ((body->hitReactionRes == (HitReactionResource *)0x0) ||
     (body->hitReactionRes->field_0x19a == '\0')) {
    if (*(int *)&actor->field_0xce4 != 0) {
      local_c.x = 0.0;
      local_c.y = 0.0;
      local_c.z = 0.0;
      local_14.msgId = Director_KeyCarrierDied;
      local_14.someActor = actor;
      avatar::getWorldPosition(&actor->avatar,&local_c);
      EventLoop::NewMessage(&local_14);
    }
    if ((*(int *)&actor->field_0xce0 == 0) ||
       ((actor->actorType != Human && ((actor->node0x93c).prev == (actor_0x93c)0x0)))) {
      assetName = body->hitReactionRes;
      if (assetName != (HitReactionResource *)0x0) {
        assetName = (HitReactionResource *)assetName->field6_0x110;
      }
      if (((param_1 != 0) && (assetName != (HitReactionResource *)0x0)) &&
         (assetName->field0_0x0 == 0x5f646961)) {
        params = Assets::GetObjParams((char *)assetName);
        if (params == (objParams *)0x0) {
          return;
        }
        FUN_0001b810(body,1,0);
        *(actor **)&params[0x66].typeIndex = actor;
        Assets::CreateEntityFromParams(params);
        free(params);
        FUN_00135080(actor);
      }
      avatar::destroy(&actor->avatar);
    }
    else if (-1 < (char)(g_globalFlagset >> 8)) {
      setNextPlaycamScriptAID(1,Game::GameState.currentSceneScript);
      g_finishedLoading_ = 1;
      return;
    }
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


