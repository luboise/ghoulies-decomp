/* ai_actor.c - Actor brain base: actorBody/actor/mind, hit reactions */
#include "ai_actor.h"

void actor::initialiseAttribs(actor *act,actorParams *params)

{
  ActorAttribsResource *pAVar1;
  ushort uVar2;
  uint tag_index;
  float fVar3;
  ActorAttribsResource *attribs;
  float val;
  
  if (*(int *)params->actorAttribsDefaultsAID == 0x5f646961) {
    Assets::GetResourceBytes(params->actorAttribsDefaultsAID,&attribs);
    if (attribs == (ActorAttribsResource *)0x0) {
      runtime::ExitGame(2);
    }
    act->attribs = attribs;
  }
  if (act->actorType == Ghoulie_old) {
    fVar3 = 0.0;
    if (act->attribs == (ActorAttribsResource *)0x0) {
      val = 0.0;
    }
    else {
      val = act->attribs->rand1;
    }
    runtime::rand = runtime::rand * 0x19660d + 0x3c6ef35f;
    act->rand1 = (float)(runtime::rand & 0x7fffff | 0x3f800000) - 1.0 <= val;
    if (act->attribs == (ActorAttribsResource *)0x0) {
      val = 0.0;
    }
    else {
      val = act->attribs->rand2;
    }
    runtime::rand = runtime::rand * 0x19660d + 0x3c6ef35f;
    act->rand2 = (float)(runtime::rand & 0x7fffff | 0x3f800000) - 1.0 <= val;
    if (act->attribs == (ActorAttribsResource *)0x0) {
      val = 0.0;
    }
    else {
      val = act->attribs->someFloatAttrib;
    }
    act->cowardTimer = val;
    if (act->attribs == (ActorAttribsResource *)0x0) {
      val = 0.0;
    }
    else {
      val = act->attribs->rand3;
    }
    runtime::rand = runtime::rand * 0x19660d + 0x3c6ef35f;
    act->rand3 = (float)(runtime::rand & 0x7fffff | 0x3f800000) - 1.0 <= val;
    if (act->attribs == (ActorAttribsResource *)0x0) {
      val = 0.0;
    }
    else {
      val = act->attribs->rand4;
    }
    runtime::rand = runtime::rand * 0x19660d + 0x3c6ef35f;
    act->rand4 = (float)(runtime::rand & 0x7fffff | 0x3f800000) - 1.0 <= val;
    if (act->attribs == (ActorAttribsResource *)0x0) {
      val = 0.0;
    }
    else {
      val = act->attribs->rand5;
    }
    runtime::rand = runtime::rand * 0x19660d + 0x3c6ef35f;
    act->rand5 = (float)(runtime::rand & 0x7fffff | 0x3f800000) - 1.0 <= val;
    if (act->attribs != (ActorAttribsResource *)0x0) {
      fVar3 = act->attribs->rand6;
    }
    runtime::rand = runtime::rand * 0x19660d + 0x3c6ef35f;
    attribs = (ActorAttribsResource *)
              (runtime::rand & 0b00000000011111111111111111111111 | 0x3f800000);
    pAVar1 = act->attribs;
    act->randTraitoristicCombat = (float)attribs - 1.0 <= fVar3;
    tag_index = Events::GetIndexOfStringInTable(0xe9,ActorTagTable + 1,pAVar1->tagName1);
    if (tag_index == 0xffffffff) {
      uVar2 = 0;
    }
    else {
      uVar2 = (short)tag_index + 1;
    }
    act->objTagTypeIndex = uVar2;
    tag_index = Events::GetIndexOfStringInTable(0xe9,ActorTagTable + 1,pAVar1->tagName2);
    if (tag_index == 0xffffffff) {
      act->objTagTypeIndex2 = 0;
      return;
    }
    act->objTagTypeIndex2 = (short)tag_index + 1;
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void actor::updateGhoulieTimers(actor *act)

{
  float delta;
  float speed;
  ObjMsgID local_4;
  
  if ((ShouldntDroneBools[1] == 0) && ("\x01"[Game::CheckMoveOn] != '\0')) {
    if (runtime::dx_timer <= 0.0) {
      delta = runtime::DeltaTime * runtime::TimeScale;
    }
    else {
      delta = 0.0;
    }
    speed = 0.0;
    if ((act->avatar).movementFreezeTimer <= 0.0) {
      speed = (act->avatar).actionSpeed;
    }
    if ((0.0 < act->cowardTimer) &&
       (delta = act->cowardTimer - speed * delta, act->cowardTimer = delta, delta <= 0.0)) {
      act->cowardTimer = 0.0;
      local_4 = Actor_TimeCowardExpired;
      (*((act->avatar).vtable)->onMessage)(act,&local_4);
    }
  }
  if ((ShouldntDroneBools[1] == 0) && ("\x01"[Game::CheckMoveOn] != '\0')) {
    if (runtime::dx_timer <= 0.0) {
      delta = runtime::DeltaTime * runtime::TimeScale;
    }
    else {
      delta = 0.0;
    }
    speed = 0.0;
    if ((act->avatar).movementFreezeTimer <= 0.0) {
      speed = (act->avatar).actionSpeed;
    }
    if ((0.0 < act->traitorTimer) &&
       (delta = act->traitorTimer - speed * delta, act->traitorTimer = delta, delta <= 0.0)) {
      act->traitorTimer = 0.0;
      local_4 = Actor_TimeTraitorExpired;
      (*((act->avatar).vtable)->onMessage)(act,&local_4);
    }
  }
  return;
}




void actorBody::onVelocityBoost(int param_1)

{
  int iVar1;
  int in_EAX;
  float fVar2;
  
  if ((*(byte *)(*(int *)(*(int *)(in_EAX + 0x15c) + 8) + 7) & 0x20) == 0) {
    iVar1 = *(int *)(*(int *)(in_EAX + 8) + 0x958);
    fVar2 = 0.0;
    if ((iVar1 != 0) && (*(int *)(iVar1 + 0x14) != 0)) {
      FUN_00041a30();
    }
    FUN_00019a90(*(undefined4 *)(param_1 + 0x10),*(float *)(*(int *)(in_EAX + 8) + 0x18) + fVar2);
  }
  return;
}




void __fastcall actorBody::onVelocityBoostToYaw(int param_1)

{
  int in_EAX;
  
  if ((*(byte *)(*(int *)(*(int *)(param_1 + 0x15c) + 8) + 7) & 0x20) == 0) {
    FUN_00019a90(*(undefined4 *)(in_EAX + 0x10),
                 *(float *)(in_EAX + 0x14) * 0.017453292 + *(float *)(*(int *)(param_1 + 8) + 0x18))
    ;
  }
  return;
}




void actorBody::onFootDown(int param_1)

{
  float fVar1;
  actor *act;
  actorBody *body;
  actor *paVar2;
  int in_EAX;
  float10 fVar3;
  float fVar4;
  float local_84;
  char local_80 [128];
  
  act = *(actor **)(in_EAX + 8);
  body = act->body;
  paVar2 = body->actor;
  fVar4 = (paVar2->avatar).physicsPos.x;
  fVar1 = (paVar2->avatar).physicsPos.z;
  fVar3 = scaled_invsqrt(fVar4 * fVar4 + fVar1 * fVar1);
  fVar4 = getMovespeed(body);
  fVar4 = (float)fVar3 / fVar4;
  if (1.0 <= fVar4) {
    fVar4 = 1.0;
  }
  fVar4 = fVar4 * 0.19999999 + 0.8;
  if (fVar4 <= 1.0) {
    local_84 = 0.8;
    if (0.8 <= fVar4) {
      local_84 = fVar4;
    }
  }
  else {
    local_84 = 1.0;
  }
  if (*(int *)(param_1 + 0x14) == 0) {
    fVar4 = (act->avatar).scale.z;
  }
  else {
    fVar4 = (act->avatar).uniformScale * (act->avatar).scale.x;
  }
  FUN_0001a020();
  if (local_80[0] != '\0') {
    FUN_0012a260(1,act,3,(vec3 *)0x0,(vec3 *)0x0,fVar4 * local_84,
                 (astruct_25 *)&(act->avatar).model0x9s[2].field_0xb0,local_80);
  }
  return;
}



// WARNING: Globals starting with '_' overlap smaller symbols at the same address
// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void actorBody::onKickedUp(actorBody *this,int param_2)

{
  Model *pMVar1;
  int iVar2;
  BoneAffineSubresourceEntry *iVar4;
  AffineTransform *pAVar3;
  Skeleton *skeleton;
  Skeleton *extraout_ECX;
  undefined4 extraout_ECX_00;
  undefined4 extraout_ECX_01;
  undefined4 unaff_EBX;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  vec3 local_18;
  undefined4 local_c;
  undefined4 local_8;
  undefined4 local_4;
  actor *actt;
  AffineTransform *av_affine;
  
  runtime::rand = runtime::rand * 0x19660d + 0x3c6ef35f;
  if ((float)(runtime::rand & 0x7fffff | 0x3f800000) - 1.0 <= *(float *)(param_2 + 0x1c)) {
    actt = this->actor;
    iVar4 = ::actor::getModelBoneAffineByBone1(actt,*(undefined2 *)(param_2 + 0x14));
    if (iVar4 != (BoneAffineSubresourceEntry *)0x0) {
      DAT_004e1c5c = 0;
      pMVar1 = (actt->avatar).model;
      if (pMVar1 == (Model *)0x0) {
        skeleton = (Skeleton *)0x0;
      }
      else {
        skeleton = pMVar1->skeleton;
        if (skeleton == (Skeleton *)0x0) {
          skeleton = pMVar1->skeleton2;
        }
      }
      fVar5 = (iVar4->affine).m[0][3];
      fVar6 = (iVar4->affine).m[1][3];
      fVar8 = (iVar4->affine).m[2][3];
      av_affine = &(actt->avatar).drawAffine;
      fVar4 = fVar5;
      fVar7 = fVar6;
      if (-1 < iVar4->bone2) {
        local_18.x = fVar5;
        local_18.y = fVar6;
        local_18.z = fVar8;
        pAVar3 = Skeleton::getBoneAffineIntoGlobal(skeleton,(int)iVar4->bone2);
        fVar4 = pAVar3->m[0][2] * fVar8 + pAVar3->m[0][1] * fVar6 + pAVar3->m[0][0] * fVar5 +
                pAVar3->m[0][3];
        fVar7 = pAVar3->m[1][0] * fVar5 + pAVar3->m[1][2] * fVar8 + pAVar3->m[1][1] * fVar6 +
                pAVar3->m[1][3];
        fVar8 = pAVar3->m[2][0] * fVar5 + pAVar3->m[2][2] * fVar8 + pAVar3->m[2][1] * fVar6 +
                pAVar3->m[2][3];
        skeleton = extraout_ECX;
      }
      local_18.x = fVar4;
      local_18.y = fVar7;
      local_18.z = fVar8;
      if (av_affine != (AffineTransform *)0x0) {
        local_18.x = (actt->avatar).drawAffine.m[0][2] * fVar8 +
                     (actt->avatar).drawAffine.m[0][1] * fVar7 + fVar4 * av_affine->m[0][0] +
                     (actt->avatar).drawAffine.m[0][3];
        local_18.y = (actt->avatar).drawAffine.m[1][0] * fVar4 +
                     (actt->avatar).drawAffine.m[1][2] * fVar8 +
                     (actt->avatar).drawAffine.m[1][1] * fVar7 + (actt->avatar).drawAffine.m[1][3];
        local_18.z = (actt->avatar).drawAffine.m[2][0] * fVar4 +
                     (actt->avatar).drawAffine.m[2][2] * fVar8 +
                     (actt->avatar).drawAffine.m[2][1] * fVar7 + (actt->avatar).drawAffine.m[2][3];
      }
      ::actor::getEulers(&local_c,skeleton,actt,iVar4);
      if (*(int *)(param_2 + 0x20) == 0) {
        _DAT_004e1c88 = (actt->avatar).scale.z;
      }
      else {
        _DAT_004e1c88 = (actt->avatar).scale.x * (actt->avatar).uniformScale;
      }
      someFxPos.x = local_18.x;
      someFxPos.y = local_18.y;
      someFxPos.z = local_18.z;
      _DAT_004e1c6c = local_c;
      DAT_004e1c5c = DAT_004e1c5c | 0x45;
      _DAT_004e1c70 = local_8;
      _DAT_004e1c74 = local_4;
      iVar2 = *(int *)(param_2 + 0x18);
      if (iVar2 == 0) {
        spawnFxForBody_("dust",unaff_EBX,extraout_ECX_00,param_2,this,&local_18,&DAT_004e1c5c);
      }
      else {
        if (iVar2 == 1) {
          spawnFxForBody_("bits",unaff_EBX,this,param_2,this,&local_18,&DAT_004e1c5c);
          return;
        }
                    // Both
        if (iVar2 == 2) {
          spawnFxForBody_("dust",unaff_EBX,&local_18,param_2,this,&local_18,&DAT_004e1c5c);
          spawnFxForBody_("bits",unaff_EBX,extraout_ECX_01,param_2,this,&local_18,&DAT_004e1c5c);
          return;
        }
      }
    }
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void actorBody::onBodyImpactFloor(void)

{
  actor *act;
  int in_EAX;
  char local_80 [128];
  
  act = *(actor **)(in_EAX + 8);
  FUN_0001a0a0("floor");
  if (local_80[0] != '\0') {
    FUN_0012a260(0,act,5,(vec3 *)0x0,(vec3 *)0x0,1.0,
                 (astruct_25 *)&(act->avatar).model0x9s[4].field_0xb0,local_80);
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void actorBody::onBodyImpactWall(void)

{
  actor *act;
  int in_EAX;
  char local_80 [128];
  
  act = *(actor **)(in_EAX + 8);
  FUN_0001a0a0("body");
  if (local_80[0] != '\0') {
    FUN_0012a260(0,act,5,(vec3 *)0x0,(vec3 *)0x0,1.0,
                 (astruct_25 *)&(act->avatar).model0x9s[4].field_0xb0,local_80);
  }
  return;
}




void __fastcall actorBody::onWeaponAttackVolume1(int param_1,int param_2)

{
  int in_EAX;
  
  if (*(int *)(param_1 + 0x48) != 0) {
    if (*(int *)(param_2 + 0x10) == 0) {
      FUN_00144e90();
      return;
    }
    FUN_00144ee0(*(undefined2 *)(in_EAX + 0x10));
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields

void actorBody::onCreateAndAttachProjectile
               (actorBody *param_1,CreateEntityParams *param_2,resource_t param_3)

{
  char cVar1;
  weapon *pwVar2;
  char *pcVar3;
  objParams *params;
  Object *entity;
  int iVar4;
  undefined4 local_88;
  char *local_84;
  asset_name local_80;
  
  if (param_1->someWeapon == (weapon *)0x0) {
    pcVar3 = param_2->assetName;
    if (*(int *)param_2->assetName == 0x5f646961) {
      iVar4 = -(int)pcVar3;
      do {
        cVar1 = *pcVar3;
        pcVar3[(int)(local_80 + iVar4)] = cVar1;
        pcVar3 = pcVar3 + 1;
      } while (cVar1 != '\0');
    }
    else {
      pwVar2 = param_1->weapon;
      local_80._0_4_ = local_80._0_4_ & 0xffffff00;
      if ((pwVar2 != (weapon *)0x0) && (pwVar2->holdableType == Container)) {
        local_84 = local_80;
        local_88 = 0x99;
        (*((pwVar2->avatar).vtable)->onMessage)(pwVar2,&local_88);
      }
    }
    if ((local_80._0_4_ == 0x5f646961) &&
       (params = Assets::GetObjParams(local_80), params != (objParams *)0x0)) {
      *(float *)(params + 4) = (param_1->actor->avatar).scale.z * *(float *)(params + 4);
      entity = (Object *)Assets::CreateEntityFromParams(params);
      free(params);
      if ((entity != (Object *)0x0) && (iVar4 = loadSpecificWeapon(param_1,entity), iVar4 == 0)) {
        Assets::DeleteResource_(entity);
      }
    }
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void actorBody::onCreateAndAttachProjectileToLocator(int param_1)

{
  AffineTransform *pAVar1;
  actor *paVar2;
  Model *pMVar3;
  int in_EAX;
  BoneAffineSubresourceEntry *pBVar4;
  AffineTransform *pAVar5;
  int *piVar6;
  Skeleton *skeleton;
  float fVar7;
  float fVar8;
  float fVar9;
  float fVar10;
  float fVar11;
  float local_28;
  int *local_24;
  float local_20;
  vec3 local_1c;
  float local_10;
  float local_c;
  float local_8;
  float local_4;
  
  paVar2 = *(actor **)(in_EAX + 8);
  pBVar4 = ::actor::getModelBoneAffineByBone1(paVar2,*(undefined2 *)(param_1 + 0x90));
  pMVar3 = (paVar2->avatar).model;
  if (pMVar3 == (Model *)0x0) {
    skeleton = (Skeleton *)0x0;
  }
  else {
    skeleton = pMVar3->skeleton;
    if (skeleton == (Skeleton *)0x0) {
      skeleton = pMVar3->skeleton2;
    }
  }
  fVar8 = (pBVar4->affine).m[0][3];
  fVar9 = (pBVar4->affine).m[1][3];
  fVar11 = (pBVar4->affine).m[2][3];
  pAVar1 = &(paVar2->avatar).drawAffine;
  fVar7 = fVar8;
  fVar10 = fVar9;
  if (-1 < pBVar4->bone2) {
    local_28 = fVar8;
    local_24 = (int *)fVar9;
    local_20 = fVar11;
    pAVar5 = Skeleton::getBoneAffineIntoGlobal(skeleton,(int)pBVar4->bone2);
    fVar7 = pAVar5->m[0][2] * fVar11 + pAVar5->m[0][1] * fVar9 + fVar8 * pAVar5->m[0][0] +
            pAVar5->m[0][3];
    fVar10 = pAVar5->m[1][2] * fVar11 + pAVar5->m[1][0] * fVar8 + pAVar5->m[1][1] * fVar9 +
             pAVar5->m[1][3];
    fVar11 = pAVar5->m[2][2] * fVar11 + pAVar5->m[2][0] * fVar8 + pAVar5->m[2][1] * fVar9 +
             pAVar5->m[2][3];
  }
  local_28 = fVar7;
  local_24 = (int *)fVar10;
  local_20 = fVar11;
  if (pAVar1 != (AffineTransform *)0x0) {
    local_28 = (paVar2->avatar).drawAffine.m[0][2] * fVar11 +
               (paVar2->avatar).drawAffine.m[0][1] * fVar10 + pAVar1->m[0][0] * fVar7 +
               (paVar2->avatar).drawAffine.m[0][3];
    local_24 = (int *)((paVar2->avatar).drawAffine.m[1][2] * fVar11 +
                       (paVar2->avatar).drawAffine.m[1][0] * fVar7 +
                       (paVar2->avatar).drawAffine.m[1][1] * fVar10 +
                      (paVar2->avatar).drawAffine.m[1][3]);
    local_20 = (paVar2->avatar).drawAffine.m[2][2] * fVar11 +
               (paVar2->avatar).drawAffine.m[2][0] * fVar7 +
               (paVar2->avatar).drawAffine.m[2][1] * fVar10 + (paVar2->avatar).drawAffine.m[2][3];
  }
  local_10 = *(float *)(in_EAX + 0x72c);
  local_c = *(float *)(in_EAX + 0x730);
  local_8 = 0.0;
  piVar6 = (int *)FUN_00112c50(0x3f800000);
  if (piVar6 != (int *)0x0) {
    local_1c.x = local_28;
    local_1c.y = (float)local_24;
    local_1c.z = local_20;
    Math::MovePointForwards
              (&local_1c,local_10 * 57.295776 * 0.017453292,local_c * 57.295776 * 0.017453292,30.0);
    local_c = local_1c.x;
    local_8 = local_1c.y;
    piVar6[0x363] = (int)paVar2;
    local_10 = 2.31214e-43;
    local_4 = local_1c.z;
    (**(code **)(*piVar6 + 0xc))(piVar6,&local_10);
    local_28 = 1.33123e-43;
    local_24 = piVar6;
    (*((paVar2->avatar).vtable)->onMessage)(paVar2,&local_28);
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void actorBody::onDeleteWeapon(void)

{
  avatar *paVar1;
  int unaff_EBX;
  int unaff_EDI;
  
  if ((*(int *)(unaff_EBX + 0x10) != 0) && (*(int *)(unaff_EDI + 0x48) != 0)) {
    paVar1 = (avatar *)FUN_0001b4c0(unaff_EDI);
    avatar::destroy(paVar1);
  }
  if ((*(int *)(unaff_EBX + 0x14) != 0) && (*(int *)(unaff_EDI + 0x4c) != 0)) {
    paVar1 = (avatar *)FUN_0001b570();
    avatar::destroy(paVar1);
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void actorBody::onCreateAndAttachWeapon(actorBody *param_1,resource_t param_2,astruct_35 *param_3)

{
  objParams *params;
  weapon *weapon;
  int iVar1;
  
  params = Assets::GetObjParams(param_3->field16_0x10);
  if (params != (objParams *)0x0) {
    weapon = (weapon *)Assets::CreateEntityFromParams(params);
    free(params);
    if ((weapon != (weapon *)0x0) && (iVar1 = FUN_0001b2b0(param_1,0,weapon), iVar1 == 0)) {
      Assets::DeleteResource_(weapon);
      return;
    }
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void actorBody::onWeaponSwing(void)

{
  CalloutDescriptor **ppCVar1;
  actor *act;
  int in_EAX;
  
  act = *(actor **)(in_EAX + 0x48);
  if ((act != (actor *)0x0) &&
     (ppCVar1 = &(act->avatar).callout, ppCVar1 != (CalloutDescriptor **)0x0)) {
    ::actor::executeCalloutInDescriptor
              (*ppCVar1,WeaponSwing,(CalloutCallback *)0x0,0,act,(entityBodyPlayer_0x924)0x0);
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void actorBody::onActorProjectileThrow(int param_1)

{
  avatar *av;
  int in_EAX;
  vec3 local_24;
  vec3 local_18;
  float local_c;
  float local_8;
  float local_4;
  
  av = *(avatar **)(param_1 + 8);
  avatar::getWorldPosition(av,&local_18);
  local_24.z = 0.0;
  local_24.y = 0.0;
  local_24.x = 0.0;
  Math::MovePointForwards
            (&local_24,*(float *)(in_EAX + 0x10),(av->rotEuler).y,*(float *)(in_EAX + 0x14));
  local_c = local_18.x + local_24.x;
  local_8 = local_18.y + local_24.y;
  local_4 = local_18.z + local_24.z;
  FUN_0001b5d0();
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void actorBody::onActorWeaponPlace(void)

{
  int in_EAX;
  int *piVar1;
  undefined4 local_4;
  
  if (*(int *)(in_EAX + 0x48) != 0) {
    piVar1 = FUN_0001b4c0(in_EAX);
    local_4 = 0x9b;
    (**(code **)(*piVar1 + 0xc))(piVar1,&local_4);
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void __fastcall actorBody::onTriggerWeaponCallout(undefined4 param_1,int param_2)

{
  CalloutDescriptor **ppCVar1;
  char cVar2;
  actor *act;
  int in_EAX;
  char *pcVar3;
  uint uVar4;
  avatarCalloutId id;
  
  act = *(actor **)(in_EAX + 0x48);
  if (act != (actor *)0x0) {
    pcVar3 = (char *)(param_2 + 0x10);
    do {
      cVar2 = *pcVar3;
      pcVar3 = pcVar3 + 1;
    } while (cVar2 != '\0');
    if (pcVar3 == (char *)(param_2 + 0x11)) {
      id = Null;
    }
    else {
      uVar4 = Events::GetIndexOfStringInTable(0x55,PTR_ARRAY_00421c98 + 1,(char *)(param_2 + 0x10));
      if (uVar4 == 0xffffffff) {
        id = Null;
      }
      else {
        id = (short)uVar4 + Accept;
      }
    }
    ppCVar1 = &(act->avatar).callout;
    if (ppCVar1 != (CalloutDescriptor **)0x0) {
      ::actor::executeCalloutInDescriptor
                (*ppCVar1,id,(CalloutCallback *)0x0,0,act,(entityBodyPlayer_0x924)0x0);
    }
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void __fastcall actorBody::onTriggerProjectileCallout(undefined4 param_1,int param_2)

{
  CalloutDescriptor **ppCVar1;
  char cVar2;
  actor *act;
  int in_EAX;
  char *pcVar3;
  uint uVar4;
  avatarCalloutId id;
  
  act = *(actor **)(in_EAX + 0x4c);
  if (act != (actor *)0x0) {
    pcVar3 = (char *)(param_2 + 0x10);
    do {
      cVar2 = *pcVar3;
      pcVar3 = pcVar3 + 1;
    } while (cVar2 != '\0');
    if (pcVar3 == (char *)(param_2 + 0x11)) {
      id = Null;
    }
    else {
      uVar4 = Events::GetIndexOfStringInTable(0x55,PTR_ARRAY_00421c98 + 1,(char *)(param_2 + 0x10));
      if (uVar4 == 0xffffffff) {
        id = Null;
      }
      else {
        id = (short)uVar4 + Accept;
      }
    }
    ppCVar1 = &(act->avatar).callout;
    if (ppCVar1 != (CalloutDescriptor **)0x0) {
      ::actor::executeCalloutInDescriptor
                (*ppCVar1,id,(CalloutCallback *)0x0,0,act,(entityBodyPlayer_0x924)0x0);
    }
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


undefined4 actorBody::onAnimEventMessage(Avatar_AnimationEventMessage *msg,actorBody *body)

{
  CreateEntityParams *pCVar1;
  resource_t unaff_EBX;
  
  pCVar1 = (CreateEntityParams *)msg->animEvent;
  switch(*(undefined2 *)&pCVar1->field_0xc) {
  case 2:
    onAttackVolume1();
    return 0;
  case 6:
    onFootDown(pCVar1);
    return 0;
  case 7:
    onInvulnerability();
    return 0;
  case 8:
    onLookAtDisable();
    return 0;
  case 9:
    onVelocityBoost(pCVar1);
    return 0;
  case 10:
    onVelocityBoostToYaw();
    return 0;
  case 0xb:
    onWeaponAttackVolume1();
    return 0;
  case 0xd:
  case 0x3a:
    onSetActorFlag(body,(Message *)msg,(int)pCVar1);
    return 0;
  case 0xe:
    onBodyImpactFloor();
    return 0;
  case 0xf:
    onBodyImpactWall();
    return 0;
  case 0x10:
    onCreateAndAttachProjectile(body,pCVar1,unaff_EBX);
    return 0;
  case 0x12:
    onBreath(msg,pCVar1);
    return 0;
  case 0x14:
    onDeleteWeapon();
    return 0;
  case 0x15:
    onCreateAndAttachWeapon(body,unaff_EBX,(astruct_35 *)pCVar1);
    return 0;
  case 0x17:
    onWeaponSwing();
    return 0;
  case 0x18:
    onInsertFright(pCVar1);
    return 0;
  case 0x19:
    onActorLimbChange(body);
    return 0;
  case 0x1a:
    onActorProjectileThrow(body);
    return 0;
  case 0x1b:
    onActorWeaponPlace();
    return 0;
  case 0x28:
    onKickedUp(body,pCVar1);
    return 0;
  case 0x2b:
    onTriggerWeaponCallout();
    return 0;
  case 0x2c:
    onTriggerProjectileCallout();
    return 0;
  case 0x2d:
    onCreateAndAttachProjectileToLocator(pCVar1);
    return 0;
  case 0x2e:
    disableInput(pCVar1,body);
  }
  return 0;
}




void __fastcall actorBody::onAttackVolume1(int param_1,int param_2)

{
  int in_EAX;
  
  if (*(int *)(param_1 + 0x10) == 0) {
    if (*(int *)(param_2 + 0x2c8) != 0) {
      FUN_0013f420(*(int *)(param_2 + 0x2c8),*(undefined2 *)(in_EAX + 0x10),
                   *(undefined2 *)(in_EAX + 0x12));
      *(undefined4 *)(param_2 + 0x2cc) = 0;
      return;
    }
  }
  else if (*(int *)(param_2 + 0x2c8) != 0) {
    FUN_0013f4d0(*(int *)(param_2 + 0x2c8));
  }
  return;
}




void __fastcall actorBody::onLookAtDisable(int param_1,int param_2)

{
  uint uVar1;
  int in_EAX;
  
  uVar1 = *(uint *)(param_1 + 0x10);
  if (*(int *)(param_2 + 0x10) == 0) {
    if ((uVar1 & 1) != 0) {
      *(char *)(in_EAX + 0x309) = *(char *)(in_EAX + 0x309) + '\x01';
    }
    if ((uVar1 & 2) != 0) {
      *(char *)(in_EAX + 0x30a) = *(char *)(in_EAX + 0x30a) + '\x01';
    }
    if ((uVar1 & 4) != 0) {
      *(char *)(in_EAX + 0x30b) = *(char *)(in_EAX + 0x30b) + '\x01';
    }
    if ((uVar1 & 8) != 0) {
      *(char *)(in_EAX + 0x30c) = *(char *)(in_EAX + 0x30c) + '\x01';
      return;
    }
  }
  else {
    if ((uVar1 & 1) != 0) {
      *(char *)(in_EAX + 0x309) = *(char *)(in_EAX + 0x309) + -1;
    }
    if ((uVar1 & 2) != 0) {
      *(char *)(in_EAX + 0x30a) = *(char *)(in_EAX + 0x30a) + -1;
    }
    if ((uVar1 & 4) != 0) {
      *(char *)(in_EAX + 0x30b) = *(char *)(in_EAX + 0x30b) + -1;
    }
    if ((uVar1 & 8) != 0) {
      *(char *)(in_EAX + 0x30c) = *(char *)(in_EAX + 0x30c) + -1;
    }
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void __fastcall actorBody::onInvulnerability(void *param_1,int param_2)

{
  int in_EAX;
  
  if (*(int *)(param_2 + 0x10) == 0) {
    FUN_0001f3f0(*(undefined4 *)(in_EAX + 0x10));
    return;
  }
  flipFlags(param_1,(byte)*(undefined4 *)(in_EAX + 0x10));
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void actorBody::onSetActorFlag(actorBody *param_1,Message *param_2,int param_3)

{
  actorBodyFlags *paVar1;
  unkfloat1 Var2;
  uint flagIndex;
  byte *pbVar3;
  float fVar4;
  undefined4 extraout_EAX;
  
  fVar4 = (float)getFlagIdByName((char *)(param_3 + 0x10));
  Var2 = (unkfloat1)fVar4;
  flagIndex = CONCAT31((int3)((uint)extraout_EAX >> 8),Var2);
  paVar1 = param_1->flagSet->flags;
  if (param_2[2].header.msgId == Null) {
    pbVar3 = (byte *)((int)&paVar1->flag1 + (flagIndex >> 3));
    *pbVar3 = *pbVar3 | '\x01' << ((byte)Var2 & 7);
    return;
  }
  flagIndex = flagIndex >> 3;
  *(byte *)((int)&paVar1->flag1 + flagIndex) =
       *(byte *)((int)&paVar1->flag1 + flagIndex) & ~('\x01' << ((byte)Var2 & 7));
  return;
}



// WARNING: Globals starting with '_' overlap smaller symbols at the same address
// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void actorBody::onBreath(int param_1,int param_2)

{
  byte *pbVar1;
  actor *paVar2;
  short sVar3;
  int in_EAX;
  BoneAffineSubresourceEntry *subres;
  int iVar4;
  Skeleton *skeleton;
  float fVar5;
  float local_18;
  float local_14;
  float local_10;
  undefined4 local_c;
  undefined4 local_8;
  undefined4 local_4;
  
  if ((*(int *)(param_1 + 0x10) == 0) &&
     ((((byte)DAT_0050ea98 & 1) != 0 ||
      ((*(byte *)(*(int *)(*(int *)(in_EAX + 0x15c) + 8) + 1) & 0x40) != 0)))) {
    paVar2 = *(actor **)(in_EAX + 8);
    subres = ::actor::getModelBoneAffineByBone1(paVar2,5);
    if (subres != (BoneAffineSubresourceEntry *)0x0) {
      _DAT_0050690c = 1;
      int32_t_00506914._0_2_ = 5;
      fxAvatar = &paVar2->avatar;
      FUN_00040a60(subres);
      ::actor::getEulers(&local_c,skeleton,paVar2,subres);
      someFxPos.x = local_18;
      someFxPos.y = local_14;
      someFxPos.z = local_10;
      _DAT_004e1c6c = local_c;
      _DAT_004e1c70 = local_8;
      _DAT_004e1c74 = local_4;
      _DAT_004e1c8c = &DAT_0050690c;
      DAT_004e1c5c = 0xd;
      iVar4 = spawnFxAndAID("aid_fxemitter_ghoulies_actor_common_breath",&DAT_004e1c5c);
      if (iVar4 != 0) {
        sVar3 = (short)int32_t_0042a434;
        int32_t_0042a434 = -1;
        if (sVar3 != -1) {
          iVar4 = (&DAT_00506930)[sVar3];
          pbVar1 = (byte *)(iVar4 + 0x18);
          *pbVar1 = *pbVar1 | 8;
          fVar5 = *(float *)(param_2 + 8);
          if (fVar5 != 0.0) {
            FUN_0003b1d0(*(int *)(param_1 + 8),paVar2);
            *(float *)(iVar4 + 0x10) = fVar5 * (*(float *)(param_2 + 8) - *(float *)(param_2 + 4));
          }
        }
      }
    }
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void __thiscall actorBody::onInsertFright(int param_1,int param_2)

{
  undefined1 local_10 [8];
  undefined4 local_8;
  undefined4 local_4;
  
  local_10._4_4_ = (actor *)0x0;
  local_8 = 0;
  local_4 = 0;
  local_10._0_4_ = Actor_Fright;
  avatar::getWorldPosition(*(avatar **)(param_1 + 8),(vec3 *)(local_10 + 4));
  ScareActorsWithinScareRadius
            (*(undefined4 *)(param_2 + 0x10),(Message *)local_10,(vec3 *)(local_10 + 4));
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void __fastcall actorBody::onActorLimbChange(actorBody *param_1)

{
  CalloutDescriptor **ppCVar1;
  int in_EAX;
  
  if (*(char *)(in_EAX + 0x10) != '\0') {
    FUN_000250e0();
    return;
  }
  param_1->field_0x2d2 = 1;
  ppCVar1 = &(param_1->actor->avatar).callout;
  if (ppCVar1 != (CalloutDescriptor **)0x0) {
    ::actor::executeCalloutInDescriptor
              (*ppCVar1,LimbLoss,CalloutCallback1,0,param_1->actor,
               (entityBodyPlayer_0x924)&param_1->field_0x2d8);
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void actorBody::disableInput(int param_1,actorBody *param_2)

{
  float fVar1;
  
  runtime::rand = runtime::rand * 0x19660d + 0x3c6ef35f;
  fVar1 = (*(float *)(param_1 + 0x14) - *(float *)(param_1 + 0x10)) *
          ((float)(runtime::rand & 0x7fffff | 0x3f800000) - 1.0) + *(float *)(param_1 + 0x10);
  if (param_2->someTimer2 <= fVar1) {
    param_2->someTimer2 = fVar1;
    return;
  }
  param_2->someTimer2 = param_2->someTimer2;
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void actorBody::removeWeapon_(weapon *param_1,actorBody *param_2)

{
  if (param_2->currentWeapon == param_1) {
    param_2->currentWeapon = (weapon *)0x0;
  }
  if ((weapon *)param_2->largeProjectile == param_1) {
    param_2->largeProjectile = (WeaponProjectilesContext *)0x0;
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


AnimEventMapping * actorBody::setAnimation(actorBody *body,char *animationName)

{
  actor *act;
  AnimEventMapping *anim_event;
  undefined1 *pcVar3;
  bodyCollisionProfile *pbVar1;
  
  pbVar1 = (bodyCollisionProfile *)body->weapon;
  if (((pbVar1 == (bodyCollisionProfile *)0x0) ||
      (pcVar3 = &pbVar1->field3501_0xdb0, pcVar3 == (undefined1 *)0x0)) || (*pcVar3 == '\0')) {
    pcVar3 = (undefined1 *)0x0;
  }
  act = body->actor;
  if ((act->avatar).animTable != (AnimtableResource *)0x0) {
    anim_event = avatar::getAnimEventByName(&act->avatar,animationName,(BOOL)pcVar3);
    if (anim_event != (AnimEventMapping *)0x0) {
LAB_0001af78:
      avatar::activateAnimation(&act->avatar,anim_event);
      sendSyncAnimationMessage(body);
      return anim_event;
    }
    if (pcVar3 != (undefined1 *)0x0) {
      anim_event = avatar::getAnimEventByName(&act->avatar,animationName,0);
      if (anim_event != (AnimEventMapping *)0x0) goto LAB_0001af78;
    }
  }
  sendSyncAnimationMessage(body);
  return (AnimEventMapping *)0x0;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void actorBody::sendSyncAnimationMessage(actorBody *body)

{
  undefined4 local_14;
  actor *act;
  uint32_t local_c;
  undefined4 local_8;
  float local_4;
  AnimInstance *allocd;
  KFCAnimation *channel;
  KeyframeContext *kfc;
  WeaponProjectilesContext *largeProjectile;
  weapon *wpn;
  
  wpn = body->currentWeapon;
  largeProjectile = body->largeProjectile;
  if ((wpn != (weapon *)0x0) || (largeProjectile != (WeaponProjectilesContext *)0x0)) {
    act = body->actor;
    kfc = (act->avatar).keyframeContext;
    if ((kfc == (KeyframeContext *)0x0) ||
       (allocd = kfc->kfcAnims->animInstance, allocd == (AnimInstance *)0x0)) {
      local_4 = 0.0;
    }
    else {
      local_4 = allocd->t;
    }
    local_14 = 0x28;
    kfc = (act->avatar).keyframeContext;
    if ((kfc == (KeyframeContext *)0x0) ||
       (channel = kfc->kfcAnims, channel->animInstance == (AnimInstance *)0x0)) {
      local_c = 0;
    }
    else {
      local_c = channel->someValue5;
    }
    local_8 = 0;
    if (wpn != (weapon *)0x0) {
      (*((wpn->avatar).vtable)->onMessage)(wpn,&local_14);
    }
    if (largeProjectile != (WeaponProjectilesContext *)0x0) {
                    // entityWeaponProjectileLarge::onMessage
      (**(code **)(*(int *)largeProjectile + 0xc))(largeProjectile,&local_14);
    }
  }
  return;
}




HoldableType actorBody::getHoldableType(actorBody *param_1)

{
  if (param_1->weapon != (weapon *)0x0) {
    return param_1->weapon->holdableType;
  }
  return 0;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


uint32_t actorBody::getSomeWeaponThing(actorBody *this)

{
  uint32_t uVar1;
  
  if (this->weapon != (weapon *)0x0) {
    uVar1 = ::weapon::getAttribute((this->actor->avatar).tag,this->weapon);
    return uVar1;
  }
  return 0;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


undefined4 actorBody::loadSpecificWeapon(actorBody *body,weapon *wpn)

{
  actor *act;
  int iVar1;
  AvatarPhysicsContext *pAVar2;
  void *this;
  objTag *poVar3;
  bool someFlag;
  
  act = body->actor;
  iVar1 = 0;
  if (0 < wpn->numHitboxes) {
    poVar3 = (objTag *)&wpn->field_0x948;
    while (*poVar3 != (act->avatar).tag) {
      iVar1 = iVar1 + 1;
      poVar3 = poVar3 + 8;
      if (wpn->numHitboxes <= iVar1) {
        return 0;
      }
    }
    if (iVar1 != -1) {
      body->someWeapon = wpn;
      body->largeProjectile = (WeaponProjectilesContext *)wpn;
      iVar1 = 0;
      poVar3 = (objTag *)&wpn->field_0x948;
                    // Searches for a specific weapon then uses it later?
      if (0 < wpn->numHitboxes) {
        do {
          if (*poVar3 == (act->avatar).tag) {
            if (poVar3[1] != ~Null) {
              someFlag = true;
              this = (void *)getWeaponWieldType_(act,wpn);
              CheckWeaponAgainstActorModel(this,someFlag,wpn,act);
              goto LAB_0001b46a;
            }
            break;
          }
          poVar3 = poVar3 + 8;
          iVar1 = iVar1 + 1;
        } while (iVar1 < wpn->numHitboxes);
      }
      pAVar2 = avatar::getOrCreatePhysicsCtx(&wpn->avatar);
      if (pAVar2 != (AvatarPhysicsContext *)0x0) {
        pAVar2 = (wpn->avatar).physicsCtx;
        pAVar2->mode2 = '\x01';
        pAVar2->actor = act;
        pAVar2->someFlag = true;
      }
LAB_0001b46a:
      FUN_001461c0();
      sendSyncAnimationMessage(body);
      avatar::onScenePrepare(wpn);
      FUN_0001b7c0();
      return 1;
    }
  }
  return 0;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


uint actorBody::initialiseAttackData(actorBody *body)

{
  ushort uVar1;
  uint uVar2;
  uint i;
  Attack *next;
  Attack *attack;
  
  attack = body->attackDataRes;
  uVar2 = 0;
  if (attack != (Attack *)0x0) {
    if (attack->numEntries != 0) {
      uVar2 = (uint)attack->numEntries;
    }
    uVar1 = attack->maxSmth;
    if ((uVar1 != 0) && (uVar2 <= uVar1)) {
      uVar2 = (uint)uVar1;
    }
    if ((body->attacks != (ushort *)0x0) && (i = (uint)(byte)body->field_0x68, i != 0)) {
      next = (Attack *)(body->attacks + 1);
      do {
        if (uVar2 <= *(ushort *)&next->entries) {
          uVar2 = (uint)*(ushort *)&next->entries;
        }
        next = next + 1;
        i = i - 1;
      } while (i != 0);
    }
  }
  return uVar2;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void actorBody::initAttackType3(actorBody *body)

{
  AttackData *pAVar1;
  byte bVar2;
  actorBodyStateId *paVar3;
  ushort *puVar4;
  AttackDataListOfAttacks *linked_list;
  int iVar5;
  uint malloc_size;
  AttackEntry *pAVar6;
  int iVar7;
  int iVar8;
  AttackEntry *pAVar9;
  uint i;
  int someAsset;
  int local_8;
  Attack *res;
  
  puVar4 = (ushort *)
           GetValueFromLoadedAttackDataResources
                     ((AttackDataResource *)body->attackDataRes,&someAsset);
  body->attacks = puVar4;
  if (puVar4 != (ushort *)0x0) {
    body->field_0x68 = (undefined1)someAsset;
    return;
  }
  res = body->attackDataRes;
  iVar5 = *(int *)&res[1].numEntries;
  pAVar9 = res[2].entries;
  paVar3 = &pAVar9->id;
  linked_list = malloc_(0x30);
  linked_list->head = (ushort *)&linked_list->values;
  linked_list->tail = (ushort *)&linked_list->values;
  linked_list->valueSize = 4;
  linked_list->capacity = 8;
  linked_list->end = &linked_list[1].valueSize;
  malloc_size = 0;
                    // Forcing a skip prevents player from acting, but not ghoulies
  while (i = 0, pAVar6 = pAVar9, pAVar9->id != Null) {
    do {
      if ((AttackEntry *)(paVar3 + iVar5) <= pAVar6) break;
      pAVar6 = (AttackEntry *)&pAVar6->field_0x2;
      i = i + 1;
    } while (*(short *)pAVar6 != 0);
    if (i == 0) break;
    pAVar9 = (AttackEntry *)(&pAVar9->field_0x2 + i * 2);
    linked_list = (AttackDataListOfAttacks *)FUN_0001c400(i,linked_list);
    if ((int)malloc_size < (int)i) {
      malloc_size = i;
    }
  }
  if (malloc_size == 0) {
    free(linked_list);
    return;
  }
  iVar5 = ((int)linked_list->tail - (int)linked_list->head) / (int)(uint)linked_list->valueSize;
  someAsset = iVar5;
  malloc_size = FUN_0001c490();
  puVar4 = malloc_(malloc_size);
  body->attacks = puVar4;
  body->field_0x68 = (char)iVar5;
  FUN_0001c4c0();
  free(linked_list);
  local_8 = 0;
  if (0 < iVar5) {
    do {
      pAVar9 = res[2].entries;
      iVar5 = *(int *)&res[1].numEntries;
      paVar3 = &pAVar9->id;
      puVar4 = body->attacks + local_8 * 4;
      for (; malloc_size = 0, pAVar6 = pAVar9, pAVar9->id != Null;
          pAVar9 = (AttackEntry *)(&pAVar9->field_0x2 + malloc_size * 2)) {
        do {
          if ((AttackEntry *)(paVar3 + iVar5) <= pAVar6) break;
          pAVar6 = (AttackEntry *)&pAVar6->field_0x2;
          malloc_size = malloc_size + 1;
        } while (*(short *)pAVar6 != 0);
        if (malloc_size == 0) break;
        i = (uint)*puVar4;
        if (malloc_size == i) {
          iVar8 = 0;
          if (i != 0) {
            iVar7 = puVar4[1] * i * 4;
            pAVar6 = pAVar9;
            do {
              *(AttackEntry **)(iVar7 + *(int *)(puVar4 + 2)) = pAVar6;
              iVar8 = iVar8 + 1;
              iVar7 = iVar7 + 4;
              pAVar6 = (AttackEntry *)&pAVar6->field_0x2;
            } while (iVar8 < (int)(uint)*puVar4);
          }
          puVar4[1] = puVar4[1] + 1;
        }
      }
      local_8 = local_8 + 1;
    } while (local_8 < someAsset);
  }
  iVar5 = g_numAttackData;
  bVar2 = body->field_0x68;
  puVar4 = body->attacks;
  iVar8 = g_numAttackData * 0x10;
  pAVar1 = g_attackDataLookup + g_numAttackData;
  g_numAttackData = g_numAttackData + 1;
  pAVar1->attackDataRes = (AttackDataResource *)body->attackDataRes;
  g_attackDataLookup[iVar5].field1_0x4 = (uint)puVar4;
  *(uint *)(&DAT_004dd558 + iVar8) = (uint)bVar2;
  *(undefined4 *)(&DAT_004dd554 + iVar8) = 1;
  return;
}




bool actorBody::checkWeaponHasAttackEntry(actorBody *param_1,AttackEntry *entry)

{
  weapon *pwVar1;
  uint32_t uVar2;
  uint32_t uVar3;
  uint uVar4;
  
  pwVar1 = param_1->someWeapon;
  if (pwVar1 == (weapon *)0x0) {
    pwVar1 = param_1->weapon;
    if (pwVar1 == (weapon *)0x0) {
      uVar3 = 0;
      uVar4 = 0;
    }
    else {
      uVar3 = ::weapon::getAttribute((param_1->actor->avatar).tag,pwVar1);
      uVar4 = (uint)pwVar1->holdableType;
    }
  }
  else {
    uVar3 = ::weapon::getAttribute((param_1->actor->avatar).tag,pwVar1);
    uVar4 = (uint)pwVar1->holdableType;
  }
  uVar2._0_2_ = entry->field27_0x24;
  uVar2._2_2_ = entry->holdableType;
  if ((uVar2 != 0) && (uVar2 != uVar3)) {
    return false;
  }
  return *(uint *)(entry + 1) == uVar4;
}




AttackEntry * actorBody::getGunAttackFromStateId(actorBody *this,actorBodyStateId id)

{
  actorBodyStateId aVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  Attack *attack_data;
  
  if ((((this->weapon != (weapon *)0x0) && (this->weapon->holdableType == Gun)) &&
      (attack_data = this->attackDataRes, attack_data != (Attack *)0x0)) &&
     (attack_data[5].entries != (AttackEntry *)0x0)) {
    iVar3 = attack_data[4].numEntries - 1;
    iVar4 = 0;
    if (-1 < iVar3) {
      do {
        iVar2 = iVar4 + iVar3 >> 1;
        aVar1 = (&(attack_data[5].entries)->id)[iVar2 * 0x12];
        if (aVar1 < id) {
          iVar4 = iVar2 + 1;
        }
        else {
          if (aVar1 <= id) {
            return (AttackEntry *)(&(attack_data[5].entries)->id + iVar2 * 0x12);
          }
          iVar3 = iVar2 + -1;
        }
      } while (iVar4 <= iVar3);
    }
    return (AttackEntry *)0x0;
  }
  return (AttackEntry *)0x0;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields

int FUN_0001c9a0(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                undefined4 param_5)

{
  int iVar1;
  weapon *wpn;
  int iVar2;
  byte *pbVar3;
  int iVar4;
  ushort uVar5;
  uint uVar6;
  uint uVar7;
  undefined4 *puVar8;
  uint uVar9;
  int local_18;
  int local_14;
  uint32_t local_c;
  
  iVar4 = param_1;
  iVar1 = *(int *)(param_1 + 0x5c);
  wpn = *(weapon **)(param_1 + 0x48);
  if (wpn == (weapon *)0x0) {
    local_c = 0;
    uVar5 = 0;
  }
  else {
    local_c = weapon::getAttribute(*(ushort *)(*(int *)(param_1 + 8) + 6),wpn);
    uVar5 = (ushort)wpn->holdableType;
  }
  iVar4 = *(int *)(iVar4 + 0x60);
  uVar7 = *(uint *)(iVar4 + 4);
  puVar8 = *(undefined4 **)(iVar4 + 8);
  for (uVar6 = uVar7 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
    *puVar8 = 0;
    puVar8 = puVar8 + 1;
  }
  for (uVar7 = uVar7 & 3; uVar7 != 0; uVar7 = uVar7 - 1) {
    *(undefined1 *)puVar8 = 0;
    puVar8 = (undefined4 *)((int)puVar8 + 1);
  }
  uVar6 = *(uint *)(iVar1 + 0x18);
  local_18 = 0;
  local_14 = 0;
  uVar7 = uVar6 + (uint)*(ushort *)(iVar1 + 0x14) * 0x28;
  uVar9 = 0;
  if (uVar6 < uVar7) {
    do {
      if (((*(ushort *)(uVar6 + 0x24) == local_c) && (*(ushort *)(uVar6 + 0x26) == uVar5)) &&
         (iVar2 = FUN_0001ba20(param_2,param_3,param_5), iVar2 != 0)) {
        if ((*(byte *)(uVar6 + 0x20) & 0x10) != 0) {
          local_18 = local_18 + 1;
        }
        local_14 = local_14 + 1;
        pbVar3 = (byte *)((uVar9 >> 3) + *(int *)(iVar4 + 8));
        *pbVar3 = *pbVar3 | '\x01' << ((byte)uVar9 & 7);
      }
      uVar6 = uVar6 + 0x28;
      uVar9 = uVar9 + 1;
    } while (uVar6 < uVar7);
    if ((local_18 != 0) && (local_18 < local_14)) {
      uVar9 = 0;
      for (uVar6 = *(uint *)(iVar1 + 0x18); uVar6 < uVar7; uVar6 = uVar6 + 0x28) {
        if ((*(byte *)(uVar6 + 0x20) & 0x10) != 0) {
          pbVar3 = (byte *)((uVar9 >> 3) + *(int *)(iVar4 + 8));
          *pbVar3 = *pbVar3 & ~('\x01' << ((byte)uVar9 & 7));
        }
        uVar9 = uVar9 + 1;
      }
    }
  }
  iVar4 = FUN_000661c0(&param_1);
  if (iVar4 == 0) {
    return 0;
  }
  return *(int *)(iVar1 + 0x18) + param_1 * 0x28;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


AttackEntry * actorBody::getAttackEntryFromBodyFields(actorBody *body,actorBodyStateId param_2)

{
  actorBodyStateId aVar1;
  float fVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  
  iVar4 = *(ushort *)&body->largeProjectile - 1;
  iVar5 = 0;
  if (-1 < iVar4) {
    fVar2 = (body->worldPosition).x;
    do {
      iVar3 = iVar5 + iVar4 >> 1;
      aVar1 = *(actorBodyStateId *)((int)fVar2 + iVar3 * 0x28);
      if (aVar1 < param_2) {
        iVar5 = iVar3 + 1;
      }
      else {
        if (aVar1 <= param_2) {
          return (AttackEntry *)((int)fVar2 + iVar3 * 0x28);
        }
        iVar4 = iVar3 + -1;
      }
    } while (iVar5 <= iVar4);
  }
  return (AttackEntry *)0x0;
}



// WARNING: Removing unreachable block (ram,0x0001cb78)
// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void actorBody::loadAttackDataResource(actorBody *body,actorBodyParams *params)

{
  uint uVar1;
  AttackInstance *pAVar2;
  uint rawSize;
  Attack *res;
  Attack *attack_data;
  
  if (*(int *)params->attackDataAID == 0x5f646961) {
    Assets::GetResourceBytes(params->attackDataAID,&res);
    if (res == (Attack *)0x0) {
      runtime::ExitGame(2);
    }
    body->attackDataRes = res;
  }
  if ((body->attackDataRes != (Attack *)0x0) &&
     (body->attackDataRes[2].entries != (AttackEntry *)0x0)) {
    initAttackType3(body);
  }
  attack_data = body->attackDataRes;
  if ((attack_data != (Attack *)0x0) && (attack_data != (Attack *)0x0)) {
    uVar1 = initialiseAttackData(body);
    rawSize = 0;
    if (-1 < (int)uVar1) {
      rawSize = uVar1;
    }
    if ((int)rawSize <= (int)(uint)attack_data[3].numEntries) {
      rawSize = (uint)attack_data[3].numEntries;
    }
    if ((int)rawSize <= (int)(uint)attack_data[4].numEntries) {
      rawSize = (uint)attack_data[4].numEntries;
    }
    if ((int)rawSize <= (int)(uint)attack_data[2].numEntries) {
      rawSize = (uint)attack_data[2].numEntries;
    }
    if (rawSize != 0) {
      pAVar2 = AttackInstance::ctor(rawSize);
      body->attackInstance = pAVar2;
    }
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


BOOL actorBody::canAttack(actorBody *param_1)

{
  actorBodyFlags *paVar1;
  BOOL BVar2;
  
  if (((param_1->field_0x6b == '\0') &&
      ((((param_1->field_0x6a == '\0' || (param_1->field_0x6c != '\0')) &&
        (param_1->noAttackTimer <= 0.0)) &&
       ((param_1->field13_0x30 == 0 && (param_1->someTimer2 == 0.0)))))) &&
     (paVar1 = param_1->flagSet->flags, (paVar1->flag1 & 0x8000000) == Null)) {
    BVar2 = flagIsSet(param_1,IsScared);
    if (BVar2 == 0) {
      BVar2 = flagIsSet(param_1,IsPickingUp);
      if ((BVar2 == 0) &&
         ((param_1->actor->field827_0xcde != 0 || ((paVar1->attackFlags_ & 0x200) != Null)))) {
        return 1;
      }
    }
  }
  return 0;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


BOOL actorBody::findAndUseAttack(actorBody *body,actorBodyStateId id)

{
  AttackDataResource *pAVar1;
  actorBody *body_01;
  undefined1 uVar2;
  bool bVar3;
  AttackEntry *attack_entry;
  uint32_t uVar4;
  undefined3 extraout_var;
  undefined3 extraout_var_00;
  AttackDataResource *body_00;
  
  pAVar1 = (AttackDataResource *)body->attackDataRes;
  if (pAVar1 != (AttackDataResource *)0x0) {
    if ((pAVar1->attack1).entries != (AttackEntry *)0x0) {
      attack_entry = AttackDataResource::getAttackByStateId(pAVar1,id);
      if (attack_entry != (AttackEntry *)0x0) goto LAB_0001d2bc;
    }
    if ((pAVar1->attack2).entries != (AttackEntry *)0x0) {
      attack_entry = (AttackEntry *)FUN_0001c5a0();
      if (attack_entry != (AttackEntry *)0x0) goto LAB_0001d2bc;
    }
  }
  body_01 = (actorBody *)body->attackDataRes;
  if ((body_01 != (actorBody *)0x0) && ((body_01->worldPosition).x != 0.0)) {
    attack_entry = getAttackEntryFromBodyFields(body_01,id);
    if (attack_entry != (AttackEntry *)0x0) {
      uVar4 = getSomeWeaponThing(body);
      if (uVar4 == attack_entry->field27_0x24) {
        uVar2 = getHoldableType(body);
        if (CONCAT31(extraout_var,uVar2) == (uint)attack_entry->holdableType) goto LAB_0001d29c;
      }
    }
  }
  pAVar1 = (AttackDataResource *)body->attackDataRes;
  if ((pAVar1 != (AttackDataResource *)0x0) &&
     ((pAVar1->weaponAttacks).entries != (AttackEntry *)0x0)) {
    attack_entry = AttackDataResource::getAttack4ById(pAVar1,id);
    if (attack_entry != (AttackEntry *)0x0) {
      bVar3 = checkWeaponHasAttackEntry(body,attack_entry);
      if (CONCAT31(extraout_var_00,bVar3) != 0) {
LAB_0001d29c:
        useAttack(body,attack_entry,0);
        return 1;
      }
    }
  }
                    // Check for gun attack
  attack_entry = getGunAttackFromStateId(body,id);
  if (attack_entry == (AttackEntry *)0x0) {
    return 0;
  }
LAB_0001d2bc:
  useAttack(body,attack_entry,0);
  return 1;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields
// Called by 0x1368a3


BOOL actorBody::useAttack(actorBody *this,AttackEntry *attackEntry,undefined4 param_3)

{
  AttackEntry *pAVar1;
  StatetableEntry *state_entry;
  
  pAVar1 = attackEntry;
  this->currentAttackEntry = attackEntry;
  *(undefined4 *)&this->useAttackParam3 = param_3;
  if ((attackEntry->id != Null) && (this->statetableRes != (StatetableResource *)0x0)) {
    state_entry = binarySearchStateTable(this->statetableRes,(Asset **)&attackEntry,attackEntry->id)
    ;
    if (state_entry != (StatetableEntry *)0x0) {
      updateStatesFromEntry(this,attackEntry,state_entry);
      *(undefined4 *)&this->useAttackParam3 = param_3;
      this->currentAttackEntry = pAVar1;
      return 1;
    }
  }
  *(undefined4 *)&this->useAttackParam3 = param_3;
  this->currentAttackEntry = pAVar1;
  return 0;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void actorBody::initAttackData(actorBody *body,actorBodyParams *params)

{
  int i;
  
  loadAttackDataResource(body,params);
  (body->v4).x = (params->someV).x;
  (body->v4).y = (params->someV).y;
  (body->v4).z = (params->someV).z;
  body->field44_0x6e = params->field11_0x1a4;
  i = 0;
  if (0 < Game::NumFrozenAttackTimers) {
    while ((body->actor->avatar).tag != Game::FrozenAttackTimers[i].someU16) {
      i = i + 1;
      if (Game::NumFrozenAttackTimers <= i) {
        return;
      }
    }
    body->noAttackTimer = Game::FrozenAttackTimers[i].timer;
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


BOOL actorBody::setWaitUntilCanAttack(actorBody *this,int param_2)

{
  BOOL BVar1;
  
  if (((this->field_0x6b == '\0') &&
      (((this->field_0x6a == '\0' || ((param_2 != 0 && (this->field_0x6c != '\0')))) &&
       (this->noAttackTimer <= 0.0)))) &&
     (((this->field13_0x30 == 0 && (this->someTimer2 == 0.0)) &&
      ((this->flagSet->flags->flag1 & 0x8000000) == Null)))) {
    BVar1 = flagIsSet(this,IsScared);
    if (BVar1 == 0) {
      BVar1 = flagIsSet(this,IsPickingUp);
      return (uint)(BVar1 == 0);
    }
  }
  return 0;
}




Actor0x68 * actorBody::handleLockOn(actorBody *param_1)

{
  actor *av;
  Actor0x68 *new_0x68;
  vec3 local_2c;
  SomeActorList uStack_20;
  
  av = param_1->actor;
  avatar::getWorldPosition(&av->avatar,&local_2c);
  uStack_20.field6_0x14 = (param_1->actor->avatar).scale.y * param_1->cameraOffsetVertical;
  uStack_20.pos.x = local_2c.x;
  uStack_20.pos.y = local_2c.y;
  uStack_20.pos.z = local_2c.z;
  uStack_20.field5_0x10 = 0;
  uStack_20.field0_0x0 = '\x04';
  uStack_20.field1_0x1 = ' ';
  uStack_20.field2_0x2 = '\x01';
  new_0x68 = ::actor::createActor0x68
                       (av,0,(char)av->backgroundCollisionIndex,param_1->field44_0x6e,&uStack_20);
  return new_0x68;
}




void actorBody::getAllocDetails(ObjectAllocDetails *param_1)

{
  param_1->entitySize = 0x894;
  param_1->paramsSize = 0x7c8;
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


actorBodyVTable * actorBody::getVTable(void)

{
  actorBodyVTable *extraout_EAX;
  
  makeActorBodyVTable(&g_actorBodyVTable);
  return extraout_EAX;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void actorBody::makeActorBodyVTable(actorBodyVTable *table)

{
  table->getAllocDetails = getAllocDetails;
  table->ctor = ctor;
  table->dtor = dtor;
  table->onMessage = onMessage;
  table->update = update;
  table->updateMovement = updateMovement;
  table->updatePosAndRot = updatePosAndRot;
  table->computeMovementAndCollisions = obj::returnOne;
  table->getStandingState = getStandingState;
  table->getNervousState = getNervousState;
  table->getIdleState = getIdleState;
  table->getWalkState = getWalkState;
  table->getStunnedState = getStunnedState;
  table->getDizzyState = getDizzyState;
  table->getCheerState = getCheerState;
  table->getCringeState = getCringeState;
  table->getShuffleState = getShuffleState;
  table->getFrightState = getFrightState;
  table->getScareState = getScareState;
  table->getKnockDownState = getKnockDownState;
  table->getDroneState = getDroneState;
  table->getDroneCheerState = getDroneCheerState;
  table->getBurstFromWallState = getBurstFromWallState;
  table->getPickupState = getPickupState;
  return;
}



// WARNING: Unable to use type for symbol tex
// WARNING: Unable to use type for symbol pRVar1
// WARNING: Unable to use type for symbol pRVar2
// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void actorBody::initHealth(actorBody *body,actorBodyParams *params)

{
  actorBodyParams *paVar1;
  float final_health;
  float min_health;
  uint64_t health;
  actorBodyParams *tex;
  actorBodyParams *pRVar1;
  actorBodyParams *pRVar2;
  ushort i;
  
  i = body->actor->statsheetIndex;
  final_health = Game::HealthMetadata[1].maxHealth;
  if (i != 0) {
    min_health = (float)Game::HealthMetadata[1].minHealthU8;
    if ((float)Game::HealthMetadata[1].maxHealthU8 != min_health) {
                    // Get health based on stat sheet???
      min_health = (((float)Assets::GhouliesStatsheet[i - 1].health - min_health) /
                   ((float)Game::HealthMetadata[1].maxHealthU8 - min_health)) *
                   (Game::HealthMetadata[1].maxHealth - Game::HealthMetadata[1].minHealth) +
                   Game::HealthMetadata[1].minHealth;
      if (Game::HealthMetadata[1].maxHealth <= Game::HealthMetadata[1].minHealth) {
        if ((Game::HealthMetadata[1].maxHealth <= min_health) &&
           (final_health = min_health, Game::HealthMetadata[1].minHealth < min_health)) {
          final_health = Game::HealthMetadata[1].minHealth;
        }
      }
      else if ((min_health <= Game::HealthMetadata[1].maxHealth) &&
              (final_health = min_health, min_health < Game::HealthMetadata[1].minHealth)) {
        final_health = Game::HealthMetadata[1].minHealth;
      }
    }
  }
  health = float10::to_uint64_t((float10)final_health);
  body->health = (ushort)health;
  body->maxHealth = (ushort)health;
  body->field_0xa4 = 0;
  body->someHealthValue = params->someHealthValue;
  Assets::GetResourceBytes("aid_texture_ghoulies_scoreboard_energy_baddielowenergy",&params);
  pRVar2 = params;
  if (params == (actorBodyParams *)0x0) {
    runtime::ExitGame(2);
  }
  body->lowEnergyTexture = (TextureDescriptor *)pRVar2;
  Assets::GetResourceBytes("aid_texture_ghoulies_scoreboard_energy_traitorenergy",&params);
  pRVar1 = params;
  if (params == (actorBodyParams *)0x0) {
    runtime::ExitGame(2);
  }
  body->traitorEnergyTexture = (TextureDescriptor *)pRVar1;
  Assets::GetResourceBytes("aid_texture_ghoulies_scoreboard_energy_traitoralt",&params);
  paVar1 = params;
  if (params == (actorBodyParams *)0x0) {
    runtime::ExitGame(2);
  }
  body->traitorAltEnergyTexture = (TextureDescriptor *)paVar1;
  Assets::GetResourceBytes("aid_texture_ghoulies_scoreboard_pauseicons_clock",&params);
  tex = params;
  if (params == (actorBodyParams *)0x0) {
    runtime::ExitGame(2);
  }
  body->pauseIconsClockTexture = (TextureDescriptor *)tex;
  return;
}




void actorBody::updateExpressionFromHealth(actorBody *this)

{
  actor *act;
  BOOL BVar1;
  int extraout_EDX;
  int extraout_EDX_00;
  float fVar2;
  uint64_t uVar3;
  float local_4;
  
  act = this->actor;
  if (this->someHealthValue != '\0') {
    switch(this->field_0xa4) {
    case 0:
      fVar2 = 0.0;
      if ((this->field_0xa7 == '\0') && (this->damageScale <= 0.0)) {
        getHealthRatio(this);
                    // If 0.25 < health, jump to LAB_0001dd64, else, clear EDX
      }
      BVar1 = ::actor::isTraitorous(act);
      if ((BVar1 != 0) || (extraout_EDX != 0)) {
        this->field84_0xbc = 1.75;
        this->field85_0xc0 = 1.75;
        this->field86_0xc4 = 0.5;
        this->field88_0xcc = 0.2;
        this->field90_0xd4 = 3.0;
        this->field87_0xc8 = fVar2;
        this->field89_0xd0 = fVar2;
        this->field_0xa4 = 1;
        this->field83_0xb8 = 0.4;
        this->field_0xa5 = 0;
        this->field_0xa8 = 1;
        FUN_0001e300();
        return;
      }
      break;
    case 1:
      FUN_0001e380();
      FUN_0001e6c0();
      FUN_0001e300();
      fVar2 = 128.0 - this->field83_0xb8 * 2.5 * 128.0;
      if (0.0 <= fVar2) {
        local_4 = 128.0;
        if (fVar2 <= 128.0) {
          local_4 = fVar2;
        }
      }
      else {
        local_4 = 0.0;
      }
      uVar3 = float10::to_uint64_t((float10)local_4);
      this->field_0xa5 = (char)uVar3;
      BVar1 = Timer::reduce(&this->field83_0xb8);
      if (BVar1 != 0) {
        this->field_0xa4 = 2;
        return;
      }
      break;
    case 2:
      FUN_0001e380();
      getHealthRatio(this);
      Timer::reduce(&this->damageScale);
      FUN_0001e6c0();
      FUN_0001e300();
      this->field_0xa5 = 0x80;
      BVar1 = ::actor::isTraitorous(act);
      if ((BVar1 == 0) && (extraout_EDX_00 != 0)) {
        this->field_0xa4 = 3;
        this->field83_0xb8 = 0.5;
        return;
      }
      break;
    case 3:
      FUN_0001e380();
      FUN_0001e300();
      fVar2 = this->field83_0xb8 * 2.0 * 128.0;
      if (fVar2 <= 128.0) {
        local_4 = 0.0;
        if (0.0 <= fVar2) {
          local_4 = fVar2;
        }
      }
      else {
        local_4 = 128.0;
      }
      uVar3 = float10::to_uint64_t((float10)local_4);
      this->field_0xa5 = (char)uVar3;
      BVar1 = Timer::reduce(&this->field83_0xb8);
      if (BVar1 != 0) {
        this->field_0xa4 = 0;
        this->field_0xa5 = 0;
      }
    }
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


float actorBody::getHealthRatio(actorBody *param_1)

{
  if (param_1->maxHealth == 0) {
    return 1.0;
  }
  return (float)param_1->health / (float)param_1->maxHealth;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


undefined4 actorBody::getHealthColour(actorBody *param_1)

{
  float fVar1;
  
  if (param_1->maxHealth != 0) {
    fVar1 = (float)param_1->health / (float)param_1->maxHealth;
    if (fVar1 < 0.25) {
      return 0xff2020ff;
    }
    if (fVar1 < 0.5) {
      return 0x80ff;
    }
    if (fVar1 < 0.75) {
      return 0xff00ffff;
    }
  }
  return 0xff00ff00;
}




BOOL actor::isTraitorous(actor *act)

{
  if (((act->derivedMarkerValue == (DerivedMarkerValue *)0x0) &&
      ((0.0 < act->traitorTimer || (act->randTraitoristicCombat != '\0')))) &&
     ((act->attribs == (ActorAttribsResource *)0x0 || (act->attribs[1].rand3 == 0.0)))) {
    return 1;
  }
  return 0;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void actorBody::initExpressions(actorBody *body,actorBodyParams *params)

{
  undefined2 *puVar1;
  int *piVar2;
  XSoundbankResource *res;
  actorBodyExpression *newExpression;
  actorBodyExpression *paVar3;
  HeapTableEntry *pHVar4;
  uint someOffset;
  char *aid;
  ActorExpression *expression;
  int i;
  int numExpressions;
  XSoundbankResource *local_4;
  
  i = 0;
  numExpressions = 0;
  aid = params->defaultExpressionAID;
  do {
    if (*(int *)aid == 0x5f646961) {
      Assets::GetResourceBytes(aid,&local_4);
      res = local_4;
      if (local_4 == (XSoundbankResource *)0x0) {
        runtime::ExitGame(2);
      }
      *(XSoundbankResource **)((int)(body->blendTargets + 2) + (i * 2 + 1) * 4) = res;
      if (res != (XSoundbankResource *)0x0) {
        someOffset = XSoundbankResource::GetResourceSize(res);
        *(uint *)((int)(body->blendTargets + 2) + (i * 2 + 2) * 4) = someOffset >> 3;
        numExpressions = numExpressions + 1;
      }
    }
    i = i + 1;
    aid = aid + 0x80;
  } while (i < 10);
  if (numExpressions != 0) {
    expression = &body->irritatedExpression;
                    // Runs 9 times
    local_4 = (XSoundbankResource *)0x9;
    do {
      if (expression->resource != (XSoundbankResource *)0x0) {
        if (body->newExpression == (actorBodyExpression *)0x0) {
          if (g_HeapTableBase[runtime::CurrentHeapToAllocateFrom].heapHandle == (HANDLE)0x0) {
            pHVar4 = (HeapTableEntry *)0x0;
          }
          else {
            pHVar4 = g_HeapTableBase + runtime::CurrentHeapToAllocateFrom;
          }
          newExpression = (actorBodyExpression *)runtime::AllocateOnHeap(pHVar4->heapHandle,0,0x34);
          if (newExpression != (actorBodyExpression *)0x0) {
            i = FUN_0014ded0(pHVar4->heapHandle,0,newExpression);
            puVar1 = (undefined2 *)(i + -4 + (int)newExpression);
            *puVar1 = 0x1234;
            *(undefined1 *)(puVar1 + 1) = *(undefined1 *)&pHVar4->field32_0x20;
          }
          body->newExpression = newExpression;
          *(uint32_t *)(&newExpression->field_0x0 + body->numBodyExpressions * 0xc) =
               expression->resource->SDBK;
          *(undefined4 *)(&body->newExpression->field_0x4 + body->numBodyExpressions * 0xc) = 0;
          *(undefined4 *)(&body->newExpression->field_0x8 + body->numBodyExpressions * 0xc) = 0;
          body->numBodyExpressions = body->numBodyExpressions + 1;
          numExpressions = 4;
        }
        else {
          i = 0;
          if (0 < (int)expression->size) {
            someOffset = (numExpressions * 3 + 0xc) * 4;
            do {
              paVar3 = body->newExpression;
              if ((paVar3 != (actorBodyExpression *)0x0) &&
                 (piVar2 = (int *)&paVar3->field_0x0,
                 paVar3 < (actorBodyExpression *)(piVar2 + body->numBodyExpressions * 3))) {
                do {
                  if (*(int *)paVar3 == *(int *)(expression->resource->name + i * 8 + -0x28))
                  goto LAB_0001e9c9;
                  paVar3 = (actorBodyExpression *)&paVar3->field_0xc;
                } while (paVar3 < (actorBodyExpression *)(piVar2 + body->numBodyExpressions * 3));
              }
              if (body->numBodyExpressions == numExpressions) {
                paVar3 = (actorBodyExpression *)
                         AllocateMoreAStruct_33(someOffset,body->newExpression);
                numExpressions = numExpressions + 4;
                body->newExpression = paVar3;
                someOffset = someOffset + 0x30;
              }
              *(undefined4 *)(&body->newExpression->field_0x0 + body->numBodyExpressions * 0xc) =
                   *(undefined4 *)(expression->resource->name + i * 8 + -0x28);
              *(undefined4 *)(&body->newExpression->field_0x4 + body->numBodyExpressions * 0xc) = 0;
              *(undefined4 *)(&body->newExpression->field_0x8 + body->numBodyExpressions * 0xc) = 0;
              body->numBodyExpressions = body->numBodyExpressions + 1;
LAB_0001e9c9:
              i = i + 1;
            } while (i < (int)expression->size);
          }
        }
      }
      expression = expression + 1;
      local_4 = (XSoundbankResource *)((int)&local_4[-1].cues[0].c + 3);
    } while (local_4 != (XSoundbankResource *)0x0);
  }
  return;
}




void actorBody::updateExpression(actorBody *param_1)

{
  int *piVar1;
  float fVar2;
  Model *pMVar3;
  KeyframeContext *kfc;
  actorBodyExpression *paVar4;
  bool bVar5;
  BOOL BVar6;
  BlendTargetInfo_ptr_8_bool pbVar8;
  int iVar7;
  int iVar8;
  int iVar9;
  float fVar10;
  
  pMVar3 = (param_1->actor->avatar).model;
  iVar9 = param_1->numBodyExpressions;
  iVar8 = 0;
  iVar7 = 0;
  bVar5 = false;
  if (0 < iVar9) {
    kfc = (param_1->actor->avatar).keyframeContext;
    do {
      if ((kfc != (KeyframeContext *)0x0) &&
         (BVar6 = KeyframeContext::hasValAtIndexInAnyChannel
                            (kfc,*(int *)(&param_1->newExpression->field_0x0 + iVar8)), BVar6 != 0))
      {
        bVar5 = true;
        break;
      }
      iVar7 = iVar7 + 1;
      iVar8 = iVar8 + 0xc;
    } while (iVar7 < iVar9);
  }
  iVar7 = 0;
  if (0 < iVar9) {
    iVar9 = 0;
    do {
      if (bVar5) {
        paVar4 = param_1->newExpression;
        if (pMVar3->blendTargets[*(int *)(&paVar4->field_0x0 + iVar9)] == (BlendTarget *)0x0) {
          *(undefined4 *)(&paVar4->field_0x4 + iVar9) = 0;
        }
        else {
          *(float *)(&paVar4->field_0x4 + iVar9) =
               pMVar3->blendTargets[*(int *)(&paVar4->field_0x0 + iVar9)]->blendWeight;
        }
      }
      else {
        if ((*(int *)(&param_1->newExpression->field_0x0 + iVar9) == 0) &&
           (param_1->hasBlendTargets != 0)) {
          iVar8 = 0;
          pbVar8 = &param_1->blendTargets[0].blendState;
          do {
            if (ADJ(pbVar8)->blendState != '\0') {
              if (pMVar3->blendTargets[0] == (BlendTarget *)0x0) {
                fVar10 = 0.0;
              }
              else {
                fVar10 = pMVar3->blendTargets[0]->blendWeight;
              }
              fVar2 = *(float *)(&param_1->newExpression->field_0x4 + iVar9);
              if (fVar10 <= fVar2) {
                fVar10 = fVar2;
              }
              if (pMVar3->blendTargets[0] != (BlendTarget *)0x0) {
                pMVar3->blendTargets[0]->blendWeight = fVar10;
              }
              goto LAB_0001ed1d;
            }
            iVar8 = iVar8 + 1;
            pbVar8 = pbVar8 + 0xc;
          } while (iVar8 < 2);
        }
        piVar1 = (int *)(&param_1->newExpression->field_0x0 + iVar9);
        if (pMVar3->blendTargets[*piVar1] != (BlendTarget *)0x0) {
          pMVar3->blendTargets[*piVar1]->blendWeight = (float)piVar1[1];
        }
      }
LAB_0001ed1d:
      iVar7 = iVar7 + 1;
      iVar9 = iVar9 + 0xc;
    } while (iVar7 < param_1->numBodyExpressions);
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void actorBody::checkIfHasGlobalBlendTargets(actorBody *param_1)

{
  BlendTargetInfo_ptr_4_float pfVar1;
  uint *val;
  int count;
  Model *instance;
  
  instance = (param_1->actor->avatar).model;
  count = 0;
  val = graphics::blend_target_indices;
  pfVar1 = &param_1->blendTargets[0].blendWeight;
  do {
    ADJ(pfVar1).float1 = 1.0;
    ADJ(pfVar1)->blendState = '\0';
    ADJ(pfVar1)->blendWeight = 0.0;
    if ((instance != (Model *)0x0) && (instance->blendTargets[*val] != (BlendTarget *)0x0)) {
      count = count + 1;
    }
    val = val + 1;
    pfVar1 = pfVar1 + 3;
  } while ((int)val < 0x217e4c);
  if ((count != 0) && (instance != (Model *)0x0)) {
    param_1->hasBlendTargets = 1;
    return;
  }
  param_1->hasBlendTargets = 0;
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void actorBody::updateBlendTargets(actorBody *this)

{
  BlendTargetInfo_ptr_8_bool pbVar1;
  int iVar1;
  float delta;
  float speed;
  float weight;
  
  if (runtime::dx_timer <= 0.0) {
    delta = runtime::DeltaTime * runtime::TimeScale;
  }
  else {
    delta = 0.0;
  }
  speed = 0.0;
  if ((this->actor->avatar).movementFreezeTimer <= 0.0) {
    speed = (this->actor->avatar).actionSpeed;
  }
  speed = speed * delta;
  pbVar1 = &this->blendTargets[0].blendState;
  iVar1 = 2;
  do {
    weight = ADJ(pbVar1)->blendWeight;
    switch(ADJ(pbVar1)->blendState) {
    case '\x01':
      delta = speed / ADJ(pbVar1).float1 + weight;
      if (1.0 < delta) {
        ADJ(pbVar1)->blendState = '\x02';
LAB_0001ee98:
        delta = 1.0;
      }
      goto LAB_0001ee9b;
    case '\x02':
      ADJ(pbVar1)->blendState = '\x03';
      break;
    case '\x03':
    case '\x04':
      delta = weight - speed / ADJ(pbVar1).float1;
      if (delta < 0.0) {
        delta = 0.0;
        ADJ(pbVar1)->blendState = '\0';
      }
      ADJ(pbVar1)->blendWeight = delta;
      break;
    case '\x05':
      delta = speed / ADJ(pbVar1).float1 + weight;
      if (1.0 < delta) {
        ADJ(pbVar1)->blendState = '\0';
        goto LAB_0001ee98;
      }
LAB_0001ee9b:
      ADJ(pbVar1)->blendWeight = delta;
    }
    pbVar1 = pbVar1 + 0xc;
    iVar1 = iVar1 + -1;
    if (iVar1 == 0) {
      return;
    }
  } while( true );
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void actorBody::updateBlendTargets(actorBody *this)

{
  actor *paVar1;
  KeyframeContext *kfc;
  BOOL has;
  BlendTarget *blend_target;
  Model *instance;
  
  paVar1 = this->actor;
  kfc = (paVar1->avatar).keyframeContext;
  if ((kfc != (KeyframeContext *)0x0) &&
     (has = KeyframeContext::hasValAtIndexInAnyChannel(kfc,0), has != 0)) {
    return;
  }
  instance = (paVar1->avatar).model;
  blend_target = instance->blendTargets[0];
  if (blend_target != (BlendTarget *)0x0) {
    blend_target->blendWeight = this->blendTargets[0].blendWeight;
  }
  blend_target = instance->blendTargets[0];
  if (blend_target != (BlendTarget *)0x0) {
    blend_target->blendWeight = this->blendTargets[1].blendWeight;
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


BOOL actorBody::flagIsSet(actorBody *param_1,actorBodyFlagId id)

{
  return (uint)((*(byte *)((int)&param_1->flagSet->flags->flag1 + (id >> 3)) &
                '\x01' << ((byte)id & 7)) != 0);
}




actorBodyFlagId actorBody::getFlagIdByName(char *name)

{
  uint i;
  uchar bVar1;
  uchar bVar2;
  uchar *pbVar3;
  
  i = 0;
  do {
    pbVar3 = (uchar *)name;
    while( true ) {
      bVar1 = *pbVar3;
      if (0x20 < bVar1) {
        bVar1 = bVar1 & 0xdf;
      }
      bVar2 = pbVar3[(int)g_actorBodyFlags[i] - (int)name];
      if (0x20 < bVar2) {
        bVar2 = bVar2 & 0xdf;
      }
      if (bVar1 != bVar2) break;
      pbVar3 = pbVar3 + 1;
      if (bVar1 == 0) {
        return (actorBodyFlagId)(float)(unkfloat1)i;
      }
    }
    if (bVar1 == bVar2) goto LAB_0001efc4;
    i = i + 1;
  } while (i < 0x41);
  i = 0;
LAB_0001efc4:
  return (actorBodyFlagId)(float)(unkfloat1)i;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void actorBody::setFlag(actorBody *param_1,uint param_2)

{
  byte *pbVar1;
  
  pbVar1 = (byte *)((int)&param_1->flagSet->flags->flag1 + (param_2 >> 3));
  *pbVar1 = *pbVar1 | '\x01' << ((byte)param_2 & 7);
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void actorBody::setFlagById(actorBody *body,actorBodyFlagId param_2,int param_3)

{
  actorBodyFlags *paVar1;
  byte *pbVar2;
  
  paVar1 = body->flagSet->flags;
  if (param_3 != 0) {
    pbVar2 = (byte *)((int)&paVar1->flag1 + (param_2 >> 3));
    *pbVar2 = *pbVar2 | '\x01' << ((byte)param_2 & 7);
    return;
  }
  *(byte *)((int)&paVar1->flag1 + (param_2 >> 3)) =
       *(byte *)((int)&paVar1->flag1 + (param_2 >> 3)) & ~('\x01' << ((byte)param_2 & 7));
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void actorBody::disableFlagByIndex(uint param_1,actorBody *body)

{
  actorBodyFlags *paVar1;
  
  paVar1 = body->flagSet->flags;
  *(byte *)((int)&paVar1->flag1 + (param_1 >> 3)) =
       *(byte *)((int)&paVar1->flag1 + (param_1 >> 3)) & ~('\x01' << ((byte)param_1 & 0b00000111));
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void __fastcall onActorReaperHit(int param_1)

{
  CalloutDescriptor **ppCVar1;
  float *in_EAX;
  
  someFxPos.x = *in_EAX;
  someFxPos.y = in_EAX[1];
  someFxPos.z = in_EAX[2];
  ppCVar1 = &((*(actor **)(param_1 + 8))->avatar).callout;
  _DAT_004e1c88 = 1.0;
  DAT_004e1c5c = 0x41;
  if (ppCVar1 != (CalloutDescriptor **)0x0) {
    actor::executeCalloutInDescriptor
              (*ppCVar1,ActorReaperHit,(CalloutCallback *)0x0,0x4e1c5c,*(actor **)(param_1 + 8),
               (entityBodyPlayer_0x924)0x0);
  }
  return;
}




void __thiscall actorBody::flipFlags(void *this,byte param_1)

{
  avatar_conflict13 *paVar1;
  avatar_conflict13 *paVar2;
  avatar_0x900_conflict6 pEVar3;
  uint32_t uVar4;
  actorBody *extraout_ECX;
  char cVar5;
  Message local_8;
  
  uVar4 = getFlagsBitfield(this);
  if ((param_1 & 1) != 0) {
    extraout_ECX->flag1 = (bool)(extraout_ECX->flag1 + -1);
  }
  if ((param_1 & 2) != 0) {
    extraout_ECX->flag2 = extraout_ECX->flag2 + -1;
  }
  if ((param_1 & 4) != 0) {
    extraout_ECX->flag3 = extraout_ECX->flag3 + -1;
  }
  if ((param_1 & 8) != 0) {
    extraout_ECX->flag4 = extraout_ECX->flag4 + -1;
  }
  if ((param_1 & 0x10) != 0) {
    extraout_ECX->flag5 = extraout_ECX->flag5 + -1;
  }
  if ((param_1 & 0x20) != 0) {
    extraout_ECX->flag6 = extraout_ECX->flag6 + -1;
  }
  cVar5 = extraout_ECX->flag1 != false;
  if (extraout_ECX->flag2 != '\0') {
    cVar5 = cVar5 + '\x02';
  }
  if (extraout_ECX->flag3 != '\0') {
    cVar5 = cVar5 + '\x04';
  }
  if (extraout_ECX->flag4 != '\0') {
    cVar5 = cVar5 + '\b';
  }
  if (extraout_ECX->flag5 != '\0') {
    cVar5 = cVar5 + '\x10';
  }
  if (extraout_ECX->flag6 != '\0') {
    cVar5 = cVar5 + ' ';
  }
  if ((uVar4 == 0x3f) && (cVar5 != '?')) {
    local_8.header.someActor = extraout_ECX->actor;
    local_8.header.msgId = Actor_NoLongerInvulnerable;
    pEVar3 = Game::SceneInfo.avatars.next;
    while (pEVar3 != (avatar_0x900_conflict6)0x0) {
      paVar1 = ADJ(pEVar3);
      paVar2 = ADJ(pEVar3);
      pEVar3 = pEVar3->next;
      (*((paVar1->object).vtable)->onMessage)(paVar2,&local_8);
    }
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


uint32_t __fastcall actorBody::getFlagsBitfield(actorBody *param_1)

{
  uint32_t uVar1;
  uchar flags;
  
  flags = param_1->flag1 != false;
  uVar1 = (uint32_t)flags;
  if (param_1->flag2 != '\0') {
    uVar1 = uVar1 + 2;
  }
  if (param_1->flag3 != '\0') {
    uVar1 = uVar1 + 4;
  }
  if (param_1->flag4 != '\0') {
    uVar1 = uVar1 + 8;
  }
  if (param_1->flag5 != '\0') {
    uVar1 = uVar1 + 0x10;
  }
  if (param_1->flag6 != '\0') {
    uVar1 = uVar1 + 0x20;
  }
  return uVar1;
}




void actorBody::addAvatarToCollisionSet(actorBody *body,avatar *av)

{
  CollisionMask mask;
  actorBodyAllocd *eventBundle;
  
  eventBundle = body->actorAllocd;
  if ((eventBundle != (actorBodyAllocd *)0x0) && (eventBundle->field13_0x10 != 0)) {
    mask = avatar::getCollisionMaskFromModel(av);
    if ((mask & (Mask0x100|Mask0x40|Mask0x2)) != Nothing) {
      InitEDB2Entry(&eventBundle->edb2Buffer,av,0);
    }
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void actorBody::initStatsheetValues(actorBody *body,actorBodyParams *params)

{
  ushort uVar1;
  float fVar2;
  float fVar3;
  
  body->shatsheetInitialised_ = 1;
  body->damageFlag_ = params->someCountNOTFLAG;
  uVar1 = body->actor->statsheetIndex;
  fVar2 = Game::HealthMetadata[0x11].maxHealth;
  if (uVar1 != 0) {
    fVar3 = (float)Game::HealthMetadata[0x11].minHealthU8;
    if ((float)Game::HealthMetadata[0x11].maxHealthU8 != fVar3) {
      fVar3 = (((float)(byte)Assets::GhouliesStatsheet[uVar1 - 1].healthStart - fVar3) /
              ((float)Game::HealthMetadata[0x11].maxHealthU8 - fVar3)) *
              (Game::HealthMetadata[0x11].maxHealth - Game::HealthMetadata[0x11].minHealth) +
              Game::HealthMetadata[0x11].minHealth;
      if (Game::HealthMetadata[0x11].maxHealth <= Game::HealthMetadata[0x11].minHealth) {
        if ((Game::HealthMetadata[0x11].maxHealth <= fVar3) &&
           (fVar2 = fVar3, Game::HealthMetadata[0x11].minHealth < fVar3)) {
          fVar2 = Game::HealthMetadata[0x11].minHealth;
        }
      }
      else if ((fVar3 <= Game::HealthMetadata[0x11].maxHealth) &&
              (fVar2 = fVar3, fVar3 < Game::HealthMetadata[0x11].minHealth)) {
        fVar2 = Game::HealthMetadata[0x11].minHealth;
      }
    }
  }
                    // Disabling these makes me able to 1shot the spider without hitting it? instant
                    // dive and kill?
  body->knockdownThreshold = fVar2 * 0.25;
  body->damageDampening_ = 0.99;
  *(uint *)&(body->actor->avatar).damageFlag_ = (uint)params->someCountNOTFLAG;
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void actorBody::updateTimers(actorBody *param_1)

{
  float fVar1;
  float fVar2;
  
  FUN_0001f600();
  if (runtime::dx_timer <= 0.0) {
    fVar1 = runtime::DeltaTime * runtime::TimeScale;
  }
  else {
    fVar1 = 0.0;
  }
  fVar2 = 0.0;
  if ((param_1->actor->avatar).movementFreezeTimer <= 0.0) {
    fVar2 = (param_1->actor->avatar).actionSpeed;
  }
  if ((0.0 < param_1->someTimer3) &&
     (fVar1 = param_1->someTimer3 - fVar2 * fVar1, param_1->someTimer3 = fVar1, fVar1 <= 0.0)) {
    param_1->someTimer3 = 0.0;
    param_1->field117_0x164 = 0;
    param_1->damageDampening_ = 0.99;
  }
  if (runtime::dx_timer <= 0.0) {
    fVar1 = runtime::DeltaTime * runtime::TimeScale;
  }
  else {
    fVar1 = 0.0;
  }
  fVar2 = 0.0;
  if ((param_1->actor->avatar).movementFreezeTimer <= 0.0) {
    fVar2 = (param_1->actor->avatar).actionSpeed;
  }
  if ((0.0 < param_1->someTimer4) &&
     (fVar1 = param_1->someTimer4 - fVar2 * fVar1, param_1->someTimer4 = fVar1, fVar1 <= 0.0)) {
    param_1->someTimer4 = 0.0;
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void actorBody::resetFlags(actorBody *body)

{
  avatar_conflict13 *paVar1;
  avatar_conflict13 *paVar2;
  avatar_0x900_conflict6 pEVar3;
  uint32_t uVar4;
  actorBody *extraout_ECX;
  char cVar5;
  Message local_8;
  
  uVar4 = getFlagsBitfield(body);
  extraout_ECX->flag1 = (bool)(extraout_ECX->flag1 + '\x01');
  extraout_ECX->flag2 = extraout_ECX->flag2 + '\x01';
  extraout_ECX->flag3 = extraout_ECX->flag3 + '\x01';
  extraout_ECX->flag4 = extraout_ECX->flag4 + '\x01';
  extraout_ECX->flag5 = extraout_ECX->flag5 + '\x01';
  extraout_ECX->flag6 = extraout_ECX->flag6 + '\x01';
  cVar5 = extraout_ECX->flag1 != false;
  if (extraout_ECX->flag2 != '\0') {
    cVar5 = cVar5 + '\x02';
  }
  if (extraout_ECX->flag3 != '\0') {
    cVar5 = cVar5 + '\x04';
  }
  if (extraout_ECX->flag4 != '\0') {
    cVar5 = cVar5 + '\b';
  }
  if (extraout_ECX->flag5 != '\0') {
    cVar5 = cVar5 + '\x10';
  }
  if (extraout_ECX->flag6 != '\0') {
    cVar5 = cVar5 + ' ';
  }
  if ((uVar4 == 0b00111111) && (cVar5 != 0b00111111)) {
    local_8.header.someActor = extraout_ECX->actor;
    local_8.header.msgId = Actor_NoLongerInvulnerable;
    pEVar3 = Game::SceneInfo.avatars.next;
    while (pEVar3 != (avatar_0x900_conflict6)0x0) {
      paVar1 = ADJ(pEVar3);
      paVar2 = ADJ(pEVar3);
      pEVar3 = pEVar3->next;
      (*((paVar1->object).vtable)->onMessage)(paVar2,&local_8);
    }
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void __fastcall actorBody::resetFlags(actorBody *param_1)

{
  avatar_conflict13 *paVar1;
  avatar_conflict13 *paVar2;
  avatar_0x900_conflict6 pEVar3;
  uint32_t uVar4;
  actorBody *paramm1;
  char cVar5;
  Message local_8;
  
  uVar4 = getFlagsBitfield(param_1);
  paramm1->flag1 = (bool)(paramm1->flag1 + -1);
  paramm1->flag2 = paramm1->flag2 + -1;
  paramm1->flag3 = paramm1->flag3 + -1;
  paramm1->flag4 = paramm1->flag4 + -1;
  paramm1->flag5 = paramm1->flag5 + -1;
  paramm1->flag6 = paramm1->flag6 + -1;
  cVar5 = paramm1->flag1 != false;
  if (paramm1->flag2 != '\0') {
    cVar5 = cVar5 + '\x02';
  }
  if (paramm1->flag3 != '\0') {
    cVar5 = cVar5 + '\x04';
  }
  if (paramm1->flag4 != '\0') {
    cVar5 = cVar5 + '\b';
  }
  if (paramm1->flag5 != '\0') {
    cVar5 = cVar5 + '\x10';
  }
  if (paramm1->flag6 != '\0') {
    cVar5 = cVar5 + ' ';
  }
  if ((uVar4 == 0b00111111) && (cVar5 != 0b00111111)) {
    local_8.header.someActor = paramm1->actor;
    local_8.header.msgId = Actor_NoLongerInvulnerable;
    pEVar3 = Game::SceneInfo.avatars.next;
    while (pEVar3 != (avatar_0x900_conflict6)0x0) {
      paVar1 = ADJ(pEVar3);
      paVar2 = ADJ(pEVar3);
      pEVar3 = pEVar3->next;
      (*((paVar1->object).vtable)->onMessage)(paVar2,&local_8);
    }
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


undefined1 * actorBody::getCollisionDrone(actorBody *body)

{
  actor *paVar1;
  Buffer<> *pBVar2;
  actorDroneActionId aVar3;
  actorDroneActionId *paVar4;
  
  paVar1 = body->actor;
  pBVar2 = paVar1->droneActionsBuf;
  if (pBVar2 == (Buffer<> *)0x0) {
    aVar3 = Null;
  }
  else {
    if (pBVar2->size == pBVar2->endOfQueue) {
      paVar4 = (actorDroneActionId *)0x0;
    }
    else {
      paVar4 = (actorDroneActionId *)
               ((int)&pBVar2->entries->actionId +
               (uint)pBVar2->currentDroneAction * (uint)pBVar2->valueSize);
    }
    aVar3 = *paVar4;
  }
  if (aVar3 != WalkToDestThenDelete) {
    if ((paVar1->actorType == Human) || ((paVar1->node0x93c).prev != (actor_0x93c)0x0)) {
      return FUN_000c0000;
    }
    switch(paVar1->actorType) {
    case Ghoulie_old:
    case 4:
    case NPC:
      return &LAB_00083ffd_3;
    case Human|Ghoulie_old:
      return (undefined1 *)0x44000;
    }
  }
  return FUN_000c4000;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void actorBody::onHitByActor(actorBody *body,Avatar_HitByActorMessage *msg)

{
  actor *paVar1;
  actor *paVar2;
  AttackEntry *pAVar3;
  Buffer<> *pBVar4;
  actorDroneActionId *paVar5;
  int iVar6;
  uint uVar7;
  HitContext *pHVar8;
  float10 extraout_ST0;
  float10 fVar9;
  float10 extraout_ST0_00;
  float __x;
  float puVar9;
  HitContext hitctx;
  HitParam1 local_10;
  actor **iVar2;
  actorBody *hitter_body;
  
  if ((body->flagSet->flags->attackFlags_ & 0x40000000) != Null) {
    return;
  }
  paVar1 = body->actor;
  paVar2 = msg->hitter;
  hitter_body = paVar2->body;
  pHVar8 = &hitctx;
  for (iVar6 = 0x1a; iVar6 != 0; iVar6 = iVar6 + -1) {
    pHVar8->type1 = '\0';
    pHVar8->field1_0x1 = '\0';
    pHVar8->field2_0x2 = '\0';
    pHVar8->field3_0x3 = '\0';
    pHVar8 = (HitContext *)&pHVar8->field4_0x4;
  }
  pAVar3 = hitter_body->currentAttackEntry;
  if (pAVar3 == (AttackEntry *)0x0) {
    hitctx.type1 = '\0';
    hitctx.field1_0x1 = '3';
    hitctx.field2_0x2 = 'e';
  }
  else {
    hitctx.type1 = pAVar3->field_0x3;
    hitctx.field1_0x1 = *(uint8_t *)&pAVar3->actorMoveParams;
    hitctx.field2_0x2 = *(uint8_t *)((int)&pAVar3->actorMoveParams + 1);
  }
  hitctx.hcDetails = (HitContextDetails *)msg->someU32;
  hitctx.field3_0x3 = *(uint8_t *)((hitctx.hcDetails)->field3_0x4 + 0x24);
  hitctx.attackerPos.x = (msg->v2).x;
  hitctx.attackerPos.y = (msg->v2).y;
  hitctx.attackerPos.z = (msg->v2).z;
  hitctx.field4_0x4 = (hitctx.type1 == '\x03') + 1;
  FUN_000fca60(&hitctx.field16_0x24,(ushort *)hitctx.hcDetails);
  hitctx.someV.x = (msg->v1).x;
  pAVar3 = hitter_body->currentAttackEntry;
  hitctx.someV.y = (msg->v1).y;
  __x = (msg->v1).z;
  if (pAVar3 == (AttackEntry *)0x0) {
    uVar7 = 0;
  }
  else {
    uVar7 = *(uint *)&pAVar3->field_0x20;
  }
  if ((uVar7 & 8) != 0) {
    pBVar4 = paVar1->droneActionsBuf;
    if (pBVar4 != (Buffer<> *)0x0) {
      if (pBVar4->size == pBVar4->endOfQueue) {
        paVar5 = (actorDroneActionId *)0x0;
      }
      else {
        paVar5 = (actorDroneActionId *)
                 ((int)&pBVar4->entries->actionId +
                 (uint)pBVar4->currentDroneAction * (uint)pBVar4->valueSize);
      }
      if (*paVar5 != Null) goto LAB_0002019a;
    }
    if ((body->field302_0x258 == 0) && ((body->flagSet->flags->attackFlags_ & 0x2000000) == Null)) {
      hitctx.field10_0x10 = 1;
    }
  }
LAB_0002019a:
  if (pAVar3 == (AttackEntry *)0x0) {
    uVar7 = 0;
  }
  else {
    uVar7 = *(uint *)&pAVar3->field_0x20;
  }
  hitctx.attacker = paVar2;
  hitctx.attacker2 = paVar2;
  hitctx.attacker3 = paVar2;
  hitctx.someV.z = __x;
  if ((uVar7 & 1) == 0) {
    if (((body->hitReactionRes != (HitReactionResource *)0x0) &&
        (body->hitReactionRes->field_0x1a0 != '\0')) &&
       ((paVar1->avatar).as23ptr != (astruct_23 *)0x0)) {
      puVar9 = __x;
      FUN_00041970(0x3f800000);
      __x = (float)&hitctx.otherV;
      FUN_001060a0(puVar9);
      goto LAB_00020256;
    }
    FUN_00041900(paVar2);
    hitctx.otherV.y = 0.0;
    sin(__x);
    hitctx.otherV.x = (float)extraout_ST0_00;
    fVar9 = (float10)cos(__x);
  }
  else {
    FUN_0001d540();
    __x = __x + (paVar2->avatar).rotEuler.y;
    hitctx.otherV.y = 0.0;
    sin(__x);
    hitctx.otherV.x = (float)extraout_ST0;
    fVar9 = (float10)cos(__x);
  }
  hitctx.otherV.z = (float)fVar9;
LAB_00020256:
  if (hitter_body->burnFxObjRes == (void *)0x0) {
    hitctx.field23_0x58 = 0;
  }
  else {
    hitctx.field23_0x58 = hitter_body->field451_0x754;
  }
  hitctx.statsheetIndex = paVar2->statsheetIndex;
  hitctx.hittee = (actor *)0x1;
  handleHit(body,&hitctx,&local_10,(void *)__x,body);
  HandleCheckWhoHitMe(&local_10,&hitctx);
  (msg->field0_0x0).someActor = (actor *)0x1;
  FUN_00020a60(paVar2,body,&hitctx);
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields

float entityBodyHuman::onActorKnockBackContactMessage
                (actorBody *param_1,int param_2,undefined4 *param_3,int param_4,uint8_t param_5,
                float *param_6,int param_7)

{
  ushort uVar1;
  int iVar2;
  int iVar3;
  HitContext *pHVar4;
  bool bVar5;
  float10 extraout_ST0;
  float10 fVar6;
  float10 extraout_ST0_00;
  vec3 local_88;
  HitParam1 local_7c;
  actor *actor;
  HitContext local_68;
  
  actor = param_1->actor;
  *param_6 = 0.0;
  iVar2 = FUN_0001f750();
  if ((iVar2 == 0) && ((param_1->flagSet->flags->attackFlags_ & IsBandaged) == Null)) {
    uVar1 = *(ushort *)(*(int *)(param_2 + 0x95c) + 0x162);
    iVar2 = *(int *)(*(int *)(param_2 + 0x95c) + 8);
    local_88.x = *(float *)(iVar2 + 0x3c);
    local_88.y = *(float *)(iVar2 + 0x40);
    local_88.z = *(float *)(iVar2 + 0x44);
    local_7c.field0_0x0 = (int)local_88.x;
    local_7c.actorWasHit = (uint)local_88.y;
    local_7c.field2_0x8 = (int)local_88.z;
    if ((local_88.x != 0.0) || ((local_88.y != 0.0 || (local_88.z != 0.0)))) {
      vec3::normalise(&local_88);
    }
    fVar6 = abs_float(local_88.x * *(float *)param_7 +
                      local_88.y * *(float *)(param_7 + 4) + local_88.z * *(float *)(param_7 + 8));
    if ((((param_4 != 0) || ((float)fVar6 < 0.5)) || (2 < uVar1 + 1)) ||
       (*(int *)(*(int *)(param_2 + 0x95c) + 0x738) < *(int *)&param_1->field_0x738)) {
      bVar5 = false;
    }
    else {
      bVar5 = true;
    }
    iVar2 = *(int *)(param_2 + 0x95c);
    pHVar4 = &local_68;
    for (iVar3 = 0x1a; iVar3 != 0; iVar3 = iVar3 + -1) {
      pHVar4->type1 = '\0';
      pHVar4->field1_0x1 = '\0';
      pHVar4->field2_0x2 = '\0';
      pHVar4->field3_0x3 = '\0';
      pHVar4 = (HitContext *)&pHVar4->field4_0x4;
    }
    if (bVar5) {
      local_68.type1 = '\x03';
      local_68.field1_0x1 = '7';
      local_68.field2_0x2 = 'h';
      local_68._8_4_ = 1;
      local_68.field4_0x4 = 2;
    }
    else {
      local_68.type1 = '\x01';
      local_68.field1_0x1 = '2';
      local_68.field2_0x2 = 'e';
      local_68.field4_0x4 = 1;
    }
    if (actor->actorType == Human) {
      bVar5 = true;
    }
    else {
      bVar5 = (actor->node0x93c).prev != (actor_0x93c)0x0;
    }
    local_68.attackerPos.x = (float)*param_3;
    local_68.attackerPos.y = (float)param_3[1];
    local_68.attackerPos.z = (float)param_3[2];
    local_68.attacker3 = *(actor **)(iVar2 + 0x274);
    local_68.field16_0x24.x = *(float *)param_7;
    local_68._20_4_ = ZEXT14(!bVar5);
    local_68.field16_0x24.y = *(float *)(param_7 + 4);
    local_68.field16_0x24.z = *(float *)(param_7 + 8);
    local_68.field3_0x3 = param_5;
    local_68.attacker = (actor *)param_2;
    local_68.attacker2 = (actor *)param_2;
    local_68.someV.x = (float)local_7c.field0_0x0;
    local_68.someV.y = (float)local_7c.actorWasHit;
    local_68.someV.z = (float)local_7c.field2_0x8;
    local_68.otherV.x = (float)local_7c.field0_0x0;
    local_68.otherV.y = (float)local_7c.actorWasHit;
    local_68.otherV.z = (float)local_7c.field2_0x8;
    if (*(int *)(iVar2 + 0x760) == 0) {
      local_68.field23_0x58 = 0;
    }
    else {
      local_68.field23_0x58 = *(int *)(iVar2 + 0x754);
    }
    local_68.statsheetIndex = *(ushort *)(param_2 + 0xcf4);
    local_68.hittee = (actor *)0x1;
    actorBody::handleHit(param_1,&local_68,&local_7c,param_1,pHVar4);
    HandleCheckWhoHitMe(&local_7c,&local_68);
    *param_6 = (float)local_7c.actorWasHit;
    return (float)extraout_ST0_00;
  }
  return (float)extraout_ST0;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void __fastcall actorBody::setCurrentWeaponType(actorBody *body,char *fmt,char *str1,char *str2)

{
  _vsprintf(body->currentWeaponType,fmt,&str2);
  return;
}




void HandleCheckWhoHitMe(HitParam1 *param_1,HitContext *param_2)

{
  undefined1 local_c [12];
  
  FUN_00021010();
  if ((param_1->actorWasHit != 0) && (param_2->type1 == '\x12')) {
    onActorReaperHit();
    return;
  }
  if (param_2->attacker2 != (actor *)0x0) {
    FUN_0001f240(local_c,param_1->field0_0x0 == 0);
    return;
  }
  if (param_2->hitter != (actor *)0x0) {
    FUN_0001f240(local_c,param_1->field0_0x0 == 0);
  }
  return;
}




int actorBody::applyDamage(actorBody *bodyy,int damage,int canDoubleDamage)

{
  BOOL BVar1;
  int newHealth;
  actorBody *body;
  actor *act;
  
  act = bodyy->actor;
  if ((act->actorType == Human) || ((act->node0x93c).prev != (actor_0x93c)0x0)) {
    BVar1 = GetAmbienceAudio__(act);
    if (BVar1 == 0) {
      return 0;
    }
  }
  if ((canDoubleDamage != 0) && ((bodyy->flagSet->flags->attackFlags_ & 0x1000) != Null)) {
    damage = damage * 2;
  }
  if (damage != 0) {
    newHealth = (uint)bodyy->health - damage;
                    // Sets the mummy's new health
    bodyy->health = (ushort)newHealth & (newHealth < 1) - 1;
  }
  return damage;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void onFingeredByReaper(actorBody *this,KnockbackData *param_2,HitParam1 *param_3)

{
  actor *paVar1;
  BOOL BVar2;
  StatetableEntry *pSVar3;
  uint uVar4;
  uint uVar5;
  Asset *local_4;
  
  local_4 = (Asset *)this->flagSet->flags;
  uVar4 = (uint)this->health;
  paVar1 = this->actor;
  if ((-1 < (char)*(actorBodyFlagId *)local_4->name) &&
     ((((paVar1->actorType != Human && ((paVar1->node0x93c).prev == (actor_0x93c)0x0)) ||
       (BVar2 = GetAmbienceAudio__(paVar1), BVar2 != 0)) && (uVar4 != 0)))) {
    if (((paVar1->actorType == Human) || ((paVar1->node0x93c).prev != (actor_0x93c)0x0)) &&
       (BVar2 = GetAmbienceAudio__(paVar1), BVar2 == 0)) {
      uVar5 = 0;
    }
    else {
      uVar5 = uVar4;
      if ((*(byte *)((int)local_4->name + 5) & 0x10) != 0) {
        uVar5 = uVar4 * 2;
      }
      if (uVar5 != 0) {
        this->health = ((int)(uVar4 - uVar5) < 1) - 1 & (ushort)(uVar4 - uVar5);
      }
    }
    if ((this->statetableRes == (StatetableResource *)0x0) ||
       (pSVar3 = binarySearchStateTable(this->statetableRes,&local_4,FaintReaper),
       pSVar3 == (StatetableEntry *)0x0)) {
      actorBody::applyKnockback
                (this,param_2,param_3,uVar5,(uint)(byte)param_2->field_0x2,0x3f800000,0x3f800000);
      return;
    }
    this->field117_0x164 = 0;
    this->damageDampening_ = 0.99;
    FUN_00024370(param_2->field49_0x34,param_2->field50_0x38,param_2->field51_0x3c,
                 param_2->field8_0x8);
    actorBody::processHitReaction(this,0x6b);
    FUN_0001b810(this,0,0);
    param_3->field0_0x0 = uVar5;
    param_3->field2_0x8 = 0;
    param_3->actorWasHit = 1;
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


int actorBody::calculateAndApplyDamage(actorBody *this,KnockbackData *param_2)

{
  undefined1 uVar1;
  actorBodyFlags *paVar2;
  actor *paVar3;
  BOOL BVar4;
  int damage;
  int iVar5;
  
  paVar2 = this->flagSet->flags;
  paVar3 = this->actor;
  if ((-1 < (char)paVar2->flag1) &&
     (((paVar3->actorType != Human && ((paVar3->node0x93c).prev == (actor_0x93c)0x0)) ||
      (BVar4 = GetAmbienceAudio__(paVar3), BVar4 != 0)))) {
    iVar5 = param_2->field50_0x38;
    uVar1 = param_2->field_0x1;
    damage = FUN_000238e0(this,iVar5);
                    // If not oko
    if ((((iVar5 == 0) || (*(int *)(iVar5 + 0xce0) == 0)) ||
        ((*(short *)(iVar5 + 0xcdc) != 2 && (*(int *)(iVar5 + 0x93c) == 0)))) ||
       (Game::PowerupParams[8].active == 0)) {
      switch(uVar1) {
      case 0x36:
      case 0x39:
      case 0x3a:
      case 0x3b:
      case 0x3c:
      case 0x3d:
      case 0x3e:
      case 0x3f:
      case 0x45:
        if ((((paVar2->attackFlags_ & IsGettingBackUp) != Null) && (damage != 0)) &&
           (damage = damage >> 1, damage < 2)) {
          damage = 1;
        }
      }
    }
                    // Damages the mummy
    iVar5 = applyDamage(this,damage,1);
    return iVar5;
  }
  return 0;
}




uint isActorDamageable(actorBody *param_1,HitContext *hitCtx)

{
  float fVar1;
  uint uVar2;
  float *pfVar3;
  uint uVar4;
  uint uVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  float fVar10;
  vec3 v;
  HitContextDetails *puVar2;
  
  puVar2 = hitCtx->hcDetails;
  if ((puVar2 == (HitContextDetails *)0x0) || ((param_1->flagSet->flags->flag1 & 0x400) != Null)) {
    return 0;
  }
  uVar4 = 0;
  for (uVar2 = puVar2->field3_0x4; uVar2 < puVar2->field4_0x8; uVar2 = uVar2 + 0x54) {
    uVar4 = uVar4 | *(uint *)(uVar2 + 0x20);
  }
  if ((uVar4 & 0x200000) == 0) {
    return 0;
  }
  if ((int)(puVar2->field4_0x8 - puVar2->field3_0x4) / (int)(uint)puVar2->field0_0x0 == 1) {
    return 1;
  }
  uVar2 = hitCtx->hcDetails->field3_0x4;
  uVar4 = hitCtx->hcDetails->field4_0x8;
  avatar::getWorldPosition(&hitCtx->attacker->avatar,&v);
  fVar1 = (hitCtx->attackerPos).y;
  fVar8 = v.x;
  fVar9 = fVar1;
  fVar10 = v.z;
  if (*(char *)(uVar2 + 0x28) == '\x01') {
    fVar8 = *(float *)(uVar2 + 0x2c);
    fVar9 = *(float *)(uVar2 + 0x30);
    fVar10 = *(float *)(uVar2 + 0x34);
  }
  uVar5 = uVar2 + 0x54;
  fVar7 = (fVar10 - v.z) * (fVar10 - v.z) + (fVar9 - fVar1) * (fVar9 - fVar1) +
          (fVar8 - v.x) * (fVar8 - v.x);
  if (uVar5 < uVar4) {
    pfVar3 = (float *)(uVar2 + 0x88);
    do {
      if (*(char *)(pfVar3 + -3) == '\x01') {
        fVar8 = pfVar3[-2];
        fVar9 = pfVar3[-1];
        fVar10 = *pfVar3;
      }
      fVar6 = (fVar10 - v.z) * (fVar10 - v.z) + (fVar9 - fVar1) * (fVar9 - fVar1) +
              (fVar8 - v.x) * (fVar8 - v.x);
      if (fVar6 < fVar7) {
        uVar2 = uVar5;
        fVar7 = fVar6;
      }
      uVar5 = uVar5 + 0x54;
      pfVar3 = pfVar3 + 0x15;
    } while (uVar5 < uVar4);
  }
  return *(uint *)(uVar2 + 0x20) >> 0x15 & 1;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void SetShockPassType(entityBodyHuman *bodyHuman,Message *msg)

{
  ObjMsgID OVar1;
  actor *paVar2;
  StatetableResource *statetable;
  Message *pMVar3;
  int iVar4;
  StatetableEntry *entry;
  undefined4 unaff_EDI;
  MessageHeader msg_header;
  char *shockPassType;
  
  pMVar3 = msg;
  OVar1 = msg[1].header.msgId;
  if (OVar1 != Null) {
    iVar4 = (bodyHuman->body).health - OVar1;
    (bodyHuman->body).health = (ushort)iVar4 & (iVar4 < 1) - 1;
  }
  paVar2 = msg[1].header.someActor;
  if (msg[2].header.msgId == Null) {
    switch(paVar2) {
    case (actor *)0x0:
      shockPassType = "shockfail";
      break;
    case (actor *)0x1:
      shockPassType = "shockfailwithweapon";
      break;
    case (actor *)0x2:
      shockPassType = "shockfailwithhand";
      break;
    case (actor *)0x3:
      shockPassType = "shockfailwithweaponwithhand";
      break;
    default:
      goto switchD_00023780_default;
    }
  }
  else {
    switch(paVar2) {
    case (actor *)0x0:
      shockPassType = "shockpass";
      break;
    case (actor *)0x1:
      shockPassType = "shockpasswithweapon";
      break;
    case (actor *)0x2:
      shockPassType = "shockpasswithhand";
      break;
    case (actor *)0x3:
      shockPassType = "shockpasswithweaponwithhand";
      break;
    default:
      goto switchD_00023780_default;
    }
  }
  actorBody::setAnimation(&bodyHuman->body,shockPassType);
switchD_00023780_default:
  *(undefined4 *)&(bodyHuman->body).field_0x240 = 0;
  *(undefined4 *)&(bodyHuman->body).field_0x23c = 0;
  paVar2 = (bodyHuman->body).actor;
  msg_header.msgId = ActorBody_HitReactionStateChange;
  msg_header.someActor = (actor *)0x7e;
  (*((paVar2->avatar).vtable)->onMessage)(paVar2,&msg_header);
  statetable = (bodyHuman->body).statetableRes;
  if ((statetable != (StatetableResource *)0x0) &&
     (entry = binarySearchStateTable(statetable,(Asset **)&msg,Hit), entry != (StatetableEntry *)0x0
     )) {
    actorBody::updateStatesFromEntry(&bodyHuman->body,(AttackEntry *)msg,entry);
  }
  OVar1 = pMVar3[1].header.msgId;
  dispatchActorHitMessage(OVar1,0,0,0,0,(uint)(OVar1 == Null),unaff_EDI);
  (pMVar3->header).someActor = (actor *)0x1;
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields
// WARNING: Struct "Actor_StruggleMessage": ignoring overlapping field "field1_0x4"

void __fastcall

void actorBody::initHitReactionResource(actorBody *body,actorBodyParams *params)

{
  HitReactionResource *local_4;
  
  *(undefined4 *)&body->field_0x278 = 1;
  if (*(int *)params->hitReactionAID == 0x5f646961) {
    Assets::GetResourceBytes(params->hitReactionAID,&local_4);
    if (local_4 == (HitReactionResource *)0x0) {
      runtime::ExitGame(2);
    }
    body->hitReactionRes = local_4;
  }
  return;
}




void dispatchActorHitInvulnerableMessage(void)

{
  Message local_14;
  
  local_14.header.msgId = Scene_ActorHitInvulnerable;
  EventLoop::DispatchMessage((ObjMsgID *)&local_14);
  EventLoop::NewMessage(&local_14.header);
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields

void dispatchSceneActorHitDefensiveMessage
               (uint param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
               undefined4 param_5)

{
  Scene_ActorHitDefensiveMessage msg;
  
  msg.field0_0x0 = Scene_ActorHitDefensive;
  msg.field3_0xc = param_1;
  EventLoop::DispatchMessage(&msg.field0_0x0);
  EventLoop::NewMessage((MessageHeader *)&msg);
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


BOOL actorBody::processHitReaction(actorBody *body,ushort reactionState)

{
  StatetableEntry *entry;
  objParamsLocator *pAStack_c;
  undefined4 uStack_8;
  uint local_4;
  
  uStack_8 = 0x61;
  local_4 = (uint)reactionState;
  (*((body->actor->avatar).vtable)->onMessage)(body->actor,&uStack_8);
  if ((reactionState != 0) && (body->statetableRes != (StatetableResource *)0x0)) {
    entry = binarySearchStateTable(body->statetableRes,(Asset **)&pAStack_c,reactionState);
    if (entry != (StatetableEntry *)0x0) {
      updateStatesFromEntry(body,(AttackEntry *)pAStack_c,entry);
      return 1;
    }
  }
  return 0;
}




undefined4 actorBody::ctor(actorBody *body,actorBodyParams *params)

{
  int i;
  actorBodyFlagSet *flagSet;
  uint32_t subres0x2_index;
  actorBodyAllocd *paVar1;
  float frac;
  float neg_frac;
  float x_frac;
  float y_frac;
  float z_frac;
  int statetable_name;
  actor *parent;
  actor *actor;
  
  parent = params->parent;
  body->actor = parent;
  if (params->scale != 0.0) {
    i = 0;
    if (0 < Assets::NumSomethingBodies) {
      do {
        if ((parent->avatar).tag == g_AssetBodySearchList[i]) goto LAB_00024d54;
        i = i + 1;
      } while (i < Assets::NumSomethingBodies);
    }
    frac = params->scale / (parent->avatar).uniformScale;
    runtime::rand = runtime::rand * 0x19660d + 0x3c6ef35f;
    actor = body->actor;
    neg_frac = 0.0 - frac;
    frac = (frac - neg_frac) * ((float)(runtime::rand & 0x7fffff | 0x3f800000) - 1.0) + neg_frac +
           1.0;
                    // Scale actor size to body size
    x_frac = frac * (parent->avatar).scale.x;
    y_frac = (parent->avatar).scale.y * frac;
    z_frac = (parent->avatar).scale.z * frac;
    if (((x_frac != (actor->avatar).scale.x) || (y_frac != (actor->avatar).scale.y)) ||
       (z_frac != (actor->avatar).scale.z)) {
      (actor->avatar).scale.x = x_frac;
      (actor->avatar).scale.y = y_frac;
      (actor->avatar).scale.z = z_frac;
      (actor->avatar).anglesCalculated = 0;
    }
  }
LAB_00024d54:
  body->cameraOffsetVertical = params->cameraOffsetVertical;
  body->closenessDistance = params->field9_0x194;
  body->field480_0x88c = params->field24_0x1b8;
  body->field481_0x890 = 2;
  initHealth(body,params);
  *(uint *)&body->field_0x738 = (uint)(byte)params->field_0x1a9;
  flagSet = malloc_(0x15);
  if (flagSet != (actorBodyFlagSet *)0x0) {
    flagSet->defaultOrMaxFlag_ = 0x41;
    flagSet->flagCount = 9;
    flagSet->flags = &flagSet->flagValues;
    (flagSet->flagValues).flag1 = Null;
    (flagSet->flagValues).attackFlags_ = Null;
    *(undefined1 *)&(flagSet->flagValues).flag9 = Null;
  }
  body->flagSet = flagSet;
  *(byte *)((int)&flagSet->flags->flag1 + 3) = *(byte *)((int)&flagSet->flags->flag1 + 3) | 0x20;
  resetHitValues(body);
  body->farRangeThreshold = false;
  body->someHitFlag = false;
  avatar::getWorldRotation(&body->actor->avatar,&body->rotation);
  avatar::getWorldPosition(&body->actor->avatar,&body->worldPosition);
  if (*(int *)params->statetableAID == 0x5f646961) {
    setStateTable(body,params->statetableAID);
  }
  body->defaultStateId = params->defaultStateIndex;
  initAttackData(body,params);
  subres0x2_index = ::actor::getSubres0x2EntryById(body->actor,4);
  body->subres0x2Index = subres0x2_index;
  initStatsheetValues(body,params);
  initHitReactionResource(body,params);
  paVar1 = avatar::initSomething(&body->actor->avatar);
  body->actorAllocd = paVar1;
  body->skipBlendTargetUpdate = true;
  checkIfHasGlobalBlendTargets(body);
  initExpressions(body,params);
  body->field_0x2d0 = params->field_0x1bc;
  body->field_0x2d1 = params->field_0x1bd;
  body->field_0x2d3 = params->field_0x1be;
  body->field_0x2d4 = params->field_0x1bf;
  if (body->field_0x2d0 != '\0') {
    body->field_0x2d2 = 0;
  }
  body->field23_0x44 = 0.0;
  body->field22_0x40 = 0.0;
  body->projRowCount_ = 0.0;
  *(undefined4 *)&body->field_0x718 = 0;
  (body->v3).x = 0.55850536;
  (body->v3).y = 12.566371;
  (body->v3).z = 6.0;
  *(undefined4 *)&body->field_0x728 = 1;
  body->movementIndex = 0;
  body->fallbackMovementIndex = 0;
  body->movementFlags = *(uint *)&params->field_0x1b4;
  body->objTag = (objTag)params->someValToU16;
  loadMorphTargetPhysics(body);
  body->field_0x717 = 0;
  initFxParticles(body,params);
  if (body->defaultStateId != Null) {
    setState(body,body->defaultStateId);
  }
  return 1;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void actorBody::dtor(EntityV *param_1)

{
  void *pvVar1;
  int iVar2;
  
  if (param_1->field61_0x64 != (void *)0x0) {
    iVar2 = FUN_0001b920();
    if (iVar2 != 0) {
      free(param_1->field61_0x64);
    }
    param_1->field61_0x64 = (void *)0x0;
  }
  if (param_1->field59_0x5c != (void *)0x0) {
    Assets::DestroyAssetOrDecrement(param_1->field59_0x5c);
    param_1->field59_0x5c = (void *)0x0;
  }
  if (param_1->field60_0x60 != (void *)0x0) {
    free(param_1->field60_0x60);
    param_1->field60_0x60 = (void *)0x0;
  }
  if (param_1->field42_0x48 != 0) {
    FUN_0001b4c0((int)param_1);
  }
  FUN_0001e9f0(param_1);
  FUN_00025090();
  if ((param_1->cameraPos).viewMatrix.m[1][3] != 0.0) {
    FUN_0013f240(param_1->field5_0x8);
    (param_1->cameraPos).viewMatrix.m[1][3] = 0.0;
  }
  pvVar1 = (void *)(param_1->cameraPos).rotEuler.z;
  if (pvVar1 != (void *)0x0) {
    Assets::DestroyAssetOrDecrement(pvVar1);
    (param_1->cameraPos).rotEuler.z = 0.0;
  }
  if (param_1->field61_0x64 != (void *)0x0) {
    iVar2 = FUN_0001b920();
    if (iVar2 != 0) {
      free(param_1->field61_0x64);
    }
    param_1->field61_0x64 = (void *)0x0;
  }
  if (param_1->field59_0x5c != (void *)0x0) {
    Assets::DestroyAssetOrDecrement(param_1->field59_0x5c);
    param_1->field59_0x5c = (void *)0x0;
  }
  if (param_1->field60_0x60 != (void *)0x0) {
    free(param_1->field60_0x60);
    param_1->field60_0x60 = (void *)0x0;
  }
  if (param_1->field1271_0x710 != (void *)0x0) {
    free(param_1->field1271_0x710);
    param_1->field1271_0x710 = (void *)0x0;
    param_1->field1272_0x714 = 0;
  }
  FUN_0001dca0();
  FUN_00027580();
  if (param_1->field297_0x15c != (void *)0x0) {
    free(param_1->field297_0x15c);
    param_1->field297_0x15c = (void *)0x0;
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void actorBody::updateModelInstanceValuesWithFlags(actorBody *param_1)

{
  undefined1 valueToSearch;
  undefined1 index;
  actor *paVar1;
  Model *instance;
  
  if (param_1->field_0x2d0 != '\0') {
    valueToSearch = param_1->field_0x2d2;
    paVar1 = param_1->actor;
    index = param_1->field_0x2d1;
    instance = (paVar1->avatar).model;
    if (instance != (Model *)0x0) {
      ModelInstance::searchForValueWithFlags(valueToSearch,instance,index);
    }
    instance = (paVar1->avatar).shadowModel;
    if (instance != (Model *)0x0) {
      ModelInstance::searchForValueWithFlags(valueToSearch,instance,index);
    }
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void actorBody::depleteSomeList(actorBody *param_1)

{
  DataForInfoFromBackground_conflict1 *node;
  
  if (*(int *)&param_1->field_0x310 != 0) {
    param_1->field_0x308 = 0;
    return;
  }
  for (node = (param_1->actor->avatar).infoList.prev;
      node != (DataForInfoFromBackground_conflict1 *)0x0;
      node = (DataForInfoFromBackground_conflict1 *)node->field1_0x4) {
    FUN_0011be40((AvatarInfoNode *)node);
  }
  param_1->field_0x308 = 0;
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void actorBody::onMessage(actorBody *body,Message *msg)

{
  actorMove *paVar1;
  weapon *av;
  int succ;
  undefined4 extraout_EAX;
  vec3 new_rots;
  vec3 new_pos;
  CollisionContext uStack_20;
  actorState *state;
  actor *bodyy;
  actor *temp_26010007d2c;
  float fVar1;
  float fVar2;
  float fVar3;
  
  state = body->actorState;
  if (state != (actorState *)0x0) {
                    // Goes to 0xa5a40
    (*state->vtable->onMessage)(state,msg);
  }
  paVar1 = body->actorMove;
  if (paVar1 != (actorMove *)0x0) {
    (*paVar1->vtable->onMessage)(paVar1,msg);
  }
  temp_26010007d2c = body->actor;
  switch((msg->header).msgId) {
  case Avatar_AddToIgnoreList:
    FUN_0001f890((msg->header).someActor,body);
    return;
  case Avatar_AnimationEvent:
    onAnimEventMessage((Avatar_AnimationEventMessage *)msg,body);
    return;
  case Avatar_BreakableHit:
  case Avatar_CutScene_SetAnim:
  case Avatar_CutScene_SetPos:
  case Avatar_CutScene_SetRot:
  case Avatar_Deflected:
  case Avatar_DeflectedByActor:
  case Avatar_DeleteRequest:
  case Avatar_DrawListAdd:
  case Avatar_DrawListRemove:
  case Avatar_Explode:
  case Avatar_HitByActor:
  case Avatar_HitByFurnace:
  case Avatar_HitByKnockDownSphere:
  case Avatar_HitByGunshot:
  case Avatar_HitByProjectile:
  case Avatar_HitByProjectileAndWaitingForFollow:
  case Avatar_HitByProp:
  case Avatar_HitBySSS:
  case Avatar_HitByWeapon:
  case Avatar_HitsDisable:
  case Avatar_HitsEnable:
  case Avatar_IsBroken:
  case Avatar_PreHitByExplode:
  case Avatar_ResetPos:
  case Actor_AStarLayerChanged:
  case Actor_AbortState:
  case Actor_ActionBegin:
  case Actor_ActionEnd:
  case Actor_Animation_Sync:
  case Actor_AttackMissed:
  case Actor_Bite:
  case Actor_BobAttackBegin:
  case Actor_Celebrate:
  case Actor_DeflectionContact:
  case Actor_DeathCurseEnd:
  case Actor_Die:
  case Actor_DroneArcBegin:
  case Actor_Dying:
  case Actor_EndDroneAction:
  case Actor_EscapedBackground:
  case Actor_FaintBegin:
  case Actor_KnockDownDeath:
  case Actor_ForceIntro:
  case Actor_Fright:
  case Actor_GeneratedAvatar:
  case Actor_GettingUp:
  case Actor_GhoulyIntroEnd:
  case Actor_GoalFlagSet:
  case Actor_Grabbed:
  case Actor_GrabAndThrowBegun:
  case Actor_GunFired:
  case Actor_GunshotHitConnected:
  case Actor_HiddenGhoulyPresence:
  case Actor_HitConnected:
  case Actor_IgnoreInputs:
  case Actor_JumpedOff:
  case Actor_JumpedOn:
  case Actor_KnockBackContact:
  case Actor_KnockBackImpact:
  case Actor_PickupContact:
  case Actor_ProjectileHitConnected:
  case Actor_PushOut:
  case Actor_Scooped:
  case Actor_SetDroneAction:
  case Actor_SmashedBreakables:
  case Actor_SpawnTrail:
  case Actor_StateAborted:
  case Actor_Struggle:
  case Actor_StruggleExited:
  case Actor_TimeCowardExpired:
  case Actor_TimeTraitorExpired:
  case Actor_Throwing:
  case Actor_RequestArcAttackSpeed:
  case Actor_RequestWeaponDropDistance:
  case Actor_WeaponHitConnected:
  case Actor_WithinScareRadius:
  case Actor_WeaponScoopComplete:
  case Actor_WithinExclusionRegion:
  case ActorBody_AttachedWeapon:
  case ActorBody_AttachedProjectile:
  case ActorBody_AttackBoost:
  case ActorBody_HitReactionStateChange:
  case ActorBody_ResolveHitsWallContact:
  case ActorMind_TargetLost:
  case ActorStrategy_SetStrategyId:
  case Background_PostAStarInit:
  case Background_ReregisterDoor:
  case Scene_ActorBandagedUp:
  case Scene_ActorBandageEscape:
  case Scene_ActorDied:
  case Scene_ActorDiedInGhoulyBox:
  case Scene_ActorGrabbedBegin:
  case Scene_ActorGrabbedEnd:
  case Scene_ActorHit:
  case Scene_ActorHitDefensive:
  case Scene_ActorHitInvulnerable:
  case Scene_ActorInserted:
  case Scene_ActorKnockDownHitWall:
  case Scene_ActorLostWeapon:
  case Scene_ActorPickedUpWeapon:
  case Scene_ActorRecoveredFromStun:
  case Scene_ActorRemoved:
  case Scene_ActorScaredBegin:
  case Scene_ActorScaredEnd:
  case Scene_ActorStoppedDroning:
  case Scene_AvatarCreatedFromProjectile:
    break;
  case Avatar_CutScene_Begin:
    freeCutsceneResources(body);
    bodyy = body->actor;
    (bodyy->avatar).physicsPos.x = Game::someGlobalPos.x;
    (bodyy->avatar).physicsPos.y = Game::someGlobalPos.y;
    (bodyy->avatar).physicsPos.z = Game::someGlobalPos.z;
    (body->velocity).x = Game::someGlobalPos.x;
    (body->velocity).y = Game::someGlobalPos.y;
    (body->velocity).z = Game::someGlobalPos.z;
                    // Something physics related
    resetFlags(body);
    return;
  case Avatar_CutScene_End:
    if (temp_26010007d2c->numSomethings < 1) {
      FUN_000277e0();
    }
    resetFlags();
    return;
  case Avatar_FxCustomRemoved:
    FUN_00027b20(body,msg);
    return;
  case Avatar_SceneInsert:
                    // Prevents attacking on spawn?
    updatePositionAndLockon(body);
    return;
  case Actor_NoLongerInvulnerable:
    if (body->actorAllocd != (actorBodyAllocd *)0x0) {
      actorAllocd::ensureAvatarInAllocd(body->actorAllocd,(msg->header).someActor);
      return;
    }
    break;
  case Actor_Reset:
    new_pos.x = (temp_26010007d2c->setup_position_).x;
    new_pos.y = (temp_26010007d2c->setup_position_).y;
    new_pos.z = (temp_26010007d2c->setup_position_).z;
    new_rots.x = (temp_26010007d2c->world_rot_).x;
    new_rots.y = (temp_26010007d2c->world_rot_).y;
    new_rots.z = (temp_26010007d2c->world_rot_).z;
    ::actor::setPosition(temp_26010007d2c,&new_pos);
    ::actor::setRotation(temp_26010007d2c,&new_rots);
    body->field_0x6b = 0;
    body->field_0x6a = 0;
    body->health = body->maxHealth;
    disableFlagByIndex(0x1b,body);
    setState(body,body->defaultStateId);
    return;
  case Actor_SetNoAttackTimer:
    body->noAttackTimer = (float)(msg->header).someActor;
    return;
  case Actor_SetSurfaceOverride:
    body->fallbackMovementIndex = *(undefined1 *)&(msg->header).someActor;
    body->someCount = 2;
    return;
  case ActorBody_SolidDeflectPole:
    fVar1 = (body->worldPosition).x;
    fVar2 = (body->worldPosition).y;
    fVar3 = (body->worldPosition).z;
    new_rots.z = 0.0;
    new_rots.y = 0.0;
    new_rots.x = 0.0;
    uStack_20.field9_0x14 = (temp_26010007d2c->avatar).scale.y * body->cameraOffsetVertical;
    uStack_20._16_4_ = 0;
    uStack_20._24_4_ = 0;
    uStack_20.field14_0x1c = (temp_26010007d2c->avatar).scale.z * body->closenessDistance;
    uStack_20.field0_0x0 = '\x04';
    uStack_20.field1_0x1 = ' ';
    uStack_20.field2_0x2 = '\x01';
    uStack_20.currentPos.x = fVar1;
    uStack_20.currentPos.y = fVar2;
    uStack_20.currentPos.z = fVar3;
    succ = runCollisionTest(&new_rots,&new_pos,&uStack_20,(int)&(msg->header).someActor);
    if (succ != 0) {
      (body->worldPosition).x = new_pos.x + fVar1;
      (body->worldPosition).y = new_pos.y + fVar2;
      (body->worldPosition).z = new_pos.z + fVar3;
      return;
    }
    break;
  case Scene_AvatarInserted:
    addAvatarToCollisionSet(body,(msg->header).someActor);
    break;
  case Scene_AvatarRemoved:
    av = (weapon *)(msg->header).someActor;
    removeWeapon_(av,body);
    FUN_0001b100(extraout_EAX,av);
    if (body->actorAllocd != (actorBodyAllocd *)0x0) {
      actorAllocd::ensureAvatarInAllocd(body->actorAllocd,av);
    }
    FUN_00024340();
    if (av == *(weapon **)&body->field_0x718) {
      *(undefined4 *)&body->field_0x718 = 0;
    }
    if (av == (weapon *)temp_26010007d2c) {
      freeCutsceneResources(body);
      return;
    }
    break;
  default:
    goto switchD_000253ff_default;
  }
switchD_000253ff_default:
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields
// Disabling this globally prevents lockon AND KNOCKDOWNS


void actorBody::updatePositionAndLockon(actorBody *body)

{
  CollisionMask CVar1;
  
  avatar::getWorldPosition(&body->actor->avatar,&body->worldPosition);
  avatar::getWorldRotation(&body->actor->avatar,&body->rotation);
  CVar1 = avatar::getCollisionMaskFromModel(&body->actor->avatar);
                    // If has a target???
  if ((CVar1 & Mask0x2) != Nothing) {
                    // This is the part that handles the lockon
    handleLockOn(body);
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void actorBody::resetHitValues(actorBody *body)

{
  actorBody_ptr_840_undefined1 puVar1;
  int i;
  
  body->airResistance = 10.0;
  body->yVelocity = -200.0;
  body->numStatesDeep = 0;
  body->speedRatio = 1.0;
  body->indexInStatsheet = 2;
  body->bigVec3SetIndex = 0;
  puVar1 = &body->bigVec3Set[0].y;
  i = 0x50;
  do {
    ADJ(puVar1)->z = 0.0;
    ADJ(puVar1)->y = 0.0;
    ADJ(puVar1).x = 0.0;
    puVar1 = puVar1 + 3;
    i = i + -1;
  } while (i != 0);
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


float actorBody::getMovespeed(actorBody *body)

{
  byte index;
  float actor_speed;
  ushort statsheet_index;
  
  statsheet_index = body->actor->statsheetIndex;
  index = body->indexInStatsheet;
                    // Weird edge case
  if (statsheet_index == 0) {
    return body->speedRatio * Game::HealthMetadata[index].maxHealth;
  }
  actor_speed = Game::AddDamage(index,Assets::GhouliesStatsheet[statsheet_index].tagName
                                      [index - 0x48]);
  return body->speedRatio * actor_speed;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


int actor::doSomeWeirdVec3Shit(actor *thsi,int *param_2,vec3 *param_3)

{
  int iVar1;
  float fVar2;
  float fVar3;
  vec3 *pfVar1;
  vec3 *pfVar2;
  
  if (runtime::dx_timer <= 0.0) {
    fVar3 = runtime::DeltaTime * runtime::TimeScale;
  }
  else {
    fVar3 = 0.0;
  }
  fVar2 = 0.0;
  if ((thsi->avatar).movementFreezeTimer <= 0.0) {
    fVar2 = (thsi->avatar).actionSpeed;
  }
  pfVar1 = (vec3 *)(param_2 + *param_2 * 3 + 1);
  pfVar1->x = param_3->x;
  pfVar1->y = param_3->y;
  pfVar1->z = param_3->z;
  if (0.0 < fVar2 * fVar3) {
    fVar3 = 1.0 / (fVar2 * fVar3);
    pfVar2 = (vec3 *)(param_2 + *param_2 * 3 + 1);
    pfVar2->x = (float)param_2[*param_2 * 3 + 1] * fVar3;
    pfVar2->y = pfVar2->y * fVar3;
    pfVar2->z = pfVar2->z * fVar3;
  }
  iVar1 = *param_2;
  *param_2 = (iVar1 + 1) % 80;
  return (iVar1 + 1) / 0x50;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields
// Controls targeting/aiming


void actorBody::updatePosAndRot(actorBody *body)

{
  ushort uVar1;
  float fVar2;
  float speed;
  actorState *state;
  
  if (body->hasBlendTargets != 0) {
    updateBlendTargets(body);
  }
  if (0 < body->numBodyExpressions) {
    updateExpression(body);
  }
  depleteSomeList(body);
  somethingFromColliders(body);
  if (body->someCount != 0) {
    uVar1 = body->someCount - 1;
    body->someCount = uVar1;
    if (uVar1 == 0) {
      body->fallbackMovementIndex = 0;
    }
  }
  updateTimers(body);
  if ((ShouldntDroneBools[1] == 0) && ("\x01"[Game::CheckMoveOn] != '\0')) {
    if (runtime::dx_timer <= 0.0) {
      fVar2 = runtime::DeltaTime * runtime::TimeScale;
    }
    else {
      fVar2 = 0.0;
    }
    speed = 0.0;
    if ((body->actor->avatar).movementFreezeTimer <= 0.0) {
      speed = (body->actor->avatar).actionSpeed;
    }
    if ((0.0 < body->noAttackTimer) &&
       (fVar2 = body->noAttackTimer - speed * fVar2, body->noAttackTimer = fVar2, fVar2 <= 0.0)) {
      body->noAttackTimer = 0.0;
    }
  }
  updateTimersAndFx(body);
  if (runtime::dx_timer <= 0.0) {
    fVar2 = runtime::DeltaTime * runtime::TimeScale;
  }
  else {
    fVar2 = 0.0;
  }
  speed = 0.0;
  if ((body->actor->avatar).movementFreezeTimer <= 0.0) {
    speed = (body->actor->avatar).actionSpeed;
  }
  if ((0.0 < body->someTimer2) &&
     (fVar2 = body->someTimer2 - speed * fVar2, body->someTimer2 = fVar2, fVar2 <= 0.0)) {
    body->someTimer2 = 0.0;
  }
  updateExpressionFromHealth(body);
  updateModelInstanceValuesWithFlags(body);
  state = body->actorState;
  if (state != (actorState *)0x0) {
    (*state->vtable->func5)(state);
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void actorBody::somethingFromColliders(actorBody *param_1)

{
  actor *av;
  actor *paVar1;
  float10 fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  vec3 local_58;
  vec3 world_pos;
  SomeActorBodyList list2;
  SomeActorBodyList list1;
  astruct_23 *as23;
  Model *model;
  
  av = param_1->actor;
  model = (av->avatar).model;
  if ((model != (Model *)0x0) && (model->descriptor != (ModelDescriptor *)0x0)) {
    as23 = (av->avatar).as23ptr;
    avatar::getWorldPosition(&av->avatar,&world_pos);
    if (as23 != (astruct_23 *)0x0) {
      paVar1 = param_1->actor;
      list1.pos.x = world_pos.x;
      list1.pos.y = world_pos.y;
      list1.pos.z = world_pos.z;
      list1.someFloat = (paVar1->avatar).scale.y * param_1->cameraOffsetVertical;
      list1.field11_0x1c = (paVar1->avatar).scale.z * param_1->closenessDistance;
      local_58.x = (paVar1->avatar).physicsPos.x;
      local_58.y = (paVar1->avatar).physicsPos.y;
      local_58.z = (paVar1->avatar).physicsPos.z;
      list1.field0_0x0 = '\x04';
      list1.field1_0x1 = ' ';
      list1.field2_0x2 = '\x01';
      list1.someYScale = 0.0;
      list1._24_4_ = 0;
      if ((param_1->flagSet->flags->attackFlags_ & 0x1000000) == Null) {
        recalculatePunchAndCollisionStuff(av,&list2,param_1->field481_0x890,1);
        FUN_0012b160(&list2,(char)av->backgroundCollisionIndex,&list1,as23,&local_58);
      }
      else {
        list2.pos.x = (as23->somePos).x + (param_1->v1).x;
        list2.field2_0x2 = '\x01';
        list2.someFloat = *(float *)&as23->field_0x30;
        list2.field1_0x1 = ' ';
        list2.field11_0x1c = *(float *)&as23->field_0x38;
        list2.pos.y = (as23->somePos).y + (param_1->v1).y;
        list2.pos.z = (as23->somePos).z + (param_1->v1).z;
        list2.field0_0x0 = '\x04';
        list2.someYScale = 0.0;
        list2._24_4_ = 0;
        FUN_0012b160(&list2,(char)av->backgroundCollisionIndex,&list1,as23,&local_58);
      }
    }
    recalculatePunchAndCollisionStuff(av,&list2,param_1->field480_0x88c,0);
    fVar4 = 1.0 / (av->avatar).scale.y;
    fVar3 = (list2.pos.y - world_pos.y) * fVar4;
    fVar4 = ((list2.someFloat + list2.pos.y) - world_pos.y) * fVar4;
    fVar5 = list2.field11_0x1c / (av->avatar).scale.z;
    (av->avatar).fromModelMatrix1 = fVar4;
    (av->avatar).field193_0x1cc = fVar3;
    (av->avatar).fromModelMatrix2 = fVar5;
    if (fVar4 < fVar3) {
      fVar4 = fVar3;
    }
    fVar2 = scaled_invsqrt(fVar4 * fVar4 + fVar5 * fVar5);
    (av->avatar).someMagnitude = (float)fVar2;
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void actorBody::update(actorBody *body,InputHandlerType1 *param_2)

{
  actorState *paVar1;
  actorMove *paVar2;
  
  paVar1 = body->actorState;
  if (paVar1 != (actorState *)0x0) {
    (*paVar1->vtable->update)(paVar1,param_2);
  }
  paVar2 = body->actorMove;
  if (paVar2 != (actorMove *)0x0) {
    (*paVar2->vtable->update)(paVar2,param_2);
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void actorBody::runCollisions(actorBody *body)

{
  undefined4 uVar1;
  PhysicsSomething *pPVar2;
  PhysicsSomething *physicsPtr;
  vec3 currentPos;
  AffineTransform local_30;
  
  if ((body->physicsSomethings != (PhysicsSomething *)0x0) && (body->dead != false)) {
    currentPos.x = (body->worldPosition).x;
    currentPos.y = (body->worldPosition).y;
    currentPos.z = (body->worldPosition).z;
                    // Combines velocity with some other movement
    avatar::updateAndGetAffine(&body->actor->avatar,&local_30,&currentPos);
    physicsPtr = body->physicsSomethings;
    pPVar2 = physicsPtr + (byte)body->numPhysicsSomethings;
    body->field_0x716 = 0;
    for (; physicsPtr < pPVar2; physicsPtr = physicsPtr + 1) {
      uVar1 = updateBodyPhysics(body,physicsPtr);
      body->field_0x716 = body->field_0x716 + (char)uVar1;
    }
  }
  return;
}




void actorBody::loadMorphTargetPhysics(actorBody *body)

{
  char *pcVar1;
  Model *pMVar2;
  ModelDescriptor *pMVar3;
  ColliderType *pCVar4;
  uint uVar5;
  AnimCollisionSubresourceEntry *pAVar6;
  PhysicsSomething *pPVar7;
  AnimCollisionSubresourceEntry *pAVar8;
  ModelFooterEntry *pMVar9;
  int i;
  AnimCollisionSubresource *uVar3;
  
  pMVar2 = (body->actor->avatar).model;
  if ((pMVar2 != (Model *)0x0) && (pMVar3 = pMVar2->descriptor, pMVar3 != (ModelDescriptor *)0x0)) {
    uVar5 = 0;
    if (pMVar3->numFooterEntries != 0) {
      pMVar9 = pMVar3->footerEntries;
      while (pMVar9->subresourceType != AnimColliders) {
        uVar5 = uVar5 + 1;
        pMVar9 = pMVar9 + 1;
        if (pMVar3->numFooterEntries <= uVar5) {
          return;
        }
      }
      uVar3 = (AnimCollisionSubresource *)pMVar3->footerEntries[uVar5].offset;
      if (uVar3 != (AnimCollisionSubresource *)0x0) {
        pAVar8 = uVar3->entries;
        i = 0;
        pAVar6 = pAVar8;
        if (pAVar8 != (AnimCollisionSubresourceEntry *)0x0) {
          do {
            if (((pAVar6->collisionMask & Mask0x10) != Nothing) && (pAVar6->colliderType == Sphere))
            {
              i = i + 1;
            }
            pcVar1 = &pAVar6->size;
          } while ((*pcVar1 != 0) &&
                  (pCVar4 = &pAVar6->colliderType,
                  pAVar6 = (AnimCollisionSubresourceEntry *)(pCVar4 + (byte)*pcVar1),
                  (AnimCollisionSubresourceEntry *)(pCVar4 + (byte)*pcVar1) !=
                  (AnimCollisionSubresourceEntry *)0x0));
          if (i != 0) {
            body->numPhysicsSomethings = (char)i;
            pPVar7 = malloc_(i * 0x58);
            body->physicsSomethings = pPVar7;
            for (uVar5 = (uint)(i * 0x58) >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
              *(undefined4 *)pPVar7 = 0;
              pPVar7 = (PhysicsSomething *)&pPVar7->field_0x4;
            }
            for (i = 0; i != 0; i = i + -1) {
              *(undefined1 *)pPVar7 = 0;
              pPVar7 = (PhysicsSomething *)&pPVar7->field_0x1;
            }
            if (pAVar8 != (AnimCollisionSubresourceEntry *)0x0) {
              i = 0;
              do {
                if (((pAVar8->collisionMask & Mask0x10) != Nothing) &&
                   (pAVar8->colliderType == Sphere)) {
                  (&body->physicsSomethings->field38_0x26)[i] = '\0';
                  *(AnimCollisionSubresourceEntry **)
                   ((int)&body->physicsSomethings->morphTargets + i) = pAVar8;
                  i = i + 0x58;
                }
              } while ((pAVar8->size != 0) &&
                      (pAVar8 = (AnimCollisionSubresourceEntry *)
                                (&pAVar8->colliderType + (byte)pAVar8->size),
                      pAVar8 != (AnimCollisionSubresourceEntry *)0x0));
            }
            body->dead = false;
          }
        }
      }
    }
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


undefined4 actorBody::updateBodyPhysics(actorBody *param_1,PhysicsSomething *param_2)

{
  float fVar1;
  actor *av;
  Model *pMVar2;
  Collision0x54 *smth1;
  actorBody *paVar3;
  undefined1 *collisionFunction;
  int iVar4;
  Skeleton *skeleton;
  float10 magnitude;
  float10 fVar5;
  float someZ;
  float someY;
  float someX;
  float fVar6;
  AffineTransform *in_stack_0000000c;
  int i;
  vec3 local_48;
  vec3 local_3c;
  vec3 displacement;
  vec3 someVec;
  vec3 local_18;
  
  paVar3 = param_1;
  av = param_1->actor;
  param_2->field38_0x26 = '\0';
  pMVar2 = (av->avatar).model;
  if (pMVar2 == (Model *)0x0) {
    skeleton = (Skeleton *)0x0;
  }
  else {
    skeleton = pMVar2->skeleton;
    if (skeleton == (Skeleton *)0x0) {
      skeleton = pMVar2->skeleton2;
    }
  }
  checkCollisionAgainstSkeleton(param_2->morphTargets,skeleton,&local_18,in_stack_0000000c);
  fVar1 = (float)magnitude;
  local_3c.x = local_18.x;
  local_3c.y = local_18.y;
  local_3c.z = local_18.z;
  avatar::getWorldPosition(&av->avatar,&someVec);
                    // 1.0 = air resistance?
  someVec.y = someVec.y + fVar1 + 1.0;
  collisionFunction = getCollisionDrone(param_1);
  i = 0;
  do {
    local_48.x = local_3c.x;
    local_48.y = local_3c.y;
    local_48.z = local_3c.z;
    if (param_1->field_0x717 == '\0') {
      iVar4 = Collision::runCollisionFunctionWithAllAvatars
                        (&local_48,&someVec,fVar1,Ground|Walls,collisionFunction);
    }
    else {
      if (param_1->field_0x717 != '\x01') break;
      someY = local_3c.y - someVec.y;
      someX = local_3c.x - someVec.x;
      someZ = local_3c.z - someVec.z;
      fVar6 = someZ * someZ + someY * someY + someX * someX;
      if (fVar6 != 0.0) {
        fVar5 = (float10)invsqrt(fVar6);
        someX = (float)((float10)someX * fVar5);
        someY = (float)((float10)someY * fVar5);
        someZ = (float)((float10)someZ * fVar5);
      }
      local_48.x = someX * fVar1 + local_48.x;
      local_48.y = someY * fVar1 + local_48.y;
      local_48.z = someZ * fVar1 + local_48.z;
      iVar4 = Collision::checkAvatarsWithCollisionInScene
                        (&someVec,&local_48,Ground|Walls,collisionFunction);
    }
    if (iVar4 == 0) break;
    smth1 = (Physics::CollisionContexts[0].ctx)->head;
    if (param_2->field38_0x26 == '\0') {
      resolveCollision(smth1,param_2);
    }
    someX = (smth1->velocity).x;
    someY = (smth1->velocity).y;
    someZ = (smth1->velocity).z;
    fVar6 = 0.0 - (((local_3c.z - someVec.z) - (local_48.z - someVec.z)) * someZ +
                   ((local_3c.y - someVec.y) - (local_48.y - someVec.y)) * someY +
                  ((local_3c.x - someVec.x) - (local_48.x - someVec.x)) * someX);
    if (0.05 <= fVar6) {
      if (0.0 <= fVar6) goto LAB_000263c6;
    }
    else {
      fVar6 = 0.05;
LAB_000263c6:
      local_3c.x = fVar6 * someX + local_3c.x;
      local_3c.y = someY * fVar6 + local_3c.y;
      local_3c.z = someZ * fVar6 + local_3c.z;
    }
    i = i + 1;
  } while (i < 3);
  if (param_2->field38_0x26 != '\0') {
    displacement.x = local_48.x - local_18.x;
    displacement.y = local_48.y - local_18.y;
    displacement.z = local_48.z - local_18.z;
    if ((param_1->flagSet->flags->attackFlags_ & 0x200) != Null) {
      displacement.y = 0.0;
    }
    if (runtime::dx_timer <= 0.0) {
      param_1 = (actorBody *)(runtime::DeltaTime * runtime::TimeScale);
    }
    else {
      param_1 = (actorBody *)0x0;
    }
    if ((av->avatar).movementFreezeTimer <= 0.0) {
      param_2 = (PhysicsSomething *)(av->avatar).actionSpeed;
    }
    else {
      param_2 = (PhysicsSomething *)0x0;
    }
    fVar1 = (float)param_1 * (float)param_2 * FLOAT_003390c8;
    fVar5 = scaled_invsqrt(displacement.x * displacement.x + displacement.z * displacement.z);
    if (((float10)fVar1 < fVar5) &&
       (someX = displacement.x * displacement.x + displacement.z * displacement.z, someX != 0.0)) {
      fVar5 = (float10)invsqrt(someX);
      fVar5 = fVar5 * (float10)fVar1;
      displacement.x = (float)((float10)displacement.x * fVar5);
      displacement.z = (float)((float10)displacement.z * fVar5);
    }
    (paVar3->worldPosition).x = (paVar3->worldPosition).x + displacement.x;
    (paVar3->worldPosition).y = (paVar3->worldPosition).y + displacement.y;
    (paVar3->worldPosition).z = (paVar3->worldPosition).z + displacement.z;
    return 1;
  }
  return 0;
}




void actorBody::updateRotationFromActor(actorBody *body)

{
  actor *this;
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float local_30;
  vec3 local_24;
  float local_14;
  float local_10;
  vec3 local_c;
  
  this = body->actor;
  if (*(int *)&body->field_0x728 != 0) {
    avatar::getWorldRotation(&this->avatar,&local_24);
    local_14 = (body->rotation).y;
    local_c.x = (body->rotation).x;
    local_10 = (body->rotation).z;
    fVar6 = 0.0;
    if (runtime::dx_timer <= 0.0) {
      local_30 = runtime::DeltaTime * runtime::TimeScale;
    }
    else {
      local_30 = 0.0;
    }
    if ((this->avatar).movementFreezeTimer <= 0.0) {
      fVar6 = (this->avatar).actionSpeed;
    }
    fVar1 = (body->v3).z;
    fVar2 = (body->v3).y;
    fVar3 = (body->v3).x;
    fVar6 = fVar6 * local_30;
    FUN_00101280(local_24.x,fVar3,fVar2,fVar1,fVar6);
    fVar4 = local_14;
    FUN_00101280(local_24.y,fVar3,fVar2,fVar1,fVar6);
    fVar5 = local_10;
    local_c.y = fVar4;
    FUN_00101280(local_24.z,fVar3,fVar2,fVar1,fVar6);
    local_c.z = fVar5;
    Maths::NormaliseAngles2PI(&local_c,&(this->avatar).rotEuler);
    (this->avatar).anglesCalculated = 0;
    avatar::getWorldRotation(&this->body->actor->avatar,&this->body->rotation);
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


actorBodyStateId actorBody::getStandingState(actorBody *body)

{
  actorMind *paVar1;
  actorBody *paVar2;
  StatetableEntry *pSVar3;
  ushort alertStandType;
  
  paVar2 = body;
  getStandingStates(body,(actorBodyStateId *)&body,&alertStandType);
  paVar1 = paVar2->actor->mind;
  if ((((paVar1 != (actorMind *)0x0) && (paVar1->field_0x20 != '\0')) &&
      (paVar2->statetableRes != (StatetableResource *)0x0)) &&
     ((pSVar3 = binarySearchStateTable
                          (paVar2->statetableRes,(Asset **)&alertStandType,alertStandType),
      pSVar3 != (StatetableEntry *)0x0 &&
      ((paVar2->flagSet->flags->attackFlags_ & 0x8000000) == Null)))) {
    return alertStandType;
  }
  return (actorBodyStateId)body;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


actorBodyStateId actorBody::getNervousState(actorBody *this)

{
  weapon *wpn;
  actorBody *paVar1;
  HoldableType HVar2;
  uint32_t uVar3;
  StatetableEntry *pSVar4;
  actorBodyStateId desiredState;
  
  paVar1 = this;
  wpn = this->weapon;
  if (wpn == (weapon *)0x0) {
    HVar2 = Invalid;
  }
  else {
    HVar2 = wpn->holdableType;
    if (Gun < HVar2) {
      return Null;
    }
  }
  switch(HVar2) {
  default:
    desiredState = NervousStand;
    break;
  case None:
    if (wpn == (weapon *)0x0) {
      uVar3 = 0;
    }
    else {
      uVar3 = ::weapon::getAttribute((this->actor->avatar).tag,wpn);
    }
    if (uVar3 == 1) {
      desiredState = NervousStandWieldingOneHandedWeapon;
    }
    else if (uVar3 == 2) {
      desiredState = NervousStandWieldingTwoHandedWeapon;
    }
    else {
      if (uVar3 != 3) {
        return Null;
      }
      desiredState = NervousStandWieldingLargeTwoHandedWeapon;
    }
    break;
  case Container:
    desiredState = NervousStandHoldingContainer;
    break;
  case LargeProjectile:
    desiredState = NervousStandHoldingLargeProjectile;
    break;
  case Gun:
    desiredState = NervousStandHoldingGun;
  }
  if ((paVar1->statetableRes != (StatetableResource *)0x0) &&
     (pSVar4 = binarySearchStateTable(paVar1->statetableRes,(Asset **)&this,desiredState),
     pSVar4 != (StatetableEntry *)0x0)) {
    return desiredState;
  }
  return Null;
}




actorBodyStateId actorBody::getIdleState(int param_1)

{
  if ((*(int *)(param_1 + 0x48) != 0) && (*(char *)(*(int *)(param_1 + 0x48) + 0x93d) != '\0')) {
    return Null;
  }
  return StandIdle;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


actorBodyStateId actorBody::getWalkState(actorBody *body)

{
  actorMind *paVar1;
  actorBody *paVar2;
  StatetableEntry *pSVar3;
  actorBodyStateId local_4 [2];
  
  paVar2 = body;
  getWalkStates(body,(actorBodyStateId *)&body,local_4);
  paVar1 = paVar2->actor->mind;
  if ((((paVar1 != (actorMind *)0x0) && (paVar1->field_0x20 != '\0')) &&
      (paVar2->statetableRes != (StatetableResource *)0x0)) &&
     ((pSVar3 = binarySearchStateTable(paVar2->statetableRes,(Asset **)local_4,local_4[0]),
      pSVar3 != (StatetableEntry *)0x0 &&
      ((paVar2->flagSet->flags->attackFlags_ & 0x8000000) == Null)))) {
    return local_4[0];
  }
  return (actorBodyStateId)body;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


actorBodyStateId actorBody::getStunnedState(int param_1)

{
  weapon *wpn;
  HoldableType HVar1;
  uint32_t uVar2;
  
  wpn = *(weapon **)(param_1 + 0x48);
  if (wpn == (weapon *)0x0) {
    HVar1 = Invalid;
  }
  else {
    HVar1 = wpn->holdableType;
    if (Gun < HVar1) {
switchD_00026b46_caseD_4:
      return Null;
    }
  }
  switch(HVar1) {
  default:
    return Stunned;
  case None:
    break;
  case Container:
    return StunnedHoldingContainer;
  case LargeProjectile:
    return StunnedHoldingLargeProjectile;
  case Gun:
    return StunnedHoldingGun;
  }
  if (wpn == (weapon *)0x0) {
    uVar2 = 0;
  }
  else {
    uVar2 = ::weapon::getAttribute(*(ushort *)(*(int *)(param_1 + 8) + 6),wpn);
  }
  switch(uVar2) {
  case 1:
    return StunnedWieldingOneHandedWeapon;
  case 2:
    return StunnedWieldingTwoHandedWeapon;
  case 3:
    return StunnedWieldingLargeTwoHandedWeapon;
  case 4:
    goto switchD_00026b46_caseD_4;
  default:
    return (actorBodyStateId)param_1;
  }
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


actorBodyStateId actorBody::getDizzyState(int param_1)

{
  weapon *wpn;
  HoldableType HVar1;
  uint32_t uVar2;
  
  wpn = *(weapon **)(param_1 + 0x48);
  if (wpn == (weapon *)0x0) {
    HVar1 = Invalid;
  }
  else {
    HVar1 = wpn->holdableType;
    if (Gun < HVar1) {
switchD_00026bf6_caseD_4:
      return Null;
    }
  }
  switch(HVar1) {
  default:
    return Dizzy;
  case None:
    break;
  case Container:
    return DizzyHoldingContainer;
  case LargeProjectile:
    return DizzyHoldingLargeProjectile;
  case Gun:
    return DizzyHoldingGun;
  }
  if (wpn == (weapon *)0x0) {
    uVar2 = 0;
  }
  else {
    uVar2 = ::weapon::getAttribute(*(ushort *)(*(int *)(param_1 + 8) + 6),wpn);
  }
  switch(uVar2) {
  case 1:
    return DizzyWieldingOneHandedWeapon;
  case 2:
    return DizzyWieldingTwoHandedWeapon;
  case 3:
    return DizzyWieldingLargeTwoHandedWeapon;
  case 4:
    goto switchD_00026bf6_caseD_4;
  default:
    return (actorBodyStateId)param_1;
  }
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


actorBodyStateId actorBody::getPickupState(Object *param_1,avatar *param_2)

{
  char cVar1;
  actor *av;
  int iVar2;
  undefined4 uVar3;
  vec3 local_18;
  vec3 local_c;
  
  cVar1 = *(char *)((int)&param_2[1].pos.x + 1);
  if (cVar1 == '\x01') {
    av = param_1->rcp1;
    uVar3 = FUN_00146030();
    switch(uVar3) {
    case 1:
      return PickupOneHandedWeapon;
    case 2:
      return PickupTwoHandedWeapon;
    case 3:
      if (*(char *)((int)&param_2[1].pos.y + 2) != '\0') {
        avatar::getWorldPosition(&av->avatar,&local_18);
        avatar::getWorldPosition(param_2,&local_c);
        if (((float)param_1->field700_0x884 * (param_1->rcp1->avatar).scale.y * 0.85 <=
             local_c.y - local_18.y) && (iVar2 = FUN_00027620(), iVar2 != 0)) {
          return PickupLargeTwoHandedWeaponHigh;
        }
      }
      return PickupLargeTwoHandedWeapon;
    case 4:
      return PickupHugeWeapon;
    }
  }
  else {
    if (cVar1 == '\x02') {
      if (*(char *)((int)&param_2[1].pos.y + 2) != '\0') {
        avatar::getWorldPosition(&param_1->rcp1->avatar,&local_c);
        avatar::getWorldPosition(param_2,&local_18);
        if (((float)param_1->field700_0x884 * (param_1->rcp1->avatar).scale.y * 0.35 <=
             local_18.y - local_c.y) && (iVar2 = FUN_00027620(), iVar2 != 0)) {
          return PickupContainerHigh;
        }
      }
      return PickupContainer;
    }
    if (cVar1 == '\x03') {
      return ScoopLargeProjectile;
    }
  }
  return Null;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


actorBodyStateId actorBody::getCheerState(Asset *param_1)

{
  weapon *wpn;
  Asset *pAVar1;
  HoldableType HVar2;
  uint32_t uVar3;
  StatetableEntry *pSVar4;
  actorBodyStateId desiredState;
  
  pAVar1 = param_1;
  wpn = *(weapon **)(param_1->name + 0x48);
  if (wpn == (weapon *)0x0) {
    HVar2 = Invalid;
  }
  else {
    HVar2 = wpn->holdableType;
    if (Gun < HVar2) {
      return Null;
    }
  }
  switch(HVar2) {
  default:
    desiredState = Cheer;
    break;
  case None:
    if (wpn == (weapon *)0x0) {
      uVar3 = 0;
    }
    else {
      uVar3 = ::weapon::getAttribute(*(ushort *)(*(int *)(param_1->name + 8) + 6),wpn);
    }
    switch(uVar3) {
    case 1:
      desiredState = CheerWieldingOneHandedWeapon;
      break;
    case 2:
      desiredState = CheerWieldingTwoHandedWeapon;
      break;
    case 3:
      desiredState = CheerWieldingLargeTwoHandedWeapon;
      break;
    case 4:
      goto switchD_00026e2b_caseD_3;
    default:
      desiredState = (actorBodyStateId)param_1;
      if (desiredState == Null) {
        return Null;
      }
    }
    break;
  case Container:
    desiredState = CheerHoldingContainer;
    break;
  case LargeProjectile:
    desiredState = CheerHoldingLargeProjectile;
    break;
  case Gun:
    desiredState = CheerHoldingGun;
  }
  if ((*(StatetableResource **)(pAVar1[0xd].name + 0x20) != (StatetableResource *)0x0) &&
     (pSVar4 = binarySearchStateTable
                         (*(StatetableResource **)(pAVar1[0xd].name + 0x20),&param_1,desiredState),
     pSVar4 != (StatetableEntry *)0x0)) {
    return desiredState;
  }
switchD_00026e2b_caseD_3:
  return Null;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


actorBodyStateId actorBody::getCringeState(Asset *param_1)

{
  weapon *wpn;
  Asset *pAVar1;
  HoldableType HVar2;
  uint32_t uVar3;
  StatetableEntry *pSVar4;
  actorBodyStateId desiredState;
  
  pAVar1 = param_1;
  wpn = *(weapon **)(param_1->name + 0x48);
  if (wpn == (weapon *)0x0) {
    HVar2 = Invalid;
  }
  else {
    HVar2 = wpn->holdableType;
    if (Gun < HVar2) {
      return Null;
    }
  }
  switch(HVar2) {
  default:
    desiredState = Cringe;
    break;
  case None:
    if (wpn == (weapon *)0x0) {
      uVar3 = 0;
    }
    else {
      uVar3 = ::weapon::getAttribute(*(ushort *)(*(int *)(param_1->name + 8) + 6),wpn);
    }
    switch(uVar3) {
    case 1:
      desiredState = CringeWieldingOneHandedWeapon;
      break;
    case 2:
      desiredState = CringeWieldingTwoHandedWeapon;
      break;
    case 3:
      desiredState = CringeWieldingLargeTwoHandedWeapon;
      break;
    case 4:
      goto switchD_00026edd_caseD_3;
    default:
      desiredState = (actorBodyStateId)param_1;
      if (desiredState == Null) {
        return Null;
      }
    }
    break;
  case Container:
    desiredState = CringeHoldingContainer;
    break;
  case LargeProjectile:
    goto switchD_00026edd_caseD_3;
  case Gun:
    desiredState = CringeHoldingGun;
  }
  if ((*(StatetableResource **)(pAVar1[0xd].name + 0x20) != (StatetableResource *)0x0) &&
     (pSVar4 = binarySearchStateTable
                         (*(StatetableResource **)(pAVar1[0xd].name + 0x20),&param_1,desiredState),
     pSVar4 != (StatetableEntry *)0x0)) {
    return desiredState;
  }
switchD_00026edd_caseD_3:
  return Null;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


actorBodyStateId actorBody::getShuffleState(actorBody *param_1)

{
  weapon *wpn;
  actorBody *paVar1;
  HoldableType HVar2;
  uint32_t uVar3;
  StatetableEntry *pSVar4;
  actorBodyStateId desiredState;
  
  paVar1 = param_1;
  wpn = param_1->weapon;
  if (wpn == (weapon *)0x0) {
    HVar2 = Invalid;
  }
  else {
    HVar2 = wpn->holdableType;
    if (Gun < HVar2) {
      return Null;
    }
  }
  switch(HVar2) {
  default:
    desiredState = Shuffle;
    break;
  case None:
    if (wpn == (weapon *)0x0) {
      uVar3 = 0;
    }
    else {
      uVar3 = ::weapon::getAttribute((param_1->actor->avatar).tag,wpn);
    }
    switch(uVar3) {
    case 1:
      desiredState = ShuffleWieldingOneHandedWeapon;
      break;
    case 2:
      desiredState = ShuffleWieldingTwoHandedWeapon;
      break;
    case 3:
      desiredState = ShuffleWieldingLargeTwoHandedWeapon;
      break;
    default:
      goto switchD_00026fd7_caseD_3;
    }
    break;
  case Container:
    desiredState = ShuffleHoldingContainer;
    break;
  case LargeProjectile:
    desiredState = ShuffleHoldingLargeProjectile;
    break;
  case Gun:
    desiredState = ShuffleHoldingGun;
  }
  if ((paVar1->statetableRes != (StatetableResource *)0x0) &&
     (pSVar4 = binarySearchStateTable(paVar1->statetableRes,(Asset **)&param_1,desiredState),
     pSVar4 != (StatetableEntry *)0x0)) {
    return desiredState;
  }
switchD_00026fd7_caseD_3:
  return Null;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields

void actorBody::getStandingStates
               (actorBody *body,actorBodyStateId *regularState,actorBodyStateId *alertState)

{
  HoldableType WVar1;
  HoldableType uVar2;
  WieldableType uVar1;
  uint32_t uVar3;
  weapon *wpn;
  
  wpn = body->weapon;
  if (wpn == (weapon *)0x0) {
    WVar1 = Invalid;
  }
  else {
    WVar1 = wpn->holdableType;
    if (Gun < WVar1) {
switchD_000270b2_caseD_4:
      *alertState = Null;
      *regularState = Null;
      return;
    }
  }
  switch(WVar1) {
  default:
    *alertState = StandAlert;
    *regularState = Stand;
    return;
  case None:
    break;
  case Container:
    *alertState = StandAlertHoldingContainer;
    *regularState = StandHoldingContainer;
    return;
  case LargeProjectile:
    *alertState = StandAlertHoldingLargeProjectile;
    *regularState = StandHoldingLargeProjectile;
    return;
  case Gun:
    *alertState = StandAlertHoldingGun;
    *regularState = StandHoldingGun;
    return;
  }
  if (wpn == (weapon *)0x0) {
    uVar3 = 0;
  }
  else {
    uVar3 = ::weapon::getAttribute((body->actor->avatar).tag,wpn);
  }
  switch(uVar3) {
  case 1:
    *alertState = StandAlertWieldingOneHandedWeapon;
    *regularState = StandWieldingOneHandedWeapon;
    return;
  case 2:
    *alertState = StandAlertWieldingTwoHandedWeapon;
    *regularState = StandWieldingTwoHandedWeapon;
    return;
  case 3:
    *alertState = StandAlertWieldingLargeTwoHandedWeapon;
    *regularState = StandWieldingLargeTwoHandedWeapon;
    return;
  case 4:
    goto switchD_000270b2_caseD_4;
  default:
    return;
  }
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void actorBody::getWalkStates(actorBody *this,actorBodyStateId *param_2,actorBodyStateId *param_3)

{
  weapon *wpn;
  HoldableType HVar1;
  uint32_t uVar2;
  
  wpn = this->weapon;
  if (wpn == (weapon *)0x0) {
    HVar1 = Invalid;
  }
  else {
    HVar1 = wpn->holdableType;
    if (Gun < HVar1) {
switchD_00027192_caseD_4:
      *param_3 = Null;
      *param_2 = Null;
      return;
    }
  }
  switch(HVar1) {
  default:
    *param_3 = WalkAlert;
    *param_2 = Walk;
    return;
  case None:
    break;
  case Container:
    *param_3 = WalkAlertHoldingContainer;
    *param_2 = WalkHoldingContainer;
    return;
  case LargeProjectile:
    *param_3 = WalkAlertHoldingLargeProjectile;
    *param_2 = WalkHoldingLargeProjectile;
    return;
  case Gun:
    *param_3 = WalkAlertHoldingGun;
    *param_2 = WalkHoldingGun;
    return;
  }
  if (wpn == (weapon *)0x0) {
    uVar2 = 0;
  }
  else {
    uVar2 = ::weapon::getAttribute((this->actor->avatar).tag,wpn);
  }
  switch(uVar2) {
  case 1:
    *param_3 = WalkAlertWieldingOneHandedWeapon;
    *param_2 = WalkWieldingOneHandedWeapon;
    return;
  case 2:
    *param_3 = WalkAlertWieldingTwoHandedWeapon;
    *param_2 = WalkWieldingTwoHandedWeapon;
    return;
  case 3:
    *param_3 = WalkAlertWieldingLargeTwoHandedWeapon;
    *param_2 = WalkWieldingLargeTwoHandedWeapon;
    return;
  case 4:
    goto switchD_00027192_caseD_4;
  default:
    return;
  }
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


actorBodyStateId actorBody::getFrightState(int param_1)

{
  weapon *wpn;
  HoldableType HVar1;
  uint32_t uVar2;
  
  wpn = *(weapon **)(param_1 + 0x48);
  if (wpn == (weapon *)0x0) {
    HVar1 = Invalid;
  }
  else {
    HVar1 = wpn->holdableType;
    if (Gun < HVar1) {
switchD_00027266_caseD_4:
      return Null;
    }
  }
  switch(HVar1) {
  default:
    return Fright;
  case None:
    break;
  case Container:
    return FrightHoldingContainer;
  case LargeProjectile:
    return FrightHoldingLargeProjectile;
  case Gun:
    return FrightHoldingGun;
  }
  if (wpn == (weapon *)0x0) {
    uVar2 = 0;
  }
  else {
    uVar2 = ::weapon::getAttribute(*(ushort *)(*(int *)(param_1 + 8) + 6),wpn);
  }
  switch(uVar2) {
  case 1:
    return FrightWieldingOneHandedWeapon;
  case 2:
    return FrightWieldingTwoHandedWeapon;
  case 3:
    return FrightWieldingLargeTwoHandedWeapon;
  case 4:
    goto switchD_00027266_caseD_4;
  default:
    return (actorBodyStateId)param_1;
  }
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


actorBodyStateId actorBody::getScareState(actorBody *this)

{
  weapon *pwVar1;
  HoldableType HVar2;
  BOOL BVar3;
  
  pwVar1 = this->weapon;
  if (pwVar1 == (weapon *)0x0) {
    HVar2 = Invalid;
  }
  else {
    HVar2 = pwVar1->holdableType;
  }
  if (HVar2 != Invalid) {
    if (HVar2 == None) {
      BVar3 = FUN_001460c0((bodyCollisionProfile *)pwVar1);
      return (-(ushort)(BVar3 != 0) & 4) + Scare;
    }
    if (HVar2 == Gun) {
      return ScareHoldingGun;
    }
  }
  return Scare;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


actorBodyStateId actorBody::getDroneState(actorBody *param_1)

{
  weapon *wpn;
  HoldableType HVar1;
  uint32_t uVar2;
  
  wpn = param_1->weapon;
  if (wpn == (weapon *)0x0) {
    HVar1 = Invalid;
  }
  else {
    HVar1 = wpn->holdableType;
    if (Gun < HVar1) {
switchD_00027366_caseD_4:
      return Null;
    }
  }
  switch(HVar1) {
  default:
    return DroneWait;
  case None:
    break;
  case Container:
    return DroneWaitHoldingContainer;
  case LargeProjectile:
    return DroneWaitHoldingLargeProjectile;
  case Gun:
    return DroneWaitHoldingGun;
  }
  if (wpn == (weapon *)0x0) {
    uVar2 = 0;
  }
  else {
    uVar2 = ::weapon::getAttribute((param_1->actor->avatar).tag,wpn);
  }
  switch(uVar2) {
  case 1:
    return DroneWaitWieldingOneHandedWeapon;
  case 2:
    return DroneWaitWieldingTwoHandedWeapon;
  case 3:
    return DroneWaitWieldingLargeTwoHandedWeapon;
  case 4:
    goto switchD_00027366_caseD_4;
  default:
    return (actorBodyStateId)param_1;
  }
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


actorBodyStateId actorBody::getDroneCheerState(actorBody *param_1)

{
  weapon *wpn;
  byte bVar1;
  uint32_t uVar1;
  
  wpn = param_1->weapon;
  if (wpn == (weapon *)0x0) {
    bVar1 = 0;
  }
  else {
    bVar1 = wpn->holdableType;
    if (Gun < bVar1) {
switchD_00027416_caseD_4:
      return Null;
    }
  }
  switch(bVar1) {
  default:
    return DroneCheer;
  case 1:
    break;
  case 2:
    return DroneCheerHoldingContainer;
  case 3:
    return DroneCheerHoldingLargeProjectile;
  case 4:
    return DroneCheerHoldingGun;
  }
  if (wpn == (weapon *)0x0) {
    uVar1 = 0;
  }
  else {
    uVar1 = ::weapon::getAttribute((param_1->actor->avatar).tag,wpn);
  }
  switch(uVar1) {
  case 1:
    return DroneCheerWieldingOneHandedWeapon;
  case 2:
    return DroneCheerWieldingTwoHandedWeapon;
  case 3:
    return DroneCheerWieldingLargeTwoHandedWeapon;
  case 4:
    goto switchD_00027416_caseD_4;
  default:
    return (actorBodyStateId)param_1;
  }
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


actorBodyStateId actorBody::getBurstFromWallState(actorBody *body)

{
  weapon *wpn;
  HoldableType HVar1;
  uint32_t uVar2;
  
  wpn = body->weapon;
  if (wpn == (weapon *)0x0) {
    HVar1 = Invalid;
  }
  else {
    HVar1 = wpn->holdableType;
    if (Gun < HVar1) {
      return Null;
    }
  }
  switch(HVar1) {
  case None:
    if (wpn == (weapon *)0x0) {
      uVar2 = 0;
    }
    else {
      uVar2 = ::weapon::getAttribute((body->actor->avatar).tag,wpn);
    }
    if (uVar2 != 1) {
      if (uVar2 == 2) {
        return BurstFromWallWieldingTwoHandedWeapon;
      }
      if (uVar2 != 3) {
        return (actorBodyStateId)body;
      }
      return BurstFromWallWieldingLargeTwoHandedWeapon;
    }
    break;
  case LargeProjectile:
    return BurstFromWallHoldingLargeProjectile;
  }
  return BurstFromWall;
}




actorBodyStateId actorBody::getKnockDownState(void)

{
  return KnockDown;
}



StatetableEntry *
binarySearchStateTable
          (StatetableResource *statetable,Asset **assetOut,actorBodyStateId desiredState)

{
  int index;
  int max_i;
  int i;
  actorBodyStateId id;
  
  if (statetable == (StatetableResource *)0x0) {
    return (StatetableEntry *)0x0;
  }
  max_i = statetable->numEntries - 1;
  i = 0;
  if (-1 < max_i) {
    do {
                    // Div 2
      index = i + max_i >> 1;
      id = statetable->entries[index].state;
      if (id < desiredState) {
        i = index + 1;
      }
      else {
        if (id <= desiredState) {
          *assetOut = (Asset *)0x0;
          return statetable->entries + index;
        }
        max_i = index + -1;
      }
    } while (i <= max_i);
  }
  *assetOut = (Asset *)0x0;
  return (StatetableEntry *)0x0;
}




void actorBody::freeCutsceneResources(actorBody *param_1)

{
  if (param_1->actorMove != (actorMove *)0x0) {
    Assets::DeleteResource_(param_1->actorMove);
    param_1->actorMove = (actorMove *)0x0;
  }
  if (param_1->actorState != (actorState *)0x0) {
    Assets::DeleteResource_(param_1->actorState);
    param_1->actorState = (actorState *)0x0;
  }
  param_1->currentStateEntry = (StatetableEntry *)0x0;
  param_1->stateId = Null;
  return;
}




BOOL actorBody::setState(actorBody *body,actorBodyStateId state)

{
  StatetableEntry *entry;
  Asset *local_4;
  
  if ((state != Null) && (body->statetableRes != (StatetableResource *)0x0)) {
    entry = binarySearchStateTable(body->statetableRes,&local_4,state);
    if (entry != (StatetableEntry *)0x0) {
      updateStatesFromEntry(body,(AttackEntry *)local_4,entry);
      return 1;
    }
  }
  return 0;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


BOOL actorBody::updateStatesFromEntry(actorBody *body,AttackEntry *param_2,StatetableEntry *entry)

{
  actorBodyStateId id;
  
  id = entry->state;
  if (body->actorMove != (actorMove *)0x0) {
    Assets::DeleteResource_(body->actorMove);
    body->actorMove = (actorMove *)0x0;
  }
  if (body->actorState != (actorState *)0x0) {
    Assets::DeleteResource_(body->actorState);
    body->actorState = (actorState *)0x0;
  }
  body->currentStateEntry = (StatetableEntry *)0x0;
  body->stateId = Null;
                    // Setting here
  if (entry->animationName != (char *)0x0) {
    setAnimation(body,entry->animationName);
  }
  body->currentStateEntry = entry;
  body->stateId = id;
  setActorMove(body,param_2,entry->actorMoveAID);
                    // Actually update the state in here
  setActorState(body,param_2,entry->actorStateAID);
  if (body->setStateSuccessfully == 0) {
    body->field_0x6c = 0;
    body->currentAttackEntry = (AttackEntry *)0x0;
  }
  return 1;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void actorBody::setStateTable(actorBody *body,char *stateTableAID)

{
  char *pcVar1;
  
  pcVar1 = stateTableAID;
  if (body->actorMove != (actorMove *)0x0) {
    Assets::DeleteResource_(body->actorMove);
    body->actorMove = (actorMove *)0x0;
  }
  if (body->actorState != (actorState *)0x0) {
    Assets::DeleteResource_(body->actorState);
    body->actorState = (actorState *)0x0;
  }
  body->currentStateEntry = (StatetableEntry *)0x0;
  body->stateId = Null;
  if (body->statetableRes != (StatetableResource *)0x0) {
    Assets::DestroyAssetOrDecrement(body->statetableRes);
    body->statetableRes = (StatetableResource *)0x0;
    body->currentStateEntry = (StatetableEntry *)0x0;
  }
  if (*(int *)pcVar1 != 0x5f646961) {
    body->statetableRes = (StatetableResource *)0x0;
    return;
  }
  Assets::GetResourceBytes(pcVar1,&stateTableAID);
  pcVar1 = stateTableAID;
  if (stateTableAID == (char *)0x0) {
    runtime::ExitGame(2);
  }
  body->statetableRes = (StatetableResource *)pcVar1;
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void actorBody::setActorMove(actorBody *body,AttackEntry *attack,char *name)

{
  actorMoveParams *params;
  actorMove *actor_move;
  actorMoveParams *bruh;
  
  if (*(int *)name != 0x5f646961) {
    return;
  }
  if (attack == (AttackEntry *)0x0) {
    params = (actorMoveParams *)Assets::GetObjParams(name);
  }
  else {
    bruh = attack->actorMoveParams;
    params = malloc_((uint)(bruh->params).paramsSize);
    if (params != (actorMoveParams *)0x0) {
      memcpy(params,bruh,(uint)(bruh->params).paramsSize);
    }
  }
  params->body = body;
                    // Also constructs for actorState?
  actor_move = (actorMove *)Assets::CreateEntityFromParams(&params->params);
  body->actorMove = actor_move;
  free(params);
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void __fastcall actorBody::setActorState(actorBody *body,AttackEntry *param_2,char *assetName)

{
  ushort *str;
  actorStateParams *params;
  actorState *paVar1;
  
  if (*(int *)assetName != 0x5f646961) {
    return;
  }
  if (param_2 == (AttackEntry *)0x0) {
    params = (actorStateParams *)Assets::GetObjParams(assetName);
  }
  else {
    str = *(ushort **)param_2;
    params = malloc_((uint)*str);
    if (params != (actorStateParams *)0x0) {
      memcpy(params,str,(uint)*str);
    }
  }
  params->body = body;
  paVar1 = (actorState *)Assets::CreateEntityFromParams(&params->objParams);
  body->actorState = paVar1;
  free(params);
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void actorBody::initFxParticles(actorBody *body,actorBodyParams *param_2)

{
  char cVar1;
  int iVar2;
  char *ptr;
  
  *(uint *)&body->field_0x750 = (uint)(byte)param_2->field_0x1c0;
  ptr = param_2->burnFxObjParamsAID;
  iVar2 = 0x764 - (int)ptr;
  do {
    cVar1 = *ptr;
    ptr[(int)body + iVar2] = cVar1;
    ptr = ptr + 1;
  } while (cVar1 != '\0');
  ptr = param_2->invulnerableFxObjParamsAID;
  iVar2 = 0x7f4 - (int)ptr;
  do {
    cVar1 = *ptr;
    ptr[(int)body + iVar2] = cVar1;
    ptr = ptr + 1;
  } while (cVar1 != '\0');
  body->someFxFloat = param_2->field35_0x2c4;
  if (param_2->particlesOnSpawn != '\0') {
    createParticleRing(0.0,1,body);
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void actorBody::updateTimersAndFx(actorBody *this)

{
  int *piVar1;
  float fVar2;
  float fVar3;
  undefined4 local_8;
  undefined4 local_4;
  
  if (runtime::dx_timer <= 0.0) {
    fVar2 = runtime::DeltaTime * runtime::TimeScale;
  }
  else {
    fVar2 = 0.0;
  }
  fVar3 = 0.0;
  if ((this->actor->avatar).movementFreezeTimer <= 0.0) {
    fVar3 = (this->actor->avatar).actionSpeed;
  }
  if ((0.0 < this->field453_0x75c) &&
     (fVar2 = this->field453_0x75c - fVar3 * fVar2, this->field453_0x75c = fVar2, fVar2 <= 0.0)) {
    this->field453_0x75c = 0.0;
  }
  if (this->burnFxObjRes != (void *)0x0) {
    if (runtime::dx_timer <= 0.0) {
      fVar2 = runtime::DeltaTime * runtime::TimeScale;
    }
    else {
      fVar2 = 0.0;
    }
    fVar3 = 0.0;
    if ((this->actor->avatar).movementFreezeTimer <= 0.0) {
      fVar3 = (this->actor->avatar).actionSpeed;
    }
    if ((0.0 < this->burnFxTimer) &&
       (fVar2 = this->burnFxTimer - fVar3 * fVar2, this->burnFxTimer = fVar2, fVar2 <= 0.0)) {
      this->burnFxTimer = 0.0;
      piVar1 = this->burnFxObjRes;
      if (piVar1 != (int *)0x0) {
        local_4 = 0;
        local_8 = 5;
        (**(code **)(*piVar1 + 0xc))(piVar1,&local_8);
      }
    }
  }
  if ((this->field_0x7e4 != '\0') && (this->field_0x7e5 == '\0')) {
    if (runtime::dx_timer <= 0.0) {
      fVar2 = runtime::DeltaTime * runtime::TimeScale;
    }
    else {
      fVar2 = 0.0;
    }
    fVar3 = 0.0;
    if ((this->actor->avatar).movementFreezeTimer <= 0.0) {
      fVar3 = (this->actor->avatar).actionSpeed;
    }
    if ((0.0 < this->attackTimer) &&
       (fVar2 = this->attackTimer - fVar3 * fVar2, this->attackTimer = fVar2, fVar2 <= 0.0)) {
      this->attackTimer = 0.0;
      if (*(obj **)&this->field_0x7f0 != (obj *)0x0) {
        obj::closeObject(*(obj **)&this->field_0x7f0);
      }
      flipFlags(this,0x3f);
      this->field_0x7e4 = 0;
    }
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void actorBody::createParticleRing(float burnTimer,int param_2,actorBody *body)

{
  actor *paVar1;
  void *inners;
  obj *poVar2;
  undefined4 local_4;
  ObjectFullVTable *piVar1;
  
  piVar1 = body->burnFxObjRes;
  paVar1 = body->actor;
  if (piVar1 == (ObjectFullVTable *)0x0) {
    inners = Assets::GetObjParams(body->burnFxObjParamsAID);
    if (inners == (void *)0x0) {
      poVar2 = (obj *)0x0;
    }
    else {
      *(actor **)((int)inners + 8) = paVar1;
      poVar2 = Assets::CreateEntityFromParams(inners);
      free(inners);
    }
    body->burnFxObjRes = poVar2;
  }
  else {
    local_4 = 3;
    (**(code **)(piVar1->getAllocDetails + 0xc))(piVar1,&local_4);
  }
  if (body->field451_0x754 == 0) {
    body->burnFxTimer = burnTimer;
    body->field451_0x754 = param_2;
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void actor::getAllocDetails(ObjectAllocDetails *param_1)

{
  param_1->entitySize = 0xcf8;
  param_1->paramsSize = 0x63c;
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


ObjectFullVTable * actor::getVTable(void)

{
  ObjectFullVTable *extraout_EAX;
  
  avatar::initVTable(&vtable);
  vtable.getAllocDetails = getAllocDetails;
  vtable.ctor = ctor;
  vtable.dtor = dtor;
  vtable.onMessage = onMessage;
  vtable.update = update;
  vtable.draw = draw;
  return extraout_EAX;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


BOOL actor::defaultMessageHandler(actor *act,Message *msg)

{
  int *piVar1;
  actorStrategy *strategy;
  actorDroneActionId aVar2;
  BOOL BVar3;
  int iVar4;
  
  switch((msg->header).msgId) {
  case Avatar_CutScene_Begin:
    iVar4 = act->numSomethings + 1;
    act->numSomethings = iVar4;
    if (iVar4 == 1) {
      if (act->strategy != (actorStrategy *)0x0) {
        actorStrategy::setStrategy(act->strategy,Null);
      }
      aVar2 = getNextDroneAction(act);
      if (aVar2 != Null) {
        drone(act);
        return 1;
      }
    }
    break;
  case Avatar_CutScene_End:
    piVar1 = &act->numSomethings;
    *piVar1 = *piVar1 + -1;
    if (((*piVar1 == 0) && (strategy = act->strategy, strategy != (actorStrategy *)0x0)) &&
       (BVar3 = GetAmbienceAudio__(act), BVar3 != 0)) {
      actorStrategy::setStrategy(strategy,strategy->resetState);
    }
    break;
  case Avatar_CutScene_SetAnim:
  case Avatar_CutScene_SetPos:
  case Avatar_CutScene_SetRot:
    break;
  default:
    return 0;
  }
  return 1;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


undefined4 actor::draw(actor *param_1,undefined4 param_2,BOOL param_3)

{
  undefined4 uVar1;
  actorState *actor_state;
  actorBody *body;
  
  if ((*(int *)&param_1->field_0xce0 != 0) &&
     (((param_1->actorType == Human || ((param_1->node0x93c).prev != (actor_0x93c)0x0)) &&
      (((undefined1)g_globalFlagset & HealthAltered?) != 0)))) {
    return 0;
  }
  uVar1 = avatar::draw(&param_1->avatar,param_2,param_3);
  body = param_1->body;
  FUN_0001df70(param_3,body);
  actor_state = body->actorState;
  if (actor_state != (actorState *)0x0) {
    (*actor_state->vtable->func6)(actor_state,param_3);
  }
  return uVar1;
}




void actor::drone(actor *param_1)

{
  Buffer<> *pBVar1;
  
  pBVar1 = param_1->droneActionsBuf;
  while (pBVar1 != (Buffer<> *)0x0) {
    goToNextDroneAction(param_1);
    pBVar1 = param_1->droneActionsBuf;
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void actor::goToNextDroneAction(actor *this)

{
  actorDroneActionId id;
  DroneAction *paVar2;
  actorDroneActionId *paVar1;
  BOOL resets;
  ObjMsgID local_8;
  actor *local_4;
  Buffer<> *pvVar1;
  Buffer<> *actions;
  
  actions = this->droneActionsBuf;
  if (actions != (Buffer<> *)0x0) {
    if (actions == (Buffer<> *)0x0) {
      id = Null;
    }
    else {
      if (actions->size == actions->endOfQueue) {
        paVar2 = (DroneAction *)0x0;
      }
      else {
        paVar2 = (DroneAction *)
                 ((int)&actions->entries->actionId +
                 (uint)actions->currentDroneAction * (uint)actions->valueSize);
      }
      id = paVar2->actionId;
    }
    resets = actorDroneActionId::shouldResetBodyFlagsAfter(id);
    if (resets != 0) {
      actorBody::resetFlags();
    }
    actions = this->droneActionsBuf;
    if (actions->currentDroneAction == actions->size) {
      actions->size = actions->endOfQueue;
    }
    else {
      actions->currentDroneAction =
           (ushort)((ulonglong)(actions->currentDroneAction + 1) %
                   (ulonglong)(longlong)(int)(uint)actions->endOfQueue);
    }
    pvVar1 = this->droneActionsBuf;
    if (pvVar1->size == pvVar1->endOfQueue) {
      if (pvVar1 != (Buffer<> *)0x0) {
        free(pvVar1);
        this->droneActionsBuf = (Buffer<> *)0x0;
      }
      this->isDroning = 0;
      local_8 = Scene_ActorStoppedDroning;
      local_4 = this;
      EventLoop::DispatchMessage(&local_8);
      if (this->droneBool != false) {
        this->droneBool = false;
        updateFreezeTimers(this);
        return;
      }
    }
    else {
      actions = this->droneActionsBuf;
      if (actions == (Buffer<> *)0x0) {
        id = Null;
      }
      else {
        if (actions->size == actions->endOfQueue) {
          paVar1 = (actorDroneActionId *)0x0;
        }
        else {
          paVar1 = (actorDroneActionId *)
                   ((int)&actions->entries->actionId +
                   (uint)actions->currentDroneAction * (uint)actions->valueSize);
        }
        id = *paVar1;
      }
      resets = actorDroneActionId::shouldResetBodyFlagsAfter(id);
      if (resets != 0) {
        actorBody::resetFlags(this->body);
      }
    }
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


actorDroneActionId actor::getNextDroneAction(actor *param_1)

{
  Buffer<> *drone_data;
  
  drone_data = param_1->droneActionsBuf;
  if (drone_data == (Buffer<> *)0x0) {
    return Null;
  }
  if (drone_data->size == drone_data->endOfQueue) {
    return aRam00000000;
  }
  return *(actorDroneActionId *)
          ((int)&drone_data->entries->actionId +
          (uint)drone_data->currentDroneAction * (uint)drone_data->valueSize);
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


uint actor::searchSomeComponent(actor *act)

{
  Buffer<> *pBVar1;
  Buffer<> *drone_data;
  
  pBVar1 = act->droneActionsBuf;
  if (pBVar1 == (Buffer<> *)0x0) {
    return 0;
  }
  if (pBVar1->size == pBVar1->endOfQueue) {
    return uRam0000001c;
  }
  return *(uint *)((int)&pBVar1->entries->searchedUint +
                  (uint)pBVar1->currentDroneAction * (uint)pBVar1->valueSize);
}




BOOL actorDroneActionId::shouldResetBodyFlagsAfter(actorDroneActionId param_1)

{
  switch(param_1) {
  case Burst:
  case BurstFromWall:
  case BurstFromFloor:
  case StandNervously:
  case Dance:
  case DanceMove:
  case Nothing:
  case CelebrateLoopVulnerable:
    return 0;
  default:
    return 1;
  }
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void actor::addDroneAction(actor *param_1,actorDroneActionId id,uint param_3)

{
  Buffer<> *actions;
  BOOL BVar1;
  DroneAction *drone_action;
  vec2 *unaff_EBX;
  vec2 *unaff_EDI;
  
  if (param_1->droneActionsBuf == (Buffer<> *)0x0) {
    actions = malloc_(400);
    actions->entries = actions->_data;
    actions->valueSize = 0x20;
    actions->endOfQueue = 0xc;
    actions->end = actions + 1;
    actions->currentDroneAction = 0;
    actions->size = 0xc;
    param_1->droneActionsBuf = actions;
    BVar1 = actorDroneActionId::shouldResetBodyFlagsAfter(id);
    if (BVar1 != 0) {
      actorBody::resetFlags(param_1->body);
    }
  }
  actions = param_1->droneActionsBuf;
  if (actions->size == actions->endOfQueue) {
    actions->currentDroneAction = 0;
    actions->size = 0;
  }
  else {
    actions->size =
         (ushort)((ulonglong)(actions->size + 1) %
                 (ulonglong)(longlong)(int)(uint)actions->endOfQueue);
  }
  drone_action = (DroneAction *)
                 ((int)&actions->entries->actionId + (uint)actions->size * (uint)actions->valueSize)
  ;
  drone_action->actionId = id;
  drone_action->searchedUint = param_3;
  (drone_action->pos).x = unaff_EBX->x;
  (drone_action->pos).y = unaff_EBX->y;
  (drone_action->pos).z = unaff_EBX[1].x;
  (drone_action->pos2).x = unaff_EDI->x;
  (drone_action->pos2).y = unaff_EDI->y;
  (drone_action->pos2).z = unaff_EDI[1].x;
  param_1->isDroning = 0;
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void actor::initGhoulyBox(actor *act,actorParams *params)

{
  GhoulyBox *box;
  
  if (*(int *)params->ghoulyBoxAID == 0x5f646961) {
    if (act->ghoulyBox != (void *)0x0) {
      GhoulyBox::dtor(act->ghoulyBox);
      act->ghoulyBox = (void *)0x0;
    }
    act->ghoulyBoxResetValue = 0;
    if (params->ghoulyBoxAID != (char *)0x0) {
      box = GhoulyBox::fromAID(params->ghoulyBoxAID);
      act->ghoulyBox = box;
      if (box != (GhoulyBox *)0x0) {
        box->parentActor = act;
        box->initialised_ = 1;
        Scripting::AddGhoulySpawnToList(box,&g_ghoulyBoxes);
        return;
      }
    }
  }
  return;
}




int actor::GetGoalFlagIndexByName(char *param_1)

{
  uint uVar1;
  
  uVar1 = Events::GetIndexOfStringInTable(3,GoalFlags + 1,param_1);
  if (uVar1 == 0xffffffff) {
    return 0;
  }
  return uVar1 + 1;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


undefined4 actor::ctor(actor *act,actorParams *params)

{
  ObjectTag tag;
  float fVar1;
  actor *act_00;
  actorParams *params_00;
  ushort uVar2;
  weapon *weapon;
  actorBody *body;
  
  params_00 = params;
  act_00 = act;
  act->actorType = params->field1_0x334;
  act->field827_0xcde = params->field2_0x336;
  tag = params->field3_0x338;
  act->tag = tag;
  if (tag != Null) {
    uVar2 = nameFromObjectTag(tag);
    act_00->statsheetIndex = uVar2;
    act_00->tag = tag;
  }
  avatar::getWorldPosition(&act_00->avatar,&act_00->setup_position_);
  avatar::getWorldRotation(&act_00->avatar,&act_00->world_rot_);
  act_00->droneTriggerId = params_00->some_u16;
  runtime::rand = runtime::rand * 0x19660d + 0x3c6ef35f;
  act = (actor *)(runtime::rand & 0x7fffff | 0x3f800000);
  act_00->randFloat0_5 = ((float)act - 1.0) * 0.5;
  initialiseAttribs(act_00,params_00);
  initGhoulyBox(act_00,params_00);
  setBody(act_00,params_00->bodyObjParamsAID);
  if (*(int *)params_00->AIMindObjParamsAID == 0x5f646961) {
    setMind(act_00,params_00->AIMindObjParamsAID);
  }
  Scripting::CreateScriptType1((InputHandlerType1 **)&act);
  act_00->input_handler_ = (InputHandlerBase *)act;
  if (*(int *)params_00->strategyObjParamsAID == 0x5f646961) {
    loadStrategy(act_00,params_00->strategyObjParamsAID);
  }
  body = act_00->body;
  if (body->hasBlendTargets != 0) {
    body->field_0x90 = 2;
    body->field_0x91 = 0;
    fVar1 = BlendTargetConfig_00338ee0.field0_0x0;
    body->skipBlendTargetUpdate = true;
    body->randValue = fVar1;
    runtime::rand = runtime::rand * 0x19660d + 0x3c6ef35f;
    act = (actor *)(runtime::rand & 0x7fffff | 0x3f800000);
    body->randValue = (float)act - 1.0;
  }
  weapon = (weapon *)0x0;
  if (*(int *)params_00->startingWeaponAID == 0x5f646961) {
    weapon = handleWeaponSetup(act_00,0,params_00->startingWeaponAID);
  }
  if (((act_00->actorType == Ghoulie_old) &&
      (DAT_00510578 = DAT_00510578 + 1, weapon != (weapon *)0x0)) &&
     (((byte)DAT_0050ea98 & 0x10) != 0)) {
    weapon->field1055_0xda0 = 1;
  }
  (act_00->avatar).hasActor_ = true;
  createOnDeathObjects(&act_00->avatar,0);
  return 1;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void actor::dtor(actor *param_1)

{
  Buffer<> *pBVar1;
  ScriptType4 *script;
  actor_0x934 pNVar2;
  actor_0x93c pNVar3;
  actor_0x944 pNVar4;
  
  if (param_1->actorType == Ghoulie_old) {
    DAT_00510578 = DAT_00510578 + -1;
  }
  param_1->droneBool = false;
  pBVar1 = param_1->droneActionsBuf;
  while (pBVar1 != (Buffer<> *)0x0) {
    goToNextDroneAction(param_1);
    pBVar1 = param_1->droneActionsBuf;
  }
  loadStrategy(param_1,(char *)0x0);
  if (param_1->mind != (actorMind *)0x0) {
    Assets::DeleteResource_(param_1->mind);
    param_1->mind = (actorMind *)0x0;
  }
  script = (ScriptType4 *)param_1->input_handler_;
  if (script != (ScriptType4 *)0x0) {
    switch((script->header).type) {
    case TYPE_1:
      Scripting::FreeScript123((InputHandlerBase *)script);
      break;
    case TYPE_2:
      Scripting::FreeScript123((InputHandlerBase *)script);
      break;
    case TYPE_3:
      Scripting::FreeScript123((InputHandlerBase *)script);
      break;
    case TYPE_4_NESTED:
      Scripting::FreeScript4(script);
      break;
    case TYPE_5:
      Scripting::FreeScript5(script);
    }
  }
  if (param_1->body != (actorBody *)0x0) {
    Assets::DeleteResource_(param_1->body);
    param_1->body = (actorBody *)0x0;
  }
  if (param_1->attribs != (ActorAttribsResource *)0x0) {
    Assets::DestroyAssetOrDecrement(param_1->attribs);
    param_1->attribs = (ActorAttribsResource *)0x0;
  }
  if (param_1->ghoulyBox != (void *)0x0) {
    GhoulyBox::dtor(param_1->ghoulyBox);
    param_1->ghoulyBox = (void *)0x0;
  }
  param_1->ghoulyBoxResetValue = 0;
  pNVar2 = (param_1->node0x934).prev;
  if (pNVar2 != (actor_0x934)0x0) {
    pNVar2->next = (param_1->node0x934).next;
  }
  pNVar2 = (param_1->node0x934).next;
  if (pNVar2 != (actor_0x934)0x0) {
    pNVar2->prev = (param_1->node0x934).prev;
  }
  (param_1->node0x934).prev = (actor_0x934)0x0;
  (param_1->node0x934).next = (actor_0x934)0x0;
  pNVar3 = (param_1->node0x93c).prev;
  if (pNVar3 != (actor_0x93c)0x0) {
    pNVar3->next = (param_1->node0x93c).next;
  }
  pNVar3 = (param_1->node0x93c).next;
  if (pNVar3 != (actor_0x93c)0x0) {
    pNVar3->prev = (param_1->node0x93c).prev;
  }
  (param_1->node0x93c).prev = (actor_0x93c)0x0;
  (param_1->node0x93c).next = (actor_0x93c)0x0;
  pNVar4 = (param_1->node0x944).prev;
  if (pNVar4 != (actor_0x944)0x0) {
    pNVar4->next = (param_1->node0x944).next;
  }
  pNVar4 = (param_1->node0x944).next;
  if (pNVar4 != (actor_0x944)0x0) {
    pNVar4->prev = (param_1->node0x944).prev;
  }
  (param_1->node0x944).prev = (actor_0x944)0x0;
  (param_1->node0x944).next = (actor_0x944)0x0;
  if (param_1->field4_0x94c != 0) {
    *(undefined4 **)(param_1->field4_0x94c + 4) = param_1->field5_0x950;
  }
  if (param_1->field5_0x950 != (int *)0x0) {
    *param_1->field5_0x950 = param_1->field4_0x94c;
  }
  param_1->field4_0x94c = 0;
  param_1->field5_0x950 = (undefined4 *)0x0;
  FUN_001108b0();
  if (param_1->statsheetIndex != 0) {
    param_1->statsheetIndex = 0;
  }
  return;
}




BOOL actorIsHumanOrNoPrevLL(actor *param_1)

{
  if (param_1->actorType == Human) {
    return 1;
  }
  return (uint)((param_1->node0x93c).prev != (actor_0x93c)0x0);
}




void actor::setBody(actor *this,char *bodyAID)

{
  actorBodyParams *params;
  actorBody *pOVar1;
  
  if (this->body != (actorBody *)0x0) {
    Assets::DeleteResource_(this->body);
    this->body = (actorBody *)0x0;
  }
  if ((bodyAID != (char *)0x0) && (*(int *)bodyAID == 0x5f646961)) {
                    // Creates objparams_player_boy
    params = (actorBodyParams *)Assets::GetObjParams(bodyAID);
    params->parent = this;
    pOVar1 = (actorBody *)Assets::CreateEntityFromParams((objParams *)params);
    this->body = pOVar1;
    free(params);
    return;
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void actor::setMind(actor *param_1,char *mindAID)

{
  actorMindParams *inners;
  actorMind *paVar1;
  
  if (param_1->mind != (actorMind *)0x0) {
    Assets::DeleteResource_(param_1->mind);
    param_1->mind = (actorMind *)0x0;
  }
  if ((mindAID != (char *)0x0) && (*(int *)mindAID == 0x5f646961)) {
    inners = (actorMindParams *)Assets::GetObjParams(mindAID);
    inners->parentActor = param_1;
    paVar1 = (actorMind *)Assets::CreateEntityFromParams((objParams *)inners);
    param_1->mind = paVar1;
    free(inners);
    return;
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void __fastcall actor::loadStrategy(actor *actor,char *strategyAID)

{
  actorStrategyOffsetId id;
  actorStrategy *strategy;
  actorStrategyParams *params;
  actorStrategy *new_strat;
  
  if (actor->strategy != (actorStrategy *)0x0) {
    Assets::DeleteResource_(actor->strategy);
    actor->strategy = (actorStrategy *)0x0;
  }
  if (actor->mind != (actorMind *)0x0) {
    actorMind::removeGoals(actor->mind);
  }
  if ((strategyAID != (char *)0x0) && (*(int *)strategyAID == 0x5f646961)) {
    params = (actorStrategyParams *)Assets::GetObjParams(strategyAID);
    params->parent = actor;
                    // Leads to actorStrategy::ctor
    new_strat = (actorStrategy *)Assets::CreateEntityFromParams((objParams *)params);
    actor->strategy = new_strat;
    free(params);
    strategy = actor->strategy;
    if (strategy != (actorStrategy *)0x0) {
      id = strategy->resetState;
      (*strategy->vtable->leaveState)(strategy,strategy->id);
      strategy->id = id;
      actorMind::removeGoals(strategy->parentActor->mind);
      (*strategy->vtable->enterState)(strategy,id);
    }
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields
// Goes to entityBodyHuman::updateFixed 0x0007c8b0


void actor::onMessage(actor *act,Message *param_2)

{
  Object *body;
  actorStrategy *strategy;
  actorMind *mind;
  
  handleMessage(act,param_2);
  strategy = act->strategy;
  if (strategy != (actorStrategy *)0x0) {
    (*strategy->vtable->onMessage)(strategy,param_2);
  }
  mind = act->mind;
  if (mind != (actorMind *)0x0) {
                    // Goes to entityMindHuman::updateFixed? 0x0007c8b0
    (*mind->vtable->onMessage)(mind,param_2);
  }
  body = (Object *)act->body;
  if (body != (Object *)0x0) {
                    // Goes to entityBodyHuman::fixedUpdate? 0x00074080
    (*body->vtable->onMessage)(body,param_2);
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void actor::handleMessage(actor *act,Message *msg)

{
  actorBodyFlags *paVar1;
  int iVar2;
  ObjMsgID local_8;
  actor *local_4;
  
  local_4 = act;
  switch((msg->header).msgId) {
  case Avatar_AnimationEvent:
    FUN_00019150();
    avatar::onMessage(&act->avatar,msg);
    return;
  default:
    defaultMessageHandler(act,msg);
    break;
  case Avatar_Deflected:
    FUN_000294f0(act);
    avatar::onMessage(&act->avatar,msg);
    return;
  case Avatar_DeflectedByActor:
    onDeflected();
    avatar::onMessage(&act->avatar,msg);
    return;
  case Avatar_SceneInsert:
                    // Runs broad phase tests
    onSceneInsert(act);
    local_8 = Scene_ActorInserted;
    EventLoop::DispatchMessage(&local_8);
    avatar::onMessage(&act->avatar,msg);
    return;
  case Actor_DeflectionContact:
    paVar1 = act->body->flagSet->flags;
    *(undefined1 *)&paVar1->flag1 = (char)paVar1->flag1 | AnimTrigger;
    avatar::onMessage(&act->avatar,msg);
    return;
  case Scene_ActorHit:
  case Scene_ActorHitInvulnerable:
    if ((((msg->header).someActor == act) && (msg[1].header.msgId != Null)) &&
       (iVar2 = FUN_000196d0(), iVar2 != 0)) {
      FUN_00019660(0);
      avatar::onMessage(&act->avatar,msg);
      return;
    }
    break;
  case Scene_AvatarRemoved:
    if ((msg->header).someActor == act) {
      local_8 = Scene_ActorRemoved;
      EventLoop::DispatchMessage(&local_8);
      avatar::onMessage(&act->avatar,msg);
      return;
    }
    break;
  case Scene_Begin:
    FUN_00029490(act);
    avatar::onMessage(&act->avatar,msg);
    return;
  case Ghouly_InsertFromAid:
    FUN_00028700();
    avatar::onMessage(&act->avatar,msg);
    return;
  case Ghouly_InsertWeapon:
    FUN_00028770();
    avatar::onMessage(&act->avatar,msg);
    return;
  case Ghouly_InsertPowerup:
    FUN_000287c0();
    avatar::onMessage(&act->avatar,msg);
    return;
  }
  avatar::onMessage(&act->avatar,msg);
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void actor::onSceneInsert(actor *act)

{
  int *piVar1;
  Node<> *pNVar2;
  actor_0x934 pNVar3;
  int *piVar4;
  actor_0x944 pNVar5;
  Buffer<> *pBVar6;
  List<>_conflict3 *pLVar7;
  Node<> *bodyLL;
  int *piVar8;
  List<>_conflict3 *pLVar9;
  actor_0x944 pNVar10;
  uint uVar11;
  int iVar12;
  actorDroneActionId *paVar13;
  undefined4 local_10;
  vec3 local_c;
  actor_0x934 actor_ptr;
  
  actor_ptr = &act->node0x934;
  pLVar7 = &Game::SceneInfo.actors_0x934;
  pNVar3 = (actor_0x934)Game::SceneInfo.actors_0x934.next;
  while (pNVar3 != (actor_0x934)0x0) {
    pLVar7 = (List<>_conflict3 *)pLVar7->next;
    pNVar3 = (actor_0x934)pLVar7->next;
  }
  pNVar3 = (actor_0x934)pLVar7->head;
  pLVar7->head = (actor_0x934_conflict5)actor_ptr;
  actor_ptr->prev = (actor_0x934)pLVar7;
  (act->node0x934).next = pNVar3;
  if (pNVar3 != (actor_0x934)0x0) {
    pNVar3->prev = actor_ptr;
  }
  if (act->actorType == Ghoulie_old) {
    pNVar2 = &act->node0x944;
    pNVar10 = (actor_0x944)&Game::SceneInfo.field22_0xa4;
    pNVar5 = Game::SceneInfo.field22_0xa4;
    while (pNVar5 != (actor_0x944)0x0) {
      pNVar10 = pNVar10->prev;
      pNVar5 = pNVar10->prev;
    }
    pNVar5 = pNVar10->next;
    pNVar10->next = pNVar2;
    pNVar2->prev = pNVar10;
    (act->node0x944).next = pNVar5;
    if (pNVar5 != (actor_0x944)0x0) {
      pNVar5->prev = pNVar2;
    }
  }
  else if (act->actorType == Human) {
    piVar1 = &act->field4_0x94c;
    piVar8 = &Game::SceneInfo.field24_0xac;
    iVar12 = Game::SceneInfo.field24_0xac;
    while (iVar12 != 0) {
      piVar8 = (int *)*piVar8;
      iVar12 = *piVar8;
    }
    piVar4 = (int *)piVar8[1];
    piVar8[1] = (int)piVar1;
    *piVar1 = (int)piVar8;
    act->field5_0x950 = piVar4;
    if (piVar4 != (int *)0x0) {
      *piVar4 = (int)piVar1;
    }
    pLVar9 = (List<>_conflict3 *)0x511b3c;
    if (Game::SceneInfo.playerActors.prev != (actor_0x93c_conflict5)0x0) {
      pLVar9 = &Game::SceneInfo.playerActors;
      do {
        pLVar9 = (List<>_conflict3 *)pLVar9->prev;
      } while (pLVar9->prev != (actor_0x93c_conflict5)0x0);
    }
    pLVar9->prev = (actor_0x93c_conflict5)&act->node0x93c;
    (act->node0x93c).prev = (actor_0x93c)pLVar9;
    (act->node0x93c).next = (actor_0x93c)0x0;
  }
  avatar::getWorldPosition(&act->avatar,&act->setup_position_);
  avatar::getWorldRotation(&act->avatar,&act->world_rot_);
  if (((act->avatar).field218_0x1fc != 0) &&
     ((act->actorType == Ghoulie_old || (act->actorType == 4)))) {
    avatar::getWorldPosition(&act->avatar,&local_c);
    uVar11 = FUN_001248d0(2,0,Null);
    if (uVar11 != 0) {
      act->skipObjectTypeLookup = uVar11;
    }
  }
  if ((act->actorType == Ghoulie_old) || (act->actorType == 4)) {
    avatar::getWorldPosition(&act->avatar,&local_c);
    uVar11 = FUN_001248d0(4,0,(act->avatar).tag);
    if (uVar11 != 0) {
      act->field812_0xca4 = uVar11;
    }
  }
  iVar12 = 0;
  if (0 < (int)g_AssetBodySearchList._116_4_) {
    do {
      if ((act->avatar).tag == g_AssetBodySearchList[iVar12 + 0x3c]) {
        act->rand2 = true;
        act->rand3 = 0;
        act->rand4 = false;
        if (0.0 < act->cowardTimer) {
          act->cowardTimer = 0.0;
          local_10 = 0x55;
          (*((act->avatar).vtable)->onMessage)(act,&local_10);
        }
        break;
      }
      iVar12 = iVar12 + 1;
    } while (iVar12 < (int)g_AssetBodySearchList._116_4_);
  }
  pBVar6 = act->droneActionsBuf;
  if (pBVar6 != (Buffer<> *)0x0) {
    if (pBVar6->size == pBVar6->endOfQueue) {
      paVar13 = (actorDroneActionId *)0x0;
    }
    else {
      paVar13 = (actorDroneActionId *)
                ((int)&pBVar6->entries->actionId +
                (uint)pBVar6->currentDroneAction * (uint)pBVar6->valueSize);
    }
    if (*paVar13 != Null) {
      act->droneBool = true;
      goto LAB_0002946d;
    }
  }
  updateFreezeTimers(act);
LAB_0002946d:
  avatar::getWorldPosition(&act->avatar,&local_c);
  uVar11 = FUN_00110bf0(&local_c,-1,0);
  act->backgroundCollisionIndex = uVar11;
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void actor::onDeflected(void)

{
  int *unaff_ESI;
  int unaff_EDI;
  undefined4 local_c;
  
  local_c = 0x2d;
  (**(code **)(*unaff_ESI + 0xc))();
  (**(code **)(**(int **)(unaff_EDI + 4) + 0xc))(*(int **)(unaff_EDI + 4),&local_c);
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


MindActionReturnCode actorMind::executeGoal(actorMind *mind,actorMindGoal *action)

{
  actor *act;
  actorBodyStateId aVar1;
  BOOL pass;
  undefined4 extraout_EAX;
  Mind51 *pMVar2;
  int iVar3;
  float distance;
  actorMindGoal *paVar4;
  float dist;
  float fVar5;
  float2 fVar6;
  undefined4 calloutIndex;
  actorMindGoal *paVar7;
  vec3 this_pos;
  actorBody *mind_target;
  actorBody *body;
  actorMind *mindd;
  
  paVar4 = action;
  mindd = mind;
  act = mind->actor;
  body = act->body;
  switch(action->goalId) {
  case BeginScript:
    setGoalFromScript(mind,(char *)(action + 1));
    return StopAndRemoveSelf;
  case CalloutExec:
    calloutIndex = 0;
    fVar6 = (float2)Callout::getByName(action + 1);
    ::actor::executeCallout(act,calloutIndex,SUB42((float)fVar6,0));
    return Success;
  default:
    goto switchD_0002960f_caseD_7;
  case ClearGoals:
    pass = Random::thresholdCheck(&runtime::rand,action[1].prev);
    return (-(uint)(pass != 0) & 2) + Success;
  case ClearGoalsIfExitStatus:
    return (-(uint)((actorMindGoal *)mind->actionReturnCode != action[1].prev) & 0xfffffffe) +
           StopAndRemoveAllGoals;
  case ClearGoalsIfFarFromTarget:
    mind = (actorMind *)mind->targetBody;
    if ((actorBody *)mind != (actorBody *)0x0) {
      avatar::getWorldPosition(&act->avatar,&this_pos);
      this_pos.z = this_pos.z - (float)mind->memoryHead;
      distance = this_pos.x - *(float *)&mind->field_0x20;
      dist = this_pos.z * this_pos.z + distance * distance;
      if (paVar4[1].next == (actorMindGoal *)0x0) {
        distance = (act->body->actor->avatar).scale.z * act->body->closenessDistance + mind->minF;
        mind = (actorMind *)dist;
      }
      else {
        mind = (actorMind *)dist;
        FUN_001416d0(act);
      }
      fVar5 = (float)paVar4[1].prev + distance;
      if ((float)mind <= fVar5 * fVar5) {
        return Success;
      }
    }
    return StopAndRemoveAllGoals;
  case DisableDamage:
    actorBody::setFlagById(body,DisableDamage,action[1].prev);
    return Success;
  case ScaleActor:
    avatar::setScaleUniform(&act->avatar,(act->avatar).scale.z * (float)action[1].prev);
    avatar::updateBaseTransform(&act->avatar);
    mind = (actorMind *)0x4a;
                    // Runs an Actor_PushOut message
    (*((act->avatar).vtable)->onMessage)(act,&mind);
    return Success;
  case SetAttackState:
    aVar1 = actorBodyStateId::fromString(action + 1);
    mindd->currentAttackTarget = mindd->targetBody;
    pass = actorBody::findAndUseAttack(body,aVar1);
    if (pass != 0) {
      return Success;
    }
    mind->currentAttackTarget = (actorBody *)0x0;
    return Success;
  case SetBodyFlag:
    fVar5 = (float)actorBody::getFlagIdByName((char *)(action + 1));
    actorBody::setFlag(body,CONCAT31((int3)((uint)extraout_EAX >> 8),(unkfloat1)fVar5));
    return Success;
  case SetGoalFlag:
    this_pos.y = 0.0;
    this_pos.z = 0.0;
    this_pos.x = 8.26766e-44;
    this_pos.z = (float)::actor::GetGoalFlagIndexByName(action + 1);
                    // Dispatch Actor_GoalFlagSet message
    (*((act->avatar).vtable)->onMessage)(act,&this_pos);
    return (uint)(this_pos.y != 0.0) * 2 + Success;
  case SetNoAttackTimer:
    paVar4 = action[1].next;
    FUN_000191c0();
    body->noAttackTimer = (float)paVar4;
    return Success;
  case SetState:
    goto switchD_0002960f_caseD_1f;
  case SetStateIfAnimIsAtEnd:
                    // Triggered on kicking imp?
    pass = avatar::updateKeyframes(&act->avatar,(int)action[1].prev);
    if (pass == 0) {
      return StopAndUpdateT;
    }
    aVar1 = actorBodyStateId::fromString(&paVar4[1].next);
    actorBody::setState(body,aVar1);
    return Success;
  case SetStateIfFlag:
    paVar7 = action[8].prev;
    actorBody::getFlagIdByName((char *)(action + 5));
    iVar3 = FUN_0001ef40(paVar7);
    if (iVar3 == 0) {
      if (paVar4[8].next != (actorMindGoal *)0x0) {
        return StopAndUpdateT;
      }
      return Success;
    }
    goto switchD_0002960f_caseD_1f;
  case SetStateIfFlagRnd:
    paVar7 = action[8].prev;
    actorBody::getFlagIdByName((char *)(action + 5));
    iVar3 = FUN_0001ef40(paVar7);
    if (iVar3 == 0) {
      iVar3._0_2_ = paVar4[8].goalId;
      iVar3._2_1_ = paVar4[8].initialised;
      iVar3._3_1_ = paVar4[8].field4_0xb;
      if (iVar3 != 0) {
        return StopAndUpdateT;
      }
      return Success;
    }
    pass = Random::thresholdCheck(&runtime::rand,paVar4[8].next);
    if (pass == 0) {
      return Success;
    }
switchD_0002960f_caseD_1f:
    aVar1 = actorBodyStateId::fromString(paVar4 + 1);
    actorBody::setState(body,aVar1);
    return Success;
  case StandIdle:
    aVar1 = (*body->vtable->getIdleState)(body);
    if ((aVar1 != Null) && (iVar3 = FUN_00027620(), iVar3 != 0)) {
      actorBody::setState(body,aVar1);
      return Success;
    }
    return ErrorGettingEvasionPos;
  case UpdateWeaponOfAttention:
    pMVar2 = (Mind51 *)FUN_00129c20(0,0x1f);
    mindd->mind51 = pMVar2;
    return Success;
  case Wait:
    if (action->t < *(float *)&action[1].goalId) {
      return StopAndUpdateT;
    }
    return Success;
  case WaitForFlag:
    paVar4 = action[4].prev;
    actorBody::getFlagIdByName((char *)(action + 1));
    iVar3 = FUN_0001ef40(paVar4);
    break;
  case WaitUntilCanAttack:
    iVar3 = actorBody::setWaitUntilCanAttack(body,(int)action[1].prev);
    break;
  case WaitUntilInputEnabled:
    iVar3 = FUN_00024c20(body);
  }
  if (iVar3 == 0) {
    return StopAndUpdateT;
  }
switchD_0002960f_caseD_7:
  return Success;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void actorMind::initObjects(actorMind *mind,actorMindParams *params)

{
  int i;
  
  mind->flags = params->field4_0x90;
  mind->field37_0x68 = params->field5_0x94;
  mind->floatFromTagList = params->defaultFloatFromTagList;
  i = 0;
  if (0 < NumObjectTypes) {
    while ((mind->actor->avatar).tag != ObjectTypes[i].tag) {
      i = i + 1;
      if (NumObjectTypes <= i) {
        return;
      }
    }
    mind->floatFromTagList = (float)ObjectTypes[i].field1_0x2;
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


uint32_t actorMind::doTraitorStuffOrFight(actorMind *mind,actorBody *target,BOOL param_3)

{
  weapon *av;
  uint uVar1;
  uint uVar2;
  BOOL BVar3;
  int iVar4;
  
  if (*(char *)&(target->worldPosition).x != '\0') {
    return 0;
  }
  uVar1 = mind->flags;
  if ((param_3 != 0) &&
     ((0.0 < mind->actor->traitorTimer || (mind->actor->randTraitoristicCombat != '\0')))) {
    uVar1 = uVar1 & 0xfffffffb | 0x10;
  }
  av = (weapon *)mind->actor;
  uVar2 = uVar1 & 0xffffff5f | 0b00001000;
  if ((target->currentWeapon != av) &&
     ((mind->field37_0x68 & 1 << (*(byte *)&target->largeProjectile & 0x1f)) != 0)) {
    BVar3 = actorBody::isTargetable(target,(char)uVar2,(char)((uVar1 & 0xffffff5f) >> 8));
    if (BVar3 != 0) {
      iVar4 = avatar::canTargetBody(av,0,target,uVar2);
      return (uint)(iVar4 != 0);
    }
  }
  return 0;
}




void actorMind::getAllocDetails(ObjectAllocDetails *param_1)

{
  param_1->entitySize = 0x7c;
  param_1->paramsSize = 0xa0;
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


ObjectFullVTable * actorMind::GetVTable(void)

{
  vtable.getAllocDetails = getAllocDetails;
  vtable.ctor = ctor;
  vtable.dtor = dtor;
  vtable.onMessage = onMessage;
  vtable.update = update;
  vtable.executeGoal = executeGoal;
  vtable.initialiseGoal = initialiseGoal;
  vtable.onRemoveAction = switchD_000d4179::EmptyFunction;
  return (ObjectFullVTable *)&vtable;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


actorMindGoal * actorMind::allocAction(actorMind *mind,actorMindFlagId goalType)

{
  actorMindGoal *new_goal;
  actorGoalInfo *curr_goal;
  uint uVar1;
  uint i;
  actorMindGoal *mem_2;
  uint size;
  
  size = actionAllocDetails[goalType].mallocSize;
  new_goal = malloc_(size);
  mem_2 = (actorMindGoal *)0x0;
  if (new_goal != (actorMindGoal *)0x0) {
    mem_2 = new_goal;
                    // Memset 0
    for (uVar1 = size >> 2; uVar1 != 0; uVar1 = uVar1 - 1) {
      mem_2->prev = (actorMindGoal *)0x0;
      mem_2 = (actorMindGoal *)&mem_2->next;
    }
    for (i = size & 3; i != 0; i = i - 1) {
      *(undefined1 *)&mem_2->prev = 0;
      mem_2 = (actorMindGoal *)((int)&mem_2->prev + 1);
    }
    curr_goal = &mind->actionInfo;
    new_goal->goalId = goalType;
    new_goal->prev = (actorMindGoal *)0x0;
    new_goal->next = (actorMindGoal *)0x0;
    mem_2 = (actorMindGoal *)(mind->actionInfo).next;
    while (mem_2 != (actorMindGoal *)0x0) {
      curr_goal = (actorGoalInfo *)((actorMindGoal *)curr_goal)->next;
      mem_2 = ((actorMindGoal *)curr_goal)->next;
    }
    ((actorMindGoal *)curr_goal)->next = new_goal;
    new_goal->prev = (actorMindGoal *)curr_goal;
    new_goal->next = (actorMindGoal *)0x0;
    mem_2 = new_goal;
  }
  return mem_2;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void removeAction(actorMind *mind,actorMindGoal *action)

{
  undefined4 uVar1;
  int iVar2;
  HeapTableEntry *pHVar3;
  
  if (action->initialised != false) {
    (*mind->vtable->onRemoveAction)(mind,action);
  }
  if (action->prev != (actorMindGoal *)0x0) {
    action->prev->next = action->next;
  }
  if (action->next != (actorMindGoal *)0x0) {
    action->next->prev = action->prev;
  }
  action->prev = (actorMindGoal *)0x0;
  action->next = (actorMindGoal *)0x0;
  iVar2 = FindHeapOf(action);
  uVar1 = runtime::CurrentHeapToAllocateFrom;
  if (g_HeapTableBase[iVar2].heapHandle == (HANDLE)0x0) {
    pHVar3 = (HeapTableEntry *)0x0;
  }
  else {
    pHVar3 = g_HeapTableBase + iVar2;
  }
  runtime::CurrentHeapToAllocateFrom = iVar2;
  XAPILIB::HeapFree(pHVar3->heapHandle,0,action);
  runtime::CurrentHeapToAllocateFrom = uVar1;
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void actorMind::removeGoals(actorMind *mind)

{
  actorMindGoal *action;
  actorMindGoal *next;
  
  action = (actorMindGoal *)(mind->actionInfo).next;
  while (action != (actorMindGoal *)0x0) {
    next = action->next;
    if (action->prev != (actorMindGoal *)0x0) {
      action->prev->next = next;
    }
    if (action->next != (actorMindGoal *)0x0) {
      action->next->prev = action->prev;
    }
    action->prev = (actorMindGoal *)0x0;
    action->next = (actorMindGoal *)0x0;
    removeAction(mind,action);
    action = next;
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


undefined4 actorMind::initialiseGoal(actorMind *param_1,actorMindGoal *param_2)

{
  if (param_2->goalId == Wait) {
    runtime::rand = runtime::rand * 0x19660d + 0x3c6ef35f;
    *(float *)&param_2[1].goalId =
         ((float)param_2[1].next - (float)param_2[1].prev) *
         ((float)(runtime::rand & 0x7fffff | 0x3f800000) - 1.0) + (float)param_2[1].prev;
  }
  return 1;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


BOOL actorMind::ctor(actorMind *mind,actorMindParams *params)

{
  AssetHeader *st_header;
  char *st_name;
  
  mind->actor = params->parentActor;
  runtime::rand = runtime::rand * 0x19660d + 0x3c6ef35f;
  mind->ranValue =
       (params->maxRan - params->minRan) * ((float)(runtime::rand & 0x7fffff | 0x3f800000) - 1.0) +
       params->minRan;
  initObjects(mind,params);
  *(undefined4 *)&mind->field_0x3c = 0;
  st_name = params->scripttableAID;
  *(undefined4 *)&mind->field_0x4c = 0x40;
  if (*(int *)st_name == 0x5f646961) {
    if ((st_name != (char *)0x0) && (*(int *)st_name == 0x5f646961)) {
      st_header = Assets::FindAssetHeader(st_name,1);
      if (st_header != (AssetHeader *)0x0) {
        mind->scripttableRes = st_header->dataPtr;
        return 1;
      }
    }
    mind->scripttableRes = (ScripttableResource *)0x0;
  }
  return 1;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void actorMind::dtor(actorMind *param_1)

{
  removeGoals(param_1);
  func_0x0002a240();
  if (param_1->astarShit != (astruct_32 *)0x0) {
    FUN_00036b60();
    param_1->astarShit = (astruct_32 *)0x0;
  }
  if (param_1->scripttableRes != (ScripttableResource *)0x0) {
    param_1->scripttableRes = (ScripttableResource *)0x0;
  }
  return;
}




void __fastcall FUN_0002a0c0(undefined4 param_1,actorMind *param_2)

{
  MindMemoryHeader *pMVar1;
  int unaff_EDI;
  
  pMVar1 = param_2->memoryHead;
  do {
    if (pMVar1 == (MindMemoryHeader *)0x0) {
LAB_0002a0dd:
      pMVar1 = actorMind::addMemory(param_2,TargetHistory,20.0);
      pMVar1[1].prev = *(MindMemoryHeader **)(unaff_EDI + 0x10);
      return;
    }
    if (pMVar1->memId == TargetHistory) {
      do {
        if (pMVar1[1].prev == *(MindMemoryHeader **)(unaff_EDI + 0x10)) {
          actorMind::removeMemory(param_2,pMVar1);
          return;
        }
        pMVar1 = pMVar1->next;
        while( true ) {
          if (pMVar1 == (MindMemoryHeader *)0x0) goto LAB_0002a0dd;
          if (pMVar1->memId == TargetHistory) break;
          pMVar1 = pMVar1->next;
        }
      } while( true );
    }
    pMVar1 = pMVar1->next;
  } while( true );
}




MindMemoryHeader * actorMind::addMemory(actorMind *mind,actorMindMemoryId memoryId,float param_3)

{
  MindMemoryHeader *new_memory;
  uint uVar1;
  uint uVar2;
  MindMemoryHeader *tail;
  MindMemoryHeader *cur;
  MindMemoryHeader *next;
  
  if ((MemoryIds[memoryId].isSingleton & 1U) != 0) {
    for (cur = mind->memoryHead; cur != (MindMemoryHeader *)0x0; cur = cur->next) {
      if (cur->memId == memoryId) {
        cur = removeMemory(mind,cur);
        return cur;
      }
    }
  }
  uVar2 = MemoryIds[memoryId].memorySize;
  new_memory = malloc_(uVar2);
  cur = (MindMemoryHeader *)0x0;
  if (new_memory != (MindMemoryHeader *)0x0) {
    cur = new_memory;
    for (uVar1 = uVar2 >> 2; uVar1 != 0; uVar1 = uVar1 - 1) {
      cur->prev = (MindMemoryHeader *)0x0;
      cur = (MindMemoryHeader *)&cur->next;
    }
    for (uVar2 = uVar2 & 3; uVar2 != 0; uVar2 = uVar2 - 1) {
      *(undefined1 *)&cur->prev = 0;
      cur = (MindMemoryHeader *)((int)&cur->prev + 1);
    }
    new_memory->memId = memoryId;
    new_memory->timeUntilInactive = param_3;
    new_memory->floatParam2 = param_3;
    new_memory->mainTimer = mind->ranValue;
    cur = (MindMemoryHeader *)&mind->memorySentinel;
    next = mind->memorySentinel;
    while (next != (MindMemoryHeader *)0x0) {
      cur = cur->prev;
      next = cur->prev;
    }
    tail = cur->next;
    cur->next = new_memory;
    new_memory->prev = cur;
    new_memory->next = tail;
    cur = new_memory;
    if (tail != (MindMemoryHeader *)0x0) {
      tail->prev = new_memory;
    }
  }
  return cur;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


MindMemoryHeader * actorMind::removeMemory(actorMind *mind,MindMemoryHeader *memory)

{
  MindMemoryHeader *pMVar1;
  MindMemoryHeader *pMVar2;
  
  memory->timeUntilInactive = memory->floatParam2;
  memory->mainTimer = mind->ranValue;
  memory->timeInactive2 = 0.0;
  memory->field_0xa = 0;
  if (memory->prev != (MindMemoryHeader *)0x0) {
    memory->prev->next = memory->next;
  }
  if (memory->next != (MindMemoryHeader *)0x0) {
    memory->next->prev = memory->prev;
  }
  pMVar2 = (MindMemoryHeader *)&mind->memorySentinel;
  memory->prev = (MindMemoryHeader *)0x0;
  memory->next = (MindMemoryHeader *)0x0;
  pMVar1 = *(MindMemoryHeader **)pMVar2;
  while (pMVar1 != (MindMemoryHeader *)0x0) {
    pMVar2 = pMVar2->prev;
    pMVar1 = pMVar2->prev;
  }
  pMVar1 = pMVar2->next;
  pMVar2->next = memory;
  memory->prev = pMVar2;
  memory->next = pMVar1;
  if (pMVar1 != (MindMemoryHeader *)0x0) {
    pMVar1->prev = memory;
  }
  return memory;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void actorMind::onMessage(actorMind *param_1,Message *param_2)

{
  undefined4 local_8;
  undefined4 local_4;
  
  switch((param_2->header).msgId) {
  case Scene_ActorHit:
    if (param_2[1].header.msgId != Null) {
      FUN_0002a3e0((param_2->header).someActor,param_2[2].header.msgId);
      return;
    }
    break;
  case Scene_ActorHitDefensive:
  case Scene_ActorHitInvulnerable:
  case Scene_ActorInserted:
  case Scene_ActorKnockDownHitWall:
  case Scene_ActorLostWeapon:
  case Scene_ActorPickedUpWeapon:
  case Scene_ActorRecoveredFromStun:
  case Scene_ActorRemoved:
  case Scene_ActorScaredBegin:
  case Scene_ActorScaredEnd:
  case Scene_ActorStoppedDroning:
  case Scene_AvatarCreatedFromProjectile:
  case Scene_AvatarInserted:
  case Scene_Begin:
  case Scene_CutsceneAlloc:
  case Scene_CutsceneFree:
  case Scene_EventBegin:
  case Scene_EventComplete:
  case Scene_EventEnd:
  case Scene_EventFailed:
  case Scene_PowerupActivated:
  case Scene_PowerupDeactivated:
  case Scene_Prepare:
  case Scene_Sfx_Started:
  case Scene_Sfx_Finished:
  case Scene_Sfx_UpdatePos:
  case Scene_Sfx_UpdateDir:
    break;
  case Scene_AvatarRemoved:
    FUN_0002a460();
    return;
  case Scene_End:
    if (param_1->targetBody != (actorBody *)0x0) {
      local_8 = 100;
      local_4 = 0;
      (*((param_1->actor->avatar).vtable)->onMessage)(param_1->actor,&local_8);
    }
    param_1->targetBody = (actorBody *)0x0;
    return;
  case Scene_LookAtRemoved:
    if (*(actor **)&param_1->field_0x30 == (param_2->header).someActor) {
      *(undefined4 *)&param_1->field_0x30 = 0;
      param_1->t = 0.0;
      param_1->minF = 0.0;
      return;
    }
    break;
  case Scene_TargetRemoved:
    FUN_0002a5a0();
    break;
  default:
    goto switchD_0002a2fe_default;
  }
switchD_0002a2fe_default:
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields

void __fastcall

FUN_0002a3e0(undefined4 param_1,actorMind *param_2,MindMemoryHeader *param_3,float param_4)

{
  MindMemoryHeader *pMVar1;
  MindMemoryHeader *unaff_ESI;
  
  pMVar1 = param_2->memoryHead;
  do {
    if (pMVar1 == (MindMemoryHeader *)0x0) {
LAB_0002a3ff:
      pMVar1 = actorMind::addMemory(param_2,FoeLastHitBy,2.0);
      *(undefined4 *)&pMVar1[1].memId = 1;
      pMVar1[1].prev = param_3;
      pMVar1[1].next = unaff_ESI;
      pMVar1[1].timeUntilInactive = param_4;
      return;
    }
    if (pMVar1->memId == FoeLastHitBy) {
      do {
        if ((pMVar1[1].prev == param_3) && (pMVar1[1].next == unaff_ESI)) {
          pMVar1[1].timeUntilInactive = param_4;
          pMVar1[1].next = unaff_ESI;
          *(int *)&pMVar1[1].memId = *(int *)&pMVar1[1].memId + 1;
          actorMind::removeMemory(param_2,pMVar1);
          return;
        }
        pMVar1 = pMVar1->next;
        while( true ) {
          if (pMVar1 == (MindMemoryHeader *)0x0) goto LAB_0002a3ff;
          if (pMVar1->memId == FoeLastHitBy) break;
          pMVar1 = pMVar1->next;
        }
      } while( true );
    }
    pMVar1 = pMVar1->next;
  } while( true );
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void actorMind::updateBodyGoal(actorMind *mind)

{
  TargetDistance distance;
  actorBody *extraout_ECX;
  float delta;
  float speed;
  actorBody *body;
  
  body = mind->actor->body;
  if (runtime::dx_timer <= 0.0) {
    delta = runtime::DeltaTime * runtime::TimeScale;
  }
  else {
    delta = 0.0;
  }
  speed = 0.0;
  if ((body->actor->avatar).movementFreezeTimer <= 0.0) {
    speed = (body->actor->avatar).actionSpeed;
  }
  if ((0.0 < mind->targetTimer) &&
     (delta = mind->targetTimer - speed * delta, mind->targetTimer = delta, delta <= 0.0)) {
    mind->targetTimer = 0.0;
  }
  switch(*(undefined4 *)&mind->field_0x4c) {
  case 0x40:
    body->bodyGoal = New_Name;
    return;
  case 0x41:
    distance = getTargetDistance(&mind->field_0x4c);
    extraout_ECX->bodyGoal = distance;
    return;
  case 0x42:
                    // Within a certain range of ghoulie
    body->bodyGoal = InTargetRange?;
    return;
  case 0x43:
    body->bodyGoal = New_Name_(9);
    return;
  case 0x44:
                    // 7 = looking straight ahead (or hitting)
    body->bodyGoal = Hitting?;
    return;
  case 0x45:
                    // 8 means focused on something, staring
    body->bodyGoal = Focused?;
    return;
  case 0x46:
    body->bodyGoal = New_Name_(6);
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


TargetDistance actorMind::getTargetDistance(actorMindStateTypePtr param_1)

{
  TargetDistance TVar1;
  
  if (ADJ(param_1)->targetTimer <= 5.0 && ADJ(param_1)->targetTimer != 5.0) {
    return VeryClose;
  }
  TVar1 = Close;
  if (10.0 < ADJ(param_1)->targetTimer || ADJ(param_1)->targetTimer == 10.0) {
    TVar1 = Far;
  }
  return TVar1;
}




BOOL actorMind::setGoalFromScript(actorMind *mind,char *goalName)

{
  char *pcVar2;
  int iVar3;
  char *res_name;
  uint i;
  actorMindGoal *paVar5;
  short goal_size;
  uint uVar1;
  ActorGoalsResource *script_ptr;
  ActorGoalsResource *pAVar8;
  ActorGoalsResource *goal_script;
  ScripttableResource *psVar3;
  uint size;
  
  psVar3 = mind->scripttableRes;
  if (psVar3 != (ScripttableResource *)0x0) {
    pcVar2 = _strchr(goalName,L'?');
    if (pcVar2 == (char *)0x0) {
      iVar3 = GetMatchesInScriptTable___(goalName,psVar3);
    }
    else {
      iVar3 = FUN_0002a810(pcVar2,goalName);
    }
    if (((iVar3 != 0) && (res_name = (char *)(iVar3 + 4), res_name != (char *)0x0)) &&
       (*(int *)res_name == 0x5f646961)) {
                    // aid_actorgoals_ghoulies_grimreaper_dizzy
      Assets::GetResourceBytes(res_name,&goal_script);
      script_ptr = goal_script;
      if (goal_script != (ActorGoalsResource *)0x0) {
        i = Events::GetIndexOfStringInTable(49,GoalIds + 1,goal_script->mindFlagId);
        pAVar8 = script_ptr;
        if (i != 0xffffffff) {
          i = i + 1;
          goal_size = (short)i;
          while (goal_size != 0) {
            uVar1 = (uint)(ushort)script_ptr->unsure;
            if ((((actorMindFlagId)i < (WalkToWeaponOfAttention|AttackTarget)) &&
                (size = uVar1 - 0x44, size != 0)) &&
               (size == (actionAllocDetails[i & 0xffff].mallocSize -
                        actionAllocDetails[i & 0xffff].idk) - 0x10)) {
              paVar5 = allocAction(mind,(actorMindFlagId)i);
              memcpy(paVar5 + 1,script_ptr + 1,size);
            }
            script_ptr = (ActorGoalsResource *)(script_ptr->mindFlagId + (uVar1 - 4));
            i = Events::GetIndexOfStringInTable(49,GoalIds + 1,script_ptr->mindFlagId);
            pAVar8 = goal_script;
            if (i == 0xffffffff) break;
            i = i + 1;
            goal_size = (short)i;
          }
        }
        Assets::DestroyAssetOrDecrement(pAVar8);
        return 1;
      }
      runtime::ExitGame(2);
    }
  }
  return 0;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void actorMind::update(actorMind *mind)

{
  float speed;
  float delta;
  
  runNextAction(mind);
  updateMemoryTimers(mind);
  speed = 0.0;
  if (runtime::dx_timer <= 0.0) {
    delta = runtime::DeltaTime * runtime::TimeScale;
  }
  else {
    delta = 0.0;
  }
  if ((mind->actor->avatar).movementFreezeTimer <= 0.0) {
    speed = (mind->actor->avatar).actionSpeed;
  }
  mind->t = speed * delta + mind->t;
  updateBodyGoal(mind);
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void actorMind::runNextAction(actorMind *mind)

{
  BOOL init_success;
  MindActionReturnCode iVar1;
  actorMindGoal *action;
  actorMindGoal *next_action;
  float actionSpeed;
  float delta;
  actorMindVTable *vtable;
  
  actionSpeed = 0.0;
  vtable = mind->vtable;
  if (runtime::dx_timer <= 0.0) {
    delta = runtime::DeltaTime * runtime::TimeScale;
  }
  else {
    delta = 0.0;
  }
  if ((mind->actor->avatar).movementFreezeTimer <= 0.0) {
    actionSpeed = (mind->actor->avatar).actionSpeed;
  }
  action = (actorMindGoal *)(mind->actionInfo).next;
  if (action == (actorMindGoal *)0x0) {
    return;
  }
  do {
    if (action->initialised == false) {
      init_success = (*vtable->initialiseGoal)(mind,action);
      action->initialised = (bool)(action->initialised + '\x01');
      if (init_success != 0) goto LAB_0002aaec;
      next_action = action->next;
      removeAction(mind,action);
    }
    else {
LAB_0002aaec:
                    // Goes to 0x0007c417
      iVar1 = (*vtable->executeGoal)(mind,action);
      if (iVar1 == StopAndRemoveAllGoals) {
        mind->actionReturnCode = StopAndRemoveAllGoals;
        removeGoals(mind);
        return;
      }
      action->t = actionSpeed * delta + action->t;
      if (iVar1 == StopAndUpdateT) {
        return;
      }
      mind->actionReturnCode = iVar1;
      next_action = action->next;
      removeAction(mind,action);
      if (iVar1 == StopAndRemoveSelf) {
        return;
      }
    }
    action = next_action;
    if (next_action == (actorMindGoal *)0x0) {
      return;
    }
  } while( true );
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void actorMind::updateMemoryTimers(actorMind *this)

{
  MindMemoryTargetWantedToAttack *mem;
  float fVar1;
  float delta;
  MindMemoryTargetWantedToAttack *next_mem;
  
  if (runtime::dx_timer <= 0.0) {
    fVar1 = runtime::DeltaTime * runtime::TimeScale;
  }
  else {
    fVar1 = 0.0;
  }
  delta = 0.0;
  if ((this->actor->avatar).movementFreezeTimer <= 0.0) {
    delta = (this->actor->avatar).actionSpeed;
  }
  delta = delta * fVar1;
  mem = (MindMemoryTargetWantedToAttack *)this->memoryHead;
  while (mem != (MindMemoryTargetWantedToAttack *)0x0) {
    fVar1 = (mem->header).mainTimer;
    next_mem = (MindMemoryTargetWantedToAttack *)(mem->header).next;
    if ((0.0 < fVar1) && (fVar1 = fVar1 - delta, (mem->header).mainTimer = fVar1, fVar1 < 0.0)) {
      (mem->header).mainTimer = 0.0;
    }
    fVar1 = (mem->header).timeUntilInactive;
    if ((fVar1 <= 0.0) ||
       (fVar1 = fVar1 - delta, (mem->header).timeUntilInactive = fVar1, 0.0 < fVar1)) {
      (mem->header).timeInactive = (mem->header).timeInactive + delta;
      (mem->header).timeInactive2 = (mem->header).timeInactive2 + delta;
      mem = next_mem;
    }
    else {
      (mem->header).timeUntilInactive = 0.0;
      MindMemory::dtor(mem);
      mem = next_mem;
    }
  }
  return;
}



// WARNING: Globals starting with '_' overlap smaller symbols at the same address
// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void actorBody::moveInDirection(actorBody *body,vec3 *v)

{
  float fVar1;
  vec3 v_xz;
  vec3 local_c;
  
  if ((((v->x != 0.0) || (v->y != 0.0)) || (v->z != 0.0)) &&
     (((body->flagSet->flags->attackFlags_ & 0x200) != Null && (body->field_0x19e != '\0')))) {
    local_c.x = (body->direction).x;
    local_c.y = (body->direction).y;
    local_c.z = (body->direction).z;
    v_xz.x = v->x;
    v_xz.y = 0.0;
    v_xz.z = v->z;
    vec3::normalise(&v_xz);
    fVar1 = v_xz.z * local_c.z + v_xz.y * local_c.y + v_xz.x * local_c.x;
    if (fVar1 < 0.0) {
      if (fVar1 < -0.3) {
        fVar1 = -0.3;
      }
      v->x = v->x * (fVar1 + 1.0);
      v->z = v->z * (fVar1 + 1.0);
    }
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void actor::setPosition(actor *actor,vec3 *newPos)

{
  avatar::setPosition(&actor->avatar,newPos);
  avatar::getWorldPosition(&actor->body->actor->avatar,&actor->body->worldPosition);
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void actor::updateExclusionRanges(actor *act)

{
  uint uVar1;
  Message local_10;
  float local_8;
  float local_4;
  
  avatar::getWorldPosition(&act->avatar,(vec3 *)&local_10.header.someActor);
  uVar1 = FUN_001248d0(4,0,Null);
  *(uint *)&act->field_0xca8 = uVar1;
  if (act->field818_0xcb8 == 0) {
    if (((uVar1 == 0) || (uVar1 == act->field812_0xca4)) ||
       ((*(objTag *)(uVar1 + 0x1c) != Null && (*(objTag *)(uVar1 + 0x1c) != (act->avatar).tag)))) {
      if ((act->body->field13_0x30 == 0) && (act->body->someTimer2 == 0.0)) {
        (act->someVec3).x = (float)local_10.header.someActor;
        (act->someVec3).y = local_8;
        (act->someVec3).z = local_4;
      }
    }
    else {
      act->field818_0xcb8 = 1;
    }
  }
  if ((((act->strategy != (actorStrategy *)0x0) && (act->actorType == Ghoulie_old)) &&
      ((act->node0x93c).prev == (actor_0x93c)0x0)) && (act->field818_0xcb8 != 0)) {
    local_10.header.msgId = Actor_WithinExclusionRegion;
    (*((act->avatar).vtable)->onMessage)(act,&local_10);
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void actor::setRotation(actor *act,vec3 *newEulers)

{
  Maths::NormaliseAngles2PI(newEulers,&(act->avatar).rotEuler);
  (act->avatar).anglesCalculated = 0;
  avatar::getWorldRotation(&act->body->actor->avatar,&act->body->rotation);
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void actor::update(actor *act)

{
  undefined1 *puVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  Buffer<> *pBVar5;
  actorBodyFlags *paVar6;
  CollisionMask CVar7;
  int iVar8;
  ModelSubresource *pMVar9;
  actorBodyAllocd *allocd;
  StatetableResource *statetable;
  actor *act_00;
  actorBodyStateId desiredState;
  int iVar10;
  StatetableEntry *entry;
  BOOL astar_layer_changed;
  byte bVar11;
  DroneAction *paVar11;
  void *this;
  astruct_32 *paVar12;
  int updateMindAndStrategy;
  float speed;
  float fVar13;
  float delta;
  MessageHeader msg;
  float fStack_20;
  float fStack_1c;
  vec3 vStack_18;
  vec3 vStack_c;
  actorStrategy *strategy;
  actorBody *body;
  InputHandlerType1 *input_handler;
  Model *instance;
  KeyframeContext *kfc;
  actorMind *mind;
  
  act_00 = act;
  input_handler = (InputHandlerType1 *)act->input_handler_;
  updateMindAndStrategy = (int)(0 < act->numSomethings);
  msg.msgId = updateMindAndStrategy;
  if ((input_handler->base).type == TYPE_1) {
    ClearScriptType1(input_handler);
  }
  else if ((input_handler->base).active != 0) {
    pBVar5 = act->droneActionsBuf;
    if (pBVar5 != (Buffer<> *)0x0) {
      if (pBVar5->size == pBVar5->endOfQueue) {
        paVar11 = (DroneAction *)0x0;
      }
      else {
        paVar11 = (DroneAction *)
                  ((int)&pBVar5->entries->actionId +
                  (uint)pBVar5->currentDroneAction * (uint)pBVar5->valueSize);
      }
      if (paVar11->actionId != Null) {
        InputHandlerBase::init((InputHandlerBase *)input_handler);
        goto LAB_0002c321;
      }
    }
    FUN_00109470((InputHandlerType4 *)input_handler);
  }
LAB_0002c321:
  if (updateMindAndStrategy == 0) {
    strategy = act_00->strategy;
    if (strategy != (actorStrategy *)0x0) {
                    // 0x0c0bb0
                    // 
                    // Disabling this breaks
                    // - Camera updates
                    // - All enemy AI
                    // 
                    // Seems to ruin decision makers when they need to make a new decision. For
                    // example, a skeleton already attacking the player will always finish their
                    // attack, but when they need to make a new decision they have no clue what
                    // they're doing.
      (*strategy->vtable->update)(strategy);
    }
    mind = act_00->mind;
    if (mind != (actorMind *)0x0) {
                    // Can go to 0x0007ce30
      (*mind->vtable->update)(mind,act_00->input_handler_);
    }
  }
  (*act_00->body->vtable->update)(act_00->body,act_00->input_handler_);
  paVar6 = act_00->body->flagSet->flags;
  speed = 0.0;
  *(undefined1 *)&paVar6->flag1 = (char)paVar6->flag1 & 0xfb;
  paVar6 = act_00->body->flagSet->flags;
  *(undefined1 *)&paVar6->flag1 = (char)paVar6->flag1 & 0xf7;
  if (runtime::dx_timer <= 0.0) {
    delta = runtime::DeltaTime * runtime::TimeScale;
  }
  else {
    delta = 0.0;
  }
  if ((act_00->avatar).movementFreezeTimer <= 0.0) {
    speed = (act_00->avatar).actionSpeed;
  }
  kfc = (act_00->avatar).keyframeContext;
  if (kfc != (KeyframeContext *)0x0) {
                    // Update skeleton from animation
    KeyframeContext::updateFromAvatar
              (kfc,(act_00->avatar).model,(uint)((act_00->avatar).preventAnimChannelAdvancing == 0),
               speed * delta);
  }
                    // UPDATE BODY MOVEMENT
                    // 
                    // actorBody::updateMovement
  (*act_00->body->vtable->updateMovement)(act_00->body);
  kfc = (act_00->avatar).keyframeContext;
  if (kfc != (KeyframeContext *)0x0) {
    KeyframeContext::updateSkeletonAndBlendTargets
              ((uint)((act_00->avatar).preventAnimChannelAdvancing == 0),kfc,(act_00->avatar).model,
               (act_00->avatar).boneList);
  }
  paVar6 = act_00->body->flagSet->flags;
  *(undefined1 *)&paVar6->flag1 = (char)paVar6->flag1 & 0xfd;
  if (updateMindAndStrategy == 0) {
    if (act_00->body->field302_0x258 == 0) {
      CVar7 = (act_00->avatar).collisionMask;
      (act_00->avatar).collisionMask = Nothing;
      act = (actor *)(act_00->avatar).has0x4CollisionFlag;
      (act_00->avatar).has0x4CollisionFlag = 0;
      avatar::updateMorphTargetsOrSomething(&act_00->avatar);
                    // Update colliders?
      actorBody::runCollisions(act_00->body);
      avatar::getWorldPosition(&act_00->avatar,(vec3 *)&msg.someActor);
      body = act_00->body;
      (body->worldPos).x = (float)msg.someActor;
      (body->worldPos).y = fStack_20;
      (body->worldPos).z = fStack_1c;
                    // entityBodyHuman::updateAgainstGlobalCollision
      iVar10 = (*act_00->body->vtable->computeMovementAndCollisions)(act_00->body);
      if (iVar10 == 0) {
        paVar6 = act_00->body->flagSet->flags;
        bVar11 = *(byte *)((int)&paVar6->flag1 + 1) | 0x10;
      }
      else {
        paVar6 = act_00->body->flagSet->flags;
        bVar11 = *(byte *)((int)&paVar6->flag1 + 1) & 0xef;
      }
      *(byte *)((int)&paVar6->flag1 + 1) = bVar11;
      (act_00->avatar).collisionMask = CVar7;
      (act_00->avatar).has0x4CollisionFlag = (uint)act;
      avatar::updateMorphTargetsOrSomething(&act_00->avatar);
      updateMindAndStrategy = msg.msgId;
    }
    else {
      act_00->body->field_0x716 = 0;
      body = act_00->body;
      msg.someActor = (actor *)(body->worldPosition).x;
      speed = (body->worldPosition).y;
      delta = (body->worldPosition).z;
      avatar::getWorldPosition(&act_00->avatar,&vStack_18);
      fVar13 = (float)msg.someActor - vStack_18.x;
      body = act_00->body;
      speed = speed - vStack_18.y;
      delta = delta - vStack_18.z;
      vStack_c.x = fVar13;
      vStack_c.y = speed;
      vStack_c.z = delta;
      doSomeWeirdVec3Shit(body->actor,&body->bigVec3SetIndex,&vStack_c);
      (body->v1).x = fVar13;
      (body->v1).y = speed;
      (body->v1).z = delta;
      avatar::setPosition(&act_00->avatar,(vec3 *)&msg.someActor);
      avatar::getWorldPosition(&act_00->body->actor->avatar,&act_00->body->worldPosition);
    }
  }
  avatar::updateBaseTransform(&act_00->avatar);
  iVar10 = *(int *)&(act_00->avatar).field_0x1d8;
  while (iVar10 != 0) {
    iVar8 = *(int *)(iVar10 + 4);
    (**(code **)(*(int *)(iVar10 + -8) + 0x10))(iVar10 + -8,act_00);
    iVar10 = iVar8;
  }
  avatar::updateFx(&act_00->avatar);
  speed = (act_00->avatar).smoothedTargetPos.z;
  delta = (act_00->avatar).smoothedTargetPos.y;
  fVar13 = (act_00->avatar).smoothedTargetPos.x;
  if (Game::UseMovementSmoothing != 0) {
    fVar2 = (act_00->avatar).smoothedCurrentPos.x;
    fVar3 = (act_00->avatar).smoothedCurrentPos.y;
    fVar4 = (act_00->avatar).smoothedCurrentPos.z;
    fVar13 = (fVar13 - fVar2) * 0.1 + fVar2;
    delta = (delta - fVar3) * 0.1 + fVar3;
    speed = (speed - fVar4) * 0.1 + fVar4;
  }
  (act_00->avatar).smoothedCurrentPos.x = fVar13;
  (act_00->avatar).smoothedCurrentPos.y = delta;
  (act_00->avatar).smoothedCurrentPos.z = speed;
  instance = (act_00->avatar).model;
  if ((instance != (Model *)0x0) &&
     (pMVar9 = instance->modelPassedToBG, pMVar9 != (ModelSubresource *)0x0)) {
    background::updateModelChildren_(pMVar9,1.0);
  }
                    // Breaks camera and enemy targeting
  (*act_00->body->vtable->updatePosAndRot)(act_00->body);
  if (updateMindAndStrategy == Null) {
    allocd = act_00->body->actorAllocd;
    if (allocd != (actorBodyAllocd *)0x0) {
      runPhysicsCallbackOnAvatar(allocd,&act_00->body->actor->avatar,onActorHitsAvatar);
    }
  }
  body = act_00->body;
  if (body->actorState == (actorState *)0x0) {
    desiredState = Null;
  }
  else {
    desiredState = (*body->actorState->vtable->func7)(body->actorState,body->actor->input_handler_);
  }
  body = act_00->body;
                    // Update actor state
  if (((desiredState != Null) &&
      (statetable = body->statetableRes, statetable != (StatetableResource *)0x0)) &&
     (entry = binarySearchStateTable(statetable,(Asset **)&act,desiredState),
     entry != (StatetableEntry *)0x0)) {
    actorBody::updateStatesFromEntry(body,(AttackEntry *)act,entry);
  }
  avatar::getWorldPosition(&act_00->body->actor->avatar,&act_00->body->worldPosition);
  body = act_00->body;
                    // Reset velocity?
  (body->velocity).z = 0.0;
  (body->velocity).y = 0.0;
  (body->velocity).x = 0.0;
  act_00->body->speed = (act_00->body->actor->avatar).rotEuler.y;
  avatar::getWorldRotation(&act_00->body->actor->avatar,&act_00->body->rotation);
  updateGhoulieTimers(act_00);
  updateExclusionRanges(act_00);
  if (BackgroundCollisionThings[0] == (BackgroundCollisionThing *)0x0) goto LAB_0002c8a2;
  avatar::getWorldPosition(&act_00->avatar,&vStack_c);
  instance = (act_00->avatar).model;
  if ((instance == (Model *)0x0) || (instance->descriptor == (ModelDescriptor *)0x0)) {
    act = (actor *)0x0;
  }
  else {
    act = (actor *)((act_00->body->actor->avatar).scale.z * act_00->body->closenessDistance);
  }
  mind = act_00->mind;
  if (mind == (actorMind *)0x0) {
    paVar12 = (astruct_32 *)0x0;
LAB_0002c81d:
    this = (void *)0xffffffff;
  }
  else {
    paVar12 = mind->astarShit;
    if (mind->targetBody == (actorBody *)0x0) goto LAB_0002c81d;
    this = (void *)(uint)*(byte *)((int)&(mind->targetBody->worldPosition).x + 1);
  }
  puVar1 = &act_00->field_0xce8;
  astar_layer_changed =
       checkAStarLayerChanged
                 ((uint)(act_00->field827_0xcde == 1),this,&vStack_c,
                  (int *)&act_00->backgroundCollisionIndex,puVar1,paVar12);
  if (astar_layer_changed != 0) {
    msg.msgId = Actor_AStarLayerChanged;
    (*((act_00->avatar).vtable)->onMessage)(act_00,&msg);
  }
  if ((float)act == 0.0) {
    if (*(int *)puVar1 != 0) {
      FUN_001108b0();
    }
  }
  else {
    runBroadPhaseTests(puVar1,&vStack_c,act_00->backgroundCollisionIndex,act,
                       *(undefined4 *)&act_00->field_0xcf0);
  }
LAB_0002c8a2:
  checkStillInBounds(act_00);
  if ((ShouldntDroneBools[1] == 0) && ("\x01"[Game::CheckMoveOn] != '\0')) {
    if (runtime::dx_timer <= 0.0) {
      speed = runtime::DeltaTime * runtime::TimeScale;
    }
    else {
      speed = 0.0;
    }
    delta = (act_00->avatar).movementFreezeTimer;
    if ((0.0 < delta) &&
       (delta = delta - speed, (act_00->avatar).movementFreezeTimer = delta, delta <= 0.0)) {
      (act_00->avatar).movementFreezeTimer = 0.0;
    }
  }
  speed = 0.0;
  if (runtime::dx_timer <= 0.0) {
    delta = runtime::DeltaTime * runtime::TimeScale;
  }
  else {
    delta = 0.0;
  }
  if ((act_00->avatar).movementFreezeTimer <= 0.0) {
    speed = (act_00->avatar).actionSpeed;
  }
  (act_00->avatar).timeAlive = speed * delta + (act_00->avatar).timeAlive;
  (act_00->avatar).timesUpdated = (act_00->avatar).timesUpdated + 1;
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void actor::checkStillInBounds(actor *act)

{
  Buffer<> *pBVar1;
  int iVar2;
  actorDroneActionId *paVar3;
  float bg_y;
  undefined4 local_10;
  vec3 pos;
  bool actor_in_bounds;
  bool escaped;
  
  avatar::getWorldPosition(&act->avatar,&pos);
  if (Background::HasBounds == '\0') {
    actor_in_bounds = true;
  }
  else {
    bg_y = Background::MaxVector.y;
    if (Background::MaxVector.y < pos.y) {
      bg_y = pos.y;
    }
    if (((((pos.x < Background::MinVector.x) || (Background::MaxVector.x <= pos.x)) ||
         (pos.y < Background::MinVector.y)) ||
        ((bg_y + 1.0 <= pos.y || (pos.z < Background::MinVector.z)))) ||
       (Background::MaxVector.z <= pos.z)) {
                    // OOB case
      actor_in_bounds = false;
    }
    else {
      actor_in_bounds = true;
    }
  }
  escaped = false;
  if (((act->field827_0xcde == 1) &&
      ((act->body->flagSet->flags->attackFlags_ & IsBandaged) == Null)) &&
     (iVar2 = Background::isCollisionThings(act->backgroundCollisionIndex,&pos), iVar2 == -1)) {
    escaped = true;
  }
  if (actor_in_bounds) {
    if (!escaped) {
      return;
    }
    pBVar1 = act->droneActionsBuf;
    if (pBVar1 != (Buffer<> *)0x0) {
      if (pBVar1->size == pBVar1->endOfQueue) {
        paVar3 = (actorDroneActionId *)0x0;
      }
      else {
        paVar3 = (actorDroneActionId *)
                 ((int)&pBVar1->entries->actionId +
                 (uint)pBVar1->currentDroneAction * (uint)pBVar1->valueSize);
      }
      if (*paVar3 != Null) {
        return;
      }
    }
  }
                    // Escaped background message
  local_10 = 0x33;
  (*((act->avatar).vtable)->onMessage)(act,&local_10);
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void DeathLoop(float param_1)

{
  uint uVar1;
  float10 fVar2;
  LARGE_INTEGER local_20;
  int local_18;
  uint uStack_14;
  undefined4 local_10;
  uint uStack_c;
  
  fVar2 = (float10)FUN_001077d0();
  do {
    XAPILIB::QueryPerformanceCounter(&local_20);
    local_18 = local_20.s.LowPart - g_PERFORMANCE_COUNTER;
    uVar1 = (local_20.s.HighPart - DAT_0050e0dc) -
            (uint)(local_20.s.LowPart < g_PERFORMANCE_COUNTER);
    uStack_14 = uVar1 & 0x7fffffff;
    uStack_c = uVar1 & 0x80000000;
    local_10 = 0;
  } while ((-(float10)(longlong)(((ulonglong)uVar1 & 0x80000000) << 0x20) +
           (float10)(CONCAT44(uVar1,local_18) & 0x7fffffffffffffff)) /
           (float10)_g_PERFORMANCE_FREQUENCY < (float10)(float)(fVar2 + (float10)param_1));
  return;
}




void __thiscall CheckWeaponAgainstActorModel(void *this,bool someFlag,weapon *wpn,actor *act)

{
  ModelDescriptor *modelRes;
  byte bVar1;
  uint uVar2;
  AvatarPhysicsContext *ctx;
  Model *model;
  
  if (((((act != (actor *)0x0) && (model = (act->avatar).model, model != (Model *)0x0)) &&
       (modelRes = model->descriptor, modelRes != (ModelDescriptor *)0x0)) &&
      ((this != (void *)0xffffffff && (model != (Model *)0x0)))) &&
     (modelRes != (ModelDescriptor *)0x0)) {
    bVar1 = ModelDescriptor::getBoneIdxFromRigid(modelRes,(short)this);
    uVar2 = (uint)bVar1;
    if (((uVar2 != 0xff) && (uVar2 != 0xffffffff)) &&
       (ctx = avatar::getOrCreatePhysicsCtx(&wpn->avatar), ctx != (AvatarPhysicsContext *)0x0)) {
      ctx = (wpn->avatar).physicsCtx;
      ctx->mode2 = '\x02';
      ctx->actor = act;
      ctx->someFlag = someFlag;
      ctx->valueFromModelRes = uVar2;
    }
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void actor::executeCallout(actor *act,uint calloutIndex,avatarCalloutId id)

{
  CalloutDescriptor **desc;
  
  desc = &(act->avatar).callout;
  if (desc == (CalloutDescriptor **)0x0) {
    return;
  }
  executeCalloutInDescriptor
            (*desc,id,(CalloutCallback *)0x0,calloutIndex,act,(entityBodyPlayer_0x924)0x0);
  return;
}




undefined2 actor::createImpactFlash(actor *param_1,uint param_2,char *impactFlashAID)

{
  int *ptr;
  
  if (*(int *)impactFlashAID != 0x5f646961) {
    return 0;
  }
  ptr = (int *)FUN_0003d330(&(param_1->avatar).fxEmitterImpactFlash,impactFlashAID,param_2);
  if (ptr != (int *)0x0) {
    if ((param_2 & 8) == 0) {
      return (short)ptr[6];
    }
    if (*ptr != 0) {
      *(int *)(*ptr + 4) = ptr[1];
    }
    if ((int *)ptr[1] != (int *)0x0) {
      *(int *)ptr[1] = *ptr;
    }
    *ptr = 0;
    ptr[1] = 0;
    FUN_0003d3a0();
    free(ptr);
  }
  return 0;
}




void actor::createOnDeathObjects(avatar *av,int param_2)

{
  D3DXMATRIX DVar1;
  D3DXMATRIX *pDVar3;
  undefined4 unaff_ESI;
  undefined4 unaff_EDI;
  uint i;
  int iVar3;
  int iVar4;
  AffineTransform *pAVar5;
  undefined1 in_stack_fffffc00 [44];
  D3DXMATRIX rs;
  D3DXMATRIX step1;
  D3DXMATRIX step8;
  D3DXMATRIX step4;
  D3DXMATRIX step9;
  D3DXMATRIX step5;
  D3DXMATRIX ry;
  D3DXMATRIX step7;
  AffineTransform someAffine;
  D3DXMATRIX local_190;
  D3DXMATRIX step6;
  D3DXMATRIX step2;
  D3DXMATRIX rz;
  D3DXMATRIX t2;
  D3DXMATRIX t1;
  OnDeathObject *as24;
  int iVar2;
  
  if (av->numTransforms != 0) {
    pAVar5 = &av->baseTransform;
    someAffine.m[0][0] = pAVar5->m[0][0];
    someAffine.m[0][1] = (av->baseTransform).m[0][1];
    someAffine.m[0][2] = (av->baseTransform).m[0][2];
    someAffine.m[0][3] = (av->baseTransform).m[0][3];
    someAffine.m[1][0] = (av->baseTransform).m[1][0];
    someAffine.m[1][1] = (av->baseTransform).m[1][1];
    someAffine.m[1][2] = (av->baseTransform).m[1][2];
    someAffine.m[1][3] = (av->baseTransform).m[1][3];
    someAffine.m[2][0] = (av->baseTransform).m[2][0];
    someAffine.m[2][1] = (av->baseTransform).m[2][1];
    someAffine.m[2][2] = (av->baseTransform).m[2][2];
    someAffine.m[2][3] = (av->baseTransform).m[2][3];
    i = 0;
    if (0 < av->numTransforms) {
      iVar3 = 0;
      do {
        as24 = (OnDeathObject *)av->transforms;
        iVar2 = *(int *)((int)&as24->field9_0x44 + iVar3);
        iVar4 = iVar3;
        if (*(int *)((int)&as24->field5_0x34 + iVar3) == 0) {
          if ((iVar2 != 0) || (param_2 != 0)) {
            D3DX8::D3DXMatrixTranslation
                      (&t1,*(float *)((int)&(as24->t1).x + iVar3),
                       *(float *)((int)&(as24->t1).y + iVar3),*(float *)((int)&(as24->t1).z + iVar3)
                      );
            D3DX8::D3DXMatrixTranslation
                      (&t2,*(float *)((int)&(as24->t2).x + iVar3),
                       *(float *)((int)&(as24->t2).y + iVar3),*(float *)((int)&(as24->t2).z + iVar3)
                      );
            Maths::RotateMatrixAroundAxis
                      ((D3DXMATRIX *)&stack0xfffffc00,
                       *(undefined4 *)((int)&(as24->rotEuler).x + iVar3),'x');
            Maths::RotateMatrixAroundAxis(&ry,*(undefined4 *)((int)&(as24->rotEuler).y + iVar3),'y')
            ;
            Maths::RotateMatrixAroundAxis(&rz,*(undefined4 *)((int)&(as24->rotEuler).z + iVar3),'z')
            ;
            D3DX8::D3DXMatrixScaling
                      (&rs,*(undefined4 *)((int)&(as24->scale).x + iVar3),
                       *(undefined4 *)((int)&(as24->scale).y + iVar3),
                       *(undefined4 *)((int)&(as24->scale).z + iVar3));
            Maths::MultiplyMat4s(&ry,&ry,&t2);
            Maths::MultiplyMat4s((D3DXMATRIX *)&stack0xfffffc00,(D3DXMATRIX *)&stack0xfffffc00,&ry);
            Maths::MultiplyMat4s((D3DXMATRIX *)&stack0xfffffc00,&rz,(D3DXMATRIX *)&stack0xfffffc00);
            Maths::MultiplyMat4s(&rs,&rs,(D3DXMATRIX *)&stack0xfffffc00);
            Maths::MultiplyMat4s(&rs,&t1,&rs);
            pDVar3 = &rs;
            goto LAB_0004050a;
          }
        }
        else if ((iVar2 != 0) || (param_2 != 0)) {
          D3DX8::D3DXMatrixTranslation
                    (&step1,*(float *)((int)&(as24->t1).x + iVar3),
                     *(float *)((int)&(as24->t1).y + iVar3),*(float *)((int)&(as24->t1).z + iVar3));
          D3DX8::D3DXMatrixTranslation
                    (&step2,*(float *)((int)&(as24->t2).x + iVar3),
                     *(float *)((int)&(as24->t2).y + iVar3),*(float *)((int)&(as24->t2).z + iVar3));
          Maths::RotateMatrixAroundAxis
                    (&local_190,*(undefined4 *)((int)&(as24->rotEuler).x + iVar3),'x');
          Maths::RotateMatrixAroundAxis
                    (&step4,*(undefined4 *)((int)&(as24->rotEuler).y + iVar3),'y');
          Maths::RotateMatrixAroundAxis
                    (&step5,*(undefined4 *)((int)&(as24->rotEuler).z + iVar3),'z');
          Maths::RotateMatrixAroundAxis(&step6,*(undefined4 *)((int)&as24->field6_0x38 + iVar3),'x')
          ;
          Maths::RotateMatrixAroundAxis(&step7,*(undefined4 *)((int)&as24->field7_0x3c + iVar3),'y')
          ;
          Maths::RotateMatrixAroundAxis(&step8,*(undefined4 *)((int)&as24->field8_0x40 + iVar3),'z')
          ;
          D3DX8::D3DXMatrixScaling
                    (&step9,*(undefined4 *)((int)&(as24->scale).x + iVar3),
                     *(undefined4 *)((int)&(as24->scale).y + iVar3),
                     *(undefined4 *)((int)&(as24->scale).z + iVar3));
          Maths::MultiplyMat4s(&step4,&step4,&step2);
          Maths::MultiplyMat4s(&local_190,&local_190,&step4);
          Maths::MultiplyMat4s(&step5,&step5,&local_190);
          Maths::MultiplyMat4s(&step1,&step1,&step5);
          Maths::MultiplyMat4s(&step7,&step7,&step1);
          Maths::MultiplyMat4s(&step6,&step6,&step7);
          Maths::MultiplyMat4s(&step8,&step8,&step6);
          Maths::MultiplyMat4s(&step9,&step9,&step8);
          pDVar3 = &step9;
LAB_0004050a:
          DVar1.m[0][1] = (float)unaff_EDI;
          DVar1.m[0][0] = (float)pDVar3;
          DVar1.m[0][2] = (float)unaff_ESI;
          DVar1.m[0][3] = (float)iVar4;
          DVar1.m[1][0] = (float)pAVar5;
          DVar1._20_44_ = in_stack_fffffc00;
          FUN_00156010((astruct_24 *)av->ndMtxArray,*(undefined4 *)&av->field_0x294,i,DVar1);
          iVar3 = iVar4;
        }
        i = i + 1;
        iVar3 = iVar3 + 0x48;
      } while ((int)i < av->numTransforms);
    }
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


BoneAffineSubresourceEntry * actor::getModelBoneAffineByBone1(actor *param_1,short bone1)

{
  Model *pMVar1;
  ModelDescriptor *pMVar2;
  uint uVar3;
  BoneAffineSubresourceEntry *entry;
  ModelFooterEntry *pMVar4;
  BoneAffineSubresourceEntry *end;
  BoneAffineSubresource *bone_affines;
  
  pMVar1 = (param_1->avatar).model;
  if ((pMVar1 != (Model *)0x0) && (pMVar2 = pMVar1->descriptor, pMVar2 != (ModelDescriptor *)0x0)) {
    uVar3 = 0;
    if (pMVar2->numFooterEntries != 0) {
      pMVar4 = pMVar2->footerEntries;
      while (pMVar4->subresourceType != BoneAffines) {
        uVar3 = uVar3 + 1;
        pMVar4 = pMVar4 + 1;
        if (pMVar2->numFooterEntries <= uVar3) {
          return (BoneAffineSubresourceEntry *)0x0;
        }
      }
      bone_affines = (BoneAffineSubresource *)pMVar2->footerEntries[uVar3].offset;
      if (bone_affines != (BoneAffineSubresource *)0x0) {
        entry = bone_affines->entries;
        end = entry + bone_affines->numEntries;
        for (; entry < end; entry = entry + 1) {
          if (entry->bone1 == bone1) {
            return entry;
          }
        }
      }
    }
  }
  return (BoneAffineSubresourceEntry *)0x0;
}




uint32_t actor::getSubres0x2EntryById(actor *param_1,uint16_t id)

{
  ModelDescriptor *pMVar1;
  uint uVar4;
  uint32_t index;
  ModelFooterEntry *subres0x2;
  ModelSubresource0x2 *subress0x2;
  Model *pMVar2;
  
  pMVar2 = (param_1->avatar).model;
  if ((pMVar2 != (Model *)0x0) && (pMVar1 = pMVar2->descriptor, pMVar1 != (ModelDescriptor *)0x0)) {
    uVar4 = 0;
    if (pMVar1->numFooterEntries != 0) {
      subres0x2 = pMVar1->footerEntries;
      do {
        if (subres0x2->subresourceType == BoneAffines) {
          subress0x2 = (ModelSubresource0x2 *)pMVar1->footerEntries[uVar4].offset;
          if (subress0x2 == (ModelSubresource0x2 *)0x0) {
            return 0;
          }
          index = ModelSubresource0x2::getSubres0x2IndexById(subress0x2,id);
          return index;
        }
        uVar4 = uVar4 + 1;
        subres0x2 = subres0x2 + 1;
      } while (uVar4 < pMVar1->numFooterEntries);
    }
  }
  return 0;
}




void actor::decrementAS23(actor *param_1)

{
  astruct_23 *paVar1;
  
  for (paVar1 = (param_1->avatar).as23ptr; paVar1 != (astruct_23 *)0x0;
      paVar1 = *(astruct_23 **)&paVar1->field_0x4) {
    paVar1->field_0x15 = paVar1->field_0x15 + -1;
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void CreateSetDroneActionMessage(Actor_SetDroneActionMessage *msg)

{
  msg->droneAction = Null;
  msg->someShort = 0;
  msg[1].msgId = Null;
  msg[1].droneAction = Null;
  msg[1].someShort = 0;
  msg[2].msgId = Null;
  msg[2].droneAction = Null;
  msg[2].someShort = 0;
  msg[3].msgId = Null;
  msg[3].droneAction = Null;
  msg[3].someShort = 0;
  msg[4].msgId = Null;
  msg->msgId = Actor_SetDroneAction;
  return;
}




void actorBody::updateMovement(actorBody *param_1)

{
  actorMove *paVar1;
  
  paVar1 = param_1->actorMove;
  if (paVar1 != (actorMove *)0x0) {
    (*paVar1->vtable->applyMovement)(paVar1);
  }
  if (0 < param_1->numBodyExpressions) {
    FUN_0001ea90();
  }
  if (param_1->hasBlendTargets != 0) {
    FUN_0001d850(param_1);
    updateBlendTargets(param_1);
    return;
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void actorBody::updatePosAndRot(actorBody *body)

{
  updatePosAndRot(body);
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void entityMindCinema::goalFunc1(entityMindCinema *mind,AnotherCameraGoal *param_2)

{
  switch((param_2->header).goalId) {
  case AnotherCameraGoal:
    onAnotherCameraGoal(mind,param_2);
    return;
  default:
    actorMind::executeGoal(&mind->mind,&param_2->header);
    return;
  case AvatarCamAttachedToFocalActor:
    FUN_00079b80(param_2);
    return;
  case BanjoCamAttachedToFocalActor:
    FUN_0007a080(mind);
    return;
  case FollowFocalActor:
    FUN_0007a910();
    return;
  }
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


BOOL entityMindCinema::onAnotherCameraGoal(entityMindCinema *mind,AnotherCameraGoal *goal)

{
  actor *act;
  actor *act_00;
  actorBody *paVar1;
  int iVar2;
  float fVar3;
  AnotherCameraGoal *pAVar4;
  float in_XMM0_Da;
  float fVar5;
  vec3 local_30;
  vec3 local_24;
  vec3 local_18;
  float local_c;
  float local_8;
  float local_4;
  
  act = (mind->mind).targetActor;
  act_00 = (mind->mind).actor;
  paVar1 = act_00->body;
  if (act == (actor *)0x0) {
    return 0;
  }
  avatar::getWorldPosition(&act_00->avatar,&local_30);
  fVar5 = FUN_0013dc40(act,in_XMM0_Da);
  if (fVar5 == 0.0) {
    FUN_00079320(mind,&local_30,goal);
  }
  else if (*(int *)&mind->field_0xac != 0) {
    *(undefined4 *)&mind->field_0xac = 0;
    *(undefined4 *)&mind->field_0xb0 = 1;
  }
  pAVar4 = goal;
  FUN_00078840(mind,(int)act_00,goal,&local_30,&local_24,&local_18,(float)act,(float *)&goal);
  FUN_00079720(mind,act_00,paVar1,&local_24,&local_18,act,goal);
  fVar3 = FLOAT_004274e0;
  fVar5 = FLOAT_004274dc;
  iVar2._0_2_ = pAVar4[1].header.goalId;
  iVar2._2_1_ = pAVar4[1].header.initialised;
  iVar2._3_1_ = pAVar4[1].header.field4_0xb;
  if (iVar2 == 0) {
    (mind->mind).evasionPos.x = local_30.x;
    (mind->mind).evasionPos.y = local_30.y;
    (mind->mind).evasionPos.z = local_30.z;
    goal = (AnotherCameraGoal *)0x3;
    (*paVar1->vtable->onMessage)(paVar1,&goal);
  }
  else {
    (mind->mind).evasionPos.x = local_24.x;
    (mind->mind).evasionPos.y = local_24.y;
    (mind->mind).evasionPos.z = local_24.z;
    FUN_0013ce80(fVar5,0,fVar3);
    (paVar1->velocity).x = local_c;
    (paVar1->velocity).y = local_8;
    (paVar1->velocity).z = local_4;
  }
  (paVar1->camPos).x = local_18.x;
  (paVar1->camPos).y = local_18.y;
  (paVar1->camPos).z = local_18.z;
  paVar1->field_0x308 = 1;
  return 1;
}




void entityMindCinema::getAllocDetails(undefined4 *param_1)

{
  *param_1 = 0xdc;
  param_1[1] = 0xa0;
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


actorMindVTable * entityMindCinema::getVTable(void)

{
  vtable.onRemoveAction = switchD_000d4179::EmptyFunction;
  vtable.getAllocDetails = getAllocDetails;
  vtable.ctor = obj::returnOne;
  vtable.dtor = switchD_000d4179::EmptyFunction;
  vtable.onMessage = onMessage;
  vtable.update = actorMind::update;
  vtable.executeGoal = goalFunc1;
  vtable.initialiseGoal = goalFunc2;
  return &vtable;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void entityMindCinema::onMessage(actorMind *param_1,Message *param_2)

{
  ObjMsgID OVar1;
  
  OVar1 = (param_2->header).msgId;
  if (OVar1 == Scene_AvatarRemoved) {
    if ((param_2->header).someActor == (actor *)param_1[1].vtable) {
      param_1[1].vtable = (actorMindVTable *)0x0;
    }
  }
  else if (OVar1 == Scene_Begin) {
    FUN_00136700(param_1);
    actorMind::onMessage(param_1,param_2);
    return;
  }
  actorMind::onMessage(param_1,param_2);
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


bool actorMind::onGoalAttackTarget(actorMind *this,actorMindGoalAttackTarget *goal)

{
  InputHandlerBase *pIVar1;
  int iVar2;
  actorBody *body;
  actorBody *targetBody;
  
  targetBody = this->targetBody;
  body = this->actor->body;
  pIVar1 = this->actor->input_handler_;
  if (targetBody == (actorBody *)0x0) {
    return true;
  }
  if ((body->field13_0x30 == 0) && (body->someTimer2 == 0.0)) {
    if ((goal->field2_0x14 != (actorMindGoal *)0x0) ||
       (*(char *)((int)&targetBody->largeProjectile + 1) == '\0')) {
      iVar2 = entityMindHuman::chooseHumanAttack(goal->attackMask,this,targetBody);
      return iVar2 != 1;
    }
    if (pIVar1 != (InputHandlerBase *)0x0) {
                    // Clear the input handler after handling the input
      InputHandlerBase::init(pIVar1);
    }
  }
  return false;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields

MindActionReturnCode

entityMindHuman::onGenerateEvasionDestinationGoal(int param_1,entityMindHuman *param_2)

{
  int iVar1;
  float local_c;
  float local_8;
  float local_4;
  
  iVar1 = FUN_00135b60((param_2->actorMind).actor,*(undefined4 *)(param_1 + 0x1c),
                       *(undefined4 *)(param_1 + 0x14),*(undefined4 *)(param_1 + 0x18),&local_c);
  if (iVar1 != 0) {
    (param_2->actorMind).evasionPos.x = local_c;
    (param_2->actorMind).evasionPos.y = local_8;
    (param_2->actorMind).evasionPos.z = local_4;
    return Success;
  }
  return ErrorGettingEvasionPos;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


int FUN_0007b5a0(int param_1,actorMind *param_2)

{
  vec3 *pvVar1;
  InputHandlerBase *pIVar2;
  int iVar3;
  int iVar4;
  float fVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  undefined4 uVar8;
  undefined4 uVar9;
  undefined4 uVar10;
  undefined4 uVar11;
  undefined1 *puVar12;
  undefined1 local_4 [4];
  
  fVar5 = *(float *)(param_1 + 0x20) + 1.0;
  pIVar2 = param_2->actor->input_handler_;
  puVar12 = local_4;
  uVar10 = *(undefined4 *)(param_1 + 0x28);
  uVar11 = 0;
  uVar9 = *(undefined4 *)(param_1 + 0x2c);
  uVar8 = *(undefined4 *)(param_1 + 0x24);
  uVar7 = *(undefined4 *)(param_1 + 0x1c);
  uVar6 = *(undefined4 *)(param_1 + 0x18);
  pvVar1 = &param_2->evasionPos;
  iVar3 = FUN_00110bf0(pvVar1,param_2->actor->backgroundCollisionIndex,0);
  iVar3 = FUN_00136d60(pIVar2,pvVar1,iVar3,uVar6,uVar7,fVar5,uVar8,uVar9,uVar10,uVar11,puVar12);
  if ((iVar3 == 0) && (iVar4 = FUN_001373f0(param_2,pvVar1), iVar4 != 0)) {
    return 1;
  }
  return iVar3;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


int actorMind::onWalkToDestinationGoal(actorMind *this,actorMindGoalWalkToDestination *goal)

{
  int iVar1;
  int iVar2;
  vec3 *local_4;
  
  local_4 = (vec3 *)(goal->field9_0x18 + 1.0);
  iVar1 = FUN_00136b00(0xffffffff,this,this->actor->input_handler_,&this->evasionPos,(float)local_4,
                       goal->field10_0x1c,goal->field11_0x20,0,&local_4);
  if ((iVar1 == 0) && (iVar2 = FUN_001373f0(this,&this->evasionPos), iVar2 != 0)) {
    return 1;
  }
  return iVar1;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


int FUN_0007bc80(actorMind *param_1,int param_2)

{
  float fVar1;
  actorBody *paVar2;
  actor *paVar3;
  actorBody *this;
  int iVar4;
  int iVar5;
  BOOL BVar6;
  uint uVar7;
  actorBody *paVar8;
  actor *local_3c;
  actorBody *local_38;
  int local_34;
  InputHandlerBase *local_30;
  vec3 local_2c;
  SomeActorBodyList local_20;
  
  iVar5 = param_2;
  local_3c = param_1->actor;
  local_38 = local_3c->body;
  paVar2 = param_1->targetBody;
  local_30 = local_3c->input_handler_;
  if (paVar2 == (actorBody *)0x0) {
    return 1;
  }
  if (*(int *)(param_2 + 0x28) != 0) {
    iVar4 = FUN_00141580();
    if (iVar4 == 0) {
      return 0;
    }
  }
  uVar7 = (uint)*(byte *)((int)&(paVar2->worldPosition).x + 1);
  iVar4 = Background::isCollisionThings(uVar7,(vec3 *)&(paVar2->worldPosition).z);
  if (iVar4 == -1) {
    local_34 = 1;
    CopySomeActorBodyList((SomeActorBodyList *)&paVar2->projRowCount_,&local_20);
  }
  else {
    local_34 = FUN_00036600(BackgroundCollisionThings[uVar7]);
    if (local_34 == 0) {
      CopySomeActorBodyList((SomeActorBodyList *)&(paVar2->worldPosition).y,&local_20);
      if (((uint)paVar2->largeProjectile & 0x100000) != 0) {
        FUN_001060f0((paVar2->currentWeapon->avatar).rotEuler.y,local_20.field11_0x1c * 2.0);
        uVar7 = (uint)*(byte *)((int)&(paVar2->worldPosition).x + 1);
        iVar4 = Background::isCollisionThings(uVar7,&local_2c);
        if (iVar4 != -1) {
          iVar4 = FUN_00036600(BackgroundCollisionThings[uVar7]);
          if (iVar4 == 0) {
            local_20.pos.x = local_2c.x;
            local_20.pos.y = local_2c.y;
            local_20.pos.z = local_2c.z;
          }
        }
      }
    }
    else {
      CopySomeActorBodyList((SomeActorBodyList *)&paVar2->projRowCount_,&local_20);
    }
  }
  if (0.0 < *(float *)(iVar5 + 0x20)) {
    avatar::getWorldPosition(&local_3c->avatar,&local_2c);
    if ((float)paVar2->attacks * (local_20.pos.z - local_2c.z) +
        (local_20.pos.x - local_2c.x) * (float)paVar2->attackDataRes +
        (local_20.pos.y - local_2c.y) * 0.0 < 0.0) {
      fVar1 = *(float *)(param_2 + 0x20);
      local_20.pos.x = (float)paVar2->attackDataRes * fVar1 + local_20.pos.x;
      local_20.pos.y = fVar1 * 0.0 + local_20.pos.y;
      local_20.pos.z = (float)paVar2->attacks * fVar1 + local_20.pos.z;
    }
  }
  paVar3 = local_3c;
  avatar::getWorldPosition(&local_3c->avatar,&local_2c);
  iVar5 = FUN_0012cc50(&local_20.pos,1,0,0,0,0,&local_3c,(paVar3->avatar).tag);
  this = local_38;
  if (iVar5 == 0) {
    local_3c = (actor *)0x0;
  }
  else {
    paVar8 = (actorBody *)(local_38->actor->avatar).scale.z;
    local_38 = paVar8;
    FUN_0001d3d0();
    local_3c = (actor *)((float)paVar8 + this->closenessDistance * (float)local_38 +
                         *(float *)(param_2 + 0x18) + local_20.field11_0x1c + 1.0);
  }
  iVar5 = param_2;
  if (local_34 == 0) {
    uVar7 = (*(byte *)((int)&paVar2->largeProjectile + 2) & 0x10) >> 4;
  }
  else {
    uVar7 = 0;
  }
  iVar4 = FUN_00136b00((uint)*(byte *)((int)&(paVar2->worldPosition).x + 1),param_1,local_30,
                       &local_20.pos,(float)local_3c,*(float *)(param_2 + 0x1c),
                       *(float *)(param_2 + 0x2c),uVar7,&param_2);
  if ((*(int *)(iVar5 + 0x24) != 0) && (iVar4 == 1)) {
    BVar6 = actorBody::setWaitUntilCanAttack(this,1);
    if (BVar6 == 0) {
      return 0;
    }
  }
  return iVar4;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


undefined4 FUN_0007bf60(actorMind *param_1)

{
  actor *av;
  actorBody *paVar1;
  InputHandlerBase *pIVar2;
  avatar_0x918 pEVar3;
  actorMind *paVar4;
  weapon *wpn;
  int iVar5;
  int local_20;
  float local_1c;
  vec3 local_18;
  vec3 local_c;
  
  wpn = (weapon *)param_1->mind51;
  av = param_1->actor;
  paVar1 = av->body;
  pIVar2 = av->input_handler_;
  if (wpn == (weapon *)0x0) {
    return 1;
  }
  pEVar3 = (wpn->avatar).node0x918.prev;
  if (((((pEVar3 != (avatar_0x918)0x0) && (pEVar3->prev != (avatar_0x918)0x0)) &&
       (pEVar3 != (avatar_0x918)0x918)) ||
      ((wpn->field9_0x93c == '\0' || (*(int *)&wpn->field_0xad0 != 0)))) ||
     (wpn->field378_0xac4 == 0)) {
    avatar::getWorldPosition(&av->avatar,&local_18);
    wpn = (weapon *)FUN_00129d70(&local_18,av,0,0x1f);
    if (wpn == (weapon *)0x0) {
      param_1->mind51 = (Mind51 *)0x0;
      return 1;
    }
    param_1->mind51 = (Mind51 *)wpn;
  }
  if ((paVar1->field13_0x30 != 0) || (paVar1->someTimer2 != 0.0)) {
    return 0;
  }
  avatar::getWorldPosition(&av->avatar,&local_c);
  iVar5 = FUN_001476d0(&local_1c,&local_20,&local_18,&local_c,wpn);
  paVar4 = param_1;
  if (iVar5 != 0) {
    FUN_00136b00(*(undefined4 *)&wpn->field_0xd00,param_1,pIVar2,&local_18,0.0,30.0,1.0,0,&param_1);
    iVar5 = FUN_00027d40();
    if ((iVar5 != 0) && (paVar4[1].currentAttackTarget != (actorBody *)0x0)) {
      return 1;
    }
    if (param_1 == (actorMind *)0x0) {
      return 0;
    }
    iVar5 = Background::isCollisionThings(av->backgroundCollisionIndex,&local_18);
    if ((iVar5 != -1) && (iVar5 = FUN_000368c0(paVar4->astarShit->field7_0x10,iVar5), iVar5 == 0)) {
      return 0;
    }
  }
  return 4;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields

MindActionReturnCode
entityMindHuman::goalFunc1
          (entityMindHuman *mind,actorMindGoal *goal,int param_3,entityMindHuman *param_4)

{
  actorMindGoal *point;
  actor *paVar1;
  entityMindHuman *peVar2;
  actorBody *this;
  actorBody *paVar3;
  entityMindHuman *this_00;
  actorMindGoal *goal_00;
  bool bVar4;
  actorBodyStateId aVar5;
  undefined4 extraout_EAX;
  BOOL BVar6;
  int iVar7;
  MindActionReturnCode MVar8;
  vec3 *point_00;
  float10 fVar9;
  float fVar10;
  float fVar11;
  float fVar12;
  int iVar13;
  entityMindHuman **ppeVar14;
  vec3 setup_pos;
  
  goal_00 = goal;
  this_00 = mind;
  paVar1 = (mind->actorMind).actor;
  peVar2 = (entityMindHuman *)paVar1->input_handler_;
  this = paVar1->body;
  switch(goal->goalId) {
  case AttackTarget:
    mind = peVar2;
    bVar4 = actorMind::onGoalAttackTarget(&this_00->actorMind,(actorMindGoalAttackTarget *)goal);
    return (uint)bVar4;
  default:
    mind = peVar2;
    MVar8 = actorMind::executeGoal(&this_00->actorMind,goal);
    return MVar8;
  case CelebrateIfFlag:
    mind = peVar2;
    fVar10 = (float)actorBody::getFlagIdByName((char *)(goal + 1));
    BVar6 = actorBody::flagIsSet(this,CONCAT31((int3)((uint)extraout_EAX >> 8),(unkfloat1)fVar10));
    if (BVar6 == 0) {
      return Success;
    }
    BVar6 = Random::thresholdCheck(&runtime::rand,goal_00[4].prev);
    peVar2 = mind;
    if (BVar6 == 0) {
      return Success;
    }
  case Celebrate:
    mind = peVar2;
    aVar5 = (*this->vtable->getCheerState)(this);
    actorBody::setState(this,aVar5);
    return Success;
  case Evade:
    mind = peVar2;
    FUN_0007ccd0(this_00);
    MVar8 = FUN_0007b170(this_00,goal_00);
    return MVar8;
  case EvadeFly:
    mind = peVar2;
    FUN_0007ccd0(this_00);
    MVar8 = FUN_0007b2f0(this_00);
    return MVar8;
  case FlyToDestination:
    mind = peVar2;
    MVar8 = FUN_0007b5a0(goal,this_00);
    return MVar8;
  case FlyToPoint:
    mind = peVar2;
    FUN_0007ccd0(this_00);
    MVar8 = FUN_00136680(goal_00,this_00,mind);
    return MVar8;
  case FlyToTarget:
    mind = peVar2;
    MVar8 = FUN_0007b620(this_00);
    return MVar8;
  case GenerateEvasionDestination:
    mind = peVar2;
    MVar8 = onGenerateEvasionDestinationGoal(goal,this_00);
    return MVar8;
  case GenerateRandomDestination:
    mind = peVar2;
    MVar8 = FUN_0007b8a0(this_00);
    return MVar8;
  case GenerateRandomDestinationInFront:
    mind = peVar2;
    MVar8 = FUN_0007b940(this_00);
    return MVar8;
  case ObserveTarget:
    mind = peVar2;
    MVar8 = FUN_0007b800(this_00,param_3);
    return MVar8;
  case PickupWeaponOfAttention:
    mind = peVar2;
    MVar8 = FUN_0007b840();
    return MVar8;
  case ReturnToSetupPosition:
    setup_pos.x = (paVar1->setup_position_).x;
    ppeVar14 = &mind;
    iVar13 = 0;
    fVar12 = 1.0;
    fVar11 = 30.0;
    setup_pos.y = (paVar1->setup_position_).y;
    fVar10 = 5.0;
    setup_pos.z = (paVar1->setup_position_).z;
    mind = peVar2;
    iVar7 = FUN_00110bf0(&setup_pos,-1,0);
    MVar8 = FUN_00136b00(iVar7,&this_00->actorMind,(InputHandlerBase *)mind,&setup_pos,fVar10,fVar11
                         ,fVar12,iVar13,ppeVar14);
    if ((MVar8 == StopAndUpdateT) &&
       (iVar7 = FUN_001373f0(&this_00->actorMind,&setup_pos), iVar7 != 0)) {
      return Success;
    }
    return MVar8;
  case StepInDirection:
    mind = peVar2;
    MVar8 = FUN_0007ba20(this_00,goal);
    return MVar8;
  case TurnToFaceDestination:
    point_00 = &(mind->actorMind).evasionPos;
    mind = peVar2;
    actorBody::turnToFacePoint(this,point_00);
    FUN_00041ae0(&paVar1->avatar,point_00);
    mind = param_4;
    break;
  case TurnToFacePoint:
    point = goal + 1;
    mind = peVar2;
    actorBody::turnToFacePoint(this,(vec3 *)point);
    FUN_00041ae0(&paVar1->avatar,(vec3 *)point);
    goal = (actorMindGoal *)(goal_00[1].t * 0.017453292);
    mind = param_4;
    fVar9 = abs_float((float)param_4);
    if ((float10)(float)goal <= fVar9) {
      return StopAndUpdateT;
    }
    return Success;
  case TurnToFaceTarget:
    paVar3 = (mind->actorMind).targetBody;
    if (paVar3 == (actorBody *)0x0) {
      return Success;
    }
    mind = peVar2;
    FUN_001345f0(this,paVar3);
    FUN_00041ae0(&paVar1->avatar,(vec3 *)&(paVar3->worldPosition).z);
    mind = param_4;
    break;
  case WalkToDestination:
    mind = peVar2;
    FUN_0007ccd0(this_00);
    MVar8 = actorMind::onWalkToDestinationGoal
                      (&this_00->actorMind,(actorMindGoalWalkToDestination *)goal_00);
    return MVar8;
  case WalkToPoint:
    mind = peVar2;
    FUN_0007ccd0(this_00);
    MVar8 = FUN_00136620(mind);
    return MVar8;
  case WalkToTarget:
    mind = peVar2;
    FUN_0007ccd0(this_00);
    MVar8 = FUN_0007bc80(this_00,goal_00);
    return MVar8;
  case WalkToWeaponOfAttention:
    mind = peVar2;
    FUN_0007ccd0(this_00);
    MVar8 = FUN_0007bf60(this_00);
    return MVar8;
  case Worried:
    mind = peVar2;
    aVar5 = (*this->vtable->getCringeState)(this);
    actorBody::setState(this,aVar5);
    return Success;
  }
  goal = (actorMindGoal *)((float)goal_00[1].prev * 0.017453292);
  fVar9 = abs_float((float)mind);
  if ((float10)(float)goal <= fVar9) {
    return StopAndUpdateT;
  }
  return Success;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void actorMind::lookupObjectType(actorMind *mind)

{
  int index;
  
  if (mind->actor->skipObjectTypeLookup == 0) {
    index = 0;
    if (0 < NumObjectTypes) {
      do {
        if ((mind->actor->avatar).tag == ObjectTypes[index].tag) {
          return;
        }
        index = index + 1;
      } while (index < NumObjectTypes);
    }
    mind->floatFromTagList = 0;
  }
  return;
}




void entityMindHuman::getAllocDetails(ObjectAllocDetails *param_1)

{
  param_1->entitySize = 0xd0;
  param_1->paramsSize = 0x128;
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


actorMindVTable * entityMindHuman::getVTable(void)

{
  vtable.onRemoveAction = switchD_000d4179::EmptyFunction;
  vtable.getAllocDetails = getAllocDetails;
  vtable.ctor = ctor;
  vtable.dtor = dtor;
  vtable.onMessage = onMessage;
  vtable.update = update;
  vtable.executeGoal = goalFunc1;
  vtable.initialiseGoal = goalFunc2;
  return &vtable;
}




undefined4 entityMindHuman::ctor(entityMindHuman *mind,entityMindHumanParams *params)

{
  uint *puVar1;
  actor *innerParams1;
  
  *(float *)&mind->field_0x7c = params->someFloat1;
  innerParams1 = (mind->actorMind).actor;
  *(float *)&mind->field_0x80 = params->someFloat2;
  if ((innerParams1->avatar).field218_0x1fc == 0) {
    puVar1 = &(mind->actorMind).flags;
    *puVar1 = *puVar1 & 0xffffffdf;
    (mind->actorMind).floatFromTagList = 0;
  }
  mind->field22_0xa0 = 0.0;
  mind->field21_0x9c = 0.0;
  mind->field24_0xa8 = 0.0;
  mind->field23_0xa4 = 0.0;
  mind->field26_0xb0 = 1;
  mind->field25_0xac = 0.0;
  mind->field28_0xb8 = 0.0;
  mind->field27_0xb4 = 0.0;
  mind->field30_0xc0 = 0.0;
  mind->field29_0xbc = 0.0;
  mind->field32_0xc8 = 1;
  mind->field31_0xc4 = 0.0;
  FUN_0007cc00(mind,params);
  return 1;
}




void entityMindHuman::dtor(int param_1)

{
  if (*(void **)(param_1 + 0x84) != (void *)0x0) {
    Assets::DestroyAssetOrDecrement(*(void **)(param_1 + 0x84));
    *(undefined4 *)(param_1 + 0x84) = 0;
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void entityMindHuman::onMessage(entityMindHuman *mind,Message *bundle)

{
  actorBody *target;
  uint32_t uVar1;
  float fVar2;
  
  switch((bundle->header).msgId) {
  case Avatar_SceneInsert:
    actorMind::lookupObjectType(&mind->actorMind);
    actorMind::onMessage(&mind->actorMind,bundle);
    return;
  case Actor_Dying:
    actorMind::onDying(&mind->actorMind,bundle);
    actorMind::onMessage(&mind->actorMind,bundle);
    return;
  case Actor_Fright:
    FUN_00137c30(bundle);
    actorMind::onMessage(&mind->actorMind,bundle);
    return;
  case Actor_TimeTraitorExpired:
    target = (mind->actorMind).targetBody;
    if ((target != (actorBody *)0x0) &&
       (uVar1 = actorMind::doTraitorStuffOrFight(&mind->actorMind,target,1), uVar1 == 0)) {
      (mind->actorMind).targetBody = (actorBody *)0x0;
      actorMind::onMessage(&mind->actorMind,bundle);
      return;
    }
    break;
  case Actor_WithinScareRadius:
    FUN_00137a80();
    actorMind::onMessage(&mind->actorMind,bundle);
    return;
  case ActorMind_TargetLost:
    if (((mind->actorMind).actor)->actorType == Ghoulie_old) {
      (mind->actorMind).flags = (mind->actorMind).flags | 0x20;
      actorMind::onMessage(&mind->actorMind,bundle);
      return;
    }
    break;
  case Scene_ActorHit:
    if (((bundle->header).someActor == (mind->actorMind).actor) &&
       (fVar2 = (mind->actorMind).targetTimer + 5.0, (mind->actorMind).targetTimer = fVar2,
       15.0 < fVar2)) {
      (mind->actorMind).targetTimer = 15.0;
      actorMind::onMessage(&mind->actorMind,bundle);
      return;
    }
    break;
  case Scene_Begin:
    FUN_00136700(mind);
    break;
  case Weapon_AwaitingPickup:
    if ((bundle->header).someActor == (actor *)(mind->actorMind).mind51) {
      *(undefined4 *)&mind->field_0x90 = 1;
      actorMind::onMessage(&mind->actorMind,bundle);
      return;
    }
  }
  actorMind::onMessage(&mind->actorMind,bundle);
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void FUN_0007cab0(entityMindHuman *param_1)

{
  actor *av;
  Buffer<> *pBVar1;
  int iVar2;
  actorDroneActionId *paVar3;
  float fVar4;
  undefined4 uVar5;
  float fVar6;
  vec3 local_18;
  vec3 local_c;
  
  av = (param_1->actorMind).actor;
  pBVar1 = av->droneActionsBuf;
  if (pBVar1 != (Buffer<> *)0x0) {
    if (pBVar1->size == pBVar1->endOfQueue) {
      paVar3 = (actorDroneActionId *)0x0;
    }
    else {
      paVar3 = (actorDroneActionId *)
               ((int)&pBVar1->entries->actionId +
               (uint)pBVar1->currentDroneAction * (uint)pBVar1->valueSize);
    }
    if (*paVar3 != Null) {
      return;
    }
  }
  if (runtime::dx_timer <= 0.0) {
    fVar4 = runtime::DeltaTime * runtime::TimeScale;
  }
  else {
    fVar4 = 0.0;
  }
  fVar6 = 0.0;
  if ((av->avatar).movementFreezeTimer <= 0.0) {
    fVar6 = (av->avatar).actionSpeed;
  }
  fVar4 = param_1->field33_0xcc - fVar6 * fVar4;
  param_1->field33_0xcc = fVar4;
  if (fVar4 <= 0.0) {
    param_1->field33_0xcc = fVar4 + 1.0;
    actorMind::removeGoals(&param_1->actorMind);
  }
  if ((param_1->actorMind).actionInfo.next == (actorGoalInfo *)0x0) {
    avatar::getWorldPosition(&av->avatar,&local_18);
    uVar5 = 0x3f32b8c2;
    FUN_00100c70((av->avatar).rotEuler.y);
    iVar2 = FUN_0013aa50(uVar5,av->backgroundCollisionIndex,0x3e9c61aa,10,0x41400000,0x41780000,0,
                         av->field812_0xca4,&local_c,1,0xd,(av->avatar).tag);
    if (iVar2 != 0) {
      iVar2 = actorMind::newGoal46(param_1,&local_c);
      *(float *)(iVar2 + 0x1c) = 1.0;
      *(float *)(iVar2 + 0x20) = 1.0;
      *(undefined4 *)(iVar2 + 0x28) = 0;
    }
  }
  return;
}



// WARNING: Removing unreachable block (ram,0x0007cc1d)
// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void FUN_0007cc00(entityMindHuman *mind,entityMindHumanParams *params)

{
  float fVar1;
  int i;
  char *pcVar2;
  generalsFx *new_object;
  
  if (*(int *)params->generalsFxAID == 0x5f646961) {
    Assets::GetResourceBytes(params->generalsFxAID,&new_object);
    if (new_object == (generalsFx *)0x0) {
      runtime::ExitGame(2);
    }
    mind->generalsFx = new_object;
    if (new_object != (generalsFx *)0x0) {
      i = 0;
      pcVar2 = &new_object->field_0x10;
      do {
        if (*pcVar2 == '\0') break;
        i = i + 1;
        pcVar2 = pcVar2 + 0x80;
        mind->fxCount_ = mind->fxCount_ + 1;
      } while (i < 3);
    }
  }
  if (mind->fxCount_ != 0) {
    fVar1 = mind->generalsFx->float1;
    runtime::rand = runtime::rand * 0x19660d + 0x3c6ef35f;
    mind->floatFromGeneralsFx =
         (mind->generalsFx->field1_0x4 - fVar1) *
         ((float)(runtime::rand & 0x7fffff | 0x3f800000) - 1.0) + fVar1;
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void FUN_0007ccd0(entityMindHuman *param_1)

{
  actor *paVar1;
  float fVar2;
  float fVar3;
  
  if (param_1->fxCount_ != 0) {
    paVar1 = (param_1->actorMind).actor;
    if ((paVar1->body->field13_0x30 == 0) && (paVar1->body->someTimer2 == 0.0)) {
      if (runtime::dx_timer <= 0.0) {
        fVar2 = runtime::DeltaTime * runtime::TimeScale;
      }
      else {
        fVar2 = 0.0;
      }
      fVar3 = 0.0;
      if ((paVar1->avatar).movementFreezeTimer <= 0.0) {
        fVar3 = (paVar1->avatar).actionSpeed;
      }
      if ((0.0 < param_1->floatFromGeneralsFx) &&
         (fVar2 = param_1->floatFromGeneralsFx - fVar3 * fVar2, param_1->floatFromGeneralsFx = fVar2
         , fVar2 <= 0.0)) {
        param_1->floatFromGeneralsFx = 0.0;
        runtime::rand = runtime::rand * 0x19660d + 0x3c6ef35f;
        FUN_00041d00(runtime::rand & 0x7fffff | 0x3f800000);
        fVar2 = *(float *)&param_1->generalsFx->field_0x8;
        runtime::rand = runtime::rand * 0x19660d + 0x3c6ef35f;
        param_1->floatFromGeneralsFx =
             (*(float *)&param_1->generalsFx->field_0xc - fVar2) *
             ((float)(runtime::rand & 0x7fffff | 0x3f800000) - 1.0) + fVar2;
      }
    }
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void entityMindHuman::update(entityMindHuman *mind,InputHandlerType1 *param_2)

{
  char cVar1;
  actor *av;
  actor *paVar2;
  actorBody *paVar3;
  bool bVar4;
  uint32_t uVar5;
  float10 extraout_ST0;
  float10 fVar6;
  float delta;
  vec3 local_28;
  actorBody *local_1c;
  vec3 local_18;
  vec3 local_c;
  actorBody *body;
  float currF;
  float *minF;
  
  av = (mind->actorMind).actor;
  body = av->body;
  if (0.0 < mind->field20_0x98) {
    FUN_0007cab0(mind);
  }
  actorMind::updateStateType(&mind->actorMind);
  actorMind::runNextAction(&mind->actorMind);
  actorMind::updateMemoryTimers(&mind->actorMind);
  currF = 0.0;
  paVar2 = (mind->actorMind).actor;
  if (runtime::dx_timer <= 0.0) {
    delta = runtime::DeltaTime * runtime::TimeScale;
  }
  else {
    delta = 0.0;
  }
  if ((paVar2->avatar).movementFreezeTimer <= 0.0) {
    currF = (paVar2->avatar).actionSpeed;
  }
  (mind->actorMind).t = currF * delta + (mind->actorMind).t;
  actorMind::updateBodyGoal(&mind->actorMind);
  FUN_00137140(0,20.0,(entityMindPlayer *)mind);
  paVar2 = (mind->actorMind).targetActor;
  if (paVar2 == (actor *)0x0) {
    if (((mind->actorMind).field_0x20 != '\0') &&
       (currF = (mind->actorMind).minF, minF = &(mind->actorMind).t,
       *minF <= currF && currF != *minF)) {
      (mind->actorMind).t = (mind->actorMind).minF;
    }
    (mind->actorMind).field_0x20 = 0;
  }
  else {
    avatar::getWorldPosition(&av->avatar,&local_28);
    avatar::getWorldPosition(&paVar2->avatar,&local_18);
    cVar1 = (mind->actorMind).field_0x20;
    currF = (local_28.z - local_18.z) * (local_28.z - local_18.z) +
            (local_28.y - local_18.y) * (local_28.y - local_18.y) +
            (local_28.x - local_18.x) * (local_28.x - local_18.x);
    if (cVar1 == '\0') {
      delta = *(float *)&mind->field_0x7c;
      if (delta <= 0.0) {
        currF = (mind->actorMind).minF;
        minF = &(mind->actorMind).t;
        if (*minF <= currF && currF != *minF) {
          (mind->actorMind).t = (mind->actorMind).minF;
        }
        (mind->actorMind).field_0x20 = 1;
      }
      else {
        bVar4 = currF < delta * delta;
        if ((bVar4) &&
           (currF = (mind->actorMind).minF, minF = &(mind->actorMind).t,
           *minF <= currF && currF != *minF)) {
          (mind->actorMind).t = (mind->actorMind).minF;
        }
        (mind->actorMind).field_0x20 = bVar4;
      }
    }
    else {
      delta = *(float *)&mind->field_0x80;
      if (0.0 < delta) {
        bVar4 = currF < delta * delta;
        if ((bVar4 != (bool)cVar1) &&
           (currF = (mind->actorMind).minF, minF = &(mind->actorMind).t,
           *minF <= currF && currF != *minF)) {
          (mind->actorMind).t = (mind->actorMind).minF;
        }
        (mind->actorMind).field_0x20 = bVar4;
      }
    }
  }
  paVar3 = (mind->actorMind).targetBody;
  local_1c = paVar3;
  if (paVar3 == (actorBody *)0x0) {
LAB_0007d09b:
    if (body->field_0x6a != '\0') goto LAB_0007d0ad;
  }
  else if (body->field_0x6a != '\0') {
    avatar::getWorldPosition(&av->avatar,&local_18);
    local_c.x = (paVar3->worldPosition).z - local_18.x;
    local_c.y = (paVar3->worldPos).x - local_18.y;
    local_c.z = (paVar3->worldPos).y - local_18.z;
    vec3::getTurnAngle(&local_c,&local_28.x);
    currF = local_28.x;
    sin(local_28.x);
    local_28.x = (float)extraout_ST0;
    fVar6 = (float10)cos(currF);
    local_28.y = (float)fVar6;
    RunInputCallbacks(param_2);
    goto LAB_0007d09b;
  }
  *(undefined4 *)&body->useAttackParam3 = 0;
  (mind->actorMind).currentAttackTarget = (actorBody *)0x0;
LAB_0007d0ad:
  body->field_0xaa = 0;
  if ((local_1c != (actorBody *)0x0) &&
     (((0.0 < av->traitorTimer || (av->randTraitoristicCombat != '\0')) &&
      (uVar5 = actorMind::doTraitorStuffOrFight(&mind->actorMind,local_1c,1), uVar5 == 0)))) {
    body->field_0xaa = 1;
  }
  actorBodyInteractiveVals::handleScaredMovement
            ((actorBodyInteractiveVals *)&mind->field_0x94,0,1.0);
  if (0 < *(int *)&mind->field_0x90) {
    *(int *)&mind->field_0x90 = *(int *)&mind->field_0x90 + -1;
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void entityMindPlayer::handleInteractivePlayerUpdate(entityMindPlayer *this)

{
  InputHandlerType1 *input_handler;
  int scared;
  float delta;
  
  input_handler = (InputHandlerType1 *)((this->actorMind).actor)->input_handler_;
  if (runtime::dx_timer <= 0.0) {
    delta = runtime::DeltaTime * runtime::TimeScale;
  }
  else {
    delta = 0.0;
  }
  if ((0.0 < this->attackTimer) &&
     (delta = this->attackTimer - delta, this->attackTimer = delta, delta <= 0.0)) {
    this->attackTimer = 0.0;
  }
  FUN_0007ee40(input_handler);
                    // Handle attack
  handleInputAndUpdateTimers(this,input_handler);
  FUN_0007d210(input_handler);
  FUN_00137140(1,30.0,this);
  decideAttack(this,input_handler);
  FUN_0007d280();
  scared = actorBodyInteractiveVals::handleScaredMovement(&this->interactiveVals,0x2fff24,2.5);
  if (scared != 0) {
    scared = FUN_0007f980(this,input_handler);
    if (scared != 0) goto LAB_0007d1fe;
  }
  *(undefined4 *)&this->field_0x194 = 0;
LAB_0007d1fe:
  FUN_0007d300();
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


MindActionReturnCode entityMindPlayer::goalFunc1(actorMind *param_1,actorMindGoal *param_2)

{
  actorBody *this;
  actorBodyStateId aVar1;
  undefined4 extraout_EAX;
  MindActionReturnCode MVar2;
  float fVar3;
  
  this = param_1->actor->body;
  switch(param_2->goalId) {
  case Celebrate:
    goto switchD_0007d38a_caseD_7;
  case CelebrateIfFlag:
    fVar3 = (float)actorBody::getFlagIdByName((char *)(param_2 + 1));
    if (('\x01' << ((byte)(unkfloat1)fVar3 & 7) &
        *(byte *)((int)&this->flagSet->flags->flag1 +
                 (CONCAT31((int3)((uint)extraout_EAX >> 8),(unkfloat1)fVar3) >> 3))) == 0) {
      return Success;
    }
switchD_0007d38a_caseD_7:
    aVar1 = (*this->vtable->getCheerState)(this);
    actorBody::setState(this,aVar1);
    return Success;
  default:
    MVar2 = actorMind::executeGoal(param_1,param_2);
    return MVar2;
  case Interactive:
    handleInteractivePlayerUpdate((entityMindPlayer *)param_1);
    return StopAndUpdateT;
  case WalkToPoint:
    MVar2 = FUN_00136620(param_1->actor->input_handler_);
    return MVar2;
  case Worried:
    aVar1 = (*this->vtable->getCringeState)(this);
    actorBody::setState(this,aVar1);
    return Success;
  }
}




void actorMind::onDying(actorMind *mind,Message *msg)

{
  BOOL fifty_fifty;
  actor *act;
  actorBody *body;
  weapon *weapon;
  
  act = mind->actor;
  body = act->body;
  weapon = body->weapon;
                    // If weapon is breakable, then break it???
  if ((((weapon != (weapon *)0x0) && (weapon->holdableType == Gun)) &&
      ((char)*(byte *)((int)&body->flagSet->flags->attackFlags_ + 1) < '\0')) &&
     ((mind->currentAttackTarget != (actorBody *)0x0 &&
      (mind->currentAttackTarget->currentWeapon == (weapon *)(msg->header).someActor)))) {
    fifty_fifty = Random::thresholdCheck(&runtime::rand,0.5);
    if (fifty_fifty != 0) {
      ::actor::executeCallout(act,0,Laugh);
    }
  }
  return;
}




void entityMindPlayer::getAllocDetails(ObjectAllocDetails *param_1)

{
  param_1->entitySize = 0x198;
  param_1->paramsSize = 0xa4;
  return;
}



// WARNING: Globals starting with '_' overlap smaller symbols at the same address
// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


undefined * entityMindPlayer::getVTable(void)

{
  _DAT_005054b4 = switchD_000d4179::EmptyFunction;
  _vtable = getAllocDetails;
  _DAT_0050549c = ctor;
  _DAT_005054a0 = dtor;
  _DAT_005054a4 = onMessage;
  _DAT_005054a8 = update;
  _DAT_005054ac = goalFunc1;
  _DAT_005054b0 = goalFunc2;
  return &vtable;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void entityMindPlayer::decideAttack(entityMindPlayer *param_1,InputHandlerType1 *param_2)

{
  actor *act;
  actorBody *body;
  bool bVar1;
  entityMindPlayer *peVar2;
  int iVar3;
  StatetableEntry *entry;
  float delta;
  vec2 local_8;
  
  peVar2 = param_1;
  act = (param_1->actorMind).actor;
  body = act->body;
  Input::GetLSMovement_(param_2,&local_8);
  if ((0.010000001 < local_8.y * local_8.y + local_8.x * local_8.x) ||
     (ScriptType1::getControllerXY(param_2,&local_8),
     0.010000001 < local_8.y * local_8.y + local_8.x * local_8.x)) {
    peVar2->t = 0.0;
    *(undefined4 *)&peVar2->field_0x150 = 0;
    peVar2->shouldCower = 0;
  }
  else {
    delta = 0.0;
    if (runtime::dx_timer <= 0.0) {
      delta = runtime::DeltaTime * runtime::TimeScale;
    }
    peVar2->t = peVar2->t + delta;
  }
  if (*(int *)&peVar2->field_0x144 == 0) {
    return;
  }
  if ((((body->stateId == Cower) &&
       (iVar3 = CheckAnimKfcThreshold((void *)0x0,act,peVar2->randAttackFloat), iVar3 != 0)) &&
      ((peVar2->actorMind).field_0x20 != '\0')) && (iVar3 = useCowerAttack(body,peVar2), iVar3 != 0)
     ) {
    peVar2->shouldCower = 1;
  }
  if (body->field13_0x30 != 0) {
    return;
  }
  if (body->someTimer2 != 0.0) {
    return;
  }
  if ((body->flagSet->flags->attackFlags_ & 0x10000) == Null) {
    return;
  }
  if ((body->weapon == (weapon *)0x0) && (*(int *)&body->field_0x50 == 0)) {
    if ((10.0 < peVar2->t) && (2 < *(int *)&peVar2->field_0x150)) {
      bVar1 = true;
      goto LAB_0007e2e0;
    }
  }
  else {
    peVar2->shouldCower = 0;
  }
  bVar1 = false;
LAB_0007e2e0:
  if ((peVar2->actorMind).field_0x20 == '\0') {
    peVar2->shouldCower = 0;
  }
  if ((bVar1) || (peVar2->shouldCower != 0)) {
    if ((body->statetableRes != (StatetableResource *)0x0) &&
       (entry = binarySearchStateTable(body->statetableRes,(Asset **)&param_1,Cower),
       entry != (StatetableEntry *)0x0)) {
      actorBody::updateStatesFromEntry(body,(AttackEntry *)param_1,entry);
    }
    peVar2->t = 0.0;
    *(undefined4 *)&peVar2->field_0x150 = 0;
    peVar2->shouldCower = 1;
    runtime::rand = runtime::rand * 0x19660d + 0x3c6ef35f;
    peVar2->randAttackFloat =
         ((float)(runtime::rand & 0x7fffff | 0x3f800000) - 1.0) * 0.34999996 + 0.6;
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void entityMindPlayer::largeAttackHandler(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  int iVar2;
  entityMindPlayer *unaff_ESI;
  float fVar3;
  float fVar4;
  
  if ((((unaff_ESI->actorMind).actor)->body->flagSet->flags->flag1 & 0x8000000) == Null) {
    iVar1 = FUN_0007e6b0();
    iVar2 = FUN_0007e880(param_1,param_2);
    if ((((iVar1 != 0) && (iVar2 != 0)) && (iVar1 != *(int *)(iVar2 + 0x10))) &&
       (*(char *)(iVar2 + 0x14) == '\0')) {
      iVar1 = FUN_0007e960(iVar2);
      if (iVar1 != 0) {
        (unaff_ESI->actorMind).targetActor = *(actor **)(iVar2 + 0x10);
      }
    }
    if (*(int *)&unaff_ESI->field_0x124 != 0) {
      fVar3 = *(float *)&unaff_ESI->field_0x120 * 0.02 * 3.0;
      if (fVar3 <= 3.0) {
        if (fVar3 < 0.0) {
          fVar3 = 0.0;
        }
      }
      else {
        fVar3 = 3.0;
      }
      if (runtime::dx_timer <= 0.0) {
        fVar4 = runtime::DeltaTime * runtime::TimeScale;
      }
      else {
        fVar4 = 0.0;
      }
      fVar4 = *(float *)&unaff_ESI->field_0x128 - fVar4;
      *(float *)&unaff_ESI->field_0x128 = fVar4;
      if (fVar4 <= 0.0) {
        *(float *)&unaff_ESI->field_0x128 = fVar4 + fVar3;
        RegisterAssetEventFromMap__(unaff_ESI,0xe);
        *(undefined4 *)&unaff_ESI->field_0x124 = 0;
      }
    }
  }
  return;
}




MindMemoryHeader * FUN_0007e880(int param_1,undefined4 param_2)

{
  HoldableType HVar1;
  actorBody *paVar2;
  weapon *pwVar3;
  actorMind *in_EAX;
  MindMemoryHeader *pMVar4;
  MindMemoryTargetWantedToAttack *mem;
  MindMemoryHeader *pMVar5;
  
  pMVar4 = in_EAX->memoryHead;
  paVar2 = in_EAX->actor->body;
  do {
    if (pMVar4 == (MindMemoryHeader *)0x0) {
      pMVar4 = (MindMemoryHeader *)0x0;
LAB_0007e8aa:
      if (param_1 != 0) {
        pMVar4 = (MindMemoryHeader *)FUN_0007d6b0(pMVar4,param_2);
        if (pMVar4 == (MindMemoryHeader *)0x0) {
          pMVar4 = (MindMemoryHeader *)FUN_0007ea20();
        }
        else {
          pwVar3 = paVar2->weapon;
          if (((pwVar3 == (weapon *)0x0) || (HVar1 = pwVar3->holdableType, HVar1 < Container)) ||
             ((HVar1 == Gun && (in_EAX[1].t != 4.2039e-45)))) {
            pMVar4 = (MindMemoryHeader *)FUN_0007e9e0();
          }
        }
        if (pMVar4 != (MindMemoryHeader *)0x0) {
          pMVar5 = actorMind::addMemory(in_EAX,TargedWantedToAttack,0.5);
          pMVar5[1].prev = pMVar4;
          return pMVar4;
        }
      }
      mem = (MindMemoryTargetWantedToAttack *)in_EAX->memoryHead;
      if (mem != (MindMemoryTargetWantedToAttack *)0x0) {
        while ((mem->header).memId != TargedWantedToAttack) {
          mem = (MindMemoryTargetWantedToAttack *)(mem->header).next;
          if (mem == (MindMemoryTargetWantedToAttack *)0x0) {
            return (MindMemoryHeader *)0x0;
          }
        }
        MindMemory::dtor(mem);
      }
      return (MindMemoryHeader *)0x0;
    }
    if (pMVar4->memId == TargedWantedToAttack) {
      pMVar4 = pMVar4[1].prev;
      goto LAB_0007e8aa;
    }
    pMVar4 = pMVar4->next;
  } while( true );
}




undefined4 entityMindPlayer::goalFunc2(entityMindPlayer *param_1,int param_2)

{
  actorBody *paVar1;
  actor *paVar2;
  float in_XMM0_Da;
  float fVar3;
  
  paVar1 = (param_1->actorMind).targetBody;
  paVar2 = (param_1->actorMind).actor;
  if (*(short *)(param_2 + 8) == 0x29) {
    runtime::rand = runtime::rand * 0x19660d + 0x3c6ef35f;
    in_XMM0_Da = (*(float *)(param_2 + 0x14) - *(float *)(param_2 + 0x10)) *
                 ((float)(runtime::rand & 0x7fffff | 0x3f800000) - 1.0) + *(float *)(param_2 + 0x10)
    ;
    *(float *)(param_2 + 0x18) = in_XMM0_Da;
  }
  switch(*(undefined2 *)(param_2 + 8)) {
  case 0xf:
    FUN_0007edf0((float *)(param_2 + 0x2c),param_2 + 0x10);
    return 1;
  case 0x10:
    FUN_0007edf0((float *)(param_2 + 0x38),param_2 + 0x1c);
    return 1;
  case 0x11:
    FUN_0007edf0((float *)(param_2 + 0x38),param_2 + 0x10);
    return 1;
  case 0x16:
    param_1->field163_0x130 = 0.0;
    *(undefined4 *)&param_1->field_0x124 = 0;
    *(undefined4 *)&param_1->field_0x94 = 0;
    param_1->gunType = 0;
    param_1->field28_0xa0 = 0.0;
    *(undefined4 *)&param_1->field_0xa4 = 0;
    *(undefined4 *)&param_1->field_0x98 = 1;
    param_1->field27_0x9c = 0.0;
    *(undefined4 *)&param_1->field_0xa8 = 0;
    *(undefined4 *)&param_1->field_0xac = 0;
    return 1;
  case 0x24:
    if ((paVar1 == (actorBody *)0x0) || (*(int *)(param_2 + 0x20) != 0)) {
      in_XMM0_Da = (paVar2->avatar).rotEuler.y;
    }
    else {
      FUN_000419d0();
    }
    runtime::rand = runtime::rand * 0x19660d + 0x3c6ef35f;
    fVar3 = 0.0 - *(float *)(param_2 + 0x14);
    *(float *)(param_2 + 0x28) =
         ((*(float *)(param_2 + 0x14) - fVar3) *
          ((float)(runtime::rand & 0x7fffff | 0x3f800000) - 1.0) + *(float *)(param_2 + 0x10) +
         fVar3) * 0.017453292 + in_XMM0_Da;
    return 1;
  case 0x2d:
    FUN_0007edf0((float *)(param_2 + 0x20),param_2 + 0x10);
    return 1;
  case 0x2e:
    FUN_0007edf0((float *)(param_2 + 0x2c),param_2 + 0x1c);
    return 1;
  case 0x2f:
    FUN_0007edf0((float *)(param_2 + 0x2c),param_2 + 0x10);
  }
  return 1;
}




undefined4 entityMindPlayer::ctor(entityMindPlayer *param_1,entityMindPlayerParams *param_2)

{
  actor *paVar1;
  actorBody *paVar2;
  StatetableResource *statetable;
  actor *paVar3;
  uint uVar4;
  StatetableEntry *pSVar5;
  int iVar6;
  undefined4 *puVar7;
  actor *inner1;
  entityMindPlayer *mind;
  
  mind = param_1;
  paVar1 = (param_1->actorMind).actor;
  if (((*SomeAS15->flags & 8) == 0) && ((g_globalFlagset & 0x200000) == 0)) {
    iVar6 = Game::Something0x7;
    if (Game::Something0x7 < 1) goto LAB_0007efa0;
  }
  else {
    iVar6 = 10;
  }
  paVar2 = paVar1->body;
  paVar2->health = (ushort)iVar6;
  paVar2->maxHealth = (ushort)iVar6;
  uVar4 = Assets::GetChapterIndexFromAID(Game::GameState.currentSceneScript);
  if (((((int)uVar4 < 9) && ((*SomeAS15->flags & 8) == 0)) && ((g_globalFlagset & 0x200000) == 0))
     && ((((byte)DAT_0050ea98 & 0x40) == 0 && (g_finishedLoading_ != 1)))) {
    FUN_001307d0();
  }
LAB_0007efa0:
  *(undefined4 *)&paVar1->field_0xce0 = 1;
  statetable = ((mind->actorMind).actor)->body->statetableRes;
  uVar4 = 0;
  if (statetable != (StatetableResource *)0x0) {
    pSVar5 = binarySearchStateTable(statetable,(Asset **)&param_1,Cower);
    uVar4 = (uint)(pSVar5 != (StatetableEntry *)0x0);
  }
  *(uint *)&mind->field_0x144 = uVar4;
  *(undefined4 *)&(mind->interactiveVals).field_0xc = 0;
  *(undefined4 *)&(mind->interactiveVals).field_0x8 = 0;
  *(undefined4 *)&(mind->interactiveVals).field_0x14 = 0;
  *(undefined4 *)&(mind->interactiveVals).field_0x10 = 0;
  *(undefined4 *)&(mind->interactiveVals).field_0x18 = 0;
  (mind->interactiveVals).field22_0x1c = 1;
  *(undefined4 *)&(mind->interactiveVals).field_0x24 = 0;
  *(undefined4 *)&(mind->interactiveVals).field_0x20 = 0;
  *(undefined4 *)&(mind->interactiveVals).field_0x2c = 0;
  *(undefined4 *)&(mind->interactiveVals).field_0x28 = 0;
  *(undefined4 *)&(mind->interactiveVals).field_0x30 = 0;
  (mind->interactiveVals).field43_0x34 = 1;
  mind->attackTimer = 1.0;
  *(BOOL *)&mind->field_0x80 = param_2->playerIsCook;
  FUN_0013ccd0((int)paVar1,1);
  *(undefined4 *)&mind->field_0x98 = 1;
  mind->field28_0xa0 = 0.0;
  *(undefined4 *)&mind->field_0xa4 = 0;
  mind->field27_0x9c = 0.0;
  *(undefined4 *)&mind->field_0x94 = 0;
  mind->gunType = 0;
  *(undefined4 *)&mind->field_0xa8 = 0;
  *(undefined4 *)&mind->field_0xac = 0;
  paVar3 = (mind->actorMind).actor;
  puVar7 = (undefined4 *)&mind->field_0xb8;
  for (iVar6 = 0x1a; iVar6 != 0; iVar6 = iVar6 + -1) {
    *puVar7 = 0;
    puVar7 = puVar7 + 1;
  }
  *(actor **)&mind->field_0xc8 = paVar3;
  *(undefined2 *)&mind->field_0xce = 0;
  mind->field_0xcc = 3;
  (paVar1->avatar).field_0x331 = 1;
  return 1;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void entityMindPlayer::dtor(int param_1)

{
  if (((g_globalFlagset & 0x800) == 0) && (*(int *)(*(int *)(param_1 + 8) + 0x960) != 0)) {
    Scripting::PopInputHandler();
    return;
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void entityMindPlayer::onMessage(entityMindPlayer *mind,Message *msg)

{
  BOOL iVar5;
  int iVar1;
  bool bVar6;
  bool bVar7;
  float fVar8;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  Director_PlayerDeflectionContactMessage local_34;
  vec3 local_1c;
  vec3 local_10;
  actor *paVar2;
  actor *paVar3;
  actorBody *paVar4;
  ushort uVar1;
  
  paVar3 = (mind->actorMind).actor;
  switch((msg->header).msgId) {
  case Avatar_SceneInsert:
    FUN_0007f870(paVar3);
    actorMind::onMessage(&mind->actorMind,msg);
    return;
  case Actor_AttackMissed:
    FUN_0007db20(mind);
    actorMind::onMessage(&mind->actorMind,msg);
    return;
  case Actor_Bite:
    FUN_0007dc40();
    *(int *)&mind->field_0x150 = *(int *)&mind->field_0x150 + 1;
    actorMind::onMessage(&mind->actorMind,msg);
    return;
  case Actor_BobAttackBegin:
    RegisterAssetEventFromMap__(mind,6);
    actorMind::onMessage(&mind->actorMind,msg);
    return;
  case Actor_DeflectionContact:
    local_34._8_4_ = msg[1].header.msgId;
    local_34.field0_0x0.msgId = Director_PlayerDeflectionContact;
    local_34._14_2_ = 0;
    local_34._12_2_ = *(ushort *)(local_34._8_4_ + Avatar_AddToIgnoreList);
    local_34.field0_0x0.someActor = paVar3;
    EventLoop::NewMessage(&local_34.field0_0x0);
    actorMind::onMessage(&mind->actorMind,msg);
    return;
  case Actor_Dying:
    actorMind::onDying(&mind->actorMind,msg);
    actorMind::onMessage(&mind->actorMind,msg);
    return;
  case Actor_FaintBegin:
    RegisterAssetEventFromMap__(mind,((msg->header).someActor != (actor *)0x0) + 0xc);
    actorMind::onMessage(&mind->actorMind,msg);
    return;
  case Actor_Fright:
    FUN_0007f920();
    actorMind::onMessage(&mind->actorMind,msg);
    return;
  case Actor_GrabAndThrowBegun:
    RegisterAssetEventFromMap__(mind,7);
    actorMind::onMessage(&mind->actorMind,msg);
    return;
  case Actor_GunFired:
    FUN_0007dae0();
    actorMind::onMessage(&mind->actorMind,msg);
    return;
  case Actor_HiddenGhoulyPresence:
    FUN_0007e5c0();
    actorMind::onMessage(&mind->actorMind,msg);
    return;
  case Actor_HitConnected:
    FUN_0007dee0();
    actorMind::onMessage(&mind->actorMind,msg);
    return;
  case Actor_IgnoreInputs:
    mind->processInput = (uint)(msg->header).someActor;
    actorMind::onMessage(&mind->actorMind,msg);
    return;
  case Actor_JumpedOn:
    if ((actor *)msg[1].header.msgId == paVar3) {
      FUN_0007dc80();
      actorMind::onMessage(&mind->actorMind,msg);
      return;
    }
    break;
  case Actor_KnockBackImpact:
    RegisterAssetEventFromMap__(mind,2);
    actorMind::onMessage(&mind->actorMind,msg);
    return;
  case Actor_PickupContact:
    RegisterAssetEventFromMap__(mind,9);
    actorMind::onMessage(&mind->actorMind,msg);
    return;
  case Actor_ProjectileHitConnected:
  case Actor_WeaponHitConnected:
    FUN_0007dee0();
    actorMind::onMessage(&mind->actorMind,msg);
    return;
  case Actor_SmashedBreakables:
    paVar3 = (msg->header).someActor;
    iVar1 = FUN_000357b0();
    if (iVar1 != 0) {
      FUN_0007e470(paVar3);
      actorMind::onMessage(&mind->actorMind,msg);
      return;
    }
    RegisterAssetEventFromMap__(mind,2);
    actorMind::onMessage(&mind->actorMind,msg);
    return;
  case Actor_WithinScareRadius:
    FUN_0007f8c0(msg);
    actorMind::onMessage(&mind->actorMind,msg);
    return;
  case Scene_ActorHit:
    if ((msg->header).someActor == paVar3) {
      FUN_0007dbe0(mind,msg[2].header.someActor,msg[2].header.msgId);
      *(int *)&mind->field_0x150 = *(int *)&mind->field_0x150 + 1;
      fVar8 = (mind->actorMind).targetTimer + 5.0;
      (mind->actorMind).targetTimer = fVar8;
      if (15.0 < fVar8) {
        (mind->actorMind).targetTimer = 15.0;
        actorMind::onMessage(&mind->actorMind,msg);
        return;
      }
    }
    else if ((actor *)msg[1].header.msgId == paVar3) {
      FUN_0007dcc0(mind);
      actorMind::onMessage(&mind->actorMind,msg);
      return;
    }
    break;
  case Scene_ActorHitInvulnerable:
    if ((actor *)msg[1].header.msgId == paVar3) {
      FUN_0007dce0(mind);
      actorMind::onMessage(&mind->actorMind,msg);
      return;
    }
    break;
  case Scene_ActorRecoveredFromStun:
    if ((*(int *)&mind->field_0x88 != 0) &&
       (*(actor **)(*(int *)&mind->field_0x88 + 0x10) == (msg->header).someActor)) {
      FUN_0007dac0();
      actorMind::onMessage(&mind->actorMind,msg);
      return;
    }
    break;
  case Scene_AvatarRemoved:
    FUN_00140a40();
    FUN_00140a40();
    actorMind::onMessage(&mind->actorMind,msg);
    return;
  case Scene_Begin:
    FUN_00136700(mind);
    if (g_finishedLoading_ == 1) {
      CreateSetDroneActionMessage((Actor_SetDroneActionMessage *)&local_34.field_0x10);
      avatar::getWorldPosition(&paVar3->avatar,&local_1c);
      avatar::getWorldRotation(&paVar3->avatar,&local_10);
      local_34._20_4_ = 0x12;
      (*((paVar3->avatar).vtable)->onMessage)(paVar3,&local_34.field_0x10);
      uVar6 = 0;
      uVar5 = 0x3f800000;
      uVar4 = 0;
      uVar3 = 0;
      uVar2 = 0x41200000;
      FUN_0003b1d0(0,paVar3);
      FUN_00061960(uVar2,uVar3,uVar4,uVar5,uVar6);
      actorMind::onMessage(&mind->actorMind,msg);
      return;
    }
    break;
  case Scene_PowerupActivated:
    if ((msg->header).someActor == paVar3) {
      iVar1 = FUN_00123e50();
      RegisterAssetEventFromMap__(mind,(iVar1 != 0) + 0x10);
      actorMind::onMessage(&mind->actorMind,msg);
      return;
    }
    break;
  case Scene_TargetRemoved:
    if (*(actor **)&mind->field_0x88 == (msg->header).someActor) {
      *(undefined4 *)&mind->field_0x88 = 0;
      FUN_0007dac0();
      actorMind::onMessage(&mind->actorMind,msg);
      return;
    }
    break;
  case Scoreboard_HeartBeat:
    iVar5 = GetAmbienceAudio__(paVar3);
    if ((iVar5 != 0) && (iVar1 = FUN_00028ca0(), iVar1 != 0)) {
      paVar4 = paVar3->body;
      iVar1 = FUN_00049d10();
      uVar1 = paVar4->health;
      if (iVar1 == 0) {
        if (uVar1 < 6) {
LAB_0007f6ed:
          RegisterAssetEventFromMap__(mind,10);
          actorMind::onMessage(&mind->actorMind,msg);
          return;
        }
        bVar6 = uVar1 < 10;
        bVar7 = uVar1 == 10;
      }
      else {
        if (uVar1 < 3) goto LAB_0007f6ed;
        bVar6 = uVar1 < 5;
        bVar7 = uVar1 == 5;
      }
      if (bVar6 || bVar7) {
        RegisterAssetEventFromMap__(mind,0xb);
        actorMind::onMessage(&mind->actorMind,msg);
        return;
      }
    }
    break;
  case Weapon_AwaitingPickup:
    FUN_0007f100((msg->header).someActor,msg + 1);
    actorMind::onMessage(&mind->actorMind,msg);
    return;
  case Player_ScareSphereProximity:
    if (msg[1].header.msgId != Null) {
      actorBody::setFlagById
                (paVar3->body,ForceFrostyBreath,(uint)((msg->header).someActor == (actor *)0x0));
    }
  }
  actorMind::onMessage(&mind->actorMind,msg);
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void entityMindPlayer::update(entityMindPlayer *mindPlayer,InputHandlerBase *inputHandler)

{
  BOOL someBool;
  actorBody *body;
  float speed;
  float delta;
  actor *act;
  actor *actt;
  
  act = (mindPlayer->actorMind).actor;
                    // Handle input if the player isn't allowed to move
  if (mindPlayer->processInput != 0) {
    switch(inputHandler->type) {
    case TYPE_1:
                    // Manages accel/decel
      InputHandlerType1::init((InputHandlerType1 *)inputHandler);
      break;
    case TYPE_2:
      InputHandlerType1::init((InputHandlerType1 *)inputHandler);
      break;
    case TYPE_4_NESTED:
      InputHandlerType4::init((InputHandlerType4 *)inputHandler);
      break;
    case TYPE_5:
                    // Process input
      InputHandlerType5::init((InputHandlerType5 *)inputHandler);
    }
  }
  actorMind::updateStateType(&mindPlayer->actorMind);
                    // Movement is not fixed towards camera and can't attack.
                    // Can't fix movement after cutscene.
                    // Doesn't walk automatically during cutscene.
  actorMind::runNextAction(&mindPlayer->actorMind);
  actorMind::updateMemoryTimers(&mindPlayer->actorMind);
  speed = 0.0;
  actt = (mindPlayer->actorMind).actor;
  if (runtime::dx_timer <= 0.0) {
    delta = runtime::DeltaTime * runtime::TimeScale;
  }
  else {
    delta = 0.0;
  }
  if ((actt->avatar).movementFreezeTimer <= 0.0) {
    speed = (actt->avatar).actionSpeed;
  }
  (mindPlayer->actorMind).t = speed * delta + (mindPlayer->actorMind).t;
  actorMind::updateBodyGoal(&mindPlayer->actorMind);
  if ((act->actorType == Human) || ((act->node0x93c).prev != (actor_0x93c)0x0)) {
    someBool = 1;
  }
  else {
    someBool = 0;
  }
  if (((ShouldntDroneBools[someBool] == 0) &&
      (body = (actorBody *)0x0, "\x01"[Game::CheckMoveOn] != '\0')) ||
     (body = act->body, (body->flagSet->flags->flag1 & 0x8000000) != Null)) {
    DisplayHealth(mindPlayer,body);
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void actorBody::walk(actorBody *body,InputHandlerType1 *param_2,entityStateWalk *state)

{
  byte bVar1;
  float10 fwd_mov;
  float10 extraout_ST0;
  float vel_z;
  float floor_scalar;
  float speed;
  vec2 ls;
  float vel_x;
  float ang;
  float theta;
  
  if (((param_2 == (InputHandlerType1 *)0x0) || (body->field13_0x30 != 0)) ||
     (body->someTimer2 != 0.0)) {
    ls.y = 0.0;
    ls.x = 0.0;
  }
  else {
    Input::GetLSMovement_(param_2,&ls);
  }
  fwd_mov = scaled_invsqrt(ls.y * ls.y + ls.x * ls.x);
  speed = (float)fwd_mov;
  if ((float10)1.0 <= fwd_mov) {
    speed = 1.0;
  }
  if ((ls.x == 0.0) && (ls.y == 0.0)) {
    ls.x = 0.0;
  }
  else {
    fwd_mov = atan2(ls.x,ls.y);
    ls.x = (float)fwd_mov;
  }
  if (state->maxMovementMagnitude < speed) {
    speed = state->maxMovementMagnitude;
  }
  if (speed <= 0.0) {
    vel_z = 0.0;
    vel_x = 0.0;
  }
  else {
    (body->rotation).x = 0.0;
    (body->rotation).y = ls.x;
    (body->rotation).z = 0.0;
    ang = ls.x;
    if (*(int *)&state->field_0x20 != 0) {
      applyBodyDirectionToRotation(body);
    }
    if ((state->rotationSpeedCheck_ != 0.0) &&
       (state->field89_0x78 <= speed && speed != state->field89_0x78)) {
      ls.x = (body->actor->avatar).rotEuler.y;
      ang = ls.x;
    }
    body->speed = ls.x;
    if (body->someCount == 0) {
      bVar1 = body->movementIndex;
    }
    else {
      bVar1 = body->fallbackMovementIndex;
    }
                    // If affected by floor
    if ((body->movementFlags & 1 << (bVar1 & 0b00011111)) == 0) {
      floor_scalar = 1.0;
    }
    else {
      floor_scalar = Game::FloorTypeMap[bVar1];
    }
    vel_z = getMovespeed(body);
    theta = ang;
                    // Velocity
    ls.x = vel_z * floor_scalar * speed;
    sin(ang);
    vel_x = (float)(extraout_ST0 * (float10)ls.x);
    fwd_mov = (float10)cos(theta);
    vel_z = (float)(fwd_mov * (float10)ls.x);
  }
  (body->velocity).x = vel_x;
  (body->velocity).y = 0.0;
  (body->velocity).z = vel_z;
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void FUN_000a7880(actorStrategy *param_1)

{
  actor *paVar1;
  actorMind *mind;
  actorBody *paVar2;
  actorStrategy *strategy;
  uint uVar3;
  actorGoalInfo *paVar4;
  int iVar5;
  BOOL BVar6;
  float in_XMM0_Da;
  float fVar7;
  float local_c;
  float local_4;
  
  strategy = param_1;
  paVar1 = param_1->parentActor;
  mind = paVar1->mind;
  paVar2 = paVar1->body;
  param_1 = (actorStrategy *)CONCAT22(param_1._2_2_,param_1->id);
  FUN_0013d400(paVar1);
  actorStrategy::update(strategy);
  FUN_000a7470();
  if ((ShouldntDroneBools[1] == 0) && ("\x01"[Game::CheckMoveOn] != '\0')) {
    if (runtime::dx_timer <= 0.0) {
      in_XMM0_Da = runtime::DeltaTime * runtime::TimeScale;
    }
    else {
      in_XMM0_Da = 0.0;
    }
    fVar7 = 0.0;
    if ((paVar1->avatar).movementFreezeTimer <= 0.0) {
      fVar7 = (paVar1->avatar).actionSpeed;
    }
    if (0.0 < *(float *)&strategy[1].newState_) {
      in_XMM0_Da = *(float *)&strategy[1].newState_ - fVar7 * in_XMM0_Da;
      *(float *)&strategy[1].newState_ = in_XMM0_Da;
      if (in_XMM0_Da <= 0.0) {
        strategy[1].newState_ = 0;
        strategy[1].actorStrategyId = 0;
      }
    }
  }
  fVar7 = 0.0;
  switch((uint)param_1 & 0xffff) {
  case 0x3ea:
    Timer::reduce((float *)&strategy[1].resetState);
    iVar5 = FUN_00139aa0(&param_1,0);
    if (iVar5 != 0) {
      iVar5 = FUN_00134430(0x40060a92,0x42480000);
      if (iVar5 == 0) {
        strategy[1].resetState = 0;
        strategy[1].id = 0;
      }
      if ((*(float *)&strategy[1].resetState == 0.0) && (iVar5 != 0)) {
LAB_000a7b38:
        FUN_000a87e0();
        return;
      }
      if ((mind->actionInfo).next == (actorGoalInfo *)0x0) {
        actorMind::setGoalFromScript(mind,"aloof");
        return;
      }
    }
    break;
  case 0x3eb:
    iVar5 = FUN_00139aa0(&param_1,0);
    if (iVar5 == 0) {
      return;
    }
    if ((mind->actionInfo).next != (actorGoalInfo *)0x0) {
      return;
    }
    FUN_000415a0();
    if (in_XMM0_Da <= 6400.0) {
      strategy[1].parentActor = (actor *)0x1;
      FUN_000a87e0();
      return;
    }
    goto LAB_000a7c8f;
  case 0x3ee:
    iVar5 = FUN_00139aa0(&param_1,0);
    if ((iVar5 != 0) && ((mind->actionInfo).next == (actorGoalInfo *)0x0)) {
      actorStrategy::setStrategy
                (strategy,(-(ushort)(*(int *)&strategy[1].field_0x4 != 0) & 0x24) + Aloof);
      return;
    }
    break;
  case 0x3f4:
    iVar5 = FUN_000a8870();
    paVar2->speedRatio = *(float *)(iVar5 + 4);
    iVar5 = FUN_00139aa0(&param_1,0);
    if (iVar5 == 0) {
      return;
    }
    paVar4 = (actorGoalInfo *)FUN_000a8700();
    goto LAB_000a7c87;
  case 0x401:
    iVar5 = FUN_00139aa0(&param_1,0);
    uVar3 = (uint)param_1;
    if (iVar5 != 0) {
      iVar5 = FUN_000a8700();
      if (iVar5 == 0) {
        strategy->parentActor->skipObjectTypeLookup = 0;
        goto LAB_000a7b38;
      }
      FUN_00041440(uVar3 + 0x20);
      if (local_4 * local_4 + local_c * local_c <= 6400.0) {
        actorStrategy::setStrategy(strategy,Coward);
        return;
      }
    }
    if ((mind->actionInfo).next == (actorGoalInfo *)0x0) {
      actorMind::setGoalFromScript(mind,"far");
      return;
    }
    break;
  case 0x402:
    if ((mind->actionInfo).next == (actorGoalInfo *)0x0) {
      actorStrategy::setStrategy(strategy,*(actorStrategyOffsetId *)&strategy[1].fearCounter);
      return;
    }
    break;
  case 0x405:
    iVar5 = FUN_000a8870();
    paVar2->speedRatio = *(float *)(iVar5 + 8);
    iVar5 = FUN_000beb80();
    if (iVar5 != 0) {
      if ((mind->actionInfo).next != (actorGoalInfo *)0x0) {
        return;
      }
      actorStrategy::setStrategy
                (strategy,(-(ushort)(paVar2->weapon != (weapon *)0x0) & 0xffe9) + Far);
      return;
    }
    goto LAB_000a7cbc;
  case 0x409:
    iVar5 = FUN_00139aa0(&param_1,0);
    if ((((iVar5 != 0) && ((mind->actionInfo).next == (actorGoalInfo *)0x0)) &&
        (BVar6 = GetAmbienceAudio__(paVar1), BVar6 != 0)) &&
       (*(float *)&strategy[1].newState_ == 0.0)) {
      iVar5 = FUN_000beb80();
      if (iVar5 != 0) {
        actorStrategy::setStrategy(strategy,GetWeapon);
        return;
      }
      iVar5 = FUN_000a8700();
      if (iVar5 == 0) {
        FUN_000a8750();
        return;
      }
      actorStrategy::setStrategy(strategy,Coward);
      return;
    }
    break;
  case 0x40e:
    iVar5 = FUN_00139aa0(&param_1,0);
    if (iVar5 == 0) {
      return;
    }
  case 0x3f8:
    paVar4 = (mind->actionInfo).next;
LAB_000a7c87:
    if (paVar4 == (actorGoalInfo *)0x0) {
LAB_000a7c8f:
      FUN_000a8750();
      return;
    }
    break;
  case 0x411:
    if ((mind->actionInfo).next != (actorGoalInfo *)0x0) {
      return;
    }
    BVar6 = GetAmbienceAudio__(paVar1);
    if (BVar6 == 0) {
      return;
    }
    if (*(float *)&strategy[1].newState_ != fVar7) {
      return;
    }
LAB_000a7cbc:
    actorStrategy::setStrategy(strategy,Far);
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void FUN_000a7d30(entityStrategyMummyCursed *param_1,Message *param_2)

{
  ObjMsgID OVar1;
  actor *paVar2;
  Buffer<> *pBVar3;
  BOOL BVar4;
  undefined4 uVar5;
  int iVar6;
  actorDroneActionId *paVar7;
  actorStrategyOffsetId aVar8;
  
  OVar1 = (param_2->header).msgId;
  paVar2 = (param_1->strategy).parentActor;
  if ((0x25 < (int)OVar1) && ((int)OVar1 < 0x28)) {
    aVar8 = (param_1->strategy).id;
    if (aVar8 == KnockedDown) {
      return;
    }
    if (aVar8 == Scared) {
      return;
    }
  }
  actorStrategy::onMessage(&param_1->strategy,param_2);
  switch((param_2->header).msgId) {
  case Avatar_FxCustomRemoved:
    if (*(actor **)(param_1->field2_0x3c + 0x24) == (param_2->header).someActor) {
      param_1->field2_0x3c[0x24] = '\0';
      param_1->field2_0x3c[0x25] = '\0';
      param_1->field2_0x3c[0x26] = '\0';
      param_1->field2_0x3c[0x27] = '\0';
      return;
    }
    break;
  case Actor_Dying:
    entityStrategyMummyCursed::onActorDyingMessage(param_1,(int)param_2);
    return;
  case Actor_ForceIntro:
    actorStrategy::forceIntro(&param_1->strategy,8);
    return;
  case Actor_RequestWeaponDropDistance:
    iVar6 = FUN_000a8870();
    param_2[1].header.msgId = General_Activate;
    param_2[1].header.someActor = *(actor **)(iVar6 + 0xc);
    OVar1 = *(ObjMsgID *)(iVar6 + 0x10);
    param_2[2].header.someActor = (actor *)-1.5707964;
    param_2[2].header.msgId = OVar1;
    param_2[3].header.msgId = Null;
    return;
  case ActorBody_AttachedWeapon:
    param_1->randStruct = (MummyRandStruct *)(param_2->header).someActor;
    return;
  case Scene_ActorHit:
    BVar4 = actorStrategy::checkAndSetDying(&param_1->strategy);
    if (BVar4 != 0) {
      return;
    }
    if (((param_2->header).someActor == paVar2) && ((param_1->strategy).fearCounter == '\0')) {
      paVar2 = (param_1->strategy).parentActor;
      if ((paVar2->actorType == Human) || ((paVar2->node0x93c).prev != (actor_0x93c)0x0)) {
        iVar6 = 1;
      }
      else {
        iVar6 = 0;
      }
      if ((ShouldntDroneBools[iVar6] == 0) && ("\x01"[Game::CheckMoveOn] != '\0')) {
        pBVar3 = paVar2->droneActionsBuf;
        if (pBVar3 != (Buffer<> *)0x0) {
          if (pBVar3->size == pBVar3->endOfQueue) {
            paVar7 = (actorDroneActionId *)0x0;
          }
          else {
            paVar7 = (actorDroneActionId *)
                     ((int)&pBVar3->entries->actionId +
                     (uint)pBVar3->currentDroneAction * (uint)pBVar3->valueSize);
          }
          if (*paVar7 != Null) goto LAB_000a7efa;
        }
        if (param_2[2].header.msgId == Null) {
          iVar6 = FUN_00134620();
          aVar8 = Dizzy;
          if (iVar6 == 0) {
            aVar8 = Angry;
          }
          actorStrategy::setStrategy(&param_1->strategy,aVar8);
        }
        else {
          actorStrategy::setStrategy(&param_1->strategy,KnockedDown);
          if (*(int *)(param_1->field2_0x3c + 0x10) == 0) {
            uVar5 = FUN_0013ff00();
            *(undefined4 *)(param_1->field2_0x3c + 0x10) = uVar5;
            *(float *)(param_1->field2_0x3c + 0xc) = 1.0;
          }
        }
      }
    }
LAB_000a7efa:
    iVar6 = FUN_001408e0();
    if ((iVar6 != 0) && (param_2[2].header.msgId != Null)) {
      param_1->field2_0x3c[0] = '\x01';
      param_1->field2_0x3c[1] = '\0';
      param_1->field2_0x3c[2] = '\0';
      param_1->field2_0x3c[3] = '\0';
      return;
    }
    break;
  case Scene_ActorPickedUpWeapon:
    if ((MummyRandStruct *)param_2[1].header.msgId != param_1->randStruct) {
      return;
    }
    if ((param_2->header).someActor == paVar2) {
      return;
    }
    if ((param_1->strategy).fearCounter == '\0') {
      paVar2 = (param_1->strategy).parentActor;
      if ((paVar2->actorType == Human) || ((paVar2->node0x93c).prev != (actor_0x93c)0x0)) {
        iVar6 = 1;
      }
      else {
        iVar6 = 0;
      }
      if ((ShouldntDroneBools[iVar6] != 0) || ("\x01"[Game::CheckMoveOn] == '\0'))
      goto LAB_000a7fac;
      pBVar3 = paVar2->droneActionsBuf;
      if (pBVar3 != (Buffer<> *)0x0) {
        if (pBVar3->size == pBVar3->endOfQueue) {
          paVar7 = (actorDroneActionId *)0x0;
        }
        else {
          paVar7 = (actorDroneActionId *)
                   ((int)&pBVar3->entries->actionId +
                   (uint)pBVar3->currentDroneAction * (uint)pBVar3->valueSize);
        }
        if (*paVar7 != Null) goto LAB_000a7fac;
      }
    }
    else {
LAB_000a7fac:
      if ((param_1->strategy).id != KnockedDown) {
        return;
      }
    }
    actorStrategy::setStrategy(&param_1->strategy,Scared);
    if ((*(int *)(param_1->field2_0x3c + 0x14) == 0) && (iVar6 = FUN_0013ff00(), iVar6 != 0)) {
      param_1->field2_0x3c[0x14] = '\x01';
      param_1->field2_0x3c[0x15] = '\0';
      param_1->field2_0x3c[0x16] = '\0';
      param_1->field2_0x3c[0x17] = '\0';
      *(float *)(param_1->field2_0x3c + 0xc) = 1.0;
      return;
    }
    break;
  case Scene_AvatarRemoved:
    FUN_00140a40();
    return;
  case Scene_Begin:
    param_1->randStruct = (MummyRandStruct *)paVar2->body->weapon;
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void FUN_000a8cd0(actorStrategy *param_1)

{
  actor *paVar1;
  actorMind *mind;
  int iVar2;
  int iVar3;
  bool bVar4;
  int iVar5;
  BOOL BVar6;
  actorBody *paVar7;
  actor *paVar8;
  float fVar9;
  actorBody *local_c;
  MessageHeader local_8;
  
  paVar1 = param_1->parentActor;
  mind = paVar1->mind;
  paVar7 = paVar1->body;
  local_8.msgId = CONCAT22(local_8.msgId._2_2_,param_1->id);
  local_c = paVar7;
  FUN_0013d400(paVar1);
  actorStrategy::update(param_1);
  FUN_000a88c0();
  if ((ShouldntDroneBools[1] != 0) || ("\x01"[Game::CheckMoveOn] == '\0')) {
    if (runtime::dx_timer <= 0.0) {
      fVar9 = runtime::DeltaTime * runtime::TimeScale;
    }
    else {
      fVar9 = 0.0;
    }
    if ((0.0 < (float)param_1[1].parentActor) &&
       (paVar8 = (actor *)((float)param_1[1].parentActor - fVar9), param_1[1].parentActor = paVar8,
       (float)paVar8 <= 0.0)) {
      param_1[1].parentActor = (actor *)0x0;
    }
  }
  if ((*(int *)&param_1[4].actorStrategyId2 == 0) || (iVar5 = FUN_000a9b50(), iVar5 == 0)) {
    FUN_000a9c90();
  }
  else {
    FUN_000a9be0();
  }
  if ((*(int *)&param_1[4].field_0x20 == 0) || (iVar5 = FUN_000a9ba0(), iVar5 == 0)) {
    if (*(int *)&param_1[4].fearCounter != 0) {
      *(undefined4 *)&param_1[4].fearCounter = 0;
      FUN_0012a3d0((astruct_25 *)&(paVar1->avatar).model0x9s[3].field_0xb0);
    }
  }
  else {
    FUN_000a9cf0();
  }
  iVar5._0_2_ = param_1[4].actorStrategyId3;
  iVar5._2_2_ = param_1[4].actorStrategyId4;
  if (((iVar5 != 0) && (paVar7->actorAllocd != (actorBodyAllocd *)0x0)) &&
     (paVar7->actorAllocd->edb2Buffer != (Buffer<EDB2Entry> *)0x0)) {
    FUN_0013eb60();
    paVar7 = local_c;
  }
  switch(local_8.msgId & 0xffff) {
  case 0x3ee:
    iVar5 = FUN_00139aa0(&local_c,0);
    if (((iVar5 != 0) &&
        ((*(int *)&param_1[1].field_0x24 == 0 || (iVar5 = FUN_000a9ea0(paVar7), iVar5 == 0)))) &&
       ((mind->actionInfo).next == (actorGoalInfo *)0x0)) {
      if (param_1[1].vtable != (actorStrategyVTable *)0x0) {
        actorStrategy::setStrategy(param_1,PostKnockDownCelebrate);
        return;
      }
LAB_000a90d6:
      iVar3._0_2_ = param_1[1].newState_;
      iVar3._2_2_ = param_1[1].actorStrategyId;
      if (iVar3 == 0) {
        actorStrategy::setStrategy(param_1,Near);
        return;
      }
      actorStrategy::setStrategy(param_1,Attack_KnockDown);
      return;
    }
    break;
  case 0x401:
    iVar5 = FUN_00139aa0(&local_c,0);
    if (iVar5 != 0) {
      param_1->parentActor->skipObjectTypeLookup = 0;
      actorStrategy::setStrategy(param_1,Near);
    }
    goto LAB_000a8eb5;
  case 0x404:
    if (*(int *)&param_1[1].field_0x20 != 0) {
      FUN_000a9db0();
    }
    if ((mind->actionInfo).next == (actorGoalInfo *)0x0) {
      if (*(int *)&param_1[1].fearCounter == 0) {
        local_8.msgId = Director_GhoulySignal;
        local_8.someActor = (actor *)(uint)(paVar1->avatar).tag;
        EventLoop::NewMessage(&local_8);
        if (*(int *)&param_1[1].field_0x20 != 0) {
          Cutscene::SetCutsceneCam();
          *(undefined4 *)&param_1[1].field_0x20 = 0;
        }
        *(int *)&param_1[1].fearCounter = *(int *)&param_1[1].fearCounter + 1;
        *(int *)&param_1[1].actorStrategyId3 = *(int *)&param_1[1].actorStrategyId3 + -1;
      }
      if (0x7fffffff < (uint)Cutscene::CurrentCutsceneIndex) goto LAB_000a8f4e;
    }
    break;
  case 0x409:
    iVar5 = FUN_00139aa0(&local_c,0);
    if (((iVar5 != 0) && ((mind->actionInfo).next == (actorGoalInfo *)0x0)) &&
       (BVar6 = GetAmbienceAudio__(paVar1), BVar6 != 0)) {
      iVar5 = FUN_000a9f90();
      if (iVar5 != 0) {
LAB_000a90c2:
        actorStrategy::setStrategy(param_1,Spin);
        return;
      }
      if ((*(int *)&param_1[1].actorStrategyId2 != 0) &&
         (iVar2._0_2_ = param_1[1].actorStrategyId3, iVar2._2_2_ = param_1[1].actorStrategyId4,
         iVar2 != 0)) {
        actorStrategy::setStrategy(param_1,GetHelp);
        return;
      }
LAB_000a8f4e:
      actorStrategy::setStrategy(param_1,Attack_KnockDown);
      return;
    }
    break;
  case 0x40c:
    iVar5 = FUN_00139aa0(&local_c,0);
    if (iVar5 == 0) {
      return;
    }
    if ((*(int *)&param_1[1].field_0x24 != 0) && (iVar5 = FUN_000a9ea0(paVar7), iVar5 != 0)) {
      return;
    }
    FUN_0012b2f0();
    if ((paVar7->health < 0x3d) && (*(int *)&param_1[1].field_0x2c != 0)) {
      bVar4 = true;
    }
    else {
      bVar4 = false;
    }
    iVar5 = FUN_000a9b20();
    if (((*(float *)&param_1[1].resetState == 0.0) || ((bVar4 && (iVar5 == 0)))) &&
       ((!bVar4 || (iVar5 == 0)))) {
      iVar5 = FUN_000a9aa0(paVar7);
      iVar5 = *(int *)(iVar5 + 8);
      param_1[1].newState_ = (short)iVar5;
      param_1[1].actorStrategyId = (short)((uint)iVar5 >> 0x10);
      if (iVar5 != 0) {
        actorStrategy::setStrategy(param_1,Attack_KnockDown);
        return;
      }
    }
LAB_000a8eb5:
    if ((mind->actionInfo).next == (actorGoalInfo *)0x0) {
      actorMind::setGoalFromScript(mind,"far");
      return;
    }
    break;
  case 0x40e:
    iVar5 = FUN_00139aa0(&local_c,0);
    if ((iVar5 != 0) && ((mind->actionInfo).next == (actorGoalInfo *)0x0)) {
      iVar5 = FUN_000a9f90();
      if (iVar5 != 0) goto LAB_000a90c2;
      goto LAB_000a90d6;
    }
    break;
  case 0x414:
    iVar5 = FUN_00139aa0(&local_c,0);
    if (iVar5 != 0) {
      if (*(int *)&param_1[1].field_0x20 != 0) {
        FUN_000a9db0();
      }
      if ((mind->actionInfo).next == (actorGoalInfo *)0x0) {
        if (*(int *)&param_1[1].field_0x20 != 0) {
          Cutscene::SetCutsceneCam();
          *(undefined4 *)&param_1[1].field_0x20 = 0;
        }
        actorStrategy::setStrategy(param_1,Near);
      }
    }
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields

actorBody *

void FUN_000aa050(actorMind *param_1)

{
  actorStrategyOffsetId aVar1;
  actorStrategy *strategy;
  int iVar2;
  
  strategy = (actorStrategy *)param_1;
  aVar1 = ((actorStrategy *)param_1)->id;
  actorStrategy::update((actorStrategy *)param_1);
  if (aVar1 == Far) {
    iVar2 = FUN_00139aa0(&stack0x00000004,0);
    if (((iVar2 != 0) && (iVar2 = FUN_00138410(), iVar2 != 0)) &&
       (iVar2 = FUN_001383a0(), iVar2 != 0)) {
      return;
    }
    if ((*(int *)&strategy[1].field_0x4 == 0) ||
       ((strategy->parentActor->body->flagSet->flags->attackFlags_ & 0x200) == Null)) {
      param_1 = strategy->parentActor->mind;
      if ((param_1->actionInfo).next == (actorGoalInfo *)0x0) {
        actorMind::setGoalFromScript(param_1,"far");
        return;
      }
    }
    else {
      actorStrategy::setStrategy(strategy,Attack_Special);
    }
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void FUN_000aa0f0(actorStrategy *param_1,Message *param_2)

{
  ObjMsgID OVar1;
  actor *av;
  vec3 local_18;
  vec3 local_c;
  
  FUN_001384f0(param_1,param_2);
  OVar1 = (param_2->header).msgId;
  if (OVar1 != Scene_ActorHit) {
    if (OVar1 == Scene_EventComplete) {
      actorStrategy::onEventCompleted(param_1);
      actorStrategy::onMessage(param_1,param_2);
      return;
    }
    if (OVar1 == Scene_EventFailed) {
      actorStrategy::onEventFailed(param_1);
      actorStrategy::onMessage(param_1,param_2);
      return;
    }
    goto LAB_000aa1b8;
  }
  av = (param_2->header).someActor;
  if (av != param_1->parentActor) {
    if ((av->avatar).tag != Actor_Chicken) goto LAB_000aa1b8;
    avatar::getWorldPosition(&param_1->parentActor->avatar,&local_18);
    avatar::getWorldPosition(&av->avatar,&local_c);
    if ((float)(param_1[1].vtable)->getAllocDetails <=
        SQRT((local_18.x - local_c.x) * (local_18.x - local_c.x) +
             (local_18.y - local_c.y) * (local_18.y - local_c.y) +
             (local_18.z - local_c.z) * (local_18.z - local_c.z))) goto LAB_000aa1b8;
  }
  *(undefined4 *)&param_1[1].field_0x4 = 1;
LAB_000aa1b8:
  actorStrategy::onMessage(param_1,param_2);
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void FUN_000ab0c0(actorStrategy *param_1)

{
  actorStrategyOffsetId aVar1;
  actorMind *mind;
  int iVar2;
  
  mind = param_1->parentActor->mind;
  actorStrategy::update(param_1);
  aVar1 = param_1->id;
  if (aVar1 == DroneAction) {
    if (param_1->parentActor->derivedMarkerValue == (DerivedMarkerValue *)0x0) {
      FUN_000ab260();
    }
  }
  else if (aVar1 == Far) {
    iVar2 = FUN_000ab260();
    if (iVar2 != 0) {
      actorStrategy::setStrategy(param_1,Scared);
      FUN_0013d400(param_1->parentActor);
      return;
    }
  }
  else if (aVar1 == Scared) {
    if ((mind->actionInfo).next == (actorGoalInfo *)0x0) {
      actorMind::setGoalFromScript(mind,"scared");
    }
    iVar2 = FUN_000ab260();
    if (iVar2 == 0) {
      actorStrategy::setStrategy(param_1,Far);
      FUN_0013d400(param_1->parentActor);
      return;
    }
  }
  FUN_0013d400(param_1->parentActor);
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void FUN_000ab170(actorStrategy *param_1,Message *param_2)

{
  actorStrategy::onMessage(param_1,param_2);
  if ((param_2->header).msgId == Scene_ActorHit) {
    FUN_000ab2d0(param_1,param_2);
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void FUN_000ab2d0(actorStrategy *param_1,int param_2)

{
  actor *paVar1;
  actor *paVar2;
  Buffer<> *pBVar3;
  actorDroneActionId *paVar4;
  BOOL BVar5;
  int iVar6;
  int iVar7;
  
  paVar1 = param_1->parentActor;
  paVar2 = *(actor **)(param_2 + 4);
  if (((paVar2 != paVar1) && (iVar6 = *(int *)(param_2 + 8), iVar6 != 0)) &&
     (param_1->fearCounter == '\0')) {
    if ((paVar1->actorType == Human) || ((paVar1->node0x93c).prev != (actor_0x93c)0x0)) {
      iVar7 = 1;
    }
    else {
      iVar7 = 0;
    }
    if ((ShouldntDroneBools[iVar7] == 0) && ("\x01"[Game::CheckMoveOn] != '\0')) {
      pBVar3 = paVar1->droneActionsBuf;
      if (pBVar3 != (Buffer<> *)0x0) {
        if (pBVar3->size == pBVar3->endOfQueue) {
          paVar4 = (actorDroneActionId *)0x0;
        }
        else {
          paVar4 = (actorDroneActionId *)
                   ((int)&pBVar3->entries->actionId +
                   (uint)pBVar3->currentDroneAction * (uint)pBVar3->valueSize);
        }
        if (*paVar4 != Null) {
          return;
        }
      }
      if (((*(short *)(iVar6 + 0xcdc) == 2) || (*(int *)(iVar6 + 0x93c) != 0)) &&
         (*(int *)(param_2 + 0x10) != 0)) {
        BVar5 = Random::thresholdCheck(&runtime::rand,0.5);
        if ((BVar5 != 0) || (iVar6 = FUN_00129210(), iVar6 == 0)) {
          actorStrategy::setStrategy(param_1,Celebrate);
          return;
        }
      }
      else if (((paVar2->actorType == Human) || ((paVar2->node0x93c).prev != (actor_0x93c)0x0)) &&
              ((*(int *)(param_2 + 0x10) != 0 &&
               (BVar5 = Random::thresholdCheck(&runtime::rand,0.5), BVar5 != 0)))) {
        actorStrategy::setStrategy(param_1,Worried);
      }
    }
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void FUN_000ac4c0(actorStrategy *param_1,undefined4 param_2)

{
  actor *paVar1;
  actorStrategy *strategy;
  int iVar2;
  float in_XMM0_Da;
  
  strategy = param_1;
  FUN_00139aa0(&param_1,0);
  if (*(int *)&strategy[5].field_0x30 != 0) {
    paVar1 = strategy->parentActor;
    strategy[5].someFloat = (float)(paVar1->avatar).collisionMask;
    strategy[6].vtable = (actorStrategyVTable *)(paVar1->avatar).has0x4CollisionFlag;
    FUN_00136540();
    *(undefined4 *)&strategy[5].field_0x30 = 0;
  }
  if (*(int *)&strategy[5].field_0x2c != 0) {
    FUN_001364b0();
    *(undefined4 *)&strategy[5].field_0x2c = 0;
  }
  iVar2 = FUN_000ac590(param_2);
  if (iVar2 != 0) {
    FUN_000ac610();
    if (0.0 <= in_XMM0_Da) {
      FUN_00122d10();
      iVar2 = FUN_000ac690();
      if (iVar2 != 0) {
        actorStrategy::setStrategy(strategy,Attack_Special);
      }
    }
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void FUN_000aca30(actorStrategy *param_1)

{
  actorStrategyOffsetId aVar1;
  actor *paVar2;
  actorBody *paVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  actorBodyFlags *paVar7;
  undefined1 uVar8;
  
  aVar1 = param_1->id;
  paVar2 = param_1->parentActor;
  paVar3 = paVar2->body;
  uVar8 = (char)paVar3->flagSet->flags->attackFlags_ & DisableDamageFromBlunderbuss;
  if ((uVar8 == Null) ||
     (iVar4._0_2_ = param_1[6].newState_, iVar4._2_2_ = param_1[6].actorStrategyId, iVar4 != 0)) {
    if ((uVar8 == Null) &&
       (iVar5._0_2_ = param_1[6].newState_, iVar5._2_2_ = param_1[6].actorStrategyId, iVar5 != 0)) {
      avatar::destroy(&paVar2->avatar);
      return;
    }
  }
  else {
    param_1[6].newState_ = 1;
    param_1[6].actorStrategyId = 0;
  }
  actorStrategy::update(param_1);
  if (aVar1 == Attack_Special) {
    iVar6._0_2_ = param_1[6].resetState;
    iVar6._2_2_ = param_1[6].id;
    if ((iVar6 == 0) && ((paVar2->body->flagSet->flags->attackFlags_ & 0x2000) != Null)) {
      FUN_000ac820();
    }
  }
  else if ((aVar1 != Attack_Special_End) && (aVar1 == Far)) {
    FUN_000ac4c0(param_1,paVar2);
  }
  paVar7 = paVar3->flagSet->flags;
  *(byte *)((int)&paVar7->attackFlags_ + 3) = *(byte *)((int)&paVar7->attackFlags_ + 3) | 0x10;
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void FUN_000acaf0(actorStrategy *param_1,Message *param_2)

{
  actorStrategy::onMessage(param_1,param_2);
  switch((param_2->header).msgId) {
  case Scene_ActorGrabbedBegin:
    *(undefined4 *)&param_1[1].field_0x4 = 1;
    return;
  case Scene_ActorGrabbedEnd:
    *(undefined4 *)&param_1[1].field_0x4 = 0;
    break;
  case Scene_Begin:
    FUN_000acc40();
    FUN_000acc60();
    return;
  case Scene_PowerupActivated:
    if (param_2[1].header.msgId == Avatar_AnimationEvent) {
      *(int *)&param_1[5].field_0x28 = *(int *)&param_1[5].field_0x28 + 1;
      return;
    }
    break;
  case Scene_PowerupDeactivated:
    if (param_2[1].header.msgId == Avatar_AnimationEvent) {
      *(int *)&param_1[5].field_0x28 = *(int *)&param_1[5].field_0x28 + -1;
      return;
    }
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void __fastcall FUN_000acd40(entityStrategyGrimReaper *param_1)

{
  actor *in_EAX;
  int iVar1;
  entityStrategyGrimReaper *local_4;
  
  local_4 = param_1;
  iVar1 = FUN_00139aa0(&local_4,0);
  if (iVar1 != 0) {
    actorStrategy::canPlayIntro(&param_1->strategy,10);
  }
  if (param_1->field51_0x94 == 0) {
    iVar1 = FUN_000ae0a0();
    if (iVar1 == 0) {
      (*((param_1->strategy).vtable)->leaveState)(&param_1->strategy,(param_1->strategy).id);
      (param_1->strategy).id = Observe;
      actorMind::removeGoals(((param_1->strategy).parentActor)->mind);
      (*((param_1->strategy).vtable)->enterState)(&param_1->strategy,Observe);
      return;
    }
    iVar1 = FUN_000ace20(param_1);
    if (iVar1 != 0) {
      actorStrategy::setStrategy(&param_1->strategy,Near);
      return;
    }
    if ((in_EAX->mind->actionInfo).next == (actorGoalInfo *)0x0) {
      FUN_000adcc0(param_1,in_EAX);
    }
  }
  else if ((in_EAX->mind->actionInfo).next == (actorGoalInfo *)0x0) {
    param_1->field51_0x94 = 0;
    return;
  }
  return;
}




void FUN_000acf10(entityStrategyGrimReaper *grim)

{
  if (grim->field48_0x88 != 1) {
    if (grim->field48_0x88 == 2) {
      entityStrategyGrimReaper::updateFinger_(grim);
    }
    grim->field48_0x88 = 1;
    grim->updatedFloat = grim->reaperStats->resetFloatValue;
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void FUN_000acf40(entityStrategyGrimReaper *grim)

{
  if (grim->field48_0x88 != 0) {
    if (grim->field48_0x88 == 2) {
      entityStrategyGrimReaper::updateFinger_(grim);
    }
    grim->field48_0x88 = 0;
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void __fastcall FUN_000acf70(entityStrategyGrimReaper *param_1)

{
  actorBodyAllocd *paVar1;
  actor *in_EAX;
  int iVar2;
  entityStrategyGrimReaper *local_4;
  
  local_4 = param_1;
  iVar2 = FUN_00139aa0(&local_4,0);
  if (iVar2 != 0) {
    actorStrategy::canPlayIntro(&param_1->strategy,10);
  }
  iVar2 = FUN_000ae0a0();
  if (iVar2 == 0) {
    (*((param_1->strategy).vtable)->leaveState)(&param_1->strategy,(param_1->strategy).id);
    (param_1->strategy).id = Observe;
    actorMind::removeGoals(((param_1->strategy).parentActor)->mind);
    (*((param_1->strategy).vtable)->enterState)(&param_1->strategy,Observe);
    return;
  }
  iVar2 = FUN_000ad2d0(param_1);
  if (iVar2 != 0) {
    (*((param_1->strategy).vtable)->leaveState)(&param_1->strategy,(param_1->strategy).id);
    (param_1->strategy).id = Far;
    actorMind::removeGoals(((param_1->strategy).parentActor)->mind);
    (*((param_1->strategy).vtable)->enterState)(&param_1->strategy,Far);
    return;
  }
  if ((in_EAX->mind->actionInfo).next == (actorGoalInfo *)0x0) {
    FUN_000adcc0(param_1,in_EAX);
  }
  if (param_1->field48_0x88 == 1) {
    iVar2 = FUN_0002b9f0();
    if ((iVar2 != 0) && (param_1->field48_0x88 != 2)) {
      if (param_1->field48_0x88 == 2) {
        entityStrategyGrimReaper::updateFinger_(param_1);
      }
      param_1->field48_0x88 = 2;
      FUN_000ad0d0(param_1);
    }
  }
  else if (((param_1->field48_0x88 == 2) &&
           (paVar1 = in_EAX->body->actorAllocd, paVar1 != (actorBodyAllocd *)0x0)) &&
          (paVar1->edb2Buffer != (Buffer<EDB2Entry> *)0x0)) {
    FUN_0013eb60();
    return;
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void FUN_000adcc0(entityStrategyGrimReaper *grim,actor *act)

{
  float fVar1;
  float fVar2;
  actorMind *mind;
  weapon *pwVar3;
  Model *pMVar4;
  HoldableType HVar5;
  actorMindGoal *paVar6;
  float10 fVar7;
  actorBody *body;
  entityStrategyGrimReaper *grimm;
  
  grimm = grim;
  mind = act->mind;
  body = act->body;
  fVar1 = (body->actor->avatar).scale.z;
  fVar2 = (body->v4).x;
  pwVar3 = body->weapon;
  if (pwVar3 == (weapon *)0x0) {
    HVar5 = Invalid;
  }
  else {
    HVar5 = pwVar3->holdableType;
  }
  if (((HVar5 == None) && (pMVar4 = (pwVar3->avatar).model, pMVar4 != (Model *)0x0)) &&
     (pMVar4->descriptor != (ModelDescriptor *)0x0)) {
    fVar7 = FUN_0003d9a0(&pwVar3->avatar);
    grim = (entityStrategyGrimReaper *)(float)fVar7;
  }
  else {
    grim = (entityStrategyGrimReaper *)0x0;
  }
  paVar6 = actorMind::allocAction(mind,WalkToTarget);
  paVar6[1].t = 30.0;
  paVar6[1].prev = (actorMindGoal *)1.0;
  paVar6[1].next = (actorMindGoal *)1.0;
  *(float *)&paVar6[1].goalId = (float)grim + fVar1 * fVar2;
  paVar6[1].prev = (actorMindGoal *)grimm->optionalVal1;
  paVar6[1].next = (actorMindGoal *)grimm->optionalVal1;
  paVar6[1].t = 0.0;
  fVar1 = grimm->optionalVal2;
  (body->v3).x = grimm->optionalVal2;
  (body->v3).y = fVar1;
  (body->v3).z = 1.0;
  paVar6 = actorMind::allocAction(mind,TurnToFaceTarget);
  paVar6[1].prev = (actorMindGoal *)0x40a00000;
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void FUN_000aea10(actorStrategy *param_1,actorStrategyOffsetId param_2)

{
  actorMind *mind;
  
  param_1->parentActor->body->indexInStatsheet = 2;
  switch(param_2) {
  case Attack_KnockDown:
    param_1->parentActor->body->indexInStatsheet = 5;
    param_1->field_0x1a = 1;
    param_1[1].resetState = 0;
    param_1[1].id = 0;
    FUN_000ae520();
    return;
  case Attack_Special:
    param_1->parentActor->body->indexInStatsheet = 6;
    mind = param_1->parentActor->mind;
    param_1->field_0x1a = 1;
    actorMind::setGoalFromScript(mind,"swingkick");
    return;
  default:
    actorStrategy::enterState(param_1,param_2);
    return;
  case Far:
    *(undefined4 *)&param_1[1].field_0x4 = 0;
    FUN_000ae360();
    return;
  case Sleep:
    FUN_000ae5a0();
    return;
  case Wake:
    actorMind::setGoalFromScript(param_1->parentActor->mind,"wakeup");
    param_1->actorStrategyId2 = Far;
    return;
  }
}




void FUN_000af5a0(actorStrategy *param_1,actorStrategyOffsetId param_2)

{
  actorMind *mind;
  char *pcVar1;
  
  mind = param_1->parentActor->mind;
  param_1->parentActor->body->indexInStatsheet = 2;
  param_1->field_0x1a = 0;
  param_1->field_0x1b = 0;
  switch(param_2) {
  case Attack_KnockBack:
    param_1->parentActor->body->indexInStatsheet = 4;
    param_1->field_0x1a = 1;
    actorMind::setGoalFromScript(mind,"attack");
    param_1[1].actorStrategyId3 = 0;
    param_1[1].actorStrategyId4 = 0;
    param_1[1].resetState = 0;
    param_1[1].id = 0;
    param_1[1].newState_ = 0;
    param_1[1].actorStrategyId = 0;
    return;
  default:
    actorStrategy::enterState(param_1,param_2);
    return;
  case Near:
    param_1->field_0x1a = 1;
    param_1->parentActor->body->indexInStatsheet = 3;
    return;
  case Sleep:
    pcVar1 = "sleep_wall";
    if (param_1[1].vtable == (actorStrategyVTable *)0x0) {
      pcVar1 = "sleep";
    }
    break;
  case Wait:
    FUN_000af870(0,param_1);
    return;
  case Wake:
    pcVar1 = "wakeup_wall";
    if (param_1[1].vtable == (actorStrategyVTable *)0x0) {
      pcVar1 = "wakeup";
    }
    actorMind::setGoalFromScript(mind,pcVar1);
    FUN_000af870(0,param_1);
    return;
  }
  actorMind::setGoalFromScript(mind,pcVar1);
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void FUN_000b3220(actorStrategy *param_1)

{
  actorStrategy *strategy;
  int in_EAX;
  int iVar1;
  
  strategy = param_1;
  iVar1 = FUN_00139aa0(&param_1,0);
  if (iVar1 != 0) {
    iVar1 = *(int *)&strategy[3].field_0x28;
    if (iVar1 == 1) {
      if ((*(byte *)(*(int *)(*(int *)(*(int *)(in_EAX + 0x95c) + 0x15c) + 8) + 6) & 1) != 0) {
        *(undefined4 *)&strategy[3].field_0x28 = 2;
        return;
      }
    }
    else if (iVar1 == 2) {
      iVar1 = FUN_000b3300();
      if ((iVar1 != 0) && (*(int *)&strategy[3].field_0x28 != 3)) {
        *(undefined4 *)&strategy[3].field_0x28 = 3;
        FUN_00108fc0();
      }
    }
    else if ((iVar1 == 3) &&
            ((iVar1 = *(int *)(*(int *)(*(int *)(in_EAX + 0x95c) + 0x15c) + 8),
             (*(byte *)(iVar1 + 4) & 1) != 0 || ((*(byte *)(iVar1 + 6) & 1) != 0)))) {
      actorStrategy::setStrategy(strategy,Far);
      return;
    }
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void __fastcall FUN_000b3780(int param_1,actorStrategy *param_2)

{
  actorStrategyStateChangeCallback *paVar1;
  void *pvVar2;
  actor *paVar3;
  actorMind *mind;
  actorBody *body;
  actorStrategyVTable *paVar4;
  AttackEntry *pAVar5;
  Object *pOVar6;
  uint uVar7;
  actorBody *body_00;
  
  if (*(int *)&param_2[3].field_0x2c != param_1) {
    paVar3 = param_2->parentActor;
    *(int *)&param_2[3].field_0x2c = param_1;
    mind = paVar3->mind;
    body = mind->actor->body;
    switch(param_1) {
    case 1:
      paVar3->skipObjectTypeLookup = 0;
      actorMind::setGoalFromScript(mind,"specialattackprepare");
      param_2[4].vtable = (actorStrategyVTable *)0x0;
      actorBody::disableFlagByIndex(0x2b,body);
      return;
    case 3:
      actorMind::setGoalFromScript(mind,"specialattackprepare2");
      FUN_0001f800();
      pAVar5 = AttackDataResource::getAttackByStateId
                         ((AttackDataResource *)body->attackDataRes,SpinAttack);
      body->currentAttackEntry = pAVar5;
      *(undefined4 *)&body->useAttackParam3 = 0;
      body->field_0x6a = body->field_0x6a + '\x01';
      FUN_0001d760();
      body->setStateSuccessfully = 1;
      actorBody::resetFlags(body_00);
      pOVar6 = CreateFxFromAID((astruct_38 *)mind->actor,&param_2[1].field_0x4);
      *(Object **)&param_2[4].field_0x4 = pOVar6;
      pvVar2 = param_2[1].vtable[1].update;
      paVar1 = param_2[1].vtable[1].enterState;
      runtime::rand = runtime::rand * 0x19660d + 0x3c6ef35f;
      uVar7 = runtime::rand & 0x7fffff;
      param_2->field_0x1a = 1;
      param_2[4].vtable = (actorStrategyVTable *)0x1;
      *(float *)&param_2[3].field_0x30 =
           ((float)paVar1 - (float)pvVar2) * ((float)(uVar7 | 0x3f800000) - 1.0) + (float)pvVar2;
      param_2[3].someFloat = body->airResistance;
      return;
    case 4:
      actorMind::setGoalFromScript(mind,"specialattack");
      paVar1 = param_2[1].vtable[1].leaveState;
      runtime::rand = runtime::rand * 0x19660d + 0x3c6ef35f;
      paVar4 = param_2[1].vtable;
      *(float *)&param_2[3].field_0x30 =
           ((float)param_2[1].vtable[2].getAllocDetails - (float)paVar1) *
           ((float)(runtime::rand & 0x7fffff | 0x3f800000) - 1.0) + (float)paVar1;
      body->airResistance = (float)paVar4[2].ctor;
      return;
    case 5:
      pvVar2 = param_2[1].vtable[2].dtor;
      runtime::rand = runtime::rand * 0x19660d + 0x3c6ef35f;
      *(float *)&param_2[3].field_0x30 =
           ((float)param_2[1].vtable[2].onMessage - (float)pvVar2) *
           ((float)(runtime::rand & 0x7fffff | 0x3f800000) - 1.0) + (float)pvVar2;
      return;
    case 6:
      actorMind::removeGoals(mind);
      actorMind::setGoalFromScript(mind,"specialattackfinish");
      FUN_000b39d0();
    case 2:
    }
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void FUN_000b4af0(entityStrategyImp *param_1,int param_2,int param_3)

{
  actor *paVar1;
  int iVar2;
  float fVar3;
  float fVar4;
  
  paVar1 = (param_1->actorStrategy).parentActor;
  if (runtime::dx_timer <= 0.0) {
    fVar3 = runtime::DeltaTime * runtime::TimeScale;
  }
  else {
    fVar3 = 0.0;
  }
  fVar4 = 0.0;
  if ((paVar1->avatar).movementFreezeTimer <= 0.0) {
    fVar4 = (paVar1->avatar).actionSpeed;
  }
  if ((0.0 < param_1->field1_0x38) &&
     (fVar3 = param_1->field1_0x38 - fVar4 * fVar3, param_1->field1_0x38 = fVar3, fVar3 <= 0.0)) {
    param_1->field1_0x38 = 0.0;
  }
  if (((param_1->field1_0x38 != 0.0) && (*(int *)(param_3 + 0x58) != 0)) &&
     (iVar2 = FUN_00112a70(&(param_1->actorStrategy).field_0x20), iVar2 != 0)) {
    return;
  }
  fVar3 = param_1->behaviourAttribs->field11_0x2c;
  runtime::rand = runtime::rand * 0x19660d + 0x3c6ef35f;
  *(float *)(*(int *)(param_2 + 0x95c) + 0x70) =
       (param_1->behaviourAttribs->field12_0x30 - fVar3) *
       ((float)(runtime::rand & 0x7fffff | 0x3f800000) - 1.0) + fVar3;
  (*((param_1->actorStrategy).vtable)->leaveState)
            (&param_1->actorStrategy,(param_1->actorStrategy).id);
  (param_1->actorStrategy).id = Near;
  actorMind::removeGoals(((param_1->actorStrategy).parentActor)->mind);
  (*((param_1->actorStrategy).vtable)->enterState)(&param_1->actorStrategy,Near);
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void __fastcall FUN_000b4df0(int param_1,actorStrategy *param_2)

{
  actorBody *paVar1;
  actorStrategyOffsetId aVar2;
  actorMind *in_EAX;
  int iVar3;
  int local_4;
  
  local_4 = param_1;
  iVar3 = FUN_00139aa0(&local_4,0);
  if (iVar3 == 0) {
    aVar2 = FUN_000b4da0();
    (*param_2->vtable->leaveState)(param_2,param_2->id);
    param_2->id = aVar2;
    actorMind::removeGoals(param_2->parentActor->mind);
    (*param_2->vtable->enterState)(param_2,aVar2);
    return;
  }
  paVar1 = param_2->parentActor->body;
  if (((paVar1->field13_0x30 == 0) && (paVar1->someTimer2 == 0.0)) &&
     ((param_2->parentActor->mind->actionInfo).next == (actorGoalInfo *)0x0)) {
    if ((*(int *)(param_1 + 0x958) != 0) && (*(int *)(*(int *)(param_1 + 0x958) + 0x10) != 0)) {
      iVar3 = FUN_000b4330(&param_2[1].parentActor);
      if (iVar3 != 0) {
        iVar3._0_2_ = param_2[1].newState_;
        iVar3._2_2_ = param_2[1].actorStrategyId;
        if (iVar3 != 0) {
          actorMind::setGoalFromScript(in_EAX,"jumpbite");
          return;
        }
        param_2->field_0x1a = 1;
        actorMind::setGoalFromScript(in_EAX,"jumpbiteprepare");
        return;
      }
    }
    aVar2 = FUN_000b4da0();
    actorStrategy::setStrategy(param_2,aVar2);
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void __fastcall FUN_000b4f50(actorStrategy *param_1)

{
  actor *paVar1;
  int iVar2;
  int in_EAX;
  int iVar3;
  
  if (in_EAX != 0) {
    paVar1 = param_1->parentActor;
    iVar2 = *(int *)(in_EAX + 0x95c);
    iVar3 = FUN_000b4ef0();
    if ((((iVar3 != 0) && (*(int *)(iVar2 + 0x50) == 0)) &&
        ((*(byte *)(*(int *)(*(int *)(iVar2 + 0x15c) + 8) + 3) & 8) == 0)) &&
       (*(int *)(iVar2 + 0x58) != 0)) {
      *(actor **)(iVar2 + 0x50) = paVar1;
      *(int *)&param_1[1].field_0x4 = iVar2;
      actorStrategy::setStrategy(param_1,Mutated);
      return;
    }
    (*param_1->vtable->leaveState)(param_1,param_1->id);
    param_1->id = Attack_KnockDown;
    actorMind::removeGoals(param_1->parentActor->mind);
    (*param_1->vtable->enterState)(param_1,Attack_KnockDown);
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void __fastcall FUN_000b5b30(actorStrategy *param_1)

{
  actorMind *mind;
  int in_EAX;
  int iVar1;
  actorStrategy *local_4;
  
  local_4 = param_1;
  iVar1 = FUN_00139aa0(&local_4,0);
  if (((iVar1 == 0) || (iVar1 = FUN_00138410(), iVar1 == 0)) || (iVar1 = FUN_001383a0(), iVar1 == 0)
     ) {
    mind = *(actorMind **)(in_EAX + 0x958);
    iVar1 = FUN_000b5cf0();
    if (iVar1 != 0) {
      param_1->parentActor->skipObjectTypeLookup = 0;
      iVar1 = FUN_000196f0();
      if (iVar1 == 0) {
        actorStrategy::setStrategy(param_1,Attack_KnockBack);
        return;
      }
      actorStrategy::setStrategy(param_1,Attack_Special);
      return;
    }
    iVar1 = FUN_000babf0(param_1);
    if (iVar1 != 0) {
      param_1->parentActor->body->indexInStatsheet = 3;
      actorMind::removeGoals(mind);
      actorMind::setGoalFromScript(mind,"evade");
      return;
    }
    if ((mind->actionInfo).next == (actorGoalInfo *)0x0) {
      iVar1 = FUN_000b5c50(param_1);
      if (iVar1 != 0) {
        param_1->parentActor->body->indexInStatsheet = 3;
        FUN_000b6630(param_1,0);
        return;
      }
      param_1->parentActor->body->indexInStatsheet = 2;
      FUN_000b6630(param_1,1);
    }
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void __fastcall FUN_000b5d70(actorStrategy *param_1)

{
  int iVar1;
  int in_EAX;
  int iVar2;
  actorStrategy *local_4;
  
  iVar1 = *(int *)(in_EAX + 0x958);
  local_4 = param_1;
  iVar2 = FUN_00139aa0(&local_4,0);
  if (iVar2 != 0) {
    iVar2 = FUN_0002b910();
    if (iVar2 == 0) {
      (*param_1->vtable->leaveState)(param_1,param_1->id);
      param_1->id = Far;
      actorMind::removeGoals(param_1->parentActor->mind);
      (*param_1->vtable->enterState)(param_1,Far);
    }
    if (param_1[4].parentActor == (actor *)0x1) {
      if (*(int *)(iVar1 + 0x58) == 0) {
        FUN_000b5e20();
      }
    }
    else if ((param_1[4].parentActor == (actor *)0x2) && (*(int *)(iVar1 + 0x58) == 0)) {
      actorStrategy::setStrategy(param_1,Far);
      return;
    }
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void FUN_000b81b0(actor *param_1,actorStrategy *param_2)

{
  actorMind *mind;
  int iVar1;
  float fVar2;
  float fVar3;
  
  mind = param_1->mind;
  if ((mind != (actorMind *)0x0) && (mind->targetBody != (actorBody *)0x0)) {
    actorStrategy::canPlayIntro(param_1->strategy,0x14);
  }
  if (runtime::dx_timer <= 0.0) {
    fVar2 = runtime::DeltaTime * runtime::TimeScale;
  }
  else {
    fVar2 = 0.0;
  }
  fVar3 = 0.0;
  if ((param_2->parentActor->avatar).movementFreezeTimer <= 0.0) {
    fVar3 = (param_2->parentActor->avatar).actionSpeed;
  }
  if ((0.0 < *(float *)&param_2[1].resetState) &&
     (fVar2 = *(float *)&param_2[1].resetState - fVar3 * fVar2,
     *(float *)&param_2[1].resetState = fVar2, fVar2 <= 0.0)) {
    param_2[1].resetState = 0;
    param_2[1].id = 0;
  }
  iVar1 = FUN_000b87f0(param_2);
  if (iVar1 != 0) {
    FUN_000b86e0();
    return;
  }
  if ((mind->actionInfo).next == (actorGoalInfo *)0x0) {
    actorMind::setGoalFromScript(mind,"angryrandomwalk");
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void FUN_000b90d0(actorStrategy *param_1)

{
  int iVar1;
  actorStrategyOffsetId aVar2;
  undefined1 local_4 [4];
  
  if ((*(int *)&param_1[3].field_0x30 != 0) && (iVar1 = FUN_00139aa0(local_4,0), iVar1 == 0)) {
    return;
  }
  if ((param_1[4].vtable == (actorStrategyVTable *)0x2) && (iVar1 = FUN_000b9160(), iVar1 != 0)) {
    aVar2 = Celebrate;
    if (*(int *)&param_1[3].field_0x2c == 0) {
      aVar2 = Far;
    }
    actorStrategy::setStrategy(param_1,aVar2);
  }
  return;
}




void FUN_000b9a20(actorStrategy *param_1,actorStrategyOffsetId param_2)

{
  param_1->parentActor->body->indexInStatsheet = 2;
  switch(param_2) {
  case Attack_KnockBack:
    FUN_000b88f0();
    return;
  case Attack_KnockDown:
    FUN_000b8b90();
    return;
  case Attack_Special:
    FUN_000b8f30();
    return;
  default:
    actorStrategy::enterState(param_1,param_2);
    return;
  case Far:
    *(getAllocDetailsFn **)&param_1[1].resetState = (param_1[1].vtable)->getAllocDetails;
    return;
  case ForceAngry:
    FUN_000b88a0();
    return;
  }
}




void __fastcall FUN_000bb090(actorStrategy *param_1)

{
  actor *paVar1;
  actorMind *mind;
  float in_EAX;
  int iVar2;
  
  if ((param_1[6].someFloat != in_EAX) && (param_1[6].someFloat = in_EAX, in_EAX == 2.8026e-45)) {
    paVar1 = param_1->parentActor;
    mind = paVar1->mind;
    iVar2 = FUN_000bb100();
    if (iVar2 != 0) {
      if ((paVar1->mind != (actorMind *)0x0) && (paVar1->mind->targetBody != (actorBody *)0x0)) {
        paVar1->strategy->parentActor->skipObjectTypeLookup = 0;
      }
      actorMind::setGoalFromScript(mind,"attack");
      return;
    }
    actorStrategy::setStrategy(param_1,Attack_Special);
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void __thiscall FUN_000bbab0(int param_1,actorMind *param_2)

{
  float fVar1;
  avatar *av;
  int in_EAX;
  BOOL BVar2;
  actorMindGoal *paVar3;
  float fVar4;
  vec3 local_c;
  
  av = *(avatar **)(in_EAX + 8);
  fVar4 = av[1].rotQuat.z;
  fVar1 = *(float *)(param_1 + 0x38);
  avatar::getWorldPosition(av,&local_c);
  fVar4 = *(float *)(*(int *)((int)fVar4 + 8) + 0x38) * *(float *)((int)fVar4 + 0x888);
  BVar2 = SpawnThingFromMarker
                    (&local_c,0,param_1 + 0x20,(uint)*(byte *)(param_1 + 0x19),fVar4 + fVar1,
                     fVar4 * 2.0 + fVar1,0,*(undefined4 *)(av[1].model0x9s[0].audioID + 0x2c),
                     (uint)av->tag,0xc);
  if ((BVar2 == 0) &&
     (BVar2 = SpawnThingFromMarker
                        (&local_c,0,param_1 + 0x20,(uint)*(byte *)(param_1 + 0x19),fVar4 + fVar1,
                         fVar4 * 6.0 + fVar1,0,*(undefined4 *)(av[1].model0x9s[0].audioID + 0x2c),
                         (uint)av->tag,0xc), BVar2 == 0)) {
    return;
  }
  actorMind::removeGoals(param_2);
  paVar3 = actorMind::allocAction(param_2,WalkToPoint);
  paVar3[1].t = 1.0;
  paVar3[2].prev = (actorMindGoal *)1.0;
  *(float *)&paVar3[2].goalId = 30.0;
  paVar3[1].prev = (actorMindGoal *)local_c.x;
  paVar3[1].next = (actorMindGoal *)local_c.y;
  *(float *)&paVar3[1].goalId = local_c.z;
  paVar3[2].goalId = Null;
  paVar3[2].initialised = false;
  paVar3[2].field4_0xb = '\0';
  return;
}




float mummy::getSomeRandomValue(MummyRandStruct *param_1)

{
  runtime::rand = runtime::rand * 0x19660d + 0x3c6ef35f;
  return (param_1->randEnd - param_1->randStart) *
         ((float)(runtime::rand & 0x7fffff | 0x3f800000) - 1.0) + param_1->randStart;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void FUN_000bc770(entityStrategyMummyCursed *strategy,actor *mummyActor)

{
  int *piVar1;
  undefined4 *puVar2;
  int iVar3;
  undefined4 local_8;
  undefined4 local_4;
  
  iVar3 = 0;
  if (*(int *)&strategy->field_0x190 != 0) {
    *(undefined4 *)&strategy->field_0x190 = 0;
  }
  if ((DAT_00545a18 != 0) && (PTR_00545a20 == mummyActor)) {
    FUN_0012e6c0();
  }
  piVar1 = *(int **)&strategy->field_0x29c;
  if (piVar1 != (int *)0x0) {
    local_4 = 0;
    local_8 = 5;
    (**(code **)(*piVar1 + 0xc))(piVar1,&local_8);
    *(undefined4 *)&strategy->field_0x29c = 0;
  }
  piVar1 = *(int **)&strategy->field_0x2a0;
  if (piVar1 != (int *)0x0) {
    local_4 = 0;
    local_8 = 5;
    (**(code **)(*piVar1 + 0xc))(piVar1,&local_8);
    *(undefined4 *)&strategy->field_0x2a0 = 0;
  }
  if (0 < *(int *)&strategy->field_0x2a4) {
    puVar2 = (undefined4 *)&strategy->field_0x2a8;
    do {
      FUN_0003cfd0((short)*puVar2,mummyActor);
      iVar3 = iVar3 + 1;
      puVar2 = puVar2 + 1;
    } while (iVar3 < *(int *)&strategy->field_0x2a4);
  }
  iVar3 = 0;
  *(undefined4 *)&strategy->field_0x2a4 = 0;
  if (*(int *)&strategy->field_0x2c8 < 1) {
    *(undefined4 *)&strategy->field_0x2c8 = 0;
    return;
  }
  puVar2 = (undefined4 *)&strategy->field_0x2cc;
  do {
    FUN_0003cfd0((short)*puVar2,mummyActor);
    iVar3 = iVar3 + 1;
    puVar2 = puVar2 + 1;
  } while (iVar3 < *(int *)&strategy->field_0x2c8);
  *(undefined4 *)&strategy->field_0x2c8 = 0;
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields

void entityStrategyMummyCursed::onProjectileHit
               (entityStrategyMummyCursed *param_1,actor *mummyActor)

{
  if (DAT_00545a18 == 0) {
    FUN_000bc910(2,param_1);
    return;
  }
  FUN_000bc770(param_1,mummyActor);
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void FUN_000bc8a0(entityStrategyMummyCursed *strategy,actor *param_2)

{
  int iVar1;
  
  if ((param_2->actorType == Human) || ((param_2->node0x93c).prev != (actor_0x93c)0x0)) {
    iVar1 = 1;
  }
  else {
    iVar1 = 0;
  }
  if ((((ShouldntDroneBools[iVar1] == 0) && ("\x01"[Game::CheckMoveOn] != '\0')) &&
      (strategy->curseTarget != (actor *)0x0)) &&
     ((param_2->body->flagSet->flags->flag1 & AttackFinished) != Null)) {
    FUN_000bc910(1,strategy);
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void FUN_000bc910(int param_1,entityStrategyMummyCursed *strategy)

{
  CalloutDescriptor **ppCVar1;
  actor *paVar2;
  actorBody *paVar3;
  actorBodyFlags *paVar4;
  objParams *poVar5;
  obj *poVar6;
  BOOL BVar7;
  BoneAffineSubresourceEntry *subres;
  Skeleton *skeleton;
  
  if (param_1 != *(int *)&strategy->field_0x190) {
    *(int *)&strategy->field_0x190 = param_1;
    if (param_1 == 1) {
      paVar2 = (strategy->strategy).parentActor;
      FUN_000bcaa0();
      FUN_0013b810((int)&strategy->field_0x2a4,paVar2);
      ppCVar1 = &(paVar2->avatar).callout;
      if (ppCVar1 != (CalloutDescriptor **)0x0) {
        actor::executeCalloutInDescriptor
                  (*ppCVar1,MummyCursedDeathCurseChantEnd,CalloutCallback1,0,paVar2,
                   (entityBodyPlayer_0x924)&strategy->field_0x2c8);
      }
      if ((strategy->randStruct[1].distanceToEvade == 0.0) &&
         (BVar7 = FUN_00052f80(0x10,(ModelFooterEntry *)((paVar2->avatar).model)->descriptor),
         BVar7 != 0)) {
        FUN_00040d50(paVar2,0x10);
        poVar5 = Assets::GetObjParams(strategy->someAid);
        subres = actor::getModelBoneAffineByBone1(paVar2,4);
        FUN_00040a60(subres);
        actor::getEulers(&poVar5[2].typeIndex,skeleton,paVar2,subres);
        poVar6 = Assets::CreateEntityFromParams(poVar5);
        *(obj **)&strategy->field_0x298 = poVar6;
        free(poVar5);
        FUN_0013b1f0(*(undefined4 *)&strategy->field_0x298,0xbf800000);
        avatar::destroy(*(avatar **)&strategy->field_0x298);
      }
    }
    else if (param_1 == 2) {
      paVar2 = (strategy->strategy).parentActor;
      paVar3 = paVar2->body;
      poVar5 = Assets::GetObjParams(strategy->field2_0x3c);
      poVar6 = (obj *)0x0;
      if (poVar5 != (objParams *)0x0) {
        *(actor **)(poVar5 + 1) = paVar2;
        poVar6 = Assets::CreateEntityFromParams(poVar5);
        free(poVar5);
      }
      *(obj **)&strategy->field_0x29c = poVar6;
      FUN_0012e5e0(strategy->randStruct[1].field1_0x4);
      dispatchFrightMessageToAvatar(paVar2);
      paVar4 = paVar3->flagSet->flags;
      *(undefined1 *)&paVar4->flag1 = (char)paVar4->flag1 | IsGettingBackUp;
      return;
    }
  }
  return;
}




void FUN_000bce80(entityStrategyMummyCursed *strategy)

{
  actor *act;
  float fVar1;
  int iVar2;
  actor *paVar3;
  undefined4 *puVar4;
  int iVar5;
  
  iVar5 = *(int *)&strategy->field_0x144;
  act = (strategy->strategy).parentActor;
  if (iVar5 != 0) {
    if (iVar5 == 2) {
      if (*(int *)&strategy->field_0x17c == 0) {
        FUN_0013b7e0(act,(entityBodyPlayer_0x924)&strategy->field_0x158,MummyCursedSlabWhack);
        *(undefined4 *)&strategy->field_0x17c = 1;
      }
    }
    else if (iVar5 == 4) {
      FUN_000bd650();
      FUN_0013b810((int)&strategy->field_0x158,act);
      *(undefined4 *)&strategy->field_0x17c = 0;
    }
    else if (iVar5 == 5) {
      *(undefined4 *)&strategy->field_0x154 = 0;
    }
    *(undefined4 *)&strategy->field_0x144 = 0;
  }
  iVar5 = 0;
  if ((strategy->otherAvatar != (avatar *)0x0) &&
     (fVar1 = strategy->otherAvatar[1].rotQuat.z, fVar1 != 0.0)) {
    iVar2 = *(int *)(*(int *)((int)fVar1 + 0x15c) + 8);
    *(byte *)(iVar2 + 7) = *(byte *)(iVar2 + 7) & 0xdf;
  }
  *(undefined4 *)&strategy->field_0x154 = 0;
  if (*(int *)&strategy->field_0x184 != 0) {
    iVar2 = *(int *)(*(int *)&strategy->field_0x184 + 0x95c);
    paVar3 = *(actor **)(iVar2 + 0x718);
    if ((paVar3 != (actor *)0x0) && (paVar3 == act)) {
      *(undefined4 *)(iVar2 + 0x718) = 0;
      *(undefined4 *)&strategy->field_0x180 = 0;
      *(undefined4 *)&strategy->field_0x184 = 0;
    }
  }
  FUN_00112a20();
  (strategy->strategy).field_0x1a = 0;
  if (0 < *(int *)&strategy->field_0x158) {
    puVar4 = (undefined4 *)&strategy->field_0x15c;
    do {
      FUN_0003cfd0((short)*puVar4,act);
      iVar5 = iVar5 + 1;
      puVar4 = puVar4 + 1;
    } while (iVar5 < *(int *)&strategy->field_0x158);
    *(undefined4 *)&strategy->field_0x158 = 0;
    *(undefined4 *)&strategy->field_0x17c = 0;
    return;
  }
  *(undefined4 *)&strategy->field_0x158 = 0;
  *(undefined4 *)&strategy->field_0x17c = 0;
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void FUN_000bcfb0(entityStrategyMummyCursed *strategy,actor *mummyActor)

{
  actor *paVar1;
  float fVar2;
  int iVar3;
  BOOL BVar4;
  float10 extraout_ST0;
  float10 dist;
  float10 whack_range;
  float fVar5;
  vec3 local_c;
  actorMind *mummy_mind;
  float other_body;
  
  mummy_mind = mummyActor->mind;
  avatar::distanceBetweenAvatars(mummyActor,strategy->otherAvatar);
  FUN_0013b840();
  iVar3 = FUN_000bd750();
  if (iVar3 != 0) {
    other_body = strategy->otherAvatar[1].rotQuat.z;
    local_c.x = *(float *)((int)other_body + 0x18);
    local_c.z = *(float *)((int)other_body + 0x20);
    fVar5 = *(float *)((int)other_body + 0x1c);
    fVar2 = -strategy->randStruct->field10_0x28;
    local_c.y = fVar5;
    FUN_00041900(mummyActor);
    sin(fVar5);
    local_c.x = (float)(extraout_ST0 * (float10)fVar2 + (float10)local_c.x);
    dist = (float10)cos(fVar5);
    *(float *)((int)other_body + 0x18) = local_c.x;
    *(float *)((int)other_body + 0x1c) = local_c.y;
    *(float *)((int)other_body + 0x20) = (float)(dist * (float10)fVar2 + (float10)local_c.z);
  }
  iVar3 = *(int *)&strategy->field_0x144;
  switch(iVar3) {
  case 1:
    if ((mummy_mind->actionInfo).next == (actorGoalInfo *)0x0) {
      FUN_000bd450(strategy,2);
      return;
    }
    break;
  case 2:
    FUN_001345b0();
    if ((mummy_mind->actionInfo).next == (actorGoalInfo *)0x0) {
      FUN_000bd450(strategy,3);
    }
    if ((*(int *)&strategy->field_0x17c == 0) &&
       (BVar4 = actorBody::flagIsSet(mummyActor->body,IsCursing), BVar4 != 0)) {
      FUN_0013b7e0(mummyActor,(entityBodyPlayer_0x924)&strategy->field_0x158,MummyCursedSlabWhack);
      *(undefined4 *)&strategy->field_0x17c = 1;
      return;
    }
    break;
  case 3:
    FUN_001345b0();
    iVar3 = FUN_0002b9f0();
    if (iVar3 != 0) {
      FUN_000bd450(strategy,4);
      return;
    }
    break;
  case 4:
                    // Process whack
    whack_range = avatar::distanceBetweenAvatars(mummyActor,strategy->otherAvatar);
    avatar::getWorldPosition(strategy->otherAvatar,&local_c);
    FUN_001345b0();
    if ((float)whack_range < strategy->randStruct->whackRange) {
      FUN_000bd450(strategy,5);
      return;
    }
    iVar3 = FUN_000bd680(&local_c,(float)whack_range);
    if ((iVar3 != 0) && (iVar3 = *(int *)&strategy->field_0x144, iVar3 != 6)) {
      paVar1 = (strategy->strategy).parentActor;
      mummy_mind = paVar1->mind;
      if (iVar3 == 2) {
        if (*(int *)&strategy->field_0x17c == 0) {
          FUN_0013b7e0(paVar1,(entityBodyPlayer_0x924)&strategy->field_0x158,MummyCursedSlabWhack);
          *(undefined4 *)&strategy->field_0x17c = 1;
        }
      }
      else if (iVar3 == 4) {
        FUN_000bd650();
        FUN_0013b810((int)&strategy->field_0x158,paVar1);
        *(undefined4 *)&strategy->field_0x17c = 0;
      }
      else if (iVar3 == 5) {
        *(undefined4 *)&strategy->field_0x154 = 0;
      }
      *(undefined4 *)&strategy->field_0x144 = 6;
      *(undefined4 *)&strategy->field_0x150 = 0;
      actorMind::setGoalFromScript(mummy_mind,"scared");
      return;
    }
    break;
  case 5:
  case 7:
    if ((mummy_mind->actionInfo).next != (actorGoalInfo *)0x0) {
      return;
    }
    goto LAB_000bd28f;
  case 6:
    fVar5 = strategy->randStruct->field12_0x30;
    dist = (float10)FUN_00041560();
    if (dist < (float10)fVar5) {
      iVar3 = *(int *)&strategy->field_0x144;
      if (iVar3 == 7) {
        return;
      }
      paVar1 = (strategy->strategy).parentActor;
      mummy_mind = paVar1->mind;
      if (iVar3 == 2) {
        if (*(int *)&strategy->field_0x17c == 0) {
          FUN_0013b7e0(paVar1,(entityBodyPlayer_0x924)&strategy->field_0x158,MummyCursedSlabWhack);
          *(undefined4 *)&strategy->field_0x17c = 1;
        }
      }
      else if (iVar3 == 4) {
        FUN_000bd650();
        FUN_0013b810((int)&strategy->field_0x158,paVar1);
        *(undefined4 *)&strategy->field_0x17c = 0;
      }
      else if (iVar3 == 5) {
        *(undefined4 *)&strategy->field_0x154 = 0;
      }
      *(undefined4 *)&strategy->field_0x144 = 7;
      actorMind::removeGoals(mummy_mind);
      actorMind::setGoalFromScript(mummy_mind,"slabwhacksneaky");
      return;
    }
    if ((mummy_mind->actionInfo).next != (actorGoalInfo *)0x0) {
      return;
    }
    iVar3 = *(int *)&strategy->field_0x144;
LAB_000bd28f:
    if (iVar3 != 8) {
      paVar1 = (strategy->strategy).parentActor;
      if (iVar3 == 2) {
        if (*(int *)&strategy->field_0x17c == 0) {
          FUN_0013b7e0(paVar1,(entityBodyPlayer_0x924)&strategy->field_0x158,MummyCursedSlabWhack);
          *(undefined4 *)&strategy->field_0x17c = 1;
        }
      }
      else {
        if (iVar3 == 4) {
          FUN_000bd650();
          FUN_0013b810((int)&strategy->field_0x158,paVar1);
          *(undefined4 *)&strategy->field_0x17c = 0;
          *(undefined4 *)&strategy->field_0x144 = 8;
          return;
        }
        if (iVar3 == 5) {
          *(undefined4 *)&strategy->field_0x154 = 0;
          *(undefined4 *)&strategy->field_0x144 = 8;
          return;
        }
      }
      *(undefined4 *)&strategy->field_0x144 = 8;
      return;
    }
    break;
  case 8:
    if ((mummy_mind->actionInfo).next == (actorGoalInfo *)0x0) {
      actorStrategy::setStrategy(&strategy->strategy,Far);
    }
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void FUN_000bd450(entityStrategyMummyCursed *strategy,int param_2)

{
  int iVar1;
  actor *act;
  actorMind *mind;
  int iVar2;
  float10 fVar3;
  float in_XMM0_Da;
  float fVar4;
  
  iVar2 = param_2;
  iVar1 = *(int *)&strategy->field_0x144;
  if (iVar1 != param_2) {
    act = (strategy->strategy).parentActor;
    mind = act->mind;
    if (iVar1 == 2) {
      if (*(int *)&strategy->field_0x17c == 0) {
        FUN_0013b7e0(act,(entityBodyPlayer_0x924)&strategy->field_0x158,MummyCursedSlabWhack);
        *(undefined4 *)&strategy->field_0x17c = 1;
      }
    }
    else if (iVar1 == 4) {
      FUN_000bd650();
      FUN_0013b810((int)&strategy->field_0x158,act);
      *(undefined4 *)&strategy->field_0x17c = 0;
      iVar2 = param_2;
    }
    else if (iVar1 == 5) {
      *(undefined4 *)&strategy->field_0x154 = 0;
    }
    *(int *)&strategy->field_0x144 = iVar2;
    switch(iVar2) {
    case 1:
      *(undefined4 *)&strategy->field_0x14c = 0;
      *(undefined4 *)&strategy->field_0x150 = 0;
      *(undefined4 *)&strategy->field_0x154 = 0;
      fVar3 = avatar::distanceBetweenAvatars(act,strategy->otherAvatar);
      if (fVar3 < (float10)strategy->randStruct->distanceToEvade) {
        actorMind::setGoalFromScript(mind,"evadeknockdown");
        return;
      }
      fVar3 = avatar::distanceBetweenAvatars(act,strategy->otherAvatar);
      if ((float10)strategy->randStruct->distanceToComeIntoRange < fVar3) {
        actorMind::setGoalFromScript(mind,"comeintorangeknockdown");
        return;
      }
      break;
    case 2:
      actorMind::setGoalFromScript(mind,"slabwhackprepare");
      return;
    case 3:
      fVar4 = mummy::getSomeRandomValue(strategy->randStruct);
      strategy->someRandValue = fVar4;
      return;
    case 4:
      *(undefined4 *)&strategy->field_0x150 = 1;
      if (strategy->otherAvatar != (avatar *)0x0) {
        actorBody::setFlag((actorBody *)strategy->otherAvatar[1].rotQuat.z,0x3d);
      }
      FUN_000bc6d0();
      strategy->someRandValue = in_XMM0_Da;
      return;
    case 5:
                    // Within scare radius
      *(undefined4 *)&strategy->field_0x150 = 0;
      if (*(int *)&strategy->field_0x154 == 0) {
        param_2 = 0x5b;
        (*strategy->otherAvatar->vtable->onMessage)(strategy->otherAvatar,&param_2);
        *(undefined4 *)&strategy->field_0x154 = 1;
        actorMind::setGoalFromScript(mind,"slabwhack");
        return;
      }
      break;
    case 6:
      *(undefined4 *)&strategy->field_0x150 = 0;
      actorMind::setGoalFromScript(mind,"scared");
      return;
    case 7:
      actorMind::removeGoals(mind);
      actorMind::setGoalFromScript(mind,"slabwhacksneaky");
    }
  }
  return;
}




void __fastcall FUN_000bd830(actorStrategy *param_1,int param_2)

{
  int iVar1;
  
  iVar1._0_2_ = param_1[7].resetState;
  iVar1._2_2_ = param_1[7].id;
  if (iVar1 == 1) {
    if (*(int *)(*(int *)(param_2 + 0x958) + 0x58) == 0) {
      FUN_000bd8b0();
      return;
    }
  }
  else if (iVar1 == 2) {
    if ((*(byte *)(*(int *)(*(int *)(*(int *)(param_2 + 0x95c) + 0x15c) + 8) + 3) & 1) == 0) {
      FUN_001345b0();
      return;
    }
    param_1[7].resetState = 3;
    param_1[7].id = 0;
  }
  else if ((iVar1 == 3) && (*(int *)(*(int *)(param_2 + 0x958) + 0x58) == 0)) {
    actorStrategy::setStrategy(param_1,Far);
    return;
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void __fastcall FUN_000bd8b0(actorStrategy *param_1)

{
  CalloutDescriptor **ppCVar1;
  int iVar2;
  actorMind *paVar3;
  actor *paVar4;
  weapon *pwVar5;
  int in_EAX;
  objParams *params;
  actorStrategyVTable *paVar6;
  float10 fVar7;
  
  iVar2._0_2_ = param_1[7].resetState;
  iVar2._2_2_ = param_1[7].id;
  if (in_EAX != iVar2) {
    param_1[7].resetState = (short)in_EAX;
    param_1[7].id = (short)((uint)in_EAX >> 0x10);
    if (in_EAX == 1) {
      paVar3 = param_1->parentActor->mind;
      paVar4 = paVar3->actor;
      if (paVar3->targetBody == (actorBody *)0x0) {
        actorStrategy::setStrategy(param_1,Far);
        return;
      }
      pwVar5 = paVar3->targetBody->currentWeapon;
      param_1[7].vtable = (actorStrategyVTable *)pwVar5;
      if (*(short *)&pwVar5->field_0xcdc != 2) {
        actorStrategy::setStrategy(param_1,Far);
        param_1[7].vtable = (actorStrategyVTable *)0x0;
        return;
      }
      fVar7 = avatar::distanceBetweenAvatars(paVar4,&pwVar5->avatar);
      if (fVar7 < (float10)(float)(param_1[1].vtable)->update) {
        actorMind::setGoalFromScript(paVar3,"evadespecial");
        return;
      }
      fVar7 = avatar::distanceBetweenAvatars(paVar4,(avatar *)param_1[7].vtable);
      if ((float10)(float)(param_1[1].vtable)->enterState < fVar7) {
        actorMind::setGoalFromScript(paVar3,"comeintorangespecial");
      }
    }
    else if (in_EAX == 2) {
      paVar3 = param_1->parentActor->mind;
      paVar4 = paVar3->actor;
      actorMind::setGoalFromScript(paVar3,"deathcurse");
      ppCVar1 = &(paVar4->avatar).callout;
      if (ppCVar1 != (CalloutDescriptor **)0x0) {
        actor::executeCalloutInDescriptor
                  (*ppCVar1,MummyCursedDeathCurseChantBegin,CalloutCallback1,0,paVar4,
                   (entityBodyPlayer_0x924)&param_1[0xc].field_0x4);
      }
      params = Assets::GetObjParams((char *)&param_1[3].actorStrategyId3);
      if (params != (objParams *)0x0) {
        *(actor **)(params + 1) = paVar4;
        paVar6 = (actorStrategyVTable *)Assets::CreateEntityFromParams(params);
        free(params);
        param_1[0xc].vtable = paVar6;
        return;
      }
      param_1[0xc].vtable = (actorStrategyVTable *)0x0;
      return;
    }
  }
  return;
}




void FUN_000bdb30(entityStrategyMummyCursed *param_1)

{
  int iVar1;
  actor *paVar2;
  
  if ((*(int *)&param_1->field_0x180 != 0) && (*(int *)&param_1->field_0x184 != 0)) {
    iVar1 = *(int *)(*(int *)&param_1->field_0x184 + 0x95c);
    paVar2 = *(actor **)(iVar1 + 0x718);
    if ((paVar2 != (actor *)0x0) && (paVar2 == (param_1->strategy).parentActor)) {
      *(undefined4 *)(iVar1 + 0x718) = 0;
      *(undefined4 *)&param_1->field_0x180 = 0;
      *(undefined4 *)&param_1->field_0x184 = 0;
    }
  }
  FUN_000bc770(param_1,(param_1->strategy).parentActor);
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void FUN_000bf8b0(actorStrategy *param_1,Message *param_2)

{
  actor *paVar1;
  actorMind *mind;
  int iVar2;
  BOOL BVar3;
  
  paVar1 = param_1->parentActor;
  mind = paVar1->mind;
  iVar2 = FUN_001384f0(param_1,param_2);
  if ((iVar2 == 0) && ((param_2->header).msgId == Scene_ActorHit)) {
    actorStrategy::onMessage(param_1,param_2);
    BVar3 = actorStrategy::checkAndSetDying(param_1);
    if ((BVar3 == 0) && ((param_2->header).someActor == paVar1)) {
      actorMind::removeGoals(mind);
    }
    return;
  }
  actorStrategy::onMessage(param_1,param_2);
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void __fastcall FUN_000c1940(actorStrategy *param_1,int param_2)

{
  void *pvVar1;
  int iVar2;
  actor *paVar3;
  int iVar4;
  actorMind *mind;
  actorMindGoal *paVar5;
  float fVar6;
  vec3 local_18;
  float local_c;
  float in_stack_fffffff8;
  float in_stack_fffffffc;
  
  iVar2._0_2_ = param_1[1].resetState;
  iVar2._2_2_ = param_1[1].id;
  if (iVar2 == 1) {
    if ((*(short *)(*(int *)(param_2 + 0x95c) + 0x30) == 0) &&
       (*(float *)(*(int *)(param_2 + 0x95c) + 0x34) == 0.0)) {
      iVar4._0_2_ = param_1[1].resetState;
      iVar4._2_2_ = param_1[1].id;
      if (iVar4 == 2) {
        return;
      }
      param_1[1].resetState = 2;
      param_1[1].id = 0;
      paVar3 = param_1->parentActor;
      mind = paVar3->mind;
      avatar::getWorldPosition(&paVar3->avatar,&local_18);
      avatar::getWorldRotation(&paVar3->avatar,(vec3 *)&local_c);
      pvVar1 = (param_1[1].vtable)->ctor;
      runtime::rand = runtime::rand * 0x19660d + 0x3c6ef35f;
      fVar6 = 0.0 - (float)pvVar1;
      FUN_001060a0((((float)pvVar1 - fVar6) * ((float)(runtime::rand & 0x7fffff | 0x3f800000) - 1.0)
                   + fVar6) * 0.017453292 + in_stack_fffffff8 + 3.1415927,0x42c80000);
      paVar5 = actorMind::allocAction(mind,TurnToFacePoint);
      paVar5[1].t = 5.0;
      paVar5[1].prev = (actorMindGoal *)(local_18.x + local_c);
      paVar5[1].next = (actorMindGoal *)(local_18.y + in_stack_fffffff8);
      *(float *)&paVar5[1].goalId = local_18.z + in_stack_fffffffc;
      return;
    }
  }
  else if (iVar2 == 2) {
    if (*(int *)(*(int *)(param_2 + 0x958) + 0x58) == 0) {
      paVar3 = param_1->parentActor;
      param_1[1].resetState = 3;
      param_1[1].id = 0;
      actorMind::setGoalFromScript(paVar3->mind,"coffinlook");
      return;
    }
  }
  else if ((iVar2 == 3) && (*(int *)(*(int *)(param_2 + 0x958) + 0x58) == 0)) {
    local_c = 1.111139e-39;
    actorStrategy::setStrategy(param_1,Far);
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void __fastcall FUN_000c1b70(actorStrategy *param_1)

{
  int iVar1;
  int iVar2;
  actor *paVar3;
  int iVar4;
  int in_EAX;
  BOOL BVar5;
  actorStrategy *local_4;
  
  iVar1 = *(int *)(in_EAX + 0x958);
  local_4 = param_1;
  FUN_00139aa0(&local_4,0);
  iVar2._0_2_ = param_1[1].actorStrategyId3;
  iVar2._2_2_ = param_1[1].actorStrategyId4;
  if (iVar2 == 1) {
    if (*(int *)(iVar1 + 0x58) != 0) {
      return;
    }
    if ((*(int *)&param_1[1].actorStrategyId2 != 0) &&
       (BVar5 = Random::thresholdCheck(&runtime::rand,(param_1[1].vtable)->enterState), BVar5 != 0))
    {
      iVar1._0_2_ = param_1[1].actorStrategyId3;
      iVar1._2_2_ = param_1[1].actorStrategyId4;
      if (iVar1 == 2) {
        return;
      }
      paVar3 = param_1->parentActor;
      param_1[1].actorStrategyId3 = 2;
      param_1[1].actorStrategyId4 = 0;
      actorMind::setGoalFromScript(paVar3->mind,"knockbackfollowup");
      return;
    }
    iVar4._0_2_ = param_1[1].actorStrategyId3;
    iVar4._2_2_ = param_1[1].actorStrategyId4;
    if (iVar4 == 3) {
      return;
    }
    param_1[1].actorStrategyId3 = 3;
    param_1[1].actorStrategyId4 = 0;
  }
  else {
    if (iVar2 != 2) {
      if (iVar2 != 3) {
        return;
      }
      if (*(int *)(iVar1 + 0x58) != 0) {
        return;
      }
      actorStrategy::setStrategy(param_1,Far);
      return;
    }
    if (*(int *)(iVar1 + 0x58) != 0) {
      return;
    }
    param_1[1].actorStrategyId3 = 3;
    param_1[1].actorStrategyId4 = 0;
  }
  actorMind::setGoalFromScript(param_1->parentActor->mind,"coffincloseknockback");
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void __fastcall FUN_000c1c80(actorStrategy *param_1)

{
  int iVar1;
  int iVar2;
  int in_EAX;
  actorStrategy *local_4;
  
  iVar1 = *(int *)(in_EAX + 0x958);
  local_4 = param_1;
  FUN_00139aa0(&local_4,0);
  iVar2._0_2_ = param_1[1].newState_;
  iVar2._2_2_ = param_1[1].actorStrategyId;
  if (iVar2 == 1) {
    if (*(int *)(iVar1 + 0x58) == 0) {
      FUN_000c1ce0();
    }
  }
  else if ((iVar2 == 2) && (*(int *)(iVar1 + 0x58) == 0)) {
    actorStrategy::setStrategy(param_1,Far);
    return;
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void __fastcall FUN_000c1dc0(actorStrategy *param_1)

{
  int iVar1;
  uint uVar2;
  actorMind *mind;
  int in_EAX;
  int iVar3;
  float fVar4;
  float fVar5;
  actorStrategy *local_4;
  
  iVar3 = *(int *)(in_EAX + 0x958);
  iVar1 = *(int *)(in_EAX + 0x95c);
  local_4 = param_1;
  FUN_00139aa0(&local_4,0);
  uVar2 = *(uint *)&param_1[1].field_0x20;
  if (uVar2 == 1) {
    if (runtime::dx_timer <= 0.0) {
      fVar4 = runtime::DeltaTime * runtime::TimeScale;
    }
    else {
      fVar4 = 0.0;
    }
    fVar5 = 0.0;
    if ((param_1->parentActor->avatar).movementFreezeTimer <= 0.0) {
      fVar5 = (param_1->parentActor->avatar).actionSpeed;
    }
    if ((0.0 < *(float *)&param_1[1].fearCounter) &&
       (fVar4 = *(float *)&param_1[1].fearCounter - fVar5 * fVar4,
       *(float *)&param_1[1].fearCounter = fVar4, fVar4 <= 0.0)) {
      *(undefined4 *)&param_1[1].fearCounter = 0;
    }
    if ((*(byte *)(*(int *)(*(int *)(iVar1 + 0x15c) + 8) + 3) & 4) == 0) {
      iVar3 = FUN_000c1ee0(param_1);
      if ((iVar3 != 0) && (*(int *)&param_1[1].field_0x20 != 3)) {
        *(undefined4 *)&param_1[1].field_0x20 = 3;
        mind = param_1->parentActor->mind;
        actorMind::removeGoals(mind);
        actorMind::setGoalFromScript(mind,"coffinclose");
      }
    }
    else if (*(int *)&param_1[1].field_0x20 != 2) {
      *(undefined4 *)&param_1[1].field_0x20 = 2;
      return;
    }
  }
  else if (((1 < uVar2) && (uVar2 < 4)) && (*(int *)(iVar3 + 0x58) == 0)) {
    actorStrategy::setStrategy(param_1,Far);
    return;
  }
  return;
}




void FUN_000c2070(actorStrategy *param_1)

{
  actorStrategyOffsetId aVar1;
  actor *paVar2;
  
  aVar1 = param_1->id;
  paVar2 = param_1->parentActor;
  param_1[1].parentActor = (actor *)0x0;
  actorStrategy::update(param_1);
  switch(aVar1) {
  case Attack_KnockBack:
    FUN_000c1b70();
    return;
  case Attack_KnockDown:
    FUN_000c1c80();
    return;
  case Attack_Special:
    FUN_000c1dc0();
    return;
  case Far:
    FUN_000c1530(paVar2);
    return;
  case HitWall:
    FUN_000c1940();
    return;
  case Wait:
    FUN_000c1f90();
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void FUN_000c2140(entityStrategyMummyCursed *param_1,Message *param_2)

{
  actor *paVar1;
  Buffer<> *pBVar2;
  BOOL BVar3;
  int iVar4;
  actorDroneActionId *paVar5;
  
  paVar1 = (param_1->strategy).parentActor;
  switch((param_2->header).msgId) {
  case Avatar_HitByProjectileAndWaitingForFollow:
    param_1->field2_0x3c[4] = '\x01';
    param_1->field2_0x3c[5] = '\0';
    param_1->field2_0x3c[6] = '\0';
    param_1->field2_0x3c[7] = '\0';
    actorStrategy::setStrategy(&param_1->strategy,Wait);
    actorStrategy::onMessage(&param_1->strategy,param_2);
    return;
  case Actor_Celebrate:
    actorStrategy::setStrategy(&param_1->strategy,Celebrate);
    actorStrategy::onMessage(&param_1->strategy,param_2);
    return;
  case Actor_Dying:
    entityStrategyMummyCursed::onActorDyingMessage(param_1,(int)param_2);
    actorStrategy::onMessage(&param_1->strategy,param_2);
    return;
  case Actor_ForceIntro:
    actorStrategy::forceIntro(&param_1->strategy,0x1b);
    actorStrategy::onMessage(&param_1->strategy,param_2);
    return;
  case Scene_ActorHit:
    BVar3 = actorStrategy::checkAndSetDying(&param_1->strategy);
    if (BVar3 == 0) {
      if ((actor *)param_2[1].header.msgId == paVar1) {
        param_1->field2_0x3c[0x14] = '\x01';
        param_1->field2_0x3c[0x15] = '\0';
        param_1->field2_0x3c[0x16] = '\0';
        param_1->field2_0x3c[0x17] = '\0';
      }
      if (((param_2->header).someActor == paVar1) && ((param_1->strategy).fearCounter == '\0')) {
        paVar1 = (param_1->strategy).parentActor;
        if ((paVar1->actorType == Human) || ((paVar1->node0x93c).prev != (actor_0x93c)0x0)) {
          iVar4 = 1;
        }
        else {
          iVar4 = 0;
        }
        if ((ShouldntDroneBools[iVar4] == 0) && ("\x01"[Game::CheckMoveOn] != '\0')) {
          pBVar2 = paVar1->droneActionsBuf;
          if (pBVar2 != (Buffer<> *)0x0) {
            if (pBVar2->size == pBVar2->endOfQueue) {
              paVar5 = (actorDroneActionId *)0x0;
            }
            else {
              paVar5 = (actorDroneActionId *)
                       ((int)&pBVar2->entries->actionId +
                       (uint)pBVar2->currentDroneAction * (uint)pBVar2->valueSize);
            }
            if (*paVar5 != Null) break;
          }
          if (*(int *)(param_1->field2_0x3c + 4) == 0) {
            actorStrategy::setStrategy(&param_1->strategy,Far);
          }
        }
      }
    }
    break;
  case Scene_EventComplete:
    actorStrategy::onEventCompleted(param_1);
    actorStrategy::onMessage(&param_1->strategy,param_2);
    return;
  case Scene_EventFailed:
    actorStrategy::onEventFailed(param_1);
    actorStrategy::onMessage(&param_1->strategy,param_2);
    return;
  }
  actorStrategy::onMessage(&param_1->strategy,param_2);
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void FUN_000c2c70(actorStrategy *param_1,actorStrategyOffsetId param_2)

{
  param_1->parentActor->body->indexInStatsheet = 2;
  switch(param_2) {
  case Attack_KnockBack:
    FUN_000c26e0();
    return;
  case Attack_KnockDown:
    FUN_000c27f0();
    return;
  default:
    actorStrategy::enterState(param_1,param_2);
switchD_000c2c9d_caseD_401:
    return;
  case Emerge:
    actorMind::setGoalFromScript(param_1->parentActor->mind,"emerge");
    return;
  case Far:
    goto switchD_000c2c9d_caseD_401;
  }
}




void __fastcall FUN_000c2ed0(actorStrategy *param_1)

{
  CalloutDescriptor **ppCVar1;
  actor *paVar2;
  actor *act;
  actor *in_EAX;
  int iVar3;
  BOOL BVar4;
  float *extraout_ECX;
  actorBody *extraout_EDX;
  float fVar5;
  float fVar6;
  actorStrategy *local_4;
  
  local_4 = param_1;
  if (param_1[7].someFloat == 0.0) {
    if (runtime::dx_timer <= 0.0) {
      fVar5 = runtime::DeltaTime * runtime::TimeScale;
    }
    else {
      fVar5 = 0.0;
    }
    fVar6 = 0.0;
    if ((param_1->parentActor->avatar).movementFreezeTimer <= 0.0) {
      fVar6 = (param_1->parentActor->avatar).actionSpeed;
    }
    if ((0.0 < *(float *)&param_1[1].resetState) &&
       (fVar5 = *(float *)&param_1[1].resetState - fVar6 * fVar5,
       *(float *)&param_1[1].resetState = fVar5, fVar5 <= 0.0)) {
      param_1[1].resetState = 0;
      param_1[1].id = 0;
    }
    if (*(float *)&param_1[1].resetState <= 0.001 && *(float *)&param_1[1].resetState != 0.001) {
      ppCVar1 = &(in_EAX->avatar).callout;
      if (ppCVar1 != (CalloutDescriptor **)0x0) {
        actor::executeCalloutInDescriptor
                  (*ppCVar1,WarlockTeleport2,(CalloutCallback *)0x0,0,in_EAX,
                   (entityBodyPlayer_0x924)0x0);
      }
      param_1[7].someFloat = 1.4013e-45;
    }
  }
  switch(*(undefined4 *)&param_1[1].field_0x4) {
  case 1:
    iVar3 = FUN_00139aa0(&local_4,0);
    if (iVar3 != 0) {
      actorStrategy::canPlayIntro(param_1,0x1d);
    }
    FUN_0002b9f0();
    if (((*extraout_ECX <= 0.001 && *extraout_ECX != 0.001) &&
        (BVar4 = actorBody::flagIsSet(extraout_EDX,IsInKnockDown), BVar4 == 0)) &&
       (BVar4 = GetAmbienceAudio__(in_EAX), BVar4 != 0)) {
      FUN_000c3160();
      return;
    }
    break;
  case 2:
    FUN_000c34e0(1);
    FUN_000c3570();
    iVar3 = FUN_0002b9f0();
    if (iVar3 != 0) {
      FUN_000c3160();
      return;
    }
    break;
  case 3:
    BVar4 = GetAmbienceAudio__(in_EAX);
    if (BVar4 != 0) {
      FUN_0002b9f0();
    }
    if (((float)param_1[1].parentActor <= 0.001 && (float)param_1[1].parentActor != 0.001) &&
       (*(int *)&param_1[1].field_0x4 != 4)) {
      act = param_1->parentActor;
      *(undefined4 *)&param_1[1].field_0x4 = 4;
      actorMind::setGoalFromScript(act->mind,"reappear");
      FUN_000c3440();
      paVar2 = param_1[1].vtable[1].onMessage;
      param_1[1].parentActor = paVar2;
      *(actor **)&param_1[1].newState_ = paVar2;
      param_1->field_0x1a = 1;
      actor::executeCallout(act,0,WarlockAppear);
      return;
    }
    break;
  case 4:
    FUN_000c34e0(0);
    FUN_000c3570();
    iVar3 = FUN_0002b9f0();
    if ((iVar3 != 0) && (*(int *)&param_1[1].field_0x4 != 5)) {
      *(undefined4 *)&param_1[1].field_0x4 = 5;
      if (*(obj **)&param_1[7].field_0x30 != (obj *)0x0) {
        obj::closeObject(*(obj **)&param_1[7].field_0x30);
        *(undefined4 *)&param_1[7].field_0x30 = 0;
      }
      FUN_000c3490();
      return;
    }
    break;
  case 5:
    if (((param_1->parentActor->mind->actionInfo).next == (actorGoalInfo *)0x0) &&
       (BVar4 = GetAmbienceAudio__(in_EAX), BVar4 != 0)) {
      actorStrategy::setStrategy(param_1,Attack_KnockDown);
    }
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void __fastcall FUN_000c3b20(actorStrategy *param_1)

{
  actorMind *mind;
  int in_EAX;
  int iVar1;
  actorStrategy *local_4;
  
  mind = *(actorMind **)(in_EAX + 0x958);
  local_4 = param_1;
  iVar1 = FUN_00139aa0(&local_4,0);
  if (iVar1 == 0) {
    (*param_1->vtable->leaveState)(param_1,param_1->id);
    param_1->id = Far;
    actorMind::removeGoals(param_1->parentActor->mind);
    (*param_1->vtable->enterState)(param_1,Far);
    return;
  }
  if ((mind->actionInfo).next == (actorGoalInfo *)0x0) {
    if ((int)*(actor **)&param_1[2].field_0x4 < (int)param_1[2].parentActor) {
      actorMind::setGoalFromScript(mind,"attack");
      *(int *)&param_1[2].field_0x4 = *(int *)&param_1[2].field_0x4 + 1;
      return;
    }
    if (*(actor **)&param_1[2].field_0x4 == param_1[2].parentActor) {
      actorMind::setGoalFromScript(mind,"attackfinish");
      *(int *)&param_1[2].field_0x4 = *(int *)&param_1[2].field_0x4 + 1;
      return;
    }
    actorStrategy::setStrategy(param_1,Far);
  }
  return;
}




void FUN_000c3ea0(actorStrategy *param_1)

{
  actorStrategyOffsetId aVar1;
  
  aVar1 = param_1->id;
  FUN_000c42f0();
  actorStrategy::update(param_1);
  if (aVar1 == Attack_KnockDown) {
    FUN_000c3b20();
    return;
  }
  if (aVar1 == Far) {
    FUN_000c2ed0();
    return;
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void __fastcall FUN_000c4f40(actorStrategy *param_1)

{
  int iVar1;
  actorMind *mind;
  actorStrategyOffsetId aVar2;
  int in_EAX;
  int iVar3;
  BOOL BVar4;
  
  iVar1 = *(int *)(in_EAX + 0x958);
  if ((*(short *)(*(int *)(in_EAX + 0x95c) + 0x30) == 0) &&
     (*(float *)(*(int *)(in_EAX + 0x95c) + 0x34) == 0.0)) {
    if ((param_1->parentActor->mind->targetBody != (actorBody *)0x0) &&
       ((iVar3 = FUN_00138410(), iVar3 != 0 && (iVar3 = FUN_001383a0(), iVar3 != 0)))) {
      return;
    }
    iVar3 = FUN_0013a330(param_1,0x47c35000);
    if (iVar3 != 0) {
      aVar2 = FUN_000c55d0();
      actorStrategy::setStrategy(param_1,aVar2);
      return;
    }
    if (*(int *)(iVar1 + 0x58) == 0) {
      if (*(int *)&param_1[1].field_0x4 == 1) {
        BVar4 = Random::thresholdCheck(&runtime::rand,(param_1[1].vtable)->leaveState);
        if ((BVar4 != 0) && (*(int *)(iVar1 + 0x10) == 0)) {
          mind = param_1->parentActor->mind;
          *(undefined4 *)&param_1[1].field_0x4 = 2;
          actorMind::setGoalFromScript(mind,"swipeaimless");
          return;
        }
      }
      else if (*(int *)&param_1[1].field_0x4 != 2) {
        return;
      }
      FUN_000c51e0();
    }
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void FUN_000c5810(actorStrategy *param_1)

{
  actorStrategyOffsetId aVar1;
  actorStrategy *paVar2;
  int iVar3;
  
  paVar2 = param_1;
  aVar1 = param_1->id;
  actorStrategy::update(param_1);
  switch(aVar1) {
  case Attack_KnockBack:
    iVar3 = FUN_00139aa0(&param_1,0);
    if (iVar3 != 0) {
      FUN_000c4ee0();
    }
    break;
  case Attack_KnockDown:
    iVar3 = FUN_00139aa0(&param_1,0);
    if (iVar3 != 0) {
      FUN_000c4ee0();
      return;
    }
    break;
  case Attack_Special:
    iVar3 = FUN_00139aa0(&param_1,0);
    if (iVar3 != 0) {
      FUN_000c5300();
      return;
    }
    break;
  case GetWeapon:
    FUN_000c4e70();
    return;
  case Near:
    FUN_00139aa0(&param_1,0);
    if (aVar1 == paVar2->id) {
      FUN_000c4f40();
      return;
    }
    break;
  case Wait:
    FUN_000c5350();
    return;
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void FUN_000c5920(actorStrategy *param_1,Message *param_2)

{
  int iVar1;
  
  iVar1 = FUN_001384f0(param_1,param_2);
  if (iVar1 != 0) {
    actorStrategy::onMessage(param_1,param_2);
    return;
  }
  if ((param_1->id == Attack_Special) && ((param_2->header).msgId == Actor_GoalFlagSet)) {
    param_1[1].parentActor = (actor *)0x1;
    return;
  }
  FUN_000c5410();
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void FUN_000c5970(actorStrategy *param_1,actorStrategyOffsetId param_2,ushort param_3)

{
  if ((((param_3 < 0x3ed) || (0x3ef < param_3)) && (Approach < param_2)) &&
     (param_2 < Attack_Special_End)) {
    param_1->parentActor->skipObjectTypeLookup = 0;
  }
  param_1->parentActor->body->indexInStatsheet = 2;
  switch(param_2) {
  case Attack_KnockBack:
    param_1->parentActor->body->indexInStatsheet = 4;
    actorMind::setGoalFromScript(param_1->parentActor->mind,"swipe");
    return;
  case Attack_KnockDown:
    param_1->parentActor->body->indexInStatsheet = 5;
    actorMind::setGoalFromScript(param_1->parentActor->mind,"kickbig");
    return;
  case Attack_Special:
    param_1->parentActor->body->indexInStatsheet = 6;
    FUN_000c5290();
    return;
  default:
    actorStrategy::enterState(param_1,param_2);
switchD_000c59d4_caseD_416:
    return;
  case GetWeapon:
    actorMind::setGoalFromScript(param_1->parentActor->mind,"getweapon");
    return;
  case Near:
    *(undefined4 *)&param_1[1].field_0x4 = 0;
    FUN_000c51e0();
    return;
  case Wait:
    goto switchD_000c59d4_caseD_416;
  }
}




void MindMemory::dtor(MindMemoryTargetWantedToAttack *mem)

{
  MindMemoryHeader *pMVar1;
  undefined4 uVar2;
  int iVar3;
  HeapTableEntry *pHVar4;
  
  pMVar1 = (mem->header).prev;
  if (pMVar1 != (MindMemoryHeader *)0x0) {
    pMVar1->next = (mem->header).next;
  }
  pMVar1 = (mem->header).next;
  if (pMVar1 != (MindMemoryHeader *)0x0) {
    pMVar1->prev = (mem->header).prev;
  }
  (mem->header).prev = (MindMemoryHeader *)0x0;
  (mem->header).next = (MindMemoryHeader *)0x0;
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
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void actor::getClosestActorOrSmth(actor **param_1,actor *act)

{
  actor_conflict5 *paVar1;
  float10 fVar2;
  float10 fVar3;
  
  if ((Game::SceneInfo.playerActors.prev != (actor_0x93c_conflict5)0x0) &&
     (paVar1 = ADJ(Game::SceneInfo.playerActors.prev), paVar1 != (actor_conflict5 *)0x0)) {
    fVar2 = avatar::distanceBetweenAvatars(paVar1,&act->avatar);
    fVar3 = avatar::distanceBetweenAvatars(paVar1,&(*param_1)->avatar);
    if ((float10)(float)fVar2 < fVar3) {
      *param_1 = act;
    }
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


BOOL actorBody::isTargetable(actorBody *param_1,byte param_2,byte param_3)

{
  BOOL BVar1;
  
  if (((*(char *)&(param_1->worldPosition).x == '\0') &&
      (((param_2 & 4) == 0 || (((uint)param_1->largeProjectile & 0x10000) != 0)))) &&
     (((param_2 & 8) != 0 || (*(char *)((int)&param_1->largeProjectile + 1) == '\0')))) {
    if ((((param_2 & 0x10) != 0) && (*(char *)&param_1->largeProjectile == '\0')) &&
       (BVar1 = actorIsHumanOrNoPrevLL((actor *)param_1->currentWeapon), BVar1 != 0)) {
      return 0;
    }
    if ((((param_3 & 2) == 0) || (((uint)param_1->largeProjectile & 0x40000) == 0)) &&
       (((param_3 & 4) == 0 ||
        ((*(char *)&param_1->largeProjectile != '\0' ||
         (*(int *)&param_1->currentWeapon->field_0x98c == 0)))))) {
      if (((param_3 & 8) != 0) &&
         ((*(char *)&param_1->largeProjectile == '\0' &&
          (BVar1 = flagIsSet(*(actorBody **)&param_1->currentWeapon->field_0x95c,IsDying),
          BVar1 != 0)))) {
        return 0;
      }
      return 1;
    }
  }
  return 0;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void actorBody::updateBodyPositionFromMoveZX(actorBody *body)

{
  float speed;
  float delta;
  EntityMoveContext ctx;
  actor *act;
  
  act = body->actor;
                    // Store physics pos into visual pos
  ctx.pos.x = (act->avatar).physicsPos.x;
  ctx.pos.y = (act->avatar).physicsPos.y;
  ctx.pos.z = (act->avatar).physicsPos.z;
  ctx.velocity.x = (body->velocity).x;
  ctx.velocity.y = (body->velocity).y;
  ctx.velocity.z = (body->velocity).z;
  speed = 0.0;
  if (runtime::dx_timer <= 0.0) {
    delta = runtime::DeltaTime * runtime::TimeScale;
  }
  else {
    delta = 0.0;
  }
  if ((act->avatar).movementFreezeTimer <= 0.0) {
    speed = (act->avatar).actionSpeed;
  }
  EntityMoveContext::updateXY(&ctx,&ctx.velocity);
  act = body->actor;
  (act->avatar).physicsPos.y = speed * delta * body->yVelocity + ctx.pos.y;
  (act->avatar).physicsPos.x = ctx.pos.x;
  (act->avatar).physicsPos.z = ctx.pos.z;
  return;
}




void actorBody::turnToFacePoint(actorBody *this,vec3 *point)

{
  vec3 local_18;
  vec3 displacement;
  actorBody *body;
  
  body = this;
  if ((this->field13_0x30 == 0) && (this->someTimer2 == 0.0)) {
    avatar::getWorldPosition(&this->actor->avatar,&local_18);
    displacement.x = point->x - local_18.x;
    displacement.y = point->y - local_18.y;
    displacement.z = point->z - local_18.z;
    vec3::getTurnAngle(&displacement,(float *)&this);
    (body->rotation).x = 0.0;
    (body->rotation).y = (float)this;
    (body->rotation).z = 0.0;
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void actorBody::applyBodyDirectionToRotation(actorBody *this)

{
  vec3 local_18;
  vec3 local_c;
  
  local_18.y = (this->rotation).y;
  local_18.z = 0.0;
  local_18.x = 0.0;
  if (this->field_0x19e != '\0') {
    local_c.x = (this->direction).x;
    local_c.y = (this->direction).y;
    local_c.z = (this->direction).z;
    FUN_001068e0(&local_18,&local_18.z,&local_c,(this->actor->avatar).rotEuler.y);
  }
  (this->rotation).x = local_18.x;
  (this->rotation).y = local_18.y;
  (this->rotation).z = local_18.z;
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields

actor * spawnActor(vec3 *pos,vec3 *rot,char *ghoulieAID,float scale,char *mindAID,char *strategyAID,
                  char *startingWeapon,char *deathSpawnDetails,char *actorAttribsAID,short param_10)

{
  ushort uVar3;
  actorParams *params;
  uint uVar4;
  actor *paVar5;
  char cVar1;
  int iVar2;
  
  if (*(int *)ghoulieAID != 0x5f646961) {
    return (actor *)0x0;
  }
  params = (actorParams *)Assets::GetObjParams(ghoulieAID);
  if (params == (actorParams *)0x0) {
    return (actor *)0x0;
  }
  (params->avatarParams).pos.x = pos->x;
  (params->avatarParams).pos.y = pos->y;
  (params->avatarParams).pos.z = pos->z;
  (params->avatarParams).rotEuler.x = rot->x;
  (params->avatarParams).rotEuler.y = rot->y;
  (params->avatarParams).rotEuler.z = rot->z;
  (params->avatarParams).scale = scale;
  if (param_10 == 0) {
    uVar3 = 0;
  }
  else {
    uVar4 = Marker::GetSmth(param_10);
    uVar3 = (ushort)uVar4;
  }
  (params->avatarParams).ghoulyboxId2 = uVar3;
  *(short *)((int)&(params->avatarParams).impactId + 2) = param_10;
  if (mindAID != (char *)0x0) {
    iVar2 = 0x3ba - (int)mindAID;
    do {
      cVar1 = *mindAID;
      mindAID[(int)params + iVar2] = cVar1;
      mindAID = mindAID + 1;
    } while (cVar1 != '\0');
  }
  if (strategyAID != (char *)0x0) {
    iVar2 = 0x33a - (int)strategyAID;
    do {
      cVar1 = *strategyAID;
      strategyAID[(int)params + iVar2] = cVar1;
      strategyAID = strategyAID + 1;
    } while (cVar1 != '\0');
  }
  if (startingWeapon != (char *)0x0) {
    iVar2 = 0x4ba - (int)startingWeapon;
    do {
      cVar1 = *startingWeapon;
      startingWeapon[(int)params + iVar2] = cVar1;
      startingWeapon = startingWeapon + 1;
    } while (cVar1 != '\0');
  }
  if (deathSpawnDetails != (char *)0x0) {
    iVar2 = 0x53a - (int)deathSpawnDetails;
    do {
      cVar1 = *deathSpawnDetails;
      deathSpawnDetails[(int)params + iVar2] = cVar1;
      deathSpawnDetails = deathSpawnDetails + 1;
    } while (cVar1 != '\0');
  }
  if (actorAttribsAID != (char *)0x0) {
    iVar2 = 0x5ba - (int)actorAttribsAID;
    do {
      cVar1 = *actorAttribsAID;
      actorAttribsAID[(int)params + iVar2] = cVar1;
      actorAttribsAID = actorAttribsAID + 1;
    } while (cVar1 != '\0');
  }
  paVar5 = (actor *)Assets::CreateEntityFromParams((objParams *)params);
  free(params);
  return paVar5;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields

actor * FUN_001348f0(char *deathSpawnAID,char *startingWeaponAID,vec3 *pos,vec3 *rot,char *ghoulyAID
                    ,char *mindAID,char *strategyAID,char *actorAttribsAID)

{
  actor *paVar1;
  
  paVar1 = spawnActor(pos,rot,ghoulyAID,1.0,mindAID,strategyAID,startingWeaponAID,deathSpawnAID,
                      actorAttribsAID,0);
  return paVar1;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


uint actor::updateDuringCutscene(actor *act)

{
  Buffer<> *pBVar1;
  actorBody *paVar2;
  uint uVar3;
  BOOL BVar4;
  actorDroneActionId aVar5;
  actorDroneActionId *paVar6;
  
  pBVar1 = act->droneActionsBuf;
  paVar2 = act->body;
  if (pBVar1 == (Buffer<> *)0x0) {
    aVar5 = Null;
  }
  else {
    if (pBVar1->size == pBVar1->endOfQueue) {
      paVar6 = (actorDroneActionId *)0x0;
    }
    else {
      paVar6 = (actorDroneActionId *)
               ((int)&pBVar1->entries->actionId +
               (uint)pBVar1->currentDroneAction * (uint)pBVar1->valueSize);
    }
    aVar5 = *paVar6;
  }
  switch(aVar5) {
  case Null:
  case Nothing:
  case NothingInvulnerable:
  case NothingIgnoreTraitorFever:
    break;
  case WalkToDest:
  case WalkToDestNotScared:
  case WalkToDestThenTaunt:
  case WalkToDestThenDelete:
  case WalkToDestNoDecel:
    if ((act->mind != (actorMind *)0x0) && ((act->mind->actionInfo).next != (actorGoalInfo *)0x0)) {
      return 0;
    }
    break;
  case Burst:
  case BurstFromWall:
  case BurstFromFloor:
  case BurstFromCeiling:
    if ((paVar2->flagSet->flags->attackFlags_ & 0x10000) != Null) {
      return 1;
    }
  default:
    return 0;
  case WaitForScare:
                    // Return not flag 1?
    return ~g_globalFlagset & 1;
  case StandNervously:
    return act->isDroning;
  case Intro:
    return ~(g_globalFlagset >> 2) & 1;
  case RestartFromFaint:
    uVar3 = actorBody::flagIsSet(paVar2,IsStanding);
    return uVar3;
  case Appear:
    BVar4 = actorBody::flagIsSet(paVar2,DroneAppear);
    return (uint)(BVar4 == 0);
  case Celebrate:
  case Worry:
    BVar4 = actorBody::flagIsSet(paVar2,IsStanding);
    if (BVar4 == 0) {
      return 0;
    }
  }
  return 1;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


BOOL actor::handleDroneTrigger(actor *act,BOOL *success)

{
  actorBody *body;
  actorBodyStateId aVar1;
  BOOL BVar2;
  
  body = act->body;
  switch(act->droneTriggerId) {
  case Null:
    aVar1 = (*body->vtable->getDroneState)(body);
    BVar2 = actorBody::setState(body,aVar1);
    *success = BVar2;
    return BVar2;
  case Argue:
    BVar2 = actorBody::setState(body,DroneArgue);
    *success = BVar2;
    return BVar2;
  case NotListening:
    BVar2 = actorBody::setState(body,DroneNotListening);
    *success = BVar2;
    return BVar2;
  case Eat:
    BVar2 = actorBody::setState(body,DroneEat);
    *success = BVar2;
    return BVar2;
  case Cook:
    BVar2 = actorBody::setState(body,DroneCook);
    *success = BVar2;
    return BVar2;
  case Dance:
    BVar2 = actorBody::setState(body,DroneDance);
    *success = BVar2;
    return BVar2;
  case Cheer:
    aVar1 = (*body->vtable->getDroneCheerState)(body);
    BVar2 = actorBody::setState(body,aVar1);
    *success = BVar2;
    return BVar2;
  case CardPlaying1:
    BVar2 = actorBody::setState(body,DroneCardPlaying1);
    *success = BVar2;
    return BVar2;
  case CardPlaying2:
    BVar2 = actorBody::setState(body,DroneCardPlaying2);
    *success = BVar2;
    return BVar2;
  case DanceMove:
    BVar2 = actorBody::setState(body,DroneDanceMove);
    *success = BVar2;
    return BVar2;
  case Waiter1:
    BVar2 = actorBody::setState(body,DroneWaiter1);
    *success = BVar2;
    return BVar2;
  case Waiter2:
    BVar2 = actorBody::setState(body,DroneWaiter2);
    *success = BVar2;
    return BVar2;
  case DJ:
    BVar2 = actorBody::setState(body,DroneDJ);
    *success = BVar2;
    return BVar2;
  case Nothing:
    *success = 0;
    return 1;
  case Drink:
    BVar2 = actorBody::setState(body,DroneDrink);
    *success = BVar2;
    return BVar2;
  case Dig1:
    BVar2 = actorBody::setState(body,DroneDig1);
    *success = BVar2;
    return BVar2;
  case Dig2:
    BVar2 = actorBody::setState(body,DroneDig2);
    *success = BVar2;
    return BVar2;
  case Dig3:
    BVar2 = actorBody::setState(body,DroneDig3);
    *success = BVar2;
    return BVar2;
  case Overseer:
    BVar2 = actorBody::setState(body,DroneOverseer);
    *success = BVar2;
    return BVar2;
  case Cleaning1:
    BVar2 = actorBody::setState(body,DroneCleaning1);
    *success = BVar2;
    return BVar2;
  case Cleaning2:
    BVar2 = actorBody::setState(body,DroneCleaning2);
    *success = BVar2;
    return BVar2;
  case Perv:
    BVar2 = actorBody::setState(body,DronePerv);
    *success = BVar2;
    return BVar2;
  default:
    *success = 0;
    return 0;
  }
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


int FUN_00135790(actor *act,void **mind,actorDroneActionId id)

{
  actorBody *body;
  actorBodyStateId aVar1;
  void *pvVar2;
  uint uVar3;
  int iVar4;
  
  body = act->body;
  *mind = (void *)0x0;
  switch(id) {
  case Null:
  case Generating:
  case WaitForScare:
  case WalkToDestNotScared:
  case Intro:
  case WalkToDestThenTaunt:
  case Nothing:
  case NothingInvulnerable:
  case WalkToDestThenDelete:
  case NothingIgnoreTraitorFever:
    break;
  case WalkToDest:
  case WalkToDestNoDecel:
    pvVar2 = (void *)FUN_00135ab0();
    *mind = pvVar2;
    return 1;
  case Burst:
    pvVar2 = (void *)actorBody::setState(body,BurstFromCrate);
    *mind = pvVar2;
    return (int)pvVar2;
  case BurstFromWall:
    aVar1 = (*body->vtable->getBurstFromWallState)(body);
    pvVar2 = (void *)actorBody::setState(body,aVar1);
    *mind = pvVar2;
    return (int)pvVar2;
  case BurstFromFloor:
    pvVar2 = (void *)actorBody::setState(body,BurstFromFloor);
    *mind = pvVar2;
    return (int)pvVar2;
  case StandNervously:
    iVar4 = 0;
    uVar3 = 0;
    do {
      if ((body->flagSet->flags->flag1 & 0x40000000) != Null) {
        iVar4 = 1;
        break;
      }
      uVar3 = uVar3 + 1;
    } while (uVar3 < 3);
    if (body->field_0x6a == '\0') {
      if (iVar4 != 0) {
        return iVar4;
      }
      pvVar2 = (void *)FUN_00135b40();
      *mind = pvVar2;
      return (int)pvVar2;
    }
    break;
  case Eat:
    pvVar2 = (void *)actorBody::setState(body,DroneEat);
    *mind = pvVar2;
    return (int)pvVar2;
  case Cook:
    pvVar2 = (void *)actorBody::setState(body,DroneCook);
    *mind = pvVar2;
    return (int)pvVar2;
  case Dance:
  case DanceInvulnerable:
    pvVar2 = (void *)actorBody::setState(body,DroneDance);
    *mind = pvVar2;
    return (int)pvVar2;
  case CardPlaying1:
    pvVar2 = (void *)actorBody::setState(body,DroneCardPlaying1);
    *mind = pvVar2;
    return (int)pvVar2;
  case CardPlaying2:
    pvVar2 = (void *)actorBody::setState(body,DroneCardPlaying2);
    *mind = pvVar2;
    return (int)pvVar2;
  case DanceMove:
    pvVar2 = (void *)actorBody::setState(body,DroneDanceMove);
    *mind = pvVar2;
    return (int)pvVar2;
  case DJ:
    pvVar2 = (void *)actorBody::setState(body,DroneDJ);
    *mind = pvVar2;
    return (int)pvVar2;
  case RestartFromFaint:
    FUN_0003ac90();
    pvVar2 = (void *)actorBody::setState(body,GetUp);
    *mind = pvVar2;
    avatar::onScenePrepare(act);
    if (body->weapon == (weapon *)0x0) {
      return (int)pvVar2;
    }
    avatar::onScenePrepare(body->weapon);
    return (int)pvVar2;
  case Dig1:
    pvVar2 = (void *)actorBody::setState(body,DroneDig1);
    *mind = pvVar2;
    return (int)pvVar2;
  case Dig2:
    pvVar2 = (void *)actorBody::setState(body,DroneDig2);
    *mind = pvVar2;
    return (int)pvVar2;
  case Dig3:
    pvVar2 = (void *)actorBody::setState(body,DroneDig3);
    *mind = pvVar2;
    return (int)pvVar2;
  case Overseer:
    pvVar2 = (void *)actorBody::setState(body,DroneOverseer);
    *mind = pvVar2;
    return (int)pvVar2;
  case Appear:
    pvVar2 = (void *)actorBody::setState(body,DroneAppearIn);
    *mind = pvVar2;
    return (int)pvVar2;
  case Disappear:
    pvVar2 = (void *)actorBody::setState(body,DroneAppearOut);
    *mind = pvVar2;
    return (int)pvVar2;
  case Celebrate:
    aVar1 = (*body->vtable->getCheerState)(body);
    pvVar2 = (void *)actorBody::setState(body,aVar1);
    *mind = pvVar2;
    return (int)pvVar2;
  case Worry:
    aVar1 = (*body->vtable->getCringeState)(body);
    pvVar2 = (void *)actorBody::setState(body,aVar1);
    *mind = pvVar2;
    return (int)pvVar2;
  case BurstFromCeiling:
    pvVar2 = (void *)actorBody::setState(body,BurstFromCeiling);
    *mind = pvVar2;
    return (int)pvVar2;
  case Cleaning1:
    pvVar2 = (void *)actorBody::setState(body,DroneCleaning1);
    *mind = pvVar2;
    return (int)pvVar2;
  case Cleaning2:
    pvVar2 = (void *)actorBody::setState(body,DroneCleaning2);
    *mind = pvVar2;
    return (int)pvVar2;
  case CelebrateLoop:
  case CelebrateLoopVulnerable:
    *mind = (void *)0x0;
    break;
  default:
    return 0;
  }
  return 1;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


int FUN_00136680(int param_1,actorMind *param_2,undefined4 param_3)

{
  int iVar1;
  int iVar2;
  float fVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  undefined4 uVar8;
  undefined4 uVar9;
  undefined1 *puVar10;
  undefined1 local_4 [4];
  
  puVar10 = local_4;
  fVar3 = *(float *)(param_1 + 0x2c) + 2.5;
  uVar8 = *(undefined4 *)(param_1 + 0x34);
  uVar9 = 0;
  uVar7 = *(undefined4 *)(param_1 + 0x38);
  uVar6 = *(undefined4 *)(param_1 + 0x30);
  uVar5 = *(undefined4 *)(param_1 + 0x28);
  uVar4 = *(undefined4 *)(param_1 + 0x24);
  iVar1 = FUN_00110bf0(param_1 + 0x10,param_2->actor->backgroundCollisionIndex,0);
  iVar1 = FUN_00136d60(param_3,param_1 + 0x10,iVar1,uVar4,uVar5,fVar3,uVar6,uVar7,uVar8,uVar9,
                       puVar10);
  if ((iVar1 == 0) && (iVar2 = FUN_001373f0(param_2,&param_2->evasionPos), iVar2 != 0)) {
    return 1;
  }
  return iVar1;
}




int entityMindHuman::chooseHumanAttack(uint attackMask,actorMind *mind,actorBody *target)

{
  byte bVar1;
  int iVar2;
  undefined3 extraout_var;
  HoldableType HVar3;
  undefined4 unaff_EDI;
  weapon *weapon;
  
  weapon = mind->actor->body->weapon;
  iVar2 = 0;
  if (weapon == (weapon *)0x0) {
    HVar3 = Invalid;
  }
  else {
    HVar3 = weapon->holdableType;
    if (Gun < HVar3) {
      return 0;
    }
  }
  switch(HVar3) {
  default:
    if ((attackMask & 2) == 0) {
      if ((attackMask & 4) == 0) goto switchD_00136793_caseD_2;
      iVar2 = useSuicideAttack(mind,target);
    }
    else {
      bVar1 = handleMeleeAttackOrKnockdown(mind,target,unaff_EDI,attackMask & 4);
      iVar2 = CONCAT31(extraout_var,bVar1);
    }
    if (iVar2 != 0) {
      return iVar2;
    }
  case Container:
  case LargeProjectile:
switchD_00136793_caseD_2:
    iVar2 = 0;
    if ((attackMask & 0x10) != 0) {
      iVar2 = handleThrowAttack(mind,target);
      return iVar2;
    }
    break;
  case None:
    if ((attackMask & 8) != 0) {
      iVar2 = handleSwingWeaponAttack(mind,target);
      return iVar2;
    }
    break;
  case Gun:
    if ((attackMask & 8) != 0) {
      iVar2 = handleSwingWeaponAttack(mind,target);
    }
    if ((attackMask & 0x20) != 0) {
      iVar2 = handleGunAttack(mind);
    }
  }
  return iVar2;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


byte handleMeleeAttackOrKnockdown(actorMind *mind,actorBody *target,uint param_3,int param_4)

{
  actorBody *body;
  BOOL BVar1;
  AttackEntry *attackEntry;
  int local_4;
  
  body = mind->actor->body;
  BVar1 = actorBody::canAttack(body);
  if (BVar1 == 0) {
    return 1;
  }
  attackEntry = (AttackEntry *)FUN_0001cda0(param_3,body,target,&local_4,param_4);
  if (attackEntry != (AttackEntry *)0x0) {
    FUN_0002a030();
    mind->currentAttackTarget = target;
    actorBody::useAttack(mind->actor->body,attackEntry,local_4);
  }
  return -(attackEntry != (AttackEntry *)0x0) & 2;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


byte useSuicideAttack(actorMind *param_1,actorBody *body)

{
  BOOL BVar1;
  AttackEntry *attackEntry;
  
  BVar1 = actorBody::canAttack(param_1->actor->body);
  if (BVar1 == 0) {
    return 1;
  }
  attackEntry = (AttackEntry *)FUN_0001cf70();
  if (attackEntry != (AttackEntry *)0x0) {
    FUN_0002a030();
    param_1->currentAttackTarget = body;
    actorBody::useAttack(param_1->actor->body,attackEntry,0);
  }
  return -(attackEntry != (AttackEntry *)0x0) & 2;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


byte handleSwingWeaponAttack(int param_1,undefined4 param_2)

{
  BOOL BVar1;
  AttackEntry *attackEntry;
  
  BVar1 = actorBody::canAttack(*(actorBody **)(*(int *)(param_1 + 8) + 0x95c));
  if (BVar1 == 0) {
    return 1;
  }
  attackEntry = (AttackEntry *)FUN_0001cfe0();
  if (attackEntry != (AttackEntry *)0x0) {
    FUN_0002a030();
    *(undefined4 *)(param_1 + 0x14) = param_2;
    actorBody::useAttack(*(undefined4 *)(*(int *)(param_1 + 8) + 0x95c),attackEntry,0);
  }
  return -(attackEntry != (AttackEntry *)0x0) & 2;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


byte handleThrowAttack(int param_1,undefined4 param_2)

{
  BOOL BVar1;
  AttackEntry *attackEntry;
  
  BVar1 = actorBody::canAttack(*(actorBody **)(*(int *)(param_1 + 8) + 0x95c));
  if (BVar1 == 0) {
    return 1;
  }
  attackEntry = (AttackEntry *)FUN_0001d060();
  if (attackEntry != (AttackEntry *)0x0) {
    FUN_0002a030();
    *(undefined4 *)(param_1 + 0x14) = param_2;
    actorBody::useAttack(*(undefined4 *)(*(int *)(param_1 + 8) + 0x95c),attackEntry,0);
  }
  return -(attackEntry != (AttackEntry *)0x0) & 2;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


byte handleGunAttack(int param_1)

{
  undefined4 in_EAX;
  BOOL BVar1;
  AttackEntry *attackEntry;
  
  BVar1 = actorBody::canAttack(*(actorBody **)(*(int *)(param_1 + 8) + 0x95c));
  if (BVar1 == 0) {
    return 1;
  }
  attackEntry = (AttackEntry *)FUN_0001d0e0();
  if (attackEntry != (AttackEntry *)0x0) {
    FUN_0002a030();
    *(undefined4 *)(param_1 + 0x14) = in_EAX;
    actorBody::useAttack(*(undefined4 *)(*(int *)(param_1 + 8) + 0x95c),attackEntry,0);
  }
  return -(attackEntry != (AttackEntry *)0x0) & 2;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


ActorGoal46 * actorMind::newGoal46(actorMind *mind,vec3 *pos)

{
  ActorGoal46 *pAVar1;
  
  pAVar1 = (ActorGoal46 *)allocAction(mind,WalkToPoint);
  pAVar1->field2_0x1c = 1.0;
  pAVar1->field3_0x20 = 1.0;
  pAVar1->field8_0x28 = 30.0;
  (pAVar1->pos).x = pos->x;
  (pAVar1->pos).y = pos->y;
  (pAVar1->pos).z = pos->z;
  return pAVar1;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void actorMind::updateStateType(actorMind *mind)

{
  actorBody *body;
  bool lowHealth;
  
  body = mind->actor->body;
  if (0.0 < mind->targetTimer) {
    *(undefined4 *)&mind->field_0x4c = 0x41;
    return;
  }
  if (mind->field_0x20 != '\0') {
    *(undefined4 *)&mind->field_0x4c = 0x42;
    return;
  }
  if ((body->maxHealth == 0) || (0.25 < (float)body->health / (float)body->maxHealth)) {
    lowHealth = false;
  }
  else {
    lowHealth = true;
  }
  if (Game::SceneInfo.enemies == (actor_0x944)0x0) {
    if ((body->flagSet->flags->attackFlags_ & WaitingForFollowUp) != Null) {
      *(undefined4 *)&mind->field_0x4c = 0x45;
      return;
    }
    if (!lowHealth) {
      *(undefined4 *)&mind->field_0x4c = 0x44;
      return;
    }
  }
  else if (!lowHealth) {
    *(undefined4 *)&mind->field_0x4c = 0x40;
    return;
  }
  *(undefined4 *)&mind->field_0x4c = 0x46;
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


BOOL actorBody::checkSomePhysicsWalkPos(undefined4 *param_1,actorBody *body,float *param_3)

{
  float10 fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  
  if ((body->flagSet->flags->flag1 & 0x1000) != Null) {
    *param_1 = 1;
    return 1;
  }
  *param_1 = 0;
  fVar3 = (body->actor->avatar).physicsPos.x;
  fVar4 = (body->actor->avatar).physicsPos.z;
  fVar5 = 0.0;
  if ((fVar3 != 0.0) || (fVar4 != 0.0)) {
    fVar2 = fVar3 * fVar3 + fVar4 * fVar4;
    if (fVar2 != 0.0) {
      fVar1 = (float10)invsqrt(fVar2);
      fVar3 = (float)((float10)fVar3 * fVar1);
      fVar5 = (float)((float10)0.0 * fVar1);
      fVar4 = (float)((float10)fVar4 * fVar1);
    }
    fVar3 = (body->somePhysicsWalkPos).z * fVar4 + (body->somePhysicsWalkPos).x * fVar3 +
            (body->somePhysicsWalkPos).y * fVar5;
    *param_3 = fVar3;
    if (fVar3 < -0.7) {
      return 1;
    }
  }
  return 0;
}




bool actor::updateFreezeTimers(actor *param_1)

{
  bool bVar1;
  bool bVar2;
  bool ret;
  MessageHeader local_14;
  
  bVar2 = false;
  bVar1 = false;
  if (param_1->actorType == Ghoulie_old) {
    bVar1 = true;
  }
  else {
    if (param_1->actorType != NPC) {
      return false;
    }
    bVar2 = true;
  }
  ret = false;
  if ((bVar1) || (bVar2)) {
    ret = Game::PowerupParams[7].active != 0;
    if (ret) {
      (param_1->avatar).movementFreezeTimer = Game::PowerupParams[7].duration;
      local_14.someActor = Game::PowerupParams[7].field3_0xc;
      local_14.msgId = Scene_PowerupActivated;
      (*((param_1->avatar).vtable)->onMessage)(param_1,&local_14);
    }
    if ((bVar1) && (Game::PowerupParams[0x13].active != 0)) {
      param_1->traitorTimer = Game::PowerupParams[0x13].duration;
      local_14.someActor = Game::PowerupParams[0x13].field3_0xc;
      ret = (bool)(ret + '\x01');
      local_14.msgId = Scene_PowerupActivated;
      (*((param_1->avatar).vtable)->onMessage)(param_1,&local_14);
    }
  }
  return ret != false;
}




undefined4 FUN_001384f0(actorStrategy *param_1,Message *param_2)

{
  actor *paVar1;
  Buffer<> *pBVar2;
  undefined4 uVar3;
  actorDroneActionId *paVar4;
  int iVar5;
  
  switch((param_2->header).msgId) {
  case Actor_TimeCowardExpired:
  case Scene_ActorInserted:
  case Scene_ActorRemoved:
  case Scene_ActorScaredBegin:
  case Scene_ActorScaredEnd:
  case Scene_ActorStoppedDroning:
  case Scene_EventBegin:
  case Scene_EventEnd:
    if (param_1->fearCounter == '\0') {
      paVar1 = param_1->parentActor;
      if ((paVar1->actorType == Human) || ((paVar1->node0x93c).prev != (actor_0x93c)0x0)) {
        iVar5 = 1;
      }
      else {
        iVar5 = 0;
      }
      if ((ShouldntDroneBools[iVar5] == 0) && ("\x01"[Game::CheckMoveOn] != '\0')) {
        pBVar2 = paVar1->droneActionsBuf;
        if (pBVar2 != (Buffer<> *)0x0) {
          if (pBVar2->size == pBVar2->endOfQueue) {
            paVar4 = (actorDroneActionId *)0x0;
          }
          else {
            paVar4 = (actorDroneActionId *)
                     ((int)&pBVar2->entries->actionId +
                     (uint)pBVar2->currentDroneAction * (uint)pBVar2->valueSize);
          }
          if (*paVar4 != Null) {
            return 0;
          }
        }
        uVar3 = FUN_00138790();
        return uVar3;
      }
    }
    break;
  case Scene_ActorLostWeapon:
    if (param_1->fearCounter == '\0') {
      paVar1 = param_1->parentActor;
      if ((paVar1->actorType == Human) || ((paVar1->node0x93c).prev != (actor_0x93c)0x0)) {
        iVar5 = 1;
      }
      else {
        iVar5 = 0;
      }
      if ((ShouldntDroneBools[iVar5] == 0) && ("\x01"[Game::CheckMoveOn] != '\0')) {
        pBVar2 = paVar1->droneActionsBuf;
        if (pBVar2 != (Buffer<> *)0x0) {
          if (pBVar2->size == pBVar2->endOfQueue) {
            paVar4 = (actorDroneActionId *)0x0;
          }
          else {
            paVar4 = (actorDroneActionId *)
                     ((int)&pBVar2->entries->actionId +
                     (uint)pBVar2->currentDroneAction * (uint)pBVar2->valueSize);
          }
          if (*paVar4 != Null) {
            return 0;
          }
        }
        uVar3 = FUN_00138700(param_2);
        return uVar3;
      }
    }
    break;
  case Scene_ActorPickedUpWeapon:
    if (param_1->fearCounter == '\0') {
      paVar1 = param_1->parentActor;
      if ((paVar1->actorType == Human) || ((paVar1->node0x93c).prev != (actor_0x93c)0x0)) {
        iVar5 = 1;
      }
      else {
        iVar5 = 0;
      }
      if ((ShouldntDroneBools[iVar5] == 0) && ("\x01"[Game::CheckMoveOn] != '\0')) {
        pBVar2 = paVar1->droneActionsBuf;
        if (pBVar2 != (Buffer<> *)0x0) {
          if (pBVar2->size == pBVar2->endOfQueue) {
            paVar4 = (actorDroneActionId *)0x0;
          }
          else {
            paVar4 = (actorDroneActionId *)
                     ((int)&pBVar2->entries->actionId +
                     (uint)pBVar2->currentDroneAction * (uint)pBVar2->valueSize);
          }
          if (*paVar4 != Null) {
            return 0;
          }
        }
        uVar3 = FUN_00138740((Scene_ActorPickedUpWeaponMessage *)param_2);
        return uVar3;
      }
    }
  }
  return 0;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void FUN_00138b40(actorStrategy *param_1,Message *param_2)

{
  actor *act;
  Buffer<> *pBVar1;
  actor *paVar2;
  int iVar3;
  actorDroneActionId *paVar4;
  vec3 local_c;
  
  act = param_1->parentActor;
  pBVar1 = act->droneActionsBuf;
  if (pBVar1 != (Buffer<> *)0x0) {
    if (pBVar1->size == pBVar1->endOfQueue) {
      paVar4 = (actorDroneActionId *)0x0;
    }
    else {
      paVar4 = (actorDroneActionId *)
               ((int)&pBVar1->entries->actionId +
               (uint)pBVar1->currentDroneAction * (uint)pBVar1->valueSize);
    }
    if (((*paVar4 != Null) && (act->derivedMarkerValue != (DerivedMarkerValue *)0x0)) &&
       (avatar::getWorldPosition(&act->avatar,&local_c),
       local_c.z = local_c.z - (float)param_2[2].header.msgId,
       local_c.y = local_c.y - (float)param_2[1].header.someActor,
       local_c.x = local_c.x - (float)param_2[1].header.msgId,
       local_c.z * local_c.z + local_c.y * local_c.y + local_c.x * local_c.x <= 900.0)) {
      paVar2 = *(actor **)&((param_2->header).someActor)->body->field_0x274;
      if (paVar2 == (actor *)0x0) {
        param_2 = (Message *)0x0;
      }
      else {
        param_2 = (Message *)actorIsHumanOrNoPrevLL(paVar2);
        iVar3 = FUN_00042070();
        if ((iVar3 != 0) && (FUN_0002a030(), *(char *)(iVar3 + 0x14) == '\0')) {
          param_1->parentActor->mind->targetActor = *(actor **)(iVar3 + 0x10);
        }
      }
      FUN_00135700(param_2);
      FUN_00028580();
      actor::updateDroneAction(act,param_1);
    }
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void __fastcall FUN_00138e40(undefined4 param_1,int param_2,actorStrategy *param_3)

{
  ushort uVar1;
  actor *act;
  Buffer<> *pBVar2;
  actorMind *paVar3;
  int iVar4;
  undefined4 uVar5;
  actorDroneActionId *paVar6;
  
  act = param_3->parentActor;
  pBVar2 = act->droneActionsBuf;
  if (pBVar2 != (Buffer<> *)0x0) {
    if (pBVar2->size == pBVar2->endOfQueue) {
      paVar6 = (actorDroneActionId *)0x0;
    }
    else {
      paVar6 = (actorDroneActionId *)
               ((int)&pBVar2->entries->actionId +
               (uint)pBVar2->currentDroneAction * (uint)pBVar2->valueSize);
    }
    if ((((*paVar6 != Null) && (uVar1 = (act->avatar).field218_0x1fc, uVar1 != 0)) &&
        (*(short *)(*(int *)(param_2 + 8) + 0x1fc) != 0)) &&
       (uVar1 == *(ushort *)(*(int *)(param_2 + 8) + 0x1fe))) {
      paVar3 = act->mind;
      iVar4 = FUN_00042070();
      if (iVar4 != 0) {
        FUN_0002a030();
        if (*(char *)(iVar4 + 0x14) == '\0') {
          paVar3->targetActor = *(actor **)(iVar4 + 0x10);
        }
        uVar5 = FUN_001414c0();
        FUN_00135700(uVar5);
        FUN_00028580();
        actor::updateDroneAction(act,param_3);
        return;
      }
    }
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


undefined4 actor::CleanupBadDroneAction(actor *param_1,actorStrategy *strategy)

{
  uint16_t id2;
  actor *act;
  DerivedMarkerValue *dmv;
  undefined4 uVar1;
  
  act = param_1;
  if ((param_1->field_0x988 == '\0') && (id2 = (param_1->avatar).field218_0x1fc, id2 != 0)) {
    dmv = Marker::getByID2(id2);
  }
  else {
    dmv = (DerivedMarkerValue *)0x0;
  }
  act->field_0x988 = 1;
  FUN_00028500(dmv,act);
  if (dmv != (DerivedMarkerValue *)0x0) {
    act->field_0x989 = 1;
    handleDroneTrigger(act,&param_1);
    (*strategy->vtable->leaveState)(strategy,strategy->id);
    strategy->id = DroneAction;
    actorMind::removeGoals(strategy->parentActor->mind);
    (*strategy->vtable->enterState)(strategy,DroneAction);
    return 1;
  }
  act->field_0x989 = 0;
  uVar1 = FUN_001391d0(act,strategy);
  return uVar1;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields
// Disabling this causes major breakage to entity choices and strategy. Controls completely broken
// and lots of other issues


undefined4 actor::updateDroneAction(actor *act,actorStrategy *strategy)

{
  ushort uVar1;
  ushort uVar2;
  int iVar3;
  BOOL BVar4;
  actorDroneActionId *paVar5;
  DroneAction *puVar7;
  actorDroneActionId action_id;
  actorStrategyOffsetId id;
  Buffer<> *drone_data;
  Buffer<> *actions;
  
  drone_data = act->droneActionsBuf;
  if (drone_data == (Buffer<> *)0x0) {
    action_id = Null;
  }
  else {
    if (drone_data->size == drone_data->endOfQueue) {
      puVar7 = (DroneAction *)0x0;
    }
    else {
      puVar7 = (DroneAction *)
               ((int)&drone_data->entries->actionId +
               (uint)drone_data->currentDroneAction * (uint)drone_data->valueSize);
    }
    action_id = puVar7->actionId;
  }
  actions = act->droneActionsBuf;
  if (actions != (Buffer<> *)0x0) {
    uVar1 = actions->size;
    if (uVar1 != actions->endOfQueue) {
      uVar2 = actions->currentDroneAction;
      if (uVar1 < uVar2) {
        iVar3 = ((uint)actions->endOfQueue - (uint)uVar2) + 1 + (uint)uVar1;
      }
      else {
        iVar3 = ((uint)uVar1 - (uint)uVar2) + 1;
      }
      if (iVar3 == 1) {
        BVar4 = actorStrategy::shouldBeDroning(strategy);
        if ((BVar4 == 0) && (action_id != WalkToDestThenDelete)) {
          act->isDroning = 1;
          return 0;
        }
      }
    }
  }
  goToNextDroneAction(act);
  if (action_id == WalkToDestThenDelete) {
    actions = act->droneActionsBuf;
    if (actions != (Buffer<> *)0x0) {
      if (actions->size == actions->endOfQueue) {
        paVar5 = (actorDroneActionId *)0x0;
      }
      else {
        paVar5 = (actorDroneActionId *)
                 ((int)&actions->entries->actionId +
                 (uint)actions->currentDroneAction * (uint)actions->valueSize);
      }
      if (*paVar5 == WalkToDestThenDelete) goto LAB_001390de;
    }
    avatar::destroy(&act->avatar);
  }
LAB_001390de:
  actions = act->droneActionsBuf;
  if (actions != (Buffer<> *)0x0) {
    if (actions->size == actions->endOfQueue) {
      paVar5 = (actorDroneActionId *)0x0;
    }
    else {
      paVar5 = (actorDroneActionId *)
               ((int)&actions->entries->actionId +
               (uint)actions->currentDroneAction * (uint)actions->valueSize);
    }
    if (*paVar5 != Null) {
      CleanupBadDroneAction(act,strategy);
      return 0;
    }
  }
  act->skipObjectTypeLookup = 0;
  BVar4 = actorStrategy::shouldBeDroning(strategy);
  if (BVar4 != 0) {
    if (strategy->someFloat <= 0.0) {
      id = strategy->actorStrategyId;
    }
    else {
      id = Stall;
    }
    (*strategy->vtable->leaveState)(strategy,strategy->id);
    strategy->id = id;
    actorMind::removeGoals(strategy->parentActor->mind);
    (*strategy->vtable->enterState)(strategy,id);
    return 1;
  }
  (*strategy->vtable->leaveState)(strategy,strategy->id);
  strategy->id = Null;
  actorMind::removeGoals(strategy->parentActor->mind);
  (*strategy->vtable->enterState)(strategy,Null);
  return 1;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


undefined4 FUN_001391d0(actor *act,actorStrategy *strategy)

{
  actorDroneActionId id;
  Buffer<> *action_idd;
  int iVar1;
  DroneAction *action;
  DroneAction *drone_action;
  actorMind *mind;
  Buffer<> *drone_data;
  
  drone_data = act->droneActionsBuf;
  id = Null;
  if (drone_data != (Buffer<> *)0x0) {
    if (drone_data->size == drone_data->endOfQueue) {
      drone_action = (DroneAction *)0x0;
    }
    else {
      drone_action = (DroneAction *)
                     ((int)&drone_data->entries->actionId +
                     (uint)drone_data->currentDroneAction * (uint)drone_data->valueSize);
    }
    id = drone_action->actionId;
  }
  iVar1 = FUN_00135790(act,&mind,id);
  if (iVar1 == 0) {
    drone_data = act->droneActionsBuf;
    while (drone_data != (Buffer<> *)0x0) {
      actor::goToNextDroneAction(act);
      drone_data = act->droneActionsBuf;
    }
    return 0;
  }
  mind = act->mind;
  (*strategy->vtable->leaveState)(strategy,strategy->id);
  strategy->id = DroneAction;
  actorMind::removeGoals(strategy->parentActor->mind);
  (*strategy->vtable->enterState)(strategy,DroneAction);
  drone_data = act->droneActionsBuf;
  if (drone_data == (Buffer<> *)0x0) {
    id = Null;
  }
  else {
    if (drone_data->size == drone_data->endOfQueue) {
      action = (DroneAction *)0x0;
    }
    else {
      action = (DroneAction *)
               ((int)&drone_data->entries->actionId +
               (uint)drone_data->currentDroneAction * (uint)drone_data->valueSize);
    }
    id = action->actionId;
  }
  if (id == Intro) {
    actorMind::setGoalFromScript(mind,"ghouly_intro");
  }
  return 1;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void FUN_0013a000(actorMindGoal *param_1,undefined4 param_2)

{
  undefined4 uVar1;
  actorMindGoal *paVar2;
  int in_EAX;
  actorMindGoal *paVar3;
  int unaff_ESI;
  undefined4 *unaff_EDI;
  
  paVar3 = actorMind::allocAction(*(actorMind **)(in_EAX + 0x958),FlyToPoint);
  paVar3[1].t = 1.0;
  paVar3[2].prev = (actorMindGoal *)1.0;
  *(float *)&paVar3[2].goalId = 1.0;
  paVar3[2].next = (actorMindGoal *)10.0;
  paVar3[3].prev = (actorMindGoal *)30.0;
  paVar3[3].next = (actorMindGoal *)0.25;
  paVar3[1].prev = (actorMindGoal *)*unaff_EDI;
  paVar3[1].next = (actorMindGoal *)unaff_EDI[1];
  uVar1 = unaff_EDI[2];
  paVar3[1].goalId = (short)uVar1;
  paVar3[1].initialised = (bool)(char)((uint)uVar1 >> 0x10);
  paVar3[1].field4_0xb = (char)((uint)uVar1 >> 0x18);
  paVar3[3].prev = (actorMindGoal *)30.0;
  paVar3[2].t = *(float *)(unaff_ESI + 8);
  paVar3[3].prev = *(actorMindGoal **)(unaff_ESI + 0xc);
  paVar3[1].t = *(float *)(unaff_ESI + 0x10);
  paVar2 = *(actorMindGoal **)(unaff_ESI + 0x14);
  paVar3[2].next = param_1;
  paVar3[2].prev = paVar2;
  paVar3[2].goalId = (undefined2)param_2;
  paVar3[2].initialised = (bool)param_2._2_1_;
  paVar3[2].field4_0xb = param_2._3_1_;
  paVar3[3].next = (actorMindGoal *)0.25;
  return;
}




undefined4 FUN_0013a0f0(actorStrategy *param_1)

{
  int iVar2;
  astruct_52 *iVar1;
  actorMindGoal *paVar3;
  uint local_20;
  BOOL local_1c;
  vec3 v2;
  vec3 v1;
  actorMind *mind;
  actor *actor;
  
  actor = param_1->parentActor;
  v1.x = (actor->someVec3).x;
  mind = actor->mind;
  v1.y = (actor->someVec3).y;
  v1.z = (actor->someVec3).z;
  local_1c = SpawnThingFromMarker
                       (&v2,0,&v1,actor->backgroundCollisionIndex,0,20.0,0,actor->field812_0xca4,
                        (uint)(actor->avatar).tag,4);
  if (*(int *)&actor->field_0xca8 == 0) {
    local_20 = actor->field812_0xca4;
    avatar::getWorldPosition(&actor->avatar,&v1);
    iVar2 = FUN_0012cc50(&v2,0,0,1,0,local_20,&local_20,(actor->avatar).tag);
    if (iVar2 != 0) {
      return 1;
    }
  }
  if (local_1c != 0) {
    actorMind::removeGoals(mind);
    (mind->evasionPos).x = v2.x;
    (mind->evasionPos).y = v2.y;
    (mind->evasionPos).z = v2.z;
    if (actor->field827_0xcde == 1) {
      iVar1 = (astruct_52 *)actorMind::allocAction(mind,FlyToDestination);
      iVar1->field16_0x10 = 1.0;
      iVar1->field17_0x14 = 1.0;
      iVar1->field19_0x1c = 1.0;
      iVar1->field24_0x24 = 30.0;
      iVar1->field25_0x28 = 0.25;
      iVar1->field18_0x18 = 10.0;
      iVar1->field24_0x24 = 0.0;
      return 0;
    }
    paVar3 = actorMind::allocAction(mind,WalkToDestination);
    paVar3[1].prev = (actorMindGoal *)1.0;
    paVar3[1].next = (actorMindGoal *)1.0;
    paVar3[1].t = 30.0;
    paVar3[1].t = 0.0;
  }
  return 0;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


weapon * actor::handleWeaponSetup(actor *act,int parent,char *weaponName)

{
  weaponParams *params;
  weapon *wpn;
  int iVar1;
  ObjMsgID local_c;
  actor *local_8;
  weapon *local_4;
  
  params = (weaponParams *)Assets::GetObjParams(weaponName);
  if (params == (weaponParams *)0x0) {
    return (weapon *)0x0;
  }
  wpn = (weapon *)Assets::CreateEntityFromParams((objParams *)params);
  if (wpn != (weapon *)0x0) {
    if (parent != 0) {
      setupScriptedCollisions(act);
    }
    iVar1 = FUN_0001b2b0(act->body,1,wpn);
    if (iVar1 == 0) {
      Assets::DeleteResource_(wpn);
      free(params);
      return (weapon *)0x0;
    }
    local_c = Scene_ActorPickedUpWeapon;
    local_8 = act;
    local_4 = wpn;
    EventLoop::DispatchMessage(&local_c);
  }
  free(params);
  return wpn;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


BOOL actor::setupScriptedCollisions(actor *act)

{
  weapon *pwVar1;
  actorBodyStateId state;
  BOOL succ;
  actorBody *bodyy;
  AnimInstance *iVar2;
  KeyframeContext *paVar1;
  
  bodyy = act->body;
  pwVar1 = bodyy->weapon;
  if (pwVar1 != (weapon *)0x0) {
    succ = FUN_00146100((bodyCollisionProfile *)pwVar1);
    if (succ == 0) {
      FUN_0001b4c0((int)bodyy);
      avatar::destroy(&pwVar1->avatar);
    }
    else {
      FUN_0001b810(bodyy,0,0);
    }
                    // Calls func8
    state = (*bodyy->vtable->getStandingState)(bodyy);
    actorBody::setState(bodyy,state);
    paVar1 = (act->avatar).keyframeContext;
    if (paVar1 != (KeyframeContext *)0x0) {
      iVar2 = paVar1->kfcAnims->animInstance;
      if (iVar2 != (AnimInstance *)0x0) {
        if (iVar2->currentValuePtr != (CombinedAnimChannel *)0x0) {
          free(iVar2->currentValuePtr);
          iVar2->currentValuePtr = (CombinedAnimChannel *)0x0;
        }
        iVar2->timeRemaining = 0.0;
      }
      paVar1->free = 1;
    }
    return 1;
  }
  return 0;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void dispatchFrightMessageToAvatar(avatar *av)

{
  float scareRadius;
  float in_stack_00000004;
  Message msg;
  
  msg.header.someActor = (actor *)0x0;
  msg.header.msgId = Actor_Fright;
  avatar::getWorldPosition(av,(vec3 *)&msg.header.someActor);
  scareRadius = 60.0;
  if (60.0 < in_stack_00000004) {
    scareRadius = in_stack_00000004;
  }
  ScareActorsWithinScareRadius(scareRadius,&msg,(vec3 *)&msg.header.someActor);
  return;
}



// WARNING: Globals starting with '_' overlap smaller symbols at the same address
// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void runPhysicsCallbackOnAvatar(actorBodyAllocd *allocd,avatar *av,void *someCallback)

{
  Buffer<EDB2_E2> *pBVar1;
  int *piVar2;
  Buffer<EDB2Entry> *pBVar3;
  undefined4 uVar4;
  EDB2Entry *dst;
  int iVar5;
  EDB2Entry *str;
  HeapTableEntry *pHVar6;
  int *piVar7;
  float speed;
  float delta;
  CollisionMask mask;
  
  if (allocd->edb2Buffer != (Buffer<EDB2Entry> *)0x0) {
    FUN_0013ed20(allocd->edb2Buffer);
  }
  if (allocd->field13_0x10 != 0) {
    if (runtime::dx_timer <= 0.0) {
      delta = runtime::DeltaTime * runtime::TimeScale;
    }
    else {
      delta = 0.0;
    }
    speed = 0.0;
    if (av->movementFreezeTimer <= 0.0) {
      speed = av->actionSpeed;
    }
    if ((0.0 < speed * delta) || (allocd->field16_0x1c != 0)) {
      mask = av->collisionMask;
      av->collisionMask = Nothing;
                    // Clear the things that collided this frame?
      if (allocd->edb2Buffer != (Buffer<EDB2Entry> *)0x0) {
        RecalculateEDB2Collisions(allocd->edb2Buffer);
      }
      allocd->useInCollisionCalculations = 1;
      avatar::hitOtherThings(av,allocd,someCallback);
      allocd->useInCollisionCalculations = 0;
      if (allocd->edb2Buffer != (Buffer<EDB2Entry> *)0x0) {
        FUN_0013ee80();
      }
      pBVar1 = allocd->edb2E2Buffer;
      if (pBVar1 != (Buffer<EDB2_E2> *)0x0) {
        piVar2 = pBVar1->tail;
        for (piVar7 = pBVar1->head; piVar7 < piVar2; piVar7 = piVar7 + 1) {
          pBVar3 = allocd->edb2Buffer;
          if (pBVar3 != (Buffer<EDB2Entry> *)0x0) {
            for (dst = pBVar3->head; dst < pBVar3->tail; dst = dst + 1) {
              if (dst->avatar == (avatar *)*piVar7) {
                str = (EDB2Entry *)((int)pBVar3->tail - (uint)pBVar3->valueSize);
                if (dst < str) {
                  memcpy(dst,str,(uint)pBVar3->valueSize);
                }
                pBVar3->tail = (EDB2Entry *)((int)pBVar3->tail - (uint)pBVar3->valueSize);
                break;
              }
            }
          }
        }
        pBVar1 = allocd->edb2E2Buffer;
        iVar5 = FindHeapOf(pBVar1);
        uVar4 = runtime::CurrentHeapToAllocateFrom;
        if (g_HeapTableBase[iVar5].heapHandle == (HANDLE)0x0) {
          pHVar6 = (HeapTableEntry *)0x0;
        }
        else {
          pHVar6 = g_HeapTableBase + iVar5;
        }
        runtime::CurrentHeapToAllocateFrom = iVar5;
        XAPILIB::HeapFree(pHVar6->heapHandle,0,pBVar1);
        runtime::CurrentHeapToAllocateFrom = uVar4;
        allocd->edb2E2Buffer = (Buffer<EDB2_E2> *)0x0;
      }
      av->collisionMask = mask;
    }
  }
  return;
}




void actorAllocd::ensureAvatarInAllocd(actorBodyAllocd *allocd,avatar *av)

{
  Buffer<EDB2_E2> *puVar2;
  int *piVar1;
  Buffer<EDB2_E2> *pBVar2;
  
  if (allocd->edb2Buffer != (Buffer<EDB2Entry> *)0x0) {
    if (allocd->useInCollisionCalculations != 0) {
                    // Init buffer if non-existant
      pBVar2 = allocd->edb2E2Buffer;
      if (pBVar2 == (Buffer<EDB2_E2> *)0x0) {
        puVar2 = malloc_(0x20);
        puVar2->head = puVar2->_data;
        puVar2->tail = puVar2->_data;
        puVar2->valueSize = 4;
        puVar2->capacity = 4;
        puVar2->end = (int *)(puVar2 + 1);
        allocd->edb2E2Buffer = puVar2;
      }
      else {
        for (piVar1 = pBVar2->head; piVar1 < pBVar2->tail; piVar1 = piVar1 + 1) {
          if ((avatar *)*piVar1 == av) {
            return;
          }
        }
      }
      pBVar2 = allocd->edb2E2Buffer;
      if (pBVar2->tail == pBVar2->end) {
        pBVar2 = (Buffer<EDB2_E2> *)runtime::ExtendArray((Buffer *)pBVar2);
        allocd->edb2E2Buffer = pBVar2;
      }
      piVar1 = pBVar2->tail;
      pBVar2->tail = (int *)((uint)pBVar2->valueSize + (int)piVar1);
      *piVar1 = (int)av;
      return;
    }
    Buffer<EDB2Entry>::addAvatarToSet(allocd->edb2Buffer,av);
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void BreakWeapon(void)

{
  int iVar1;
  int unaff_ESI;
  
  if (*(char *)(unaff_ESI + 0xdaf) == '\0') {
    FUN_0003fb80();
    iVar1 = FUN_00040040(unaff_ESI);
    if ((iVar1 != 0) && (*(int *)(unaff_ESI + 0xd94) == *(int *)(unaff_ESI + 0x28c))) {
      FUN_00145820();
      return;
    }
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names


int getWeaponWieldType_(actor *act,weapon *wpn)

{
  objTag *poVar1;
  int i;
  
  poVar1 = (objTag *)&wpn->field_0x948;
  i = 0;
  if (0 < wpn->numHitboxes) {
    do {
      if (*poVar1 == (act->avatar).tag) {
        return (int)(short)poVar1[1];
      }
      poVar1 = poVar1 + 8;
      i = i + 1;
    } while (i < wpn->numHitboxes);
  }
  return -1;
}




void LoadWeaponStatTables(void)

{
  Asset *res;
  uint uVar1;
  Asset *local_4;
  
  Assets::GetResourceBytes("aid_misc_ghoulies_weapon_stattable",&local_4);
  res = local_4;
  if (local_4 == (Asset *)0x0) {
    runtime::ExitGame(2);
  }
  Assets::MiscGhouliesWeaponStattable = res;
  uVar1 = XSoundbankResource::GetResourceSize((XSoundbankResource *)res);
  DAT_005461f8 = uVar1 / 0x44;
  Assets::GetResourceBytes("aid_loctext_ghoulies_weapon_weaponstattable",&local_4);
  if (local_4 == (Asset *)0x0) {
    runtime::ExitGame(2);
  }
  Assets::LoctextGhouliesWeaponStatTable = local_4;
  return;
}




void FUN_00157f10(ndHeader *param_1,int transformIndex)

{
  uint uVar1;
  D3DXMATRIX *pOut;
  int iVar2;
  char **ppcVar3;
  D3DXMATRIX *pDVar4;
  D3DXMATRIX local_40;
  ushort bone;
  
  uVar1 = Graphics::DisplayMatrixIndex;
  pOut = &(&Graphics::DisplayMatrices)[Graphics::DisplayMatrixIndex].projMatrix;
  if (((uint)param_1[1].subresName & 0xf) == 2) {
    bone = *(ushort *)((int)&param_1[1].subresName + 2);
    FUN_00156a30(BigBlock_004370a0.bones + bone,BigBlock_004370a0.boneTransforms + bone,&local_40);
  }
  else {
    iVar2 = 0x10;
    if ((*(byte *)((int)param_1->varDataOffset + transformIndex + 4) & 1) == 0) {
      ppcVar3 = (char **)&param_1[1].nd_type;
    }
    else {
      ppcVar3 = (char **)((int)param_1->varDataOffset + transformIndex + 8);
    }
    pDVar4 = &local_40;
    for (; iVar2 != 0; iVar2 = iVar2 + -1) {
      pDVar4->m[0][0] = (float)*ppcVar3;
      ppcVar3 = ppcVar3 + 1;
      pDVar4 = (D3DXMATRIX *)((int)pDVar4 + 4);
    }
  }
  D3DX8::D3DXMatrixMultiply
            (&(&Graphics::DisplayMatrices)[uVar1].worldMat,&local_40,
             &(&Graphics::DisplayMatrices)[uVar1].worldMat);
  D3DX8::D3DXMatrixMultiply
            (pOut,&(&Graphics::DisplayMatrices)[uVar1].worldMat,
             (&Graphics::DisplayMatrices)[uVar1].viewMatrix);
  FUN_00156540(pOut);
  return;
}



// WARNING: Inlined function: getCallbackTable


undefined4 SpawnReaperDefault(void)

{
  undefined4 *puVar1;
  undefined4 in_EAX;
  short sVar2;
  undefined2 in_SS;
  undefined4 *puVar3;
  
  sVar2 = (short)&stack0x00000000 + -4;
  puVar3 = (undefined4 *)CONCAT22((short)((uint)&stack0x00000000 >> 0x10),sVar2);
  puVar1 = (undefined4 *)segment(in_SS,sVar2);
  *puVar1 = in_EAX;
  puVar3[-1] = 0;
  puVar3[-2] = 0;
  puVar3[-3] = 0x436e99;
  EventLoop::SpawnGrimReaper();
  return *puVar3;
}


/*
Unable to decompile 'FUN_0045f400'
Cause: 
Low-level Error: Flow exceeded maximum allowable instructions
*/


