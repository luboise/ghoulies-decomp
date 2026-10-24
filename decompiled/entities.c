/* entities.c - Avatar & strategy entity subclasses */
#include "entities.h"

void switchD_000d4179::EmptyFunction(void)

{
  return;
}




void entityAvatarGhoulySetupBasic::getAllocDetails(undefined4 *param_1)

{
  *param_1 = 0xc6c;
  param_1[1] = 0x65c;
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void entityAvatarGhoulySetupBasic::getVTable(void)

{
  avatar::initVTable(&vtable);
  vtable.getAllocDetails = getAllocDetails;
  vtable.ctor = ctor;
  vtable.dtor = dtor;
  vtable.onMessage = onMessage;
  vtable.update = update;
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields

undefined4
entityAvatarGhoulySetupBasic::ctor
          (entityAvatarGhoulySetupBasic *setup,entityAvatarGhoulySetupBasicParams *params)

{
  char cVar1;
  AvatarVTable *pAVar2;
  weapon *pwVar3;
  int iVar4;
  char *pcVar5;
  
  pAVar2 = *(AvatarVTable **)&params->field_0x334;
  if (pAVar2 != (AvatarVTable *)0x0) {
    if (g_weapons->tail == g_weapons->end) {
      g_weapons = (Buffer<weapon> *)runtime::ExtendArray((Buffer *)g_weapons);
    }
    pwVar3 = g_weapons->tail;
    g_weapons->tail = (weapon *)((int)&(pwVar3->avatar).vtable + (uint)g_weapons->valueSize);
    (pwVar3->avatar).vtable = pAVar2;
    *(entityAvatarGhoulySetupBasic **)&(pwVar3->avatar).field_0x4 = setup;
  }
  *(undefined4 *)&setup->field_0x934 = *(undefined4 *)&params->field_0x338;
  *(undefined4 *)&setup->field_0x938 = *(undefined4 *)&params->field_0x33c;
  *(undefined2 *)&setup->field_0x93c = *(undefined2 *)&params->field_0x340;
  FUN_000280d0((undefined4 *)&params->field_0x342,(int)&setup->field_0x93e);
  *(undefined4 *)&setup->field_0xb40 = 0;
  *(undefined4 *)&setup->field_0xb48 = *(undefined4 *)&params->field_0x544;
  *(undefined4 *)&setup->field_0xb4c = *(undefined4 *)&params->field_0x548;
  runtime::rand = runtime::rand * 0x19660d + 0x3c6ef35f;
  if ((float)(runtime::rand & 0x7fffff | 0x3f800000) - 1.0 <= *(float *)&params->field_0x64c) {
    pcVar5 = &params->field_0x54c;
    iVar4 = 0xb50 - (int)pcVar5;
    do {
      cVar1 = *pcVar5;
      pcVar5[(int)setup + iVar4] = cVar1;
      pcVar5 = pcVar5 + 1;
    } while (cVar1 != '\0');
    pcVar5 = &params->field_0x5cc;
    iVar4 = 0xbd0 - (int)pcVar5;
    do {
      cVar1 = *pcVar5;
      pcVar5[(int)setup + iVar4] = cVar1;
      pcVar5 = pcVar5 + 1;
    } while (cVar1 != '\0');
    *(undefined4 *)&setup->field_0xc50 = *(undefined4 *)&params->field_0x650;
    *(undefined4 *)&setup->field_0xc54 = *(undefined4 *)&params->field_0x654;
  }
  *(undefined4 *)&setup->field_0xc58 = *(undefined4 *)&params->field_0x658;
  return 1;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void entityAvatarGhoulySetupBasic::dtor(entityAvatarGhoulySetupBasic *param_1)

{
  FUN_0012aca0();
  if (param_1->ghoulyBox != (GhoulyBox *)0x0) {
    GhoulyBox::dtor(param_1->ghoulyBox);
    param_1->ghoulyBox = (GhoulyBox *)0x0;
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void entityAvatarGhoulySetupBasic::update(entityAvatarGhoulySetupBasic *setup)

{
  char cVar1;
  GhoulyBox *pGVar2;
  int iVar3;
  char *pcVar4;
  vec3 local_11c;
  undefined4 local_110;
  char local_10c [128];
  char local_8c [136];
  
  avatar::getWorldPosition(&setup->avatar,&local_11c);
  iVar3 = FUN_0013e980(*(undefined4 *)&setup->field_0xc54);
  if (iVar3 == 1) {
    pcVar4 = local_10c;
    for (iVar3 = 0x41; iVar3 != 0; iVar3 = iVar3 + -1) {
      pcVar4[0] = '\0';
      pcVar4[1] = '\0';
      pcVar4[2] = '\0';
      pcVar4[3] = '\0';
      pcVar4 = pcVar4 + 4;
    }
    pcVar4 = &setup->field_0xb50;
    local_110 = 0xa8;
    iVar3 = -(int)pcVar4;
    do {
      cVar1 = *pcVar4;
      pcVar4[(int)(local_10c + iVar3)] = cVar1;
      pcVar4 = pcVar4 + 1;
    } while (cVar1 != '\0');
    pcVar4 = &setup->field_0xbd0;
    iVar3 = -(int)pcVar4;
    do {
      cVar1 = *pcVar4;
      pcVar4[(int)(local_8c + iVar3)] = cVar1;
      pcVar4 = pcVar4 + 1;
    } while (cVar1 != '\0');
    (*((setup->avatar).vtable)->onMessage)(setup,&local_110);
    *(undefined4 *)&setup->field_0xc50 = 0;
    *(undefined4 *)&setup->field_0xc54 = 0;
  }
  pGVar2 = setup->ghoulyBox;
  if ((pGVar2 != (GhoulyBox *)0x0) && (pGVar2->field3_0xc == 0)) {
    GhoulyBox::dtor(pGVar2);
    setup->ghoulyBox = (GhoulyBox *)0x0;
  }
  return;
}



// WARNING: Variable defined which should be unmapped: param_3
// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void entityAvatarGhoulySetupBgBreak::onBgBreak(entityAvatarGhoulySetupBgBreak *param_1)

{
  Marker *pMVar1;
  uint uVar2;
  int iVar3;
  ushort markerId;
  int num_markers;
  BgBreakMarker *pMVar4;
  uint uVar4;
  int i;
  int iVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  
  num_markers = Marker::getCountOfMarkerType(BgBreak);
  fVar9 = 0.0;
  i = 0;
  fVar7 = 0.0;
  fVar6 = 0.0;
  if (0 < num_markers) {
    fVar8 = 1.0;
    uVar2 = (Game::GameState.markerInstance)->numMarkers;
    pMVar1 = (Game::GameState.markerInstance)->marker;
    iVar3 = *(int *)&param_1->field_0xa44;
    do {
      markerId = Marker::nextIdOfNextMarkerOfType(BgBreak,1,0);
      iVar5 = i;
      if (0 < i) {
        do {
          markerId = Marker::nextIdOfNextMarkerOfType(BgBreak,1,markerId);
          iVar5 = iVar5 + -1;
        } while (iVar5 != 0);
      }
      uVar4 = 0;
      pMVar4 = (BgBreakMarker *)pMVar1;
      if (uVar2 != 0) {
        do {
          if ((pMVar4->marker).id == markerId) goto LAB_0006a1ff;
          uVar4 = uVar4 + 1;
          pMVar4 = (BgBreakMarker *)(pMVar4->ghoulyBoxAid + ((pMVar4->marker).size - 0x2c));
        } while (uVar4 < uVar2);
      }
      pMVar4 = (BgBreakMarker *)0x0;
LAB_0006a1ff:
      if (*(int *)&pMVar4->field_0x140 == iVar3) {
        if (*(int *)&pMVar4->field_0x144 != 0) goto LAB_0006a2a6;
        if (*(int *)&pMVar4->field_0x148 == 0) {
          fVar7 = fVar7 + fVar8;
        }
        fVar6 = fVar6 + fVar8;
      }
      i = i + 1;
    } while (i < num_markers);
    if (fVar7 != fVar9) {
      runtime::rand = runtime::rand * 0x19660d + 0x3c6ef35f;
      if (((float)(runtime::rand & 0x7fffff | 0x3f800000) - fVar8 <=
           ((fVar6 - fVar7) + fVar8) / fVar6) && (*(int *)param_1->randGhoulyBoxAID == 0x5f646961))
      {
        FUN_0006b0a0();
        FUN_0006a310();
      }
LAB_0006a2a6:
      FUN_0006a2c0();
    }
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void entityAvatarGhoulySetupBgBreak::getAllocDetails(undefined4 *param_1)

{
  *param_1 = 0xa7c;
  param_1[1] = 0x460;
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void entityAvatarGhoulySetupBgBreak::getVTable(void)

{
  avatar::initVTable(&vtable);
  vtable.getAllocDetails = getAllocDetails;
  vtable.ctor = ctor;
  vtable.dtor = &LAB_0006a600;
  vtable.onMessage = FUN_0006a7b0;
  vtable.update = update;
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields

undefined4
entityAvatarGhoulySetupBgBreak::ctor
          (entityAvatarGhoulySetupBgBreak *bgBreak,entityAvatarGhoulySetupBgBreakParams *params)

{
  AvatarVTable *pAVar1;
  weapon *pwVar2;
  
  pAVar1 = *(AvatarVTable **)&params->field_0x334;
  if (pAVar1 != (AvatarVTable *)0x0) {
    if (g_weapons->tail == g_weapons->end) {
      g_weapons = (Buffer<weapon> *)runtime::ExtendArray((Buffer *)g_weapons);
    }
    pwVar2 = g_weapons->tail;
    g_weapons->tail = (weapon *)((int)&(pwVar2->avatar).vtable + (uint)g_weapons->valueSize);
    (pwVar2->avatar).vtable = pAVar1;
    *(entityAvatarGhoulySetupBgBreak **)&(pwVar2->avatar).field_0x4 = bgBreak;
  }
  if (params->alwaysUseBox == 0) {
    setupRandChance1(bgBreak,params);
  }
  else {
    copyBoxAIDAndActorAttribsAID(bgBreak,params);
  }
  *(undefined2 *)&bgBreak->field_0xa34 = *(undefined2 *)&params->field_0x438;
  *(undefined4 *)&bgBreak->field_0xa48 = 0;
  *(undefined4 *)&bgBreak->field_0xa50 = 0;
  *(undefined4 *)&bgBreak->field_0xa54 = 0;
  *(undefined4 *)&bgBreak->field_0xa58 = 0xffffffff;
  *(undefined4 *)&bgBreak->field_0xa5c = *(undefined4 *)&params->field_0x450;
  *(undefined4 *)&bgBreak->field_0xa60 = *(undefined4 *)&params->field_0x454;
  *(undefined4 *)&bgBreak->field_0xa64 = *(undefined4 *)&params->field_0x458;
  FUN_0006af20(bgBreak);
  *(undefined4 *)&bgBreak->field_0xa68 = *(undefined4 *)&params->field_0x45c;
  return 1;
}




void entityAvatarGhoulySetupBgBreak::update(entityAvatarGhoulySetupBgBreak *param_1)

{
  void *pvVar1;
  
  avatar::update((avatar *)param_1);
  if (*(int *)&param_1->field_0xa40 == 0) {
    FUN_0006a3f0(param_1);
  }
  pvVar1 = *(void **)&param_1->field_0xa4c;
  if ((pvVar1 != (void *)0x0) && (*(int *)((int)pvVar1 + 0xc) == 0)) {
    GhoulyBox::dtor(pvVar1);
    *(undefined4 *)&param_1->field_0xa4c = 0;
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void entityAvatarGhoulieSetupCutscene::getAllocDetails(undefined4 *param_1)

{
  *param_1 = 0x9dc;
  param_1[1] = 0x3c4;
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void entityAvatarGhoulieSetupCutscene::getVTable(void)

{
  avatar::initVTable(&vtable);
  vtable.getAllocDetails = getAllocDetails;
  vtable.ctor = ctor;
  vtable.dtor = dtor;
  vtable.onMessage = onMessage;
  vtable.update = update;
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields

undefined4
entityAvatarGhoulieSetupCutscene::ctor
          (entityAvatarGhoulieSetupCutscene *setup,entityAvatarGhoulieSetupCutsceneParams *params)

{
  char *pcVar1;
  SoundSourceImpl *pSVar2;
  short sVar3;
  AvatarVTable *pAVar4;
  weapon *pwVar5;
  uint uVar6;
  int iVar7;
  IXACT_Cue *cue;
  Cutscene *pCVar8;
  int iVar9;
  char cVar10;
  
  pAVar4 = *(AvatarVTable **)&params->field_0x334;
  if (pAVar4 != (AvatarVTable *)0x0) {
    if (g_weapons->tail == g_weapons->end) {
      g_weapons = (Buffer<weapon> *)runtime::ExtendArray((Buffer *)g_weapons);
    }
    pwVar5 = g_weapons->tail;
    g_weapons->tail = (weapon *)((int)&(pwVar5->avatar).vtable + (uint)g_weapons->valueSize);
    (pwVar5->avatar).vtable = pAVar4;
    *(entityAvatarGhoulieSetupCutscene **)&(pwVar5->avatar).field_0x4 = setup;
  }
  *(undefined2 *)&setup->field_0x934 = *(undefined2 *)&params->field_0x338;
  *(undefined4 *)&setup->field_0x938 = *(undefined4 *)&params->field_0x3bc;
  *(undefined4 *)&setup->field_0x93c = *(undefined4 *)&params->field_0x3c0;
  Camera::ctor(&setup->camera,&setup->cameraName,(ProjectionSetBitField)0x0);
  pCVar8 = Assets::LoadCutscene(&params->field_0x33a,2,&setup->camera);
  setup->cutsceneBuffer = pCVar8;
  pCVar8->onEndCallback = &LAB_0006ba60;
  pCVar8->owningScene = (sceneControlObj *)setup;
  pCVar8 = setup->cutsceneBuffer;
  *(undefined4 *)&setup->field_0x9d4 = 0;
  *(undefined4 *)&setup->field_0x9d0 = 0;
  cVar10 = '\0';
  pCVar8->field18_0x158 = pCVar8->field18_0x158 + 1;
  if (0 < (int)pCVar8->numAnims) {
    iVar9 = 0;
    do {
      uVar6 = pCVar8->animAllocsPtr[iVar9].id_;
      if (uVar6 != 0) {
        if ((*(int *)&pCVar8->animAllocsPtr[iVar9].field_0xc != 0) &&
           (iVar9 = *(int *)(uVar6 + 0x50), iVar9 != 0)) {
          iVar7 = *(int *)(*(int *)(iVar9 + 0x58) + 0x28);
          if (iVar7 != 0) {
            pcVar1 = (char *)(iVar7 + 0x125);
            *pcVar1 = *pcVar1 + '\x01';
          }
          *(undefined4 *)(iVar9 + 0x5c) = 1;
        }
        iVar9 = *(int *)(uVar6 + 0x50);
        if (iVar9 != 0) {
          if (**(int **)(iVar9 + 0x58) != 0) {
            pcVar1 = (char *)(**(int **)(iVar9 + 0x58) + 0x125);
            *pcVar1 = *pcVar1 + '\x01';
          }
          *(undefined4 *)(iVar9 + 0x5c) = 1;
        }
      }
      cVar10 = cVar10 + '\x01';
      iVar9 = (int)cVar10;
    } while (iVar9 < (int)pCVar8->numAnims);
  }
  if ((pCVar8->flags & 0x10) == 0) {
    iVar9 = 0;
    do {
      sVar3 = *(short *)((pCVar8->events).field6_0x6 + iVar9 * 2 + -6);
      if (sVar3 != -1) {
        cue = Audio::SoundSources[sVar3].cue;
        pSVar2 = Audio::SoundSources + sVar3;
        if (cue != (IXACT_Cue *)0x0) {
          switch(pSVar2->state) {
          case ShouldGoTo4_1:
            pSVar2->state = ShouldGoTo4_2;
            break;
          case ShouldPause1:
          case ShouldPause2:
          case ShouldPause3:
            pSVar2->state = ShouldPause3;
            audioSoundBankPauseCue(cue,1);
          }
        }
      }
      iVar9 = iVar9 + 1;
    } while (iVar9 < 3);
  }
  if (*(int *)&setup->field_0x93c != 0) {
    _sprintf(&setup->cameraName,"spawnId%d",*(undefined4 *)&params->field_0x334);
    Camera::AppendAndSelect(&setup->camera,0);
  }
  *(undefined4 *)&setup->field_0x940 = 0;
  *(undefined4 *)&setup->field_0x9d8 = 0;
  return 1;
}




void entityAvatarGhoulieSetupCutscene::dtor(int param_1)

{
  FUN_0012aca0();
  if (*(void **)(param_1 + 0x944) != (void *)0x0) {
    GhoulyBox::dtor(*(void **)(param_1 + 0x944));
    *(undefined4 *)(param_1 + 0x944) = 0;
  }
  if (*(int *)(param_1 + 0x93c) != 0) {
    Camera::setActiveCamera(param_1 + 0x94c);
    return;
  }
  return;
}




void entityAvatarGhoulieSetupCutscene::update(entityAvatarGhoulieSetupCutscene *param_1)

{
  void *pvVar1;
  BOOL BVar2;
  Camera *cameraConfig;
  float fVar3;
  float fVar4;
  
  avatar::update(&param_1->avatar);
  pvVar1 = *(void **)&param_1->field_0x944;
  if ((pvVar1 != (void *)0x0) && (*(int *)((int)pvVar1 + 0xc) == 0)) {
    GhoulyBox::dtor(pvVar1);
    *(undefined4 *)&param_1->field_0x944 = 0;
  }
  if ((*(int *)&param_1->field_0x9d4 != 0) && (param_1->cutsceneBuffer != (Cutscene *)0x0)) {
    if (*(int *)&param_1->field_0x93c == 0) {
      cameraConfig = (Camera *)0x0;
    }
    else {
      cameraConfig = &param_1->camera;
    }
    fVar3 = 0.0;
    if (runtime::dx_timer <= 0.0) {
      fVar4 = runtime::DeltaTime * runtime::TimeScale;
    }
    else {
      fVar4 = 0.0;
    }
    if ((param_1->avatar).movementFreezeTimer <= 0.0) {
      fVar3 = (param_1->avatar).actionSpeed;
    }
    BVar2 = RuncutsceneAndShouldEnd(fVar3 * fVar4,param_1->cutsceneBuffer,cameraConfig);
    if (BVar2 != 0) {
      *(undefined4 *)&param_1->field_0x9d0 = 1;
      *(undefined4 *)&param_1->field_0x9d4 = 0;
      if (*(int *)&param_1->field_0x938 == 0) {
        Cutscene::update(param_1->cutsceneBuffer,0.0,-1.0,0);
        CloseDoorAndUpdateState(1,param_1->cutsceneBuffer);
      }
      if (*(int *)&param_1->field_0x93c != 0) {
        Camera::RevertCameraUsingConfig(&param_1->camera);
        return;
      }
    }
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void entityAvatarGhoulySetupSwap::getAllocDetails(undefined4 *param_1)

{
  *param_1 = 0xa54;
  param_1[1] = 0x4c8;
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void entityAvatarGhoulySetupSwap::getVTable(void)

{
  avatar::initVTable(&vtable);
  vtable.getAllocDetails = getAllocDetails;
  vtable.ctor = ctor;
  vtable.dtor = dtor;
  vtable.onMessage = onMessage;
  vtable.update = FUN_0006c0a0;
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields

undefined4
entityAvatarGhoulySetupSwap::ctor
          (entityAvatarGhoulySetupSwap *ava,entityAvatarGhoulySetupSwapParams *params)

{
  char cVar1;
  AvatarVTable *pAVar2;
  weapon *pwVar3;
  int iVar4;
  char *pcVar5;
  
  pAVar2 = *(AvatarVTable **)&params->field_0x334;
  if (pAVar2 != (AvatarVTable *)0x0) {
    if (g_weapons->tail == g_weapons->end) {
      g_weapons = (Buffer<weapon> *)runtime::ExtendArray((Buffer *)g_weapons);
    }
    pwVar3 = g_weapons->tail;
    g_weapons->tail = (weapon *)((int)&(pwVar3->avatar).vtable + (uint)g_weapons->valueSize);
    (pwVar3->avatar).vtable = pAVar2;
    *(entityAvatarGhoulySetupSwap **)&(pwVar3->avatar).field_0x4 = ava;
  }
  *(undefined4 *)&ava->field_0x934 = 0;
  *(undefined4 *)&ava->field_0x93c = 0;
  runtime::rand = runtime::rand * 0x19660d + 0x3c6ef35f;
  if (((float)(runtime::rand & 0x7fffff | 0x3f800000) - 1.0 <= *(float *)&params->field_0x438) &&
     (pcVar5 = &params->field_0x338, *(int *)&params->field_0x338 == 0x5f646961)) {
    iVar4 = 0x944 - (int)pcVar5;
    do {
      cVar1 = *pcVar5;
      pcVar5[(int)ava + iVar4] = cVar1;
      pcVar5 = pcVar5 + 1;
    } while (cVar1 != '\0');
    pcVar5 = &params->field_0x3b8;
    iVar4 = 0x9c4 - (int)pcVar5;
    do {
      cVar1 = *pcVar5;
      pcVar5[(int)ava + iVar4] = cVar1;
      pcVar5 = pcVar5 + 1;
    } while (cVar1 != '\0');
    *(undefined4 *)&ava->field_0xa48 = *(undefined4 *)&params->field_0x43c;
    *(undefined4 *)&ava->field_0xa4c = *(undefined4 *)&params->field_0x440;
  }
  *(undefined4 *)&ava->field_0xa50 = *(undefined4 *)&params->field_0x444;
  return 1;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void entityAvatarGhoulySetupSwap::dtor(entityAvatarGhoulySetupSwap *param_1)

{
  FUN_0012aca0();
  if (*(void **)&param_1->field_0x938 != (void *)0x0) {
    GhoulyBox::dtor(*(void **)&param_1->field_0x938);
    *(undefined4 *)&param_1->field_0x938 = 0;
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void entityAvatarGhoulySetupSwap::onMessage(entityAvatarGhoulySetupSwap *ava,Message *msg)

{
  char cVar1;
  ushort uVar2;
  Message *msg_00;
  actor *act;
  int iVar3;
  GhoulyBox *box;
  actor **ppaVar4;
  vec3 local_30;
  vec3 local_24;
  undefined1 local_18 [24];
  
  msg_00 = msg;
  switch((msg->header).msgId) {
  case Scene_AvatarRemoved:
    if ((msg->header).someActor == *(actor **)&ava->field_0x93c) {
      *(undefined4 *)&ava->field_0x93c = 0;
    }
    if ((msg->header).someActor == *(actor **)&ava->field_0x934) {
      *(undefined4 *)&ava->field_0x934 = 0;
    }
    break;
  case Scene_Begin:
    uVar2 = (ava->avatar).someUshort;
    if (uVar2 != 0) {
      iVar3 = Game::OnSceneBegin(uVar2);
      *(int *)&ava->field_0x934 = iVar3;
    }
    avatar::getWorldPosition(&ava->avatar,&local_30);
    iVar3 = FUN_00129f00(&ava->avatar);
    if (iVar3 == 0) {
      iVar3 = FUN_00129d70(&local_30,0,&msg,4);
    }
    *(int *)&ava->field_0x93c = iVar3;
    break;
  case Scene_CutsceneAlloc:
  case Scene_CutsceneFree:
  case Scene_End:
  case Scene_EventBegin:
  case Scene_EventComplete:
  case Scene_EventEnd:
  case Scene_EventFailed:
  case Scene_LookAtRemoved:
  case Scene_PowerupActivated:
  case Scene_PowerupDeactivated:
  case Scene_Prepare:
  case Scene_Sfx_Started:
  case Scene_Sfx_Finished:
  case Scene_Sfx_UpdatePos:
  case Scene_Sfx_UpdateDir:
  case Scene_TargetRemoved:
  case Scene_SuperScaryStateChange:
  case Scene_WeaponDestroyed:
  case Scoreboard_HeartBeat:
  case Weapon_Attached:
  case Weapon_AttackVolumeEnabled:
  case Weapon_ArcContact:
  case Weapon_AwaitingPickup:
  case Weapon_BobAttach:
  case Weapon_BounceToDestination:
  case Weapon_Drop:
  case Weapon_EscapedBackground:
  case Weapon_GetProjectileAid:
  case Weapon_IsRecoilType:
  case Weapon_Place:
  case Weapon_PostDetach:
  case Weapon_PreDetach:
  case Weapon_PushOutDelta:
  case Weapon_QueryAim:
  case Weapon_Scooped:
  case Weapon_SetStreamStrength:
  case Weapon_ShootBegin:
  case Weapon_ShootEnd:
  case Weapon_SpawnedActor:
  case Weapon_ThrowAt:
    break;
  case Ghouly_GetDroneToPosition:
    avatar::getWorldPosition(*(avatar **)&ava->field_0x93c,(vec3 *)(msg + 4));
    avatar::getWorldRotation(*(avatar **)&ava->field_0x93c,(vec3 *)&msg_00[5].header.someActor);
    msg_00[7].header.msgId = General_Activate;
    break;
  case Ghouly_InsertFromAid:
    iVar3 = FUN_00146150();
    if (iVar3 == 0) {
      msg_00[0x40].header.someActor = (actor *)0xfffffffe;
    }
    else {
      iVar3 = FUN_0006bca0(ava,local_18,&local_24,&local_30);
      if (iVar3 != 0) {
        act = FUN_001348f0((char *)((msg_00[0x30].header.someActor != (actor *)0x5f646961) - 1 &
                                   (uint)&msg_00[0x30].header.someActor),
                           (char *)((uint)&msg_00[0x10].header.someActor &
                                   (msg_00[0x10].header.someActor != (actor *)0x5f646961) - 1),
                           &local_24,&local_30,(char *)&(msg_00->header).someActor,(char *)0x0,
                           (char *)0x0,
                           (char *)((uint)&msg_00[0x20].header.someActor &
                                   (msg_00[0x20].header.someActor != (actor *)0x5f646961) - 1));
        msg_00[0x40].header.someActor = (actor *)(uint)(act != (actor *)0x0);
        if (act != (actor *)0x0) {
          g_globalFlagset = g_globalFlagset | 2;
          avatar::destroy(*(avatar **)&ava->field_0x93c);
          *(undefined4 *)&ava->field_0x940 = 1;
        }
      }
    }
    break;
  case Ghouly_OpenBoxFromAid:
    if (((*(int *)&ava->field_0x93c != 0) && (iVar3 = FUN_00146150(), iVar3 != 0)) &&
       (*(int *)&ava->field_0x938 == 0)) {
      box = GhoulyBox::fromAID((char *)&(msg_00->header).someActor);
      *(GhoulyBox **)&ava->field_0x938 = box;
      if (box != (GhoulyBox *)0x0) {
        ppaVar4 = &msg_00[0x10].header.someActor;
        box->parentActor = (actor *)ava;
        box->initialised_ = 0;
        if (ppaVar4 != (actor **)0x0) {
          iVar3 = 0x30 - (int)ppaVar4;
          do {
            cVar1 = *(char *)ppaVar4;
            *(char *)((int)box + iVar3 + (int)ppaVar4) = cVar1;
            ppaVar4 = (actor **)((int)ppaVar4 + 1);
          } while (cVar1 != '\0');
        }
        Scripting::AddGhoulySpawnToList(box,&g_ghoulyBoxes);
        msg_00[0x20].header.someActor = (actor *)0x1;
      }
    }
    break;
  default:
    goto switchD_0006be11_default;
  }
switchD_0006be11_default:
  avatar::onMessage(&ava->avatar,msg_00);
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void entityAvatarMiscButtonBat::getAllocDetails(undefined4 *param_1)

{
  *param_1 = 0x958;
  param_1[1] = 0x340;
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void entityAvatarMiscButtonBat::getVTable(void)

{
  avatar::initVTable((AvatarVTable *)vtable);
  vtable[0] = (uint)getAllocDetails;
  vtable[1] = (uint)ctor;
  vtable[2] = (uint)switchD_000d4179::EmptyFunction;
  vtable[3] = (uint)onMessage;
  vtable[4] = (uint)update;
  vtable[5] = (uint)FUN_0006d6c0;
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields

void entityAvatarMiscButtonBat::ctor
               (entityAvatarMiscButtonBat *param_1,entityAvatarMiscButtonBatParams *params)

{
  AnimEventMapping *pAVar1;
  
  param_1->field4_0x940 = (params->screenPos).x;
  param_1->field5_0x944 = (params->screenPos).y;
  param_1->field8_0x950 = (params->screenPos).x;
  param_1->field9_0x954 = (params->screenPos).y;
  param_1->field6_0x948 = (params->screenPos).x;
  param_1->field7_0x94c = (params->screenPos).y;
  param_1->field3_0x93c = params->speedMaybe;
  if ((param_1->avatar).animTable != (AnimtableResource *)0x0) {
    pAVar1 = avatar::getAnimEventByName(&param_1->avatar,"stand",0);
    if (pAVar1 != (AnimEventMapping *)0x0) {
      avatar::activateAnimation(&param_1->avatar,pAVar1);
    }
  }
  param_1->someTimer = 4.5;
  param_1->field8_0x950 = param_1->field6_0x948;
  param_1->field9_0x954 = param_1->field7_0x94c;
  param_1->field4_0x940 = param_1->field6_0x948;
  param_1->field5_0x944 = param_1->field7_0x94c;
  param_1->state = Idle;
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void entityAvatarMiscButtonBat::update(entityAvatarMiscButtonBat *bat)

{
  BOOL timer_ended;
  AnimEventMapping *pAVar1;
  BOOL animation_ended;
  vec3 pos;
  
  avatar::update(&bat->avatar);
  pos.x = (Graphics::CurrentCameraStruct->forwards).x * 5.0 + (Graphics::CurrentCameraStruct->pos).x
  ;
  pos.y = (Graphics::CurrentCameraStruct->forwards).y * 5.0 + (Graphics::CurrentCameraStruct->pos).y
  ;
  pos.z = (Graphics::CurrentCameraStruct->forwards).z * 5.0 + (Graphics::CurrentCameraStruct->pos).z
  ;
  avatar::setPosition(&bat->avatar,&pos);
  switch(bat->state) {
  case Idle:
    timer_ended = avatar::decreaseTimer(&bat->avatar,&bat->someTimer);
    if (timer_ended != 0) {
      if (((bat->avatar).animTable != (AnimtableResource *)0x0) &&
         (pAVar1 = avatar::getAnimEventByName(&bat->avatar,"hop",0),
         pAVar1 != (AnimEventMapping *)0x0)) {
        avatar::activateAnimation(&bat->avatar,pAVar1);
      }
      bat->state = Hopping;
      return;
    }
    break;
  case FlyBetween:
  case Hopping:
  case Doh:
    animation_ended = avatar::updateKeyframes(&bat->avatar,0);
                    // React to input
    if (animation_ended != 0) {
      setState(bat,Idle);
    }
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void entityAvatarMiscButtonBat::onMessage(entityAvatarMiscButtonBat *bat,Message *msg)

{
  avatar::onMessage(&bat->avatar,msg);
  if ((msg->header).msgId == Avatar_DrawListAdd) {
    avatar::onDrawListAdd(&bat->avatar);
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void entityAvatarMiscButtonBat::setState(entityAvatarMiscButtonBat *bat,MenuBatState newState)

{
  AnimEventMapping *pAVar1;
  char *anim_name;
  
  switch(newState) {
  case Idle:
    if (((bat->avatar).animTable != (AnimtableResource *)0x0) &&
       (pAVar1 = avatar::getAnimEventByName(&bat->avatar,"stand",0),
       pAVar1 != (AnimEventMapping *)0x0)) {
      avatar::activateAnimation(&bat->avatar,pAVar1);
    }
    bat->someTimer = 4.5;
    bat->field8_0x950 = bat->field6_0x948;
    bat->field9_0x954 = bat->field7_0x94c;
    bat->field4_0x940 = bat->field6_0x948;
    bat->field5_0x944 = bat->field7_0x94c;
    bat->state = newState;
    return;
  case FlyBetween:
    if (((bat->avatar).animTable != (AnimtableResource *)0x0) &&
       (pAVar1 = avatar::getAnimEventByName(&bat->avatar,"flybetween",0),
       pAVar1 != (AnimEventMapping *)0x0)) {
      avatar::activateAnimation(&bat->avatar,pAVar1);
    }
    if ((bat->avatar).keyframeContext != (KeyframeContext *)0x0) {
      FUN_00030db0();
    }
    if (bat->state == FlyBetween) {
      FUN_0003b2e0();
      bat->state = newState;
      return;
    }
    goto switchD_0006d8dc_default;
  case Hopping:
    if ((bat->avatar).animTable == (AnimtableResource *)0x0) goto switchD_0006d8dc_default;
    anim_name = "hop";
    break;
  case Doh:
    if ((bat->avatar).animTable == (AnimtableResource *)0x0) goto switchD_0006d8dc_default;
    anim_name = "doh";
    break;
  default:
    goto switchD_0006d8dc_default;
  }
  pAVar1 = avatar::getAnimEventByName(&bat->avatar,anim_name,0);
  if (pAVar1 != (AnimEventMapping *)0x0) {
    avatar::activateAnimation(&bat->avatar,pAVar1);
  }
switchD_0006d8dc_default:
  bat->state = newState;
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void entityAvatarMiscDestination::vtable(undefined4 *param_1)

{
  *param_1 = 0x95c;
  param_1[1] = 0x348;
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void entityAvatarMiscDestination::getVTable(void)

{
  avatar::initVTable((AvatarVTable *)vtable);
  vtable[0] = vtable;
  vtable[1] = dtor;
  vtable[2] = switchD_000d4179::EmptyFunction;
  vtable[3] = update;
  return;
}




undefined4 entityAvatarMiscDestination::dtor(int param_1,int param_2)

{
  *(undefined4 *)(param_1 + 0x934) = *(undefined4 *)(param_2 + 0x334);
  *(undefined4 *)(param_1 + 0x938) = *(undefined4 *)(param_2 + 0x338);
  *(undefined4 *)(param_1 + 0x93c) = *(undefined4 *)(param_2 + 0x33c);
  *(undefined4 *)(param_1 + 0x940) = *(undefined4 *)(param_2 + 0x340);
  *(undefined4 *)(param_1 + 0x944) = *(undefined4 *)(param_2 + 0x344);
  *(undefined4 *)(param_1 + 0x958) = 0;
  *(undefined4 *)(param_1 + 0x948) = 0xffffffff;
  *(undefined4 *)(param_1 + 0x94c) = 0xffffffff;
  *(undefined4 *)(param_1 + 0x950) = 0xffffffff;
  *(undefined4 *)(param_1 + 0x954) = 0xffffffff;
  return 1;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void entityAvatarMiscDestination::update(entityAvatarMiscDestination *dest,Message *param_2)

{
  ObjMsgID OVar1;
  
  if ((param_2->header).msgId == Ghouly_GetDroneToPosition) {
    OVar1 = FUN_0006ddf0(dest,param_2[3].header.someActor == (actor *)0x0,
                         &param_2[5].header.someActor);
    param_2[7].header.msgId = OVar1;
  }
  avatar::onMessage(&dest->avatar,param_2);
  return;
}




void entityAvatarMiscProp::getAllocDetails(undefined4 *param_1)

{
  *param_1 = 0x940;
  param_1[1] = 0x334;
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void entityAvatarMiscProp::getVTable(void)

{
  avatar::initVTable((AvatarVTable *)g_avatarVTable);
  g_avatarVTable[0] = getAllocDetails;
  g_avatarVTable[1] = ctor;
  g_avatarVTable[2] = dtor;
  g_avatarVTable[3] = onMessage;
  g_avatarVTable[4] = updateFixed_;
  g_avatarVTable[5] = avatar::draw;
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


undefined4 entityAvatarMiscProp::ctor(entityAvatarMiscProp *param_1)

{
  CollisionMask CVar1;
  
  CVar1 = avatar::getCollisionMaskFromModel(&param_1->avatar);
  param_1->someFlag1 = CVar1 & Mask0x1;
  param_1->someFlag2 = CVar1 & Mask0x1;
  return 1;
}




void entityAvatarMiscProp::dtor(int param_1)

{
  if (*(int *)(param_1 + 0x934) != 0) {
    FUN_0013ee80();
    free(*(void **)(param_1 + 0x934));
    *(undefined4 *)(param_1 + 0x934) = 0;
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void entityAvatarMiscProp::updateFixed_(entityAvatarMiscProp *param_1)

{
  avatar::update(&param_1->avatar);
  if (param_1->someFlag2 != 0) {
    if (*(int *)&param_1->field_0x934 != 0) {
      FUN_0013ed20(*(int *)&param_1->field_0x934);
      FUN_0013eb60();
    }
    FUN_0013eeb0(param_1,&param_1->field_0x934);
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void entityAvatarMiscProp::onMessage(entityAvatarMiscProp *param_1,Message *param_2)

{
  ObjMsgID OVar1;
  
  avatar::onMessage(&param_1->avatar,param_2);
  OVar1 = (param_2->header).msgId;
  if (OVar1 == Avatar_HitsDisable) {
    param_1->someFlag2 = 0;
  }
  else {
    if (OVar1 == Avatar_HitsEnable) {
      param_1->someFlag2 = 1;
      return;
    }
    if ((OVar1 == Scene_AvatarRemoved) && (param_1->someFlag2 != 0)) {
      FUN_0013f110();
      return;
    }
  }
  return;
}



// WARNING: Globals starting with '_' overlap smaller symbols at the same address


void entityAvatarMiscScare::getVTable(void)

{
  avatar::initVTable(&vtable);
  vtable.getAllocDetails = (getAllocDetailsFn *)&LAB_0006fca0;
  vtable.ctor = ctor;
  vtable.dtor = FUN_0006ff20;
  vtable.onMessage = entityAvatarFxBurnup::onMessage;
  vtable.update = update;
  vtable.draw = FUN_000702c0;
  vtable.func6 = obj::returnOne;
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields

undefined4

entityAvatarMiscScare::ctor(entityAvatarMiscScare *this,entityAvatarMiscScareParams *params)

{
  char cVar1;
  int iVar2;
  char *pcVar3;
  KeyframeContext *kfc;
  undefined4 uVar4;
  uint uVar5;
  AnimResource *pAVar6;
  KFCParams local_b0;
  
  pcVar3 = params->fxEmitterAID;
  iVar2 = 0x954 - (int)pcVar3;
  do {
    cVar1 = *pcVar3;
    pcVar3[(int)this + iVar2] = cVar1;
    pcVar3 = pcVar3 + 1;
  } while (cVar1 != '\0');
  this->playerScareTimer = 0.0;
  local_b0.playbackSpeed_ = 0.0;
  local_b0.someFloat = 0.0;
  pcVar3 = params->growAnimationEventsAID;
  *(undefined4 *)&this->field_0x934 = 1;
  *(undefined4 *)&this->field_0x938 = 3;
  local_b0.MixP = 0x4d697850;
  local_b0.someIdOrCount = 0x21;
  local_b0.length = 0.2;
  local_b0.someFloat3 = -10.0;
  local_b0.someValue4 = 0x31;
  local_b0.someFloat2 = 0.2;
  local_b0.animEventAID[0] = '\0';
  local_b0.someValue5 = (void *)0x0;
  local_b0.animResource = (AnimResource *)0x0;
  local_b0.animEvent = (AnimEventResource *)0x0;
  iVar2 = 0x24 - (int)pcVar3;
  do {
    cVar1 = *pcVar3;
    pcVar3[(int)&local_b0 + iVar2] = cVar1;
    pcVar3 = pcVar3 + 1;
  } while (cVar1 != '\0');
  local_b0.someUshort = 1;
  if ((this->avatar).keyframeContext == (KeyframeContext *)0x0) {
    kfc = KeyframeContext::ctor(4);
    (this->avatar).keyframeContext = kfc;
    kfc->animEventCallback = avatar::triggerAnimationEvent;
    kfc->avatar = &this->avatar;
  }
  if (local_b0.animResource == (AnimResource *)0x0) {
    pAVar6 = (AnimResource *)0x0;
    pcVar3 = params->growAnimationAID;
  }
  else {
    pcVar3 = (char *)0x0;
    pAVar6 = local_b0.animResource;
  }
  KeyframeContext::setFromAnimName((this->avatar).keyframeContext,0,&local_b0,pcVar3,pAVar6);
  if ((this->avatar).keyframeContext != (KeyframeContext *)0x0) {
    FUN_00030db0();
  }
  uVar4 = Graphics::SetShaderParamFromAvatar(&this->avatar,"shader_lambert3","colour0");
  *(undefined4 *)&this->field_0x940 = uVar4;
  this->playSilence = params->playSilence;
  this->playingSilence = 0;
  if ((Game::SceneInfo.playerActors.prev == (actor_0x93c_conflict5)0x0) ||
     (Game::SceneInfo.playerActors.prev == (actor_0x93c_conflict5)0x93c)) {
    uVar5 = 0;
  }
  else {
    uVar5 = (*(byte *)((int)&ADJ(Game::SceneInfo.playerActors.prev)->body->flagSet->flags->
                             attackFlags_ + 1) & 0x10) >> 4;
  }
  *(uint *)&this->field_0x944 = uVar5;
  g_globalFlagset = g_globalFlagset | Flag1;
  *(undefined4 *)&this->field_0x948 = 0;
  if (this->playSilence != 0) {
    Audio::PlayOrChangeByName(4,"XACT_SILENCE");
    this->playingSilence = 1;
  }
  return 1;
}




void entityAvatarMiscScare::update(entityAvatarMiscScare *this)

{
  undefined1 *puVar1;
  byte bVar2;
  KeyframeContext *pKVar3;
  AnimInstance *pAVar4;
  int iVar5;
  entityAvatarMiscScare *av;
  uint uVar6;
  bool bVar7;
  float10 extraout_ST0;
  float10 fVar8;
  float scareDistance;
  float fVar9;
  float fVar10;
  uint64_t uVar11;
  vec3 vStack_c;
  
  av = this;
  avatar::update(&this->avatar);
  pKVar3 = (av->avatar).keyframeContext;
  if (pKVar3 == (KeyframeContext *)0x0) {
    scareDistance = 0.0;
  }
  else {
    pAVar4 = pKVar3->kfcAnims->animInstance;
    if (pAVar4 == (AnimInstance *)0x0) {
      scareDistance = 0.0;
    }
    else {
      scareDistance = pAVar4->t;
    }
  }
  if (*(int *)&av->field_0x940 != 0) {
    scareDistance = scareDistance * 18.849556;
    sin(scareDistance);
    this = (entityAvatarMiscScare *)(float)extraout_ST0;
    bVar2 = *(byte *)(*(int *)&av->field_0x940 + 0x11);
    fVar8 = abs_float((float)this);
    this = (entityAvatarMiscScare *)(uint)bVar2;
    uVar11 = float10::to_uint64_t(((float10)(int)this - (float10)1.0) * fVar8);
    uVar6 = (uint)uVar11 & 0xff;
    if ((uVar6 != 0xffffffff) && (uVar6 < *(byte *)(*(int *)&av->field_0x940 + 0x11))) {
      *(char *)(*(int *)&av->field_0x940 + 0x13) = (char)uVar11;
    }
  }
  if (*(int *)&av->field_0x934 != 0) {
    if (runtime::dx_timer <= 0.0) {
      scareDistance = runtime::DeltaTime * runtime::TimeScale;
    }
    else {
      scareDistance = 0.0;
    }
    fVar10 = 0.0;
    if ((av->avatar).movementFreezeTimer <= 0.0) {
      fVar10 = (av->avatar).actionSpeed;
    }
    scareDistance = av->playerScareTimer - fVar10 * scareDistance;
    av->playerScareTimer = scareDistance;
    if (scareDistance <= 0.0) {
      scareDistance = scareDistance + 0.5;
      av->playerScareTimer = scareDistance;
      puVar1 = &av->field_0x938;
      *(int *)puVar1 = *(int *)puVar1 + -1;
      if (*(int *)puVar1 == 0) {
        *(undefined4 *)&av->field_0x934 = 0;
      }
    }
  }
  iVar5 = *(int *)&av->field_0x944;
  if ((Game::SceneInfo.playerActors.prev == (actor_0x93c_conflict5)0x0) ||
     (Game::SceneInfo.playerActors.prev == (actor_0x93c_conflict5)0x93c)) {
    uVar6 = 0;
  }
  else {
    uVar6 = *(byte *)((int)&ADJ(Game::SceneInfo.playerActors.prev)->body->flagSet->flags->
                            attackFlags_ + 1) >> 4 & 1;
  }
  *(uint *)&av->field_0x944 = uVar6;
  if ((uVar6 != 0) && (iVar5 == 0)) {
    scareDistance = 0.2;
    av->field22_0x94c = 0.2;
  }
  avatar::updateSkeletonBeforeScare(&av->avatar);
  av->scareDistance = scareDistance;
  avatar::getWorldPosition(&av->avatar,&vStack_c);
  vStack_c.x = vStack_c.x - (Graphics::CurrentCameraStruct->pos).x;
  vStack_c.y = vStack_c.y - (Graphics::CurrentCameraStruct->pos).y;
  vStack_c.z = vStack_c.z - (Graphics::CurrentCameraStruct->pos).z;
  uVar6 = (uint)(SQRT(vStack_c.x * vStack_c.x + vStack_c.y * vStack_c.y + vStack_c.z * vStack_c.z)
                <= av->scareDistance);
  *(uint *)&av->field_0x948 = uVar6;
  if (uVar6 != 0) {
    IdkBigStruct_00504450.field0_0x0 = FLOAT_0042742c;
    IdkBigStruct_00504450.field1_0x4 = FLOAT_0042742c;
    IdkBigStruct_00504450.field2_0x8 = FLOAT_0042742c;
    IdkBigStruct_00504450.field4_0x1c = -1.0;
    IdkBigStruct_00504450.g_float1 = -1.0;
    IdkBigStruct_00504450.field6_0x24 = 1;
  }
  this = (entityAvatarMiscScare *)0x5b;
  ScareActorsWithinScareRadius(av->scareDistance,(Message *)&this,&vStack_c);
  pKVar3 = (av->avatar).keyframeContext;
  if ((pKVar3 == (KeyframeContext *)0x0) ||
     (pAVar4 = pKVar3->kfcAnims->animInstance, pAVar4 == (AnimInstance *)0x0)) goto LAB_00070268;
  scareDistance = pAVar4->t;
  bVar7 = false;
  if (scareDistance != pAVar4->defaultT) {
    if (pAVar4->invDuration <= 0.0 && pAVar4->invDuration != 0.0) {
      fVar10 = pAVar4->defaultT;
      fVar9 = scareDistance;
    }
    else {
      fVar9 = pAVar4->defaultT;
      fVar10 = scareDistance;
    }
    if (fVar10 <= fVar9) {
      if ((fVar9 <= (float)0x3f733333) || (0.95 < fVar10)) goto LAB_0007025b;
      bVar7 = false;
    }
    else if (((float)0x3f733333 < fVar9) || (fVar10 <= 0.95)) {
      bVar7 = false;
    }
    else {
LAB_0007025b:
      bVar7 = true;
    }
  }
  if (bVar7) {
    FUN_000703a0();
  }
LAB_00070268:
  pKVar3 = (av->avatar).keyframeContext;
  if ((pKVar3 != (KeyframeContext *)0x0) &&
     (pAVar4 = pKVar3->kfcAnims->animInstance, pAVar4 != (AnimInstance *)0x0)) {
    bVar7 = false;
    if (pAVar4->loopMode == Mode1) {
      if (pAVar4->invDuration <= 0.0 && pAVar4->invDuration != 0.0) {
        bVar7 = 0.0 < pAVar4->t;
      }
      else {
        bVar7 = pAVar4->t < 1.0;
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
  avatar::destroy(&av->avatar);
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


actorStrategyVTable * entityStrategyBaron::getVTable(void)

{
  actorStrategyVTable_00505d00.getAllocDetails = (getAllocDetailsFn *)&LAB_000a77e0;
  actorStrategyVTable_00505d00.ctor = FUN_000a7850;
  actorStrategyVTable_00505d00.dtor = &LAB_000a7870;
  actorStrategyVTable_00505d00.onMessage = FUN_000a7d30;
  actorStrategyVTable_00505d00.update = FUN_000a7880;
  actorStrategyVTable_00505d00.enterState = (actorStrategyStateChangeCallback *)&DAT_000a80b0;
  actorStrategyVTable_00505d00.leaveState = FUN_000a8590;
  return &actorStrategyVTable_00505d00;
}




entityStrategyBaronPlane::enterState(actorStrategy *param_1,actorStrategyOffsetId param_2)

{
  float fVar1;
  float fVar2;
  actorMind *mind;
  actorBody *paVar3;
  actorBody *extraout_EAX;
  float *pfVar4;
  int iVar5;
  actorBody *extraout_EAX_00;
  actorBody *paVar6;
  
  paVar6 = param_1->parentActor->body;
  mind = param_1->parentActor->mind;
  paVar6->indexInStatsheet = 2;
  param_1->field_0x1a = 0;
  *(undefined4 *)&param_1[4].actorStrategyId2 = 0;
  *(undefined4 *)&param_1[4].field_0x20 = 0;
  switch(param_2) {
  case Null:
    break;
  default:
    paVar6 = (actorBody *)actorStrategy::enterState(param_1,param_2);
    return paVar6;
  case Attack_KnockDown:
    iVar5 = *(int *)&param_1[1].newState_;
    param_1[1].vtable = (actorStrategyVTable *)0x0;
    *(undefined4 *)&param_1[4].actorStrategyId2 = 1;
    *(undefined4 *)&param_1[4].field_0x20 = 1;
    if (iVar5 != 0) {
      *(int *)&param_1[1].newState_ = iVar5 + -1;
    }
    iVar5 = FUN_000a9b20();
    if (iVar5 == 0) {
      if ((paVar6->health < 0x3d) &&
         (paVar6 = param_1->parentActor->body, *(int *)&param_1[1].field_0x30 != 2)) {
        *(undefined4 *)&param_1[1].field_0x30 = 2;
        if ((paVar6->flagSet->flags->attackFlags_ & 0x200000) == Null) {
          FUN_000a8ad0();
        }
        else {
          FUN_000a89c0();
        }
      }
    }
    else {
      if (*(int *)&param_1[1].field_0x30 != 1) {
        *(undefined4 *)&param_1[1].field_0x30 = 1;
        FUN_000a8ad0();
      }
      *(undefined4 *)&param_1[1].field_0x24 = 1;
      *(float *)&param_1[1].field_0x28 = 2.0;
    }
    param_1->parentActor->body->indexInStatsheet = 5;
    param_1->field_0x1a = 1;
    param_1->actorStrategyId2 = Far;
    paVar6 = (actorBody *)actorMind::setGoalFromScript(mind,"attack");
    return paVar6;
  case DroneAction:
    *(undefined4 *)&param_1[4].field_0x20 = 1;
    paVar6 = (actorBody *)actorStrategy::enterState(param_1,param_2);
    return paVar6;
  case Far:
    param_1->parentActor->body->indexInStatsheet = 2;
    actorMind::setGoalFromScript(mind,"waitforstand");
    actorMind::setGoalFromScript(mind,"far");
    iVar5 = FUN_000a9b20();
    if (iVar5 != 0) {
      paVar6 = param_1->parentActor->body;
      if (*(int *)&param_1[1].field_0x30 != 1) {
        *(undefined4 *)&param_1[1].field_0x30 = 1;
        paVar6 = (actorBody *)FUN_000a8ad0();
      }
      *(undefined4 *)&param_1[1].field_0x24 = 1;
      *(undefined4 *)&param_1[4].actorStrategyId2 = 1;
      *(undefined4 *)&param_1[4].field_0x20 = 1;
      return paVar6;
    }
    paVar3 = (actorBody *)0x0;
    if ((paVar6->health < 0x3d) &&
       (paVar3 = param_1->parentActor->body, *(int *)&param_1[1].field_0x30 != 2)) {
      *(undefined4 *)&param_1[1].field_0x30 = 2;
      if ((paVar3->flagSet->flags->attackFlags_ & 0x200000) == Null) {
        paVar3 = (actorBody *)FUN_000a8ad0();
      }
      else {
        paVar3 = (actorBody *)FUN_000a89c0();
      }
    }
    *(undefined4 *)&param_1[4].actorStrategyId2 = 1;
    *(undefined4 *)&param_1[4].field_0x20 = 1;
    return paVar3;
  case GetHelp:
    *(undefined4 *)&param_1[1].fearCounter = 0;
    *(undefined4 *)&param_1[1].field_0x20 = 0;
    if (*(int *)&param_1[1].field_0x30 != 1) {
      *(undefined4 *)&param_1[1].field_0x30 = 1;
      FUN_000a8ad0();
    }
    param_1->parentActor->body->indexInStatsheet = 2;
    param_1->fearCounter = param_1->fearCounter + '\x01';
    FUN_000a9d40();
    actorBody::resetFlags(paVar6);
    *(undefined4 *)&param_1[4].field_0x20 = 1;
    Events::UpdateActionBeginEnds(0xff,0);
    return extraout_EAX;
  case KnockedDown:
    actorMind::setGoalFromScript(mind,"waitforstand");
    paVar6 = param_1->parentActor->body;
    if (*(int *)&param_1[1].field_0x30 != 1) {
      *(undefined4 *)&param_1[1].field_0x30 = 1;
      paVar6 = (actorBody *)FUN_000a8ad0();
    }
    *(undefined4 *)&param_1[4].actorStrategyId2 = 1;
    *(undefined4 *)&param_1[4].field_0x20 = 1;
    return paVar6;
  case Near:
    param_1->parentActor->body->indexInStatsheet = 2;
    actorMind::setGoalFromScript(mind,"waitforstand");
    actorMind::setGoalFromScript(mind,"far");
    pfVar4 = (float *)FUN_000a9aa0(paVar6);
    iVar5 = FUN_000a9b20();
    if (iVar5 == 0) {
      if ((paVar6->health < 0x3d) &&
         (paVar6 = param_1->parentActor->body, *(int *)&param_1[1].field_0x30 != 2)) {
        *(undefined4 *)&param_1[1].field_0x30 = 2;
        if ((paVar6->flagSet->flags->attackFlags_ & 0x200000) == Null) {
          FUN_000a8ad0();
        }
        else {
          FUN_000a89c0();
        }
      }
    }
    else {
      if (*(int *)&param_1[1].field_0x30 != 1) {
        *(undefined4 *)&param_1[1].field_0x30 = 1;
        FUN_000a8ad0();
      }
      *(undefined4 *)&param_1[1].field_0x24 = 1;
    }
    fVar1 = *pfVar4;
    fVar2 = pfVar4[1];
    runtime::rand = runtime::rand * 0x19660d + 0x3c6ef35f;
    paVar6 = (actorBody *)(runtime::rand & 0x7fffff | 0x3f800000);
    *(undefined4 *)&param_1[4].actorStrategyId2 = 1;
    *(undefined4 *)&param_1[4].field_0x20 = 1;
    *(float *)&param_1[1].resetState = (fVar2 - fVar1) * ((float)paVar6 - 1.0) + fVar1;
    return paVar6;
  case PostKnockDownCelebrate:
    *(undefined4 *)&param_1[4].actorStrategyId2 = 1;
    *(undefined4 *)&param_1[4].field_0x20 = 1;
    if ((paVar6->health < 0x3d) &&
       (paVar6 = param_1->parentActor->body, *(int *)&param_1[1].field_0x30 != 2)) {
      *(undefined4 *)&param_1[1].field_0x30 = 2;
      if ((paVar6->flagSet->flags->attackFlags_ & 0x200000) == Null) {
        FUN_000a8ad0();
        paVar6 = (actorBody *)actorMind::setGoalFromScript(mind,"celebrate");
        return paVar6;
      }
      FUN_000a89c0();
    }
    paVar6 = (actorBody *)actorMind::setGoalFromScript(mind,"celebrate");
    return paVar6;
  case Spin:
    *(undefined4 *)&param_1[1].field_0x20 = 0;
    *(undefined4 *)&param_1[1].field_0x2c = 1;
    if (*(int *)&param_1[1].field_0x30 != 1) {
      *(undefined4 *)&param_1[1].field_0x30 = 1;
      FUN_000a8ad0();
    }
    actorBody::resetFlags(paVar6);
    actorMind::setGoalFromScript(mind,"spin");
    Events::UpdateActionBeginEnds(0xff,0);
    return extraout_EAX_00;
  }
  *(undefined4 *)&param_1[4].field_0x20 = 1;
  if ((paVar6->health < 0x3d) &&
     (paVar6 = param_1->parentActor->body, *(int *)&param_1[1].field_0x30 != 2)) {
    *(undefined4 *)&param_1[1].field_0x30 = 2;
    if ((paVar6->flagSet->flags->attackFlags_ & 0x200000) == Null) {
      FUN_000a8ad0();
      paVar6 = (actorBody *)actorStrategy::enterState(param_1,param_2);
      return paVar6;
    }
    FUN_000a89c0();
  }
  paVar6 = (actorBody *)actorStrategy::enterState(param_1,param_2);
  return paVar6;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void entityStrategyGrimReaper::onKnockDown(entityStrategyGrimReaper *param_1)

{
  actorMind *mind;
  
  mind = ((param_1->strategy).parentActor)->mind;
  actorMind::removeGoals(mind);
  actorMind::setGoalFromScript(mind,"knockeddown");
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void entityStrategyGrimReaper::updateFinger_(entityStrategyGrimReaper *grim)

{
  actor *paVar1;
  Model *pMVar2;
  BOOL BVar3;
  actorBody *body;
  
  if (grim->somethingNeedsUpdating != 0) {
    paVar1 = (grim->strategy).parentActor;
    body = paVar1->body;
    (grim->strategy).field_0x1a = 0;
    body->currentAttackEntry = (AttackEntry *)0x0;
    *(undefined4 *)&body->useAttackParam3 = 0;
    body->field_0x6a = body->field_0x6a + -1;
    if (body->actorAllocd != (actorBodyAllocd *)0x0) {
      FUN_0013f4d0(body->actorAllocd);
    }
    if (body->actorAllocd != (actorBodyAllocd *)0x0) {
      FUN_0013f4d0(body->actorAllocd);
    }
    body->setStateSuccessfully = 0;
    FUN_0013b810((int)&grim->field_0x48,paVar1);
    BVar3 = FUN_00052f80(0x10,(ModelFooterEntry *)((paVar1->avatar).model)->descriptor);
    if (BVar3 != 0) {
      pMVar2 = (paVar1->avatar).model;
      if (pMVar2 != (Model *)0x0) {
        ModelInstance::searchForValueWithFlags(0,pMVar2,0x10);
      }
      pMVar2 = (paVar1->avatar).shadowModel;
      if (pMVar2 != (Model *)0x0) {
        ModelInstance::searchForValueWithFlags(0,pMVar2,0x10);
      }
    }
    grim->somethingNeedsUpdating = 0;
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void entityStrategyGrimReaper::getAllocDetails(undefined4 *param_1)

{
  *param_1 = 0x9c;
  param_1[1] = 0x18;
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


undefined ** entityStrategyGrimReaper::getVTable(void)

{
  vtable[0] = getAllocDetails;
  vtable[1] = ctor;
  vtable[2] = dtor;
  vtable[3] = onMessage;
  vtable[4] = update;
  vtable[5] = setState;
  vtable[6] = leaveState;
  return vtable;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


BOOL entityStrategyGrimReaper::ctor(entityStrategyGrimReaper *grim)

{
  actor *av;
  entityStrategyGrimReaper *randomValue;
  int iVar1;
  float local_1c;
  vec3 local_18;
  vec3 local_c;
  actorBody *body;
  actorBodyFlags *flags;
  entityStrategyGrimReaper *grimm;
  float minVal;
  
  grimm = grim;
  av = (grim->strategy).parentActor;
  body = av->body;
  grim->optionalVal1 = 0.5;
  grim->field50_0x90 = 0;
  grim->reaperStats = &stats;
  grim->field51_0x94 = 1;
  grim->optionalVal2 = 1.0;
  body->airResistance = 10.0;
  grim->somethingNeedsUpdating = 0;
  flags = body->flagSet->flags;
  *(undefined1 *)&flags->flag1 = (char)flags->flag1 | 0x80;
  grim->someTimer1 = grim->reaperStats->float1;
  grim->someTimer2 = grim->reaperStats->timer2;
  flags = body->flagSet->flags;
  *(byte *)((int)&flags->attackFlags_ + 3) = *(byte *)((int)&flags->attackFlags_ + 3) | 8;
  minVal = grim->reaperStats->minValue;
  runtime::rand = runtime::rand * 0x19660d + 0x3c6ef35f;
  randomValue = (entityStrategyGrimReaper *)(runtime::rand & 0x7fffff | 0x3f800000);
  g_globalFlagset = g_globalFlagset | GrimReaperAlive;
  grim->randomValue = (grim->reaperStats->maxValue - minVal) * ((float)randomValue - 1.0) + minVal;
  grim = randomValue;
  Audio::PlayOrChangeByName(5,"XACT_SOUNDBANK_GSTREAMSDITTIES_GRIMREAPERSTREAM");
  avatar::getHealthPos(&av->avatar,(float *)&grim,&local_1c,&local_18);
  local_c.x = local_18.x;
  local_c.z = local_18.z;
  local_c.y = (float)grim * 0.5 + local_18.y;
  iVar1 = CreateReaperSomethingsIndex(&local_c,0x430c0000,110.0);
  grimm->somethingsIndex = iVar1;
  return 1;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void entityStrategyGrimReaper::dtor(entityStrategyGrimReaper *grim)

{
  AudioPlayingContext *audioCtx;
  AudioPlayingContext *pAVar1;
  int iVar2;
  
                    // When the reaper dies turn his music off
  audioCtx = Audio::GetPlayingContext("XACT_SOUNDBANK_GSTREAMSDITTIES_GRIMREAPERSTREAM");
  iVar2 = audioCtx->numReferences + -1;
  audioCtx->numReferences = iVar2;
  if (iVar2 < 1) {
    if (audioCtx->playFlags != 0x12) {
      pAVar1 = Audio::GetSomePlayingThing(audioCtx);
      if (pAVar1 != (AudioPlayingContext *)0x0) {
        AudioPlayingContext::updateSomething(pAVar1);
      }
    }
    FUN_00038260(audioCtx);
    audioCtx->playFlags = 0;
  }
  iVar2 = grim->somethingsIndex;
  if (-1 < iVar2) {
    GrimReaperFloatsArray[iVar2].active = 0;
    NumReaperSomethings = NumReaperSomethings + -1;
    if (iVar2 < ReaperSomethingsIndex) {
      ReaperSomethingsIndex = iVar2;
    }
    grim->somethingsIndex = -1;
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void entityStrategyGrimReaper::update(entityStrategyGrimReaper *strategy)

{
  int iVar1;
  entityStrategyGrimReaper *grim;
  float local_10;
  vec3 v3;
  actor *act;
  actorMind *mind;
  actorStrategyOffsetId status;
  
  grim = strategy;
  status = (strategy->strategy).id;
  act = (strategy->strategy).parentActor;
  if (-1 < strategy->somethingsIndex) {
    avatar::getHealthPos(&act->avatar,(float *)&strategy,&local_10,&v3);
    iVar1 = grim->somethingsIndex;
    GrimReaperFloatsArray[iVar1].pos.y = (float)strategy * 0.5 + v3.y;
    GrimReaperFloatsArray[iVar1].pos.x = v3.x;
    GrimReaperFloatsArray[iVar1].pos.z = v3.z;
  }
                    // If not dizzy, but dizzy can is active, then activate dizzy
  if ((status != Aloof) && (Game::PowerupParams[2].active != 0)) {
    (*((grim->strategy).vtable)->leaveState)(&grim->strategy,(grim->strategy).id);
    (grim->strategy).id = Aloof;
    actorMind::removeGoals(((grim->strategy).parentActor)->mind);
                    // Enter dizzy state
    (*((grim->strategy).vtable)->enterState)(&grim->strategy,Aloof);
  }
  actorStrategy::update(&grim->strategy);
  switch(status) {
  case Aloof:
    mind = act->mind;
    if ((mind->actionInfo).next == (actorGoalInfo *)0x0) {
      actorMind::setGoalFromScript(mind,"dizzy");
    }
    break;
  case Far:
    FUN_000adb90();
    FUN_000adfb0();
    updateSpeedAndFinger(grim);
    FUN_000acd40();
    return;
  case KnockedDown:
    updateSpeedAndFinger(grim);
    FUN_000acea0();
    return;
  case Near:
    FUN_000adfb0();
    FUN_000adb90();
    updateSpeedAndFinger(grim);
    FUN_000acf70();
    return;
  case Observe:
    FUN_000adb90();
    updateSpeedAndFinger(grim);
    FUN_000ad330();
    return;
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void entityStrategyGrimReaper::onMessage(entityStrategyGrimReaper *strategy,Message *msg)

{
  uint8_t uVar1;
  weapon *pwVar2;
  actorBody *paVar3;
  Buffer<> *pBVar4;
  uint uVar5;
  int iVar6;
  actorDroneActionId *paVar7;
  float fVar8;
  actor *act;
  
  act = (strategy->strategy).parentActor;
  switch((msg->header).msgId) {
  case Actor_ActionEnd:
    if ((strategy->strategy).id == Celebrate) {
      return;
    }
  default:
    actorStrategy::onMessage(&strategy->strategy,msg);
    break;
  case Actor_Dying:
    pwVar2 = (weapon *)(msg->header).someActor;
    if (((act->mind == (actorMind *)0x0) ||
        (paVar3 = act->mind->targetBody, paVar3 == (actorBody *)0x0)) ||
       (paVar3->currentWeapon != pwVar2)) {
      if (*(actor **)(*(int *)&pwVar2->field_0x95c + 0x270) != act) {
        return;
      }
    }
    else {
      strategy->field50_0x90 = 1;
    }
    FUN_00041d00();
    actorStrategy::setStrategy(&strategy->strategy,Celebrate);
    return;
  case Actor_ForceIntro:
    actorStrategy::forceIntro(&strategy->strategy,10);
    return;
  case Scene_ActorHit:
    uVar5 = FUN_00117560(1);
    if (uVar5 == 0) {
      return;
    }
    if ((msg->header).someActor == act) {
      if (strategy->stunned == 0) {
        strategy->stunned = 1;
        strategy->setFromOptional1 = strategy->optionalVal1;
        strategy->optionalVal1 = 0.001;
        fVar8 = strategy->reaperStats->field12_0x30;
      }
      else {
        strategy->optionalVal1 = 0.001;
        fVar8 = strategy->reaperStats->field12_0x30;
      }
      uVar1 = (strategy->strategy).fearCounter;
      fVar8 = fVar8 * strategy->setFromOptional1;
      strategy->field43_0x74 = fVar8;
      strategy->field44_0x78 = fVar8;
      if (uVar1 == '\0') {
        if ((act->actorType == Human) || ((act->node0x93c).prev != (actor_0x93c)0x0)) {
          iVar6 = 1;
        }
        else {
          iVar6 = 0;
        }
        if ((ShouldntDroneBools[iVar6] == 0) && ("\x01"[Game::CheckMoveOn] != '\0')) {
          pBVar4 = act->droneActionsBuf;
          if (pBVar4 != (Buffer<> *)0x0) {
            if (pBVar4->size == pBVar4->endOfQueue) {
              paVar7 = (actorDroneActionId *)0x0;
            }
            else {
              paVar7 = (actorDroneActionId *)
                       ((int)&pBVar4->entries->actionId +
                       (uint)pBVar4->currentDroneAction * (uint)pBVar4->valueSize);
            }
            if (*paVar7 != Null) goto LAB_000ad992;
          }
          actorStrategy::setStrategy(&strategy->strategy,Far);
        }
      }
    }
LAB_000ad992:
    iVar6 = FUN_001408a0(msg);
    if (iVar6 != 0) {
      actorStrategy::setStrategy(&strategy->strategy,KnockedDown);
      return;
    }
    iVar6 = FUN_00140910();
    if (iVar6 != 0) {
      actorStrategy::setStrategy(&strategy->strategy,Observe);
      return;
    }
    break;
  case Scene_EventComplete:
    actorStrategy::onEventCompleted(strategy);
    return;
  case Scene_EventFailed:
    actorStrategy::onEventFailed(strategy);
    return;
  case Scene_PowerupActivated:
    if (msg[1].header.msgId == General_Deactivate) {
      actorStrategy::setStrategy(&strategy->strategy,Aloof);
      return;
    }
    break;
  case Scene_PowerupDeactivated:
    if (msg[1].header.msgId == General_Deactivate) {
      actorStrategy::setStrategy(&strategy->strategy,Far);
      return;
    }
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields

void entityStrategyGrimReaper::setState
               (entityStrategyGrimReaper *grim,actorStrategyOffsetId param_2)

{
  switch(param_2) {
  case Aloof:
    actorMind::setGoalFromScript(((grim->strategy).parentActor)->mind,"dizzy");
switchD_000ada88_caseD_40d:
    return;
  default:
    actorStrategy::enterState(&grim->strategy,param_2);
    return;
  case Far:
    FUN_000acd00(grim);
    return;
  case KnockedDown:
    onKnockDown(grim);
    return;
  case Near:
    FUN_000acf10(grim);
    return;
  case Observe:
    goto switchD_000ada88_caseD_40d;
  }
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields

void entityStrategyGrimReaper::leaveState
               (entityStrategyGrimReaper *grim,actorStrategyOffsetId state)

{
  uint8_t *puVar1;
  
  switch(state) {
  case Aloof:
  case Far:
  case KnockedDown:
  case Observe:
    goto switchD_000adb27_caseD_3ea;
  default:
    if (((state == Dying) || (state == ExitExclusionRegion)) || (state == Stall)) {
      puVar1 = &(grim->strategy).fearCounter;
      *puVar1 = *puVar1 + 0xff;
    }
switchD_000adb27_caseD_3ea:
    return;
  case Near:
    FUN_000acf40(grim);
    return;
  }
}




void entityStrategyGrimReaper::updateSpeedAndFinger(entityStrategyGrimReaper *grim)

{
  actorStrategyOffsetId aVar1;
  actorBodyFlags *paVar2;
  actor *paVar3;
  actorMind *mind;
  int iVar4;
  float delta;
  float speed;
  actor *actt;
  actorBody *body;
  GrimReaperStats *stats;
  
  actt = (grim->strategy).parentActor;
  body = actt->body;
  if ((body->flagSet->flags->attackFlags_ & 0x8000000) != Null) {
    if (runtime::dx_timer <= 0.0) {
      delta = runtime::DeltaTime * runtime::TimeScale;
    }
    else {
      delta = 0.0;
    }
    speed = 0.0;
    if ((actt->avatar).movementFreezeTimer <= 0.0) {
      speed = (actt->avatar).actionSpeed;
    }
    if ((0.0 < grim->someTimer1) &&
       (delta = grim->someTimer1 - speed * delta, grim->someTimer1 = delta, delta <= 0.0)) {
      grim->someTimer1 = 0.0;
    }
    if (grim->someTimer1 <= 0.001 && grim->someTimer1 != 0.001) {
      paVar2 = body->flagSet->flags;
      *(byte *)((int)&paVar2->attackFlags_ + 3) = *(byte *)((int)&paVar2->attackFlags_ + 3) & 0xf7;
    }
  }
  if (grim->field51_0x94 == 0) {
    paVar3 = (grim->strategy).parentActor;
    if (runtime::dx_timer <= 0.0) {
      delta = runtime::DeltaTime * runtime::TimeScale;
    }
    else {
      delta = 0.0;
    }
    speed = 0.0;
    if ((paVar3->avatar).movementFreezeTimer <= 0.0) {
      speed = (paVar3->avatar).actionSpeed;
    }
    if ((0.0 < grim->someTimer2) &&
       (delta = grim->someTimer2 - speed * delta, grim->someTimer2 = delta, delta <= 0.0)) {
      grim->someTimer2 = 0.0;
    }
    if (grim->someTimer2 <= 0.001 && grim->someTimer2 != 0.001) {
      stats = grim->reaperStats;
      mind = actt->mind;
      grim->someTimer2 = stats->timer2;
      if (grim->optionalVal1 <= 1.0 && grim->optionalVal1 != 1.0) {
        if (grim->stunned == 0) {
          delta = stats->field2_0x8 + grim->optionalVal1;
          grim->optionalVal1 = delta;
          if (1.0 < delta) {
            grim->optionalVal1 = 1.0;
          }
        }
        else {
          delta = grim->setFromOptional1 + stats->field2_0x8;
          grim->setFromOptional1 = delta;
          if (1.0 < delta) {
            grim->setFromOptional1 = 1.0;
          }
          grim->field43_0x74 = stats->field12_0x30 * stats->field2_0x8 + grim->field43_0x74;
          grim->field44_0x78 = stats->field12_0x30 * stats->field2_0x8 + grim->field44_0x78;
        }
      }
      if (grim->optionalVal2 <= stats->field5_0x14 && stats->field5_0x14 != grim->optionalVal2) {
        grim->optionalVal2 = stats->field4_0x10 + grim->optionalVal2;
      }
      iVar4 = FUN_000ae0a0();
      if ((iVar4 != 0) && ((aVar1 = (grim->strategy).id, aVar1 == Far || (aVar1 == Near)))) {
        actorMind::removeGoals(mind);
        FUN_000adcc0(grim,actt);
      }
    }
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void entityStrategyPlayer::getAllocDetails(ObjectAllocDetails *param_1)

{
  param_1->entitySize = 0x54;
  param_1->paramsSize = 0x18;
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void entityStrategyImp::getAllocDetails(ObjectAllocDetails *param_1)

{
  param_1->entitySize = 0x50;
  param_1->paramsSize = 0x18;
  return;
}




void entityStrategyHauntedTV::getAllocDetails(undefined4 *param_1)

{
  *param_1 = 0x11c;
  param_1[1] = 0x498;
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


undefined ** entityStrategyHauntedTV::getVTable(void)

{
  vtable[0] = getAllocDetails;
  vtable[1] = ctor;
  vtable[2] = dtor;
  vtable[3] = onMessage;
  vtable[4] = update;
  vtable[5] = enterState;
  vtable[6] = leaveState;
  return vtable;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields

undefined4
entityStrategyHauntedTV::ctor
          (entityStrategyHauntedTV *param_1,entityStrategyHauntedTVParams *param_2)

{
  void *in_ECX;
  
  FUN_000b1ad0(in_ECX,param_2,param_1);
  loadSpawnedActor(param_1,param_2);
  return 1;
}




void entityStrategyHauntedTV::dtor(void)

{
  FUN_000b1b50();
  FUN_000b1530();
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void entityStrategyHauntedTV::update(actorStrategy *param_1)

{
  actorStrategyOffsetId aVar1;
  actor *paVar2;
  actorMind *mind;
  actorStrategy *paVar3;
  actorStrategy *strategy;
  actorMindGoal *paVar4;
  int iVar5;
  BOOL BVar6;
  bool bVar7;
  float fVar8;
  float fVar9;
  
  strategy = param_1;
  aVar1 = param_1->id;
  paVar2 = param_1->parentActor;
  mind = paVar2->mind;
  if (runtime::dx_timer <= 0.0) {
    fVar8 = runtime::DeltaTime * runtime::TimeScale;
  }
  else {
    fVar8 = 0.0;
  }
  fVar9 = 0.0;
  if ((paVar2->avatar).movementFreezeTimer <= 0.0) {
    fVar9 = (paVar2->avatar).actionSpeed;
  }
  if (0.0 < *(float *)&param_1[1].actorStrategyId2) {
    fVar8 = *(float *)&param_1[1].actorStrategyId2 - fVar9 * fVar8;
    *(float *)&param_1[1].actorStrategyId2 = fVar8;
    if (fVar8 <= 0.0) {
      *(undefined4 *)&param_1[1].actorStrategyId2 = 0;
    }
  }
  bVar7 = *(int *)&paVar2->ghoulyBoxResetValue != 0x5f646961;
  actorStrategy::update(param_1);
  switch(aVar1) {
  case Attack_KnockDown:
    iVar5 = FUN_00139aa0(&param_1,0);
    paVar3 = param_1;
    if (iVar5 == 0) goto switchD_000b200d_caseD_3f0;
    param_1 = (actorStrategy *)FUN_00141530(paVar2);
    if ((mind->actionInfo).next == (actorGoalInfo *)0x0) {
      paVar4 = actorMind::allocAction(mind,TurnToFaceTarget);
      fVar8 = 0.17453294;
      paVar4[1].prev = (actorMindGoal *)0x3e32b8c3;
    }
    iVar5 = FUN_000b29d0();
    if (iVar5 == 2) {
      FUN_00042320();
      fVar8 = fVar8 + *(float *)&strategy[1].actorStrategyId3;
      *(float *)&strategy[1].actorStrategyId3 = fVar8;
      if ((0.5 <= fVar8) || (param_1 == (actorStrategy *)0x0)) {
        FUN_000b2a60(param_1 == (actorStrategy *)0x0);
      }
      goto switchD_000b200d_caseD_3f0;
    }
    if (iVar5 != 3) {
      strategy[1].actorStrategyId3 = 0;
      strategy[1].actorStrategyId4 = 0;
      if (param_1 == (actorStrategy *)0x0) {
        FUN_000b2a60(1);
      }
      goto switchD_000b200d_caseD_3f0;
    }
    break;
  case Attack_Special:
    iVar5 = FUN_00139aa0(&param_1,0);
    if ((iVar5 == 0) || ((mind->actionInfo).next != (actorGoalInfo *)0x0))
    goto switchD_000b200d_caseD_3f0;
    BVar6 = actorStrategy::shouldBeDroning(strategy);
    if (BVar6 == 0) {
      actorStrategy::setStrategy(strategy,Null);
      goto switchD_000b200d_caseD_3f0;
    }
    iVar5 = FUN_000b2a60(0);
    if (iVar5 != 0) goto switchD_000b200d_caseD_3f0;
    goto LAB_000b2140;
  default:
    goto switchD_000b200d_caseD_3f0;
  case Evade:
    iVar5 = FUN_00139aa0(&param_1,0);
    if (iVar5 == 0) goto switchD_000b200d_caseD_3f0;
    iVar5 = FUN_00042450(0x3f000000);
    if ((iVar5 != 0) || ((mind->actionInfo).next == (actorGoalInfo *)0x0)) {
      FUN_000b2a60(0);
    }
    iVar5 = FUN_000b29d0();
    if (iVar5 == 1) {
LAB_000b21b2:
      actorStrategy::setStrategy(strategy,Attack_KnockDown);
      goto switchD_000b200d_caseD_3f0;
    }
    paVar3 = param_1;
    if (iVar5 != 3) goto switchD_000b200d_caseD_3f0;
    break;
  case KnockedDown:
    FUN_00139aa0(&param_1,0);
    if ((mind->actionInfo).next != (actorGoalInfo *)0x0) goto switchD_000b200d_caseD_3f0;
    strategy->parentActor->skipObjectTypeLookup = 0;
    paVar3 = param_1;
    break;
  case PreIntro:
    FUN_00139aa0(&param_1,0);
    if (param_1 != (actorStrategy *)0x0) {
      actorStrategy::canPlayIntro(strategy,0xe);
      goto switchD_000b200d_caseD_3f0;
    }
LAB_000b2140:
    actorStrategy::setStrategy(strategy,Wait);
    goto switchD_000b200d_caseD_3f0;
  case Sleep:
    iVar5 = FUN_00139aa0(&param_1,0);
    if ((iVar5 != 0) && (FUN_000415a0(), fVar8 < 3600.0)) {
      strategy->parentActor->skipObjectTypeLookup = 0;
      actorStrategy::setStrategy(strategy,Wake);
    }
    goto switchD_000b200d_caseD_3f0;
  case Wait:
    FUN_00139aa0(&param_1,0);
    if ((mind->actionInfo).next == (actorGoalInfo *)0x0) {
      actorMind::setGoalFromScript(mind,"wait");
    }
    iVar5 = FUN_00042450(0x3f000000);
    paVar3 = param_1;
    if ((iVar5 != 0) && (iVar5 = FUN_000b2a60(0), iVar5 != 0)) goto switchD_000b200d_caseD_3f0;
    iVar5 = FUN_000b29d0();
    if (iVar5 == 1) goto LAB_000b21b2;
    if (((iVar5 != 3) || (paVar3 == (actorStrategy *)0x0)) || (bVar7))
    goto switchD_000b200d_caseD_3f0;
    goto LAB_000b2302;
  case Wake:
    if ((mind->actionInfo).next != (actorGoalInfo *)0x0) goto switchD_000b200d_caseD_3f0;
    iVar5 = FUN_000f29a0();
    if (iVar5 == 0) {
      actorStrategy::setStrategy(strategy,PreIntro);
      goto switchD_000b200d_caseD_3f0;
    }
    BVar6 = actorStrategy::shouldBeDroning(strategy);
    if (BVar6 == 0) {
      actorStrategy::setStrategy(strategy,Null);
      goto switchD_000b200d_caseD_3f0;
    }
    goto LAB_000b2302;
  }
  if ((paVar3 == (actorStrategy *)0x0) || (bVar7)) {
    actorStrategy::setStrategy(strategy,Wait);
  }
  else {
LAB_000b2302:
    FUN_000b2b30();
  }
switchD_000b200d_caseD_3f0:
  if (*(int *)&strategy[1].field_0x20 != 0) {
    FUN_000f8640();
  }
  FUN_000b1590();
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void entityStrategyHauntedTV::onMessage(actorStrategy *strat,Message *param_2)

{
  actor *paVar1;
  actorStrategy *strategy;
  Message *pMVar2;
  BOOL has_target;
  int iVar3;
  
  pMVar2 = param_2;
  strategy = strat;
  paVar1 = strat->parentActor;
  switch((param_2->header).msgId) {
  case General_Activate:
    if (strat->id == ActionEnabledDelay) {
      if (*(int *)&strat[1].field_0x4 != 0) {
        return;
      }
    }
    else if (strat->id != Sleep) goto switchD_000b240d_caseD_2;
    has_target = actorStrategy::updateAndGetTarget(strat,(actorBody **)&strat,0);
    if (has_target != 0) {
      strategy->parentActor->skipObjectTypeLookup = 0;
      actorStrategy::setStrategy(strategy,Wake);
      return;
    }
    break;
  default:
switchD_000b240d_caseD_2:
    actorStrategy::onMessage(strat,param_2);
    return;
  case Actor_ActionEnd:
    if ((strat->id != Wake) &&
       (iVar3._0_2_ = strat[1].newState_, iVar3._2_2_ = strat[1].actorStrategyId, iVar3 == 0)) {
      actorStrategy::onMessage(strat,param_2);
      return;
    }
    break;
  case Actor_KnockDownDeath:
    iVar3 = *(int *)&strat[1].fearCounter;
    if ((iVar3 != 0) && (iVar3 != 5)) {
      if ((&DAT_00303038)[iVar3] != '\0') {
        FUN_0012a3d0((astruct_25 *)&(paVar1->avatar).model0x9s[5].field_0xb0);
      }
      *(undefined4 *)&strategy[1].fearCounter = 5;
      FUN_000b1ce0();
      FUN_00041d00();
      return;
    }
    break;
  case Actor_GeneratedAvatar:
    FUN_000b1ba0(2);
    return;
  case Actor_GhoulyIntroEnd:
    strat->actorStrategyId = Attack_Special;
    strat->actorStrategyId2 = Attack_Special;
    strat->actorStrategyId3 = Wait;
    strat->actorStrategyId4 = Wait;
    return;
  case Actor_GoalFlagSet:
    *(undefined4 *)&strat[1].field_0x4 = 1;
    FUN_0013a400();
    return;
  case Scene_ActorHit:
    actorStrategy::onMessage(strat,param_2);
    has_target = actorStrategy::checkAndSetDying(strategy);
    if ((has_target == 0) && ((pMVar2->header).someActor == paVar1)) {
      FUN_00139390((Object *)strategy,pMVar2,0xffffffff);
      iVar3 = FUN_000f29a0();
      if (iVar3 == 0) {
        FUN_000b1710();
        actorStrategy::setStrategy(strategy,PreIntro);
        return;
      }
      iVar3 = FUN_001408a0(pMVar2);
      if (iVar3 != 0) {
        actorStrategy::setStrategy(strategy,KnockedDown);
        return;
      }
      if (strategy->id == Sleep) {
        actorStrategy::setStrategy(strategy,Wait);
      }
    }
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void entityStrategyHauntedTV::enterState(actorStrategy *param_1,actorStrategyOffsetId param_2)

{
  actor *paVar1;
  actorMind *mind;
  int iVar2;
  
  paVar1 = param_1->parentActor;
  mind = paVar1->mind;
  paVar1->body->indexInStatsheet = 2;
  param_1->field_0x1a = 0;
  param_1->field_0x1b = 0;
  switch(param_2) {
  case Attack_KnockDown:
    param_1->parentActor->body->indexInStatsheet = 5;
    param_1->field_0x1a = 1;
    param_1[1].actorStrategyId3 = 0;
    param_1[1].actorStrategyId4 = 0;
    FUN_000b1ba0(3);
    FUN_000b1710();
    return;
  case Attack_Special:
    param_1->parentActor->body->indexInStatsheet = 6;
    param_1->actorStrategyId = Wait;
    param_1->actorStrategyId2 = Wait;
    param_1->actorStrategyId3 = Wait;
    param_1->actorStrategyId4 = Wait;
    param_1->field_0x1b = 1;
    actorMind::setGoalFromScript(mind,"generateghouly");
    iVar2._0_2_ = param_1[1].resetState;
    iVar2._2_2_ = param_1[1].id;
    if (iVar2 == 0) {
      FUN_000b1710();
      *(int *)&param_1[1].resetState = *(int *)&param_1[1].resetState + 1;
      *(int *)&param_1[1].newState_ = *(int *)&param_1[1].newState_ + 1;
    }
    break;
  default:
    actorStrategy::enterState(param_1,param_2);
    return;
  case Dying:
    actorStrategy::enterState(param_1,param_2);
    if (paVar1->ghoulyBox != (void *)0x0) {
      GhoulyBox::dtor(paVar1->ghoulyBox);
      paVar1->ghoulyBox = (void *)0x0;
    }
    paVar1->ghoulyBoxResetValue = 0;
    return;
  case Evade:
    param_1->parentActor->body->indexInStatsheet = 3;
    param_1[1].vtable = (actorStrategyVTable *)0.5;
    FUN_000b1ba0(2);
    return;
  case KnockedDown:
    *(float *)&param_1[1].actorStrategyId2 = 1.0;
    FUN_000b1710();
    actorMind::setGoalFromScript(mind,"knocked_down");
    return;
  case PreIntro:
    param_1->actorStrategyId = PreIntro;
    param_1->actorStrategyId2 = PreIntro;
    FUN_000b1ba0(2);
    return;
  case Sleep:
    actorMind::setGoalFromScript(mind,"sleep");
    param_1->fearCounter = param_1->fearCounter + '\x01';
    FUN_000b1ba0(0);
    return;
  case Wait:
    param_1[1].vtable = (actorStrategyVTable *)0.5;
    actorMind::setGoalFromScript(mind,"wait");
    FUN_000b1ba0(2);
    return;
  case Wake:
    param_1->actorStrategyId2 =
         (-(ushort)((PTR_00506c6c->field2_0x8[1] & 0x40) != 0) & 7) + PreIntro;
    FUN_000b1ba0(3);
    param_1->field_0x1b = 1;
    actorMind::setGoalFromScript(mind,"wakeup");
    return;
  }
  paVar1 = param_1->parentActor;
  if ((&DAT_00303038)[*(int *)&param_1[1].fearCounter] != '\0') {
    FUN_0012a3d0((astruct_25 *)&(paVar1->avatar).model0x9s[5].field_0xb0);
  }
  *(undefined4 *)&param_1[1].fearCounter = 4;
  FUN_000b1d30((int)param_1,(int)paVar1);
  return;
}




void entityStrategyHauntedTV::leaveState(int param_1,short param_2,short param_3)

{
  switch(param_2) {
  case 0x3ef:
    FUN_000b1780();
    if (*(int *)(param_1 + 0x48) != 0) {
      *(int *)(param_1 + 0x48) = *(int *)(param_1 + 0x48) + -1;
      return;
    }
    break;
  default:
    if (((param_2 != 0x3fc) && (param_2 != 0x3ff)) && (param_2 != 0x415)) {
      return;
    }
  case 0x413:
    *(char *)(param_1 + 0x1c) = *(char *)(param_1 + 0x1c) + -1;
    break;
  case 0x3fe:
    *(float *)(*(int *)(*(int *)(param_1 + 8) + 0x95c) + 0x32c) = 1.0;
    return;
  case 0x409:
    if (param_3 == 0x3ef) {
      return;
    }
  case 0x3ee:
    FUN_000b1780();
    return;
  case 0x417:
    break;
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void __fastcall entityStrategyHunchback::doSpecialAttack(actorStrategy *param_1)

{
  int iVar1;
  int iVar2;
  actor *paVar3;
  int in_EAX;
  float *extraout_ECX;
  float *extraout_ECX_00;
  float *extraout_ECX_01;
  actorMind *paVar4;
  
  iVar1 = *(int *)(in_EAX + 0x95c);
  iVar2 = *(int *)(iVar1 + 0x2c8);
  if ((iVar2 != 0) && (*(int *)(iVar2 + 8) != 0)) {
    FUN_0013eb60();
  }
  switch(*(undefined4 *)&param_1[3].field_0x2c) {
  case 1:
    if ((*(byte *)(*(int *)(*(int *)(iVar1 + 0x15c) + 8) + 5) & 8) != 0) {
      FUN_000b3780(3,param_1);
      return;
    }
    break;
  case 3:
    FUN_0002b9f0();
    if (*extraout_ECX != 0.0) {
      return;
    }
    if (param_1[4].parentActor == (actor *)0x0) {
      FUN_000b3780(4,param_1);
      return;
    }
    goto LAB_000b369f;
  case 4:
    paVar4 = *(actorMind **)(in_EAX + 0x958);
    if (param_1[4].parentActor == (actor *)0x0) {
      if ((paVar4->actionInfo).next == (actorGoalInfo *)0x0) {
        actorMind::setGoalFromScript(paVar4,"specialattack");
      }
      FUN_0002b9f0();
      if (*extraout_ECX_00 != 0.0) {
        return;
      }
      if (*(int *)&param_1[3].field_0x2c == 6) {
        return;
      }
      paVar3 = param_1->parentActor;
      *(undefined4 *)&param_1[3].field_0x2c = 6;
      paVar4 = paVar3->mind;
    }
    else {
      actorMind::removeGoals(paVar4);
      if (*(int *)&param_1[3].field_0x2c == 6) {
        return;
      }
      *(undefined4 *)&param_1[3].field_0x2c = 6;
      paVar4 = param_1->parentActor->mind;
    }
    goto LAB_000b360f;
  case 5:
    FUN_0002b9f0();
    if (*extraout_ECX_01 != 0.0) {
      return;
    }
LAB_000b369f:
    if (*(int *)&param_1[3].field_0x2c != 6) {
      paVar3 = param_1->parentActor;
      *(undefined4 *)&param_1[3].field_0x2c = 6;
      paVar4 = paVar3->mind;
LAB_000b360f:
      actorMind::removeGoals(paVar4);
      actorMind::setGoalFromScript(paVar4,"specialattackfinish");
      FUN_000b39d0();
      return;
    }
    break;
  case 6:
    if (*(int *)(*(int *)(in_EAX + 0x958) + 0x58) == 0) {
      actorStrategy::setStrategy(param_1,Far);
    }
  }
  return;
}




actorStrategyVTable * entityStrategyHunchback::getVTable(void)

{
  actorStrategyVTable_00505e88.getAllocDetails = (getAllocDetailsFn *)&LAB_000b3a70;
  actorStrategyVTable_00505e88.ctor = &DAT_000b3ae0;
  actorStrategyVTable_00505e88.dtor = switchD_000d4179::EmptyFunction;
  actorStrategyVTable_00505e88.onMessage = &DAT_000b3bf0;
  actorStrategyVTable_00505e88.update = update;
  actorStrategyVTable_00505e88.enterState = (actorStrategyStateChangeCallback *)&DAT_000b3dd0;
  actorStrategyVTable_00505e88.leaveState = (actorStrategyStateChangeCallback *)&DAT_000b3e70;
  return &actorStrategyVTable_00505e88;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void entityStrategyHunchback::update(actorStrategy *strategy)

{
  actorStrategyOffsetId aVar1;
  actorStrategy *strategy_00;
  actor *av;
  int iVar2;
  float unaff_EBX;
  float unaff_ESI;
  float unaff_EDI;
  float fVar3;
  float fVar4;
  float fVar5;
  int iStack_14;
  getAllocDetailsFn *pgVar6;
  
  aVar1 = strategy->id;
  av = strategy->parentActor;
  iStack_14 = 0xb3b54;
  actorStrategy::update(strategy);
  switch(aVar1) {
  case Attack_Special:
    doSpecialAttack();
    return;
  case Evade:
    FUN_000b2bf0();
    return;
  case Far:
    FUN_000b2dd0();
    return;
  case KnockedDown:
    iStack_14 = 0xb3b9e;
    FUN_000b3220();
    break;
  case Near:
    iVar2 = FUN_00139aa0(&iStack_14,0,unaff_EDI,unaff_ESI);
    if (iVar2 != 0) {
      pgVar6 = (strategy[1].vtable)->getAllocDetails;
      avatar::getWorldPosition(&av->avatar,(vec3 *)&stack0xfffffff4);
      fVar5 = unaff_EBX - *(float *)(iStack_14 + 0x28);
      fVar3 = unaff_EDI - *(float *)(iStack_14 + 0x20);
      fVar4 = unaff_ESI - *(float *)(iStack_14 + 0x24);
      if ((float)pgVar6 * (float)pgVar6 < fVar5 * fVar5 + fVar3 * fVar3 + fVar4 * fVar4) {
        strategy_00 = av->strategy;
        (*strategy_00->vtable->leaveState)(strategy_00,strategy_00->id);
        strategy_00->id = Far;
        actorMind::removeGoals(strategy_00->parentActor->mind);
        (*strategy_00->vtable->enterState)(strategy_00,Far);
      }
    }
    return;
  }
  return;
}




ObjectFullVTable * entityStrategyImp::getVTable(void)

{
  ObjectFullVTable_00505ea4.getAllocDetails = getAllocDetails;
  ObjectFullVTable_00505ea4.ctor = ctor;
  ObjectFullVTable_00505ea4.dtor = &LAB_000b45b0;
  ObjectFullVTable_00505ea4.onMessage = updateFixed_;
  ObjectFullVTable_00505ea4.update = update;
  ObjectFullVTable_00505ea4.enterState = func5;
  ObjectFullVTable_00505ea4.leaveState = func6;
  return &ObjectFullVTable_00505ea4;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


obj * entityStrategyImp::ctor(entityStrategyImp *param_1)

{
  objParams *params;
  actor_conflict5 *av;
  obj *poVar1;
  float unaff_retaddr;
  vec3 vStack_50;
  vec3 vStack_44;
  vec3 vStack_38;
  undefined4 uStack_2c;
  undefined4 uStack_28;
  float fStack_24;
  float fStack_20;
  float fStack_1c;
  float fStack_18;
  float fStack_14;
  astruct_38 *pvVar1;
  
  pvVar1 = (astruct_38 *)(param_1->actorStrategy).parentActor;
  param_1->field11_0x48 = 0;
  param_1->field6_0x40 = 0;
  fStack_14 = 1.035146e-39;
  FUN_000b43b0(pvVar1,1,(astruct_39 *)&param_1->field6_0x40);
  param_1->behaviourAttribs = &attribs;
  if (Game::SceneInfo.playerActors.prev == (actor_0x93c_conflict5)0x0) {
    av = (actor_conflict5 *)0x0;
  }
  else {
    av = ADJ(Game::SceneInfo.playerActors.prev);
  }
  avatar::getWorldPosition((avatar *)av,&vStack_38);
  GetReaperPosFromMarkerAndSpawn(&vStack_50,&vStack_44,&vStack_38);
  params = Assets::GetObjParams("aid_objparams_ghoulies_actor_grimreaper");
  if (params == (objParams *)0x0) {
    poVar1 = (obj *)0x0;
  }
  else {
    *(float *)(params + 1) = vStack_50.x;
    *(float *)&params[1].typeIndex = vStack_50.y;
    *(float *)(params + 2) = vStack_50.z;
    *(float *)&params[2].typeIndex = vStack_44.x;
    *(float *)(params + 3) = vStack_44.y;
    *(float *)&params[3].typeIndex = vStack_44.z;
    *(float *)(params + 4) = 1.0;
    params[0x55].objInitValue = 0;
    params[0x55].typeIndex = 0;
    poVar1 = Assets::CreateEntityFromParams(params);
    free(params);
    if (poVar1 != (obj *)0x0) {
      fStack_24 = vStack_50.x;
      fStack_20 = vStack_50.y;
      fStack_1c = vStack_50.z;
      fStack_18 = vStack_44.x;
      *(undefined2 *)&poVar1[0x132].vtable = 0;
      fStack_14 = vStack_44.y;
      uStack_2c = 0x4d;
      uStack_28 = 4;
      (*poVar1->vtable->onMessage)(poVar1,&uStack_2c);
    }
  }
  if (unaff_retaddr != 0.0) {
    *(float *)(*(int *)&poVar1[0x12a].field_0x4 + 0x3c) = unaff_retaddr;
  }
  return poVar1;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void entityStrategyImp::update(entityStrategyImp *param_1)

{
  actorStrategyOffsetId aVar1;
  actor *paVar2;
  actorMind *paVar3;
  
  aVar1 = (param_1->actorStrategy).id;
  paVar2 = (param_1->actorStrategy).parentActor;
  paVar3 = paVar2->mind;
  actorStrategy::update(&param_1->actorStrategy);
  switch(aVar1) {
  case Attack_KnockDown:
    FUN_000b4af0(param_1,(int)paVar2,(int)paVar3);
    break;
  case Attack_Special:
    FUN_000b4df0();
    return;
  case Far:
    FUN_000b4c20(paVar2,paVar3);
    return;
  case Mutated:
    FUN_000b4cc0();
    return;
  case Near:
    FUN_000b3f80(paVar2);
    return;
  case Wait:
    FUN_000b4d50();
    return;
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


uint entityStrategyImp::updateFixed_(actorStrategy *param_1,Message *param_2)

{
  actorStrategyOffsetId aVar1;
  actor *paVar2;
  ObjMsgID OVar3;
  actor *paVar4;
  Buffer<> *pBVar5;
  int iVar6;
  uint uVar7;
  uint extraout_EAX;
  uint extraout_EAX_00;
  uint extraout_EAX_01;
  uint extraout_EAX_02;
  actorDroneActionId *paVar8;
  bool bVar9;
  
  paVar2 = param_1->parentActor;
  iVar6 = FUN_001384f0(param_1,param_2);
  if ((iVar6 != 0) || (OVar3 = (param_2->header).msgId, 0x70 < OVar3 - Avatar_FxCustomRemoved))
  goto switchD_000b46dd_caseD_15;
  uVar7 = (uint)*(byte *)((int)&PTR_caseD_7c_000b487c + OVar3);
  switch(OVar3) {
  case Avatar_FxCustomRemoved:
    if (*(actor **)&param_1[1].resetState != (param_2->header).someActor) {
      return uVar7;
    }
    param_1[1].resetState = 0;
    param_1[1].id = 0;
    return uVar7;
  case Actor_ActionBegin:
  case Actor_ActionEnd:
    if ((param_1->id == Attack_Special) &&
       (uVar7._0_2_ = param_1[1].newState_, uVar7._2_2_ = param_1[1].actorStrategyId, uVar7 != 0)) {
      return uVar7;
    }
  default:
switchD_000b46dd_caseD_15:
    uVar7 = actorStrategy::onMessage(param_1,param_2);
    break;
  case Actor_Dying:
    uVar7 = *(uint *)&param_1[1].field_0x4;
    if (uVar7 == 0) {
      return 0;
    }
    bVar9 = (param_2->header).someActor == *(actor **)(uVar7 + 8);
    goto LAB_000b4828;
  case Actor_ForceIntro:
    actorStrategy::forceIntro(param_1,0x10);
    return extraout_EAX;
  case Actor_GoalFlagSet:
    param_1[1].newState_ = 1;
    param_1[1].actorStrategyId = 0;
    return uVar7;
  case Actor_JumpedOff:
    bVar9 = (param_2->header).someActor == paVar2;
    goto LAB_000b474d;
  case Actor_JumpedOn:
    if ((param_2->header).someActor != paVar2) {
      return uVar7;
    }
    uVar7 = FUN_000b4380();
    return uVar7;
  case Actor_StateAborted:
    bVar9 = param_1->id == Attack_Special;
LAB_000b474d:
    if (!bVar9) {
      return uVar7;
    }
    FUN_000b43b0((astruct_38 *)paVar2,1,(astruct_39 *)&param_1[1].parentActor);
    return extraout_EAX_00;
  case Scene_ActorHit:
    paVar4 = (param_2->header).someActor;
    aVar1 = param_1->id;
    actorStrategy::onMessage(param_1,param_2);
    uVar7 = actorStrategy::checkAndSetDying(param_1);
    if (uVar7 != 0) {
      return uVar7;
    }
    if (paVar4 != paVar2) {
      if (aVar1 != Attack_Special) {
        uVar7 = FUN_001395c0();
        return uVar7;
      }
      return 0;
    }
    switch(aVar1) {
    case Attack_KnockDown:
    case Far:
      goto switchD_000b47ca_caseD_3ee;
    case Attack_Special:
switchD_000b47ca_caseD_3ef:
      actorStrategy::setStrategy(param_1,Attack_Special);
      return extraout_EAX_02;
    default:
      return aVar1 - 0x3ee;
    case Mutated:
      iVar6 = FUN_000b4330(&param_1[1].parentActor);
      if (iVar6 != 0) goto switchD_000b47ca_caseD_3ef;
switchD_000b47ca_caseD_3ee:
      actorStrategy::setStrategy(param_1,Near);
      return extraout_EAX_01;
    }
  case Scene_AvatarRemoved:
    bVar9 = (param_2->header).someActor == paVar2;
LAB_000b4828:
    if (bVar9) {
switchD_000b46dd_caseD_80:
      uVar7 = FUN_000c2d90();
      return uVar7;
    }
    break;
  case Scene_End:
    goto switchD_000b46dd_caseD_80;
  case Scene_EventComplete:
    uVar7 = actorStrategy::onEventCompleted(param_1);
    return uVar7;
  case Scene_EventFailed:
    if (param_1->fearCounter == '\0') {
      paVar2 = param_1->parentActor;
      if ((paVar2->actorType == Human) || ((paVar2->node0x93c).prev != (actor_0x93c)0x0)) {
        iVar6 = 1;
      }
      else {
        iVar6 = 0;
      }
      if ((ShouldntDroneBools[iVar6] == 0) && ("\x01"[Game::CheckMoveOn] != '\0')) {
        pBVar5 = paVar2->droneActionsBuf;
        if (pBVar5 != (Buffer<> *)0x0) {
          if (pBVar5->size == pBVar5->endOfQueue) {
            paVar8 = (actorDroneActionId *)0x0;
          }
          else {
            paVar8 = (actorDroneActionId *)
                     ((int)&pBVar5->entries->actionId +
                     (uint)pBVar5->currentDroneAction * (uint)pBVar5->valueSize);
          }
          if (*paVar8 != Null) {
            return 0;
          }
        }
        if (((paVar2->body->field13_0x30 == 0) && (paVar2->body->someTimer2 == 0.0)) &&
           (runtime::rand = runtime::rand * 0x19660d + 0x3c6ef35f,
           (float)(runtime::rand & 0x7fffff | 0x3f800000) - 1.0 <= 1.0)) {
          actorStrategy::setStrategy(param_1,Celebrate);
          return 1;
        }
      }
    }
    return 0;
  }
  return uVar7;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void entityStrategyImp::func5(actorStrategy *param_1,actorStrategyOffsetId param_2)

{
  actor *paVar1;
  actorMind *mind;
  
  paVar1 = param_1->parentActor;
  mind = paVar1->mind;
  paVar1->body->indexInStatsheet = 2;
  switch(param_2) {
  case Attack_KnockDown:
    param_1->parentActor->body->indexInStatsheet = 4;
    actorMind::setGoalFromScript(mind,"attack");
    param_1[1].vtable = *(actorStrategyVTable **)(*(int *)&param_1[1].actorStrategyId3 + 0x28);
    return;
  case Attack_Special:
    param_1->parentActor->body->indexInStatsheet = 6;
    return;
  default:
    actorStrategy::enterState(param_1,param_2);
switchD_000b4979_caseD_401:
    return;
  case Far:
  case Wait:
    goto switchD_000b4979_caseD_401;
  case Mutated:
    param_1->parentActor->body->indexInStatsheet = 6;
    FUN_000b43b0((astruct_38 *)paVar1,2,(astruct_39 *)&param_1[1].parentActor);
    actorMind::setGoalFromScript(mind,"mutateup");
    return;
  case Near:
    param_1->parentActor->body->indexInStatsheet = 3;
    param_1[1].vtable = (actorStrategyVTable *)0x0;
    return;
  }
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void entityStrategyImp::func6(int param_1,short param_2,short param_3)

{
  astruct_38 *paVar1;
  int iVar2;
  
  paVar1 = *(astruct_38 **)(param_1 + 8);
  if (param_3 != 0x3ee) {
    FUN_00112a20();
  }
  if ((param_2 == 0x3ef) || (param_2 == 0x40b)) {
    *(undefined4 *)(param_1 + 0x48) = 0;
    *(undefined1 *)(param_1 + 0x1a) = 0;
    if (param_3 != 0x3ef) {
      FUN_000b43b0(paVar1,1,(astruct_39 *)(param_1 + 0x40));
      iVar2 = *(int *)(param_1 + 0x3c);
      if ((iVar2 != 0) && (*(int *)(iVar2 + 0x50) == *(int *)(param_1 + 8))) {
        *(undefined4 *)(iVar2 + 0x50) = 0;
        *(undefined4 *)(param_1 + 0x3c) = 0;
      }
    }
  }
  else if (((param_2 == 0x3fc) || (param_2 == 0x3ff)) || (param_2 == 0x415)) {
    *(char *)(param_1 + 0x1c) = *(char *)(param_1 + 0x1c) + -1;
    return;
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void entityStrategyJessieClyde::onNotDizzy(actor *param_1,actorStrategy *strategy)

{
  BOOL BVar1;
  int iVar2;
  actorBody *local_4;
  
  local_4 = (actorBody *)strategy;
  BVar1 = actorStrategy::updateAndGetTarget(strategy,&local_4,0);
  if (((BVar1 != 0) && (iVar2 = FUN_00138410(), iVar2 != 0)) && (iVar2 = FUN_001383a0(), iVar2 != 0)
     ) {
    return;
  }
  if (strategy[1].parentActor == (actor *)0x0) {
    FUN_000b81b0(param_1,strategy);
    return;
  }
  FUN_000b8100();
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


undefined ** entityStrategyJessieClyde::getVTable(void)

{
  vtable[0] = &LAB_000b9420;
  vtable[1] = &LAB_000b9490;
  vtable[2] = FUN_000b95a0;
  vtable[3] = &DAT_000b9750;
  vtable[4] = update;
  vtable[5] = FUN_000b9a20;
  vtable[6] = FUN_000b9ac0;
  return vtable;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void entityStrategyJessieClyde::update(actorStrategy *strategy)

{
  actorStrategyOffsetId aVar1;
  actorBody *paVar2;
  int iVar3;
  uint uVar4;
  actor *act;
  
  aVar1 = strategy->id;
  act = strategy->parentActor;
  if ((act->mind == (actorMind *)0x0) ||
     (paVar2 = act->mind->targetBody, paVar2 == (actorBody *)0x0)) {
    uVar4 = 1;
    if (act->traitorTimer <= 0.0) {
      uVar4 = (uint)(byte)act->randTraitoristicCombat;
    }
  }
  else if (((0.0 < act->traitorTimer) || (act->randTraitoristicCombat != '\0')) ||
          (iVar3 = FUN_001414f0(paVar2), iVar3 == 0)) {
    uVar4 = 1;
  }
  else {
    uVar4 = 0;
  }
  *(uint *)&strategy[1].field_0x4 = uVar4;
  actorStrategy::update(strategy);
  switch(aVar1) {
  case Attack_KnockBack:
    FUN_000b8970(act);
    FUN_0013d400(act);
    return;
  case Attack_KnockDown:
    FUN_000b8e30();
    FUN_0013d400(act);
    return;
  case Attack_Special:
    FUN_000b90d0(strategy);
    break;
  case Far:
    onNotDizzy(act,strategy);
    FUN_0013d400(act);
    return;
  }
  FUN_0013d400(act);
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void entityStrategyMummyCursed::onAttackKnockDown(entityStrategyMummyCursed *strategy)

{
  actorMind *paVar1;
  int iVar2;
  actorBody *body;
  weapon *wpn;
  
  paVar1 = ((strategy->strategy).parentActor)->mind;
  if ((paVar1 != (actorMind *)0x0) && (body = paVar1->targetBody, body != (actorBody *)0x0)) {
    strategy->otherAvatar = &body->currentWeapon->avatar;
    if (((*(char *)&body->largeProjectile == '\0') &&
        (wpn = body->currentWeapon, *(int *)&wpn->field_0xce0 != 0)) &&
       ((*(short *)&wpn->field_0xcdc == 2 ||
        (iVar2._0_1_ = wpn->field9_0x93c, iVar2._1_1_ = wpn->holdableType,
        iVar2._2_1_ = wpn->field_0x93e, iVar2._3_1_ = wpn->field12_0x93f, iVar2 != 0)))) {
      iVar2 = 1;
    }
    else {
      iVar2 = 5;
    }
    FUN_000bd450(strategy,iVar2);
    ((strategy->strategy).parentActor)->body->indexInStatsheet = 5;
    (strategy->strategy).field_0x1a = 1;
    return;
  }
  (*((strategy->strategy).vtable)->leaveState)(&strategy->strategy,(strategy->strategy).id);
  (strategy->strategy).id = Far;
  actorMind::removeGoals(((strategy->strategy).parentActor)->mind);
  (*((strategy->strategy).vtable)->enterState)(&strategy->strategy,Far);
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


actorStrategyVTable * entityStrategyMummyCursed::getVTable(void)

{
  vtable.getAllocDetails = FUN_000bda00;
  vtable.ctor = ctor;
  vtable.dtor = FUN_000bdb30;
  vtable.onMessage = onMessage;
  vtable.update = update;
  vtable.enterState = enterState;
  vtable.leaveState = leaveState;
  return &vtable;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields

BOOL entityStrategyMummyCursed::ctor
               (entityStrategyMummyCursed *param_1,entityStrategyMummyCursedParams *param_2)

{
  char cVar1;
  int iVar2;
  char *pcVar3;
  
  param_1->randStruct = &MummyRandStruct_00428848;
  *(undefined4 *)&param_1->field_0x18c = 0;
  param_1->curseTarget = (actor *)0x0;
  *(undefined4 *)&param_1->field_0x180 = 0;
  *(undefined4 *)&param_1->field_0x184 = 0;
  param_1->otherAvatar = (avatar *)0x0;
  if (*(int *)&param_1->field_0x190 != 0) {
    *(undefined4 *)&param_1->field_0x190 = 0;
  }
  pcVar3 = &param_2->field_0x98;
  iVar2 = 0x3c - (int)pcVar3;
  do {
    cVar1 = *pcVar3;
    pcVar3[(int)param_1 + iVar2] = cVar1;
    pcVar3 = pcVar3 + 1;
  } while (cVar1 != '\0');
  pcVar3 = &param_2->field_0x18;
  iVar2 = 0xbc - (int)pcVar3;
  do {
    cVar1 = *pcVar3;
    pcVar3[(int)param_1 + iVar2] = cVar1;
    pcVar3 = pcVar3 + 1;
  } while (cVar1 != '\0');
  pcVar3 = &param_2->field_0x118;
  iVar2 = 0x218 - (int)pcVar3;
  do {
    cVar1 = *pcVar3;
    pcVar3[(int)param_1 + iVar2] = cVar1;
    pcVar3 = pcVar3 + 1;
  } while (cVar1 != '\0');
  pcVar3 = &param_2->field_0x198;
  iVar2 = 0x198 - (int)pcVar3;
  do {
    cVar1 = *pcVar3;
    pcVar3[(int)param_1 + iVar2] = cVar1;
    pcVar3 = pcVar3 + 1;
  } while (cVar1 != '\0');
  return 1;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void entityStrategyMummyCursed::update(entityStrategyMummyCursed *strategy)

{
  actorStrategyOffsetId aVar1;
  actor *mummyActor;
  
  aVar1 = (strategy->strategy).id;
  mummyActor = (strategy->strategy).parentActor;
  FUN_000bc8a0(strategy,mummyActor);
  actorStrategy::update(&strategy->strategy);
  if (aVar1 == Attack_KnockDown) {
    FUN_000bcfb0(strategy,mummyActor);
  }
  else {
    if (aVar1 == Attack_Special) {
      FUN_000bd830();
      return;
    }
    if (aVar1 == Far) {
      FUN_000bcae0();
      return;
    }
  }
  return;
}



// WARNING: Unable to use type for symbol pMVar5
// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void entityStrategyMummyCursed::onMessage(entityStrategyMummyCursed *strategy,Message *msg)

{
  ushort uVar1;
  actor *paVar2;
  astruct_23 *paVar3;
  Buffer<> *pBVar4;
  entityStrategyMummyCursed *strategy_00;
  int iVar5;
  BOOL BVar6;
  actorDroneActionId *paVar7;
  actor *paVar8;
  Message local_c;
  Message *pMVar5;
  
  pMVar5 = msg;
  strategy_00 = strategy;
  paVar2 = (strategy->strategy).parentActor;
  actorStrategy::onMessage(&strategy->strategy,msg);
  switch((pMVar5->header).msgId) {
  case Actor_DeathCurseEnd:
                    // If the curse that ended came from this cursed mummy
    if ((pMVar5->header).someActor == paVar2) {
      paVar8 = strategy_00->curseTarget;
      local_c.header.msgId = Actor_Die;
      uVar1 = paVar8->body->health;
      local_c.header.someActor = paVar8;
      (*((paVar8->avatar).vtable)->onMessage)(paVar8,&local_c);
      dispatchActorHitMessage((uint)uVar1,0,0,0,0,0,paVar8);
      FUN_000bc770(strategy_00,paVar2);
    }
    break;
  case Actor_Dying:
    iVar5 = onActorDyingMessage(strategy_00,(int)pMVar5);
    if (iVar5 != 0) {
      FUN_000be070();
      return;
    }
    if ((pMVar5->header).someActor == paVar2) {
      FUN_000be070();
      FUN_000bc770(strategy_00,(strategy_00->strategy).parentActor);
      if (*(int *)&strategy_00->field_0x18c != 0) {
        strategy = (entityStrategyMummyCursed *)0x2c;
        (*((strategy_00->curseTarget->avatar).vtable)->onMessage)
                  (strategy_00->curseTarget,&strategy);
        return;
      }
    }
    break;
  case Actor_ForceIntro:
    actorStrategy::forceIntro(&strategy_00->strategy,0x17);
    return;
  case Actor_ProjectileHitConnected:
    if (((actor *)pMVar5[3].header.msgId == strategy_00->curseTarget) &&
       (*(actor **)((pMVar5->header).someActor[1].avatar.calloutAID + 4) == paVar2)) {
      onProjectileHit(strategy_00,paVar2);
      return;
    }
    break;
  case ActorBody_AttachedProjectile:
    paVar3 = (strategy_00->curseTarget->avatar).as23ptr;
    *(undefined4 *)&strategy_00->field_0x18c = 1;
    *(astruct_23 **)&(pMVar5->header).someActor[1].avatar.field_0x158 = paVar3;
    return;
  case Scene_ActorHit:
    BVar6 = actorStrategy::checkAndSetDying(&strategy_00->strategy);
    if (BVar6 == 0) {
      iVar5 = FUN_000b7120();
      if (iVar5 == 0) {
        FUN_001395c0();
      }
      if ((*(int *)&strategy_00->field_0x180 == 0) &&
         (BVar6 = actorBody::flagIsSet(paVar2->body,DeathCurseConnected), BVar6 == 0)) {
        FUN_00139390((Object *)strategy_00,pMVar5,0xffffffff);
      }
      if ((pMVar5->header).someActor == paVar2) {
        if ((strategy_00->strategy).fearCounter == '\0') {
          paVar2 = (strategy_00->strategy).parentActor;
          if ((paVar2->actorType == Human) || ((paVar2->node0x93c).prev != (actor_0x93c)0x0)) {
            iVar5 = 1;
          }
          else {
            iVar5 = 0;
          }
          if ((ShouldntDroneBools[iVar5] == 0) && ("\x01"[Game::CheckMoveOn] != '\0')) {
            pBVar4 = paVar2->droneActionsBuf;
            if (pBVar4 != (Buffer<> *)0x0) {
              if (pBVar4->size == pBVar4->endOfQueue) {
                paVar7 = (actorDroneActionId *)0x0;
              }
              else {
                paVar7 = (actorDroneActionId *)
                         ((int)&pBVar4->entries->actionId +
                         (uint)pBVar4->currentDroneAction * (uint)pBVar4->valueSize);
              }
              if (*paVar7 != Null) {
                return;
              }
            }
            actorStrategy::setStrategy(&strategy_00->strategy,Far);
            return;
          }
        }
      }
      else {
        iVar5 = FUN_001408e0();
        if (iVar5 != 0) {
          FUN_001395c0();
          *(undefined4 *)&strategy_00->field_0x14c = 1;
          return;
        }
      }
    }
    break;
  case Scene_AvatarRemoved:
    if ((pMVar5->header).someActor == (actor *)strategy_00->otherAvatar) {
      strategy_00->otherAvatar = (avatar *)0x0;
      FUN_000be070();
    }
    if ((pMVar5->header).someActor == strategy_00->curseTarget) {
      strategy_00->curseTarget = (actor *)0x0;
      return;
    }
    break;
  case Scene_End:
    FUN_000be070();
    FUN_000bc770(strategy_00,(strategy_00->strategy).parentActor);
    return;
  case Scene_EventComplete:
    iVar5 = FUN_000b7120();
    if (iVar5 == 0) {
      actorStrategy::onEventCompleted(strategy_00);
      return;
    }
    break;
  case Scene_EventFailed:
    iVar5 = FUN_000b7120();
    if (iVar5 == 0) {
      actorStrategy::onEventFailed(strategy_00);
      return;
    }
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields

void entityStrategyMummyCursed::enterState
               (entityStrategyMummyCursed *strategy,actorStrategyOffsetId param_2)

{
  ((strategy->strategy).parentActor)->body->indexInStatsheet = 2;
  if (param_2 == Attack_KnockDown) {
    onAttackKnockDown(strategy);
    return;
  }
  if (param_2 != Attack_Special) {
    if (param_2 != Far) {
      actorStrategy::enterState(&strategy->strategy,param_2);
      return;
    }
    *(undefined4 *)&strategy->field_0x13c = 0;
    return;
  }
  FUN_000bd8b0();
  ((strategy->strategy).parentActor)->body->indexInStatsheet = 6;
  (strategy->strategy).field_0x1a = 1;
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields

void entityStrategyMummyCursed::leaveState
               (entityStrategyMummyCursed *strategy,actorStrategyOffsetId param_2)

{
  uint8_t *puVar1;
  
  if (param_2 == Attack_KnockDown) {
    FUN_000bce80(strategy);
  }
  else {
    if (param_2 == Attack_Special) {
      FUN_000bd7d0();
      return;
    }
    if (param_2 == Far) {
      *(undefined4 *)&strategy->field_0x13c = 0;
      return;
    }
    if (((param_2 == Dying) || (param_2 == ExitExclusionRegion)) || (param_2 == Stall)) {
      puVar1 = &(strategy->strategy).fearCounter;
      *puVar1 = *puVar1 + 0xff;
      return;
    }
  }
  return;
}




undefined ** entityStrategyPlayer::getVTable(void)

{
  updateFixed_[0] = getAllocDetails;
  updateFixed_[1] = obj::returnOne;
  updateFixed_[2] = dtor;
  updateFixed_[3] = update;
  updateFixed_[4] = updateFixed_;
  updateFixed_[5] = func5;
  updateFixed_[6] = leaveState;
  return updateFixed_;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void entityStrategyPlayer::dtor(entityStrategyPlayer *param_1)

{
  if (*(int *)&param_1->field_0x48 != 0) {
    Game::NotAllowedToPause = Game::NotAllowedToPause + -1;
    *(undefined4 *)&param_1->field_0x48 = 0;
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void entityStrategyPlayer::update(entityStrategyPlayer *param_1,Message *param_2)

{
  int iVar1;
  
  switch((param_2->header).msgId) {
  case Actor_ActionEnd:
    if ((param_1->strategy).id == ButlersBrew) {
      return;
    }
    break;
  case Actor_Celebrate:
  case Scene_EventComplete:
    *(undefined4 *)&param_1->field_0x3c = 1;
    actorStrategy::onMessage(&param_1->strategy,param_2);
    return;
  case Scene_ActorHit:
    actorStrategy::checkAndSetDying(&param_1->strategy);
    actorStrategy::onMessage(&param_1->strategy,param_2);
    return;
  case Scene_Begin:
    iVar1 = FUN_000bedb0();
    if (iVar1 != 0) {
      param_1->field6_0x40 = 1;
      actorStrategy::onMessage(&param_1->strategy,param_2);
      return;
    }
    break;
  case Player_HitWalkToDestTrigger:
                    // Sets a destination?
    setDestination(param_1,param_2);
  }
  actorStrategy::onMessage(&param_1->strategy,param_2);
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void entityStrategyPlayer::updateFixed_(entityStrategyPlayer *strategy)

{
  actor *act;
  actorBody *paVar1;
  uint uVar5;
  uint correct_button;
  BOOL iVar4;
  int iVar2;
  GameState *gameState;
  actorBody *inAsset;
  InputHandlerType4 *input_events;
  actorMind *mind;
  InputHandlerType5 *pIVar2;
  actorStrategyOffsetId status;
  
  status = (strategy->strategy).id;
  act = (strategy->strategy).parentActor;
  mind = act->mind;
  paVar1 = act->body;
                    // Restores input?
  if (strategy->restorePlayerInput != 0) {
    if ((paVar1->flagSet->flags->attackFlags_ & 0x10000) != Null) {
      paVar1->field13_0x30 = paVar1->field13_0x30 - 1;
      strategy->restorePlayerInput = 0;
    }
    if (strategy->restorePlayerInput != 0) {
      InputHandlerBase::init(act->input_handler_);
    }
  }
                    // Patching this prevents me from becoming unstuck after a cutscene (DOESN'T
                    // BREAK ME IF IM ALREADY ABLE TO MOVE THOUGH!)
                    // - also breaks input
  actorStrategy::update(&strategy->strategy);
  switch(status) {
  case ButlersBrew:
    input_events = (InputHandlerType4 *)act->input_handler_;
    FUN_00109180(input_events,(vec2 *)&DAT_0030d390);
    FUN_00108fc0();
    RunInputCallbacks((InputHandlerType1 *)input_events);
    if ((0x7fffffff < (uint)Cutscene::CurrentCutsceneIndex) && (Game::DialogState == NotInDialog)) {
      FUN_0012d4a0();
      FUN_00130710(gameState,0,(uint)paVar1->health);
      BaronDraw_00433c10.scalar = 2.0;
      UI::LoadHealthTextures(inAsset);
      uVar5 = Input::ContextHasButton(BUTTON_A,(InputHandlerType3 *)input_events);
      if (uVar5 != 0) {
        Audio::Play("XACT_SOUNDBANK_GSUPERSCARYSTUF_RIGHTBUTTON",1,uVar5,0.0);
        ::actor::executeCallout(act,0,Accept);
        Game::Save.field4_0x10 = Game::Save.field4_0x10 + 1;
        DAT_00430d98 = 1;
        FUN_0012d510();
        paVar1->health = paVar1->health << 1;
        actorStrategy::setStrategy(&strategy->strategy,Interactive);
        Events::UpdateActionBeginEnds(0xff,1);
        FUN_0013ff30();
        return;
      }
      iVar4 = avatar::decreaseTimer(&act->avatar,&strategy->field19_0x50);
      if ((iVar4 != 0) ||
         (iVar4 = Input::ContextHasButton(BUTTON_B,(InputHandlerType3 *)input_events), iVar4 != 0))
      {
        correct_button = Input::ContextHasButton(BUTTON_B,(InputHandlerType3 *)input_events);
        if (correct_button == 0) {
          Audio::Play("XACT_SOUNDBANK_GSUPERSCARYSTUF_WRONGBUTTON",1,0,0.0);
        }
        else {
          Audio::Play("XACT_SOUNDBANK_GSUPERSCARYSTUF_RIGHTBUTTON",1,correct_button,0.0);
          ::actor::executeCallout(act,0,Decline);
        }
        BaronDraw_00545994.scalar = 2.0;
        FLOAT_ARRAY_005459a8[1] = 0.0;
        FLOAT_ARRAY_005459a8[0] = 0.0;
        FUN_0012f990(&g_someVec3,(int *)FLOAT_ARRAY_005459a8);
        FUN_0012d4e0();
        actorStrategy::setStrategy(&strategy->strategy,Interactive);
        Events::UpdateActionBeginEnds(0xff,1);
        return;
      }
    }
    break;
  case Celebrate:
  case Dying:
    pIVar2 = (InputHandlerType5 *)act->input_handler_;
    switch((pIVar2->header).type) {
    case TYPE_1:
      InputHandlerType1::init((InputHandlerType1 *)pIVar2);
      return;
    case TYPE_2:
      InputHandlerType1::init((InputHandlerType1 *)pIVar2);
      return;
    default:
      return;
    case TYPE_4_NESTED:
      InputHandlerType4::init((InputHandlerType4 *)pIVar2);
      return;
    case TYPE_5:
      InputHandlerType5::init(pIVar2);
      return;
    }
  case Idle:
                    // If the player is pressing stuff, no longer idle
    iVar4 = Input::PlayerIsPressingAnything(act);
    if (iVar4 == 0) {
      if ((mind->actionInfo).next == (actorGoalInfo *)0x0) {
        actorMind::setGoalFromScript(mind,"idle");
        return;
      }
    }
    else {
      actorStrategy::setStrategy(&strategy->strategy,Interactive);
    }
    break;
  case Interactive:
                    // Normal?
    iVar4 = actorStrategy::checkAndSetDying(&strategy->strategy);
    if (iVar4 != 0) {
      strategy->field6_0x40 = 0;
      return;
    }
    if (strategy->field6_0x40 != 0) {
                    // Enter super scary shock?
      strategy->field6_0x40 = 0;
      (strategy->strategy).actorStrategyId = ButlersBrew;
      (strategy->strategy).actorStrategyId2 = ButlersBrew;
      actorStrategy::setStrategy(&strategy->strategy,ButlersBrew);
      return;
    }
    if (*(int *)&strategy->field_0x3c == 0) {
      iVar2 = FUN_000bf600(paVar1,(int)act,(int)strategy);
      if (iVar2 != 0) {
        actorStrategy::setStrategy(&strategy->strategy,Idle);
        return;
      }
    }
    else {
      iVar2 = FUN_00024c20(paVar1);
      if (iVar2 != 0) {
        if ((g_pauseMenuState_ != Paused) && (iVar2 = FUN_000d0690(), iVar2 == 0)) {
          actorStrategy::setStrategy(&strategy->strategy,Celebrate);
        }
        *(undefined4 *)&strategy->field_0x3c = 0;
        return;
      }
    }
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void switchD_000bf42d::caseD_3f1(void)

{
  int unaff_ESI;
  int unaff_EDI;
  
  *(undefined2 *)(unaff_ESI + 0x18) = 0x408;
  *(undefined2 *)(unaff_ESI + 0x12) = 0x408;
  *(char *)(unaff_ESI + 0x1c) = *(char *)(unaff_ESI + 0x1c) + -1;
  Game::NotAllowedToPause = Game::NotAllowedToPause + -1;
  if (((unaff_EDI == 0x3fc) || (unaff_EDI == 0x3ff)) || (unaff_EDI == 0x415)) {
    *(char *)(unaff_ESI + 0x1c) = *(char *)(unaff_ESI + 0x1c) + -1;
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields

void __fastcall

entityStrategyPlayer::setDestination(entityStrategyPlayer *strategy,Message *param_2)

{
  Marker *marker;
  Marker *pMVar1;
  uint uVar2;
  uint16_t index;
  MessageHeader local_24;
  actor *act;
  uint num_markers;
  
  index = *(uint16_t *)&(param_2->header).someActor;
  act = (strategy->strategy).parentActor;
  if (index != 0) {
    num_markers = (Game::GameState.markerInstance)->numMarkers;
    marker = (Game::GameState.markerInstance)->marker;
    do {
      uVar2 = 0;
      pMVar1 = marker;
      if (num_markers != 0) {
        do {
          if (pMVar1->id == index) break;
          uVar2 = uVar2 + 1;
          pMVar1 = (Marker *)((int)&pMVar1->size + pMVar1->size);
        } while (uVar2 < num_markers);
      }
      num_markers = 0;
      local_24.msgId = Actor_SetDroneAction;
      local_24.someActor = (actor *)0x8;
      if ((Game::GameState.markerInstance)->numMarkers != 0) {
        do {
          if (marker->id == index) break;
          num_markers = num_markers + 1;
          marker = (Marker *)((int)&marker->size + marker->size);
        } while (num_markers < (Game::GameState.markerInstance)->numMarkers);
      }
                    // Update actor using local 24?
                    // 
                    // actor->update()
      (*((act->avatar).vtable)->onMessage)(act,&local_24);
      num_markers = (Game::GameState.markerInstance)->numMarkers;
      marker = (Game::GameState.markerInstance)->marker;
      uVar2 = 0;
      pMVar1 = marker;
      if (num_markers == 0) {
        return;
      }
      while (pMVar1->id != index) {
        pMVar1 = (Marker *)((int)&pMVar1->size + pMVar1->size);
        uVar2 = uVar2 + 1;
        if (num_markers <= uVar2) {
          return;
        }
      }
      index = pMVar1->runtimeId;
    } while (index != 0);
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


undefined ** entityStrategySpider::getVTable(void)

{
  vtable[0] = &LAB_000a9fc0;
  vtable[1] = obj::returnOne;
  vtable[2] = switchD_000d4179::EmptyFunction;
  vtable[3] = onMessage;
  vtable[4] = update;
  vtable[5] = &DAT_000c1040;
  vtable[6] = &LAB_000b5af0;
  return vtable;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void entityStrategySpider::update(actorStrategy *param_1)

{
  actorStrategyOffsetId aVar1;
  actor *paVar2;
  actorMind *mind;
  actorStrategy *strategy;
  actorStrategy *paVar3;
  int iVar4;
  char *goalName;
  int iVar5;
  actorStrategyVTable *paVar6;
  float fVar7;
  
  strategy = param_1;
  aVar1 = param_1->id;
  paVar2 = param_1->parentActor;
  mind = paVar2->mind;
  if (runtime::dx_timer <= 0.0) {
    paVar6 = (actorStrategyVTable *)(runtime::DeltaTime * runtime::TimeScale);
  }
  else {
    paVar6 = (actorStrategyVTable *)0x0;
  }
  fVar7 = 0.0;
  if ((paVar2->avatar).movementFreezeTimer <= 0.0) {
    fVar7 = (paVar2->avatar).actionSpeed;
  }
  if (0.0 < (float)param_1[1].vtable) {
    paVar6 = (actorStrategyVTable *)((float)param_1[1].vtable - fVar7 * (float)paVar6);
    param_1[1].vtable = paVar6;
    if ((float)paVar6 <= 0.0) {
      param_1[1].vtable = (actorStrategyVTable *)0x0;
    }
  }
  actorStrategy::update(param_1);
  switch(aVar1) {
  case Approach:
    iVar5 = FUN_00139aa0(&param_1,0);
    if (iVar5 != 0) {
      FUN_000c0af0();
      if ((mind->actionInfo).next == (actorGoalInfo *)0x0) {
        iVar5 = FUN_000c0620(param_1);
      }
      else {
        iVar5 = 0;
      }
      iVar4 = FUN_000c1150();
      if (iVar4 != 0) {
        FUN_000c11f0();
        return;
      }
      if (iVar5 != 0) {
        actorStrategy::setStrategy(strategy,Observe);
        return;
      }
    }
    break;
  case Attack_KnockBack:
    iVar5 = FUN_00139aa0(&param_1,0);
    paVar3 = param_1;
    if (iVar5 == 0) {
      return;
    }
    if (*(int *)&strategy[1].field_0x4 == 0) {
      FUN_000c0af0();
      if ((mind->actionInfo).next == (actorGoalInfo *)0x0) {
        iVar5 = FUN_000c0620(paVar3);
        *(int *)&strategy[1].field_0x4 = iVar5;
        if (iVar5 == 0) goto LAB_000c0d31;
        if (paVar3 == (actorStrategy *)0x0) {
LAB_000c0d23:
          goalName = "attack_nodelay";
        }
        else {
          iVar5 = FUN_00141490();
          goalName = "attack";
          if (iVar5 == 0) goto LAB_000c0d23;
        }
        actorMind::setGoalFromScript(mind,goalName);
        goto LAB_000c0d31;
      }
    }
    else {
LAB_000c0d31:
      if ((mind->actionInfo).next == (actorGoalInfo *)0x0) {
        actorStrategy::setStrategy(strategy,Observe);
      }
    }
    iVar5 = FUN_000c1150();
    if (iVar5 == 0) {
LAB_000c0d55:
      actorStrategy::setStrategy(strategy,Observe);
      return;
    }
    break;
  case Attack_Special:
    iVar5 = FUN_00139aa0(&param_1,0);
    paVar3 = param_1;
    if (iVar5 == 0) {
      return;
    }
    if ((*(int *)&strategy[1].field_0x4 == 0) &&
       (FUN_000c0af0(), (mind->actionInfo).next == (actorGoalInfo *)0x0)) {
      iVar5 = FUN_000c0620(paVar3);
      *(int *)&strategy[1].field_0x4 = iVar5;
      if (iVar5 != 0) {
        actorMind::removeGoals(mind);
        actorMind::setGoalFromScript(mind,"stickywebspit");
      }
    }
    iVar5 = FUN_000c1150();
    if (iVar5 != 0) {
      if ((mind->actionInfo).next != (actorGoalInfo *)0x0) {
        FUN_000c1290();
        return;
      }
      iVar5 = FUN_000c1190();
      if (iVar5 == 0) {
        actorStrategy::setStrategy(strategy,Approach);
        return;
      }
      actorStrategy::setStrategy(strategy,Attack_KnockBack);
      return;
    }
    goto LAB_000c0d55;
  case Far:
    iVar5 = FUN_00139aa0(&param_1,0);
    if (iVar5 != 0) {
      iVar5 = FUN_00138410();
      if (iVar5 == 0) {
        strategy->parentActor->skipObjectTypeLookup = 0;
        actorStrategy::setStrategy(strategy,Approach);
        return;
      }
      iVar5 = FUN_001383a0();
      if (iVar5 != 0) {
        return;
      }
    }
    FUN_000c0af0();
    if ((mind->actionInfo).next == (actorGoalInfo *)0x0) {
      FUN_000c08a0();
    }
    break;
  case Observe:
    iVar5 = FUN_00139aa0(&param_1,0);
    if ((iVar5 != 0) &&
       ((FUN_000415a0(), 6400.0 < (float)paVar6 || (iVar5 = FUN_000c1150(), iVar5 != 0)))) {
      actorStrategy::setStrategy(strategy,Approach);
      return;
    }
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void entityStrategySpider::onMessage(actorStrategy *param_1,Message *msg)

{
  actor *paVar1;
  int iVar2;
  BOOL BVar3;
  
  paVar1 = param_1->parentActor;
  iVar2 = FUN_001384f0(param_1,msg);
  if (iVar2 == 0) {
    switch((msg->header).msgId) {
    case Actor_Dying:
      entityStrategyMummyCursed::onActorDyingMessage((entityStrategyMummyCursed *)param_1,(int)msg);
      return;
    case Actor_ForceIntro:
      actorStrategy::forceIntro(param_1,0x1a);
      return;
    case Scene_ActorHit:
      actorStrategy::onMessage(param_1,msg);
      BVar3 = actorStrategy::checkAndSetDying(param_1);
      if (BVar3 != 0) {
        return;
      }
      iVar2 = FUN_00139390((Object *)param_1,msg,0xffffffff);
      if (iVar2 == 0) {
        FUN_001395c0();
      }
      if ((actor *)msg[1].header.msgId != paVar1) {
        return;
      }
      param_1[1].vtable = (actorStrategyVTable *)0x40a00000;
      actorStrategy::setStrategy(param_1,Celebrate);
      return;
    case Scene_EventComplete:
      actorStrategy::onEventCompleted(param_1);
      return;
    case Scene_EventFailed:
      actorStrategy::onEventFailed(param_1);
      return;
    }
  }
  actorStrategy::onMessage(param_1,msg);
  return;
}




void entityStrategyUglyGirl::getAllocDetails(undefined4 *param_1)

{
  *param_1 = 0xbc;
  param_1[1] = 0x98;
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


actorStrategyVTable * entityStrategyUglyGirl::getVTable(void)

{
  actorStrategyVTable_00506010.getAllocDetails = getAllocDetails;
  actorStrategyVTable_00506010.ctor = ctor;
  actorStrategyVTable_00506010.dtor = switchD_000d4179::EmptyFunction;
  actorStrategyVTable_00506010.onMessage = actorStrategy::entityStrategyUglyGirl::onMessage;
  actorStrategyVTable_00506010.update = update;
  actorStrategyVTable_00506010.enterState = enterState;
  actorStrategyVTable_00506010.leaveState = leaveState;
  return &actorStrategyVTable_00506010;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields

undefined4

entityStrategyUglyGirl::ctor(entityStrategyUglyGirl *param_1,entityStrategyUglyGirlParams *param_2)

{
  char cVar1;
  int iVar2;
  char *pcVar3;
  
  pcVar3 = param_2->field1_0x18;
  iVar2 = 0x3c - (int)pcVar3;
  do {
    cVar1 = *pcVar3;
    pcVar3[(int)param_1 + iVar2] = cVar1;
    pcVar3 = pcVar3 + 1;
  } while (cVar1 != '\0');
  return 1;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void entityStrategyUglyGirl::update(entityStrategyUglyGirl *param_1)

{
  actorStrategyOffsetId aVar1;
  actorMind *mind;
  entityStrategyUglyGirl *strategy;
  int iVar2;
  
  strategy = param_1;
  mind = ((param_1->strategy).parentActor)->mind;
  aVar1 = (param_1->strategy).id;
  actorStrategy::update(&param_1->strategy);
  if (aVar1 == Approach) {
    iVar2 = FUN_00139aa0(&param_1,0);
    if ((iVar2 != 0) && ((mind->actionInfo).next == (actorGoalInfo *)0x0)) {
      actorMind::setGoalFromScript(mind,"attack");
    }
  }
  else if (aVar1 == Far) {
    iVar2 = FUN_00139aa0(&param_1,0);
    if (iVar2 != 0) {
      ((strategy->strategy).parentActor)->skipObjectTypeLookup = 0;
      actorStrategy::setStrategy(&strategy->strategy,Approach);
      return;
    }
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void actorStrategy::entityStrategyUglyGirl::onMessage(actorStrategy *actorStrategy,Message *msg)

{
  actorStrategy::onMessage(actorStrategy,msg);
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields

void entityStrategyUglyGirl::enterState
               (entityStrategyUglyGirl *param_1,actorStrategyOffsetId param_2)

{
  actor *paVar1;
  actorMind *mind;
  int iVar2;
  uint uVar3;
  
  paVar1 = (param_1->strategy).parentActor;
  mind = paVar1->mind;
  paVar1->body->indexInStatsheet = 2;
  if (param_2 != Approach) {
    if (param_2 != Far) {
      actorStrategy::enterState(&param_1->strategy,param_2);
      return;
    }
    actorMind::setGoalFromScript(mind,"far");
    return;
  }
  if (*(int *)param_1->someAid == 0x5f646961) {
    iVar2 = avatarFxEmitter::ctor(&(paVar1->avatar).fxEmitterImpactFlash,0,1,param_1->someAid);
    if (iVar2 != 0) {
      *(undefined2 *)(iVar2 + 0xc) = 4;
      uVar3 = (uint)*(ushort *)(iVar2 + 0x18);
      goto LAB_000c14b0;
    }
  }
  uVar3 = 0;
LAB_000c14b0:
  paVar1 = (param_1->strategy).parentActor;
  *(uint *)&param_1->field_0x38 = uVar3;
  paVar1->body->indexInStatsheet = 3;
  actorMind::setGoalFromScript(mind,"attack");
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields

void entityStrategyUglyGirl::leaveState
               (entityStrategyUglyGirl *param_1,actorStrategyOffsetId param_2)

{
  uint8_t *puVar1;
  
  if (param_2 == Approach) {
    if (*(int *)&param_1->field_0x38 != 0) {
      FUN_0003cfd0((short)*(int *)&param_1->field_0x38,(param_1->strategy).parentActor);
      *(undefined4 *)&param_1->field_0x38 = 0;
    }
  }
  else if (((param_2 == Dying) || (param_2 == ExitExclusionRegion)) || (param_2 == Stall)) {
    puVar1 = &(param_1->strategy).fearCounter;
    *puVar1 = *puVar1 + 0xff;
    return;
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


entityStrategyMummyCursed::onActorDyingMessage(entityStrategyMummyCursed *strategy,int param_2)

{
  actor *paVar1;
  Buffer<> *pBVar2;
  avatar *paVar3;
  int iVar4;
  actorDroneActionId *paVar5;
  float in_XMM0_Da;
  
  paVar1 = (strategy->strategy).parentActor;
  if ((strategy->strategy).fearCounter == '\0') {
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
        if (*paVar5 != Null) {
          return 0;
        }
      }
      if ((paVar1->mind->targetActor == *(actor **)(param_2 + 4)) &&
         (iVar4 = FUN_001372f0(), iVar4 != 0)) {
        paVar3 = FUN_00128df0(&paVar1->avatar,0,0.0,(vec2 *)0x0,0xc00,(undefined *)0x0,(vec3 *)0x0);
        if ((paVar3 != (avatar *)0x0) && (FUN_001363e0(), in_XMM0_Da < 40.0)) {
          return 0;
        }
        actorStrategy::setStrategy(&strategy->strategy,Celebrate);
        return 1;
      }
    }
  }
  return 0;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


entityAvatarMiscButtonBat::create(float param_1,float param_2,vec2 *initialPos)

{
  undefined4 uVar1;
  entityAvatarMiscButtonBatParams *params;
  entityAvatarMiscButtonBat *poVar4;
  int iVar2;
  HeapTableEntry *pHVar3;
  
  params = (entityAvatarMiscButtonBatParams *)"aid_objparams_ghoulies_misc_buttonbatgold";
  if ((PTR_00506c6c->field2_0x8[4] & 0x40) == 0) {
    params = (entityAvatarMiscButtonBatParams *)"aid_objparams_ghoulies_misc_buttonbat";
  }
  params = (entityAvatarMiscButtonBatParams *)Assets::GetObjParams((char *)params);
  (params->screenPos).x = initialPos->x;
  (params->screenPos).y = initialPos->y;
  (params->screenPos).x = (params->screenPos).x - param_1 * 2.0;
  (params->screenPos).y = (params->screenPos).y - param_1 * 21.0;
  if (param_2 != -1.0) {
    params->speedMaybe = param_2;
  }
  poVar4 = (entityAvatarMiscButtonBat *)Assets::CreateEntityFromParams((objParams *)params);
  iVar2 = FindHeapOf(params);
  uVar1 = runtime::CurrentHeapToAllocateFrom;
  if (g_HeapTableBase[iVar2].heapHandle == (HANDLE)0x0) {
    pHVar3 = (HeapTableEntry *)0x0;
  }
  else {
    pHVar3 = g_HeapTableBase + iVar2;
  }
  runtime::CurrentHeapToAllocateFrom = iVar2;
  XAPILIB::HeapFree(pHVar3->heapHandle,0,params);
  runtime::CurrentHeapToAllocateFrom = uVar1;
  return poVar4;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void switchD_000d4179::EmptyFunction(void)

{
  return;
}




