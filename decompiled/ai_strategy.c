/* ai_strategy.c - Actor strategies (enemy behaviours) */
#include "ai_strategy.h"

void actorStrategy::getAllocDetails(ObjectAllocDetails *param_1)

{
  param_1->entitySize = 0x38;
  param_1->paramsSize = 0x18;
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


actorStrategyVTable * actorStrategy::getVTable(void)

{
  vtable.getAllocDetails = getAllocDetails;
  vtable.ctor = ctor;
  vtable.dtor = FUN_0002b7a0;
  vtable.onMessage = onMessage;
  vtable.update = update;
  vtable.enterState = enterState;
  vtable.leaveState = leaveState;
  return &vtable;
}




undefined4 actorStrategy::ctor(actorStrategy *strategy,actorStrategyParams *params)

{
  strategy->parentActor = params->parent;
  strategy->resetState = params->field2_0xc;
  strategy->newState_ = params->field3_0xe;
  strategy->actorStrategyId = params->field4_0x10;
  strategy->actorStrategyId3 = params->field5_0x12;
  strategy->actorStrategyId4 = params->field6_0x14;
  strategy->actorStrategyId2 = params->field7_0x16;
  FUN_0010f760(&strategy->someFloat,(strategy->parentActor->avatar).tag);
  return 1;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


BOOL actorStrategy::shouldBeDroning(actorStrategy *strategy)

{
  BOOL iVar1;
  
  if ((strategy->parentActor->actorType == Human) ||
     ((strategy->parentActor->node0x93c).prev != (actor_0x93c)0x0)) {
    iVar1 = 1;
  }
  else {
    iVar1 = 0;
  }
  if (ShouldntDroneBools[iVar1] != 0) {
    return 0;
  }
  return (uint)(byte)"\x01"[Game::CheckMoveOn];
}




void actorStrategy::setStrategy(actorStrategy *strategy,actorStrategyOffsetId param_2)

{
  (*strategy->vtable->leaveState)(strategy,strategy->id);
  strategy->id = param_2;
                    // Check mind goals
  actorMind::removeGoals(strategy->parentActor->mind);
  (*strategy->vtable->enterState)(strategy,param_2);
  return;
}




void actorStrategy::enterState(actorStrategy *strategy,actorStrategyOffsetId id)

{
  actorMind *mind;
  MindMemoryTargetWantedToAttack *mem;
  actor *actor;
  
  actor = strategy->parentActor;
  mind = actor->mind;
  switch(id) {
  case ActionEnabledDelay:
    actorMind::setGoalFromScript(mind,"actionenableddelay");
    return;
  default:
    return;
  case Celebrate:
  case CelebrateLoop:
    actorMind::setGoalFromScript(mind,"celebrate");
    return;
  case Coward:
                    // Disabling this causes a crash. Likely a state or input lockup variable
    actor->body->indexInStatsheet = 8;
                    // Disabling this stops the zombie from running away in scullery
    actorMind::setGoalFromScript(mind,"coward");
    return;
  case DroneAction:
    onInCutscene(strategy);
    return;
  case Dying:
    break;
  case ExitExclusionRegion:
    actor->body->indexInStatsheet = 7;
  case Stall:
    strategy->fearCounter = strategy->fearCounter + '\x01';
    return;
  case Worried:
    actorMind::setGoalFromScript(mind,"worried");
    return;
  }
  mind->targetBody = (actorBody *)0x0;
  mem = (MindMemoryTargetWantedToAttack *)mind->memoryHead;
  if (mem != (MindMemoryTargetWantedToAttack *)0x0) {
    while ((mem->header).memId != TargedWantedToAttack) {
      mem = (MindMemoryTargetWantedToAttack *)(mem->header).next;
      if (mem == (MindMemoryTargetWantedToAttack *)0x0) {
        strategy->fearCounter = strategy->fearCounter + '\x01';
        return;
      }
    }
    MindMemory::dtor(mem);
  }
  strategy->fearCounter = strategy->fearCounter + '\x01';
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void actorStrategy::onMessage(actorStrategy *actorStrategy,Message *msg)

{
  actor *act;
  Message *pMVar1;
  actorDroneActionId aVar2;
  actorDroneActionId *paVar3;
  int iVar4;
  DroneAction *action;
  BOOL BVar5;
  Buffer<> *actions;
  actorStrategy *strategyy;
  
  pMVar1 = msg;
  strategyy = actorStrategy;
  act = actorStrategy->parentActor;
  switch((msg->header).msgId) {
  case General_Activate:
    onActivate(actorStrategy);
    return;
  case General_Deactivate:
  case General_Reset:
  case General_Open:
  case General_Close:
  case Avatar_AddToIgnoreList:
  case Avatar_AnimationEvent:
  case Avatar_BreakableHit:
  case Avatar_CutScene_Begin:
  case Avatar_CutScene_End:
  case Avatar_CutScene_SetAnim:
  case Avatar_CutScene_SetPos:
  case Avatar_CutScene_SetRot:
  case Avatar_Deflected:
  case Avatar_DeflectedByActor:
  case Avatar_DeleteRequest:
  case Avatar_DrawListAdd:
  case Avatar_DrawListRemove:
  case Avatar_Explode:
  case Avatar_FxCustomRemoved:
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
  case Avatar_SceneInsert:
  case Actor_AbortState:
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
  case Actor_NoLongerInvulnerable:
  case Actor_PickupContact:
  case Actor_ProjectileHitConnected:
  case Actor_PushOut:
  case Actor_Scooped:
  case Actor_SetNoAttackTimer:
  case Actor_SetSurfaceOverride:
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
  case ActorBody_AttachedWeapon:
  case ActorBody_AttachedProjectile:
  case ActorBody_AttackBoost:
  case ActorBody_HitReactionStateChange:
  case ActorBody_ResolveHitsWallContact:
  case ActorBody_SolidDeflectPole:
  case Background_PostAStarInit:
  case Background_ReregisterDoor:
  case Scene_ActorBandagedUp:
  case Scene_ActorBandageEscape:
  case Scene_ActorDied:
  case Scene_ActorDiedInGhoulyBox:
  case Scene_ActorGrabbedBegin:
  case Scene_ActorGrabbedEnd:
  case Scene_ActorHitDefensive:
  case Scene_ActorInserted:
  case Scene_ActorLostWeapon:
  case Scene_ActorRecoveredFromStun:
  case Scene_ActorRemoved:
  case Scene_ActorScaredBegin:
  case Scene_ActorScaredEnd:
  case Scene_ActorStoppedDroning:
  case Scene_AvatarCreatedFromProjectile:
  case Scene_AvatarInserted:
  case Scene_AvatarRemoved:
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
    break;
  case Actor_AStarLayerChanged:
    if ((act->actorType == Ghoulie_old) && (actorStrategy->fearCounter == '\0')) {
      if ((act->actorType == Human) || ((act->node0x93c).prev != (actor_0x93c)0x0)) {
        iVar4 = 1;
      }
      else {
        iVar4 = 0;
      }
      if ((ShouldntDroneBools[iVar4] == 0) && ("\x01"[Game::CheckMoveOn] != '\0')) {
        actions = act->droneActionsBuf;
        if (actions != (Buffer<> *)0x0) {
          if (actions->size == actions->endOfQueue) {
            paVar3 = (actorDroneActionId *)0x0;
          }
          else {
            paVar3 = (actorDroneActionId *)
                     ((int)&actions->entries->actionId +
                     (uint)actions->currentDroneAction * (uint)actions->valueSize);
          }
          if (*paVar3 != Null) break;
        }
        if (act->mind->targetBody == (actorBody *)0x0) {
          actorMind::removeGoals(act->mind);
          return;
        }
      }
    }
    break;
  case Actor_ActionBegin:
    BVar5 = shouldBeDroning(actorStrategy);
    if ((BVar5 != 0) &&
       ((aVar2 = ::actor::getNextDroneAction(act), aVar2 == Null || (act->isDroning != 0)))) {
      aVar2 = ::actor::getNextDroneAction(act);
      if (aVar2 != Null) {
        ::actor::drone(act);
        if (strategyy->someFloat <= 0.0) {
          setStrategy(strategyy,strategyy->actorStrategyId);
          return;
        }
        setStrategy(strategyy,Stall);
        return;
      }
      iVar4 = FUN_00028c30();
      if ((iVar4 != 0) && (act->actorType == Ghoulie_old)) {
        setStrategy(strategyy,ActionEnabledDelay);
        return;
      }
      setStrategy(strategyy,strategyy->actorStrategyId2);
      return;
    }
    break;
  case Actor_ActionEnd:
    aVar2 = ::actor::getNextDroneAction(act);
    if ((aVar2 == Null) && (strategyy->id != CelebrateLoop)) {
      setStrategy(strategyy,Null);
      return;
    }
    break;
  case Actor_EndDroneAction:
    ::actor::updateDroneAction(act,actorStrategy);
    return;
  case Actor_Reset:
    setStrategy(actorStrategy,actorStrategy->resetState);
    return;
  case Actor_SetDroneAction:
    setDroneAction(actorStrategy,(Actor_SetDroneActionMessage *)msg);
    return;
  case Actor_WithinExclusionRegion:
    if (actorStrategy->fearCounter == '\0') {
      if ((act->actorType == Human) || ((act->node0x93c).prev != (actor_0x93c)0x0)) {
        iVar4 = 1;
      }
      else {
        iVar4 = 0;
      }
      if ((ShouldntDroneBools[iVar4] == 0) && ("\x01"[Game::CheckMoveOn] != '\0')) {
        actions = act->droneActionsBuf;
        if (actions != (Buffer<> *)0x0) {
          if (actions->size == actions->endOfQueue) {
            paVar3 = (actorDroneActionId *)0x0;
          }
          else {
            paVar3 = (actorDroneActionId *)
                     ((int)&actions->entries->actionId +
                     (uint)actions->currentDroneAction * (uint)actions->valueSize);
          }
          if (*paVar3 != Null) break;
        }
        BVar5 = GetAmbienceAudio__(act);
        if (BVar5 != 0) {
          setStrategy(strategyy,ExitExclusionRegion);
          return;
        }
      }
    }
    break;
  case ActorMind_TargetLost:
    BVar5 = GetAmbienceAudio__(act);
    if ((BVar5 != 0) && (strategyy->fearCounter == '\0')) {
      if ((act->actorType == Human) || ((act->node0x93c).prev != (actor_0x93c)0x0)) {
        iVar4 = 1;
      }
      else {
        iVar4 = 0;
      }
      if ((ShouldntDroneBools[iVar4] == 0) && ("\x01"[Game::CheckMoveOn] != '\0')) {
        actions = act->droneActionsBuf;
        if (actions == (Buffer<> *)0x0) {
LAB_0002bf23:
          if ((pMVar1->header).someActor == (actor *)0x0) {
            setStrategy(strategyy,strategyy->actorStrategyId3);
            return;
          }
          setStrategy(strategyy,strategyy->actorStrategyId4);
          return;
        }
        if (actions->size == actions->endOfQueue) {
          paVar3 = (actorDroneActionId *)0x0;
        }
        else {
          paVar3 = (actorDroneActionId *)
                   ((int)&actions->entries->actionId +
                   (uint)actions->currentDroneAction * (uint)actions->valueSize);
        }
        if (*paVar3 == Null) goto LAB_0002bf23;
      }
    }
    break;
  case ActorStrategy_SetStrategyId:
    if (actorStrategy->fearCounter == '\0') {
      if ((act->actorType == Human) || ((act->node0x93c).prev != (actor_0x93c)0x0)) {
        iVar4 = 1;
      }
      else {
        iVar4 = 0;
      }
      if ((ShouldntDroneBools[iVar4] == 0) && ("\x01"[Game::CheckMoveOn] != '\0')) {
        actions = act->droneActionsBuf;
        if (actions == (Buffer<> *)0x0) {
LAB_0002bfcb:
          setStrategy(actorStrategy,*(actorStrategyOffsetId *)&(msg->header).someActor);
          return;
        }
        if (actions->size == actions->endOfQueue) {
          action = (DroneAction *)0x0;
        }
        else {
          action = (DroneAction *)
                   ((int)&actions->entries->actionId +
                   (uint)actions->currentDroneAction * (uint)actions->valueSize);
        }
        if (action->actionId == Null) goto LAB_0002bfcb;
      }
    }
    break;
  case Scene_ActorHit:
    if ((msg[2].header.msgId != Null) && ((msg->header).someActor == act)) {
      FUN_00112a20();
    }
  case Scene_ActorHitInvulnerable:
    onActorHitInvulnerable(strategyy,(pMVar1->header).someActor,pMVar1[1].header.msgId);
    return;
  case Scene_ActorKnockDownHitWall:
    FUN_00138b40(actorStrategy,msg);
    return;
  case Scene_ActorPickedUpWeapon:
    FUN_00138e40(actorStrategy);
    return;
  case Scene_Begin:
    BVar5 = shouldBeDroning(actorStrategy);
    if (BVar5 == 0) {
      actorStrategy = (actorStrategy *)0x27;
      (*((act->avatar).vtable)->onMessage)(act,&actorStrategy);
      return;
    }
    break;
  case Scene_WeaponDestroyed:
    FUN_00138ef0(msg);
    break;
  default:
    goto LAB_0002c054;
  }
LAB_0002c054:
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void actorStrategy::update(actorStrategy *strategy)

{
  actor *av;
  int iVar1;
  BOOL BVar2;
  float *extraout_EDX;
  actorMind *mind;
  
  av = strategy->parentActor;
  mind = av->mind;
  switch(strategy->id) {
  case Null:
    InputHandlerBase::init(av->input_handler_);
    return;
  case ActionEnabledDelay:
  case Coward:
    if ((mind->actionInfo).next == (actorGoalInfo *)0x0) {
LAB_0002c19a:
      setStrategy(strategy,strategy->actorStrategyId2);
      return;
    }
    break;
  case Celebrate:
  case Worried:
    if ((mind->actionInfo).next == (actorGoalInfo *)0x0) {
      setStrategy(strategy,strategy->newState_);
    }
    break;
  case CelebrateLoop:
                    // If we are currently celebrating and the mind isn't, tell that mf to celebrate
    if ((mind->actionInfo).next == (actorGoalInfo *)0x0) {
      actorMind::setGoalFromScript(mind,"celebrate");
      return;
    }
    break;
  case DroneAction:
                    // Exit cutscene?
    updateDuringCutscene(strategy);
    return;
  case ExitExclusionRegion:
    if ((mind->targetBody != (actorBody *)0x0) &&
       (iVar1 = FUN_00141760(av->field812_0xca4,mind->targetBody), iVar1 != 0)) {
      mind->targetBody = (actorBody *)0x0;
    }
    if ((mind->actionInfo).next == (actorGoalInfo *)0x0) {
      iVar1 = FUN_0013a0f0(strategy);
    }
    else {
      iVar1 = FUN_0013a2a0();
    }
    if (iVar1 != 0) {
      FUN_0002b540();
      BVar2 = GetAmbienceAudio__(av);
      if (BVar2 == 0) {
        setStrategy(strategy,Null);
        return;
      }
      goto LAB_0002c19a;
    }
    break;
  case Stall:
    avatar::decreaseTimer(&av->avatar,&strategy->someFloat);
    if (*extraout_EDX == 0.0) {
      setStrategy(strategy,strategy->actorStrategyId);
      return;
    }
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void actorStrategy::leaveState(actorStrategy *strategy,actorStrategyOffsetId newState)

{
  if (((newState == Dying) || (newState == ExitExclusionRegion)) || (newState == Stall)) {
    strategy->fearCounter = strategy->fearCounter + 0b11111111;
  }
  return;
}




BOOL actorStrategy::setDroneAction(actorStrategy *strategy,Actor_SetDroneActionMessage *msg)

{
  actor *paVar1;
  BOOL BVar2;
  DroneAction *action;
  actorDroneActionId id;
  Buffer<> *drone_data;
  
  paVar1 = strategy->parentActor;
  drone_data = paVar1->droneActionsBuf;
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
  ::actor::addDroneAction(paVar1,msg->droneAction,msg[4].msgId);
  if (id != Null) {
    return 1;
  }
  BVar2 = ::actor::CleanupBadDroneAction(paVar1,strategy);
  return BVar2;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void actorStrategy::onInCutscene(actorStrategy *strategy)

{
  actor *act;
  actorMind *mind;
  DroneAction *puVar1;
  uint uVar1;
  ActorGoal46 *iVar4;
  BOOL BVar2;
  int iVar3;
  DroneAction *entry;
  actorDroneActionId uVar4;
  float local_10;
  vec3 somePos;
  Buffer<> *drone_data;
  Buffer<> *compp;
  
  act = strategy->parentActor;
  if (act->derivedMarkerValue == (DerivedMarkerValue *)0x0) {
    mind = act->mind;
    act->body->indexInStatsheet = 7;
    drone_data = act->droneActionsBuf;
    if (drone_data == (Buffer<> *)0x0) {
      uVar4 = Null;
    }
    else {
      if (drone_data->size == drone_data->endOfQueue) {
        entry = (DroneAction *)0x0;
      }
      else {
        entry = (DroneAction *)
                ((int)&drone_data->entries->actionId +
                (uint)drone_data->currentDroneAction * (uint)drone_data->valueSize);
      }
      uVar4 = entry->actionId;
    }
    compp = act->droneActionsBuf;
    if (compp != (Buffer<> *)0x0) {
      if (compp->size == compp->endOfQueue) {
        puVar1 = (DroneAction *)0x0;
      }
      else {
        puVar1 = (DroneAction *)
                 ((int)&compp->entries->actionId +
                 (uint)compp->currentDroneAction * (uint)compp->valueSize);
      }
      somePos.x = (puVar1->pos).x;
      somePos.y = (puVar1->pos).y;
      somePos.z = (puVar1->pos).z;
    }
    switch(uVar4) {
    case WalkToDest:
    case WalkToDestNotScared:
    case WalkToDestThenDelete:
      iVar3 = actorMind::newGoal46(mind,&somePos);
      uVar1 = ::actor::searchSomeComponent(act);
      if ((uVar1 != 0) || (act->field_0x989 != '\0')) {
        *(undefined4 *)(iVar3 + 0x28) = 0;
        return;
      }
      break;
    case WalkToDestThenTaunt:
      iVar4 = (ActorGoal46 *)actorMind::newGoal46(mind,&somePos);
      uVar1 = ::actor::searchSomeComponent(act);
      if ((uVar1 != 0) || (act->field_0x989 != '\0')) {
        iVar4->field8_0x28 = 0.0;
      }
      avatar::findTarget(&mind->actor->avatar,mind->actor->field812_0xca4,Null,Null,&local_10,
                         mind->field37_0x68,mind->flags & 0xffffffdf | 8);
      FUN_0002a030();
                    // If taunt fails, then celebrate instead
      BVar2 = actorMind::setGoalFromScript(mind,"taunt");
      if (BVar2 == 0) {
        actorMind::setGoalFromScript(mind,"celebrate");
        return;
      }
      break;
    case WalkToDestNoDecel:
      iVar3 = actorMind::newGoal46(mind,&somePos);
      *(undefined4 *)(iVar3 + 0x28) = 0;
    }
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


undefined4 actorStrategy::updateDuringCutscene(actorStrategy *strategy)

{
  actor *act;
  short pfVar5;
  actorDroneActionId drone_id;
  int iVar1;
  undefined4 uVar2;
  uint uVar3;
  undefined1 local_4 [4];
  Buffer<> *drone_data;
  DroneAction *entry;
  actorMind *mind;
  
  act = strategy->parentActor;
  mind = act->mind;
                    // Might be handling "did cutscene just end?"
  if (act->derivedMarkerValue == (DerivedMarkerValue *)0x0) {
    uVar3 = ::actor::updateDuringCutscene(act);
    if (uVar3 != 0) {
                    // Disablign this stops cooper freaking out during cutscene, but breaks input
                    // after cutscene
      uVar2 = ::actor::updateDroneAction(act,strategy);
      return uVar2;
    }
    drone_data = act->droneActionsBuf;
    if (drone_data == (Buffer<> *)0x0) {
      drone_id = Null;
    }
    else {
      if (drone_data->size == drone_data->endOfQueue) {
        entry = (DroneAction *)0x0;
      }
      else {
        entry = (DroneAction *)
                ((int)&drone_data->entries->actionId +
                (uint)drone_data->currentDroneAction * (uint)drone_data->valueSize);
      }
      drone_id = entry->actionId;
    }
    if (drone_id == WaitForScare) {
      if ((mind->actionInfo).next == (actorGoalInfo *)0x0) {
        actorMind::setGoalFromScript(mind,"drone_waitforscare");
      }
    }
    else if (((drone_id == CelebrateLoop) || (drone_id == CelebrateLoopVulnerable)) &&
            ((mind->actionInfo).next == (actorGoalInfo *)0x0)) {
      actorMind::setGoalFromScript(mind,"celebrate");
      return 0;
    }
  }
  else {
    FUN_0013d400(act);
    iVar1 = FUN_00139e90(local_4);
    if (iVar1 != 0) {
      iVar1 = FUN_000285b0();
      if (iVar1 != 0) {
        uVar2 = FUN_001414c0();
        FUN_00135700(uVar2);
        FUN_00028580();
        FUN_001391d0(act,strategy);
        FUN_00028150();
        return 0;
      }
    }
  }
  return 0;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void actorStrategy::onActivate(actorStrategy *param_1)

{
  actor *act_00;
  Buffer<> *pBVar1;
  uint uVar2;
  actorBody *paVar3;
  undefined4 uVar4;
  actorDroneActionId *drone_action;
  objTag blacklistType;
  objTag whitelistType;
  float local_4;
  actor *act;
  actor *actt;
  actorMind *mindd;
  
  act_00 = param_1->parentActor;
  param_1->someFloat = 0.0;
  pBVar1 = act_00->droneActionsBuf;
  if (pBVar1 != (Buffer<> *)0x0) {
    if (pBVar1->size == pBVar1->endOfQueue) {
      drone_action = (actorDroneActionId *)0x0;
    }
    else {
      drone_action = (actorDroneActionId *)
                     ((int)&pBVar1->entries->actionId +
                     (uint)pBVar1->currentDroneAction * (uint)pBVar1->valueSize);
    }
    if (*drone_action != Null) {
      mindd = act_00->mind;
      actt = mindd->actor;
      uVar2 = mindd->flags;
      if ((0.0 < actt->traitorTimer) || (actt->randTraitoristicCombat != '\0')) {
        uVar2 = uVar2 & 0xfffffffb | 0x10;
      }
      local_4 = (float)(uVar2 & 0xffffffdf | 8);
      if (((actt->traitorTimer <= 0.0) && (actt->randTraitoristicCombat == '\0')) ||
         (blacklistType = actt->objTagTypeIndex2, blacklistType < Actor_Baron)) {
        blacklistType = Null;
      }
      if (((actt->traitorTimer <= 0.0) && (actt->randTraitoristicCombat == '\0')) ||
         (whitelistType = actt->objTagTypeIndex, whitelistType < Actor_Baron)) {
        whitelistType = Null;
      }
      paVar3 = avatar::findTarget(&actt->avatar,actt->field812_0xca4,whitelistType,blacklistType,
                                  &local_4,mindd->field37_0x68,local_4);
      if ((paVar3 != (actorBody *)0x0) ||
         (((0.0 < act_00->traitorTimer || (act_00->randTraitoristicCombat != '\0')) &&
          (paVar3 = avatar::findTarget(&mindd->actor->avatar,mindd->actor->field812_0xca4,Null,Null,
                                       &local_4,mindd->field37_0x68,mindd->flags & 0xffffffdf | 8),
          paVar3 != (actorBody *)0x0)))) {
        FUN_0002a030();
        if (*(char *)&paVar3->largeProjectile == '\0') {
          mindd->targetActor = (actor *)paVar3->currentWeapon;
        }
        if (act_00->derivedMarkerValue != (DerivedMarkerValue *)0x0) {
          uVar4 = FUN_001414c0();
          FUN_00135700(uVar4);
          FUN_00028580();
          FUN_001391d0(act_00,param_1);
          FUN_00028150();
          return;
        }
        uVar4 = FUN_001414c0();
        FUN_00135700(uVar4);
        FUN_00028580();
        ::actor::updateDroneAction(act_00,param_1);
      }
    }
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void actorStrategy::onActorHitInvulnerable(actorStrategy *strat,actor *inAct,actor *param_3)

{
  actor *act;
  Buffer<> *pBVar1;
  actorMind *paVar2;
  actorDroneActionId *paVar3;
  undefined4 uVar4;
  int iVar5;
  HitReactionResource *hitReactionRes;
  
  act = strat->parentActor;
  if (((inAct == act) && (param_3 != (actor *)0x0)) &&
     (pBVar1 = act->droneActionsBuf, pBVar1 != (Buffer<> *)0x0)) {
    if (pBVar1->size == pBVar1->endOfQueue) {
      paVar3 = (actorDroneActionId *)0x0;
    }
    else {
      paVar3 = (actorDroneActionId *)
               ((int)&pBVar1->entries->actionId +
               (uint)pBVar1->currentDroneAction * (uint)pBVar1->valueSize);
    }
    if ((((*paVar3 != Null) && (act->derivedMarkerValue != (DerivedMarkerValue *)0x0)) &&
        ((hitReactionRes = act->body->hitReactionRes, hitReactionRes == (HitReactionResource *)0x0
         || (hitReactionRes->someBool != '\0')))) &&
       ((act->droneTriggerId != DJ && ((param_3->avatar).as23ptr != (astruct_23 *)0x0)))) {
      uVar4 = FUN_001414c0();
      FUN_00135700(uVar4);
      iVar5 = FUN_00042070();
      if (iVar5 != 0) {
        paVar2 = act->mind;
        FUN_0002a030();
        paVar2->targetActor = param_3;
      }
      FUN_00028580();
      FUN_001391d0(act,strat);
    }
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


undefined4 actorStrategy::onEventCompleted(actorStrategy *param_1)

{
  actor *paVar1;
  Buffer<> *pBVar2;
  int iVar3;
  actorDroneActionId *paVar4;
  
  paVar1 = param_1->parentActor;
  if (param_1->fearCounter == '\0') {
    if ((paVar1->actorType == Human) || ((paVar1->node0x93c).prev != (actor_0x93c)0x0)) {
      iVar3 = 1;
    }
    else {
      iVar3 = 0;
    }
    if ((ShouldntDroneBools[iVar3] == 0) && ("\x01"[Game::CheckMoveOn] != '\0')) {
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
      if (((paVar1->body->field13_0x30 == 0) && (paVar1->body->someTimer2 == 0.0)) &&
         (runtime::rand = runtime::rand * 0x19660d + 0x3c6ef35f,
         (float)(runtime::rand & 0x7fffff | 0x3f800000) - 1.0 <= 1.0)) {
        setStrategy(param_1,Worried);
        return 1;
      }
    }
  }
  return 0;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


undefined4 actorStrategy::onEventFailed(actorStrategy *param_1)

{
  actor *paVar1;
  Buffer<> *pBVar2;
  int iVar3;
  actorDroneActionId *paVar4;
  
  if (param_1->fearCounter == '\0') {
    paVar1 = param_1->parentActor;
    if ((paVar1->actorType == Human) || ((paVar1->node0x93c).prev != (actor_0x93c)0x0)) {
      iVar3 = 1;
    }
    else {
      iVar3 = 0;
    }
    if ((ShouldntDroneBools[iVar3] == 0) && ("\x01"[Game::CheckMoveOn] != '\0')) {
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
      if (((paVar1->body->field13_0x30 == 0) && (paVar1->body->someTimer2 == 0.0)) &&
         (runtime::rand = runtime::rand * 0x19660d + 0x3c6ef35f,
         (float)(runtime::rand & 0x7fffff | 0x3f800000) - 1.0 <= 1.0)) {
        setStrategy(param_1,Celebrate);
        return 1;
      }
    }
  }
  return 0;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


BOOL actorStrategy::updateAndGetTarget(actorStrategy *strat,actorBody **targetBody,BOOL someFlag)

{
  actorMind *mind;
  actor *av;
  MindMemoryTargetWantedToAttack *mem;
  uint uVar1;
  actorBody *target_body;
  MindMemoryTargetWantedToAttack *new_memory;
  objTag oVar2;
  objTag whitelistType;
  actor *act;
  Message targetLostMessage;
  
  act = strat->parentActor;
  mind = act->mind;
  target_body = mind->targetBody;
  if (someFlag == 0) {
    if (target_body != (actorBody *)0x0) {
      oVar2 = (act->avatar).tag;
      if ((((*(char *)&target_body->largeProjectile == '\0') &&
           (uVar1 = *(uint *)&target_body->currentWeapon->field_0xca8, uVar1 != 0)) &&
          (uVar1 != act->field812_0xca4)) &&
         (((oVar2 == Null || (*(objTag *)(uVar1 + 0x1c) == Null)) ||
          (*(objTag *)(uVar1 + 0x1c) == oVar2)))) {
        someFlag = 1;
      }
      goto LAB_00139cc7;
    }
LAB_00139cd3:
    av = mind->actor;
    uVar1 = mind->flags;
    if ((0.0 < av->traitorTimer) || (av->randTraitoristicCombat != '\0')) {
      uVar1 = uVar1 & 0xfffffffb | 0x10;
    }
    if (((av->traitorTimer <= 0.0) && (av->randTraitoristicCombat == '\0')) ||
       (oVar2 = av->objTagTypeIndex2, oVar2 < Actor_Baron)) {
      oVar2 = Null;
    }
    if (((av->traitorTimer <= 0.0) && (av->randTraitoristicCombat == '\0')) ||
       (whitelistType = av->objTagTypeIndex, whitelistType < Actor_Baron)) {
      whitelistType = Null;
    }
    target_body = avatar::findTarget(&av->avatar,av->field812_0xca4,whitelistType,oVar2,
                                     (float *)&targetLostMessage,mind->field37_0x68,
                                     uVar1 & 0xffffffdf | 8);
    if (target_body == (actorBody *)0x0) {
      if ((0.0 < act->traitorTimer) || (act->randTraitoristicCombat != '\0')) {
        target_body = avatar::findTarget(&mind->actor->avatar,mind->actor->field812_0xca4,Null,Null,
                                         (float *)&act,mind->field37_0x68,mind->flags);
        if ((target_body == (actorBody *)0x0) ||
           (((float)mind->floatFromTagList <= 0.0 ||
            ((float)act < (float)mind->floatFromTagList ||
             (float)act == (float)mind->floatFromTagList)))) {
          if (target_body != (actorBody *)0x0) goto LAB_00139e0b;
        }
        else {
          target_body = (actorBody *)0x0;
        }
      }
      if (mind->targetBody != (actorBody *)0x0) {
        targetLostMessage.header.msgId = ActorMind_TargetLost;
        targetLostMessage.header.someActor = (actor *)0x0;
        (*((mind->actor->avatar).vtable)->onMessage)(mind->actor,&targetLostMessage);
      }
    }
LAB_00139e0b:
    mind->targetBody = target_body;
    if (target_body == (actorBody *)0x0) {
      for (mem = (MindMemoryTargetWantedToAttack *)mind->memoryHead;
          mem != (MindMemoryTargetWantedToAttack *)0x0;
          mem = (MindMemoryTargetWantedToAttack *)(mem->header).next) {
        if ((mem->header).memId == TargedWantedToAttack) {
          MindMemory::dtor(mem);
          break;
        }
      }
      mind->targetActor = (actor *)0x0;
      goto LAB_00139e70;
    }
    FUN_0002a0c0();
  }
  else {
LAB_00139cc7:
    if ((target_body == (actorBody *)0x0) || (someFlag != 0)) goto LAB_00139cd3;
  }
  new_memory = (MindMemoryTargetWantedToAttack *)actorMind::addMemory(mind,TargedWantedToAttack,0.5)
  ;
  new_memory->targetBody = target_body;
  if (*(char *)&target_body->largeProjectile == '\0') {
    mind->targetActor = (actor *)target_body->currentWeapon;
    *targetBody = target_body;
    return (uint)(target_body != (actorBody *)0x0);
  }
LAB_00139e70:
  *targetBody = target_body;
  return (uint)(target_body != (actorBody *)0x0);
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


BOOL actorStrategy::canPlayIntro(actorStrategy *strategy,uint param_2)

{
  actor *act;
  Buffer<> *pBVar1;
  actorBody *body;
  
  act = strategy->parentActor;
  body = act->body;
  if ((body->health == 0) && (body->maxHealth != 0)) {
    return 0;
  }
  pBVar1 = act->droneActionsBuf;
  if (pBVar1 != (Buffer<> *)0x0) {
    if (pBVar1->size == pBVar1->endOfQueue) {
      body = (actorBody *)0x0;
    }
    else {
      body = (actorBody *)
             ((int)&pBVar1->entries->actionId +
             (uint)pBVar1->currentDroneAction * (uint)pBVar1->valueSize);
    }
    if (*(actorDroneActionId *)&body->vtable != Null) {
      return 0;
    }
  }
  FUN_000f4870(act,body,param_2);
  return 1;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


BOOL actorStrategy::checkAndSetDying(actorStrategy *strategy)

{
  actorBody *body;
  
  body = strategy->parentActor->body;
  if ((body->health == 0) && (body->maxHealth != 0)) {
    if ((strategy->id != Null) && (strategy->id != Dying)) {
      ::actor::drone(strategy->parentActor);
      strategy->actorStrategyId2 = Dying;
      strategy->actorStrategyId3 = Dying;
      strategy->actorStrategyId4 = Dying;
      setStrategy(strategy,Dying);
    }
    return 1;
  }
  return 0;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void actorStrategy::forceIntro(actorStrategy *strategy,undefined4 param_2)

{
  actorBody *paVar1;
  BOOL BVar2;
  actorBody *local_4;
  
  paVar1 = strategy->parentActor->mind->targetBody;
  BVar2 = updateAndGetTarget(strategy,&local_4,0);
  if (BVar2 != 0) {
    BVar2 = canPlayIntro(strategy,param_2);
    if ((BVar2 == 0) && (paVar1 == (actorBody *)0x0)) {
      strategy->parentActor->mind->targetBody = (actorBody *)0x0;
    }
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


