/* weapon.c - Weapons, projectiles, extinguishers, wield logic */
#include "weapon.h"

BOOL entityWeaponProjectileHome::hasAudioEntry(char *param_1)

{
  BOOL BVar1;
  
  if (*param_1 == '\0') {
    return 0;
  }
  BVar1 = Audio::QueryAudioByXACTName(param_1,(uint *)0x0,(uint *)0x0);
  return BVar1;
}




void switchD_000c6114::caseD_10(weapon *param_1)

{
  FUN_00144d00(param_1);
  return;
}




void entityWeaponExtinguisher::initProjectiles(entityWeaponExtinguisher *param_1)

{
  Buffer<> *puVar1;
  
  puVar1 = malloc_(0x710);
  puVar1->head = puVar1->values;
  puVar1->tail = puVar1->values;
  puVar1->end = (ExtinguisherThing *)(puVar1 + 1);
  puVar1->valueSize = 0x38;
  puVar1->capacity = 0x20;
  param_1->particles = puVar1;
  param_1->someProjectilesNumber = 0.0;
  return;
}



// WARNING: Inlined function: FUN_000c8d30
// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void entityWeaponExtinguisher::updateParticleLists(entityWeaponExtinguisher *param_1)

{
  Buffer<> *mem;
  undefined4 uVar1;
  int iVar2;
  Buffer<> **ppBVar3;
  HeapTableEntry *pHVar4;
  
  mem = param_1->particles;
  if (mem != (Buffer<> *)0x0) {
    if (((int)mem->tail - (int)mem->head) / (int)(uint)mem->valueSize == 0) {
      free(mem);
      param_1->particles = (Buffer<> *)0x0;
    }
    else {
      iVar2 = 0;
      ppBVar3 = param_1->particleLists;
      do {
        if (*ppBVar3 == (Buffer<> *)0x0) {
          param_1->particleLists[iVar2] = mem;
          param_1->particles = (Buffer<> *)0x0;
          return;
        }
        iVar2 = iVar2 + 1;
        ppBVar3 = ppBVar3 + 1;
      } while (iVar2 < 8);
      iVar2 = FindHeapOf(mem);
      uVar1 = runtime::CurrentHeapToAllocateFrom;
      if (g_HeapTableBase[iVar2].heapHandle == (HANDLE)0x0) {
        pHVar4 = (HeapTableEntry *)0x0;
      }
      else {
        pHVar4 = g_HeapTableBase + iVar2;
      }
      runtime::CurrentHeapToAllocateFrom = iVar2;
      XAPILIB::HeapFree(pHVar4->heapHandle,0,mem);
      runtime::CurrentHeapToAllocateFrom = uVar1;
      param_1->particles = (Buffer<> *)0x0;
    }
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void entityWeaponExtinguisher::updateParticles2(entityWeaponExtinguisher *param_1,float dt)

{
  Buffer<> *mem;
  undefined4 uVar1;
  bool bVar2;
  undefined3 extraout_var;
  undefined3 extraout_var_00;
  int iVar3;
  HeapTableEntry *pHVar4;
  int i;
  Buffer<> **ppBVar5;
  
  param_1->ammo = param_1->field143_0xee8 * 0.135 + 0.015;
  if (param_1->particles != (Buffer<> *)0x0) {
    bVar2 = updateParticles(param_1->particles,dt);
    if ((CONCAT31(extraout_var,bVar2) == 0) && (*(int *)&param_1->field_0xe54 == 0)) {
      free(param_1->particles);
      param_1->particles = (Buffer<> *)0x0;
    }
  }
  ppBVar5 = param_1->particleLists;
  i = 8;
  do {
    if (*ppBVar5 != (Buffer<> *)0x0) {
      bVar2 = updateParticles(*ppBVar5,dt);
      if (CONCAT31(extraout_var_00,bVar2) == 0) {
        mem = *ppBVar5;
        iVar3 = FindHeapOf(mem);
        uVar1 = runtime::CurrentHeapToAllocateFrom;
        if (g_HeapTableBase[iVar3].heapHandle == (HANDLE)0x0) {
          pHVar4 = (HeapTableEntry *)0x0;
        }
        else {
          pHVar4 = g_HeapTableBase + iVar3;
        }
        runtime::CurrentHeapToAllocateFrom = iVar3;
        XAPILIB::HeapFree(pHVar4->heapHandle,0,mem);
        runtime::CurrentHeapToAllocateFrom = uVar1;
        *ppBVar5 = (Buffer<> *)0x0;
      }
    }
    ppBVar5 = ppBVar5 + 1;
    i = i + -1;
  } while (i != 0);
  return;
}




void entityWeaponWaterPistol::getVTable(void)

{
  FUN_000ca990((AvatarVTable *)&ObjectFullVTable_00506278);
  ObjectFullVTable_00506278.getAllocDetails = FUN_000c91f0;
  ObjectFullVTable_00506278.ctor = FUN_000c9280;
  ObjectFullVTable_00506278.dtor = &LAB_000c9330;
  ObjectFullVTable_00506278.func19 = FUN_000c9410;
  ObjectFullVTable_00506278.func20 = FUN_000c9540;
  ObjectFullVTable_00506278.func21 = &LAB_000c95f0;
  ObjectFullVTable_00506278.func22 = FUN_000ca1f0;
  ObjectFullVTable_00506278.func23 = &LAB_000c98d0;
  _DAT_005062d8 = FUN_000c9b20;
  return;
}




void entityWeaponGun::getVTable(void)

{
  FUN_000ca990(&AvatarVTable_005062e0);
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void entityWeaponGun::onMessage(entityWeaponGun *param_1,Message *param_2)

{
  AvatarVTable *pAVar1;
  actor *paVar2;
  int iVar3;
  vec3 local_18;
  vec3 local_c;
  
  switch((param_2->header).msgId) {
  case Actor_WeaponHitConnected:
    if (param_2[5].header.someActor != (actor *)0x0) {
      *(undefined4 *)&param_1->field_0xef4 = 1;
      ::weapon::onMessage(&param_1->weapon,param_2);
      return;
    }
    break;
  case Actor_WithinScareRadius:
  case Actor_WeaponScoopComplete:
  case Actor_WithinExclusionRegion:
  case ActorBody_AttachedWeapon:
  case ActorBody_AttachedProjectile:
  case ActorBody_AttackBoost:
  case ActorBody_HitReactionStateChange:
  case ActorBody_ResolveHitsWallContact:
  case ActorBody_SolidDeflectPole:
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
  case Scene_AvatarInserted:
  case Scene_AvatarRemoved:
  case Scene_Begin:
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
  case Weapon_PushOutDelta:
  case Weapon_Scooped:
    break;
  case Weapon_Attached:
    ::weapon::onSignal(&param_1->weapon,Attached);
    ::weapon::onMessage(&param_1->weapon,param_2);
    return;
  case Weapon_AttackVolumeEnabled:
    if ((param_2->header).someActor != (actor *)0x0) {
      *(undefined4 *)&param_1->field_0xef4 = 0;
      ::weapon::onMessage(&param_1->weapon,param_2);
      return;
    }
    break;
  case Weapon_PreDetach:
    ::weapon::onSignal(&param_1->weapon,PostDetach);
    ::weapon::onMessage(&param_1->weapon,param_2);
    return;
  case Weapon_QueryAim:
    paVar2 = (actor *)FUN_000cb330(param_2 + 1,param_1,(vec3 *)&param_2[2].header.someActor);
    (param_2->header).someActor = paVar2;
    ::weapon::onMessage(&param_1->weapon,param_2);
    return;
  case Weapon_SetStreamStrength:
    *(actor **)&param_1->field_0xee8 = (param_2->header).someActor;
    ::weapon::onMessage(&param_1->weapon,param_2);
    return;
  case Weapon_ShootBegin:
    FUN_00041d00();
    pAVar1 = (param_1->weapon).avatar.vtable;
    *(undefined4 *)&param_1->field_0xe54 = 1;
    if ((pAVar1[1].update != (void *)0x0) &&
       (iVar3 = FUN_000cb330(&local_c,param_1,&local_18), iVar3 != 0)) {
      (*(param_1->weapon).avatar.vtable[1].update)(param_1,&local_c,&local_18,param_2 + 1);
LAB_000cacf9:
      *(undefined4 *)&param_1->field_0xef8 = 0;
    }
    break;
  case Weapon_ShootEnd:
    FUN_0012a3d0((astruct_25 *)&(param_1->weapon).avatar.model0x9s[3].field_0xb0);
    FUN_00146230();
    pAVar1 = (param_1->weapon).avatar.vtable;
    *(undefined4 *)&param_1->field_0xe54 = 0;
    if ((pAVar1[1].draw != (void *)0x0) &&
       (iVar3 = FUN_000cb330(&local_18,param_1,&local_c), iVar3 != 0)) {
      (*(param_1->weapon).avatar.vtable[1].draw)(param_1,&local_18,&local_c);
      goto LAB_000cacf9;
    }
    break;
  default:
    goto switchD_000cab65_default;
  }
switchD_000cab65_default:
  ::weapon::onMessage(&param_1->weapon,param_2);
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void entityWeaponProjectile::getAllocDetails(undefined4 *param_1)

{
  *param_1 = 0xf70;
  param_1[1] = 0x6a0;
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void entityWeaponProjectile::getVTable(void)

{
  avatar::initVTable((AvatarVTable *)PTR_ARRAY_00506348);
  PTR_ARRAY_00506348[5] = ::weapon::func5;
  PTR_ARRAY_00506348[4] = ::weapon::update;
  PTR_ARRAY_00506348[0x12] = switchD_000d4179::EmptyFunction;
  PTR_ARRAY_00506348[0] = getAllocDetails;
  PTR_ARRAY_00506348[1] = ctor;
  PTR_ARRAY_00506348[2] = dtor;
  PTR_ARRAY_00506348[3] = onMessage;
  PTR_ARRAY_00506348[0xf] = func15;
  PTR_ARRAY_00506348[0x10] = func16;
  PTR_ARRAY_00506348[0x11] = func17;
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


undefined4 entityWeaponProjectile::ctor(avatar *param_1,int param_2)

{
  char cVar1;
  int iVar2;
  AnimEventMapping *pAVar3;
  char *pcVar4;
  
  *(code **)&param_1[1].field_0x68 = FUN_000cbf80;
  pAVar3 = avatar::getAnimEventByName(param_1,*(char **)(param_2 + 0x5f8),0);
  *(AnimEventMapping **)(param_1[1].model0x9s[2].audioID + 0x7c) = pAVar3;
  *(undefined4 *)&param_1[1].model0x9s[2].field_0x88 = *(undefined4 *)(param_2 + 0x690);
  *(undefined4 *)&param_1[1].model0x9s[2].field_0x90 = *(undefined4 *)(param_2 + 0x67c);
  *(undefined4 *)(param_1[1].model0x9s[3].audioID + 0x78) = *(undefined4 *)(param_2 + 0x68c);
  *(undefined4 *)(param_1[1].model0x9s[3].audioID + 0x7c) = *(undefined4 *)(param_2 + 0x698);
  *(undefined4 *)&param_1[1].model0x9s[3].field_0x88 = *(undefined4 *)(param_2 + 0x69c);
  *(undefined4 *)(param_1[1].model0x9s[3].audioID + 0x60) = *(undefined4 *)(param_2 + 0x680);
  *(undefined4 *)(param_1[1].model0x9s[3].audioID + 100) = *(undefined4 *)(param_2 + 0x684);
  pcVar4 = (char *)(param_2 + 0x5fc);
  *(undefined4 *)(param_1[1].model0x9s[3].audioID + 0x68) = *(undefined4 *)(param_2 + 0x688);
  iVar2 = 0xe80 - (int)pcVar4;
  do {
    cVar1 = *pcVar4;
    pcVar4[(int)param_1 + iVar2] = cVar1;
    pcVar4 = pcVar4 + 1;
  } while (cVar1 != '\0');
  *(undefined4 *)&param_1[1].model0x9s[3].field_0xb0 = *(undefined4 *)(param_2 + 0x694);
  return 1;
}




void entityWeaponProjectile::dtor(int param_1)

{
  if (*(int *)(param_1 + 0xf40) != 0) {
    FUN_0013ee80();
    free(*(void **)(param_1 + 0xf40));
    *(undefined4 *)(param_1 + 0xf40) = 0;
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void entityWeaponProjectile::func17(entityWeaponProjectile *param_1,undefined4 param_2)

{
  int iVar1;
  objParams local_354 [103];
  undefined1 local_18;
  undefined4 local_8;
  undefined4 local_4;
  
  switch((undefined2)param_2) {
  case 2:
    FUN_000cc910();
    ::weapon::func17(&param_1->weapon,(undefined2)param_2);
    FUN_000cc210();
    return;
  case 3:
    break;
  case 4:
    iVar1 = FUN_000cc530();
    if (iVar1 != 0) {
      (param_1->weapon).arcContactValue = 0xb;
      return;
    }
    break;
  default:
    ::weapon::func17(&param_1->weapon,(undefined2)param_2);
    break;
  case 9:
    iVar1 = FUN_00040040(param_1);
    if (iVar1 != 0) {
      FUN_00069590(0.5);
      local_18 = *(undefined1 *)((int)&(param_1->weapon).avatar.someInt32 + 3);
      local_4 = 0;
      local_8 = 0;
      Assets::CreateEntityFromParams(local_354);
      avatar::destroy((avatar *)param_1);
      return;
    }
    break;
  case 0xb:
    iVar1 = FUN_00040040(param_1);
    if (iVar1 != 0) {
      FUN_00069590(0.5);
      local_18 = *(undefined1 *)((int)&(param_1->weapon).avatar.someInt32 + 3);
      local_4 = 0;
      local_8 = 0;
      Assets::CreateEntityFromParams(local_354);
      avatar::destroy((avatar *)param_1);
      return;
    }
    break;
  case 0x10:
    FUN_00147430();
    return;
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void entityWeaponProjectile::onMessage(entityWeaponProjectile *wpn,Message *msg)

{
  int iVar1;
  
  switch((msg->header).msgId) {
  case Avatar_Explode:
    ::weapon::onSignal(&wpn->weapon,Destroy);
    ::weapon::onMessage(&wpn->weapon,msg);
    return;
  case Avatar_HitByGunshot:
    msg[2].header.msgId = General_Activate;
    ::actor::executeCallout((actor *)wpn,0,Extinguished);
    (wpn->weapon).arcContactValue = 9;
    break;
  case Actor_ProjectileHitConnected:
    if (msg[5].header.someActor != (actor *)0x0) {
      FUN_000cc430();
      ::weapon::onMessage(&wpn->weapon,msg);
      return;
    }
    break;
  case Scene_AvatarRemoved:
    if (*(Buffer<EDB2Entry> **)&wpn->field_0xf40 != (Buffer<EDB2Entry> *)0x0) {
      Buffer<EDB2Entry>::addAvatarToSet
                (*(Buffer<EDB2Entry> **)&wpn->field_0xf40,&((msg->header).someActor)->avatar);
      ::weapon::onMessage(&wpn->weapon,msg);
      return;
    }
    break;
  case Scene_Begin:
    if ((wpn->weapon).attachState == 0) {
      ::weapon::onSignal(&wpn->weapon,SceneBegun);
      ::weapon::onMessage(&wpn->weapon,msg);
      return;
    }
    break;
  case Weapon_Attached:
    ::weapon::onSignal(&wpn->weapon,Attached);
    ::weapon::onMessage(&wpn->weapon,msg);
    return;
  case Weapon_ArcContact:
    iVar1 = FUN_000cc340(msg);
    if (iVar1 != 0) {
      avatar::destroy((avatar *)wpn);
      return;
    }
    if (*(int *)&wpn->field_0xf48 != 0) {
      ::weapon::onSignal(&wpn->weapon,ArcContact);
      return;
    }
    break;
  case Weapon_Drop:
    ::weapon::onSignal(&wpn->weapon,Destroy);
    return;
  case Weapon_PostDetach:
    ::weapon::onSignal(&wpn->weapon,PostDetach);
    ::weapon::onMessage(&wpn->weapon,msg);
    return;
  case Weapon_PreDetach:
    FUN_000cc010(&wpn->field_0xf30);
    ::weapon::onMessage(&wpn->weapon,msg);
    return;
  case Weapon_ThrowAt:
    *(actor **)&wpn->field_0xe74 = (msg->header).someActor;
    *(ObjMsgID *)&wpn->field_0xe78 = msg[1].header.msgId;
    *(actor **)&wpn->field_0xe7c = msg[1].header.someActor;
    ::weapon::onSignal(&wpn->weapon,ThrownAt);
    ::actor::executeCallout((actor *)wpn,0,Throw);
    ::weapon::onMessage(&wpn->weapon,msg);
    return;
  }
  ::weapon::onMessage(&wpn->weapon,msg);
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields

void entityWeaponProjectile::func15
               (entityWeaponProjectile *wpn,WeaponSignal param_2,undefined4 param_3)

{
  CalloutDescriptor **ppCVar1;
  CollisionMask *pCVar2;
  int iVar4;
  WeaponProjectilesContext *iVar3;
  
  iVar3 = (wpn->weapon).projectilesCtx;
  switch(param_2 & 0xffff) {
  case ThrownAt:
    ::weapon::func15(wpn,param_2,param_3);
    FUN_000cbd90(iVar3);
    FUN_0013b7c0();
    return;
  case Attached:
    iVar4 = iVar3->field2396_0x95c;
    *(entityWeaponProjectile **)(iVar4 + 0x4c) = wpn;
    *(entityWeaponProjectile **)(iVar4 + 0x14) = wpn;
    return;
  case ArcContact:
    iVar4 = FUN_00145470();
    if (iVar4 != 0) {
      FUN_001454b0();
      ::weapon::onDestroy(&wpn->weapon);
    }
    FUN_000cc4d0();
    return;
  default:
    ::weapon::func15(wpn,param_2,param_3);
    break;
  case PostDetach:
    FUN_000cc1e0();
    return;
  case Destroy:
    ppCVar1 = &(wpn->weapon).avatar.callout;
    if (ppCVar1 != (CalloutDescriptor **)0x0) {
      ::actor::executeCalloutInDescriptor
                (*ppCVar1,HitImpact,(CalloutCallback *)0x0,0,(actor *)wpn,
                 (entityBodyPlayer_0x924)0x0);
    }
    (wpn->weapon).avatar.collisionMask = (wpn->weapon).avatar.collisionMask & 0xfffff7ff;
    iVar4 = FUN_00145470();
    if (iVar4 != 0) {
      FUN_001454b0();
      ::weapon::onDestroy(&wpn->weapon);
      return;
    }
    avatar::destroy((avatar *)wpn);
    return;
  case SceneBegun:
    FUN_00145bc0();
    (wpn->weapon).avatar.has0x4CollisionFlag = (wpn->weapon).avatar.has0x4CollisionFlag | 4;
    avatar::updateMorphTargetsOrSomething((avatar *)wpn);
    pCVar2 = &(wpn->weapon).avatar.collisionMask;
    *pCVar2 = *pCVar2 | Mask0x100;
    FUN_00144d00(&wpn->weapon);
    if ((wpn->weapon).field1057_0xda8 == 0) {
      FUN_00146310();
      return;
    }
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void entityWeaponProjectile::func16(actor *param_1,WeaponSignal param_2,uint newState)

{
  uint *puVar1;
  CollisionMask *pCVar2;
  int iVar3;
  int iVar4;
  
  iVar3 = *(int *)(param_1[1].avatar.calloutAID + 4);
  switch(param_2 & 0xffff) {
  case New_Name:
    if (*(int *)&param_1[1].avatar.field_0x4 != 0) {
      FUN_001108b0();
    }
    puVar1 = &(param_1->avatar).has0x4CollisionFlag;
    *puVar1 = *puVar1 & 0xfffffffb;
    avatar::updateMorphTargetsOrSomething(&param_1->avatar);
    return;
  default:
    ::weapon::func16(param_1,param_2,newState);
    break;
  case ThrownAt:
    FUN_0013b810((int)(param_1[1].avatar.modelAID + 0x4c),param_1);
    ::weapon::func16(param_1,param_2,newState);
    return;
  case Attached:
    if (iVar3 == 0) {
      avatar::destroy(&param_1->avatar);
      return;
    }
    iVar4 = *(int *)(iVar3 + 0x95c);
    *(undefined4 *)(iVar4 + 0x4c) = 0;
    *(undefined4 *)(iVar4 + 0x14) = 0;
    if (*(actor **)(*(int *)(iVar3 + 0x95c) + 0x48) == param_1) {
      FUN_0001b680();
      return;
    }
    break;
  case SceneBegun:
    if (*(int *)&param_1[1].avatar.field_0x4 != 0) {
      FUN_001108b0();
    }
    (param_1->avatar).has0x4CollisionFlag = (param_1->avatar).has0x4CollisionFlag & 0xfffffffb;
    avatar::updateMorphTargetsOrSomething(&param_1->avatar);
    pCVar2 = &(param_1->avatar).collisionMask;
    *pCVar2 = *pCVar2 & ~Mask0x100;
    FUN_00042040();
    return;
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void entityWeaponProjectileHome::getAllocDetails(undefined4 *param_1)

{
  *param_1 = 0xf60;
  param_1[1] = 0x6a4;
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void entityWeaponProjectileHome::getVTable(void)

{
  avatar::initVTable((AvatarVTable *)vtable);
  vtable[4] = ::weapon::update;
  vtable[0x12] = switchD_000d4179::EmptyFunction;
  vtable[0] = getAllocDetails;
  vtable[1] = ctor;
  vtable[2] = FUN_000cc8e0;
  vtable[3] = onMessage;
  vtable[0xf] = func15;
  vtable[0x10] = func16;
  vtable[0x11] = func17;
  vtable[5] = draw;
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields

undefined4
entityWeaponProjectileHome::ctor
          (entityWeaponProjectileHome *wpn,entityWeaponProjectileHomeParams *params)

{
  char cVar1;
  int iVar2;
  AnimEventMapping *pAVar3;
  char *pcVar4;
  
  (wpn->weapon).weaponHitCallback = HitCallback;
  pAVar3 = avatar::getAnimEventByName((avatar *)wpn,*(char **)&params->field_0x5f8,0);
  *(AnimEventMapping **)&wpn->field_0xe64 = pAVar3;
  *(undefined4 *)&wpn->field_0xe68 = *(undefined4 *)&params->field_0x5fc;
  *(undefined4 *)&wpn->field_0xe94 = *(undefined4 *)&params->field_0x600;
  *(undefined4 *)&wpn->field_0xf28 = *(undefined4 *)&params->field_0x604;
  *(undefined4 *)&wpn->field_0xf2c = *(undefined4 *)&params->field_0x608;
  *(undefined4 *)&wpn->field_0xf30 = *(undefined4 *)&params->field_0x60c;
  *(undefined4 *)&wpn->field_0xf58 = *(undefined4 *)&params->field_0x610;
  *(undefined4 *)&wpn->field_0xf5c = *(undefined4 *)&params->field_0x614;
  iVar2 = *(int *)&params->field_0x618;
  *(int *)&wpn->field_0xe98 = iVar2;
  if (iVar2 != 0) {
    pcVar4 = &params->field_0x624;
    iVar2 = 0xea8 - (int)pcVar4;
    do {
      cVar1 = *pcVar4;
      pcVar4[(int)wpn + iVar2] = cVar1;
      pcVar4 = pcVar4 + 1;
    } while (cVar1 != '\0');
    *(undefined4 *)&wpn->field_0xea4 = *(undefined4 *)&params->field_0x61c;
    *(undefined4 *)&wpn->field_0xea0 = *(undefined4 *)&params->field_0x620;
    *(undefined4 *)&wpn->field_0xe9c = 0;
  }
  return 1;
}




void entityWeaponProjectileHome::func17(entityWeaponProjectileHome *param_1,undefined4 param_2)

{
  undefined1 *puVar1;
  BOOL has_entry;
  int iVar2;
  objParams *poVar3;
  float10 fVar4;
  
  switch((undefined2)param_2) {
  case 3:
    break;
  case 4:
    iVar2 = FUN_000cd3a0();
    if (iVar2 != 0) {
      (param_1->weapon).arcContactValue = 0xb;
      return;
    }
    break;
  default:
    ::weapon::func17(&param_1->weapon,(undefined2)param_2);
    break;
  case 9:
    iVar2 = FUN_00040040(param_1);
    if (iVar2 != 0) {
      poVar3 = (objParams *)FUN_00069590(0.5);
      Assets::CreateEntityFromParams(poVar3);
      avatar::destroy((avatar *)param_1);
      return;
    }
    break;
  case 10:
    if (*(int *)&param_1->field_0xe98 != 0) {
      puVar1 = &param_1->field_0xe9c;
      Timer::reduce((float *)puVar1);
      iVar2 = FUN_00149c30();
      if ((((iVar2 != 0) &&
           (fVar4 = (float10)FUN_00041560(), fVar4 < (float10)*(float *)&param_1->field_0xea4)) &&
          (*(float *)puVar1 <= 0.001 && *(float *)puVar1 != 0.001)) &&
         (has_entry = hasAudioEntry(param_1->audioName), has_entry != 0)) {
        FUN_00041d40(0,0,0x3f800000);
        *(undefined4 *)puVar1 = *(undefined4 *)&param_1->field_0xea0;
      }
    }
    FUN_000cc910();
    ::weapon::func17(&param_1->weapon,(undefined2)param_2);
    return;
  case 0xb:
    iVar2 = FUN_00040040(param_1);
    if (iVar2 != 0) {
      poVar3 = (objParams *)FUN_00069590(0.5);
      Assets::CreateEntityFromParams(poVar3);
      avatar::destroy((avatar *)param_1);
      return;
    }
    break;
  case 0x10:
    FUN_00147430();
    return;
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void entityWeaponProjectileHome::onMessage(weapon *wpn,Message *param_2)

{
  actor *paVar1;
  int iVar2;
  
  switch((param_2->header).msgId) {
  case Avatar_Explode:
    ::weapon::onSignal(wpn,Destroy);
    ::weapon::onMessage(wpn,param_2);
    return;
  case Avatar_HitByGunshot:
    param_2[2].header.msgId = General_Activate;
    ::actor::executeCallout((actor *)wpn,0,Extinguished);
    wpn->arcContactValue = 9;
    break;
  case Actor_Dying:
    if ((wpn->attachState == 10) && (*(int *)&wpn->field_0xe50 != 0)) {
      paVar1 = (param_2->header).someActor;
      if (paVar1 == (actor *)wpn->projectilesCtx) goto LAB_000ccbf3;
      if (paVar1 == *(actor **)(*(int *)&wpn->field_0xe50 + 0x10)) {
        FUN_000cd2a0();
        ::weapon::onMessage(wpn,param_2);
        return;
      }
    }
    break;
  case Actor_ProjectileHitConnected:
    if (((param_2[5].header.someActor != (actor *)0x0) && (*(int *)&wpn->field_0xe50 != 0)) &&
       (param_2[3].header.msgId == *(ObjMsgID *)(*(int *)&wpn->field_0xe50 + 0x10))) {
LAB_000ccbf3:
      FUN_000cd2a0();
      ::weapon::onMessage(wpn,param_2);
      return;
    }
    break;
  case Scene_Begin:
    if (wpn->attachState == 0) {
      ::weapon::onSignal(wpn,SceneBegun);
      ::weapon::onMessage(wpn,param_2);
      return;
    }
    break;
  case Weapon_Attached:
    ::weapon::onSignal(wpn,Attached);
    ::weapon::onMessage(wpn,param_2);
    return;
  case Weapon_ArcContact:
    iVar2 = FUN_000cd260();
    if (iVar2 != 0) {
      avatar::destroy(&wpn->avatar);
      return;
    }
    if (wpn[1].avatar.physicsPos.y != 0.0) {
      ::weapon::onSignal(wpn,ArcContact);
      return;
    }
    break;
  case Weapon_Drop:
    ::weapon::onSignal(wpn,Destroy);
    return;
  case Weapon_PostDetach:
    ::weapon::onSignal(wpn,PostDetach);
    ::weapon::onMessage(wpn,param_2);
    return;
  case Weapon_PreDetach:
    FUN_000cc010(&wpn[1].avatar.rotQuat.z);
    ::weapon::onMessage(wpn,param_2);
    return;
  case Weapon_ThrowAt:
    ::weapon::onSignal(wpn,New_Name_(10));
    ::actor::executeCallout((actor *)wpn,0,Throw);
    ::weapon::onMessage(wpn,param_2);
    return;
  }
  ::weapon::onMessage(wpn,param_2);
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields

void entityWeaponProjectileHome::func15
               (entityWeaponProjectileHome *wpn,uint param_2,undefined4 param_3)

{
  CalloutDescriptor **ppCVar1;
  CollisionMask *pCVar2;
  int iVar3;
  
  switch(param_2 & 0xffff) {
  case 3:
    iVar3 = ((wpn->weapon).projectilesCtx)->field2396_0x95c;
    *(entityWeaponProjectileHome **)(iVar3 + 0x4c) = wpn;
    *(entityWeaponProjectileHome **)(iVar3 + 0x14) = wpn;
    return;
  case 4:
    iVar3 = FUN_00145470();
    if (iVar3 != 0) {
      ::weapon::onDestroy(&wpn->weapon);
    }
    FUN_000cd340();
    return;
  default:
    ::weapon::func15(wpn,param_2,param_3);
    break;
  case 7:
    FUN_000cd230();
    if (*(AnimEventMapping **)&wpn->field_0xe64 != (AnimEventMapping *)0x0) {
      avatar::activateAnimation((avatar *)wpn,*(AnimEventMapping **)&wpn->field_0xe64);
      return;
    }
    avatar::clearAnimation((avatar *)wpn);
    return;
  case 9:
    ppCVar1 = &(wpn->weapon).avatar.callout;
    if (ppCVar1 != (CalloutDescriptor **)0x0) {
      ::actor::executeCalloutInDescriptor
                (*ppCVar1,HitImpact,(CalloutCallback *)0x0,0,(actor *)wpn,
                 (entityBodyPlayer_0x924)0x0);
    }
    (wpn->weapon).avatar.collisionMask = (wpn->weapon).avatar.collisionMask & 0xfffff7ff;
    iVar3 = FUN_00145470();
    if (iVar3 != 0) {
      ::weapon::onDestroy(&wpn->weapon);
      return;
    }
    avatar::destroy((avatar *)wpn);
    return;
  case 10:
    ::weapon::func15(wpn,param_2,param_3);
    FUN_000cd120();
    FUN_0013b7c0();
    return;
  case 0x10:
    FUN_00145bc0();
    (wpn->weapon).avatar.has0x4CollisionFlag = (wpn->weapon).avatar.has0x4CollisionFlag | 4;
    avatar::updateMorphTargetsOrSomething((avatar *)wpn);
    pCVar2 = &(wpn->weapon).avatar.collisionMask;
    *pCVar2 = *pCVar2 | Mask0x100;
    FUN_00144d00(&wpn->weapon);
    if ((wpn->weapon).field1057_0xda8 == 0) {
      FUN_00146310();
      return;
    }
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields

void entityWeaponProjectileHome::func16
               (entityWeaponProjectileHome *param_1,uint param_2,undefined4 param_3)

{
  uint *puVar1;
  CollisionMask *pCVar2;
  WeaponProjectilesContext *pWVar3;
  int iVar4;
  
  pWVar3 = (param_1->weapon).projectilesCtx;
  switch(param_2 & 0xffff) {
  case 0:
    if (*(int *)&(param_1->weapon).field_0xcfc != 0) {
      FUN_001108b0();
    }
    puVar1 = &(param_1->weapon).avatar.has0x4CollisionFlag;
    *puVar1 = *puVar1 & 0xfffffffb;
    avatar::updateMorphTargetsOrSomething((avatar *)param_1);
    return;
  default:
    ::weapon::func16(param_1,param_2,param_3);
    break;
  case 3:
    if (pWVar3 == (WeaponProjectilesContext *)0x0) {
      avatar::destroy((avatar *)param_1);
      return;
    }
    iVar4 = pWVar3->field2396_0x95c;
    *(undefined4 *)(iVar4 + 0x4c) = 0;
    *(undefined4 *)(iVar4 + 0x14) = 0;
    if (*(entityWeaponProjectileHome **)(pWVar3->field2396_0x95c + 0x48) == param_1) {
      FUN_0001b680();
      return;
    }
    break;
  case 10:
    FUN_0013b810((int)&param_1->field_0xf34,(actor *)param_1);
    ::weapon::func16(param_1,param_2,param_3);
    return;
  case 0x10:
    if (*(int *)&(param_1->weapon).field_0xcfc != 0) {
      FUN_001108b0();
    }
    (param_1->weapon).avatar.has0x4CollisionFlag =
         (param_1->weapon).avatar.has0x4CollisionFlag & 0xfffffffb;
    avatar::updateMorphTargetsOrSomething((avatar *)param_1);
    pCVar2 = &(param_1->weapon).avatar.collisionMask;
    *pCVar2 = *pCVar2 & ~Mask0x100;
    FUN_00042040();
    return;
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


undefined4 entityWeaponProjectileHome::draw(avatar *param_1,undefined4 param_2,int param_3)

{
  if (*(int *)param_1[1].model0x9s[4].audioID != 0) {
    avatar::update0x1d8s(param_1);
    if (param_3 == 2) {
      FUN_00062220((vec2 *)0x0,(vec2 *)0x0);
      avatar::draw(param_1,param_2,1);
      FUN_00062490(0x80ffffff);
    }
    return 1;
  }
  avatar::draw(param_1,param_2,param_3);
  return 1;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void entityWeaponProjectileLarge::getAllocDetails(undefined4 *param_1)

{
  *param_1 = 0xf08;
  param_1[1] = 0x604;
  return;
}



// WARNING: Globals starting with '_' overlap smaller symbols at the same address
// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void entityWeaponProjectileLarge::getVTable(void)

{
  avatar::initVTable(&vtable);
  vtable.draw = ::weapon::func5;
  vtable.update = ::weapon::update;
  _DAT_00506430 = switchD_000d4179::EmptyFunction;
  vtable.getAllocDetails = getAllocDetails;
  vtable.ctor = &LAB_000cd6b0;
  vtable.dtor = FUN_000cdaa0;
  vtable.onMessage = onMessage;
  _DAT_00506424 = &LAB_000cd700;
  _DAT_00506428 = &DAT_000cd8a0;
  _DAT_0050642c = FUN_000cda10;
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void entityWeaponProjectileLarge::onMessage(entityWeaponProjectileLarge *param_1,Message *param_2)

{
  WeaponProjectilesContext *pWVar1;
  BOOL BVar2;
  
  switch((param_2->header).msgId) {
  case Actor_ProjectileHitConnected:
    if (((param_2[5].header.someActor != (actor *)0x0) &&
        (::actor::executeCallout((actor *)param_1,0,HitImpact),
        param_2[6].header.someActor != (actor *)0x0)) && (param_1->field33_0xe74 == 0.0)) {
      FUN_00146230();
      ::weapon::onSignal(&param_1->weapon,ArcContact);
      ::weapon::onMessage(&param_1->weapon,param_2);
      return;
    }
    break;
  case Scene_AvatarRemoved:
    if (param_1->bufferOfEdb2s != (Buffer<EDB2Entry> *)0x0) {
      Buffer<EDB2Entry>::addAvatarToSet
                (param_1->bufferOfEdb2s,&((param_2->header).someActor)->avatar);
    }
    break;
  case Weapon_Attached:
    ::weapon::onSignal(&param_1->weapon,Attached);
    ::weapon::onMessage(&param_1->weapon,param_2);
    return;
  case Weapon_Drop:
    pWVar1 = (param_1->weapon).projectilesCtx;
    if ((pWVar1 != (WeaponProjectilesContext *)0x0) && (BVar2 = FUN_00028d20(pWVar1), BVar2 != 0)) {
      _DAT_004326a4 = 0;
      _DAT_004326a0 = 0;
      BaronDraw_0043268c.scalar = 2.0;
      FUN_0012f990(&LAB_00312f8c,(int *)&DAT_004326a0);
      DAT_00432688 = 7;
      FUN_0012d8a0();
      DAT_004326e0 = 2;
    }
    ::weapon::onSignal(&param_1->weapon,New_Name_(6));
    return;
  case Weapon_PostDetach:
    ::weapon::onSignal(&param_1->weapon,PostDetach);
    ::weapon::onMessage(&param_1->weapon,param_2);
    return;
  case Weapon_PreDetach:
    FUN_000ce660(&param_1->field_0xe98);
    ::weapon::onMessage(&param_1->weapon,param_2);
    return;
  case Weapon_Scooped:
    if ((param_1->weapon).attachState == 0x10) {
      *(actor **)&param_1->field_0xec0 = param_2[1].header.someActor;
      *(ObjMsgID *)&param_1->field_0xec4 = param_2[2].header.msgId;
      *(actor **)&param_1->field_0xec8 = param_2[2].header.someActor;
      *(float *)&param_1->field_0xec0 =
           *(float *)&param_1->field_0xed8 + *(float *)&param_1->field_0xec0;
      *(undefined4 *)&param_1->field_0xecc = 0;
      *(ObjMsgID *)&param_1->field_0xed0 = param_2[3].header.msgId;
      *(ObjMsgID *)&param_1->field_0xea4 = param_2[1].header.msgId;
      avatar::getWorldPosition((avatar *)param_1,(vec3 *)&param_1->field_0xeb4);
      avatar::getWorldRotation((avatar *)param_1,(vec3 *)&param_1->field_0xea8);
      ::weapon::onSignal(&param_1->weapon,New_Name_(15));
      *(entityWeaponProjectileLarge **)(param_2[1].header.msgId + 0x314) = param_1;
      (param_2->header).someActor = (actor *)0x1;
      ::weapon::onMessage(&param_1->weapon,param_2);
      return;
    }
    break;
  case Weapon_SpawnedActor:
    InitEDB2Entry(&param_1->bufferOfEdb2s,&((param_2->header).someActor)->avatar,0);
    ::weapon::onMessage(&param_1->weapon,param_2);
    return;
  case Weapon_ThrowAt:
    pWVar1 = (param_1->weapon).projectilesCtx;
    if ((pWVar1 != (WeaponProjectilesContext *)0x0) && (BVar2 = FUN_00028d20(pWVar1), BVar2 != 0)) {
      _DAT_004326a4 = 0;
      _DAT_004326a0 = 0;
      BaronDraw_0043268c.scalar = 2.0;
      FUN_0012f990(&LAB_00312f8c,(int *)&DAT_004326a0);
      DAT_00432688 = 7;
      FUN_0012d8a0();
      DAT_004326e0 = 2;
    }
    *(actor **)&param_1->field_0xe54 = (param_2->header).someActor;
    *(ObjMsgID *)&param_1->field_0xe58 = param_2[1].header.msgId;
    *(actor **)&param_1->field_0xe5c = param_2[1].header.someActor;
    ::weapon::onSignal(&param_1->weapon,ThrownAt);
    ::actor::executeCallout((actor *)param_1,0,Throw);
    ::weapon::onMessage(&param_1->weapon,param_2);
    return;
  }
  ::weapon::onMessage(&param_1->weapon,param_2);
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void entityWeaponWielding::getAllocDetails(undefined4 *param_1)

{
  *param_1 = 0xf08;
  param_1[1] = 0x684;
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void entityWeaponWielding::getVTable(void)

{
  avatar::initVTable((AvatarVTable *)&vtable);
  vtable.enterState = ::weapon::func5;
  vtable.update = ::weapon::update;
  vtable.func18 = switchD_000d4179::EmptyFunction;
  vtable.getAllocDetails = getAllocDetails;
  vtable.ctor = ctor;
  vtable.dtor = switchD_000d4179::EmptyFunction;
  vtable.onMessage = onMessage;
  vtable.getCringeState = FUN_000cf400;
  vtable.func16 = FUN_000cf510;
  vtable.func17 = FUN_000cf050;
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void entityWeaponWielding::ctor(entityWeaponWielding *weapon,entityWeaponWieldingParams *params)

{
  char cVar1;
  int iVar2;
  char *pcVar3;
  
  (weapon->weapon).weaponHitCallback = HitCallback;
  *(undefined4 *)&weapon->field_0xe54 = *(undefined4 *)&params->field_0x5f8;
  weapon->baseDurability = params->baseDurability;
  if (*(int *)&params->field_0x600 != 0) {
    (weapon->weapon).field_0x942 = 1;
  }
  if (weapon->baseDurability == 0) {
    (weapon->weapon).isInvalid = true;
  }
  pcVar3 = &params->field_0x604;
  iVar2 = 0xe70 - (int)pcVar3;
  do {
    cVar1 = *pcVar3;
    pcVar3[(int)weapon + iVar2] = cVar1;
    pcVar3 = pcVar3 + 1;
  } while (cVar1 != '\0');
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void entityWeaponWielding::onMessage(entityWeaponWielding *weapon,Message *param_2)

{
  WeaponProjectilesContext *pWVar1;
  int *piVar2;
  BOOL BVar3;
  actor *paVar4;
  uint uVar5;
  vec3 local_c;
  
  switch((param_2->header).msgId) {
  case Avatar_FxCustomRemoved:
    if (*(actor **)&weapon->field_0xe6c == (param_2->header).someActor) {
      *(undefined4 *)&weapon->field_0xe6c = 0;
    }
    break;
  case Actor_WeaponHitConnected:
    if (((param_2[5].header.someActor != (actor *)0x0) &&
        (((paVar4 = (actor *)::weapon::getIntOrStruct(weapon), paVar4 == (actor *)0x0 ||
          (BVar3 = actorIsHumanOrNoPrevLL(paVar4), BVar3 == 0)) ||
         (Game::PowerupParams[0xd].active == 0)))) && (*(int *)&weapon->field_0xe64 == 0)) {
      *(undefined4 *)&weapon->field_0xe64 = 1;
      if (0 < (int)weapon->durability) {
        uVar5 = weapon->durability - 1;
        weapon->durability = uVar5;
        if ((int)uVar5 < 1) {
          *(undefined4 *)&weapon->field_0xe68 = 1;
          ::weapon::onMessage(&weapon->weapon,param_2);
          return;
        }
        FUN_000fca60(&local_c,(ushort *)param_2[3].header.someActor);
        FUN_001451c0((float)(int)weapon->durability / (float)(int)weapon->maxDurability);
        ::weapon::onMessage(&weapon->weapon,param_2);
        return;
      }
    }
    break;
  case Weapon_Attached:
    ::weapon::onSignal(&weapon->weapon,Attached);
    BVar3 = actorIsHumanOrNoPrevLL((param_2->header).someActor);
    if (BVar3 != 0) {
      weapon->durability = weapon->baseDurability;
      weapon->maxDurability = weapon->baseDurability;
      ::weapon::onMessage(&weapon->weapon,param_2);
      return;
    }
    weapon->durability = *(uint *)&weapon->field_0xe54;
    weapon->maxDurability = *(uint *)&weapon->field_0xe54;
    ::weapon::onMessage(&weapon->weapon,param_2);
    return;
  case Weapon_AttackVolumeEnabled:
    if ((param_2->header).someActor != (actor *)0x0) {
      *(undefined4 *)&weapon->field_0xe64 = 0;
      ::weapon::onMessage(&weapon->weapon,param_2);
      return;
    }
    if ((*(int *)&weapon->field_0xe68 != 0) &&
       (piVar2 = ::weapon::getIntOrStruct(weapon), piVar2 != (int *)0x0)) {
      FUN_00146230();
      FUN_0001b4c0(piVar2[599]);
      ::weapon::onSignal(&weapon->weapon,New_Name_(6));
      ::weapon::onMessage(&weapon->weapon,param_2);
      return;
    }
    break;
  case Weapon_Drop:
    if ((param_2->header).someActor == (actor *)0x0) {
      pWVar1 = (weapon->weapon).projectilesCtx;
      if ((pWVar1 != (WeaponProjectilesContext *)0x0) && (BVar3 = FUN_00028d20(pWVar1), BVar3 != 0))
      {
        BaronDraw_0043268c.scalar = 2.0;
        _DAT_004326a4 = 0;
        _DAT_004326a0 = 0;
        FUN_0012f990(&LAB_00312f8c,(int *)&DAT_004326a0);
        DAT_00432688 = 7;
        FUN_0012d8a0();
        DAT_004326e0 = 2;
      }
      ::weapon::onSignal(&weapon->weapon,New_Name_(6));
      return;
    }
    break;
  case Weapon_PostDetach:
    ::weapon::onSignal(&weapon->weapon,PostDetach);
    ::weapon::onMessage(&weapon->weapon,param_2);
    return;
  }
  ::weapon::onMessage(&weapon->weapon,param_2);
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void weapon::initPickupHitboxes(weapon *wpn,weaponParams *params)

{
  int i;
  WeaponHitboxParams *param_hitboxes;
  WeaponHitbox *hitboxes;
  weaponParams *paramss;
  
  paramss = params;
  i = 0;
  wpn->numHitboxes = (short)params->numHitboxes;
  wpn->field18_0x946 = 0;
  param_hitboxes = params->weaponHitboxes;
  hitboxes = (WeaponHitbox *)&wpn->field_0x948;
  if (0 < params->numHitboxes) {
    do {
      if (*(int *)param_hitboxes->someAID == 0x5f646961) {
        Assets::GetResourceBytes(param_hitboxes->someAID,&params);
        if (params == (weaponParams *)0x0) {
          runtime::ExitGame(2);
        }
        hitboxes->hitboxRes = (uint)params;
      }
      *(objTag *)&hitboxes->field2_0x4 = param_hitboxes->field2_0x4;
      hitboxes->weaponTypeOrIndex = param_hitboxes->field0_0x0;
      hitboxes->field4_0xc = param_hitboxes->field5_0x8;
      hitboxes->field1_0x2 = param_hitboxes->field1_0x2;
      i = i + 1;
      hitboxes = hitboxes + 1;
      param_hitboxes = param_hitboxes + 1;
    } while (i < paramss->numHitboxes);
  }
  return;
}




int weapon::onDestroy(weapon *weapon)

{
  CalloutDescriptor **ppCVar1;
  Model *pMVar2;
  DataForInfoFromBackground_conflict1 *pDVar3;
  int iVar4;
  AudioParentState extraout_ECX;
  Subresource0x11 *pSVar5;
  int iVar6;
  uint uVar7;
  int local_c;
  ObjMsgID local_8;
  weapon *local_4;
  
  pMVar2 = (weapon->avatar).model;
  if (((pMVar2 == (Model *)0x0) || (pMVar2->descriptor == (ModelDescriptor *)0x0)) ||
     (pSVar5 = pMVar2->descriptor->runtimeCtx->subres0x11, pSVar5 == (Subresource0x11 *)0x0)) {
    uVar7 = 0;
  }
  else {
    uVar7 = (uint)pSVar5->otherCount;
  }
  local_c = 0;
  iVar6 = 0;
  if ((uVar7 != 0) && (0 < (weapon->avatar).numTransforms)) {
    if ((pMVar2 == (Model *)0x0) || (pMVar2->descriptor == (ModelDescriptor *)0x0)) {
      pSVar5 = (Subresource0x11 *)0x0;
    }
    else {
      pSVar5 = pMVar2->descriptor->runtimeCtx->subres0x11;
    }
    ppCVar1 = &(weapon->avatar).callout;
    if (ppCVar1 != (CalloutDescriptor **)0x0) {
      ::actor::executeCalloutInDescriptor
                (*ppCVar1,Break,(CalloutCallback *)0x0,0,(actor *)weapon,(entityBodyPlayer_0x924)0x0
                );
    }
    iVar4 = weapon->field1048_0xd90;
    (weapon->avatar).hasActor_ = false;
    iVar6 = local_c;
    if (iVar4 < (int)uVar7) {
      local_c = 1;
      do {
        iVar6 = weapon->field1048_0xd90;
        FUN_0003f820(weapon);
        iVar4 = weapon->field1048_0xd90 + 1;
        weapon->field1049_0xd94 =
             weapon->field1049_0xd94 +
             (uint)*(byte *)((int)&pSVar5->someOtherPtrOrSize + iVar6 * 0xc + 2);
        weapon->field1048_0xd90 = iVar4;
        iVar6 = local_c;
      } while (iVar4 < (int)uVar7);
    }
  }
  FUN_001457a0(0);
  weapon->field9_0x93c = 0;
  if (weapon->field_0xd08 != '\0') {
    weapon->field_0xd08 = 0;
    if (weapon->field1044_0xd88 != -1) {
      AudioParent::UpdateState(0,Audio::SoundSources + (short)weapon->field1044_0xd88,extraout_ECX);
      weapon->field1044_0xd88 = 0xffff;
    }
  }
  if ((weapon->avatar).shadowModel != (Model *)0x0) {
    (weapon->avatar).hasShadow = 0;
  }
  if (iVar6 != 0) {
    pDVar3 = (weapon->avatar).infoList.prev;
    while (pDVar3 != (DataForInfoFromBackground_conflict1 *)0x0) {
      pDVar3 = (DataForInfoFromBackground_conflict1 *)pDVar3->field1_0x4;
      FUN_0011bda0();
    }
    FUN_0003de90(weapon);
    FUN_00148430(&weapon->field_0xb6c);
  }
  *(undefined4 *)&weapon->field_0x9a0 = 1;
  if ((weapon->weaponState != 0) && (weapon->skipDestroyMsg == 0)) {
    FUN_001456d0(weapon->weaponState);
  }
  if (weapon->skipDestroyMsg == 0) {
    DAT_00545978 = DAT_00545978 + 1;
    local_8 = Scene_WeaponDestroyed;
    local_4 = weapon;
    EventLoop::DispatchMessage(&local_8);
  }
  return iVar6;
}




void weapon::getAllocDetails(undefined4 *param_1)

{
  *param_1 = 0xe54;
  param_1[1] = 0x5f8;
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void weapon::getVTable(void)

{
  avatar::initVTable((AvatarVTable *)vtable);
  vtable[0] = getAllocDetails;
  vtable[1] = ctor;
  vtable[2] = dtor;
  vtable[3] = onMessage;
  vtable[5] = func5;
  vtable[4] = update;
  vtable[0xf] = func15;
  vtable[0x10] = func16;
  vtable[0x11] = func17;
  vtable[0x12] = switchD_000d4179::EmptyFunction;
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


undefined4 weapon::func5(avatar *param_1,undefined4 param_2,BOOL param_3)

{
  avatar_0x918 pEVar1;
  undefined4 uVar2;
  
  pEVar1 = (param_1->node0x918).prev;
  if (((((pEVar1 != (avatar_0x918)0x0) && (pEVar1->prev != (avatar_0x918)0x0)) &&
       (pEVar1 != (avatar_0x918)0x918)) &&
      ((*(int *)(pEVar1 + 0x79) != 0 &&
       ((*(short *)((int)(pEVar1 + 0x78) + 4) == 2 || (*(int *)((int)(pEVar1 + 4) + 4) != 0)))))) &&
     (((undefined1)g_globalFlagset & HealthAltered?) != 0)) {
    return 0;
  }
  uVar2 = avatar::draw(param_1,param_2,param_3);
  FUN_00147560();
  return uVar2;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


undefined4 weapon::ctor(weapon *weapon,weaponParams *param_2)

{
  char cVar1;
  ushort uVar2;
  AvatarVTable *pAVar3;
  weapon *pwVar4;
  int iVar5;
  actorBodyAllocd *paVar6;
  char *pcVar7;
  char *pcVar8;
  
  weapon->field9_0x93c = 1;
  weapon->field12_0x93f = param_2->field_0x336;
  weapon->holdableType = param_2->field_0x337;
  weapon->field1055_0xda0 = *(undefined4 *)&param_2->field_0x460;
  weapon->field1056_0xda4 = *(undefined4 *)&param_2->field_0x464;
  weapon->field1058_0xdac = param_2->field_0x338;
  weapon->field1059_0xdad = param_2->field_0x339;
  weapon->field1060_0xdae = param_2->field_0x33a;
  weapon->field1057_0xda8 = *(undefined4 *)&param_2->field_0x46c;
                    // Init pickup hitboxes
  initPickupHitboxes(weapon,param_2);
  paVar6 = avatar::initSomething(&weapon->avatar);
  weapon->field100_0x998 = paVar6;
  weapon->field701_0xc18 = *(undefined4 *)&param_2->field_0x574;
  FUN_00145150();
  loadGraphics(weapon);
  FUN_00147e10(weapon);
  calculateRandomValues(weapon,param_2);
  weapon->numCallouts = param_2->numCallouts;
  weapon->field366_0xaac = 1;
  weapon->field1048_0xd90 = 0;
  weapon->field1049_0xd94 = 0;
  weapon->field1050_0xd98 = 0;
  weapon->field1061_0xdaf = 0;
  weapon->field1044_0xd88 = 0xffff;
  pcVar8 = *(char **)&param_2->field_0x33c;
  if (pcVar8 != (char *)0x0) {
    pcVar7 = &weapon->field1062_0xdb0;
    do {
      cVar1 = *pcVar8;
      *pcVar7 = cVar1;
      pcVar7 = pcVar7 + 1;
      pcVar8 = pcVar8 + 1;
    } while (cVar1 != '\0');
  }
  pcVar8 = (param_2->avatarParams).standAnimationAID;
  iVar5 = 0xdd0 - (int)pcVar8;
  do {
    cVar1 = *pcVar8;
    pcVar8[(int)weapon + iVar5] = cVar1;
    pcVar8 = pcVar8 + 1;
  } while (cVar1 != '\0');
  avatar::loadTransforms(&weapon->avatar);
  if (*(int *)&param_2->field_0x468 != 0) {
    FUN_00147860(weapon);
  }
  pcVar8 = &param_2->field_0x578;
  if (param_2->field_0x578 != '\0') {
    iVar5 = 0xd08 - (int)pcVar8;
    do {
      cVar1 = *pcVar8;
      pcVar8[(int)weapon + iVar5] = cVar1;
      pcVar8 = pcVar8 + 1;
    } while (cVar1 != '\0');
  }
  *(undefined4 *)&(weapon->avatar).damageFlag_ = 4;
  uVar2 = weapon->numCallouts;
  weapon->arcContactValue = 0;
  (*(weapon->avatar).vtable[1].ctor)(weapon,weapon->attachState,uVar2);
  weapon->attachState = uVar2;
  weapon->t = 0.0;
  (*(weapon->avatar).vtable[1].getAllocDetails)((ObjectAllocDetails *)weapon);
  pAVar3 = *(AvatarVTable **)&param_2->field_0x470;
  if (pAVar3 != (AvatarVTable *)0x0) {
    if (g_weapons->tail == g_weapons->end) {
      g_weapons = (Buffer<weapon> *)runtime::ExtendArray((Buffer *)g_weapons);
    }
    pwVar4 = g_weapons->tail;
    g_weapons->tail = (weapon *)((int)&(pwVar4->avatar).vtable + (uint)g_weapons->valueSize);
    (pwVar4->avatar).vtable = pAVar3;
    *(weapon **)&(pwVar4->avatar).field_0x4 = weapon;
  }
  (weapon->avatar).hasActor_ = true;
  ::actor::createOnDeathObjects(&weapon->avatar,0);
  return 1;
}




void weapon::dtor(int param_1)

{
  AudioParentState extraout_ECX;
  AudioParentState extraout_ECX_00;
  AudioParentState extraout_ECX_01;
  AudioParentState extraout_ECX_02;
  AudioParentState extraout_ECX_03;
  AudioParentState AVar1;
  
  if (*(int *)(param_1 + 0x934) != 0) {
    *(undefined4 *)(*(int *)(param_1 + 0x934) + 4) = *(undefined4 *)(param_1 + 0x938);
  }
  if (*(undefined4 **)(param_1 + 0x938) != (undefined4 *)0x0) {
    **(undefined4 **)(param_1 + 0x938) = *(undefined4 *)(param_1 + 0x934);
  }
  *(undefined4 *)(param_1 + 0x934) = 0;
  *(undefined4 *)(param_1 + 0x938) = 0;
  if (*(void **)(param_1 + 0xad8) != (void *)0x0) {
    Assets::DestroyAssetOrDecrement(*(void **)(param_1 + 0xad8));
    *(undefined4 *)(param_1 + 0xad8) = 0;
  }
  if (*(int *)(param_1 + 0x998) != 0) {
    FUN_0013f240(param_1);
    *(undefined4 *)(param_1 + 0x998) = 0;
  }
  FUN_00144b30(param_1);
  if (*(void **)(param_1 + 0xc04) != (void *)0x0) {
    GhoulyBox::dtor(*(void **)(param_1 + 0xc04));
    *(undefined4 *)(param_1 + 0xc04) = 0;
  }
  FUN_0014a0d0();
  AVar1 = extraout_ECX;
  if (*(void **)(param_1 + 0xae8) != (void *)0x0) {
    free(*(void **)(param_1 + 0xae8));
    *(undefined4 *)(param_1 + 0xae8) = 0;
    *(undefined2 *)(param_1 + 0xae6) = 0;
    AVar1 = extraout_ECX_00;
  }
  if (*(int *)(param_1 + 0xd9c) != 0) {
    FUN_001450a0(param_1);
    free(*(void **)(param_1 + 0xd9c));
    *(undefined4 *)(param_1 + 0xd9c) = 0;
    AVar1 = extraout_ECX_01;
  }
  if (*(void **)(param_1 + 0x2a4) != (void *)0x0) {
    free(*(void **)(param_1 + 0x2a4));
    *(undefined4 *)(param_1 + 0x2a4) = 0;
    AVar1 = extraout_ECX_02;
  }
  if (*(int *)(param_1 + 0xcfc) != 0) {
    FUN_001108b0();
    AVar1 = extraout_ECX_03;
  }
  if (*(short *)(param_1 + 0xd88) != -1) {
    AudioParent::UpdateState(0,Audio::SoundSources + *(short *)(param_1 + 0xd88),AVar1);
    *(undefined2 *)(param_1 + 0xd88) = 0xffff;
  }
  if (*(int *)(param_1 + 0xd98) != 0) {
    FUN_000ed2e0();
    *(undefined4 *)(param_1 + 0xd98) = 0;
  }
  FUN_0012aca0();
  return;
}




int * weapon::getIntOrStruct(int param_1)

{
  int *piVar1;
  
  piVar1 = *(int **)(param_1 + 0x918);
  if ((piVar1 != (int *)0x0) && (*piVar1 != 0)) {
    return piVar1 + -0x246;
  }
  return (int *)0x0;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


uint32_t weapon::getAttribute(ushort param_1,weapon *wpn)

{
  short sVar1;
  ushort *puVar2;
  int i;
  
  sVar1 = wpn->numHitboxes;
  i = 0;
  puVar2 = (ushort *)&wpn->field_0x948;
  if (0 < sVar1) {
    do {
      if (*puVar2 == param_1) {
        return (uint)puVar2[2];
      }
      puVar2 = puVar2 + 8;
      i = i + 1;
    } while (i < sVar1);
  }
  if (sVar1 != 0) {
    return (uint)*(ushort *)&wpn->field_0x94c;
  }
  return 0;
}




void weapon::onMessage(weapon *weapon,Message *param_2)

{
  CollisionMask *pCVar1;
  WeaponProjectilesContext *av;
  weapon *wpn;
  int *piVar2;
  ObjMsgID OVar3;
  BOOL BVar4;
  int iVar5;
  actor *paVar6;
  Message *pMVar7;
  undefined2 weaponState;
  float local_44;
  vec3 local_40;
  vec3 local_34;
  vec3 local_28;
  undefined4 local_1c;
  weapon *local_18;
  int local_14;
  weapon *local_10;
  Message *local_c;
  float local_8;
  float local_4;
  Avatar_HitByWeaponMessage *msgg;
  Message *pAVar8;
  
  pMVar7 = param_2;
  wpn = weapon;
  avatar::onMessage(&weapon->avatar,param_2);
  switch((pMVar7->header).msgId) {
  case General_Activate:
    onSignal(weapon,SceneBegun);
    return;
  case General_Deactivate:
    onSignal(weapon,New_Name_(12));
    return;
  case General_Reset:
  case General_Open:
  case General_Close:
  case Avatar_AnimationEvent:
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
  case Avatar_FxCustomRemoved:
  case Avatar_HitByFurnace:
  case Avatar_HitByKnockDownSphere:
  case Avatar_HitByGunshot:
  case Avatar_HitByProjectileAndWaitingForFollow:
  case Avatar_HitByProp:
  case Avatar_HitBySSS:
  case Avatar_HitsDisable:
  case Avatar_HitsEnable:
  case Avatar_PreHitByExplode:
  case Avatar_ResetPos:
  case Actor_AStarLayerChanged:
  case Actor_AbortState:
  case Actor_ActionBegin:
  case Actor_ActionEnd:
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
  case Actor_Reset:
  case Actor_Scooped:
  case Actor_SetDroneAction:
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
  case Actor_WithinExclusionRegion:
  case ActorBody_AttachedWeapon:
  case ActorBody_AttachedProjectile:
  case ActorBody_AttackBoost:
  case ActorBody_HitReactionStateChange:
  case ActorBody_ResolveHitsWallContact:
  case ActorBody_SolidDeflectPole:
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
  case Scene_AvatarInserted:
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
  case Scene_SuperScaryStateChange:
  case Scene_WeaponDestroyed:
  case Scoreboard_HeartBeat:
  case Weapon_Attached:
  case Weapon_AttackVolumeEnabled:
  case Weapon_AwaitingPickup:
  case Weapon_BobAttach:
  case Weapon_GetProjectileAid:
  case Weapon_IsRecoilType:
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
  case Ghouly_GetDroneToPosition:
    break;
  case Avatar_AddToIgnoreList:
    FUN_00144fb0();
    return;
  case Avatar_BreakableHit:
    onBreakableHit(weapon,(Avatar_BreakableHitMessage *)pMVar7);
    return;
  case Avatar_Explode:
    iVar5 = FUN_00145470();
    if (iVar5 != 0) {
      weapon->weaponState = 0;
      onDestroy(weapon);
      onSignal(weapon,Destroy);
      return;
    }
    break;
  case Avatar_HitByActor:
                    // Player hits weapon
    paVar6 = (actor *)FUN_00146b80(weapon,pMVar7[1].header.msgId,1);
    (pMVar7->header).someActor = paVar6;
    return;
  case Avatar_HitByProjectile:
    OVar3 = FUN_00146b80(weapon,*(undefined4 *)(pMVar7[3].header.someActor[1].avatar.calloutAID + 4)
                         ,5);
    pMVar7[2].header.msgId = OVar3;
    pMVar7[3].header.msgId = Null;
    return;
  case Avatar_HitByWeapon:
    weaponState = 4;
    piVar2 = getIntOrStruct(pMVar7[2].header.someActor);
    OVar3 = FUN_00146b80(weapon,piVar2,weaponState);
    pMVar7[2].header.msgId = OVar3;
    return;
  case Avatar_IsBroken:
    (pMVar7->header).someActor = *(actor **)&weapon->field_0x9a0;
    return;
  case Avatar_SceneInsert:
    if (*(int *)&weapon->field_0x934 == 0) {
      FUN_0002cbd0();
    }
    pCVar1 = &(weapon->avatar).collisionMask;
    *pCVar1 = *pCVar1 & ~Mask0x40;
    if (*(int *)&weapon->field_0xad0 != 0) {
      FUN_0003ef40((actor *)weapon);
    }
    avatar::getWorldPosition(&weapon->avatar,&local_28);
    iVar5 = FUN_00110bf0(&local_28,-1,0);
    *(int *)&weapon->field_0xd00 = iVar5;
    return;
  case Actor_Animation_Sync:
    FUN_00144b80(weapon);
    return;
  case Actor_NoLongerInvulnerable:
    if ((actorBodyAllocd *)weapon->field100_0x998 != (actorBodyAllocd *)0x0) {
      actorAllocd::ensureAvatarInAllocd
                ((actorBodyAllocd *)weapon->field100_0x998,(pMVar7->header).someActor);
      return;
    }
    break;
  case Scene_AvatarRemoved:
    FUN_001462b0();
    return;
  case Scene_Begin:
    FUN_00144fd0();
    FUN_00148600();
    return;
  case Scene_TargetRemoved:
    FUN_001462f0();
    return;
  case Weapon_ArcContact:
    weapon->arcContactValue = 9;
    return;
  case Weapon_BounceToDestination:
    onSignal(weapon,New_Name_(5));
    FUN_00149230();
    return;
  case Weapon_Drop:
    if ((pMVar7->header).someActor != (actor *)0x0) {
      av = weapon->projectilesCtx;
      weapon = (weapon *)10.0;
      param_2 = (Message *)30.0;
      local_44 = 4.0;
      if (av == (WeaponProjectilesContext *)0x0) {
        avatar::getWorldPosition(&wpn->avatar,&local_34);
        iVar5 = FUN_00110bf0(&local_34,-1,0);
      }
      else {
        avatar::getWorldPosition((avatar *)av,&local_34);
        iVar5 = *(int *)&av[1].field_0x38c;
        local_14 = 0;
        local_10 = (weapon *)0x0;
        local_c = (Message *)0x0;
        local_8 = 0.0;
        local_4 = 0.0;
        local_1c = 0x59;
        local_18 = wpn;
        (**(code **)(*(int *)av + 0xc))(av,&local_1c);
        if (local_14 != 0) {
          weapon = local_10;
          param_2 = local_c;
          avatar::getWorldRotation(&wpn->avatar,&local_40);
          local_40.z = local_40.z + local_8;
          Maths::NormaliseAngles2PI(&local_40,&(wpn->avatar).rotEuler);
          (wpn->avatar).anglesCalculated = 0;
          local_44 = local_4;
        }
      }
      BVar4 = SpawnThingFromMarker(&local_40,0,&local_34,iVar5,weapon,(float)param_2,0,0,0,0x19);
      if (BVar4 == 0) {
        local_40.x = local_34.x;
        local_40.y = local_34.y;
        local_40.z = local_34.z;
      }
      FUN_00110bb0(&local_40.y);
      local_40.y = local_40.y + local_44;
      onSignal(wpn,New_Name_(8));
      FUN_00149580();
      return;
    }
    break;
  case Weapon_EscapedBackground:
    if (((actor *)weapon->projectilesCtx != (actor *)0x0) &&
       (BVar4 = actorIsHumanOrNoPrevLL((actor *)weapon->projectilesCtx), BVar4 != 0)) {
      FUN_001456d0(1);
    }
    avatar::destroy(&weapon->avatar);
    return;
  case Weapon_Place:
    avatar::setScaleUniform(&weapon->avatar,1.0);
    onSignal(weapon,SceneBegun);
    avatar::getWorldPosition(&weapon->avatar,&local_34);
    iVar5 = FUN_00110bb0(&param_2);
    if (iVar5 != 0) {
      local_28.x = local_34.x;
      local_40.x = local_34.x;
      local_28.z = local_34.z;
      local_40.z = local_34.z;
      local_28.y = (float)param_2 + 10.0;
      local_40.y = (float)param_2 - 10.0;
      iVar5 = Collision::checkAvatarsWithCollisionInScene(&local_28,&local_40,Ground,(void *)0x0);
      pMVar7 = (Message *)local_40.y;
      if (iVar5 == 0) {
        pMVar7 = param_2;
      }
      local_34.y = (float)pMVar7 + 2.0;
      avatar::setPosition(&weapon->avatar,&local_34);
      return;
    }
    break;
  case Ghouly_InsertFromAid:
    iVar5 = FUN_00147fc0(weapon,&(pMVar7->header).someActor,&pMVar7[0x20].header.someActor,
                         &pMVar7[0x10].header.someActor,&pMVar7[0x30].header.someActor,
                         *(int *)&weapon->field_0xc00 == 0);
    pMVar7[0x40].header.someActor = (actor *)(uint)(iVar5 != 0);
    return;
  case Ghouly_OpenBoxFromAid:
    paVar6 = (actor *)FUN_00148430(&pMVar7[0x10].header.someActor);
    pMVar7[0x20].header.someActor = paVar6;
    return;
  case Ghouly_InsertWeapon:
    iVar5 = FUN_00148270(&(pMVar7->header).someActor);
    pMVar7[0x10].header.someActor = (actor *)(uint)(iVar5 != 0);
    return;
  case Ghouly_InsertPowerup:
    iVar5 = FUN_00148300(&(pMVar7->header).someActor);
    pMVar7[0x10].header.someActor = (actor *)((-(uint)(iVar5 != 0) & 3) - 2);
    return;
  case Background_PartExploded:
    FUN_00145030(pMVar7[1].header.msgId);
    break;
  default:
    goto switchD_001463fe_default;
  }
switchD_001463fe_default:
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void weapon::onBreakableHit(weapon *weapon,Avatar_BreakableHitMessage *msg)

{
  Model *pMVar1;
  ModelDescriptor *pMVar2;
  Subresource0x11 *pSVar3;
  int iVar4;
  int iVar5;
  uint8_t uVar6;
  
  if (*(int *)&weapon->field_0x9a0 == 0) {
    pMVar1 = (weapon->avatar).model;
    if (((pMVar1 == (Model *)0x0) || (pMVar2 = pMVar1->descriptor, pMVar2 == (ModelDescriptor *)0x0)
        ) || (pSVar3 = pMVar2->runtimeCtx->subres0x11, pSVar3 == (Subresource0x11 *)0x0)) {
      uVar6 = '\0';
    }
    else {
      uVar6 = pSVar3->otherCount;
    }
    if (uVar6 != '\0') {
      weapon->weaponState = 0;
      if (*(int *)&msg->field_0x10 != 0) {
        iVar4 = *(int *)(*(int *)&msg->field_0x10 + 0x95c);
        iVar5 = *(int *)(iVar4 + 0x270);
        iVar4 = *(int *)(iVar4 + 0x274);
        if ((iVar5 == 0) || ((*(short *)(iVar5 + 0xcdc) != 2 && (*(int *)(iVar5 + 0x93c) == 0)))) {
          if ((iVar4 == 0) || ((*(short *)(iVar4 + 0xcdc) != 2 && (*(int *)(iVar4 + 0x93c) == 0))))
          {
            weapon->weaponState = 0;
          }
          else {
            weapon->weaponState = 3;
          }
        }
        else {
          weapon->weaponState = 2;
        }
      }
      onDestroy(weapon);
      weapon->arcContactValue = 0;
      (*(weapon->avatar).vtable[1].ctor)(weapon,weapon->attachState,9);
      weapon->attachState = 9;
      weapon->t = 0.0;
      (*(weapon->avatar).vtable[1].getAllocDetails)((ObjectAllocDetails *)weapon);
      (msg->field0_0x0).someActor = (actor *)0x1;
    }
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void weapon::loadGraphics(weapon *param_1)

{
  float fVar1;
  float fVar2;
  short sVar3;
  undefined1 uVar4;
  uint subres0x2index;
  char *pcVar5;
  D3DXMATRIX *iVar10;
  AffineTransform *pAVar6;
  int iVar7;
  ModelFooterEntry *pMVar8;
  int *piVar9;
  int *piVar10;
  Skeleton *pSVar11;
  float fVar12;
  float fVar13;
  int *local_28;
  int i;
  undefined1 local_20 [4];
  float local_1c;
  vec3 v;
  undefined1 local_c [12];
  ModelDescriptor *descriptor;
  Model *instance;
  
  param_1->someFloat = 0.7;
  Assets::GetResourceBytes("aid_texture_ghoulies_weapon_interacthand",(void **)&i);
  if (i == 0) {
    runtime::ExitGame(2);
  }
  param_1->interactHandTexture = (TextureDescriptor *)i;
  param_1->field396_0xadc = 0;
  param_1->field397_0xade = 0;
  param_1->numSomething = 0;
  piVar10 = (int *)0x0;
  while ((instance = (param_1->avatar).model, instance != (Model *)0x0 &&
         (descriptor = instance->descriptor, descriptor != (ModelDescriptor *)0x0))) {
    subres0x2index = 0;
    if (descriptor->numFooterEntries == 0) break;
    pMVar8 = descriptor->footerEntries;
    while (pMVar8->subresourceType != BoneAffines) {
      subres0x2index = subres0x2index + 1;
      pMVar8 = pMVar8 + 1;
      if (descriptor->numFooterEntries <= subres0x2index) goto LAB_00146da1;
    }
    piVar9 = (int *)descriptor->footerEntries[subres0x2index].offset;
    if (piVar9 == (int *)0x0) break;
    if (piVar10 == (int *)0x0) {
      piVar10 = piVar9 + 1;
      piVar9 = piVar10 + *piVar9 * 0xd;
    }
    else {
      piVar10 = piVar10 + 0xd;
      piVar9 = piVar9 + *piVar9 * 0xd + 1;
    }
    while( true ) {
      if (piVar9 <= piVar10) goto LAB_00146da1;
      if ((short)*piVar10 == 1) break;
      piVar10 = piVar10 + 0xd;
    }
    (&param_1->field369_0xab8)[param_1->numSomething] = (int)piVar10;
    param_1->numSomething = param_1->numSomething + 1;
  }
LAB_00146da1:
  pcVar5 = (char *)FUN_00042560(0x400);
  if (pcVar5 != (char *)0x0) {
    do {
      *(char **)(&param_1->field_0xac8 + param_1->field378_0xac4 * 4) = pcVar5;
      param_1->field378_0xac4 = param_1->field378_0xac4 + 1;
      instance = (param_1->avatar).model;
      if ((instance != (Model *)0x0) &&
         (descriptor = instance->descriptor, descriptor != (ModelDescriptor *)0x0)) {
        subres0x2index = 0;
        if (descriptor->numFooterEntries != 0) {
          pMVar8 = descriptor->footerEntries;
          do {
            if (pMVar8->subresourceType == AnimColliders) break;
            subres0x2index = subres0x2index + 1;
            pMVar8 = pMVar8 + 1;
          } while (subres0x2index < descriptor->numFooterEntries);
        }
      }
      if (pcVar5[1] == 0) break;
      pcVar5 = pcVar5 + (byte)pcVar5[1];
      while( true ) {
        if (pcVar5 == (char *)0x0) goto LAB_00146e2c;
        if (((*(uint *)(pcVar5 + 4) & 0x400) != 0) && (*pcVar5 == '\0')) break;
        if (pcVar5[1] == 0) goto LAB_00146e2c;
        pcVar5 = pcVar5 + (byte)pcVar5[1];
      }
    } while( true );
  }
LAB_00146e2c:
  instance = (param_1->avatar).model;
  if (instance == (Model *)0x0) {
    pSVar11 = (Skeleton *)0x0;
  }
  else {
    pSVar11 = instance->skeleton;
    if (pSVar11 == (Skeleton *)0x0) {
      pSVar11 = instance->skeleton2;
    }
  }
  i = 0;
  if (0 < param_1->numSomething) {
    local_28 = &param_1->field369_0xab8;
    do {
      iVar7 = *local_28;
      fVar1 = *(float *)(iVar7 + 0x10);
      fVar2 = *(float *)(iVar7 + 0x20);
      v.z = *(float *)(iVar7 + 0x30);
      sVar3 = *(short *)(iVar7 + 2);
      fVar12 = fVar1;
      fVar13 = fVar2;
      if (-1 < sVar3) {
        if (pSVar11->ignoresGlobalBone == 0) {
          iVar10 = (D3DXMATRIX *)(sVar3 * 0x40);
          ::skeleton::gotten_affine.m[0][0] = *(float *)((int)&(iVar10->field1)._21 + (int)pSVar11);
          iVar7 = (int)&(iVar10->field1)._21 + (int)pSVar11;
          ::skeleton::gotten_affine.m[0][1] = *(float *)(iVar7 + 0x10);
          ::skeleton::gotten_affine.m[0][2] = *(float *)(iVar7 + 0x20);
          ::skeleton::gotten_affine.m[0][3] = *(float *)(iVar7 + 0x30);
          ::skeleton::gotten_affine.m[1][0] = *(float *)(iVar7 + 4);
          ::skeleton::gotten_affine.m[1][1] = *(float *)(iVar7 + 0x14);
          ::skeleton::gotten_affine.m[1][2] = *(float *)(iVar7 + 0x24);
          ::skeleton::gotten_affine.m[1][3] = *(float *)(iVar7 + 0x34);
          ::skeleton::gotten_affine.m[2][0] = *(float *)(iVar7 + 8);
          ::skeleton::gotten_affine.m[2][1] = *(float *)(iVar7 + 0x18);
          ::skeleton::gotten_affine.m[2][2] = *(float *)(iVar7 + 0x28);
          ::skeleton::gotten_affine.m[2][3] = *(float *)(iVar7 + 0x38);
          pAVar6 = &::skeleton::gotten_affine;
        }
        else {
          pAVar6 = pSVar11->boneAffines + sVar3;
        }
        fVar12 = pAVar6->m[0][2] * v.z + pAVar6->m[0][1] * fVar2 + pAVar6->m[0][0] * fVar1 +
                 pAVar6->m[0][3];
        fVar13 = pAVar6->m[1][0] * fVar1 + pAVar6->m[1][2] * v.z + pAVar6->m[1][1] * fVar2 +
                 pAVar6->m[1][3];
        v.z = pAVar6->m[2][0] * fVar1 + pAVar6->m[2][2] * v.z + pAVar6->m[2][1] * fVar2 +
              pAVar6->m[2][3];
      }
      pAVar6 = &(param_1->avatar).drawAffine;
      v.x = fVar12;
      v.y = fVar13;
      if (pAVar6 != (AffineTransform *)0x0) {
        v.x = (param_1->avatar).drawAffine.m[0][2] * v.z +
              (param_1->avatar).drawAffine.m[0][1] * fVar13 + pAVar6->m[0][0] * fVar12 +
              (param_1->avatar).drawAffine.m[0][3];
        v.y = (param_1->avatar).drawAffine.m[1][0] * fVar12 +
              (param_1->avatar).drawAffine.m[1][2] * v.z +
              (param_1->avatar).drawAffine.m[1][1] * fVar13 + (param_1->avatar).drawAffine.m[1][3];
        v.z = (param_1->avatar).drawAffine.m[2][0] * fVar12 +
              (param_1->avatar).drawAffine.m[2][2] * v.z +
              (param_1->avatar).drawAffine.m[2][1] * fVar13 + (param_1->avatar).drawAffine.m[2][3];
      }
      iVar7 = FUN_001476d0(&local_1c,(int *)local_20,local_c,&v,param_1);
      uVar4 = local_20[0];
      if (iVar7 == 0) {
        uVar4 = 0xff;
      }
      (&param_1->field_0xac0)[i] = uVar4;
      i = i + 1;
      local_28 = local_28 + 1;
    } while (i < param_1->numSomething);
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void weapon::calculateRandomValues(weapon *weapon,weaponParams *params)

{
  char cVar1;
  int iVar2;
  char *pcVar3;
  
  runtime::rand = runtime::rand * 0x19660d + 0x3c6ef35f;
  if ((float)(runtime::rand & 0x7fffff | 0x3f800000) - 1.0 <= params->randomThreshold) {
    pcVar3 = &params->field_0x354;
    iVar2 = 0xaec - (int)pcVar3;
    do {
      cVar1 = *pcVar3;
      pcVar3[(int)weapon + iVar2] = cVar1;
      pcVar3 = pcVar3 + 1;
    } while (cVar1 != '\0');
    pcVar3 = &params->field_0x3d4;
    iVar2 = 0xb6c - (int)pcVar3;
    do {
      cVar1 = *pcVar3;
      pcVar3[(int)weapon + iVar2] = cVar1;
      pcVar3 = pcVar3 + 1;
    } while (cVar1 != '\0');
    *(undefined4 *)&weapon->field_0xbf0 = *(undefined4 *)&params->field_0x344;
    *(undefined4 *)&weapon->field_0xbf4 = *(undefined4 *)&params->field_0x348;
    *(undefined4 *)&weapon->field_0xbf8 = *(undefined4 *)&params->field_0x34c;
  }
  *(undefined4 *)&weapon->field_0xbec = *(undefined4 *)&params->field_0x454;
  *(undefined4 *)&weapon->field_0xbfc = *(undefined4 *)&params->field_0x350;
  *(undefined4 *)&weapon->field_0xc00 = 0;
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields

actor * FUN_00147fc0(avatar *param_1,int *param_2,int *param_3,int *param_4,int *param_5,int param_6
                    )

{
  float fVar1;
  int *piVar2;
  actor *paVar3;
  int iVar4;
  float *pfVar5;
  vec3 local_8c;
  vec3 local_80;
  undefined4 local_74;
  float local_70;
  float local_6c;
  float local_68;
  float local_64;
  float local_60;
  float local_5c;
  float local_58;
  undefined4 local_54;
  undefined4 local_50;
  actor *local_4c;
  vec3 local_48;
  undefined4 local_3c;
  float local_38 [4];
  float local_28;
  float local_24;
  float local_1c;
  float local_18;
  float local_14;
  float local_10;
  float local_c;
  float local_8;
  int local_4;
  
  avatar::getWorldPosition(param_1,&local_80);
  if (param_6 == 0) {
    avatar::getWorldRotation(param_1,&local_8c);
  }
  else {
    local_48.x = (Graphics::CurrentCameraStruct->pos).x - local_80.x;
    local_48.y = (Graphics::CurrentCameraStruct->pos).y - local_80.y;
    local_48.z = (Graphics::CurrentCameraStruct->pos).z - local_80.z;
    vec3::getTurnAngle(&local_48,&local_8c.y);
    local_8c.z = 0.0;
    local_8c.x = 0.0;
  }
  if (*param_2 == 0x5f646961) {
    paVar3 = spawnActor(&local_80,&local_8c,(char *)param_2,1.0,(char *)0x0,(char *)0x0,
                        (char *)((*param_4 != 0x5f646961) - 1 & (uint)param_4),
                        (char *)((*param_5 != 0x5f646961) - 1 & (uint)param_5),
                        (char *)((uint)param_3 & (*param_3 != 0x5f646961) - 1),0);
    if (paVar3 != (actor *)0x0) {
      fVar1 = param_1[1].drawAffine.m[0][3];
      if (fVar1 != 0.0) {
        local_70 = 0.0;
        local_6c = 0.0;
        local_68 = 0.0;
        local_64 = 0.0;
        local_60 = 0.0;
        pfVar5 = local_38;
        for (iVar4 = 0xe; iVar4 != 0; iVar4 = iVar4 + -1) {
          *pfVar5 = 0.0;
          pfVar5 = pfVar5 + 1;
        }
        piVar2 = (int *)param_1[1].drawAffine.m[2][2];
        local_5c = 0.0;
        local_58 = 0.0;
        local_54 = 0;
        local_74 = 0x4d;
        local_3c = 0xa6;
        if (piVar2 != (int *)0x0) {
          local_38[0] = local_80.x;
          local_38[1] = local_80.y;
          local_38[2] = local_80.z;
          local_38[3] = local_8c.x;
          local_28 = local_8c.y;
          local_24 = local_8c.z;
          (**(code **)(*piVar2 + 0xc))(piVar2,&local_3c);
        }
        if (local_4 == 0) {
          local_6c = local_80.x;
          local_68 = local_80.y;
          local_64 = local_80.z;
          local_60 = local_8c.x;
          local_5c = local_8c.y;
          local_8 = local_8c.z;
        }
        else {
          local_6c = local_1c;
          local_68 = local_18;
          local_64 = local_14;
          local_60 = local_10;
          local_5c = local_c;
        }
        local_70 = fVar1;
        local_58 = local_8;
        (*((paVar3->avatar).vtable)->onMessage)(paVar3,&local_74);
      }
      local_50 = 0xa4;
      local_4c = paVar3;
      (*param_1->vtable->onMessage)(param_1,&local_50);
      return paVar3;
    }
  }
  return (actor *)0x0;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void weapon::func17OnSomething(void)

{
  CalloutDescriptor **ppCVar1;
  bool bVar2;
  uint uVar3;
  actor *unaff_EBX;
  float10 extraout_ST0;
  float fVar4;
  float fVar5;
  float fVar6;
  vec3 local_18;
  float local_c;
  float local_8;
  float local_4;
  
  if (unaff_EBX->field818_0xcb8 == 0) {
    if (runtime::dx_timer <= 0.0) {
      fVar4 = runtime::DeltaTime * runtime::TimeScale;
    }
    else {
      fVar4 = 0.0;
    }
    fVar6 = 0.0;
    if ((unaff_EBX->avatar).movementFreezeTimer <= 0.0) {
      fVar6 = (unaff_EBX->avatar).actionSpeed;
    }
    fVar5 = (unaff_EBX->someVec3).z;
    if ((fVar5 <= 0.0) ||
       (fVar5 = fVar5 - fVar6 * fVar4, (unaff_EBX->someVec3).z = fVar5, 0.0 < fVar5)) {
      bVar2 = false;
    }
    else {
      (unaff_EBX->someVec3).z = 0.0;
      bVar2 = true;
    }
    fVar4 = 1.0 - (unaff_EBX->someVec3).z * 1.3333334;
    local_18.x = (*(float *)&unaff_EBX->field_0xca8 - *(float *)&unaff_EBX->field_0xc9c) * fVar4 +
                 *(float *)&unaff_EBX->field_0xc9c;
    local_18.y = ((unaff_EBX->someVec3).x - (float)unaff_EBX->skipObjectTypeLookup) * fVar4 +
                 (float)unaff_EBX->skipObjectTypeLookup;
    local_18.z = ((unaff_EBX->someVec3).y - (float)unaff_EBX->field812_0xca4) * fVar4 +
                 (float)unaff_EBX->field812_0xca4;
    sin(fVar4 * 3.1415927);
    cos(fVar4 * 3.1415927);
    local_18.y = (float)extraout_ST0 * 8.0 + local_18.y;
    avatar::setPosition(&unaff_EBX->avatar,&local_18);
    if (bVar2) {
      ppCVar1 = &(unaff_EBX->avatar).callout;
      if (ppCVar1 != (CalloutDescriptor **)0x0) {
        ::actor::executeCalloutInDescriptor
                  (*ppCVar1,Bounce,(CalloutCallback *)0x0,0,unaff_EBX,(entityBodyPlayer_0x924)0x0);
      }
      (unaff_EBX->avatar).physicsPos.x = 0.0;
      (unaff_EBX->avatar).physicsPos.y = 15.0;
      (unaff_EBX->avatar).physicsPos.z = 0.0;
      unaff_EBX->field818_0xcb8 = unaff_EBX->field818_0xcb8 + 1;
      return;
    }
  }
  else {
    fVar4 = 0.0;
    bVar2 = false;
    if (runtime::dx_timer <= 0.0) {
      fVar6 = runtime::DeltaTime * runtime::TimeScale;
    }
    else {
      fVar6 = 0.0;
    }
    if ((unaff_EBX->avatar).movementFreezeTimer <= 0.0) {
      fVar4 = (unaff_EBX->avatar).actionSpeed;
    }
    local_4 = (unaff_EBX->avatar).physicsPos.z;
    fVar4 = fVar4 * fVar6;
    local_c = (unaff_EBX->avatar).physicsPos.x;
    local_8 = (unaff_EBX->avatar).physicsPos.y - fVar4 * 50.0;
    avatar::getWorldPosition(&unaff_EBX->avatar,&local_18);
    local_18.x = local_c * fVar4 + local_18.x;
    local_18.y = local_8 * fVar4 + local_18.y;
    fVar6 = (unaff_EBX->someVec3).x;
    local_18.z = local_4 * fVar4 + local_18.z;
    if ((local_18.y < fVar6) && (local_8 < 0.0)) {
      uVar3 = unaff_EBX->field818_0xcb8 + 1;
      unaff_EBX->field818_0xcb8 = uVar3;
      if ((int)uVar3 < 3) {
        local_8 = local_8 * -0.4;
      }
      else {
        local_4 = 0.0;
        local_8 = 0.0;
        local_c = 0.0;
      }
      bVar2 = (int)uVar3 >= 3;
      local_18.y = fVar6;
    }
    (unaff_EBX->avatar).physicsPos.x = local_c;
    (unaff_EBX->avatar).physicsPos.y = local_8;
    (unaff_EBX->avatar).physicsPos.z = local_4;
    avatar::setPosition(&unaff_EBX->avatar,&local_18);
    if (bVar2) {
      *(undefined2 *)&unaff_EBX->field_0xc0e = 0x10;
    }
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void weapon::func17(void)

{
  CalloutDescriptor **ppCVar1;
  bool bVar2;
  int iVar3;
  actor *unaff_EBX;
  float10 extraout_ST0;
  float fVar4;
  float fVar5;
  float fVar6;
  vec3 local_18;
  float local_c;
  float local_8;
  float local_4;
  
  if (unaff_EBX->numSomethings == 0) {
    if (runtime::dx_timer <= 0.0) {
      fVar4 = runtime::DeltaTime * runtime::TimeScale;
    }
    else {
      fVar4 = 0.0;
    }
    fVar6 = 0.0;
    if ((unaff_EBX->avatar).movementFreezeTimer <= 0.0) {
      fVar6 = (unaff_EBX->avatar).actionSpeed;
    }
    fVar5 = (unaff_EBX->world_rot_).z;
    if ((fVar5 <= 0.0) ||
       (fVar5 = fVar5 - fVar6 * fVar4, (unaff_EBX->world_rot_).z = fVar5, 0.0 < fVar5)) {
      bVar2 = false;
    }
    else {
      (unaff_EBX->world_rot_).z = 0.0;
      bVar2 = true;
    }
    fVar4 = 1.0 - (unaff_EBX->world_rot_).z * 1.3333334;
    local_18.x = ((unaff_EBX->setup_position_).z - *(float *)&unaff_EBX->field_0xcbc) * fVar4 +
                 *(float *)&unaff_EBX->field_0xcbc;
    local_18.y = ((unaff_EBX->world_rot_).x - (unaff_EBX->setup_position_).x) * fVar4 +
                 (unaff_EBX->setup_position_).x;
    local_18.z = ((unaff_EBX->world_rot_).y - (unaff_EBX->setup_position_).y) * fVar4 +
                 (unaff_EBX->setup_position_).y;
    sin(fVar4 * 3.1415927);
    cos(fVar4 * 3.1415927);
    local_18.y = (float)extraout_ST0 * 8.0 + local_18.y;
    avatar::setPosition(&unaff_EBX->avatar,&local_18);
    if (bVar2) {
      ppCVar1 = &(unaff_EBX->avatar).callout;
      if (ppCVar1 != (CalloutDescriptor **)0x0) {
        ::actor::executeCalloutInDescriptor
                  (*ppCVar1,Bounce,(CalloutCallback *)0x0,0,unaff_EBX,(entityBodyPlayer_0x924)0x0);
      }
      (unaff_EBX->avatar).physicsPos.x = 0.0;
      (unaff_EBX->avatar).physicsPos.y = 15.0;
      (unaff_EBX->avatar).physicsPos.z = 0.0;
      unaff_EBX->numSomethings = unaff_EBX->numSomethings + 1;
      return;
    }
  }
  else {
    fVar4 = 0.0;
    bVar2 = false;
    if (runtime::dx_timer <= 0.0) {
      fVar6 = runtime::DeltaTime * runtime::TimeScale;
    }
    else {
      fVar6 = 0.0;
    }
    if ((unaff_EBX->avatar).movementFreezeTimer <= 0.0) {
      fVar4 = (unaff_EBX->avatar).actionSpeed;
    }
    local_4 = (unaff_EBX->avatar).physicsPos.z;
    fVar4 = fVar4 * fVar6;
    local_c = (unaff_EBX->avatar).physicsPos.x;
    local_8 = (unaff_EBX->avatar).physicsPos.y - fVar4 * 50.0;
    avatar::getWorldPosition(&unaff_EBX->avatar,&local_18);
    local_18.x = local_c * fVar4 + local_18.x;
    local_18.y = local_8 * fVar4 + local_18.y;
    fVar6 = (unaff_EBX->world_rot_).x;
    local_18.z = local_4 * fVar4 + local_18.z;
    if ((local_18.y < fVar6) && (local_8 < 0.0)) {
      iVar3 = unaff_EBX->numSomethings + 1;
      unaff_EBX->numSomethings = iVar3;
      if (iVar3 < 3) {
        local_8 = local_8 * -0.4;
      }
      else {
        local_4 = 0.0;
        local_8 = 0.0;
        local_c = 0.0;
      }
      bVar2 = iVar3 >= 3;
      local_18.y = fVar6;
    }
    (unaff_EBX->avatar).physicsPos.x = local_c;
    (unaff_EBX->avatar).physicsPos.y = local_8;
    (unaff_EBX->avatar).physicsPos.z = local_4;
    avatar::setPosition(&unaff_EBX->avatar,&local_18);
    if (bVar2) {
      *(undefined2 *)&unaff_EBX->field_0xc0e = 0x10;
    }
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void weapon::doSomething(weapon *wpn,void *this)

{
  WeaponProjectilesContext *pWVar1;
  undefined4 uVar2;
  Collision0x54 *pCVar3;
  int iVar4;
  void *ptr;
  BOOL BVar5;
  AudioParentState extraout_ECX;
  float10 fVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  float fVar10;
  float fVar11;
  vec3 local_3c;
  vec3 local_30;
  vec3 local_24;
  vec3 local_18;
  vec3 local_c;
  
  pWVar1 = wpn->projectilesCtx;
  if (pWVar1 == (WeaponProjectilesContext *)0x0) {
    wpn->field9_0x93c = 0;
    if (wpn->field_0xd08 != '\0') {
      wpn->field_0xd08 = 0;
      if (wpn->field1044_0xd88 != -1) {
        AudioParent::UpdateState
                  (0,Audio::SoundSources + (short)wpn->field1044_0xd88,(AudioParentState)this);
        wpn->field1044_0xd88 = 0xffff;
      }
    }
    wpn->arcContactValue = 0;
    (*(wpn->avatar).vtable[1].ctor)(wpn,wpn->attachState,9);
    wpn->attachState = 9;
    wpn->t = 0.0;
    (*(wpn->avatar).vtable[1].getAllocDetails)((ObjectAllocDetails *)wpn);
    return;
  }
  fVar7 = 0.0;
  if (runtime::dx_timer <= 0.0) {
    fVar9 = runtime::DeltaTime * runtime::TimeScale;
  }
  else {
    fVar9 = 0.0;
  }
  if ((wpn->avatar).movementFreezeTimer <= 0.0) {
    fVar7 = (wpn->avatar).actionSpeed;
  }
  fVar7 = fVar7 * fVar9;
  iVar4 = FUN_00149d20(wpn,&local_18);
  if (iVar4 == 0) {
    wpn->field9_0x93c = 0;
    if (wpn->field_0xd08 != '\0') {
      wpn->field_0xd08 = 0;
      if (wpn->field1044_0xd88 != -1) {
        AudioParent::UpdateState(0,Audio::SoundSources + (short)wpn->field1044_0xd88,extraout_ECX);
        wpn->field1044_0xd88 = 0xffff;
      }
    }
    onSignal(wpn,Destroy);
    return;
  }
  avatar::getWorldPosition(&wpn->avatar,&local_30);
  uVar2 = *(undefined4 *)&pWVar1->field_0x1f0;
  fVar8 = local_18.x * fVar7;
  fVar10 = local_18.y * fVar7;
  fVar11 = local_18.z * fVar7;
  local_3c.x = local_30.x + fVar8;
  local_3c.y = local_30.y + fVar10;
  local_3c.z = local_30.z + fVar11;
  *(undefined4 *)&pWVar1->field_0x1f0 = 0;
  fVar6 = FUN_0003d9a0(&wpn->avatar);
  fVar9 = (float)fVar6;
  if (*(int *)&wpn->field_0xcdc != 0) {
    if ((*(int *)&wpn->field_0xcf8 == 0) &&
       (iVar4 = Collision::runWeaponCollision(&local_30,fVar9,Ground|Walls,FUN_000c4000), 0 < iVar4)
       ) {
      ptr = (void *)FUN_00122310();
      FUN_000fc3f0(ptr,&local_30,fVar9);
      free(ptr);
      local_30.x = local_24.x;
      local_30.y = local_24.y;
      local_30.z = local_24.z;
      avatar::setPosition(&wpn->avatar,&local_30);
      local_3c.x = fVar8 + local_30.x;
      local_3c.y = fVar10 + local_30.y;
      local_3c.z = fVar11 + local_30.z;
    }
    *(undefined4 *)&wpn->field_0xcdc = 0;
  }
  if (*(int *)&wpn->field_0xcf8 == 0) {
    local_24.x = local_3c.x;
    local_24.y = local_3c.y;
    local_24.z = local_3c.z;
    BVar5 = Collision::runCollisionFunctionWithAllAvatars
                      (&local_24,&local_30,fVar9,Ground|Walls,FUN_000c4000);
    if (BVar5 == 1) {
      pCVar3 = (Physics::CollisionContexts[0].ctx)->head;
      local_c.x = (pCVar3->velocity).x;
      local_c.z = (pCVar3->velocity).z;
      local_c.y = (pCVar3->velocity).y;
      if (local_c.y < 0.9) {
        FUN_00103330(&local_30);
        goto LAB_00149ad8;
      }
    }
    local_3c.x = local_24.x;
    local_3c.y = local_24.y;
    local_3c.z = local_24.z;
  }
LAB_00149ad8:
  *(undefined4 *)&pWVar1->field_0x1f0 = uVar2;
  iVar4 = FUN_00105e20(&local_18,(float *)&wpn->field_0xce4,(float *)&wpn->field_0xce0);
  if (iVar4 == 0) {
    *(undefined4 *)&wpn->field_0xce8 = 0;
    *(undefined4 *)&wpn->field_0xce4 = 0;
    *(undefined4 *)&wpn->field_0xce0 = 0;
  }
  else {
    *(undefined4 *)&wpn->field_0xce8 = 0;
  }
  avatar::getWorldRotation(&wpn->avatar,&local_c);
  FUN_00105b90(PI,fVar7);
  Maths::NormaliseAngles2PI(&local_c,&(wpn->avatar).rotEuler);
  (wpn->avatar).anglesCalculated = 0;
  if ((Background::HasBounds != '\0') &&
     (((((local_3c.x < Background::MinVector.x || (Background::MaxVector.x <= local_3c.x)) ||
        (local_3c.y < Background::MinVector.y)) ||
       ((Background::MaxVector.y <= local_3c.y || (local_3c.z < Background::MinVector.z)))) ||
      (Background::MaxVector.z <= local_3c.z)))) {
    avatar::destroy(&wpn->avatar);
  }
  if (((ShouldntDroneBools[1] == 0) && ("\x01"[Game::CheckMoveOn] != '\0')) &&
     ((ShouldntDroneBools[0] == 0 && ("\x01"[Game::CheckMoveOn] != '\0')))) {
    (wpn->avatar).physicsPos.x = local_18.x;
    (wpn->avatar).physicsPos.y = local_18.y;
    (wpn->avatar).physicsPos.z = local_18.z;
    avatar::setPosition(&wpn->avatar,&local_3c);
    return;
  }
  (wpn->avatar).physicsPos.z = 0.0;
  (wpn->avatar).physicsPos.y = 0.0;
  (wpn->avatar).physicsPos.x = 0.0;
  return;
}




void weapon::func15(int param_1,undefined2 param_2)

{
  switch(param_2) {
  case 2:
    FUN_001487c0();
    return;
  case 5:
  case 8:
    *(uint *)(param_1 + 0x1f0) = *(uint *)(param_1 + 0x1f0) & 0xfffffeff;
    return;
  case 10:
    FUN_001495c0(param_1);
  }
  return;
}




void weapon::func16(int param_1,undefined2 param_2)

{
  switch(param_2) {
  case 2:
    FUN_00148850();
    return;
  case 3:
  case 4:
  case 6:
  case 7:
  case 9:
    goto switchD_0014a18e_caseD_3;
  case 5:
    *(uint *)(param_1 + 0x1f0) = *(uint *)(param_1 + 0x1f0) | 0x100;
    *(float *)(param_1 + 0x3c) = Game::someGlobalPos.x;
    *(float *)(param_1 + 0x40) = Game::someGlobalPos.y;
    *(float *)(param_1 + 0x44) = Game::someGlobalPos.z;
    return;
  case 8:
    *(uint *)(param_1 + 0x1f0) = *(uint *)(param_1 + 0x1f0) | 0x100;
    return;
  case 10:
    FUN_001496d0();
switchD_0014a18e_caseD_3:
    return;
  default:
    return;
  }
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void weapon::func17(weapon *param_1,undefined2 param_2)

{
  switch(param_2) {
  case 2:
    FUN_001488d0(param_1);
    return;
  case 3:
  case 4:
  case 6:
  case 7:
  case 9:
    goto switchD_0014a22e_default;
  case 5:
    func17OnSomething();
    return;
  case 8:
    func17();
    return;
  case 10:
    doSomething(param_1,param_1);
switchD_0014a22e_default:
    return;
  default:
    return;
  }
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void weapon::onSignal(weapon *wpn,WeaponSignal signal)

{
  wpn->arcContactValue = 0;
  (*(wpn->avatar).vtable[1].ctor)(wpn,wpn->attachState,signal);
  wpn->attachState = (short)signal;
  wpn->t = 0.0;
  (*(wpn->avatar).vtable[1].getAllocDetails)((ObjectAllocDetails *)wpn);
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void weapon::update(weapon *weapon)

{
  float fVar1;
  float fVar2;
  float fVar3;
  short sVar4;
  avatar_0x918 pEVar5;
  int iVar6;
  Model *pMVar7;
  ModelSubresource *pMVar8;
  WeaponProjectilesContext *pWVar9;
  DataForInfoFromBackground_conflict1 *node;
  int iVar10;
  float speed;
  float fVar11;
  float delta;
  KeyframeContext *kfc;
  
  speed = 0.0;
  if (runtime::dx_timer <= 0.0) {
    delta = runtime::DeltaTime * runtime::TimeScale;
  }
  else {
    delta = 0.0;
  }
  if ((weapon->avatar).movementFreezeTimer <= 0.0) {
    speed = (weapon->avatar).actionSpeed;
  }
  weapon->t = speed * delta + weapon->t;
                    // Run callouts/pickup
  (*(weapon->avatar).vtable[1].dtor)(weapon,weapon->attachState);
  pEVar5 = (weapon->avatar).node0x918.prev;
  if ((((pEVar5 != (avatar_0x918)0x0) && (pEVar5->prev != (avatar_0x918)0x0)) &&
      (pEVar5 != (avatar_0x918)0x918)) &&
     ((weapon->avatar).keyframeContext != (KeyframeContext *)0x0)) {
    FUN_00030db0();
  }
  speed = 0.0;
  if (runtime::dx_timer <= 0.0) {
    delta = runtime::DeltaTime * runtime::TimeScale;
  }
  else {
    delta = 0.0;
  }
  if ((weapon->avatar).movementFreezeTimer <= 0.0) {
    speed = (weapon->avatar).actionSpeed;
  }
  kfc = (weapon->avatar).keyframeContext;
  if (kfc != (KeyframeContext *)0x0) {
    KeyframeContext::updateFromAvatar
              (kfc,(weapon->avatar).model,(uint)((weapon->avatar).preventAnimChannelAdvancing == 0),
               speed * delta);
  }
  kfc = (weapon->avatar).keyframeContext;
  if (kfc != (KeyframeContext *)0x0) {
    KeyframeContext::updateSkeletonAndBlendTargets
              ((uint)((weapon->avatar).preventAnimChannelAdvancing == 0),kfc,(weapon->avatar).model,
               (weapon->avatar).boneList);
  }
  iVar10 = *(int *)&(weapon->avatar).field_0x1d8;
  while (iVar10 != 0) {
    iVar6 = *(int *)(iVar10 + 4);
    (**(code **)(*(int *)(iVar10 + -8) + 0x10))(iVar10 + -8,weapon);
    iVar10 = iVar6;
  }
  avatar::updateFx(&weapon->avatar);
  speed = (weapon->avatar).smoothedTargetPos.z;
  delta = (weapon->avatar).smoothedTargetPos.y;
  fVar11 = (weapon->avatar).smoothedTargetPos.x;
  if (Game::UseMovementSmoothing != 0) {
    fVar1 = (weapon->avatar).smoothedCurrentPos.x;
    fVar2 = (weapon->avatar).smoothedCurrentPos.y;
    fVar3 = (weapon->avatar).smoothedCurrentPos.z;
    fVar11 = (fVar11 - fVar1) * 0.1 + fVar1;
    delta = (delta - fVar2) * 0.1 + fVar2;
    speed = (speed - fVar3) * 0.1 + fVar3;
  }
  (weapon->avatar).smoothedCurrentPos.x = fVar11;
  (weapon->avatar).smoothedCurrentPos.y = delta;
  (weapon->avatar).smoothedCurrentPos.z = speed;
  pMVar7 = (weapon->avatar).model;
  if ((pMVar7 != (Model *)0x0) &&
     (pMVar8 = pMVar7->modelPassedToBG, pMVar8 != (ModelSubresource *)0x0)) {
    background::updateModelChildren_(pMVar8,1.0);
  }
  pEVar5 = (weapon->avatar).node0x918.prev;
  if (((pEVar5 != (avatar_0x918)0x0) && (pEVar5->prev != (avatar_0x918)0x0)) &&
     (pEVar5 != (avatar_0x918)0x918)) {
    avatar::updateBaseTransform(&weapon->avatar);
  }
  pWVar9 = weapon->projectilesCtx;
  if (pWVar9 == (WeaponProjectilesContext *)0x0) {
    speed = 1.0;
  }
  else {
    speed = 0.0;
    if (*(float *)&pWVar9->field_0x930 <= 0.0) {
      speed = *(float *)&pWVar9->field_0x92c;
    }
  }
  (weapon->avatar).actionSpeed = speed;
  (*(weapon->avatar).vtable[1].onMessage)(weapon,weapon->attachState);
  FUN_00145a40();
  FUN_00144e30(weapon);
  pEVar5 = (weapon->avatar).node0x918.prev;
  if (((pEVar5 != (avatar_0x918)0x0) && (pEVar5->prev != (avatar_0x918)0x0)) &&
     (ADJ(pEVar5) != (avatar *)0x0)) {
    FUN_00147b30(ADJ(pEVar5));
  }
  sVar4 = weapon->arcContactValue;
  if (sVar4 != 0) {
    weapon->arcContactValue = 0;
    (*(weapon->avatar).vtable[1].ctor)(weapon,weapon->attachState,sVar4);
    weapon->attachState = sVar4;
    weapon->t = 0.0;
    (*(weapon->avatar).vtable[1].getAllocDetails)((ObjectAllocDetails *)weapon);
  }
  for (node = (weapon->avatar).infoList.prev; node != (DataForInfoFromBackground_conflict1 *)0x0;
      node = (DataForInfoFromBackground_conflict1 *)node->field1_0x4) {
    FUN_0011be40((AvatarInfoNode *)node);
  }
  FUN_00148510();
  BreakWeapon();
  FUN_0014a6d0();
  FUN_00147160();
  FUN_0014a770();
  if ((ShouldntDroneBools[1] == 0) && ("\x01"[Game::CheckMoveOn] != '\0')) {
    if (runtime::dx_timer <= 0.0) {
      speed = runtime::DeltaTime * runtime::TimeScale;
    }
    else {
      speed = 0.0;
    }
    delta = (weapon->avatar).movementFreezeTimer;
    if ((0.0 < delta) &&
       (delta = delta - speed, (weapon->avatar).movementFreezeTimer = delta, delta <= 0.0)) {
      (weapon->avatar).movementFreezeTimer = 0.0;
    }
  }
  speed = 0.0;
  if (runtime::dx_timer <= 0.0) {
    delta = runtime::DeltaTime * runtime::TimeScale;
  }
  else {
    delta = 0.0;
  }
  if ((weapon->avatar).movementFreezeTimer <= 0.0) {
    speed = (weapon->avatar).actionSpeed;
  }
  (weapon->avatar).timeAlive = speed * delta + (weapon->avatar).timeAlive;
  (weapon->avatar).timesUpdated = (weapon->avatar).timesUpdated + 1;
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


