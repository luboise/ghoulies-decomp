/* game_core.c - Core game state, world update, save */
#include "game_core.h"

actorBodyStateId actorBodyStateId::fromString(char *param_1)

{
  uint uVar1;
  
  uVar1 = Events::GetIndexOfStringInTable(0x174,PTR_ARRAY_003390e0 + 1,param_1);
  if (uVar1 == 0xffffffff) {
    return Null;
  }
                    // Add 1 to skip null since we are searching from null + 1 onwards
  return (short)uVar1 + Angry;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void runtime::ExitGame(int exitCode)

{
  LanguageID LVar1;
  int fps_target;
  
  if (game::prevent_exiting == (bool *)0x0) {
                    // Writes to index.dat
    MarkForDeletion("Z:\\index.dat");
    LVar1 = LanguageID;
    ExitCode = exitCode;
    SwapBuffers_(LanguageID);
    SwapBuffers_(LVar1);
    do {
      if ((Config::IsPal == 0) || (fps_target = 50, Config::Use60Hz != 0)) {
        fps_target = 60;
      }
      DeathLoop(1.0 / (float)fps_target);
    } while( true );
  }
  return;
}




void FUN_000481e0(GamePauseContext *gpc)

{
  undefined1 index;
  undefined1 valueToSearch;
  uint uVar1;
  
  if (*(int *)&Cutscene::PauseCutsceneLookupTable[gpc->id].field_0x118 != -1) {
    uVar1 = Cutscene::getEventIdFromModelName
                      (gpc->cutsceneBuffer,Cutscene::PauseCutsceneLookupTable[gpc->id].cutsceneModel
                      );
    index = Cutscene::PauseCutsceneLookupTable[gpc->id].field_0x118;
    valueToSearch = Cutscene::PauseCutsceneLookupTable[gpc->id].field_0x11c;
    if (*(Model **)(uVar1 + 0x204) != (Model *)0x0) {
      ModelInstance::searchForValueWithFlags(valueToSearch,*(Model **)(uVar1 + 0x204),index);
    }
    if (*(Model **)(uVar1 + 0x310) != (Model *)0x0) {
      ModelInstance::searchForValueWithFlags(valueToSearch,*(Model **)(uVar1 + 0x310),index);
    }
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void UpdateDoor(short doorId,ushort doorState,int param_3,BOOL nothingToRun)

{
  Draw2D **ppDVar1;
  ushort cutsceneEventType;
  Buffer<Draw2D> *pBVar2;
  undefined2 in_register_00000002;
  BOOL BVar3;
  Cutscene *pCVar4;
  Cutscene *dst;
  undefined2 in_stack_00000006;
  char local_100 [128];
  char local_80 [128];
  
  for (dst = (Cutscene *)game::doors->head; dst < (Cutscene *)game::doors->tail;
      dst = (Cutscene *)((dst->events).field6_0x6 + (game::doors->valueSize - 0x4e))) {
    if (*(short *)&(dst->v2).y == doorId) goto LAB_0005b5a7;
  }
  FUN_0005b2d0(0xc,CONCAT22(in_register_00000002,doorId));
  dst = (Cutscene *)FUN_000663b0((Buffer<AudioSmth> *)game::doors,FUN_0005b870);
LAB_0005b5a7:
  if (doorState == 6) {
    if (dst != (Cutscene *)0x0) {
      pCVar4 = *(Cutscene **)&(dst->events).field_0xf8;
      if (pCVar4 != (Cutscene *)0x0) {
        Cutscene::dtor(pCVar4);
        *(undefined4 *)&(dst->events).field_0xf8 = 0;
      }
      pCVar4 = *(Cutscene **)&(dst->events).field_0xfc;
      if (pCVar4 != (Cutscene *)0x0) {
        Cutscene::dtor(pCVar4);
        *(undefined4 *)&(dst->events).field_0xfc = 0;
      }
      pBVar2 = game::doors;
      ppDVar1 = &game::doors->tail;
      pCVar4 = (Cutscene *)((int)*ppDVar1 - (uint)game::doors->valueSize);
      if (dst < pCVar4) {
        memcpy(dst,pCVar4,(uint)game::doors->valueSize);
      }
      *ppDVar1 = (Draw2D *)((int)*ppDVar1 - (uint)pBVar2->valueSize);
      return;
    }
  }
  else if (doorState == 7) {
    FUN_0005a9b0(dst);
    pCVar4 = *(Cutscene **)&(dst->events).field_0xf8;
    if (pCVar4 != (Cutscene *)0x0) {
      Cutscene::dtor(pCVar4);
      *(undefined4 *)&(dst->events).field_0xf8 = 0;
    }
    pCVar4 = *(Cutscene **)&(dst->events).field_0xfc;
    if (pCVar4 != (Cutscene *)0x0) {
      Cutscene::dtor(pCVar4);
      *(undefined4 *)&(dst->events).field_0xfc = 0;
    }
  }
  else {
    cutsceneEventType = *(short *)((int)&(dst->v2).y + 2);
    if (doorState != cutsceneEventType) {
      if (*(int *)&(dst->events).field_0x100 == 0) {
        FindDoorCameras(doorState,(uint)(dst->v2).x,local_100,local_80,*(undefined2 *)&(dst->v2).y,
                        (uint)(doorState == 0));
        *(ushort *)((int)&(dst->v2).y + 2) = doorState;
        *(ushort *)&(dst->v2).z = (ushort)(doorState == 0);
      }
      else {
        FindDoorCameras(cutsceneEventType,(uint)(dst->v2).x,local_100,local_80,
                        *(undefined2 *)&(dst->v2).y,_doorState);
        *(ushort *)&(dst->v2).z = doorState;
      }
      BVar3 = Assets::AssetNamesMatch(local_100,(dst->events).field6_0x6 + 0x72);
      if (BVar3 == 0) {
        FUN_0005b960(dst,local_100);
      }
      if (*(int *)&(dst->events).field_0x100 == 0) {
        FUN_0005bdb0();
      }
      else {
        FocusOnDoors_((int)dst,1);
        if (param_3 == 0) {
                    // Close the door and update state
          CloseDoorAndUpdateState(0,*(Cutscene **)&(dst->events).field_0xf8);
        }
        pCVar4 = *(Cutscene **)&(dst->events).field_0xfc;
        if ((pCVar4 != (Cutscene *)0x0) ||
           (pCVar4 = *(Cutscene **)&(dst->events).field_0xf8, pCVar4->descriptor->numCameras != '\0'
           )) {
          Cutscene::updateCameraFromCutscene(pCVar4,&g_doorsProjectionSet);
        }
      }
      *(int *)&(dst->events).field_0x104 = param_3;
      dst->onEndCallback = nothingToRun;
    }
  }
  *(undefined4 *)&(dst->events).field_0x100 = 1;
  return;
}




undefined4 updateAvatarAgainstDoor(avatar *param_1,entityBodyHuman *human)

{
  float fVar1;
  undefined1 *puVar2;
  int collided;
  void *ptr;
  float fVar3;
  vec3 local_24;
  float local_18;
  float local_14;
  float local_10;
  float local_c;
  float local_8;
  float local_4;
  
  avatar::getWorldPosition(param_1,&local_24);
  fVar1 = (param_1->scale).z;
  local_18 = local_24.x;
  local_10 = local_24.z;
  fVar3 = human->someFloat2 * fVar1;
  local_14 = human->physicsScalar * fVar1 + fVar3 + 0.5 + local_24.y;
  puVar2 = actorBody::getCollisionDrone(&human->body);
  collided = Collision::runWeaponCollision(&local_18,fVar3,Walls,puVar2);
  if (collided != 0) {
    ptr = (void *)FUN_00122310();
    FUN_000fc3f0(ptr,&local_18,fVar3);
    local_24.x = (local_c - local_18) + local_24.x;
    local_24.y = (local_8 - local_14) + local_24.y;
    local_24.z = (local_4 - local_10) + local_24.z;
    avatar::setPosition(param_1,&local_24);
    free(ptr);
    return 1;
  }
  return 0;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


actorBodyStateId FUN_00075a70(actorBody *param_1)

{
  actorBodyStateId aVar1;
  
  if ((char)*(byte *)((int)&param_1->flagSet->flags->flag1 + 1) < '\0') {
    return AngryStand;
  }
  aVar1 = actorBody::getStandingState(param_1);
  return aVar1;
}




actorBodyStateId FUN_00076100(actorBody *param_1)

{
  actorBodyStateId aVar1;
  
  if ((param_1->flagSet->flags->flag1 & 0x80000) != Null) {
    return StandBig;
  }
  aVar1 = actorBody::getStandingState(param_1);
  return aVar1;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


actorBodyStateId FUN_00076130(actorBody *param_1)

{
  actorBodyStateId aVar1;
  
  if ((param_1->flagSet->flags->flag1 & 0x80000) != Null) {
    return WalkBig;
  }
  aVar1 = actorBody::getWalkState(param_1);
  return aVar1;
}




actorBodyStateId FUN_00076210(actorBody *param_1)

{
  actorBodyStateId aVar1;
  
  if (((param_1->field_0x2d0 != '\0') && (param_1->field_0x2d0 == '\x01')) &&
     (param_1->field_0x2d2 != '\0')) {
    return StandWithoutLimb;
  }
  aVar1 = actorBody::getStandingState(param_1);
  return aVar1;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


actorBodyStateId FUN_00076250(actorBody *param_1)

{
  actorBodyStateId aVar1;
  
  if (((param_1->field_0x2d0 != '\0') && (param_1->field_0x2d0 == '\x01')) &&
     (param_1->field_0x2d2 != '\0')) {
    return WalkWithoutLimb;
  }
  aVar1 = actorBody::getWalkState(param_1);
  return aVar1;
}




void FUN_00083d90(entitySceneControlGameSelect *param_1)

{
  GamePauseContext *pGVar1;
  Cutscene *pCVar2;
  float fVar3;
  uint index;
  
  pGVar1 = param_1->gamePauseCtx;
  if ((pGVar1 != (GamePauseContext *)0x0) && (pGVar1->field7_0x10 != 0)) {
    FromPlayToPause(pGVar1);
    param_1->gamePauseCtx = (GamePauseContext *)0x0;
  }
  if (param_1->gamePauseCtx != (GamePauseContext *)0x0) {
    FUN_000483e0(param_1->gamePauseCtx);
    pGVar1 = param_1->gamePauseCtx;
    index = pGVar1->id;
    pCVar2 = pGVar1->cutsceneBuffer;
    fVar3 = pCVar2->t / pCVar2->length;
    if (fVar3 < Cutscene::PauseCutsceneLookupTable[index].tToDoLoad ||
        fVar3 == Cutscene::PauseCutsceneLookupTable[index].tToDoLoad) {
      index = Cutscene::PauseCutsceneLookupTable[index].field5_0x10c;
    }
    else {
      fVar3 = pCVar2->t / pCVar2->length;
      if (fVar3 < Cutscene::PauseCutsceneLookupTable[index].tToSwapBuffers ||
          fVar3 == Cutscene::PauseCutsceneLookupTable[index].tToSwapBuffers) {
        return;
      }
      index = Cutscene::PauseCutsceneLookupTable[index].field6_0x110;
    }
    if (index != 0xffffffff) {
      *(float *)((int)(&pGVar1->cameraCfg + 1) + (index * 4 + 3) * 4) = 1.4013e-45;
    }
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


undefined4 __fastcall FUN_00083e20(entitySceneControlGameSelect *entity)

{
  Cutscene *pCVar1;
  float cutscene_progress_;
  int status;
  
  status = entity->status;
  if (status == 1) {
    return 1;
  }
  if (status == 2) {
    pCVar1 = entity->gamePauseCtx->cutsceneBuffer;
    cutscene_progress_ = pCVar1->t / pCVar1->length;
    if (Cutscene::PauseCutsceneLookupTable[entity->gamePauseCtx->id].tToDoLoad <= cutscene_progress_
        && cutscene_progress_ !=
           Cutscene::PauseCutsceneLookupTable[entity->gamePauseCtx->id].tToDoLoad) {
      return 1;
    }
  }
  else {
    if (status != 3) {
      return 1;
    }
    pCVar1 = entity->gamePauseCtx->cutsceneBuffer;
    cutscene_progress_ = pCVar1->t / pCVar1->length;
    if (Cutscene::PauseCutsceneLookupTable[entity->gamePauseCtx->id].tToDoLoad <= cutscene_progress_
        && cutscene_progress_ !=
           Cutscene::PauseCutsceneLookupTable[entity->gamePauseCtx->id].tToDoLoad) {
      return 1;
    }
  }
  return 0;
}




void FUN_00092d10(entityStateGenerateGhouly *param_1)

{
  int iVar1;
  undefined4 *puVar2;
  
  puVar2 = (undefined4 *)&param_1->field_0x32c;
  iVar1 = 2;
  do {
    FUN_00092ff0(*(undefined4 *)&param_1->field_0x348,*(undefined4 *)&param_1->field_0x34c,*puVar2);
    puVar2 = puVar2 + 3;
    iVar1 = iVar1 + -1;
  } while (iVar1 != 0);
  return;
}




void FUN_00094800(actorState param_1,undefined4 param_2)

{
  Marker *pMVar1;
  void *pvVar2;
  actor *paVar3;
  uint uVar4;
  actorStateVTable *paVar5;
  uint16_t uVar6;
  BoneAffineSubresourceEntry *pBVar7;
  int iVar8;
  uint16_t uVar9;
  Marker *pMVar10;
  uint uVar11;
  actorBody *local_1c;
  vec3 local_18;
  vec3 local_c;
  actorStateVTable *iVar6;
  
  iVar6 = param_1.vtable;
  pvVar2 = (param_1.vtable)->dtor;
  paVar3 = *(actor **)((int)pvVar2 + 8);
  if (paVar3->mind == (actorMind *)0x0) {
    local_1c = (actorBody *)0x0;
  }
  else {
    local_1c = paVar3->mind->targetBody;
  }
  iVar8 = param_1._4_4_;
  (param_1.vtable)->func6 = *(void **)(iVar8 + 0xc);
  *(undefined2 *)&(param_1.vtable)->func7 = *(undefined2 *)(iVar8 + 0x10);
  param_1.vtable = (actorStateVTable *)paVar3;
  pBVar7 = actor::getModelBoneAffineByBone1(paVar3,*(undefined2 *)(iVar8 + 0x12));
  iVar6[2].func6 = (void *)0x0;
  iVar6[1].getAllocDetails = (getAllocDetailsFn *)pBVar7;
  avatar::getWorldPosition((avatar *)param_1.vtable,&local_18);
  iVar6[1].func5 = (void *)0x0;
  iVar6[1].update = (void *)0x0;
  iVar6[1].onMessage = (void *)0x0;
  iVar6[1].func6 = (void *)0x0;
  if (*(char *)&local_1c->largeProjectile == '\0') {
    iVar6[1].ctor = local_1c->currentWeapon;
  }
  param_1._4_2_ = *(undefined2 *)&param_1.vtable[0xf].func7;
  param_1.tag = Null;
  if ((param_1._4_2_ != 0) &&
     (uVar6 = Marker::nextIdOfNextMarkerOfType(Unknown0x1a,1,0), uVar6 != 0)) {
    uVar4 = (Game::GameState.markerInstance)->numMarkers;
    pMVar1 = (Game::GameState.markerInstance)->marker;
    do {
      uVar11 = 0;
      pMVar10 = pMVar1;
      if (uVar4 != 0) {
        do {
          if (pMVar10->id == uVar6) {
            uVar9 = pMVar10->runtimeId;
            goto LAB_000948d7;
          }
          pMVar10 = (Marker *)((int)&pMVar10->size + pMVar10->size);
          uVar11 = uVar11 + 1;
        } while (uVar11 < uVar4);
      }
      uVar9 = 0;
LAB_000948d7:
      if (uVar9 == param_1._4_2_) {
        *(uint16_t *)&iVar6[1].dtor = uVar6;
        break;
      }
      uVar6 = Marker::nextIdOfNextMarkerOfType(Unknown0x1a,0,uVar6);
    } while (uVar6 != 0);
  }
  if (*(short *)&iVar6[1].dtor == 0) {
    uVar6 = Marker::getFurthestMarkerFromPoint(Unknown0x1a,&local_18);
    *(uint16_t *)&iVar6[1].dtor = uVar6;
  }
  paVar5 = param_1.vtable;
  *(undefined1 *)((int)pvVar2 + 0x38) = 1;
  *(undefined1 *)((int)pvVar2 + 0x39) = 1;
  for (iVar8 = *(int *)(*(int *)((int)pvVar2 + 8) + 0x8f8); iVar8 != 0; iVar8 = *(int *)(iVar8 + 4))
  {
    *(char *)(iVar8 + 0x15) = *(char *)(iVar8 + 0x15) + '\x01';
  }
  *(char *)((int)pvVar2 + 0x6d) = *(char *)((int)pvVar2 + 0x6d) + '\x01';
  *(char *)((int)pvVar2 + 0x6a) = *(char *)((int)pvVar2 + 0x6a) + '\x01';
  *(char *)((int)pvVar2 + 0x309) = *(char *)((int)pvVar2 + 0x309) + '\x01';
  *(char *)((int)pvVar2 + 0x30a) = *(char *)((int)pvVar2 + 0x30a) + '\x01';
  *(char *)((int)pvVar2 + 0x30b) = *(char *)((int)pvVar2 + 0x30b) + '\x01';
  *(char *)((int)pvVar2 + 0x30c) = *(char *)((int)pvVar2 + 0x30c) + '\x01';
  if ((((iVar6[1].ctor == (void *)0x0) ||
       (iVar8 = *(int *)((int)iVar6[1].ctor + 0x95c),
       (*(byte *)(*(int *)(*(int *)(iVar8 + 0x15c) + 8) + 3) & 8) != 0)) ||
      (*(short *)(iVar8 + 0x94) == 0)) || (*(int *)(iVar8 + 0x718) != 0)) {
    iVar6[2].func6 = (void *)0x1;
  }
  else {
    *(actorStateVTable **)(iVar8 + 0x718) = param_1.vtable;
  }
  local_18.x = (local_1c->worldPosition).z;
  local_18.y = (local_1c->worldPos).x;
  local_18.z = (local_1c->worldPos).y;
  avatar::getWorldPosition((avatar *)param_1.vtable,&local_c);
  iVar8 = FUN_0012cc50(&local_18,1,0,0,0,0,&param_1,*(undefined2 *)((int)&paVar5->ctor + 2));
  if (iVar8 == 0) {
    iVar6[2].func6 = (void *)0x1;
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


actorStateVTable * FUN_00095740(void)

{
  entityStateGroundAttack::vtable.func5 = switchD_000d4179::EmptyFunction;
  entityStateGroundAttack::vtable.func6 = switchD_000d4179::EmptyFunction;
  entityStateGroundAttack::vtable.func7 = actorState::func7;
  entityStateGroundAttack::vtable.getAllocDetails = FUN_00095720;
  entityStateGroundAttack::vtable.ctor = entityStateGroundAttack::ctor;
  entityStateGroundAttack::vtable.dtor = FUN_000958a0;
  entityStateGroundAttack::vtable.onMessage = FUN_00095c90;
  entityStateGroundAttack::vtable.update = FUN_00095940;
  return &entityStateGroundAttack::vtable;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void FUN_000a5dc0(actorBody *body,entityStateWalk *state)

{
  float fVar1;
  float fVar2;
  uint uVar3;
  float10 fVar4;
  float vx;
  float vz;
  
  vx = (body->velocity).x;
  fVar1 = (body->actor->avatar).physicsPos.x;
  fVar2 = (body->actor->avatar).physicsPos.z;
  vz = (body->velocity).z;
  fVar4 = scaled_invsqrt(fVar1 * fVar1 + fVar2 * fVar2);
  scaled_invsqrt(vz * vz + vx * vx);
  uVar3 = FUN_000a5fd0(state,(float)fVar4,body);
  if (uVar3 != state->currentKeyframe_) {
    (body->actor->avatar).needsAnimMapping = 1;
    FUN_0001afa0(*(undefined4 *)(&state->field_0x30 + uVar3 * 0x10),body);
    state->currentKeyframe_ = (ushort)uVar3;
  }
  FUN_000a5c70((float)fVar4);
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


int FUN_000a5fd0(entityStateWalk *param_1,float param_2,actorBody *param_3)

{
  byte bVar1;
  byte bVar2;
  int numSomethings;
  float *pfVar3;
  int i;
  float fVar4;
  float fVar5;
  float fVar6;
  ushort sheet_index;
  
  numSomethings = (int)param_1->numWalks;
  i = 0;
  if (0 < numSomethings) {
    sheet_index = param_3->actor->statsheetIndex;
    bVar1 = param_3->indexInStatsheet;
    pfVar3 = (float *)&param_1->field_0x3c;
    do {
      if (sheet_index == 0) {
        fVar4 = Game::HealthMetadata[bVar1].maxHealth;
      }
      else {
        fVar4 = Game::HealthMetadata[bVar1].maxHealth;
        fVar5 = Game::HealthMetadata[bVar1].minHealth;
        fVar6 = (float)Game::HealthMetadata[bVar1].minHealthU8;
        if ((float)Game::HealthMetadata[bVar1].maxHealthU8 != fVar6) {
          fVar6 = (((float)(byte)Assets::GhouliesStatsheet[sheet_index].tagName[bVar1 - 0x48] -
                   fVar6) / ((float)Game::HealthMetadata[bVar1].maxHealthU8 - fVar6)) *
                  (fVar4 - fVar5) + fVar5;
          if (fVar4 <= fVar5) {
            if ((fVar4 <= fVar6) && (fVar4 = fVar6, fVar5 < fVar6)) {
              fVar4 = fVar5;
            }
          }
          else if ((fVar6 <= fVar4) && (fVar4 = fVar6, fVar6 < fVar5)) {
            fVar4 = fVar5;
          }
        }
      }
      if (param_3->someCount == 0) {
        bVar2 = param_3->movementIndex;
      }
      else {
        bVar2 = param_3->fallbackMovementIndex;
      }
      if ((param_3->movementFlags & 1 << (bVar2 & 0x1f)) == 0) {
        fVar5 = 1.0;
      }
      else {
        fVar5 = Game::FloorTypeMap[bVar2];
      }
      if ((0.0 <= param_2) && (param_2 < param_3->speedRatio * *pfVar3 * fVar4 * fVar5)) {
        return i;
      }
      i = i + 1;
      pfVar3 = pfVar3 + 4;
    } while (i < numSomethings);
  }
  return numSomethings + -1;
}




void Game::ReplayScene(uint *new_index)

{
  char cVar1;
  asset_name_t pcVar2;
  char *assetName;
  ReplaySceneMenu *menu;
  astruct_15 *paVar3;
  undefined4 uVar4;
  long lVar5;
  uint scene_index;
  BOOL BVar6;
  char *pcVar7;
  void *str;
  char *pcVar8;
  asset_name_t pcVar9;
  uint uVar10;
  uint player;
  int iVar11;
  int iVar12;
  HeapTableEntry *pHVar13;
  uint uVar14;
  char *pcVar15;
  void *local_c;
  
  pcVar8 = Assets::SceneOrderAHandle.sceneOrder;
joined_r0x000e3147:
  assetName = pcVar8;
  if (assetName != (char *)0x0) {
    lVar5 = Assets::PlaycamAIDFromAID(assetName);
    scene_index = Assets::GetChapterIndexFromAID(assetName);
    pcVar15 = Assets::SceneOrderAHandle.sceneOrder;
    if (scene_index == 0) {
      uVar14 = 0xffffffff;
    }
    else {
      uVar14 = 0;
      iVar11 = 1;
      if (lVar5 == 0) {
        if (1 < (int)scene_index) {
          do {
            uVar14 = uVar14 + ChapterSceneCounts[iVar11];
            iVar11 = iVar11 + 1;
          } while (iVar11 < (int)scene_index);
        }
      }
      else {
        if (1 < (int)scene_index) {
          do {
            uVar14 = uVar14 + ChapterSceneCounts[iVar11];
            iVar11 = iVar11 + 1;
          } while (iVar11 < (int)scene_index);
        }
        uVar14 = (uVar14 - 1) + lVar5;
      }
    }
    if (uVar14 != *new_index) {
      if (Assets::SceneOrderAHandle.sceneOrder != (char *)0x0) goto code_r0x000e31b0;
      goto LAB_000e31ed;
    }
  }
  iVar11 = 0;
                    // Patch for randomised level
  scene_index = GetSceneIndexFromAID(assetName);
  pcVar8 = Assets::SceneOrderAHandle.sceneOrder;
  pcVar2 = assetName;
  while ((Assets::SceneOrderAHandle.sceneOrder = pcVar8, pcVar2 != (asset_name_t)0x0 &&
         (*new_index == scene_index))) {
    iVar11 = iVar11 + 1;
    if (pcVar8 == (char *)0x0) {
LAB_000e3259:
      pcVar15 = (char *)0x0;
    }
    else {
      pcVar15 = pcVar8;
      if (pcVar2 != (asset_name_t)0x0) {
        do {
          BVar6 = Assets::AssetNamesMatch(pcVar8,pcVar2);
          if (BVar6 != 0) {
            if (pcVar8 != (char *)0x0) {
              if (*(int *)(pcVar8 + 0x80) == 0x5f646961) {
                pcVar15 = pcVar8 + 0x80;
              }
              goto LAB_000e325b;
            }
            break;
          }
          pcVar7 = pcVar8 + 0x80;
          if (*(int *)(pcVar8 + 0x80) != 0x5f646961) {
            pcVar7 = (char *)0x0;
          }
          pcVar8 = pcVar7;
        } while (pcVar7 != (char *)0x0);
        goto LAB_000e3259;
      }
    }
LAB_000e325b:
    lVar5 = Assets::PlaycamAIDFromAID(pcVar15);
    uVar14 = Assets::GetChapterIndexFromAID(pcVar15);
    pcVar8 = Assets::SceneOrderAHandle.sceneOrder;
    pcVar2 = pcVar15;
    if (uVar14 == 0) {
      scene_index = 0xffffffff;
    }
    else {
      scene_index = 0;
      iVar12 = 1;
      if (lVar5 == 0) {
        if (1 < (int)uVar14) {
          do {
            scene_index = scene_index + ChapterSceneCounts[iVar12];
            iVar12 = iVar12 + 1;
          } while (iVar12 < (int)uVar14);
        }
      }
      else {
        if (1 < (int)uVar14) {
          do {
            scene_index = scene_index + ChapterSceneCounts[iVar12];
            iVar12 = iVar12 + 1;
          } while (iVar12 < (int)uVar14);
        }
        scene_index = (scene_index - 1) + lVar5;
      }
    }
  }
  scene_index = (iVar11 + 2) * 0x80;
  str = malloc_(scene_index);
  pcVar8 = "aid_script_ghoulies_gameselect_gameselect";
  do {
    cVar1 = *pcVar8;
    pcVar8[(int)str + -0x322b8c] = cVar1;
    pcVar8 = pcVar8 + 1;
  } while (cVar1 != '\0');
  iVar11 = 1;
  uVar14 = GetSceneIndexFromAID(assetName);
  local_c = str;
  pcVar2 = assetName;
  do {
    if ((pcVar2 == (asset_name_t)0x0) ||
       (local_c = (void *)((int)local_c + 0x80), *new_index != uVar14)) {
      pcVar8 = "aid_script_ghoulies_gameselect_gameselect";
      do {
        cVar1 = *pcVar8;
        pcVar8[(int)str + iVar11 * 0x80 + -0x322b8c] = cVar1;
        pcVar8 = pcVar8 + 1;
      } while (cVar1 != '\0');
      pcVar8 = malloc_(scene_index + 0x80);
      memcpy(pcVar8,str,scene_index);
      pcVar8[scene_index] = '\0';
      iVar11 = FindHeapOf(str);
      uVar4 = runtime::CurrentHeapToAllocateFrom;
      if (g_HeapTableBase[iVar11].heapHandle == (HANDLE)0x0) {
        pHVar13 = (HeapTableEntry *)0x0;
      }
      else {
        pHVar13 = g_HeapTableBase + iVar11;
      }
      runtime::CurrentHeapToAllocateFrom = iVar11;
      XAPILIB::HeapFree(pHVar13->heapHandle,0,str);
      runtime::CurrentHeapToAllocateFrom = uVar4;
      if ((Assets::SceneOrderAHandle.deallocFn != (void *)0x0) &&
         (Assets::SceneOrderAHandle.sceneOrder != (char *)0x0)) {
        (*Assets::SceneOrderAHandle.deallocFn)(&Assets::SceneOrderAHandle);
      }
      Assets::SceneOrderAHandle.deallocFn = FUN_000358f0;
      resource::next_menu_id = ReplayScene;
      Assets::SceneOrderAHandle.sceneOrder = pcVar8;
      XAPILIB::lstrcpyW(g_wString,ReplaySceneMenu->someWideString);
      if ((Input::MenuInputHandler->header).type == TYPE_3) {
        player = Input::FirstPlayerPressed
                           (TRIGGER_R|TRIGGER_L|BUTTON_WHITE|BUTTON_BLACK|BUTTON_Y|BUTTON_X|BUTTON_B
                            |BUTTON_A|BUTTON_RS|BUTTON_LS|SELECT|START|DPAD_RIGHT|DPAD_LEFT|
                            DPAD_DOWN|DPAD_UP);
        Input::BindControllerToPlayer_(player,0x10);
      }
      entitySceneControlGameSelect::setPlaycamScript(ReplaySceneMenu->gameselectControl,2,assetName)
      ;
      paVar3 = SomeAS15;
      *SomeAS15->flags = *SomeAS15->flags | 0x10;
      menu = ReplaySceneMenu;
      *paVar3->flags = *paVar3->flags | 0x20;
      ReplaySceneMenu::setState(menu,3);
      return;
    }
    pcVar9 = pcVar2;
    do {
      cVar1 = *pcVar9;
      pcVar9[(int)local_c - (int)pcVar2] = cVar1;
      pcVar8 = Assets::SceneOrderAHandle.sceneOrder;
      pcVar9 = pcVar9 + 1;
    } while (cVar1 != '\0');
    iVar11 = iVar11 + 1;
    if (Assets::SceneOrderAHandle.sceneOrder == (char *)0x0) {
LAB_000e33b9:
      pcVar8 = (char *)0x0;
    }
    else {
      pcVar15 = Assets::SceneOrderAHandle.sceneOrder;
      if (pcVar2 != (asset_name_t)0x0) {
        do {
          BVar6 = Assets::AssetNamesMatch(pcVar15,pcVar2);
          if (BVar6 != 0) {
            if (pcVar15 != (char *)0x0) {
              if (*(int *)(pcVar15 + 0x80) == 0x5f646961) {
                pcVar8 = pcVar15 + 0x80;
              }
              goto LAB_000e33bb;
            }
            break;
          }
          pcVar7 = pcVar15 + 0x80;
          if (*(int *)(pcVar15 + 0x80) != 0x5f646961) {
            pcVar7 = (char *)0x0;
          }
          pcVar15 = pcVar7;
        } while (pcVar7 != (char *)0x0);
        goto LAB_000e33b9;
      }
    }
LAB_000e33bb:
    lVar5 = Assets::PlaycamAIDFromAID(pcVar8);
    uVar10 = Assets::GetChapterIndexFromAID(pcVar8);
    pcVar2 = pcVar8;
    if (uVar10 == 0) {
      uVar14 = 0xffffffff;
    }
    else {
      uVar14 = 0;
      iVar12 = 1;
      if (lVar5 == 0) {
        if (1 < (int)uVar10) {
          do {
            uVar14 = uVar14 + ChapterSceneCounts[iVar12];
            iVar12 = iVar12 + 1;
          } while (iVar12 < (int)uVar10);
        }
      }
      else {
        if (1 < (int)uVar10) {
          do {
            uVar14 = uVar14 + ChapterSceneCounts[iVar12];
            iVar12 = iVar12 + 1;
          } while (iVar12 < (int)uVar10);
        }
        uVar14 = (uVar14 - 1) + lVar5;
      }
    }
  } while( true );
code_r0x000e31b0:
  pcVar7 = Assets::SceneOrderAHandle.sceneOrder;
  pcVar8 = pcVar15;
  if (assetName != (char *)0x0) {
    do {
      BVar6 = Assets::AssetNamesMatch(pcVar7,assetName);
      if (BVar6 != 0) {
        if (pcVar7 != (char *)0x0) {
          pcVar8 = pcVar7 + 0x80;
          if (*(int *)(pcVar7 + 0x80) != 0x5f646961) {
            pcVar8 = pcVar15;
          }
          goto joined_r0x000e3147;
        }
        break;
      }
      pcVar8 = pcVar7 + 0x80;
      if (*(int *)(pcVar7 + 0x80) != 0x5f646961) {
        pcVar8 = (char *)0x0;
      }
      pcVar7 = pcVar8;
    } while (pcVar8 != (char *)0x0);
LAB_000e31ed:
    pcVar8 = (char *)0x0;
  }
  goto joined_r0x000e3147;
}




void game::load_cheap_dust_fx(void)

{
  BigCheapDustStruct *pvVar1;
  int iVar1;
  int *piVar2;
  void *local_4;
  
  pvVar1 = malloc_(0x19c8);
  DAT_005068dc = 0;
  iVar1 = 0;
  piVar2 = &pvVar1->field124_0x7c;
  DAT_005068d8 = pvVar1;
  do {
    iVar1 = iVar1 + 1;
    *piVar2 = iVar1;
    piVar2 = piVar2 + 0x21;
  } while (iVar1 < 0x31);
  *(undefined4 *)&pvVar1->field_0x19c0 = 0xffffffff;
  Assets::GetResourceBytes("aid_misc_ghoulies_fx_cheap_dust",&local_4);
  if (local_4 == (void *)0x0) {
    runtime::ExitGame(2);
  }
  misc_fx_cheap_dust_resource = local_4;
  FUN_000ebb10();
  return;
}




int __fastcall game::get_num_books(uint param_1)

{
  char cVar1;
  byte *pbVar2;
  int iVar3;
  int iVar4;
  
  pbVar2 = (byte *)((param_1 >> 3) + (int)PTR_00506c54->field2_0x8);
  *pbVar2 = *pbVar2 | '\x01' << ((byte)param_1 & 7);
  iVar3 = FUN_00066180();
  if (iVar3 == 1) {
    iVar4 = FUN_0013ff70();
    if (iVar4 == 0) goto LAB_000f253a;
    iVar4 = 0;
    do {
      cVar1 = "challenge_firstbonusbook"[iVar4];
      (&DAT_00545b44)[iVar4] = cVar1;
      iVar4 = iVar4 + 1;
    } while (cVar1 != '\0');
  }
  else {
    if ((iVar3 != 5) || (iVar4 = FUN_0013ff70(), iVar4 == 0)) goto LAB_000f253a;
    iVar4 = 0;
    do {
      cVar1 = "challenge_firstchallenge"[iVar4];
      (&DAT_00545b44)[iVar4] = cVar1;
      iVar4 = iVar4 + 1;
    } while (cVar1 != '\0');
  }
  Game::UpdateActionType = 1;
LAB_000f253a:
  if (oldNextPlaycamScriptWide[0] != L'\0') {
    FUN_000f3230();
    iVar4 = FUN_0010dc20();
    if (iVar4 != 0) {
      FUN_0010e2c0();
    }
    FUN_0010da80(FUN_000f32f0);
  }
  FUN_0012d7e0(iVar3);
  return iVar3;
}




void game::reset_scene_vars_on_leave(void)

{
  if (DAT_00506c58 != 0) {
    DAT_00506c58 = 0;
    FUN_0012fdc0();
    DAT_00506c60 = -1.0;
    DAT_00506c68 = 0;
  }
  return;
}



// WARNING: Globals starting with '_' overlap smaller symbols at the same address
// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void Game::MaybeSaveGame(void)

{
  int iVar1;
  
  if ((game::oldNextPlaycamScriptWide[0] != L'\0') && ((*SomeAS15->flags & 8) != 0)) {
    FUN_00049d40();
    FUN_0010e800(DAT_004e1740);
    FUN_0010e850(TimeInCurrentLevel + FLOAT_004e1744);
    FUN_000f3290();
    FUN_000f34c0();
    iVar1 = FUN_0010dc20();
    if (iVar1 != 0) {
      FUN_0010e2c0();
    }
    FUN_0010da80(FUN_000f32f0);
  }
  return;
}




void runtime::SaveTheGame_(void)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  LPWSTR local_10 [4];
  
  local_10[0] = (LPWSTR)0x0;
  local_10[2] = (LPWSTR)0x0;
  local_10[1] = (LPWSTR)0x0;
  if (game::oldNextPlaycamScriptWide[0] != L'\0') {
    if ((*SomeAS15->flags & 2) == 0) {
      Game::Save.timeSeconds = 0;
      Game::Save.numKills = 0;
      Game::Save.numDeaths = 0;
      Game::Save.numPrisoners = 0;
      Game::Save.field4_0x10 = 0;
    }
    else {
                    // Saves
      uVar1 = FUN_0010dda0(game::oldNextPlaycamScriptWide);
      uVar2 = FUN_0010dd60(game::oldNextPlaycamScriptWide);
      uVar3 = FUN_0010dd20(game::oldNextPlaycamScriptWide);
      local_10[3] = (LPWSTR)FUN_0010dce0(game::oldNextPlaycamScriptWide);
      Game::Save.timeSeconds = FUN_0010dca0(game::oldNextPlaycamScriptWide);
      Game::Save.numKills = (uint)local_10[3];
      Game::Save.numDeaths = uVar3;
      Game::Save.numPrisoners = uVar2;
      Game::Save.field4_0x10 = uVar1;
    }
    Game::DeathsInCurrentRoom = 0;
    FUN_0010dde0(local_10,game::oldNextPlaycamScriptWide);
    memcpy(PTR_00506c6c->field2_0x8,*(void **)(local_10[0] + 4),*(uint *)(local_10[0] + 2));
    FUN_0010de80(local_10 + 1);
    FUN_000f2ac0();
    FUN_0010de30(local_10 + 2);
    memcpy(PTR_00506c54->field2_0x8,*(void **)(local_10[2] + 4),*(uint *)(local_10[2] + 2));
    FUN_0010ded0();
    FUN_0010e050();
  }
  return;
}




GhoulyBox * DeathDropContext::ctor(void)

{
  GhoulyBox *dd;
  Buffer<> *inners;
  
  dd = malloc_(0xb4);
  inners = malloc_(0x520);
  inners->valueSize = 0x288;
  inners->capacity = 2;
  inners->head = inners->values;
  inners->tail = inners->values;
  inners->end = (GhoulyBoxInner *)(inners + 1);
  dd->inners = inners;
  dd->f2 = 0.0;
  *(undefined4 *)&dd->field7_0x1c = 0;
  dd->head = (GhoulyBoxLLHead *)0x0;
  dd->next = (GhoulyBox *)0x0;
  dd->field3_0xc = 0;
  dd->capacity_ = 0;
  dd->innersInitialised_ = 0;
  dd->field5_0x14 = 0;
  dd->actorAttribsAID[0] = '\0';
  dd->field12_0x28 = -1;
  dd->f1 = 0.001;
  return dd;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


int initIntroData(void)

{
  uint uVar1;
  XSoundbankResource *local_4;
  
  Assets::GetResourceBytes("aid_misc_ghoulies_actor_introdata",&local_4);
  if (local_4 == (XSoundbankResource *)0x0) {
    runtime::ExitGame(2);
  }
  DAT_00506d90 = local_4;
  uVar1 = XSoundbankResource::GetResourceSize(local_4);
  Game::ActorPerformingIntro = (actor *)0x0;
  DAT_00506e00 = 0;
  Game::InGhoulyIntro = 0;
  DAT_00506e2c = 0;
  DAT_00506d94 = uVar1 / 0x44;
  return uVar1 * -0xf0f0f0f;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


GhoulyBox * game::execute_ghouly_spawn(char *param_1)

{
  GhoulyBox *spawn;
  GhoulySpawnOperation *local_4;
  
  spawn = (GhoulyBox *)0x0;
  if (*(int *)param_1 == 0x5f646961) {
    Assets::GetResourceBytes(param_1,&local_4);
    if (local_4 == (GhoulySpawnOperation *)0x0) {
      runtime::ExitGame(2);
      return (GhoulyBox *)0x0;
    }
    spawn = malloc_(0x124);
    spawn->head = (GhoulyBoxLLHead *)0x0;
    spawn->next = (GhoulyBox *)0x0;
    spawn->inners = (Buffer<> *)0x0;
    spawn->field3_0xc = 0;
    spawn->capacity_ = 0;
    spawn->field5_0x14 = 0;
    spawn->f2 = 0.0;
    spawn->field7_0x1c = 0;
    spawn->f1 = 0.0;
    Scripting::AddGhoulySpawnToList(spawn,(GhoulyBoxLLHead *)&DAT_00510570);
    FUN_00051940(local_4,spawn);
    Assets::DestroyAssetOrDecrement(local_4);
  }
  return spawn;
}




void FUN_000fa110(GamepadState *pad)

{
  float *pfVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  
  pfVar1 = &pad->field17_0x3c;
  uVar4 = 0x3c;
  if ((GamepadState *)pfVar1 != pad) {
    if ((((uint)pfVar1 & 7) == 0) && (((uint)pad & 7) == 0)) {
      iVar2 = 7;
      do {
        *pfVar1 = pad->normLsx;
        pfVar1[1] = pad->normLsy;
        pfVar1 = pfVar1 + 2;
        pad = (GamepadState *)&pad->normRsx;
        uVar4 = uVar4 - 8;
        iVar2 = iVar2 + -1;
      } while (iVar2 != 0);
    }
    if (((((uint)pfVar1 & 3) == 0) && (((uint)pad & 3) == 0)) && (3 < uVar4)) {
      uVar3 = uVar4 >> 2;
      do {
        *pfVar1 = pad->normLsx;
        pfVar1 = pfVar1 + 1;
        pad = (GamepadState *)&pad->normLsy;
        uVar4 = uVar4 - 4;
        uVar3 = uVar3 - 1;
      } while (uVar3 != 0);
    }
    if (uVar4 != 0) {
      iVar2 = (int)pad - (int)pfVar1;
      do {
        *(undefined1 *)pfVar1 = *(undefined1 *)(iVar2 + (int)pfVar1);
        pfVar1 = (float *)((int)pfVar1 + 1);
        uVar4 = uVar4 - 1;
      } while (uVar4 != 0);
    }
  }
  return;
}




void onVerticalBlank(D3DVBLANKDATA *data)

{
  if ((DoDat0x0050e0b8 == 0) && (g_PlayingMovies__ == 0)) {
    DAT_005096d8 = DAT_005096d8 + 1;
    if ((data->Flags & D3DVBLANK_SWAPDONE) != 0) {
      runtime::VBlanksSinceLastFrame = DAT_005096d8 - DAT_005096d4;
      DAT_005096d4 = DAT_005096d8;
    }
  }
  return;
}




void Game::SetSomeVec3(vec3 *param_1)

{
  float fVar1;
  float fVar2;
  float fVar3;
  
  if (param_1 == (vec3 *)0x0) {
    fVar1 = 0.0;
    fVar2 = 1.0;
    fVar3 = -1.0;
  }
  else {
    fVar1 = param_1->x;
    fVar2 = param_1->y;
    fVar3 = param_1->z;
  }
  SomeVec3.x = fVar1 * 30.0;
  SomeVec3.y = fVar2 * 30.0;
  SomeVec3.z = fVar3 * 30.0;
  return;
}




undefined4 FUN_0010a6d0(powerup *pwup,int param_2,actor *param_3)

{
  CalloutDescriptor **ppCVar1;
  actorBody *paVar2;
  weapon *pwVar3;
  Model *pMVar4;
  avatar_0x110 pEVar5;
  DataForInfoFromBackground_conflict1 *pDVar6;
  KeyframeContext *kfc;
  int iVar7;
  AnimCollisionSubresourceEntry *entry;
  avatar *this;
  Skeleton *skeleton;
  float10 extraout_ST0;
  float10 fVar8;
  float fVar9;
  float fVar10;
  float fVar11;
  vec3 local_384;
  int local_378;
  undefined1 local_374;
  undefined1 local_373;
  undefined1 local_372;
  float local_370;
  float local_36c;
  float local_368;
  undefined4 local_364;
  float local_360;
  undefined4 local_35c;
  float local_358;
  objParams local_354 [103];
  undefined1 local_18;
  undefined4 local_8;
  undefined4 local_4;
  
  paVar2 = param_3->body;
  avatar::getWorldPosition(&paVar2->actor->avatar,&local_384);
  local_360 = (paVar2->actor->avatar).scale.y * paVar2->cameraOffsetVertical;
  local_370 = local_384.x;
  local_36c = local_384.y;
  local_368 = local_384.z;
  local_364 = 0;
  local_35c = 0;
  local_358 = (paVar2->actor->avatar).scale.z * paVar2->closenessDistance;
  local_374 = 4;
  local_373 = 0x20;
  local_372 = 1;
  iVar7 = FUN_001205f0(param_2,&local_374);
  pwVar3 = param_3->body->weapon;
  local_378 = 0;
  if (pwVar3 != (weapon *)0x0) {
    entry = (AnimCollisionSubresourceEntry *)FUN_00042560(0x10);
    while (entry != (AnimCollisionSubresourceEntry *)0x0) {
      pMVar4 = (pwVar3->avatar).model;
      if (pMVar4 == (Model *)0x0) {
        skeleton = (Skeleton *)0x0;
      }
      else {
        skeleton = pMVar4->skeleton;
        if (skeleton == (Skeleton *)0x0) {
          skeleton = pMVar4->skeleton2;
        }
      }
      checkCollisionAgainstSkeleton(entry,skeleton,&local_384,&(pwVar3->avatar).drawAffine);
      fVar9 = (float)extraout_ST0;
      local_360 = fVar9 + fVar9;
      local_384.y = local_384.y - fVar9;
      if ((local_384.y <= *(float *)(param_2 + 0x14) + *(float *)(param_2 + 8)) &&
         (*(float *)(param_2 + 8) <= local_360 + local_384.y)) {
        fVar9 = *(float *)(param_2 + 0x1c) + fVar9;
        fVar11 = local_384.z - *(float *)(param_2 + 0xc);
        fVar10 = local_384.x - *(float *)(param_2 + 4);
        fVar8 = scaled_invsqrt(fVar11 * fVar11 + fVar10 * fVar10);
        fVar10 = (float)fVar8;
        if (fVar8 < (float10)1e-05) {
          fVar10 = fVar9 - 0.01;
        }
        if (fVar10 < fVar9) {
          local_378 = 1;
          break;
        }
      }
      entry = (AnimCollisionSubresourceEntry *)FUN_000425d0(0x10);
    }
  }
  if ((iVar7 != 0) && (local_378 == 0)) {
    return 0;
  }
  ppCVar1 = &(pwup->avatar).callout;
  if ((ppCVar1 != (CalloutDescriptor **)0x0) &&
     (actor::executeCalloutInDescriptor
                (*ppCVar1,Explode,(CalloutCallback *)0x0,0,(actor *)pwup,(entityBodyPlayer_0x924)0x0
                ), ppCVar1 != (CalloutDescriptor **)0x0)) {
    actor::executeCalloutInDescriptor
              (*ppCVar1,Pickup,(CalloutCallback *)0x0,0,(actor *)pwup,(entityBodyPlayer_0x924)0x0);
  }
  ppCVar1 = &(param_3->avatar).callout;
  if (ppCVar1 != (CalloutDescriptor **)0x0) {
    actor::executeCalloutInDescriptor
              (*ppCVar1,Powerup,(CalloutCallback *)0x0,0,param_3,(entityBodyPlayer_0x924)0x0);
  }
  powerup::onTouchPowerup
            (pwup->field11_0x944,pwup->field13_0x94c,param_3,pwup->pwupType,
             (float)pwup->field11_0x944,pwup->field12_0x948);
  FUN_00069590(1.0);
  local_18 = *(undefined1 *)((int)&(pwup->avatar).someInt32 + 3);
  local_4 = 0;
  local_8 = 1;
  Assets::CreateEntityFromParams(local_354);
  this = (avatar *)FUN_0003e850((entityAvatarFxBurnup *)pwup);
  (pwup->avatar).has0x4CollisionFlag = 0;
  avatar::updateMorphTargetsOrSomething(this);
  pEVar5 = (pwup->avatar).node0x110.prev;
  if (pEVar5 != (avatar_0x110)0x0) {
    pEVar5->next = (pwup->avatar).node0x110.next;
  }
  pEVar5 = (pwup->avatar).node0x110.next;
  if (pEVar5 != (avatar_0x110)0x0) {
    pEVar5->prev = (pwup->avatar).node0x110.prev;
  }
  (pwup->avatar).node0x110.prev = (avatar_0x110)0x0;
  (pwup->avatar).node0x110.next = (avatar_0x110)0x0;
  FUN_0003d0a0(pwup);
  pDVar6 = (pwup->avatar).infoList.prev;
  while (pDVar6 != (DataForInfoFromBackground_conflict1 *)0x0) {
    pDVar6 = (DataForInfoFromBackground_conflict1 *)pDVar6->field1_0x4;
    FUN_0011bda0();
  }
  kfc = (pwup->avatar).keyframeContext;
  if (kfc != (KeyframeContext *)0x0) {
    KeyFrameContext::dtor(kfc,0);
    (pwup->avatar).keyframeContext = (KeyframeContext *)0x0;
  }
  pwup->field88_0x9ac = 1.0;
  pwup->field9_0x93c = 2;
  return 1;
}




void runtime::SetupHeapSaveData(void)

{
  Buffer<SaveEntry> *save1;
  Buffer<SaveEntry> *save2;
  SaveEntry *heap_data;
  GameSaveSet *saves;
  
  Saves = malloc_(0x18);
  Saves->save1 = (Buffer<SaveEntry> *)0x0;
  save1 = malloc_(0x10);
  heap_data = save1->values;
  save1->head = heap_data;
  save1->tail = heap_data;
  save1->end = heap_data;
  saves = Saves;
  save1->valueSize = 0x18;
  save1->capacity = 10;
  saves->save1 = save1;
  saves->save2 = (Buffer<SaveEntry> *)0x0;
  save2 = malloc_(0x10);
  heap_data = save2->values;
  save2->head = heap_data;
  save2->tail = heap_data;
  save2->end = heap_data;
  saves = Saves;
  save2->valueSize = 256;
  save2->capacity = 10;
  saves->save2 = save2;
  saves->field1_0x4 = 0;
  saves->field3_0xc = (ushort *)0x0;
  saves->save3 = (Buffer<SaveEntry> *)0x0;
  saves->timer = 0;
  ReadSavedGames();
  return;
}



undefined4 __thiscall

uint Save::getHighestCompletedChapter(LPCWSTR param_1)

{
  Buffer<SaveEntry> *pBVar1;
  int iVar2;
  SaveEntry *pSVar3;
  
  pBVar1 = runtime::Saves->save1;
  pSVar3 = pBVar1->head;
  if (pSVar3 < pBVar1->tail) {
    do {
      iVar2 = XAPILIB::lstrcmpW((LPCWSTR)&pSVar3->entries->field1_0x2,param_1);
      if (iVar2 == 0) {
        return pSVar3->entries[1].field2_0x6;
      }
      pSVar3 = (SaveEntry *)((int)&pSVar3->val1 + (uint)pBVar1->valueSize);
    } while (pSVar3 < pBVar1->tail);
  }
  return 0;
}




void Save::SetSecondsPlayed(uint secondsPlayed,LPCWSTR str)

{
  int iVar1;
  astruct_41 *uVar3;
  SomeSceneStruct *pSVar1;
  
  pSVar1 = (SomeSceneStruct *)runtime::Saves->save1;
  uVar3 = pSVar1->min;
  if (uVar3 < pSVar1->field4_0x8) {
    while( true ) {
      iVar1 = XAPILIB::lstrcmpW((LPCWSTR)(uVar3->field4_0x4 + 2),str);
      if (iVar1 == 0) break;
      uVar3 = (astruct_41 *)(&uVar3->field_0x0 + pSVar1->field0_0x0);
      if (pSVar1->field4_0x8 <= uVar3) {
        return;
      }
    }
    *(uint *)(uVar3->field4_0x4 + 0x18c) = secondsPlayed;
  }
  return;
}




void Save::SetNumKills(uint param_1)

{
  Buffer<SaveEntry> *pBVar1;
  int iVar2;
  LPCWSTR unaff_EBX;
  SaveEntry *pSVar3;
  
  pBVar1 = runtime::Saves->save1;
  pSVar3 = pBVar1->head;
  if (pSVar3 < pBVar1->tail) {
    while( true ) {
      iVar2 = XAPILIB::lstrcmpW((LPCWSTR)&pSVar3->entries->field1_0x2,unaff_EBX);
      if (iVar2 == 0) break;
      pSVar3 = (SaveEntry *)((int)&pSVar3->val1 + (uint)pBVar1->valueSize);
      if (pBVar1->tail <= pSVar3) {
        return;
      }
    }
    pSVar3->entries[1].field4_0xe = param_1;
  }
  return;
}




void Save::SetNumDeaths(uint param_1)

{
  Buffer<SaveEntry> *pBVar1;
  int iVar2;
  LPCWSTR unaff_EBX;
  SaveEntry *pSVar3;
  
  pBVar1 = runtime::Saves->save1;
  pSVar3 = pBVar1->head;
  if (pSVar3 < pBVar1->tail) {
    while( true ) {
      iVar2 = XAPILIB::lstrcmpW((LPCWSTR)&pSVar3->entries->field1_0x2,unaff_EBX);
      if (iVar2 == 0) break;
      pSVar3 = (SaveEntry *)((int)&pSVar3->val1 + (uint)pBVar1->valueSize);
      if (pBVar1->tail <= pSVar3) {
        return;
      }
    }
    pSVar3->entries[1].field5_0x12 = param_1;
  }
  return;
}




void Save::SetNumPrisoners(uint param_1)

{
  Buffer<SaveEntry> *pBVar1;
  int iVar2;
  LPCWSTR unaff_EBX;
  SaveEntry *pSVar3;
  
  pBVar1 = runtime::Saves->save1;
  pSVar3 = pBVar1->head;
  if (pSVar3 < pBVar1->tail) {
    while( true ) {
      iVar2 = XAPILIB::lstrcmpW((LPCWSTR)&pSVar3->entries->field1_0x2,unaff_EBX);
      if (iVar2 == 0) break;
      pSVar3 = (SaveEntry *)((int)&pSVar3->val1 + (uint)pBVar1->valueSize);
      if (pBVar1->tail <= pSVar3) {
        return;
      }
    }
    pSVar3->entries[1].field6_0x16 = param_1;
  }
  return;
}




void runtime::ReadSavedGames(void)

{
  SaveEntry *pSVar1;
  HANDLE handle;
  int iVar2;
  Buffer<SaveEntry> *save_data_;
  Buffer<SaveEntry> **ppvVar3;
  int iVar4;
  XGAME_FIND_DATA save_data;
  
  handle = XAPILIB::XFindFirstSaveGame("U:\\",&save_data);
  if (handle != (HANDLE)0xffffffff) {
    do {
      save_data_ = Saves->save2;
      ppvVar3 = &Saves->save2;
      if (save_data_->tail == save_data_->end) {
        iVar2 = ((int)save_data_->tail - (int)save_data_->head) / (int)(uint)save_data_->valueSize;
        iVar4 = (uint)save_data_->capacity + iVar2;
        save_data_ = (Buffer<SaveEntry> *)
                     AllocateMoreAStruct_33((uint)save_data_->valueSize * iVar4 + 0x10,save_data_);
        pSVar1 = save_data_->values;
        save_data_->tail = (SaveEntry *)((int)&pSVar1->val1 + (uint)save_data_->valueSize * iVar2);
        save_data_->end = (SaveEntry *)((int)&pSVar1->val1 + (uint)save_data_->valueSize * iVar4);
        save_data_->head = pSVar1;
        *ppvVar3 = save_data_;
      }
      pSVar1 = save_data_->tail;
      save_data_->tail = (SaveEntry *)((int)&pSVar1->val1 + (uint)save_data_->valueSize);
      XAPILIB::lstrcpyW((LPWSTR)pSVar1,save_data.szSaveGameName);
      iVar2 = XAPILIB::XFindNextSaveGame(handle,&save_data);
    } while (iVar2 != 0);
    XAPILIB::XFindClose(handle);
  }
  return;
}




void runtime::SomethingSaveRelated(void)

{
  Buffer<SaveEntry> *pBVar1;
  int iVar2;
  uint uVar3;
  SaveEntry *pSVar4;
  WCHAR local_100 [128];
  
  if (0 < (int)Saves->save3) {
    local_100[0] = L'\0';
    iVar2 = FUN_0010d710(local_100);
    if ((iVar2 != 0) &&
       (uVar3 = FUN_000663b0((Buffer<AudioSmth> *)Saves->save1,FUN_0010e990), uVar3 != 0)) {
      if (*(int *)(uVar3 + 8) != 0) {
        FUN_0010eb60(*(undefined4 *)(uVar3 + 0x14));
        return;
      }
      iVar2 = FUN_0010d7a0();
      if (iVar2 != 0) {
        do {
          pBVar1 = Saves->save1;
          pSVar4 = pBVar1->head;
          if (pSVar4 < pBVar1->tail) {
            do {
              iVar2 = XAPILIB::lstrcmpW((LPCWSTR)&pSVar4->entries->field1_0x2,local_100);
              if (iVar2 == 0) {
                if (pSVar4->val3 != 0) {
                  FUN_0010eb60(pSVar4[1].entries);
                  return;
                }
                break;
              }
              pSVar4 = (SaveEntry *)((int)&pSVar4->val1 + (uint)pBVar1->valueSize);
            } while (pSVar4 < pBVar1->tail);
          }
          iVar2 = FUN_0010d7a0();
          if (iVar2 == 0) {
            return;
          }
        } while( true );
      }
    }
  }
  return;
}




void Game::AddNoAttackTimer(ushort param_1,float param_2)

{
  FrozenAttackTimers[NumFrozenAttackTimers].someU16 = param_1;
  FrozenAttackTimers[NumFrozenAttackTimers].timer = param_2;
  NumFrozenAttackTimers = NumFrozenAttackTimers + 1;
  return;
}




int GetCurrentScenePauseFlags(void)

{
  if (g_currentPlaycamScriptHeader != (AssetScriptHeader *)0x0) {
    return g_currentPlaycamScriptHeader->pauseFlags;
  }
  return g_scriptHeaders[0].pauseFlags;
}



// WARNING: This is an inlined function
// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void Game::SetBackgroundPositions(vec3 *param_1,vec3 *param_2)

{
  Background::HasBounds = 1;
  Background::MinVector.x = param_1->x - 25.0;
  Background::MinVector.y = param_1->y - 25.0;
  Background::MinVector.z = param_1->z - 25.0;
  Background::MaxVector.x = param_2->x + 25.0;
  Background::MaxVector.y = param_2->y + 25.0;
  Background::MaxVector.z = param_2->z + 25.0;
  background_pos3.x = param_1->x;
  background_pos3.y = param_1->y;
  background_pos3.z = param_1->z;
  background_pos4.x = param_2->x;
  background_pos4.y = param_1->y;
  background_pos4.z = param_1->z;
  background_pos5.x = param_1->x;
  background_pos5.y = param_2->y;
  background_pos5.z = param_1->z;
  background_pos6.x = param_2->x;
  background_pos6.y = param_2->y;
  background_pos6.z = param_1->z;
  background_pos7.x = param_1->x;
  background_pos7.y = param_1->y;
  background_pos7.z = param_2->z;
  background_pos8.x = param_2->x;
  background_pos8.y = param_1->y;
  background_pos8.z = param_2->z;
  background_pos9.x = param_1->x;
  background_pos9.y = param_2->y;
  background_pos9.z = param_2->z;
  background_pos10.x = param_2->x;
  background_pos10.y = param_2->y;
  background_pos10.z = param_2->z;
  return;
}




void Game::AddSubres0x14(ModelSubresource0x14 *subres)

{
  float fVar1;
  float fVar2;
  float fVar3;
  uint index;
  ModelSubresource0x14 *instance;
  
  Subres0x14Instances[NumSubres0x14s].subres = subres;
  index = NumSubres0x14s;
  instance = Subres0x14Instances[NumSubres0x14s].subres;
  Subres0x14Instances[NumSubres0x14s].maxes.x = (instance->maxes).x;
  Subres0x14Instances[index].maxes.y = (instance->maxes).y;
  Subres0x14Instances[index].maxes.z = (instance->maxes).z;
  Subres0x14Instances[index].mins.x = (instance->mins).x;
  Subres0x14Instances[index].mins.y = (instance->mins).y;
  Subres0x14Instances[index].mins.z = (instance->mins).z;
  fVar1 = Subres0x14Instances[NumSubres0x14s].maxes.x - Subres0x14Instances[NumSubres0x14s].mins.x;
  fVar2 = Subres0x14Instances[NumSubres0x14s].maxes.y - Subres0x14Instances[NumSubres0x14s].mins.y;
  fVar3 = Subres0x14Instances[NumSubres0x14s].maxes.z - Subres0x14Instances[NumSubres0x14s].mins.z;
  Subres0x14Instances[NumSubres0x14s].magnitude =
       SQRT(fVar2 * fVar2 + fVar1 * fVar1 + fVar3 * fVar3);
  NumSubres0x14s = NumSubres0x14s + 1;
  return;
}




void Game::EndScene(int param_1)

{
  int iVar1;
  ObjMsgID local_8;
  uint local_4;
  
  _DAT_0051065c = 1;
  if (DialogState != NotInDialog) {
    Events::SetDialogState(NotInDialog);
  }
  Cutscene::SetCutsceneCam();
  FUN_00049ef0();
  FUN_0005b1e0();
  Model::NumRegistered0x8s = 0;
  Model::Subresource0x8s[0] = (Subresource0x8 *)0x0;
  Model::Subresource0x8s[1] = (Subresource0x8 *)0x0;
  Model::Subresource0x8s[2] = (Subresource0x8 *)0x0;
  Model::Subresource0x8s[3] = (Subresource0x8 *)0x0;
  FUN_00115f00();
  local_8 = Scene_End;
  EventLoop::DispatchMessage(&local_8);
  avatar::destroyStaleAvatars();
  FUN_001222a0();
  FUN_00110ab0();
  UnloadGraphicsTextures_();
  FUN_00123640();
  FUN_001199f0();
  FUN_0011f610();
                    // Clear the resource
  if (g_wavyTexture != (D3DTexture *)0x0) {
    D3D8::D3DResource_Release((D3DResource *)g_wavyTexture);
    g_wavyTexture = (D3DTexture *)0x0;
  }
  DAT_00510580 = 0;
  FUN_001133b0();
  Background::HasBounds = 0;
  BackgroundHasCollision = false;
  Background::MinVector.z = 0.0;
  Background::MinVector.y = 0.0;
  Background::MinVector.x = 0.0;
  Background::MaxVector.z = 0.0;
  Background::MaxVector.y = 0.0;
  Background::MaxVector.x = 0.0;
  BackgroundAABB.aabb.maxZ = 0;
  BackgroundAABB.aabb.maxY = 0;
  BackgroundAABB.aabb.maxX = 0;
  BackgroundAABB.aabb.minZ = 0;
  BackgroundAABB.aabb.minY = 0;
  BackgroundAABB.aabb.minX = 0;
  BackgroundAABB.matrixPtr = 0;
  FUN_000fd710();
  local_4 = g_globalFlagset >> 8 & 1;
  DAT_0050ea98 = 0;
  g_globalFlagset = 0;
  if (local_4 != 0) {
    g_globalFlagset = 0x100;
  }
  *(undefined4 *)(param_1 + 0x118) = 0;
  FUN_000ed450();
  DAT_00504330 = 0;
  FUN_00129f70();
  Audio::LoadReverbSettings(0xd);
  FUN_00118560();
  if (DAT_00512344 != (void *)0x0) {
    free(DAT_00512344);
    DAT_00512344 = (void *)0x0;
  }
  _DAT_00512348 = 0;
  DAT_00545d20 = 1;
  DAT_00545d28 = 0;
  actorMind::NumObjectTypes = 0;
  NumFrozenAttackTimers = 0;
  Assets::NumSomethingBodies = 0;
  g_AssetBodySearchList[8] = 0;
  g_AssetBodySearchList[9] = 0;
  g_AssetBodySearchList[0x3a] = 0;
  g_AssetBodySearchList[0x3b] = 0;
  FUN_000f44b0();
  UpdateActionType = 0;
  EndCurrentSceneOrDialog = 0;
  DAT_00545b44 = 0;
  DAT_00545bc4 = 0;
  FUN_0012a9b0();
  FUN_00123b30();
  UnloadBurnups();
  UI::UnloadManyElements_();
  Events::EventCount2 = 0;
  FUN_000fae40();
  FUN_0011b630();
  if (GameState.markerInstance != (MarkerInstance *)0x0) {
    free(GameState.markerInstance);
    GameState.markerInstance = (MarkerInstance *)0x0;
  }
  InvertChallengeStatusGraphics();
  FUN_001272b0();
  g_timeSpentInCurrentLevel = 0.0;
  TimeInCurrentLevel = 0.0;
  g_ticksInCurrentLevel = 0;
  TicksInCurrentLevel = 0;
  runtime::TimeScale = 1.0;
  runtime::Clear_g_itemsToClear();
  FUN_00057dc0();
  FUN_0011cd90();
  FUN_00106e30();
  DAT_00511a10 = 0;
  FUN_0011aea0();
  Subres0x14Instances[0].subres = (ModelSubresource0x14 *)0x0;
  Subres0x14Instances[1].subres = (ModelSubresource0x14 *)0x0;
  Subres0x14Instances[2].subres = (ModelSubresource0x14 *)0x0;
  Subres0x14Instances[3].subres = (ModelSubresource0x14 *)0x0;
  Subres0x14Instances[4].subres = (ModelSubresource0x14 *)0x0;
  Subres0x14Instances[5].subres = (ModelSubresource0x14 *)0x0;
  Subres0x14Instances[6].subres = (ModelSubresource0x14 *)0x0;
  Subres0x14Instances[7].subres = (ModelSubresource0x14 *)0x0;
  NumSubres0x14s = 0;
  D3D8::D3D_KickOffAndWaitForIdle();
  FUN_001593d0();
  FUN_000f97f0();
  do {
    iVar1 = FUN_00035d30();
    FUN_00036180();
    FUN_00036180();
  } while (iVar1 != 0);
  FUN_00034880();
  _DAT_0051065c = 0;
  return;
}




BOOL Game::AddSceneControl(char *param_1)

{
  char cVar1;
  char *pcVar2;
  
  pcVar2 = SceneControlAIDs + NumSceneControls * 0x80;
  do {
    cVar1 = *param_1;
    *pcVar2 = cVar1;
    pcVar2 = pcVar2 + 1;
    param_1 = param_1 + 1;
  } while (cVar1 != '\0');
  NumSceneControls = NumSceneControls + 1;
  return 1;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void Game::SetPauseState(PauseState param_1)

{
  char cVar1;
  float baseX;
  float fVar2;
  LoctextValueContext *pLVar3;
  Scene *pSVar4;
  int iVar5;
  LoctextDescriptor *pLVar6;
  undefined4 uVar7;
  uint int_or_pointer;
  char *pcVar8;
  char *pcVar9;
  undefined4 *puVar10;
  vec3 vStack_6a4;
  undefined4 uStack_698;
  undefined4 uStack_694;
  float afStack_690 [2];
  undefined4 uStack_688;
  undefined4 auStack_665 [4];
  undefined4 auStack_652 [18];
  WCHAR aWStack_608 [256];
  WCHAR aWStack_408 [256];
  WCHAR aWStack_208 [258];
  
  if (param_1 != g_pauseState) {
    do {
      pSVar4 = DAT_00510e30;
      fVar2 = g_DXContext.__0;
      baseX = g_DXContext.field28_0x48;
      g_pauseState = param_1;
      switch(param_1) {
      case Playing:
        FUN_0011eba0();
        g_globalFlagset = g_globalFlagset & ~Paused;
        g_paused_ = 0;
        if (DAT_00510e24 == (GamePauseContext *)0x0) {
          g_paused_ = 0;
          return;
        }
        FromPlayToPause(DAT_00510e24);
        DAT_00510e24 = (GamePauseContext *)0x0;
        return;
      case EnteringPause:
        GlobalCounter2 = GlobalCounter2 + 1;
        _DAT_00510e38 = 0;
        DAT_00510e34 = 1;
        Scripting::CreateScriptType2((InputHandlerType4 **)&g_pausePadScript);
        runtime::PushInputHandlerAndSetActive(g_pausePadScript,"pausepad");
        if (DAT_00510cf8 == (LoctextValueContext *)0x0) {
          DAT_00510e3c = runtime::rand * 0x19660d + 0x3c6ef35f;
          runtime::rand = DAT_00510e3c;
          runtime::AllocateForLoctext_(0,1,(void *)0x802c0,&DAT_00510cf8);
          int_or_pointer = DAT_00510e3c;
          pLVar3 = DAT_00510cf8;
          (DAT_00510cf8->somePos).x = 2.5;
          (pLVar3->somePos).y = 0.4;
          pLVar3->maybeState = int_or_pointer;
        }
        if (DAT_00510e30 == (Scene *)0x0) {
          pcVar8 = "aid_loctext_ghoulies_menu_menutext";
          puVar10 = &uStack_688;
          for (iVar5 = 8; iVar5 != 0; iVar5 = iVar5 + -1) {
            *puVar10 = *(undefined4 *)pcVar8;
            pcVar8 = pcVar8 + 4;
            puVar10 = puVar10 + 1;
          }
          *(undefined2 *)puVar10 = *(undefined2 *)pcVar8;
          *(char *)((int)puVar10 + 2) = pcVar8[2];
          puVar10 = auStack_665;
          for (iVar5 = 0x17; iVar5 != 0; iVar5 = iVar5 + -1) {
            *puVar10 = 0;
            puVar10 = puVar10 + 1;
          }
          vStack_6a4.x = g_DXContext.field32_0x58 + 16.0;
          vStack_6a4.y = g_DXContext.field35_0x64 - 16.0;
          *(undefined1 *)puVar10 = 0;
          uStack_698 = 0;
          uStack_694 = 0xc2000000;
          afStack_690[0] = 20.0;
          afStack_690[1] = -16.0;
          TransitionAndLoadScene
                    (0,0,&vStack_6a4,&uStack_698,afStack_690,0,0x3f800000,&DAT_3f400000,"menutext",
                     &uStack_688,&LAB_000c00c0);
          int_or_pointer = DAT_00510e3c;
          iVar5 = DAT_00510e30->field3814_0x1020;
          *(undefined4 *)(iVar5 + 0x14) = 0x40200000;
          *(float *)(iVar5 + 0x18) = 0.4;
          *(uint *)(iVar5 + 0x1c) = int_or_pointer;
        }
        FUN_00118cb0();
        vStack_6a4.x = DAT_00510e0c;
        vStack_6a4.y = DAT_00510e10 - 500.0;
        vStack_6a4.z = DAT_00510e14;
        SetBackgroundPositions(&vStack_6a4,(vec3 *)&DAT_00510e18);
        g_globalFlagset = g_globalFlagset | Paused;
        g_paused_ = 1;
        DAT_00507df4 = 1;
        DAT_00510cf0 = Assets::GetChapterIndexFromAID(GameState.currentSceneScript);
        if (DAT_00510cf0 == 0) {
          XAPILIB::lstrcpyW(aWStack_608,_No_Name_Available_);
        }
        else {
          pLVar6 = Assets::GetResourceBytesOrExit("aid_loctext_ghoulies_pause_pausetext");
          createGameselectString("pausetext","Chapter",aWStack_208,pLVar6);
          createGameselectString("pausetext","Scene",aWStack_408,pLVar6);
          Assets::DestroyAssetOrDecrement(pLVar6);
          int_or_pointer = ChapterIndexToTrueIndex[DAT_00510cf0];
          uVar7 = FUN_0011ec70();
                    // Print pause text
          XAPILIB::wsprintfW(aWStack_608,L"%s %d, %s %d: %s",aWStack_208,int_or_pointer,aWStack_408,
                             uVar7,_No_Name_Available_);
        }
        PlayGhoulLaugh();
        int_or_pointer = GetCurrentScenePauseFlags();
                    // Called pause game in mummmy basement,
                    // arg1=0x 90 00 00 00
        DAT_00510e24 = GamePauseContext::ctor(int_or_pointer,0,(char *)0x0);
        loctext::get_text(PTR_s_aid_loctext_ghoulies_pause_pause_00430c1c,"pausetext","Paused",
                          (LPWSTR)&DAT_00510ae8);
        DAT_00510e04 = CreateLoctext(DAT_00510cf8,(LPWSTR)&DAT_00510ae8,baseX,fVar2 - 25.0,1.5,1.5,
                                     3.0,1,1,1);
        DAT_00510e00 = CreateLoctext(DAT_00510cf8,aWStack_608,baseX,fVar2 - 125.0,0.75,0.75,3.0,1,1,
                                     1);
        FUN_0011dd90();
        iVar5 = FUN_0011ecf0();
        if (iVar5 == -1) {
          return;
        }
        iVar5 = FUN_000f2490();
        if (iVar5 == 0) {
          return;
        }
        pcVar8 = "aid_texture_ghoulies_scoreboard_pauseicons_bonusbooks";
        puVar10 = &uStack_688;
        for (iVar5 = 0xd; iVar5 != 0; iVar5 = iVar5 + -1) {
          *puVar10 = *(undefined4 *)pcVar8;
          pcVar8 = pcVar8 + 4;
          puVar10 = puVar10 + 1;
        }
        *(undefined2 *)puVar10 = *(undefined2 *)pcVar8;
        puVar10 = auStack_652;
        for (iVar5 = 0x12; iVar5 != 0; iVar5 = iVar5 + -1) {
          *puVar10 = 0;
          puVar10 = puVar10 + 1;
        }
        *(undefined2 *)puVar10 = 0;
        DAT_00510e40 = Assets::GetResourceBytesOrExit(&uStack_688);
        _DAT_00510e44 = baseX;
        _DAT_00510e48 = fVar2 + 210.0;
        _DAT_00510e4c = 0.75;
        _DAT_00510e50 = 0.75;
        return;
      case Paused:
        FUN_00048940(0.123);
        iVar5 = (int)DAT_00510e24 + 8;
        if (*(int *)((int)DAT_00510e24 + 8) != 0) {
          return;
        }
        CloseDoorAndUpdateState(1,*(Cutscene **)((int)DAT_00510e24 + 0x24));
        *(undefined4 *)iVar5 = 1;
        return;
      case New_Name_(2):
        Events::BeginDialogSequence(0);
        return;
      case ChallengeRules:
        if (g_pauseMenuState_ == Paused) {
          iVar5 = FUN_000d0780();
        }
        else {
          if (INT_004e17c8 != 3) {
            return;
          }
          iVar5 = FUN_0004a270();
        }
        if (iVar5 != 0) {
          return;
        }
        param_1 = Paused;
        if (g_pauseState == Paused) {
          return;
        }
        break;
      case ExitingPause:
        FUN_00048940(0.815);
        iVar5 = (int)DAT_00510e24 + 8;
        if (*(int *)((int)DAT_00510e24 + 8) != 0) {
          CloseDoorAndUpdateState(0,*(Cutscene **)((int)DAT_00510e24 + 0x24));
          *(undefined4 *)iVar5 = 0;
        }
        PlayGhoulLaugh();
        pSVar4 = DAT_00510e30;
        DAT_00510e30->field2160_0x950 = 0;
        FUN_00142c20(3,pSVar4);
        FUN_0005f7e0(DAT_00510cf8);
        FUN_0005f7e0(DAT_00510cf8);
        FUN_0005f7e0(DAT_00510cf8);
        return;
      case MapScreen:
        DAT_00510e2c = 0xffffffff;
        DAT_00510e30->field2160_0x950 = 0;
        FUN_00142c20(3,pSVar4);
        FUN_00048940(0.123);
        iVar5 = (int)DAT_00510e24 + 8;
        if (*(int *)((int)DAT_00510e24 + 8) != 0) {
          CloseDoorAndUpdateState(0,*(Cutscene **)((int)DAT_00510e24 + 0x24));
          *(undefined4 *)iVar5 = 0;
        }
        FUN_00048960();
        pcVar8 = FUN_001410f0();
        iVar5 = (int)DAT_00510e24;
        if (pcVar8 != (char *)0x0) {
          pcVar9 = (char *)((int)DAT_00510e24 + 0x118);
          do {
            cVar1 = *pcVar8;
            pcVar8 = pcVar8 + 1;
            *pcVar9 = cVar1;
            pcVar9 = pcVar9 + 1;
          } while (cVar1 != '\0');
          *(undefined1 *)(iVar5 + 0x138) = 0;
          return;
        }
        *(undefined1 *)((int)DAT_00510e24 + 0x118) = 0;
        *(undefined1 *)(iVar5 + 0x138) = 0;
        return;
      case 8:
        FUN_0011dd10();
        g_globalFlagset = g_globalFlagset | 0x2200;
        return;
      case 9:
        FUN_00048920();
        g_globalFlagset = g_globalFlagset & 0xffffddff;
        FUN_0011dd90();
        return;
      default:
        goto switchD_0011d4bf_default;
      }
    } while( true );
  }
switchD_0011d4bf_default:
  return;
}




void runtime::UpdateGameState(GameState *state)

{
  BOOL iVar1;
  
  if ((((state->preventLoading == 0) && (*(int *)state->newSceneScriptAID == 0x5f646961)) &&
      (EventLoop::SetLoadState(state,BeginLoading), TransitionData.discReadEnum != 1)) &&
     (TransitionData.discReadEnum != 2)) {
    EventLoop::CreateTransitionCameraAndText();
  }
  state->prev_load_state = state->load_state;
  if (((state->new_load_state != state->load_state) && (state->preventLoading == 0)) &&
     (g_paused_ == 0)) {
    EventLoop::SetLoadState(state,state->new_load_state);
  }
                    // Handle input 
  FUN_00109470(state->field81_0x230);
  UpdatePauseScreen();
  switch(state->load_state) {
  case EndingBookCutscene?:
    Game::GameState.new_load_state = Null;
    UpdateGameWorld(state);
    UpdateStorybook();
    return;
  case BeginLoading:
                    // Unable to run any cutscenes when skipped,
                    // - Music doesn't stop playing
                    // - Cutscene is permanently loading
                    // - Game fails to begin cutscene
                    // - Game fails to exit from cutscene
                    // 
                    // NO impact when disabled mid cutscene
    if (state->use_scene_focus != 0) {
      EventLoop::SetLoadState(state,Loading);
    }
    state->use_scene_focus = 1;
    UpdateStorybook();
    return;
  case Loading:
    Audio::Loading = 1;
    iVar1 = Events::loadBnlFromScriptAid();
    if ((iVar1 == 0) && (CacheContext.utilityDriveError = 0, TransitionData.discReadEnum == 2)) {
                    // Update transition state
      FUN_0012c770();
      state->preventLoading = 0;
      EventLoop::RunPostLoadSetupScripts(state);
      Game::GameState.new_load_state = FinishedLoading;
      UpdateStorybook();
      return;
    }
    break;
  case FinishedLoading:
    if (TransitionData.discReadEnum == 0) {
      Game::GameState.new_load_state = state->newLoadState2___;
      UpdateStorybook();
      return;
    }
    if (Game::GameState.currentChapter == 0) break;
  case Normal:
    UpdateGameWorld(state);
  }
  UpdateStorybook();
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void __fastcall UpdateGameWorld(GameState *state)

{
  sceneControlObj_0x8 puVar1;
  uint32_t uVar2;
  BOOL matches;
  float delta;
  Buffer<> *piVar2;
  sceneControlObj_0x8 next;
  
  if (state->someLoadedVar != 0) {
    uVar2 = state->someLoadedVar - 1;
    state->someLoadedVar = uVar2;
    if (uVar2 == 2) {
      Audio::Loading = 0;
    }
                    // If done loading, unmute the game
    UpdateGameVolumes();
  }
  if ((0.0 < runtime::dx_timer) &&
     (runtime::dx_timer = runtime::dx_timer - runtime::DeltaTime * runtime::TimeScale,
     runtime::dx_timer <= 0.0)) {
    runtime::dx_timer = 0.0;
  }
  delta = runtime::DeltaTime * runtime::TimeScale * 300.0 + g_totalTicksUpdated;
  g_ticksToRun = (int)delta;
                    // Disabling this causes weird animation effects and stiffness
  g_totalTicksUpdated = delta - (float)g_ticksToRun;
  UpdateCutsceneProgress();
  UpdateCutsceneAndDraws();
  Events::UpdateDialogState();
                    // If in dialogs
                    // 
  if (Game::UpdateActionType == 3) {
    CheckEndOfCutscene();
  }
  Scripting::updateLevelScript();
  Events::RunChallengeSetupTriggers();
  Events::RunEndOfScaryShockEvents();
  Scripting::updateLevelScript();
  puVar1 = Game::SceneControls.next;
  if (Game::InGhoulyIntro == 1) {
    EventLoop::ExecuteGhoulieIntro();
    puVar1 = Game::SceneControls.next;
  }
                    // Update scene controls
  while (puVar1 != (sceneControlObj_0x8)0x0) {
    next = *(sceneControlObj_0x8 *)(puVar1 + 4);
                    // Skipping this breaks
                    // - music in level
                    // - menu completely
                    // - menu input if menu already loaded
                    // - but not dialog?
    (**(code **)&(*(sceneControlObj **)(puVar1 + -8))->field_0x10)(puVar1 + -8);
    puVar1 = next;
  }
                    // 0x511b18 = scene tree?
                    // - set to 0 when entering level
  avatar::updateRecursive((avatar_0x918)Game::SceneInfo.sceneTree.head);
                    // Draw Background
  Background::updateViews();
  Events::UpdatePerSecondTimers();
  Events::UpdateGhoulyBoxes();
  Events::Scripting::RunScriptConditionsCallback2();
  Events::ExecuteGhoulieIntroLoctext();
  Events::NotUpdateDialogs_();
  delta = 0.0;
  if ((runtime::dx_timer <= 0.0) &&
     (delta = runtime::DeltaTime * runtime::TimeScale, 0.016666668 < delta)) {
    delta = 0.016666668;
  }
  Events::UpdateTextureMaybeSomethings(delta * 7.2);
  Graphics::CleanupResources_();
  if ((DAT_00510580 != 0) && (DAT_00510650 == 0)) {
    DAT_00510648 = DAT_00510648 + 0.002;
    DAT_0051064c = DAT_0051064c + 0.002;
    Graphics::InitialiseScreenSpaceQuads();
  }
  Events::UpdateDeltaAngles();
  Events::UpdateAmbientAudio();
  FUN_000fdda0();
  Graphics::UpdateFog_();
                    // Pause if able
  if ((((((int)Input::InputHandlers->tail - (int)Input::InputHandlers->head) /
         (int)(uint)Input::InputHandlers->valueSize != 0) &&
       (piVar2 = *(Buffer<> **)
                  (Input::InputHandlers->head->handlerName +
                  (Input::NumInputHandlers - 1) * (uint)Input::InputHandlers->valueSize + -4),
       piVar2 != (Buffer<> *)0x0)) &&
      (matches = Input::ContextHasButton(START,(InputHandlerType3 *)piVar2), matches != 0)) &&
     (Game::NotAllowedToPause == 0)) {
    Game::GameState.new_load_state =
         (-(uint)(g_paused_ != 0) & 0b11111111111111111111111111111011) + Paused;
  }
  return;
}



// WARNING: Globals starting with '_' overlap smaller symbols at the same address
// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


uint Game::GetSceneIndexFromAID(char *param_1)

{
  long lVar1;
  uint chapter_index;
  uint scene_index;
  int i;
  int startOffset;
  
  lVar1 = Assets::PlaycamAIDFromAID(param_1);
  chapter_index = Assets::GetChapterIndexFromAID(param_1);
  if (chapter_index == 0) {
    return 0xffffffff;
  }
  if (lVar1 != 0) {
    i = 1;
    startOffset = 0;
    if (1 < (int)chapter_index) {
      do {
        startOffset = startOffset + ChapterSceneCounts[i];
        i = i + 1;
      } while (i < (int)chapter_index);
    }
    return startOffset + -1 + lVar1;
  }
  scene_index = FUN_0004b530();
  return scene_index;
}




void deliverMessageToParam1(short param_1)

{
  int iVar1;
  int iVar3;
  avatar_0x918 iVar2;
  avatar *piVar2;
  
  iVar1 = Game::SceneInfo.sceneTree_;
  while (iVar1 != 0) {
    iVar3 = iVar1 + -0x92e;
    piVar2 = (avatar *)(iVar1 + -0x934);
    iVar1 = *(int *)(iVar1 + 4);
    if (*(short *)iVar3 == param_1) {
      (*piVar2->vtable->onMessage)(piVar2);
    }
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void UpdatePowerups(void)

{
  int *piVar1;
  int *piVar2;
  float *pfVar3;
  int iVar4;
  powerupId pwupType;
  float fVar5;
  float local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  undefined4 local_8;
  undefined4 local_4;
  
  pwupType = Null;
  pfVar3 = (float *)&Game::PowerupParams[0].duration;
  do {
    if ((pfVar3[-1] != 0.0) && (fVar5 = *pfVar3, 0.0 < fVar5)) {
      if ((ShouldntDroneBools[1] != 0) ||
         ((("\x01"[Game::CheckMoveOn] == '\0' || (fVar5 <= 0.0)) ||
          (fVar5 = fVar5 - runtime::DeltaTime * runtime::TimeScale, *pfVar3 = fVar5, 0.0 < fVar5))))
      {
        if (pfVar3[4] != 0.0) {
          FUN_00132620(*pfVar3 <= 3.0 && *pfVar3 != 3.0);
        }
      }
      else {
        *pfVar3 = 0.0;
        Game::DeactivatePowerup(pwupType);
      }
    }
    pfVar3 = pfVar3 + 6;
    pwupType = pwupType + Book;
  } while ((int)pfVar3 < 0x512324);
  iVar4 = 0;
  local_28 = 0.0;
  if (0 < DAT_00512320) {
    do {
      if (local_28 < (float)(&DAT_00512334)[iVar4]) {
        local_28 = (float)(&DAT_00512334)[iVar4];
      }
      if (((ShouldntDroneBools[1] != 0) || ("\x01"[Game::CheckMoveOn] == '\0')) ||
         (((float)(&DAT_00512334)[iVar4] <= 0.0 ||
          (fVar5 = (float)(&DAT_00512334)[iVar4] - runtime::DeltaTime * runtime::TimeScale,
          (&DAT_00512334)[iVar4] = fVar5, 0.0 < fVar5)))) {
        iVar4 = iVar4 + 1;
      }
      else {
        local_1c = 0;
        local_18 = 0;
        local_14 = 0;
        local_10 = 0;
        local_c = 0;
        local_8 = 0;
        local_4 = 0;
        (&DAT_00512334)[iVar4] = 0;
        local_24 = 0x4d;
        local_20 = 0x1b;
        (**(code **)(*(int *)(&DAT_00512324)[iVar4] + 0xc))((int *)(&DAT_00512324)[iVar4],&local_24)
        ;
        (&DAT_00512324)[iVar4] = (&DAT_00512320)[DAT_00512320];
        (&DAT_00512334)[iVar4] = (&DAT_00512330)[DAT_00512320];
        DAT_00512320 = DAT_00512320 + -1;
        if (DAT_00512320 == 0) {
          Game::DeactivatePowerup(MiniCooper);
        }
      }
    } while (iVar4 < DAT_00512320);
  }
  if (DAT_00512320 != 0) {
    if (3.0 <= local_28) {
      piVar2 = *(int **)(*UI::PowerupUI + 4);
      piVar1 = *(int **)(*UI::PowerupUI + 8);
      if (piVar2 < piVar1) {
        while (*piVar2 != Game::PowerupParams[0xc].field5_0x14) {
          piVar2 = piVar2 + 0x25;
          if (piVar1 <= piVar2) {
            return;
          }
        }
        piVar2[6] = 0;
      }
    }
    else {
      piVar2 = *(int **)(*UI::PowerupUI + 4);
      piVar1 = *(int **)(*UI::PowerupUI + 8);
      if (piVar2 < piVar1) {
        do {
          if (*piVar2 == Game::PowerupParams[0xc].field5_0x14) {
            piVar2[6] = 1;
            return;
          }
          piVar2 = piVar2 + 0x25;
        } while (piVar2 < piVar1);
        return;
      }
    }
  }
  return;
}




void Game::DeactivatePowerup(powerupId pwupType)

{
  ObjMsgID msg;
  undefined4 uStack_8;
  powerupId local_4;
  
  uStack_8 = PowerupParams[pwupType].field3_0xc;
  PowerupParams[pwupType].active = 0;
  msg = Scene_PowerupDeactivated;
  local_4 = pwupType;
  EventLoop::DispatchMessage(&msg);
  if (UI::PowerupUI != 0) {
    FUN_001319c0();
  }
  PowerupParams[pwupType].field5_0x14 = 0;
  PowerupParams[pwupType].active = 0;
  PowerupParams[pwupType].field3_0xc = 0;
  PowerupParams[pwupType].field2_0x8 = 0;
  PowerupParams[pwupType].field4_0x10 = 0;
  PowerupParams[pwupType].duration = 0;
  return;
}




int Game::OnSceneBegin(short param_1)

{
  avatar_0x900_conflict6 pEVar1;
  
  pEVar1 = SceneInfo.avatars.next;
  if (param_1 != 0) {
    for (; pEVar1 != (avatar_0x900_conflict6)0x0; pEVar1 = pEVar1->next) {
      if (ADJ(pEVar1)->field237_0x1fc == param_1) {
        return (int)ADJ(pEVar1);
      }
    }
  }
  return 0;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void runtime::UpdateGlobalTimers(void)

{
  float delta;
  
  delta = 0.0;
  if (dx_timer <= 0.0) {
    delta = DeltaTime * TimeScale;
  }
  g_ticksInCurrentLevel = g_ticksInCurrentLevel + 1;
  g_totalTimeSpentThisSession = g_totalTimeSpentThisSession + delta;
  g_timeSpentInCurrentLevel = g_timeSpentInCurrentLevel + delta;
  if ((g_globalFlagset & 0x27001e0) == 0) {
    Game::TimeInCurrentLevel = Game::TimeInCurrentLevel + delta;
    TicksInCurrentLevel = g_ticksInCurrentLevel;
  }
  return;
}




BOOL Timer::reduce(float *param_1)

{
  float fVar1;
  
  if (runtime::dx_timer <= 0.0) {
    fVar1 = runtime::DeltaTime * runtime::TimeScale;
  }
  else {
    fVar1 = 0.0;
  }
  if ((0.0 < *param_1) && (fVar1 = *param_1 - fVar1, *param_1 = fVar1, fVar1 <= 0.0)) {
    *param_1 = 0.0;
    return 1;
  }
  return 0;
}




void FUN_00130710(GameState *gameState,int param_2,int param_3)

{
  int *piVar1;
  actorBody *extraout_ECX;
  actorBody *extraout_ECX_00;
  actorBody *inAsset;
  undefined1 *puVar1;
  float fVar2;
  
  UI::LoadHealthTextures((actorBody *)gameState);
  fVar2 = 2.0;
  if ((INT_00433c38 != param_3) || (UI::PlayerHealth != param_3)) {
    BaronDraw_00433c10.scalar = 2.0;
  }
  INT_00433be0 = 1;
  INT_00433c70 = param_2;
  puVar1 = &LAB_00313a2c;
  if (param_2 == 0) {
    puVar1 = &LAB_00313a18;
  }
  if (param_3 < 0) {
    param_3 = 0;
  }
  inAsset = extraout_ECX;
  UI::PlayerHealth = param_3;
  if (INT_00433c38 == 0) {
    INT_00433c38 = param_3;
    FUN_0012f990(puVar1,&INT_00433c38);
    inAsset = extraout_ECX_00;
  }
  if ((Game::PowerupParams[10].active == 0) && (DAT_00433be8 != 1)) {
    inAsset = (actorBody *)0x0;
    piVar1 = &DAT_00313a40;
    do {
      if (INT_00433c38 <= *piVar1) {
        if (inAsset == (actorBody *)0x0) goto LAB_001307b9;
        break;
      }
      piVar1 = piVar1 + 6;
      inAsset = (actorBody *)((int)&inAsset->vtable + 1);
    } while ((int)piVar1 < 0x313ab8);
  }
  if (param_2 == 0) {
    return;
  }
LAB_001307b9:
  BaronDraw_00433c10.scalar = fVar2;
  UI::LoadHealthTextures(inAsset);
  return;
}




void FUN_00132540(uint powerupIndex)

{
  LoctextValueContext *pLVar1;
  BOOL BVar2;
  
  if (powerupIndex != 1) {
    u__00507e78[0] = L'\0';
    BVar2 = loctext::get_text("aid_loctext_ghoulies_scoreboard_powerups","powerups",
                              PowerUpStrings[powerupIndex] + 10,u__00507e78);
    if (BVar2 != 0) {
      if (g_UIElement3 == (LoctextValueContext *)0x0) {
        runtime::AllocateForLoctext_(0,0,(void *)0x4e4,&g_UIElement3);
        pLVar1 = g_UIElement3;
        (g_UIElement3->somePos).x = 2.5;
        (pLVar1->somePos).y = 0.7;
        pLVar1->maybeState = 0x80;
      }
      CreateLoctext(g_UIElement3,u__00507e78,(float)g_DXContext.backBufferWidth * 0.5,
                    g_DXContext.field35_0x64 - 25.0,0.97,0.97,1.5,1,0,0);
    }
  }
  return;
}




undefined4 HauntedObjectActivatedCondition::callback1(ScriptOperation *param_1)

{
  void *pvVar1;
  int *piVar2;
  int iVar3;
  
  pvVar1 = g_scriptRelatedLinkedList_;
  while( true ) {
    if (pvVar1 == (void *)0x0) {
      return 0;
    }
    if (*(int *)((int)pvVar1 + 8) == 0xb4) break;
    pvVar1 = *(void **)((int)pvVar1 + 4);
  }
  piVar2 = (int *)((int)pvVar1 + 8);
  if (piVar2 == (int *)0x0) {
    return 0;
  }
  do {
    if ((*(short *)param_1->data == 0) || ((short)piVar2[1] == *(short *)param_1->data)) {
      MindMemory::dtor((MindMemoryTargetWantedToAttack *)(piVar2 + -2));
      return 1;
    }
    iVar3 = piVar2[-1];
    if (iVar3 == 0) {
      return 0;
    }
    while (*(int *)(iVar3 + 8) != *piVar2) {
      iVar3 = *(int *)(iVar3 + 4);
      if (iVar3 == 0) {
        return 0;
      }
    }
    piVar2 = (int *)(iVar3 + 8);
  } while (piVar2 != (int *)0x0);
  return 0;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


BOOL PlayerEntersRegionCondition::callback1(int param_1)

{
  undefined4 uVar1;
  BOOL BVar2;
  vec3 local_c;
  
  uVar1 = *(undefined4 *)(param_1 + 8);
  if (((Game::SceneInfo.playerActors.prev != (actor_0x93c_conflict5)0x0) &&
      (ADJ(Game::SceneInfo.playerActors.prev) != (actor_conflict5 *)0x0)) &&
     (ADJ(Game::SceneInfo.playerActors.prev)->body->health != 0)) {
    avatar::getWorldPosition((avatar *)ADJ(Game::SceneInfo.playerActors.prev),&local_c);
    BVar2 = FUN_00124860(uVar1);
    return BVar2;
  }
  return 0;
}




float Game::AddDamage(byte index,byte damage)

{
  float health;
  float min_health;
  float min;
  
  health = HealthMetadata[index].maxHealth;
  min = HealthMetadata[index].minHealth;
  min_health = (float)HealthMetadata[index].minHealthU8;
  if ((float)HealthMetadata[index].maxHealthU8 != min_health) {
    min_health = (((float)damage - min_health) /
                 ((float)HealthMetadata[index].maxHealthU8 - min_health)) * (health - min) + min;
    if (health <= min) {
      if ((health <= min_health) && (health = min_health, min < min_health)) {
        return min;
      }
    }
    else if ((min_health <= health) && (health = min_health, min_health < min)) {
      return min;
    }
  }
  return health;
}




BOOL Game::AllGhoulyBoxesFinishedOpening(void)

{
  actorDroneActionId uVar1;
  GhoulyBox *pGVar1;
  DroneAction *action;
  int i;
  actor_0x934 a0x934;
  Buffer<> *drone_data;
  
  i = 0;
  pGVar1 = g_ghoulyBoxes.next;
  if (g_ghoulyBoxes.next != (GhoulyBox *)0x0) {
    do {
      if ((pGVar1->initialised_ & 1) == 0) {
        i = i + 1;
      }
      pGVar1 = pGVar1->next;
    } while (pGVar1 != (GhoulyBox *)0x0);
                    // If any of these match the 1 flag, return 0
    if (i != 0) {
      return 0;
    }
  }
  if (SceneInfo.newAvatars.next != (avatar_0x900_conflict6)0x0) {
    return 0;
  }
  a0x934 = (actor_0x934)SceneInfo.actors_0x934.head;
  if (SceneInfo.actors_0x934.head != (actor_0x934_conflict5)0x0) {
    do {
      drone_data = ADJ(a0x934)->droneActionsBuf;
      if (drone_data == (Buffer<> *)0x0) {
        uVar1 = Null;
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
        uVar1 = action->actionId;
      }
      switch(uVar1) {
      case Null:
      case StandNervously:
      case Eat:
      case Cook:
      case Dance:
      case CardPlaying1:
      case CardPlaying2:
      case DanceMove:
      case DJ:
      case Nothing:
      case NothingInvulnerable:
      case Dig1:
      case Dig2:
      case Dig3:
      case Overseer:
      case DanceInvulnerable:
      case NothingIgnoreTraitorFever:
        break;
      default:
                    // Grim reaper is failing this check
        if ((ADJ(a0x934)->derivedMarkerValue == (DerivedMarkerValue *)0x0) &&
           (ADJ(a0x934)->isDroning == 0)) {
          return 0;
        }
      }
      a0x934 = a0x934->next;
      if (a0x934 == (actor_0x934)0x0) {
        return 1;
      }
    } while( true );
  }
  return 1;
}




void Scene::free(Scene *scene)

{
  actor *paVar1;
  int iVar2;
  HeapTableEntry *puVar3;
  void **piVar4;
  int local_4;
  undefined4 uVar1;
  
  if ((scene->field2493_0xaf4 != 0) && (scene->field2492_0xaf0 != (void *)0x0)) {
    Assets::DestroyAssetOrDecrement(scene->field2492_0xaf0);
    scene->field2492_0xaf0 = (void *)0x0;
  }
  piVar4 = &scene->field2182_0x9a8;
  local_4 = 10;
  do {
    if (*piVar4 != (void *)0x0) {
      Assets::DestroyAssetOrDecrement(*piVar4);
      *piVar4 = (void *)0x0;
    }
    piVar4 = piVar4 + 1;
    local_4 = local_4 + -1;
  } while (local_4 != 0);
  if (scene->field3814_0x1020 != 0) {
    UnregisterScript__(scene->field3814_0x1020);
    scene->field3814_0x1020 = 0;
  }
  paVar1 = (actor *)scene->field3815_0x1024;
  scene->field2158_0x948 = 0;
  scene->inputContextStart = (SceneInputContext *)0x0;
  scene->field2160_0x950 = 0;
  scene->numInputCallbacks = 0;
  if (paVar1 != (actor *)0x0) {
    pickup::DetachFromActor((paVar1->avatar).statePickUp,paVar1);
    if ((paVar1->avatar).skipUpdate == 0) {
      local_4 = 0x80;
      (*((paVar1->avatar).vtable)->onMessage)(paVar1,&local_4);
      if ((paVar1->avatar).skipUpdate == 0) {
        removeavatarfromsomelistsshit(paVar1);
      }
    }
    scene->field3815_0x1024 = (int *)0x0;
  }
  iVar2 = FindHeapOf(scene);
  uVar1 = runtime::CurrentHeapToAllocateFrom;
  if (g_HeapTableBase[iVar2].heapHandle == (HANDLE)0x0) {
    puVar3 = (HeapTableEntry *)0x0;
  }
  else {
    puVar3 = g_HeapTableBase + iVar2;
  }
  runtime::CurrentHeapToAllocateFrom = iVar2;
  XAPILIB::HeapFree(puVar3->heapHandle,0,scene);
  runtime::CurrentHeapToAllocateFrom = uVar1;
  return;
}




void Scene::LoadFromLoadContext(SceneLoadContext *loadContext,Scene *scene)

{
  float *pfVar1;
  int i;
  
  scene->field2162_0x958 = (undefined *)loadContext->scene;
  scene->field2163_0x95c = (float)loadContext->createFlag;
  if (scene->field1_0x4 == 0) {
    scene->field2162_0x958 = (undefined *)loadContext->scene;
    scene->field2163_0x95c = (float)loadContext->createFlag;
    scene->field2164_0x960 = (float)scene->field2162_0x958 + scene->field2232_0x9e0;
    scene->field2165_0x964 = scene->field2163_0x95c + scene->field2233_0x9e4;
    scene->field2166_0x968 = scene->field2164_0x960 + scene->field2232_0x9e0;
    scene->field2167_0x96c = scene->field2165_0x964 + scene->field2233_0x9e4;
    scene->field2168_0x970 = scene->field2166_0x968 + scene->field2232_0x9e0;
    scene->field2169_0x974 = scene->field2167_0x96c + scene->field2233_0x9e4;
    scene->field2170_0x978 = scene->field2168_0x970 + scene->field2232_0x9e0;
    scene->field2171_0x97c = scene->field2169_0x974 + scene->field2233_0x9e4;
    scene->field2172_0x980 = scene->field2170_0x978 + scene->field2232_0x9e0;
    scene->field2173_0x984 = scene->field2171_0x97c + scene->field2233_0x9e4;
    scene->field2174_0x988 = scene->field2172_0x980 + scene->field2232_0x9e0;
    scene->field2175_0x98c = scene->field2173_0x984 + scene->field2233_0x9e4;
    scene->field2176_0x990 = scene->field2174_0x988 + scene->field2232_0x9e0;
    scene->field2177_0x994 = scene->field2175_0x98c + scene->field2233_0x9e4;
    scene->field2178_0x998 = scene->field2176_0x990 + scene->field2232_0x9e0;
    scene->field2179_0x99c = scene->field2177_0x994 + scene->field2233_0x9e4;
    scene->field2180_0x9a0 = scene->field2178_0x998 + scene->field2232_0x9e0;
    scene->field2181_0x9a4 = scene->field2179_0x99c + scene->field2233_0x9e4;
  }
  else if (scene->field1_0x4 == 1) {
    scene->field2162_0x958 = (undefined *)loadContext->scene;
    scene->field2163_0x95c = (float)loadContext->createFlag;
    scene->field2164_0x960 = (float)scene->field2162_0x958 + scene->field2234_0x9e8;
    scene->field2165_0x964 = scene->field2163_0x95c + scene->field2235_0x9ec;
    pfVar1 = &scene->field2167_0x96c;
    i = 4;
    do {
      pfVar1[-1] = (float)pfVar1[-5] + scene->field2232_0x9e0;
      *pfVar1 = pfVar1[-4] + scene->field2233_0x9e4;
      pfVar1 = pfVar1 + 4;
      i = i + -1;
    } while (i != 0);
    pfVar1 = &scene->field2169_0x974;
    i = 4;
    do {
      pfVar1[-1] = pfVar1[-5] + scene->field2232_0x9e0;
      *pfVar1 = pfVar1[-4] + scene->field2233_0x9e4;
      pfVar1 = pfVar1 + 4;
      i = i + -1;
    } while (i != 0);
    return;
  }
  return;
}




undefined4 FUN_00146b80(weapon *weapon,int *param_2,ushort weaponState)

{
  Model *pMVar1;
  ModelDescriptor *pMVar2;
  Subresource0x11 *pSVar3;
  uint8_t uVar4;
  undefined4 uStack_8;
  undefined4 uStack_4;
  
  if (*(int *)&weapon->field_0x9a0 == 0) {
    pMVar1 = (weapon->avatar).model;
    if (((pMVar1 == (Model *)0x0) || (pMVar2 = pMVar1->descriptor, pMVar2 == (ModelDescriptor *)0x0)
        ) || (pSVar3 = pMVar2->runtimeCtx->subres0x11, pSVar3 == (Subresource0x11 *)0x0)) {
      uVar4 = '\0';
    }
    else {
      uVar4 = pSVar3->otherCount;
    }
    if (uVar4 != '\0') {
      if ((param_2 == (int *)0x0) || (((short)param_2[0x337] != 2 && (param_2[0x24f] == 0)))) {
        weapon->weaponState = 0;
      }
      else {
        weapon->weaponState = weaponState;
      }
      ::weapon::onDestroy(weapon);
      weapon->arcContactValue = 0;
      (*(weapon->avatar).vtable[1].ctor)(weapon,weapon->attachState,9);
      weapon->attachState = 9;
      weapon->t = 0.0;
      (*(weapon->avatar).vtable[1].getAllocDetails)((ObjectAllocDetails *)weapon);
      if (param_2 != (int *)0x0) {
        uStack_4 = 0;
        uStack_8 = 0x50;
        (**(code **)(*param_2 + 0xc))(param_2,&uStack_8);
      }
      return 1;
    }
  }
  return 0;
}




void ___FrameUnwindToState(int param_1,undefined4 param_2,int param_3,int param_4)

{
  int iVar1;
  int *piVar2;
  int iVar3;
  
  iVar3 = *(int *)(param_1 + 8);
  iVar1 = FUN_0016ae40();
  *(int *)(iVar1 + 0x80) = *(int *)(iVar1 + 0x80) + 1;
  while (iVar3 != param_4) {
    if ((iVar3 < 0) || (*(int *)(param_3 + 4) <= iVar3)) {
      __inconsistency__YAXXZ();
    }
    iVar1 = iVar3 * 8;
    piVar2 = (int *)(*(int *)(param_3 + 8) + iVar1);
    iVar3 = *piVar2;
    if (piVar2[1] != 0) {
      *(int *)(param_1 + 8) = iVar3;
      __CallSettingFrame_12(*(undefined4 *)(*(int *)(param_3 + 8) + 4 + iVar1),param_1,0x103);
    }
  }
  FUN_0016ba2f();
  if (iVar3 != param_4) {
    __inconsistency__YAXXZ();
  }
  *(int *)(param_1 + 8) = iVar3;
  return;
}




