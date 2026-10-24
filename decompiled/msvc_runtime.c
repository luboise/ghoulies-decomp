/* msvc_runtime.c - MSVC C++ runtime / CRT / math (external, keep as-is) */
#include "msvc_runtime.h"

bool FALSE(void)

{
  return false;
}




void __break(void)

{
  code *pcVar1;
  
  pcVar1 = (code *)swi(3);
  (*pcVar1)();
  return;
}




BOOL strcmp(char *str1,char *str2)

{
  char cVar1;
  char cVar2;
  int iVar3;
  
  cVar1 = *str1;
  cVar2 = *str2;
  if (cVar1 == cVar2) {
    iVar3 = (int)str2 - (int)str1;
    do {
      str1 = str1 + 1;
      if (cVar1 == '\0') {
        return 1;
      }
      cVar1 = *str1;
      cVar2 = str1[iVar3];
    } while (cVar1 == cVar2);
  }
  return (uint)(cVar1 == cVar2);
}




void * malloc2electricboogaloo(uint size)

{
  undefined4 uVar1;
  void *pvVar2;
  
  uVar1 = runtime::CurrentHeapToAllocateFrom;
  if (size != 0) {
    runtime::CurrentHeapToAllocateFrom = 1;
    pvVar2 = malloc_(size);
    runtime::CurrentHeapToAllocateFrom = uVar1;
    return pvVar2;
  }
  return (void *)0x0;
}




void free2electricboogaloo(void *param_1)

{
  undefined4 uVar1;
  HeapTableEntry *pHVar2;
  
  uVar1 = runtime::CurrentHeapToAllocateFrom;
  runtime::CurrentHeapToAllocateFrom = 1;
  runtime::CurrentHeapToAllocateFrom = FindHeapOf(param_1);
  if (g_HeapTableBase[runtime::CurrentHeapToAllocateFrom].heapHandle == (HANDLE)0x0) {
    pHVar2 = (HeapTableEntry *)0x0;
  }
  else {
    pHVar2 = g_HeapTableBase + runtime::CurrentHeapToAllocateFrom;
  }
  XAPILIB::HeapFree(pHVar2->heapHandle,0,param_1);
  runtime::CurrentHeapToAllocateFrom = uVar1;
  return;
}



// WARNING: Inlined function: FUN_0015d060


Object * CreateFxFromAID(astruct_38 *outFx,char *assetName)

{
  objParams *params;
  Object *pOVar1;
  
  params = Assets::GetObjParams(assetName);
  if (params == (objParams *)0x0) {
    return (Object *)0x0;
  }
  *(astruct_38 **)(params + 1) = outFx;
  pOVar1 = (Object *)Assets::CreateEntityFromParams(params);
  free(params);
  return pOVar1;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields

undefined4
avatar::runPhysics(avatar *av,vec3 *sphereStart,vec3 *sphereEnd,CollisionMask colWhitelist,
                  void *collisionFunction,Collision0x54 *col0x54)

{
  BOOL not_colliding;
  CollisionMask collisionWhitelist;
  int iVar1;
  Skeleton *skeleton;
  ColliderSetDescriptor *col_desc;
  undefined4 in_stack_00000018;
  Collision0x54 CStack_54;
  ColliderSetDescriptor *c_set;
  Model *instance;
  ModelDescriptor *model_desc;
  
                    // Handles floor collision
  if (((av->model != (Model *)0x0) &&
      (model_desc = av->model->descriptor, model_desc != (ModelDescriptor *)0x0)) &&
     (col_desc = model_desc->runtimeCtx->colliders, col_desc != (ColliderSetDescriptor *)0x0)) {
                    // Checks for 0x1235 collision
    not_colliding = ColliderSetDescriptor::hasCollision0x1235_(col_desc);
    col_desc = (ColliderSetDescriptor *)(-(uint)(not_colliding != 0) & (uint)col_desc);
    if ((col_desc != (ColliderSetDescriptor *)0x0) &&
       (collisionWhitelist = colWhitelist & av->collisionMask, collisionWhitelist != Nothing)) {
      not_colliding = notCollidingWithSphereFromEndpoints(av,sphereStart,sphereEnd);
      if (not_colliding == 0) {
        instance = av->model;
        if (instance == (Model *)0x0) {
          skeleton = (Skeleton *)0x0;
        }
        else {
          skeleton = instance->skeleton;
          if (skeleton == (Skeleton *)0x0) {
            skeleton = instance->skeleton2;
          }
        }
        iVar1 = ColliderSetDescriptor::narrowCollisionCheck
                          (sphereStart,sphereEnd,col_desc,&av->drawAffine,&av->baseTransform,
                           skeleton,collisionWhitelist,collisionFunction,&CStack_54);
        if (iVar1 != 0) {
          resolveCollision(&CStack_54,in_stack_00000018);
          return 1;
        }
      }
      return 0;
    }
  }
  return 0;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields

undefined4
avatar::runDeltaPhysics
          (avatar *av,vec3 *pos,float radius,uint param_4,undefined4 param_5,Buffer<> *param_6)

{
  ModelDescriptor *pMVar1;
  ColliderSetDescriptor *desc;
  Model *pMVar2;
  BOOL BVar3;
  undefined4 uVar4;
  Skeleton *pSVar5;
  
  if ((((av->model != (Model *)0x0) &&
       (pMVar1 = av->model->descriptor, pMVar1 != (ModelDescriptor *)0x0)) &&
      (desc = pMVar1->runtimeCtx->colliders, desc != (ColliderSetDescriptor *)0x0)) &&
     ((BVar3 = ColliderSetDescriptor::hasCollision0x1235_(desc),
      (-(uint)(BVar3 != 0) & (uint)desc) != 0 && ((param_4 & av->collisionMask) != Nothing)))) {
                    // Broad phase collision check
    BVar3 = notSphereColliding(av,pos,radius);
                    // If colliding,
    if (BVar3 == 0) {
      pMVar2 = av->model;
      if (pMVar2 == (Model *)0x0) {
        pSVar5 = (Skeleton *)0x0;
      }
      else {
        pSVar5 = pMVar2->skeleton;
        if (pSVar5 == (Skeleton *)0x0) {
          pSVar5 = pMVar2->skeleton2;
        }
      }
      uVar4 = FUN_00055960(&av->drawAffine,&av->baseTransform,pSVar5,pos,(Buffer<> *)radius);
      return uVar4;
    }
    return 0;
  }
  return 0;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields

undefined4
avatar::handleWallCollisions
          (avatar *param_1,vec3 *param_2,vec3 *param_3,undefined4 param_4,
          CollisionMask collisionMask,undefined4 param_6,undefined4 param_7)

{
  ModelDescriptor *pMVar1;
  Model *pMVar2;
  BOOL has;
  CollisionMask CVar3;
  int collision_occurred;
  Skeleton *skeleton;
  Collision0x54 local_54;
  ColliderSetDescriptor *colliders;
  
  if (((param_1->model != (Model *)0x0) &&
      (pMVar1 = param_1->model->descriptor, pMVar1 != (ModelDescriptor *)0x0)) &&
     (colliders = pMVar1->runtimeCtx->colliders, colliders != (ColliderSetDescriptor *)0x0)) {
    has = ColliderSetDescriptor::hasCollision0x1235_(colliders);
    colliders = (ColliderSetDescriptor *)(-(uint)(has != 0) & (uint)colliders);
    if ((colliders != (ColliderSetDescriptor *)0x0) &&
       (CVar3 = collisionMask & param_1->collisionMask, CVar3 != Nothing)) {
      has = broadPhaseSphereCheck(param_3,param_4,param_1,param_2);
      if (has == 0) {
        pMVar2 = param_1->model;
        if (pMVar2 == (Model *)0x0) {
          skeleton = (Skeleton *)0x0;
        }
        else {
          skeleton = pMVar2->skeleton;
          if (skeleton == (Skeleton *)0x0) {
            skeleton = pMVar2->skeleton2;
          }
        }
        collision_occurred =
             ColliderSetDescriptor::runCollisionCallbacks
                       (colliders,&param_1->drawAffine,&param_1->baseTransform,skeleton,param_4,
                        CVar3,param_6,&local_54,param_2,param_3);
                    // Fix camera
        if (collision_occurred != 0) {
          resolveCollision(&local_54,param_7);
          return 1;
        }
      }
      return 0;
    }
  }
  return 0;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields

int avatar::checkForHitByWeapon
              (avatar *param_1,vec3 *param_2,vec3 *param_3,undefined4 param_4,CollisionMask param_5,
              vec3 *param_6)

{
  ModelDescriptor *pMVar1;
  AnimCollisionSubresource *pAVar2;
  Model *pMVar3;
  uint uVar4;
  BOOL BVar5;
  Skeleton *pSVar6;
  int iVar7;
  ModelFooterEntry *pMVar8;
  CollisionMask CVar9;
  uint32_t *puVar10;
  
  if ((param_1->model != (Model *)0x0) &&
     (pMVar1 = param_1->model->descriptor, pMVar1 != (ModelDescriptor *)0x0)) {
    uVar4 = 0;
    if (pMVar1->numFooterEntries != 0) {
      pMVar8 = pMVar1->footerEntries;
      while (pMVar8->subresourceType != AnimColliders) {
        uVar4 = uVar4 + 1;
        pMVar8 = pMVar8 + 1;
        if (pMVar1->numFooterEntries <= uVar4) {
          return 0;
        }
      }
      pAVar2 = (AnimCollisionSubresource *)pMVar1->footerEntries[uVar4].offset;
      if ((pAVar2 != (AnimCollisionSubresource *)0x0) &&
         (CVar9 = param_5 & param_1->collisionMask, CVar9 != Nothing)) {
        BVar5 = broadPhaseSphereCheck(param_3,param_4,param_1,param_2);
        if (BVar5 == 0) {
          if (param_1->model == (Model *)0x0) {
            puVar10 = (uint32_t *)0x0;
          }
          else {
            puVar10 = param_1->model->boneIndices;
          }
          pMVar3 = param_1->model;
          if (pMVar3 == (Model *)0x0) {
            pSVar6 = (Skeleton *)0x0;
          }
          else {
            pSVar6 = pMVar3->skeleton;
            if (pSVar6 == (Skeleton *)0x0) {
              pSVar6 = pMVar3->skeleton2;
            }
          }
                    // Handle hit by weapon
          iVar7 = MorphTargetsSubresource::checkCollisions
                            (pAVar2,&param_1->drawAffine,&param_1->baseTransform,pSVar6,param_4,
                             CVar9,(int)puVar10,param_6,param_2,param_3);
          return iVar7;
        }
      }
    }
  }
  return 0;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields

undefined4
avatar::checkCollisions2
          (avatar *av,vec3 *pathStart,vec3 *pathEnd,CollisionMask param_4,undefined4 param_5)

{
  Model *pMVar1;
  uint uVar2;
  BOOL BVar3;
  Skeleton *pSVar4;
  undefined4 uVar5;
  ModelSubresourceType *piVar6;
  CollisionMask CVar6;
  uint32_t *puVar7;
  ColliderSetDescriptor *desc;
  ModelDescriptor *entry;
  
  if ((av->model != (Model *)0x0) &&
     (entry = av->model->descriptor, entry != (ModelDescriptor *)0x0)) {
    uVar2 = 0;
    if (entry->numFooterEntries != 0) {
      piVar6 = &entry->footerEntries->subresourceType;
      while (*piVar6 != AnimColliders) {
        uVar2 = uVar2 + 1;
        piVar6 = piVar6 + 2;
        if (entry->numFooterEntries <= uVar2) {
          return 0;
        }
      }
      desc = (ColliderSetDescriptor *)entry->footerEntries[uVar2].offset;
      if ((desc != (ColliderSetDescriptor *)0x0) &&
         (CVar6 = param_4 & av->collisionMask, CVar6 != Nothing)) {
        BVar3 = notCollidingWithSphereFromEndpoints(av,pathStart,pathEnd);
        if (BVar3 == 0) {
          if (av->model == (Model *)0x0) {
            puVar7 = (uint32_t *)0x0;
          }
          else {
            puVar7 = av->model->boneIndices;
          }
          pMVar1 = av->model;
          if (pMVar1 == (Model *)0x0) {
            pSVar4 = (Skeleton *)0x0;
          }
          else {
            pSVar4 = pMVar1->skeleton;
            if (pSVar4 == (Skeleton *)0x0) {
              pSVar4 = pMVar1->skeleton2;
            }
          }
          uVar5 = FUN_000568e0(desc,&av->drawAffine,&av->baseTransform,pSVar4,CVar6,puVar7,param_5);
          return uVar5;
        }
      }
    }
  }
  return 0;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields

undefined4

void __break(void)

{
  code *pcVar1;
  
  pcVar1 = (code *)swi(3);
  (*pcVar1)();
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


undefined4 spawnFxAndAID(int *param_1)

{
  int *piVar1;
  undefined4 uVar2;
  
  if (*param_1 == 0x5f646961) {
    Assets::GetResourceBytes((char *)param_1,&param_1);
    piVar1 = param_1;
    if (param_1 != (int *)0x0) {
      uVar2 = FUN_00053140();
      Assets::DestroyAssetOrDecrement(piVar1);
      return uVar2;
    }
    runtime::ExitGame(2);
  }
  return 0;
}




void free(void *ptr)

{
  int heap;
  HeapTableEntry *pHVar3;
  undefined4 prev_heap;
  
  heap = FindHeapOf(ptr);
  prev_heap = runtime::CurrentHeapToAllocateFrom;
  if (g_HeapTableBase[heap].heapHandle == (HANDLE)0x0) {
    pHVar3 = (HeapTableEntry *)0x0;
  }
  else {
    pHVar3 = g_HeapTableBase + heap;
  }
  runtime::CurrentHeapToAllocateFrom = heap;
  XAPILIB::HeapFree(pHVar3->heapHandle,0,ptr);
  runtime::CurrentHeapToAllocateFrom = prev_heap;
  return;
}




undefined4 goalFunc2(Asset *param_1,int param_2)

{
  actorBody *body;
  StatetableResource *statetable;
  StatetableEntry *entry;
  actorBodyStateId desiredState;
  
  body = *(actorBody **)(*(int *)((int)param_1->name + 8) + 0x95c);
  if (*(short *)(param_2 + 8) == 0x29) {
    runtime::rand = runtime::rand * 0x19660d + 0x3c6ef35f;
    param_1 = (Asset *)(runtime::rand & 0x7fffff | 0x3f800000);
    *(float *)(param_2 + 0x18) =
         (*(float *)(param_2 + 0x14) - *(float *)(param_2 + 0x10)) * ((float)param_1 - 1.0) +
         *(float *)(param_2 + 0x10);
  }
  if ((*(short *)(param_2 + 8) == 1) || (*(short *)(param_2 + 8) == 0x12)) {
    desiredState = CameraCrane;
    if (body->stateId == CameraCrane) {
      return 1;
    }
    statetable = body->statetableRes;
    if (statetable == (StatetableResource *)0x0) {
      return 1;
    }
  }
  else {
    statetable = body->statetableRes;
    if (statetable == (StatetableResource *)0x0) {
      return 1;
    }
    desiredState = CameraMove;
  }
  entry = binarySearchStateTable(statetable,&param_1,desiredState);
  if (entry != (StatetableEntry *)0x0) {
    actorBody::updateStatesFromEntry(body,(AttackEntry *)param_1,entry);
  }
  return 1;
}




undefined4 goalFunc2(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  float in_XMM0_Da;
  float fVar3;
  
  iVar2 = *(int *)(param_1 + 0x10);
  iVar1 = *(int *)(param_1 + 8);
  if (*(short *)(param_2 + 8) == 0x29) {
    runtime::rand = runtime::rand * 0x19660d + 0x3c6ef35f;
    in_XMM0_Da = (*(float *)(param_2 + 0x14) - *(float *)(param_2 + 0x10)) *
                 ((float)(runtime::rand & 0x7fffff | 0x3f800000) - 1.0) + *(float *)(param_2 + 0x10)
    ;
    *(float *)(param_2 + 0x18) = in_XMM0_Da;
  }
  switch(*(undefined2 *)(param_2 + 8)) {
  case 0xd:
    if (iVar2 == 0) {
      return 0;
    }
    fVar3 = *(float *)(param_2 + 0x1c);
    FUN_000191c0();
    *(float *)(param_2 + 0x28) = fVar3;
    FUN_00041970();
    *(float *)(param_2 + 0x2c) = fVar3 + 3.1415927;
    return 1;
  case 0xe:
    if (iVar2 == 0) {
      return 0;
    }
    fVar3 = *(float *)(param_2 + 0x24);
    FUN_000191c0();
    *(float *)(param_2 + 0x34) = fVar3;
    FUN_00041970();
    *(float *)(param_2 + 0x38) = fVar3 + 3.1415927;
    return 1;
  case 0xf:
    FUN_0007edf0((float *)(param_2 + 0x2c),param_2 + 0x10);
    return 1;
  case 0x10:
    FUN_0007edf0((float *)(param_2 + 0x38),param_2 + 0x1c);
    return 1;
  case 0x11:
    FUN_0007edf0((float *)(param_2 + 0x38),param_2 + 0x10);
    return 1;
  default:
    goto switchD_0007c5fb_caseD_12;
  case 0x24:
    if ((iVar2 == 0) || (*(int *)(param_2 + 0x20) != 0)) {
      in_XMM0_Da = *(float *)(iVar1 + 0x18);
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
    iVar2 = param_2 + 0x1c;
    break;
  case 0x2f:
    iVar2 = param_2 + 0x10;
  }
  FUN_0007edf0((float *)(param_2 + 0x2c),iVar2);
switchD_0007c5fb_caseD_12:
  return 1;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


bool updateParticles(Buffer<> *param_1,float delta)

{
  float fVar1;
  ExtinguisherThing *pEVar2;
  ExtinguisherThing *tail;
  ExtinguisherThing *head;
  float newTimeAlive;
  float fVar3;
  float fVar4;
  uint64_t uVar5;
  float local_8;
  
  tail = param_1->tail;
  head = param_1->head;
  if (head < tail) {
    do {
      head->field4_0x10 = delta * 0.0 + head->field4_0x10;
      head->field16_0x34 = head->field15_0x30 * delta + head->field16_0x34;
      head->field1_0x4 = head->field1_0x4 + delta * head->field4_0x10;
      newTimeAlive = head->timeAlive + delta;
      head->field0_0x0 = head->field0_0x0 + head->field3_0xc * delta;
      head->field2_0x8 = head->field2_0x8 + head->field5_0x14 * delta;
      head->timeAlive = newTimeAlive;
      if (newTimeAlive < head->survivalTime) {
                    // Don't clean up 
        fVar4 = head->field14_0x2c;
        fVar1 = head->field13_0x28;
        if (head->survivalTime != 0.0) {
          fVar3 = (newTimeAlive / head->survivalTime) * (fVar4 - fVar1) + fVar1;
          if (fVar4 <= fVar1) {
            if ((fVar4 <= fVar3) && (fVar4 = fVar3, fVar1 < fVar3)) {
              fVar4 = fVar1;
            }
          }
          else if ((fVar3 <= fVar4) && (fVar4 = fVar3, fVar3 < fVar1)) {
            fVar4 = fVar1;
          }
        }
        head->field12_0x24 = fVar4;
        local_8 = (float)head->field10_0x22;
        fVar4 = (float)head->field9_0x21;
        if (head->survivalTime != 0.0) {
          newTimeAlive = (newTimeAlive / head->survivalTime) * (local_8 - fVar4) + fVar4;
          if (local_8 <= fVar4) {
            if ((local_8 <= newTimeAlive) && (local_8 = fVar4, newTimeAlive <= fVar4))
            goto LAB_000c7fdd;
          }
          else if ((newTimeAlive <= local_8) && (local_8 = fVar4, fVar4 <= newTimeAlive)) {
LAB_000c7fdd:
            local_8 = newTimeAlive;
          }
        }
        uVar5 = float10::to_uint64_t((float10)local_8);
        head->field8_0x20 = (char)uVar5;
      }
      else {
        pEVar2 = (ExtinguisherThing *)((int)param_1->tail - (uint)param_1->valueSize);
        if (head < pEVar2) {
          _memmove(head,(void *)((int)&head->field0_0x0 + (uint)param_1->valueSize),
                   (int)pEVar2 - (int)head);
        }
        head = head + -1;
        param_1->tail = (ExtinguisherThing *)((int)param_1->tail - (uint)param_1->valueSize);
        tail = tail + -1;
      }
      head = head + 1;
    } while (head < tail);
  }
  return ((int)param_1->tail - (int)param_1->head) / (int)(uint)param_1->valueSize != 0;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields

void entityWeaponExtinguisher::updateProjectilesOrCreate
               (entityWeaponExtinguisher *param_1,float param_2,float *param_3,vec3 *param_4)

{
  ExtinguisherThing *pEVar1;
  entityWeaponExtinguisher *peVar2;
  int iVar3;
  Buffer<> *pBVar4;
  int iVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  float fVar10;
  uint64_t uVar11;
  vec3 local_c;
  
  peVar2 = param_1;
  (param_1->weapon).field_0x940 = SUB41(param_2,0);
  if (runtime::dx_timer <= 0.0) {
    fVar9 = runtime::DeltaTime * runtime::TimeScale;
  }
  else {
    fVar9 = 0.0;
  }
  fVar6 = 0.0;
  if ((param_1->weapon).avatar.movementFreezeTimer <= 0.0) {
    fVar6 = (param_1->weapon).avatar.actionSpeed;
  }
  if (param_2 == 0.0) {
    fVar9 = param_1->somebullshitprojectileairresistance - fVar6 * fVar9 * 4.95;
    param_1->somebullshitprojectileairresistance = fVar9;
    if (fVar9 < 0.01) {
      param_1->somebullshitprojectileairresistance = 0.01;
      return;
    }
  }
  else {
    fVar9 = fVar6 * fVar9 * 1.98 + param_1->somebullshitprojectileairresistance;
    param_1->somebullshitprojectileairresistance = fVar9;
    if (1.0 < fVar9) {
      param_1->somebullshitprojectileairresistance = 1.0;
    }
    if (runtime::dx_timer <= 0.0) {
      fVar9 = runtime::DeltaTime * runtime::TimeScale;
    }
    else {
      fVar9 = 0.0;
    }
    fVar6 = 0.0;
    if ((param_1->weapon).avatar.movementFreezeTimer <= 0.0) {
      fVar6 = (param_1->weapon).avatar.actionSpeed;
    }
    param_1->someProjectilesNumber = fVar6 * fVar9 + param_1->someProjectilesNumber;
    fVar6 = param_1->field143_0xee8 * 70.0 + 30.0;
    fVar7 = (param_1->field143_0xee8 + 1.0) * 0.5;
    param_1 = (entityWeaponExtinguisher *)0x0;
    D3DX8::D3DXVec3Normalize(&local_c,param_4);
    fVar9 = peVar2->someProjectilesNumber;
    while (0.033333335 < fVar9) {
      pBVar4 = peVar2->particles;
      if (pBVar4->tail == pBVar4->end) {
        iVar3 = ((int)pBVar4->tail - (int)pBVar4->head) / (int)(uint)pBVar4->valueSize;
        iVar5 = (uint)(ushort)pBVar4->capacity + iVar3;
        pBVar4 = (Buffer<> *)AllocateMoreAStruct_33((uint)pBVar4->valueSize * iVar5 + 0x10,pBVar4);
        pEVar1 = pBVar4->values;
        pBVar4->end = (ExtinguisherThing *)
                      ((int)&pEVar1->field0_0x0 + (uint)pBVar4->valueSize * iVar5);
        pBVar4->head = pEVar1;
        pBVar4->tail = (ExtinguisherThing *)
                       ((int)&pEVar1->field0_0x0 + (uint)pBVar4->valueSize * iVar3);
        peVar2->particles = pBVar4;
      }
      pEVar1 = pBVar4->tail;
      pBVar4->tail = (ExtinguisherThing *)((int)&pEVar1->field0_0x0 + (uint)pBVar4->valueSize);
      fVar9 = (float)param_1 * fVar6;
      pEVar1->field0_0x0 = *param_3 + local_c.x * fVar9;
      pEVar1->field1_0x4 = param_3[1] + local_c.y * fVar9;
      pEVar1->field2_0x8 = param_3[2] + local_c.z * fVar9;
      pEVar1->field3_0xc = local_c.x * fVar6;
      pEVar1->field4_0x10 = local_c.y * fVar6;
      pEVar1->field5_0x14 = local_c.z * fVar6;
      runtime::rand = runtime::rand * 0x19660d + 0x3c6ef35f;
      pEVar1->survivalTime =
           ((float)(runtime::rand & 0x7fffff | 0x3f800000) - 1.0) * 0.19999999 + 0.25;
      pEVar1->timeAlive = (float)param_1;
      pEVar1->field_0x23 = 0;
      runtime::rand = runtime::rand * 0x19660d + 0x3c6ef35f;
      pEVar1->field13_0x28 =
           (((float)(runtime::rand & 0x7fffff | 0x3f800000) - 1.0) * 0.29999995 + 2.5) * fVar7;
      runtime::rand = runtime::rand * 0x19660d + 0x3c6ef35f;
      fVar8 = (((float)(runtime::rand & 0x7fffff | 0x3f800000) - 1.0) + 8.0) * fVar7;
      fVar9 = pEVar1->field13_0x28;
      pEVar1->field14_0x2c = fVar8;
      if (pEVar1->survivalTime != 0.0) {
        fVar10 = (pEVar1->timeAlive / pEVar1->survivalTime) * (fVar8 - fVar9) + fVar9;
        if (fVar8 <= fVar9) {
          if ((fVar8 <= fVar10) && (fVar8 = fVar9, fVar10 <= fVar9)) goto LAB_000c83b8;
        }
        else if ((fVar10 <= fVar8) && (fVar8 = fVar9, fVar9 <= fVar10)) {
LAB_000c83b8:
          fVar8 = fVar10;
        }
      }
      pEVar1->field12_0x24 = fVar8;
      runtime::rand = runtime::rand * 0x19660d + 0x3c6ef35f;
      uVar11 = float10::to_uint64_t
                         (((float10)(float)(runtime::rand & 0x7fffff | 0x3f800000) - (float10)1.0) *
                          (float10)32.0 + (float10)192.0);
      pEVar1->field9_0x21 = (byte)uVar11;
      runtime::rand = runtime::rand * 0x19660d + 0x3c6ef35f;
      uVar11 = float10::to_uint64_t
                         (((float10)(float)(runtime::rand & 0x7fffff | 0x3f800000) - (float10)1.0) *
                          (float10)32.0 + (float10)64.0);
      pEVar1->field10_0x22 = (byte)uVar11;
      param_2 = (float)(byte)uVar11;
      fVar9 = (float)pEVar1->field9_0x21;
      if (pEVar1->survivalTime != 0.0) {
        fVar8 = (pEVar1->timeAlive / pEVar1->survivalTime) * (param_2 - fVar9) + fVar9;
        if (param_2 <= fVar9) {
          if ((param_2 <= fVar8) && (param_2 = fVar9, fVar8 <= fVar9)) goto LAB_000c84a4;
        }
        else if ((fVar8 <= param_2) && (param_2 = fVar9, fVar9 <= fVar8)) {
LAB_000c84a4:
          param_2 = fVar8;
        }
      }
      uVar11 = float10::to_uint64_t((float10)param_2);
      pEVar1->field8_0x20 = (char)uVar11;
      runtime::rand = runtime::rand * 0x19660d + 0x3c6ef35f;
      pEVar1->field15_0x30 =
           ((float)(runtime::rand & 0x7fffff | 0x3f800000) - 1.0) * 180.0 * 0.017453292 + 1.2217305;
      runtime::rand = runtime::rand * 0x19660d + 0x3c6ef35f;
      pEVar1->field16_0x34 = ((float)(runtime::rand & 0x7fffff | 0x3f800000) - 1.0) * 6.2831855;
      peVar2->someProjectilesNumber = peVar2->someProjectilesNumber - 0.033333335;
      param_1 = (entityWeaponExtinguisher *)((float)param_1 + 0.033333335);
      fVar9 = peVar2->someProjectilesNumber;
    }
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void __fastcall memcpy(void *dst,void *str,uint size)

{
  int iVar1;
  uint uVar2;
  
  if ((size != 0) && (dst != str)) {
    if ((((uint)dst & 7) == 0) && ((((uint)str & 7) == 0 && (7 < size)))) {
      uVar2 = size >> 3;
      do {
        *(undefined4 *)dst = *(undefined4 *)str;
        *(undefined4 *)((int)dst + 4) = *(undefined4 *)((int)str + 4);
        dst = (void *)((int)dst + 8);
        str = (void *)((int)str + 8);
        size = size - 8;
        uVar2 = uVar2 - 1;
      } while (uVar2 != 0);
    }
    if (((((uint)dst & 3) == 0) && (((uint)str & 3) == 0)) && (3 < size)) {
      uVar2 = size >> 2;
      do {
        *(undefined4 *)dst = *(undefined4 *)str;
        dst = (void *)((int)dst + 4);
        str = (void *)((int)str + 4);
        size = size - 4;
        uVar2 = uVar2 - 1;
      } while (uVar2 != 0);
    }
    if (size != 0) {
      iVar1 = (int)str - (int)dst;
      do {
        *(undefined1 *)dst = *(undefined1 *)(iVar1 + (int)dst);
        dst = (void *)((int)dst + 1);
        size = size - 1;
      } while (size != 0);
    }
  }
  return;
}




void * malloc_(uint size)

{
  undefined2 *puVar1;
  void *pcVar2;
  int iVar3;
  HeapTableEntry *pHVar4;
  
  if (g_HeapTableBase[runtime::CurrentHeapToAllocateFrom].heapHandle == (HANDLE)0x0) {
    pHVar4 = (HeapTableEntry *)0x0;
  }
  else {
    pHVar4 = g_HeapTableBase + runtime::CurrentHeapToAllocateFrom;
  }
  pcVar2 = (void *)runtime::AllocateOnHeap(pHVar4->heapHandle,0,size + 4);
  if (pcVar2 != (void *)0x0) {
    iVar3 = FUN_0014ded0(pHVar4->heapHandle,0,pcVar2);
    puVar1 = (undefined2 *)(iVar3 + -4 + (int)pcVar2);
    *puVar1 = 0x1234;
    *(undefined1 *)(puVar1 + 1) = *(undefined1 *)&pHVar4->field32_0x20;
  }
  return pcVar2;
}




void * malloc_(uint size)

{
  undefined2 *puVar1;
  void *pvVar2;
  int iVar3;
  HeapTableEntry *pHVar4;
  
  if (g_HeapTableBase[runtime::CurrentHeapToAllocateFrom].heapHandle == (HANDLE)0x0) {
    pHVar4 = (HeapTableEntry *)0x0;
  }
  else {
    pHVar4 = g_HeapTableBase + runtime::CurrentHeapToAllocateFrom;
  }
  pvVar2 = (void *)runtime::AllocateOnHeap(pHVar4->heapHandle,0,size + 4);
  if (pvVar2 != (void *)0x0) {
    iVar3 = FUN_0014ded0(pHVar4->heapHandle,0,pvVar2);
    puVar1 = (undefined2 *)(iVar3 + -4 + (int)pvVar2);
    *puVar1 = 0x1234;
    *(undefined1 *)(puVar1 + 1) = *(undefined1 *)&pHVar4->field32_0x20;
  }
  return pvVar2;
}




uint __fastcall strcasecmp(char *s1,char *s2)

{
  char c1;
  char c2;
  int diff;
  
  diff = (int)s2 - (int)s1;
  while( true ) {
                    // Convert to uppercase
    c1 = *s1;
    if (0b00100000 < (byte)c1) {
      c1 = c1 & uVar4;
    }
    c2 = s1[diff];
    if (0b00100000 < (byte)c2) {
      c2 = c2 & uVar8;
    }
    if (c1 != c2) break;
    s1 = s1 + 1;
    if (c1 == 0) {
      return 0;
    }
  }
  return (uint)(byte)c1 - (uint)(byte)c2;
}




float System__GetMSElapsed_(void)

{
  float fVar1;
  
  fVar1 = 0.0;
  if (runtime::dx_timer <= 0.0) {
    fVar1 = runtime::DeltaTime * runtime::TimeScale;
  }
  return fVar1;
}




ushort nameFromObjectTag(ObjectTag tag)

{
  char first;
  ushort index;
  char *ptr_offset;
  char c2;
  char c;
  uint asset_ptr;
  char *read_ptr;
  char *ptr;
  
  ptr_offset = "objTag_Null" + -(int)Assets::GhouliesStatsheet;
  index = 1;
  asset_ptr = (uint)Assets::GhouliesStatsheet;
  while( true ) {
    first = ((StatsheetEntry *)asset_ptr)->tagName[0];
    c = 'o';
    read_ptr = (char *)asset_ptr;
    c2 = first;
                    // If tag starts with 'o'
    if (first == 'o') {
      do {
        read_ptr = read_ptr + 1;
        if (c2 == '\0') {
          return 0;
        }
        c2 = *read_ptr;
        c = ptr_offset[(int)read_ptr];
      } while (c2 == c);
    }
    if (c2 == c) {
      return 0;
    }
    c = *ActorTagTable[tag];
    if (first == c) {
      ptr = (char *)asset_ptr;
      do {
        ptr = ptr + 1;
        if (first == '\0') {
          return index;
        }
        first = *ptr;
        c = ptr[(int)ActorTagTable[tag] - asset_ptr];
      } while (first == c);
    }
    if (first == c) break;
    asset_ptr = asset_ptr + 0x87;
    ptr_offset = ptr_offset + -0x87;
    index = index + 1;
  }
  return index;
}




void destroyGlobalMalloced100(void)

{
  actor *paVar1;
  undefined4 uVar2;
  int iVar3;
  Malloced100 *pMVar4;
  HeapTableEntry *pHVar5;
  undefined4 local_4;
  
  UnregisterScript__((int)malloced100->loctextValueCtx);
  pMVar4 = malloced100;
  malloced100->loctextValueCtx = (LoctextValueContext *)0x0;
  if (pMVar4->param9 != 0.0) {
    iVar3 = pMVar4->field22_0x60;
    while (iVar3 != 0) {
      iVar3 = *(int *)(iVar3 + 4);
      FUN_001434e0();
      pMVar4 = malloced100;
    }
  }
  if (pMVar4->value != (Malloced100Value *)0x0) {
    FUN_00144820();
    pMVar4 = malloced100;
  }
  if (pMVar4->value2 != (Malloced100Value *)0x0) {
    FUN_00144820();
    pMVar4 = malloced100;
  }
  paVar1 = (actor *)pMVar4->buttonBat;
  pickup::DetachFromActor((paVar1->avatar).statePickUp,paVar1);
  if ((paVar1->avatar).skipUpdate == 0) {
    local_4 = 0x80;
    (*((paVar1->avatar).vtable)->onMessage)(paVar1,&local_4);
    if ((paVar1->avatar).skipUpdate == 0) {
      removeavatarfromsomelistsshit(paVar1);
    }
  }
  pMVar4 = malloced100;
  malloced100->buttonBat = (entityAvatarMiscButtonBat *)0x0;
  iVar3 = FindHeapOf(pMVar4);
  uVar2 = runtime::CurrentHeapToAllocateFrom;
  if (g_HeapTableBase[iVar3].heapHandle == (HANDLE)0x0) {
    pHVar5 = (HeapTableEntry *)0x0;
  }
  else {
    pHVar5 = g_HeapTableBase + iVar3;
  }
  runtime::CurrentHeapToAllocateFrom = iVar3;
  XAPILIB::HeapFree(pHVar5->heapHandle,0,pMVar4);
  runtime::CurrentHeapToAllocateFrom = uVar2;
  malloced100 = (Malloced100 *)0x0;
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void destroyNode(BigBlockCallbackCtx *param_1,ndHeader *header,undefined4 param_3)

{
                    // Goes to 0x158940
  (*param_1->callbacks[1])(header,param_3);
  return;
}



// WARNING: This is an inlined function


uint Get20(void)

{
  return 0x14;
}




int cmp_fn(uint param_1,LSBLValueLookup *param_2)

{
  return (param_1 & 0xffff) - (uint)param_2->hash;
}




uint16_t getLoctextHash(char *param_1)

{
  uint16_t ret;
  uint masked;
  uint acc;
  char cVar1;
  
  acc = 0;
  ret = 0;
  cVar1 = *param_1;
  while ((short)cVar1 != 0) {
                    // Shift 4 bits to the left, then add the new value
    acc = acc * 0x10 + (uint)(ushort)(short)cVar1;
    masked = acc & 0xf000;
    param_1 = param_1 + 1;
    if ((short)masked != 0) {
      acc = acc ^ (masked >> 8 | masked);
    }
    ret = (uint16_t)acc;
    cVar1 = *param_1;
  }
  return ret;
}




void __fastcall __1exception__UAE_XZ(undefined4 *param_1)

{
  *param_1 = &PTR_FUN_002090d0;
  if (param_1[2] != 0) {
    FUN_00167f2e(param_1[1]);
  }
  return;
}




void __fastcall __1type_info__UAE_XZ(undefined4 *param_1)

{
  *param_1 = &type_info::vftable;
  FUN_001681c1(0xe);
  if (param_1[1] != 0) {
    FUN_00167f2e(param_1[1]);
  }
  FUN_00165f0e();
  return;
}




undefined4 __thiscall ___Gtype_info__UAEPAXI_Z(undefined4 param_1,byte param_2)

{
  __1type_info__UAE_XZ();
  if ((param_2 & 1) != 0) {
    thunk_FUN_00167f2e(param_1);
  }
  return param_1;
}



// Library Function - Single Match
//  ??2@YAPAXI@Z
// 
// Library: Visual Studio 2003 Release


void __2_YAPAXI_Z(undefined4 param_1)

{
  __nh_malloc(param_1,1);
  return;
}



// Library Function - Single Match
//  _wcsncpy
// 
// Library: Visual Studio 2003 Release


LPWSTR lstrcpyW(LPWSTR dst,WCHAR *src)

{
  WCHAR WVar1;
  LPWSTR pWVar2;
  
  pWVar2 = dst;
  do {
    WVar1 = *src;
    *pWVar2 = WVar1;
    pWVar2 = pWVar2 + 1;
    src = src + 1;
  } while (WVar1 != L'\0');
  return dst;
}



// Library Function - Single Match
//  __fclose_lk
// 
// Library: Visual Studio 2003 Release


undefined4 __fclose_lk(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  
  uVar2 = 0xffffffff;
  if ((*(byte *)(param_1 + 0xc) & 0x83) != 0) {
    uVar2 = __flush(param_1);
    __freebuf(param_1);
    iVar1 = __close(*(undefined4 *)(param_1 + 0x10));
    if (iVar1 < 0) {
      uVar2 = 0xffffffff;
    }
    else if (*(int *)(param_1 + 0x1c) != 0) {
      FUN_00167f2e(*(int *)(param_1 + 0x1c));
      *(undefined4 *)(param_1 + 0x1c) = 0;
    }
  }
  *(undefined4 *)(param_1 + 0xc) = 0;
  return uVar2;
}



// WARNING: Function: __SEH_prolog replaced with injection: SEH_prolog
// WARNING: Function: __SEH_epilog replaced with injection: EH_epilog3
// Library Function - Single Match
//  _fclose
// 
// Library: Visual Studio 2003 Release


uint __abstract_cw(void)

{
  uint uVar1;
  ushort uVar2;
  ushort unaff_BX;
  
  uVar1 = 0;
  if ((unaff_BX & 1) != 0) {
    uVar1 = 0x10;
  }
  if ((unaff_BX & 4) != 0) {
    uVar1 = uVar1 | 8;
  }
  if ((unaff_BX & 8) != 0) {
    uVar1 = uVar1 | 4;
  }
  if ((unaff_BX & 0x10) != 0) {
    uVar1 = uVar1 | 2;
  }
  if ((unaff_BX & 0x20) != 0) {
    uVar1 = uVar1 | 1;
  }
  if ((unaff_BX & 2) != 0) {
    uVar1 = uVar1 | 0x80000;
  }
  uVar2 = unaff_BX & 0xc00;
  if ((unaff_BX & 0xc00) != 0) {
    if (uVar2 == 0x400) {
      uVar1 = uVar1 | 0x100;
    }
    else if (uVar2 == 0x800) {
      uVar1 = uVar1 | 0x200;
    }
    else if (uVar2 == 0xc00) {
      uVar1 = uVar1 | 0x300;
    }
  }
  if ((unaff_BX & 0x300) == 0) {
    uVar1 = uVar1 | 0x20000;
  }
  else if ((unaff_BX & 0x300) == 0x200) {
    uVar1 = uVar1 | 0x10000;
  }
  if ((unaff_BX & 0x1000) != 0) {
    uVar1 = uVar1 | 0x40000;
  }
  return uVar1;
}



// Library Function - Single Match
//  __hw_cw
// 
// Library: Visual Studio 2003 Release


uint __hw_cw(void)

{
  uint uVar1;
  uint uVar2;
  uint unaff_EBX;
  
  uVar1 = (uint)((unaff_EBX & 0x10) != 0);
  if ((unaff_EBX & 8) != 0) {
    uVar1 = uVar1 | 4;
  }
  if ((unaff_EBX & 4) != 0) {
    uVar1 = uVar1 | 8;
  }
  if ((unaff_EBX & 2) != 0) {
    uVar1 = uVar1 | 0x10;
  }
  if ((unaff_EBX & 1) != 0) {
    uVar1 = uVar1 | 0x20;
  }
  if ((unaff_EBX & 0x80000) != 0) {
    uVar1 = uVar1 | 2;
  }
  uVar2 = unaff_EBX & 0x300;
  if (uVar2 != 0) {
    if (uVar2 == 0x100) {
      uVar1 = uVar1 | 0x400;
    }
    else if (uVar2 == 0x200) {
      uVar1 = uVar1 | 0x800;
    }
    else if (uVar2 == 0x300) {
      uVar1 = uVar1 | 0xc00;
    }
  }
  if ((unaff_EBX & 0x30000) == 0) {
    uVar1 = uVar1 | 0x300;
  }
  else if ((unaff_EBX & 0x30000) == 0x10000) {
    uVar1 = uVar1 | 0x200;
  }
  if ((unaff_EBX & 0x40000) != 0) {
    uVar1 = uVar1 | 0x1000;
  }
  return uVar1;
}



// Library Function - Single Match
//  __control87
// 
// Library: Visual Studio 2003 Release


uint __control87(uint param_1,uint param_2)

{
  uint uVar1;
  
  uVar1 = __abstract_cw();
  __hw_cw();
  return uVar1 & ~param_2 | param_1 & param_2;
}



// Library Function - Single Match
//  __controlfp
// 
// Library: Visual Studio 2003 Release


void __controlfp(undefined4 param_1,uint param_2)

{
  __control87(param_1,param_2 & 0xfff7ffff);
  return;
}



// Library Function - Single Match
//  __snprintf
// 
// Library: Visual Studio 2003 Release


undefined4 __snprintf(undefined1 *param_1,int param_2,undefined4 param_3)

{
  undefined4 uVar1;
  undefined1 *local_24;
  int local_20;
  undefined1 *local_1c;
  undefined4 local_18;
  
  local_20 = param_2;
  local_18 = 0x42;
  local_1c = param_1;
  local_24 = param_1;
  uVar1 = FUN_00168fed(&local_24,param_3,&stack0x00000010);
  if (param_1 != (undefined1 *)0x0) {
    local_20 = local_20 + -1;
    if (local_20 < 0) {
      __flsbuf(0,&local_24);
    }
    else {
      *local_24 = 0;
    }
  }
  return uVar1;
}



// Library Function - Single Match
//  _strncmp
// 
// Libraries: Visual Studio 2003 Debug, Visual Studio 2003 Release


int __vsnprintf(char *buffer,size_t count,char *format,va_list argptr)

{
  int iVar1;
  char *local_24;
  size_t local_20;
  char *local_1c;
  undefined4 local_18;
  
  local_20 = count;
  local_18 = 0x42;
  local_1c = buffer;
  local_24 = buffer;
  iVar1 = FUN_00168fed(&local_24,format,argptr);
  if (buffer != (char *)0x0) {
    local_20 = local_20 - 1;
    if ((int)local_20 < 0) {
      __flsbuf(0,&local_24);
    }
    else {
      *local_24 = '\0';
    }
  }
  return iVar1;
}



// Library Function - Single Match
//  _strncat
// 
// Library: Visual Studio


void _shortsort(undefined1 *param_1,int param_2,code *param_3)

{
  undefined1 uVar1;
  undefined1 *puVar2;
  undefined1 *in_EAX;
  int iVar3;
  undefined1 *puVar4;
  
  for (; puVar2 = param_1, puVar4 = param_1, param_1 < in_EAX; in_EAX = in_EAX + -param_2) {
    while (puVar4 = puVar4 + param_2, puVar4 <= in_EAX) {
      iVar3 = (*param_3)(puVar4,puVar2);
      if (0 < iVar3) {
        puVar2 = puVar4;
      }
    }
    if ((puVar2 != in_EAX) && (param_2 != 0)) {
      puVar4 = in_EAX;
      iVar3 = param_2;
      do {
        uVar1 = puVar4[(int)puVar2 - (int)in_EAX];
        puVar4[(int)puVar2 - (int)in_EAX] = *puVar4;
        *puVar4 = uVar1;
        puVar4 = puVar4 + 1;
        iVar3 = iVar3 + -1;
      } while (iVar3 != 0);
    }
  }
  return;
}



// Library Function - Single Match
//  _qsort
// 
// Library: Visual Studio 2003 Release


void __SEH_epilog(void)

{
  undefined4 *unaff_EBP;
  undefined4 *unaff_FS_OFFSET;
  undefined4 unaff_retaddr;
  
  *unaff_FS_OFFSET = unaff_EBP[-4];
  *unaff_EBP = unaff_retaddr;
  return;
}



// Library Function - Single Match
//  __seh_longjmp_unwind@4
// 
// Libraries: Visual Studio 1998 Debug, Visual Studio 1998 Release, Visual Studio 2003 Debug, Visual
// Studio 2003 Release


void __seh_longjmp_unwind_4(int param_1)

{
  __local_unwind2(*(undefined4 *)(param_1 + 0x18),*(undefined4 *)(param_1 + 0x1c));
  return;
}



// Library Function - Single Match
//  _wcscmp
// 
// Library: Visual Studio 2003 Release


int __stricmp(undefined1 *param_1,undefined1 *param_2)

{
  int iVar1;
  int iVar2;
  
  if (DAT_004dd2ac == 0) {
    iVar1 = ___ascii_stricmp();
    return iVar1;
  }
  do {
    iVar1 = FUN_0016b050(*param_1);
    param_1 = param_1 + 1;
    iVar2 = FUN_0016b050(*param_2);
    param_2 = param_2 + 1;
    if (iVar1 == 0) break;
  } while (iVar1 == iVar2);
  return iVar1 - iVar2;
}



// Library Function - Single Match
//  __allmul
// 
// Library: Visual Studio


longlong __allmul(uint param_1,int param_2,uint param_3,int param_4)

{
  if (param_4 == 0 && param_2 == 0) {
    return (ulonglong)param_1 * (ulonglong)param_3;
  }
  return CONCAT44((int)((ulonglong)param_1 * (ulonglong)param_3 >> 0x20) +
                  param_2 * param_3 + param_1 * param_4,
                  (int)((ulonglong)param_1 * (ulonglong)param_3));
}



// WARNING: Unable to track spacebase fully for stack


void __global_unwind2(PVOID param_1)

{
  RtlUnwind(param_1,(PVOID)0x167038,(PEXCEPTION_RECORD)0x0,(PVOID)0x0);
  return;
}



// Library Function - Single Match
//  __local_unwind2
// 
// Library: Visual Studio 2003 Release


void __local_unwind2(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  undefined4 *unaff_FS_OFFSET;
  undefined4 uStack_1c;
  undefined1 *puStack_18;
  undefined4 local_14;
  int iStack_10;
  
  iStack_10 = param_1;
  puStack_18 = &LAB_00167040;
  uStack_1c = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &uStack_1c;
  while( true ) {
    iVar1 = *(int *)(param_1 + 8);
    iVar2 = *(int *)(param_1 + 0xc);
    if ((iVar2 == -1) || (iVar2 == param_2)) break;
    local_14 = *(undefined4 *)(iVar1 + iVar2 * 0xc);
    *(undefined4 *)(param_1 + 0xc) = local_14;
    if (*(int *)(iVar1 + 4 + iVar2 * 0xc) == 0) {
      FUN_001670f6(0x101);
      (**(code **)(iVar1 + 8 + iVar2 * 0xc))();
    }
  }
  *unaff_FS_OFFSET = uStack_1c;
  return;
}



// Library Function - Single Match
//  __abnormal_termination
// 
// Library: Visual Studio


undefined4 __abnormal_termination(void)

{
  int iVar1;
  undefined4 uVar2;
  int *unaff_FS_OFFSET;
  
  uVar2 = 0;
  iVar1 = *unaff_FS_OFFSET;
  if ((*(undefined1 **)(iVar1 + 4) == &LAB_00167040) &&
     (*(int *)(iVar1 + 8) == *(int *)(*(int *)(iVar1 + 0xc) + 0xc))) {
    uVar2 = 1;
  }
  return uVar2;
}



// Library Function - Single Match
//  __NLG_Notify1
// 
// Libraries: Visual Studio 2017 Debug, Visual Studio 2017 Release, Visual Studio 2019 Debug, Visual
// Studio 2019 Release


void __fastcall __NLG_Notify1(undefined4 param_1)

{
  undefined4 in_EAX;
  undefined4 unaff_EBP;
  
  DAT_00337a78 = param_1;
  DAT_00337a74 = in_EAX;
  DAT_00337a7c = unaff_EBP;
  return;
}




ulonglong __fastcall __aullshr(byte param_1,uint param_2)

{
  uint in_EAX;
  
  if (0x3f < param_1) {
    return 0;
  }
  if (param_1 < 0x20) {
    return CONCAT44(param_2 >> (param_1 & 0x1f),
                    in_EAX >> (param_1 & 0x1f) | param_2 << 0x20 - (param_1 & 0x1f));
  }
  return (ulonglong)(param_2 >> (param_1 & 0x1f));
}



// Library Function - Single Match
//  __aullrem
// 
// Library: Visual Studio


undefined8 __aullrem(uint param_1,uint param_2,uint param_3,uint param_4)

{
  ulonglong uVar1;
  longlong lVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  int iVar6;
  int iVar7;
  uint uVar8;
  uint uVar9;
  uint uVar10;
  bool bVar11;
  
  uVar4 = param_1;
  uVar9 = param_4;
  uVar10 = param_2;
  uVar3 = param_3;
  if (param_4 == 0) {
    iVar6 = (int)(((ulonglong)param_2 % (ulonglong)param_3 << 0x20 | (ulonglong)param_1) %
                 (ulonglong)param_3);
    iVar7 = 0;
  }
  else {
    do {
      uVar5 = uVar9 >> 1;
      uVar3 = (uint)(CONCAT14((uVar9 & 1) != 0,uVar3) >> 1);
      uVar8 = uVar10 >> 1;
      uVar4 = (uint)(CONCAT14((uVar10 & 1) != 0,uVar4) >> 1);
      uVar9 = uVar5;
      uVar10 = uVar8;
    } while (uVar5 != 0);
    uVar1 = CONCAT44(uVar8,uVar4) / (ulonglong)uVar3;
    uVar3 = (int)uVar1 * param_4;
    lVar2 = (uVar1 & 0xffffffff) * (ulonglong)param_3;
    uVar9 = (uint)((ulonglong)lVar2 >> 0x20);
    uVar4 = (uint)lVar2;
    uVar10 = uVar9 + uVar3;
    if (((CARRY4(uVar9,uVar3)) || (param_2 < uVar10)) || ((param_2 <= uVar10 && (param_1 < uVar4))))
    {
      bVar11 = uVar4 < param_3;
      uVar4 = uVar4 - param_3;
      uVar10 = (uVar10 - param_4) - (uint)bVar11;
    }
    iVar6 = -(uVar4 - param_1);
    iVar7 = -(uint)(uVar4 - param_1 != 0) - ((uVar10 - param_2) - (uint)(uVar4 < param_1));
  }
  return CONCAT44(iVar7,iVar6);
}



// Library Function - Multiple Matches With Different Base Names
//  ?swprintf@@YAHPA_WIPB_WZZ
//  __snwprintf
// 
// Library: Visual Studio 2003 Release

undefined4

FID_conflict__swprintf__YAHPA_WIPB_WZZ(undefined1 *param_1,int param_2,undefined4 param_3)

{
  undefined4 uVar1;
  undefined1 *local_24;
  int local_20;
  undefined1 *local_1c;
  undefined4 local_18;
  
  local_1c = param_1;
  local_24 = param_1;
  local_20 = param_2 * 2;
  local_18 = 0x42;
  uVar1 = FUN_0016993d(&local_24,param_3,&stack0x00000010);
  local_20 = local_20 + -1;
  if (local_20 < 0) {
    __flsbuf(0,&local_24);
  }
  else {
    *local_24 = 0;
    local_24 = local_24 + 1;
  }
  local_20 = local_20 + -1;
  if (local_20 < 0) {
    __flsbuf(0,&local_24);
  }
  else {
    *local_24 = 0;
  }
  return uVar1;
}



// Library Function - Single Match
//  __strnicmp
// 
// Library: Visual Studio 2003 Release


int __strnicmp(undefined1 *param_1,undefined1 *param_2,int param_3)

{
  int iVar1;
  int iVar2;
  
  if (param_3 == 0) {
    return 0;
  }
  if (DAT_004dd2ac == 0) {
    iVar1 = ___ascii_strnicmp();
    return iVar1;
  }
  do {
    iVar1 = FUN_0016b050(*param_1);
    param_1 = param_1 + 1;
    iVar2 = FUN_0016b050(*param_2);
    param_2 = param_2 + 1;
    param_3 = param_3 + -1;
    if ((param_3 == 0) || (iVar1 == 0)) break;
  } while (iVar1 == iVar2);
  return iVar1 - iVar2;
}



// Library Function - Single Match
//  __alldiv
// 
// Library: Visual Studio


undefined8 __alldiv(uint param_1,uint param_2,uint param_3,uint param_4)

{
  ulonglong uVar1;
  longlong lVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  bool bVar10;
  char cVar11;
  uint uVar9;
  
  cVar11 = (int)param_2 < 0;
  if ((bool)cVar11) {
    bVar10 = param_1 != 0;
    param_1 = -param_1;
    param_2 = -(uint)bVar10 - param_2;
  }
  if ((int)param_4 < 0) {
    cVar11 = cVar11 + '\x01';
    bVar10 = param_3 != 0;
    param_3 = -param_3;
    param_4 = -(uint)bVar10 - param_4;
  }
  uVar7 = param_1;
  uVar3 = param_3;
  uVar5 = param_2;
  uVar9 = param_4;
  if (param_4 == 0) {
    uVar3 = param_2 / param_3;
    iVar4 = (int)(((ulonglong)param_2 % (ulonglong)param_3 << 0x20 | (ulonglong)param_1) /
                 (ulonglong)param_3);
  }
  else {
    do {
      uVar8 = uVar9 >> 1;
      uVar3 = (uint)(CONCAT14((uVar9 & 1) != 0,uVar3) >> 1);
      uVar6 = uVar5 >> 1;
      uVar7 = (uint)(CONCAT14((uVar5 & 1) != 0,uVar7) >> 1);
      uVar5 = uVar6;
      uVar9 = uVar8;
    } while (uVar8 != 0);
    uVar1 = CONCAT44(uVar6,uVar7) / (ulonglong)uVar3;
    iVar4 = (int)uVar1;
    lVar2 = (ulonglong)param_3 * (uVar1 & 0xffffffff);
    uVar3 = (uint)((ulonglong)lVar2 >> 0x20);
    uVar7 = uVar3 + iVar4 * param_4;
    if (((CARRY4(uVar3,iVar4 * param_4)) || (param_2 < uVar7)) ||
       ((param_2 <= uVar7 && (param_1 < (uint)lVar2)))) {
      iVar4 = iVar4 + -1;
    }
    uVar3 = 0;
  }
  if (cVar11 == '\x01') {
    bVar10 = iVar4 != 0;
    iVar4 = -iVar4;
    uVar3 = -(uint)bVar10 - uVar3;
  }
  return CONCAT44(uVar3,iVar4);
}



// Library Function - Single Match
//  __aulldiv
// 
// Library: Visual Studio


undefined8 __aulldiv(uint param_1,uint param_2,uint param_3,uint param_4)

{
  ulonglong uVar1;
  longlong lVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  uint uVar7;
  uint uVar8;
  uint uVar9;
  uint uVar6;
  
  uVar9 = param_1;
  uVar6 = param_4;
  uVar7 = param_2;
  uVar3 = param_3;
  if (param_4 == 0) {
    uVar3 = param_2 / param_3;
    iVar4 = (int)(((ulonglong)param_2 % (ulonglong)param_3 << 0x20 | (ulonglong)param_1) /
                 (ulonglong)param_3);
  }
  else {
    do {
      uVar5 = uVar6 >> 1;
      uVar3 = (uint)(CONCAT14((uVar6 & 1) != 0,uVar3) >> 1);
      uVar8 = uVar7 >> 1;
      uVar9 = (uint)(CONCAT14((uVar7 & 1) != 0,uVar9) >> 1);
      uVar6 = uVar5;
      uVar7 = uVar8;
    } while (uVar5 != 0);
    uVar1 = CONCAT44(uVar8,uVar9) / (ulonglong)uVar3;
    iVar4 = (int)uVar1;
    lVar2 = (ulonglong)param_3 * (uVar1 & 0xffffffff);
    uVar3 = (uint)((ulonglong)lVar2 >> 0x20);
    uVar9 = uVar3 + iVar4 * param_4;
    if (((CARRY4(uVar3,iVar4 * param_4)) || (param_2 < uVar9)) ||
       ((param_2 <= uVar9 && (param_1 < (uint)lVar2)))) {
      iVar4 = iVar4 + -1;
    }
    uVar3 = 0;
  }
  return CONCAT44(uVar3,iVar4);
}




int __fpclass(int param_1,uint param_2)

{
  int iVar1;
  int iStack_8;
  
  if ((param_2._2_2_ & 0x7ff0) == 0x7ff0) {
    iVar1 = __sptype();
    if (iVar1 == 1) {
      return 0x200;
    }
    if (iVar1 == 2) {
      iStack_8 = 4;
    }
    else {
      if (iVar1 != 3) {
        return 1;
      }
      iStack_8 = 2;
    }
    return iStack_8;
  }
  if (((param_2 & 0x7ff00000) == 0) && (((param_2 & 0xfffff) != 0 || (param_1 != 0)))) {
    return (-(uint)((param_2 & 0x80000000) != 0) & 0xffffff90) + 0x80;
  }
  if ((double)CONCAT26(param_2._2_2_,CONCAT24((undefined2)param_2,param_1)) == 0.0) {
    return (-(uint)((param_2 & 0x80000000) != 0) & 0xffffffe0) + 0x40;
  }
  return (-(uint)((param_2 & 0x80000000) != 0) & 0xffffff08) + 0x100;
}




void __JumpToContinuation__YGXPAXPAUEHRegistrationNode___Z(code *UNRECOVERED_JUMPTABLE)

{
  undefined4 *unaff_FS_OFFSET;
  
  *unaff_FS_OFFSET = *(undefined4 *)*unaff_FS_OFFSET;
                    // WARNING: Could not recover jumptable at 0x001675f4. Too many branches
                    // WARNING: Treating indirect jump as call
  (*UNRECOVERED_JUMPTABLE)();
  return;
}



// Library Function - Multiple Matches With Different Base Names
//  ?_CallMemberFunction1@@YGXPAX00@Z
//  ?_CallMemberFunction2@@YGXPAX00H@Z
// 
// Library: Visual Studio 2003 Release


void FID_conflict___CallMemberFunction1__YGXPAX00_Z(undefined4 param_1,code *UNRECOVERED_JUMPTABLE)

{
  LOCK();
  UNLOCK();
                    // WARNING: Could not recover jumptable at 0x00167600. Too many branches
                    // WARNING: Treating indirect jump as call
  (*UNRECOVERED_JUMPTABLE)();
  return;
}



// Library Function - Single Match
//  ?_UnwindNestedFrames@@YGXPAUEHRegistrationNode@@PAUEHExceptionRecord@@@Z
// 
// Library: Visual Studio 2003 Release

void __UnwindNestedFrames__YGXPAUEHRegistrationNode__PAUEHExceptionRecord___Z
               (PVOID param_1,PEXCEPTION_RECORD param_2)

{
  undefined4 *puVar1;
  undefined4 *unaff_FS_OFFSET;
  
  puVar1 = (undefined4 *)*unaff_FS_OFFSET;
  RtlUnwind(param_1,(PVOID)0x16762b,param_2,(PVOID)0x0);
  param_2->ExceptionFlags = param_2->ExceptionFlags & 0xfffffffd;
  *puVar1 = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = puVar1;
  return;
}



// Library Function - Single Match
//  ___CxxFrameHandler
// 
// Library: Visual Studio 2003 Release

undefined4

___CxxFrameHandler(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 uVar1;
  
  uVar1 = ___InternalCxxFrameHandler(param_1,param_2,param_3,param_4);
  return uVar1;
}



// Library Function - Single Match
//  ?_CallSETranslator@@YAHPAUEHExceptionRecord@@PAUEHRegistrationNode@@PAX2PBU_s_FuncInfo@@H1@Z
// 
// Library: Visual Studio 2003 Release

undefined4
__CallSETranslator__YAHPAUEHExceptionRecord__PAUEHRegistrationNode__PAX2PBU_s_FuncInfo__H1_Z
          (undefined4 *param_1,undefined4 *param_2,undefined4 param_3,undefined4 param_4,
          undefined4 param_5,undefined4 param_6,undefined4 param_7)

{
  int iVar1;
  int *unaff_FS_OFFSET;
  undefined4 local_38;
  undefined4 *local_34;
  undefined4 local_30;
  undefined4 *local_2c;
  code *local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 *local_1c;
  undefined4 local_18;
  undefined4 local_14;
  undefined1 *local_10;
  undefined1 *local_c;
  int local_8;
  
  local_c = &stack0xfffffffc;
  local_10 = &stack0xffffffc4;
  if (param_1 == (undefined4 *)0x123) {
    *param_2 = 0x167760;
    local_38 = 1;
  }
  else {
    local_28 = 
    _TranslatorGuardHandler__YA_AW4_EXCEPTION_DISPOSITION__PAUEHExceptionRecord__PAUTranslatorGuardRN__PAX2_Z
    ;
    local_24 = DAT_00337aac;
    local_20 = param_5;
    local_1c = param_2;
    local_18 = param_6;
    local_14 = param_7;
    local_8 = 0;
    local_2c = (undefined4 *)*unaff_FS_OFFSET;
    *unaff_FS_OFFSET = (int)&local_2c;
    local_34 = param_1;
    local_30 = param_3;
    iVar1 = FUN_0016ae40(*param_1,&local_34);
    (**(code **)(iVar1 + 0x70))();
    local_38 = 0;
    if (local_8 == 0) {
      *unaff_FS_OFFSET = (int)local_2c;
    }
    else {
      *local_2c = *(undefined4 *)*unaff_FS_OFFSET;
      *unaff_FS_OFFSET = (int)local_2c;
    }
  }
  return local_38;
}



// Library Function - Single Match
//  
// ?TranslatorGuardHandler@@YA?AW4_EXCEPTION_DISPOSITION@@PAUEHExceptionRecord@@PAUTranslatorGuardRN@@PAX2@Z
// 
// Library: Visual Studio 2003 Release

undefined4
_TranslatorGuardHandler__YA_AW4_EXCEPTION_DISPOSITION__PAUEHExceptionRecord__PAUTranslatorGuardRN__PAX2_Z
          (int param_1,int param_2,undefined4 param_3)

{
  undefined4 uVar1;
  code *local_8;
  
  if (*(int *)(param_2 + 8) == DAT_00337aac) {
    if ((*(uint *)(param_1 + 4) & 0x66) == 0) {
      ___InternalCxxFrameHandler
                (param_1,*(undefined4 *)(param_2 + 0x10),param_3,0,*(undefined4 *)(param_2 + 0xc),
                 *(undefined4 *)(param_2 + 0x14),*(undefined4 *)(param_2 + 0x18),1);
      if (*(int *)(param_2 + 0x24) == 0) {
        __UnwindNestedFrames__YGXPAUEHRegistrationNode__PAUEHExceptionRecord___Z(param_2,param_1);
      }
      __CallSETranslator__YAHPAUEHExceptionRecord__PAUEHRegistrationNode__PAX2PBU_s_FuncInfo__H1_Z
                (0x123,&local_8,0,0,0,0,0);
                    // WARNING: Could not recover jumptable at 0x00167836. Too many branches
                    // WARNING: Treating indirect jump as call
      uVar1 = (*local_8)();
      return uVar1;
    }
    *(undefined4 *)(param_2 + 0x24) = 1;
  }
  else {
    *(uint *)(param_1 + 4) = *(uint *)(param_1 + 4) | 8;
  }
  return 1;
}



// Library Function - Single Match
//  ?_GetRangeOfTrysToCheck@@YAPBU_s_TryBlockMapEntry@@PBU_s_FuncInfo@@HHPAI1@Z
// 
// Library: Visual Studio 2003 Release

int __GetRangeOfTrysToCheck__YAPBU_s_TryBlockMapEntry__PBU_s_FuncInfo__HHPAI1_Z
              (int param_1,int param_2,int param_3,uint *param_4,uint *param_5)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  
  uVar6 = *(uint *)(param_1 + 0xc);
  iVar2 = *(int *)(param_1 + 0x10);
  uVar5 = uVar6;
  uVar4 = uVar6;
  while (uVar3 = uVar5, -1 < param_2) {
    if (uVar6 == 0xffffffff) {
      __inconsistency__YAXXZ();
    }
    uVar6 = uVar6 - 1;
    iVar1 = iVar2 + uVar6 * 0x14;
    if (((*(int *)(iVar1 + 4) < param_3) && (param_3 <= *(int *)(iVar1 + 8))) ||
       (uVar5 = uVar3, uVar6 == 0xffffffff)) {
      param_2 = param_2 + -1;
      uVar5 = uVar6;
      uVar4 = uVar3;
    }
  }
  uVar6 = uVar6 + 1;
  *param_4 = uVar6;
  *param_5 = uVar4;
  if ((*(uint *)(param_1 + 0xc) < uVar4) || (uVar4 < uVar6)) {
    __inconsistency__YAXXZ();
  }
  return iVar2 + uVar6 * 0x14;
}




void __FindAndUnlinkFrame__YAXPAUFrameInfo___Z(int param_1)

{
  int iVar1;
  int iVar2;
  
  iVar1 = FUN_0016ae40();
  if (param_1 == *(int *)(iVar1 + 0x84)) {
    iVar1 = FUN_0016ae40();
    *(undefined4 *)(iVar1 + 0x84) = *(undefined4 *)(param_1 + 4);
    return;
  }
  iVar1 = FUN_0016ae40();
  iVar1 = *(int *)(iVar1 + 0x84);
  do {
    iVar2 = iVar1;
    if (*(int *)(iVar2 + 4) == 0) {
      __inconsistency__YAXXZ();
      return;
    }
    iVar1 = *(int *)(iVar2 + 4);
  } while (param_1 != *(int *)(iVar2 + 4));
  *(undefined4 *)(iVar2 + 4) = *(undefined4 *)(param_1 + 4);
  return;
}



// Library Function - Single Match
//  ?_CallCatchBlock2@@YAPAXPAUEHRegistrationNode@@PBU_s_FuncInfo@@PAXHK@Z
// 
// Library: Visual Studio 2003 Release

undefined4
__CallCatchBlock2__YAPAXPAUEHRegistrationNode__PBU_s_FuncInfo__PAXHK_Z
          (undefined4 param_1,undefined4 param_2,undefined4 param_3,int param_4,undefined4 param_5)

{
  undefined4 uVar1;
  int *unaff_FS_OFFSET;
  int local_1c;
  undefined1 *local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  int local_8;
  
  local_14 = DAT_00337aac;
  local_10 = param_2;
  local_8 = param_4 + 1;
  local_18 = &LAB_0016768a;
  local_c = param_1;
  local_1c = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = (int)&local_1c;
  uVar1 = __CallSettingFrame_12(param_3,param_1,param_5);
  *unaff_FS_OFFSET = local_1c;
  return uVar1;
}




void __onexit_lk(void)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  undefined4 unaff_EDI;
  
  uVar1 = FUN_0016c37d(DAT_0054dd6c);
  if (uVar1 < (uint)((int)DAT_0054dd68 + (4 - DAT_0054dd6c))) {
    uVar3 = 0x800;
    if (uVar1 < 0x800) {
      uVar3 = uVar1;
    }
    iVar2 = FUN_0016c290(DAT_0054dd6c,uVar3 + uVar1);
    if (iVar2 == 0) {
      iVar2 = FUN_0016c290(DAT_0054dd6c,uVar1 + 0x10);
      if (iVar2 == 0) {
        return;
      }
    }
    DAT_0054dd68 = (undefined4 *)(iVar2 + ((int)DAT_0054dd68 - DAT_0054dd6c >> 2) * 4);
    DAT_0054dd6c = iVar2;
  }
  *DAT_0054dd68 = unaff_EDI;
  DAT_0054dd68 = DAT_0054dd68 + 1;
  return;
}



// Library Function - Single Match
//  ___onexitinit
// 
// Library: Visual Studio 2003 Release


undefined4 ___onexitinit(void)

{
  DAT_0054dd6c = _malloc(0x80);
  if (DAT_0054dd6c == (undefined4 *)0x0) {
    return 0x18;
  }
  *DAT_0054dd6c = 0;
  DAT_0054dd68 = DAT_0054dd6c;
  return 0;
}



// WARNING: Function: __SEH_prolog replaced with injection: SEH_prolog
// WARNING: Function: __SEH_epilog replaced with injection: EH_epilog3
// Library Function - Single Match
//  __onexit
// 
// Library: Visual Studio 2003 Release


undefined4 __onexit(void)

{
  undefined4 uVar1;
  
  FUN_00169786();
  uVar1 = __onexit_lk();
  FUN_00167ada();
  return uVar1;
}




void __thiscall _xtoa(char *param_1,uint param_2,int param_3)

{
  ulonglong uVar1;
  char *pcVar2;
  uint in_EAX;
  char *pcVar3;
  char cVar4;
  
  pcVar2 = param_1;
  if (param_3 != 0) {
    *param_1 = '-';
    param_1 = param_1 + 1;
    in_EAX = -in_EAX;
    pcVar2 = param_1;
  }
  do {
    pcVar3 = pcVar2;
    uVar1 = (ulonglong)in_EAX;
    in_EAX = in_EAX / param_2;
    cVar4 = (char)(uVar1 % (ulonglong)param_2);
    if ((uint)(uVar1 % (ulonglong)param_2) < 10) {
      cVar4 = cVar4 + '0';
    }
    else {
      cVar4 = cVar4 + 'W';
    }
    *pcVar3 = cVar4;
    pcVar2 = pcVar3 + 1;
  } while (in_EAX != 0);
  pcVar3[1] = '\0';
  do {
    cVar4 = *pcVar3;
    *pcVar3 = *param_1;
    pcVar3 = pcVar3 + -1;
    *param_1 = cVar4;
    param_1 = param_1 + 1;
  } while (param_1 < pcVar3);
  return;
}



// Library Function - Single Match
//  __itoa
// 
// Library: Visual Studio 2003 Release


undefined4 __itoa(int param_1,undefined4 param_2,int param_3)

{
  undefined4 uVar1;
  
  if ((param_3 == 10) && (param_1 < 0)) {
    uVar1 = 1;
    param_3 = 10;
  }
  else {
    uVar1 = 0;
  }
  _xtoa(param_3,uVar1);
  return param_2;
}



// WARNING: Function: __SEH_prolog replaced with injection: SEH_prolog
// WARNING: Function: __SEH_epilog replaced with injection: EH_epilog3
// Library Function - Single Match
//  ??_L@YGXPAXIHP6EX0@Z1@Z
// 
// Library: Visual Studio 2003 Release


void ___L_YGXPAXIHP6EX0_Z1_Z(undefined4 param_1,undefined4 param_2,int param_3,code *param_4)

{
  undefined4 local_20;
  
  for (local_20 = 0; local_20 < param_3; local_20 = local_20 + 1) {
    (*param_4)();
  }
  FUN_00167bde();
  return;
}




void ___M_YGXPAXIHP6EX0_Z_Z(undefined4 param_1,undefined4 param_2,int param_3,code *param_4)

{
  while( true ) {
    param_3 = param_3 + -1;
    if (param_3 < 0) break;
    (*param_4)();
  }
  FUN_00167c9c();
  return;
}




int __nh_malloc(uint param_1,int param_2)

{
  int iVar1;
  
  if (param_1 < 0xffffffe1) {
    do {
      iVar1 = FUN_00167ec9(param_1);
      if (iVar1 != 0) {
        return iVar1;
      }
      if (param_2 == 0) {
        return 0;
      }
      iVar1 = __callnewh(param_1);
    } while (iVar1 != 0);
  }
  return 0;
}



// Library Function - Single Match
//  _malloc
// 
// Library: Visual Studio 2003 Release


_bsearch(void *__key,void *__base,size_t __nmemb,size_t __size,__compar_fn_t __compar)

{
  uint uVar1;
  void *pvVar2;
  int iVar3;
  uint uVar4;
  void *pvVar5;
  
  pvVar5 = (void *)((__nmemb - 1) * __size + (int)__base);
  if (__base <= pvVar5) {
    do {
      uVar4 = __nmemb >> 1;
      if (uVar4 == 0) {
        if (__nmemb == 0) {
          return (void *)0x0;
        }
        iVar3 = (*__compar)(__key,__base);
        return (void *)(~-(uint)(iVar3 != 0) & (uint)__base);
      }
      uVar1 = uVar4;
      if ((__nmemb & 1) == 0) {
        uVar1 = uVar4 - 1;
      }
      pvVar2 = (void *)(uVar1 * __size + (int)__base);
      iVar3 = (*__compar)(__key,pvVar2);
      if (iVar3 == 0) {
        return pvVar2;
      }
      if (iVar3 < 0) {
        pvVar5 = (void *)((int)pvVar2 - __size);
        if ((__nmemb & 1) == 0) {
          uVar4 = uVar4 - 1;
        }
      }
      else {
        __base = (void *)((int)pvVar2 + __size);
      }
      __nmemb = uVar4;
    } while (__base <= pvVar5);
  }
  return (void *)0x0;
}




undefined4 __mtinitlocks(void)

{
  int iVar1;
  int iVar2;
  undefined *puVar3;
  
  iVar2 = 0;
  puVar3 = &DAT_004dd0d8;
  do {
    if ((&DAT_00337ab4)[iVar2 * 2] == 1) {
      (&DAT_00337ab0)[iVar2 * 2] = puVar3;
      puVar3 = puVar3 + 0x1c;
      iVar1 = FUN_0016d9f8((&DAT_00337ab0)[iVar2 * 2],4000);
      if (iVar1 == 0) {
        (&DAT_00337ab0)[iVar2 * 2] = 0;
        return 0;
      }
    }
    iVar2 = iVar2 + 1;
  } while (iVar2 < 0x24);
  return 1;
}




undefined4 __mtinitlocknum(int param_1)

{
  int *piVar1;
  void *pvVar2;
  undefined4 *puVar3;
  int iVar4;
  undefined1 local_14 [8];
  undefined4 uStack_c;
  undefined *local_8;
  
  local_8 = &DAT_00209190;
  uStack_c = 0x16812d;
  piVar1 = &DAT_00337ab0 + param_1 * 2;
  if (*piVar1 == 0) {
    pvVar2 = _malloc(0x1c);
    if (pvVar2 == (void *)0x0) {
      puVar3 = (undefined4 *)FUN_00168af5();
      *puVar3 = 0xc;
      return 0;
    }
    FUN_001681c1(10);
    local_8 = (undefined *)0x0;
    if (*piVar1 == 0) {
      iVar4 = FUN_0016d9f8(pvVar2,4000);
      if (iVar4 == 0) {
        FUN_00167f2e(pvVar2);
        puVar3 = (undefined4 *)FUN_00168af5();
        *puVar3 = 0xc;
        __local_unwind2(local_14,0xffffffff);
        return 0;
      }
      *piVar1 = (int)pvVar2;
    }
    else {
      FUN_00167f2e(pvVar2);
    }
    local_8 = (undefined *)0xffffffff;
    FUN_001681b8();
  }
  return 1;
}




undefined4 __sptype(int param_1,uint param_2)

{
  undefined4 uStack_8;
  
  if (param_2 == 0x7ff00000) {
    if (param_1 == 0) {
      return 1;
    }
  }
  else if ((param_2 == 0xfff00000) && (param_1 == 0)) {
    return 2;
  }
  if ((param_2._2_2_ & 0x7ff8) == 0x7ff8) {
    uStack_8 = 3;
  }
  else {
    if (((param_2._2_2_ & 0x7ff8) != 0x7ff0) || (((param_2 & 0x7ffff) == 0 && (param_1 == 0)))) {
      return 0;
    }
    uStack_8 = 4;
  }
  return uStack_8;
}




int __ctrlfp(void)

{
  short in_FPUControlWord;
  
  return (int)in_FPUControlWord;
}



// WARNING: Globals starting with '_' overlap smaller symbols at the same address


uint __filbuf(undefined4 *param_1)

{
  byte bVar1;
  uint uVar2;
  int iVar3;
  undefined *puVar4;
  
  uVar2 = param_1[3];
  if (((uVar2 & 0x83) != 0) && ((uVar2 & 0x40) == 0)) {
    if ((uVar2 & 2) == 0) {
      param_1[3] = uVar2 | 1;
      if ((uVar2 & 0x10c) == 0) {
        __getbuf(param_1);
      }
      else {
        *param_1 = param_1[2];
      }
      iVar3 = __read(param_1[4],param_1[2],param_1[6]);
      param_1[1] = iVar3;
      if ((iVar3 != 0) && (iVar3 != -1)) {
        if ((param_1[3] & 0x82) == 0) {
          uVar2 = param_1[4];
          if (uVar2 == 0xffffffff) {
            puVar4 = &DAT_00338250;
          }
          else {
            puVar4 = (undefined *)((&DAT_0054dc60)[(int)uVar2 >> 5] + (uVar2 & 0x1f) * 0x28);
          }
          if ((puVar4[4] & 0x82) == 0x82) {
            param_1[3] = param_1[3] | 0x2000;
          }
        }
        if (((param_1[6] == 0x200) && ((param_1[3] & 8) != 0)) && ((param_1[3] & 0x400) == 0)) {
          param_1[6] = 0x1000;
        }
        param_1[1] = iVar3 + -1;
        bVar1 = *(byte *)*param_1;
        *param_1 = (byte *)*param_1 + 1;
        return (uint)bVar1;
      }
      param_1[3] = param_1[3] | (-(uint)(iVar3 != 0) & 0x10) + 0x10;
      param_1[1] = 0;
    }
    else {
      param_1[3] = uVar2 | 0x20;
    }
  }
  return 0xffffffff;
}




void __dosmaperr(uint param_1)

{
  int iVar1;
  uint uVar2;
  
  iVar1 = FUN_0016ae40();
  *(uint *)(iVar1 + 0xc) = param_1;
  uVar2 = 0;
  do {
    if (param_1 == (&DAT_00337f78)[uVar2 * 2]) {
      iVar1 = FUN_0016ae40();
      *(undefined4 *)(iVar1 + 8) = *(undefined4 *)(uVar2 * 8 + 0x337f7c);
      return;
    }
    uVar2 = uVar2 + 1;
  } while (uVar2 < 0x2d);
  if ((0x12 < param_1) && (param_1 < 0x25)) {
    iVar1 = FUN_0016ae40();
    *(undefined4 *)(iVar1 + 8) = 0xd;
    return;
  }
  if ((0xbb < param_1) && (param_1 < 0xcb)) {
    iVar1 = FUN_0016ae40();
    *(undefined4 *)(iVar1 + 8) = 8;
    return;
  }
  iVar1 = FUN_0016ae40();
  *(undefined4 *)(iVar1 + 8) = 0x16;
  return;
}




undefined4 __close(uint param_1)

{
  undefined4 *puVar1;
  int iVar2;
  undefined4 local_20;
  
  if (param_1 < DAT_0054dc40) {
    iVar2 = (param_1 & 0x1f) * 0x28;
    if ((*(byte *)((&DAT_0054dc60)[(int)param_1 >> 5] + 4 + iVar2) & 1) != 0) {
      __lock_fhandle(param_1);
      if ((*(byte *)((&DAT_0054dc60)[(int)param_1 >> 5] + 4 + iVar2) & 1) == 0) {
        puVar1 = (undefined4 *)FUN_00168af5();
        *puVar1 = 9;
        local_20 = 0xffffffff;
      }
      else {
        local_20 = FUN_00168b96(param_1);
      }
      FUN_00168c8e();
      return local_20;
    }
  }
  puVar1 = (undefined4 *)FUN_00168af5();
  *puVar1 = 9;
  puVar1 = (undefined4 *)FUN_00168afe();
  *puVar1 = 0;
  return 0xffffffff;
}




void __freebuf(undefined4 *param_1)

{
  if (((param_1[3] & 0x83) != 0) && ((param_1[3] & 8) != 0)) {
    FUN_00167f2e(param_1[2]);
    *(ushort *)(param_1 + 3) = *(ushort *)(param_1 + 3) & 0xfbf7;
    *param_1 = 0;
    param_1[2] = 0;
    param_1[1] = 0;
  }
  return;
}



// Library Function - Single Match
//  __flush
// 
// Library: Visual Studio 2003 Release


undefined4 __flush(int *param_1)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  
  uVar2 = 0;
  if ((((byte)param_1[3] & 3) == 2) && ((param_1[3] & 0x108U) != 0)) {
    iVar3 = *param_1 - param_1[2];
    if (0 < iVar3) {
      iVar1 = __write(param_1[4],param_1[2],iVar3);
      if (iVar1 == iVar3) {
        if ((char)param_1[3] < '\0') {
          param_1[3] = param_1[3] & 0xfffffffd;
        }
      }
      else {
        param_1[3] = param_1[3] | 0x20;
        uVar2 = 0xffffffff;
      }
    }
  }
  param_1[1] = 0;
  *param_1 = param_1[2];
  return uVar2;
}



// Library Function - Single Match
//  __fflush_lk
// 
// Library: Visual Studio 2003 Release


int __fflush_lk(int param_1)

{
  int iVar1;
  
  iVar1 = __flush(param_1);
  if (iVar1 != 0) {
    return -1;
  }
  if ((*(byte *)(param_1 + 0xd) & 0x40) != 0) {
    iVar1 = FUN_0016dea6(*(undefined4 *)(param_1 + 0x10));
    return -(uint)(iVar1 != 0);
  }
  return 0;
}



// WARNING: Function: __SEH_prolog replaced with injection: SEH_prolog
// WARNING: Function: __SEH_epilog replaced with injection: EH_epilog3
// Library Function - Single Match
//  _flsall
// 
// Library: Visual Studio 2003 Release


int _flsall(int param_1)

{
  int iVar1;
  int iVar2;
  undefined4 local_28;
  undefined4 local_20;
  
  local_20 = 0;
  local_28 = 0;
  FUN_001681c1(1);
  for (iVar2 = 0; iVar2 < DAT_0054dd78; iVar2 = iVar2 + 1) {
    iVar1 = *(int *)(DAT_0054dd74 + iVar2 * 4);
    if ((iVar1 != 0) && ((*(byte *)(iVar1 + 0xc) & 0x83) != 0)) {
      __lock_file2(iVar2,iVar1);
      iVar1 = *(int *)(DAT_0054dd74 + iVar2 * 4);
      if ((*(uint *)(iVar1 + 0xc) & 0x83) != 0) {
        if (param_1 == 1) {
          iVar1 = __fflush_lk(iVar1);
          if (iVar1 != -1) {
            local_20 = local_20 + 1;
          }
        }
        else if ((param_1 == 0) && ((*(uint *)(iVar1 + 0xc) & 2) != 0)) {
          iVar1 = __fflush_lk(iVar1);
          if (iVar1 == -1) {
            local_28 = -1;
          }
        }
      }
      FUN_00168e08();
    }
  }
  FUN_00168e34();
  if (param_1 != 1) {
    local_20 = local_28;
  }
  return local_20;
}




void __flushall(void)

{
  _flsall(1);
  return;
}



// Library Function - Single Match
//  __flsbuf
// 
// Library: Visual Studio 2003 Release


uint __flsbuf(uint param_1,int *param_2)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  int *piVar4;
  int iVar5;
  undefined *puVar6;
  
  piVar4 = param_2;
  uVar1 = param_2[3];
  uVar2 = param_2[4];
  if (((uVar1 & 0x82) == 0) || ((uVar1 & 0x40) != 0)) {
LAB_00168f52:
    param_2[3] = uVar1 | 0x20;
  }
  else {
    if ((uVar1 & 1) != 0) {
      param_2[1] = 0;
      if ((uVar1 & 0x10) == 0) goto LAB_00168f52;
      *param_2 = param_2[2];
      param_2[3] = uVar1 & 0xfffffffe;
    }
    uVar1 = param_2[3];
    param_2[1] = 0;
    param_2 = (int *)0x0;
    piVar4[3] = uVar1 & 0xffffffef | 2;
    if (((uVar1 & 0x10c) == 0) &&
       (((piVar4 != (int *)&DAT_00337d18 && (piVar4 != (int *)&DAT_00337d38)) ||
        (iVar5 = __isatty(uVar2), iVar5 == 0)))) {
      __getbuf(piVar4);
    }
    if ((*(ushort *)(piVar4 + 3) & 0x108) == 0) {
      iVar5 = 1;
      param_2 = (int *)__write(uVar2,&param_1,1);
    }
    else {
      iVar3 = piVar4[2];
      iVar5 = *piVar4;
      *piVar4 = iVar3 + 1;
      iVar5 = iVar5 - iVar3;
      piVar4[1] = piVar4[6] + -1;
      if (iVar5 < 1) {
        if (uVar2 == 0xffffffff) {
          puVar6 = &DAT_00338250;
        }
        else {
          puVar6 = (undefined *)((&DAT_0054dc60)[(int)uVar2 >> 5] + (uVar2 & 0x1f) * 0x28);
        }
        if ((puVar6[4] & 0x20) != 0) {
          __lseek(uVar2,0,2);
        }
      }
      else {
        param_2 = (int *)__write(uVar2,iVar3,iVar5);
      }
      *(undefined1 *)piVar4[2] = (undefined1)param_1;
    }
    if (param_2 == (int *)iVar5) {
      return param_1 & 0xff;
    }
    piVar4[3] = piVar4[3] | 0x20;
  }
  return 0xffffffff;
}



// Library Function - Single Match
//  _write_char
// 
// Library: Visual Studio 2003 Release


void __fastcall _write_char(int *param_1)

{
  int *piVar1;
  byte in_AL;
  uint uVar2;
  int *unaff_ESI;
  
  if (((*(byte *)(param_1 + 3) & 0x40) == 0) || (param_1[2] != 0)) {
    piVar1 = param_1 + 1;
    *piVar1 = *piVar1 + -1;
    if (*piVar1 < 0) {
      uVar2 = __flsbuf((int)(char)in_AL,param_1);
    }
    else {
      *(byte *)*param_1 = in_AL;
      *param_1 = *param_1 + 1;
      uVar2 = (uint)in_AL;
    }
    if (uVar2 == 0xffffffff) {
      *unaff_ESI = -1;
      return;
    }
  }
  *unaff_ESI = *unaff_ESI + 1;
  return;
}



// Library Function - Single Match
//  _write_multi_char
// 
// Libraries: Visual Studio 2003 Release, Visual Studio 2005 Release, Visual Studio 2008 Release,
// Visual Studio 2010 Release


void _write_multi_char(undefined4 param_1,int param_2)

{
  int *in_EAX;
  
  do {
    if (param_2 < 1) {
      return;
    }
    param_2 = param_2 + -1;
    _write_char();
  } while (*in_EAX != -1);
  return;
}



// Library Function - Single Match
//  _write_string
// 
// Library: Visual Studio 2003 Release


void _write_string(int param_1)

{
  int *in_EAX;
  int unaff_EDI;
  
  if (((*(byte *)(unaff_EDI + 0xc) & 0x40) == 0) || (*(int *)(unaff_EDI + 8) != 0)) {
    do {
      if (param_1 < 1) {
        return;
      }
      param_1 = param_1 + -1;
      _write_char();
    } while (*in_EAX != -1);
  }
  else {
    *in_EAX = *in_EAX + param_1;
  }
  return;
}




void _write_char(undefined4 param_1)

{
  short sVar1;
  int in_EAX;
  int *unaff_ESI;
  
  if (((*(byte *)(in_EAX + 0xc) & 0x40) == 0) || (*(int *)(in_EAX + 8) != 0)) {
    sVar1 = FUN_0016dfb5(param_1);
    if (sVar1 == -1) {
      *unaff_ESI = -1;
      return;
    }
  }
  *unaff_ESI = *unaff_ESI + 1;
  return;
}



// Library Function - Single Match
//  _write_multi_char
// 
// Libraries: Visual Studio 2003 Release, Visual Studio 2005 Release


void _write_multi_char(undefined4 param_1,int param_2)

{
  int *in_EAX;
  
  do {
    if (param_2 < 1) {
      return;
    }
    param_2 = param_2 + -1;
    _write_char(param_1);
  } while (*in_EAX != -1);
  return;
}



// Library Function - Single Match
//  _write_string
// 
// Library: Visual Studio 2003 Release


void __thiscall _write_string(undefined2 *param_1,int param_2)

{
  int *in_EAX;
  int unaff_EDI;
  
  if (((*(byte *)(unaff_EDI + 0xc) & 0x40) == 0) || (*(int *)(unaff_EDI + 8) != 0)) {
    do {
      if (param_2 < 1) {
        return;
      }
      param_2 = param_2 + -1;
      _write_char(*param_1);
      param_1 = param_1 + 1;
    } while (*in_EAX != -1);
  }
  else {
    *in_EAX = *in_EAX + param_2;
  }
  return;
}




uint __hextodec(void)

{
  uint uVar1;
  int iVar2;
  uint unaff_ESI;
  
  if ((unaff_ESI & 0xff00) == 0) {
    if (DAT_00338188 < 2) {
      uVar1 = (byte)PTR_DAT_00338180[(unaff_ESI & 0xff) * 2] & 4;
    }
    else {
      uVar1 = FUN_0016ae1f(unaff_ESI & 0xff,4);
    }
    if (uVar1 != 0) {
      return unaff_ESI & 0xffff;
    }
  }
  iVar2 = FUN_00166bf9();
  uVar1 = unaff_ESI - 0x27;
  if (iVar2 == 0) {
    uVar1 = unaff_ESI - 7;
  }
  return uVar1;
}




uint __whiteout(undefined4 param_1)

{
  uint __wc;
  int iVar1;
  int *unaff_ESI;
  
  do {
    *unaff_ESI = *unaff_ESI + 1;
    __wc = __getwc_lk(param_1);
    iVar1 = _iswspace(__wc);
  } while (iVar1 != 0);
  return __wc & 0xffff;
}



// WARNING: Function: __SEH_prolog replaced with injection: SEH_prolog
// WARNING: Function: __SEH_epilog replaced with injection: EH_epilog3


int ___ascii_stricmp(byte *param_1,byte *param_2)

{
  byte bVar1;
  byte bVar2;
  byte bVar3;
  char cVar4;
  
  bVar3 = 0xff;
  do {
    do {
      cVar4 = '\0';
      if (bVar3 == 0) goto LAB_0016b0d6;
      bVar3 = *param_2;
      param_2 = param_2 + 1;
      bVar2 = *param_1;
      param_1 = param_1 + 1;
    } while (bVar2 == bVar3);
    bVar1 = bVar3 + 0xbf + (-((byte)(bVar3 + 0xbf) < 0x1a) & 0x20U) + 0x41;
    bVar2 = bVar2 + 0xbf;
    bVar3 = bVar2 + (-(bVar2 < 0x1a) & 0x20U) + 0x41;
  } while (bVar3 == bVar1);
  cVar4 = (bVar3 < bVar1) * -2 + '\x01';
LAB_0016b0d6:
  return (int)cVar4;
}



// Library Function - Single Match
//  ___ascii_strnicmp
// 
// Library: Visual Studio 2003 Release


undefined4 ___ascii_strnicmp(byte *param_1,char *param_2,int param_3)

{
  char cVar1;
  byte bVar2;
  ushort uVar3;
  uint uVar4;
  undefined4 uVar5;
  bool bVar6;
  
  uVar5 = 0;
  if (param_3 != 0) {
    do {
      bVar2 = *param_1;
      cVar1 = *param_2;
      uVar3 = CONCAT11(bVar2,cVar1);
      if (bVar2 == 0) break;
      uVar3 = CONCAT11(bVar2,cVar1);
      uVar4 = (uint)uVar3;
      if (cVar1 == '\0') break;
      param_1 = param_1 + 1;
      param_2 = param_2 + 1;
      if ((0x40 < bVar2) && (bVar2 < 0x5b)) {
        uVar4 = (uint)CONCAT11(bVar2 + 0x20,cVar1);
      }
      uVar3 = (ushort)uVar4;
      bVar2 = (byte)uVar4;
      if ((0x40 < bVar2) && (bVar2 < 0x5b)) {
        uVar3 = (ushort)CONCAT31((int3)(uVar4 >> 8),bVar2 + 0x20);
      }
      bVar2 = (byte)(uVar3 >> 8);
      bVar6 = bVar2 < (byte)uVar3;
      if (bVar2 != (byte)uVar3) goto LAB_0016b131;
      param_3 = param_3 + -1;
    } while (param_3 != 0);
    uVar5 = 0;
    bVar2 = (byte)(uVar3 >> 8);
    bVar6 = bVar2 < (byte)uVar3;
    if (bVar2 != (byte)uVar3) {
LAB_0016b131:
      uVar5 = 0xffffffff;
      if (!bVar6) {
        uVar5 = 1;
      }
    }
  }
  return uVar5;
}



// Library Function - Single Match
//  __forcdecpt
// 
// Library: Visual Studio 2003 Release


void __forcdecpt(char *param_1)

{
  char cVar1;
  char cVar2;
  int iVar3;
  uint uVar4;
  
  iVar3 = FUN_0016b050((int)*param_1);
  if (iVar3 != 0x65) {
    do {
      param_1 = param_1 + 1;
      if (DAT_00338188 < 2) {
        uVar4 = (byte)PTR_DAT_00338180[*param_1 * 2] & 4;
      }
      else {
        uVar4 = FUN_0016ae1f((int)*param_1,4);
      }
    } while (uVar4 != 0);
  }
  cVar2 = *param_1;
  *param_1 = DAT_0033818c;
  do {
    param_1 = param_1 + 1;
    cVar1 = *param_1;
    *param_1 = cVar2;
    cVar2 = cVar1;
  } while (*param_1 != '\0');
  return;
}



// Library Function - Single Match
//  __fassign
// 
// Library: Visual Studio 2003 Release


void __fassign(int param_1,int *param_2,undefined4 param_3)

{
  int local_c;
  int local_8;
  
  if (param_1 != 0) {
    FUN_0016e770(&local_c);
    *param_2 = local_c;
    param_2[1] = local_8;
    return;
  }
  FUN_0016e79d(&param_1,param_3);
  *param_2 = param_1;
  return;
}




uint __fastcall __fload_withFB(undefined4 param_1,int param_2)

{
  uint uVar1;
  
  uVar1 = *(uint *)(param_2 + 4) & 0x7ff00000;
  if (uVar1 != 0x7ff00000) {
    return uVar1;
  }
  return *(uint *)(param_2 + 4);
}




void __math_exit(void)

{
  ushort in_FPUStatusWord;
  ushort unaff_retaddr;
  
  if (((unaff_retaddr != 0x27f) && ((unaff_retaddr & 0x20) != 0)) &&
     ((in_FPUStatusWord & 0x20) != 0)) {
    __startOneArgErrorHandling();
    return;
  }
  return;
}




void ___DestructExceptionObject(int param_1)

{
  int iVar1;
  
  if ((param_1 != 0) && (iVar1 = *(int *)(*(int *)(param_1 + 0x1c) + 4), iVar1 != 0)) {
    FID_conflict___CallMemberFunction1__YGXPAX00_Z(*(undefined4 *)(param_1 + 0x18),iVar1);
  }
  return;
}



// Library Function - Single Match
//  ?AdjustPointer@@YAPAXPAXABUPMD@@@Z
// 
// Library: Visual Studio 2003 Release


int __fastcall _AdjustPointer__YAPAXPAXABUPMD___Z(int *param_1)

{
  int in_EAX;
  int iVar1;
  
  iVar1 = *param_1 + in_EAX;
  if (-1 < param_1[1]) {
    iVar1 = iVar1 + *(int *)(*(int *)(param_1[1] + in_EAX) + param_1[2]) + param_1[1];
  }
  return iVar1;
}



// WARNING: Function: __SEH_prolog replaced with injection: SEH_prolog
// WARNING: Function: __SEH_epilog replaced with injection: EH_epilog3

undefined4 __thiscall
FUN_0016baae(undefined4 param_1,int param_2,int param_3,undefined4 param_4,undefined4 param_5,
            undefined4 param_6,undefined4 param_7)

{
  int iVar1;
  undefined1 local_54 [8];
  undefined4 local_4c;
  undefined4 local_48;
  undefined4 local_44;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_24;
  undefined4 uStack_c;
  undefined *local_8;
  
  local_8 = &DAT_00209c10;
  uStack_c = 0x16baba;
  local_4c = 0;
  local_3c = *(undefined4 *)(param_3 + -4);
  local_24 = param_1;
  local_40 = FUN_001678b8(local_54,*(undefined4 *)(param_2 + 0x18));
  iVar1 = FUN_0016ae40();
  local_44 = *(undefined4 *)(iVar1 + 0x78);
  iVar1 = FUN_0016ae40();
  local_48 = *(undefined4 *)(iVar1 + 0x7c);
  iVar1 = FUN_0016ae40();
  *(int *)(iVar1 + 0x78) = param_2;
  iVar1 = FUN_0016ae40();
  *(undefined4 *)(iVar1 + 0x7c) = param_4;
  local_8 = (undefined *)0x1;
  local_24 = __CallCatchBlock2__YAPAXPAUEHRegistrationNode__PBU_s_FuncInfo__PAXHK_Z
                       (param_3,param_5,param_1,param_6,param_7);
  local_8 = (undefined *)0xffffffff;
  FUN_0016bbf1();
  return local_24;
}




void __inconsistency__YAXXZ(void)

{
  if (PTR_FUN_003381e8 != (undefined *)0x0) {
    (*(code *)PTR_FUN_003381e8)();
  }
  FUN_0016c177();
  return;
}



// WARNING: Restarted to delay deadcode elimination for space: stack
// Library Function - Single Match
//  __CallSettingFrame@12
// 
// Library: Visual Studio 2003 Release


void __CallSettingFrame_12(undefined4 param_1,undefined4 param_2,int param_3)

{
  code *pcVar1;
  
  pcVar1 = (code *)__NLG_Notify1(param_3);
  (*pcVar1)();
  if (param_3 == 0x100) {
    param_3 = 2;
  }
  __NLG_Notify1(param_3);
  return;
}




uint __hextodec(void)

{
  uint in_EAX;
  uint uVar1;
  
  if (DAT_00338188 < 2) {
    uVar1 = (byte)PTR_DAT_00338180[in_EAX * 2] & 4;
  }
  else {
    uVar1 = FUN_0016ae1f();
  }
  if (uVar1 == 0) {
    in_EAX = (in_EAX & 0xffffffdf) - 7;
  }
  return in_EAX;
}



// Library Function - Single Match
//  __inc
// 
// Library: Visual Studio 2003 Release


uint __fastcall __inc(undefined4 param_1,undefined4 *param_2)

{
  int *piVar1;
  byte bVar2;
  uint uVar3;
  
  piVar1 = param_2 + 1;
  *piVar1 = *piVar1 + -1;
  if (-1 < *piVar1) {
    bVar2 = *(byte *)*param_2;
    *param_2 = (byte *)*param_2 + 1;
    return (uint)bVar2;
  }
  uVar3 = __filbuf(param_2);
  return uVar3;
}



// WARNING: Function: __SEH_prolog replaced with injection: SEH_prolog
// WARNING: Function: __SEH_epilog replaced with injection: EH_epilog3


undefined8 __aulldvrm(uint param_1,uint param_2,uint param_3,uint param_4)

{
  ulonglong uVar1;
  longlong lVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  uint uVar7;
  uint uVar8;
  uint uVar9;
  uint uVar6;
  
  uVar9 = param_1;
  uVar6 = param_4;
  uVar7 = param_2;
  uVar3 = param_3;
  if (param_4 == 0) {
    uVar3 = param_2 / param_3;
    iVar4 = (int)(((ulonglong)param_2 % (ulonglong)param_3 << 0x20 | (ulonglong)param_1) /
                 (ulonglong)param_3);
  }
  else {
    do {
      uVar5 = uVar6 >> 1;
      uVar3 = (uint)(CONCAT14((uVar6 & 1) != 0,uVar3) >> 1);
      uVar8 = uVar7 >> 1;
      uVar9 = (uint)(CONCAT14((uVar7 & 1) != 0,uVar9) >> 1);
      uVar6 = uVar5;
      uVar7 = uVar8;
    } while (uVar5 != 0);
    uVar1 = CONCAT44(uVar8,uVar9) / (ulonglong)uVar3;
    iVar4 = (int)uVar1;
    lVar2 = (ulonglong)param_3 * (uVar1 & 0xffffffff);
    uVar3 = (uint)((ulonglong)lVar2 >> 0x20);
    uVar9 = uVar3 + iVar4 * param_4;
    if (((CARRY4(uVar3,iVar4 * param_4)) || (param_2 < uVar9)) ||
       ((param_2 <= uVar9 && (param_1 < (uint)lVar2)))) {
      iVar4 = iVar4 + -1;
    }
    uVar3 = 0;
  }
  return CONCAT44(uVar3,iVar4);
}




undefined4 __callnewh(undefined4 param_1)

{
  int iVar1;
  
  if (DAT_004dd2c8 != (code *)0x0) {
    iVar1 = (*DAT_004dd2c8)(param_1);
    if (iVar1 != 0) {
      return 1;
    }
  }
  return 0;
}




undefined4 __lseek(uint param_1,undefined4 param_2,undefined4 param_3)

{
  undefined4 *puVar1;
  int iVar2;
  undefined4 local_20;
  
  if (param_1 < DAT_0054dc40) {
    iVar2 = (param_1 & 0x1f) * 0x28;
    if ((*(byte *)((&DAT_0054dc60)[(int)param_1 >> 5] + 4 + iVar2) & 1) != 0) {
      __lock_fhandle(param_1);
      if ((*(byte *)((&DAT_0054dc60)[(int)param_1 >> 5] + 4 + iVar2) & 1) == 0) {
        puVar1 = (undefined4 *)FUN_00168af5();
        *puVar1 = 9;
        puVar1 = (undefined4 *)FUN_00168afe();
        *puVar1 = 0;
        local_20 = 0xffffffff;
      }
      else {
        local_20 = FUN_0016d466(param_1,param_2,param_3);
      }
      FUN_0016d55f();
      return local_20;
    }
  }
  puVar1 = (undefined4 *)FUN_00168af5();
  *puVar1 = 9;
  puVar1 = (undefined4 *)FUN_00168afe();
  *puVar1 = 0;
  return 0xffffffff;
}




undefined4 __read(uint param_1,undefined4 param_2,undefined4 param_3)

{
  undefined4 *puVar1;
  int iVar2;
  undefined4 local_20;
  
  if (param_1 < DAT_0054dc40) {
    iVar2 = (param_1 & 0x1f) * 0x28;
    if ((*(byte *)((&DAT_0054dc60)[(int)param_1 >> 5] + 4 + iVar2) & 1) != 0) {
      __lock_fhandle(param_1);
      if ((*(byte *)((&DAT_0054dc60)[(int)param_1 >> 5] + 4 + iVar2) & 1) == 0) {
        puVar1 = (undefined4 *)FUN_00168af5();
        *puVar1 = 9;
        puVar1 = (undefined4 *)FUN_00168afe();
        *puVar1 = 0;
        local_20 = 0xffffffff;
      }
      else {
        local_20 = FUN_0016d583(param_1,param_2,param_3);
      }
      FUN_0016d7e1();
      return local_20;
    }
  }
  puVar1 = (undefined4 *)FUN_00168af5();
  *puVar1 = 9;
  puVar1 = (undefined4 *)FUN_00168afe();
  *puVar1 = 0;
  return 0xffffffff;
}




void __getbuf(undefined4 *param_1)

{
  void *pvVar1;
  
  _DAT_004dd260 = _DAT_004dd260 + 1;
  pvVar1 = _malloc(0x1000);
  param_1[2] = pvVar1;
  if (pvVar1 == (void *)0x0) {
    param_1[3] = param_1[3] | 4;
    param_1[2] = param_1 + 5;
    param_1[6] = 2;
  }
  else {
    param_1[3] = param_1[3] | 8;
    param_1[6] = 0x1000;
  }
  param_1[1] = 0;
  *param_1 = param_1[2];
  return;
}




undefined4 __get_osfhandle(uint param_1)

{
  undefined4 *puVar1;
  
  if ((param_1 < DAT_0054dc40) &&
     (puVar1 = (undefined4 *)((&DAT_0054dc60)[(int)param_1 >> 5] + (param_1 & 0x1f) * 0x28),
     (*(byte *)(puVar1 + 1) & 1) != 0)) {
    return *puVar1;
  }
  puVar1 = (undefined4 *)FUN_00168af5();
  *puVar1 = 9;
  puVar1 = (undefined4 *)FUN_00168afe();
  *puVar1 = 0;
  return 0xffffffff;
}



// WARNING: Function: __SEH_prolog replaced with injection: SEH_prolog
// WARNING: Function: __SEH_epilog replaced with injection: EH_epilog3
// Library Function - Single Match
//  __lock_fhandle
// 
// Library: Visual Studio 2003 Release


undefined4 __lock_fhandle(uint param_1)

{
  int iVar1;
  int iVar2;
  undefined1 local_14 [8];
  undefined4 uStack_c;
  undefined *local_8;
  
  local_8 = &DAT_00209e98;
  uStack_c = 0x16dbba;
  iVar1 = (&DAT_0054dc60)[(int)param_1 >> 5] + (param_1 & 0x1f) * 0x28;
  if (*(int *)(iVar1 + 8) == 0) {
    FUN_001681c1(10);
    local_8 = (undefined *)0x0;
    if (*(int *)(iVar1 + 8) == 0) {
      iVar2 = FUN_0016d9f8(iVar1 + 0xc,4000);
      if (iVar2 == 0) {
        __local_unwind2(local_14,0xffffffff);
        return 0;
      }
      *(int *)(iVar1 + 8) = *(int *)(iVar1 + 8) + 1;
    }
    local_8 = (undefined *)0xffffffff;
    FUN_0016dc45();
  }
  RtlEnterCriticalSection
            ((PRTL_CRITICAL_SECTION)
             ((&DAT_0054dc60)[(int)param_1 >> 5] + 0xc + (param_1 & 0x1f) * 0x28));
  return 1;
}




undefined4 __write(uint param_1,undefined4 param_2,undefined4 param_3)

{
  undefined4 *puVar1;
  int iVar2;
  undefined4 local_20;
  
  if (param_1 < DAT_0054dc40) {
    iVar2 = (param_1 & 0x1f) * 0x28;
    if ((*(byte *)((&DAT_0054dc60)[(int)param_1 >> 5] + 4 + iVar2) & 1) != 0) {
      __lock_fhandle(param_1);
      if ((*(byte *)((&DAT_0054dc60)[(int)param_1 >> 5] + 4 + iVar2) & 1) == 0) {
        puVar1 = (undefined4 *)FUN_00168af5();
        *puVar1 = 9;
        puVar1 = (undefined4 *)FUN_00168afe();
        *puVar1 = 0;
        local_20 = 0xffffffff;
      }
      else {
        local_20 = FUN_0016dc70(param_1,param_2,param_3);
      }
      FUN_0016de82();
      return local_20;
    }
  }
  puVar1 = (undefined4 *)FUN_00168af5();
  *puVar1 = 9;
  puVar1 = (undefined4 *)FUN_00168afe();
  *puVar1 = 0;
  return 0xffffffff;
}




byte __isatty(uint param_1)

{
  if (DAT_0054dc40 <= param_1) {
    return 0;
  }
  return *(byte *)((&DAT_0054dc60)[(int)param_1 >> 5] + 4 + (param_1 & 0x1f) * 0x28) & 0x40;
}




undefined4 __ZeroTail(int param_1,int param_2)

{
  uint uVar1;
  int iVar2;
  
  iVar2 = param_2 / 0x20;
  uVar1 = *(uint *)(param_1 + iVar2 * 4) & ~(-1 << (0x1fU - (char)(param_2 % 0x20) & 0x1f));
  while( true ) {
    if (uVar1 != 0) {
      return 0;
    }
    iVar2 = iVar2 + 1;
    if (2 < iVar2) break;
    uVar1 = *(uint *)(param_1 + iVar2 * 4);
  }
  return 1;
}



// Library Function - Single Match
//  __IncMan
// 
// Library: Visual Studio 2003 Release


void __IncMan(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  undefined4 *puVar3;
  
  puVar3 = (undefined4 *)(param_1 + (param_2 / 0x20) * 4);
  iVar1 = ___addl(*puVar3,1 << (0x1fU - (char)(param_2 % 0x20) & 0x1f),puVar3);
  iVar2 = param_2 / 0x20 + -1;
  if (-1 < iVar2) {
    puVar3 = (undefined4 *)(param_1 + iVar2 * 4);
    do {
      if (iVar1 == 0) {
        return;
      }
      iVar1 = ___addl(*puVar3,1,puVar3);
      iVar2 = iVar2 + -1;
      puVar3 = puVar3 + -1;
    } while (-1 < iVar2);
  }
  return;
}



// Library Function - Single Match
//  __RoundMan
// 
// Library: Visual Studio 2003 Release


undefined4 __RoundMan(int param_1,int param_2)

{
  uint *puVar1;
  int iVar2;
  int iVar3;
  byte bVar4;
  undefined4 *puVar5;
  undefined4 local_8;
  
  local_8 = 0;
  iVar2 = param_2 / 0x20;
  bVar4 = 0x1f - (char)(param_2 % 0x20);
  if (((*(uint *)(param_1 + iVar2 * 4) & 1 << (bVar4 & 0x1f)) != 0) &&
     (iVar3 = __ZeroTail(param_1,param_2), iVar3 == 0)) {
    local_8 = __IncMan(param_1,param_2 + -1);
  }
  puVar1 = (uint *)(param_1 + iVar2 * 4);
  *puVar1 = *puVar1 & -1 << (bVar4 & 0x1f);
  iVar2 = iVar2 + 1;
  if (iVar2 < 3) {
    puVar5 = (undefined4 *)(param_1 + iVar2 * 4);
    for (iVar3 = 3 - iVar2; iVar3 != 0; iVar3 = iVar3 + -1) {
      *puVar5 = 0;
      puVar5 = puVar5 + 1;
    }
  }
  return local_8;
}



// Library Function - Single Match
//  __CopyMan
// 
// Library: Visual Studio 2003 Release


void __CopyMan(int param_1,undefined4 *param_2)

{
  int iVar1;
  
  iVar1 = 3;
  param_1 = param_1 - (int)param_2;
  do {
    *(undefined4 *)(param_1 + (int)param_2) = *param_2;
    param_2 = param_2 + 1;
    iVar1 = iVar1 + -1;
  } while (iVar1 != 0);
  return;
}



// Library Function - Single Match
//  __IsZeroMan
// 
// Library: Visual Studio 2003 Release


undefined4 __IsZeroMan(int param_1)

{
  int iVar1;
  
  iVar1 = 0;
  do {
    if (*(int *)(param_1 + iVar1 * 4) != 0) {
      return 0;
    }
    iVar1 = iVar1 + 1;
  } while (iVar1 < 3);
  return 1;
}



// Library Function - Single Match
//  __ShrMan
// 
// Library: Visual Studio 2003 Release


void __ShrMan(int param_1,int param_2)

{
  uint uVar1;
  int iVar2;
  byte bVar3;
  undefined4 *puVar4;
  uint local_8;
  
  bVar3 = (byte)(param_2 % 0x20);
  iVar2 = 0;
  local_8 = 0;
  do {
    uVar1 = *(uint *)(param_1 + iVar2 * 4);
    *(uint *)(param_1 + iVar2 * 4) = uVar1 >> (bVar3 & 0x1f) | local_8;
    local_8 = (uVar1 & ~(-1 << (bVar3 & 0x1f))) << (0x20 - bVar3 & 0x1f);
    iVar2 = iVar2 + 1;
  } while (iVar2 < 3);
  iVar2 = 2;
  puVar4 = (undefined4 *)(param_1 + (2 - param_2 / 0x20) * 4);
  do {
    if (iVar2 < param_2 / 0x20) {
      *(undefined4 *)(param_1 + iVar2 * 4) = 0;
    }
    else {
      *(undefined4 *)(param_1 + iVar2 * 4) = *puVar4;
    }
    iVar2 = iVar2 + -1;
    puVar4 = puVar4 + -1;
  } while (-1 < iVar2);
  return;
}



// Library Function - Single Match
//  __ld12cvt
// 
// Library: Visual Studio 2003 Release


undefined4 __ld12cvt(ushort *param_1,uint *param_2,int *param_3)

{
  ushort uVar1;
  int iVar2;
  undefined4 uVar3;
  uint uVar4;
  int iVar5;
  undefined1 local_1c [12];
  uint local_10;
  uint local_c;
  int local_8;
  
  uVar1 = param_1[5];
  local_10 = *(uint *)(param_1 + 3);
  local_c = *(uint *)(param_1 + 1);
  local_8 = (uint)*param_1 << 0x10;
  uVar4 = uVar1 & 0x7fff;
  iVar5 = uVar4 - 0x3fff;
  if (iVar5 == -0x3fff) {
    iVar5 = 0;
    iVar2 = __IsZeroMan();
    if (iVar2 != 0) {
LAB_0016e704:
      uVar3 = 0;
      goto LAB_0016e706;
    }
    local_10 = 0;
    local_c = 0;
  }
  else {
    __CopyMan(local_1c,&local_10);
    iVar2 = __RoundMan(&local_10,param_3[2]);
    if (iVar2 != 0) {
      iVar5 = uVar4 - 0x3ffe;
    }
    iVar2 = param_3[1];
    if (iVar5 < iVar2 - param_3[2]) {
      local_10 = 0;
      local_c = 0;
    }
    else {
      if (iVar2 < iVar5) {
        if (*param_3 <= iVar5) {
          local_c = 0;
          local_8 = 0;
          local_10 = 0x80000000;
          __ShrMan(&local_10,param_3[3]);
          iVar5 = param_3[5] + *param_3;
          uVar3 = 1;
          goto LAB_0016e706;
        }
        local_10 = local_10 & 0x7fffffff;
        iVar5 = param_3[5] + iVar5;
        __ShrMan(&local_10,param_3[3]);
        goto LAB_0016e704;
      }
      __CopyMan(&local_10,local_1c);
      __ShrMan(&local_10,iVar2 - iVar5);
      __RoundMan(&local_10,param_3[2]);
      __ShrMan(&local_10,param_3[3] + 1);
    }
  }
  iVar5 = 0;
  uVar3 = 2;
LAB_0016e706:
  local_10 = iVar5 << (0x1fU - (char)param_3[3] & 0x1f) |
             -(uint)((uVar1 & 0x8000) != 0) & 0x80000000 | local_10;
  if (param_3[4] == 0x40) {
    param_2[1] = local_10;
    *param_2 = local_c;
  }
  else if (param_3[4] == 0x20) {
    *param_2 = local_10;
  }
  return uVar3;
}



// Library Function - Multiple Matches With Different Base Names
//  __ld12tod
//  __ld12tof
// 
// Library: Visual Studio 2003 Release


void FID_conflict___ld12tod(undefined4 param_1,undefined4 param_2)

{
  __ld12cvt(param_1,param_2,&DAT_00338308);
  return;
}



// Library Function - Multiple Matches With Different Base Names
//  __ld12tod
//  __ld12tof
// 
// Library: Visual Studio 2003 Release


void FID_conflict___ld12tod(undefined4 param_1,undefined4 param_2)

{
  __ld12cvt(param_1,param_2,&DAT_00338320);
  return;
}




void ___dtold(uint *param_1,uint *param_2)

{
  ushort uVar1;
  uint uVar2;
  ushort uVar3;
  ushort uVar4;
  uint local_8;
  
  uVar1 = *(ushort *)((int)param_2 + 6);
  local_8 = 0x80000000;
  uVar3 = uVar1 >> 4;
  uVar4 = uVar3 & 0x7ff;
  uVar2 = *param_2;
  if ((uVar3 & 0x7ff) == 0) {
    if (((param_2[1] & 0xfffff) == 0) && (uVar2 == 0)) {
      param_1[1] = 0;
      *param_1 = 0;
      *(undefined2 *)(param_1 + 2) = 0;
      return;
    }
    uVar4 = uVar4 + 0x3c01;
    local_8 = 0;
  }
  else if (uVar4 == 0x7ff) {
    uVar4 = 0x7fff;
  }
  else {
    uVar4 = uVar4 + 0x3c00;
  }
  param_1[1] = uVar2 >> 0x15 | (param_2[1] & 0xfffff) << 0xb | local_8;
  *param_1 = uVar2 << 0xb;
  while (local_8 == 0) {
    uVar2 = param_1[1];
    uVar4 = uVar4 - 1;
    param_1[1] = uVar2 << 1 | *param_1 >> 0x1f;
    *param_1 = *param_1 * 2;
    local_8 = uVar2 << 1 & 0x80000000;
  }
  *(ushort *)(param_1 + 2) = uVar1 & 0x8000 | uVar4;
  return;
}




uint __ungetc_lk(uint param_1,int *param_2)

{
  uint uVar1;
  char *pcVar2;
  
  if (param_1 != 0xffffffff) {
    uVar1 = param_2[3];
    if (((uVar1 & 1) != 0) || (((char)uVar1 < '\0' && ((uVar1 & 2) == 0)))) {
      if (param_2[2] == 0) {
        __getbuf(param_2);
      }
      if (*param_2 == param_2[2]) {
        if (param_2[1] != 0) {
          return 0xffffffff;
        }
        *param_2 = *param_2 + 1;
      }
      *param_2 = *param_2 + -1;
      pcVar2 = (char *)*param_2;
      if ((*(byte *)(param_2 + 3) & 0x40) == 0) {
        *pcVar2 = (char)param_1;
      }
      else if (*pcVar2 != (char)param_1) {
        *param_2 = (int)(pcVar2 + 1);
        return 0xffffffff;
      }
      param_2[1] = param_2[1] + 1;
      param_2[3] = param_2[3] & 0xffffffefU | 1;
      return param_1 & 0xff;
    }
  }
  return 0xffffffff;
}



// WARNING: Function: __SEH_prolog replaced with injection: SEH_prolog
// WARNING: Function: __SEH_epilog replaced with injection: EH_epilog3
// Library Function - Single Match
//  _ungetc
// 
// Library: Visual Studio 2003 Release


undefined2 __flswbuf(undefined2 param_1,int *param_2)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  int *piVar4;
  int iVar5;
  undefined *puVar6;
  
  piVar4 = param_2;
  uVar1 = param_2[3];
  uVar2 = param_2[4];
  if (((uVar1 & 0x82) == 0) || ((uVar1 & 0x40) != 0)) {
LAB_0016f40a:
    param_2[3] = uVar1 | 0x20;
  }
  else {
    if ((uVar1 & 1) != 0) {
      param_2[1] = 0;
      if ((uVar1 & 0x10) == 0) goto LAB_0016f40a;
      *param_2 = param_2[2];
      param_2[3] = uVar1 & 0xfffffffe;
    }
    uVar1 = param_2[3];
    param_2[3] = uVar1 & 0xffffffef | 2;
    param_2[1] = 0;
    param_2 = (int *)0x0;
    if (((uVar1 & 0x10c) == 0) &&
       (((piVar4 != (int *)&DAT_00337d18 && (piVar4 != (int *)&DAT_00337d38)) ||
        (iVar5 = __isatty(uVar2), iVar5 == 0)))) {
      __getbuf(piVar4);
    }
    if ((*(ushort *)(piVar4 + 3) & 0x108) == 0) {
      iVar5 = 2;
      param_2 = (int *)CONCAT22(param_2._2_2_,param_1);
      param_2 = (int *)__write(uVar2,&param_2,2);
    }
    else {
      iVar3 = piVar4[2];
      iVar5 = *piVar4;
      *piVar4 = iVar3 + 2;
      iVar5 = iVar5 - iVar3;
      piVar4[1] = piVar4[6] + -2;
      if (iVar5 < 1) {
        if (uVar2 == 0xffffffff) {
          puVar6 = &DAT_00338250;
        }
        else {
          puVar6 = (undefined *)((&DAT_0054dc60)[(int)uVar2 >> 5] + (uVar2 & 0x1f) * 0x28);
        }
        if ((puVar6[4] & 0x20) != 0) {
          __lseek(uVar2,0,2);
        }
      }
      else {
        param_2 = (int *)__write(uVar2,iVar3,iVar5);
      }
      *(undefined2 *)piVar4[2] = param_1;
    }
    if (param_2 == (int *)iVar5) {
      return param_1;
    }
    piVar4[3] = piVar4[3] | 0x20;
  }
  return 0xffff;
}



// Library Function - Single Match
//  __filwbuf
// 
// Library: Visual Studio 2003 Release


undefined2 __filwbuf(undefined4 *param_1)

{
  undefined2 uVar1;
  uint uVar2;
  int iVar3;
  undefined *puVar4;
  
  uVar2 = param_1[3];
  if (((uVar2 & 0x83) != 0) && ((uVar2 & 0x40) == 0)) {
    if ((uVar2 & 2) == 0) {
      param_1[3] = uVar2 | 1;
      if ((uVar2 & 0x10c) == 0) {
        __getbuf(param_1);
      }
      else {
        *param_1 = param_1[2];
      }
      iVar3 = __read(param_1[4],param_1[2],param_1[6]);
      param_1[1] = iVar3;
      if (((iVar3 != 0) && (iVar3 != 1)) && (iVar3 != -1)) {
        if ((param_1[3] & 0x82) == 0) {
          uVar2 = param_1[4];
          if (uVar2 == 0xffffffff) {
            puVar4 = &DAT_00338250;
          }
          else {
            puVar4 = (undefined *)((&DAT_0054dc60)[(int)uVar2 >> 5] + (uVar2 & 0x1f) * 0x28);
          }
          if ((puVar4[4] & 0x82) == 0x82) {
            param_1[3] = param_1[3] | 0x2000;
          }
        }
        if (((param_1[6] == 0x200) && ((param_1[3] & 8) != 0)) && ((param_1[3] & 0x400) == 0)) {
          param_1[6] = 0x1000;
        }
        param_1[1] = iVar3 + -2;
        uVar1 = *(undefined2 *)*param_1;
        *param_1 = (undefined2 *)*param_1 + 1;
        return uVar1;
      }
      param_1[3] = param_1[3] | (-(uint)(iVar3 != 0) & 0x10) + 0x10;
      param_1[1] = 0;
    }
    else {
      param_1[3] = uVar2 | 0x20;
    }
  }
  return 0xffff;
}



// Library Function - Single Match
//  ___addl
// 
// Library: Visual Studio 2003 Release


undefined4 ___addl(uint param_1,uint param_2,uint *param_3)

{
  uint uVar1;
  undefined4 uVar2;
  
  uVar1 = param_1 + param_2;
  uVar2 = 0;
  if ((uVar1 < param_1) || (uVar1 < param_2)) {
    uVar2 = 1;
  }
  *param_3 = uVar1;
  return uVar2;
}



// Library Function - Single Match
//  ___add_12
// 
// Library: Visual Studio 2003 Release


void ___add_12(undefined4 *param_1,undefined4 *param_2)

{
  int iVar1;
  
  iVar1 = ___addl(*param_1,*param_2,param_1);
  if (iVar1 != 0) {
    iVar1 = ___addl(param_1[1],1,param_1 + 1);
    if (iVar1 != 0) {
      param_1[2] = param_1[2] + 1;
    }
  }
  iVar1 = ___addl(param_1[1],param_2[1],param_1 + 1);
  if (iVar1 != 0) {
    param_1[2] = param_1[2] + 1;
  }
  ___addl(param_1[2],param_2[2],param_1 + 2);
  return;
}



// Library Function - Single Match
//  ___shl_12
// 
// Library: Visual Studio 2003 Release


void ___shl_12(uint *param_1)

{
  uint uVar1;
  uint uVar2;
  
  uVar1 = *param_1;
  uVar2 = param_1[1];
  *param_1 = uVar1 * 2;
  param_1[1] = uVar2 * 2 | uVar1 >> 0x1f;
  param_1[2] = param_1[2] << 1 | uVar2 >> 0x1f;
  return;
}



// Library Function - Single Match
//  ___shr_12
// 
// Libraries: Visual Studio 2003 Release, Visual Studio 2005 Release


void ___shr_12(uint *param_1)

{
  uint uVar1;
  
  uVar1 = param_1[1];
  param_1[1] = uVar1 >> 1 | param_1[2] << 0x1f;
  param_1[2] = param_1[2] >> 1;
  *param_1 = *param_1 >> 1 | uVar1 << 0x1f;
  return;
}




void RtlUnwind(PVOID TargetFrame,PVOID TargetIp,PEXCEPTION_RECORD ExceptionRecord,PVOID ReturnValue)

{
                    // WARNING: Could not recover jumptable at 0x0017024a. Too many branches
                    // WARNING: Treating indirect jump as call
  RtlUnwind(TargetFrame,TargetIp,ExceptionRecord,ReturnValue);
  return;
}



void DirectXShaderConstant::write
               (DirectXShaderConstant *shaderConstant,float c1,float c2,float c3,float c4)

{
  shaderConstant->c1 = c1;
  shaderConstant->c2 = c2;
  shaderConstant->c3 = c3;
  shaderConstant->c4 = c4;
  return;
}



// Library Function - Single Match
//  __allrem
// 
// Library: Visual Studio


undefined8 __allrem(uint param_1,uint param_2,uint param_3,uint param_4)

{
  ulonglong uVar1;
  longlong lVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  uint uVar7;
  uint uVar8;
  uint uVar9;
  uint uVar10;
  uint uVar11;
  bool bVar12;
  bool bVar13;
  
  bVar13 = (int)param_2 < 0;
  if (bVar13) {
    bVar12 = param_1 != 0;
    param_1 = -param_1;
    param_2 = -(uint)bVar12 - param_2;
  }
  uVar11 = (uint)bVar13;
  if ((int)param_4 < 0) {
    bVar13 = param_3 != 0;
    param_3 = -param_3;
    param_4 = -(uint)bVar13 - param_4;
  }
  uVar4 = param_1;
  uVar3 = param_3;
  uVar8 = param_2;
  uVar9 = param_4;
  if (param_4 == 0) {
    iVar5 = (int)(((ulonglong)param_2 % (ulonglong)param_3 << 0x20 | (ulonglong)param_1) %
                 (ulonglong)param_3);
    iVar6 = 0;
    if ((int)(uVar11 - 1) < 0) goto LAB_0017032d;
  }
  else {
    do {
      uVar10 = uVar9 >> 1;
      uVar3 = (uint)(CONCAT14((uVar9 & 1) != 0,uVar3) >> 1);
      uVar7 = uVar8 >> 1;
      uVar4 = (uint)(CONCAT14((uVar8 & 1) != 0,uVar4) >> 1);
      uVar8 = uVar7;
      uVar9 = uVar10;
    } while (uVar10 != 0);
    uVar1 = CONCAT44(uVar7,uVar4) / (ulonglong)uVar3;
    uVar3 = (int)uVar1 * param_4;
    lVar2 = (uVar1 & 0xffffffff) * (ulonglong)param_3;
    uVar8 = (uint)((ulonglong)lVar2 >> 0x20);
    uVar4 = (uint)lVar2;
    uVar9 = uVar8 + uVar3;
    if (((CARRY4(uVar8,uVar3)) || (param_2 < uVar9)) || ((param_2 <= uVar9 && (param_1 < uVar4)))) {
      bVar13 = uVar4 < param_3;
      uVar4 = uVar4 - param_3;
      uVar9 = (uVar9 - param_4) - (uint)bVar13;
    }
    iVar5 = uVar4 - param_1;
    iVar6 = (uVar9 - param_2) - (uint)(uVar4 < param_1);
    if (-1 < (int)(uVar11 - 1)) goto LAB_0017032d;
  }
  bVar13 = iVar5 != 0;
  iVar5 = -iVar5;
  iVar6 = -(uint)bVar13 - iVar6;
LAB_0017032d:
  return CONCAT44(iVar6,iVar5);
}



// Library Function - Single Match
//  __cintrindisp2
// 
// Library: Visual Studio


void __cintrindisp2(void)

{
  __trandisp2();
  FUN_0017052a();
  return;
}



// Library Function - Single Match
//  __cintrindisp1
// 
// Library: Visual Studio


void __cintrindisp1(void)

{
  __trandisp1();
  FUN_0017052a();
  return;
}



// Library Function - Single Match
//  __ctrandisp2
// 
// Libraries: Visual Studio 1998, Visual Studio 2003, Visual Studio 2005, Visual Studio 2008


uint __thiscall AutoClass2__FUN_00176fd0(void *this)

{
  void *pvVar1;
  uint uVar2;
  int iVar3;
  byte bVar4;
  
  pvVar1 = XAPILIB::XMemAlloc(Graphics::DXPushBufferSize,0xbc800000);
  *(void **)((int)this + 0x24) = pvVar1;
  if (pvVar1 == (void *)0x0) {
    return 0x8007000e;
  }
  *(uint *)((int)this + 0x28) = (int)pvVar1 + (Graphics::DXPushBufferSize & 0xfffffffc);
  *(void **)this = pvVar1;
  *(uint *)((int)this + 4) = (int)pvVar1 + ((Graphics::DXPushBufferSize & 0xfffffffc) - 0x204);
  *(undefined4 *)((int)this + 0x2c) = 5;
  **(undefined4 **)((int)this + 0x30) = 3;
  uVar2 = (Graphics::DXPushBufferSize - 1) / Graphics::DXPushBufferSize;
  bVar4 = 0;
  do {
    uVar2 = uVar2 >> 1;
    bVar4 = bVar4 + 1;
  } while (uVar2 != 0);
  iVar3 = 1 << (bVar4 & 0x1f);
  *(int *)((int)this + 0x38) = iVar3 + -1;
  pvVar1 = XAPILIB::XMemAlloc(iVar3 * 8,0x64800000);
  *(void **)((int)this + 0x44) = pvVar1;
  return (pvVar1 != (void *)0x0) - 1 & 0x8007000e;
}




void System__DebugPrint(char *outBuf,char *param_2,char *param_3)

{
  char local_104 [260];
  
  __vsnprintf(local_104,0x104,outBuf,(va_list)&param_2);
  DbgPrint(local_104);
  return;
}




void ___H_YGXPAXIHP6EPAX0_Z_Z(undefined4 param_1,undefined4 param_2,int param_3,code *param_4)

{
  if (-1 < param_3 + -1) {
    do {
      (*param_4)();
      param_3 = param_3 + -1;
    } while (param_3 != 0);
  }
  return;
}




