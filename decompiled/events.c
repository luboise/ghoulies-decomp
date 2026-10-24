/* events.c - Event loops, markers, challenge triggers */
#include "events.h"

void FUN_00028500(DerivedMarkerValue *dmv,actor *param_2)

{
  Buffer<> *pBVar1;
  actorDroneActionId aVar2;
  actorDroneActionId *paVar3;
  
  param_2->derivedMarkerValue = dmv;
  if (dmv == (DerivedMarkerValue *)0x0) {
    if (param_2->field_0x98a != '\0') {
      actorBody::resetFlags();
      param_2->field_0x98a = 0;
    }
  }
  else {
    pBVar1 = param_2->droneActionsBuf;
    if (pBVar1 == (Buffer<> *)0x0) {
      aVar2 = Null;
    }
    else {
      if (pBVar1->size == pBVar1->endOfQueue) {
        paVar3 = (actorDroneActionId *)0x0;
      }
      else {
        paVar3 = (actorDroneActionId *)
                 ((int)&pBVar1->entries->actionId +
                 (uint)pBVar1->currentDroneAction * (uint)pBVar1->valueSize);
      }
      aVar2 = *paVar3;
    }
    if ((aVar2 == BurstFromWall) && (param_2->field_0x98a == '\0')) {
      actorBody::resetFlags(param_2->body);
      param_2->field_0x98a = 1;
      return;
    }
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void Events::Update(void)

{
  void *j;
  EventCallback_ *callback;
  
  EventDelta = runtime::TrueDeltaTime + EventDelta;
  EventCount1 = EventCount1 + 1;
  EventCount2 = EventCount2 + 1;
  callback = FunctionTableStart;
  do {
    if ((callback->parent != (void *)0x0) &&
       (j = (void *)((int)callback->parent + -1), callback->parent = j, j == (void *)0x0)) {
      (*(code *)callback->callback)(callback->data);
      callback->data = (void *)0x0;
      callback->callback = (EventCallback_ *)0x0;
    }
    callback = callback + 1;
  } while ((int)callback < 0x4deb54);
  return;
}




BOOL Events::loadBnlFromScriptAid(void)

{
  BundleContext *pBVar1;
  int extraout_EAX;
  Buffer<> *buf;
  BundleContext *bundle;
  int unaff_EDI;
  
  buf = g_openBundles;
                    // Close the open bundles from last scene?
  if (g_some0x2cBufferSize != 0) {
    bundle = g_openBundles->tail;
    pBVar1 = g_openBundles->head;
    while (bundle = bundle + -1, pBVar1 <= bundle) {
      if (bundle->someBool_ == 0) {
                    // Both of these just free heap memory
        closeBundleContext(bundle);
        BundleContext::delete(bundle);
        buf = g_openBundles;
      }
    }
    g_some0x2cBufferSize = 0;
  }
  if ((game::bundle_opened_successfully == 0) &&
     ((int)g_some0x2cMinSize < (int)g_openBundleContexts_)) {
    for (bundle = buf->head; bundle < buf->tail;
        bundle = (BundleContext *)((int)&bundle->fileCtx + (uint)buf->valueSize)) {
      if (bundle->isEmpty__ == 0) goto LAB_00034262;
                    // Go to next ele
    }
    bundle = (BundleContext *)0x0;
LAB_00034262:
    LoadBundleFromDisc(bundle,unaff_EDI);
    if (extraout_EAX != 0) {
      CloseBundleContextOnError(extraout_EAX,bundle);
    }
  }
  return game::bundle_opened_successfully;
}




void UpdateAttacks_(void)

{
  char cVar1;
  MindMemoryTargetWantedToAttack *pMVar2;
  float fVar3;
  MindMemoryTargetWantedToAttack *mem;
  int iVar4;
  float *pfVar5;
  byte bVar6;
  int iVar7;
  int iVar8;
  float10 fVar9;
  actorBody *paVar10;
  float fVar11;
  float fVar12;
  float fVar13;
  MindMemoryHeader *pMVar14;
  MindMemoryHeader *pMVar15;
  float fVar16;
  float local_8;
  
  pMVar2 = g_itemsToClear;
  if (runtime::dx_timer <= 0.0) {
    local_8 = runtime::DeltaTime * runtime::TimeScale;
  }
  else {
    local_8 = 0.0;
  }
  do {
    do {
      while( true ) {
        while( true ) {
          mem = pMVar2;
          if (mem == (MindMemoryTargetWantedToAttack *)0x0) {
            return;
          }
          cVar1 = *(char *)&mem[3].header.mainTimer;
          pMVar2 = (MindMemoryTargetWantedToAttack *)(mem->header).next;
          if (cVar1 != '\x01') break;
          fVar12 = 1.0;
          if (mem[1].header.timeUntilInactive < 0.0) {
            fVar12 = -1.0;
          }
          mem[1].header.floatParam2 = fVar12;
          *(undefined1 *)&mem[3].header.mainTimer = 2;
          *(undefined1 *)((int)&mem[3].header.mainTimer + 3) = 0;
        }
        if (cVar1 != '\x02') break;
        fVar12 = mem[1].header.mainTimer;
        if (fVar12 == 0.0) {
          bVar6 = *(byte *)((int)&mem[3].header.mainTimer + 3);
          if (bVar6 != 0) {
            pMVar15 = mem[1].header.prev;
            mem[1].header.timeUntilInactive =
                 (float)pMVar15 * (float)pMVar15 * mem[1].header.timeUntilInactive;
          }
        }
        else {
          fVar12 = fVar12 - local_8;
          if (fVar12 <= 0.0) {
            fVar12 = 0.0;
          }
          bVar6 = *(byte *)((int)&mem[3].header.mainTimer + 3);
          mem[1].header.mainTimer = fVar12;
          if (bVar6 != 0) {
            paVar10 = mem->targetBody;
            pMVar15 = mem[1].header.next;
            fVar3 = *(float *)&mem[1].header.memId;
            if ((float)paVar10 == 0.0) {
LAB_000491a9:
              mem[1].header.timeUntilInactive = (float)pMVar15;
            }
            else {
              pMVar14 = (MindMemoryHeader *)
                        (((fVar12 - (float)paVar10) / (0.0 - (float)paVar10)) *
                         ((float)pMVar15 - fVar3) + fVar3);
              if ((float)pMVar15 <= fVar3) {
                if (((float)pMVar14 < (float)pMVar15) ||
                   (pMVar15 = pMVar14, (float)pMVar14 <= fVar3)) goto LAB_000491a9;
                mem[1].header.timeUntilInactive = fVar3;
              }
              else {
                if (((float)pMVar15 < (float)pMVar14) ||
                   (pMVar15 = pMVar14, fVar3 <= (float)pMVar14)) goto LAB_000491a9;
                mem[1].header.timeUntilInactive = fVar3;
              }
            }
          }
        }
        mem[1].header.floatParam2 = 0.0 - mem[1].header.floatParam2;
        pMVar15 = mem[1].header.prev;
        *(byte *)((int)&mem[3].header.mainTimer + 3) = bVar6 ^ 1;
        if (((float)pMVar15 != 1.0) &&
           (fVar9 = abs_float(mem[1].header.timeUntilInactive), fVar9 < (float10)0.001)) {
LAB_00049216:
          MindMemory::dtor(mem);
        }
      }
    } while (cVar1 != '\x03');
    pfVar5 = &mem[1].header.mainTimer;
    if ((float)mem->targetBody < *pfVar5 || (float)mem->targetBody == *pfVar5) goto LAB_00049216;
    paVar10 = (actorBody *)(mem[1].header.mainTimer + local_8);
    if ((float)mem->targetBody < (float)paVar10) {
      paVar10 = mem->targetBody;
    }
    fVar3 = mem[3].header.floatParam2;
    mem[1].header.mainTimer = (float)paVar10;
    fVar11 = (float)paVar10 / (float)mem->targetBody;
    fVar12 = mem[1].header.timeInactive;
    iVar8 = 0;
    iVar7 = (int)fVar3 + -1;
    if (fVar12 <= fVar11) {
      pfVar5 = &mem[1].header.floatParam2 + (int)fVar3 * 2;
      if (fVar11 < *pfVar5 || fVar11 == *pfVar5) {
        if (1 < iVar7) {
          do {
            iVar4 = (iVar7 - iVar8) / 2 + iVar8;
            if (fVar11 < (&mem[1].header.timeInactive)[iVar4 * 2]) {
              iVar7 = iVar4;
              iVar4 = iVar8;
            }
            iVar8 = iVar4;
          } while (iVar8 + 1 < iVar7);
        }
        fVar12 = (&mem[1].header.timeInactive)[iVar7 * 2];
        pfVar5 = &mem[1].header.timeInactive + iVar8 * 2;
      }
      else {
        fVar12 = mem[1].header.timeInactive + 1.0;
        iVar7 = 0;
        pfVar5 = &mem[1].header.floatParam2 + (int)fVar3 * 2;
      }
      fVar16 = *pfVar5;
    }
    else {
      fVar16 = (&mem[1].header.floatParam2)[(int)fVar3 * 2] - 1.0;
      pfVar5 = &mem[1].header.floatParam2 + (int)fVar3 * 2;
      iVar7 = 0;
    }
    fVar3 = pfVar5[1];
    fVar13 = (&mem[1].header.timeInactive2)[iVar7 * 2];
    if (fVar12 != fVar16) {
      fVar12 = ((fVar11 - fVar16) / (fVar12 - fVar16)) * (fVar13 - fVar3) + fVar3;
      if (fVar13 <= fVar3) {
        if ((fVar13 <= fVar12) && (fVar13 = fVar12, fVar3 < fVar12)) {
          fVar13 = fVar3;
        }
      }
      else if ((fVar12 <= fVar13) && (fVar13 = fVar12, fVar12 < fVar3)) {
        fVar13 = fVar3;
      }
    }
    fVar12 = mem[1].header.floatParam2;
    mem[1].header.timeUntilInactive = (float)mem[1].header.next * fVar13;
    mem[1].header.floatParam2 = 0.0 - fVar12;
  } while( true );
}




void UseRegularSceneOrderAIDList(void)

{
  byte *pbVar1;
  
  pbVar1 = SomeAS15->flags;
  if (((*pbVar1 & 8) == 0) && ((g_globalFlagset & 0x200000) == 0)) {
    return;
  }
  *pbVar1 = *pbVar1 & 0xf7;
  DAT_004e1748 = 0;
  SetGlobalSceneOrder("aid_aidlist_ghoulies_sceneorder_game");
  return;
}




void Events::RunEndOfScaryShockEvents(void)

{
  char *pcVar1;
  float fVar2;
  
  switch((char *)(INT_004e17c8 + -2)) {
  case (char *)0x0:
    FUN_0004a4d0(3,(char *)(INT_004e17c8 + -2));
    return;
  case (char *)0x1:
    FUN_0004ac00();
    pcVar1 = (char *)FUN_0004ab40();
    if (pcVar1 != (char *)0x0) {
      FUN_0004a4d0(4,pcVar1);
      return;
    }
    break;
  case (char *)0x2:
    pcVar1 = (char *)FUN_0004ac00();
    if (runtime::dx_timer <= 0.0) {
      fVar2 = runtime::DeltaTime * runtime::TimeScale;
    }
    else {
      fVar2 = 0.0;
    }
    if ((0.0 < Game::ChallengeTimer) &&
       (Game::ChallengeTimer = Game::ChallengeTimer - fVar2, Game::ChallengeTimer <= 0.0)) {
      Game::ChallengeTimer = 0.0;
      FUN_0004a4d0(5,pcVar1);
      return;
    }
    if (Game::ChallengeTimer < 0.001) {
      FUN_0004a4d0(5,pcVar1);
      return;
    }
    break;
  case (char *)0x3:
    if (Game::DialogState == NotInDialog) {
      FUN_0004a4d0(6,(char *)0x0);
      return;
    }
    break;
  case (char *)0x4:
    FUN_0004ac00();
    FUN_00109470((InputHandlerType4 *)DAT_004e19a4);
    Input::UpdateMenuInput(DAT_004e19a4,(Scene *)INT_004e19a0);
    pcVar1 = (char *)FUN_0004a990();
    if (pcVar1 != (char *)0x0) {
      FUN_0004a4d0(1,pcVar1);
    }
  }
  return;
}




void FUN_0004a100(challengeId id)

{
  uint local_14;
  int local_c;
  undefined4 local_8;
  undefined4 local_4;
  
  PTR_004e17d8 = malloc_(0x38);
  PTR_004e17d8->head = &PTR_004e17d8->values;
  PTR_004e17d8->tail = &PTR_004e17d8->values;
  PTR_004e17d8->valueSize = 0x14;
  PTR_004e17d8->capacity = 2;
  PTR_004e17d8->end = (void *)((int)&PTR_004e17d8[3].head + 1);
  challengeId_004e17cc = id & 0xffff;
  switch(challengeId_004e17cc) {
  case Attacks:
  case Health:
  case Survive:
  case Time:
    local_14 = 0xf;
    EventLoop::SolidifyNewChallengeFromId(&local_14);
    g_globalFlagset = g_globalFlagset | 0x8000;
    return;
  case Buttons:
    local_14 = 2;
    EventLoop::SolidifyNewChallengeFromId(&local_14);
    local_14 = 0xe;
    local_c = 0;
    EventLoop::SolidifyNewChallengeFromId(&local_14);
    FUN_0004a0e0();
    g_LinkedListRemovals = 1;
    break;
  case Challenge21:
    local_14 = 1;
    EventLoop::SolidifyNewChallengeFromId(&local_14);
    return;
  case Damage:
    FUN_0004a0e0();
    FUN_0012dcd0();
    return;
  case Kills:
    local_14 = 6;
    EventLoop::SolidifyNewChallengeFromId(&local_14);
    FUN_0004a0e0();
    return;
  case KillsBOB:
    local_8 = 0;
    local_4 = 0;
    local_14 = 7;
    EventLoop::SolidifyNewChallengeFromId(&local_14);
    local_c = DAT_005295a8 + DAT_00528c20;
    local_14 = 0xd;
    EventLoop::SolidifyNewChallengeFromId(&local_14);
    FUN_0004a0e0();
    return;
  }
  return;
}




void EventLoop::SolidifyNewChallengeFromId(int *param_1)

{
  void *dst;
  undefined4 uVar1;
  
  if (PTR_004e17d8->tail == PTR_004e17d8->end) {
    PTR_004e17d8 = (Buffer<> *)runtime::ExtendArray((Buffer *)PTR_004e17d8);
  }
  dst = PTR_004e17d8->tail;
  PTR_004e17d8->tail = (void *)((uint)PTR_004e17d8->valueSize + (int)dst);
  memcpy(dst,param_1,*(uint *)(&DAT_004231cc + *param_1 * 0xc));
  switch(*param_1) {
  case 0:
  case 1:
  case 2:
  case 3:
  case 5:
  case 6:
  case 7:
  case 8:
  case 0xb:
  case 0xc:
  case 0x10:
  case 0x11:
  case 0x12:
    goto switchD_0004ae1c_caseD_0;
  case 4:
    if ((short)param_1[2] == 0) goto switchD_0004ae1c_caseD_d;
switchD_0004ae1c_caseD_0:
    uVar1 = FUN_0012fca0();
    *(undefined4 *)((int)dst + 4) = uVar1;
    return;
  case 9:
  case 10:
    uVar1 = FUN_0012fca0();
    *(undefined4 *)((int)dst + 4) = uVar1;
    return;
  default:
switchD_0004ae1c_caseD_d:
    *(undefined4 *)((int)dst + 4) = 0;
    return;
  }
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void FUN_0004c560(CutsceneEventsDescriptor *events)

{
  void *in_ECX;
  void *pvVar1;
  int iVar2;
  char *name;
  void *local_4;
  CutsceneEventType event_type;
  
  if (events != (CutsceneEventsDescriptor *)0x0) {
    event_type = events->eventType;
    local_4 = in_ECX;
    while (event_type != NoEvent) {
      if (events->eventType == New_Name_(17)) {
        events->field_0x91 = 0;
        events->field_0x92 = 0;
        events->field_0x93 = 0;
        events->field131_0x9c = (Object *)0x0;
        name = asset_name_00423320;
                    // Clear all current global asset name
        iVar2 = 6;
        do {
          if (*(int *)name == 0x5f646961) {
            Assets::GetResourceBytes(name,&local_4);
            pvVar1 = local_4;
            if (local_4 == (void *)0x0) {
              runtime::ExitGame(2);
            }
          }
          else {
            pvVar1 = (void *)0x0;
          }
          Assets::DestroyAssetOrDecrement(pvVar1);
          name = (char *)((int)name + 0x80);
          iVar2 = iVar2 + -1;
        } while (iVar2 != 0);
      }
      else if ((events->eventType == New_Name_(27)) && (events->field4_0x4 == 0.0)) {
        FUN_0004c850((Cutscene *)0x0,0,events,0,0);
      }
      events = (CutsceneEventsDescriptor *)
               (&events->field_0x0 + CutsceneEventSizes[events->eventType]);
      event_type = events->eventType;
    }
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void * CutsceneEvents::Get(CutsceneEvents *param_1,char *eventName)

{
  CutsceneEventsDescriptor *events;
  void *res;
  BOOL BVar1;
  CutsceneEventsDescriptor *local_4;
  CutsceneEventsDescriptor *loaded;
  
  param_1->field6_0x6[0] = '\0';
  param_1->field_0x86 = 0;
  local_4 = (CutsceneEventsDescriptor *)eventName;
  res = Assets::newAssetInstance(Assets::LoadedResources,eventName);
  if (res == (void *)0x0) {
    BVar1 = LoadResourceFromFiles((int)eventName);
    if (BVar1 == 0) {
      return (void *)0x0;
    }
  }
  if (*(int *)eventName != 0x5f646961) {
    FUN_0004c560((CutsceneEventsDescriptor *)0x0);
    return (void *)0x0;
  }
  Assets::GetResourceBytes(eventName,&local_4);
  events = local_4;
  if (local_4 == (CutsceneEventsDescriptor *)0x0) {
    runtime::ExitGame(2);
  }
  FUN_0004c560(events);
  return events;
}



undefined4 __thiscall

void EventLoop::PopImportantStack(void)

{
  if (-1 < Cutscene::CurrentCutsceneIndex) {
    Cutscene::drop(Cutscene::LoadedCutscenes[Cutscene::CurrentCutsceneIndex]);
    Cutscene::LoadedCutscenes[Cutscene::CurrentCutsceneIndex] = (Cutscene *)0x0;
    Cutscene::CurrentCutsceneIndex = Cutscene::CurrentCutsceneIndex + -1;
    g_stateStack = g_stateStack + -1;
    if (g_stateStack < 0) {
      g_stateStack = 0;
    }
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void __fastcall Events::UpdateDialogState(void)

{
  BOOL timer_ended;
  int *piVar1;
  float fVar2;
  
  if (DAT_004ee22c == (Cutscene *)0x0) {
    if (NumDialogsAgain__ == 0) {
      return;
    }
    SetDialogState(TextIncoming);
  }
  if (DAT_004ee290 != 0) {
    if (DialogInputHandlerType2 == (InputHandlerBase *)0x0) {
      if (((int)Input::InputHandlers->tail - (int)Input::InputHandlers->head) /
          (int)(uint)Input::InputHandlers->valueSize == 0) {
        piVar1 = (int *)0x0;
      }
      else {
        piVar1 = *(int **)(Input::InputHandlers->head->handlerName +
                          (Input::NumInputHandlers - 1) * (uint)Input::InputHandlers->valueSize + -4
                          );
      }
      if (*piVar1 == 3) {
        ::Scripting::CreateInputHandler3((InputHandlerType3 **)&DialogInputHandlerType2);
      }
      else {
        ::Scripting::CreateScriptType2((InputHandlerType4 **)&DialogInputHandlerType2);
      }
      runtime::PushInputHandlerAndSetActive(DialogInputHandlerType2,"dialog");
    }
    FUN_00109470((InputHandlerType4 *)DialogInputHandlerType2);
    Input::UpdateMenuInput((InputHandlerType3 *)DialogInputHandlerType2,DAT_004ee2a8);
  }
  if (DAT_004ee22c->length <= DAT_004ee22c->t) {
    Cutscene::update(DAT_004ee22c,0.0,0.0,0);
  }
  fVar2 = 0.0;
  if (runtime::dx_timer <= 0.0) {
    fVar2 = runtime::DeltaTime * runtime::TimeScale;
  }
  RuncutsceneAndShouldEnd(fVar2,DAT_004ee22c,(Camera *)&DAT_004ee230);
  if (PlayDialogAudio != 0) {
    FUN_00057450();
  }
  switch(Game::DialogState) {
  case TextIncoming:
    fVar2 = (DialogInputTimer - 0.3) * -3.3333333;
    if (fVar2 <= 1.0) {
      DialogOutputTimer = 0.0;
      if (0.0 <= fVar2) {
        DialogOutputTimer = fVar2;
      }
    }
    else {
      DialogOutputTimer = 1.0;
    }
    timer_ended = Timer::reduce(&DialogInputTimer);
    if (timer_ended != 0) {
      SetDialogState(WaitOnInput);
    }
    break;
  case WaitOnInput:
    if (DAT_004ee290 == 0) {
      timer_ended = Timer::reduce(&DialogInputTimer);
    }
    else {
      timer_ended = NotWaitingOnDialogInput;
      if (DAT_004ee1fc == 0) goto LAB_00058017;
    }
    if (timer_ended != 0) {
      SetDialogState(TextShrinking);
    }
LAB_00058017:
    fVar2 = 0.0;
    if (runtime::dx_timer <= 0.0) {
      fVar2 = runtime::DeltaTime * runtime::TimeScale;
    }
    TimeWaitingForInput_ = TimeWaitingForInput_ + fVar2;
    return;
  case TextShrinking:
    fVar2 = 1.0 - (DialogInputTimer - 0.3) * -3.3333333;
    if (0.0 <= fVar2) {
      DialogOutputTimer = 1.0;
      if (fVar2 <= 1.0) {
        DialogOutputTimer = fVar2;
      }
    }
    else {
      DialogOutputTimer = 0.0;
    }
    timer_ended = Timer::reduce(&DialogInputTimer);
    if (timer_ended != 0) {
      if (InMapView != 0) {
        SetDialogState(OpeningMapView);
        return;
      }
LAB_00058129:
      FUN_00058ae0();
      return;
    }
    break;
  case DialogEnded:
    if (1 < NumDialogsAgain__) {
      DialogTexts[DAT_004ee1e0].dialog[0] = L'\0';
      DAT_004ee1e0 = DAT_004ee1e0 + 1;
      if (7 < DAT_004ee1e0) {
        DAT_004ee1e0 = 0;
      }
      NumDialogsAgain__ = NumDialogsAgain__ + -1;
      FUN_000589f0();
      SetDialogState(TextIncoming);
      return;
    }
    SetDialogState(NotInDialog);
    return;
  case OpeningMapView:
    if (DAT_004ee2b4 != 0) goto LAB_00058129;
  }
  return;
}



// WARNING: Globals starting with '_' overlap smaller symbols at the same address
// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


BOOL __thiscall Events::BeginDialogSequence(char *param_1,undefined1 param_2)

{
  BOOL BVar1;
  
  if (8 < NumDialogsAgain__ + 1) {
    return 0;
  }
  loctext::get_text("aid_loctext_ghoulies_dialog_dialogs","dialogs",param_1,u__00507e78);
  BVar1 = CreateDialog(u__00507e78,param_2);
  return BVar1;
}




void Events::createMapViewSceneControl(void)

{
  sceneControlObjParams *params;
  
  params = (sceneControlObjParams *)Assets::GetObjParams(asset_name_00424880);
  if (params != (sceneControlObjParams *)0x0) {
    Assets::CreateEntityFromParams((objParams *)params);
    free(params);
    return;
  }
  return;
}



// WARNING: Inlined function: PlayDialogAudio
// WARNING: Globals starting with '_' overlap smaller symbols at the same address
// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void Events::SetDialogState(DialogState newState)

{
  float *pfVar1;
  Scene *pSVar2;
  i16 soundSourceIndex;
  DialogText *pDVar3;
  int iVar4;
  char *pcVar5;
  undefined4 *puVar6;
  float fVar7;
  undefined4 uVar8;
  float local_120 [3];
  float local_114;
  undefined4 local_110;
  undefined4 local_10c;
  undefined4 local_108;
  undefined4 local_e5;
  undefined4 local_e1 [22];
  undefined4 local_88;
  undefined4 local_65 [24];
  
  if (newState != Game::DialogState) {
    if (Game::DialogState == NotInDialog) {
      Game::NotAllowedToPause = Game::NotAllowedToPause + 1;
      g_gameStateStack = g_gameStateStack + 1;
      if ((g_globalFlagset & Paused) == 0) {
        UpdateActionBeginEnds(0xff,0);
      }
      if (DAT_004ee2a8 == (Scene *)0x0) {
        pcVar5 = "aid_loctext_ghoulies_menu_menutext";
        puVar6 = &local_108;
        for (iVar4 = 8; iVar4 != 0; iVar4 = iVar4 + -1) {
          *puVar6 = *(undefined4 *)pcVar5;
          pcVar5 = pcVar5 + 4;
          puVar6 = puVar6 + 1;
        }
        *(undefined2 *)puVar6 = *(undefined2 *)pcVar5;
        *(char *)((int)puVar6 + 2) = pcVar5[2];
        puVar6 = &local_e5;
        for (iVar4 = 0x17; iVar4 != 0; iVar4 = iVar4 + -1) {
          *puVar6 = 0;
          puVar6 = puVar6 + 1;
        }
        *(undefined1 *)puVar6 = 0;
        local_120[2] = (float)g_DXContext.backBufferWidth * 0.5;
        local_114 = g_DXContext.field35_0x64 - 16.0;
        local_110 = 0;
        local_10c = 0xc2900000;
        local_120[0] = 40.0;
        local_120[1] = -36.0;
        TransitionAndLoadScene
                  (0,0,local_120 + 2,&local_110,local_120,0,0x3fc00000,&DAT_3f400000,"menutext",
                   &local_108,0x80);
        pSVar2 = DAT_004ee2a8;
        pfVar1 = &DAT_004ee2a8->someTimer;
        DAT_004ee2a8->originalTimerValue = 0.3;
        if (0.3 < *pfVar1) {
          pSVar2->someTimer = 0.3;
        }
        *(float *)(pSVar2->field3814_0x1020 + 0x20) = 0.3;
        FUN_00142860(0x40000000,0);
      }
      g_globalFlagset = g_globalFlagset | 0x40;
      runtime::rand = runtime::rand * 0x19660d + 0x3c6ef35f;
      local_120[0] = (float)(runtime::rand & 0x7fffff | 0x3f800000);
      fVar7 = local_120[0] - 1.0;
      Camera::ctor((Camera *)&DAT_004ee230,"dialog",(ProjectionSetBitField)0x8);
      Camera::AppendAndSelect((Camera *)&DAT_004ee230,0);
      if ((PTR_00506c6c->field2_0x8[4] & 0x40) != 0) {
        pcVar5 = "aid_model_ghoulies_actor_dialogbat";
        puVar6 = &local_88;
        for (iVar4 = 8; iVar4 != 0; iVar4 = iVar4 + -1) {
          *puVar6 = *(undefined4 *)pcVar5;
          pcVar5 = pcVar5 + 4;
          puVar6 = puVar6 + 1;
        }
        *(undefined2 *)puVar6 = *(undefined2 *)pcVar5;
        *(char *)((int)puVar6 + 2) = pcVar5[2];
        puVar6 = local_65;
        for (iVar4 = 0x17; iVar4 != 0; iVar4 = iVar4 + -1) {
          *puVar6 = 0;
          puVar6 = puVar6 + 1;
        }
        *(undefined1 *)puVar6 = 0;
        pcVar5 = "aid_model_ghoulies_actor_dialogbatgold";
        puVar6 = &local_108;
        for (iVar4 = 9; iVar4 != 0; iVar4 = iVar4 + -1) {
          *puVar6 = *(undefined4 *)pcVar5;
          pcVar5 = pcVar5 + 4;
          puVar6 = puVar6 + 1;
        }
        *(undefined2 *)puVar6 = *(undefined2 *)pcVar5;
        *(char *)((int)puVar6 + 2) = pcVar5[2];
        puVar6 = local_e1;
        for (iVar4 = 0x16; iVar4 != 0; iVar4 = iVar4 + -1) {
          *puVar6 = 0;
          puVar6 = puVar6 + 1;
        }
        *(undefined1 *)puVar6 = 0;
        FUN_0004e610();
      }
      DAT_004ee22c = Assets::LoadCutscene
                               ("aid_cutscene_ghoulies_dialogs_dialogpage1" + (int)fVar7 * 0x80,6,
                                (Camera *)&DAT_004ee230);
      if (DialogTexts[DAT_004ee1e0].nullchar_ == '\0') {
        Camera::SetActiveCameraConfig(0,"dialog");
      }
      _DAT_004ee2a0 = (uint)(DialogTexts[DAT_004ee1e0].nullchar_ == '\0');
      FUN_000589f0();
    }
    else if (Game::DialogState == TextIncoming) {
      TimeWaitingForInput_ = 0.0;
    }
    pSVar2 = DAT_004ee2a8;
    uVar8 = 0;
    switch(newState) {
    case NotInDialog:
                    // Set back to normal
      InADialogSequence = 0;
      FUN_00058b90();
      Audio::LoadReverbSettings(DAT_004ee2ac);
      Game::NotAllowedToPause = Game::NotAllowedToPause + -1;
      g_globalFlagset = g_globalFlagset & 0xffffffbf;
      g_gameStateStack = g_gameStateStack + -1;
      Cutscene::dtor(DAT_004ee22c);
      DAT_004ee22c = (Cutscene *)0x0;
      Camera::setActiveCamera(&DAT_004ee230);
      if ((DialogInputHandlerType2 != (InputHandlerBase *)0x0) &&
         (DialogInputHandlerType2->active != 0)) {
        ::Scripting::PopInputHandler();
        FUN_00108230();
        DialogInputHandlerType2 = (InputHandlerBase *)0x0;
      }
      if (DAT_004ee2a8 != (Scene *)0x0) {
        Scene::free(DAT_004ee2a8);
        DAT_004ee2a8 = (Scene *)0x0;
      }
      FUN_00057400();
      DAT_004ee1fc = 0;
      FUN_000577b0();
      NumDialogsAgain__ = 0;
      NumDialogs = 0;
      DAT_004ee1e0 = 0;
      pDVar3 = DialogTexts;
      do {
        pDVar3->dialog[0] = L'\0';
        pDVar3 = pDVar3 + 1;
      } while ((int)pDVar3 < 0x4ee1e0);
      if ((g_globalFlagset & Paused) == 0) {
        UpdateActionBeginEnds(0xff,1);
        Game::DialogState = newState;
        return;
      }
      break;
    case TextIncoming:
      DialogInputTimer = 0.3;
      InADialogSequence = 1;
      DialogOutputTimer = 0.0;
      FUN_00058b50(DAT_004ee290);
      if (DAT_004ee1fc != 0) {
        FUN_00142180();
        Game::DialogState = newState;
        return;
      }
      break;
    case WaitOnInput:
      if (PlayDialogAudio != 0) {
        uVar8 = 0;
        soundSourceIndex = Audio::CreateSoundSourceAndReturnIndex(AudioType0);
        if (soundSourceIndex != -1) {
          Audio::SoundSources[soundSourceIndex].flags = 1;
          Audio::FindBySoundbankStrAndPlay(UnspecifiedAudio,soundSourceIndex);
        }
      }
      DialogInputTimer = DAT_004ee298;
      InADialogSequence = 1;
      DialogOutputTimer = 1.0;
      NotWaitingOnDialogInput = uVar8;
      Game::DialogState = newState;
      return;
    case TextShrinking:
      DAT_004ee1fc = (uint)(DAT_004ee290 != 0);
      DialogInputTimer = 0.3;
      InADialogSequence = 1;
      DialogOutputTimer = 1.0;
      if (DAT_004ee1fc != 0) {
        DAT_004ee2a8->field2160_0x950 = 0;
        FUN_00142c20(3,pSVar2);
      }
      if (InMapView != 0) {
        createMapViewSceneControl();
        Game::DialogState = newState;
        return;
      }
      break;
    case DialogEnded:
      DialogInputTimer = 0.0;
      DAT_004ee1fc = 0;
      InADialogSequence = 0;
      DialogOutputTimer = 0.0;
      Game::DialogState = newState;
      return;
    case OpeningMapView:
      InMapView = 0;
      DAT_004ee2b4 = 0;
    }
    Game::DialogState = newState;
  }
  return;
}




void UnregisterScript__(int param_1)

{
  astruct_55 **ppaVar1;
  void *mem;
  astruct_29 *paVar2;
  undefined4 uVar3;
  uint uVar4;
  LoctextValueContext **dst;
  int iVar5;
  HeapTableEntry *pHVar6;
  astruct_55 *paVar7;
  uint uVar8;
  
  iVar5 = *(int *)param_1;
  if (iVar5 != 0) {
    uVar4 = ((int)LoctextValueBuffer->tail - (int)LoctextValueBuffer->head) /
            (int)(uint)LoctextValueBuffer->valueSize;
    uVar8 = 0;
    *(undefined4 *)(iVar5 + 8) = *(undefined4 *)(iVar5 + 4);
    paVar2 = LoctextValueBuffer;
    if (uVar4 != 0) {
      paVar7 = LoctextValueBuffer->head;
      do {
        if (paVar7->field0_0x0 == (LoctextValueContext *)param_1) {
          uVar4 = (uint)LoctextValueBuffer->valueSize;
          dst = (LoctextValueContext **)((int)&LoctextValueBuffer->head->field0_0x0 + uVar4 * uVar8)
          ;
          ppaVar1 = &LoctextValueBuffer->tail;
          if (dst < (undefined1 *)((int)*ppaVar1 - uVar4)) {
            memcpy(dst,(undefined1 *)((int)*ppaVar1 - uVar4),uVar4);
          }
          *ppaVar1 = (astruct_55 *)((int)*ppaVar1 - (uint)paVar2->valueSize);
          break;
        }
        uVar8 = uVar8 + 1;
        paVar7 = (astruct_55 *)((int)&paVar7->field0_0x0 + (uint)LoctextValueBuffer->valueSize);
      } while (uVar8 < uVar4);
    }
    mem = *(void **)param_1;
    if (mem != (void *)0x0) {
      iVar5 = FindHeapOf(mem);
      uVar3 = runtime::CurrentHeapToAllocateFrom;
      if (g_HeapTableBase[iVar5].heapHandle == (HANDLE)0x0) {
        pHVar6 = (HeapTableEntry *)0x0;
      }
      else {
        pHVar6 = g_HeapTableBase + iVar5;
      }
      runtime::CurrentHeapToAllocateFrom = iVar5;
      XAPILIB::HeapFree(pHVar6->heapHandle,0,mem);
      runtime::CurrentHeapToAllocateFrom = uVar3;
      *(undefined4 *)param_1 = 0;
    }
  }
  iVar5 = FindHeapOf((void *)param_1);
  uVar3 = runtime::CurrentHeapToAllocateFrom;
  if (g_HeapTableBase[iVar5].heapHandle == (HANDLE)0x0) {
    pHVar6 = (HeapTableEntry *)0x0;
  }
  else {
    pHVar6 = g_HeapTableBase + iVar5;
  }
  runtime::CurrentHeapToAllocateFrom = iVar5;
  XAPILIB::HeapFree(pHVar6->heapHandle,0,(LPVOID)param_1);
  runtime::CurrentHeapToAllocateFrom = uVar3;
  return;
}




void __fastcall FUN_00075120(Message *eventCtx,vec3 *param_2)

{
  ObjMsgID OVar1;
  float10 invMagnitude;
  float newZ;
  float newY;
  float fVar4;
  float squared_sum;
  float local_20;
  float scaled_update;
  float fVar1;
  actor *fVar2;
  float fVar3;
  float max_displacement;
  
  fVar1 = (float)eventCtx[3].header.msgId;
  OVar1 = eventCtx[1].header.msgId;
  fVar2 = eventCtx[3].header.someActor;
  fVar3 = (float)eventCtx[4].header.msgId;
  if (runtime::dx_timer <= 0.0) {
    scaled_update = runtime::DeltaTime * runtime::TimeScale;
  }
  else {
    scaled_update = 0.0;
  }
  if (*(float *)(OVar1 + 0x930) <= 0.0) {
    local_20 = *(float *)(OVar1 + 0x92c);
  }
  else {
    local_20 = 0.0;
  }
  newY = param_2->y;
  newZ = param_2->z;
  fVar4 = param_2->x;
  max_displacement = local_20 * scaled_update * 50.0;
  squared_sum = newZ * newZ + newY * newY + fVar4 * fVar4;
  if ((max_displacement < SQRT(squared_sum)) && (squared_sum != 0.0)) {
    invMagnitude = (float10)invsqrt(squared_sum);
    invMagnitude = invMagnitude * (float10)max_displacement;
    fVar4 = (float)((float10)fVar4 * invMagnitude);
    newY = (float)((float10)newY * invMagnitude);
    newZ = (float)((float10)newZ * invMagnitude);
  }
  eventCtx[3].header.msgId = (ObjMsgID)(fVar4 + fVar1);
  eventCtx[3].header.someActor = (actor *)(newY + (float)fVar2);
  eventCtx[4].header.msgId = (ObjMsgID)(newZ + fVar3);
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


actor * EventLoop::SpawnGrimReaper(float param1,float param2)

{
  actorParams *params;
  actor_conflict5 *av;
  actor *grim;
  vec3 pos;
  vec3 rot;
  vec3 local_30;
  MessageHeader local_24;
  entityStrategyGrimReaper *strategy;
  
  if (Game::SceneInfo.playerActors.prev == (actor_0x93c_conflict5)0x0) {
    av = (actor_conflict5 *)0x0;
  }
  else {
    av = ADJ(Game::SceneInfo.playerActors.prev);
  }
  avatar::getWorldPosition((avatar *)av,&local_30);
  GetReaperPosFromMarkerAndSpawn(&pos,&rot,&local_30);
  params = (actorParams *)Assets::GetObjParams("aid_objparams_ghoulies_actor_grimreaper");
  if (params == (actorParams *)0x0) {
    grim = (actor *)0x0;
  }
  else {
    (params->avatarParams).pos.x = pos.x;
    (params->avatarParams).pos.y = pos.y;
    (params->avatarParams).pos.z = pos.z;
    (params->avatarParams).rotEuler.x = rot.x;
    (params->avatarParams).rotEuler.y = rot.y;
    (params->avatarParams).rotEuler.z = rot.z;
    (params->avatarParams).scale = 1.0;
    *(undefined2 *)((int)&(params->avatarParams).impactId + 2) = 0;
    (params->avatarParams).ghoulyboxId2 = 0;
    grim = (actor *)Assets::CreateEntityFromParams((objParams *)params);
    free(params);
    if (grim != (actor *)0x0) {
      grim->droneTriggerId = Null;
      local_24.msgId = Actor_SetDroneAction;
      local_24.someActor = (actor *)0x4;
      (*((ObjectFullVTable *)(grim->avatar).vtable)->onMessage)(grim,&local_24);
    }
  }
  strategy = (entityStrategyGrimReaper *)grim->strategy;
  if (param1 != 0.0) {
    strategy->optionalVal1 = param1;
  }
  if (param2 != 0.0) {
    strategy->optionalVal2 = param2;
  }
  return grim;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void GetReaperPosFromMarkerAndSpawn(vec3 *pos,vec3 *rot,vec3 *param_3)

{
  uint16_t index;
  int iVar1;
  Marker *entry;
  Marker *first_entry;
  uint i;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  vec3 local_c;
  float puVar8;
  uint numMarkers;
  
  index = Marker::getFurthestMarkerFromPoint(Reaper,param_3);
  first_entry = (Game::GameState.markerInstance)->marker;
  numMarkers = (Game::GameState.markerInstance)->numMarkers;
  i = 0;
  entry = first_entry;
  if (numMarkers != 0) {
    do {
      if (entry->id == index) {
        local_c.x = (entry->pos).x;
        local_c.y = (entry->pos).y;
        local_c.z = (entry->pos).z;
        break;
      }
      i = i + 1;
      entry = (Marker *)((int)&entry->size + entry->size);
    } while (i < numMarkers);
  }
  i = 0;
  if (numMarkers != 0) {
    do {
      if (first_entry->id == index) {
        rot->x = (first_entry->eulerRot).x;
        rot->y = (first_entry->eulerRot).y;
        rot->z = (first_entry->eulerRot).z;
        break;
      }
      i = i + 1;
      first_entry = (Marker *)((int)&first_entry->size + first_entry->size);
    } while (i < numMarkers);
  }
  uVar5 = 0;
  uVar4 = 0;
  uVar3 = 0;
                    // 15
  puVar8 = (float)&DAT_41700000;
  uVar2 = 0;
  iVar1 = FUN_00110bf0(&local_c,-1,0);
  SpawnThingFromMarker(pos,0,&local_c,iVar1,uVar2,puVar8,uVar3,uVar4,uVar5,0);
  return;
}




void Events::RunChallengeSetupTriggers(void)

{
  int finished_challenges;
  int iVar1;
  undefined2 doorId;
  short local_c [2];
  MessageHeader msg_header;
  
  if (0 < ::Scripting::numScriptConditions) {
    UpdateChallenges();
    return;
  }
  switch(g_pauseMenuState_) {
  case Playing:
    UpdateChallenges();
    FUN_000d12e0();
    return;
  case EnteringPause:
    iVar1 = FUN_000d1190();
    if (iVar1 == 0) {
      return;
    }
    if (g_pauseMenuState_ == New_Name_(2)) {
      msg_header.msgId = Scene_EventEnd;
      msg_header.someActor = (actor *)0x1;
      EventLoop::NewMessage(&msg_header);
      EventLoop::DispatchMessage(&msg_header.msgId);
    }
    g_pauseMenuState_ = Paused;
    UpdateActionBeginEnds(0xff,1);
    return;
  case Paused:
    finished_challenges = UpdateChallengeStatus();
    if (finished_challenges == 0) {
      return;
    }
    doorId = (undefined2)_ChallengeShort;
    g_globalFlagset = g_globalFlagset | NotInAChallenge?;
    iVar1 = FUN_0005b510();
    if (iVar1 != 0) {
      if (g_pauseMenuState_ == New_Name_(2)) {
        msg_header.msgId = Scene_EventEnd;
        msg_header.someActor = (actor *)0x1;
        EventLoop::NewMessage(&msg_header);
        EventLoop::DispatchMessage(&msg_header.msgId);
        doorId = (undefined2)_ChallengeShort;
      }
      iVar1 = FUN_0005b510();
      if (iVar1 != 0) {
        UpdateDoor(doorId,0,0,0);
      }
      g_pauseMenuState_ = New_Name_(2);
      UpdateActionBeginEnds(0xff,0);
      return;
    }
    break;
  case New_Name_(2):
    iVar1 = FUN_0005b510();
    if (iVar1 != 0) {
      iVar1 = FUN_0005b780(local_c);
      if (iVar1 == 0) {
        return;
      }
      if (local_c[0] != 0) {
        return;
      }
    }
    break;
  default:
    goto switchD_000d0326_default;
  }
  BeginEventsSequence(0);
switchD_000d0326_default:
  return;
}




void DrainChallengeList(void)

{
  LiveChallenge *pLVar1;
  undefined4 uVar2;
  int iVar3;
  HeapTableEntry *pHVar4;
  LiveChallenge *pLVar5;
  ChallengeBuffer *mem;
  
  if (EventLoop::ChallengeList != (ChallengeBuffer *)0x0) {
    pLVar1 = EventLoop::ChallengeList->tail;
    mem = EventLoop::ChallengeList;
    for (pLVar5 = EventLoop::ChallengeList->head; pLVar5 < pLVar1; pLVar5 = pLVar5 + 1) {
      if ((*(int *)pLVar5 == 0xf) && (*(int *)&pLVar5->field_0x84 != 0)) {
        Camera::setActiveCamera(&pLVar5->field_0x24);
        *(undefined4 *)&pLVar5->field_0x84 = 0;
        mem = EventLoop::ChallengeList;
      }
    }
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
    EventLoop::ChallengeList = (ChallengeBuffer *)0x0;
    runtime::CurrentHeapToAllocateFrom = uVar2;
  }
  return;
}




void ExitChallenge_(void)

{
  DrainChallengeList();
  EventLoop::ChallengeShort = 0;
  g_pauseMenuState_ = New_Name;
  g_globalFlagset = g_globalFlagset & ~NotInAChallenge?;
  return;
}




void EventLoop::CreateNewChallengeList(ushort param_1,uint param_2,char *eventIntroName)

{
  char cVar1;
  int iVar2;
  
  if (ChallengeShort == 0) {
    ChallengeList = malloc_(0x120);
    ChallengeList->head = ChallengeList->values;
    ChallengeList->tail = ChallengeList->values;
    ChallengeList->valueSize = 0x88;
    ChallengeList->capacity = 2;
    ChallengeList->end = (LiveChallenge *)(ChallengeList + 1);
  }
  else {
    g_pauseMenuState_ = New_Name;
  }
  ChallengeShort = param_1;
  ChallengeUint = param_2;
  DAT_00506528 = 0;
  iVar2 = (int)ChallengeIntroName - (int)eventIntroName;
  do {
    cVar1 = *eventIntroName;
    eventIntroName[iVar2] = cVar1;
    eventIntroName = eventIntroName + 1;
  } while (cVar1 != '\0');
  return;
}




void CreateNewChallenge(TimeLimitChallenge *chlng)

{
  LiveChallenge *challenge;
  
  if (((undefined1)g_globalFlagset & GrimReaperAlive) != 0) {
    switch(chlng->challengeType) {
    case TimeLimit:
    case 7:
    case 8:
    case 9:
    case 10:
    case 0xb:
    case 0xc:
    case 0x10:
    case 0x11:
      return;
    }
  }
  if (EventLoop::ChallengeList->tail == EventLoop::ChallengeList->end) {
    EventLoop::ChallengeList =
         (ChallengeBuffer *)runtime::ExtendArray((Buffer *)EventLoop::ChallengeList);
  }
  challenge = EventLoop::ChallengeList->tail;
  EventLoop::ChallengeList->tail =
       (LiveChallenge *)((int)&challenge->field_0x0 + (uint)EventLoop::ChallengeList->valueSize);
  memcpy(challenge,chlng,(&DAT_0042890c)[chlng->challengeType * 5]);
  challenge->inittedZero1 = 0;
  challenge->inittedZero2 = 0;
  return;
}




LiveChallenge * __fastcall FUN_000d0650(undefined4 param_1,int param_2)

{
  LiveChallenge *pLVar1;
  
  if (EventLoop::ChallengeList == (ChallengeBuffer *)0x0) {
    return (LiveChallenge *)0x0;
  }
  pLVar1 = EventLoop::ChallengeList->head;
  while( true ) {
    if (EventLoop::ChallengeList->tail <= pLVar1) {
      return (LiveChallenge *)0x0;
    }
    if (*(int *)pLVar1 == param_2) break;
    pLVar1 = pLVar1 + 1;
  }
  return pLVar1;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void StartEventsSequence(void)

{
  BeginEventsSequence(1);
  FUN_000d12e0();
  return;
}




bool onTouchChallengeCompleted(void)

{
  uint uVar1;
  Draw2D *head;
  bool bVar2;
  int iVar3;
  MessageHeader msg;
  
  if (EventLoop::ChallengeList == (ChallengeBuffer *)0x0) {
    return false;
  }
  DrainChallengeList();
  Audio::loadAudioIntoEmptySlot(10,"XACT_SOUNDBANK_GSTREAMSDITTIES_EVENTCOMPLETE");
  DAT_0050653c = 0;
  head = game::doors->head;
  if (head < game::doors->tail) {
    do {
      if (*(ushort *)&head->field_0x4 == EventLoop::ChallengeShort) {
        if (g_pauseMenuState_ == New_Name_(2)) {
          msg.msgId = Scene_EventEnd;
          msg.someActor = (actor *)0x1;
          EventLoop::NewMessage(&msg);
          EventLoop::DispatchMessage(&msg.msgId);
        }
        uVar1 = _ChallengeShort;
        iVar3 = FUN_0005b510();
        if (iVar3 != 0) {
          UpdateDoor((short)uVar1,0,0,0);
        }
        g_pauseMenuState_ = New_Name_(2);
        iVar3 = 0;
        goto LAB_000d0916;
      }
      head = (Draw2D *)((int)&head->index + (uint)game::doors->valueSize);
    } while (head < game::doors->tail);
  }
  bVar2 = g_pauseMenuState_ == New_Name_(2);
  if (bVar2) {
    msg.msgId = Scene_EventEnd;
    msg.someActor = (actor *)0x1;
    EventLoop::NewMessage(&msg);
    EventLoop::DispatchMessage(&msg.msgId);
  }
  _ChallengeShort = _ChallengeShort & 0xffff0000;
  g_pauseMenuState_ = New_Name;
  if (bVar2) {
    iVar3 = 1;
LAB_000d0916:
    Events::UpdateActionBeginEnds(0xff,iVar3);
  }
  g_globalFlagset = g_globalFlagset | NotInAChallenge?;
  return true;
}



// WARNING: Globals starting with '_' overlap smaller symbols at the same address
// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void BeginEventsSequence(PauseState param_1)

{
  uint uVar1;
  int iVar2;
  bool bVar3;
  MessageHeader msgHeader;
  int iStack_8;
  LiveChallenge *pLStack_4;
  
  bVar3 = g_pauseMenuState_ == New_Name_(2);
  if (bVar3) {
    msgHeader.someActor = (actor *)0x1;
    msgHeader.msgId = Scene_EventEnd;
    EventLoop::NewMessage(&msgHeader);
    EventLoop::DispatchMessage(&msgHeader.msgId);
  }
  uVar1 = _ChallengeShort;
  iVar2 = 1;
  switch(param_1) {
  case New_Name:
    _ChallengeShort = _ChallengeShort & 0xffff0000;
    break;
  case Playing:
    FUN_000d0b10();
    msgHeader.someActor = (actor *)(_ChallengeShort & 0xffff);
    msgHeader.msgId = Scene_EventBegin;
    iStack_8 = ((int)EventLoop::ChallengeList->tail - (int)EventLoop::ChallengeList->head) /
               (int)(uint)EventLoop::ChallengeList->valueSize;
    pLStack_4 = EventLoop::ChallengeList->head;
    EventLoop::DispatchMessage(&msgHeader.msgId);
    uVar1 = _ChallengeShort;
    iVar2 = FUN_0005b510();
    if ((iVar2 != 0) &&
       (UpdateDoor((short)uVar1,5,EventLoop::ChallengeUint,1), EventLoop::ChallengeUint == 0)) {
      Audio::loadAudioIntoEmptySlot(9,"XACT_SOUNDBANK_GSTREAMSDITTIES_EVENTBEGIN");
    }
    iVar2 = 0;
    bVar3 = true;
    DAT_00506534 = 1.0;
    break;
  case Paused:
    iVar2 = 1;
    goto LAB_000d0ad6;
  case New_Name_(2):
    iVar2 = FUN_0005b510();
    if (iVar2 != 0) {
      UpdateDoor((short)uVar1,0,0,0);
    }
    iVar2 = 0;
LAB_000d0ad6:
    bVar3 = true;
  }
  g_pauseMenuState_ = param_1;
  if (bVar3) {
    Events::UpdateActionBeginEnds(0xff,iVar2);
  }
  return;
}




bool UpdateChallengeStatus(void)

{
  LiveChallenge **ppLVar1;
  ChallengeBuffer *pCVar2;
  undefined4 uVar3;
  int iVar4;
  uint *puVar5;
  char *audio;
  LiveChallenge *pLVar6;
  undefined1 *cam;
  LiveChallenge *pLVar7;
  float fVar8;
  LiveChallenge *local_14;
  ObjMsgID local_10;
  int local_c;
  ObjMsgID local_8;
  undefined4 local_4;
  bool spawn_grim;
  uint channel_index;
  
  local_8 = Null;
  local_10 = Null;
  if (EventLoop::ChallengeList == (ChallengeBuffer *)0x0) {
    return true;
  }
  fVar8 = 0.0;
  pLVar7 = EventLoop::ChallengeList->head;
  local_14 = EventLoop::ChallengeList->tail;
  local_c = 0;
  if (0.0 < FLOAT_00506538) {
    if (runtime::dx_timer <= 0.0) {
      fVar8 = runtime::DeltaTime * runtime::TimeScale;
    }
    FLOAT_00506538 = FLOAT_00506538 - fVar8;
  }
  local_4 = 0;
  FUN_000d0f20();
  if (pLVar7 < local_14) {
    cam = &pLVar7->field_0x24;
    do {
      if (((undefined1)g_globalFlagset & GrimReaperAlive) == 0) {
switchD_000d0bda_caseD_5:
        if (((Game::SceneInfo.playerActors.prev == (actor_0x93c_conflict5)0x0) ||
            (Game::SceneInfo.playerActors.prev == (actor_0x93c_conflict5)0x93c)) ||
           ((ADJ(Game::SceneInfo.playerActors.prev)->body->flagSet->flags->flag1 & 0x8000000) !=
            Null)) {
          uVar3 = 0;
        }
        else {
          uVar3 = (*(code *)(&PTR_LAB_003039cc)[*(int *)pLVar7 * 2])(pLVar7);
        }
        switch(uVar3) {
        case 1:
          local_8 = Scene_EventComplete;
          EventLoop::DispatchMessage(&local_8);
          FUN_0012fdc0();
          pLVar7->inittedZero1 = 0;
          if ((*(int *)pLVar7 == 0xf) && (*(int *)&pLVar7->field_0x84 != 0)) {
            Camera::setActiveCamera(cam);
            *(undefined4 *)&pLVar7->field_0x84 = 0;
          }
          pCVar2 = EventLoop::ChallengeList;
          ppLVar1 = &EventLoop::ChallengeList->tail;
          pLVar6 = (LiveChallenge *)
                   ((int)EventLoop::ChallengeList->tail - (uint)EventLoop::ChallengeList->valueSize)
          ;
          if (pLVar7 < pLVar6) {
            memcpy(pLVar7,pLVar6,(uint)EventLoop::ChallengeList->valueSize);
          }
          local_14 = local_14 + -1;
          *ppLVar1 = (LiveChallenge *)((int)*ppLVar1 - (uint)pCVar2->valueSize);
          pLVar7 = pLVar7 + -1;
          cam = cam + -0x88;
          local_8 = General_Activate;
          local_10 = General_Activate;
          break;
        case 2:
          local_c = local_c + 1;
          break;
        case 3:
          local_10 = Scene_EventFailed;
          EventLoop::DispatchMessage(&local_10);
          FUN_0012fdc0();
          spawn_grim = (bool)((undefined1)g_globalFlagset & GrimReaperAlive);
          pLVar7->inittedZero1 = 0;
          if (spawn_grim == false) {
            EventLoop::SpawnGrimReaper(ChallengeFloats.reaperFloat1,ChallengeFloats.reaperFloat2);
          }
          if ((*(int *)pLVar7 == 0xf) && (*(int *)&pLVar7->field_0x84 != 0)) {
            Camera::setActiveCamera(cam);
            *(undefined4 *)&pLVar7->field_0x84 = 0;
          }
          pCVar2 = EventLoop::ChallengeList;
          ppLVar1 = &EventLoop::ChallengeList->tail;
          pLVar6 = (LiveChallenge *)
                   ((int)EventLoop::ChallengeList->tail - (uint)EventLoop::ChallengeList->valueSize)
          ;
          if (pLVar7 < pLVar6) {
            memcpy(pLVar7,pLVar6,(uint)EventLoop::ChallengeList->valueSize);
          }
          local_14 = local_14 + -1;
          *ppLVar1 = (LiveChallenge *)((int)*ppLVar1 - (uint)pCVar2->valueSize);
          pLVar7 = pLVar7 + -1;
          cam = cam + -0x88;
          local_10 = General_Activate;
          break;
        case 4:
          if (((undefined1)g_globalFlagset & GrimReaperAlive) == 0) {
            _DAT_0050652c = 0;
            EventLoop::SpawnGrimReaper(ChallengeFloats.reaperFloat1,ChallengeFloats.reaperFloat2);
          }
          break;
        case 5:
          local_4 = 1;
          DAT_0050653c = 1;
        }
      }
      else {
        switch(*(int *)pLVar7) {
        case 4:
        case 7:
        case 8:
        case 9:
        case 10:
        case 0xb:
        case 0xc:
        case 0x10:
        case 0x11:
          if ((*(int *)pLVar7 == 0xf) && (*(int *)&pLVar7->field_0x84 != 0)) {
            Camera::setActiveCamera(cam);
            *(undefined4 *)&pLVar7->field_0x84 = 0;
          }
          pCVar2 = EventLoop::ChallengeList;
          ppLVar1 = &EventLoop::ChallengeList->tail;
          pLVar6 = (LiveChallenge *)
                   ((int)EventLoop::ChallengeList->tail - (uint)EventLoop::ChallengeList->valueSize)
          ;
          if (pLVar7 < pLVar6) {
            memcpy(pLVar7,pLVar6,(uint)EventLoop::ChallengeList->valueSize);
          }
          local_14 = local_14 + -1;
          *ppLVar1 = (LiveChallenge *)((int)*ppLVar1 - (uint)pCVar2->valueSize);
          pLVar7 = pLVar7 + -1;
          cam = cam + -0x88;
          break;
        default:
          goto switchD_000d0bda_caseD_5;
        }
      }
      pLVar7 = pLVar7 + 1;
      cam = cam + 0x88;
    } while (pLVar7 < local_14);
  }
  pLVar7 = EventLoop::ChallengeList->tail;
  pLVar6 = EventLoop::ChallengeList->head;
  iVar4 = ((int)pLVar7 - (int)pLVar6) / (int)(uint)EventLoop::ChallengeList->valueSize;
  if ((local_10 == Null) || ((iVar4 != 0 && (iVar4 != local_c)))) {
    if (local_8 == Null) goto LAB_000d0ec7;
    channel_index = 0xb;
    audio = "XACT_SOUNDBANK_GSTREAMSDITTIES_EVENTCOMPLETEHALF";
  }
  else {
    for (; pLVar6 < pLVar7; pLVar6 = pLVar6 + 1) {
      for (puVar5 = *(uint **)(*g_UIElement1 + 4); puVar5 < *(uint **)(*g_UIElement1 + 8);
          puVar5 = puVar5 + 0x25) {
        if (*puVar5 == pLVar6->inittedZero1) {
          if ((1 < (int)puVar5[2]) && ((int)puVar5[2] < 4)) {
            puVar5[3] = 0;
          }
          puVar5[2] = 5;
          puVar5[4] = 0x3fc00000;
          break;
        }
      }
      pLVar6->inittedZero1 = 0;
    }
    DrainChallengeList();
    if (local_8 == Null) goto LAB_000d0ec7;
    channel_index = 10;
    audio = "XACT_SOUNDBANK_GSTREAMSDITTIES_EVENTCOMPLETE";
  }
  Audio::loadAudioIntoEmptySlot(channel_index,audio);
LAB_000d0ec7:
  DAT_0050653c = local_4;
  return EventLoop::ChallengeList == (ChallengeBuffer *)0x0;
}




void UpdateChallenges(void)

{
  LiveChallenge *pLVar1;
  uint *puVar2;
  LiveChallenge *pLVar3;
  
  if (EventLoop::ChallengeList != (ChallengeBuffer *)0x0) {
    pLVar1 = EventLoop::ChallengeList->tail;
    for (pLVar3 = EventLoop::ChallengeList->head; pLVar3 < pLVar1; pLVar3 = pLVar3 + 1) {
      if (pLVar3->inittedZero1 != 0) {
        for (puVar2 = *(uint **)(*g_UIElement1 + 4); puVar2 < *(uint **)(*g_UIElement1 + 8);
            puVar2 = puVar2 + 0x25) {
          if (*puVar2 == pLVar3->inittedZero1) {
            puVar2[3] = (uint)2.0;
            break;
          }
        }
      }
    }
  }
  return;
}




void FUN_000d6f90(BonusChallengesMenu *param_1)

{
  void *pvVar1;
  int iVar2;
  int iVar3;
  
  iVar2 = 0;
  if (0 < param_1->numFuckers) {
    iVar3 = 0;
    do {
      pvVar1 = *(void **)((int)param_1->field4_0x10c + iVar3 + 0x45c);
      if (pvVar1 != (void *)0x0) {
        Assets::DestroyAssetOrDecrement(pvVar1);
        *(undefined4 *)((int)param_1->field4_0x10c + iVar3 + 0x45c) = 0;
      }
      iVar2 = iVar2 + 1;
      iVar3 = iVar3 + 0x46c;
    } while (iVar2 < param_1->numFuckers);
  }
  return;
}




undefined4 ExecuteScript(fxParticleImpactFlash *entity,void **bytesPtr,uint *param_3)

{
  char cVar1;
  int *piVar2;
  int iVar3;
  bool bVar4;
  vec3 *pvVar5;
  undefined4 uVar6;
  uint fxCustom_type;
  undefined3 extraout_var;
  vec3 *in_ECX;
  vec3 *extraout_ECX;
  vec3 *extraout_ECX_00;
  vec3 *extraout_ECX_01;
  vec3 *extraout_ECX_02;
  vec3 *extraout_ECX_03;
  float *pfVar7;
  uint *puVar8;
  bool bVar9;
  uint fxCustomType;
  fxParticleScript *fxps;
  Script *script_chars;
  fxParticleScript *stream;
  char *texture_name;
  uint operationType;
  float fxp_f1;
  float fxp_f2;
  float fxp_f3;
  float fxp_f4;
  float fxp_f5;
  float fxp_f6;
  
LAB_ScriptNextInstruction:
  fxps = *bytesPtr;
  switch((fxps->header).opcode) {
  case 0x1f41:
    *bytesPtr = &fxps->operationType;
    entity->maybeOtherFlags_ = 0;
    (entity->scriptV1).x = 0.0;
    break;
  case 0x1f42:
    in_ECX = (vec3 *)&fxps->f1;
    *bytesPtr = in_ECX;
    entity->maybeOtherFlags_ = 1;
    (entity->scriptV1).x = (float)fxps->operationType;
    break;
  case 0x1f43:
    *bytesPtr = &fxps->deg1;
    entity->maybeOtherFlags_ = 2;
    (entity->scriptV1).x = fxps->f1 * 0.5;
    (entity->scriptV1).y = 0.0;
    (entity->scriptV1).z = fxps->f1 * 0.5;
    if (fxps->operationType != 0) {
      *(byte *)&entity->flags = (byte)entity->flags | 4;
    }
    fxp_f6 = fxps->f2;
    bVar4 = fxp_f6 == fxps->f3;
    bVar9 = fxp_f6 < fxps->f3;
    (entity->scriptV2).y = fxp_f6 * 0.017453292;
    fxp_f6 = fxps->f3;
    goto LAB_000edef8;
  case 0x1f44:
    in_ECX = (vec3 *)&fxps->deg2;
    *bytesPtr = in_ECX;
    entity->maybeOtherFlags_ = 2;
    (entity->scriptV1).x = fxps->f1 * 0.5;
    (entity->scriptV1).y = 0.0;
    (entity->scriptV1).z = fxps->f2 * 0.5;
    if (fxps->operationType != 0) {
      *(byte *)&entity->flags = (byte)entity->flags | 4;
    }
    fxp_f6 = fxps->f3;
    bVar4 = fxp_f6 == fxps->deg1;
    bVar9 = fxp_f6 < fxps->deg1;
    (entity->scriptV2).y = fxp_f6 * 0.017453292;
    fxp_f6 = fxps->deg1;
LAB_000edef8:
    if (!bVar9 && !bVar4) {
      fxp_f6 = fxp_f6 + 360.0;
    }
    (entity->scriptV3).y = fxp_f6 * 0.017453292;
    goto LAB_ScriptNextInstruction;
  case 0x1f45:
    *bytesPtr = &fxps->deg1;
    entity->maybeOtherFlags_ = 3;
    in_ECX = (vec3 *)fxps->f2;
    (entity->scriptV1).x = (float)in_ECX;
    (entity->scriptV1).y = 0.0;
    (entity->scriptV1).z = fxps->f3;
    if (fxps->operationType != 0) {
      *(byte *)&entity->flags = (byte)entity->flags | 4;
    }
    goto LAB_ScriptNextInstruction;
  case 0x1f46:
    *bytesPtr = &fxps->deg1;
    entity->maybeOtherFlags_ = 4;
    (entity->scriptV1).x = fxps->f1;
    in_ECX = (vec3 *)fxps->f2;
    (entity->scriptV1).y = (float)in_ECX;
    (entity->scriptV1).z = fxps->f3;
    if (fxps->operationType != 0) {
      *(byte *)&entity->flags = (byte)entity->flags | 4;
    }
    goto LAB_ScriptNextInstruction;
  case 0x1f47:
    *bytesPtr = &fxps->deg3;
    entity->maybeOtherFlags_ = 5;
    (entity->scriptV1).x = fxps->f1 * 0.5;
    (entity->scriptV1).y = fxps->f1 * 0.5;
    (entity->scriptV1).z = fxps->f1 * 0.5;
    if (fxps->operationType != 0) {
      *(byte *)&entity->flags = (byte)entity->flags | 4;
    }
    fxp_f6 = fxps->f2;
    fxp_f5 = fxps->f3;
    fxp_f4 = fxps->f3;
    (entity->scriptV2).y = fxp_f6 * 0.017453292;
    fxp_f3 = fxps->f3;
    if (fxp_f4 <= fxp_f6 && fxp_f6 != fxp_f5) {
      fxp_f3 = fxp_f3 + 360.0;
    }
    (entity->scriptV3).y = fxp_f3 * 0.017453292;
    fxp_f6 = fxps->deg1;
    if (fxp_f6 < fxps->deg2 || fxp_f6 == fxps->deg2) goto LAB_000ee154;
    (entity->scriptV2).x = fxp_f6 * 0.017453292;
    (entity->scriptV3).x = (fxps->deg2 + 360.0) * 0.017453292;
    goto LAB_ScriptNextInstruction;
  case 0x1f48:
    *bytesPtr = &fxps->deg5;
    entity->maybeOtherFlags_ = 5;
    (entity->scriptV1).x = fxps->f1;
    (entity->scriptV1).y = fxps->f2;
    in_ECX = (vec3 *)fxps->f3;
    (entity->scriptV1).z = (float)in_ECX;
    if (fxps->operationType != 0) {
      *(byte *)&entity->flags = (byte)entity->flags | 4;
    }
    fxp_f6 = fxps->deg1;
    fxp_f5 = fxps->deg2;
    fxp_f4 = fxps->deg2;
    (entity->scriptV2).y = fxp_f6 * 0.017453292;
    fxp_f3 = fxps->deg2;
    if (fxp_f4 <= fxp_f6 && fxp_f6 != fxp_f5) {
      fxp_f3 = fxp_f3 + 360.0;
    }
    (entity->scriptV3).y = fxp_f3 * 0.017453292;
    fxp_f6 = fxps->deg3;
    fxp_f5 = fxps->deg4;
    fxp_f4 = fxps->deg4;
    (entity->scriptV2).x = fxp_f6 * 0.017453292;
    fxp_f3 = fxps->deg4;
    if (fxp_f6 < fxp_f4 || fxp_f6 == fxp_f5) goto LAB_000ee165;
    (entity->scriptV3).x = (fxp_f3 + 360.0) * 0.017453292;
    goto LAB_ScriptNextInstruction;
  case 0x1f49:
    *bytesPtr = &fxps->deg3;
    entity->maybeOtherFlags_ = 6;
    (entity->scriptV1).x = fxps->f1;
    in_ECX = (vec3 *)fxps->f2;
    (entity->scriptV1).y = (float)in_ECX;
    (entity->scriptV1).z = fxps->f3;
    if (fxps->operationType != 0) {
      *(byte *)&entity->flags = (byte)entity->flags | 4;
    }
    fxp_f6 = fxps->deg1;
    if (fxp_f6 < fxps->deg2 || fxp_f6 == fxps->deg2) {
LAB_000ee154:
      (entity->scriptV2).x = fxp_f6 * 0.017453292;
      fxp_f3 = fxps->deg2;
LAB_000ee165:
      (entity->scriptV3).x = fxp_f3 * 0.017453292;
    }
    else {
      (entity->scriptV2).x = fxp_f6 * 0.017453292;
      (entity->scriptV3).x = (fxps->deg2 + 360.0) * 0.017453292;
    }
    goto LAB_ScriptNextInstruction;
  case 0x1f4a:
    *bytesPtr = &fxps->f3;
    (entity->eulerRot_).x = (float)fxps->operationType * 0.017453292;
    (entity->eulerRot_).y = fxps->f1 * 0.017453292;
    (entity->eulerRot_).z = fxps->f2 * 0.017453292;
    goto LAB_ScriptNextInstruction;
  case 0x1f4b:
    in_ECX = (vec3 *)&fxps->f3;
    *bytesPtr = in_ECX;
    (entity->pos_).x = (float)fxps->operationType * 0.017453292;
    (entity->pos_).y = fxps->f1 * 0.017453292;
    (entity->pos_).z = fxps->f2 * 0.017453292;
    goto LAB_ScriptNextInstruction;
  case 0x1f4c:
    *bytesPtr = &fxps->f3;
    *(uint *)&entity->field_0x80 = fxps->operationType;
    in_ECX = (vec3 *)fxps->f1;
    *(vec3 **)&entity->field_0x84 = in_ECX;
    *(float *)&entity->field_0x88 = fxps->f2;
    goto LAB_ScriptNextInstruction;
  case 0x1f4d:
    *bytesPtr = &fxps->f3;
    *(float *)&entity->field_0x5c = (float)fxps->operationType * 0.017453292;
    *(float *)&entity->field_0x60 = fxps->f1 * 0.017453292;
    *(float *)&entity->field_0x64 = fxps->f2 * 0.017453292;
    goto LAB_ScriptNextInstruction;
  case 0x1f4e:
    in_ECX = (vec3 *)&fxps->f3;
    *bytesPtr = in_ECX;
    *(float *)&entity->field_0x68 = (float)fxps->operationType * 0.017453292;
    *(float *)&entity->field_0x6c = fxps->f1 * 0.017453292;
    *(float *)&entity->field_0x70 = fxps->f2 * 0.017453292;
    goto LAB_ScriptNextInstruction;
  case 0x1f4f:
    puVar8 = &fxps->operationType;
    *bytesPtr = &fxps[1].deg4;
    if (*puVar8 == 0x5f646961) {
      bVar4 = Assets::AssetInGroup(in_ECX,(int)puVar8,"texture");
      if (CONCAT31(extraout_var,bVar4) == 0) {
        FUN_000ed8c0(puVar8);
        in_ECX = extraout_ECX_01;
      }
      else {
        FUN_000ed730((int *)puVar8,fxps[1].f3,fxps[1].deg1 * 0.01,fxps[1].f1,(int)fxps[1].f2,
                     (int)fxps[1].deg2,(int)fxps[1].deg3);
        in_ECX = extraout_ECX_00;
      }
    }
    goto LAB_ScriptNextInstruction;
  case 0x1f50:
    *bytesPtr = &fxps->f1;
    if (entity->someAsset1 != (void *)0x0) {
      in_ECX = (vec3 *)Assets::DestroyAssetOrDecrement(entity->someAsset1);
      entity->someAsset1 = (void *)0x0;
    }
    entity->field184_0x13c = fxps->operationType;
    goto LAB_ScriptNextInstruction;
  case 0x1f51:
                    // Go to next command
    *bytesPtr = &fxps[2].deg1;
    if (entity == (fxParticleImpactFlash *)0x0) {
      if ((param_3 == (uint *)0x0) || ((*param_3 & 1) == 0)) {
        pvVar5 = &Game::someGlobalPos;
      }
      else {
        pvVar5 = (vec3 *)(param_3 + 1);
      }
      int32_t_0042a434 =
           FUN_000ed550(&fxps->f1,(uint)*(ushort *)((int)&fxps->operationType + 2),pvVar5,
                        (uint)(byte)fxps->operationType);
      if (int32_t_0042a434 == -1) {
        return 0;
      }
      entity = (fxParticleImpactFlash *)(&DAT_00506930)[int32_t_0042a434];
      if (entity == (fxParticleImpactFlash *)0x0) {
        return 0;
      }
      entity->field7_0x8 = -2.0;
      if (fxps[2].f3 == 0.0) {
        *(byte *)&entity->flags = (byte)entity->flags & 0x7f;
      }
      else {
        *(byte *)&entity->flags = (byte)entity->flags | 0x80;
      }
      if (*(char *)&fxps[1].f2 != '\0') {
        FUN_000ef870();
      }
      in_ECX = (vec3 *)param_3;
      if (param_3 != (uint *)0x0) {
        if ((*param_3 & 0x40) != 0) {
          if ((*param_3 & 0x40) == 0) {
            fxp_f6 = 1.0;
          }
          else {
            fxp_f6 = (float)param_3[0xb];
          }
          entity->field124_0xb8 = fxp_f6;
        }
        if ((*param_3 & 8) != 0) {
          if (((*param_3 & 8) == 0) || (piVar2 = (int *)param_3[0xc], piVar2 == (int *)0x0)) {
            *(undefined4 *)&entity->field_0xc4 = 0;
            *(undefined4 *)&entity->field_0xc8 = 0xffffffff;
          }
          else {
            *(int *)&entity->field_0xc0 = piVar2[1];
            iVar3 = *piVar2;
            if (iVar3 == 0) {
              in_ECX = (vec3 *)piVar2[2];
              *(vec3 **)&entity->field_0xc8 = in_ECX;
              *(undefined4 *)&entity->field_0xc4 = 0;
            }
            else if (iVar3 == 1) {
              *(short *)&entity->field_0xd0 = (short)piVar2[2];
              *(undefined4 *)&entity->field_0xc4 = 1;
              in_ECX = (vec3 *)0x0;
            }
            else {
              in_ECX = (vec3 *)(iVar3 - 2);
              if (in_ECX == (vec3 *)0x0) {
                uVar6 = FUN_00040af0(piVar2[1]);
                *(undefined4 *)&entity->field_0xd8 = uVar6;
                *(undefined4 *)&entity->field_0xc4 = 2;
                in_ECX = extraout_ECX;
              }
            }
          }
          goto LAB_ScriptNextInstruction;
        }
      }
      *(undefined4 *)&entity->field_0xc0 = 0;
    }
    goto LAB_ScriptNextInstruction;
  case 0x1f52:
    in_ECX = (vec3 *)&fxps->f2;
    *bytesPtr = in_ECX;
    if (fxps->f1 == 0.0) {
      fxp_f6 = 1.0 / (float)fxps->operationType;
      entity->field7_0x8 = fxp_f6;
      runtime::rand = runtime::rand * 0x19660d + 0x3c6ef35f;
      *(float *)&entity->field_0xc = ((float)(runtime::rand & 0x7fffff | 0x3f800000) - 1.0) * fxp_f6
      ;
    }
    else {
      entity->field7_0x8 = -2.0;
    }
    goto LAB_ScriptNextInstruction;
  case 0x1f53:
    fxp_f6 = -1.0;
    *bytesPtr = &fxps->f2;
    if (fxps->f1 == 0.0) {
      fxp_f6 = (float)fxps->operationType;
    }
    entity->field12_0x10 = fxp_f6;
    goto LAB_ScriptNextInstruction;
  case 0x1f54:
    *bytesPtr = &fxps[1].f1;
    FUN_000ed120();
    in_ECX = extraout_ECX_02;
    goto LAB_ScriptNextInstruction;
  case 0x1f55:
    *bytesPtr = &fxps[2].f2;
    puVar8 = &fxps->operationType;
    iVar3 = 0x15c - (int)puVar8;
    do {
      fxCustom_type = *puVar8;
      *(char *)((int)puVar8 + (int)entity + iVar3) = (char)fxCustom_type;
      puVar8 = (uint *)((int)puVar8 + 1);
    } while ((char)fxCustom_type != '\0');
    pfVar7 = &fxps[1].f1;
    in_ECX = (vec3 *)((int)entity + (0x1dc - (int)pfVar7));
    do {
      cVar1 = *(char *)pfVar7;
      *(char *)((int)pfVar7 + (int)in_ECX) = cVar1;
      pfVar7 = (float *)((int)pfVar7 + 1);
    } while (cVar1 != '\0');
    goto LAB_ScriptNextInstruction;
  case 0x1f56:
    puVar8 = &fxps->operationType;
    *bytesPtr = &fxps[1].f1;
    in_ECX = (vec3 *)((int)entity + (0x25c - (int)puVar8));
    do {
      fxCustom_type = *puVar8;
      *(char *)((int)puVar8 + (int)in_ECX) = (char)fxCustom_type;
      puVar8 = (uint *)((int)puVar8 + 1);
    } while ((char)fxCustom_type != '\0');
    goto LAB_ScriptNextInstruction;
  case 0x1f57:
    *bytesPtr = &fxps->deg1;
    if (fxps->operationType == 0) {
      entity->fxCustomType = 1;
    }
    else if (fxps->operationType == 1) {
      entity->fxCustomType = 2;
    }
    in_ECX = (vec3 *)fxps->f1;
    fxp_f6 = fxps->f2;
    entity->f1 = (float)in_ECX;
    entity->f2 = fxp_f6;
    entity->f3 = fxps->f3;
    goto LAB_ScriptNextInstruction;
  case 0x1f58:
                    // Init fx custom
    *bytesPtr = fxps + 1;
    operationType = fxps->operationType;
    if (operationType == 0) {
      fxCustomType = 3;
    }
    else if (operationType == 1) {
      fxCustomType = 4;
    }
    else if (operationType == 2) {
      fxCustomType = 5;
    }
    fxp_f6 = fxps->f2;
    entity->f1 = fxps->f1;
    entity->f2 = fxp_f6;
    entity->f3 = fxps->f3;
    fxCustom_type = 2;
    if (*(int *)&fxps->field_0x78 == 0) {
      fxCustom_type = fxCustomType;
    }
    fxp_f6 = fxps->deg6;
    fxp_f5 = fxps->deg5;
    fxp_f4 = fxps->deg4;
    fxp_f3 = fxps->deg3;
    fxp_f2 = fxps->deg2;
    fxp_f1 = fxps->deg1;
    entity->fxCustomType = fxCustom_type;
    entity->rad1 = fxp_f1 * 0.017453292;
    entity->rad4 = fxp_f2 * 0.017453292;
    entity->rad2 = fxp_f3 * 0.017453292;
    entity->rad5 = fxp_f4 * 0.017453292;
    entity->rad3 = fxp_f5 * 0.017453292;
    entity->rad6 = fxp_f6 * 0.017453292;
    fxParticleImpactFlash::UpdateScriptVecs
              (entity,&fxps->v3,&fxps->v2,*(uint *)&fxps->field_0x4c,&fxps->v1,fxps->someFlag);
    if (fxps->doUpdatesOnAngleInit_ == 0) {
      (entity->eulerRot_).x = (fxps->eulerRot_).x;
      (entity->eulerRot_).y = (fxps->eulerRot_).y;
      (entity->eulerRot_).z = (fxps->eulerRot_).z;
    }
    else {
      (entity->eulerRot_).x = (fxps->eulerRot_).x + (entity->updatedAngles).x;
      (entity->eulerRot_).y = (fxps->eulerRot_).y + (entity->updatedAngles).y;
      (entity->eulerRot_).z = (fxps->eulerRot_).z + (entity->updatedAngles).z;
    }
    in_ECX = (vec3 *)(fxps->pos_).x;
    (entity->pos_).x = (float)in_ECX;
    (entity->pos_).y = (fxps->pos_).y;
    (entity->pos_).z = (fxps->pos_).z;
    goto LAB_ScriptNextInstruction;
  case 0x1f59:
    *bytesPtr = &fxps->f3;
    if ((((float)fxps->operationType == 0.0) && (fxps->f1 == 0.0)) && (fxps->f2 == 0.0)) {
      *(byte *)&entity->flags = (byte)entity->flags & 0xef;
    }
    else {
      *(uint *)&entity->field_0x74 = fxps->operationType;
      in_ECX = (vec3 *)fxps->f1;
      *(vec3 **)&entity->field_0x78 = in_ECX;
      *(float *)&entity->field_0x7c = fxps->f2;
      *(byte *)&entity->flags = (byte)entity->flags | 0x10;
    }
    goto LAB_ScriptNextInstruction;
  case 0x1f5a:
    *bytesPtr = &fxps[1].f1;
    if (fxps->operationType == 0x5f646961) {
      FUN_000ed8c0(&fxps->operationType);
      in_ECX = extraout_ECX_03;
    }
    goto LAB_ScriptNextInstruction;
  case 0x1f5b:
    goto switchD_000eda13_caseD_1f5b;
  default:
    if ((7999 < *(int *)((int)*bytesPtr + 4)) && (*(int *)((int)*bytesPtr + 4) < 0x1f5d)) {
      return 0;
    }
    return 1;
  }
  (entity->scriptV1).y = 0.0;
  (entity->scriptV1).z = 0.0;
  goto LAB_ScriptNextInstruction;
switchD_000eda13_caseD_1f5b:
  *bytesPtr = &fxps->f2;
  in_ECX = (vec3 *)fxps->operationType;
  entity->field117_0x98 = (float)in_ECX;
  *(float *)&entity->field_0x9c = fxps->f1;
  goto LAB_ScriptNextInstruction;
}



// WARNING: Globals starting with '_' overlap smaller symbols at the same address


void EventLoop::UpdateSceneValues(int param_1)

{
  if (((*SomeAS15->flags & 2) != 0) &&
     (Game::Save.timeSeconds = Game::Save.timeSeconds + (int)Game::TimeInCurrentLevel, param_1 == 0)
     ) {
    Game::Save.numKills = Game::Save.numKills + Game::KillsInCurrentLevel;
    Game::Save.numPrisoners = Game::Save.numPrisoners + Game::PrisonersSavedInCurrentLevel;
  }
  return;
}




void Events::ExecuteGhoulieIntroLoctext(void)

{
  actorMind *paVar1;
  actor *paVar2;
  int iVar3;
  uint index;
  undefined4 uVar4;
  float fVar5;
  float fVar6;
  vec2 local_8;
  
  if (Game::InGhoulyIntro == 1) {
    EventLoop::ExecuteGhoulieIntro();
  }
  else {
    uVar4 = 0;
    if (Game::InGhoulyIntro == 2) {
      if (runtime::dx_timer <= 0.0) {
        fVar5 = runtime::DeltaTime * runtime::TimeScale;
      }
      else {
        fVar5 = 0.0;
      }
      if ((0.0 < DAT_00506e34) && (DAT_00506e34 = DAT_00506e34 - fVar5, DAT_00506e34 <= 0.0)) {
        DAT_00506e34 = 0.0;
        FUN_000f4da0(u__00507e78);
        iVar3 = Font::MeasureParagraphSize(1.5,-1.0,&local_8,(LPWSTR)u__00507e78,0,uVar4);
        fVar5 = (float)(int)(runtime::GloopyFontResource.gloopy)->lineHeight * 1.5;
        CreateLoctext(DAT_00506e3c,u__00507e78,(float)Graphics::BackbufferWidth * 0.5,
                      ((float)Graphics::BackbufferHeight - fVar5) * 0.85 -
                      (float)(iVar3 + -1) * fVar5,1.5,1.5,5.5,1,0,0);
      }
      fVar5 = 0.0;
      paVar1 = Game::ActorPerformingIntro->mind;
      if (paVar1 != (actorMind *)0x0) {
        *(undefined4 *)&paVar1->field_0x3c = 1;
        (paVar1->v3).x = g_someProjectionSet.pos.x;
        (paVar1->v3).y = g_someProjectionSet.pos.y;
        (paVar1->v3).z = g_someProjectionSet.pos.z;
      }
      paVar2 = Game::ActorPerformingIntro;
      if (runtime::dx_timer <= 0.0) {
        fVar6 = runtime::DeltaTime * runtime::TimeScale;
      }
      else {
        fVar6 = 0.0;
      }
      if (((0.0 < DAT_00506e30) && (DAT_00506e30 = DAT_00506e30 - fVar6, DAT_00506e30 <= 0.0)) &&
         (DAT_00506e30 = 0.0, -1 < (int)DAT_00506e2c)) {
        if ((int)DAT_00506e2c < 3) {
          index = DAT_00506e2c + 1;
          DAT_00506e2c = index;
          FUN_000f4df0();
          RunGhoulieIntro(&g_someProjectionSet,&GlobalFloatStruct_0030c748,&paVar2->avatar,fVar5,
                          index);
          DAT_00506e30 = 0.9;
        }
        else if (DAT_00506e2c == 3) {
          FUN_000f4b90();
        }
      }
    }
  }
  if (DAT_00506e44 == 1) {
    if (runtime::dx_timer <= 0.0) {
      fVar5 = runtime::DeltaTime * runtime::TimeScale;
    }
    else {
      fVar5 = 0.0;
    }
    if ((0.0 < DAT_00506e4c) && (DAT_00506e4c = DAT_00506e4c - fVar5, DAT_00506e4c <= 0.0)) {
      DAT_00506e4c = 0.0;
      FUN_000f4da0(u__00507e78);
      runtime::AllocateForLoctext_(0,1,(void *)0xe0,&DAT_00506e54);
      CreateLoctext(DAT_00506e54,u__00507e78,(float)Graphics::BackbufferWidth * 0.5,
                    ((float)Graphics::BackbufferHeight -
                    (float)(int)(runtime::GloopyFontResource.gloopy)->lineHeight * 1.5) * 0.85,1.5,
                    1.5,DAT_00506e50,1,0,0);
      DAT_00506e44 = 2;
    }
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void EventLoop::ExecuteGhoulieIntro(void)

{
  actor *paVar1;
  int iVar2;
  uint uVar3;
  float uVar4;
  Actor_SetDroneActionMessage local_24;
  
  if (((((g_globalFlagset & 0x4000) == 0) && (ShouldntDroneBools[1] == 0)) &&
      ("\x01"[Game::CheckMoveOn] != '\0')) && ((g_globalFlagset & Flag1) == 0)) {
    g_globalFlagset = g_globalFlagset | HealthAltered?;
    Game::InGhoulyIntro = 2;
    local_24.msgId = Actor_SetDroneAction;
    local_24.droneAction = Intro;
    local_24.someShort = 0;
    (*((Game::ActorPerformingIntro->avatar).vtable)->onMessage)
              (Game::ActorPerformingIntro,&local_24);
    Events::UpdateActionBeginEnds(0xff,0);
    paVar1 = Game::ActorPerformingIntro;
    iVar2 = FUN_000f4d40();
    if (iVar2 == 0) {
      uVar4 = 0.85;
    }
    else {
      uVar4 = *(float *)(iVar2 + 0x40);
    }
    RunGhoulieIntro(&g_someProjectionSet,&GlobalFloatStruct_0030c748,&paVar1->avatar,uVar4,0);
    DAT_00506e30 = 0.9;
    DAT_00506e2c = 0;
    DAT_00506e34 = 0.5;
    runtime::AllocateForLoctext_(0,1,(void *)0xe0,(LoctextValueContext **)&DAT_00506e3c);
    iVar2 = DAT_00506e3c;
    uVar3 = runtime::rand * 0x19660d + 0x3c6ef35f;
    runtime::rand = uVar3;
    *(undefined4 *)(DAT_00506e3c + 0x14) = 0x402ccccd;
    *(uint *)(iVar2 + 0x1c) = uVar3;
    *(float *)(iVar2 + 0x18) = 0.6;
    Audio::PlayOrChangeByName(0x12,"XACT_SOUNDBANK_GSTREAMSDITTIES_GHOULINTRODITTY");
    Game::NotAllowedToPause = Game::NotAllowedToPause + 1;
    GlobalCounter2 = GlobalCounter2 + 1;
    DAT_00506e38 = 1;
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


uint Events::GetIndexOfStringInTable(int tableSize,char **nameTable,char *tagName)

{
  int iVar1;
  byte *pbVar2;
  byte bVar3;
  byte bVar4;
  int max_index;
  uint uVar5;
  int iVar6;
  
  max_index = tableSize + -1;
  iVar1 = 0;
  if (-1 < max_index) {
    do {
      uVar5 = iVar1 + max_index >> 1;
      pbVar2 = (byte *)nameTable[uVar5];
      bVar3 = *pbVar2;
      bVar4 = *tagName;
      if (bVar3 == *tagName) {
        iVar6 = (int)tagName - (int)pbVar2;
        do {
          pbVar2 = pbVar2 + 1;
          if (bVar3 == 0) {
            return uVar5;
          }
          bVar3 = *pbVar2;
          bVar4 = pbVar2[iVar6];
        } while (bVar3 == bVar4);
      }
      iVar6 = (uint)bVar3 - (uint)bVar4;
      if (iVar6 < 0) {
        iVar1 = uVar5 + 1;
      }
      else {
        if ((uint)bVar3 == (uint)bVar4 || iVar6 < 0) {
          return uVar5;
        }
        max_index = uVar5 - 1;
      }
    } while (iVar1 <= max_index);
  }
  return 0xffffffff;
}




void FUN_000fffd0(vec3 *param_1,int *param_2,Marker *param_3)

{
  uint uVar1;
  vec3 *v;
  Marker *pMVar2;
  Marker *pMVar3;
  undefined4 local_24;
  uint local_20;
  float local_1c;
  float local_18;
  float local_14;
  float local_10;
  float local_c;
  float local_8;
  uint local_4;
  
  local_4 = 0;
  local_24 = 0x4d;
  pMVar3 = param_3;
  if (param_3->runtimeId == 0) {
    local_1c = v->x;
    local_18 = v->y;
    local_14 = v->z;
    local_20 = (uint)*(ushort *)((int)&param_3[1].size + 2);
    local_10 = param_1->x;
    local_c = param_1->y;
    local_8 = param_1->z;
    (**(code **)(*param_2 + 0xc))(param_2,&local_24);
    return;
  }
  do {
    pMVar2 = (Game::GameState.markerInstance)->marker;
    uVar1 = 0;
    if ((Game::GameState.markerInstance)->numMarkers != 0) {
      do {
        if (pMVar2->id == pMVar3->runtimeId) goto LAB_00100036;
        uVar1 = uVar1 + 1;
        pMVar2 = (Marker *)((int)&pMVar2->size + pMVar2->size);
      } while (uVar1 < (Game::GameState.markerInstance)->numMarkers);
    }
    pMVar2 = (Marker *)0x0;
LAB_00100036:
    local_1c = (pMVar2->pos).x;
    local_20 = (uint)*(ushort *)((int)&param_3[1].size + 2);
    local_18 = (pMVar2->pos).y;
    local_14 = (pMVar2->pos).z;
    local_10 = (pMVar2->eulerRot).x;
    local_c = (pMVar2->eulerRot).y;
    local_8 = (pMVar2->eulerRot).z;
    local_4 = (uint)(pMVar2->runtimeId != 0);
    (**(code **)(*param_2 + 0xc))(param_2,&local_24);
    pMVar3 = pMVar2;
    if (pMVar2->runtimeId == 0) {
      return;
    }
  } while( true );
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void Events::UpdatePerSecondTimers(void)

{
  SomeUpdatedStruct *pSVar1;
  float delta;
  
  if (runtime::dx_timer <= 0.0) {
    delta = runtime::DeltaTime * runtime::TimeScale;
  }
  else {
    delta = 0.0;
  }
  Game::SecondTimer = Game::SecondTimer - delta;
  if (Game::SecondTimer <= 0.0) {
    Game::SecondTimer = Game::SecondTimer + 1.0;
    pSVar1 = Game::UpdatedEachSeconds;
    do {
      if (pSVar1->enabled != 0) {
        FUN_00112b40(pSVar1);
      }
      pSVar1 = pSVar1 + 1;
    } while (pSVar1 < &currentBg);
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void EventLoop::ClearTextureListsAndSwizzle(void)

{
  undefined4 uVar1;
  void *pSource;
  undefined1 *puVar2;
  undefined1 uVar3;
  int iVar4;
  HeapTableEntry *pHVar5;
  int i;
  float fVar6;
  float fVar7;
  DWORD local_8;
  LPVOID local_4;
  
  g_bufferTextureMaybeSomething = malloc_(0x18);
  g_bufferTextureMaybeSomething->head = (undefined2 *)g_bufferTextureMaybeSomething->values;
  g_bufferTextureMaybeSomething->tail = (undefined2 *)g_bufferTextureMaybeSomething->values;
  g_bufferTextureMaybeSomething->valueSize = 4;
  g_bufferTextureMaybeSomething->capacity = 2;
  g_bufferTextureMaybeSomething->end = g_bufferTextureMaybeSomething + 1;
  g_bufferSome0x40 = malloc_(0x90);
  g_bufferSome0x40->head = g_bufferSome0x40->values;
  g_bufferSome0x40->tail = g_bufferSome0x40->values;
  g_bufferSome0x40->valueSize = 0x40;
  g_bufferSome0x40->capacity = 2;
  g_bufferSome0x40->end = (Some0x40 *)(g_bufferSome0x40 + 1);
  g_bufferNewTextureMaybe = malloc_(0x68);
  g_bufferNewTextureMaybe->head = g_bufferNewTextureMaybe->values;
  g_bufferNewTextureMaybe->tail = g_bufferNewTextureMaybe->values;
  g_bufferNewTextureMaybe->valueSize = 0x2c;
  g_bufferNewTextureMaybe->capacity = 2;
  g_bufferNewTextureMaybe->end = (NewTextureMaybe *)(g_bufferNewTextureMaybe + 1);
  g_someTexture = D3D8::D3DDevice_CreateTexture2(0x100,1,1,1,0,D3DFMT_A8R8G8B8,D3DRTYPE_TEXTURE);
  D3D8::D3DTexture_LockRect(g_someTexture,0,&local_8,0,0);
  pSource = malloc_(0x400);
  i = 0;
  puVar2 = (undefined1 *)((int)pSource + 2);
  do {
    fVar6 = (float)i;
    if (25.6 <= fVar6) {
      if (51.2 <= fVar6) {
        if (76.8 <= fVar6) {
          if (102.4 <= fVar6) {
            if (179.2 <= fVar6) {
              if (204.8 <= fVar6) {
                fVar7 = 0.75;
                if (230.4 <= fVar6) {
                  fVar7 = 0.85;
                }
              }
              else {
                fVar7 = 0.7;
              }
            }
            else {
              fVar7 = 0.65;
            }
          }
          else {
            fVar7 = 0.6;
          }
        }
        else {
          fVar7 = 0.5;
        }
      }
      else {
        fVar7 = 0.35;
      }
    }
    else {
      fVar7 = 0.3;
    }
    iVar4 = (int)(fVar7 * 256.0);
    if (iVar4 < 0) {
      iVar4 = 0;
    }
    else if (0xff < iVar4) {
      iVar4 = 0xff;
    }
    uVar3 = (undefined1)iVar4;
    puVar2[-2] = uVar3;
    puVar2[-1] = uVar3;
    *puVar2 = uVar3;
    puVar2[1] = 0xff;
    i = i + 1;
    puVar2 = puVar2 + 4;
  } while (i < 0x100);
  XGRAPHC::XGSwizzleRect(pSource,local_8,(LPCRECT)0x0,local_4,0x100,1,(LPPOINT)0x0,4);
  i = FindHeapOf(pSource);
  uVar1 = runtime::CurrentHeapToAllocateFrom;
  if (g_HeapTableBase[i].heapHandle == (HANDLE)0x0) {
    pHVar5 = (HeapTableEntry *)0x0;
  }
  else {
    pHVar5 = g_HeapTableBase + i;
  }
  runtime::CurrentHeapToAllocateFrom = i;
  XAPILIB::HeapFree(pHVar5->heapHandle,0,pSource);
  runtime::CurrentHeapToAllocateFrom = uVar1;
  g_someTexture2 = g_someTexture;
  return;
}




void Events::UpdateTextureMaybeSomethings(float param_1)

{
  int *piVar1;
  int iVar2;
  undefined2 uVar3;
  BOOL BVar4;
  int *piVar5;
  float10 fVar6;
  float local_c;
  float local_8;
  float local_4;
  
  if (g_bufferTextureMaybeSomething != (Buffer<> *)0x0) {
    piVar5 = (int *)g_bufferTextureMaybeSomething->head;
    piVar1 = (int *)g_bufferTextureMaybeSomething->tail;
    if (((int)piVar1 - (int)piVar5) / (int)(uint)g_bufferTextureMaybeSomething->valueSize != 0) {
      for (; piVar5 < piVar1; piVar5 = piVar5 + 1) {
        iVar2 = *piVar5;
        if ((*(int *)(iVar2 + 0x1dc) != 0) ||
           (BVar4 = Graphics::AABBvsFrustum
                              ((GraphicsCamera *)&Graphics::CurrentCameraStruct->field_0x138,
                               (vec3 *)(iVar2 + 0x48),(vec3 *)(iVar2 + 0x54),
                               &Graphics::CurrentCameraStruct->field_0x1e0), BVar4 != 0)) {
          FUN_0004c000((TextureMaybeSomething *)*piVar5);
          if (((CurtainAlloc *)*piVar5)->field389_0x1e6 != '\0') {
            FUN_0004c0e0((CurtainAlloc *)*piVar5);
            iVar2 = *piVar5;
            if (*(char *)(iVar2 + 0x1ea) != '\0') {
              if (0.0 < *(float *)(iVar2 + 0x154)) {
                *(float *)(iVar2 + 0x154) = *(float *)(iVar2 + 0x154) - param_1;
              }
              else {
                fVar6 = (float10)FUN_0004c1b0();
                if ((float10)1.0 < fVar6) {
                  *(undefined4 *)(iVar2 + 0x154) = 0x40a00000;
                  iVar2 = *piVar5;
                  local_c = (*(float *)(iVar2 + 0x54) + *(float *)(iVar2 + 0x48)) * 0.5;
                  local_8 = (*(float *)(iVar2 + 0x58) + *(float *)(iVar2 + 0x4c)) * 0.5;
                  local_4 = (*(float *)(iVar2 + 0x5c) + *(float *)(iVar2 + 0x50)) * 0.5;
                  uVar3 = FUN_00039580(iVar2 + 0x15a,1,&local_c);
                  *(undefined2 *)(*piVar5 + 0x158) = uVar3;
                }
              }
            }
          }
        }
      }
      FUN_001137e0();
    }
  }
  return;
}




void Events::EmptySceneList(void)

{
  EmbeddedNode<> *pEVar1;
  
  while (pEVar1 = Game::NewlyAddedSceneControls.next,
        Game::NewlyAddedSceneControls.next != (EmbeddedNode<> *)0x0) {
    if ((Game::NewlyAddedSceneControls.next)->prev != (sceneControlObj_0x8)0x0) {
      *(sceneControlObj_0x8 *)((Game::NewlyAddedSceneControls.next)->prev + 4) =
           (Game::NewlyAddedSceneControls.next)->next;
    }
    if (pEVar1->next != (sceneControlObj_0x8)0x0) {
      *(sceneControlObj_0x8 *)pEVar1->next = pEVar1->prev;
    }
    pEVar1->prev = (sceneControlObj_0x8)0x0;
    pEVar1->next = (sceneControlObj_0x8)0x0;
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void EventLoop::NewMessage(MessageHeader *param_1)

{
  int hasMessage;
  astruct_60 *puVar2;
  undefined *puVar1;
  void **ppvVar2;
  
  hasMessage = ProcessNewMessage((Message *)param_1);
  if (hasMessage != 0) {
    puVar2 = malloc_(0x214);
    puVar2->field0_0x0 = (undefined *)0x0;
    puVar2->field1_0x4 = 0;
    puVar1 = &DAT_0050e4d8;
    if (g_scriptRelatedLinkedList_ != (void *)0x0) {
      ppvVar2 = &g_scriptRelatedLinkedList_;
      do {
        puVar1 = *ppvVar2;
        ppvVar2 = (void **)(puVar1 + 4);
      } while (*(int *)(puVar1 + 4) != 0);
    }
    *(astruct_60 **)(puVar1 + 4) = puVar2;
    puVar2->field0_0x0 = puVar1;
    puVar2->field1_0x4 = 0;
    memcpy(&puVar2->field2_0x8,param_1,MessageEntry_ARRAY_0030dc20[param_1->msgId].length);
    puVar2->msgTime = g_timeSpentInCurrentLevel;
  }
  return;
}




bool EventLoop::ProcessNewMessage(Message *param_1)

{
  short sVar1;
  undefined2 markerId;
  BOOL BVar2;
  int *piVar3;
  actor *av;
  int iVar4;
  EVP_PKEY_CTX *unaff_EDI;
  vec3 *pvVar5;
  undefined4 local_3c;
  vec3 local_38;
  vec3 local_2c;
  vec3 local_1c;
  vec3 vStack_10;
  int local_4;
  
  switch((param_1->header).msgId) {
  case Actor_Dying:
    FUN_0012acf0();
    BVar2 = FUN_00028d20((WeaponProjectilesContext *)(param_1->header).someActor);
    if (BVar2 != 0) {
      Scripting::numScriptConditions = Scripting::numScriptConditions + 1;
      return false;
    }
    break;
  case Scene_ActorDiedInGhoulyBox:
    FUN_0012acf0();
    break;
  case Scene_ActorHit:
    FUN_00116c10(param_1[3].header.msgId);
    return false;
  case Scene_ActorHitInvulnerable:
    FUN_0012acf0();
    FUN_0012acf0();
    return false;
  case Scene_Begin:
  case Scene_EventBegin:
  case Player_PickedUpObject:
  case Player_FoundTheKey:
  case Director_HauntedObjectActivated:
  case Director_KeyCarrierDied:
  case Director_GhoulyTriggered:
  case Director_PlayerTriggeredScare:
  case Director_GhoulySignal:
    return true;
  case Scene_End:
    Scene::cleanup(unaff_EDI);
    return false;
  case Scene_EventEnd:
    if ((param_1->header).someActor != (actor *)0x0) {
      Game::MoveOn = Game::MoveOn + 1;
    }
    Scene::cleanup(unaff_EDI);
    return false;
  case Player_NextSceneTrigger:
  case Player_GameMovesOn:
                    // Used in relic after scare
    Game::MoveOn = Game::MoveOn + 1;
    return false;
  case Player_HitExitBox:
    sVar1 = *(short *)&(param_1->header).someActor;
    if (sVar1 != 0) {
      pvVar5 = &local_38;
      for (iVar4 = 0xe; iVar4 != 0; iVar4 = iVar4 + -1) {
        pvVar5->x = 0.0;
        pvVar5 = (vec3 *)&pvVar5->y;
      }
                    // GhoulyGetDroneToPosition
      local_3c = 0xa6;
      piVar3 = (int *)Game::OnSceneBegin(sVar1);
      if (piVar3 != (int *)0x0) {
        av = getThePlayer();
        if (av != (actor *)0x0) {
          avatar::getWorldPosition(&av->avatar,&local_38);
          avatar::getWorldRotation(&av->avatar,&local_2c);
        }
        (**(code **)(*piVar3 + 0xc))(piVar3,&local_3c);
      }
      if (local_4 == 0) {
        markerId = *(undefined2 *)&(param_1->header).someActor;
        Marker::GetPosByIndex(markerId,&local_1c);
        Marker::getEulersByIndex(markerId,&vStack_10);
      }
      SetPlayerExitedBox(&vStack_10,&local_1c);
    }
    CheckLevelExits = 1;
    return false;
  case Director_PlayerDeflectionContact:
    iVar4 = FUN_00116890();
    return iVar4 == 0;
  }
  return false;
}




void __fastcall Events::LoadSceneScriptFromAID(GameState *param_1,char *sceneSuffix)

{
  int iVar4;
  BOOL BVar1;
  ScriptResource *in_stack_ffffff7c;
  char script_name [128];
  char cVar2;
  int iVar1;
  ScriptEntry *pAVar3;
  
  iVar4 = 5;
  cVar2 = param_1->currentSceneScript[5];
  while (cVar2 != '_') {
    iVar1 = iVar4 + 1;
    iVar4 = iVar4 + 1;
    cVar2 = param_1->currentSceneScript[iVar1];
  }
  Utils::SprintfToUpper
            (script_name,"aid_%s_%s","script",param_1->currentSceneScript + iVar4 + 1,sceneSuffix,
             (char *)in_stack_ffffff7c);
  ::Scripting::RunSetupScriptFromScriptAID(script_name);
  if (script_name._0_4_ == 0x5f646961) {
    Assets::GetResourceBytes(script_name,(void **)&stack0xffffff7c);
    if (in_stack_ffffff7c == (ScriptResource *)0x0) {
      runtime::ExitGame(2);
    }
  }
  else {
    in_stack_ffffff7c = (ScriptResource *)0x0;
  }
  ::Scripting::LoadedResource = in_stack_ffffff7c;
                    // Load the new script (playcam script)
  if (in_stack_ffffff7c != (ScriptResource *)0x0) {
    if (Scripts->tail == Scripts->end) {
      Scripts = (Buffer<> *)runtime::ExtendArray((Buffer *)Scripts);
    }
    pAVar3 = Scripts->tail;
    Scripts->tail = (ScriptEntry *)((int)&pAVar3->currentOp + (uint)Scripts->valueSize);
    pAVar3->currentOp = in_stack_ffffff7c;
    pAVar3->resource = in_stack_ffffff7c;
                    // Then execute it to set up the level
    BVar1 = ::Scripting::RunScripts();
    if (BVar1 != 0) {
      Assets::DestroyAssetOrDecrement(::Scripting::LoadedResource);
      ::Scripting::LoadedResource = (ScriptResource *)0x0;
    }
  }
  if ((*SomeAS15->flags & 8) == 0) {
    if (g_finishedLoading_ != 1) {
      FUN_000f2c40();
      return;
    }
    FUN_000f2d10();
    return;
  }
  Game::MaybeSaveGame();
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void InvertChallengeStatusGraphics(void)

{
  DrainChallengeList();
  g_globalFlagset = g_globalFlagset & ~NotInAChallenge?;
  EventLoop::UpdateSceneValues(g_finishedLoading_ == 1);
  FUN_00049ff0();
  if (((*SomeAS15->flags & 8) != 0) || ((g_globalFlagset & 0x200000) != 0)) {
    FLOAT_004e1744 = Game::TimeInCurrentLevel + FLOAT_004e1744;
  }
  if (g_weapons != (Buffer<weapon> *)0x0) {
    free(g_weapons);
    g_weapons = (Buffer<weapon> *)0x0;
  }
  FUN_001289a0();
  if (Scripting::ScriptConditions != (Buffer<> *)0x0) {
    free(Scripting::ScriptConditions);
    Scripting::ScriptConditions = (Buffer<> *)0x0;
  }
  FUN_00116790();
  if (DAT_0050e560 != 0) {
    DAT_0050e560 = 0;
  }
  FUN_0012df90();
  if (Scripting::LoadedResource != (ScriptResource *)0x0) {
    Assets::DestroyAssetOrDecrement(Scripting::LoadedResource);
    Scripting::LoadedResource = (ScriptResource *)0x0;
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void Events::UpdateActionBeginEnds(byte param_1,int param_2)

{
  int iVar1;
  int i;
  MessageHeader msg;
  actor_conflict5 *act;
  actor_0x934_conflict5 actor0x934;
  actor_0x934_conflict5 next;
  
  msg.someActor = (actor *)0x0;
  if (param_2 == 0) {
    if (((param_1 & 1) != 0) &&
       (ShouldntDroneBools[0] = ShouldntDroneBools[0] + 1,
       (actor *)ShouldntDroneBools[0] == (actor *)0x1)) {
      msg.someActor = (actor *)ShouldntDroneBools[0];
    }
    if ((param_1 & 2) != 0) {
      ShouldntDroneBools[1] = ShouldntDroneBools[1] + 1;
    }
  }
  else {
    if (((param_1 & 1) != 0) &&
       (ShouldntDroneBools[0] = ShouldntDroneBools[0] + -1, ShouldntDroneBools[0] == 0)) {
      msg.someActor = (actor *)0x1;
    }
    if ((param_1 & 2) != 0) {
      ShouldntDroneBools[1] = ShouldntDroneBools[1] + -1;
    }
  }
  i = 0;
  do {
    if ((&msg.someActor)[i] != (actor *)0x0) {
      if (param_2 == 0) {
        msg.msgId = Actor_ActionEnd;
        actor0x934 = Game::SceneInfo.actors_0x934.head;
        while (actor0x934 != (actor_0x934_conflict5)0x0) {
          act = ADJ(actor0x934);
          next = actor0x934->next;
          if ((ADJ(actor0x934)->actorType == Human) ||
             ((ADJ(actor0x934)->node0x93c).prev != (actor_0x93c_conflict5)0x0)) {
            iVar1 = 1;
          }
          else {
            iVar1 = 0;
          }
          actor0x934 = next;
          if (iVar1 == i) {
            (*((act->avatar).object.vtable)->onMessage)(act,&msg);
          }
        }
      }
      else {
        msg.msgId = Actor_ActionBegin;
        actor0x934 = Game::SceneInfo.actors_0x934.head;
        while (actor0x934 != (actor_0x934_conflict5)0x0) {
          act = ADJ(actor0x934);
          next = actor0x934->next;
          if ((ADJ(actor0x934)->actorType == Human) ||
             ((ADJ(actor0x934)->node0x93c).prev != (actor_0x93c_conflict5)0x0)) {
            iVar1 = 1;
          }
          else {
            iVar1 = 0;
          }
          actor0x934 = next;
          if (iVar1 == i) {
            (*((act->avatar).object.vtable)->onMessage)(act,&msg);
          }
        }
      }
    }
    i = i + 1;
  } while (i < 2);
  return;
}




void __fastcall Events::UpdateAmbientAudio(undefined4 param_1)

{
  float10 extraout_ST0;
  float10 fVar1;
  float fVar2;
  
  FUN_00117a50(param_1);
  FUN_00118120();
  FUN_00118380();
  if ((DAT_0050e944 != 0) && (DAT_0050e94c = DAT_0050e94c + -1, DAT_0050e94c < 1)) {
    runtime::rand = runtime::rand * 0x19660d + 0x3c6ef35f;
    DAT_0050e948 = ((float)(runtime::rand & 0x7fffff | 0x3f800000) - 1.0) * 0.3 + 0.7;
    DAT_0050e94c = 2;
  }
  if ((DAT_0050e950 != 0) && (DAT_0050e954 != 0)) {
    if (runtime::dx_timer <= 0.0) {
      fVar2 = runtime::DeltaTime * runtime::TimeScale;
    }
    else {
      fVar2 = 0.0;
    }
    DAT_0050e968 = DAT_0050e968 + fVar2;
    if ((DAT_0050e96c < DAT_0050e968) &&
       (DAT_0050e968 = DAT_0050e968 - DAT_0050e96c, DAT_0050e97c != '\0')) {
      FUN_00039480(0x3f800000);
    }
    if (DAT_0050e96c == 0.0) {
      fVar2 = 3.1415927;
    }
    else {
      fVar2 = (DAT_0050e968 / DAT_0050e96c) * 3.1415927;
      if (fVar2 <= 3.1415927) {
        if (fVar2 < 0.0) {
          fVar2 = 0.0;
        }
      }
      else {
        fVar2 = 3.1415927;
      }
    }
    sin(fVar2);
    fVar1 = abs_float((float)extraout_ST0);
    DAT_0050e964 = (float)(((float10)_DAT_0050e974 - (float10)_DAT_0050e970) * fVar1 +
                          (float10)_DAT_0050e970);
  }
  if ((DAT_0050e944 == 0) && (DAT_0050e950 == 0)) {
    if (((DAT_0050e7a4 != 0) || (g_stateStack != 0)) ||
       (Graphics::SetShaderConstant.c3 = DAT_0050e7b8, DAT_0050e930 < 1)) {
      Graphics::SetShaderConstant.c3 = 0.0;
    }
  }
  else {
    Graphics::SetShaderConstant.c3 = DAT_0050e964 + DAT_0050e948;
  }
  Graphics::SetShaderConstant.c4 = 1.0;
  Graphics::SetShaderConstant.c2 = Graphics::SetShaderConstant.c3;
  Graphics::SetShaderConstant.c1 = Graphics::SetShaderConstant.c3;
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void Events::UpdateGhoulyBoxes(void)

{
  int iVar1;
  GhoulyBox *pGVar2;
  int iVar3;
  GhoulyBox *as7;
  BOOL BVar4;
  float delta;
  vec3 local_c;
  
  if (((undefined1)g_globalFlagset & 0x40) == 0) {
    if (runtime::dx_timer <= 0.0) {
      delta = runtime::DeltaTime * runtime::TimeScale;
    }
    else {
      delta = 0.0;
    }
    if ((Game::SceneInfo.playerActors.prev == (actor_0x93c_conflict5)0x0) ||
       (ADJ(Game::SceneInfo.playerActors.prev) == (actor_conflict5 *)0x0)) {
      local_c.z = 0.0;
      local_c.y = 0.0;
      local_c.x = 0.0;
      iVar3 = DAT_00510574;
    }
    else {
      avatar::getWorldPosition((avatar *)ADJ(Game::SceneInfo.playerActors.prev),&local_c);
      iVar3 = DAT_00510574;
    }
    while (pGVar2 = g_ghoulyBoxes.next, iVar3 != 0) {
      iVar1 = *(int *)(iVar3 + 4);
      BVar4 = FUN_000f4f80(&local_c,delta,iVar3);
      iVar3 = iVar1;
      if (BVar4 != 0) {
                    // If ghouly box was opened, destroy the box?
        FUN_000f4ee0();
      }
    }
    while (as7 = pGVar2, as7 != (GhoulyBox *)0x0) {
      pGVar2 = as7->next;
      BVar4 = FUN_000f3cf0(delta,as7);
      if ((BVar4 != 0) && (as7->head != (GhoulyBoxLLHead *)0x0)) {
        as7->head->next = as7->next;
        if (as7->next != (GhoulyBox *)0x0) {
          as7->next->head = as7->head;
        }
        as7->head = (GhoulyBoxLLHead *)0x0;
        as7->next = (GhoulyBox *)0x0;
      }
    }
  }
  return;
}




void EventLoop::RunPostLoadSetupScripts(GameState *param_1)

{
  Events::LoadSceneScriptFromAID(&Game::GameState,param_1->currentSceneScript);
  Events::BeginScene();
  Events::UpdateGhoulyBoxes();
  Scripting::updateLevelScript();
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void Events::BeginScene(void)

{
  Model *pMVar1;
  undefined4 *puVar2;
  undefined4 unaff_ESI;
  ObjMsgID local_4;
  ModelDescriptor *model_descriptor;
  
  ClearIDKBigStruct();
  Assets::LoadNewMarker(Game::GameState.currentSceneScript,unaff_ESI);
  Game::SecondTimer = 1.0;
  SomeAudioStruct_00512520.field0_0x0 = 0x14;
  SomeAudioStruct_00512534.field0_0x0 = 6;
  FUN_000ec2d0();
  game::load_cheap_dust_fx();
  game::doors = malloc_(0x560);
  game::doors->head = game::doors->values;
  game::doors->tail = game::doors->values;
  game::doors->valueSize = 0x154;
  game::doors->capacity = 4;
  game::doors->end = (Draw2D *)(game::doors + 1);
  DAT_004ee320 = 0;
  _DAT_004ee324 = 0;
  _DAT_004ee328 = 0;
  EventLoop::ClearTextureListsAndSwizzle();
  if (::Scripting::BackgroundAID._0_4_ == 0x5f646961) {
    Assets::CreateBackgroundFromAID(::Scripting::BackgroundAID);
  }
  ::Scripting::BackgroundAID._0_4_ = ::Scripting::BackgroundAID._0_4_ & 0xffffff00;
  avatar::processNew();
  FUN_00111820();
  NormaliseGraphicsCamera_();
  FUN_00123560();
  FUN_00119990();
  FUN_0011f450();
  if (Game::SceneInfo.backgrounds.head == (background_0x934_conflict3)0x0) {
    ModelSubresource0x12 = (TilesSubresource *)0x0;
  }
  else {
    pMVar1 = ADJ(Game::SceneInfo.backgrounds.head).avatar.modelInstance;
    if ((pMVar1 == (Model *)0x0) ||
       (model_descriptor = pMVar1->descriptor, model_descriptor == (ModelDescriptor *)0x0)) {
      ModelSubresource0x12 = (TilesSubresource *)0x0;
    }
    else {
      ModelSubresource0x12 = model_descriptor->runtimeCtx->subres0x12;
    }
  }
  NumBurnups = (undefined *)0x0;
  DAT_00510580 = FUN_0011b7a0();
                    // Loading texture
  if (DAT_00510580 != 0) {
    CreateWavyTexture_();
    DAT_00510648 = 0;
    DAT_0051064c = 0;
    Graphics::InitialiseScreenSpaceQuads();
  }
  DAT_00510650 = 0;
  LoadBackgroundTiles();
  DAT_00510560 = 0;
  puVar2 = &ZeroedOutSceneThing_ARRAY_0050ef20[0].field1_0x4;
  do {
    puVar2[-1] = 0;
    *puVar2 = 0;
    puVar2 = puVar2 + 0x58;
  } while ((int)puVar2 < 0x510524);
  InitialiseDoors();
  InitialiseColliders();
  SetupBackgroundEntries();
  FUN_0011c980();
  initIntroData();
  DoMarkerSceneStuff();
  sceneControlObj::processNew();
  avatar::processNew();
  local_4 = Scene_Begin;
  EventLoop::NewMessage((MessageHeader *)&local_4);
  FUN_001231f0();
  sceneControlObj::BeginScene();
  avatar::BeginScene();
  EmptySceneList();
  FUN_00123240();
  FUN_0012a1e0();
  FUN_00132040();
  FUN_00049ba0();
  DAT_005462fc = 0;
  return;
}




void EventLoop::UnpauseGame(void)

{
  AudioPlayingContext *pAVar1;
  AudioPlayingContext *pAVar2;
  int iVar3;
  
  if (Game::g_pauseState != Playing) {
    *(undefined4 *)(*DAT_00510cf8 + 8) = *(undefined4 *)(*DAT_00510cf8 + 4);
    FUN_00142aa0();
    Game::SetPauseState(Playing);
  }
  Game::SetBackgroundPositions((vec3 *)&DAT_00510e0c,(vec3 *)&DAT_00510e18);
  if (Game::DialogState != NotInDialog) {
    Events::SetDialogState(NotInDialog);
  }
  g_gameStateStack = g_gameStateStack + -1;
  DAT_00507df4 = 0;
  if (DAT_00510e24 != 0) {
    FromPlayToPause(DAT_00510e24);
    DAT_00510e24 = 0;
  }
  if (g_paused_ != 0) {
    g_globalFlagset = g_globalFlagset & ~Paused;
    g_paused_ = 0;
  }
  if ((g_pausePadScript->header).active != 0) {
    Scripting::PopInputHandler();
  }
  switch((g_pausePadScript->header).type) {
  case TYPE_1:
    Scripting::FreeScript123(&g_pausePadScript->header);
    break;
  case TYPE_2:
    Scripting::FreeScript123(&g_pausePadScript->header);
    break;
  case TYPE_3:
    Scripting::FreeScript123(&g_pausePadScript->header);
    break;
  case TYPE_4_NESTED:
    Scripting::FreeScript4(g_pausePadScript);
    break;
  case TYPE_5:
    Scripting::FreeScript5(g_pausePadScript);
  }
  g_pausePadScript = (ScriptType4 *)0x0;
  if (DAT_00510e40 != (void *)0x0) {
    Assets::DestroyAssetOrDecrement(DAT_00510e40);
    DAT_00510e40 = (void *)0x0;
  }
  if (DAT_00510e34 != 0) {
    GlobalCounter2 = GlobalCounter2 + -1;
    DAT_00510e34 = 0;
  }
  pAVar1 = Audio::GetPlayingContext("XACT_SOUNDBANK_GSTREAMSDITTIES_PAUSE");
  iVar3 = pAVar1->numReferences + -1;
  pAVar1->numReferences = iVar3;
  if (iVar3 < 1) {
    if ((pAVar1->playFlags != 0x12) &&
       (pAVar2 = Audio::GetSomePlayingThing(pAVar1), pAVar2 != (AudioPlayingContext *)0x0)) {
      AudioPlayingContext::updateSomething(pAVar2);
    }
    FUN_00038260(pAVar1);
    pAVar1->playFlags = 0;
  }
  UpdateGameVolumes();
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void EventLoop::SetLoadState(GameState *state,LoadState new_state)

{
  char *pcVar1;
  char cVar2;
  int index;
  char *pcVar3;
  
  if (state->load_state != new_state) {
                    // Cleanup current state first
    switch(state->load_state) {
    case Normal:
    case EndingBookCutscene?:
      g_stateStack = g_stateStack + 1;
      FUN_00106e90();
      break;
    case Loading:
      Game::NotAllowedToPause = Game::NotAllowedToPause + -1;
      GlobalCounter2 = GlobalCounter2 + -1;
      break;
    case FinishedLoading:
      runtime::FinaliseLoad();
      break;
    case Paused:
                    // If the new state isn't PAUSED, then we should unpause the game
      UnpauseGame();
    }
    switch(new_state) {
    case Normal:
    case EndingBookCutscene?:
      g_stateStack = g_stateStack + -1;
      if (g_stateStack < 0) {
        g_stateStack = 0;
      }
      UpdateDrawingData___();
      state->load_state = new_state;
      return;
    case BeginLoading:
      state->preventLoading = 1;
      state->game_is_loaded = 0;
      state->use_scene_focus = 0;
      state->load_state = new_state;
      return;
    case Loading:
      Game::EndScene(state);
      Game::NotAllowedToPause = Game::NotAllowedToPause + 1;
      GlobalCounter2 = GlobalCounter2 + 1;
                    // Game::GameState.currentSceneScript = Game::GameState.newSceneScript
      pcVar1 = state->newSceneScriptAID;
      pcVar3 = pcVar1;
      do {
        cVar2 = *pcVar3;
        pcVar3[(int)state - (int)pcVar1] = cVar2;
        pcVar3 = pcVar3 + 1;
      } while (cVar2 != '\0');
      *pcVar1 = '\0';
      index = Scripting::ScriptHeaderIndexFromAID(Game::GameState.currentSceneScript);
      g_currentPlaycamScriptHeader = g_scriptHeaders + index;
      state->someLoadedVar = 4;
      UpdateGameVolumes();
      InitPlaycamScriptAndGlobals();
      state->game_is_loaded = 1;
      break;
    case Paused:
                    // Pause is entered here
      UI::EnterPauseUI();
      state->load_state = new_state;
      return;
    }
    state->load_state = new_state;
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


int Events::RenderAllFromNode(int param_1,int param_2,int param_3,EmbeddedSentinel<> *param_4)

{
  undefined1 valueToSearch;
  int iVar1;
  uint i;
  int *piVar2;
  ModelDescriptor *pMVar3;
  ModelFooterEntry *pMVar4;
  Model *pMVar5;
  int iVar6;
  avatar *av;
  background *bg;
  float fVar7;
  float fVar8;
  undefined1 index;
  vec3 local_c;
  background_0x934 av_offset;
  ModelFooterEntry *footer_entries;
  
  for (av_offset = param_4->head; av_offset != (background_0x934)0x0; av_offset = av_offset->next) {
    pMVar5 = ADJ(av_offset).avatar.model;
                    // convert bg pointer to bg
    bg = ADJ(av_offset);
    if (pMVar5 != (Model *)0x0) {
      pMVar5->field342_0x15c = (ModelSubresource *)param_3;
    }
    if (param_3 == 1) {
      local_c.x = (Graphics::CurrentCameraStruct->pos).x;
      local_c.y = (Graphics::CurrentCameraStruct->pos).y;
      local_c.z = (Graphics::CurrentCameraStruct->pos).z;
      iVar1 = FUN_0011f310();
      pMVar5 = ADJ(av_offset).avatar.model;
      if (pMVar5 == (Model *)0x0) {
        footer_entries = (ModelFooterEntry *)0x0;
      }
      else {
        footer_entries = (ModelFooterEntry *)pMVar5->descriptor;
      }
      i = 0;
      if (footer_entries->offset != 0) {
        piVar2 = (int *)footer_entries->subresourceType;
        do {
          if (*piVar2 == 1) {
            i = ((int *)footer_entries->subresourceType)[i * 2 + 1];
            goto LAB_001219a6;
          }
          i = i + 1;
          piVar2 = piVar2 + 2;
        } while (i < footer_entries->offset);
      }
      i = 0;
LAB_001219a6:
      if ((i & 0x40000000) != 0) {
        ModelInstance::searchForValueWithFlags(iVar1 == 0,pMVar5,0x1e);
      }
      pMVar5 = ADJ(av_offset).avatar.model;
      if (pMVar5 == (Model *)0x0) {
        pMVar3 = (ModelDescriptor *)0x0;
      }
      else {
        pMVar3 = pMVar5->descriptor;
      }
      i = 0;
      if (pMVar3->numFooterEntries != 0) {
        pMVar4 = pMVar3->footerEntries;
        do {
          if (pMVar4->subresourceType == ModelFlags) {
            i = pMVar3->footerEntries[i].offset;
            goto LAB_001219f0;
          }
          i = i + 1;
          pMVar4 = pMVar4 + 1;
        } while (i < pMVar3->numFooterEntries);
      }
      i = 0;
LAB_001219f0:
      if ((i & 0x20000000) != 0) {
        ModelInstance::searchForValueWithFlags((char)iVar1,pMVar5,0x1d);
      }
      pMVar5 = ADJ(av_offset).avatar.model;
      if (pMVar5 == (Model *)0x0) {
        pMVar3 = (ModelDescriptor *)0x0;
      }
      else {
        pMVar3 = pMVar5->descriptor;
      }
      i = 0;
      if (pMVar3->numFooterEntries != 0) {
        pMVar4 = pMVar3->footerEntries;
        do {
          if (pMVar4->subresourceType == ModelFlags) {
            i = pMVar3->footerEntries[i].offset;
            goto LAB_00121a36;
          }
          i = i + 1;
          pMVar4 = pMVar4 + 1;
        } while (i < pMVar3->numFooterEntries);
      }
      i = 0;
LAB_00121a36:
      if ((i & 0x10000000) != 0) {
        index = 0x1c;
        valueToSearch = 1;
LAB_00121b1e:
        ModelInstance::searchForValueWithFlags(valueToSearch,pMVar5,index);
      }
    }
    else {
      pMVar5 = ADJ(av_offset).avatar.model;
      if (pMVar5 == (Model *)0x0) {
        pMVar3 = (ModelDescriptor *)0x0;
      }
      else {
        pMVar3 = pMVar5->descriptor;
      }
      i = 0;
      if (pMVar3->numFooterEntries != 0) {
        pMVar4 = pMVar3->footerEntries;
        do {
          if (pMVar4->subresourceType == ModelFlags) {
            i = pMVar3->footerEntries[i].offset;
            goto LAB_00121a7f;
          }
          i = i + 1;
          pMVar4 = pMVar4 + 1;
        } while (i < pMVar3->numFooterEntries);
      }
      i = 0;
LAB_00121a7f:
      if ((i & 0x10000000) != 0) {
        ModelInstance::searchForValueWithFlags(0,pMVar5,0x1c);
      }
      pMVar5 = ADJ(av_offset).avatar.model;
      if (pMVar5 == (Model *)0x0) {
        pMVar3 = (ModelDescriptor *)0x0;
      }
      else {
        pMVar3 = pMVar5->descriptor;
      }
      i = 0;
      if (pMVar3->numFooterEntries != 0) {
        pMVar4 = pMVar3->footerEntries;
        do {
          if (pMVar4->subresourceType == ModelFlags) {
            i = pMVar3->footerEntries[i].offset;
            goto LAB_00121ac5;
          }
          i = i + 1;
          pMVar4 = pMVar4 + 1;
        } while (i < pMVar3->numFooterEntries);
      }
      i = 0;
LAB_00121ac5:
      if ((i & 0x20000000) != 0) {
        ModelInstance::searchForValueWithFlags(0,pMVar5,0x1d);
      }
      pMVar5 = ADJ(av_offset).avatar.model;
      if (pMVar5 == (Model *)0x0) {
        pMVar3 = (ModelDescriptor *)0x0;
      }
      else {
        pMVar3 = pMVar5->descriptor;
      }
      i = 0;
      if (pMVar3->numFooterEntries != 0) {
        pMVar4 = pMVar3->footerEntries;
        do {
          if (pMVar4->subresourceType == ModelFlags) {
            i = pMVar3->footerEntries[i].offset;
            goto LAB_00121b13;
          }
          i = i + 1;
          pMVar4 = pMVar4 + 1;
        } while (i < pMVar3->numFooterEntries);
      }
      i = 0;
LAB_00121b13:
      if ((i & 0x40000000) != 0) {
        index = 0x1e;
        valueToSearch = 0;
        goto LAB_00121b1e;
      }
    }
    FUN_001572c0();
    if (param_3 == 0) {
      (*((bg->avatar).vtable)->draw)(bg,param_2,0);
    }
                    // Background::func5 (draw function)
    (*((bg->avatar).vtable)->draw)(bg,param_2,1);
    FUN_001572b0();
  }
  if (param_3 == 0) {
    if (DoneReadingLoad < 1) {
      FUN_00119ad0();
    }
    FUN_000fe960();
    renderBurnups();
    FUN_001237e0();
    Graphics::RenderSomethingLeadsToVS0xe(0);
  }
  iVar1 = *(int *)(param_1 + 4);
                    // Draw the scene entities
  if (iVar1 != 0) {
    do {
      iVar6 = iVar1 + (param_2 + param_3 * 4) * -0xc;
      av = (avatar *)(iVar6 + -0x124);
      if (*(int *)(iVar6 + 0xe0) != 0) {
        *(int *)(*(int *)(iVar6 + 0xe0) + 0x15c) = param_3;
      }
      if ((1 << ((byte)param_2 & 0x1f) & (uint)*(ushort *)(iVar6 + 0x70)) != 0) {
        if (param_3 == 1) {
          fVar7 = avatar::getCalculatedRadius(av);
          avatar::getWorldPosition(av,&local_c);
          fVar8 = local_c.z * DAT_00511170 + local_c.y * DAT_0051116c + local_c.x * DAT_00511168 +
                  DAT_00511174;
          if (((0.0 < (g_IdkGraphicsVec3.z * DAT_00511170 + g_IdkGraphicsVec3.y * DAT_0051116c +
                       g_IdkGraphicsVec3.x * DAT_00511168 + DAT_00511174) * fVar8) &&
              (fVar7 * fVar7 <= fVar8 * fVar8)) ||
             ((DAT_00511160 != 0 &&
              (iVar6 = FUN_00159ad0(0x5110b8,&local_c,fVar7,&DAT_00511164), iVar6 == 0))))
          goto LAB_00121d0e;
        }
        else if (param_3 == 0) {
          (*av->vtable->draw)(av,param_2,0);
        }
        (*av->vtable->draw)(av,param_2,1);
      }
LAB_00121d0e:
      iVar1 = *(int *)(iVar1 + 4);
    } while (iVar1 != 0);
  }
  if (param_3 == 0) {
    Graphics::DrawUIStuff_();
    Graphics::RenderSomethingLeadsToVS0xe(1);
  }
  return param_1;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void EventLoop::DispatchMessage(ObjMsgID *msg)

{
  avatar_conflict13 *paVar1;
  avatar_conflict13 *paVar2;
  avatar_0x900_conflict6 pEVar3;
  
  pEVar3 = Game::SceneInfo.avatars.next;
  while (pEVar3 != (avatar_0x900_conflict6)0x0) {
    paVar1 = ADJ(pEVar3);
    paVar2 = ADJ(pEVar3);
    pEVar3 = pEVar3->next;
    (*((paVar1->object).vtable)->onMessage)(paVar2,msg);
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void SetGlobalSceneOrder(char *name)

{
  char *asset;
  
  if ((Assets::SceneOrderAHandle.deallocFn != (void *)0x0) &&
     (Assets::SceneOrderAHandle.sceneOrder != (char *)0x0)) {
                    // Unload/delete
    (*Assets::SceneOrderAHandle.deallocFn)(&Assets::SceneOrderAHandle);
  }
                    // If invalid asset name in, detach the current gameselect script
  if (*(int *)name != 0x5f646961) {
    Assets::SceneOrderAHandle.sceneOrder = (char *)0x0;
    Assets::SceneOrderAHandle.deallocFn = AssetHandle::Unload;
    return;
  }
  Assets::GetResourceBytes(name,&asset);
  if (asset == (char *)0x0) {
    runtime::ExitGame(2);
  }
  Assets::SceneOrderAHandle.sceneOrder = asset;
  Assets::SceneOrderAHandle.deallocFn = AssetHandle::Unload;
  return;
}




uint GetChallengeHeader(void)

{
  BOOL BVar1;
  int i;
  uint uVar2;
  ScriptNameStub *name2;
  
  i = 0;
  name2 = &ScriptNameStub_00430da0;
  uVar2 = 0;
  do {
    BVar1 = Assets::AssetNamesMatch(Game::GameState.currentSceneScript,name2->name);
    if (BVar1 != 0) {
      return (&ScriptNameStub_00430da0)[i].flags_;
    }
    uVar2 = uVar2 + 0x84;
    i = i + 1;
    name2 = name2 + 1;
  } while (uVar2 < 0x210);
  return 0;
}




BOOL EventLoop::IsPlayStateSomething(void)

{
  BOOL BVar1;
  
  BVar1 = 1;
  if (((g_finishedLoading_ != 1) && ((*SomeAS15->flags & 8) == 0)) &&
     ((g_globalFlagset & 0x200000) == 0)) {
    BVar1 = 0;
  }
  return BVar1;
}




void EventLoop::SetAggressions(BOOL playerControllable,int playType,char *param_3)

{
  char cVar1;
  char cVar2;
  MindMemoryTargetWantedToAttack *pMVar3;
  MindMemoryTargetWantedToAttack *pMVar4;
  MindMemoryTargetWantedToAttack *mem;
  int iVar5;
  char c;
  
  if ((playerControllable != Game::CheckMoveOn) || (playType != UINT_00512490)) {
    cVar1 = "\x01"[Game::CheckMoveOn];
    cVar2 = "\x01"[playerControllable];
    iVar5 = (int)Game::CurrentLog - (int)param_3;
    Game::CheckMoveOn = playerControllable;
    UINT_00512490 = playType;
    do {
      c = *param_3;
      param_3[iVar5] = c;
      param_3 = param_3 + 1;
    } while (c != '\0');
    Game::CheckedMoveOn = (BOOL)(Game::CheckMoveOn == 0);
    Game::WaitingForChallenge = 0;
    Game::MoveOn = 0;
    Scripting::ScriptConditions->tail = Scripting::ScriptConditions->head;
    pMVar3 = g_scriptRelatedLinkedList_;
    pMVar4 = g_scriptRelatedLinkedList_;
    while (mem = pMVar3, mem != (MindMemoryTargetWantedToAttack *)0x0) {
      pMVar3 = (MindMemoryTargetWantedToAttack *)(mem->header).next;
      if (*(int *)&(mem->header).memId == 0xb7) {
        MindMemory::dtor(mem);
        pMVar4 = g_scriptRelatedLinkedList_;
      }
    }
    while (pMVar3 = pMVar4, pMVar3 != (MindMemoryTargetWantedToAttack *)0x0) {
      pMVar4 = (MindMemoryTargetWantedToAttack *)(pMVar3->header).next;
      if (*(int *)&(pMVar3->header).memId == 0xb6) {
        MindMemory::dtor(pMVar3);
      }
    }
    if (g_pauseMenuState_ != Paused) {
      FUN_0012af10();
      DAT_00545980 = 0;
    }
    if (cVar1 != cVar2) {
      Events::UpdateActionBeginEnds(0xff,(uint)(byte)"\x01"[Game::CheckMoveOn]);
    }
  }
  return;
}




void Events::UpdateDeltaAngles(void)

{
  float *pfVar1;
  float delta;
  
  if (DAT_00512af0 != 0) {
    if (runtime::dx_timer <= 0.0) {
      delta = runtime::DeltaTime * runtime::TimeScale;
    }
    else {
      delta = 0.0;
    }
    pfVar1 = (float *)&DeltaAngleFloats;
    do {
      if (pfVar1[3] != 0.0) {
        pfVar1[-3] = *pfVar1 * delta + pfVar1[-3];
        pfVar1[-2] = pfVar1[1] * delta + pfVar1[-2];
        pfVar1[-1] = pfVar1[2] * delta + pfVar1[-1];
        Math::WrapAnglesRad((vec3 *)(pfVar1 + -3));
      }
      pfVar1 = pfVar1 + 0xb;
    } while ((int)pfVar1 < 0x512b88);
  }
  return;
}




void EventLoop::CreateTransitionCameraAndText(void)

{
  Camera *conf;
  
  if (TransitionData.discReadEnum != 0) {
    runtime::FinaliseLoad();
  }
  if (TransitionData.discReadEnum == 0) {
    Game::NotAllowedToPause = Game::NotAllowedToPause + 1;
    GlobalCounter2 = GlobalCounter2 + 1;
    g_globalFlagset = g_globalFlagset | 0x100;
  }
  else if (TransitionData.discReadEnum == 1) {
    Game::GameState.currentScene = 0;
  }
  else if (TransitionData.discReadEnum == 3) {
    Game::GameState.currentChapter = 0;
  }
  TransitionData.discReadEnum = 1;
  TransitionData.transitionIndex =
       Events::getTransitionAndOtherScriptHeaderValueFromNewSceneScriptAID
                 (&TransitionData.transitionVal2,(uint *)&TransitionData.scriptHeaderVal2);
  TransitionData.transitionVal1 = g_globalTransitionStates[TransitionData.transitionIndex].val1;
  TransitionData.doneReading_ = 0;
  TransitionData.field11_0x20 = 0xf;
  TransitionData.transitionAssetName_ =
       (char *)((*(int *)(&DAT_0043147c + TransitionData.transitionIndex * 0x110) != 0x5f646961) - 1
               & (uint)(&DAT_0043147c + TransitionData.transitionIndex * 0x110));
  TransitionData.transitionVal1Again = TransitionData.transitionVal1;
  Camera::ctor(&Camera::TransitionConfig,"transition",(ProjectionSetBitField)0x0);
  Camera::TransitionConfig.next = (Camera *)Camera::AvailableConfigs;
  conf = Camera::AvailableConfigs[0].head;
  while (conf != (Camera *)0x0) {
    Camera::TransitionConfig.next = (Camera::TransitionConfig.next)->next;
    conf = (Camera::TransitionConfig.next)->next;
  }
  Camera::TransitionConfig.prev = (Camera::TransitionConfig.next)->prev;
  (Camera::TransitionConfig.next)->prev = &Camera::TransitionConfig;
  if (Camera::TransitionConfig.prev != (Camera *)0x0) {
    (Camera::TransitionConfig.prev)->next = &Camera::TransitionConfig;
  }
  if (Camera::ActiveConfigs[0] == (Camera *)0x0) {
    Camera::SetActiveCameraConfig(0,Camera::TransitionConfig.name);
  }
  runtime::Clear_g_itemsToClear();
  runtime::AllocateForLoctext_
            (0,1,(void *)0x80,(LoctextValueContext **)&TransitionData.field12_0x24);
                    // Fetches from 
                    // aid_loctext_ghoulies_gameselect_gameselecttext
                    //     > gameselect
                    //         > loading
  loctext::get_text("aid_loctext_ghoulies_gameselect_gameselecttext","gameselect","loading",
                    TransitionData.g_LoadingText);
  (*(code *)g_callback6Sets[*(int *)(&DAT_00431478 + TransitionData.transitionIndex * 0x110)][4])
            (&TransitionData);
  GlobalCounter2 = GlobalCounter2 + 1;
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


Events::TriggerAssetTypeCallback1(asset_name *assetName,void *descriptorPtr,void *param_3)

{
  int iVar1;
  int iVar2;
  ResourceLoaderStub *set;
  char name;
  
  iVar2 = 0;
  name = (*assetName)[4];
  while (name != '_') {
    Assets::LoadingAssetType[iVar2] = name;
    iVar1 = iVar2 + 5;
    iVar2 = iVar2 + 1;
    name = (*assetName)[iVar1];
  }
  Assets::LoadingAssetType[iVar2] = '\0';
  set = GetResourceLoaderStub(Assets::LoadingAssetType);
  if ((set != (ResourceLoaderStub *)0x0) && (set->processDescriptor != (code *)0x0)) {
                    // Calls
                    // 0x00051f00 - loctext
                    // 0x00051190 - cutscene
                    // 0x00051190 - Unknown
                    // 0x000516a0 - font
    (*set->processDescriptor)(descriptorPtr,descriptorPtr,param_3);
  }
  return;
}




void Events::NotUpdateDialogs_(void)

{
  float delta;
  
  if (Game::UpdateActionType == 1) {
    if ((ShouldntDroneBools[1] == 0) && ("\x01"[Game::CheckMoveOn] != '\0')) {
      UpdateActionBeginEnds(0xff,0);
      ::Scripting::numScriptConditions = ::Scripting::numScriptConditions + 1;
      Game::UpdateActionType = 2;
      Game::SomeActionBeginTimer = 1.0;
      EndCurrentSceneOrDialog = 1;
    }
  }
  else if (Game::UpdateActionType == 2) {
    if (runtime::dx_timer <= 0.0) {
      delta = runtime::DeltaTime * runtime::TimeScale;
    }
    else {
      delta = 0.0;
    }
    if ((0.0 < Game::SomeActionBeginTimer) &&
       (Game::SomeActionBeginTimer = Game::SomeActionBeginTimer - delta,
       Game::SomeActionBeginTimer <= 0.0)) {
      Game::SomeActionBeginTimer = 0.0;
      Game::UpdateActionType = 3;
      BeginDialogSequence(0);
      if (DAT_00545bc4 != '\0') {
        BeginDialogSequence(0);
        return;
      }
    }
  }
  else {
                    // In dialog
    if (Game::UpdateActionType == 3) {
      CheckEndOfCutscene();
      return;
    }
  }
  return;
}




void DoMarkerSceneStuff(void)

{
  MarkerInstance *newInstance;
  int iVar4;
  HeapTableEntry *pHVar5;
  MarkerInstance *markerInstance;
  uint *puVar1;
  undefined4 uVar3;
  
  markerInstance = Game::GameState.markerInstance;
  puVar1 = &(Game::GameState.markerInstance)->end;
  newInstance = malloc_(*puVar1);
  if (newInstance != (MarkerInstance *)0x0) {
    memcpy(newInstance,markerInstance,*puVar1);
  }
  FUN_001401b0(newInstance);
  FUN_001402b0(newInstance);
  FUN_0011eec0(newInstance);
  iVar4 = FindHeapOf(newInstance);
  uVar3 = runtime::CurrentHeapToAllocateFrom;
  if (g_HeapTableBase[iVar4].heapHandle == (HANDLE)0x0) {
    pHVar5 = (HeapTableEntry *)0x0;
  }
  else {
    pHVar5 = g_HeapTableBase + iVar4;
  }
  runtime::CurrentHeapToAllocateFrom = iVar4;
  XAPILIB::HeapFree(pHVar5->heapHandle,0,newInstance);
  runtime::CurrentHeapToAllocateFrom = uVar3;
  return;
}




void FUN_001401b0(MarkerInstance *param_1)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  uint16_t uVar7;
  uint uVar8;
  uint uVar9;
  Marker *pMVar10;
  Marker *pMVar11;
  int i;
  
  i = 0;
  if (0 < DAT_00545cc8) {
    do {
      uVar8 = param_1->numMarkers;
      uVar9 = 0;
      if (uVar8 != 0) {
        pMVar11 = param_1->marker;
        do {
          if (pMVar11->id == (&DAT_00545c48)[i * 2]) goto LAB_001401f7;
          uVar9 = uVar9 + 1;
          pMVar11 = (Marker *)((int)&pMVar11->size + pMVar11->size);
        } while (uVar9 < uVar8);
      }
      pMVar11 = (Marker *)0x0;
LAB_001401f7:
      uVar9 = 0;
      if (uVar8 != 0) {
        pMVar10 = param_1->marker;
        do {
          if (pMVar10->id == (&DAT_00545c4a)[i * 2]) goto LAB_00140216;
          pMVar10 = (Marker *)((int)&pMVar10->size + pMVar10->size);
          uVar9 = uVar9 + 1;
        } while (uVar9 < uVar8);
      }
      pMVar10 = (Marker *)0x0;
LAB_00140216:
      if ((pMVar11 != (Marker *)0x0) && (pMVar10 != (Marker *)0x0)) {
        fVar1 = (pMVar11->pos).x;
        fVar2 = (pMVar11->pos).y;
        fVar3 = (pMVar11->pos).z;
        fVar4 = (pMVar11->eulerRot).x;
        fVar5 = (pMVar11->eulerRot).y;
        fVar6 = (pMVar11->eulerRot).z;
        uVar7 = pMVar11->runtimeId;
        (pMVar11->pos).x = (pMVar10->pos).x;
        (pMVar11->pos).y = (pMVar10->pos).y;
        (pMVar11->pos).z = (pMVar10->pos).z;
        (pMVar11->eulerRot).x = (pMVar10->eulerRot).x;
        (pMVar11->eulerRot).y = (pMVar10->eulerRot).y;
        (pMVar11->eulerRot).z = (pMVar10->eulerRot).z;
        pMVar11->runtimeId = pMVar10->runtimeId;
        (pMVar10->pos).x = fVar1;
        (pMVar10->pos).y = fVar2;
        (pMVar10->pos).z = fVar3;
        (pMVar10->eulerRot).x = fVar4;
        (pMVar10->eulerRot).y = fVar5;
        (pMVar10->eulerRot).z = fVar6;
        pMVar10->runtimeId = uVar7;
      }
      i = i + 1;
    } while (i < DAT_00545cc8);
  }
  return;
}




void __fastcall SetupEvents_(int *param_1)

{
  uint *puVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  undefined4 *puVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int local_14;
  undefined4 *local_10;
  undefined4 *local_8;
  
  iVar2 = *param_1;
  iVar3 = param_1[param_1[0x40] + 0x4e];
  iVar6 = iVar3 + 0x70000;
  puVar1 = (uint *)(iVar6 * 0x10 + iVar2);
  *puVar1 = *puVar1 | 1;
  iVar4 = iVar6 * 4;
  *(undefined4 *)(iVar2 + 0x33c + iVar6 * 0x10) = 0xffff0000;
  *(undefined4 *)(iVar2 + 0x340 + iVar6 * 0x10) = 0;
  *(undefined4 *)(iVar2 + 0x344 + iVar6 * 0x10) = 0;
  *(undefined4 *)(iVar2 + 0x348 + iVar6 * 0x10) = 0;
  *(undefined4 *)(iVar2 + 0x34c + iVar6 * 0x10) = 0;
  *(undefined4 *)(iVar2 + 0x350 + iVar6 * 0x10) = 0;
  *(undefined4 *)(iVar2 + 0x354 + iVar6 * 0x10) = 0;
  *(undefined4 *)(iVar2 + 0x358 + iVar6 * 0x10) = 0;
  *(undefined4 *)(iVar2 + 0x35c + iVar6 * 0x10) = 0;
  *(undefined4 *)(iVar2 + 0x360 + iVar6 * 0x10) = 0;
  *(undefined4 *)(iVar2 + 0x364 + iVar6 * 0x10) = 0;
  *(undefined4 *)(iVar2 + 0x368 + iVar6 * 0x10) = 0;
  *(undefined4 *)(iVar2 + 0x36c + iVar6 * 0x10) = 0;
  *(undefined4 *)(iVar2 + 0x370 + iVar6 * 0x10) = 0;
  *(undefined4 *)(iVar2 + 0x374 + iVar6 * 0x10) = 0;
  *(undefined4 *)(iVar2 + 0x378 + iVar6 * 0x10) = 0;
  *(undefined4 *)(iVar2 + 0x37c + iVar6 * 0x10) = 0;
  *(undefined4 *)(iVar2 + 0x380 + iVar6 * 0x10) = 0;
  *(undefined4 *)(iVar2 + 900 + iVar6 * 0x10) = 0;
  *(undefined4 *)(iVar2 + 0x388 + iVar6 * 0x10) = 0;
  *(undefined4 *)(iVar2 + 0x38c + iVar6 * 0x10) = 0;
  *(undefined4 *)(iVar2 + 0x390 + iVar6 * 0x10) = 0;
  *(undefined4 *)(iVar2 + 0x394 + iVar6 * 0x10) = 0;
  *(undefined4 *)(iVar2 + 0x398 + iVar6 * 0x10) = 0;
  *(undefined4 *)(iVar2 + 0x39c + iVar6 * 0x10) = 0;
  *(undefined4 *)(iVar2 + 0x3a0 + iVar6 * 0x10) = 0xfff0000;
  *(undefined4 *)(iVar2 + 0x3a4 + iVar6 * 0x10) = 0xfff0000;
  *(undefined4 *)(iVar2 + 0x3a8 + iVar6 * 0x10) = 0;
  *(undefined4 *)(iVar2 + 0x3ac + iVar6 * 0x10) = 0;
  *(undefined4 *)(iVar2 + 0x3b0 + iVar6 * 0x10) = 0;
  *(undefined4 *)(iVar2 + 0x3b4 + iVar6 * 0x10) = 0;
  *(undefined4 *)(iVar2 + 0x3b8 + iVar6 * 0x10) = 0;
  *(undefined4 *)(iVar2 + 0x3bc + iVar6 * 0x10) = 0;
  *(undefined4 *)(iVar2 + 0x3c0 + iVar6 * 0x10) = 0;
  *(undefined4 *)(iVar2 + 0x3c4 + iVar6 * 0x10) = 0;
  *(undefined4 *)(iVar2 + 0x3c8 + iVar6 * 0x10) = 0;
  *(undefined4 *)(iVar2 + 0x3cc + iVar6 * 0x10) = 0;
  *(undefined4 *)(iVar2 + 0x3d0 + iVar6 * 0x10) = 0;
  *(undefined4 *)(iVar2 + 0x3d4 + iVar6 * 0x10) = 0;
  *(undefined4 *)(iVar2 + 0x3d8 + iVar6 * 0x10) = 0;
  *(undefined4 *)(iVar2 + 0x3dc + iVar6 * 0x10) = 0;
  *(undefined4 *)(iVar2 + 0x3e0 + iVar6 * 0x10) = 0;
  *(undefined4 *)(iVar2 + 0x3e4 + iVar6 * 0x10) = 0;
  *(undefined4 *)(iVar2 + 1000 + iVar6 * 0x10) = 0;
  *(undefined4 *)(iVar2 + 0x3ec + iVar6 * 0x10) = 0;
  *(undefined4 *)(iVar2 + 0x3f0 + iVar6 * 0x10) = 0;
  *(undefined4 *)(iVar2 + 0x3f4 + iVar6 * 0x10) = 0;
  *(undefined4 *)(iVar2 + 0x3f8 + iVar6 * 0x10) = 0;
  *(undefined4 *)(iVar2 + 0x3fc + iVar6 * 0x10) = 0;
  *(undefined4 *)(iVar2 + 0x400 + iVar6 * 0x10) = 0;
  *(undefined4 *)(iVar2 + 0x404 + iVar6 * 0x10) = 0;
  *(undefined4 *)(iVar2 + 0x408 + iVar6 * 0x10) = 0;
  *(undefined4 *)(iVar2 + 0x40c + iVar6 * 0x10) = 0;
  *(undefined4 *)(iVar2 + 0x410 + iVar6 * 0x10) = 0;
  *(undefined4 *)(iVar2 + 0x414 + iVar6 * 0x10) = 0;
  *(undefined4 *)(iVar2 + 0x418 + iVar6 * 0x10) = 0;
  *(undefined4 *)(iVar2 + 0x41c + iVar6 * 0x10) = 0;
  *(undefined4 *)(iVar2 + 0x420 + iVar6 * 0x10) = 0;
  *(undefined4 *)(iVar2 + 0x424 + iVar6 * 0x10) = 0;
  *(undefined4 *)(iVar2 + 0x428 + iVar6 * 0x10) = 0;
  *(undefined4 *)(iVar2 + 0x42c + iVar6 * 0x10) = 0;
  *(undefined4 *)(iVar2 + 0x430 + iVar6 * 0x10) = 0;
  *(undefined4 *)(iVar2 + 0x434 + iVar6 * 0x10) = 0;
  *(undefined4 *)(iVar2 + 0x438 + iVar6 * 0x10) = 0;
  *(undefined4 *)(iVar2 + 0x43c + iVar6 * 0x10) = 0;
  *(undefined4 *)(iVar2 + 0x440 + iVar6 * 0x10) = 0;
  *(undefined4 *)(iVar2 + 0x444 + iVar6 * 0x10) = 0;
  *(undefined4 *)(iVar2 + 0x448 + iVar6 * 0x10) = 0;
  *(undefined4 *)(iVar2 + 0x44c + iVar6 * 0x10) = 0;
  *(undefined4 *)(iVar2 + 0x450 + iVar6 * 0x10) = 0;
  *(undefined4 *)(iVar2 + 0x454 + iVar6 * 0x10) = 0;
  *(undefined4 *)(iVar2 + 0x458 + iVar6 * 0x10) = 0;
  *(undefined4 *)(iVar2 + 0x45c + iVar6 * 0x10) = 0;
  *(undefined4 *)(iVar2 + 0x460 + iVar6 * 0x10) = 0;
  *(undefined4 *)(iVar2 + 0x464 + iVar6 * 0x10) = 0;
  *(undefined4 *)(iVar2 + 0x468 + iVar6 * 0x10) = 0;
  *(undefined4 *)(iVar2 + 0x46c + iVar6 * 0x10) = 0;
  *(undefined4 *)(iVar2 + 0x470 + iVar6 * 0x10) = 0;
  *(undefined4 *)(iVar2 + 0x474 + iVar6 * 0x10) = 0;
  *(undefined4 *)(iVar2 + 0x478 + iVar6 * 0x10) = 0;
  *(undefined4 *)(iVar2 + 0x47c + iVar6 * 0x10) = 0x101;
  *(undefined4 *)(iVar2 + 0x480 + iVar6 * 0x10) = 0;
  *(undefined4 *)(iVar2 + 0x484 + iVar6 * 0x10) = 0;
  *(undefined4 *)(iVar2 + 0x488 + iVar6 * 0x10) = 0;
  *(undefined4 *)(iVar2 + 0x48c + iVar6 * 0x10) = 0;
  *(undefined4 *)(iVar2 + 0x490 + iVar6 * 0x10) = 0x111;
  *(undefined4 *)(iVar2 + 0x494 + iVar6 * 0x10) = 0;
  *(undefined4 *)(iVar2 + 0x498 + iVar6 * 0x10) = 0;
  *(undefined4 *)(iVar2 + 0x49c + iVar6 * 0x10) = 0;
  *(undefined4 *)(iVar2 + 0x4a0 + iVar6 * 0x10) = 0;
  *(undefined4 *)(iVar2 + 0x4a4 + iVar6 * 0x10) = 0;
  *(undefined4 *)(iVar2 + 0x4a8 + iVar6 * 0x10) = 0x44400000;
  *(undefined4 *)(iVar2 + 0x4ac + iVar6 * 0x10) = 0;
  *(undefined4 *)(iVar2 + 0x4b0 + iVar6 * 0x10) = 0;
  *(undefined4 *)(iVar2 + 0x4b4 + iVar6 * 0x10) = 0;
  *(undefined4 *)(iVar2 + 0x4b8 + iVar6 * 0x10) = 0;
  *(undefined4 *)(iVar2 + 0x4bc + iVar6 * 0x10) = 0;
  *(undefined4 *)(iVar2 + 0x4c0 + iVar6 * 0x10) = 0;
  *(undefined4 *)(iVar2 + 0x4c4 + iVar6 * 0x10) = 0;
  *(undefined4 *)(iVar2 + 0x4c8 + iVar6 * 0x10) = 0;
  *(undefined4 *)(iVar2 + 0x4cc + iVar6 * 0x10) = 0;
  *(undefined4 *)(iVar2 + 0x4d0 + iVar6 * 0x10) = 0;
  *(undefined4 *)(iVar2 + 0x4d4 + iVar6 * 0x10) = 0x30303;
  *(undefined4 *)(iVar2 + 0x4d8 + iVar6 * 0x10) = 0x30303;
  *(undefined4 *)(iVar2 + 0x4dc + iVar6 * 0x10) = 0x30303;
  *(undefined4 *)(iVar2 + 0x4e0 + iVar6 * 0x10) = 0x30303;
  *(undefined4 *)(iVar2 + 0x4e4 + iVar6 * 0x10) = 0;
  *(undefined4 *)(iVar2 + 0x4e8 + iVar6 * 0x10) = 0;
  *(undefined4 *)(iVar2 + 0x4ec + iVar6 * 0x10) = 0;
  *(undefined4 *)(iVar2 + 0x4f0 + iVar6 * 0x10) = 0;
  *(undefined4 *)(iVar2 + 0x4f4 + iVar6 * 0x10) = 0x80000;
  *(undefined4 *)(iVar2 + 0x4f8 + iVar6 * 0x10) = 0x80000;
  *(undefined4 *)(iVar2 + 0x4fc + iVar6 * 0x10) = 0x80000;
  *(undefined4 *)(iVar2 + 0x500 + iVar6 * 0x10) = 0x80000;
  *(undefined4 *)(iVar2 + 0x504 + iVar6 * 0x10) = 0;
  *(undefined4 *)(iVar2 + 0x508 + iVar6 * 0x10) = 0;
  *(undefined4 *)(iVar2 + 0x50c + iVar6 * 0x10) = 0x1012000;
  *(undefined4 *)(iVar2 + 0x510 + iVar6 * 0x10) = 0x1012000;
  *(undefined4 *)(iVar2 + 0x514 + iVar6 * 0x10) = 0x1012000;
  *(undefined4 *)(iVar2 + 0x518 + iVar6 * 0x10) = 0x1012000;
  *(undefined4 *)(iVar2 + 0x51c + iVar6 * 0x10) = 67000;
  *(undefined4 *)(iVar2 + 0x520 + iVar6 * 0x10) = 67000;
  *(undefined4 *)(iVar2 + 0x524 + iVar6 * 0x10) = 67000;
  *(undefined4 *)(iVar2 + 0x528 + iVar6 * 0x10) = 67000;
  *(undefined1 **)(iVar2 + 0x52c + iVar6 * 0x10) = &LAB_00080006_2;
  *(undefined1 **)(iVar2 + 0x530 + iVar6 * 0x10) = &LAB_00080006_2;
  *(undefined1 **)(iVar2 + 0x534 + iVar6 * 0x10) = &LAB_00080006_2;
  *(undefined1 **)(iVar2 + 0x538 + iVar6 * 0x10) = &LAB_00080006_2;
  *(undefined4 *)(iVar2 + 0x53c + iVar6 * 0x10) = 0;
  *(undefined4 *)(iVar2 + 0x540 + iVar6 * 0x10) = 0;
  *(undefined4 *)(iVar2 + 0x544 + iVar6 * 0x10) = 0;
  *(undefined4 *)(iVar2 + 0x548 + iVar6 * 0x10) = 0;
  *(undefined4 *)(iVar2 + 0x54c + iVar6 * 0x10) = 0;
  *(undefined4 *)(iVar2 + 0x550 + iVar6 * 0x10) = 0;
  *(undefined4 *)(iVar2 + 0x554 + iVar6 * 0x10) = 0;
  *(undefined4 *)(iVar2 + 0x558 + iVar6 * 0x10) = 0;
  puVar5 = (undefined4 *)(iVar3 * 0x10 + 0x70055c + iVar2);
  iVar7 = 8;
  do {
    *puVar5 = 0x7ff0000;
    puVar5 = puVar5 + 1;
    iVar7 = iVar7 + -1;
  } while (iVar7 != 0);
  puVar5 = (undefined4 *)(iVar2 + 0x57c + iVar6 * 0x10);
  iVar7 = 8;
  do {
    *puVar5 = 0x7ff0000;
    puVar5 = puVar5 + 1;
    iVar7 = iVar7 + -1;
  } while (iVar7 != 0);
  *(undefined4 *)(iVar2 + 0x59c + iVar6 * 0x10) = 0;
  *(undefined4 *)(iVar2 + 0x5a0 + iVar6 * 0x10) = 0;
  *(undefined4 *)(iVar2 + 0x5a4 + iVar6 * 0x10) = 0x4b7fffff;
  *(undefined4 *)(iVar2 + 0x5a8 + iVar6 * 0x10) = 0;
  *(undefined4 *)(iVar2 + 0x5ac + iVar6 * 0x10) = 0;
  *(undefined4 *)(iVar2 + 0x5b0 + iVar6 * 0x10) = 0;
  *(undefined4 *)(iVar2 + 0x5b4 + iVar6 * 0x10) = 0;
  *(undefined4 *)(iVar2 + 0x5b8 + iVar6 * 0x10) = 0;
  *(undefined4 *)(iVar2 + 0x5bc + iVar6 * 0x10) = 0;
  *(undefined4 *)(iVar2 + 0x5c0 + iVar6 * 0x10) = 0;
  *(undefined4 *)(iVar2 + 0x5c4 + iVar6 * 0x10) = 0;
  *(undefined4 *)(iVar2 + 0x5c8 + iVar6 * 0x10) = 0;
  *(undefined4 *)(iVar2 + 0x5cc + iVar6 * 0x10) = 0;
  *(undefined4 *)(iVar2 + 0x5d0 + iVar6 * 0x10) = 0;
  *(undefined4 *)(iVar2 + 0x5d4 + iVar6 * 0x10) = 0;
  *(undefined4 *)(iVar2 + 0x5d8 + iVar6 * 0x10) = 0;
  *(undefined4 *)(iVar2 + 0x5dc + iVar6 * 0x10) = 0;
  *(undefined4 *)(iVar2 + 0x5e0 + iVar6 * 0x10) = 0;
  *(undefined4 *)(iVar2 + 0x5e4 + iVar6 * 0x10) = 0;
  *(undefined4 *)(iVar2 + 0x5e8 + iVar6 * 0x10) = 0;
  *(undefined4 *)(iVar2 + 0x5ec + iVar6 * 0x10) = 0;
  *(undefined4 *)(iVar2 + 0x5f0 + iVar6 * 0x10) = 0;
  *(undefined4 *)(iVar2 + 0x5f4 + iVar6 * 0x10) = 0;
  *(undefined4 *)(iVar2 + 0x5f8 + iVar6 * 0x10) = 0;
  *(undefined4 *)(iVar2 + 0x5fc + iVar6 * 0x10) = 1;
  *(undefined4 *)(iVar2 + 0x600 + iVar6 * 0x10) = 0;
  *(undefined4 *)(iVar2 + 0x604 + iVar6 * 0x10) = 0x4000;
  *(undefined4 *)(iVar2 + 0x608 + iVar6 * 0x10) = 0;
  *(undefined4 *)(iVar2 + 0x60c + iVar6 * 0x10) = 0;
  *(undefined4 *)(iVar2 + 0x610 + iVar6 * 0x10) = 1;
  *(undefined4 *)(iVar2 + 0x614 + iVar6 * 0x10) = 0;
  *(undefined4 *)(iVar2 + 0x618 + iVar6 * 0x10) = 0x40000;
  *(undefined4 *)(iVar2 + 0x61c + iVar6 * 0x10) = 0x10000;
  iVar7 = 0x23;
  *(undefined4 *)(iVar2 + 0x620 + iVar6 * 0x10) = 0;
  *(undefined4 *)(iVar2 + 0x624 + iVar6 * 0x10) = 0;
  *(undefined4 *)(iVar2 + 0x628 + iVar6 * 0x10) = 0;
  puVar5 = (undefined4 *)(iVar2 + 0x62c + iVar6 * 0x10);
  do {
    *puVar5 = 0;
    puVar5 = puVar5 + 1;
    iVar7 = iVar7 + -1;
  } while (iVar7 != 0);
  puVar5 = (undefined4 *)(iVar2 + 0x6b8 + iVar6 * 0x10);
  iVar7 = 0x1d;
  do {
    *puVar5 = 0;
    puVar5 = puVar5 + 1;
    iVar7 = iVar7 + -1;
  } while (iVar7 != 0);
  puVar5 = (undefined4 *)(iVar2 + 0x72c + iVar6 * 0x10);
  iVar7 = 0x1d;
  do {
    *puVar5 = 0;
    puVar5 = puVar5 + 1;
    iVar7 = iVar7 + -1;
  } while (iVar7 != 0);
  puVar5 = (undefined4 *)(iVar2 + 0x7a0 + iVar6 * 0x10);
  iVar7 = 0x1d;
  do {
    *puVar5 = 0;
    puVar5 = puVar5 + 1;
    iVar7 = iVar7 + -1;
  } while (iVar7 != 0);
  puVar5 = (undefined4 *)(iVar2 + 0x814 + iVar6 * 0x10);
  iVar7 = 2;
  do {
    *puVar5 = 0;
    puVar5 = puVar5 + 1;
    iVar7 = iVar7 + -1;
  } while (iVar7 != 0);
  iVar7 = 0x80;
  puVar5 = (undefined4 *)(iVar2 + 0x81c + iVar6 * 0x10);
  iVar8 = 0x80;
  do {
    *puVar5 = 0;
    puVar5 = puVar5 + 1;
    iVar8 = iVar8 + -1;
  } while (iVar8 != 0);
  puVar5 = (undefined4 *)(iVar2 + 0xa1c + iVar6 * 0x10);
  iVar8 = 0x80;
  do {
    *puVar5 = 0;
    puVar5 = puVar5 + 1;
    iVar8 = iVar8 + -1;
  } while (iVar8 != 0);
  puVar5 = (undefined4 *)(iVar2 + 0xc1c + iVar6 * 0x10);
  iVar8 = 0x80;
  do {
    *puVar5 = 0;
    puVar5 = puVar5 + 1;
    iVar8 = iVar8 + -1;
  } while (iVar8 != 0);
  puVar5 = (undefined4 *)(iVar2 + 0xe1c + iVar6 * 0x10);
  do {
    *puVar5 = 0;
    puVar5 = puVar5 + 1;
    iVar7 = iVar7 + -1;
  } while (iVar7 != 0);
  puVar5 = (undefined4 *)(iVar2 + 0x101c + iVar6 * 0x10);
  iVar7 = 0xc0;
  do {
    *puVar5 = 0;
    puVar5 = puVar5 + 1;
    iVar7 = iVar7 + -1;
  } while (iVar7 != 0);
  puVar5 = (undefined4 *)(iVar2 + 0x131c + iVar6 * 0x10);
  iVar7 = 0x1e0;
  do {
    *puVar5 = 0;
    puVar5 = puVar5 + 1;
    iVar7 = iVar7 + -1;
  } while (iVar7 != 0);
  puVar5 = (undefined4 *)(iVar2 + 0x1a9c + iVar6 * 0x10);
  local_10 = (undefined4 *)0x88;
  iVar6 = 0x6a7;
  do {
    iVar7 = iVar6;
    *puVar5 = 0x10700ff9;
    puVar5[1] = 0x436086c;
    puVar5[2] = &LAB_000c001b;
    puVar5[3] = 0;
    puVar5 = puVar5 + 4;
    local_10 = (undefined4 *)((int)local_10 + -1);
    iVar6 = iVar7 + 4;
  } while (local_10 != (undefined4 *)0x0);
  local_10 = (undefined4 *)0x300;
  local_8 = (undefined4 *)(iVar2 + (iVar4 + iVar7 + 4) * 4);
  do {
    local_10 = (undefined4 *)((int)local_10 + -1);
    *local_8 = 0;
    local_8 = local_8 + 1;
  } while (local_10 != (undefined4 *)0x0);
  local_14 = 0x68;
  local_10 = (undefined4 *)(iVar2 + (iVar4 + iVar7 + 0x304) * 4);
  do {
    local_14 = local_14 + -1;
    *local_10 = 0;
    local_10 = local_10 + 1;
  } while (local_14 != 0);
  local_14 = 0xd0;
  local_10 = (undefined4 *)(iVar2 + (iVar4 + iVar7 + 0x36c) * 4);
  do {
    local_14 = local_14 + -1;
    *local_10 = 0;
    local_10 = local_10 + 1;
  } while (local_14 != 0);
  local_14 = 4;
  local_10 = (undefined4 *)(iVar2 + (iVar4 + iVar7 + 0x43c) * 4);
  do {
    local_14 = local_14 + -1;
    *local_10 = 0;
    local_10 = local_10 + 1;
  } while (local_14 != 0);
  local_14 = 0x14;
  local_10 = (undefined4 *)(iVar2 + (iVar4 + iVar7 + 0x440) * 4);
  do {
    local_14 = local_14 + -1;
    *local_10 = 0;
    local_10 = local_10 + 1;
  } while (local_14 != 0);
  local_14 = 0xf;
  local_10 = (undefined4 *)(iVar2 + (iVar4 + iVar7 + 0x454) * 4);
  do {
    local_14 = local_14 + -1;
    *local_10 = 0;
    local_10 = local_10 + 1;
  } while (local_14 != 0);
  local_14 = 0xe;
  local_10 = (undefined4 *)(iVar2 + (iVar4 + iVar7 + 0x463) * 4);
  do {
    local_14 = local_14 + -1;
    *local_10 = 0;
    local_10 = local_10 + 1;
  } while (local_14 != 0);
  local_14 = 0x44;
  local_10 = (undefined4 *)(iVar2 + (iVar4 + iVar7 + 0x471) * 4);
  do {
    local_14 = local_14 + -1;
    *local_10 = 0;
    local_10 = local_10 + 1;
  } while (local_14 != 0);
  local_14 = 0x20;
  local_10 = (undefined4 *)(iVar2 + (iVar4 + iVar7 + 0x4b5) * 4);
  do {
    local_14 = local_14 + -1;
    *local_10 = 0;
    local_10 = local_10 + 1;
  } while (local_14 != 0);
  local_14 = 0xf;
  local_10 = (undefined4 *)(iVar2 + (iVar4 + iVar7 + 0x4d5) * 4);
  do {
    local_14 = local_14 + -1;
    *local_10 = 0;
    local_10 = local_10 + 1;
  } while (local_14 != 0);
  *(undefined4 *)(iVar2 + (iVar7 + 0x4e4 + iVar4) * 4) = 0;
  *(undefined4 *)(iVar2 + (iVar4 + iVar7 + 0xe4) * 4) = 0x3f800000;
  *(undefined4 *)(iVar2 + (iVar4 + iVar7 + 0xe5) * 4) = 0;
  *(undefined4 *)(iVar2 + (iVar4 + iVar7 + 0xe6) * 4) = 0;
  iVar6 = iVar3 * 4;
  *(undefined4 *)(iVar2 + 0x700004 + (iVar7 + 0xe6 + iVar6) * 4) = 0;
  *(undefined4 *)(iVar2 + (iVar4 + iVar7 + 0xf4) * 4) = 0x40000000;
  *(undefined4 *)(iVar2 + (iVar4 + iVar7 + 0xf5) * 4) = 0x3f800000;
  *(undefined4 *)(iVar2 + (iVar4 + iVar7 + 0xf6) * 4) = 0x3f000000;
  *(undefined4 *)(iVar2 + 0x700004 + (iVar7 + 0xf6 + iVar6) * 4) = 0;
  *(undefined4 *)(iVar2 + (iVar4 + iVar7 + 0xf8) * 4) = 0x40000000;
  *(undefined4 *)(iVar2 + (iVar4 + iVar7 + 0xf9) * 4) = 0x3f800000;
  *(undefined4 *)(iVar2 + (iVar4 + iVar7 + 0xfa) * 4) = 0;
  *(undefined4 *)(iVar2 + 0x700004 + (iVar7 + 0xfa + iVar6) * 4) = 0xbf800000;
  *(undefined4 *)(iVar2 + (iVar4 + iVar7 + 0xfc) * 4) = 0;
  *(undefined4 *)(iVar2 + (iVar4 + iVar7 + 0xfd) * 4) = 0xbf800000;
  *(undefined4 *)(iVar2 + (iVar4 + iVar7 + 0xfe) * 4) = 0;
  *(undefined4 *)(iVar2 + 0x700004 + (iVar7 + 0xfe + iVar6) * 4) = 0;
  *(undefined4 *)(iVar2 + (iVar4 + iVar7 + 0xe8) * 4) = 0;
  *(undefined4 *)(iVar2 + (iVar4 + iVar7 + 0xe9) * 4) = 0x3f800000;
  *(undefined4 *)(iVar2 + (iVar4 + iVar7 + 0xea) * 4) = 0;
  *(undefined4 *)(iVar2 + 0x700004 + (iVar7 + 0xea + iVar6) * 4) = 0;
  *(undefined4 *)(iVar2 + (iVar4 + iVar7 + 0x100) * 4) = 0;
  *(undefined4 *)(iVar2 + (iVar4 + iVar7 + 0x101) * 4) = 0;
  *(undefined4 *)(iVar2 + (iVar4 + iVar7 + 0x102) * 4) = 0;
  *(undefined4 *)(iVar2 + 0x700004 + (iVar7 + 0x102 + iVar6) * 4) = 0;
  *(undefined4 *)(iVar2 + (iVar4 + iVar7 + 0x35c) * 4) = 0;
  *(undefined4 *)(iVar2 + (iVar4 + iVar7 + 0x35d) * 4) = 0;
  *(undefined4 *)(iVar2 + (iVar4 + iVar7 + 0x35e) * 4) = 0;
  *(undefined4 *)(iVar2 + 0x700004 + (iVar7 + 0x35e + iVar6) * 4) = 0;
  *(undefined4 *)(iVar2 + (iVar4 + iVar7 + 0x344) * 4) = 0;
  *(undefined4 *)(iVar2 + (iVar4 + iVar7 + 0x345) * 4) = 0;
  *(undefined4 *)(iVar2 + (iVar4 + iVar7 + 0x346) * 4) = 0xfe000;
  *(undefined4 *)(iVar2 + 0x700004 + (iVar7 + 0x346 + iVar6) * 4) = 0;
  *(undefined4 *)(iVar2 + (iVar4 + iVar7 + 0x348) * 4) = 0;
  *(undefined4 *)(iVar2 + (iVar4 + iVar7 + 0x349) * 4) = 0;
  *(undefined4 *)(iVar2 + (iVar4 + iVar7 + 0x34a) * 4) = 0;
  *(undefined4 *)(iVar2 + 0x700004 + (iVar7 + 0x34a + iVar6) * 4) = 0;
  *(undefined4 *)(iVar2 + (iVar4 + iVar7 + 0x350) * 4) = 0;
  *(undefined4 *)(iVar2 + (iVar4 + iVar7 + 0x351) * 4) = 0;
  *(undefined4 *)(iVar2 + (iVar4 + iVar7 + 0x352) * 4) = 0;
  *(undefined4 *)(iVar2 + 0x700004 + (iVar7 + 0x352 + iVar6) * 4) = 0;
  *(undefined4 *)(iVar2 + (iVar4 + iVar7 + 0x364) * 4) = 0;
  *(undefined4 *)(iVar2 + (iVar4 + iVar7 + 0x365) * 4) = 0x3f8;
  *(undefined4 *)(iVar2 + (iVar4 + iVar7 + 0x366) * 4) = 0;
  *(undefined4 *)(iVar2 + 0x700004 + (iVar6 + iVar7 + 0x366) * 4) = 0;
  *(char **)(iVar2 + 0x700004 + (iVar7 + 0x43c + iVar6) * 4) = "HALLENGE_WINNOWT";
  *(undefined4 *)(iVar2 + (iVar7 + 0x1c0444 + iVar3 * 4) * 4) = 0x1c527c;
  iVar6 = iVar6 + iVar7 + 0x440;
  *(undefined4 *)(iVar2 + 0x700014 + iVar6 * 4) = 0x1c527c;
  *(undefined4 *)(iVar2 + 0x700018 + iVar6 * 4) = 0x1c527c;
  *(undefined4 *)(iVar2 + 0x70001c + iVar6 * 4) = 0x1c527c;
  *(undefined4 *)(iVar2 + (iVar7 + 0x1c0448 + iVar3 * 4) * 4) = 0x1c527c;
  *(undefined4 *)(iVar2 + 0x700024 + iVar6 * 4) = 0x1c527c;
  *(undefined4 *)(iVar2 + 0x700028 + iVar6 * 4) = 0x1c527c;
  *(undefined4 *)(iVar2 + 0x70002c + iVar6 * 4) = 0x1c527c;
  return;
}




