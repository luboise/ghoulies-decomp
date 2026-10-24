/* marker.c - Spawn/scene markers */
#include "marker.h"

void Marker::Handler::Handler4(Marker *param_1)

{
  uint16_t markerId;
  float fVar1;
  Marker *pMVar2;
  Marker *marker;
  int iVar3;
  uint uVar4;
  uint uVar5;
  int iVar6;
  vec3 rot;
  vec3 pos;
  
  uVar5 = (Game::GameState.markerInstance)->numMarkers;
  marker = (Game::GameState.markerInstance)->marker;
  uVar4 = 0;
  if (uVar5 != 0) {
    pMVar2 = marker;
    do {
      if (pMVar2->id == param_1->id) {
        markerId = pMVar2->runtimeId;
        if (markerId != 0) {
          GetPosByIndex(markerId,&pos);
          getEulersByIndex(markerId,&rot);
          goto LAB_000ff54c;
        }
        break;
      }
      uVar4 = uVar4 + 1;
      pMVar2 = (Marker *)((int)&pMVar2->size + pMVar2->size);
    } while (uVar4 < uVar5);
  }
  pos.z = 0.0;
  pos.y = 0.0;
  pos.x = 0.0;
  rot.z = 0.0;
  rot.y = 0.0;
  rot.x = 0.0;
LAB_000ff54c:
  fVar1 = param_1[0xd].eulerRot.z;
  if ((fVar1 != 0.0) && (param_1->runtimeId != 0)) {
    uVar4 = 0;
    if (uVar5 != 0) {
      do {
        if (marker->id == param_1->runtimeId) goto LAB_000ff578;
        uVar4 = uVar4 + 1;
        marker = (Marker *)((int)&marker->size + marker->size);
      } while (uVar4 < uVar5);
    }
    marker = (Marker *)0x0;
LAB_000ff578:
    if (marker->runtimeId != 0) {
      iVar6 = 1;
      goto LAB_000ff5ab;
    }
  }
  iVar6 = 0;
LAB_000ff5ab:
  iVar3._0_2_ = param_1[4].runtimeId;
  iVar3._2_2_ = param_1[4].field4_0xa;
  iVar3 = FUN_001349e0((param_1[10].eulerRot.x != 1.6458793e+19) - 1 & (uint)&param_1[10].eulerRot,
                       (param_1[7].pos.y != 1.6458793e+19) - 1 & (uint)&param_1[7].pos.y,
                       &param_1->pos,&param_1->eulerRot,param_1->scale,param_1 + 1,
                       (iVar3 != 0x5f646961) - 1 & (uint)&param_1[4].runtimeId,fVar1,
                       SUB42(param_1[0xd].scale,0),&pos,&rot,&param_1[0xe].markerType,iVar6,
                       param_1->id);
  if ((iVar3 != 0) && (iVar6 != 0)) {
    marker = (Game::GameState.markerInstance)->marker;
    uVar5 = 0;
    if ((Game::GameState.markerInstance)->numMarkers != 0) {
      do {
        if (marker->id == param_1->runtimeId) goto LAB_000ff667;
        uVar5 = uVar5 + 1;
        marker = (Marker *)((int)&marker->size + marker->size);
      } while (uVar5 < (Game::GameState.markerInstance)->numMarkers);
    }
    marker = (Marker *)0x0;
LAB_000ff667:
    avatarSetupBasic::spawnFromMarker(marker->runtimeId,iVar3);
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void Marker::Handler::Handler3(int param_1)

{
  char *animAID;
  char cVar1;
  int iVar2;
  int iVar3;
  int *piVar4;
  char *pcVar5;
  obj *av;
  KFCParams local_3e4;
  avatarParams local_334;
  
  avatarParams::init(&local_334);
  local_334.pos.x = *(float *)(param_1 + 0xc);
  local_334.impactId._2_2_ = *(undefined2 *)(param_1 + 6);
  local_334.ghoulyboxId2 = *(ushort *)(param_1 + 8);
  local_334.pos.y = *(float *)(param_1 + 0x10);
  local_334.pos.z = *(float *)(param_1 + 0x14);
  local_334.rotEuler.x = *(float *)(param_1 + 0x18);
  local_334.rotEuler.y = *(float *)(param_1 + 0x1c);
  local_334.rotEuler.z = *(float *)(param_1 + 0x20);
  piVar4 = (int *)(param_1 + 0x28);
  local_334.scale = *(float *)(param_1 + 0x24);
  local_334.objParams.typeIndex = 2;
  if (*piVar4 == 0x5f646961) {
    iVar2 = 0x28 - (int)piVar4;
    do {
      iVar3 = *piVar4;
      *(char *)((int)&local_334 + iVar2 + (int)piVar4) = (char)iVar3;
      piVar4 = (int *)((int)piVar4 + 1);
    } while ((char)iVar3 != '\0');
  }
  animAID = (char *)(param_1 + 0xa8);
  if (*(int *)(param_1 + 0xa8) == 0x5f646961) {
    pcVar5 = animAID;
    do {
      cVar1 = *pcVar5;
      pcVar5[(int)&local_334 + (0xa8 - (int)animAID)] = cVar1;
      pcVar5 = pcVar5 + 1;
    } while (cVar1 != '\0');
  }
  av = Assets::CreateEntityFromParams(&local_334.objParams);
  if ((av != (obj *)0x0) &&
     (pcVar5 = (char *)(param_1 + 0x128), *(int *)(param_1 + 0x128) == 0x5f646961)) {
    local_3e4.playbackSpeed_ = 0.0;
    local_3e4.someFloat = 0.0;
    local_3e4.MixP = 0x4d697850;
    local_3e4.someIdOrCount = 0x21;
    local_3e4.length = 0.2;
    local_3e4.someFloat3 = -10.0;
    local_3e4.someUshort = 0;
    local_3e4.someValue4 = 0x31;
    local_3e4.someFloat2 = 0.2;
    local_3e4.animEventAID[0] = '\0';
    local_3e4.someValue5 = (void *)0x0;
    local_3e4.animResource = (AnimResource *)0x0;
    local_3e4.animEvent = (AnimEventResource *)0x0;
    iVar2 = 0x24 - (int)pcVar5;
    do {
      cVar1 = *pcVar5;
      pcVar5[(int)&local_3e4 + iVar2] = cVar1;
      pcVar5 = pcVar5 + 1;
    } while (cVar1 != '\0');
    avatar::setKFFromAnimAID(av,&local_3e4,0,animAID);
  }
  return;
}




void Marker::Handler::Handler19(int param_1)

{
  if (*(int *)(param_1 + 0x28) == 0) {
    DAT_00545ad0 = *(undefined4 *)(param_1 + 0xc);
    DAT_00545ae4 = *(undefined4 *)(param_1 + 0x20);
    DAT_00545adc = 0.0 - *(float *)(param_1 + 0x18);
    DAT_00545ae0 = *(float *)(param_1 + 0x1c) + 3.1415927;
    DAT_00545ad4 = *(undefined4 *)(param_1 + 0x10);
    DAT_00545ad8 = *(undefined4 *)(param_1 + 0x14);
    DAT_00545ae8 = 1;
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void Marker::Handler::FxEmitter(int param_1)

{
  char cVar1;
  int iVar2;
  char *pcVar3;
  objParams local_c8;
  undefined4 local_c0;
  undefined4 local_bc;
  undefined4 local_b8;
  undefined4 local_b4;
  undefined4 local_b0;
  undefined4 local_ac;
  undefined4 local_a8;
  undefined4 local_a4;
  undefined4 local_a0;
  char local_9c [128];
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  undefined4 local_8;
  undefined4 local_4;
  
  pcVar3 = (char *)(param_1 + 0x28);
  if (*(int *)(param_1 + 0x28) == 0x5f646961) {
    local_c8.objInitValue = 0;
    local_c8.paramsSize = 200;
    local_c8.typeIndex = 0x97;
    iVar2 = -(int)pcVar3;
    do {
      cVar1 = *pcVar3;
      pcVar3[(int)(local_9c + iVar2)] = cVar1;
      pcVar3 = pcVar3 + 1;
    } while (cVar1 != '\0');
    local_1c = *(undefined4 *)(param_1 + 0xb0);
    local_18 = *(undefined4 *)(param_1 + 0xb4);
    local_14 = *(undefined4 *)(param_1 + 0xb8);
    local_10 = *(undefined4 *)(param_1 + 0xbc);
    local_a0 = *(undefined4 *)(param_1 + 0xac);
    local_c0 = *(undefined4 *)(param_1 + 0xc);
    local_bc = *(undefined4 *)(param_1 + 0x10);
    local_b8 = *(undefined4 *)(param_1 + 0x14);
    local_b4 = *(undefined4 *)(param_1 + 0x18);
    local_b0 = *(undefined4 *)(param_1 + 0x1c);
    local_ac = *(undefined4 *)(param_1 + 0x20);
    local_a4 = *(undefined4 *)(param_1 + 0xa8);
    local_a8 = *(undefined4 *)(param_1 + 0x24);
    local_c = *(undefined4 *)(param_1 + 0xc0);
    local_8 = *(undefined4 *)(param_1 + 0xc4);
    local_4 = *(undefined4 *)(param_1 + 200);
    Assets::CreateEntityFromParams(&local_c8);
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void Marker::Handler::Handler24(int param_1)

{
  background_0x934_conflict3 pEVar1;
  int iVar2;
  undefined2 uVar3;
  undefined1 *sal;
  undefined1 local_20;
  undefined1 local_1f;
  undefined1 local_1e;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  undefined4 local_8;
  undefined4 local_4;
  
  pEVar1 = Game::SceneInfo.backgrounds.head;
  if (Game::SceneInfo.backgrounds.head != (background_0x934_conflict3)0x0) {
    local_1c = *(undefined4 *)(param_1 + 0xc);
    local_c = *(undefined4 *)(param_1 + 0x28);
    local_18 = *(undefined4 *)(param_1 + 0x10);
    local_14 = *(undefined4 *)(param_1 + 0x14);
    local_10 = 0;
    local_8 = 0;
    local_4 = *(undefined4 *)(param_1 + 0x2c);
    sal = &local_20;
    uVar3 = 0;
    local_20 = 4;
    local_1f = 0x20;
    local_1e = 1;
    iVar2 = FUN_00110bf0(param_1 + 0xc,-1,0);
    ::actor::createActor0x68((actor *)ADJ(pEVar1),3,(char)iVar2,uVar3,sal);
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void Marker::Handler::Handler11(int param_1)

{
  char cVar1;
  int iVar2;
  obj *poVar3;
  int *piVar4;
  char *pcVar5;
  int iVar6;
  char *pcVar7;
  undefined4 local_770;
  char local_76c [128];
  char local_6ec [128];
  undefined4 local_66c;
  objParams local_668 [204];
  
  pcVar5 = (char *)(param_1 + 0xcc);
  piVar4 = (int *)(param_1 + 0x4c);
  FUN_0006a010(*(undefined2 *)(param_1 + 6),*(undefined2 *)(param_1 + 8),
               *(undefined4 *)(param_1 + 0x28),*(undefined4 *)(param_1 + 0x2c),
               *(undefined4 *)(param_1 + 0x30),*(undefined2 *)(param_1 + 0x34),param_1 + 0x14c,
               *(undefined4 *)(param_1 + 0x38),*(undefined4 *)(param_1 + 0x3c),piVar4,pcVar5,
               (float)*(int *)(param_1 + 0x40) * 0.01,*(undefined4 *)(param_1 + 0x44),
               (float)*(int *)(param_1 + 0x48) * 0.01,*(undefined4 *)(param_1 + 0x34c));
  poVar3 = Assets::CreateEntityFromParams(local_668);
  if (((poVar3 != (obj *)0x0) && ((float)*(int *)(param_1 + 0x40) == 0.0)) &&
     (*piVar4 == 0x5f646961)) {
    pcVar7 = local_76c;
    for (iVar6 = 0x41; iVar6 != 0; iVar6 = iVar6 + -1) {
      pcVar7[0] = '\0';
      pcVar7[1] = '\0';
      pcVar7[2] = '\0';
      pcVar7[3] = '\0';
      pcVar7 = pcVar7 + 4;
    }
    local_770 = 0xa8;
    iVar6 = -(int)piVar4;
    do {
      iVar2 = *piVar4;
      (local_76c + iVar6)[(int)piVar4] = (char)iVar2;
      piVar4 = (int *)((int)piVar4 + 1);
    } while ((char)iVar2 != '\0');
    iVar6 = -(int)pcVar5;
    do {
      cVar1 = *pcVar5;
      pcVar5[(int)(local_6ec + iVar6)] = cVar1;
      pcVar5 = pcVar5 + 1;
    } while (cVar1 != '\0');
    local_66c = 0;
    (*poVar3->vtable->onMessage)(poVar3,&local_770);
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void Marker::Handler::BgBreak(BgBreakMarker *marker)

{
  entityAvatarGhoulySetupBgBreakParams local_460;
  
  entityAvatarGhoulySetupBgBreakParams::ctor
            (&local_460,&(marker->marker).eulerRot,marker->ghoulyBoxAid,&(marker->marker).pos,
             (marker->marker).id,(marker->marker).runtimeId,(short)marker->field1_0x28,
             (short)(marker->field1_0x28 >> 0x10),marker->actorAttribsAid,marker->short1,
             (float)marker->someValDiv100_1 * 0.01,marker->otherNumSomething,
             (float)marker->someValDiv100_2 * 0.01,*(undefined4 *)&marker->field_0x13c,
             *(undefined4 *)&marker->field_0x140,*(undefined4 *)&marker->field_0x14c,
             *(undefined4 *)&marker->field_0x150,*(undefined4 *)&marker->field_0x154,
             *(undefined4 *)&marker->field_0x158);
  *(undefined4 *)&marker->field_0x144 = 0;
  *(undefined4 *)&marker->field_0x148 = 0;
  Assets::CreateEntityFromParams((objParams *)&local_460);
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void Marker::Handler::Handler15(Marker *param_1)

{
  objParams *params;
  entityAvatarGhoulieSetupCutsceneParams local_3c4;
  
  FUN_0006ba70(&local_3c4,&param_1[1].runtimeId,&param_1->pos,&param_1->eulerRot,param_1->id,
               param_1->runtimeId,param_1[1].size,param_1[1].markerType,param_1[4].pos.y,
               param_1[4].pos.z);
  Assets::CreateEntityFromParams(params);
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void Marker::Handler::Handler17(int param_1)

{
  objParams *params;
  
  params = (objParams *)
           FUN_0006c170(*(undefined2 *)(param_1 + 6),*(undefined2 *)(param_1 + 8),
                        *(undefined4 *)(param_1 + 0x28),param_1 + 0xac,
                        (float)*(int *)(param_1 + 300) * 0.01,*(undefined4 *)(param_1 + 0x130),
                        (float)*(int *)(param_1 + 0x134) * 0.01,*(undefined4 *)(param_1 + 0x138));
  Assets::CreateEntityFromParams(params);
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void Marker::Handler::Handler16(int param_1)

{
  objParams *params;
  
  params = (objParams *)
           FUN_0006e110(*(undefined2 *)(param_1 + 6),*(undefined2 *)(param_1 + 8),
                        *(undefined4 *)(param_1 + 0x28),*(undefined4 *)(param_1 + 0x2c),
                        *(undefined4 *)(param_1 + 0x30),*(undefined4 *)(param_1 + 0x34),
                        *(undefined4 *)(param_1 + 0x38));
  Assets::CreateEntityFromParams(params);
  return;
}




void Marker::Handler::Player(Marker *param_1)

{
  int iVar1;
  actor *paVar2;
  BOOL BVar3;
  vec3 local_18;
  vec3 local_c;
  
  iVar1._0_2_ = param_1[1].markerType;
  iVar1._2_2_ = param_1[1].id;
  if ((iVar1 == 0) ||
     (((((DAT_005462fc == 0 || (g_finishedLoading_ == 1)) || ((*SomeAS15->flags & 8) != 0)) ||
       ((g_globalFlagset & 0x200000) != 0)) && ((iVar1 == 0 || ((short)param_1[1].size == 0)))))) {
    if ((*(short *)((int)&param_1[1].size + 2) == 0) ||
       (((g_finishedLoading_ != 1 && ((*SomeAS15->flags & 8) == 0)) &&
        ((g_globalFlagset & 0x200000) == 0)))) {
      local_c.x = (param_1->pos).x;
      local_c.y = (param_1->pos).y;
      local_c.z = (param_1->pos).z;
      local_18.x = (param_1->eulerRot).x;
      local_18.y = (param_1->eulerRot).y;
      local_18.z = (param_1->eulerRot).z;
    }
    else {
      overridePosAndRot(param_1,&local_c,&local_18);
    }
    paVar2 = spawnPlayerAtLocationAndRotation(&local_18,(char *)0x0,&local_c);
    if ((paVar2 != (actor *)0x0) && (*(short *)((int)&param_1[1].size + 2) != 0)) {
      BVar3 = EventLoop::IsPlayStateSomething();
      if (BVar3 == 0) {
                    // Should set drone action
        FUN_000fffd0(&local_18,paVar2,param_1);
      }
    }
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void Marker::overridePosAndRot(Marker *param_1,vec3 *param_2,vec3 *param_3)

{
  uint uVar1;
  MarkerInstance *pMVar2;
  Marker *pMVar3;
  uint uVar4;
  
  pMVar2 = Game::GameState.markerInstance;
  if (param_1->runtimeId == 0) {
    param_2->x = (param_1->pos).x;
    param_2->y = (param_1->pos).y;
    param_2->z = (param_1->pos).z;
    param_3->x = (param_1->eulerRot).x;
    param_3->y = (param_1->eulerRot).y;
    param_3->z = (param_1->eulerRot).z;
    return;
  }
  do {
    uVar1 = pMVar2->numMarkers;
    uVar4 = 0;
    pMVar3 = pMVar2->marker;
    if (uVar1 != 0) {
      do {
        if (pMVar3->id == param_1->runtimeId) goto LAB_00100140;
        pMVar3 = (Marker *)((int)&pMVar3->size + pMVar3->size);
        uVar4 = uVar4 + 1;
      } while (uVar4 < uVar1);
    }
    pMVar3 = (Marker *)0x0;
LAB_00100140:
    param_2->x = (pMVar3->pos).x;
    param_2->y = (pMVar3->pos).y;
    param_2->z = (pMVar3->pos).z;
    param_3->x = (pMVar3->eulerRot).x;
    param_3->y = (pMVar3->eulerRot).y;
    param_3->z = (pMVar3->eulerRot).z;
    param_1 = pMVar3;
    if (pMVar3->runtimeId == 0) {
      return;
    }
  } while( true );
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void Marker::Handler::Powerup(Marker *param_1)

{
  ushort uVar1;
  powerupParams *params;
  
  params = (powerupParams *)Assets::GetObjParams((char *)(param_1 + 1));
  if (params != (powerupParams *)0x0) {
    (params->params).pos.x = (param_1->pos).x;
    (params->params).pos.y = (param_1->pos).y;
    (params->params).pos.z = (param_1->pos).z;
    (params->params).rotEuler.x = (param_1->eulerRot).x;
    (params->params).rotEuler.y = (param_1->eulerRot).y;
    (params->params).rotEuler.z = (param_1->eulerRot).z;
    (params->params).scale = param_1->scale;
    uVar1 = param_1->runtimeId;
    *(uint16_t *)((int)&(params->params).impactId + 2) = param_1->id;
    (params->params).ghoulyboxId2 = uVar1;
    Assets::CreateEntityFromParams((objParams *)params);
    free(params);
    return;
  }
  return;
}




void Marker::Handler::Handler8(Marker *param_1)

{
  undefined4 uVar1;
  int iVar2;
  float fVar3;
  
  Events::GetIndexOfStringInTable(0xe9,ActorTagTable + 1,(char *)&param_1[1].runtimeId);
  uVar1._0_2_ = param_1[3].markerType;
  uVar1._2_2_ = param_1[3].id;
  iVar2._0_2_ = param_1[1].markerType;
  iVar2._2_2_ = param_1[1].id;
  fVar3 = (float)iVar2;
  iVar2 = FUN_001246a0(0,(char)param_1[1].size,param_1->id,param_1[2].eulerRot.z,param_1[2].scale,
                       param_1[3].size,uVar1);
  *(float *)(iVar2 + 0x20) = (param_1->pos).x;
  *(float *)(iVar2 + 0x24) = (param_1->pos).y;
  *(float *)(iVar2 + 0x28) = (param_1->pos).z;
  *(float *)(iVar2 + 0x2c) = fVar3;
  *(float *)(iVar2 + 0x30) = fVar3 * fVar3;
  return;
}




void Marker::Handler::Handler20(int param_1)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  Events::GetIndexOfStringInTable(0xe9,ActorTagTable + 1,(char *)(param_1 + 0x34));
  uVar1 = *(undefined4 *)(param_1 + 0x1c);
  iVar2 = *(int *)(param_1 + 0x30);
  iVar3 = *(int *)(param_1 + 0x2c);
  iVar4 = FUN_001246a0(1,*(undefined1 *)(param_1 + 0x28),*(undefined2 *)(param_1 + 6),
                       *(undefined4 *)(param_1 + 0x74),*(undefined4 *)(param_1 + 0x78),
                       *(undefined4 *)(param_1 + 0x7c),*(undefined4 *)(param_1 + 0x80));
  *(undefined4 *)(iVar4 + 0x20) = *(undefined4 *)(param_1 + 0xc);
  *(undefined4 *)(iVar4 + 0x24) = *(undefined4 *)(param_1 + 0x10);
  *(undefined4 *)(iVar4 + 0x28) = *(undefined4 *)(param_1 + 0x14);
  *(float *)(iVar4 + 0x2c) = (float)iVar3;
  *(float *)(iVar4 + 0x30) = (float)iVar2;
  *(undefined4 *)(iVar4 + 0x34) = uVar1;
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void Marker::Handler::ShockObjectHandler(ScareMarker *param_1)

{
  float fVar1;
  uint uVar2;
  undefined2 uVar3;
  undefined2 uVar4;
  undefined2 uVar5;
  undefined2 uVar6;
  undefined2 uVar7;
  undefined2 uVar8;
  undefined2 uVar9;
  undefined4 uVar10;
  objParams *params;
  int iVar11;
  Marker *pMVar12;
  Marker *entry;
  HeapTableEntry *pHVar13;
  uint uVar14;
  uint16_t uVar15;
  float px;
  float py;
  float pz;
  
  params = Assets::GetObjParams(g_shockObjects[param_1->field1_0x28 + 1]);
  entry = (Game::GameState.markerInstance)->marker;
  uVar2 = (Game::GameState.markerInstance)->numMarkers;
  uVar14 = 0;
  if (uVar2 != 0) {
    uVar15 = (param_1->marker).id;
    pMVar12 = entry;
    do {
      if (pMVar12->id == uVar15) {
        if (pMVar12->runtimeId != 0) {
          uVar14 = 0;
          pMVar12 = entry;
          if (uVar2 != 0) goto LAB_00100490;
          goto LAB_0010049d;
        }
        break;
      }
      pMVar12 = (Marker *)((int)&pMVar12->size + pMVar12->size);
      uVar14 = uVar14 + 1;
    } while (uVar14 < uVar2);
  }
  px = (param_1->marker).pos.x;
  py = (param_1->marker).pos.y;
  pz = (param_1->marker).pos.z;
  goto LAB_001003d0;
  while( true ) {
    pMVar12 = (Marker *)((int)&pMVar12->size + pMVar12->size);
    uVar14 = uVar14 + 1;
    if (uVar2 <= uVar14) break;
LAB_00100490:
    if (pMVar12->id == uVar15) {
      uVar15 = pMVar12->runtimeId;
      goto LAB_0010049f;
    }
  }
LAB_0010049d:
  uVar15 = 0;
LAB_0010049f:
  uVar14 = 0;
  if (uVar2 != 0) {
    do {
      if (entry->id == uVar15) goto LAB_001004b8;
      uVar14 = uVar14 + 1;
      entry = (Marker *)((int)&entry->size + entry->size);
    } while (uVar14 < uVar2);
  }
  entry = (Marker *)0x0;
LAB_001004b8:
  px = (entry->pos).x;
  py = (entry->pos).y;
  pz = (entry->pos).z;
LAB_001003d0:
  fVar1 = *(float *)&param_1[1].marker.markerType;
  uVar3 = param_1->field3_0x2e;
  uVar8 = *(undefined2 *)&param_1[1].marker.size;
  uVar9 = *(undefined2 *)((int)&param_1[1].marker.size + 2);
  uVar6 = param_1->playAudio;
  uVar7 = param_1->field7_0x36;
  uVar4 = param_1->field4_0x30;
  uVar5 = param_1->field5_0x32;
  params[0x66].typeIndex = param_1->field2_0x2c;
  params[0x66].field3_0x6 = uVar3;
  params[0x67].paramsSize = uVar4;
  params[0x67].objInitValue = uVar5;
  params[0x67].typeIndex = uVar6;
  params[0x67].field3_0x6 = uVar7;
  params[0x68].paramsSize = uVar8;
  params[0x68].objInitValue = uVar9;
  *(float *)&params[0x68].typeIndex = fVar1 * 0.8;
  *(float *)(params + 0x69) = px;
  *(float *)&params[0x69].typeIndex = py;
  *(float *)(params + 0x6a) = pz;
  *(float *)(params + 1) = (param_1->marker).pos.x;
  *(float *)&params[1].typeIndex = (param_1->marker).pos.y;
  *(float *)(params + 2) = (param_1->marker).pos.z;
  *(float *)&params[2].typeIndex = (param_1->marker).eulerRot.x;
  *(float *)(params + 3) = (param_1->marker).eulerRot.y;
  *(float *)&params[3].typeIndex = (param_1->marker).eulerRot.z;
  *(float *)(params + 4) = (param_1->marker).scale;
  Assets::CreateEntityFromParams(params);
  iVar11 = FindHeapOf(params);
  uVar10 = runtime::CurrentHeapToAllocateFrom;
  if (g_HeapTableBase[iVar11].heapHandle == (HANDLE)0x0) {
    pHVar13 = (HeapTableEntry *)0x0;
  }
  else {
    pHVar13 = g_HeapTableBase + iVar11;
  }
  runtime::CurrentHeapToAllocateFrom = iVar11;
  XAPILIB::HeapFree(pHVar13->heapHandle,0,params);
  runtime::CurrentHeapToAllocateFrom = uVar10;
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void Marker::Handler::Handler7(int param_1)

{
  uint16_t uVar1;
  Marker *pMVar2;
  uint uVar3;
  
  uVar1 = FUN_0011efa0(param_1 + 0xc);
  if (uVar1 != 0) {
    pMVar2 = (Game::GameState.markerInstance)->marker;
    uVar3 = 0;
    if ((Game::GameState.markerInstance)->numMarkers != 0) {
      do {
        if (pMVar2->id == uVar1) {
          if ((pMVar2 != (Marker *)0x0) && (pMVar2->runtimeId == *(uint16_t *)(param_1 + 6))) {
            return;
          }
          break;
        }
        uVar3 = uVar3 + 1;
        pMVar2 = (Marker *)((int)&pMVar2->size + pMVar2->size);
      } while (uVar3 < (Game::GameState.markerInstance)->numMarkers);
    }
  }
  if (*(char *)(param_1 + 0x28) != '\0') {
    FUN_0012a190(param_1 + 0x28);
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void Marker::Handler::Handler20(int param_1)

{
  objParams local_754 [234];
  
  FUN_000725e0(*(undefined4 *)(param_1 + 0x28),*(undefined4 *)(param_1 + 0x2c),
               *(undefined4 *)(param_1 + 0x130),*(undefined4 *)(param_1 + 0x134),param_1 + 0xb0,
               param_1 + 0x138,param_1 + 0x1b8,param_1 + 0x238,param_1 + 0x2b8,param_1 + 0x338,
               param_1 + 0x3b8,*(undefined4 *)(param_1 + 0x438));
  Assets::CreateEntityFromParams(local_754);
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void Marker::Handler::ScaleHandler(ScareMarker *this)

{
  BOOL BVar1;
  uint16_t markerId;
  int iVar2;
  undefined2 uVar3;
  undefined2 uVar4;
  undefined2 uVar5;
  undefined2 uVar6;
  undefined2 uVar7;
  undefined2 uVar8;
  objParams *params;
  Marker *pMVar9;
  entityAvatarMiscScareParams *dropper_blob_params;
  uint uVar10;
  vec3 local_c;
  
  iVar2 = this->field1_0x28;
  if (iVar2 == 0) {
    markerId = (this->marker).runtimeId;
    if (markerId != 0) {
      pMVar9 = (Game::GameState.markerInstance)->marker;
      uVar10 = 0;
      if ((Game::GameState.markerInstance)->numMarkers != 0) {
        do {
          if (pMVar9->id == markerId) {
            GetPosByIndex(markerId,&local_c);
            break;
          }
          uVar10 = uVar10 + 1;
          pMVar9 = (Marker *)((int)&pMVar9->size + pMVar9->size);
        } while (uVar10 < (Game::GameState.markerInstance)->numMarkers);
      }
    }
    dropper_blob_params = (entityAvatarMiscScareParams *)Assets::GetObjParams(g_shockObjects[0xc]);
    BVar1 = *(BOOL *)&this->playAudio;
    uVar5 = this->field4_0x30;
    uVar6 = this->field5_0x32;
    uVar3 = this->field2_0x2c;
    uVar4 = this->field3_0x2e;
    (dropper_blob_params->avatarParams).pos.x = (this->marker).pos.x;
    (dropper_blob_params->avatarParams).pos.y = (this->marker).pos.y;
    (dropper_blob_params->avatarParams).pos.z = (this->marker).pos.z;
    (dropper_blob_params->avatarParams).rotEuler.x = (this->marker).eulerRot.x;
    (dropper_blob_params->avatarParams).rotEuler.y = (this->marker).eulerRot.y;
    (dropper_blob_params->avatarParams).rotEuler.z = (this->marker).eulerRot.z;
    dropper_blob_params->playSilence = BVar1;
    dropper_blob_params->scareParam1 = uVar3;
    dropper_blob_params->scareParam2 = uVar4;
    dropper_blob_params->scareParam3 = uVar5;
    dropper_blob_params->scareParam4 = uVar6;
    *(float *)dropper_blob_params->growAnimationAID = local_c.x;
    *(float *)(dropper_blob_params->growAnimationAID + 4) = local_c.y;
    *(float *)(dropper_blob_params->growAnimationAID + 8) = local_c.z;
    Assets::CreateEntityFromParams((objParams *)dropper_blob_params);
    free(dropper_blob_params);
  }
  else if ((0 < iVar2) && (iVar2 < 5)) {
    params = Assets::GetObjParams(g_shockObjects[iVar2 + 0xc]);
    uVar7 = this->playAudio;
    uVar8 = this->field7_0x36;
    uVar5 = this->field4_0x30;
    uVar6 = this->field5_0x32;
    uVar3 = this->field2_0x2c;
    uVar4 = this->field3_0x2e;
    *(float *)(params + 1) = (this->marker).pos.x;
    *(float *)&params[1].typeIndex = (this->marker).pos.y;
    *(float *)(params + 2) = (this->marker).pos.z;
    *(float *)&params[2].typeIndex = (this->marker).eulerRot.x;
    *(float *)(params + 3) = (this->marker).eulerRot.y;
    *(float *)&params[3].typeIndex = (this->marker).eulerRot.z;
    params[0x66].typeIndex = uVar3;
    params[0x66].field3_0x6 = uVar4;
    params[0x67].paramsSize = uVar5;
    params[0x67].objInitValue = uVar6;
    params[0x67].typeIndex = uVar7;
    params[0x67].field3_0x6 = uVar8;
    Assets::CreateEntityFromParams(params);
    free(params);
    return;
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void Marker::Handler::Handler5(astruct_6 *param_1)

{
  ushort uVar1;
  int iVar2;
  int iVar3;
  undefined2 uVar4;
  undefined2 uVar5;
  undefined2 uVar6;
  undefined2 uVar7;
  undefined2 uVar8;
  objParams *params;
  Marker *pMVar9;
  uint uVar10;
  float fVar11;
  
  params = Assets::GetObjParams(&param_1->field_0x28);
  if (params == (objParams *)0x0) {
    return;
  }
  uVar4 = *(undefined2 *)((int)&param_1->field10_0xc + 2);
  fVar11 = param_1->field16_0x24 * *(float *)(params + 4);
  params[1].paramsSize = *(undefined2 *)&param_1->field10_0xc;
  params[1].objInitValue = uVar4;
  uVar4 = *(undefined2 *)((int)&param_1->field11_0x10 + 2);
  params[1].typeIndex = *(undefined2 *)&param_1->field11_0x10;
  params[1].field3_0x6 = uVar4;
  uVar4 = *(undefined2 *)((int)&param_1->field12_0x14 + 2);
  params[2].paramsSize = *(undefined2 *)&param_1->field12_0x14;
  params[2].objInitValue = uVar4;
  uVar4 = *(undefined2 *)((int)&param_1->field13_0x18 + 2);
  params[2].typeIndex = *(undefined2 *)&param_1->field13_0x18;
  params[2].field3_0x6 = uVar4;
  uVar4 = *(undefined2 *)((int)&param_1->field14_0x1c + 2);
  params[3].paramsSize = *(undefined2 *)&param_1->field14_0x1c;
  params[3].objInitValue = uVar4;
  uVar4 = *(undefined2 *)((int)&param_1->field15_0x20 + 2);
  params[3].typeIndex = *(undefined2 *)&param_1->field15_0x20;
  params[3].field3_0x6 = uVar4;
  *(float *)(params + 4) = fVar11;
  uVar1 = param_1->field7_0x8;
  params[0x55].objInitValue = param_1->field6_0x6;
  params[0x55].typeIndex = uVar1;
  if (param_1->assetNameAgain == 0x5f646961) {
    FUN_00100770(fVar11);
  }
  if (*(int *)param_1->assetName == 0x5f646961) {
    FUN_00146c80(param_1->field399_0x228);
  }
  uVar5 = *(undefined2 *)&param_1->field404_0x23c;
  uVar6 = *(undefined2 *)((int)&param_1->field404_0x23c + 2);
  iVar2 = param_1->field403_0x238;
  iVar3 = param_1->field401_0x230;
  uVar7 = *(undefined2 *)&param_1->field407_0x248;
  uVar8 = *(undefined2 *)((int)&param_1->field407_0x248 + 2);
  uVar4 = *(undefined2 *)((int)&param_1->field402_0x234 + 2);
  params[0x68].typeIndex = *(undefined2 *)&param_1->field402_0x234;
  params[0x68].field3_0x6 = uVar4;
  params[0x69].typeIndex = uVar5;
  params[0x69].field3_0x6 = uVar6;
  params[0x6a].paramsSize = uVar7;
  params[0x6a].objInitValue = uVar8;
  *(float *)(params + 0x69) = (float)iVar2 * 0.01;
  *(float *)(params + 0x68) = (float)iVar3 * 0.01;
  uVar4 = *(undefined2 *)((int)&param_1->field405_0x240 + 2);
  params[0x8d].paramsSize = *(undefined2 *)&param_1->field405_0x240;
  params[0x8d].objInitValue = uVar4;
  uVar4 = *(undefined2 *)((int)&param_1->field406_0x244 + 2);
  params[0x8d].typeIndex = *(undefined2 *)&param_1->field406_0x244;
  params[0x8d].field3_0x6 = uVar4;
  uVar4 = *(undefined2 *)((int)&param_1->field416_0x254 + 2);
  params[0xae].typeIndex = *(undefined2 *)&param_1->field416_0x254;
  params[0xae].field3_0x6 = uVar4;
  uVar4 = *(undefined2 *)((int)&param_1->field400_0x22c + 2);
  params[0x8e].paramsSize = *(undefined2 *)&param_1->field400_0x22c;
  params[0x8e].objInitValue = uVar4;
  if (param_1->field7_0x8 != 0) {
    pMVar9 = (Game::GameState.markerInstance)->marker;
    uVar10 = 0;
    if ((Game::GameState.markerInstance)->numMarkers != 0) {
      do {
        if (pMVar9->id == param_1->field7_0x8) {
          if ((pMVar9 != (Marker *)0x0) && (pMVar9->markerType == 7)) {
            FUN_00146cc0();
          }
          break;
        }
        uVar10 = uVar10 + 1;
        pMVar9 = (Marker *)((int)&pMVar9->size + pMVar9->size);
      } while (uVar10 < (Game::GameState.markerInstance)->numMarkers);
    }
  }
  Assets::CreateEntityFromParams(params);
  free(params);
  return;
}




Marker * Marker::getMarkerById(uint16_t id)

{
  Marker *pMVar1;
  uint uVar2;
  
  pMVar1 = (Game::GameState.markerInstance)->marker;
  uVar2 = 0;
  if ((Game::GameState.markerInstance)->numMarkers != 0) {
    do {
      if (pMVar1->id == id) {
        return pMVar1;
      }
      uVar2 = uVar2 + 1;
      pMVar1 = (Marker *)((int)&pMVar1->size + pMVar1->size);
    } while (uVar2 < (Game::GameState.markerInstance)->numMarkers);
  }
  return (Marker *)0x0;
}




int Marker::getCountOfMarkerType(MarkerType param_1)

{
  ushort uVar1;
  int iVar2;
  
  uVar1 = nextIdOfNextMarkerOfType(param_1,1,0);
  if (uVar1 == 0) {
    return 0;
  }
                    // Linear search
  iVar2 = 1;
  for (uVar1 = nextIdOfNextMarkerOfType(param_1,0,uVar1); uVar1 != 0;
      uVar1 = nextIdOfNextMarkerOfType(param_1,0,uVar1)) {
    iVar2 = iVar2 + 1;
  }
  return iVar2;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


uint16_t Marker::getFurthestMarkerFromPoint(MarkerType markerType,vec3 *param_2)

{
  Marker *pMVar1;
  uint uVar2;
  uint16_t uVar3;
  uint16_t markerId;
  int num_markers;
  Marker *pMVar4;
  uint uVar5;
  int iVar6;
  int iVar7;
  float fVar8;
  float fVar9;
  float fVar10;
  float furthest;
  float local_c;
  float local_8;
  float local_4;
  
  furthest = -1e+09;
  uVar3 = 0;
  num_markers = getCountOfMarkerType(markerType);
  iVar6 = 0;
  if (num_markers < 1) {
    return 0;
  }
  uVar2 = (Game::GameState.markerInstance)->numMarkers;
  pMVar1 = (Game::GameState.markerInstance)->marker;
  do {
    markerId = nextIdOfNextMarkerOfType(markerType,1,0);
    iVar7 = iVar6;
    if (0 < iVar6) {
      do {
        markerId = nextIdOfNextMarkerOfType(markerType,1,markerId);
        iVar7 = iVar7 + -1;
      } while (iVar7 != 0);
    }
    uVar5 = 0;
    pMVar4 = pMVar1;
    if (uVar2 != 0) {
      do {
        if (pMVar4->id == markerId) {
          local_c = (pMVar4->pos).x;
          local_8 = (pMVar4->pos).y;
          local_4 = (pMVar4->pos).z;
          break;
        }
        pMVar4 = (Marker *)((int)&pMVar4->size + pMVar4->size);
        uVar5 = uVar5 + 1;
      } while (uVar5 < uVar2);
    }
    fVar10 = param_2->y - local_8;
    fVar8 = param_2->z - local_4;
    fVar9 = param_2->x - local_c;
    fVar8 = fVar8 * fVar8 + fVar10 * fVar10 + fVar9 * fVar9;
    if (furthest < fVar8) {
      furthest = fVar8;
      uVar3 = markerId;
    }
    iVar6 = iVar6 + 1;
    if (num_markers <= iVar6) {
      return uVar3;
    }
  } while( true );
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


ushort Marker::nextIdOfNextMarkerOfType(MarkerType markerType,BOOL performFullCheck,short markerId)

{
  Marker *markerr;
  Marker *next_marker;
  uint next_marker_unchecked;
  Marker *marker;
  uint num_markers;
  
  num_markers = (Game::GameState.markerInstance)->numMarkers;
  marker = (Game::GameState.markerInstance)->marker;
  next_marker_unchecked = 0;
  markerr = marker;
  if (num_markers != 0) {
    do {
      if (markerr->id == markerId) goto LAB_0011f1f9;
      next_marker_unchecked = next_marker_unchecked + 1;
      markerr = (Marker *)((int)&markerr->size + markerr->size);
    } while (next_marker_unchecked < num_markers);
  }
  if ((num_markers == 0) || (markerr = marker, marker == (Marker *)0x0)) {
    return 0;
  }
LAB_0011f1f9:
  if (markerType == Any) {
    markerType = markerr->markerType;
  }
  next_marker = markerr;
  do {
                    // Bounds check for next marker instead of just assuming there will be one there
    next_marker_unchecked = (int)&next_marker->size + next_marker->size;
    next_marker = (Marker *)
                  (-(uint)(next_marker_unchecked - (int)Game::GameState.markerInstance <
                          (Game::GameState.markerInstance)->end) & next_marker_unchecked);
    if (next_marker == (Marker *)0x0) {
      if (performFullCheck == 0) {
        return 0;
      }
      next_marker = (Marker *)(-(uint)(num_markers != 0) & (uint)marker);
    }
    if (next_marker->markerType == markerType) goto LAB_0011f244;
  } while (next_marker != markerr);
  if (next_marker->markerType != markerType) {
    return 0;
  }
LAB_0011f244:
  return next_marker->id;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void Marker::GetPosByIndex(uint16_t markerId,vec3 *outPos)

{
  Marker *pMVar1;
  uint uVar2;
  
  pMVar1 = (Game::GameState.markerInstance)->marker;
  uVar2 = 0;
  if ((Game::GameState.markerInstance)->numMarkers != 0) {
    while (pMVar1->id != markerId) {
      uVar2 = uVar2 + 1;
      pMVar1 = (Marker *)((int)&pMVar1->size + pMVar1->size);
      if ((Game::GameState.markerInstance)->numMarkers <= uVar2) {
        return;
      }
    }
    outPos->x = (pMVar1->pos).x;
    outPos->y = (pMVar1->pos).y;
    outPos->z = (pMVar1->pos).z;
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void Marker::getEulersByIndex(uint16_t param_1,vec3 *eulers)

{
  Marker *pMVar1;
  uint uVar2;
  
  pMVar1 = (Game::GameState.markerInstance)->marker;
  uVar2 = 0;
  if ((Game::GameState.markerInstance)->numMarkers != 0) {
    while (pMVar1->id != param_1) {
      uVar2 = uVar2 + 1;
      pMVar1 = (Marker *)((int)&pMVar1->size + pMVar1->size);
      if ((Game::GameState.markerInstance)->numMarkers <= uVar2) {
        return;
      }
    }
    eulers->x = (pMVar1->eulerRot).x;
    eulers->y = (pMVar1->eulerRot).y;
    eulers->z = (pMVar1->eulerRot).z;
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


uint Marker::GetSmth(uint16_t index)

{
  Marker *pMVar1;
  uint uVar2;
  
  pMVar1 = (Game::GameState.markerInstance)->marker;
  uVar2 = 0;
  if ((Game::GameState.markerInstance)->numMarkers != 0) {
    do {
      if (pMVar1->id == index) {
        return CONCAT22((short)((uint)pMVar1 >> 0x10),pMVar1->runtimeId);
      }
      uVar2 = uVar2 + 1;
      pMVar1 = (Marker *)((int)&pMVar1->size + pMVar1->size);
    } while (uVar2 < (Game::GameState.markerInstance)->numMarkers);
  }
  return (uint)pMVar1 & 0xffff0000;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


DerivedMarkerValue * Marker::getByID2(uint16_t id2)

{
  DerivedMarkerValue *uVar1;
  uint16_t uVar2;
  Marker *marker;
  uint i;
  
  if (DAT_00512344 == 0) {
    return (DerivedMarkerValue *)0x0;
  }
  uVar1 = *(DerivedMarkerValue **)(DAT_00512344 + 4);
  if (uVar1 < *(DerivedMarkerValue **)(DAT_00512344 + 8)) {
    do {
      i = 0;
      if ((Game::GameState.markerInstance)->numMarkers != 0) {
        marker = (Game::GameState.markerInstance)->marker;
        do {
          if (marker->id == uVar1->id) {
            uVar2 = marker->runtimeId;
            goto LAB_00124841;
          }
          marker = (Marker *)((int)&marker->size + marker->size);
          i = i + 1;
        } while (i < (Game::GameState.markerInstance)->numMarkers);
      }
      uVar2 = 0;
LAB_00124841:
      if (uVar2 == id2) {
        return uVar1;
      }
      uVar1 = uVar1 + 1;
    } while (uVar1 < *(DerivedMarkerValue **)(DAT_00512344 + 8));
  }
  return (DerivedMarkerValue *)0x0;
}




