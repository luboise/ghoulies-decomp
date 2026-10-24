/* animation.c - Animation: keyframes, attack instances, bone affines */
#include "animation.h"

void FUN_0001afa0(AnimEventMapping *mapping,actorBody *body)

{
  actor *av;
  AnimEventMapping *pAVar1;
  KFCParams local_b0;
  
  av = body->actor;
  pAVar1 = FUN_000322a0(mapping,(av->avatar).needsAnimMapping,&local_b0);
  avatar::setKFFromAnimAID
            (av,&local_b0,(int)*(char *)((int)&pAVar1->field7_0x114 + 3),pAVar1->animAID);
  (av->avatar).needsAnimMapping = 0;
  actorBody::sendSyncAnimationMessage(body);
  return;
}




undefined4 GetValueFromLoadedAttackDataResources(AttackDataResource *res,int *param_2)

{
  int i;
  AttackData *pAVar1;
  
  i = 0;
  if (0 < g_numAttackData) {
    pAVar1 = g_attackDataLookup;
    do {
      if (pAVar1->attackDataRes == res) {
        *(int *)(&DAT_004dd554 + i * 0x10) = *(int *)(&DAT_004dd554 + i * 0x10) + 1;
        *param_2 = *(int *)(&DAT_004dd558 + i * 0x10);
        return g_attackDataLookup[i].field1_0x4;
      }
      i = i + 1;
      pAVar1 = pAVar1 + 1;
    } while (i < g_numAttackData);
  }
  return 0;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


ushort * FUN_0001c400(uint param_1,AttackDataListOfAttacks *param_2)

{
  undefined1 *puVar1;
  int iVar2;
  ushort *head;
  int iVar3;
  ushort *tail;
  
  tail = param_2->tail;
  head = param_2->head;
  while( true ) {
    if (tail <= head) {
      if (tail == param_2->end) {
        iVar2 = ((int)tail - (int)param_2->head) / (int)(uint)param_2->valueSize;
        iVar3 = (uint)param_2->capacity + iVar2;
        param_2 = (AttackDataListOfAttacks *)
                  AllocateMoreAStruct_33((uint)param_2->valueSize * iVar3 + 0x10,param_2);
        puVar1 = &param_2->values;
        param_2->tail = (ushort *)(puVar1 + (uint)param_2->valueSize * iVar2);
        param_2->end = (ushort *)(puVar1 + (uint)param_2->valueSize * iVar3);
        param_2->head = (ushort *)puVar1;
      }
      tail = param_2->tail;
      param_2->tail = (ushort *)((uint)param_2->valueSize + (int)tail);
      *tail = (ushort)param_1;
      tail[1] = 1;
      return &param_2->valueSize;
    }
    if (*head == param_1) break;
    head = head + 2;
  }
  head[1] = head[1] + 1;
  return &param_2->valueSize;
}




AttackDataResource::getAttackByStateId(AttackDataResource *param_1,actorBodyStateId param_2)

{
  actorBodyStateId aVar1;
  AttackEntry *pAVar2;
  int index;
  int iVar3;
  int i;
  
  iVar3 = (param_1->attack1).numEntries - 1;
  i = 0;
  if (-1 < iVar3) {
    pAVar2 = (param_1->attack1).entries;
    do {
      index = i + iVar3 >> 1;
      aVar1 = (&pAVar2->id)[index * 0x12];
      if (aVar1 < param_2) {
        i = index + 1;
      }
      else {
        if (aVar1 <= param_2) {
          return (AttackEntry *)(&pAVar2->id + index * 0x12);
        }
        iVar3 = index + -1;
      }
    } while (i <= iVar3);
  }
  return (AttackEntry *)0x0;
}




AttackDataResource::getAttack4ById(AttackDataResource *param_1,actorBodyStateId param_2)

{
  actorBodyStateId aVar1;
  AttackEntry *pAVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  
  iVar4 = (param_1->attacks4).numEntries - 1;
  iVar5 = 0;
  if (-1 < iVar4) {
    pAVar2 = (param_1->weaponAttacks).entries;
    do {
      iVar3 = iVar5 + iVar4 >> 1;
      aVar1 = *(actorBodyStateId *)(iVar3 * 0x2c + (int)pAVar2);
      if (aVar1 < param_2) {
        iVar5 = iVar3 + 1;
      }
      else {
        if (aVar1 <= param_2) {
          return (AttackEntry *)(iVar3 * 0x2c + (int)pAVar2);
        }
        iVar4 = iVar3 + -1;
      }
    } while (iVar5 <= iVar4);
  }
  return (AttackEntry *)0x0;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void KeyframeAllocdValue::initialise(CombinedAnimChannel *allocdValue)

{
  CombinedAnimChannel *pCVar1;
  KfTransform_0x24 pfVar1;
  int iVar2;
  uint i;
  KeyframeAllocdValueData *pfVar3;
  
  i = 0;
  pCVar1 = allocdValue;
  if (allocdValue->numTransforms != 0) {
    do {
      pfVar1 = &pCVar1->boneTransforms[0].scale.z;
      pCVar1->boneTransforms[0].rotQuat.x = 0.0;
      pCVar1->boneTransforms[0].rotQuat.y = 0.0;
      pCVar1->boneTransforms[0].rotQuat.z = 0.0;
      pCVar1->boneTransforms[0].rotQuat.w = 1.0;
      pCVar1->boneTransforms[0].scale.x = 1.0;
      pCVar1->boneTransforms[0].scale.y = 1.0;
                    // scale.z
      (ADJ(pfVar1)->scale).z = 1.0;
      pCVar1->boneTransforms[0].pos.z = 0.0;
      pCVar1->boneTransforms[0].pos.y = 0.0;
      pCVar1->boneTransforms[0].pos.x = 0.0;
      i = i + 1;
                    // += 0x28
      pCVar1 = (CombinedAnimChannel *)pfVar1;
    } while (i < allocdValue->numTransforms);
  }
                    // eax *= 5
  pfVar3 = (KeyframeAllocdValueData *)(allocdValue->boneTransforms + allocdValue->numTransforms);
  for (iVar2 = 0x40; iVar2 != 0; iVar2 = iVar2 + -1) {
    *(undefined4 *)pfVar3 = 0;
    pfVar3 = (KeyframeAllocdValueData *)&pfVar3->field_0x4;
  }
  return;
}




CombinedAnimChannel * FUN_0002d3f0(void)

{
  uint uVar1;
  int iVar2;
  CombinedAnimChannel *allocdValue;
  uint *puVar3;
  int iVar4;
  uint *unaff_EBX;
  
  uVar1 = *unaff_EBX;
  allocdValue = malloc_(uVar1 * 0x28 + 0x104);
  allocdValue->numTransforms = uVar1;
  KeyframeAllocdValue::initialise(allocdValue);
  iVar4 = *unaff_EBX * 0x28 + 0x100;
  puVar3 = unaff_EBX + 1;
  if (iVar4 != 0) {
    iVar2 = 4 - (int)puVar3;
    do {
      *(uint *)((int)allocdValue + iVar2 + (int)puVar3) = *puVar3;
      puVar3 = puVar3 + 1;
      iVar4 = iVar4 + -4;
    } while (iVar4 != 0);
  }
  return allocdValue;
}



void CombineAnimations(CombinedAnimChannel *param_1,CombinedAnimChannel *param_2,
                      CombinedAnimChannel *param_3,float blendFactor)

{
  KFTransform *pKVar1;
  KFTransform *pKVar2;
  CombinedAnimChannel *pCVar3;
  uint *puVar4;
  int iVar5;
  CombinedAnimChannel *pCVar6;
  float *pfVar8;
  float *pfVar10;
  vec3 *pvVar11;
  int i;
  KfTransform_0x24 pfVar9;
  float fVar12;
  KfTransform_0x20 pfVar7;
  
  pCVar6 = param_2;
  puVar4 = &param_2->numTransforms;
  fVar12 = 1.0 - blendFactor;
  param_2 = (CombinedAnimChannel *)0x0;
  if (*puVar4 != 0) {
    pfVar8 = &pCVar6->boneTransforms[0].pos.z;
    pfVar7 = &param_3->boneTransforms[0].scale.y;
    pCVar3 = param_1;
    do {
      pfVar9 = &pCVar3->boneTransforms[0].scale.z;
      Quaternion::SLERP((Quaternion *)(pfVar8 + -6),&ADJ(pfVar7).rotQuat,
                        &pCVar3->boneTransforms[0].rotQuat,blendFactor);
      pCVar3->boneTransforms[0].scale.x = (ADJ(pfVar7)->scale).x * blendFactor + pfVar8[1] * fVar12;
      *(float *)(((int)param_1->boneTransforms - (int)param_3->boneTransforms) + (int)pfVar7) =
           *(float *)((int)pCVar6 + (4 - (int)param_3->boneTransforms) + (int)pfVar7) * fVar12 +
           (ADJ(pfVar7)->scale).y * blendFactor;
      (ADJ(pfVar9)->scale).z =
           *(float *)((int)pCVar6 + (4 - (int)param_1->boneTransforms) + (int)pfVar9) * fVar12 +
           (ADJ(pfVar7)->scale).z * blendFactor;
      pCVar3->boneTransforms[0].pos.x =
           (ADJ(pfVar7)->pos).x * blendFactor + ((vec3 *)(pfVar8 + -2))->x * fVar12;
      pCVar3->boneTransforms[0].pos.y = (ADJ(pfVar7)->pos).y * blendFactor + pfVar8[-1] * fVar12;
      pCVar3->boneTransforms[0].pos.z = (ADJ(pfVar7)->pos).z * blendFactor + *pfVar8 * fVar12;
      param_2 = (CombinedAnimChannel *)((int)&param_2->numTransforms + 1);
      pfVar7 = pfVar7 + 10;
      pfVar8 = pfVar8 + 10;
      pCVar3 = (CombinedAnimChannel *)pfVar9;
    } while (param_2 < (CombinedAnimChannel *)pCVar6->numTransforms);
  }
  iVar5 = pCVar6->numTransforms * 0x28 + 4;
  pKVar1 = param_1->boneTransforms + param_1->numTransforms;
  pKVar2 = param_3->boneTransforms + param_3->numTransforms;
  pfVar8 = &(pKVar2->rotQuat).y;
  pvVar11 = &pCVar6->boneTransforms[pCVar6->numTransforms].pos;
  pfVar10 = &(pKVar1->rotQuat).z;
  i = 6;
  do {
    ((Quaternion *)(pfVar10 + -2))->x =
         ((Quaternion *)(pfVar8 + -1))->x * blendFactor +
         *(float *)((int)(pvVar11 + -2) + 8) * fVar12;
    *(float *)((int)pfVar8 + ((int)pKVar1 - (int)pKVar2)) =
         *(float *)((int)pfVar8 + (int)pCVar6 + (iVar5 - (int)pKVar2)) * fVar12 +
         *pfVar8 * blendFactor;
    *pfVar10 = *(float *)((int)pfVar10 + (int)pCVar6 + (iVar5 - (int)pKVar1)) * fVar12 +
               pfVar8[1] * blendFactor;
    pfVar10[1] = pfVar8[2] * blendFactor + *(float *)((int)(pvVar11 + -1) + 8) * fVar12;
    pfVar10[2] = pfVar8[3] * blendFactor + pvVar11->x * fVar12;
    pfVar10[3] = pfVar8[4] * blendFactor + pvVar11->y * fVar12;
    pfVar10[4] = pfVar8[5] * blendFactor + pvVar11->z * fVar12;
    pfVar10[5] = pfVar8[6] * blendFactor + pvVar11[1].x * fVar12;
    pfVar8 = pfVar8 + 8;
    pfVar10 = pfVar10 + 8;
    pvVar11 = (vec3 *)((int)(pvVar11 + 2) + 8);
    i = i + -1;
  } while (i != 0);
  return;
}



float10 FUN_0002d6e0(undefined4 param_1,undefined4 param_2,float param_3,float param_4,float param_5
                    )

{
  return (float10)param_4 * (float10)param_5 + ((float10)1.0 - (float10)param_5) * (float10)param_3;
}




AnimInstance * AnimInstance::ctor(void)

{
  AnimInstance *allocd;
  int iVar1;
  AnimInstance *pAVar2;
  
  allocd = malloc_(0x128);
  pAVar2 = allocd;
  for (iVar1 = 0x4a; iVar1 != 0; iVar1 = iVar1 + -1) {
    pAVar2->animRes = (AnimResource *)0x0;
    pAVar2 = (AnimInstance *)&pAVar2->animStream;
  }
  allocd->timeRemaining2 = 0.25;
  allocd->timeRemaining = 0.0;
  allocd->defaultT = 0.0;
  (allocd->kft2_1).pos.z = 0.0;
  (allocd->kft2_1).pos.y = 0.0;
  (allocd->kft2_1).pos.x = 0.0;
  (allocd->kft2_1).rotQuat.x = 0.0;
  (allocd->kft2_1).rotQuat.y = 0.0;
  (allocd->kft2_1).rotQuat.z = 0.0;
  (allocd->kft2_1).rotQuat.w = 1.0;
  (allocd->kft2_2).pos.z = 0.0;
  (allocd->kft2_2).pos.y = 0.0;
  (allocd->kft2_2).pos.x = 0.0;
  (allocd->kft2_2).rotQuat.x = 0.0;
  (allocd->kft2_2).rotQuat.y = 0.0;
  (allocd->kft2_2).rotQuat.z = 0.0;
  (allocd->kft2_2).rotQuat.w = 1.0;
  return allocd;
}




void AnimInstance::dtor(void *this,AnimInstance *allocd)

{
  undefined4 uVar1;
  int h_index;
  HeapTableEntry *pHVar2;
  
  if (allocd->currentValuePtr != (CombinedAnimChannel *)0x0) {
    free(allocd->currentValuePtr);
  }
  allocd->currentValuePtr = (CombinedAnimChannel *)0x0;
  if (allocd->finalCombinedChannel != (CombinedAnimChannel *)0x0) {
    free(allocd->finalCombinedChannel);
  }
  if ((allocd->animResource != (AnimResource *)0x0) && (allocd->hasAnimAID != false)) {
    Assets::DestroyAssetOrDecrement(allocd->animResource);
    allocd->animResource = (AnimResource *)0x0;
  }
  h_index = FindHeapOf(allocd);
  uVar1 = runtime::CurrentHeapToAllocateFrom;
  if (g_HeapTableBase[h_index].heapHandle == (HANDLE)0x0) {
    pHVar2 = (HeapTableEntry *)0x0;
  }
  else {
    pHVar2 = g_HeapTableBase + h_index;
  }
  runtime::CurrentHeapToAllocateFrom = h_index;
  XAPILIB::HeapFree(pHVar2->heapHandle,0,allocd);
  runtime::CurrentHeapToAllocateFrom = uVar1;
  return;
}



BOOL AnimInstance::loadAnimFromExistingResource
               (AnimResource *animRes,AnimInstance *this,float t,float param_4,char param_5,
               short param_6,char *animAID)

{
  float fVar1;
  char cVar2;
  int iVar3;
  char *pcVar4;
  CombinedAnimChannel *allocdvalue;
  float10 fVar5;
  ushort numAllocdValues;
  
  if ((this->animResource == (AnimResource *)0x0) || (this->timeRemaining2 <= 0.0)) {
    this->timeRemaining2 = 0.0;
    this->timeRemaining = 0.0;
  }
  else {
    if (this->field_0x124 != '\0') {
      if (this->currentValuePtr != (CombinedAnimChannel *)0x0) {
        free(this->currentValuePtr);
      }
      this->currentValuePtr = this->finalCombinedChannel;
      this->finalCombinedChannel = (CombinedAnimChannel *)0x0;
    }
    this->timeRemaining = this->timeRemaining2;
  }
  if (this->finalCombinedChannel != (CombinedAnimChannel *)0x0) {
    free(this->finalCombinedChannel);
    this->finalCombinedChannel = (CombinedAnimChannel *)0x0;
  }
  if ((this->animResource != (AnimResource *)0x0) && (this->hasAnimAID != false)) {
    Assets::DestroyAssetOrDecrement(this->animResource);
    this->animResource = (AnimResource *)0x0;
  }
  this->animResource = animRes;
  pcVar4 = animAID;
  if (animAID == (char *)0x0) {
    pcVar4 = g_GlobalAssetName;
  }
  iVar3 = 0x2c - (int)pcVar4;
  do {
    cVar2 = *pcVar4;
    pcVar4[(int)this + iVar3] = cVar2;
    pcVar4 = pcVar4 + 1;
  } while (cVar2 != '\0');
  this->hasAnimAID = animAID != (char *)0x0;
  copyOffsetsFromAnimResource(this,animRes,(int)t,param_5,Linear);
  if (param_4 <= 0.0) {
    param_4 = this->animRes->duration;
  }
  this->duration = param_4;
  if (0.0 < this->invDuration || this->invDuration == 0.0) {
    fVar5 = abs_float(1.0 / param_4);
  }
  else {
    fVar5 = abs_float(1.0 / param_4);
    fVar5 = -fVar5;
  }
  this->invDuration = (float)fVar5;
  if (param_6 == 0) {
    fVar5 = abs_float(this->invDuration);
  }
  else {
    if (param_6 != 1) {
      if (param_6 == 2) {
        this->invDuration = 0.0 - this->invDuration;
      }
      goto LAB_0002da4c;
    }
    fVar5 = abs_float(this->invDuration);
    fVar5 = -fVar5;
  }
  this->invDuration = (float)fVar5;
LAB_0002da4c:
  numAllocdValues = animRes->numBones;
  allocdvalue = malloc_((uint)numAllocdValues * 0x28 + 0x104);
  allocdvalue->numTransforms = (uint)numAllocdValues;
  KeyframeAllocdValue::initialise(allocdvalue);
  this->defaultT = t;
  this->finalCombinedChannel = allocdvalue;
  this->numTicks = 0;
  this->totalDelta = 0.0;
  this->field_0x124 = 0;
  (this->kft2_2).pos.z = 0.0;
  (this->kft2_2).pos.y = 0.0;
  (this->kft2_2).pos.x = 0.0;
  (this->kft2_2).rotQuat.x = 0.0;
  (this->kft2_2).rotQuat.y = 0.0;
  (this->kft2_2).rotQuat.z = 0.0;
  (this->kft2_2).rotQuat.w = 1.0;
  (this->kft2_3).pos.z = 0.0;
  (this->kft2_3).pos.y = 0.0;
  (this->kft2_3).pos.x = 0.0;
  (this->kft2_3).rotQuat.x = 0.0;
  (this->kft2_3).rotQuat.y = 0.0;
  (this->kft2_3).rotQuat.z = 0.0;
  (this->kft2_3).rotQuat.w = 1.0;
  if (this->cValsPtr != 0) {
    fVar1 = this->t;
    this->t = 1.0;
    readAnimResource(this,&this->kft2_3,(AnimInstance_0xd4)0x0,0.0,0,0,0,this->slerpT);
    this->t = fVar1;
  }
  return 1;
}



BOOL AnimInstance::loadAnimFromNewResource
               (AnimInstance *allocd,float t,float param_3,char param_4,
               short playbackSpeedGreaterThanOne,char *animAID)

{
  BOOL BVar1;
  AnimResource *local_4;
  
  if (*(int *)animAID == 0x5f646961) {
    Assets::GetResourceBytes(animAID,&local_4);
    if (local_4 != (AnimResource *)0x0) {
      BVar1 = loadAnimFromExistingResource
                        (local_4,allocd,t,param_3,param_4,playbackSpeedGreaterThanOne,animAID);
      return BVar1;
    }
    runtime::ExitGame(2);
  }
  return 0;
}




void AnimInstance::update(AnimInstance *this,float delta,BOOL ignoreErrors)

{
  float fVar1;
  
  if (this->animResource != (AnimResource *)0x0) {
    fVar1 = 0.0;
    if (this->restartAnimation == '\0') {
      fVar1 = delta;
    }
    this->delta = fVar1;
    this->defaultT = this->t;
    updateAnimAndRunEvents
              (this,this->delta,(uint)(byte)this->field_0x124,&this->kft2_1,&this->kft2_2);
    if (ignoreErrors == 0) {
                    // Update the actual skeleton/channels
      updateFromAnimRes(this,this->finalCombinedChannel,(float *)0x0,0,0,this->slerpT);
      AnimInstanceHeader::updateFaceAndEvents(this);
      this->field_0x124 = 1;
    }
    if (0.0 < this->timeRemaining) {
      fVar1 = this->timeRemaining - this->delta;
      this->timeRemaining = fVar1;
      if (((fVar1 <= 0.0) || (ignoreErrors != 0)) ||
         (this->currentValuePtr == (CombinedAnimChannel *)0x0)) {
        if (this->currentValuePtr != (CombinedAnimChannel *)0x0) {
          free(this->currentValuePtr);
        }
        this->currentValuePtr = (CombinedAnimChannel *)0x0;
        this->timeRemaining = 0.0;
      }
      else {
                    // Flatten animations down?
        CombineAnimations(this->finalCombinedChannel,this->finalCombinedChannel,
                          this->currentValuePtr,fVar1 / this->timeRemaining2);
      }
    }
    this->numTicks = this->numTicks + 1;
    this->totalDelta = this->totalDelta + this->delta;
  }
  return;
}




void Assets::AnimResource::InitLoader(void)

{
  uint i;
  ResourceLoaderStub *pRVar1;
  
  i = 0;
  pRVar1 = g_majorResourceLoaders;
  do {
    if (pRVar1->typeStr == (char *)0x0) {
      pRVar1 = g_majorResourceLoaders + i;
      goto LAB_0002dd6f;
    }
    i = i + 1;
    pRVar1 = pRVar1 + 1;
  } while (i < 16);
  pRVar1 = (ResourceLoaderStub *)0x0;
LAB_0002dd6f:
  pRVar1->typeStr = "anim";
  pRVar1->processDescriptor = processMetadata;
  pRVar1->ctor = (AfterLoadFn *)0x0;
  pRVar1->dtor = (void *)0x0;
  return;
}



void Assets::AnimResource::processMetadata
               (AnimResource *descriptor,uint resOffset,DataViewList *dvl)

{
  int iVar1;
  int i;
  
                    // Move pointers to point to real asset data
  if (descriptor->somePtrList != (uint32_t *)0x0) {
    descriptor->somePtrList = (uint32_t *)((int)descriptor->somePtrList + resOffset);
    i = 0;
    do {
      iVar1 = *(int *)((int)descriptor->somePtrList + i);
      if (iVar1 != 0) {
        *(uint *)((int)descriptor->somePtrList + i) = iVar1 + resOffset;
      }
      iVar1 = *(int *)((int)descriptor->somePtrList + i + 4);
      if (iVar1 != 0) {
        *(uint *)((int)descriptor->somePtrList + i + 4) = iVar1 + resOffset;
      }
      iVar1 = *(int *)((int)descriptor->somePtrList + i + 8);
      if (iVar1 != 0) {
        *(uint *)((int)descriptor->somePtrList + i + 8) = iVar1 + resOffset;
      }
      iVar1 = *(int *)((int)descriptor->somePtrList + i + 0xc);
      if (iVar1 != 0) {
        *(uint *)((int)descriptor->somePtrList + i + 0xc) = iVar1 + resOffset;
      }
      i = i + 0x10;
    } while (i < 0x100);
    return;
  }
  descriptor->somePtrList = (uint32_t *)0x0;
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields

void AnimEventsResource::updateEventsForAnim
               (AnimEventResource *animEvent,TriggerAnimationEventCallback *callback,
               AnimInstance *anim,uint animIndex,avatar *av)

{
  animEventId aVar1;
  
  if (callback != (TriggerAnimationEventCallback *)0x0) {
    aVar1 = animEvent->events[0].animEventType;
    while (aVar1 != Null) {
      if ((PinataTime_SetResidencyCheck < animEvent->events[0].animEventType) ||
         (Animation::anim_events_lut[animEvent->events[0].animEventType].size ==
          (uint)animEvent->events[0].size)) {
        Animation::DispatchAnimEvents(callback,animEvent->events,anim,animIndex,av);
      }
      animEvent = (AnimEventResource *)
                  ((int)&animEvent->events[0].size + (uint)animEvent->events[0].size);
      aVar1 = ((AnimEventEntry *)animEvent)->animEventType;
    }
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields

void Animation::PreDispatchAnimEvents
               (AnimEventResource *animEventRes,AnimInstance *allocd,
               TriggerAnimationEventCallback *callback,undefined4 param_4,avatar *av)

{
  float fVar6;
  AnimEventEntry_ptr_12_AnimEventType offset_ptr;
  animEventId event_type;
  float oldT;
  float t;
  
  if (callback != (TriggerAnimationEventCallback *)0x0) {
    oldT = allocd->defaultT;
    t = allocd->t;
    fVar6 = 0.0;
    if (0.0 < allocd->invDuration || allocd->invDuration == 0.0) {
      fVar6 = 1.0;
    }
    offset_ptr = &animEventRes->events[0].animEventType;
    allocd->t = fVar6;
    allocd->defaultT = t;
    event_type = ADJ(offset_ptr)->animEventType;
    while (event_type != Null) {
      if ((((uint)(byte)animEventRes->events[0].field_0xe |
           anim_events_lut[ADJ(offset_ptr)->animEventType].animEventFlags) & 1) != 0) {
        DispatchAnimEvents(callback,animEventRes->events,allocd,param_4,av);
      }
      animEventRes = (AnimEventResource *)
                     ((int)&animEventRes->events[0].size + (uint)animEventRes->events[0].size);
      offset_ptr = &((AnimEventEntry *)animEventRes)->animEventType;
                    // Dispatches all events
      event_type = ((AnimEventEntry *)animEventRes)->animEventType;
    }
    allocd->t = t;
    allocd->defaultT = oldT;
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields

void AnimInstance::triggerAnimStartEvents
               (AnimEventEntry *events,AnimInstance *param_2,
               TriggerAnimationEventCallback *animCallback,undefined4 param_4,avatar *av)

{
  float fVar1;
  animEventId aVar2;
  animEventId *paVar3;
  float fVar4;
  
  if (animCallback != (TriggerAnimationEventCallback *)0x0) {
    fVar1 = param_2->defaultT;
    fVar4 = 0.0;
    if (param_2->invDuration <= 0.0 && param_2->invDuration != 0.0) {
      fVar4 = 1.0;
    }
    paVar3 = &events->animEventType;
    param_2->defaultT = fVar4;
    aVar2 = *paVar3;
    while (aVar2 != Null) {
      if ((((uint)(byte)events->field_0xe | Animation::anim_events_lut[*paVar3].animEventFlags) & 1)
          != 0) {
        Animation::DispatchAnimEvents(animCallback,events,param_2,param_4,av);
      }
      events = (AnimEventEntry *)((int)&events->size + (uint)events->size);
      paVar3 = &events->animEventType;
      aVar2 = events->animEventType;
    }
    param_2->defaultT = fVar1;
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields

BOOL Animation::DispatchAnimEvents
               (TriggerAnimationEventCallback *animCallback,AnimEventEntry *event_res,
               AnimInstance *allocd,uint32_t animIndex,avatar *av)

{
  float fVar5;
  float fVar6;
  float t;
  bool anim_is_good;
  bool bVar3;
  float fVar2;
  
  if ((uint)event_res->size != anim_events_lut[event_res->animEventType].size) {
    return 0;
  }
  t = allocd->t;
  fVar2 = event_res->duration;
  anim_is_good = false;
  if (t != allocd->defaultT) {
    if (allocd->invDuration <= 0.0 && allocd->invDuration != 0.0) {
      fVar5 = allocd->defaultT;
    }
    else {
      fVar5 = t;
      t = allocd->defaultT;
    }
    if (fVar5 <= t) {
      if ((t <= fVar2) || (fVar2 < fVar5)) goto LAB_0002e035;
      anim_is_good = false;
    }
    else if ((fVar2 < t) || (fVar5 <= fVar2)) {
      anim_is_good = false;
    }
    else {
LAB_0002e035:
      anim_is_good = true;
      if (animCallback != (TriggerAnimationEventCallback *)0x0) {
                    // Update the player
        (*animCallback)((AnimEventResource *)event_res,animIndex,(uint32_t)allocd->t,av);
      }
    }
  }
  if (((((((uint)(byte)event_res->field_0xe |
          anim_events_lut[event_res->animEventType].animEventFlags) & 4) != 0) &&
       (event_res->duration <= allocd->t)) && (allocd->t < event_res->field3_0x8)) &&
     (animCallback != (TriggerAnimationEventCallback *)0x0)) {
    (*animCallback)((AnimEventResource *)event_res,animIndex,(uint32_t)allocd->t,av);
  }
  t = event_res->field3_0x8;
  if ((t != 0.0) && (fVar2 = allocd->t, fVar2 != allocd->defaultT)) {
    if (allocd->invDuration <= 0.0 && allocd->invDuration != 0.0) {
      fVar5 = allocd->defaultT;
      fVar6 = fVar2;
    }
    else {
      fVar6 = allocd->defaultT;
      fVar5 = fVar2;
    }
    if (fVar5 <= fVar6) {
      if (t < fVar6) goto joined_r0x0002e0f5;
LAB_0002e0f7:
      bVar3 = true;
      if (animCallback != (TriggerAnimationEventCallback *)0x0) {
                    // Disabling this gives the player weird accelerated movement
        (*animCallback)((AnimEventResource *)event_res,animIndex,(uint32_t)allocd->t,av);
      }
      goto LAB_0002e115;
    }
    if (fVar6 <= t) {
joined_r0x0002e0f5:
      if (t < fVar5) goto LAB_0002e0f7;
    }
  }
  bVar3 = false;
LAB_0002e115:
  if ((!anim_is_good) && (!bVar3)) {
    return 0;
  }
  return 1;
}




float10 Animation::PickLinearKeyframe(float progress,undefined4 unused,int v1,int v2)

{
  return (float10)(v2 - v1) * (float10)progress + (float10)v1;
}




float10 Animation::PickCubicHardKeyframes(float t,int prev,int start,int end,int next)

{
  float10 fVar1;
  float10 fVar2;
  
  fVar1 = (float10)start;
  fVar2 = (float10)end;
  return ((fVar2 * (float10)0.5 - (float10)((float)prev * 0.5)) +
         (((fVar2 + fVar2 + ((float10)prev - fVar1 * (float10)2.5)) - (float10)next * (float10)0.5)
         + (((fVar1 * (float10)1.5 - fVar2 * (float10)1.5) + (float10)next * (float10)0.5) -
           (float10)((float)prev * 0.5)) * (float10)t) * (float10)t) * (float10)t + fVar1;
}



float10 Animation::PickCubicSoftKeyframes
                  (float param_1,int param_2,int param_3,int param_4,int param_5)

{
  float10 fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  
  fVar1 = (float10)param_3;
  fVar2 = (float)param_4 * 0.5;
                    // 1/6
  fVar4 = (float)param_2 * 0.16666667;
  fVar3 = (float)param_2 * 0.5;
  return fVar1 * (float10)0.6666667 + (float10)param_4 * (float10)0.16666667 + (float10)fVar4 +
         (((float10)fVar2 - (float10)fVar3) +
         (((float10)fVar3 - fVar1) + (float10)fVar2 +
         (((float10)param_5 * (float10)0.16666667 + ((float10)0.5 * fVar1 - (float10)fVar2)) -
         (float10)fVar4) * (float10)param_1) * (float10)param_1) * (float10)param_1;
}



void ParsedAnimVal::getVec3
               (ParsedAnimVal *this,vec3 *param_2,float scale,float defaultVal,byte format)

{
  short sVar1;
  byte numBitsToRead;
  vec3 *v;
  int curs;
  float10 computedValue;
  float def;
  uint next;
  uint end;
  uint start;
  uint prev;
  byte local_4;
  undefined3 uStack_3;
  byte *cursor;
  ushort i_mask;
  byte second_nib;
  
  v = param_2;
                    // Runs 3 times
  param_2 = (vec3 *)0b10000000;
  do {
    i_mask = (ushort)param_2;
    def = defaultVal;
    if ((format & i_mask) == 0) {
LAB_0002e37a:
      v->x = def;
    }
    else {
      cursor = (byte *)this->shorts;
                    // If storing directly, use the value
      if ((ushort)(i_mask >> 3 & (ushort)format) != 0) {
        sVar1 = *(short *)cursor;
        this->shorts = (short *)(cursor + 2);
        def = (float)(int)sVar1 * scale;
                    // continue
        goto LAB_0002e37a;
      }
                    // Otherwise, figure out which keyframes we're using and interpolate the value
      curs = (int)*(short *)cursor;
                    // Somewhere here describes the keyframe structure and uses some masks to parse
                    // it
      second_nib = this->oddBitSize;
      this->shorts = (short *)(cursor + 2);
      numBitsToRead = *this->section2;
                    // Skip the bit size cursor ahead only on the second nibble
      this->section2 = this->section2 + second_nib;
                    // Rounds it out to bit boundaries
                    // 
                    // Always add 1 to number of bits to read
      numBitsToRead = ((numBitsToRead & this->nibbleMask) >> ((second_nib & 0b00000111) << 2)) + 1;
                    // Toggle it
      this->oddBitSize = second_nib == 0;
      next = 0;
      end = 0;
      start = 0;
      prev = 0;
      _local_4 = CONCAT31(uStack_3,numBitsToRead);
                    // Shift left by 0 or 4
      this->nibbleMask = 0b00001111 << ((second_nib == 0) << 2);
                    // Calculate indices
      readBitsFromBitStream
                (this->prevKeyframe->data,this->startKeyframe->data,this->endKeyframe->data,
                 this->nextKeyframe->data,&this->curByte,&this->curBit,&prev,&start,&end,&next,
                 numBitsToRead);
                    // Merge floats together into one
                    // 
                    // Goes to Animation::PickLinearKeyframeGet the relevant offset indices to the
                    // base position
      computedValue =
           (float10)(*(code *)this->keyframeSelectionCallback)
                              (this->slerpT,prev + curs,start + curs,end + curs,next + curs);
      v->x = (float)(computedValue * (float10)scale);
    }
    v = (vec3 *)&v->y;
    param_2 = (vec3 *)(uint)(i_mask >> 1);
    if (i_mask >> 1 == 0b00010000) {
      return;
    }
  } while( true );
}




void FUN_0002e750(vec3 *param_1,AnimInstance *param_2)

{
  if ((*(byte *)(param_2->cValsPtr + 0xc) & 2) != 0) {
    FUN_0002e650(*(undefined1 *)(param_2->cValsPtr + 0xd));
    return;
  }
  param_1->z = 0.0;
  param_1->y = 0.0;
  param_1->x = 0.0;
  return;
}



void __fastcall
ParsedAnimVal::fromAnimVal
          (ParsedAnimVal *this,AnimStream *stream,ushort prev,ushort current,ushort next,
          ushort nextnext)

{
  short *shorts;
  uint sizeof_s1;
  uint block_size;
  uint sizeof_s2;
  ushort blockSize;
  ushort offset2;
  ushort sect1_size;
  
  blockSize = stream->blockSize;
  sect1_size = stream->section1Size;
  shorts = (short *)(stream->section1 + (stream->headerSize - 0xc));
  offset2 = stream->section2Size;
  this->oddBitSize = '\0';
  this->curBit = '\0';
  this->curByte = 0;
  sizeof_s1 = (uint)sect1_size;
  this->section2 = (uint8_t *)(sizeof_s1 + (int)shorts);
  block_size = (uint)blockSize;
  sizeof_s2 = (uint)offset2;
  this->prevKeyframe = (RawAnimKeyframe *)(prev * block_size + sizeof_s2 + sizeof_s1 + (int)shorts);
  this->startKeyframe =
       (RawAnimKeyframe *)(current * block_size + sizeof_s2 + sizeof_s1 + (int)shorts);
  this->endKeyframe = (RawAnimKeyframe *)(next * block_size + sizeof_s2 + sizeof_s1 + (int)shorts);
  this->nextKeyframe =
       (RawAnimKeyframe *)(nextnext * block_size + sizeof_s2 + sizeof_s1 + (int)shorts);
  this->nibbleMask = 0b00001111;
  this->shorts = shorts;
  this->slerpCallback = Quaternion::slerpIntoQ1;
  return;
}



void AnimInstance::updateFromAnimRes
               (AnimInstance *this,CombinedAnimChannel *out,float *progress,undefined4 param_4,
               int numBones,float slerp_t)

{
  ushort num_keyframes;
  AnimStream *stream;
  byte *packFormat;
  KFTransform_ptr_24_float pfVar6;
  KeyframeAllocdValue_0x18 pfVar5;
  int i;
  ushort next;
  uint32_t current;
  float scaler;
  float div2;
  ParsedAnimVal parsedVal;
  KeyframeSelectionMethod KVar1;
  byte bVar2;
  KFTransform *transform;
  uint uVar3;
  
  if (numBones == 0) {
    stream = this->animStream;
    num_keyframes = this->animRes->numKeyframes;
  }
  else {
    stream = (AnimStream *)this->cValsPtr;
    num_keyframes = this->animRes->somethingSize;
  }
  updateKeyframeIndices
            (param_4,&scaler,progress,this,(uint)num_keyframes,(short *)&scaler,(short *)&next,&i,
             &current);
  ParsedAnimVal::fromAnimVal(&parsedVal,stream,scaler._0_2_,(ushort)current,next,(ushort)i);
  KVar1 = this->keyframeMethod;
  packFormat = stream->section1;
  if (KVar1 == Linear) {
    parsedVal.keyframeSelectionCallback = Animation::PickLinearKeyframe;
  }
  else if (KVar1 == CubicHard) {
    parsedVal.keyframeSelectionCallback = Animation::PickCubicHardKeyframes;
  }
  else if (KVar1 == CubicSoft) {
    parsedVal.keyframeSelectionCallback = Animation::PickCubicSoftKeyframes;
  }
  uVar3 = this->animRes->precisionSpecifiers;
  _next = 1.0 / (float)(1 << ((byte)(uVar3 >> 0x12) & 0b00011111));
  div2 = 1.0 / (float)(1 << ((byte)(uVar3 >> 8) & uVar5));
  scaler = 1.0 / ((float)(1 << (((byte)(uVar3 >> 0x17) & uVar6) - 1 & 0x1f)) - 1.0);
  if (numBones == 0) {
    numBones = (int)this->animRes->numBones;
  }
  else {
    numBones = 1;
  }
                    // Base anim?
  if ((short)numBones != 0) {
    i = numBones;
    transform = out->boneTransforms;
    do {
      bVar2 = *packFormat;
      current = CONCAT31(current._1_3_,bVar2);
      ParsedAnimVal::getQuat(&parsedVal,transform,current,scaler,0);
      if ((bVar2 & 2) == 0) {
        (transform->pos).z = 0.0;
        (transform->pos).y = 0.0;
        (transform->pos).x = 0.0;
        packFormat = packFormat + 1;
      }
      else {
        ParsedAnimVal::getVec3(&parsedVal,&transform->pos,_next,0.0,packFormat[1]);
        packFormat = packFormat + 2;
      }
      if ((bVar2 & 1) == 0) {
        (transform->scale).x = 1.0;
        (transform->scale).y = 1.0;
        (transform->scale).z = 1.0;
      }
      else {
        ParsedAnimVal::getVec3(&parsedVal,&transform->scale,div2,1.0,*packFormat);
        packFormat = packFormat + 1;
      }
      transform = transform + 1;
      i = i + -1;
    } while (i != 0);
    i = 0;
  }
  if ((slerp_t != 1.0) && ((short)numBones != 0)) {
    pfVar6 = &out->boneTransforms[0].pos.z;
    do {
                    // Slerp the rot quat into itself
      Quaternion::SLERP(&animation::slerp_quat,&ADJ(pfVar6).rotQuat,&ADJ(pfVar6).rotQuat,slerp_t);
      (ADJ(pfVar6)->pos).x = (ADJ(pfVar6)->pos).x * slerp_t;
      (ADJ(pfVar6)->pos).y = slerp_t * (ADJ(pfVar6)->pos).y;
      (ADJ(pfVar6)->pos).z = slerp_t * (ADJ(pfVar6)->pos).z;
      (ADJ(pfVar6)->scale).x = slerp_t * (ADJ(pfVar6)->scale).x;
      (ADJ(pfVar6)->scale).y = (ADJ(pfVar6)->scale).y * slerp_t;
      (ADJ(pfVar6)->scale).z = (ADJ(pfVar6)->scale).z * slerp_t;
                    // + 0x28
      pfVar6 = pfVar6 + 10;
      numBones = numBones + -1;
                    // Force skipping this breaks swingable weapons and makes throwables be thrown
                    // instantly
                    // 
                    // Possibly folding parent animation down through children?
                    // 
                    // It also breaks knockdowns though, which are a blend between 2 poses
                    // 
                    // Most likely just combines animations
                    // 
                    // It also instantly skips death animation
                    // > It's likely that the animation is ending early and bypassing the event
    } while (numBones != 0);
  }
  return;
}



long updateKeyframeIndices
               (uint *param_1,undefined4 param_2,float *param_3,AnimInstance *param_4,
               uint numKeyframes,short *prev,short *next,short *nextNext,ushort *current)

{
  longlong lVar1;
  ushort uVar2;
  short sVar3;
  uint loops;
  float fVar4;
  uint64_t uVar5;
  
  if (param_1 == (uint *)0x0) {
    loops = (uint)(param_4->loopMode == 0);
  }
  else {
    loops = *param_1;
  }
  if (loops == 0) {
    numKeyframes = numKeyframes - 1;
  }
  if (param_3 == (float *)0x0) {
    fVar4 = (float)(int)numKeyframes * param_4->t;
  }
  else {
    fVar4 = *param_3;
  }
  if (loops != 0) {
    uVar5 = float10::to_uint64_t((float10)fVar4);
    lVar1 = (longlong)(ulonglong)((uint)uVar5 & 0xffff) % (longlong)(int)numKeyframes;
    *current = (ushort)lVar1;
    *next = (short)((longlong)(ulonglong)(((uint)lVar1 & 0xffff) + 1) % (longlong)(int)numKeyframes)
    ;
    *nextNext = (short)((longlong)(ulonglong)(*current + 2) % (longlong)(int)numKeyframes);
    *prev = (short)((int)((*current - 1) + numKeyframes) % (int)numKeyframes);
    return (uint)*current;
  }
  uVar5 = float10::to_uint64_t((float10)fVar4);
  uVar2 = (ushort)uVar5;
  *current = uVar2;
  *prev = uVar2 - (uVar2 != 0);
  loops = (uint)*current + (uint)(*current != numKeyframes);
  sVar3 = (short)loops;
  *next = sVar3;
  *nextNext = (ushort)((loops & 0xffff) != numKeyframes) + sVar3;
  return (uint)*current;
}



void ReadQuatFromKeyframes
               (RawAnimKeyframe *kf1,RawAnimKeyframe *kf2,int *startingByte,byte *startingBit,
               uint *val1,uint *val2,byte numBitsToRead)

{
  byte bVar1;
  byte bVar2;
  char cVar3;
  byte bVar4;
  uint uVar5;
  byte numBits;
  int iVar6;
  undefined4 uStack_4;
  
  bVar4 = *startingBit;
  iVar6 = *startingByte;
  uStack_4 = (uint)bVar4 << 0x18;
  numBits = numBitsToRead;
  if (numBitsToRead == 0) {
    *startingBit = bVar4;
    *startingByte = iVar6;
    return;
  }
  do {
    uVar5 = (uint)bVar4;
    _numBitsToRead = 0;
    bVar1 = ('\x01' << (numBits & 0x1f)) + -1 << (bVar4 & 0x1f);
    do {
      cVar3 = (char)_numBitsToRead;
      if ((((uint)(bVar1 >> (bVar4 & 0x1f)) << 0x18) >> (0x1fU - cVar3 & 0x1f) & 1) != 0)
      goto LAB_0002ecb7;
      _numBitsToRead = _numBitsToRead + 1;
    } while (_numBitsToRead < 0x20);
    cVar3 = '\0';
LAB_0002ecb7:
    bVar2 = 8 - cVar3;
    numBits = numBits - bVar2;
    *val1 = *val1 | (uint)(byte)((kf1[iVar6].data[0] & bVar1) >> (bVar4 & 0x1f)) <<
                    (uStack_4._2_1_ & 0x1f);
    *val2 = *val2 | (uint)(byte)((kf2[iVar6].data[0] & bVar1) >> (bVar4 & 0x1f)) <<
                    (uStack_4._2_1_ & 0x1f);
    bVar4 = bVar2 + uStack_4._3_1_ & 7;
    iVar6 = iVar6 + (uint)(bVar2 + uVar5 == 8);
    uStack_4 = (uint)(CONCAT11(bVar2 + uStack_4._3_1_,uStack_4._2_1_ + bVar2) & 0x7ff) << 0x10;
    if (numBits == 0) {
      *startingBit = bVar4;
      *startingByte = iVar6;
      return;
    }
  } while( true );
}



void ParsedAnimVal::readBitsFromBitStream
               (byte *stream1,byte *stream2,byte *stream3,byte *stream4,int *byteIndex,
               byte *bitIndex,uint *k1,uint *k2,uint *k3,uint *k4,byte bitLen)

{
  byte read_mask;
  byte bVar1;
  uint8_t bitlenn;
  byte j;
  uint uVar2;
  byte len;
  int i;
  undefined4 uStack_4;
  
  j = *bitIndex;
  i = *byteIndex;
  uStack_4 = (uint)j << 0x18;
  len = bitLen;
                    // If len is 0, do nothing
  if (bitLen == 0) {
    *bitIndex = j;
    *byteIndex = i;
    return;
  }
  do {
                    // Read the bytes in 2 pieces based on the byte boundary. Eg, 3 bits then 5 bits
                    // then 3 bits then 5 bits etc etc
    uVar2 = (uint)j;
    _bitLen = 0;
                    // Create read mask based on length, then shift it based on j
                    // 
                    // eg. bitLen = 20.
                    // 
                    // Start with 0b1, then shift left by 20 (bit 21 is active)
                    // 0b00000000 00010000 00000000 00000000
                    // 
                    // Subtract 1 (extract bottom 20 bits)
                    // 0b00000000 00001111 11111111 11111111
                    // 
                    // Shift the whole thing left by j, the bit index
                    // 
                    // eg. j = 3
                    // 
                    // 0b00000000 01111111 11111111 11111000
    read_mask = ('\x01' << (len & 0b00011111)) + -1 << (j & 0x1f);
    do {
      bitlenn = (uint8_t)_bitLen;
                    // Find the first non-zero bit in the mask
      if ((((uint)(read_mask >> (j & 0b00011111)) << 0x18) >> (0x1f - bitlenn & 0x1f) & 1) != 0)
      goto DoTheReading;
      _bitLen = _bitLen + 1;
    } while (_bitLen < 0x20);
    bitlenn = '\0';
DoTheReading:
    bVar1 = 8 - bitlenn;
    len = len - bVar1;
                    // Read using the mask shifted bit index to the right by bit index
                    // 
                    // Then shift it to the appropriate byte of the new constructed value
    *k1 = *k1 | (uint)(byte)((stream1[i] & read_mask) >> (j & 0x1f)) << (uStack_4._2_1_ & 0x1f);
    *k2 = *k2 | (uint)(byte)((stream2[i] & read_mask) >> (j & 0x1f)) << (uStack_4._2_1_ & 0x1f);
    *k3 = *k3 | (uint)(byte)((stream3[i] & read_mask) >> (j & 0x1f)) << (uStack_4._2_1_ & 0x1f);
    *k4 = *k4 | (uint)(byte)((stream4[i] & read_mask) >> (j & 0x1f)) << (uStack_4._2_1_ & 0x1f);
    j = bVar1 + uStack_4._3_1_ & 7;
    i = i + (uint)(bVar1 + uVar2 == 8);
    uStack_4 = (uint)(CONCAT11(bVar1 + uStack_4._3_1_,uStack_4._2_1_ + bVar1) & 0x7ff) << 0x10;
    if (len == 0) {
      *bitIndex = j;
      *byteIndex = i;
      return;
    }
  } while( true );
}




void BoneList::dtor(BoneList *param_1)

{
  undefined4 uVar1;
  int iVar2;
  HeapTableEntry *pHVar3;
  
  if (param_1->ids != (Buffer<uint16_t> *)0x0) {
    free(param_1->ids);
    param_1->ids = (Buffer<uint16_t> *)0x0;
  }
  if (param_1->boneParentCallbacks != (Buffer<> *)0x0) {
    free(param_1->boneParentCallbacks);
    param_1->boneParentCallbacks = (Buffer<> *)0x0;
  }
  if (param_1->bone0x10s != (Buffer<Bone0x10> *)0x0) {
    free(param_1->bone0x10s);
    param_1->bone0x10s = (Buffer<Bone0x10> *)0x0;
  }
  iVar2 = FindHeapOf(param_1);
  uVar1 = runtime::CurrentHeapToAllocateFrom;
  if (g_HeapTableBase[iVar2].heapHandle == (HANDLE)0x0) {
    pHVar3 = (HeapTableEntry *)0x0;
  }
  else {
    pHVar3 = g_HeapTableBase + iVar2;
  }
  runtime::CurrentHeapToAllocateFrom = iVar2;
  XAPILIB::HeapFree(pHVar3->heapHandle,0,param_1);
  runtime::CurrentHeapToAllocateFrom = uVar1;
  return;
}




void BoneList::addRigidByBoneIndex(BoneList *bs,ushort id,void *transformCallback,RigidBone *ptr0x9)

{
  ushort uVar1;
  ushort uVar2;
  uint32_t *puVar3;
  uint32_t index;
  Bone0x10 *bone0x10;
  Bone0x10 *firstBone;
  
  if (bs->numBones == 0) {
    index = ctor(bs);
  }
  else {
    index = resizeForSize(bs,id);
  }
  uVar1 = bs->boneParentCallbacks->valueSize;
  puVar3 = bs->boneParentCallbacks->head;
  uVar2 = bs->bone0x10s->valueSize;
  firstBone = bs->bone0x10s->head;
  *(ushort *)(bs->ids->valueSize * index + (int)bs->ids->head) = id;
  *(code **)(uVar1 * index + (int)puVar3) = getBoneTransform;
  bone0x10 = (Bone0x10 *)((int)&firstBone->getTransform + uVar2 * index);
  bone0x10->getTransform = transformCallback;
  bone0x10->idk0x9ptr = ptr0x9;
  return;
}




uint32_t BoneList::ctor(BoneList *param_1)

{
  Buffer<uint16_t> *pBVar1;
  Buffer<> *pBVar2;
  Buffer<Bone0x10> *pBVar3;
  undefined4 *puVar4;
  
  pBVar1 = malloc_(0x14);
  pBVar1->head = pBVar1->values;
  pBVar1->tail = pBVar1->values;
  pBVar1->valueSize = 2;
  pBVar1->capacity = 2;
  pBVar1->end = &pBVar1[1].valueSize;
  param_1->ids = pBVar1;
  pBVar2 = malloc_(0x14);
  pBVar2->head = pBVar2->values;
  pBVar2->tail = pBVar2->values;
  pBVar2->valueSize = 4;
  pBVar2->capacity = 1;
  pBVar2->end = (uint32_t *)(pBVar2 + 1);
  param_1->boneParentCallbacks = pBVar2;
  pBVar3 = malloc_(0x20);
  pBVar3->head = pBVar3->values;
  pBVar3->tail = pBVar3->values;
  pBVar3->capacity = 1;
  pBVar3->valueSize = 0x10;
  pBVar3->end = (Bone0x10 *)(pBVar3 + 1);
  param_1->bone0x10s = pBVar3;
  param_1->numBones = 1;
  ExtendBuffer2((Buffer **)param_1,0);
  ExtendBuffer2((Buffer **)param_1,0);
  ExtendBuffer2((Buffer **)&param_1->boneParentCallbacks,0);
  puVar4 = ExtendBuffer2((Buffer **)&param_1->bone0x10s,0);
  *puVar4 = 0;
  puVar4[2] = 0;
  puVar4[1] = 0;
  puVar4[3] = 0;
  *(undefined2 *)((uint)param_1->ids->valueSize + (int)param_1->ids->head) = 0xffff;
  return 0;
}




int BoneList::resizeForSize(BoneList *bs,ushort id)

{
  Buffer<uint16_t> *pBVar1;
  undefined4 uVar2;
  int *mem;
  ushort *puVar3;
  int iVar4;
  Bone0x10 *puVar5;
  HeapTableEntry *pHVar5;
  int i;
  
  i = 0;
  mem = malloc_(4);
  *mem = 0;
  while( true ) {
    pBVar1 = bs->ids;
    puVar3 = (ushort *)((uint)pBVar1->valueSize * *mem + (int)pBVar1->head);
    if (puVar3 == pBVar1->tail) break;
    *mem = *mem + 1;
    if ((puVar3 == (ushort *)0x0) || (id <= *puVar3)) goto LAB_0002f4cd;
    i = i + 1;
  }
  puVar3 = (ushort *)0x0;
LAB_0002f4cd:
  iVar4 = FindHeapOf(mem);
  uVar2 = runtime::CurrentHeapToAllocateFrom;
  if (g_HeapTableBase[iVar4].heapHandle == (HANDLE)0x0) {
    pHVar5 = (HeapTableEntry *)0x0;
  }
  else {
    pHVar5 = g_HeapTableBase + iVar4;
  }
  runtime::CurrentHeapToAllocateFrom = iVar4;
  XAPILIB::HeapFree(pHVar5->heapHandle,0,mem);
  runtime::CurrentHeapToAllocateFrom = uVar2;
  if (puVar3 == (ushort *)0x0) {
    i = i + 1;
  }
  else if (*puVar3 == id) {
    return i;
  }
  ExtendBuffer2((Buffer **)bs,i);
  ExtendBuffer2((Buffer **)&bs->boneParentCallbacks,i);
  puVar5 = ExtendBuffer2((Buffer **)&bs->bone0x10s,i);
  puVar5->getTransform = (void *)0x0;
  puVar5->secondTransformCallback = (void *)0x0;
  puVar5->idk0x9ptr = (RigidBone *)0x0;
  *(undefined4 *)&puVar5->field_0xc = 0;
  bs->numBones = bs->numBones + 1;
  return i;
}




void BoneList::removeBoneById(uint16_t boneId,BoneList *param_2)

{
  Buffer<uint16_t> *pBVar1;
  Buffer<> *pBVar2;
  Buffer<Bone0x10> *pBVar3;
  undefined4 uVar4;
  int *mem;
  uint16_t *puVar5;
  int iVar6;
  uint32_t *__dest;
  void **__dest_00;
  HeapTableEntry *pHVar7;
  uint16_t *puVar8;
  uint32_t *puVar9;
  undefined1 *puVar10;
  uint uVar11;
  int i;
  
  mem = malloc_(4);
  *mem = 0;
  i = 0;
  while( true ) {
    pBVar1 = param_2->ids;
    puVar5 = (uint16_t *)((uint)pBVar1->valueSize * *mem + (int)pBVar1->head);
    if (((puVar5 == pBVar1->tail) || (*mem = *mem + 1, puVar5 == (uint16_t *)0x0)) ||
       (boneId == *puVar5)) break;
    i = i + 1;
  }
  iVar6 = FindHeapOf(mem);
  uVar4 = runtime::CurrentHeapToAllocateFrom;
  if (g_HeapTableBase[iVar6].heapHandle == (HANDLE)0x0) {
    pHVar7 = (HeapTableEntry *)0x0;
  }
  else {
    pHVar7 = g_HeapTableBase + iVar6;
  }
  runtime::CurrentHeapToAllocateFrom = iVar6;
  XAPILIB::HeapFree(pHVar7->heapHandle,0,mem);
  pBVar1 = param_2->ids;
  runtime::CurrentHeapToAllocateFrom = uVar4;
  param_2->numBones = param_2->numBones + -1;
  uVar11 = (uint)pBVar1->valueSize;
  puVar5 = (uint16_t *)(uVar11 * i + (int)pBVar1->head);
  puVar8 = (uint16_t *)((int)pBVar1->tail - uVar11);
  if (puVar5 < puVar8) {
    _memmove(puVar5,(void *)(uVar11 + (int)puVar5),(int)puVar8 - (int)puVar5);
  }
  pBVar1->tail = (uint16_t *)((int)pBVar1->tail - (uint)pBVar1->valueSize);
  pBVar2 = param_2->boneParentCallbacks;
  uVar11 = (uint)pBVar2->valueSize;
  __dest = (uint32_t *)(uVar11 * i + (int)pBVar2->head);
  puVar9 = (uint32_t *)((int)pBVar2->tail - uVar11);
  if (__dest < puVar9) {
    _memmove(__dest,(void *)(uVar11 + (int)__dest),(int)puVar9 - (int)__dest);
  }
  pBVar2->tail = (uint32_t *)((int)pBVar2->tail - (uint)pBVar2->valueSize);
  pBVar3 = param_2->bone0x10s;
  uVar11 = (uint)pBVar3->valueSize;
  __dest_00 = (void **)((int)&pBVar3->head->getTransform + uVar11 * i);
  puVar10 = (undefined1 *)((int)pBVar3->tail - uVar11);
  if (__dest_00 < puVar10) {
    _memmove(__dest_00,(void *)((int)__dest_00 + uVar11),(int)puVar10 - (int)__dest_00);
    pBVar3->tail = (Bone0x10 *)((int)pBVar3->tail - (uint)pBVar3->valueSize);
    return;
  }
  pBVar3->tail = (Bone0x10 *)((int)pBVar3->tail - (uint)pBVar3->valueSize);
  return;
}



void BoneList::getBoneTransform
               (AffineTransform *affine1,AffineTransform *affine2,AffineTransform *outAffine,
               ushort boneIndex,BoneList *this,float delta)

{
  int iVar1;
  uint16_t *puVar2;
  Bone0x10 *head_bone0x10;
  code *transform_cb;
  
  head_bone0x10 = this->bone0x10s->head;
  puVar2 = (uint16_t *)((uint)this->ids->valueSize * (uint)boneIndex + (int)this->ids->head);
  iVar1 = (uint)this->bone0x10s->valueSize * (uint)boneIndex;
  transform_cb = *(void **)((int)&head_bone0x10->getTransform + iVar1);
  if (transform_cb != (code *)0x0) {
                    // Goes to 0x2f060
    (*transform_cb)(affine1,affine2,outAffine,*puVar2,
                    *(RigidBone **)((int)&head_bone0x10->idk0x9ptr + iVar1),delta);
  }
  transform_cb = *(void **)((int)&head_bone0x10->secondTransformCallback + iVar1);
  if (transform_cb != (code *)0x0) {
    (*transform_cb)(affine1,affine2,outAffine,*puVar2,
                    *(undefined4 *)(&head_bone0x10->field_0xc + iVar1),delta);
  }
  return;
}




void WriteAffinesIntoBones(AffineTransform *affines,int numBones,ndSkeletonBone *bones)

{
  float fVar1;
  float fVar2;
  float *pfVar3;
  int iVar4;
  int i;
  
  i = 0;
  if (3 < numBones) {
    iVar4 = (numBones - 4U >> 2) + 1;
    i = iVar4 * 4;
    do {
      affines->m[0][3] =
           affines->m[0][3] -
           (affines->m[0][2] * (bones->globalTransform).z +
            (bones->globalTransform).y * affines->m[0][1] +
           (bones->globalTransform).x * affines->m[0][0]);
      affines->m[1][3] =
           affines->m[1][3] -
           (affines->m[1][1] * (bones->globalTransform).y +
            affines->m[1][0] * (bones->globalTransform).x +
           affines->m[1][2] * (bones->globalTransform).z);
      fVar1 = affines[1].m[0][1];
      affines->m[2][3] =
           affines->m[2][3] -
           (affines->m[2][1] * (bones->globalTransform).y +
            affines->m[2][0] * (bones->globalTransform).x +
           affines->m[2][2] * (bones->globalTransform).z);
      fVar2 = affines[1].m[1][1];
      affines[1].m[0][3] =
           affines[1].m[0][3] -
           (fVar1 * bones[1].globalTransform.y + affines[1].m[0][0] * bones[1].globalTransform.x +
           affines[1].m[0][2] * bones[1].globalTransform.z);
      fVar1 = affines[1].m[2][1];
      affines[1].m[1][3] =
           affines[1].m[1][3] -
           (fVar2 * bones[1].globalTransform.y + affines[1].m[1][0] * bones[1].globalTransform.x +
           affines[1].m[1][2] * bones[1].globalTransform.z);
      fVar2 = affines[2].m[0][2];
      affines[1].m[2][3] =
           affines[1].m[2][3] -
           (fVar1 * bones[1].globalTransform.y + affines[1].m[2][0] * bones[1].globalTransform.x +
           affines[1].m[2][2] * bones[1].globalTransform.z);
      fVar1 = affines[2].m[1][2];
      affines[2].m[0][3] =
           affines[2].m[0][3] -
           (fVar2 * bones[2].globalTransform.z + affines[2].m[0][1] * bones[2].globalTransform.y +
           affines[2].m[0][0] * bones[2].globalTransform.x);
      fVar2 = affines[2].m[2][2];
      affines[2].m[1][3] =
           affines[2].m[1][3] -
           (fVar1 * bones[2].globalTransform.z + affines[2].m[1][1] * bones[2].globalTransform.y +
           affines[2].m[1][0] * bones[2].globalTransform.x);
      fVar1 = affines[3].m[0][2];
      affines[2].m[2][3] =
           affines[2].m[2][3] -
           (fVar2 * bones[2].globalTransform.z + affines[2].m[2][1] * bones[2].globalTransform.y +
           affines[2].m[2][0] * bones[2].globalTransform.x);
      fVar2 = affines[3].m[1][2];
      affines[3].m[0][3] =
           affines[3].m[0][3] -
           (fVar1 * bones[3].globalTransform.z + affines[3].m[0][1] * bones[3].globalTransform.y +
           affines[3].m[0][0] * bones[3].globalTransform.x);
      fVar1 = affines[3].m[2][2];
      affines[3].m[1][3] =
           affines[3].m[1][3] -
           (fVar2 * bones[3].globalTransform.z + affines[3].m[1][1] * bones[3].globalTransform.y +
           affines[3].m[1][0] * bones[3].globalTransform.x);
      affines[3].m[2][3] =
           affines[3].m[2][3] -
           (fVar1 * bones[3].globalTransform.z + affines[3].m[2][1] * bones[3].globalTransform.y +
           affines[3].m[2][0] * bones[3].globalTransform.x);
      affines = affines + 4;
      bones = bones + 4;
      iVar4 = iVar4 + -1;
    } while (iVar4 != 0);
  }
  if (i < numBones) {
    pfVar3 = &(bones->globalTransform).y;
    i = numBones - i;
    do {
      fVar1 = affines->m[1][2];
      affines->m[0][3] =
           affines->m[0][3] -
           (affines->m[0][2] * pfVar3[1] + affines->m[0][0] * ((vec3 *)(pfVar3 + -1))->x +
           *pfVar3 * affines->m[0][1]);
      fVar2 = affines->m[2][2];
      affines->m[1][3] =
           affines->m[1][3] -
           (fVar1 * pfVar3[1] + affines->m[1][0] * ((vec3 *)(pfVar3 + -1))->x +
           affines->m[1][1] * *pfVar3);
      affines->m[2][3] =
           affines->m[2][3] -
           (fVar2 * pfVar3[1] + affines->m[2][0] * ((vec3 *)(pfVar3 + -1))->x +
           affines->m[2][1] * *pfVar3);
      affines = affines + 1;
      pfVar3 = pfVar3 + 8;
      i = i + -1;
    } while (i != 0);
  }
  return;
}



// WARNING: Unable to use type for symbol puVar9

void ApplyAnimToBones(AnimInstance *anim,void **callback,ushort *param_3,BoneList *boneData,
                     AffineTransform *outAffines,int num_bones,ndSkeletonBone *ndBones,float delta)

{
  ushort uVar1;
  uint uVar2;
  ndSkeletonBone *pnVar3;
  AffineTransform *startingAffine;
  ushort i;
  KFTransform_ptr_12_float btrans;
  int iVar4;
  float fVar5;
  float norm_factor;
  float fVar6;
  float fVar7;
  float fVar8;
  int local_74;
  uint j;
  ndSkeletonBone *nd_bone;
  AffineTransform rotmat;
  ushort *puVar9;
  AffineTransform *b_affine;
  CombinedAnimChannel *combined;
  ushort numBones;
  float qww;
  float qx;
  float qy;
  float qz;
  float x_scale;
  float y_scale;
  float z_scale;
  
  puVar9 = param_3;
  numBones = anim->animRes->numBones;
  combined = anim->finalCombinedChannel;
  i = 0;
  b_affine = outAffines;
  if (numBones == 0) {
    fVar7 = 1.0;
  }
  else {
    local_74 = 0;
    j = 0;
    nd_bone = ndBones;
    btrans = &combined->boneTransforms[0].rotQuat.z;
    do {
                    // Transform with quat to rotation matrix
      qww = (ADJ(btrans)->pos).x;
      fVar7 = 1.0;
      qx = ADJ(btrans).rotQuat.y;
      qy = ADJ(btrans).rotQuat.z;
      qz = ADJ(btrans).rotQuat.w;
      x_scale = (ADJ(btrans)->scale).y;
      y_scale = (ADJ(btrans)->scale).z;
      z_scale = btrans[7];
      if (qww == 1.0) {
        rotmat.m[0][0] = 1.0;
        rotmat.m[0][1] = 0.0;
        rotmat.m[0][2] = 0.0;
        rotmat.m[1][0] = 0.0;
        rotmat.m[1][1] = 1.0;
        rotmat.m[1][2] = 0.0;
        rotmat.m[2][0] = 0.0;
        rotmat.m[2][1] = 0.0;
        rotmat.m[2][2] = 1.0;
      }
      else {
        norm_factor = 2.0 / (qz * qz + qy * qy + qx * qx + qww * qww);
        fVar5 = qz * norm_factor;
        fVar8 = qy * norm_factor;
        fVar6 = qx * norm_factor * qww;
        norm_factor = qx * qx * norm_factor;
        rotmat.m[0][0] = 1.0 - (qz * fVar5 + qy * fVar8);
        rotmat.m[0][1] = fVar8 * qx - fVar5 * qww;
        rotmat.m[1][0] = fVar8 * qx + fVar5 * qww;
        rotmat.m[1][1] = 1.0 - (qz * fVar5 + norm_factor);
        rotmat.m[2][0] = fVar5 * qx - fVar8 * qww;
        rotmat.m[0][2] = fVar5 * qx + fVar8 * qww;
        rotmat.m[2][1] = qy * fVar5 + fVar6;
        rotmat.m[1][2] = qy * fVar5 - fVar6;
        rotmat.m[2][2] = 1.0 - (qy * fVar8 + norm_factor);
      }
      rotmat.m[0][3] = (nd_bone->bindTransform).x + (ADJ(btrans)->pos).y;
      rotmat.m[1][3] = (nd_bone->bindTransform).y + (ADJ(btrans)->pos).z;
      rotmat.m[2][3] = (nd_bone->bindTransform).z + (ADJ(btrans)->scale).x;
      if (x_scale != 1.0) {
        rotmat.m[0][0] = rotmat.m[0][0] * x_scale;
        rotmat.m[1][0] = rotmat.m[1][0] * x_scale;
        rotmat.m[2][0] = rotmat.m[2][0] * x_scale;
      }
      if (y_scale != 1.0) {
        rotmat.m[1][1] = rotmat.m[1][1] * y_scale;
        rotmat.m[0][1] = rotmat.m[0][1] * y_scale;
        rotmat.m[2][1] = rotmat.m[2][1] * y_scale;
      }
      if (z_scale != 1.0) {
        rotmat.m[0][2] = rotmat.m[0][2] * z_scale;
        rotmat.m[1][2] = rotmat.m[1][2] * z_scale;
        rotmat.m[2][2] = rotmat.m[2][2] * z_scale;
      }
      uVar1 = nd_bone->parentBone;
      if (uVar1 == 0xffff) {
        startingAffine = &AffineTransform::Identity;
      }
      else {
        if ((anim->tailDataPtr != (void *)0x0) &&
           ((*(byte *)((j >> 3) + (int)anim->tailDataPtr) >> ((byte)j & 7) & 1) != 0)) {
          qww = combined->boneTransforms[uVar1].scale.x;
          qx = combined->boneTransforms[uVar1].scale.y;
          qy = combined->boneTransforms[uVar1].scale.z;
          if (qww == 0.0) {
            qww = 0.0001;
          }
          if (qx == 0.0) {
            qx = 0.0001;
          }
          if (qy == 0.0) {
            qy = 0.0001;
          }
          qww = 1.0 / qww;
          rotmat.m[0][0] = qww * rotmat.m[0][0];
          rotmat.m[0][1] = qww * rotmat.m[0][1];
          qx = 1.0 / qx;
          rotmat.m[1][0] = qx * rotmat.m[1][0];
          rotmat.m[1][1] = qx * rotmat.m[1][1];
          qy = 1.0 / qy;
          rotmat.m[2][0] = qy * rotmat.m[2][0];
          rotmat.m[2][1] = qy * rotmat.m[2][1];
          rotmat.m[2][2] = qy * rotmat.m[2][2];
          rotmat.m[0][2] = qww * rotmat.m[0][2];
          rotmat.m[1][2] = qx * rotmat.m[1][2];
        }
        startingAffine = outAffines + uVar1;
      }
      if ((*param_3 == 0xffff) || (*param_3 != i)) {
        Graphics::leftCombineTransforms(b_affine,startingAffine,&rotmat);
      }
      else {
                    // Goes to 0x2f6a0 (BoneData::getBoneTransform)
        (**callback)(startingAffine,&rotmat,b_affine,local_74 >> 1,boneData,delta);
        fVar7 = 1.0;
        callback = callback + 1;
        param_3 = param_3 + 1;
        local_74 = local_74 + 2;
      }
      i = i + 1;
      j = j + 1;
      nd_bone = nd_bone + 1;
      btrans = btrans + 10;
      b_affine = b_affine + 1;
    } while (i < numBones);
  }
  uVar2 = (uint)i;
  if ((int)uVar2 < num_bones) {
    iVar4 = (int)param_3 - (int)puVar9;
    do {
      pnVar3 = ndBones + uVar2;
      rotmat.m[0][1] = 0.0;
      rotmat.m[0][2] = 0.0;
      rotmat.m[1][0] = 0.0;
      rotmat.m[1][2] = 0.0;
      rotmat.m[2][0] = 0.0;
      rotmat.m[2][1] = 0.0;
      rotmat.m[0][3] = (pnVar3->bindTransform).x;
      rotmat.m[1][3] = (pnVar3->bindTransform).y;
      rotmat.m[2][3] = (pnVar3->bindTransform).z;
      if (pnVar3->parentBone == 0xffff) {
        startingAffine = &AffineTransform::Identity;
      }
      else {
        startingAffine = outAffines + pnVar3->parentBone;
      }
      rotmat.m[0][0] = fVar7;
      rotmat.m[1][1] = fVar7;
      rotmat.m[2][2] = fVar7;
      if ((*param_3 == 0xffff) || (*param_3 != i)) {
        Graphics::leftCombineTransforms(b_affine,startingAffine,&rotmat);
      }
      else {
        (**callback)(startingAffine,&rotmat,b_affine,iVar4 >> 1,boneData,delta);
        fVar7 = 1.0;
        callback = callback + 1;
        param_3 = param_3 + 1;
        iVar4 = iVar4 + 2;
      }
      i = i + 1;
      uVar2 = (uint)i;
      b_affine = b_affine + 1;
    } while ((int)uVar2 < num_bones);
  }
  WriteAffinesIntoBones(outAffines,num_bones,ndBones);
  return;
}



// WARNING: Restarted to delay deadcode elimination for space: stack

void handleRootBoneAffines
               (AnimInstance *anim,AffineTransform *affines,int numBones,ndSkeletonBone *bones)

{
  vec3 *pvVar1;
  uint uVar2;
  ndSkeletonBone *bone;
  AffineTransform *affine;
  KFTransform_0xc kft_0x10;
  int i;
  float normalising_scale;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  float fVar10;
  float fVar11;
  uint local_4c;
  uint local_40;
  AffineTransform affine2;
  float sx;
  float sy;
  float sz;
  ushort animated_bones;
  CombinedAnimChannel *finalChannel;
  float new_w;
  float rx;
  float ry;
  float rz;
  
  rz = 1.0;
  fVar11 = 0.0;
  finalChannel = anim->finalCombinedChannel;
  animated_bones = anim->animRes->numBones;
  i = 0;
  affine = affines;
  uVar2 = i;
  if (animated_bones != 0) {
    ry = 0.0001;
    i = (int)animated_bones;
    local_4c = 0;
    kft_0x10 = &finalChannel->boneTransforms[0].rotQuat.w;
    bone = bones;
    fVar7 = rz;
    local_40 = i;
    do {
                    // Actually takes first float (w)
      new_w = ADJ(kft_0x10).rotQuat.w;
      affine2.m[0][2] = fVar11;
      affine2.m[1][2] = fVar11;
      rz = fVar7;
      affine2.m[0][0] = fVar7;
      affine2.m[0][1] = fVar11;
      affine2.m[1][0] = fVar11;
      affine2.m[1][1] = fVar7;
      affine2.m[2][0] = fVar11;
      affine2.m[2][1] = fVar11;
                    // If quaternion is not identity, write the rotations
      if (new_w != fVar7) {
        rx = ADJ(kft_0x10).rotQuat.x;
        rz = ADJ(kft_0x10).rotQuat.z;
        ry = ADJ(kft_0x10).rotQuat.y;
        normalising_scale = 2.0 / (new_w * new_w + rx * rx + rz * rz + ry * ry);
        new_w = ADJ(kft_0x10).rotQuat.z * normalising_scale;
        fVar8 = ADJ(kft_0x10).rotQuat.y * normalising_scale;
        fVar3 = ADJ(kft_0x10).rotQuat.w * rx * normalising_scale;
        fVar4 = ADJ(kft_0x10).rotQuat.w * fVar8;
        fVar5 = ADJ(kft_0x10).rotQuat.w * new_w;
        fVar6 = rx * rx * normalising_scale;
        rz = ADJ(kft_0x10).rotQuat.y * fVar8;
        fVar9 = ADJ(kft_0x10).rotQuat.y * new_w;
        fVar10 = ADJ(kft_0x10).rotQuat.z * new_w;
        affine2.m[0][0] = fVar7 - (fVar10 + rz);
        fVar7 = 1.0 - (rz + fVar6);
        ry = 0.0001;
        affine2.m[0][2] = rx * new_w + fVar4;
        affine2.m[1][2] = fVar9 - fVar3;
        rz = 1.0;
        affine2.m[0][1] = rx * fVar8 - fVar5;
        affine2.m[1][0] = rx * fVar8 + fVar5;
        affine2.m[1][1] = 1.0 - (fVar10 + fVar6);
        affine2.m[2][0] = rx * new_w - fVar4;
        affine2.m[2][1] = fVar9 + fVar3;
      }
      affine2.m[0][3] = (ADJ(kft_0x10)->pos).x + (bone->bindTransform).x;
      affine2.m[1][3] = (ADJ(kft_0x10)->pos).y + (bone->bindTransform).y;
      affine2.m[2][3] = (ADJ(kft_0x10)->pos).z + (bone->bindTransform).z;
      sx = (ADJ(kft_0x10)->scale).x;
      if (sx != rz) {
        affine2.m[0][0] = sx * affine2.m[0][0];
        affine2.m[1][0] = (ADJ(kft_0x10)->scale).x * affine2.m[1][0];
        affine2.m[2][0] = (ADJ(kft_0x10)->scale).x * affine2.m[2][0];
      }
      sy = (ADJ(kft_0x10)->scale).y;
      if (sy != rz) {
        affine2.m[0][1] = sy * affine2.m[0][1];
        affine2.m[1][1] = (ADJ(kft_0x10)->scale).y * affine2.m[1][1];
        affine2.m[2][1] = (ADJ(kft_0x10)->scale).y * affine2.m[2][1];
      }
      sz = (ADJ(kft_0x10)->scale).z;
      if (sz != rz) {
        affine2.m[0][2] = sz * affine2.m[0][2];
        affine2.m[1][2] = (ADJ(kft_0x10)->scale).z * affine2.m[1][2];
        fVar7 = (ADJ(kft_0x10)->scale).z * fVar7;
      }
      animated_bones = bone->parentBone;
      affine2.m[2][2] = fVar7;
      if (animated_bones == 0xffff) {
        affine->m[0][0] = affine2.m[0][0];
        affine->m[0][1] = affine2.m[0][1];
        affine->m[0][2] = affine2.m[0][2];
        affine->m[0][3] = affine2.m[0][3];
        affine->m[1][0] = affine2.m[1][0];
        affine->m[1][1] = affine2.m[1][1];
        affine->m[1][2] = affine2.m[1][2];
        affine->m[1][3] = affine2.m[1][3];
        affine->m[2][0] = affine2.m[2][0];
        affine->m[2][1] = affine2.m[2][1];
        affine->m[2][2] = fVar7;
        affine->m[2][3] = affine2.m[2][3];
      }
      else {
        if ((anim->tailDataPtr != (void *)0x0) &&
           ((*(byte *)((local_4c >> 3) + (int)anim->tailDataPtr) >> ((byte)local_4c & 7) & 1) != 0))
        {
          pvVar1 = &finalChannel->boneTransforms[animated_bones].scale;
          if (finalChannel->boneTransforms[animated_bones].scale.x == fVar11) {
            pvVar1->x = ry;
          }
          if (pvVar1->y == fVar11) {
            pvVar1->y = ry;
          }
          if (pvVar1->z == fVar11) {
            pvVar1->z = ry;
          }
          if (pvVar1->x != rz) {
            ry = rz / pvVar1->x;
            affine2.m[0][0] = ry * affine2.m[0][0];
            affine2.m[0][1] = ry * affine2.m[0][1];
            affine2.m[0][2] = ry * affine2.m[0][2];
            ry = 0.0001;
          }
          if (pvVar1->y != rz) {
            new_w = rz / pvVar1->y;
            affine2.m[1][0] = new_w * affine2.m[1][0];
            affine2.m[1][1] = new_w * affine2.m[1][1];
            affine2.m[1][2] = new_w * affine2.m[1][2];
          }
          if (pvVar1->z != rz) {
            affine2.m[2][2] = rz / pvVar1->z;
            affine2.m[2][0] = affine2.m[2][2] * affine2.m[2][0];
            affine2.m[2][1] = affine2.m[2][2] * affine2.m[2][1];
            affine2.m[2][2] = affine2.m[2][2] * fVar7;
          }
        }
        Graphics::leftCombineTransforms(affine,affines + bone->parentBone,&affine2);
      }
      local_4c = local_4c + 1;
      bone = bone + 1;
      affine = affine + 1;
                    // Next KFTransform
      kft_0x10 = kft_0x10 + 10;
      local_40 = local_40 - 1;
      fVar7 = rz;
      uVar2 = i;
    } while (local_40 != 0);
  }
  while (i < numBones) {
    bone = bones + i;
                    // If no parent
    if (bone->parentBone == 0xffff) {
      fVar7 = (bone->bindTransform).z;
      ry = (bone->bindTransform).y;
      new_w = (bone->bindTransform).x;
      affine->m[0][0] = rz;
      affine->m[0][1] = fVar11;
      affine->m[0][2] = fVar11;
      affine->m[0][3] = new_w;
      affine->m[1][0] = fVar11;
      affine->m[1][1] = rz;
      affine->m[1][2] = fVar11;
      affine->m[1][3] = ry;
      affine->m[2][0] = fVar11;
      affine->m[2][1] = fVar11;
      affine->m[2][2] = rz;
      affine->m[2][3] = fVar7;
    }
    else {
      affine2.m[0][3] = (bone->bindTransform).x;
      affine2.m[1][3] = (bone->bindTransform).y;
      affine2.m[2][3] = (bone->bindTransform).z;
      affine2.m[0][0] = rz;
      affine2.m[0][1] = fVar11;
      affine2.m[0][2] = fVar11;
      affine2.m[1][0] = fVar11;
      affine2.m[1][1] = rz;
      affine2.m[1][2] = fVar11;
      affine2.m[2][0] = fVar11;
      affine2.m[2][1] = fVar11;
      affine2.m[2][2] = rz;
      Graphics::leftCombineTransforms(affine,affines + bone->parentBone,&affine2);
    }
    i = uVar2 + 1 & 0xffff;
    affine = affine + 1;
    uVar2 = uVar2 + 1;
  }
  WriteAffinesIntoBones(affines,numBones,bones);
  return;
}




KeyframeContext * KeyframeContext::ctor(uint numChannels)

{
  KeyframeContext *kfc;
  uint kfc_size;
  int iVar3;
  KeyframeContext *pKVar4;
  
  kfc_size = numChannels * 0x28 + 0x68;
  kfc = malloc_(kfc_size);
  pKVar4 = kfc;
  for (kfc_size = kfc_size >> 2; kfc_size != 0; kfc_size = kfc_size - 1) {
    pKVar4->animEventCallback = (TriggerAnimationEventCallback *)0x0;
    pKVar4 = (KeyframeContext *)&pKVar4->avatar;
  }
  for (iVar3 = 0; iVar3 != 0; iVar3 = iVar3 + -1) {
    *(undefined1 *)&pKVar4->animEventCallback = 0;
    pKVar4 = (KeyframeContext *)((int)&pKVar4->animEventCallback + 1);
  }
  kfc->kfcAnims = kfc->_channelsData;
  kfc->kfHeaderPtr = &kfc->_kfHeader;
  kfc->numAnimations = (ushort)numChannels;
  kfc->free = 1;
  (kfc->_kfHeader).floatSet.pos.z = 0.0;
  (kfc->_kfHeader).floatSet.pos.y = 0.0;
  (kfc->_kfHeader).floatSet.pos.x = 0.0;
  (kfc->_kfHeader).floatSet.rotQuat.x = 0.0;
  (kfc->_kfHeader).floatSet.rotQuat.y = 0.0;
  (kfc->_kfHeader).floatSet.rotQuat.z = 0.0;
  (kfc->_kfHeader).floatSet.rotQuat.w = 1.0;
  return kfc;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void KeyFrameContext::dtor(KeyframeContext *kfc,int param_2)

{
  CombinedAnimChannel *mem;
  undefined4 uVar1;
  int iVar2;
  HeapTableEntry *pHVar3;
  uint i;
  
  i = 0;
  if (kfc->numAnimations != 0) {
    do {
      KeyframeContext::deleteAnimationByIndex(param_2,i,kfc);
      i = i + 1;
    } while (i < kfc->numAnimations);
  }
  mem = (kfc->instanceHeader).finalCombinedChannel;
  if (mem != (CombinedAnimChannel *)0x0) {
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
  }
  (kfc->instanceHeader).finalCombinedChannel = (CombinedAnimChannel *)0x0;
  iVar2 = FindHeapOf(kfc);
  uVar1 = runtime::CurrentHeapToAllocateFrom;
  if (g_HeapTableBase[iVar2].heapHandle == (HANDLE)0x0) {
    pHVar3 = (HeapTableEntry *)0x0;
  }
  else {
    pHVar3 = g_HeapTableBase + iVar2;
  }
  runtime::CurrentHeapToAllocateFrom = iVar2;
  XAPILIB::HeapFree(pHVar3->heapHandle,0,kfc);
  runtime::CurrentHeapToAllocateFrom = uVar1;
  return;
}



// WARNING: Unable to use type for symbol pKVar1
// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields

BOOL KeyframeContext::setFromAnimName
               (KeyframeContext *kfc,uint animIndex,KFCParams *kfcParams,char *animAID,
               AnimResource *param_5)

{
  uint offset;
  AnimInstance *allocd;
  int iVar1;
  AnimInstance *extraout_EAX;
  KFCAnimation *kf_value;
  KFCAnimation *channel;
  float10 fVar2;
  float playbackSpeed_;
  ushort local_14;
  char fStack_c;
  float someFloat;
  KFCParams *pKVar1;
  AnimEventResource *anim_event_res;
  KFCParams *kfc_params;
  bool playbackSpeedOver0;
  
  kfc_params = kfcParams;
  pKVar1 = (KFCParams *)kfcParams->someFloat;
  playbackSpeed_ = kfcParams->playbackSpeed_;
  playbackSpeedOver0 = kfcParams->playbackSpeed_ <= 0.0 && kfcParams->playbackSpeed_ != 0.0;
  local_14 = (ushort)playbackSpeedOver0;
  fStack_c = (char)kfcParams->someUshort;
  offset = animIndex * 0x28;
  anim_event_res = kfc->kfcAnims[animIndex].animEventsRes;
  channel = kfc->kfcAnims + animIndex;
                    // Clear resource if the kfc is being reused
  if (anim_event_res != (AnimEventResource *)0x0) {
    if (channel->animInstance->numTicks != 0) {
      Animation::PreDispatchAnimEvents
                (anim_event_res,channel->animInstance,kfc->animEventCallback,animIndex,kfc->avatar);
    }
    if (channel->hasEvent == 0) {
      Assets::DestroyAssetOrDecrement(channel->animEventsRes);
    }
    channel->animEventsRes = (AnimEventResource *)0x0;
    channel->hasEvent = 0;
  }
  if (channel->animInstance == (AnimInstance *)0x0) {
    allocd = AnimInstance::ctor();
    channel->animInstance = allocd;
    channel->progress = 0.0;
  }
  channel->playbackType = Normal;
  if ((float)pKVar1 == -1.0) {
    kfcParams = (KFCParams *)channel->animInstance->t;
  }
  else {
    kfcParams = pKVar1;
    if ((float)pKVar1 == -2.0) {
                    // Update the global seed
      runtime::rand = runtime::rand * 0x19660d + 0x3c6ef35f;
                    // Random value from [0,1]
      kfcParams = (KFCParams *)((float)(runtime::rand & 0x7fffff | 0x3f800000) - 1.0);
    }
  }
  channel->animInstance->timeRemaining2 = kfc_params->someFloat2;
  if (animAID == (char *)0x0) {
    fVar2 = abs_float(playbackSpeed_);
    iVar1 = AnimInstance::loadAnimFromExistingResource
                      (param_5,channel->animInstance,(float)kfcParams,(float)fVar2,fStack_c,
                       (ushort)playbackSpeedOver0,(char *)0x0);
  }
  else {
    fVar2 = abs_float(playbackSpeed_);
    iVar1 = AnimInstance::loadAnimFromNewResource
                      (channel->animInstance,(float)kfcParams,(float)fVar2,fStack_c,local_14,animAID
                      );
  }
  if (iVar1 == 0) {
    if (animIndex != 0) {
      anim_event_res = kfc->kfcAnims[animIndex].animEventsRes;
      kf_value = kfc->kfcAnims + animIndex;
                    // Delete existing event
      if (anim_event_res != (AnimEventResource *)0x0) {
        if (kf_value->hasEvent == 0) {
          offset = Assets::DestroyAssetOrDecrement(anim_event_res);
        }
        kf_value->animEventsRes = (AnimEventResource *)0x0;
                    // Cleanup
        kf_value->hasEvent = 0;
      }
      if (kf_value->animInstance != (AnimInstance *)0x0) {
        AnimInstance::dtor((void *)offset,kf_value->animInstance);
        kf_value->animInstance = extraout_EAX;
      }
      kf_value->progress = 0.0;
      kf_value->playbackType = StoppedOrInvalid;
      kfc->free = 1;
    }
    return 0;
  }
  if (kfc_params->someFloat3 == -10.0) {
    playbackSpeed_ = 1.0;
    if (kfc_params->someIdOrCount == 0x21) {
      playbackSpeed_ = 0.5;
    }
    channel->playbackSpeed_ = playbackSpeed_;
  }
  if (kfc_params->length == 0.0) {
    channel->playbackType = StoppedOrInvalid;
    channel->progress = 1.0;
  }
  channel->length = kfc_params->length;
  channel->someIdOrCount = kfc_params->someIdOrCount;
  channel->someValue4 = kfc_params->someValue4;
  channel->someValue5 = (uint32_t)kfc_params->someValue5;
  anim_event_res = kfc_params->animEvent;
  if (anim_event_res == (AnimEventResource *)0x0) {
    if (*(int *)kfc_params->animEventAID != 0x5f646961) goto LAB_00030af6;
    anim_event_res = Assets::GetResourceBytesOrExit(kfc_params->animEventAID);
  }
  else {
    channel->hasEvent = 1;
  }
  channel->animEventsRes = anim_event_res;
LAB_00030af6:
  kfc->free = 1;
  return iVar1;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields

void KeyframeContext::setAnim
               (KeyframeContext *kfc,KFCParams *params,uint channelIndex,char *param_4)

{
  if (params->animResource != (AnimResource *)0x0) {
    setFromAnimName(kfc,channelIndex,params,(char *)0x0,params->animResource);
    return;
  }
  setFromAnimName(kfc,channelIndex,params,param_4,(AnimResource *)0x0);
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


BOOL KeyframeContext::hasValAtIndexInAnyChannel(KeyframeContext *kfc,int index)

{
  uint uVar1;
  KFCAnimation *channel;
  AnimResource *anim_res;
  uint32_t *somePtr;
  
  uVar1 = 0;
  if (kfc->numAnimations != 0) {
    channel = kfc->kfcAnims;
    do {
      if ((((channel->animInstance != (AnimInstance *)0x0) &&
           (anim_res = channel->animInstance->animRes, anim_res != (AnimResource *)0x0)) &&
          (somePtr = anim_res->somePtrList, somePtr != (uint32_t *)0x0)) && (somePtr[index] != 0)) {
        return 1;
      }
      uVar1 = uVar1 + 1;
      channel = channel + 1;
    } while (uVar1 < kfc->numAnimations);
  }
  return 0;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields

BOOL KeyframeContext::updateFromAvatar
               (KeyframeContext *kfc,Model *instance,BOOL preventChannelAdvancing,float delta)

{
  BOOL BVar1;
  KFCAnimation *kfc_anim;
  int numAnimationsFinished;
  uint i;
  
  (kfc->_kfHeader).floatSet.pos.z = 0.0;
  (kfc->_kfHeader).floatSet.pos.y = 0.0;
  (kfc->_kfHeader).floatSet.pos.x = 0.0;
  (kfc->_kfHeader).floatSet.rotQuat.x = 0.0;
  (kfc->_kfHeader).floatSet.rotQuat.y = 0.0;
  (kfc->_kfHeader).floatSet.rotQuat.z = 0.0;
  (kfc->_kfHeader).floatSet.rotQuat.w = 1.0;
  i = 0;
  if (kfc->numAnimations != 0) {
                    // Find first non null animation slot
    kfc_anim = kfc->kfcAnims;
    do {
      if ((kfc_anim->animInstance != (AnimInstance *)0x0) &&
         (kfc_anim->animInstance->restartAnimation == '\0')) goto UpdateChannels;
      i = i + 1;
      kfc_anim = kfc_anim + 1;
    } while (i < kfc->numAnimations);
  }
  if (kfc->free == 0) {
    kfc->skipUpdate = 1;
    return 0;
  }
UpdateChannels:
  numAnimationsFinished = 0;
  i = 0;
  kfc->skipUpdate = 0;
  if (kfc->numAnimations != 0) {
    do {
      BVar1 = updateAnimation(kfc,i,delta,preventChannelAdvancing);
      numAnimationsFinished = numAnimationsFinished + BVar1;
      i = i + 1;
    } while (i < kfc->numAnimations);
    if ((numAnimationsFinished != 0) && (preventChannelAdvancing == 0)) {
                    // This is bad case
      collapseChannelsIntoCombined(kfc);
    }
  }
  return 1;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields

void KeyframeContext::updateSkeletonAndBlendTargets
               (BOOL skipUpdate,KeyframeContext *kfc,Model *instance,BoneList *boneList)

{
  uint num_bones;
  Skeleton *skelly;
  astruct_58 *pKVar1;
  float delta;
  AS58Entry *entry;
  uint32_t *iVar1;
  AnimInstance *pose;
  ndSkeleton *skel;
  
  if ((skipUpdate == 0) && (kfc->skipUpdate == 0)) {
    pose = kfc->kfcAnims->animInstance;
                    // Reset skeleton
    if (pose == (AnimInstance *)0x0) {
      (kfc->_kfHeader).floatSet.pos.z = 0.0;
      (kfc->_kfHeader).floatSet.pos.y = 0.0;
      (kfc->_kfHeader).floatSet.pos.x = 0.0;
      (kfc->_kfHeader).floatSet.rotQuat.x = 0.0;
      (kfc->_kfHeader).floatSet.rotQuat.y = 0.0;
      (kfc->_kfHeader).floatSet.rotQuat.z = 0.0;
      (kfc->_kfHeader).floatSet.rotQuat.w = 1.0;
                    // Reset all bones to identity matrix
      ModelInstance::setAllBoneAffines(&AffineTransform::Identity,instance);
      ModelInstance::clearBlendTargets(instance);
    }
    else {
      skelly = instance->skeleton;
      if (skelly == (Skeleton *)0x0) {
        skelly = instance->skeleton2;
      }
      if (skelly != (Skeleton *)0x0) {
        delta = pose->delta;
        skel = instance->ndSkeleton;
        num_bones = ModelInstance::numBones(instance);
        UpdateBoneAffines((kfc->_kfHeader).restAnimInstance,delta,boneList,skel->bonesStart,
                          num_bones,skelly->boneAffines);
        skelly->ignoresGlobalBone = 1;
      }
      pKVar1 = (astruct_58 *)((kfc->_kfHeader).restAnimInstance)->finalCombinedChannel;
      entry = (AS58Entry *)(&pKVar1->entries[0].field0_0x0 + pKVar1->currentEntry * 10);
                    // Updates blend targets
      ModelInstance::setBlendTargetWeights(instance,(BlendTargetWeights *)entry);
      iVar1 = ((kfc->_kfHeader).restAnimInstance)->animRes->somePtrList;
      if ((iVar1 != (uint32_t *)0x0) && (iVar1[0x30] != 0)) {
        FUN_000320f0(entry,instance);
        kfc->free = 0;
        return;
      }
    }
    kfc->free = 0;
  }
  return;
}




void KeyframeContext::collapseChannelsIntoCombined(KeyframeContext *kfc)

{
  KFCAnimation *channel_l;
  CombinedAnimChannel *combined;
  uint minChannels;
  int sizeof_KFCAnimation_;
  uint num_channels;
  float playbackSpeed;
  KFCAnimation *channel_r;
  AnimInstance *instance;
  
  instance = kfc->kfcAnims->animInstance;
  if (instance != (AnimInstance *)0x0) {
    playbackSpeed = 1.0;
    if (instance->invDuration <= 0.0 && instance->invDuration != 0.0) {
      playbackSpeed = -1.0;
    }
    AnimInstanceHeader::initialiseFromAnimResource
              (1.0,playbackSpeed,instance->loopMode,0,instance->animResource,&kfc->instanceHeader);
    num_channels = (uint)instance->animRes->numBones;
    if (1 < kfc->numAnimations) {
      channel_l = kfc->kfcAnims;
      sizeof_KFCAnimation_ = kfc->numAnimations - 1;
      do {
        channel_l = channel_l + 1;
        if ((channel_l->animInstance != (AnimInstance *)0x0) &&
           (minChannels = (uint)channel_l->animInstance->animRes->numBones,
           num_channels < minChannels)) {
          num_channels = minChannels;
        }
        sizeof_KFCAnimation_ = sizeof_KFCAnimation_ + -1;
      } while (sizeof_KFCAnimation_ != 0);
    }
    if (kfc->numCombinedChannels < num_channels) {
      combined = (kfc->instanceHeader).finalCombinedChannel;
      if (combined == (CombinedAnimChannel *)0x0) {
        combined = malloc_(num_channels * 0x28 + 0x104);
      }
      else {
        combined = (CombinedAnimChannel *)
                   AllocateMoreAStruct_33(num_channels * 0x28 + 0x104,combined);
      }
      combined->numTransforms = num_channels;
      KeyframeAllocdValue::initialise(combined);
      (kfc->instanceHeader).finalCombinedChannel = combined;
      kfc->numCombinedChannels = (ushort)num_channels;
    }
    (kfc->_kfHeader).restAnimInstance = instance;
    kfc->kfHeaderPtr = (KeyframeHeader *)&instance->kft2_1;
    num_channels = 1;
    if (1 < kfc->numAnimations) {
                    // Reduce all of the channels into a single value
      sizeof_KFCAnimation_ = 0x28;
      do {
        channel_l = kfc->kfcAnims;
        channel_r = *(KFCAnimation **)((int)&channel_l->animInstance + sizeof_KFCAnimation_);
        if (channel_r != (KFCAnimation *)0x0) {
          CombineAnimChannels((kfc->_kfHeader).restAnimInstance,channel_r,&channel_r[4].playbackType
                              ,*(float *)((int)&channel_l->playbackSpeed_ + sizeof_KFCAnimation_) *
                               *(float *)((int)&channel_l->progress + sizeof_KFCAnimation_),
                              (kfc->instanceHeader).finalCombinedChannel,
                              *(uint32_t *)((int)&channel_l->someIdOrCount + sizeof_KFCAnimation_),
                              &kfc->_kfHeader,kfc->kfHeaderPtr);
          (kfc->_kfHeader).restAnimInstance = (AnimInstance *)&kfc->instanceHeader;
          kfc->kfHeaderPtr = &kfc->_kfHeader;
        }
        num_channels = num_channels + 1;
        sizeof_KFCAnimation_ = sizeof_KFCAnimation_ + 0x28;
      } while (num_channels < kfc->numAnimations);
    }
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void KeyframeContext::deleteAnimationByIndex(int param_1,uint channelIndex,KeyframeContext *kfc)

{
  AnimInstance *extraout_EAX;
  AnimEventResource *extraout_ECX;
  AnimEventResource *animEventRes;
  KFCAnimation *channel;
  
  channel = kfc->kfcAnims + channelIndex;
  animEventRes = channel->animEventsRes;
  if (animEventRes != (AnimEventResource *)0x0) {
    if ((param_1 != 0) && (channel->animInstance->numTicks != 0)) {
      Animation::PreDispatchAnimEvents
                (animEventRes,channel->animInstance,kfc->animEventCallback,channelIndex,kfc->avatar)
      ;
      animEventRes = extraout_ECX;
    }
    if (channel->hasEvent == 0) {
      animEventRes = (AnimEventResource *)Assets::DestroyAssetOrDecrement(channel->animEventsRes);
    }
    channel->animEventsRes = (AnimEventResource *)0x0;
    channel->hasEvent = 0;
  }
  if (channel->animInstance != (AnimInstance *)0x0) {
    AnimInstance::dtor(animEventRes,channel->animInstance);
    channel->animInstance = extraout_EAX;
  }
  channel->progress = 0.0;
  channel->playbackType = StoppedOrInvalid;
  kfc->free = 1;
  return;
}




AffineTransform * SetGlobalAffineFromBone(Skeleton *skeleton,int index)

{
  if (skeleton->ignoresGlobalBone != 0) {
    return skeleton->boneAffines + index;
  }
  SomeSkeletonAffineTransform.m[0][0] = skeleton[index].boneAffines[0].m[0][0];
  SomeSkeletonAffineTransform.m[0][1] = skeleton[index].boneAffines[0].m[1][0];
  SomeSkeletonAffineTransform.m[0][2] = skeleton[index].boneAffines[0].m[2][0];
  SomeSkeletonAffineTransform.m[0][3] = (float)skeleton[index + 1].numBones;
  SomeSkeletonAffineTransform.m[1][0] = skeleton[index].boneAffines[0].m[0][1];
  SomeSkeletonAffineTransform.m[1][1] = skeleton[index].boneAffines[0].m[1][1];
  SomeSkeletonAffineTransform.m[1][2] = skeleton[index].boneAffines[0].m[2][1];
  SomeSkeletonAffineTransform.m[1][3] = (float)skeleton[index + 1].ignoresGlobalBone;
  SomeSkeletonAffineTransform.m[2][0] = skeleton[index].boneAffines[0].m[0][2];
  SomeSkeletonAffineTransform.m[2][1] = skeleton[index].boneAffines[0].m[1][2];
  SomeSkeletonAffineTransform.m[2][2] = skeleton[index].boneAffines[0].m[2][2];
  SomeSkeletonAffineTransform.m[2][3] = *(float *)&skeleton[index + 1].field_0x8;
  return &SomeSkeletonAffineTransform;
}




AffineTransform * FUN_000316b0(float *param_1,int param_2,int param_3,int param_4)

{
  float fVar1;
  float fVar2;
  float fVar3;
  WeirdTransform *pWVar4;
  AffineTransform *m2;
  
  graphics::bone_acc = (WeirdTransform *)&g_affine;
  g_affine.m[0][0] = *param_1;
  g_affine.m[0][1] = param_1[1];
  g_affine.m[0][2] = param_1[2];
  g_affine.m[0][3] = param_1[3];
  g_affine.m[1][0] = param_1[4];
  g_affine.m[1][1] = param_1[5];
  g_affine.m[1][2] = param_1[6];
  g_affine.m[1][3] = param_1[7];
  g_affine.m[2][0] = param_1[8];
  g_affine.m[2][1] = param_1[9];
  g_affine.m[2][2] = param_1[10];
  g_affine.m[2][3] = param_1[0xb];
  m2 = Skeleton::getBoneAffineIntoGlobal((Skeleton *)param_4,param_3);
  Graphics::leftCombineTransforms(&graphics::bone_acc->affine1,&graphics::bone_acc->affine1,m2);
  pWVar4 = graphics::bone_acc;
  fVar1 = *(float *)(param_2 + 0x18);
  fVar2 = *(float *)(param_2 + 0x14);
  fVar3 = *(float *)(param_2 + 0x10);
  (graphics::bone_acc->affine2).m[0][0] = 1.0;
  (pWVar4->affine2).m[0][1] = 0.0;
  (pWVar4->affine2).m[0][2] = 0.0;
  (pWVar4->affine2).m[0][3] = fVar3;
  (pWVar4->affine2).m[1][0] = 0.0;
  (pWVar4->affine2).m[1][1] = 1.0;
  (pWVar4->affine2).m[1][2] = 0.0;
  (pWVar4->affine2).m[1][3] = fVar2;
  (pWVar4->affine2).m[2][0] = 0.0;
  (pWVar4->affine2).m[2][1] = 0.0;
  (pWVar4->affine2).m[2][2] = 1.0;
  (pWVar4->affine2).m[2][3] = fVar1;
  Graphics::leftCombineTransforms
            (&graphics::bone_acc->affine1,&graphics::bone_acc->affine1,&graphics::bone_acc->affine2)
  ;
  return &graphics::bone_acc->affine1;
}



// WARNING: Unable to use type for symbol pKVar1


void AnimInstanceHeader::updateFaceAndEvents(AnimInstance *header)

{
  float fVar1;
  float fVar2;
  float fVar3;
  uint32_t *puVar4;
  int iVar5;
  KFTransform *pKVar6;
  uint uVar7;
  uint uVar8;
  uint uVar9;
  uint uVar10;
  uint uVar11;
  bool bVar12;
  float10 fVar13;
  float fVar14;
  float fVar15;
  float fVar16;
  uint64_t uVar17;
  int i;
  KFTransform *pKVar1;
  
  puVar4 = header->animRes->somePtrList;
  pKVar1 = header->finalCombinedChannel->boneTransforms +
           header->finalCombinedChannel->numTransforms;
                    // 48 floats
  i = 0x30;
  pKVar6 = pKVar1;
  do {
                    // This is going to write into an AnimResource?
    if ((puVar4 == (uint32_t *)0x0) ||
       (iVar5 = *(int *)((int)puVar4 + ((int)pKVar6 - (int)pKVar1)), iVar5 == 0)) {
      fVar15 = 0.0;
    }
    else {
      uVar11 = header->animRes->field12_0x24;
      bVar12 = header->loopMode != 0;
      if (bVar12) {
        uVar11 = uVar11 - 1;
      }
      fVar14 = (float)(int)uVar11 * header->t;
      fVar13 = (float10)fVar14;
      if (bVar12) {
        uVar17 = float10::to_uint64_t(fVar13);
        uVar8 = (uint)uVar17;
        uVar7 = uVar8 & 0xffff;
        uVar10 = uVar8 - ((short)uVar17 != 0);
        uVar8 = (uVar7 != uVar11) + uVar8;
        uVar9 = ((uVar8 & 0xffff) != uVar11) + uVar8;
      }
      else {
        uVar17 = float10::to_uint64_t(fVar13);
        uVar7 = (uint)((longlong)(ulonglong)((uint)uVar17 & 0xffff) % (longlong)(int)uVar11) &
                0xffff;
        uVar8 = (uint)((longlong)(ulonglong)(uVar7 + 1) % (longlong)(int)uVar11);
        uVar9 = (uint)((longlong)(ulonglong)(uVar7 + 2) % (longlong)(int)uVar11);
        uVar10 = (int)((uVar7 - 1) + uVar11) % (int)uVar11;
      }
      fVar15 = *(float *)(iVar5 + uVar7 * 4);
      fVar1 = *(float *)(iVar5 + (uVar9 & 0xffff) * 4);
      fVar2 = *(float *)(iVar5 + (uVar8 & 0xffff) * 4);
      fVar14 = fVar14 - (float)uVar7;
      fVar3 = *(float *)(iVar5 + (uVar10 & 0xffff) * 4);
      fVar16 = fVar2 - fVar15;
      fVar15 = ((((fVar16 * 2.0 + fVar3) - (fVar1 + fVar15) * 0.5) +
                (((fVar1 - fVar3) - fVar16) * 0.5 - fVar16) * fVar14) * fVar14 +
               (fVar2 - fVar3) * 0.5) * fVar14 + fVar15;
    }
    (pKVar6->rotQuat).x = fVar15;
    pKVar6 = (KFTransform *)&(pKVar6->rotQuat).y;
    i = i + -1;
  } while (i != 0);
  if ((puVar4 != (uint32_t *)0x0) && (puVar4[0x30] != 0)) {
    pKVar1[4].scale.y =
         *(float *)(puVar4[0x30] +
                   (int)((float)(int)(header->animRes->field12_0x24 - 1) * header->t) * 4);
    return;
  }
  pKVar1[4].scale.y = 0.0;
  return;
}




AnimTableResource::getEventMappingBySomething(AnimtableResource *param_1,char *param_2)

{
  AnimtableEntry *animtable_entry;
  AnimEventMapping *pAVar1;
  
  animtable_entry = AnimtableResource::getEntry(param_1,param_2);
  if (animtable_entry != (AnimtableEntry *)0x0) {
    pAVar1 = AnimtableResource::getEventMapping(param_1,animtable_entry->field1_0x4);
    return pAVar1;
  }
  pAVar1 = AnimtableResource::getEventMapping(param_1,param_2);
  return pAVar1;
}




AnimEventMapping * AnimtableResource::getEventMapping(AnimtableResource *res,char *name)

{
  int iVar1;
  byte *pbVar2;
  byte bVar3;
  byte bVar4;
  int max_i;
  int index;
  int iVar5;
  
  max_i = res->numEntries - 1;
  iVar1 = 0;
  if (-1 < max_i) {
    do {
      index = iVar1 + max_i >> 1;
      pbVar2 = (byte *)res->mappings[index].triggeringName;
      bVar3 = *pbVar2;
      bVar4 = *name;
      if (bVar3 == *name) {
        iVar5 = (int)name - (int)pbVar2;
        do {
          pbVar2 = pbVar2 + 1;
          if (bVar3 == 0) goto LAB_000321f8;
          bVar3 = *pbVar2;
          bVar4 = pbVar2[iVar5];
        } while (bVar3 == bVar4);
      }
      iVar5 = (uint)bVar3 - (uint)bVar4;
      if (iVar5 < 0) {
        iVar1 = index + 1;
      }
      else {
        if ((uint)bVar3 == (uint)bVar4 || iVar5 < 0) {
LAB_000321f8:
          return res->mappings + index;
        }
        max_i = index + -1;
      }
    } while (iVar1 <= max_i);
  }
  return (AnimEventMapping *)0x0;
}



// Binary search by name


AnimtableEntry * AnimtableResource::getEntry(AnimtableResource *param_1,char *name)

{
  byte *pbVar1;
  byte bVar2;
  byte bVar3;
  int i;
  int max_i;
  int iVar4;
  int iVar5;
  
  max_i = param_1->numAnims - 1;
  i = 0;
  if (-1 < max_i) {
    do {
      iVar4 = i + max_i >> 1;
      pbVar1 = (byte *)param_1->entries[iVar4].field0_0x0;
      bVar2 = *pbVar1;
      bVar3 = *name;
      if (bVar2 == *name) {
        iVar5 = (int)name - (int)pbVar1;
        do {
          pbVar1 = pbVar1 + 1;
          if (bVar2 == 0) goto LAB_00032282;
          bVar2 = *pbVar1;
          bVar3 = pbVar1[iVar5];
        } while (bVar2 == bVar3);
      }
      if ((int)((uint)bVar2 - (uint)bVar3) < 0) {
        i = iVar4 + 1;
      }
      else {
        if ((int)((uint)bVar2 - (uint)bVar3) < 1) {
LAB_00032282:
          return param_1->entries + iVar4;
        }
        max_i = iVar4 + -1;
      }
    } while (i <= max_i);
  }
  return (AnimtableEntry *)0x0;
}




AnimEventMapping * FUN_000322a0(AnimEventMapping *mapping,int param_2,KFCParams *param_3)

{
  char cVar1;
  int iVar2;
  char *pcVar3;
  float fVar4;
  
  param_3->playbackSpeed_ = 0.0;
  param_3->someFloat = 0.0;
  param_3->someIdOrCount = 0x21;
  param_3->length = 0.2;
  param_3->someUshort = 0;
  param_3->someValue4 = 0x31;
  param_3->someFloat2 = 0.2;
  param_3->animEventAID[0] = '\0';
  param_3->MixP = 0x4d697850;
  param_3->someFloat3 = -10.0;
  param_3->someValue5 = (void *)0x0;
  param_3->animResource = (AnimResource *)0x0;
  param_3->animEvent = (AnimEventResource *)0x0;
  param_3->playbackSpeed_ = (float)mapping->field3_0x104;
  param_3->someIdOrCount = (int)*(char *)((int)&mapping->field7_0x114 + 2);
  param_3->length = mapping->field6_0x110;
  param_3->someUshort = (short)(char)mapping->field7_0x114;
  param_3->someValue4 = (int)*(char *)((int)&mapping->field7_0x114 + 1);
  pcVar3 = mapping->eventAID;
  param_3->someFloat2 = mapping->field5_0x10c;
  iVar2 = 0x24 - (int)pcVar3;
  do {
    cVar1 = *pcVar3;
    pcVar3[(int)param_3 + iVar2] = cVar1;
    pcVar3 = pcVar3 + 1;
  } while (cVar1 != '\0');
  fVar4 = -1.0;
  param_3->animResource = (AnimResource *)0x0;
  param_3->animEvent = (AnimEventResource *)0x0;
  param_3->someValue5 = mapping;
  if (param_2 == 0) {
    fVar4 = (float)mapping->field4_0x108;
  }
  param_3->someFloat = fVar4;
  return mapping;
}




void Assets::AnimTableResource::InitLoader(void)

{
  uint uVar1;
  ResourceLoaderStub *pRVar2;
  
  InitialiseAssetGroup("animtable",0x56,1,g_animtableHeaders);
  uVar1 = 0;
  pRVar2 = g_majorResourceLoaders;
  do {
    if (pRVar2->typeStr == (char *)0x0) {
      pRVar2 = g_majorResourceLoaders + uVar1;
      goto LAB_00034b90;
    }
    uVar1 = uVar1 + 1;
    pRVar2 = pRVar2 + 1;
  } while (uVar1 < 0x10);
  pRVar2 = (ResourceLoaderStub *)0x0;
LAB_00034b90:
                    // Write the loader
  pRVar2->typeStr = "animtable";
  pRVar2->processDescriptor = (void *)0x0;
  pRVar2->ctor = switchD_000d4179::EmptyFunction;
  pRVar2->dtor = switchD_000d4179::EmptyFunction;
  return;
}




undefined4 CheckAnimKfcThreshold(void *this,actor *act,float param_3)

{
  KeyframeContext *pKVar1;
  AnimInstance *pAVar2;
  float fVar3;
  float fVar4;
  
  pKVar1 = (act->avatar).keyframeContext;
  if ((pKVar1 == (KeyframeContext *)0x0) ||
     (pAVar2 = pKVar1->kfcAnims[(int)this].animInstance, pAVar2 == (AnimInstance *)0x0)) {
    return 0;
  }
  fVar4 = pAVar2->t;
  if (fVar4 == pAVar2->defaultT) {
    return 0;
  }
  if (pAVar2->invDuration <= 0.0 && pAVar2->invDuration != 0.0) {
    fVar3 = pAVar2->defaultT;
  }
  else {
    fVar3 = fVar4;
    fVar4 = pAVar2->defaultT;
  }
  if (fVar3 <= fVar4) {
    if (fVar4 <= param_3) {
      return 1;
    }
  }
  else if (param_3 < fVar4) {
    return 0;
  }
  if (param_3 < fVar3) {
    return 1;
  }
  return 0;
}




GetAnimMiscPropFromCutscene_(CutsceneDescriptor *descriptor,int param_2,uint animIndex)

{
  char cVar1;
  AnimResource *pAVar2;
  BOOL BVar3;
  int iVar4;
  entityAvatarMiscProp *peVar5;
  int iVar6;
  char *pcVar7;
  float in_XMM0_Da;
  vec3 pos;
  char asset_name [128];
  char local_80 [128];
  
  GetKeyframePosition(animIndex,0.0,&pos,0.0,descriptor,in_XMM0_Da);
  pAVar2 = descriptor->animRes;
  iVar4 = *(int *)(pAVar2->ANIM + (char)animIndex * 100);
  iVar6 = (char)animIndex * 100;
  pcVar7 = *(char **)(pAVar2->ANIM + iVar6);
  do {
    cVar1 = *pcVar7;
    pcVar7[(int)(asset_name + -iVar4)] = cVar1;
    pcVar7 = pcVar7 + 1;
  } while (cVar1 != '\0');
  if (g_assetName._0_4_ == 0x5f646961) {
    BVar3 = Assets::AssetNamesMatch(asset_name,g_assetName);
    if (BVar3 != 0) {
      iVar4 = 0;
      do {
        cVar1 = *(char *)((int)g_someWString + iVar4 + 0x8c);
        asset_name[iVar4] = cVar1;
        iVar4 = iVar4 + 1;
      } while (cVar1 != '\0');
    }
  }
  pcVar7 = *(char **)(pAVar2->ANIM + iVar6 + 0x18);
  if (pcVar7 != (char *)0x0) {
    iVar4 = -(int)pcVar7;
    do {
      cVar1 = *pcVar7;
      pcVar7[(int)(local_80 + iVar4)] = cVar1;
      pcVar7 = pcVar7 + 1;
    } while (cVar1 != '\0');
  }
                    // Runs when creating pause menu
  peVar5 = CreateMiscProp((param_2 != 0) - 1 & *(uint *)(pAVar2->ANIM + iVar6 + 0xc) & 1,&pos,
                          asset_name,"aid_objparams_ghoulies_misc_prop");
  return peVar5;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void FUN_00051430(CutsceneDescriptor *cutsceneDesc,vec3 *param_2,char animIndex,float param_4)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  uint64_t uVar4;
  AnimResource *res;
  
  res = cutsceneDesc->animRes;
  iVar2 = animIndex * 100;
  uVar3 = (uint)*(ushort *)((int)res->stream + iVar2);
  uVar4 = float10::to_uint64_t
                    (((float10)param_4 / (float10)*(float *)((int)res->stream + iVar2 + 4)) *
                     (float10)uVar3);
  uVar1 = (uint)uVar4;
  if (uVar3 <= uVar1) {
    uVar1 = uVar3 - 1;
  }
  param_2->x = *(float *)(*(int *)((int)res->stream + iVar2 + 8) + uVar1 * 4);
  uVar3 = (uint)*(ushort *)((int)res->stream + iVar2 + 0xc);
  uVar4 = float10::to_uint64_t
                    (((float10)param_4 / (float10)*(float *)((int)res->stream + iVar2 + 0x10)) *
                     (float10)uVar3);
  uVar1 = (uint)uVar4;
  if (uVar3 <= uVar1) {
    uVar1 = uVar3 - 1;
  }
  param_2->y = *(float *)(*(int *)((int)res->stream + iVar2 + 0x14) + uVar1 * 4);
  uVar3 = (uint)*(ushort *)((int)res->stream + iVar2 + 0x18);
  uVar4 = float10::to_uint64_t
                    (((float10)param_4 / (float10)*(float *)((int)res->stream + iVar2 + 0x1c)) *
                     (float10)uVar3);
  uVar1 = (uint)uVar4;
  if (uVar3 <= uVar1) {
    uVar1 = uVar3 - 1;
  }
  param_2->z = *(float *)(*(int *)((int)res->stream + iVar2 + 0x20) + uVar1 * 4);
  return;
}




void FUN_00051ce0(int param_1,int param_2,vec3 *param_3,AffineTransform *param_4)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  float fVar10;
  float fVar11;
  AffineTransform *pfVar12;
  
  fVar1 = *(float *)(param_2 + 0x30);
  fVar2 = *(float *)(param_2 + 0x20);
  param_3->x = *(float *)(param_2 + 0x10);
  param_3->y = fVar2;
  param_3->z = fVar1;
  if (-1 < *(short *)(param_2 + 2)) {
    pfVar12 = Skeleton::getBoneAffineIntoGlobal((Skeleton *)param_1,(int)*(short *)(param_2 + 2));
    fVar1 = pfVar12->m[1][2];
    fVar2 = pfVar12->m[2][2];
    fVar3 = pfVar12->m[1][0];
    fVar4 = param_3->x;
    fVar5 = pfVar12->m[1][1];
    fVar6 = pfVar12->m[2][0];
    fVar7 = param_3->x;
    fVar8 = pfVar12->m[1][3];
    fVar9 = pfVar12->m[2][1];
    fVar10 = param_3->y;
    fVar11 = pfVar12->m[2][3];
    param_3->x = pfVar12->m[0][2] * param_3->z + pfVar12->m[0][1] * param_3->y +
                 pfVar12->m[0][0] * param_3->x + pfVar12->m[0][3];
    param_3->y = fVar3 * fVar4 + fVar1 * param_3->z + fVar5 * param_3->y + fVar8;
    param_3->z = fVar6 * fVar7 + fVar2 * param_3->z + fVar9 * fVar10 + fVar11;
  }
  if (param_4 != (AffineTransform *)0x0) {
    fVar1 = param_4->m[1][2];
    fVar2 = param_4->m[2][2];
    fVar3 = param_4->m[1][0];
    fVar4 = param_3->x;
    fVar5 = param_4->m[1][1];
    fVar6 = param_4->m[2][0];
    fVar7 = param_3->x;
    fVar8 = param_4->m[1][3];
    fVar9 = param_4->m[2][1];
    fVar10 = param_3->y;
    fVar11 = param_4->m[2][3];
    param_3->x = param_4->m[0][2] * param_3->z + param_4->m[0][1] * param_3->y +
                 param_4->m[0][0] * param_3->x + param_4->m[0][3];
    param_3->y = fVar3 * fVar4 + fVar1 * param_3->z + fVar5 * param_3->y + fVar8;
    param_3->z = fVar6 * fVar7 + fVar2 * param_3->z + fVar9 * fVar10 + fVar11;
  }
  return;
}



void Skeleton::getBoneAndWriteAffine
               (Skeleton *skeleton,BoneAffineSubresourceEntry *param_2,AffineTransform *param_3,
               AffineTransform *out)

{
  AffineTransform *m2;
  AffineTransform *outMat;
  
  if (param_2->bone2 != -1) {
    outMat = out;
    m2 = getBoneAffineIntoGlobal(skeleton,(int)param_2->bone2);
    Graphics::leftCombineTransforms(outMat,param_3,m2);
    Graphics::leftCombineTransforms(out,out,&param_2->affine);
    return;
  }
  out->m[0][0] = param_3->m[0][0];
  out->m[0][1] = param_3->m[0][1];
  out->m[0][2] = param_3->m[0][2];
  out->m[0][3] = param_3->m[0][3];
  out->m[1][0] = param_3->m[1][0];
  out->m[1][1] = param_3->m[1][1];
  out->m[1][2] = param_3->m[1][2];
  out->m[1][3] = param_3->m[1][3];
  out->m[2][0] = param_3->m[2][0];
  out->m[2][1] = param_3->m[2][1];
  out->m[2][2] = param_3->m[2][2];
  out->m[2][3] = param_3->m[2][3];
  Graphics::leftCombineTransforms(out,out,&param_2->affine);
  return;
}



// WARNING: Inlined function: EmptyFunction


AttackInstance * AttackInstance::ctor(int rawSize)

{
  AttackInstance *new_memory;
  AttackInstance *pAVar1;
  uint uVar2;
  uint divvedSize;
  AttackInstanceEntry *pAVar3;
  
                    // Align to 8
  divvedSize = rawSize + 7U >> 3;
  new_memory = malloc_(divvedSize + 0xc);
  pAVar1 = (AttackInstance *)0x0;
  if (new_memory != (AttackInstance *)0x0) {
    new_memory->size = rawSize;
    new_memory->sizeDiv8 = divvedSize;
    new_memory->field2_0x8 = (int *)new_memory->field3_0xc;
    pAVar3 = new_memory->field3_0xc;
    for (uVar2 = rawSize + 7U >> 5; uVar2 != 0; uVar2 = uVar2 - 1) {
      *(undefined4 *)pAVar3 = 0;
      pAVar3 = (AttackInstanceEntry *)&pAVar3->field_0x4;
    }
    for (divvedSize = divvedSize & 3; pAVar1 = new_memory, divvedSize != 0;
        divvedSize = divvedSize - 1) {
      *(undefined1 *)pAVar3 = 0;
      pAVar3 = (AttackInstanceEntry *)&pAVar3->field_0x1;
    }
  }
  return pAVar1;
}




void GetVFromSubres0x8ModelName(char *modelAid,float *outx,float *outy,float *outz)

{
  Model0x8Instance *pMVar1;
  int iVar2;
  BOOL BVar3;
  int iVar4;
  Model0x8Instance *name2;
  
  iVar2 = Num0x8Instances;
  pMVar1 = PTR_0050d798;
  iVar4 = 0;
  name2 = PTR_0050d798;
  if (0 < Num0x8Instances) {
    do {
      BVar3 = Assets::AssetNamesMatch(modelAid,name2->modelAID);
      if (BVar3 != 0) {
        *outx = pMVar1[iVar4].pos.x;
        *outy = PTR_0050d798[iVar4].pos.y;
        *outz = PTR_0050d798[iVar4].pos.z;
        return;
      }
      iVar4 = iVar4 + 1;
      name2 = name2 + 1;
    } while (iVar4 < iVar2);
  }
  *outx = 0.3;
  *outy = 0.3;
  *outz = 1.2;
  return;
}



void ModelSubresource0x8::calcMaxMinXYZ
               (Subresource0x8 *param_1,undefined4 param_2,byte *bx,byte *by,byte *bz)

{
  float fVar1;
  float fVar2;
  
  fVar1 = (float)*by * 0.003921569;
  if ((float)*by * 0.003921569 <= (float)*bx * 0.003921569) {
    fVar1 = (float)*bx * 0.003921569;
  }
  fVar2 = (float)*bz * 0.003921569;
  if ((float)*bz * 0.003921569 <= fVar1) {
    fVar2 = fVar1;
  }
  if (fVar2 < Model::Subres0x8MaxAnyXYZ) {
    Model::Subres0x8MaxAnyXYZ = fVar2;
  }
  if (Model::Subres0x8MinAnyXYZ < fVar2) {
    Model::Subres0x8MinAnyXYZ = fVar2;
  }
  return;
}



void ModelSubresource0x8::Callback2
               (Subresource0x8 *subres,undefined4 param_2,byte *bx,byte *by,byte *bz)

{
  byte *pbVar1;
  byte *pbVar2;
  byte *pbVar3;
  int iVar4;
  float fVar5;
  float tx;
  float tz;
  float ty;
  float fVar6;
  float fVar7;
  uint64_t uVar8;
  
  pbVar3 = bz;
  pbVar2 = by;
  pbVar1 = bx;
  ty = (float)*by * 0.003921569;
  tx = (float)*bx * 0.003921569;
  tz = (float)*bz * 0.003921569;
  fVar6 = tx;
  if (ty <= tx) {
    fVar6 = ty;
  }
  if (tz <= fVar6) {
    fVar6 = tz;
  }
  fVar5 = tx;
  if (tx < ty) {
    fVar5 = ty;
  }
  if (fVar5 < tz) {
    fVar5 = tz;
  }
  fVar6 = fVar5 - fVar6;
  if (fVar5 == 0.0) {
    fVar6 = -1.0;
    fVar7 = 0.0;
  }
  else {
    fVar7 = fVar6 / fVar5;
    if (tx == fVar5) {
      fVar6 = (ty - tz) / fVar6;
    }
    else if (ty == fVar5) {
      fVar6 = (tz - tx) / fVar6 + 2.0;
    }
    else {
      fVar6 = (tx - ty) / fVar6 + 4.0;
    }
    fVar6 = fVar6 * 60.0;
    if (fVar6 < 0.0) {
      fVar6 = fVar6 + 360.0;
    }
  }
  fVar7 = Model::Subresource0x8Vec.x * fVar7;
  bz = (byte *)Model::Subresource0x8Vec.z;
  if (Model::Subres0x8MinAnyXYZ != Model::Subres0x8MaxAnyXYZ) {
    tx = ((fVar5 - Model::Subres0x8MaxAnyXYZ) /
         (Model::Subres0x8MinAnyXYZ - Model::Subres0x8MaxAnyXYZ)) *
         (Model::Subresource0x8Vec.z - Model::Subresource0x8Vec.y) + Model::Subresource0x8Vec.y;
    if (Model::Subresource0x8Vec.z <= Model::Subresource0x8Vec.y) {
      bz = (byte *)Model::Subresource0x8Vec.z;
      if ((tx < Model::Subresource0x8Vec.z) ||
         (bz = (byte *)Model::Subresource0x8Vec.y, Model::Subresource0x8Vec.y < tx))
      goto LAB_000fed43;
    }
    else {
      bz = (byte *)Model::Subresource0x8Vec.z;
      if ((Model::Subresource0x8Vec.z < tx) ||
         (bz = (byte *)Model::Subresource0x8Vec.y, tx < Model::Subresource0x8Vec.y))
      goto LAB_000fed43;
    }
    bz = (byte *)tx;
  }
LAB_000fed43:
  if (1.0 <= (float)bz) {
    bz = (byte *)1.0;
  }
  bx = bz;
  by = bz;
  if (fVar7 != 0.0) {
    fVar6 = fVar6 * 0.016666668;
    iVar4 = (int)fVar6;
    if (fVar6 < (float)iVar4) {
      iVar4 = iVar4 + -1;
    }
    tx = (1.0 - fVar7) * (float)bz;
    tz = (1.0 - (fVar6 - (float)iVar4) * fVar7) * (float)bz;
    fVar6 = (1.0 - (1.0 - (fVar6 - (float)iVar4)) * fVar7) * (float)bz;
    bx = (byte *)tz;
    by = (byte *)tx;
    switch(iVar4) {
    case 0:
      bx = (byte *)tx;
      by = (byte *)fVar6;
      break;
    case 1:
      bx = (byte *)tx;
      by = bz;
      bz = (byte *)tz;
      break;
    case 2:
      bx = (byte *)fVar6;
      by = bz;
      bz = (byte *)tx;
      break;
    case 3:
      bx = bz;
      by = (byte *)tz;
      bz = (byte *)tx;
      break;
    case 4:
      bx = bz;
      bz = (byte *)fVar6;
    }
  }
  uVar8 = float10::to_uint64_t((float10)(float)bz * (float10)255.0);
  *pbVar1 = (byte)uVar8;
  uVar8 = float10::to_uint64_t((float10)(float)by * (float10)255.0);
  *pbVar2 = (byte)uVar8;
  uVar8 = float10::to_uint64_t((float10)(float)bx * (float10)255.0);
  *pbVar3 = (byte)uVar8;
  return;
}




FUN_00120480(vec3 *inPos,avatar *av,HumanAnimColliderData *param_3,undefined4 num0x4s,vec3 *outPos)

{
  vec3 *in_EAX;
  int iVar2;
  float *local_40;
  undefined4 local_3c;
  vec3 local_38;
  float local_2c;
  float local_28;
  float local_24;
  undefined1 local_20 [32];
  avatar_0x110 iVar1;
  
  DAT_00511188 = 0;
  FUN_001202c0();
  if (av == (avatar *)0x0) {
    local_40 = (float *)0x0;
  }
  else {
    avatar::getWorldPosition(av,&local_38);
    local_2c = inPos->x - local_38.x;
    local_28 = inPos->y - local_38.y;
    local_24 = inPos->z - local_38.z;
    local_40 = &local_2c;
  }
  outPos->z = 0.0;
  outPos->y = 0.0;
  outPos->x = 0.0;
  local_3c = 0;
  for (iVar1 = (avatar_0x110)Game::SceneInfo.avatars_0x110.head;
      (EmbeddedNode<>_conflict *)iVar1 != (EmbeddedNode<>_conflict *)0x0;
      iVar1 = (avatar_0x110)((EmbeddedNode<>_conflict *)iVar1)->next) {
    iVar2 = (*((avatar *)(iVar1 + -0x22))->vtable->updatePositionsAndAnimations)
                      ((avatar *)(iVar1 + -0x22),av,local_40,local_20,param_3,num0x4s,&local_38);
    if (iVar2 != 0) {
      (&DAT_0051118c)[DAT_00511188] = (avatar *)(iVar1 + -0x22);
      DAT_00511188 = DAT_00511188 + 1;
      FUN_00120d10(local_20);
      outPos->x = outPos->x + local_38.x;
      outPos->y = outPos->y + local_38.y;
      outPos->z = local_38.z + outPos->z;
      local_3c = 1;
    }
  }
  return local_3c;
}




void __fastcall FUN_0013c490(float *param_1,float *param_2,AffineTransform *param_3)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  
  if (Background::HasBounds == '\0') {
    fVar4 = 1500.0;
  }
  else {
    fVar4 = 0.0 - (param_3->m[2][0] * background_pos3.x + background_pos3.y * param_3->m[2][1] +
                   background_pos3.z * param_3->m[2][2] + param_3->m[2][3]);
    fVar1 = 0.0 - (param_3->m[2][0] * background_pos4.x + background_pos4.y * param_3->m[2][1] +
                   background_pos4.z * param_3->m[2][2] + param_3->m[2][3]);
    fVar3 = fVar1;
    if ((fVar4 <= fVar1) && (fVar3 = fVar4, fVar4 < fVar1)) {
      fVar4 = fVar1;
    }
    fVar2 = 0.0 - (param_3->m[2][0] * background_pos5.x + background_pos5.y * param_3->m[2][1] +
                   background_pos5.z * param_3->m[2][2] + param_3->m[2][3]);
    fVar1 = fVar2;
    if ((fVar3 <= fVar2) && (fVar1 = fVar3, fVar4 < fVar2)) {
      fVar4 = fVar2;
    }
    fVar2 = 0.0 - (param_3->m[2][0] * background_pos6.x + background_pos6.y * param_3->m[2][1] +
                   background_pos6.z * param_3->m[2][2] + param_3->m[2][3]);
    fVar3 = fVar2;
    if ((fVar1 <= fVar2) && (fVar3 = fVar1, fVar4 < fVar2)) {
      fVar4 = fVar2;
    }
    fVar2 = 0.0 - (background_pos7.y * param_3->m[2][1] + background_pos7.x * param_3->m[2][0] +
                   background_pos7.z * param_3->m[2][2] + param_3->m[2][3]);
    fVar1 = fVar2;
    if ((fVar3 <= fVar2) && (fVar1 = fVar3, fVar4 < fVar2)) {
      fVar4 = fVar2;
    }
    fVar2 = 0.0 - (background_pos8.y * param_3->m[2][1] + background_pos8.z * param_3->m[2][2] +
                   background_pos8.x * param_3->m[2][0] + param_3->m[2][3]);
    fVar3 = fVar2;
    if ((fVar1 <= fVar2) && (fVar3 = fVar1, fVar4 < fVar2)) {
      fVar4 = fVar2;
    }
    fVar2 = 0.0 - (background_pos9.y * param_3->m[2][1] + background_pos9.z * param_3->m[2][2] +
                   background_pos9.x * param_3->m[2][0] + param_3->m[2][3]);
    fVar1 = fVar2;
    if ((fVar3 <= fVar2) && (fVar1 = fVar3, fVar4 < fVar2)) {
      fVar4 = fVar2;
    }
    fVar3 = 0.0 - (background_pos10.y * param_3->m[2][1] + background_pos10.z * param_3->m[2][2] +
                   background_pos10.x * param_3->m[2][0] + param_3->m[2][3]);
    if ((fVar1 <= fVar3) && (fVar4 < fVar3)) {
      fVar4 = fVar3;
    }
    fVar4 = fVar4 + 100.0;
  }
  *param_2 = 0.5;
  if (*param_1 <= fVar4 && fVar4 != *param_1) {
    *param_1 = fVar4;
  }
  fVar4 = *param_2 + 1.0;
  if (*param_1 <= fVar4 && fVar4 != *param_1) {
    *param_1 = fVar4;
  }
  *param_1 = *param_1 * 1.1;
  return;
}




