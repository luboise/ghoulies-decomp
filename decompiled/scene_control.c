/* scene_control.c - Scene controllers (chapters, game select, doors) */
#include "scene_control.h"

void switchD_0002123a::caseD_f(void)

{
  FUN_00021c50();
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields

void handleHitOneWay(actorBody *body,HitContext *hitCtx,void *param_3,int param_4,
                    undefined4 *param_5)

{
  BOOL iVar1;
  
  switch(hitCtx->type1) {
  default:
    return;
  case '\x01':
  case '\x02':
  case '\b':
  case '\t':
  case '\f':
  case '\r':
  case '\x10':
    break;
  case '\x03':
  case '\x06':
  case '\a':
    iVar1 = actorBody::flagIsSet(body,IsLyingOnTheFloor);
    if (iVar1 != 0) {
      FUN_000218e0((Object *)body,(Message *)hitCtx,(void *)param_4,(int)param_3);
      return;
    }
    break;
  case '\x04':
    iVar1 = actorBody::flagIsSet(body,IsLyingOnTheFloor);
    if (iVar1 != 0) {
      FUN_000218e0((Object *)body,(Message *)hitCtx,(void *)param_4,(int)param_3);
      return;
    }
    break;
  case '\x05':
    FUN_000218e0((Object *)body,(Message *)hitCtx,(void *)param_4,(int)param_3);
    return;
  case '\v':
    FUN_00021b70(param_3);
    return;
  case '\x0e':
    FUN_00021d10(body,hitCtx);
    return;
  case '\x0f':
    FUN_00021c50(hitCtx,param_3);
    return;
  case '\x12':
    onFingeredByReaper(body,(KnockbackData *)hitCtx,param_3);
    return;
  case '\x13':
    FUN_00022010(param_3);
    if (*(int *)((int)param_3 + 4) != 0) {
      return;
    }
    *param_5 = 0;
    return;
  }
  FUN_00021760(body,(int)param_3,param_4);
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields

void FUN_000215c0(actorBody *this,Asset *param_2,KnockbackData *kbd,int *param_4,undefined4 param_5,
                 int param_6)

{
  uint32_t uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  StatetableEntry *pSVar5;
  undefined2 extraout_var;
  undefined4 uVar6;
  Asset *pAVar7;
  Asset *local_8;
  int local_4;
  
  if ((this->flagSet->flags->attackFlags_ & IsBandaged) == Null) {
    iVar3 = actorBody::calculateAndApplyDamage(this,kbd);
    local_4 = iVar3;
    if (iVar3 != 0) {
      iVar4 = FUN_00024680();
      if (this->health < (ushort)(iVar4 == 0)) {
        this->health = (ushort)(iVar4 == 0);
      }
    }
    if ((this->statetableRes != (StatetableResource *)0x0) &&
       (pSVar5 = binarySearchStateTable(this->statetableRes,&local_8,Hit),
       pSVar5 != (StatetableEntry *)0x0)) {
      FUN_00023cb0();
      FUN_0001ff60();
      this->field117_0x164 = this->field117_0x164 + 1;
      FUN_00022400(kbd);
      if (param_6 == 0) {
        iVar3 = kbd->field50_0x38;
        if (iVar3 == 0) {
          iVar3 = kbd->field49_0x34;
        }
        FUN_000246d0(iVar3);
      }
      iVar2 = local_4;
      uVar1 = kbd->field51_0x3c;
      iVar3 = kbd->field50_0x38;
      iVar4 = kbd->field49_0x34;
      *(uint *)&this->field_0x27c = (uint)kbd->field0_0x0;
      *(int *)&this->field_0x26c = iVar4;
      *(uint32_t *)&this->field_0x274 = uVar1;
      *(undefined4 *)&this->field_0x278 = 0;
      *(int *)&this->field_0x280 = local_4;
      *(int *)&this->field_0x270 = iVar3;
      *(undefined2 *)((int)&this->field116_0x160 + 2) = 0;
      FUN_00023e20(iVar3,kbd->field88_0x64);
      pAVar7 = param_2;
      local_8 = param_2;
      FUN_00023f70();
      if (iVar2 == 0) {
        local_8 = (Asset *)((float)pAVar7 * 0.5);
        param_2 = (Asset *)((float)param_2 * 0.5);
      }
      if (param_6 == 0) {
        uVar6 = CONCAT22(extraout_var,(ushort)kbd->field3_0x3);
        iVar3 = 1;
        pAVar7 = param_2;
        FUN_000244e0(&kbd->field52_0x40);
        FUN_00024970(this,0x7e,(float)local_8,param_2,pAVar7,uVar6,iVar3);
      }
      param_4[1] = 1;
      iVar3 = local_4;
    }
    *param_4 = iVar3;
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void entitySceneControlAmbientTune::getAllocDetails(undefined4 *param_1)

{
  *param_1 = 0x3c;
  param_1[1] = 8;
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


undefined ** entitySceneControlAmbientTune::getVTable(void)

{
  PTR_ARRAY_00505530[5] = switchD_000d4179::EmptyFunction;
  PTR_ARRAY_00505530[0] = getAllocDetails;
  PTR_ARRAY_00505530[1] = ctor;
  PTR_ARRAY_00505530[2] = dtor;
  PTR_ARRAY_00505530[3] = sceneControlObj::onMessage;
  PTR_ARRAY_00505530[4] = updateFixed_;
  return PTR_ARRAY_00505530;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


undefined4 entitySceneControlAmbientTune::ctor(entitySceneControlAmbientTune *param_1)

{
  uint current_chapter;
  
  FUN_00080670(&param_1->field_0x24,0x2a);
  param_1->musicIndex = 0xffffffff;
  param_1->countdown = 2;
  current_chapter = Assets::GetChapterIndexFromAID(Game::GameState.currentSceneScript);
  param_1->isRaceCountdown = (uint)(current_chapter == 9);
  return 1;
}




void entitySceneControlAmbientTune::dtor(int param_1)

{
  void *mem;
  undefined4 uVar1;
  int iVar2;
  HeapTableEntry *pHVar3;
  
  FUN_00080810();
  mem = *(void **)(param_1 + 0x24);
  iVar2 = FindHeapOf(mem);
  uVar1 = runtime::CurrentHeapToAllocateFrom;
  if (g_HeapTableBase[iVar2].heapHandle == (HANDLE)0x0) {
    pHVar3 = (HeapTableEntry *)0x0;
  }
  else {
    pHVar3 = g_HeapTableBase + iVar2;
  }
  runtime::CurrentHeapToAllocateFrom = iVar2;
  XAPILIB::HeapFree(pHVar3->heapHandle,0,mem);
  runtime::CurrentHeapToAllocateFrom = uVar1;
  return;
}




void entitySceneControlAmbientTune::updateFixed_(entitySceneControlAmbientTune *obj)

{
  int iVar1;
  float delta;
  uint countdown;
  
  delta = 0.0;
  if (runtime::dx_timer <= 0.0) {
    delta = runtime::DeltaTime * runtime::TimeScale;
  }
  countdown = obj->countdown;
  (obj->controlObj).timeElapsed = (obj->controlObj).timeElapsed + delta;
                    // dec countdown if > 0. If we hit 0, run function
  if ((countdown != 0) && (countdown = countdown - 1, obj->countdown = countdown, countdown == 0)) {
    PlayMusic(obj);
  }
  if (obj->musicIndex != 0xffffffff) {
    iVar1 = FUN_000389c0();
    if (iVar1 == 2) {
      PlayMusic(obj);
      return;
    }
  }
  return;
}




void entitySceneControlAmbientTune::PlayMusic(entitySceneControlAmbientTune *obj)

{
  int i;
  char *pcVar2;
  uint levelMusicIndex;
  asset_name music_name;
  char c;
  ushort uVar1;
  
  FUN_00080810();
  uVar1 = *(ushort *)(*(int *)&obj->field_0x24 + *(int *)&obj->field_0x28 * 2);
  i = *(int *)&obj->field_0x28 + 1;
  *(int *)&obj->field_0x28 = i;
  if (i == *(int *)&obj->field_0x2c) {
    *(undefined4 *)&obj->field_0x28 = 0;
  }
  levelMusicIndex = (uint)uVar1;
  obj->musicIndex = levelMusicIndex;
  if (obj->isRaceCountdown != 0) {
    i = 0;
    do {
      c = "XACT_SOUNDBANK_GSTREAMSWALK_CHAPTERFIVE_TIMER"[i];
      music_name[i] = c;
      i = i + 1;
    } while (c != '\0');
    Audio::PlayOrChangeByName(2,music_name);
    return;
  }
  pcVar2 = g_walkAboutAssetAIDs[levelMusicIndex];
  do {
    c = *pcVar2;
    (&stack0xffcfffc8 + levelMusicIndex * -0x80)[(int)pcVar2] = c;
    pcVar2 = pcVar2 + 1;
  } while (c != '\0');
  Audio::PlayOrChangeByName(2,music_name);
  return;
}




void entitySceneControlAttract::getAllocDetails(undefined4 *param_1)

{
  *param_1 = 0x324;
  param_1[1] = 0x188;
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


undefined ** entitySceneControlAttract::getVTable(void)

{
  vtable[0] = getAllocDetails;
  vtable[1] = ctor;
  vtable[2] = &LAB_00080bb0;
  vtable[3] = sceneControlObj::onMessage;
  vtable[4] = update;
  vtable[5] = switchD_000d4179::EmptyFunction;
  return vtable;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names


void entitySceneControlAttract::update(entitySceneControlAttract *param_1)

{
  float fVar1;
  
  fVar1 = 0.0;
  if (runtime::dx_timer <= 0.0) {
    fVar1 = runtime::DeltaTime * runtime::TimeScale;
  }
  (param_1->sceneControl).timeElapsed = (param_1->sceneControl).timeElapsed + fVar1;
  FUN_00080d20();
  if (param_1->goNext == 0) {
    handleInput(param_1);
  }
  if (runtime::dx_timer <= 0.0) {
    fVar1 = runtime::DeltaTime * runtime::TimeScale;
  }
  else {
    fVar1 = 0.0;
  }
  if ((0.0 < param_1->someTimer) &&
     (fVar1 = param_1->someTimer - fVar1, param_1->someTimer = fVar1, fVar1 <= 0.0)) {
    param_1->someTimer = 0.0;
    FUN_000809c0(param_1);
  }
  return;
}




void entitySceneControlAttract::handleInput(entitySceneControlAttract *param_1)

{
  int iVar1;
  char *pcVar2;
  char *pcVar3;
  asset_name next_playcam;
  
  pcVar2 = "aid_script_ghoulies_gameselect_gameselect";
  pcVar3 = next_playcam;
  for (iVar1 = 10; iVar1 != 0; iVar1 = iVar1 + -1) {
    *(undefined4 *)pcVar3 = *(undefined4 *)pcVar2;
    pcVar2 = pcVar2 + 4;
    pcVar3 = pcVar3 + 4;
  }
  *(undefined2 *)pcVar3 = *(undefined2 *)pcVar2;
  pcVar2 = next_playcam + 0x2a;
  for (iVar1 = 0x15; iVar1 != 0; iVar1 = iVar1 + -1) {
    pcVar2[0] = '\0';
    pcVar2[1] = '\0';
    pcVar2[2] = '\0';
    pcVar2[3] = '\0';
    pcVar2 = pcVar2 + 4;
  }
  pcVar2[0] = '\0';
  pcVar2[1] = '\0';
  Scripting::Input::ResolveHandlers();
  FUN_00109470((InputHandlerType4 *)Input::GlobalInputHandler);
                    // if anyone pressed start, set the next playercam script to the game select
  iVar1 = Input::AnyPlayerPressedAOrStart();
  if (iVar1 != 0) {
    setNextPlaycamScriptAID(1,next_playcam);
    Audio::PlayRandomBaronLaugh();
    param_1->goNext = 1;
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void entitySceneControlChapter1Scene10::getAllocDetails(undefined4 *param_1)

{
  *param_1 = 0x5c;
  param_1[1] = 8;
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


undefined ** entitySceneControlChapter1Scene10::getVTable(void)

{
  PTR_ARRAY_00505578[0] = getAllocDetails;
  PTR_ARRAY_00505578[1] = ctor;
  PTR_ARRAY_00505578[2] = updateFixed_;
  PTR_ARRAY_00505578[3] = update;
  PTR_ARRAY_00505578[4] = func4;
  PTR_ARRAY_00505578[5] = func5;
  return PTR_ARRAY_00505578;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


undefined4 entitySceneControlChapter1Scene10::ctor(entitySceneControlChapter1Scene10 *scene)

{
  updateCandleState(scene,1);
  *(undefined4 *)&scene->field_0x58 = 0;
  *(undefined4 *)&scene->field_0x2c = 0;
  return 1;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void entitySceneControlChapter1Scene10::func4(entitySceneControlChapter1Scene10 *param_1)

{
  uint uVar1;
  int iVar2;
  float fVar3;
  byte new_state;
  
  if (((g_globalFlagset & 0x400) == 0) && (g_ticksInCurrentLevel != TicksInCurrentLevel)) {
    fVar3 = 0.0;
    if (runtime::dx_timer <= 0.0) {
      fVar3 = runtime::DeltaTime * runtime::TimeScale;
    }
    Game::TimeInCurrentLevel = Game::TimeInCurrentLevel + fVar3;
    TicksInCurrentLevel = g_ticksInCurrentLevel;
  }
  uVar1 = param_1->sceneState;
  if (uVar1 == 1) {
    new_state = 2;
LAB_00081115:
    updateCandleState(param_1,new_state);
  }
  else {
    if (uVar1 != 2) {
      if (uVar1 != 4) goto LAB_0008111d;
      iVar2 = FUN_00129ea0();
      *(int *)&param_1->field_0x34 = iVar2;
      if (iVar2 != 0) {
        new_state = 3;
        goto LAB_00081115;
      }
    }
    FUN_000c7060();
  }
LAB_0008111d:
  fVar3 = 0.0;
  if (runtime::dx_timer <= 0.0) {
    fVar3 = runtime::DeltaTime * runtime::TimeScale;
  }
  (param_1->control).timeElapsed = (param_1->control).timeElapsed + fVar3;
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void entitySceneControlChapter1Scene10::updateFixed_(entitySceneControlChapter1Scene10 *param_1)

{
  if (*(int *)&param_1->field_0x3c != 0) {
    FUN_000c7260(*(int *)&param_1->field_0x3c);
    *(undefined4 *)&param_1->field_0x3c = 0;
  }
  if (*(int *)&param_1->field_0x58 != 0) {
    Game::NotAllowedToPause = Game::NotAllowedToPause + 1;
    GlobalCounter2 = GlobalCounter2 + 1;
    *(undefined4 *)&param_1->field_0x58 = 0;
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields

void entitySceneControlChapter1Scene10::update
               (entitySceneControlChapter1Scene10 *param_1,Message *param_2)

{
  char cVar1;
  ObjMsgID OVar2;
  actor *paVar3;
  int iVar4;
  undefined2 extraout_DX;
  undefined4 *puVar5;
  MessageHeader local_148;
  undefined4 uStack_140;
  undefined4 auStack_13c [4];
  undefined4 uStack_12c;
  undefined4 uStack_128;
  undefined2 uStack_120;
  char acStack_114 [140];
  char acStack_88 [132];
  
  OVar2 = (param_2->header).msgId;
  if (OVar2 == Scene_Begin) {
    updateCandleState(param_1,2);
  }
  else if (OVar2 == Scene_CutsceneFree) {
    if (((param_2->header).someActor == (actor *)param_1->cutsceneBuffer) &&
       (*(int *)&param_1->field_0x58 != 0)) {
      Game::NotAllowedToPause = Game::NotAllowedToPause + 1;
      GlobalCounter2 = GlobalCounter2 + 1;
      *(undefined4 *)&param_1->field_0x58 = 0;
    }
  }
  else if (OVar2 == Scene_SuperScaryStateChange) {
    paVar3 = (param_2->header).someActor;
    if (paVar3 == (actor *)0x1) {
      local_148.msgId = Avatar_CutScene_Begin;
      (**(code **)(**(int **)&param_1->field_0x34 + 0xc))(*(int **)&param_1->field_0x34,&local_148);
      puVar5 = auStack_13c;
      for (iVar4 = 0x4d; iVar4 != 0; iVar4 = iVar4 + -1) {
        *puVar5 = 0;
        puVar5 = puVar5 + 1;
      }
      uStack_140 = 0xb;
      auStack_13c[0] = 0;
      FUN_000306e0();
      uStack_128 = 0;
      uStack_12c = 0x23;
      iVar4 = 0;
      do {
        cVar1 = "aid_animevents_ghoulies_actor_mummy_cheer"[iVar4];
        acStack_114[iVar4] = cVar1;
        iVar4 = iVar4 + 1;
      } while (cVar1 != (char)extraout_DX);
      iVar4 = 0;
      do {
        cVar1 = "aid_anim_ghoulies_actor_mummy_cheer"[iVar4];
        acStack_88[iVar4] = cVar1;
        iVar4 = iVar4 + 1;
      } while (cVar1 != (char)extraout_DX);
      uStack_120 = extraout_DX;
      (**(code **)(**(int **)&param_1->field_0x34 + 0xc))(*(int **)&param_1->field_0x34,&uStack_140)
      ;
    }
    else if ((6 < (int)paVar3) && ((int)paVar3 < 9)) {
      local_148.someActor = (actor *)0xa;
      (**(code **)(**(int **)&param_1->field_0x34 + 0xc))
                (*(int **)&param_1->field_0x34,&local_148.someActor);
      g_globalFlagset = g_globalFlagset & 0xfffffff7;
      FUN_00116140();
      local_148.msgId = Player_GameMovesOn;
      EventLoop::NewMessage(&local_148);
    }
  }
  if ((param_2->header).msgId == Scene_End) {
    sceneControlObj::cleanupGameselect(&param_1->control);
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void entitySceneControlChapter1Scene10::func5(entitySceneControlChapter1Scene10 *param_1)

{
  if (*(int *)&param_1->field_0x3c != 0) {
    FUN_000c6c80();
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields

void entitySceneControlChapter1Scene10::updateCandleState
               (entitySceneControlChapter1Scene10 *scene,byte new_state)

{
  char cVar1;
  short sVar2;
  Cutscene *pCVar3;
  BoneAffineSubresourceEntry *pBVar4;
  int *piVar5;
  actor *paVar6;
  int iVar7;
  char *pcVar8;
  vec3 *pvVar9;
  vec3 local_12c;
  vec3 local_11c;
  undefined4 local_110;
  char local_10c [264];
  
  switch(new_state) {
  case 1:
    *(undefined4 *)&scene->field_0x34 = 0;
    scene->sceneState = (uint)new_state;
    return;
  case 2:
    pCVar3 = (Cutscene *)Cutscene::LoadFromLevel("aid_cutscene_ghoulies_chapter1_scene10_walk",0,1);
    scene->cutsceneBuffer = pCVar3;
    if ((runtime::Config::IsPal != 0) && (runtime::Config::Use60Hz == 0)) {
      pCVar3->flags = pCVar3->flags | 0x40;
    }
    Game::NotAllowedToPause = Game::NotAllowedToPause + -1;
    GlobalCounter2 = GlobalCounter2 + -1;
    pCVar3 = scene->cutsceneBuffer;
    *(undefined4 *)&scene->field_0x58 = 1;
    pCVar3->onEndCallback = endCallback;
    pCVar3->owningScene = &scene->control;
    paVar6 = (actor *)Cutscene::getEventIdFromModelName
                                (scene->cutsceneBuffer,"aid_model_ghoulies_cutscene_reliccandle");
    *(actor **)&scene->field_0x3c = paVar6;
    pBVar4 = ::actor::getModelBoneAffineByBone1(paVar6,0);
    *(BoneAffineSubresourceEntry **)&scene->field_0x44 = pBVar4;
    *(undefined4 *)&scene->field_0x40 = 0;
    *(undefined4 *)&scene->field_0x50 = 0;
    *(undefined4 *)&scene->field_0x54 = 0;
    scene->field_0x48 = 0xff;
    *(undefined4 *)&scene->field_0x4c = 0xffffffff;
    FUN_000c6fb0();
    FUN_000c7060();
    runtime::rand = runtime::rand * 0x19660d + 0x3c6ef35f;
    scene->mummyLocation =
         (int)(((float)(runtime::rand & 0x7fffff | 0b00111111100000000000000000000000) - 1.0) * 6.0)
    ;
    scene->sceneState = (uint)new_state;
    return;
  case 3:
    FUN_000c7260(*(undefined4 *)&scene->field_0x3c);
    *(undefined4 *)&scene->field_0x3c = 0;
    local_12c.x = (Graphics::CurrentCameraStruct->pos).x;
    local_12c.y = (Graphics::CurrentCameraStruct->pos).y;
    local_12c.z = (Graphics::CurrentCameraStruct->pos).z;
    if (Cutscene::CurrentCutsceneIndex < 1) {
      Cutscene::SetCutsceneCam();
    }
    else {
      EventLoop::PopImportantStack();
    }
    local_11c.x = 0.0;
    local_11c.y = 0.0;
    local_11c.z = 0.0;
    paVar6 = spawnPlayerAtLocationAndRotation
                       (&local_11c,"aid_objparams_ghoulies_weapon_candle",&local_12c);
    *(actor **)&scene->field_0x38 = paVar6;
    pvVar9 = &local_12c;
    Game::OnSceneBegin(*(short *)(&DAT_00427600 + scene->mummyLocation * 4));
    FUN_00081650(pvVar9);
    getAttackCutscene(*(undefined4 *)&scene->field_0x34,&local_12c,
                      *(int *)(&DAT_00427600 + scene->mummyLocation * 4),(int)scene,
                      (int)&scene->field_0x40);
    break;
  case 4:
    sVar2 = *(short *)(&DAT_00427600 + scene->mummyLocation * 4);
    g_globalFlagset = g_globalFlagset | 8;
    pcVar8 = local_10c;
    for (iVar7 = 0x41; iVar7 != 0; iVar7 = iVar7 + -1) {
      pcVar8[0] = '\0';
      pcVar8[1] = '\0';
      pcVar8[2] = '\0';
      pcVar8[3] = '\0';
      pcVar8 = pcVar8 + 4;
    }
    local_110 = 0xa8;
    piVar5 = (int *)Game::OnSceneBegin(sVar2);
    iVar7 = 0;
    do {
      cVar1 = "aid_ghoulybox_ghoulies_chapter1_scene10_sssmummy"[iVar7];
      local_10c[iVar7] = cVar1;
      iVar7 = iVar7 + 1;
    } while (cVar1 != '\0');
    (**(code **)(*piVar5 + 0xc))(piVar5,&local_110);
    scene->sceneState = (uint)new_state;
    return;
  }
  scene->sceneState = (uint)new_state;
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields

int entitySceneControlChapter1Scene10::getAttackCutscene
              (undefined4 param_1,undefined4 *param_2,int param_3,int param_4,int param_5)

{
  obj *poVar1;
  char *pcVar2;
  char *pcVar3;
  char local_2d8 [128];
  char local_258 [128];
  objParams local_1d8 [59];
  
  pcVar3 = "aid_cutscene_ghoulies_chapter1_scene10_attack1";
  pcVar2 = "%s_%d";
  Utils::SprintfToUpper
            (local_2d8,"%s_%d","aid_cutscene_ghoulies_chapter1_scene10_attack1",(char *)param_3,
             (char *)param_5,(char *)param_4);
  Utils::SprintfToUpper
            (local_258,"%s_%d","aid_cutscene_ghoulies_chapter1_scene10_attack2",(char *)param_3,
             pcVar2,pcVar3);
  FUN_000873a0((avatar *)local_1d8,local_2d8,param_1,0x3f0ccccd,0x3f0ccccd,param_2,(undefined4 *)0x0
               ,1,(undefined4 *)0x0,1,1,0,local_258);
  poVar1 = Assets::CreateEntityFromParams(local_1d8);
  return (int)poVar1;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields

void entitySceneControlChapter1Scene10::endCallback
               (undefined4 param_1,entitySceneControlChapter1Scene10 *scene)

{
  if (*(int *)&scene->field_0x2c == scene->mummyLocation) {
    updateCandleState(scene,4);
    return;
  }
  *(int *)&scene->field_0x2c = *(int *)&scene->field_0x2c + 1;
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void entitySceneControlChapter1Scene2::update(entitySceneControlChapter1Scene2 *this)

{
  ESCC12State EVar1;
  entitySceneControlChapter1Scene2 *this_00;
  CutsceneDescriptor *ctsc_desc;
  int iVar2;
  char cVar3;
  Cutscene *cutscene;
  uint scareIndex;
  float fVar4;
  uint pcVar2;
  byte animIndexScare;
  
  this_00 = this;
  if (((g_globalFlagset & 0x400) == 0) && (g_ticksInCurrentLevel != TicksInCurrentLevel)) {
    fVar4 = 0.0;
    if (runtime::dx_timer <= 0.0) {
      fVar4 = runtime::DeltaTime * runtime::TimeScale;
    }
    Game::TimeInCurrentLevel = Game::TimeInCurrentLevel + fVar4;
    TicksInCurrentLevel = g_ticksInCurrentLevel;
  }
  EVar1 = this->state;
  if (EVar1 == Walking) {
    if (0.0 < this->timer) {
      Cutscene::update(Cutscene::LoadedCutscenes[Cutscene::CurrentCutsceneIndex],
                       this->timer /
                       Cutscene::LoadedCutscenes[Cutscene::CurrentCutsceneIndex]->length,0.0,0);
      this_00->timer = 0.0;
    }
    if ((Cutscene::CurrentCutsceneIndex < 0) ||
       (Cutscene::LoadedCutscenes[Cutscene::CurrentCutsceneIndex]->t <
        Cutscene::LoadedCutscenes[Cutscene::CurrentCutsceneIndex]->length)) {
                    // If walking
      cutscene = Cutscene::LoadedCutscenes[Cutscene::CurrentCutsceneIndex];
      ctsc_desc = cutscene->descriptor;
      this = (entitySceneControlChapter1Scene2 *)((uint)this & 0xffffff00);
      if ('\0' < (char)ctsc_desc->numAnimResources) {
        do {
          animIndexScare = ctsc_desc->animRes->ANIM[(char)this * 100 + 0x10];
          scareIndex = (uint)animIndexScare;
          if (scareIndex != 0) {
            if (*(int *)&cutscene->animAllocsPtr[(char)this].field_0x8 == 0) {
              if (this_00->scaresUsed2[scareIndex] != 0) {
                this_00->scaresUsed2[scareIndex] = 0;
              }
            }
            else {
              iVar2 = canUseScare(this_00,animIndexScare);
                    // If its not in the list, and its not in the first table, and its not in the
                    // second table
              if (((iVar2 != 0) && (this_00->scaresUsed2[scareIndex] == 0)) &&
                 (this_00->scaresUsed1[scareIndex - 1] == 0)) {
                *(uint *)&this_00->field_0xf4 = scareIndex;
                this_00->scaresUsed2[scareIndex] = 1;
                this_00->scaresUsed1[scareIndex - 1] = 1;
                    // Start a scare
                setState(this_00,CreateScare);
              }
            }
          }
          cutscene = Cutscene::LoadedCutscenes[Cutscene::CurrentCutsceneIndex];
          ctsc_desc = cutscene->descriptor;
          cVar3 = (char)this + '\x01';
          this = (entitySceneControlChapter1Scene2 *)CONCAT31(this._1_3_,cVar3);
        } while (cVar3 < (char)ctsc_desc->numAnimResources);
      }
    }
    else {
      setState(this_00,NoScare);
    }
  }
  else if (EVar1 == NoScare) {
                    // Player_NextSceneTrigger
    this = (entitySceneControlChapter1Scene2 *)0xaf;
    EventLoop::NewMessage((MessageHeader *)&this);
  }
  else if ((EVar1 == EndOfLevel) && (Game::DialogState == NotInDialog)) {
    setState(this,Walking);
  }
  if (((*(int *)&this_00->field_0x184 == 0) && (this_00->state == Walking)) &&
     (((g_globalFlagset & 0x4400) == 0 &&
      (0.985 < Cutscene::LoadedCutscenes[Cutscene::CurrentCutsceneIndex]->t /
               Cutscene::LoadedCutscenes[Cutscene::CurrentCutsceneIndex]->length)))) {
    setState(this_00,EndOfLevel);
  }
  fVar4 = 0.0;
  if (runtime::dx_timer <= 0.0) {
    fVar4 = runtime::DeltaTime * runtime::TimeScale;
  }
  (this_00->control).timeElapsed = (this_00->control).timeElapsed + fVar4;
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


entitySceneControlChapter1Scene2::canUseScare(entitySceneControlChapter1Scene2 *this,char index)

{
  int8_t *piVar1;
  
  piVar1 = this->rngVals;
  while( true ) {
    if (*piVar1 == -1) {
      return 0;
    }
    if (*piVar1 == index) break;
    piVar1 = piVar1 + 1;
    if ((int8_t *)0x3 < piVar1 + (-0x46 - (int)this)) {
      return 0;
    }
  }
  return 1;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void entitySceneControlChapter1Scene2::generateRNG(entitySceneControlChapter1Scene2 *this)

{
  int8_t iVar1;
  void *pvVar2;
  
  this->rngVals[0] = -1;
  this->rngVals[1] = -1;
  this->rngVals[2] = -1;
  this->rngVals[3] = -1;
  do {
    runtime::rand = runtime::rand * 0x19660d + 0x3c6ef35f;
    iVar1 = (int8_t)(int)(((float)(runtime::rand & 0x7fffff | 0x3f800000) - 1.0) * 2.0 + 1.0);
    pvVar2 = doOneRNG(this,iVar1);
  } while (pvVar2 == (void *)0x0);
  this->rngVals[0] = iVar1;
  do {
    runtime::rand = runtime::rand * 0x19660d + 0x3c6ef35f;
    iVar1 = (int8_t)(int)(((float)(runtime::rand & 0x7fffff | 0x3f800000) - 1.0) * 8.0 + 4.0);
    pvVar2 = doOneRNG(this,iVar1);
  } while (pvVar2 == (void *)0x0);
  this->rngVals[1] = iVar1;
  do {
    runtime::rand = runtime::rand * 0x19660d + 0x3c6ef35f;
    iVar1 = (int8_t)(int)(((float)(runtime::rand & 0x7fffff | 0x3f800000) - 1.0) * 8.0 + 14.0);
    pvVar2 = doOneRNG(this,iVar1);
  } while (pvVar2 == (void *)0x0);
  this->rngVals[2] = iVar1;
  runtime::rand = runtime::rand * 0x19660d + 0x3c6ef35f;
  if ((float)(runtime::rand & 0x7fffff | 0x3f800000) - 1.0 < 0.5) {
    do {
      runtime::rand = runtime::rand * 0x19660d + 0x3c6ef35f;
      iVar1 = (int8_t)(int)(((float)(runtime::rand & 0x7fffff | 0x3f800000) - 1.0) * 21.0 + 1.0);
      pvVar2 = doOneRNG(this,iVar1);
    } while (pvVar2 == (void *)0x0);
    this->rngVals[3] = iVar1;
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void entitySceneControlChapter2Scene4::getVTable(undefined4 *param_1)

{
  *param_1 = 0x38;
  param_1[1] = 0x88;
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


undefined ** entitySceneControlChapter2Scene4::getVTable(void)

{
  PTR_ARRAY_005055c0[5] = switchD_000d4179::EmptyFunction;
  PTR_ARRAY_005055c0[0] = getVTable;
  PTR_ARRAY_005055c0[1] = ctor;
  PTR_ARRAY_005055c0[2] = dtor;
  PTR_ARRAY_005055c0[3] = sceneControlObj::onMessage;
  PTR_ARRAY_005055c0[4] = fixedUpdate_;
  return PTR_ARRAY_005055c0;
}



undefined4
entitySceneControlChapter2Scene4::ctor
          (entitySceneControlChapter2Scene4 *ctrl,entitySceneControlChapter2Scene4Params *param_2)

{
  NewTextureMaybe *head;
  NewTextureMaybe *tail;
  
  if (((g_finishedLoading_ != 1) && ((*SomeAS15->flags & 8) == 0)) &&
     ((g_globalFlagset & 0x200000) == 0)) {
    Cutscene::LoadFromLevel(&param_2->field_0x8,0,1);
    setState(ctrl,1);
    return 1;
  }
  if (g_bufferNewTextureMaybe != (Buffer<> *)0x0) {
    tail = g_bufferNewTextureMaybe->tail;
    head = g_bufferNewTextureMaybe->head;
    if (((int)tail - (int)head) / (int)(uint)g_bufferNewTextureMaybe->valueSize != 0) {
      for (; head < tail; head = head + 1) {
        head->field0_0x0[0x28] = '\x01';
      }
    }
  }
  ctrl->state = 4;
  return 1;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void entitySceneControlChapter2Scene4::fixedUpdate_(entitySceneControlChapter2Scene4 *control)

{
  float fVar1;
  uint state;
  
  state = control->state;
  if (state == 1) {
    if ((Cutscene::CurrentCutsceneIndex < 0) ||
       (Cutscene::LoadedCutscenes[Cutscene::CurrentCutsceneIndex]->t <
        Cutscene::LoadedCutscenes[Cutscene::CurrentCutsceneIndex]->length)) goto LAB_00082b7d;
LAB_00082b70:
    state = 3;
  }
  else {
    if (state == 2) {
      if (runtime::dx_timer <= 0.0) {
        fVar1 = runtime::DeltaTime * runtime::TimeScale;
      }
      else {
        fVar1 = 0.0;
      }
      if ((control->f1 <= 0.0) || (fVar1 = control->f1 - fVar1, control->f1 = fVar1, 0.0 < fVar1))
      goto LAB_00082b7d;
      control->f1 = 0.0;
      goto LAB_00082b70;
    }
    if (state != 3) goto LAB_00082b7d;
    if (g_bufferNewTextureMaybe->head->field0_0x0[0x28] != '\0') {
      if (runtime::dx_timer <= 0.0) {
        fVar1 = runtime::DeltaTime * runtime::TimeScale;
      }
      else {
        fVar1 = 0.0;
      }
      if ((0.0 < control->f2) && (fVar1 = control->f2 - fVar1, control->f2 = fVar1, fVar1 <= 0.0)) {
        control->f2 = 0.0;
      }
      goto LAB_00082b7d;
    }
    state = 4;
  }
  setState(control,state);
LAB_00082b7d:
  fVar1 = 0.0;
  if (runtime::dx_timer <= 0.0) {
    fVar1 = runtime::DeltaTime * runtime::TimeScale;
  }
  (control->sceneControl).timeElapsed = (control->sceneControl).timeElapsed + fVar1;
  return;
}




void entitySceneControlChapter2Scene4::dtor(void)

{
  Audio::GlobalObstructionOffset = 0;
  return;
}



void entitySceneControlChapter2Scene4::setState
               (entitySceneControlChapter2Scene4 *ctrl,uint newState)

{
  uint uVar1;
  uint state;
  
  state = newState & 0xff;
  switch(state) {
  case 1:
    Audio::GlobalObstructionOffset = 8;
    ctrl->state = state;
    return;
  case 2:
    runtime::rand = runtime::rand * 0x19660d + 0x3c6ef35f;
    uVar1 = runtime::rand & 0x7fffff;
    ctrl->state = state;
    ctrl->f1 = ((float)(uVar1 | 0x3f800000) - 1.0) * 0.5 + 0.5;
    return;
  case 3:
    FUN_00114050();
    Audio::GlobalObstructionOffset = 0;
    ctrl->state = state;
    ctrl->f2 = 0.5;
    return;
  case 4:
    break;
  case 5:
    FUN_00116140();
  default:
    ctrl->state = state;
    return;
  }
  if (Cutscene::CurrentCutsceneIndex < 1) {
    Cutscene::SetCutsceneCam();
    Game::MoveOn = Game::MoveOn + 1;
    ctrl->state = state;
    return;
  }
  EventLoop::PopImportantStack();
  Game::MoveOn = Game::MoveOn + 1;
  ctrl->state = state;
  return;
}




undefined ** entitySceneControlFinalScore::getVTable(void)

{
  PTR_ARRAY_005055f0[0] = FUN_00082d50;
  PTR_ARRAY_005055f0[1] = ctor;
  PTR_ARRAY_005055f0[2] = dtor;
  PTR_ARRAY_005055f0[3] = sceneControlObj::onMessage;
  PTR_ARRAY_005055f0[4] = update;
  PTR_ARRAY_005055f0[5] = resource19::func5;
  return PTR_ARRAY_005055f0;
}




undefined4 entitySceneControlFinalScore::ctor(entitySceneControlFinalScore *param_1)

{
  param_1->state = 0;
  Game::NotAllowedToPause = Game::NotAllowedToPause + 1;
  g_globalFlagset = g_globalFlagset | InMenu;
  FUN_000f2d70();
  FUN_000d3e30();
  param_1->state = 1;
  FUN_000d44d0();
  FUN_000d4190();
  return 1;
}




void entitySceneControlFinalScore::dtor(void)

{
  FUN_000d3fb0();
  g_globalFlagset = g_globalFlagset & ~InMenu;
  Game::NotAllowedToPause = Game::NotAllowedToPause + -1;
  return;
}




void entitySceneControlFinalScore::update(entitySceneControlFinalScore *control)

{
  int iVar1;
  char *pcVar2;
  char *pcVar3;
  undefined4 *puVar4;
  float delta;
  char acStack_88 [34];
  undefined4 auStack_66 [24];
  
  delta = 0.0;
  if (runtime::dx_timer <= 0.0) {
    delta = runtime::DeltaTime * runtime::TimeScale;
  }
  (control->control).timeElapsed = (control->control).timeElapsed + delta;
  FUN_000d4070();
  switch(control->state) {
  case 1:
    iVar1 = FUN_000d34f0();
    if (iVar1 != 0) {
      control->state = 2;
      FUN_000d41e0();
      return;
    }
    break;
  case 2:
    iVar1 = FUN_000d1da0();
    if (iVar1 != 0) {
      control->state = 3;
      FUN_000d4230();
      return;
    }
    break;
  case 3:
    iVar1 = FUN_000d4bc0();
    goto LAB_00082f12;
  case 4:
    iVar1 = FUN_000d3350();
LAB_00082f12:
    if (iVar1 != 0) {
      control->state = 5;
      pcVar2 = "aid_script_ghoulies_credits_final";
      pcVar3 = acStack_88;
      for (iVar1 = 8; iVar1 != 0; iVar1 = iVar1 + -1) {
        *(undefined4 *)pcVar3 = *(undefined4 *)pcVar2;
        pcVar2 = pcVar2 + 4;
        pcVar3 = pcVar3 + 4;
      }
      *(undefined2 *)pcVar3 = *(undefined2 *)pcVar2;
      puVar4 = auStack_66;
      for (iVar1 = 0x17; iVar1 != 0; iVar1 = iVar1 + -1) {
        *puVar4 = 0;
        puVar4 = puVar4 + 1;
      }
      *(undefined2 *)puVar4 = 0;
      FUN_000d4500();
      setNextPlaycamScriptAID(1,acStack_88);
    }
  }
  return;
}




void entitySceneControlFx::getAllocDetails(undefined4 *param_1)

{
  *param_1 = 0x1ec;
  param_1[1] = 200;
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


undefined ** entitySceneControlFx::getVTable(void)

{
  PTR_ARRAY_00505608[5] = switchD_000d4179::EmptyFunction;
  PTR_ARRAY_00505608[0] = getAllocDetails;
  PTR_ARRAY_00505608[1] = ctor;
  PTR_ARRAY_00505608[2] = switchD_000d4179::EmptyFunction;
  PTR_ARRAY_00505608[3] = sceneControlObj::onMessage;
  PTR_ARRAY_00505608[4] = updateFixed_;
  return PTR_ARRAY_00505608;
}




undefined4 entitySceneControlFx::ctor(entitySceneControlFx *obj,entitySceneControlFxParams *params)

{
  undefined1 *puVar1;
  char cVar2;
  float __x;
  int iVar3;
  entitySceneControlFxParams *peVar4;
  char *pcVar5;
  uint uVar6;
  entitySceneControlFx_ptr_224_entitySceneControlFxInner1 puVar7;
  float10 extraout_ST0;
  float10 fVar7;
  float fVar8;
  
  peVar4 = params;
  *(undefined4 *)&obj->field_0xb0 = *(undefined4 *)&params->field_0xac;
  *(undefined4 *)&obj->field_0xb4 = *(undefined4 *)&params->field_0xb0;
  obj->minF = params->field162_0xb4;
  obj->maxF = params->field163_0xb8;
  *(undefined4 *)&obj->field_0x24 = *(undefined4 *)&params->field_0x20;
  *(undefined4 *)&obj->field_0xc0 = *(undefined4 *)&params->field_0xbc;
  *(undefined4 *)&obj->field_0xc4 = *(undefined4 *)&params->field_0xc0;
  *(undefined4 *)&obj->field_0x2c = *(undefined4 *)&params->field_0x28;
  *(undefined4 *)&obj->field_0x28 = *(undefined4 *)&params->field_0x24;
  *(undefined4 *)&obj->field_0xc8 = *(undefined4 *)&params->field_0xc4;
  pcVar5 = &params->field_0x2c;
  iVar3 = 0x30 - (int)pcVar5;
  do {
    cVar2 = *pcVar5;
    pcVar5[(int)obj + iVar3] = cVar2;
    pcVar5 = pcVar5 + 1;
  } while (cVar2 != '\0');
  params = (entitySceneControlFxParams *)0x0;
  if (0 < *(int *)&obj->field_0x2c) {
    puVar7 = &obj->field172_0xe0;
    do {
      *(undefined4 *)&ADJ(puVar7)->field_0xec = 0xffffffff;
      puVar1 = &ADJ(puVar7)->field_0xcc;
      *(float *)puVar1 = (peVar4->someVec).x;
      (ADJ(puVar7)->field167_0xd0).x = (peVar4->someVec).y;
      (ADJ(puVar7)->field167_0xd0).y = (peVar4->someVec).z;
      if (*(float *)&obj->field_0x28 != 0.0) {
        uVar6 = runtime::rand * 0x19660d + 0x3c6ef35f;
        runtime::rand = uVar6 * 0x19660d + 0x3c6ef35f;
        fVar8 = ((float)(uVar6 & 0x7fffff | 0x3f800000) - 1.0) * *(float *)&obj->field_0x28;
        __x = ((float)(runtime::rand & 0x7fffff | 0x3f800000) - 1.0) * 6.2831855 - 3.1415927;
        sin(__x);
        fVar7 = (float10)cos(__x);
        *(float *)puVar1 = (float)extraout_ST0 * fVar8 + *(float *)puVar1;
        (ADJ(puVar7)->field167_0xd0).y = (float)fVar7 * fVar8 + (ADJ(puVar7)->field167_0xd0).y;
      }
      (ADJ(puVar7)->field167_0xd0).z = *(float *)&peVar4->field_0x14;
      *(undefined4 *)&ADJ(puVar7)->field_0xdc = *(undefined4 *)&peVar4->field_0x18;
      ADJ(puVar7)->field172_0xe0 = *(float *)&peVar4->field_0x1c;
      if (((*(float *)&obj->field_0xb0 == 0.0) && (*(float *)&obj->field_0xb4 == 0.0)) ||
         ((obj->minF == 0.0 && (obj->maxF == 0.0)))) {
        FUN_00083080(1);
      }
      else {
        runtime::rand = runtime::rand * 0x19660d + 0x3c6ef35f;
        if ((float)(runtime::rand & 0x7fffff | 0x3f800000) - 1.0 <= 0.5) {
          FUN_00082ff0(obj,(int)puVar1);
        }
        else {
          FUN_00083080(1);
        }
      }
      params = (entitySceneControlFxParams *)
               ((int)&(params->controlObjParams).objParams.paramsSize + 1);
      puVar7 = (entitySceneControlFx_ptr_224_entitySceneControlFxInner1)&ADJ(puVar7)->field_0x104;
    } while ((int)params < *(int *)&obj->field_0x2c);
  }
  return 1;
}




void entitySceneControlFx::updateFixed_(int param_1)

{
  float fVar1;
  
  if (runtime::dx_timer <= 0.0) {
    fVar1 = runtime::DeltaTime * runtime::TimeScale;
  }
  else {
    fVar1 = 0.0;
  }
  *(float *)(param_1 + 0x20) = *(float *)(param_1 + 0x20) + fVar1;
  if (0.0 < runtime::dx_timer) {
    FUN_00083280(0,0);
    return;
  }
  FUN_00083280(runtime::DeltaTime * runtime::TimeScale,0);
  return;
}




void entitySceneControlGameSelect::getAllocDetails(ObjectAllocDetails *param_1)

{
  param_1->entitySize = 0x12c;
  param_1->paramsSize = 8;
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


undefined ** entitySceneControlGameSelect::getVTable(void)

{
  vtable[0] = getAllocDetails;
  vtable[1] = ctor;
  vtable[2] = dtor;
  vtable[3] = sceneControlObj::onMessage;
  vtable[4] = update;
  vtable[5] = func5;
  return vtable;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


BOOL entitySceneControlGameSelect::ctor(entitySceneControlGameSelect *control)

{
  Camera *pCVar1;
  TextureHeader *new_tex;
  ReplayChapterMenu *aid_list;
  CameraLLNode *ppcVar6;
  int i;
  uint uVar8;
  uint uVar9;
  char *aid_ptr;
  char *c_ptr;
  char *pcVar10;
  byte *puVar11;
  void *local_94;
  int vStack_90;
  undefined1 auStack_8c [4];
  undefined1 auStack_88 [4];
  asset_name gameselect_text_aid;
  MenuVTable **res_vtable;
  Camera *maybe_v;
  astruct_15 *paVar4;
  
  paVar4 = SomeAS15;
  c_ptr = gameselect_text_aid;
  aid_ptr = "aid_loctext_ghoulies_gameselect_gameselecttext";
  for (i = 11; c_ptr = c_ptr + 4, i != 0; i = i + -1) {
    *(undefined4 *)c_ptr = *(undefined4 *)aid_ptr;
    aid_ptr = aid_ptr + 4;
  }
  *(undefined2 *)c_ptr = *(undefined2 *)aid_ptr;
  c_ptr[2] = aid_ptr[2];
  pcVar10 = gameselect_text_aid + 0x33;
  for (i = 0x14; i != 0; i = i + -1) {
    pcVar10[0] = '\0';
    pcVar10[1] = '\0';
    pcVar10[2] = '\0';
    pcVar10[3] = '\0';
    pcVar10 = pcVar10 + 4;
  }
  uVar9 = SomeAS15->field1_0x4;
  *pcVar10 = '\0';
  puVar11 = SomeAS15->flags;
  for (uVar8 = uVar9 >> 2; uVar8 != 0; uVar8 = uVar8 - 1) {
    puVar11[0] = 0;
    puVar11[1] = 0;
    puVar11[2] = 0;
    puVar11[3] = 0;
    puVar11 = puVar11 + 4;
  }
  for (uVar9 = uVar9 & 3; uVar9 != 0; uVar9 = uVar9 - 1) {
    *puVar11 = 0;
    puVar11 = puVar11 + 1;
  }
  puVar11 = paVar4->flags;
  *puVar11 = *puVar11 | 2;
  puVar11 = paVar4->flags;
  Game::Save.timeSeconds = 0;
  Game::Save.numKills = 0;
  Game::Save.numDeaths = 0;
  Game::Save.numPrisoners = 0;
  Game::Save.field4_0x10 = 0;
  Game::DeathsInCurrentRoom = 0;
  *puVar11 = *puVar11 | 4;
  runtime::SaveTheGame_();
  g_globalFlagset = g_globalFlagset | InMenu;
  control->menuID = None;
  control->newMenuID = None;
  control->status = 1;
  control->field9_0x11c = 1;
  control->harddisk0SpaceUsed = 0;
  new_tex = Graphics::CreateTextureHeader(640,480,1,D3DFMT_LIN_X8L8V8U8,(void *)0x0);
  control->tex = new_tex;
  control->playerChoice = NoChoice;
  if (gameselect_text_aid._4_4_ == 0x5f646961) {
    Assets::GetResourceBytes(gameselect_text_aid + 4,&local_94);
    if (local_94 == (void *)0x0) {
      runtime::ExitGame(2);
    }
  }
  else {
    local_94 = (void *)0x0;
  }
  res_vtable = &control->menuVTable;
  PTR_005462c4 = local_94;
  control->gamePauseCtx = (GamePauseContext *)0x0;
  *res_vtable = (MenuVTable *)0x0;
  getLastMenuUsed(res_vtable);
  SetGlobalSceneOrder("aid_aidlist_ghoulies_sceneorder_game");
  aid_list = (ReplayChapterMenu *)(*(*res_vtable)->alloc)();
  control->menuInstance = aid_list;
                    // Load Dialogs
  (*(*res_vtable)->ctor)(control,aid_list);
  maybe_v = &control->maybeVertex;
  Camera::ctor(maybe_v,"gameselect",(ProjectionSetBitField)0x8);
  (control->maybeVertex).aspectRatioType = 0;
  Camera::ComputeTangents
            ((control->maybeVertex).fov,&vStack_90,(float *)gameselect_text_aid,(float *)&local_94,
             &(control->maybeVertex).aspectRatio,&(control->maybeVertex).cotangentOffset,0,
             auStack_8c,auStack_88);
  ppcVar6 = Camera::AvailableConfigs;
  pCVar1 = Camera::AvailableConfigs[0].head;
  while (pCVar1 != (Camera *)0x0) {
    ppcVar6 = (CameraLLNode *)((Camera *)ppcVar6)->next;
    pCVar1 = ((Camera *)ppcVar6)->next;
  }
  pCVar1 = ((Camera *)ppcVar6)->prev;
  ((Camera *)ppcVar6)->prev = maybe_v;
  maybe_v->next = (Camera *)ppcVar6;
  (control->maybeVertex).prev = pCVar1;
  if (pCVar1 != (Camera *)0x0) {
    pCVar1->next = maybe_v;
  }
  if (Camera::ActiveConfigs[0] == (Camera *)0x0) {
    Camera::SetActiveCameraConfig(0,(control->maybeVertex).name);
  }
  Game::NotAllowedToPause = Game::NotAllowedToPause + 1;
                    // Create input handler for menu?
  runtime::PushInputHandlerAndSetActive(&Input::MenuInputHandler->header,"game select");
  return 1;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void entitySceneControlGameSelect::dtor(entitySceneControlGameSelect *param_1)

{
  FUN_000e5b70();
  (*param_1->menuVTable->dtor)(param_1->menuInstance);
  (*param_1->menuVTable->dealloc)(param_1->menuInstance);
  Camera::setActiveCamera(&param_1->maybeVertex);
  Assets::DestroyAssetOrDecrement(PTR_005462c4);
  if (param_1->gamePauseCtx != (GamePauseContext *)0x0) {
    FromPlayToPause(param_1->gamePauseCtx);
  }
  Game::NotAllowedToPause = Game::NotAllowedToPause + -1;
  FreePhysicalTexture(param_1->tex);
  Scripting::PopInputHandler();
  g_globalFlagset = g_globalFlagset & ~InMenu;
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void entitySceneControlGameSelect::update(entitySceneControlGameSelect *entity)

{
  MenuID MVar1;
  int iVar2;
  void *newMenu;
  float time;
  
  time = 0.0;
  if (runtime::dx_timer <= 0.0) {
    time = runtime::DeltaTime * runtime::TimeScale;
  }
  (entity->sceneControlObj).timeElapsed = (entity->sceneControlObj).timeElapsed + time;
  FUN_00109470((InputHandlerType4 *)Input::MenuInputHandler);
  if (entity->harddisk0SpaceUsed != 0) {
    if (entity->playerChoice == ContinueStory) {
                    // Load regular game
      continueStory(entity);
    }
    else {
      if (entity->playerChoice != ReplayLevelOrChapter) goto LAB_0008393b;
      onReplayLevel(entity);
    }
    entity->playerChoice = NoChoice;
  }
LAB_0008393b:
  if (entity->newMenuID != None) {
    iVar2 = FUN_00083e20(entity);
    if (iVar2 != 0) {
      (*entity->menuVTable->dtor)(entity->menuInstance);
      (*entity->menuVTable->dealloc)(entity->menuInstance);
      MVar1 = entity->newMenuID;
      entity->menuID = MVar1;
      entity->newMenuID = None;
      entity->menuVTable = menu::vtableLookup + MVar1;
                    // goes to 0x4dea0, resource8::alloc
      newMenu = (void *)(*menu::vtableLookup[MVar1].alloc)();
      entity->menuInstance = newMenu;
      (*entity->menuVTable->ctor)(entity,newMenu);
    }
  }
  (*entity->menuVTable->update)(entity->menuInstance);
  if (entity->status == 2) {
    FUN_00083d90(entity);
  }
  else if (entity->status == 3) {
    FUN_00083d90(entity);
    return;
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void entitySceneControlGameSelect::func5(entitySceneControlGameSelect *param_1)

{
  float fVar1;
  int iVar2;
  float *extraout_ECX;
  float *extraout_EDX;
  
  iVar2 = FUN_000489e0(&param_1->maybeVertex);
  if (iVar2 != 0) {
    Graphics::RecalculateWorldAndViews();
    FUN_0013c490(&(param_1->maybeVertex).float5,&(param_1->maybeVertex).field5_0x28,
                 &Graphics::CurrentCameraStruct->affineT);
    fVar1 = *extraout_ECX;
    Graphics::CurrentCameraStruct->near = *extraout_EDX;
    Graphics::CurrentCameraStruct->far = fVar1;
    Graphics::UpdatePerspectiveProj();
    Graphics::UpdateViewport2();
  }
                    // WARNING: Could not recover jumptable at 0x00083a46. Too many branches
                    // WARNING: Treating indirect jump as call
  (*param_1->menuVTable->draw)();
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


entitySceneControlGameSelect::isStatus2Or3(entitySceneControlGameSelect *param_1)

{
  int iVar1;
  
  if ((TransitionData.discReadEnum == 0) &&
     ((((iVar1 = param_1->status, iVar1 == 1 || (iVar1 < 2)) || (3 < iVar1)) ||
      (param_1->gamePauseCtx == (GamePauseContext *)0x0)))) {
    return 0;
  }
  return 1;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


BOOL entitySceneControlGameSelect::continueStory(entitySceneControlGameSelect *param_1)

{
  int iVar1;
  astruct_15 *paVar2;
  byte *pbVar3;
  byte bVar4;
  char local_80 [128];
  
  paVar2 = SomeAS15;
  iVar1 = param_1->field9_0x11c;
  if (iVar1 == 1) {
    pbVar3 = SomeAS15->flags;
    bVar4 = *pbVar3 | 2;
LAB_00083cb9:
    *pbVar3 = bVar4;
    pbVar3 = paVar2->flags;
    bVar4 = *pbVar3 | 4;
  }
  else {
    if (iVar1 == 2) {
      pbVar3 = SomeAS15->flags;
      bVar4 = *pbVar3 & 0xfd;
      goto LAB_00083cb9;
    }
    if (iVar1 != 3) goto LAB_00083cc5;
    *SomeAS15->flags = *SomeAS15->flags & 0xfd;
    pbVar3 = paVar2->flags;
    bVar4 = *pbVar3 & 0xfb;
  }
  *pbVar3 = bVar4;
LAB_00083cc5:
  XAPILIB::lstrcpyW(game::oldNextPlaycamScriptWide,game::nextPlaycamScriptWide);
  runtime::SaveTheGame_();
  runtime::GetLatestLoadableScript(local_80,game::nextPlaycamScriptWide);
  setNextPlaycamScriptAID(1,local_80);
  return 1;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void entitySceneControlMapView::getAllocDetails(undefined4 *param_1)

{
  *param_1 = 0x30;
  param_1[1] = 8;
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


undefined ** entitySceneControlMapView::getVTable(void)

{
  vtable[5] = switchD_000d4179::EmptyFunction;
  vtable[0] = getAllocDetails;
  vtable[1] = ctor;
  vtable[2] = dtor;
  vtable[3] = sceneControlObj::onMessage;
  vtable[4] = fixedUpdate_;
  return vtable;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


undefined4 entitySceneControlMapView::ctor(entitySceneControlMapView *control)

{
  BOOL is_match;
  GamePauseContext *iVar3;
  char *pcVar1;
  AssetPlaycamLocator *cam_script;
  int i;
  uint uVar5;
  char cVar1;
  
  i = 0;
  cam_script = g_mapViewPlaycams;
  uVar5 = 0;
  do {
    is_match = Assets::AssetNamesMatch(Game::GameState.currentSceneScript,cam_script->aid);
    if (is_match != 0) {
      iVar3 = GamePauseContext::ctor(g_mapViewPlaycams[i].playcamScriptId,1,(char *)0x0);
      control->pauseCtx = iVar3;
      iVar3->field6_0xc = 1;
      iVar3->field8_0x14 = 1;
      *(undefined4 *)&iVar3->field_0x18 = 0;
      iVar3->locationStr[0] = '\0';
      iVar3->field_0x138 = 0;
      pcVar1 = g_mapViewPlaycams[i].scriptLocation;
      iVar3 = control->pauseCtx;
                    // Copy the location string in
      if (pcVar1 == (char *)0x0) {
        iVar3->locationStr[0] = '\0';
      }
      else {
        i = 0x118 - (int)pcVar1;
        do {
          cVar1 = *pcVar1;
          pcVar1[(int)iVar3 + i] = cVar1;
          pcVar1 = pcVar1 + 1;
        } while (cVar1 != '\0');
      }
      iVar3->field_0x138 = 0;
      *(undefined4 *)&control->pauseCtx->field_0xe8 = 1;
      *(undefined4 *)&control->field_0x28 = 0;
      Events::UpdateActionBeginEnds(0xff,0);
      *(undefined4 *)&control->field_0x2c = 0;
      return 1;
    }
    uVar5 = uVar5 + 0x88;
    i = i + 1;
    cam_script = cam_script + 1;
  } while (uVar5 < 0x330);
  return 1;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void entitySceneControlMapView::dtor(int param_1)

{
  FromPlayToPause(*(undefined4 *)(param_1 + 0x24));
  Events::UpdateActionBeginEnds(0xff,1);
  return;
}




void entitySceneControlMapView::fixedUpdate_(int param_1)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  float fVar5;
  
  FUN_000483e0(*(undefined4 *)(param_1 + 0x24));
  piVar1 = *(int **)(param_1 + 0x24);
  iVar2 = *piVar1;
  iVar3 = piVar1[9];
  fVar5 = *(float *)(iVar3 + 0x2c) / *(float *)(iVar3 + 0x34);
  if (fVar5 < Cutscene::PauseCutsceneLookupTable[iVar2].tToDoLoad ||
      fVar5 == Cutscene::PauseCutsceneLookupTable[iVar2].tToDoLoad) {
    uVar4 = Cutscene::PauseCutsceneLookupTable[iVar2].field5_0x10c;
  }
  else {
    fVar5 = *(float *)(iVar3 + 0x2c) / *(float *)(iVar3 + 0x34);
    if (fVar5 < Cutscene::PauseCutsceneLookupTable[iVar2].tToSwapBuffers ||
        fVar5 == Cutscene::PauseCutsceneLookupTable[iVar2].tToSwapBuffers) goto LAB_00084048;
    uVar4 = Cutscene::PauseCutsceneLookupTable[iVar2].field6_0x110;
  }
  if (uVar4 != 0xffffffff) {
    piVar1[uVar4 * 4 + 0x25] = 1;
  }
LAB_00084048:
  if (*(int *)(param_1 + 0x28) == 0) {
    if (*(int *)(*(int *)(param_1 + 0x24) + 0x10) != 0) {
      *(undefined4 *)(*(int *)(param_1 + 0x24) + 0xc) = 0;
      FUN_00047370();
      *(undefined4 *)(param_1 + 0x28) = 1;
    }
  }
  else if (*(int *)(param_1 + 0x28) == 1) {
    if (*(int *)(*(int *)(param_1 + 0x24) + 0x10) != 0) {
      FUN_00116140();
      return;
    }
    if ((*(int *)(param_1 + 0x2c) == 0) &&
       (iVar2 = *(int *)(*(int *)(param_1 + 0x24) + 0x24),
       0.7 < *(float *)(iVar2 + 0x2c) / *(float *)(iVar2 + 0x34))) {
      DAT_004ee2b4 = 1;
      *(undefined4 *)(param_1 + 0x2c) = 1;
      return;
    }
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void entitySceneControlSuperScary::getAllocDetails(undefined4 *param_1)

{
  *param_1 = 0x2c8;
  param_1[1] = 0x1d8;
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


undefined ** entitySceneControlSuperScary::getVTable(void)

{
  vtable[0] = getAllocDetails;
  vtable[1] = ctor;
  vtable[2] = dtor;
  vtable[3] = onMessage;
  vtable[4] = update;
  vtable[5] = func5;
  return vtable;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields

undefined4
entitySceneControlSuperScary::ctor
          (entitySceneControlSuperScary *control,entitySceneControlSuperScaryParams *params)

{
  undefined1 *mv;
  char cVar1;
  undefined4 uVar2;
  Camera *pCVar3;
  bool bVar4;
  uint uVar5;
  entitySceneControlSuperScary *peVar6;
  entitySceneControlSuperScaryParams *peVar7;
  entitySceneControlSuperScaryParams *peVar8;
  actor *paVar9;
  BoneAffineSubresourceEntry *pBVar10;
  char *pcVar11;
  CameraLLNode *pCVar12;
  int iVar13;
  
  peVar7 = params;
  peVar6 = control;
  Game::NotAllowedToPause = Game::NotAllowedToPause + 1;
  if (*(int *)&params->field_0x154 == 0x5f646961) {
    Assets::GetResourceBytes(&params->field_0x154,&params);
    peVar8 = params;
    if (params == (entitySceneControlSuperScaryParams *)0x0) {
      runtime::ExitGame(2);
    }
  }
  else {
    peVar8 = (entitySceneControlSuperScaryParams *)0x0;
  }
  *(entitySceneControlSuperScaryParams **)&control->field_0x294 = peVar8;
  uVar5 = Game::NumSuperScaryInputs;
  bVar4 = (uint)Cutscene::CurrentCutsceneIndex < 0x80000000;
  control->field5_0x28 = (avatar *)0x0;
  DAT_00505680 = 0;
  g_LinkedListRemovals = 0;
  *(uint *)&control->field_0x26c = (uint)bVar4;
  uVar2 = *(undefined4 *)&peVar7->field_0x8;
  control->field128_0xac = 0.25;
  control->field126_0xa4 = 0.45;
  control->field127_0xa8 = 0.01;
  *(undefined4 *)&control->field_0x2c = uVar2;
  *(undefined4 *)&control->field_0x3c = 0;
  *(undefined4 *)&control->field_0x34 = 0;
  control->numInputs = uVar5;
  control->successfulInputs = 0;
  *(undefined4 *)&control->thingsToDraw = 0;
  *(undefined4 *)&control->field_0x208 = 8;
  *(undefined4 *)&control->field_0xb0 = 0;
  *(undefined4 *)&control->field_0xb4 = 0;
  *(undefined4 *)&control->field_0x270 = *(undefined4 *)&peVar7->field_0x134;
  *(undefined4 *)&control->field_0x1b8 = *(undefined4 *)&peVar7->field_0x10c;
  *(undefined4 *)&control->field_0x1bc = *(undefined4 *)&peVar7->field_0x110;
  *(undefined4 *)&control->field_0x28c = *(undefined4 *)&peVar7->field_0x150;
  *(undefined4 *)&control->field_0x2b8 = 0;
  *(undefined4 *)&control->field_0x2c0 = 0;
  *(undefined4 *)&control->field_0x2c4 = 0;
  *(undefined4 *)&control->field_0x2bc = *(undefined4 *)&peVar7->field_0x1d4;
  *(undefined4 *)&control->field_0x1f4 = 0;
  *(undefined4 *)&control->field_0x1f0 = 0;
  *(undefined4 *)&control->field_0x1ec = 0;
  *(undefined4 *)&control->field_0x200 = 0;
  *(undefined4 *)&control->field_0x1fc = 0;
  *(undefined4 *)&control->field_0x1f8 = 0;
  if (*(int *)&control->field_0x28c == 2) {
    paVar9 = *(actor **)&control->field_0x2c;
    if (paVar9 == (actor *)0x0) {
      *(undefined4 *)&control->field_0x28c = 0;
      goto LAB_000844e6;
    }
  }
  else {
    if (*(int *)&control->field_0x28c != 3) goto LAB_000844e6;
    paVar9 = *(actor **)&control->field_0x2c;
    if (paVar9 == (actor *)0x0) {
      *(undefined4 *)&control->field_0x28c = 1;
      goto LAB_000844e6;
    }
  }
  pBVar10 = ::actor::getModelBoneAffineByBone1(paVar9,2);
  *(BoneAffineSubresourceEntry **)&control->field_0x288 = pBVar10;
LAB_000844e6:
  pcVar11 = &peVar7->field_0xc;
  iVar13 = 0xb8 - (int)pcVar11;
  do {
    cVar1 = *pcVar11;
    pcVar11[(int)control + iVar13] = cVar1;
    pcVar11 = pcVar11 + 1;
  } while (cVar1 != '\0');
  pcVar11 = &peVar7->field_0x8c;
  iVar13 = 0x138 - (int)pcVar11;
  do {
    cVar1 = *pcVar11;
    pcVar11[(int)control + iVar13] = cVar1;
    pcVar11 = pcVar11 + 1;
  } while (cVar1 != '\0');
  if (*(int *)&peVar7->field_0x120 == 0) {
    *(undefined4 *)&control->field_0x274 = 0;
  }
  else {
    *(undefined4 *)&control->field_0x1d4 = *(undefined4 *)&peVar7->field_0x114;
    *(undefined4 *)&control->field_0x1d8 = *(undefined4 *)&peVar7->field_0x118;
    *(undefined4 *)&control->field_0x1dc = *(undefined4 *)&peVar7->field_0x11c;
    *(undefined4 *)&control->field_0x274 = 1;
  }
  if (*(int *)&peVar7->field_0x130 == 0) {
    *(undefined4 *)&control->field_0x1c8 = *(undefined4 *)&peVar7->field_0x124;
    *(undefined4 *)&control->field_0x1cc = *(undefined4 *)&peVar7->field_0x128;
    *(undefined4 *)&control->field_0x1d0 = *(undefined4 *)&peVar7->field_0x12c;
    *(undefined4 *)&control->field_0x278 = 0;
  }
  else {
    *(undefined4 *)&control->field_0x278 = 1;
  }
  if (*(int *)&peVar7->field_0x144 == 0) {
    *(undefined4 *)&control->field_0x268 = 0;
  }
  else {
    *(undefined4 *)&control->field_0x1e0 = *(undefined4 *)&peVar7->field_0x138;
    *(undefined4 *)&control->field_0x1e4 = *(undefined4 *)&peVar7->field_0x13c;
    *(undefined4 *)&control->field_0x1e8 = *(undefined4 *)&peVar7->field_0x140;
    *(undefined4 *)&control->field_0x268 = 1;
  }
  FUN_00087170();
  mv = &control->field_0x40;
  Camera::ctor((Camera *)mv,"superscaryshock",(ProjectionSetBitField)0x1);
  pCVar12 = Camera::AvailableConfigs;
  pCVar3 = Camera::AvailableConfigs[0].head;
  while (pCVar3 != (Camera *)0x0) {
    pCVar12 = (CameraLLNode *)((Camera *)pCVar12)->next;
    pCVar3 = ((Camera *)pCVar12)->next;
  }
  pCVar3 = ((Camera *)pCVar12)->prev;
  ((Camera *)pCVar12)->prev = (Camera *)mv;
  *(CameraLLNode **)mv = pCVar12;
  *(Camera **)&control->field_0x44 = pCVar3;
  if (pCVar3 != (Camera *)0x0) {
    pCVar3->next = (Camera *)mv;
  }
  if (Camera::ActiveConfigs[0] == (Camera *)0x0) {
    Camera::SetActiveCameraConfig(0,&control->field_0x74);
  }
  *(undefined4 *)&control->field_0xa0 = 1;
  iVar13 = 0x1880;
  control = (entitySceneControlSuperScary *)&control->field_0x298;
  do {
    if (*(int *)(*(int *)&peVar6->field_0x294 + iVar13) == 0x5f646961) {
      Assets::GetResourceBytes((char *)(*(int *)&peVar6->field_0x294 + iVar13),&params);
      peVar8 = params;
      if (params == (entitySceneControlSuperScaryParams *)0x0) {
        runtime::ExitGame(2);
        peVar8 = params;
      }
    }
    else {
      peVar8 = (entitySceneControlSuperScaryParams *)0x0;
    }
    (control->controlObj).object.vtable = (ObjectFullVTable *)peVar8;
    iVar13 = iVar13 + 0x80;
    control = (entitySceneControlSuperScary *)&(control->controlObj).object.field_0x4;
  } while (iVar13 < 0x1b00);
  *(undefined4 *)&peVar6->field_0x1c4 = 0;
  *(undefined4 *)&peVar6->field_0x290 = *(undefined4 *)&peVar7->field_0x14c;
  *(undefined2 *)&peVar6->field_0x264 = 0xffff;
  if (Game::WalkinLoctext != (LoctextValueContext *)0x0) {
    Game::WalkinLoctext->buffer->tail = Game::WalkinLoctext->buffer->head;
  }
  return 1;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void entitySceneControlSuperScary::dtor(int param_1)

{
  SoundSourceImpl *pSVar1;
  short sVar2;
  ScriptType4 *script;
  InputHandlerType5 *pIVar3;
  IXACT_Cue *cue;
  actor *paVar4;
  int iVar5;
  char *pcVar6;
  int iVar7;
  undefined4 *puVar8;
  
  iVar5 = param_1;
  Game::NotAllowedToPause = Game::NotAllowedToPause + -1;
  if (*(int *)(param_1 + 700) != 0) {
    if (*(int *)(param_1 + 0x2c0) != 0) {
      FUN_0003cae0(*(undefined4 *)(param_1 + 0x28));
      *(undefined4 *)(iVar5 + 0x2c0) = 0;
    }
    if (*(int *)(iVar5 + 0x2c4) != 0) {
      FUN_0003cae0(*(undefined4 *)(iVar5 + 0x2c));
      *(undefined4 *)(iVar5 + 0x2c4) = 0;
    }
  }
  iVar7 = *(int *)(iVar5 + 0x1c4);
  if (iVar7 == 0) goto LAB_00084765;
  if (iVar7 == 1) {
    pcVar6 = "XACT_SOUNDBANK_GSTREAMSDITTIES_BUTTONPRESS";
LAB_0008475a:
    PlayCutsceneMusic(pcVar6);
  }
  else {
    if (iVar7 == 2) {
      pcVar6 = "XACT_SOUNDBANK_GSTREAMSDITTIES_SUCCEED";
      goto LAB_0008475a;
    }
    if (iVar7 == 3) {
      pcVar6 = "XACT_SOUNDBANK_GSTREAMSDITTIES_BUTTONNODIE";
      goto LAB_0008475a;
    }
  }
  *(undefined4 *)(iVar5 + 0x1c4) = 0;
LAB_00084765:
  puVar8 = (undefined4 *)(iVar5 + 0x298);
  iVar7 = 5;
  do {
    Assets::DestroyAssetOrDecrement((void *)*puVar8);
    puVar8 = puVar8 + 1;
    iVar7 = iVar7 + -1;
  } while (iVar7 != 0);
  if (*(int *)(iVar5 + 0x2b8) == 0) {
    param_1 = 10;
    (**(code **)(**(int **)(iVar5 + 0x28) + 0xc))(*(int **)(iVar5 + 0x28),&param_1);
    *(undefined4 *)(iVar5 + 0x2b8) = 1;
  }
  if (*(int *)(iVar5 + 0xa0) != 0) {
    Camera::setActiveCamera(iVar5 + 0x40);
    *(undefined4 *)(iVar5 + 0xa0) = 0;
  }
  if (*(int *)(iVar5 + 0x3c) != 0) {
    Scripting::PopInputHandler();
    script = *(ScriptType4 **)(iVar5 + 0x38);
    switch((script->header).type) {
    case TYPE_1:
      Scripting::FreeScript123(&script->header);
      break;
    case TYPE_2:
      Scripting::FreeScript123(&script->header);
      break;
    case TYPE_3:
      Scripting::FreeScript123(&script->header);
      break;
    case TYPE_4_NESTED:
      Scripting::FreeScript4(script);
      break;
    case TYPE_5:
      pIVar3 = script->s1;
      (script->header).active = 0;
      if (pIVar3 == (InputHandlerType5 *)0xffffffff) {
        free(script);
      }
      else {
        *(undefined4 *)&script->s2[0xc].field_0x90 = 0;
        FUN_00107a40(script[7].s3);
      }
    }
    *(undefined4 *)(iVar5 + 0x3c) = 0;
  }
  sVar2 = *(short *)(iVar5 + 0x264);
  if (sVar2 != -1) {
    cue = Audio::SoundSources[sVar2].cue;
    pSVar1 = Audio::SoundSources + sVar2;
    if (cue == (IXACT_Cue *)0x0) {
      pSVar1->state = Finished;
    }
    else {
      switch(pSVar1->state) {
      case ShouldGoTo4_1:
      case ShouldGoTo4_2:
        pSVar1->state = State4;
        break;
      case ShouldPause1:
      case ShouldPause2:
      case ShouldPause3:
        pSVar1->state = Paused;
        IXACT_Cue::stop(cue,0);
      }
    }
    *(undefined2 *)(iVar5 + 0x264) = 0xffff;
  }
  if (*(void **)(iVar5 + 0x294) != (void *)0x0) {
    Assets::DestroyAssetOrDecrement(*(void **)(iVar5 + 0x294));
    *(undefined4 *)(iVar5 + 0x294) = 0;
  }
  paVar4 = *(actor **)(iVar5 + 0x30);
  if (paVar4 != (actor *)0x0) {
    pickup::DetachFromActor((paVar4->avatar).statePickUp,paVar4);
    if ((paVar4->avatar).skipUpdate == 0) {
      param_1 = 0x80;
      (*((paVar4->avatar).vtable)->onMessage)(paVar4,&param_1);
      if ((paVar4->avatar).skipUpdate == 0) {
        removeavatarfromsomelistsshit(paVar4);
      }
    }
    *(undefined4 *)(iVar5 + 0x30) = 0;
  }
  g_globalFlagset = g_globalFlagset & 0xfffffbff;
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void entitySceneControlSuperScary::onMessage(entitySceneControlSuperScary *control,int *param_2)

{
  if ((*param_2 == 0x7c) && (control->field5_0x28 == (avatar *)param_2[1])) {
    control->field5_0x28 = (avatar *)0x0;
  }
  if (*param_2 == 0x80) {
    sceneControlObj::cleanupGameselect(&control->controlObj);
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void entitySceneControlSuperScary::update(entitySceneControlSuperScary *control)

{
  GlobalFlagset GVar1;
  entitySceneControlSuperScary *peVar2;
  entitySceneControlSuperScary *n2;
  BOOL BVar3;
  entitySceneControlSuperScary *n1;
  GameState *extraout_ECX;
  GameState *extraout_ECX_00;
  GameState *extraout_ECX_01;
  GameState *extraout_ECX_02;
  GameState *extraout_ECX_03;
  GameState *extraout_ECX_04;
  GameState *extraout_ECX_05;
  GameState *extraout_ECX_06;
  GameState *extraout_ECX_07;
  GameState *extraout_ECX_08;
  GameState *extraout_ECX_09;
  GameState *extraout_ECX_10;
  GameState *extraout_ECX_11;
  GameState *extraout_ECX_12;
  actorBody *inAsset;
  int pressed_right_button;
  uint uVar4;
  bool changes_made;
  float10 extraout_ST0;
  float fVar5;
  float fVar6;
  entitySceneControlSuperScary *peVar7;
  undefined4 uVar9;
  uint uVar8;
  
  peVar2 = control;
  fVar5 = 0.0;
  if (runtime::dx_timer <= 0.0) {
    fVar5 = runtime::DeltaTime * runtime::TimeScale;
  }
  changes_made = g_LinkedListRemovals != 0;
  (control->controlObj).timeElapsed = (control->controlObj).timeElapsed + fVar5;
  if (changes_made) {
    runtime::rand = runtime::rand * 0x19660d + 0x3c6ef35f;
    n1 = (entitySceneControlSuperScary *)&control->field_0x214;
    n2 = (entitySceneControlSuperScary *)
         (&WeirdNodeInnerData0x80_ARRAY_00302198[0].field0_0x0 +
         (int)(((float)(runtime::rand & 0x7fffff | 0x3f800000) - 1.0) * 4.0) * 20);
    pressed_right_button = 20;
    do {
      (n1->controlObj).object.vtable = (n2->controlObj).object.vtable;
      n2 = (entitySceneControlSuperScary *)&(n2->controlObj).object.field_0x4;
      n1 = (entitySceneControlSuperScary *)&(n1->controlObj).object.field_0x4;
      pressed_right_button = pressed_right_button + -1;
    } while (pressed_right_button != 0);
    g_LinkedListRemovals = 0;
  }
  switch(*(undefined4 *)&control->field_0x34) {
  case 0:
    setState(control,1);
    n1 = (entitySceneControlSuperScary *)extraout_ECX;
    break;
  case 1:
    BVar3 = Timer::reduce((float *)&control->field_0x1b8);
    if (BVar3 != 0) {
      uVar8 = 2;
LAB_00084a40:
      setState(control,uVar8);
    }
    goto LAB_00084a49;
  case 2:
    BVar3 = avatar::updateKeyframes(control->field5_0x28,0);
    if (BVar3 != 0) {
      uVar8 = 3;
      goto LAB_00084a40;
    }
    goto LAB_00084a49;
  case 3:
    BVar3 = Timer::reduce((float *)&control->field_0x1bc);
    if (BVar3 != 0) {
      uVar8 = 4;
      goto LAB_00084a40;
    }
    goto LAB_00084a49;
  case 4:
    BVar3 = avatar::updateKeyframes(control->field5_0x28,0);
    if (BVar3 != 0) {
      uVar8 = 5;
      goto LAB_00084a40;
    }
LAB_00084a49:
    FUN_00086990();
    n1 = (entitySceneControlSuperScary *)extraout_ECX_00;
    break;
  case 5:
  case 6:
                    // Case 5/6 is probably on button pushed
    FUN_00109470(*(InputHandlerType4 **)&control->field_0x38);
    fVar5 = 0.0;
    if (0.0 < *(float *)&control->field_0xb0) {
      fVar6 = System__GetMSElapsed_();
      *(float *)&control->field_0xb0 = *(float *)&control->field_0xb0 - fVar6;
    }
    if (*(float *)&control->field_0xb0 <= fVar5) {
      pressed_right_button = FUN_00086a40();
      if (pressed_right_button == 0) {
        pressed_right_button = FUN_00086b30(control,*(int *)&control->field_0x38);
        if (pressed_right_button == 0) goto LAB_00084b76;
        Audio::PlaySoundWithFlags("XACT_SOUNDBANK_GSUPERSCARYSTUF_WRONGBUTTON",1);
        *(float *)&control->field_0xb0 = 1.0;
        FUN_0006dad0();
      }
      else {
        uVar4 = control->successfulInputs + 1;
        GVar1 = g_globalFlagset & 0x1000000;
        control->successfulInputs = uVar4;
        if (GVar1 == 0) {
          DAT_00505680 = uVar4;
        }
        Audio::PlaySoundWithFlags("XACT_SOUNDBANK_GSUPERSCARYSTUF_RIGHTBUTTON",1);
        if (control->successfulInputs == control->numInputs) goto LAB_00084ba3;
        FUN_00085190(control->successfulInputs);
        FUN_0006da00(0x3fc00000);
      }
      fVar5 = 0.0;
    }
LAB_00084b76:
    BVar3 = Timer::reduce(&control->field127_0xa8);
    if (BVar3 == 0) {
      peVar7 = (entitySceneControlSuperScary *)
               (1.0 - ((float)*(int *)&control->field_0x208 - 8.0) * -0.125);
      if (fVar5 <= (float)peVar7) {
        control = (entitySceneControlSuperScary *)1.0;
        if ((float)peVar7 <= 1.0) {
          control = peVar7;
        }
        FUN_00084e50(control);
        n1 = (entitySceneControlSuperScary *)extraout_ECX_04;
      }
      else {
        FUN_00084e50(fVar5);
        n1 = (entitySceneControlSuperScary *)extraout_ECX_03;
      }
    }
    else {
      pressed_right_button = *(int *)&control->field_0x208 + -1;
      *(int *)&control->field_0x208 = pressed_right_button;
      if (pressed_right_button < 0) {
        if (-1 < (char)(g_globalFlagset >> 8)) {
          setState(control,10);
          return;
        }
LAB_00084ba3:
        setState(control,Success);
        return;
      }
      fVar6 = 1.0 - ((float)pressed_right_button - 8.0) * -0.125;
      if ((fVar5 <= fVar6) && (fVar5 = fVar6, 1.0 < fVar6)) {
        fVar5 = 1.0;
      }
      FUN_00103850();
      FUN_00103850();
      FUN_00103850();
      uVar4 = FUN_00103850();
      control->field128_0xac = 0.25;
      control->field127_0xa8 = (float)(extraout_ST0 * (float10)0.7 + (float10)0.3);
      if (*(int *)&control->field_0x208 < 4) {
        Audio::Play("XACT_SOUNDBANK_GSUPERSCARYSTUF_HEARTBEATFAST",1,uVar4,0.0);
        FUN_00086b70(control);
        FUN_00084e50(fVar5);
        n1 = (entitySceneControlSuperScary *)extraout_ECX_01;
      }
      else {
        Audio::Play("XACT_SOUNDBANK_GSUPERSCARYSTUF_HEARTBEAT",1,uVar4,0.0);
        FUN_00086b70(control);
        FUN_00084e50(fVar5);
        n1 = (entitySceneControlSuperScary *)extraout_ECX_02;
      }
    }
    break;
  case 7:
    if (Game::DialogState == NotInDialog) {
      FUN_00086bc0(7);
      n1 = (entitySceneControlSuperScary *)extraout_ECX_06;
    }
    break;
  case 8:
    BVar3 = Cutscene::InACutscene();
    if (BVar3 == 0) {
LAB_00084d7a:
      FUN_00087720();
      n1 = (entitySceneControlSuperScary *)extraout_ECX_08;
      break;
    }
    pressed_right_button = FUN_000f29a0();
    uVar9 = 7;
    if (pressed_right_button == 0) {
      setState(control,7);
      n1 = (entitySceneControlSuperScary *)extraout_ECX_07;
      break;
    }
    goto LAB_00084d29;
  case 9:
    if (Game::DialogState != NotInDialog) break;
    goto LAB_00084d27;
  case 10:
    pressed_right_button = FUN_00049d10();
    if ((pressed_right_button != 0) &&
       (BVar3 = Assets::AssetNamesMatch
                          (Game::GameState.currentSceneScript,
                           "aid_script_ghoulies_chapter1_scene2_1viewcam"),
       n1 = (entitySceneControlSuperScary *)extraout_ECX_09, BVar3 != 0)) break;
    BVar3 = Cutscene::InACutscene();
    if (BVar3 == 0) goto LAB_00084d7a;
    pressed_right_button = FUN_000f29a0();
    if (pressed_right_button == 0) {
      setState(control,9);
      n1 = (entitySceneControlSuperScary *)extraout_ECX_10;
      break;
    }
LAB_00084d27:
    uVar9 = 8;
LAB_00084d29:
    FUN_00086bc0(uVar9);
    n1 = (entitySceneControlSuperScary *)extraout_ECX_05;
    break;
  case 0xb:
    BVar3 = Timer::reduce(&control->field126_0xa4);
    n1 = (entitySceneControlSuperScary *)extraout_ECX_11;
    if (BVar3 != 0) {
      FUN_00116140();
      n1 = (entitySceneControlSuperScary *)extraout_ECX_12;
    }
  }
  if (peVar2->field5_0x28 != (avatar *)0x0) {
    FUN_00130710((GameState *)n1,0,(uint)*(ushort *)((int)peVar2->field5_0x28[1].rotQuat.z + 0x94));
    BaronDraw_00433c10.scalar = 2.0;
    UI::LoadHealthTextures(inAsset);
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void entitySceneControlSuperScary::func5(entitySceneControlSuperScary *control)

{
  int *piVar1;
  uint i;
  int32_t local_1c;
  
  if (((4 < *(int *)&control->field_0x34) && (*(int *)&control->field_0x34 < 7)) &&
     (-1 < (char)(undefined1)g_globalFlagset)) {
    i = 0;
    if (0 < (int)control->numInputs) {
      piVar1 = (int *)&control->field_0x214;
      do {
        FUN_00085190(i);
        if (control->successfulInputs == i) {
          FUN_00085280();
        }
        local_1c = -1;
        if ((int)i < (int)control->successfulInputs) {
          local_1c = 0x60ffffff;
        }
        FUN_001221b0(*(undefined4 *)(&control->field_0x298 + *piVar1 * 4),local_1c,0);
        if ((control->successfulInputs == i) && (0.1 < *(float *)&control->field_0xb0)) {
          FUN_001221b0(*(undefined4 *)&control->field_0x2a8,0x800000ff,0);
        }
        i = i + 1;
        piVar1 = piVar1 + 1;
      } while ((int)i < (int)control->numInputs);
    }
    piVar1 = *(int **)&control->thingsToDraw;
    if (piVar1 != (int *)0x0) {
      (**(code **)(*piVar1 + 0x14))
                (piVar1,(int)&Graphics::CurrentCameraStruct[-0x2a8c].transformMat / 0x1e4,3);
    }
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void entitySceneControlGameSelect::getLastMenuUsed(MenuVTable **vtable)

{
  int err;
  
                    // If no error reading previous menu?
  err = runtime::GetSpaceUsedByDiskType(HARDDISK_0,(uint *)0x0,(uint *)0x0);
  if (err == 0) {
    *vtable = menu::vtableLookup + resource::next_menu_id;
    return;
  }
                    // Default to menu 18
  *vtable = menu::vtableLookup + 18;
  err = runtime::GetSpaceUsedByDiskType(HARDDISK_0,(uint *)0x0,(uint *)0x0);
  if (err == 0) {
    g_someDiskFloat = 0.0;
    return;
  }
  g_someDiskFloat = 5.0;
  return;
}




void sceneControlObj::getAllocDetails(ObjectAllocDetails *param_1)

{
  param_1->entitySize = 0x24;
  param_1->paramsSize = 8;
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


sceneControlObjectVTable * sceneControlObj::getVTable(void)

{
  vtable.getAllocDetails = getAllocDetails;
  vtable.ctor = ctor;
  vtable.dtor = dtor;
  vtable.onMessage = onMessage;
  vtable.update = updateFixed_;
  vtable.func5 = switchD_000d4179::EmptyFunction;
  return &vtable;
}




BOOL sceneControlObj::ctor(sceneControlObj *obj)

{
  EmbeddedSentinel<> *pEVar1;
  
  pEVar1 = &Game::NewSceneControls;
  if (Game::NewSceneControls.next != (EmbeddedNode<> *)0x0) {
    pEVar1 = &Game::NewSceneControls;
    do {
      pEVar1 = (EmbeddedSentinel<> *)((EmbeddedNode<> *)pEVar1)->next;
    } while (((EmbeddedNode<> *)pEVar1)->next != (sceneControlObj_0x8)0x0);
  }
  ((EmbeddedNode<> *)pEVar1)->next = (sceneControlObj_0x8)&obj->obj_0x8;
  (obj->obj_0x8).prev = (sceneControlObj_0x8)pEVar1;
  (obj->obj_0x8).next = (sceneControlObj_0x8)0x0;
  return 1;
}




void sceneControlObj::dtor(sceneControlObj *param_1)

{
  sceneControlObj_0x8 puVar1;
  sceneControlObj_0x18 puVar2;
  
  puVar1 = (param_1->obj_0x8).prev;
  if (puVar1 != (sceneControlObj_0x8)0x0) {
    *(sceneControlObj_0x8 *)(puVar1 + 4) = (param_1->obj_0x8).next;
  }
  puVar1 = (param_1->obj_0x8).next;
  if (puVar1 != (sceneControlObj_0x8)0x0) {
    *(sceneControlObj_0x8 *)puVar1 = (param_1->obj_0x8).prev;
  }
  (param_1->obj_0x8).prev = (sceneControlObj_0x8)0x0;
  (param_1->obj_0x8).next = (sceneControlObj_0x8)0x0;
  puVar2 = (param_1->obj_0x18).prev;
  if (puVar2 != (sceneControlObj_0x18)0x0) {
    *(sceneControlObj_0x18 *)(puVar2 + 4) = (param_1->obj_0x18).next;
  }
  puVar2 = (param_1->obj_0x18).next;
  if (puVar2 != (sceneControlObj_0x18)0x0) {
    *(sceneControlObj_0x18 *)puVar2 = (param_1->obj_0x18).prev;
  }
  (param_1->obj_0x18).prev = (sceneControlObj_0x18)0x0;
  (param_1->obj_0x18).next = (sceneControlObj_0x18)0x0;
  return;
}




void sceneControlObj::updateFixed_(int param_1)

{
  float fVar1;
  
  fVar1 = 0.0;
  if (runtime::dx_timer <= 0.0) {
    fVar1 = runtime::DeltaTime * runtime::TimeScale;
  }
  *(float *)(param_1 + 0x20) = *(float *)(param_1 + 0x20) + fVar1;
  return;
}




undefined4 sceneControlObj::cleanupGameselect(sceneControlObj *control)

{
  sceneControlObj_0x8 puVar1;
  void **ppvVar2;
  EmbeddedSentinel<> *pEVar3;
  
  if ((control->obj_0x18).prev == (sceneControlObj_0x18)0x0) {
    ppvVar2 = &PTR_0050e44c;
    if (Game::StaleSceneControls.sentinel != (EmbeddedNode<> *)0x0) {
      pEVar3 = &Game::StaleSceneControls;
      do {
        ppvVar2 = &pEVar3->sentinel->prev;
        pEVar3 = (EmbeddedSentinel<> *)&((EmbeddedNode<> *)ppvVar2)->next;
      } while (((EmbeddedNode<> *)ppvVar2)->next != (sceneControlObj_0x18)0x0);
    }
    ((EmbeddedNode<> *)ppvVar2)->next = (sceneControlObj_0x18)&control->obj_0x18;
    (control->obj_0x18).prev = (sceneControlObj_0x18)ppvVar2;
    (control->obj_0x18).next = (sceneControlObj_0x18)0x0;
    puVar1 = (control->obj_0x8).prev;
    if (puVar1 != (sceneControlObj_0x8)0x0) {
      *(sceneControlObj_0x8 *)(puVar1 + 4) = (control->obj_0x8).next;
    }
    puVar1 = (control->obj_0x8).next;
    if (puVar1 != (sceneControlObj_0x8)0x0) {
      *(sceneControlObj_0x8 *)puVar1 = (control->obj_0x8).prev;
    }
    (control->obj_0x8).prev = (sceneControlObj_0x8)0x0;
    (control->obj_0x8).next = (sceneControlObj_0x8)0x0;
    return 1;
  }
  return 0;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void sceneControlObj::onMessage(sceneControlObj *param_1,Message *msg)

{
  if ((msg->header).msgId == Scene_End) {
    cleanupGameselect(param_1);
  }
  return;
}




void sceneControlObj::destroyStaleControls(void)

{
  Object *mem;
  EmbeddedNode<> *pEVar1;
  EmbeddedNode<> *pEVar2;
  undefined4 uVar3;
  int iVar4;
  HeapTableEntry *pHVar5;
  
  pEVar1 = Game::StaleSceneControls.sentinel;
  while (pEVar1 != (EmbeddedNode<> *)0x0) {
    pEVar2 = pEVar1 + -3;
    mem = (Object *)(pEVar1 + -3);
    pEVar1 = (EmbeddedNode<> *)pEVar1->next;
                    // Destroys gameselect scene control
    obj::destroy(mem,*(ushort *)&pEVar2->next,0);
    iVar4 = FindHeapOf(mem);
    uVar3 = runtime::CurrentHeapToAllocateFrom;
    if (g_HeapTableBase[iVar4].heapHandle == (HANDLE)0x0) {
      pHVar5 = (HeapTableEntry *)0x0;
    }
    else {
      pHVar5 = g_HeapTableBase + iVar4;
    }
    runtime::CurrentHeapToAllocateFrom = iVar4;
    XAPILIB::HeapFree(pHVar5->heapHandle,0,mem);
    Entity::Count = Entity::Count + -1;
    runtime::CurrentHeapToAllocateFrom = uVar3;
  }
  return;
}




void sceneControlObj::processNew(void)

{
  EmbeddedSentinel<> *pEVar1;
  EmbeddedNode<> *tail;
  SceneNode *weird_tail;
  SceneNode **ptr2;
  sceneControlObj_0x8 new_ctrl;
  SceneNode *head_next;
  sceneControlObj_0x8 active_prev;
  EmbeddedNode<> *next;
  
  next = Game::NewSceneControls.next;
  while (next != (EmbeddedNode<> *)0x0) {
                    // Remove scene control obj from list
    Game::NewSceneControls.next = next;
    if (next->prev != (sceneControlObj_0x8)0x0) {
      *(sceneControlObj_0x8 *)(next->prev + 4) = next->next;
    }
    if (next->next != (sceneControlObj_0x8)0x0) {
      *(sceneControlObj_0x8 *)next->next = next->prev;
    }
    next->prev = (sceneControlObj_0x8)0x0;
    next->next = (sceneControlObj_0x8)0x0;
                    // Append to tail of active scene controls
    tail = &Game::SceneControls;
    active_prev = Game::SceneControls.prev;
    while (active_prev != (sceneControlObj_0x8)0x0) {
      tail = (EmbeddedNode<> *)tail->prev;
      active_prev = tail->prev;
    }
    active_prev = tail->next;
    tail->next = (sceneControlObj_0x8)next;
    next->prev = (sceneControlObj_0x8)tail;
    next->next = active_prev;
    if (active_prev != (sceneControlObj_0x8)0x0) {
      *(EmbeddedNode<> **)active_prev = next;
    }
    weird_tail = (SceneNode *)&Game::NewlyAddedSceneControls;
    if (Game::NewlyAddedSceneControls.next != (EmbeddedNode<> *)0x0) {
                    // Get tail of sceneNode
      pEVar1 = &Game::NewlyAddedSceneControls;
      do {
        ptr2 = &((SceneNode *)pEVar1)->next;
        weird_tail = *ptr2;
        pEVar1 = (EmbeddedSentinel<> *)weird_tail;
      } while (weird_tail->next != (SceneNode *)0x0);
    }
    weird_tail->next = (SceneNode *)(next + 1);
    ((SceneNode *)(next + 1))->prev = weird_tail;
    next[1].next = (sceneControlObj_0x8)0x0;
    next = Game::NewSceneControls.next;
  }
  Game::NewSceneControls.next = next;
  return;
}



// Tells all objects the scene has begun


void sceneControlObj::BeginScene(void)

{
  EmbeddedNode<> *pEVar1;
  ObjMsgID local_4;
  
  if (Game::NewlyAddedSceneControls.next != (EmbeddedNode<> *)0x0) {
    local_4 = Scene_Begin;
    pEVar1 = Game::NewlyAddedSceneControls.next;
    do {
      (**(code **)(pEVar1[-2].prev + 0xc))(pEVar1 + -2,&local_4);
      pEVar1 = (EmbeddedNode<> *)pEVar1->next;
    } while (pEVar1 != (EmbeddedNode<> *)0x0);
  }
  return;
}




void sceneControlObj::UpdateNewSceneControls(void)

{
  entitySceneControlSuperScary *curr;
  EmbeddedNode<> *ctrl;
  
  ctrl = Game::NewlyAddedSceneControls.next;
                    // Happens when loading new cutscenes or loading between areas (eg., on respawn)
                    // 
                    // Game crashes when this isn't present (Embassy ballroom 1)
  while (ctrl != (EmbeddedNode<> *)0x0) {
    Game::NewlyAddedSceneControls.next = ctrl;
                    // Remove from SceneControls
                    // 
    if (ctrl->prev != (sceneControlObj_0x8)0x0) {
      *(sceneControlObj_0x8 *)(ctrl->prev + 4) = ctrl->next;
    }
    if (ctrl->next != (sceneControlObj_0x8)0x0) {
      *(sceneControlObj_0x8 *)ctrl->next = ctrl->prev;
    }
    ctrl->prev = (sceneControlObj_0x8)0x0;
    ctrl->next = (sceneControlObj_0x8)0x0;
    (**(code **)(ctrl[-2].prev + 0x10))(ctrl + -2);
                    // Jumps to
                    // 0x00084960
                    // 
    ctrl = Game::NewlyAddedSceneControls.next;
  }
  Game::NewlyAddedSceneControls.next = ctrl;
  return;
}




void Challenge::GetChallengeDetails(ChallengeDetails *param_1,uint param_2)

{
  uint uVar1;
  uint uVar2;
  uint *puVar3;
  
  uVar1 = TimeLimitChallenge::metadata.size - 0x18;
  if (uVar1 != 0) {
    puVar3 = &param_1->data;
    for (uVar2 = uVar1 >> 2; uVar2 != 0; uVar2 = uVar2 - 1) {
      *puVar3 = 0;
      puVar3 = puVar3 + 1;
    }
    for (uVar1 = uVar1 & 3; uVar1 != 0; uVar1 = uVar1 - 1) {
      *(undefined1 *)puVar3 = 0;
      puVar3 = (uint *)((int)puVar3 + 1);
    }
  }
  param_1->index = 4;
  param_1->field1_0x4 = param_2;
  param_1->field2_0x8 = (char *)0x0;
  param_1->field3_0xc = (char *)0x0;
  return;
}




