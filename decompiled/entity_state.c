/* entity_state.c - Actor state machines (walk/hit/scoop/pickup, etc.) */
#include "entity_state.h"

entityStateWalk::onActorStruggle(int param_1,actorBody *body,Actor_StruggleMessage *msg)

{
  actor *paVar1;
  actorBodyStateId reactionState;
  
  paVar1 = (msg->header).someActor;
  if ((actor *)param_1 == paVar1) {
    if (body->health == 0) {
      msg->field2_0x8 = 0;
      return;
    }
    if (paVar1 != (actor *)0x0) {
      actorBody::processHitReaction(body,0x117);
      msg->field2_0x8 = 1;
      return;
    }
    reactionState = (*body->vtable->getStandingState)(body);
    actorBody::processHitReaction(body,reactionState);
    msg->field2_0x8 = 1;
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


actorStateVTable * actorState::getVTable(void)

{
  vtable.getAllocDetails = getAllocDetails;
  vtable.ctor = ctor;
  vtable.dtor = switchD_000d4179::EmptyFunction;
  vtable.onMessage = switchD_000d4179::EmptyFunction;
  vtable.update = update;
  vtable.func5 = switchD_000d4179::EmptyFunction;
  vtable.func6 = switchD_000d4179::EmptyFunction;
  vtable.func7 = func7;
  return &vtable;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


undefined4 actorState::ctor(actorState *res,actorStateParams *params)

{
  res->body = params->body;
  return 1;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


ushort actorState::func7(actorState *param_1)

{
  return param_1->func6ret;
}




void entityStateDie::getAllocDetails(ObjectAllocDetails *param_1)

{
  param_1->entitySize = 0x28;
  param_1->paramsSize = 0x14;
  return;
}




undefined ** entityStateDie::getVTable(void)

{
  PTR_ARRAY_00505740[5] = switchD_000d4179::EmptyFunction;
  PTR_ARRAY_00505740[6] = switchD_000d4179::EmptyFunction;
  PTR_ARRAY_00505740[7] = actorState::func7;
  PTR_ARRAY_00505740[0] = getAllocDetails;
  PTR_ARRAY_00505740[1] = ctor;
  PTR_ARRAY_00505740[2] = &LAB_0008c750;
  PTR_ARRAY_00505740[3] = switchD_000d4179::EmptyFunction;
  PTR_ARRAY_00505740[4] = updateFixed_;
  return PTR_ARRAY_00505740;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


undefined4 entityStateDie::ctor(entityStateDie *state,entityStateDieParams *params)

{
  undefined1 uVar1;
  actor *paVar2;
  undefined4 uStack_8;
  actor *paStack_4;
  actorBody *paVar3;
  void *fVar4;
  actorMind *mind;
  astruct_7 *puVar2;
  actor *act;
  actorBody *bodyy;
  
  bodyy = (state->actorMove).body;
  puVar2 = (astruct_7 *)bodyy->flagSet->flags;
  act = bodyy->actor;
  mind = act->mind;
  puVar2->field3_0x3 = puVar2->field3_0x3 | 8;
  bodyy->field_0x309 = bodyy->field_0x309 + '\x01';
  bodyy->field_0x30a = bodyy->field_0x30a + '\x01';
  bodyy->field_0x30b = bodyy->field_0x30b + '\x01';
  bodyy->field_0x30c = bodyy->field_0x30c + '\x01';
  bodyy->field13_0x30 = bodyy->field13_0x30 + 1;
  bodyy->skipBlendTargetUpdate = true;
  bodyy->blendTargets[1].blendState = '\x05';
  bodyy->blendTargets[1].float1 = 0.09;
  bodyy->blendTargets[0].blendState = '\x05';
  bodyy->blendTargets[0].float1 = 0.09;
  bodyy->farRangeThreshold = true;
  bodyy->someHitFlag = true;
  actorBody::resetFlags(bodyy);
  bodyy->dead = true;
  paVar2 = (actor *)0x0;
  if (*(int *)&params->field_0xc != 0) {
    act = (actor *)(act->avatar).as23ptr;
    while (act != (actor *)0x0) {
      paVar2 = *(actor **)&(act->avatar).field_0x4;
      FUN_0012b0b0((int)act);
      act = paVar2;
    }
  }
  if ((actor *)mind != paVar2) {
    mind->targetActor = paVar2;
    if ((actor *)mind->targetBody != paVar2) {
      uStack_8 = 100;
      paStack_4 = paVar2;
      (*((mind->actor->avatar).vtable)->onMessage)(mind->actor,&uStack_8);
    }
    fVar4 = mind->memoryHead;
    mind->targetBody = (actorBody *)paVar2;
    mind->currentAttackTarget = (actorBody *)paVar2;
    for (; fVar4 != paVar2; fVar4 = *(void **)&(((actor *)fVar4)->avatar).field_0x4) {
      if (*(short *)&(((actor *)fVar4)->avatar).pos.x == 3) {
        MindMemory::dtor(fVar4);
        break;
      }
    }
  }
  *(actor **)&state->field_0x18 = paVar2;
  uVar1 = FUN_0001feb0(bodyy);
  state->field_0x20 = uVar1;
  FUN_00024910();
  return 1;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void entityStateDie::updateFixed_(entityStateDie *param_1)

{
  actorBody *paVar1;
  actor *paVar2;
  KeyframeContext *pKVar3;
  bool bVar4;
  float fVar5;
  float fVar6;
  astruct_40 *iVar3;
  
  paVar1 = (param_1->actorMove).body;
  paVar2 = paVar1->actor;
  if (runtime::dx_timer <= 0.0) {
    fVar6 = runtime::DeltaTime * runtime::TimeScale;
  }
  else {
    fVar6 = 0.0;
  }
  fVar5 = 0.0;
  if ((paVar2->avatar).movementFreezeTimer <= 0.0) {
    fVar5 = (paVar2->avatar).actionSpeed;
  }
  (param_1->actorMove).t = fVar5 * fVar6 + (param_1->actorMove).t;
  (paVar1->rotation).z = 0.0;
  (paVar1->rotation).x = 0.0;
  if (*(int *)&param_1->field_0x18 == 0) {
    pKVar3 = (paVar2->avatar).keyframeContext;
    if ((pKVar3 != (KeyframeContext *)0x0) &&
       (iVar3 = (astruct_40 *)pKVar3->kfcAnims->animInstance, iVar3 != (astruct_40 *)0x0)) {
      bVar4 = false;
      if (iVar3->field36_0x2a == '\x01') {
        if (iVar3->field25_0x1c <= 0.0 && iVar3->field25_0x1c != 0.0) {
          bVar4 = 0.0 < iVar3->field20_0x14;
        }
        else {
          bVar4 = iVar3->field20_0x14 < 1.0;
        }
        if (bVar4) {
          bVar4 = false;
        }
        else {
          bVar4 = true;
        }
      }
      if (!bVar4) {
        return;
      }
    }
    *(undefined4 *)&param_1->field_0x18 = 1;
    *(float *)&param_1->field_0x1c = 1.0;
  }
  else if (*(int *)&param_1->field_0x18 == 1) {
    paVar2 = ((param_1->actorMove).body)->actor;
    if (runtime::dx_timer <= 0.0) {
      fVar6 = runtime::DeltaTime * runtime::TimeScale;
    }
    else {
      fVar6 = 0.0;
    }
    fVar5 = 0.0;
    if ((paVar2->avatar).movementFreezeTimer <= 0.0) {
      fVar5 = (paVar2->avatar).actionSpeed;
    }
    if ((0.0 < *(float *)&param_1->field_0x1c) &&
       (fVar6 = *(float *)&param_1->field_0x1c - fVar5 * fVar6,
       *(float *)&param_1->field_0x1c = fVar6, fVar6 <= 0.0)) {
      *(undefined4 *)&param_1->field_0x1c = 0;
      entityBodyHuman::onEscapeBackground(1,paVar1->actor);
      return;
    }
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


actorStateVTable * entityStateExplode::getVTable(void)

{
  actorStateVTable_005057e0.func5 = switchD_000d4179::EmptyFunction;
  actorStateVTable_005057e0.func6 = switchD_000d4179::EmptyFunction;
  actorStateVTable_005057e0.func7 = actorState::func7;
  actorStateVTable_005057e0.getAllocDetails = (getAllocDetailsFn *)&LAB_0008e740;
  actorStateVTable_005057e0.ctor = ctor;
  actorStateVTable_005057e0.dtor = dtor;
  actorStateVTable_005057e0.onMessage = switchD_000d4179::EmptyFunction;
  actorStateVTable_005057e0.update = &LAB_0008ea90;
  return &actorStateVTable_005057e0;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


undefined4 entityStateExplode::ctor(int param_1)

{
  avatar_conflict13 *paVar1;
  avatar_conflict13 *paVar2;
  actorBody *paVar3;
  actor *paVar4;
  avatar_0x900_conflict6 pEVar5;
  uint32_t uVar6;
  char cVar7;
  Message local_8;
  
  paVar3 = *(actorBody **)(param_1 + 8);
  paVar4 = paVar3->actor;
  paVar3->field_0x6a = paVar3->field_0x6a + '\x01';
  paVar3->field_0x309 = paVar3->field_0x309 + '\x01';
  paVar3->field_0x30b = paVar3->field_0x30b + '\x01';
  paVar3->field_0x30a = paVar3->field_0x30a + '\x01';
  paVar3->field_0x30c = paVar3->field_0x30c + '\x01';
  uVar6 = actorBody::getFlagsBitfield(paVar3);
  paVar3->flag1 = (bool)(paVar3->flag1 + '\x01');
  paVar3->flag2 = paVar3->flag2 + '\x01';
  paVar3->flag3 = paVar3->flag3 + '\x01';
  paVar3->flag4 = paVar3->flag4 + '\x01';
  paVar3->flag5 = paVar3->flag5 + '\x01';
  paVar3->flag6 = paVar3->flag6 + '\x01';
  cVar7 = paVar3->flag1 != false;
  if (paVar3->flag2 != '\0') {
    cVar7 = cVar7 + '\x02';
  }
  if (paVar3->flag3 != '\0') {
    cVar7 = cVar7 + '\x04';
  }
  if (paVar3->flag4 != '\0') {
    cVar7 = cVar7 + '\b';
  }
  if (paVar3->flag5 != '\0') {
    cVar7 = cVar7 + '\x10';
  }
  if (paVar3->flag6 != '\0') {
    cVar7 = cVar7 + ' ';
  }
  if ((uVar6 == 0x3f) && (cVar7 != '?')) {
    local_8.header.someActor = paVar3->actor;
    local_8.header.msgId = Actor_NoLongerInvulnerable;
    pEVar5 = Game::SceneInfo.avatars.next;
    while (pEVar5 != (avatar_0x900_conflict6)0x0) {
      paVar1 = ADJ(pEVar5);
      paVar2 = ADJ(pEVar5);
      pEVar5 = pEVar5->next;
      (*((paVar1->object).vtable)->onMessage)(paVar2,&local_8);
    }
  }
  paVar3->numStatesDeep = paVar3->numStatesDeep + 1;
  paVar3->backedUpAirResistance = paVar3->airResistance;
  paVar3->airResistance = 0.0;
  FUN_0003e850((entityAvatarFxBurnup *)paVar4);
  paVar3->farRangeThreshold = true;
  paVar3->someHitFlag = true;
  *(undefined4 *)(param_1 + 0x18) = 0;
  return 1;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void entityStateExplode::dtor(actorState *param_1)

{
  avatar_conflict13 *paVar1;
  avatar_conflict13 *paVar2;
  avatar_0x900_conflict6 pEVar3;
  uint32_t uVar4;
  char cVar5;
  Message local_8;
  actorBody *body;
  
  body = param_1->body;
  body->field_0x6a = body->field_0x6a + -1;
  body->field_0x309 = body->field_0x309 + -1;
  body->field_0x30b = body->field_0x30b + -1;
  body->field_0x30a = body->field_0x30a + -1;
  body->field_0x30c = body->field_0x30c + -1;
  uVar4 = actorBody::getFlagsBitfield(body);
  body->flag1 = (bool)(body->flag1 + -1);
  body->flag2 = body->flag2 + -1;
  body->flag3 = body->flag3 + -1;
  body->flag4 = body->flag4 + -1;
  body->flag5 = body->flag5 + -1;
  body->flag6 = body->flag6 + -1;
  cVar5 = body->flag1 != false;
  if (body->flag2 != '\0') {
    cVar5 = cVar5 + '\x02';
  }
  if (body->flag3 != '\0') {
    cVar5 = cVar5 + '\x04';
  }
  if (body->flag4 != '\0') {
    cVar5 = cVar5 + '\b';
  }
  if (body->flag5 != '\0') {
    cVar5 = cVar5 + '\x10';
  }
  if (body->flag6 != '\0') {
    cVar5 = cVar5 + ' ';
  }
  if ((uVar4 == 0x3f) && (cVar5 != '?')) {
    local_8.header.someActor = body->actor;
    local_8.header.msgId = Actor_NoLongerInvulnerable;
    pEVar3 = Game::SceneInfo.avatars.next;
    while (pEVar3 != (avatar_0x900_conflict6)0x0) {
      paVar1 = ADJ(pEVar3);
      paVar2 = ADJ(pEVar3);
      pEVar3 = pEVar3->next;
      (*((paVar1->object).vtable)->onMessage)(paVar2,&local_8);
    }
  }
  body->airResistance = body->backedUpAirResistance;
  body->numStatesDeep = body->numStatesDeep - 1;
  if ((param_1[1].body != (actorBody *)0x0) && (param_1[1].body != (actorBody *)0x0)) {
    FUN_0013ee80();
    free(param_1[1].body);
    param_1[1].body = (actorBody *)0x0;
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void entityStateFaint::getAllocDetails(undefined4 *param_1)

{
  *param_1 = 0x3c;
  param_1[1] = 0x18;
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


undefined ** entityStateFaint::getVTable(void)

{
  PTR_ARRAY_00505800[5] = switchD_000d4179::EmptyFunction;
  PTR_ARRAY_00505800[6] = switchD_000d4179::EmptyFunction;
  PTR_ARRAY_00505800[7] = actorState::func7;
  PTR_ARRAY_00505800[0] = getAllocDetails;
  PTR_ARRAY_00505800[1] = ctor;
  PTR_ARRAY_00505800[2] = dtor;
  PTR_ARRAY_00505800[3] = switchD_000d4179::EmptyFunction;
  PTR_ARRAY_00505800[4] = update;
  return PTR_ARRAY_00505800;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


undefined4 entityStateFaint::ctor(entityStateFaint *param_1,entityStateFaintParams *param_2)

{
  byte bVar1;
  actorBody *paVar2;
  actor *paVar3;
  actorMind *paVar4;
  actorBodyFlags *paVar5;
  float fVar6;
  MindMemoryTargetWantedToAttack *mem;
  char *pcVar7;
  actor *paVar8;
  undefined1 uVar9;
  AnimEventMapping *pAVar10;
  char *pcVar11;
  undefined4 local_8;
  undefined4 local_4;
  actorBody *as58_ptr;
  
  paVar2 = (param_1->actorState).body;
  paVar3 = paVar2->actor;
  paVar4 = paVar3->mind;
  paVar5 = paVar2->flagSet->flags;
  *(byte *)((int)&paVar5->flag1 + 3) = *(byte *)((int)&paVar5->flag1 + 3) | 8;
  paVar5 = paVar2->flagSet->flags;
  *(byte *)((int)&paVar5->flag1 + 3) = *(byte *)((int)&paVar5->flag1 + 3) | 0x10;
  paVar2->field_0x30c = paVar2->field_0x30c + '\x01';
  paVar2->field_0x30a = paVar2->field_0x30a + '\x01';
  paVar2->field_0x309 = paVar2->field_0x309 + '\x01';
  paVar2->field_0x30b = paVar2->field_0x30b + '\x01';
  paVar2->field13_0x30 = paVar2->field13_0x30 + 1;
  paVar2->farRangeThreshold = true;
  paVar2->someHitFlag = true;
  actorBody::resetFlags(paVar2);
  paVar2->dead = true;
  bVar1 = paVar2->field_0x717;
  paVar2->field_0x717 = 1;
  *(undefined4 *)&param_1->field_0x28 = 1;
  *(uint *)&param_1->field_0x30 = (uint)bVar1;
  *(undefined4 *)&param_1->field_0x24 = *(undefined4 *)&param_2->field_0x14;
  *(undefined4 *)&param_1->field_0x2c = 0;
  as58_ptr = (actorBody *)paVar2->weapon;
  if ((as58_ptr == (actorBody *)0x0) ||
     ((as58_ptr[1].field_0xab != '\x01' &&
      ((as58_ptr[1].field_0xab != '\x02' ||
       ((fVar6 = as58_ptr[1].bigVec3Set[0x24].y, fVar6 != 0.0 &&
        ((*(short *)((int)fVar6 + 0xcdc) == 2 || (*(int *)((int)fVar6 + 0x93c) != 0)))))))))) {
    FUN_0001b810(paVar2,0,0);
  }
  if (paVar4 != (actorMind *)0x0) {
    paVar4->targetActor = (actor *)0x0;
    if (paVar4->targetBody != (actorBody *)0x0) {
      local_8 = 100;
      local_4 = 0;
      (*((paVar4->actor->avatar).vtable)->onMessage)(paVar4->actor,&local_8);
    }
    mem = (MindMemoryTargetWantedToAttack *)paVar4->memoryHead;
    paVar4->targetBody = (actorBody *)0x0;
    paVar4->currentAttackTarget = (actorBody *)0x0;
    for (; mem != (MindMemoryTargetWantedToAttack *)0x0;
        mem = (MindMemoryTargetWantedToAttack *)(mem->header).next) {
      if ((mem->header).memId == TargedWantedToAttack) {
        MindMemory::dtor(mem);
        break;
      }
    }
  }
  uVar9 = FUN_0001feb0(paVar2);
  param_1->field_0x20 = uVar9;
  pcVar7 = *(char **)&param_2->field_0xc;
  if (pcVar7 == (char *)0x0) {
    pAVar10 = (AnimEventMapping *)0x0;
  }
  else {
    if (((paVar2->weapon == (weapon *)0x0) ||
        (pcVar11 = &paVar2->weapon->field1062_0xdb0, pcVar11 == (char *)0x0)) || (*pcVar11 == '\0'))
    {
      pcVar11 = (char *)0x0;
    }
    paVar8 = paVar2->actor;
    pAVar10 = avatar::getAnimEventByName(&paVar8->avatar,pcVar7,(BOOL)pcVar11);
    if ((pAVar10 == (AnimEventMapping *)0x0) && (pcVar11 != (char *)0x0)) {
      pAVar10 = avatar::getAnimEventByName(&paVar8->avatar,pcVar7,0);
    }
  }
  *(AnimEventMapping **)&param_1->field_0x34 = pAVar10;
  pcVar7 = *(char **)&param_2->field_0x10;
  if (((paVar2->weapon == (weapon *)0x0) ||
      (pcVar11 = &paVar2->weapon->field1062_0xdb0, pcVar11 == (char *)0x0)) || (*pcVar11 == '\0')) {
    pcVar11 = (char *)0x0;
  }
  paVar8 = paVar2->actor;
  pAVar10 = avatar::getAnimEventByName(&paVar8->avatar,pcVar7,(BOOL)pcVar11);
  if ((pAVar10 == (AnimEventMapping *)0x0) && (pcVar11 != (char *)0x0)) {
    pAVar10 = avatar::getAnimEventByName(&paVar8->avatar,pcVar7,0);
  }
  *(AnimEventMapping **)&param_1->field_0x38 = pAVar10;
  if (*(int *)&param_1->field_0x34 == 0) {
    FUN_0008f4d0();
  }
  else {
    paVar2 = (param_1->actorState).body;
    param_1->status = 0;
    FUN_0001afa0(*(int *)&param_1->field_0x34,paVar2);
  }
  if ((*(int *)&paVar3->field_0xce0 != 0) &&
     ((paVar3->actorType == Human || ((paVar3->node0x93c).prev != (actor_0x93c)0x0)))) {
    Game::NotAllowedToPause = Game::NotAllowedToPause + 1;
    GlobalCounter2 = GlobalCounter2 + 1;
  }
  return 1;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void entityStateFaint::dtor(int param_1)

{
  int iVar1;
  actorBody *paVar2;
  actorBodyFlags *paVar3;
  
  iVar1 = *(int *)(*(int *)(param_1 + 8) + 8);
  paVar2 = *(actorBody **)(iVar1 + 0x95c);
  paVar2->field13_0x30 = paVar2->field13_0x30 - 1;
  paVar2->field_0x309 = paVar2->field_0x309 + -1;
  paVar2->field_0x30a = paVar2->field_0x30a + -1;
  paVar2->field_0x30b = paVar2->field_0x30b + -1;
  paVar2->field_0x30c = paVar2->field_0x30c + -1;
  FUN_0001feb0(paVar2);
  if (*(int *)(param_1 + 0x28) != 0) {
    FUN_00025fa0();
    paVar2->field_0x717 = *(undefined1 *)(param_1 + 0x30);
    *(undefined4 *)(param_1 + 0x28) = 0;
  }
  actorBody::resetFlags();
  paVar3 = paVar2->flagSet->flags;
  *(byte *)((int)&paVar3->flag1 + 3) = *(byte *)((int)&paVar3->flag1 + 3) & 0xef;
  if ((*(int *)(iVar1 + 0xce0) != 0) &&
     ((*(short *)(iVar1 + 0xcdc) == 2 || (*(int *)(iVar1 + 0x93c) != 0)))) {
    Game::NotAllowedToPause = Game::NotAllowedToPause + -1;
    GlobalCounter2 = GlobalCounter2 + -1;
  }
  if (*(int *)(param_1 + 0x2c) != 0) {
    Audio::PlayOneOff("XACT_SOUNDBANK_GSTREAMSDITTIES_FAILPITCHBEND");
    *(undefined4 *)(param_1 + 0x2c) = 0;
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void entityStateFaint::update(entityStateFaint *state)

{
  actor *paVar2;
  KeyframeContext *pKVar3;
  astruct_14 *paVar4;
  BOOL BVar5;
  int iVar6;
  uint uVar7;
  int extraout_EDX;
  float advance_amount;
  float delta;
  actorStateInner1_Inner2_Inner1 *someas58;
  actor *paVar1;
  actorBody *inner1;
  
  inner1 = (state->actorState).body;
  paVar2 = inner1->actor;
  if (runtime::dx_timer <= 0.0) {
    delta = runtime::DeltaTime * runtime::TimeScale;
  }
  else {
    delta = 0.0;
  }
  advance_amount = 0.0;
  if ((paVar2->avatar).movementFreezeTimer <= 0.0) {
    advance_amount = (paVar2->avatar).actionSpeed;
  }
  (state->actorState).t = advance_amount * delta + (state->actorState).t;
  pKVar3 = (paVar2->avatar).keyframeContext;
  if (((pKVar3 == (KeyframeContext *)0x0) ||
      (someas58 = (actorStateInner1_Inner2_Inner1 *)pKVar3->kfcAnims->animInstance,
      someas58 == (actorStateInner1_Inner2_Inner1 *)0x0)) || (someas58->someF <= 0.5)) {
    (inner1->rotation).z = 0.0;
    (inner1->rotation).x = 0.0;
  }
  else {
    delta = (paVar2->avatar).rotEuler.y;
    advance_amount = delta;
    FUN_00136150();
    (inner1->rotation).x = advance_amount;
    (inner1->rotation).y = delta;
    (inner1->rotation).z = 0.0;
  }
  switch(state->status) {
  case 0:
    BVar5 = avatar::updateKeyframes(&paVar2->avatar,0);
    if (BVar5 != 0) {
      FUN_0008f4d0();
      return;
    }
    break;
  case 1:
    BVar5 = avatar::updateKeyframes(&paVar2->avatar,0);
    if (BVar5 != 0) {
      paVar2 = ((state->actorState).body)->actor;
      state->status = 2;
      if (*(int *)&state->field_0x28 != 0) {
        FUN_00025fa0();
        *(undefined1 *)(extraout_EDX + 0x717) = state->field_0x30;
        *(undefined4 *)&state->field_0x28 = 0;
      }
      *(float *)&state->field_0x1c = 1.0;
      BVar5 = FUN_00028d20((WeaponProjectilesContext *)paVar2);
      if ((BVar5 != 0) && (-1 < (char)(g_globalFlagset >> 8))) {
        EventLoop::CreateTransitionCameraAndText();
        return;
      }
    }
    break;
  case 2:
    BVar5 = FUN_00028d20((WeaponProjectilesContext *)paVar2);
    if (BVar5 == 0) {
      iVar6 = FUN_0002b630();
      if (iVar6 == 0) {
        return;
      }
      FUN_0008f650(state);
      return;
    }
    if (TransitionData.discReadEnum != 2) {
      return;
    }
    iVar6 = FUN_000f2b30();
    if (((iVar6 != 0) && (DAT_00430d9c <= (int)Game::DeathsInCurrentRoom)) &&
       ((uVar7 = Assets::GetChapterIndexFromAID(Game::GameState.currentSceneScript),
        paVar4 = PTR_00506c6c, (int)uVar7 < 8 && (INT_004e17c8 != 3)))) {
      state->status = 4;
      if ((paVar4->field2_0x8[4] & 2) != 0) {
        return;
      }
      if (INT_004e17c8 == 3) {
        return;
      }
      FUN_000f29d0();
      Events::BeginDialogSequence(0);
      return;
    }
    goto LAB_0008f49f;
  case 4:
    if (Game::DialogState != NotInDialog) {
      return;
    }
LAB_0008f49f:
    FUN_0008f650(state);
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void switchD_0008f359::caseD_2(void)

{
  astruct_14 *paVar1;
  BOOL BVar2;
  int iVar3;
  uint uVar4;
  WeaponProjectilesContext *unaff_EBP;
  int unaff_EDI;
  
  BVar2 = FUN_00028d20(unaff_EBP);
  if (BVar2 == 0) {
    iVar3 = FUN_0002b630();
    if (iVar3 != 0) {
      FUN_0008f650();
      return;
    }
  }
  else if (TransitionData.discReadEnum == 2) {
    iVar3 = FUN_000f2b30();
    if ((((iVar3 != 0) && (DAT_00430d9c <= (int)Game::DeathsInCurrentRoom)) &&
        (uVar4 = Assets::GetChapterIndexFromAID(Game::GameState.currentSceneScript),
        paVar1 = PTR_00506c6c, (int)uVar4 < 8)) && (INT_004e17c8 != 3)) {
      *(undefined4 *)(unaff_EDI + 0x18) = 4;
      if ((paVar1->field2_0x8[4] & 2) != 0) {
        return;
      }
      if (INT_004e17c8 == 3) {
        return;
      }
      FUN_000f29d0();
      Events::BeginDialogSequence(0);
      return;
    }
    FUN_0008f650();
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void entityStateHit::getAllocDetails(undefined4 *param_1)

{
  *param_1 = 0x30;
  param_1[1] = 0x14;
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void entityStateFly::getAllocDetails(undefined4 *param_1)

{
  *param_1 = 0x78;
  param_1[1] = 0xa8;
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void entityStateFly::update(entityStateFly *param_1)

{
  actor *act;
  float fVar1;
  float fVar2;
  float fVar3;
  
  fVar2 = 0.0;
  act = (actor *)(param_1->state).body;
  fVar1 = (act->avatar).pos.x;
  if (runtime::dx_timer <= 0.0) {
    fVar3 = runtime::DeltaTime * runtime::TimeScale;
  }
  else {
    fVar3 = 0.0;
  }
  if (*(float *)((int)fVar1 + 0x930) <= 0.0) {
    fVar2 = *(float *)((int)fVar1 + 0x92c);
  }
  (param_1->state).t = fVar2 * fVar3 + (param_1->state).t;
  FUN_00091210(param_1);
  updateMovement(param_1,act);
  FUN_000916c0(param_1);
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void entityStateFly::updateMovement(entityStateFly *fly,actor *act)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  uint uVar5;
  uint uVar6;
  actorBody *extraout_EDX;
  float10 fVar7;
  float10 fVar8;
  
  fVar4 = (act->avatar).pos.x;
  fVar1 = (act->avatar).smoothedCurrentPos.x;
  fVar2 = *(float *)((int)fVar4 + 0x3c);
  fVar4 = *(float *)((int)fVar4 + 0x44);
  fVar3 = (act->avatar).smoothedCurrentPos.z;
  fVar7 = scaled_invsqrt(fVar2 * fVar2 + fVar4 * fVar4);
  fVar8 = scaled_invsqrt(fVar3 * fVar3 + fVar1 * fVar1);
  uVar5 = FUN_000a5fd0((entityStateWalk *)fly,(float)fVar8,(actorBody *)act);
  uVar6 = FUN_000a5fd0((entityStateWalk *)fly,(float)fVar7,extraout_EDX);
  if ((uVar6 == uVar5) && (uVar5 != fly->field23_0x2e)) {
    *(undefined4 *)((int)(act->avatar).pos.x + 0x84) = 1;
    FUN_0001afa0(*(undefined4 *)(&fly->field_0x30 + uVar5 * 0x10),act);
    fly->field23_0x2e = (ushort)uVar5;
  }
  FUN_00091480((float)fVar7);
  return;
}




void entityStateGenerateGhouly::getAllocDetails(undefined4 *param_1)

{
  *param_1 = 0x4a0;
  param_1[1] = 0x318;
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


undefined ** entityStateGenerateGhouly::getVTable(void)

{
  vtable[5] = switchD_000d4179::EmptyFunction;
  vtable[7] = actorState::func7;
  vtable[0] = getAllocDetails;
  vtable[1] = ctor;
  vtable[2] = dtor;
  vtable[3] = onMessage;
  vtable[4] = update;
  vtable[6] = func6;
  return vtable;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields

undefined4
entityStateGenerateGhouly::ctor
          (entityStateGenerateGhouly *param_1,entityStateGenerateGhoulyParams *param_2)

{
  undefined1 *puVar1;
  char cVar2;
  actorBody *paVar3;
  actor *act;
  actor *paVar4;
  int iVar5;
  AnimEventMapping *pAVar6;
  char *pcVar7;
  BOOL BVar8;
  char *pcVar9;
  
  pcVar7 = param_2->field1_0xc;
  paVar3 = (param_1->actorState).body;
  act = paVar3->actor;
  if (((paVar3->weapon == (weapon *)0x0) ||
      (pcVar9 = &paVar3->weapon->field1062_0xdb0, pcVar9 == (char *)0x0)) || (*pcVar9 == '\0')) {
    pcVar9 = (char *)0x0;
  }
  pAVar6 = avatar::getAnimEventByName(&act->avatar,pcVar7,(BOOL)pcVar9);
  if ((pAVar6 == (AnimEventMapping *)0x0) && (pcVar9 != (char *)0x0)) {
    pAVar6 = avatar::getAnimEventByName(&act->avatar,pcVar7,0);
  }
  *(AnimEventMapping **)&param_1->field_0x20 = pAVar6;
  pcVar7 = *(char **)&param_2->field_0x10;
  if (((paVar3->weapon == (weapon *)0x0) ||
      (pcVar9 = &paVar3->weapon->field1062_0xdb0, pcVar9 == (char *)0x0)) || (*pcVar9 == '\0')) {
    pcVar9 = (char *)0x0;
  }
  paVar4 = paVar3->actor;
  pAVar6 = avatar::getAnimEventByName(&paVar4->avatar,pcVar7,(BOOL)pcVar9);
  if ((pAVar6 == (AnimEventMapping *)0x0) && (pcVar9 != (char *)0x0)) {
    pAVar6 = avatar::getAnimEventByName(&paVar4->avatar,pcVar7,0);
  }
  *(AnimEventMapping **)&param_1->field_0x24 = pAVar6;
  pcVar7 = *(char **)&param_2->field_0x14;
  if (((paVar3->weapon == (weapon *)0x0) ||
      (pcVar9 = &paVar3->weapon->field1062_0xdb0, pcVar9 == (char *)0x0)) || (*pcVar9 == '\0')) {
    pcVar9 = (char *)0x0;
  }
  paVar4 = paVar3->actor;
  pAVar6 = avatar::getAnimEventByName(&paVar4->avatar,pcVar7,(BOOL)pcVar9);
  if ((pAVar6 == (AnimEventMapping *)0x0) && (pcVar9 != (char *)0x0)) {
    pAVar6 = avatar::getAnimEventByName(&paVar4->avatar,pcVar7,0);
  }
  puVar1 = &param_1->field_0xac;
  *(AnimEventMapping **)&param_1->field_0x28 = pAVar6;
  pcVar7 = puVar1;
  do {
    cVar2 = pcVar7[(int)param_2 + (0x98 - (int)puVar1)];
    *pcVar7 = cVar2;
    pcVar7 = pcVar7 + 1;
  } while (cVar2 != '\0');
  pcVar7 = &param_2->field_0x18;
  iVar5 = 0x2c - (int)pcVar7;
  do {
    cVar2 = *pcVar7;
    pcVar7[(int)param_1 + iVar5] = cVar2;
    pcVar7 = pcVar7 + 1;
  } while (cVar2 != '\0');
  BVar8 = FUN_0012a970((astruct_25 *)&(act->avatar).model0x9s[3].field_0xb0);
  if ((BVar8 != 0) && ((act->avatar).model0x9s[4].indexValue != 0xffff)) {
    *puVar1 = 0;
  }
  pcVar7 = &param_2->field_0x118;
  iVar5 = 300 - (int)pcVar7;
  do {
    cVar2 = *pcVar7;
    pcVar7[(int)param_1 + iVar5] = cVar2;
    pcVar7 = pcVar7 + 1;
  } while (cVar2 != '\0');
  pcVar7 = &param_2->field_0x198;
  iVar5 = 0x1ac - (int)pcVar7;
  do {
    cVar2 = *pcVar7;
    pcVar7[(int)param_1 + iVar5] = cVar2;
    pcVar7 = pcVar7 + 1;
  } while (cVar2 != '\0');
  pcVar7 = &param_2->field_0x218;
  iVar5 = 0x22c - (int)pcVar7;
  do {
    cVar2 = *pcVar7;
    pcVar7[(int)param_1 + iVar5] = cVar2;
    pcVar7 = pcVar7 + 1;
  } while (cVar2 != '\0');
  pcVar7 = &param_2->field_0x298;
  iVar5 = 0x2ac - (int)pcVar7;
  do {
    cVar2 = *pcVar7;
    pcVar7[(int)param_1 + iVar5] = cVar2;
    pcVar7 = pcVar7 + 1;
  } while (cVar2 != '\0');
  paVar3->field13_0x30 = paVar3->field13_0x30 + 1;
  paVar3->field_0x30b = paVar3->field_0x30b + '\x01';
  paVar3->field_0x309 = paVar3->field_0x309 + '\x01';
  paVar3->field_0x30a = paVar3->field_0x30a + '\x01';
  paVar3->field_0x30c = paVar3->field_0x30c + '\x01';
  paVar3->farRangeThreshold = true;
  paVar3->someHitFlag = true;
  *(short *)&act->field_0xb9e = *(short *)&act->field_0xb9e + 1;
  param_1->field_0x494 = 0xff;
  FUN_00093800();
  FUN_000925c0(param_1);
  FUN_00093190();
  FUN_000941a0();
  return 1;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void entityStateGenerateGhouly::dtor(entityStateGenerateGhouly *param_1)

{
  undefined1 *puVar1;
  actorBody *paVar2;
  astruct_23 *paVar3;
  
  paVar2 = (param_1->actorState).body;
  if (*(int *)&param_1->field_0x18 == 2) {
    for (paVar3 = (paVar2->actor->avatar).as23ptr; paVar3 != (astruct_23 *)0x0;
        paVar3 = *(astruct_23 **)&paVar3->field_0x4) {
      paVar3->field_0x15 = paVar3->field_0x15 + -1;
    }
    paVar2->field_0x6d = paVar2->field_0x6d + -1;
    paVar2->field_0x7e5 = paVar2->field_0x7e5 + -1;
  }
  *(undefined4 *)&param_1->field_0x18 = 0;
  FUN_00092790(param_1);
  FUN_000936a0();
  if ((*(void **)&param_1->field_0x454 != (void *)0x0) && (*(int *)&param_1->field_0x45c == 0)) {
    Assets::DeleteResource_(*(void **)&param_1->field_0x454);
    if (*(void **)&param_1->field_0x458 != (void *)0x0) {
      Assets::DeleteResource_(*(void **)&param_1->field_0x458);
    }
  }
  *(undefined4 *)&param_1->field_0x454 = 0;
  *(undefined4 *)&param_1->field_0x458 = 0;
  paVar2->field13_0x30 = paVar2->field13_0x30 - 1;
  paVar2->field_0x309 = paVar2->field_0x309 + -1;
  paVar2->field_0x30a = paVar2->field_0x30a + -1;
  paVar2->field_0x30b = paVar2->field_0x30b + -1;
  paVar2->field_0x30c = paVar2->field_0x30c + -1;
  puVar1 = &paVar2->actor->field_0xb9e;
  *(short *)puVar1 = *(short *)puVar1 + -1;
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void entityStateGenerateGhouly::update(entityStateGenerateGhouly *param_1)

{
  actorBody *paVar1;
  actor *paVar2;
  int iVar3;
  astruct_23 *paVar4;
  actorBodyStateId aVar5;
  BOOL BVar6;
  float fVar7;
  float fVar8;
  vec3 local_c;
  
  paVar1 = (param_1->actorState).body;
  paVar2 = paVar1->actor;
  if (runtime::dx_timer <= 0.0) {
    fVar8 = runtime::DeltaTime * runtime::TimeScale;
  }
  else {
    fVar8 = 0.0;
  }
  fVar7 = 0.0;
  if ((paVar2->avatar).movementFreezeTimer <= 0.0) {
    fVar7 = (paVar2->avatar).actionSpeed;
  }
  (param_1->actorState).t = fVar7 * fVar8 + (param_1->actorState).t;
  (paVar1->rotation).z = 0.0;
  (paVar1->rotation).x = 0.0;
  iVar3 = *(int *)&param_1->field_0x18;
  if (iVar3 == 1) {
    *(undefined4 *)&param_1->field_0x498 = 0;
    FUN_00093800();
    FUN_00093ad0();
    FUN_00092840(param_1,1);
    local_c.x = *(float *)&param_1->field_0x480;
    local_c.y = *(float *)&param_1->field_0x484;
    local_c.z = *(float *)&param_1->field_0x488;
    actorBody::turnToFacePoint(paVar1,&local_c);
    BVar6 = avatar::updateKeyframes(&paVar2->avatar,0);
    if (BVar6 != 0) {
      FUN_00093700();
      FUN_000941a0();
    }
  }
  else if (iVar3 == 2) {
    paVar2 = ((param_1->actorState).body)->actor;
    if (runtime::dx_timer <= 0.0) {
      fVar8 = runtime::DeltaTime * runtime::TimeScale;
    }
    else {
      fVar8 = 0.0;
    }
    fVar7 = 0.0;
    if ((paVar2->avatar).movementFreezeTimer <= 0.0) {
      fVar7 = (paVar2->avatar).actionSpeed;
    }
    if ((0.0 < *(float *)&param_1->field_0x1c) &&
       (fVar8 = *(float *)&param_1->field_0x1c - fVar7 * fVar8,
       *(float *)&param_1->field_0x1c = fVar8, fVar8 <= 0.0)) {
      *(undefined4 *)&param_1->field_0x1c = 0;
    }
    *(undefined4 *)&param_1->field_0x498 = 1;
    FUN_00093800();
    FUN_00093ad0();
    FUN_00092840(param_1,0);
    if ((*(int *)&param_1->field_0x45c != 0) && (*(int *)&param_1->field_0x454 != 0)) {
      FUN_00093540();
    }
    local_c.x = *(float *)&param_1->field_0x480;
    local_c.y = *(float *)&param_1->field_0x484;
    local_c.z = *(float *)&param_1->field_0x488;
    actorBody::turnToFacePoint(paVar1,&local_c);
    if (*(float *)&param_1->field_0x1c == 0.0) {
      paVar1 = (param_1->actorState).body;
      if (*(int *)&param_1->field_0x18 == 2) {
        for (paVar4 = (paVar1->actor->avatar).as23ptr; paVar4 != (astruct_23 *)0x0;
            paVar4 = *(astruct_23 **)&paVar4->field_0x4) {
          paVar4->field_0x15 = paVar4->field_0x15 + -1;
        }
        paVar1->field_0x6d = paVar1->field_0x6d + -1;
        paVar1->field_0x7e5 = paVar1->field_0x7e5 + -1;
      }
      *(undefined4 *)&param_1->field_0x18 = 3;
      *(undefined4 *)&param_1->field_0x344 = 0;
      FUN_00093780();
      FUN_00093660();
      FUN_0001afa0(*(undefined4 *)&param_1->field_0x28,paVar1);
      return;
    }
  }
  else if ((iVar3 == 3) && (BVar6 = avatar::updateKeyframes(&paVar2->avatar,0), BVar6 != 0)) {
    aVar5 = (*paVar1->vtable->getStandingState)(paVar1);
    (param_1->actorState).func6ret = aVar5;
    return;
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void entityStateGenerateGhouly::func6(entityStateGenerateGhouly *param_1,int param_2)

{
  if ((param_2 == 2) && (*(int *)&param_1->field_0x344 != 0)) {
    FUN_00092d10(param_1);
  }
  return;
}




void entityStateGenerateGhouly::onMessage(int param_1,int *param_2)

{
  int iVar1;
  
  if (*param_2 == 0x7c) {
    iVar1 = param_2[1];
    if (*(int *)(param_1 + 0x454) == iVar1) {
      *(undefined4 *)(param_1 + 0x454) = 0;
      *(undefined4 *)(param_1 + 0x45c) = 0;
      *(undefined4 *)(param_1 + 0x460) = 0;
    }
    if (*(int *)(param_1 + 0x458) == iVar1) {
      *(undefined4 *)(param_1 + 0x458) = 0;
    }
    if (*(int *)(param_1 + 0x47c) == iVar1) {
      *(undefined4 *)(param_1 + 0x47c) = 0;
    }
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void entityStateGrabAndThrow::update(actorState *param_1)

{
  actorStateVTable *paVar1;
  actor *act;
  KeyframeContext *pKVar2;
  AnimInstance *pAVar3;
  actorState *paVar4;
  actorBodyStateId aVar5;
  int iVar6;
  actorBody *body;
  actorBody *target;
  bool bVar7;
  float fVar8;
  ObjMsgID OVar9;
  float fVar10;
  float fVar11;
  undefined4 uStack_38;
  actorBody *local_34;
  vec3 local_30;
  vec3 local_24;
  Message local_18;
  
  paVar4 = param_1;
  body = param_1->body;
  act = body->actor;
  if (act->mind == (actorMind *)0x0) {
    target = (actorBody *)0x0;
  }
  else {
    target = act->mind->targetBody;
  }
  fVar11 = 0.0;
  if (runtime::dx_timer <= 0.0) {
    fVar10 = runtime::DeltaTime * runtime::TimeScale;
  }
  else {
    fVar10 = 0.0;
  }
  fVar8 = 0.0;
  if ((body->actor->avatar).movementFreezeTimer <= 0.0) {
    fVar8 = (body->actor->avatar).actionSpeed;
  }
  param_1->t = fVar8 * fVar10 + param_1->t;
  (body->rotation).z = 0.0;
  (body->rotation).x = 0.0;
  local_34 = body;
  if (param_1[3].body != (actorBody *)0x0) goto LAB_00094eac;
  if ((*(int *)&param_1[3].field_0x4 == 0) && (target != (actorBody *)0x0)) {
    local_30.x = (target->worldPosition).z;
    local_30.y = (target->worldPos).x;
    local_30.z = (target->worldPos).y;
    iVar6 = FUN_0012c970(&local_30,1,0,0,0);
    if (iVar6 == 0) {
      param_1[3].t = 1.4013e-45;
    }
    else {
      pKVar2 = (act->avatar).keyframeContext;
      if (pKVar2 == (KeyframeContext *)0x0) {
        param_1 = (actorState *)0x0;
LAB_00094c1f:
        FUN_001345f0(body,target);
      }
      else {
        pAVar3 = pKVar2->kfcAnims->animInstance;
        if (pAVar3 == (AnimInstance *)0x0) {
          param_1 = (actorState *)0x0;
        }
        else {
          param_1 = (actorState *)pAVar3->t;
        }
        if ((float)param_1 <= 0.25) goto LAB_00094c1f;
      }
      if (((0.15 <= (float)param_1) && ((float)param_1 <= 0.25)) &&
         (iVar6 = FUN_00095000(paVar4,&local_30), iVar6 != 0)) {
        local_18.header.someActor = (actor *)0x0;
        local_18.header.msgId = Actor_Grabbed;
        (*((target->currentWeapon->avatar).vtable)->onMessage)(target->currentWeapon,&local_18);
        if (local_18.header.someActor != (actor *)0x0) {
          uStack_38 = 0x3d;
          (*((target->currentWeapon->avatar).vtable)->onMessage)(target->currentWeapon,&uStack_38);
          FUN_0013ad60(target->currentWeapon,paVar4[1].vtable,&local_30);
          *(undefined4 *)&paVar4[3].field_0x4 = 1;
          avatar::getWorldRotation(&act->avatar,(vec3 *)&paVar4[2].func6ret);
          paVar4[3].vtable = (actorStateVTable *)param_1;
          actorBody::resetFlags(body);
          *(undefined4 *)&paVar4[3].func6ret = 1;
        }
      }
    }
  }
  fVar11 = 0.0;
  if (((paVar4[3].body == (actorBody *)0x0) && (*(int *)&paVar4[3].field_0x4 != 0)) &&
     (*(int *)&paVar4[1].func6ret != 0)) {
    if (*(short *)&paVar4[1].t != 0) {
      avatar::getWorldPosition(&act->avatar,&local_24);
      Marker::GetPosByIndex(*(undefined2 *)&paVar4[1].t,&local_30);
      local_18.header.msgId = (ObjMsgID)(local_30.x - local_24.x);
      local_18.header.someActor = (actor *)(local_30.y - local_24.y);
      vec3::getTurnAngle((vec3 *)&local_18,&local_24.y);
      pKVar2 = (act->avatar).keyframeContext;
      if ((pKVar2 == (KeyframeContext *)0x0) ||
         (pAVar3 = pKVar2->kfcAnims->animInstance, pAVar3 == (AnimInstance *)0x0)) {
        fVar11 = 0.0;
      }
      else {
        fVar11 = pAVar3->t;
      }
      paVar1 = paVar4[3].vtable;
      if ((float)paVar1 == 0.55) {
        param_1 = (actorState *)1.0;
      }
      else {
        param_1 = (actorState *)((fVar11 - (float)paVar1) / (0.55 - (float)paVar1));
        if ((float)param_1 <= 1.0) {
          if ((float)param_1 < 0.0) {
            param_1 = (actorState *)0x0;
          }
        }
        else {
          param_1 = (actorState *)1.0;
        }
      }
      avatar::getWorldRotation(&act->avatar,(vec3 *)&local_18);
      OVar9 = Null;
      FUN_001013a0(*(undefined4 *)&paVar4[2].func6ret,param_1);
      local_18.header.msgId = OVar9;
      FUN_001013a0(paVar4[2].t,param_1);
      local_18.header.someActor = (actor *)local_24.y;
      FUN_001013a0(paVar4[2].field9_0x14,param_1);
      ::actor::setRotation(act,(vec3 *)&local_18);
      body = local_34;
    }
    fVar11 = 0.0;
    iVar6 = CheckAnimKfcThreshold((void *)0x0,act,0.55);
    if (iVar6 != 0) {
      FUN_000951b0(paVar4,act);
      fVar11 = 0.0;
      paVar4[3].body = (actorBody *)0x1;
    }
  }
LAB_00094eac:
  if (((paVar4[3].t == 0.0) &&
      (pKVar2 = (act->avatar).keyframeContext, pKVar2 != (KeyframeContext *)0x0)) &&
     (pAVar3 = pKVar2->kfcAnims->animInstance, pAVar3 != (AnimInstance *)0x0)) {
    bVar7 = false;
    if (pAVar3->loopMode == Mode1) {
      if (pAVar3->invDuration <= fVar11 && fVar11 != pAVar3->invDuration) {
        bVar7 = fVar11 < pAVar3->t;
      }
      else {
        bVar7 = pAVar3->t < 1.0;
      }
      if (bVar7) {
        bVar7 = false;
      }
      else {
        bVar7 = true;
      }
    }
    if (!bVar7) {
      return;
    }
  }
  aVar5 = (*body->vtable->getStandingState)(body);
  paVar4->func6ret = aVar5;
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void actorState::getAllocDetails(ObjectAllocDetails *param_1)

{
  param_1->entitySize = 0x18;
  param_1->paramsSize = 0xc;
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void actorState::update(actorState *this)

{
  float value;
  float delta;
  actor *actor;
  
  value = 0.0;
  actor = this->body->actor;
  if (runtime::dx_timer <= 0.0) {
    delta = runtime::DeltaTime * runtime::TimeScale;
  }
  else {
    delta = 0.0;
  }
  if ((actor->avatar).movementFreezeTimer <= 0.0) {
    value = (actor->avatar).actionSpeed;
  }
  this->t = value * delta + this->t;
  return;
}




undefined4 entityStateGroundAttack::ctor(actorState *state,int param_2)

{
  actorBody *paVar1;
  actor *this;
  actorBody *paVar2;
  
  paVar1 = state->body;
  this = paVar1->actor;
  paVar1->farRangeThreshold = true;
  paVar1->someHitFlag = true;
  paVar1->backedUpAirResistance = paVar1->airResistance;
  paVar1->airResistance = 7.0;
  paVar1->numStatesDeep = paVar1->numStatesDeep + 1;
  paVar1->field_0x6a = paVar1->field_0x6a + '\x01';
  if (((this->mind != (actorMind *)0x0) &&
      (paVar2 = this->mind->currentAttackTarget, paVar2 != (actorBody *)0x0)) &&
     (*(char *)&paVar2->largeProjectile == '\0')) {
    *(weapon **)&(this->avatar).field_0x11c = paVar2->currentWeapon;
  }
  avatar::getWorldRotation(&this->avatar,(vec3 *)&state[2].body);
  state[3].vtable = *(actorStateVTable **)(param_2 + 0xc);
  paVar1->field_0x309 = paVar1->field_0x309 + '\x01';
  paVar1->field_0x30a = paVar1->field_0x30a + '\x01';
  paVar1->field_0x30b = paVar1->field_0x30b + '\x01';
  paVar1->field_0x30c = paVar1->field_0x30c + '\x01';
  state[2].field9_0x14 = (float)paVar1->weapon;
  *(undefined4 *)&state[2].field_0x4 = *(undefined4 *)(param_2 + 0x10);
  *(undefined4 *)&state[3].func6ret = *(undefined4 *)(param_2 + 0x14);
  state[3].t = *(float *)(param_2 + 0x18);
  *(undefined2 *)&state[4].field_0x4 = *(undefined2 *)(param_2 + 0x1c);
  state[4].body = *(actorBody **)(param_2 + 0x20);
  *(undefined4 *)&state[4].func6ret = *(undefined4 *)(param_2 + 0x24);
  *(undefined4 *)&state[3].field_0x4 = 0;
  state[3].body = (actorBody *)0x0;
  state[3].field9_0x14 = (float)(uint)(paVar1->weapon != (weapon *)0x0);
  return 1;
}




actorStateVTable * entityStateHit::getVTable(void)

{
  vtable.func5 = switchD_000d4179::EmptyFunction;
  vtable.func6 = switchD_000d4179::EmptyFunction;
  vtable.func7 = actorState::func7;
  vtable.getAllocDetails = getAllocDetails;
  vtable.ctor = ctor;
  vtable.dtor = dtor;
  vtable.onMessage = switchD_000d4179::EmptyFunction;
  vtable.update = update;
  return &vtable;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void entityStateHit::ctor(entityStateHit *param_1,entityStateHitParams *param_2)

{
  actorBodyFlags *paVar1;
  actorBody *body;
  
  body = (param_1->field0_0x0).body;
  *(undefined4 *)&param_1->field_0x20 = 0;
  param_1->someu16 = param_2->field2_0xc;
  *(undefined4 *)&param_1->field_0x1c = *(undefined4 *)&param_2->field_0x10;
  body->field_0x6b = body->field_0x6b + '\x01';
  body->field_0x309 = body->field_0x309 + '\x01';
  body->field_0x30a = body->field_0x30a + '\x01';
  body->field_0x30b = body->field_0x30b + '\x01';
  body->field_0x30c = body->field_0x30c + '\x01';
  body->field13_0x30 = body->field13_0x30 + 1;
  body->backedUpAirResistance = body->airResistance;
  body->numStatesDeep = body->numStatesDeep + 1;
  body->airResistance = 7.0;
  body->farRangeThreshold = true;
  body->someHitFlag = true;
  paVar1 = body->flagSet->flags;
  *(byte *)((int)&paVar1->flag1 + 2) = *(byte *)((int)&paVar1->flag1 + 2) | 2;
  if (*(int *)&param_1->field_0x1c != 0) {
    paVar1 = body->flagSet->flags;
    *(byte *)((int)&paVar1->attackFlags_ + 3) = *(byte *)((int)&paVar1->attackFlags_ + 3) | 1;
  }
  if (body->someHealthValue != '\0') {
    body->damageScale = 2.0;
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void entityStateHit::dtor(entityStateHit *param_1)

{
  actorBody *paVar1;
  actorBodyFlags *paVar2;
  
  paVar1 = (param_1->field0_0x0).body;
  paVar1->field13_0x30 = paVar1->field13_0x30 - 1;
  paVar1->numStatesDeep = paVar1->numStatesDeep - 1;
  paVar1->airResistance = paVar1->backedUpAirResistance;
  paVar1->field_0x6b = paVar1->field_0x6b + -1;
  paVar1->field_0x309 = paVar1->field_0x309 + -1;
  paVar1->field_0x30a = paVar1->field_0x30a + -1;
  paVar1->field_0x30c = paVar1->field_0x30c + -1;
  paVar1->field_0x30b = paVar1->field_0x30b + -1;
  paVar2 = paVar1->flagSet->flags;
  *(byte *)((int)&paVar2->flag1 + 2) = *(byte *)((int)&paVar2->flag1 + 2) & 0xfd;
  if (*(int *)&param_1->field_0x1c != 0) {
    paVar2 = paVar1->flagSet->flags;
    *(byte *)((int)&paVar2->attackFlags_ + 3) = *(byte *)((int)&paVar2->attackFlags_ + 3) & 0xfe;
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void entityStateHit::update(actorState *param_1,InputHandlerType1 *param_2)

{
  actorBody *paVar1;
  actor *paVar2;
  KeyframeContext *pKVar3;
  AnimInstance *pAVar4;
  actor *paVar5;
  bool bVar6;
  actorState *paVar7;
  bool bVar8;
  float fVar9;
  float fVar10;
  vec2 local_8;
  
  paVar7 = param_1;
  paVar1 = param_1->body;
  paVar2 = paVar1->actor;
  if (runtime::dx_timer <= 0.0) {
    fVar10 = runtime::DeltaTime * runtime::TimeScale;
  }
  else {
    fVar10 = 0.0;
  }
  fVar9 = 0.0;
  if ((paVar2->avatar).movementFreezeTimer <= 0.0) {
    fVar9 = (paVar2->avatar).actionSpeed;
  }
  param_1->t = fVar9 * fVar10 + param_1->t;
  if ((paVar1->hitReactionRes != (HitReactionResource *)0x0) &&
     (1.0 < paVar1->hitReactionRes->field13_0x19c)) {
    FUN_000965c0(param_1);
  }
  (paVar1->rotation).z = 0.0;
  (paVar1->rotation).x = 0.0;
  pKVar3 = (paVar2->avatar).keyframeContext;
  if (pKVar3 == (KeyframeContext *)0x0) {
    param_1 = (actorState *)0x0;
  }
  else {
    pAVar4 = pKVar3->kfcAnims->animInstance;
    if (pAVar4 == (AnimInstance *)0x0) {
      param_1 = (actorState *)0x0;
    }
    else {
      param_1 = (actorState *)pAVar4->t;
    }
  }
  paVar5 = paVar1->actor;
  if ((*(int *)&paVar5->field_0xce0 == 0) ||
     ((((paVar5->actorType != Human && ((paVar5->node0x93c).prev == (actor_0x93c)0x0)) ||
       (Input::GetLSMovement_(param_2,&local_8),
       local_8.y * local_8.y + local_8.x * local_8.x <= 0.010000001)) || ((float)param_1 <= 0.45))))
  {
    bVar6 = false;
  }
  else {
    bVar6 = true;
  }
  pKVar3 = (paVar2->avatar).keyframeContext;
  if ((pKVar3 != (KeyframeContext *)0x0) &&
     (pAVar4 = pKVar3->kfcAnims->animInstance, pAVar4 != (AnimInstance *)0x0)) {
    bVar8 = false;
    if (pAVar4->loopMode == Mode1) {
      if (pAVar4->invDuration <= 0.0 && pAVar4->invDuration != 0.0) {
        bVar8 = 0.0 < pAVar4->t;
      }
      else {
        bVar8 = pAVar4->t < 1.0;
      }
      if (bVar8) {
        bVar8 = false;
      }
      else {
        bVar8 = true;
      }
    }
    if ((!bVar8) && (!bVar6)) {
      return;
    }
  }
  FUN_00133f50(paVar7,*(undefined2 *)&paVar7[1].vtable);
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void entityStateJumpOnOff::getAllocDetails(undefined4 *param_1)

{
  *param_1 = 0x158;
  param_1[1] = 0xb0;
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void entityStatePickup::getAllocDetails(undefined4 *param_1)

{
  *param_1 = 0x2c;
  param_1[1] = 0x10;
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


undefined ** entityStatePickup::getVTable(void)

{
  PTR_ARRAY_00505a60[5] = switchD_000d4179::EmptyFunction;
  PTR_ARRAY_00505a60[6] = switchD_000d4179::EmptyFunction;
  PTR_ARRAY_00505a60[7] = actorState::func7;
  PTR_ARRAY_00505a60[0] = getAllocDetails;
  PTR_ARRAY_00505a60[1] = ctor;
  PTR_ARRAY_00505a60[2] = dtor;
  PTR_ARRAY_00505a60[3] = switchD_000d4179::EmptyFunction;
  PTR_ARRAY_00505a60[4] = updateFixed_;
  return PTR_ARRAY_00505a60;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


undefined4 entityStatePickup::ctor(entityStatePickup *param_1,int param_2)

{
  actorBody *paVar1;
  actorBodyFlags *paVar2;
  actor *av;
  astruct_23 *paVar3;
  
  paVar1 = (param_1->state).body;
  paVar1->farRangeThreshold = true;
  paVar1->someHitFlag = true;
  paVar2 = paVar1->flagSet->flags;
  av = paVar1->actor;
  *(byte *)((int)&paVar2->attackFlags_ + 1) = *(byte *)((int)&paVar2->attackFlags_ + 1) | 4;
  for (paVar3 = (paVar1->actor->avatar).as23ptr; paVar3 != (astruct_23 *)0x0;
      paVar3 = *(astruct_23 **)&paVar3->field_0x4) {
    paVar3->field_0x15 = paVar3->field_0x15 + '\x01';
  }
  paVar1->field_0x6d = paVar1->field_0x6d + '\x01';
  paVar1->field_0x309 = paVar1->field_0x309 + '\x01';
  paVar1->field_0x30a = paVar1->field_0x30a + '\x01';
  paVar1->field_0x30b = paVar1->field_0x30b + '\x01';
  paVar1->field_0x30c = paVar1->field_0x30c + '\x01';
  avatar::getWorldPosition(&av->avatar,(vec3 *)&param_1->field2_0x1c);
  param_1->field1_0x18 = 0;
  param_1->field8_0x28 = *(float *)(param_2 + 0xc);
  return 1;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void entityStatePickup::dtor(int param_1)

{
  int iVar1;
  int iVar2;
  MessageHeader local_14;
  ObjMsgID local_c;
  undefined4 local_8;
  int local_4;
  
  iVar1 = *(int *)(param_1 + 8);
  iVar2 = *(int *)(*(int *)(iVar1 + 0x15c) + 8);
  *(byte *)(iVar2 + 5) = *(byte *)(iVar2 + 5) & 0xfb;
  *(char *)(iVar1 + 0x309) = *(char *)(iVar1 + 0x309) + -1;
  *(char *)(iVar1 + 0x30a) = *(char *)(iVar1 + 0x30a) + -1;
  *(char *)(iVar1 + 0x30b) = *(char *)(iVar1 + 0x30b) + -1;
  *(char *)(iVar1 + 0x30c) = *(char *)(iVar1 + 0x30c) + -1;
  for (iVar2 = *(int *)(*(int *)(iVar1 + 8) + 0x8f8); iVar2 != 0; iVar2 = *(int *)(iVar2 + 4)) {
    *(char *)(iVar2 + 0x15) = *(char *)(iVar2 + 0x15) + -1;
  }
  *(char *)(iVar1 + 0x6d) = *(char *)(iVar1 + 0x6d) + -1;
  iVar2 = *(int *)(iVar1 + 0x48);
  if (iVar2 != 0) {
    local_8 = *(undefined4 *)(iVar1 + 8);
    local_c = Scene_ActorPickedUpWeapon;
    local_4 = iVar2;
    EventLoop::DispatchMessage(&local_c);
    *(short *)(iVar2 + 0xae4) = *(short *)(iVar2 + 0xae4) + -1;
    if ((*(short *)(*(int *)(iVar1 + 8) + 0xcdc) == 2) ||
       (*(int *)(*(int *)(iVar1 + 8) + 0x93c) != 0)) {
      local_14.msgId = Player_PickedUpObject;
      local_14.someActor = (actor *)(uint)*(ushort *)(iVar2 + 6);
      EventLoop::NewMessage(&local_14);
    }
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void entityStatePickup::updateFixed_(entityStatePickup *pickup)

{
  CalloutDescriptor **ppCVar1;
  KeyframeContext *pKVar2;
  AnimInstance *pAVar3;
  bool bVar4;
  actorBodyStateId aVar5;
  int iVar6;
  actor_0x944 *ppNVar7;
  int iVar8;
  Mind51 *mind51;
  bool bVar9;
  float fVar10;
  float fVar11;
  float fVar12;
  float fVar13;
  InputHandlerType1 *in_stack_00000008;
  float local_14;
  actorBody *local_10;
  actorMind *mind;
  float fStack_8;
  actor *local_4;
  actorBody *body;
  actor *act;
  
  body = (pickup->state).body;
  act = body->actor;
  mind = act->mind;
  if (mind == (actorMind *)0x0) {
    mind51 = (Mind51 *)0x0;
  }
  else {
    mind51 = mind->mind51;
  }
  fVar12 = 0.0;
  if (runtime::dx_timer <= 0.0) {
    fVar13 = runtime::DeltaTime * runtime::TimeScale;
  }
  else {
    fVar13 = 0.0;
  }
  fVar10 = 0.0;
  if ((body->actor->avatar).movementFreezeTimer <= 0.0) {
    fVar10 = (body->actor->avatar).actionSpeed;
  }
  (pickup->state).t = fVar10 * fVar13 + (pickup->state).t;
  (body->rotation).z = 0.0;
  (body->rotation).x = 0.0;
  local_10 = body;
  local_4 = act;
  if ((actor *)mind51 == (actor *)0x0) goto LAB_0009e16f;
  iVar8 = (int)*(short *)&(((actor *)mind51)->node0x944).prev;
  iVar6 = 0;
  ppNVar7 = &(((actor *)mind51)->node0x944).next;
  if (0 < iVar8) {
    do {
      if (*(objTag *)ppNVar7 == (act->avatar).tag) {
        local_14 = (float)ppNVar7[3];
        goto LAB_0009e056;
      }
      ppNVar7 = ppNVar7 + 4;
      iVar6 = iVar6 + 1;
    } while (iVar6 < iVar8);
  }
  local_14 = 0.0;
LAB_0009e056:
  if (pickup->field1_0x18 == 0) {
    FUN_0009e2b0(pickup,body,mind51,local_14);
  }
  fVar12 = 0.0;
  pKVar2 = (act->avatar).keyframeContext;
  if ((pKVar2 == (KeyframeContext *)0x0) ||
     (pAVar3 = pKVar2->kfcAnims->animInstance, pAVar3 == (AnimInstance *)0x0)) goto LAB_0009e16f;
  fVar13 = pAVar3->t;
  bVar9 = false;
  if (fVar13 != pAVar3->defaultT) {
    if (pAVar3->invDuration <= 0.0 && pAVar3->invDuration != 0.0) {
      fVar10 = pAVar3->defaultT;
      fVar11 = fVar13;
    }
    else {
      fVar11 = pAVar3->defaultT;
      fVar10 = fVar13;
    }
    if (fVar10 <= fVar11) {
      if ((fVar11 <= local_14) || (local_14 < fVar10)) goto LAB_0009e0ef;
      bVar9 = false;
    }
    else if ((local_14 < fVar11) || (fVar10 <= local_14)) {
      bVar9 = false;
    }
    else {
LAB_0009e0ef:
      bVar9 = true;
    }
  }
  if (bVar9) {
    pickup->field1_0x18 = 1;
    iVar6 = FUN_00146150();
    if (iVar6 != 0) {
      iVar6 = FUN_0001b190(body,0);
      if (iVar6 != 0) {
        *(short *)&((actor *)mind51)->field_0xae4 = *(short *)&((actor *)mind51)->field_0xae4 + 1;
        ppCVar1 = &(((actor *)mind51)->avatar).callout;
        if (ppCVar1 != (CalloutDescriptor **)0x0) {
          ::actor::executeCalloutInDescriptor
                    (*ppCVar1,Pickup,(CalloutCallback *)0x0,0,(actor *)mind51,
                     (entityBodyPlayer_0x924)0x0);
        }
        local_14 = 1.00893e-43;
        (*((act->avatar).vtable)->onMessage)(act,&local_14);
      }
      fVar12 = 0.0;
    }
    if (mind != (actorMind *)0x0) {
      mind->mind51 = (Mind51 *)0x0;
    }
  }
LAB_0009e16f:
  pKVar2 = (act->avatar).keyframeContext;
  if ((pKVar2 != (KeyframeContext *)0x0) &&
     (pAVar3 = pKVar2->kfcAnims->animInstance, pAVar3 != (AnimInstance *)0x0)) {
    fVar12 = pAVar3->t;
  }
  fVar13 = pickup->field8_0x28;
  if ((pickup->field1_0x18 == 0) || (body->weapon != (weapon *)0x0)) {
    bVar9 = false;
  }
  else {
    bVar9 = true;
  }
  Input::GetLSMovement_(in_stack_00000008,(vec2 *)&mind);
  if ((0.010000001 < fStack_8 * fStack_8 + (float)mind * (float)mind) ||
     (ScriptType1::getControllerXY(in_stack_00000008,(vec2 *)&mind),
     0.010000001 < fStack_8 * fStack_8 + (float)mind * (float)mind)) {
    bVar4 = true;
  }
  else {
    bVar4 = false;
  }
  if (((fVar13 <= fVar12) && (pickup->field1_0x18 != 0)) && (bVar4)) {
    aVar5 = (*local_10->vtable->getWalkState)(local_10);
    (pickup->state).func6ret = aVar5;
    return;
  }
  if (((!bVar9) && (pKVar2 = (local_4->avatar).keyframeContext, pKVar2 != (KeyframeContext *)0x0))
     && (pAVar3 = pKVar2->kfcAnims->animInstance, pAVar3 != (AnimInstance *)0x0)) {
    bVar9 = false;
    if (pAVar3->loopMode == Mode1) {
      if (pAVar3->invDuration <= 0.0 && pAVar3->invDuration != 0.0) {
        bVar9 = 0.0 < pAVar3->t;
      }
      else {
        bVar9 = pAVar3->t < 1.0;
      }
      if (bVar9) {
        bVar9 = false;
      }
      else {
        bVar9 = true;
      }
    }
    if (!bVar9) {
      return;
    }
  }
  aVar5 = (*local_10->vtable->getStandingState)(local_10);
  (pickup->state).func6ret = aVar5;
  return;
}


/*
Unable to decompile 'FUN_0009e2b0'
Cause: Exception while decompiling 0009e2b0: process: timeout

*/


// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void entityStateScoop::update(actorState *param_1,InputHandlerType1 *param_2)

{
  actorStateVTable *paVar1;
  actorBody *paVar2;
  actorBody *this;
  actor *paVar3;
  KeyframeContext *pKVar4;
  AnimInstance *pAVar5;
  actorBodyFlags *paVar6;
  actorBodyStateId aVar7;
  int iVar8;
  actorBodyVTable *paVar9;
  Mind51 *pMVar10;
  bool bVar11;
  float fVar12;
  float fVar13;
  float fVar14;
  float fVar15;
  vec2 local_28;
  actor *local_20;
  undefined4 local_1c;
  int local_18;
  actor *local_14;
  float local_10;
  float local_c;
  float local_8;
  float local_4;
  
  this = param_1->body;
  paVar3 = this->actor;
  if (runtime::dx_timer <= 0.0) {
    fVar14 = runtime::DeltaTime * runtime::TimeScale;
  }
  else {
    fVar14 = 0.0;
  }
  fVar12 = 0.0;
  if ((paVar3->avatar).movementFreezeTimer <= 0.0) {
    fVar12 = (paVar3->avatar).actionSpeed;
  }
  param_1->t = fVar12 * fVar14 + param_1->t;
  (this->rotation).z = 0.0;
  (this->rotation).x = 0.0;
  fVar14 = param_1[1].field9_0x14;
  if (fVar14 == 1.4013e-45) {
    if (paVar3->mind == (actorMind *)0x0) {
      pMVar10 = (Mind51 *)0x0;
    }
    else {
      pMVar10 = paVar3->mind->mind51;
    }
  }
  else if ((fVar14 == 2.8026e-45) || (fVar14 != 4.2039e-45)) {
    pMVar10 = (Mind51 *)0x0;
  }
  else {
    pMVar10 = (Mind51 *)param_1[1].t;
  }
  local_20 = paVar3;
  if (fVar14 == 1.4013e-45) {
    FUN_0009ea70(this,pMVar10);
  }
  fVar14 = 0.0;
  pKVar4 = (paVar3->avatar).keyframeContext;
  paVar1 = param_1[1].vtable;
  bVar11 = false;
  if (pKVar4 != (KeyframeContext *)0x0) {
    pAVar5 = pKVar4->kfcAnims->animInstance;
    if ((pAVar5 != (AnimInstance *)0x0) && (fVar12 = pAVar5->t, fVar12 != pAVar5->defaultT)) {
      if (pAVar5->invDuration <= 0.0 && pAVar5->invDuration != 0.0) {
        fVar15 = pAVar5->defaultT;
        fVar13 = fVar12;
      }
      else {
        fVar13 = pAVar5->defaultT;
        fVar15 = fVar12;
      }
      if (fVar15 <= fVar13) {
        if ((fVar13 <= (float)paVar1) || ((float)paVar1 < fVar15)) goto LAB_0009e7c7;
        bVar11 = false;
      }
      else if (((float)paVar1 < fVar13) || (fVar15 <= (float)paVar1)) {
        bVar11 = false;
      }
      else {
LAB_0009e7c7:
        bVar11 = true;
      }
    }
    if ((pKVar4 != (KeyframeContext *)0x0) &&
       (pAVar5 = pKVar4->kfcAnims->animInstance, pAVar5 != (AnimInstance *)0x0)) {
      fVar12 = pAVar5->t;
      goto LAB_0009e7e3;
    }
  }
  fVar12 = 0.0;
LAB_0009e7e3:
  paVar2 = param_1[1].body;
  if (((bVar11) && (param_1[1].field9_0x14 = 2.8026e-45, pMVar10 != (Mind51 *)0x0)) &&
     (iVar8 = FUN_00146150(), iVar8 != 0)) {
    pKVar4 = (paVar3->avatar).keyframeContext;
    local_4 = fVar14;
    if ((pKVar4 != (KeyframeContext *)0x0) &&
       (pAVar5 = pKVar4->kfcAnims->animInstance, pAVar5 != (AnimInstance *)0x0)) {
      local_4 = pAVar5->duration;
    }
    local_18 = 0;
    local_4 = (*(float *)&param_1[1].field_0x4 - (float)param_1[1].vtable) * local_4;
    local_c = (paVar3->avatar).scale.z * *(float *)&param_1[1].func6ret;
    local_1c = 0xa0;
    local_14 = paVar3;
    local_10 = fVar14;
    local_8 = fVar14;
    (**(code **)(*(int *)pMVar10 + 0xc))(pMVar10,&local_1c);
    if (local_18 != 0) {
      param_1[1].t = (float)pMVar10;
      param_1[1].field9_0x14 = 4.2039e-45;
      paVar6 = this->flagSet->flags;
      *(byte *)((int)&paVar6->attackFlags_ + 1) = *(byte *)((int)&paVar6->attackFlags_ + 1) | 0x40;
      local_28.x = 1.00893e-43;
      (*((paVar3->avatar).vtable)->onMessage)(paVar3,&local_28);
    }
  }
  fVar14 = param_1[1].field9_0x14;
  Input::GetLSMovement_(param_2,&local_28);
  if ((0.010000001 < local_28.y * local_28.y + local_28.x * local_28.x) ||
     (ScriptType1::getControllerXY(param_2,&local_28),
     0.010000001 < local_28.y * local_28.y + local_28.x * local_28.x)) {
    bVar11 = true;
  }
  else {
    bVar11 = false;
  }
  if ((fVar12 < (float)paVar2) || (fVar14 != 2.8026e-45)) {
    pKVar4 = (local_20->avatar).keyframeContext;
    if ((pKVar4 != (KeyframeContext *)0x0) &&
       (pAVar5 = pKVar4->kfcAnims->animInstance, pAVar5 != (AnimInstance *)0x0)) {
      bVar11 = false;
      if (pAVar5->loopMode == Mode1) {
        if (pAVar5->invDuration <= 0.0 && pAVar5->invDuration != 0.0) {
          bVar11 = 0.0 < pAVar5->t;
        }
        else {
          bVar11 = pAVar5->t < 1.0;
        }
        if (bVar11) {
          bVar11 = false;
        }
        else {
          bVar11 = true;
        }
      }
      if (!bVar11) {
        return;
      }
    }
    paVar9 = this->vtable;
  }
  else {
    paVar9 = this->vtable;
    if (bVar11) {
      aVar7 = (*paVar9->getWalkState)(this);
      param_1->func6ret = aVar7;
      return;
    }
  }
  aVar7 = (*paVar9->getStandingState)(this);
  param_1->func6ret = aVar7;
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void entityStateShoot::getAllocDetails(undefined4 *param_1)

{
  *param_1 = 0xd0;
  param_1[1] = 0xa4;
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


undefined ** entityStateShoot::getVTable(void)

{
  PTR_ARRAY_00505b00[5] = switchD_000d4179::EmptyFunction;
  PTR_ARRAY_00505b00[6] = switchD_000d4179::EmptyFunction;
  PTR_ARRAY_00505b00[7] = actorState::func7;
  PTR_ARRAY_00505b00[0] = getAllocDetails;
  PTR_ARRAY_00505b00[1] = ctor;
  PTR_ARRAY_00505b00[2] = dtor;
  PTR_ARRAY_00505b00[3] = switchD_000d4179::EmptyFunction;
  PTR_ARRAY_00505b00[4] = updateFixed_;
  return PTR_ARRAY_00505b00;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


undefined4 entityStateShoot::ctor(entityStateShoot *state,entityStateShootParams *param_2)

{
  char cVar1;
  actorBodyFlags *paVar2;
  AnimEventMapping *pAVar3;
  char *pcVar4;
  actorBody *paVar5;
  int iVar6;
  char *pcVar7;
  float fVar8;
  float fVar9;
  undefined4 local_8;
  int local_4;
  actor *act;
  actor *actr;
  actorBody *body;
  weapon *wpn;
  
  pcVar4 = *(char **)&param_2->field_0xc;
  body = (state->actorState).body;
  wpn = body->weapon;
  actr = body->actor;
  if (((wpn == (weapon *)0x0) || (pcVar7 = &wpn->field1062_0xdb0, pcVar7 == (char *)0x0)) ||
     (*pcVar7 == '\0')) {
    pcVar7 = (char *)0x0;
  }
  pAVar3 = avatar::getAnimEventByName(&actr->avatar,pcVar4,(BOOL)pcVar7);
  if ((pAVar3 == (AnimEventMapping *)0x0) && (pcVar7 != (char *)0x0)) {
    pAVar3 = avatar::getAnimEventByName(&actr->avatar,pcVar4,0);
  }
  state->field14_0x28 = (int)pAVar3;
  pcVar4 = *(char **)&param_2->field_0x10;
  if (((body->weapon == (weapon *)0x0) ||
      (pcVar7 = &body->weapon->field1062_0xdb0, pcVar7 == (char *)0x0)) || (*pcVar7 == '\0')) {
    pcVar7 = (char *)0x0;
  }
  act = body->actor;
  pAVar3 = avatar::getAnimEventByName(&act->avatar,pcVar4,(BOOL)pcVar7);
  if ((pAVar3 == (AnimEventMapping *)0x0) && (pcVar7 != (char *)0x0)) {
    pAVar3 = avatar::getAnimEventByName(&act->avatar,pcVar4,0);
  }
  state->field15_0x2c = (int)pAVar3;
  pcVar4 = *(char **)&param_2->field_0x14;
  if (((body->weapon == (weapon *)0x0) ||
      (pcVar7 = &body->weapon->field1062_0xdb0, pcVar7 == (char *)0x0)) || (*pcVar7 == '\0')) {
    pcVar7 = (char *)0x0;
  }
  act = body->actor;
  pAVar3 = avatar::getAnimEventByName(&act->avatar,pcVar4,(BOOL)pcVar7);
  if ((pAVar3 == (AnimEventMapping *)0x0) && (pcVar7 != (char *)0x0)) {
    pAVar3 = avatar::getAnimEventByName(&act->avatar,pcVar4,0);
  }
  state->field16_0x30 = (int)pAVar3;
  pcVar4 = *(char **)&param_2->field_0x18;
  if (((body->weapon == (weapon *)0x0) ||
      (pcVar7 = &body->weapon->field1062_0xdb0, pcVar7 == (char *)0x0)) || (*pcVar7 == '\0')) {
    pcVar7 = (char *)0x0;
  }
  act = body->actor;
  pAVar3 = avatar::getAnimEventByName(&act->avatar,pcVar4,(BOOL)pcVar7);
  if ((pAVar3 == (AnimEventMapping *)0x0) && (pcVar7 != (char *)0x0)) {
    pAVar3 = avatar::getAnimEventByName(&act->avatar,pcVar4,0);
  }
  state->field17_0x34 = (int)pAVar3;
  state->field18_0x38 = *(float *)&param_2->field_0x1c * 0.017453292;
  fVar8 = state->field18_0x38;
  fVar9 = *(float *)&param_2->field_0x20 * 0.017453292;
  state->field19_0x3c = fVar9;
  if (fVar9 == fVar8) {
    fVar8 = 1.0;
  }
  else {
    fVar8 = (0.0 - fVar8) / (fVar9 - fVar8);
    if (fVar8 <= 1.0) {
      if (fVar8 < 0.0) {
        fVar8 = 0.0;
      }
    }
    else {
      fVar8 = 1.0;
    }
  }
  pcVar4 = &param_2->field_0x24;
  state->field20_0x40 = fVar8;
  state->field21_0x44 = fVar8;
  iVar6 = 0x4c - (int)pcVar4;
  do {
    cVar1 = *pcVar4;
    pcVar4[(int)state + iVar6] = cVar1;
    pcVar4 = pcVar4 + 1;
  } while (cVar1 != '\0');
  if (actr->mind == (actorMind *)0x0) {
    paVar5 = (actorBody *)0x0;
  }
  else {
    paVar5 = actr->mind->currentAttackTarget;
  }
  state->field154_0xcc = paVar5;
  body->farRangeThreshold = true;
  body->someHitFlag = true;
  body->field_0x6a = body->field_0x6a + '\x01';
  iVar6 = 0;
  do {
    if ((1 << ((byte)iVar6 & 0x1f) & 0xffffU) != 0) {
      pcVar4 = (char *)((int)body->bigVec3Set + iVar6 + -0x3b);
      *pcVar4 = *pcVar4 + '\x01';
    }
    iVar6 = iVar6 + 1;
  } while (iVar6 < 4);
  paVar2 = body->flagSet->flags;
  *(byte *)((int)&paVar2->attackFlags_ + 1) = *(byte *)((int)&paVar2->attackFlags_ + 1) | 0x80;
  local_4 = 0;
  local_8 = 0x9a;
  (*((wpn->avatar).vtable)->onMessage)(wpn,&local_8);
  state->field5_0x1c = (uint)(local_4 != 0);
  FUN_0009fed0(1);
  return 1;
}




void entityStateShoot::dtor(int param_1)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  int iVar4;
  
  iVar4 = param_1;
  iVar1 = *(int *)(param_1 + 8);
  iVar2 = *(int *)(iVar1 + 8);
  piVar3 = *(int **)(iVar1 + 0x48);
  if (*(int *)(param_1 + 0x18) == 1) {
    if ((piVar3 != (int *)0x0) && (*(int *)(param_1 + 0x20) != 0)) {
      param_1 = 0xa3;
      (**(code **)(*piVar3 + 0xc))(piVar3,&param_1);
    }
    *(undefined4 *)(iVar4 + 0x20) = 0;
    *(undefined4 *)(iVar4 + 0x48) = 0;
  }
  *(undefined4 *)(iVar4 + 0x18) = 0;
  *(char *)(iVar1 + 0x6a) = *(char *)(iVar1 + 0x6a) + -1;
  *(char *)(iVar1 + 0x309) = *(char *)(iVar1 + 0x309) + -1;
  *(char *)(iVar1 + 0x30a) = *(char *)(iVar1 + 0x30a) + -1;
  *(char *)(iVar1 + 0x30c) = *(char *)(iVar1 + 0x30c) + -1;
  *(char *)(iVar1 + 0x30b) = *(char *)(iVar1 + 0x30b) + -1;
  iVar1 = *(int *)(*(int *)(iVar1 + 0x15c) + 8);
  *(byte *)(iVar1 + 5) = *(byte *)(iVar1 + 5) & 0x7f;
  iVar1 = *(int *)(iVar2 + 0x50);
  if (iVar1 != 0) {
    iVar2 = *(int *)(iVar1 + 0x58);
    if (*(int *)(iVar2 + 0x50) != 0) {
      *(float *)(iVar2 + 0x6c) = 0.25;
      *(undefined4 *)(iVar2 + 0x68) = 3;
    }
    *(undefined4 *)(iVar1 + 0x5c) = 1;
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void entityStateShoot::updateFixed_(entityStateShoot *state)

{
  actorBody *this;
  actor *paVar1;
  weapon *pwVar2;
  KeyframeContext *pKVar3;
  AnimInstance *pAVar4;
  undefined4 uVar5;
  bool bVar6;
  actorBodyStateId aVar7;
  int iVar8;
  uint uVar9;
  actorBody *paVar10;
  uint uVar11;
  bool bVar12;
  float fVar13;
  float fVar14;
  InputHandlerType1 *in_stack_00000008;
  actorBody *local_38;
  vec2 vStack_2c;
  float fStack_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  undefined4 local_8;
  undefined4 local_4;
  
  fVar13 = 0.0;
  this = (state->actorState).body;
  if (runtime::dx_timer <= 0.0) {
    fVar14 = runtime::DeltaTime * runtime::TimeScale;
  }
  else {
    fVar14 = 0.0;
  }
  if ((this->actor->avatar).movementFreezeTimer <= 0.0) {
    fVar13 = (this->actor->avatar).actionSpeed;
  }
  (state->actorState).t = fVar13 * fVar14 + (state->actorState).t;
  paVar1 = this->actor;
  pwVar2 = this->weapon;
  if (paVar1->mind == (actorMind *)0x0) {
    local_38 = (actorBody *)0x0;
  }
  else {
    local_38 = paVar1->mind->currentAttackTarget;
  }
  local_1c = 0;
  local_18 = 0;
  local_14 = 0;
  local_10 = 0;
  local_c = 0;
  local_8 = 0;
  local_4 = 0;
  local_20 = 0x9f;
  (*((pwVar2->avatar).vtable)->onMessage)(pwVar2,&local_20);
  if (runtime::dx_timer <= 0.0) {
    fVar13 = runtime::DeltaTime * runtime::TimeScale;
  }
  else {
    fVar13 = 0.0;
  }
  fVar14 = 0.0;
  if ((paVar1->avatar).movementFreezeTimer <= 0.0) {
    fVar14 = (paVar1->avatar).actionSpeed;
  }
  if ((0.0 < *(float *)&state->field_0x24) &&
     (fVar13 = *(float *)&state->field_0x24 - fVar14 * fVar13, *(float *)&state->field_0x24 = fVar13
     , fVar13 <= 0.0)) {
    *(undefined4 *)&state->field_0x24 = 0;
  }
  if (*(int *)&state->field_0x18 != 1) {
    if (*(int *)&state->field_0x18 == 2) {
      if (local_38 == (actorBody *)0x0) {
        (this->rotation).z = 0.0;
        (this->rotation).x = 0.0;
      }
      else {
        FUN_000a0320(&vStack_2c);
        (this->rotation).x = vStack_2c.x;
        (this->rotation).y = vStack_2c.y;
        (this->rotation).z = fStack_24;
      }
      pKVar3 = (paVar1->avatar).keyframeContext;
      if ((pKVar3 != (KeyframeContext *)0x0) &&
         (pAVar4 = pKVar3->kfcAnims->animInstance, pAVar4 != (AnimInstance *)0x0)) {
        bVar12 = false;
        if (pAVar4->loopMode == Mode1) {
          if (pAVar4->invDuration <= 0.0 && pAVar4->invDuration != 0.0) {
            bVar12 = 0.0 < pAVar4->t;
          }
          else {
            bVar12 = pAVar4->t < 1.0;
          }
          if (bVar12) {
            bVar12 = false;
          }
          else {
            bVar12 = true;
          }
        }
        if (!bVar12) goto LAB_0009feb8;
      }
      iVar8 = FUN_00028c50();
      if (iVar8 == 0) {
        aVar7 = (*this->vtable->getStandingState)(this);
        state->field154_0xcc = local_38;
        (state->actorState).func6ret = aVar7;
        return;
      }
      FUN_0009fed0(1);
      state->field154_0xcc = local_38;
      return;
    }
    goto LAB_0009feb8;
  }
  if (local_38 == (actorBody *)0x0) {
    bVar12 = true;
    (this->rotation).z = 0.0;
    (this->rotation).x = 0.0;
  }
  else {
    fStack_24 = (local_38->worldPos).y;
    vStack_2c.x = (local_38->worldPosition).z;
    uVar5._0_1_ = local_38->farRangeThreshold;
    uVar5._1_1_ = local_38->someHitFlag;
    uVar5._2_2_ = *(undefined2 *)&local_38->field_0x3a;
    vStack_2c.y = *(float *)&local_38->field13_0x30 * 0.5 + (local_38->worldPos).x;
    FUN_0009ff90(local_38,uVar5,pwVar2);
    FUN_000a0320(&vStack_2c);
    (this->rotation).x = vStack_2c.x;
    (this->rotation).y = vStack_2c.y;
    (this->rotation).z = fStack_24;
    if (local_38 != (actorBody *)state->field154_0xcc) {
      vStack_2c.x = (this->actor->avatar).rotEuler.y;
      uVar9 = FUN_0001cc10(vStack_2c.x);
      if (this->currentAttackEntry == (AttackEntry *)0x0) {
        uVar11 = 1;
      }
      else {
        uVar11 = (uint)*(byte *)((int)&this->currentAttackEntry->actorMoveParams + 2);
      }
      if (uVar9 != uVar11) {
        bVar12 = true;
        goto LAB_0009fd5f;
      }
    }
    paVar10 = (actorBody *)FUN_00028c50();
    bVar12 = local_38 != paVar10;
    if ((0.0 < *(float *)&state->field_0x24) && (iVar8 = FUN_00028c50(), iVar8 == 0)) {
      bVar12 = false;
    }
  }
LAB_0009fd5f:
  FUN_000a0160();
  ScriptType1::getControllerXY(in_stack_00000008,&vStack_2c);
  fVar13 = vStack_2c.x;
  if ((0.010000001 < vStack_2c.y * vStack_2c.y + vStack_2c.x * vStack_2c.x) ||
     (fVar13 = *(float *)&state->field_0x24, fVar13 != 0.0)) {
    bVar6 = false;
  }
  else {
    bVar6 = true;
  }
  if (!bVar12) {
    if (bVar6) {
      if (pwVar2->field9_0x93c != '\0') goto LAB_0009fea2;
    }
    else if (pwVar2->field9_0x93c != '\0') {
      if (*(int *)&state->field_0x20 != 0) {
        if (state->field5_0x1c == 0) {
          vStack_2c.y = 0.0;
          vStack_2c.x = 2.25609e-43;
          FUN_00140a60();
          vStack_2c.y = fVar13;
          (*((pwVar2->avatar).vtable)->onMessage)(pwVar2,&vStack_2c);
          state->field154_0xcc = local_38;
          return;
        }
        if (state->field5_0x1c == 1) {
          FUN_0009fed0(2);
        }
      }
      goto LAB_0009feb8;
    }
    FUN_00041d00();
  }
LAB_0009fea2:
  aVar7 = (*this->vtable->getStandingState)(this);
  (state->actorState).func6ret = aVar7;
LAB_0009feb8:
  state->field154_0xcc = local_38;
  return;
}




void entityStateStand::getAllocDetails(undefined4 *param_1)

{
  *param_1 = 0x50;
  param_1[1] = 0xbc;
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


actorStateVTable * entityStateStand::getVTable(void)

{
  vtable.func5 = switchD_000d4179::EmptyFunction;
  vtable.func6 = switchD_000d4179::EmptyFunction;
  vtable.func7 = actorState::func7;
  vtable.getAllocDetails = getAllocDetails;
  vtable.ctor = ctor;
  vtable.dtor = dtor;
  vtable.onMessage = switchD_000d4179::EmptyFunction;
  vtable.update = update;
  return &vtable;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


BOOL entityStateStand::ctor(entityStateStand *state,entityStateStandParams *params)

{
  undefined1 *puVar1;
  actorBody *paVar2;
  actorBodyFlags *paVar3;
  KeyframeContext *pKVar4;
  AnimInstance *pAVar5;
  uint uVar6;
  Model *pMVar7;
  undefined1 index;
  byte bVar8;
  byte *pbVar9;
  char uVar9;
  actor *innerinner1;
  astruct_22 *iVar2;
  char uVar4;
  char uVar7;
  
  paVar2 = (state->actorState).body;
  innerinner1 = paVar2->actor;
  state->field1_0x18 = params->field1_0xc;
  state->field2_0x1a = params->field2_0xe;
  state->field3_0x1c = params->field3_0x10;
  state->field4_0x20 = params->field4_0x14;
  state->field5_0x24 = params->field5_0x18;
  state->field6_0x28 = params->field6_0x1c;
  state->field14_0x48 = params->field140_0xb4;
  state->field7_0x2c = params->field7_0x20;
  state->field8_0x30 = params->field8_0x24;
  state->field9_0x34 = params->field9_0x28;
  state->field10_0x38 = params->field11_0x30;
  state->field11_0x3c = params->field10_0x2c;
  state->field12_0x40 = (innerinner1->avatar).hasShadow;
  paVar3 = paVar2->flagSet->flags;
  *(byte *)((int)&paVar3->attackFlags_ + 2) = *(byte *)((int)&paVar3->attackFlags_ + 2) | 1;
  paVar2->farRangeThreshold = true;
  paVar2->someHitFlag = true;
  *(undefined2 *)&paVar2->field116_0x160 = 0;
  if ((state->field5_0x24 != 0) &&
     (pKVar4 = (innerinner1->avatar).keyframeContext, pKVar4 != (KeyframeContext *)0x0)) {
    pAVar5 = pKVar4->kfcAnims->animInstance;
    if (pAVar5 != (AnimInstance *)0x0) {
      puVar1 = &pAVar5->restartAnimation;
      *puVar1 = *puVar1 + '\x01';
    }
    pKVar4->free = 1;
  }
  if (state->field4_0x20 != 0) {
    paVar2->field_0x309 = paVar2->field_0x309 + '\x01';
    paVar2->field_0x30a = paVar2->field_0x30a + '\x01';
    paVar2->field_0x30b = paVar2->field_0x30b + '\x01';
    paVar2->field_0x30c = paVar2->field_0x30c + '\x01';
  }
  if (params->field12_0x34 != '\0') {
    if (params->field12_0x34 != '\0') {
      FUN_0012a260(0,innerinner1,4,(vec3 *)0x0,(vec3 *)0x0,1.0,
                   (astruct_25 *)&(innerinner1->avatar).model0x9s[3].field_0xb0,
                   &params->field12_0x34);
    }
    state->field13_0x44 = 1;
  }
  uVar6 = state->field14_0x48;
  if (uVar6 != 0) {
    pbVar9 = (byte *)((int)&paVar2->flagSet->flags->flag1 + (uVar6 >> 3));
    *pbVar9 = *pbVar9 | '\x01' << ((byte)uVar6 & 7);
  }
  if (state->field7_0x2c != 0xffffffff) {
    index = (undefined1)state->field7_0x2c;
    pMVar7 = (innerinner1->avatar).model;
    if (pMVar7 != (Model *)0x0) {
      ModelInstance::searchForValueWithFlags(1,pMVar7,index);
    }
    pMVar7 = (innerinner1->avatar).shadowModel;
    if (pMVar7 != (Model *)0x0) {
      ModelInstance::searchForValueWithFlags(1,pMVar7,index);
    }
  }
  if (params->field141_0xb8 == 0) {
    state->field15_0x4c = (uint)(byte)paVar2->shatsheetInitialised_;
  }
  else {
    bVar8 = FUN_0001feb0(paVar2);
    state->field15_0x4c = (uint)bVar8;
  }
  if (state->field6_0x28 != 0) {
    paVar2->field302_0x258 = paVar2->field302_0x258 + 1;
  }
  if ((state->field11_0x3c != 0) && ((innerinner1->avatar).shadowModel != (Model *)0x0)) {
    (innerinner1->avatar).hasShadow = 0;
    return 1;
  }
  return 1;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void entityStateStand::dtor(entityStateStand *param_1)

{
  undefined1 *puVar1;
  uint *puVar2;
  undefined1 index;
  actorBody *paVar3;
  actorBodyFlags *paVar4;
  actor *paVar5;
  KeyframeContext *pKVar6;
  AnimInstance *pAVar7;
  uint uVar8;
  Model *pMVar9;
  weapon *pwVar10;
  entityStateStand *peVar11;
  undefined4 uStack_8;
  undefined4 uStack_4;
  
  peVar11 = param_1;
  paVar3 = (param_1->actorState).body;
  paVar4 = paVar3->flagSet->flags;
  paVar5 = paVar3->actor;
  *(byte *)((int)&paVar4->attackFlags_ + 2) = *(byte *)((int)&paVar4->attackFlags_ + 2) & 0xfe;
  if (param_1->field4_0x20 != 0) {
    paVar3->field_0x309 = paVar3->field_0x309 + -1;
    paVar3->field_0x30a = paVar3->field_0x30a + -1;
    paVar3->field_0x30b = paVar3->field_0x30b + -1;
    paVar3->field_0x30c = paVar3->field_0x30c + -1;
  }
  if ((param_1->field5_0x24 != 0) &&
     (pKVar6 = (paVar3->actor->avatar).keyframeContext, pKVar6 != (KeyframeContext *)0x0)) {
    pAVar7 = pKVar6->kfcAnims->animInstance;
    if (pAVar7 != (AnimInstance *)0x0) {
      puVar1 = &pAVar7->restartAnimation;
      *puVar1 = *puVar1 + -1;
    }
    pKVar6->free = 1;
  }
  if (param_1->field13_0x44 != 0) {
    FUN_0012a3d0((astruct_25 *)&(paVar5->avatar).model0x9s[3].field_0xb0);
  }
  uVar8 = peVar11->field14_0x48;
  if (uVar8 != 0) {
    paVar4 = paVar3->flagSet->flags;
    *(byte *)((int)&paVar4->flag1 + (uVar8 >> 3)) =
         *(byte *)((int)&paVar4->flag1 + (uVar8 >> 3)) & ~('\x01' << ((byte)uVar8 & 7));
  }
  if ((peVar11->field7_0x2c != 0xffffffff) && (peVar11->field8_0x30 == 0)) {
    index = (undefined1)peVar11->field7_0x2c;
    param_1 = (entityStateStand *)CONCAT31(param_1._1_3_,index);
    pMVar9 = (paVar5->avatar).model;
    if (pMVar9 != (Model *)0x0) {
      ModelInstance::searchForValueWithFlags(0,pMVar9,index);
    }
    pMVar9 = (paVar5->avatar).shadowModel;
    if (pMVar9 != (Model *)0x0) {
      ModelInstance::searchForValueWithFlags(0,pMVar9,index);
    }
  }
  FUN_0001feb0(paVar3);
  if (peVar11->field6_0x28 != 0) {
    puVar2 = &paVar3->field302_0x258;
    *puVar2 = *puVar2 - 1;
    if (*puVar2 == 0) {
      param_1 = (entityStateStand *)0x4a;
      (*paVar3->vtable->onMessage)(paVar3,&param_1);
    }
  }
  if ((peVar11->field9_0x34 != 0) && (pwVar10 = paVar3->someWeapon, pwVar10 != (weapon *)0x0)) {
    FUN_0001b570();
    uStack_4 = 0;
    uStack_8 = 0x97;
    (*((pwVar10->avatar).vtable)->onMessage)(pwVar10,&uStack_8);
  }
  if ((peVar11->field11_0x3c != 0) && ((paVar5->avatar).shadowModel != (Model *)0x0)) {
    (paVar5->avatar).hasShadow = peVar11->field12_0x40;
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void entityStateStand::update(entityStateStand *param_1,InputHandlerType1 *param_2)

{
  int iVar1;
  actorBodyStateId aVar2;
  actorBodyFlags *in_ECX;
  actorBodyFlags *extraout_ECX;
  actorBodyFlags *extraout_ECX_00;
  vec2 vStack_8;
  actorBody *body;
  actorBody *bodyy;
  avatar *paVar2;
  actor *act;
  float fx;
  float fy;
  float fz;
  
  bodyy = (param_1->actorState).body;
  act = bodyy->actor;
  if (runtime::dx_timer <= 0.0) {
    fz = runtime::DeltaTime * runtime::TimeScale;
  }
  else {
    fz = 0.0;
  }
  fy = 0.0;
  if ((act->avatar).movementFreezeTimer <= 0.0) {
    fy = (act->avatar).actionSpeed;
  }
  iVar1 = param_1->field3_0x1c;
  (param_1->actorState).t = fy * fz + (param_1->actorState).t;
  if (iVar1 != 0) {
    fz = (bodyy->v2).z;
    fy = (bodyy->v2).y;
    fx = (bodyy->v2).x;
    if ((fz * fz + fy * fy + fx * fx <= 0.0) ||
       (in_ECX = bodyy->flagSet->flags, (in_ECX->flag1 & AnimTrigger) == Null)) {
      aVar2 = Null;
    }
    else {
      aVar2 = (*bodyy->vtable->getShuffleState)(bodyy);
      in_ECX = extraout_ECX;
    }
    (param_1->actorState).func6ret = aVar2;
  }
  if (param_1->field6_0x28 == 0) {
    if (param_1->field10_0x38 == 0) {
      (bodyy->rotation).z = 0.0;
      (bodyy->rotation).x = 0.0;
    }
    else {
      actorBody::applyBodyDirectionToRotation(bodyy);
      in_ECX = extraout_ECX_00;
    }
  }
  if (((((bodyy->flagSet->flags->attackFlags_ & 0x8000000) != Null) ||
       (in_ECX = (actorBodyFlags *)CONCAT22((short)((uint)in_ECX >> 0x10),param_1->field2_0x1a),
       param_1->field2_0x1a == 0)) || (act->mind == (actorMind *)0x0)) ||
     (act->mind->field_0x20 == '\0')) {
    FUN_000a2a90(in_ECX,bodyy);
    if (param_1->field1_0x18 == 0) {
      return;
    }
    Input::GetLSMovement_(param_2,&vStack_8);
    if (vStack_8.y * vStack_8.y + vStack_8.x * vStack_8.x <= 0.010000001) {
      return;
    }
    in_ECX = (actorBodyFlags *)(uint)(ushort)param_1->field1_0x18;
  }
  (param_1->actorState).func6ret = (ushort)in_ECX;
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void entityStateStruggle::getAllocDetails(undefined4 *param_1)

{
  *param_1 = 0x20;
  param_1[1] = 0x8c;
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


undefined ** entityStateStruggle::getVTable(void)

{
  vtable[5] = switchD_000d4179::EmptyFunction;
  vtable[6] = switchD_000d4179::EmptyFunction;
  vtable[7] = actorState::func7;
  vtable[0] = getAllocDetails;
  vtable[1] = ctor;
  vtable[2] = dtor;
  vtable[3] = onMessage;
  vtable[4] = update;
  return vtable;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


undefined4 entityStateStruggle::ctor(entityStateStruggle *state,entityStateStruggleParams *params)

{
  undefined1 uVar4;
  undefined4 uStack_8;
  undefined4 local_4;
  actor *act;
  MindMemoryTargetWantedToAttack *iVar3;
  actorBody *paVar1;
  actorMind *paVar2;
  
  paVar1 = (state->state).body;
  act = paVar1->actor;
  paVar2 = act->mind;
  state->jumpedOffFloat = 0.0;
  paVar1->field_0x30b = paVar1->field_0x30b + '\x01';
  paVar1->field_0x309 = paVar1->field_0x309 + '\x01';
  paVar1->field_0x30a = paVar1->field_0x30a + '\x01';
  paVar1->field_0x30c = paVar1->field_0x30c + '\x01';
  paVar1->field13_0x30 = paVar1->field13_0x30 + 1;
  if (paVar2 != (actorMind *)0x0) {
    paVar2->targetActor = (actor *)0x0;
    if (paVar2->targetBody != (actorBody *)0x0) {
      uStack_8 = 100;
      local_4 = 0;
      (*((paVar2->actor->avatar).vtable)->onMessage)(paVar2->actor,&uStack_8);
    }
    iVar3 = (MindMemoryTargetWantedToAttack *)paVar2->memoryHead;
    paVar2->targetBody = (actorBody *)0x0;
    paVar2->currentAttackTarget = (actorBody *)0x0;
    for (; iVar3 != (MindMemoryTargetWantedToAttack *)0x0;
        iVar3 = (MindMemoryTargetWantedToAttack *)(iVar3->header).next) {
      if ((iVar3->header).memId == TargedWantedToAttack) {
        MindMemory::dtor(iVar3);
        break;
      }
    }
  }
  uVar4 = FUN_0001feb0(paVar1);
  state->field_0x18 = uVar4;
  if (params->field_0xc != '\0') {
    FUN_0012a260(0,act,4,(vec3 *)0x0,(vec3 *)0x0,1.0,
                 (astruct_25 *)&(act->avatar).model0x9s[3].field_0xb0,&params->field_0xc);
  }
  return 1;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void entityStateStruggle::dtor(int param_1)

{
  actorBody *paVar1;
  int *piVar2;
  actor *paVar3;
  
  paVar1 = *(actorBody **)(param_1 + 8);
  piVar2 = *(int **)&paVar1->field_0x50;
  paVar3 = paVar1->actor;
  if (piVar2 != (int *)0x0) {
    param_1 = 0x54;
    (**(code **)(*piVar2 + 0xc))(piVar2,&param_1);
  }
  paVar1->field13_0x30 = paVar1->field13_0x30 - 1;
  paVar1->field_0x309 = paVar1->field_0x309 + -1;
  paVar1->field_0x30a = paVar1->field_0x30a + -1;
  paVar1->field_0x30b = paVar1->field_0x30b + -1;
  paVar1->field_0x30c = paVar1->field_0x30c + -1;
  FUN_0001feb0(paVar1);
  FUN_0012a3d0((astruct_25 *)&(paVar3->avatar).model0x9s[3].field_0xb0);
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void entityStateStruggle::update(entityStateStruggle *struggle)

{
  actor *paVar1;
  actorBodyStateId aVar2;
  float fVar3;
  float fVar4;
  actorBody *body;
  
  body = (struggle->state).body;
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
  (struggle->state).t = fVar3 * fVar4 + (struggle->state).t;
  (body->rotation).z = 0.0;
  (body->rotation).x = 0.0;
  paVar1 = ((struggle->state).body)->actor;
  if (runtime::dx_timer <= 0.0) {
    fVar4 = runtime::DeltaTime * runtime::TimeScale;
  }
  else {
    fVar4 = 0.0;
  }
  fVar3 = 0.0;
  if ((paVar1->avatar).movementFreezeTimer <= 0.0) {
    fVar3 = (paVar1->avatar).actionSpeed;
  }
  if ((0.0 < struggle->jumpedOffFloat) &&
     (fVar4 = struggle->jumpedOffFloat - fVar3 * fVar4, struggle->jumpedOffFloat = fVar4,
     fVar4 <= 0.0)) {
    struggle->jumpedOffFloat = 0.0;
    aVar2 = (*body->vtable->getStandingState)(body);
    (struggle->state).func6ret = aVar2;
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields
// WARNING: Struct "Actor_StruggleMessage": ignoring overlapping field "field1_0x4"


void entityStateStruggle::onMessage(entityStateStruggle *param_1,Message *msg)

{
  ObjMsgID OVar1;
  
  OVar1 = (msg->header).msgId;
  if (OVar1 == Actor_JumpedOff) {
    param_1->jumpedOffFloat = 0.5;
  }
  else if (OVar1 == Actor_Struggle) {
    entityStateWalk::onActorStruggle(0,(param_1->state).body,(Actor_StruggleMessage *)msg);
    return;
  }
  return;
}



// WARNING: Globals starting with '_' overlap smaller symbols at the same address
// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


switchD_000a49eb::caseD_7c(int param_1,undefined4 param_2,undefined4 param_3,int param_4)

{
  if (*(avatar **)(param_1 + 4) == *(avatar **)(param_4 + 0x20)) {
    avatar::destroy(*(avatar **)(param_4 + 0x20));
    *(undefined4 *)(param_4 + 0x20) = 0;
    return;
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void switchD_000a49eb::caseD_15(undefined4 param_1,undefined4 param_2,int param_3)

{
  actor *act;
  
  act = *(actor **)(*(int *)(param_3 + 8) + 8);
  if (*(char *)(param_3 + 0x33c) != '\0') {
    FUN_0012a260(0,act,1,(vec3 *)0x0,(vec3 *)0x0,1.0,
                 (astruct_25 *)&(act->avatar).model0x9s[0].field_0xb0,(char *)(param_3 + 0x33c));
  }
  FUN_0003cae0(act);
  entityBodyHuman::onEscapeBackground(1,act);
  if (*(int *)(param_3 + 0x20) != 0) {
    FUN_0013b1f0(*(int *)(param_3 + 0x20),0x40a00000);
    avatar::destroy(*(avatar **)(param_3 + 0x20));
    *(undefined4 *)(param_3 + 0x20) = 0;
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void entityStateWalk::getAllocDetails(undefined4 *param_1)

{
  *param_1 = 0x88;
  param_1[1] = 0xb8;
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


actorStateVTable * entityStateWalk::getVTable(void)

{
  vtable.func5 = switchD_000d4179::EmptyFunction;
  vtable.func6 = switchD_000d4179::EmptyFunction;
  vtable.func7 = actorState::func7;
  vtable.getAllocDetails = getAllocDetails;
  vtable.ctor = ctor;
  vtable.dtor = dtor;
  vtable.onMessage = onMessage;
  vtable.update = update;
  return &vtable;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


undefined4 entityStateWalk::ctor(entityStateWalk *walk,entityStateWalkParams *params)

{
  undefined2 *puVar1;
  char cVar2;
  actor *act_00;
  actorBodyFlags *paVar3;
  uint uVar4;
  AnimEventMapping *pAVar5;
  KeyframeContext *new_mem;
  int i_ptr;
  undefined4 *puVar6;
  byte *pbVar7;
  HeapTableEntry *pHVar8;
  KeyframeContext *pKVar9;
  char *pcVar10;
  char *has_wpn;
  int i;
  KFCParams animConfig;
  actor *act;
  actorBody *bodyy;
  short num_walks;
  
  num_walks = params->numWalks;
  bodyy = (walk->actorState).body;
  act = bodyy->actor;
  i_ptr = 0;
  walk->numWalks = num_walks;
  i = 0;
  if (0 < num_walks) {
    puVar6 = (undefined4 *)&walk->field_0x34;
    do {
      pcVar10 = *(char **)((int)&(params->maybeKeyframeList->pos).x + i_ptr);
      if (((bodyy->weapon == (weapon *)0x0) ||
          (has_wpn = &bodyy->weapon->field1062_0xdb0, has_wpn == (char *)0x0)) || (*has_wpn == '\0')
         ) {
        has_wpn = (char *)0x0;
      }
      act_00 = bodyy->actor;
      pAVar5 = avatar::getAnimEventByName(&act_00->avatar,pcVar10,(BOOL)has_wpn);
      if ((pAVar5 == (AnimEventMapping *)0x0) && (has_wpn != (char *)0x0)) {
        pAVar5 = avatar::getAnimEventByName(&act_00->avatar,pcVar10,0);
      }
      puVar6[-1] = pAVar5;
      *puVar6 = *(undefined4 *)((int)&(params->maybeKeyframeList->pos).y + i_ptr);
      puVar6[1] = *(undefined4 *)((int)&(params->maybeKeyframeList->pos).z + i_ptr);
      puVar6[2] = *(undefined4 *)((int)&params->maybeKeyframeList->index + i_ptr);
      i = i + 1;
      i_ptr = i_ptr + 0x10;
      puVar6 = puVar6 + 4;
    } while (i < walk->numWalks);
  }
  walk->currentKeyframe_ = 0;
  *(undefined2 *)&walk->field_0x1a = *(undefined2 *)&params->field_0x94;
  *(undefined2 *)&walk->field_0x1c = *(undefined2 *)&params->field_0x96;
  *(undefined4 *)&walk->field_0x20 = *(undefined4 *)&params->field_0x98;
  *(undefined4 *)&walk->field_0x24 = *(undefined4 *)&params->field_0x9c;
  walk->maxMovementMagnitude = *(float *)&params->field_0xa0;
  walk->rotationSpeedCheck_ = *(float *)&params->field_0xa4;
  walk->field89_0x78 = *(float *)&params->field_0xa8;
  *(undefined4 *)&walk->field_0x7c = *(undefined4 *)&params->field_0xac;
  *(undefined4 *)&walk->field_0x80 = *(undefined4 *)&params->field_0xb0;
  *(undefined4 *)&walk->field_0x84 = *(undefined4 *)&params->field_0xb4;
  paVar3 = bodyy->flagSet->flags;
  *(byte *)((int)&paVar3->attackFlags_ + 2) = *(byte *)((int)&paVar3->attackFlags_ + 2) | 0x80;
  cVar2 = params->field_0x14;
  if (cVar2 != '\0') {
    if (cVar2 != '\0') {
      FUN_0012a260(0,act,4,(vec3 *)0x0,(vec3 *)0x0,1.0,
                   (astruct_25 *)&(act->avatar).model0x9s[3].field_0xb0,&params->field_0x14);
    }
    *(undefined4 *)&walk->field_0x70 = 1;
  }
  uVar4 = *(uint *)&walk->field_0x84;
  if (uVar4 != 0) {
    pbVar7 = (byte *)((int)&bodyy->flagSet->flags->flag1 + (uVar4 >> 3));
    *pbVar7 = *pbVar7 | '\x01' << ((byte)uVar4 & 7);
  }
  act = bodyy->actor;
  pAVar5 = *(AnimEventMapping **)(&walk->field_0x30 + (uint)walk->currentKeyframe_ * 0x10);
  FUN_000322a0(pAVar5,(act->avatar).needsAnimMapping,&animConfig);
  cVar2 = *(char *)((int)&pAVar5->field7_0x114 + 3);
  pcVar10 = pAVar5->animAID;
  if ((act->avatar).keyframeContext == (KeyframeContext *)0x0) {
    if (g_HeapTableBase[runtime::CurrentHeapToAllocateFrom].heapHandle == (HANDLE)0x0) {
      pHVar8 = (HeapTableEntry *)0x0;
    }
    else {
      pHVar8 = g_HeapTableBase + runtime::CurrentHeapToAllocateFrom;
    }
    new_mem = (KeyframeContext *)runtime::AllocateOnHeap(pHVar8->heapHandle,0,0x10c);
    if (new_mem != (KeyframeContext *)0x0) {
      i_ptr = FUN_0014ded0(pHVar8->heapHandle,0,new_mem);
      puVar1 = (undefined2 *)((int)new_mem->_channelsData + i_ptr + -0x6c);
      *puVar1 = 0x1234;
      *(undefined1 *)(puVar1 + 1) = *(undefined1 *)&pHVar8->field32_0x20;
    }
    pKVar9 = new_mem;
    for (i_ptr = 0x42; i_ptr != 0; i_ptr = i_ptr + -1) {
      pKVar9->animEventCallback = (TriggerAnimationEventCallback *)0x0;
      pKVar9 = (KeyframeContext *)&pKVar9->avatar;
    }
    new_mem->numAnimations = 4;
    new_mem->free = 1;
    new_mem->kfcAnims = new_mem->_channelsData;
    new_mem->kfHeaderPtr = &new_mem->_kfHeader;
    (new_mem->_kfHeader).floatSet.pos.z = 0.0;
    (new_mem->_kfHeader).floatSet.pos.y = 0.0;
    (new_mem->_kfHeader).floatSet.pos.x = 0.0;
    (new_mem->_kfHeader).floatSet.rotQuat.x = 0.0;
    (new_mem->_kfHeader).floatSet.rotQuat.y = 0.0;
    (new_mem->_kfHeader).floatSet.rotQuat.z = 0.0;
    (new_mem->_kfHeader).floatSet.rotQuat.w = 1.0;
    (act->avatar).keyframeContext = new_mem;
    new_mem->animEventCallback = avatar::triggerAnimationEvent;
    new_mem->avatar = &act->avatar;
  }
  if (animConfig.animResource == (AnimResource *)0x0) {
    animConfig.animResource = (AnimResource *)0x0;
  }
  else {
    pcVar10 = (char *)0x0;
  }
  KeyframeContext::setFromAnimName
            ((act->avatar).keyframeContext,(int)cVar2,&animConfig,pcVar10,animConfig.animResource);
  (act->avatar).needsAnimMapping = 0;
  actorBody::sendSyncAnimationMessage(bodyy);
  bodyy->farRangeThreshold = true;
  bodyy->someHitFlag = true;
  return 1;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void entityStateWalk::dtor(int param_1)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  
  iVar1 = *(int *)(param_1 + 8);
  if (*(int *)(param_1 + 0x70) != 0) {
    FUN_0012a3d0((astruct_25 *)(*(int *)(iVar1 + 8) + 0x614));
  }
  uVar2 = *(uint *)(param_1 + 0x84);
  if (uVar2 != 0) {
    iVar3 = *(int *)(*(int *)(iVar1 + 0x15c) + 8);
    *(byte *)((uVar2 >> 3) + iVar3) =
         *(byte *)((uVar2 >> 3) + iVar3) & ~('\x01' << ((byte)uVar2 & 7));
  }
  iVar1 = *(int *)(*(int *)(iVar1 + 0x15c) + 8);
  *(byte *)(iVar1 + 6) = *(byte *)(iVar1 + 6) & 0x7f;
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void entityStateWalk::update(actorState *this,InputHandlerType1 *param_2)

{
  actorBody *body;
  float fVar1;
  float delta;
  
  fVar1 = 0.0;
  body = this->body;
  if (runtime::dx_timer <= 0.0) {
    delta = runtime::DeltaTime * runtime::TimeScale;
  }
  else {
    delta = 0.0;
  }
  if ((body->actor->avatar).movementFreezeTimer <= 0.0) {
    fVar1 = (body->actor->avatar).actionSpeed;
  }
  this->t = fVar1 * delta + this->t;
  actorBody::walk(body,param_2,(entityStateWalk *)this);
  FUN_000a5dc0(body,(entityStateWalk *)this);
  FUN_000a5ea0();
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields
// WARNING: Struct "Actor_StruggleMessage": ignoring overlapping field "field1_0x4"


void entityStateWalk::onMessage(entityStateWalk *param_1,Message *msg)

{
  if ((msg->header).msgId == Actor_Struggle) {
    onActorStruggle(1,(param_1->actorState).body,(Actor_StruggleMessage *)msg);
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void pickup::DetachFromActor(entityStatePickup *param_1,actor *param_2)

{
  undefined1 *puVar1;
  actorBody *paVar2;
  entityStatePickup *peVar3;
  entityStatePickup *peVar4;
  actor *paVar5;
  
  paVar5 = param_2;
  peVar3 = param_1;
  while (peVar4 = peVar3, peVar4 != (entityStatePickup *)0x0) {
    paVar2 = (peVar4->state).body;
    if (paVar2 != (actorBody *)0x0) {
      DetachFromActor((entityStatePickup *)paVar2,paVar5);
    }
    puVar1 = &peVar4[-0x35].state.field_0x4;
    peVar3 = *(entityStatePickup **)&(peVar4->state).field_0x4;
    if (peVar4[-1].field2_0x1c == 0.0) {
      param_1 = (entityStatePickup *)0x80;
      (**(code **)(*(int *)puVar1 + 0xc))(puVar1,&param_1);
      if (peVar4[-1].field2_0x1c == 0.0) {
        removeavatarfromsomelistsshit(puVar1);
      }
    }
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


