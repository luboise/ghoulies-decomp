/* fx.c - Particle/FX avatars and impact effects */
#include "fx.h"

void Callout::DefaultCallback(CalloutDescriptor *descriptor,uint index,actor *param_3)

{
  switch(descriptor->id) {
  case 1:
    FUN_0003bd80(descriptor,index,param_3);
    return;
  case 2:
  case 3:
    goto switchD_0003bed4_default;
  case 4:
    FUN_0003bbf0();
    return;
  case 5:
    FUN_0003bc20();
    return;
  case 6:
    FUN_0003bc40();
    return;
  case 7:
    FUN_0003bd10(index,param_3);
    return;
  case 8:
    FUN_0003bce0(param_3);
    return;
  case 9:
    FUN_0003bc70(descriptor);
    return;
  case 10:
    Audio::loadAudioIntoEmptySlot(0x12,descriptor->someAID2);
switchD_0003bed4_default:
    return;
  default:
    return;
  }
}




avatarCalloutId Callout::getByName(char *calloutId)

{
  char cVar1;
  char *pcVar2;
  uint uVar3;
  
  pcVar2 = calloutId;
  do {
    cVar1 = *pcVar2;
    pcVar2 = pcVar2 + 1;
  } while (cVar1 != '\0');
  if (pcVar2 != calloutId + 1) {
    uVar3 = Events::GetIndexOfStringInTable(0x55,PTR_ARRAY_00421c98 + 1,calloutId);
    if (uVar3 != 0xffffffff) {
      return (avatarCalloutId)(float2)(float)(uVar3 + 1);
    }
  }
  return (avatarCalloutId)(float2)0.0;
}




void entityAvatarFxBurnup::checkCollision0x4(entityAvatarFxBurnup *param_1)

{
  avatar_0x110 pEVar1;
  
  (param_1->avatar).has0x4CollisionFlag = 0;
  avatar::updateMorphTargetsOrSomething(&param_1->avatar);
  pEVar1 = (param_1->avatar).node0x110.prev;
  if (pEVar1 != (avatar_0x110)0x0) {
    pEVar1->next = (param_1->avatar).node0x110.next;
  }
  pEVar1 = (param_1->avatar).node0x110.next;
  if (pEVar1 != (avatar_0x110)0x0) {
    pEVar1->prev = (param_1->avatar).node0x110.prev;
  }
  (param_1->avatar).node0x110.prev = (avatar_0x110)0x0;
  (param_1->avatar).node0x110.next = (avatar_0x110)0x0;
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


avatarFxEmitter::ctor(avatarFxEmitter *emitter,int param_2,int param_3,char *impactFlashAID)

{
  char cVar1;
  void *pvVar2;
  void *pvVar3;
  int iVar4;
  impactFlashFxEmitterData *new_emitter;
  
  new_emitter = malloc_(0xc4);
  iVar4 = 0x24 - (int)impactFlashAID;
  do {
    cVar1 = *impactFlashAID;
    impactFlashAID[(int)new_emitter + iVar4] = cVar1;
    impactFlashAID = impactFlashAID + 1;
  } while (cVar1 != '\0');
  new_emitter->field12_0x20 = param_3;
  new_emitter->impactId = 0xffff;
  new_emitter->field2_0x8 = -1;
  pvVar3 = &emitter->field_0x8;
  new_emitter->field6_0x10 = 0;
  new_emitter->field7_0x14 = 0;
  new_emitter->field11_0x1c = param_2;
  new_emitter->field0_0x0 = 0;
  new_emitter->field1_0x4 = 0;
  pvVar2 = emitter->field12_0xc;
  while (pvVar2 != (void *)0x0) {
    pvVar3 = *(void **)((int)pvVar3 + 4);
    pvVar2 = *(void **)((int)pvVar3 + 4);
  }
  *(impactFlashFxEmitterData **)((int)pvVar3 + 4) = new_emitter;
  new_emitter->field1_0x4 = 0;
  new_emitter->field0_0x0 = (int)pvVar3;
  emitter->field13_0x10 = emitter->field13_0x10 + 1;
  new_emitter->field8_0x18 = emitter->field13_0x10;
  new_emitter->field14_0xa4 = 0;
  new_emitter->field15_0xa5 = 0;
  new_emitter->field42_0xc0 = 1.0;
  return new_emitter;
}



void __thiscall

void entityAvatarFxAnimEmitter::getVTable(void)

{
  avatar::initVTable((AvatarVTable *)PTR_ARRAY_00504964);
  PTR_ARRAY_00504964[0] = FUN_00066740;
  PTR_ARRAY_00504964[1] = FUN_000667b0;
  PTR_ARRAY_00504964[2] = switchD_000d4179::EmptyFunction;
  PTR_ARRAY_00504964[3] = onMessage;
  PTR_ARRAY_00504964[4] = update;
  PTR_ARRAY_00504964[5] = avatar::draw;
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void entityAvatarFxAnimEmitter::update(actor *param_1)

{
  int iVar1;
  int iVar2;
  actor_0x934 *ppNVar3;
  vec3 local_18;
  undefined4 local_c;
  undefined4 local_8;
  undefined4 local_4;
  
  iVar2 = 0;
  if (0 < (int)param_1->strategy) {
    ppNVar3 = &(param_1->node0x934).next;
    do {
      ::actor::getTransformedBonePos(param_1,&Game::someGlobalPos,*(uint16_t *)ppNVar3,&local_18);
      FUN_0003b050(*(uint16_t *)ppNVar3,&local_c);
      iVar1 = (&DAT_00506930)[(int)((Node<> *)(ppNVar3 + -1))->prev];
      *(float *)(iVar1 + 0x1c) = local_18.x;
      *(float *)(iVar1 + 0x20) = local_18.y;
      *(float *)(iVar1 + 0x24) = local_18.z;
      *(undefined4 *)(iVar1 + 0x50) = local_c;
      *(undefined4 *)(iVar1 + 0x54) = local_8;
      *(undefined4 *)(iVar1 + 0x58) = local_4;
      iVar2 = iVar2 + 1;
      ppNVar3 = ppNVar3 + 2;
    } while (iVar2 < (int)param_1->strategy);
  }
  avatar::update(&param_1->avatar);
  return;
}




void entityAvatarFxBurnup::getAllocDetails(undefined4 *param_1)

{
  *param_1 = 0xa50;
  param_1[1] = 0x4b8;
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void entityAvatarFxBurnup::getVTable(void)

{
  avatar::initVTable(&vtable);
  vtable.getAllocDetails = getAllocDetails;
  vtable.ctor = ctor;
  vtable.dtor = dtor;
  vtable.onMessage = onMessage;
  vtable.update = update;
  return;
}




undefined4 entityAvatarFxBurnup::ctor(entityAvatarFxBurnup *this,entityAvatarFxBurnupParams *params)

{
  undefined1 *name;
  char cVar1;
  entityAvatarFxBurnup *avatar;
  char *pcVar2;
  entityAvatarFxBurnup *peVar3;
  int iVar4;
  float10 fVar5;
  char *aid1;
  entityAvatarFxBurnupParams *paramss;
  
  paramss = params;
  avatar = this;
  aid1 = this->someAID1;
  pcVar2 = &params->someAID1;
  *(undefined4 *)&this->field_0x944 = 0;
  this->someFloat = 0.5;
  iVar4 = (int)aid1 - (int)pcVar2;
  do {
    cVar1 = *pcVar2;
    pcVar2[iVar4] = cVar1;
    pcVar2 = pcVar2 + 1;
  } while (cVar1 != '\0');
  pcVar2 = params->someAID2;
  iVar4 = 0x9d0 - (int)pcVar2;
  do {
    cVar1 = *pcVar2;
    pcVar2[(int)this + iVar4] = cVar1;
    pcVar2 = pcVar2 + 1;
  } while (cVar1 != '\0');
  ::avatar::loadFromParent(&this->avatar,*(AvatarParent **)&params->field_0x334);
  ::avatar::updateBaseTransform(&avatar->avatar);
  avatar->fx_y_from_scale = (avatar->avatar).scale.y;
  fVar5 = FUN_0003d9a0(&avatar->avatar);
  FUN_00066ab0(&avatar->avatar,aid1,(float)(fVar5 * (float10)0.1));
  burnupInit(&avatar->avatar);
  name = &paramss->someOtherAID;
  (avatar->avatar).preDrawCallback = ::avatar::callback0x1a0;
  (avatar->avatar).textureCallback = FUN_00066c00;
  (avatar->avatar).preDrawData = avatar;
  if (*(int *)name == 0x5f646961) {
    Assets::GetResourceBytes(name,&this);
    peVar3 = this;
    if (this == (entityAvatarFxBurnup *)0x0) {
      runtime::ExitGame(2);
    }
  }
  else {
    peVar3 = (entityAvatarFxBurnup *)0x0;
  }
  *(entityAvatarFxBurnup **)&avatar->field_0x94c = peVar3;
  cVar1 = *(char *)(*(int *)&paramss->field_0x334 + 0x196);
  avatar->field7_0x940 = -1;
  *(uint *)&avatar->field_0x948 = 7 - (uint)(cVar1 != '\0');
  return 1;
}




void entityAvatarFxBurnup::dtor(int param_1)

{
  Assets::DestroyAssetOrDecrement(*(void **)(param_1 + 0x94c));
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void entityAvatarFxBurnup::update(entityAvatarFxBurnup *param_1)

{
  int iVar1;
  float10 fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  
  if (runtime::dx_timer <= 0.0) {
    fVar3 = runtime::DeltaTime * runtime::TimeScale;
  }
  else {
    fVar3 = 0.0;
  }
  fVar5 = 0.0;
  if ((param_1->avatar).movementFreezeTimer <= 0.0) {
    fVar5 = (param_1->avatar).actionSpeed;
  }
  if ((param_1->someFloat <= 0.0) ||
     (fVar3 = param_1->someFloat - fVar5 * fVar3, param_1->someFloat = fVar3, 0.0 < fVar3)) {
    fVar3 = (param_1->avatar).scale.x;
    fVar5 = (param_1->avatar).scale.z;
    fVar2 = (float10)FUN_00066940();
    fVar4 = 0.0001;
    if ((float10)0.0001 < fVar2) {
      fVar4 = (float)fVar2;
    }
    fVar4 = param_1->fx_y_from_scale * fVar4;
    if (((fVar3 != (param_1->avatar).scale.x) || (fVar4 != (param_1->avatar).scale.y)) ||
       (fVar5 != (param_1->avatar).scale.z)) {
      (param_1->avatar).scale.y = fVar4;
      (param_1->avatar).scale.x = fVar3;
      (param_1->avatar).scale.z = fVar5;
      (param_1->avatar).anglesCalculated = 0;
    }
    if (-1 < param_1->field7_0x940) {
      fVar3 = 1.0;
      if (((*(int *)&param_1->field_0x944 == 3) && (fVar5 = param_1->someFloat, fVar5 <= 1.0)) &&
         (fVar3 = 0.0, 0.0 <= fVar5)) {
        fVar3 = fVar5;
      }
      fVar5 = avatar::getCalculatedRadius(&param_1->avatar);
      fVar3 = fVar5 * fVar3 * 4.0;
      if (60.0 < fVar3) {
        fVar3 = 60.0;
      }
      iVar1 = param_1->field7_0x940;
      (&DAT_00511b8c)[iVar1 * 0xb] = fVar3;
      (&DAT_00511b90)[iVar1 * 0xb] = fVar3 * 2.0;
    }
  }
  else {
    param_1->someFloat = 0.0;
    iVar1 = *(int *)&param_1->field_0x944;
    *(int *)&param_1->field_0x944 = iVar1 + 1;
    if (iVar1 == 0) {
      FUN_00066f70();
      if ((DAT_005120f0 != 0) || (DAT_00512104 != 0)) {
        FUN_000669d0();
      }
    }
    else if (iVar1 == 2) {
      FUN_0012a3d0((astruct_25 *)&(param_1->avatar).model0x9s[3].field_0xb0);
    }
    else if (iVar1 == 3) {
      FUN_00066a80();
      goto switchD_00067240_caseD_4;
    }
    param_1->someFloat = *(float *)(&DAT_002ff768 + *(int *)&param_1->field_0x944 * 4);
  }
  fVar3 = *(float *)(&DAT_002ff768 + *(int *)&param_1->field_0x944 * 4);
  if (fVar3 == 0.0) {
    fVar3 = 1.0;
  }
  else {
    fVar3 = (param_1->someFloat - fVar3) / (0.0 - fVar3);
    if (fVar3 <= 1.0) {
      if (fVar3 < 0.0) {
        fVar3 = 0.0;
      }
    }
    else {
      fVar3 = 1.0;
    }
  }
  *(float *)&param_1->field_0x93c = fVar3;
  switch(*(int *)&param_1->field_0x944) {
  case 1:
    fVar3 = fVar3 + 1.0;
  case 0:
    fVar3 = fVar3 * 0.25;
    break;
  case 2:
    fVar3 = fVar3 * 0.25 + 0.5;
    break;
  case 3:
    fVar3 = fVar3 * 0.25 + 0.75;
    break;
  case 4:
switchD_00067240_caseD_4:
    avatar::destroy(&param_1->avatar);
    return;
  default:
    goto switchD_00067240_default;
  }
  *(float *)&param_1->field_0x93c = fVar3;
switchD_00067240_default:
  avatar::update(&param_1->avatar);
  return;
}




void entityAvatarFxExplode::getAllocDetails(undefined4 *param_1)

{
  *param_1 = 0x94c;
  param_1[1] = 0x3bc;
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void entityAvatarFxExplode::getVTable(void)

{
  avatar::initVTable((AvatarVTable *)vtable);
  vtable[0] = getAllocDetails;
  vtable[1] = ctor;
  vtable[2] = dtor;
  vtable[3] = onMessage;
  vtable[4] = update;
  vtable[5] = func5;
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields

undefined4

entityAvatarFxExplode::ctor(entityAvatarFxExplode *fx,entityAvatarFxExplodeParams *param_2)

{
  CalloutDescriptor **ppCVar1;
  
  avatar::loadFromParent(&fx->avatar,param_2->parent);
  avatar::destroyFx_(&fx->avatar);
  *(undefined4 *)&fx->field_0x938 = *(undefined4 *)&param_2->field_0x3b8;
  *(undefined4 *)&fx->field_0x948 = 0;
  fx->parent = param_2->parent;
  ppCVar1 = &(fx->avatar).callout;
  if (ppCVar1 != (CalloutDescriptor **)0x0) {
    ::actor::executeCalloutInDescriptor
              (*ppCVar1,ExplodeBegin,(CalloutCallback *)0x0,0,(actor *)fx,
               (entityBodyPlayer_0x924)0x0);
  }
  return 1;
}




void entityAvatarFxExplode::dtor(int param_1)

{
  void *mem;
  undefined4 uVar1;
  int iVar2;
  HeapTableEntry *pHVar3;
  
  if (*(int *)(param_1 + 0x934) != 0) {
    FUN_000ed2e0();
    *(undefined4 *)(param_1 + 0x934) = 0;
  }
  mem = *(void **)(param_1 + 0x940);
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



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void entityAvatarFxExplode::update(entityAvatarFxExplode *fx)

{
  CalloutDescriptor **ppCVar1;
  float __x;
  Model *pMVar2;
  WeirdTransform *pWVar3;
  WeirdTransform *pWVar4;
  float *pfVar5;
  undefined4 uVar6;
  float *pfVar7;
  int iVar8;
  int iVar9;
  float10 extraout_ST0;
  float10 fVar10;
  float10 extraout_ST0_00;
  float10 extraout_ST0_01;
  float fVar11;
  float fVar12;
  float local_384;
  uint i;
  Skeleton *local_37c;
  int bone_offset;
  ndSkeletonBone *bone;
  objParams local_354 [103];
  undefined1 local_18;
  undefined4 local_8;
  undefined4 local_4;
  ndSkeletonBone *first_bone;
  int num_parts;
  ndSkeleton *skeleton;
  
  avatar::update(&fx->avatar);
  if (*(int *)&fx->field_0x948 == 0) {
    pMVar2 = (fx->avatar).model;
    if (pMVar2 == (Model *)0x0) {
      local_37c = (Skeleton *)0x0;
    }
    else {
      local_37c = pMVar2->skeleton;
      if (local_37c == (Skeleton *)0x0) {
        local_37c = pMVar2->skeleton2;
      }
    }
    num_parts = local_37c->numBones;
    pMVar2 = (fx->avatar).model;
    if (runtime::dx_timer <= 0.0) {
      fVar11 = runtime::DeltaTime * runtime::TimeScale;
    }
    else {
      fVar11 = 0.0;
    }
    fVar12 = 0.0;
    if ((fx->avatar).movementFreezeTimer <= 0.0) {
      fVar12 = (fx->avatar).actionSpeed;
    }
    if (0.0 < fVar12 * fVar11) {
      if (runtime::dx_timer <= 0.0) {
        local_384 = runtime::DeltaTime * runtime::TimeScale;
      }
      else {
        local_384 = 0.0;
      }
      FUN_000ef2d0(local_384,*(astruct_46 **)&fx->field_0x934);
      *(undefined4 *)&fx->field_0x948 = 1;
      i = 0;
      if (0 < num_parts) {
        local_384 = 0.0;
        bone_offset = 0;
        do {
          if ((*(int *)&fx->field_0x948 == 0) ||
             (*(char *)((short)i * 0x150 + 0x3e4 + *(int *)&fx->field_0x934) == '\0')) {
            uVar6 = 0;
          }
          else {
            uVar6 = 1;
          }
          *(undefined4 *)&fx->field_0x948 = uVar6;
          skeleton = pMVar2->ndSkeleton;
          if ((skeleton == (ndSkeleton *)0x0) ||
             (first_bone = skeleton->bonesStart, first_bone == (ndSkeletonBone *)0x0)) {
            bone = (ndSkeletonBone *)0x0;
          }
          else {
            bone = (ndSkeletonBone *)((int)&first_bone->parentBone + bone_offset);
          }
          iVar9 = *(int *)&fx->field_0x934;
          iVar8 = (short)i * 0x150;
          fVar11 = *(float *)(iVar9 + 0x39c + iVar8);
          Graphics::ComputedTextureAffine.m[0][3] = *(float *)(iVar9 + 0x390 + iVar8);
          Graphics::ComputedTextureAffine.m[1][3] = *(float *)(iVar9 + 0x394 + iVar8);
          Graphics::ComputedTextureAffine.m[2][3] = *(float *)(iVar9 + 0x398 + iVar8);
          iVar9 = iVar9 + 0x390 + iVar8;
          fVar12 = *(float *)(iVar9 + 0x10);
          __x = *(float *)(iVar9 + 0x14);
          graphics::bone_acc = (WeirdTransform *)&g_affine;
          g_affine.m[0][0] = (fx->avatar).baseTransform.m[0][0];
          g_affine.m[0][1] = (fx->avatar).baseTransform.m[0][1];
          g_affine.m[0][2] = (fx->avatar).baseTransform.m[0][2];
          g_affine.m[0][3] = (fx->avatar).baseTransform.m[0][3];
          g_affine.m[1][0] = (fx->avatar).baseTransform.m[1][0];
          g_affine.m[1][1] = (fx->avatar).baseTransform.m[1][1];
          g_affine.m[1][2] = (fx->avatar).baseTransform.m[1][2];
          g_affine.m[1][3] = (fx->avatar).baseTransform.m[1][3];
          g_affine.m[2][0] = (fx->avatar).baseTransform.m[2][0];
          g_affine.m[2][1] = (fx->avatar).baseTransform.m[2][1];
          g_affine.m[2][2] = (fx->avatar).baseTransform.m[2][2];
          g_affine.m[2][3] = (fx->avatar).baseTransform.m[2][3];
          Graphics::ComputedTextureAffine.m[0][0] = 1.0;
          Graphics::ComputedTextureAffine.m[0][1] = 0.0;
          Graphics::ComputedTextureAffine.m[0][2] = 0.0;
          Graphics::ComputedTextureAffine.m[1][0] = 0.0;
          Graphics::ComputedTextureAffine.m[1][1] = 1.0;
          Graphics::ComputedTextureAffine.m[1][2] = 0.0;
          Graphics::ComputedTextureAffine.m[2][0] = 0.0;
          Graphics::ComputedTextureAffine.m[2][1] = 0.0;
          Graphics::ComputedTextureAffine.m[2][2] = 1.0;
          Graphics::leftCombineTransforms(&g_affine,&g_affine,&Graphics::ComputedTextureAffine);
          sin(fVar11);
          fVar10 = (float10)cos(fVar11);
          FUN_001046a0((float)extraout_ST0,(float)fVar10);
          Graphics::leftCombineTransforms
                    (&graphics::bone_acc->affine1,&graphics::bone_acc->affine1,
                     &graphics::bone_acc->affine2);
          sin(fVar12);
          fVar10 = (float10)cos(fVar12);
          FUN_001046a0((float)extraout_ST0_00,(float)fVar10);
          Graphics::leftCombineTransforms
                    (&graphics::bone_acc->affine1,&graphics::bone_acc->affine1,
                     &graphics::bone_acc->affine2);
          sin(__x);
          fVar10 = (float10)cos(__x);
          FUN_001046a0((float)extraout_ST0_01,(float)fVar10);
          Graphics::leftCombineTransforms
                    (&graphics::bone_acc->affine1,&graphics::bone_acc->affine1,
                     &graphics::bone_acc->affine2);
          pWVar3 = graphics::bone_acc;
          iVar9 = *(int *)&fx->field_0x940;
          fVar11 = *(float *)(iVar9 + 8 + (int)local_384);
          fVar12 = *(float *)(iVar9 + 4 + (int)local_384);
          (graphics::bone_acc->affine2).m[0][0] = *(float *)(iVar9 + (int)local_384);
          (pWVar3->affine2).m[0][1] = 0.0;
          (pWVar3->affine2).m[0][2] = 0.0;
          (pWVar3->affine2).m[0][3] = 0.0;
          (pWVar3->affine2).m[1][0] = 0.0;
          (pWVar3->affine2).m[1][1] = fVar12;
          (pWVar3->affine2).m[1][2] = 0.0;
          (pWVar3->affine2).m[1][3] = 0.0;
          (pWVar3->affine2).m[2][0] = 0.0;
          (pWVar3->affine2).m[2][1] = 0.0;
          (pWVar3->affine2).m[2][2] = fVar11;
          (pWVar3->affine2).m[2][3] = 0.0;
          Graphics::leftCombineTransforms
                    (&graphics::bone_acc->affine1,&graphics::bone_acc->affine1,
                     &graphics::bone_acc->affine2);
          pWVar3 = graphics::bone_acc;
          pWVar4 = (WeirdTransform *)Skeleton::getBoneAffineIntoGlobal(local_37c,i);
          if (pWVar3 != pWVar4) {
            (pWVar4->affine1).m[0][0] = (pWVar3->affine1).m[0][0];
            (pWVar4->affine1).m[0][1] = (pWVar3->affine1).m[0][1];
            (pWVar4->affine1).m[0][2] = (pWVar3->affine1).m[0][2];
            (pWVar4->affine1).m[0][3] = (pWVar3->affine1).m[0][3];
            (pWVar4->affine1).m[1][0] = (pWVar3->affine1).m[1][0];
            (pWVar4->affine1).m[1][1] = (pWVar3->affine1).m[1][1];
            (pWVar4->affine1).m[1][2] = (pWVar3->affine1).m[1][2];
            (pWVar4->affine1).m[1][3] = (pWVar3->affine1).m[1][3];
            (pWVar4->affine1).m[2][0] = (pWVar3->affine1).m[2][0];
            (pWVar4->affine1).m[2][1] = (pWVar3->affine1).m[2][1];
            (pWVar4->affine1).m[2][2] = (pWVar3->affine1).m[2][2];
            (pWVar4->affine1).m[2][3] = (pWVar3->affine1).m[2][3];
          }
          pfVar7 = (pWVar4->affine1).m[0] + 3;
          pfVar5 = (pWVar3->affine1).m[0] + 1;
          iVar9 = 3;
          do {
            *pfVar7 = *pfVar7 - ((*(float (*) [4])(pfVar5 + -1))[0] * (bone->globalTransform).x +
                                 pfVar5[1] * (bone->globalTransform).z +
                                *pfVar5 * (bone->globalTransform).y);
            pfVar5 = pfVar5 + 4;
            pfVar7 = pfVar7 + 4;
            iVar9 = iVar9 + -1;
          } while (iVar9 != 0);
          if ((((*(int *)&fx->field_0x944 == 0) &&
               (*(int *)(*(int *)&fx->field_0x934 + 0x3ec + iVar8) != 0)) &&
              (*(char *)(*(int *)&fx->field_0x934 + iVar8 + 0x3e5) == '\0')) &&
             (0.75 < DAT_00506928)) {
            ppCVar1 = &(fx->avatar).callout;
            *(undefined4 *)&fx->field_0x944 = 1;
            if (ppCVar1 != (CalloutDescriptor **)0x0) {
              ::actor::executeCalloutInDescriptor
                        (*ppCVar1,Explode,(CalloutCallback *)0x0,0,(actor *)fx,
                         (entityBodyPlayer_0x924)0x0);
            }
          }
          i = i + 1;
          bone_offset = bone_offset + 0x20;
          local_384 = (float)((int)local_384 + 0xc);
        } while ((int)i < num_parts);
      }
      if (*(int *)&fx->field_0x948 != 0) {
        ::actor::createOnDeathObjects(&fx->avatar,1);
        (fx->avatar).hasActor_ = true;
        ::actor::createOnDeathObjects(&fx->avatar,0);
      }
    }
  }
  else if (*(float *)&fx->field_0x938 != -1.0) {
    if (runtime::dx_timer <= 0.0) {
      fVar11 = runtime::DeltaTime * runtime::TimeScale;
    }
    else {
      fVar11 = 0.0;
    }
    fVar12 = 0.0;
    if ((fx->avatar).movementFreezeTimer <= 0.0) {
      fVar12 = (fx->avatar).actionSpeed;
    }
    if ((0.0 < *(float *)&fx->field_0x938) &&
       (fVar11 = *(float *)&fx->field_0x938 - fVar12 * fVar11, *(float *)&fx->field_0x938 = fVar11,
       fVar11 <= 0.0)) {
      *(undefined4 *)&fx->field_0x938 = 0;
      FUN_00069590(2.0);
      local_18 = *(undefined1 *)((int)&(fx->avatar).someInt32 + 3);
      local_4 = 0;
      local_8 = 0;
      Assets::CreateEntityFromParams(local_354);
      avatar::destroy(&fx->avatar);
      return;
    }
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


undefined4 entityAvatarFxExplode::func5(entityAvatarFxExplode *fx)

{
  Model *instance;
  undefined4 in_stack_0000000c;
  
  instance = (fx->avatar).model;
  if ((fx->avatar).hasActor_ == false) {
    ::actor::createOnDeathObjects(&fx->avatar,0);
  }
  ModelInstance::draw(instance,&(fx->avatar).drawAffine,in_stack_0000000c);
  return 1;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void entityAvatarFxExplode::onMessage(entityAvatarFxExplode *fx,Message *msg)

{
  ObjMsgID OVar1;
  DataForInfoFromBackground_conflict1 *pDVar2;
  
  avatar::onMessage(&fx->avatar,msg);
  OVar1 = (msg->header).msgId;
  if (OVar1 == Avatar_SceneInsert) {
    FUN_0003e850((entityAvatarFxBurnup *)fx);
    entityAvatarFxBurnup::checkCollision0x4((entityAvatarFxBurnup *)fx);
    pDVar2 = (fx->avatar).infoList.prev;
    while (pDVar2 != (DataForInfoFromBackground_conflict1 *)0x0) {
      pDVar2 = (DataForInfoFromBackground_conflict1 *)pDVar2->field1_0x4;
      FUN_0011bda0();
    }
  }
  else if ((OVar1 == Scene_AvatarRemoved) && (fx->parent == (msg->header).someActor)) {
    FUN_00041d90(fx);
    fx->parent = (AvatarParent *)0x0;
    return;
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void entityAvatarFxExplodeParts::getAllocDetails(undefined4 *param_1)

{
  *param_1 = 0xaac;
  param_1[1] = 0x55c;
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void entityAvatarFxExplodeParts::getVTable(void)

{
  avatar::initVTable(&vtable);
  vtable.getAllocDetails = getAllocDetails;
  vtable.ctor = ctor;
  vtable.dtor = dtor;
  vtable.onMessage = update;
  vtable.update = updateFixed_;
  vtable.draw = func5;
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields

undefined4
entityAvatarFxExplodeParts::ctor
          (entityAvatarFxExplodeParts *parts,entityAvatarFxExplodePartsParams *params)

{
  CalloutDescriptor **ppCVar1;
  entityAvatarFxExplodePartsParamsInners1 *peVar2;
  Model *pMVar3;
  int iVar4;
  char *pcVar5;
  BOOL success;
  undefined4 *puVar6;
  Asset *pAVar7;
  char c;
  
  avatar::loadFromParent(&parts->avatar,params->parentActor);
  avatar::updateBaseTransform(&parts->avatar);
  *(undefined4 *)&parts->field_0x9d4 = *(undefined4 *)&params->field_0x4b8;
  pcVar5 = &params->field_0x438;
  iVar4 = 0x954 - (int)pcVar5;
  do {
    c = *pcVar5;
    pcVar5[(int)parts + iVar4] = c;
    pcVar5 = pcVar5 + 1;
  } while (c != '\0');
  success = LoadSomething(parts,params);
  if (success == 0) {
    return 0;
  }
  peVar2 = params->inners1;
  if ((peVar2 != (entityAvatarFxExplodePartsParamsInners1 *)0x0) &&
     (*(int *)peVar2->assetName == 0x5f646961)) {
    pMVar3 = (parts->avatar).model;
    FUN_00140560(&peVar2->field0_0x0,(int)&parts->field_0x9dc);
    puVar6 = FUN_000f8540((char *)params->inners1->field0_0x0,(char *)params->inners1->field1_0x4,
                          pMVar3);
    *(undefined4 **)&parts->field_0x9d8 = puVar6;
    pAVar7 = Assets::GetResourceBytesOrExit(params->inners1->assetName);
    *(Asset **)&parts->field_0xa64 = pAVar7;
    FUN_000f86f0(pAVar7,0,*(Asset **)&parts->field_0x9d8);
  }
  *(undefined4 *)&parts->field_0x93c = *(undefined4 *)&params->field_0x4c0;
  *(undefined4 *)&parts->field_0x940 = *(undefined4 *)&params->field_0x4bc;
  *(undefined4 *)&parts->field_0x944 = *(undefined4 *)&params->field_0x4bc;
  parts->someUintIs255 = 0xff;
  *(undefined4 *)&parts->field_0x950 = 0;
  parts->parent = params->parentActor;
  ppCVar1 = &(parts->avatar).callout;
  if (ppCVar1 != (CalloutDescriptor **)0x0) {
    ::actor::executeCalloutInDescriptor
              (*ppCVar1,ExplodeBegin,(CalloutCallback *)0x0,0,(actor *)parts,
               (entityBodyPlayer_0x924)0x0);
  }
  if ((params->field_0x4c4 != '\0') && (params->field_0x4c4 != '\0')) {
    FUN_0012a260(0,(actor *)parts,1,(vec3 *)0x0,(vec3 *)0x0,1.0,
                 (astruct_25 *)&(parts->avatar).model0x9s[0].field_0xb0,&params->field_0x4c4);
  }
  return 1;
}




void entityAvatarFxExplodeParts::dtor(int param_1)

{
  if (*(int *)(param_1 + 0x934) != 0) {
    FUN_000ed2e0();
    *(undefined4 *)(param_1 + 0x934) = 0;
  }
  if (*(int *)(param_1 + 0x9d8) != 0) {
    FUN_000f85d0();
  }
  if (*(void **)(param_1 + 0xa64) != (void *)0x0) {
    Assets::DestroyAssetOrDecrement(*(void **)(param_1 + 0xa64));
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void entityAvatarFxExplodeParts::updateFixed_(actor *param_1)

{
  Node<> *pNVar1;
  CalloutDescriptor **ppCVar2;
  float fVar3;
  float fVar4;
  char cVar5;
  byte bVar6;
  ushort uVar7;
  Model *pMVar8;
  Subresource0x11 *pSVar9;
  actor_0x934 pNVar10;
  actor *act;
  int iVar11;
  undefined4 *puVar12;
  int iVar13;
  vec3 *pvVar14;
  AvatarMatrix *pAVar15;
  byte *pbVar16;
  float10 extraout_ST0;
  float fVar17;
  actor_0x93c pNVar18;
  float fVar19;
  float fVar20;
  float fVar21;
  uint64_t uVar22;
  Subresource0x11 *local_40;
  int local_3c;
  int *local_38;
  uint local_34;
  float local_24;
  float local_20;
  float local_1c;
  float local_18;
  float local_14;
  float local_10;
  
  act = param_1;
  fVar17 = 0.0;
  if (runtime::dx_timer <= 0.0) {
    fVar20 = runtime::DeltaTime * runtime::TimeScale;
  }
  else {
    fVar20 = 0.0;
  }
  if ((param_1->avatar).movementFreezeTimer <= 0.0) {
    fVar17 = (param_1->avatar).actionSpeed;
  }
  local_3c = 0;
  avatar::update(&param_1->avatar);
  if (*(int *)&param_1->field_0x9d8 != 0) {
    FUN_000f8640();
  }
  if (param_1->field5_0x950 == (undefined4 *)0x0) {
    if (0.0 < (float)(param_1->node0x93c).next) {
      if (runtime::dx_timer <= 0.0) {
        fVar19 = runtime::DeltaTime * runtime::TimeScale;
      }
      else {
        fVar19 = 0.0;
      }
      fVar21 = 0.0;
      if ((param_1->avatar).movementFreezeTimer <= 0.0) {
        fVar21 = (param_1->avatar).actionSpeed;
      }
      pNVar18 = (param_1->node0x93c).next;
      if (((float)pNVar18 <= 0.0) ||
         (pNVar18 = (actor_0x93c)((float)pNVar18 - fVar21 * fVar19),
         (param_1->node0x93c).next = pNVar18, 0.0 < (float)pNVar18)) {
        sin(((float)(param_1->node0x93c).next / (float)(param_1->node0x944).prev) * 3.1415927 -
            1.5707964);
        uVar22 = float10::to_uint64_t((extraout_ST0 + (float10)1.0) * (float10)127.5);
        (param_1->node0x944).next = (actor_0x944)uVar22;
      }
      else {
        (param_1->node0x93c).next = (actor_0x93c)0x0;
        avatar::destroy(&param_1->avatar);
      }
    }
    if (0.0 < fVar17 * fVar20) {
      pNVar1 = &param_1->node0x934;
      if (runtime::dx_timer <= 0.0) {
        param_1 = (actor *)(runtime::DeltaTime * runtime::TimeScale);
      }
      else {
        param_1 = (actor *)0x0;
      }
      FUN_000ef2d0((float)param_1,(astruct_46 *)pNVar1->prev);
      pMVar8 = (act->avatar).model;
      if ((pMVar8 == (Model *)0x0) || (pMVar8->descriptor == (ModelDescriptor *)0x0)) {
        local_40 = (Subresource0x11 *)0x0;
      }
      else {
        local_40 = pMVar8->descriptor->runtimeCtx->subres0x11;
      }
      if (((pMVar8 == (Model *)0x0) || (pMVar8->descriptor == (ModelDescriptor *)0x0)) ||
         (pSVar9 = pMVar8->descriptor->runtimeCtx->subres0x11, pSVar9 == (Subresource0x11 *)0x0)) {
        local_34 = 0;
      }
      else {
        local_34 = (uint)pSVar9->otherCount;
      }
      act->field5_0x950 = (undefined4 *)0x1;
      param_1 = (actor *)0x0;
      if (local_34 != 0) {
        pbVar16 = (byte *)((int)&local_40->someOtherPtrOrSize + 2);
        do {
          uVar7 = *(ushort *)(pbVar16 + -2);
          iVar13 = 0;
          if (*pbVar16 != 0) {
            local_38 = (int *)(&act->field_0xa68 + local_3c * 4);
            do {
              iVar11 = (int)(short)param_1;
              pNVar10 = (act->node0x934).prev;
              cVar5 = *(char *)&pNVar10[iVar11 * 0x2a + 0x7c].next;
              if ((act->field5_0x950 == (undefined4 *)0x0) || (cVar5 == '\0')) {
                puVar12 = (undefined4 *)0x0;
              }
              else {
                puVar12 = (undefined4 *)0x1;
              }
              act->field5_0x950 = puVar12;
              fVar17 = (&ADJ(pNVar10)->setup_position_)[iVar11 * 0x1c].y;
              fVar20 = (&ADJ(pNVar10)->setup_position_)[iVar11 * 0x1c].z;
              fVar19 = (&ADJ(pNVar10)->world_rot_)[iVar11 * 0x1c].x;
              fVar21 = (&ADJ(pNVar10)->world_rot_)[iVar11 * 0x1c].y;
              fVar3 = (&ADJ(pNVar10)->world_rot_)[iVar11 * 0x1c].z;
              fVar4 = (float)(&ADJ(pNVar10)->numSomethings)[iVar11 * 0x54];
              if (pbVar16[5] == 0) {
                bVar6 = (&local_40->otherCount)[iVar13 + (uint)uVar7];
                pAVar15 = (act->avatar).transforms;
                pAVar15[bVar6].pos.x = fVar17;
                pAVar15[bVar6].pos.y = fVar20;
                pAVar15[bVar6].pos.z = fVar19;
                (act->avatar).field235_0x2a0 = 0;
                (act->avatar).field234_0x29c = 0;
                pAVar15[bVar6].field9_0x44 = 1.4013e-45;
                pAVar15 = (act->avatar).transforms + (&local_40->otherCount)[iVar13 + (uint)uVar7];
                pvVar14 = &pAVar15->rotEuler;
                pvVar14->x = fVar21;
                (pAVar15->rotEuler).y = fVar3;
                (pAVar15->rotEuler).z = fVar4;
              }
              else {
                if (iVar13 == 0) {
                  local_24 = fVar17;
                  local_20 = fVar20;
                  local_1c = fVar19;
                  local_18 = fVar21;
                  local_14 = fVar3;
                  local_10 = fVar4;
                }
                bVar6 = (&local_40->otherCount)[iVar13 + (uint)uVar7];
                pAVar15 = (act->avatar).transforms;
                pAVar15[bVar6].pos.x = local_24;
                pAVar15[bVar6].pos.y = local_20;
                pAVar15[bVar6].pos.z = local_1c;
                (act->avatar).field234_0x29c = 0;
                (act->avatar).field235_0x2a0 = 0;
                pAVar15[bVar6].field9_0x44 = 1.4013e-45;
                pAVar15 = (act->avatar).transforms + (&local_40->otherCount)[iVar13 + (uint)uVar7];
                pvVar14 = &pAVar15->rotEuler;
                pvVar14->x = local_18;
                (pAVar15->rotEuler).y = local_14;
                (pAVar15->rotEuler).z = local_10;
              }
              Math::WrapAnglesRad(pvVar14);
              pAVar15->field9_0x44 = 1.4013e-45;
              if (((act->field4_0x94c == 0) &&
                  (pNVar10 = (act->node0x934).prev,
                  pNVar10[iVar11 * 0x2a + 0x7d].next != (actor_0x934)0x0)) &&
                 ((*(char *)((int)&pNVar10[iVar11 * 0x2a + 0x7c].next + 1) == '\0' &&
                  (0.75 < DAT_00506928)))) {
                ppCVar2 = &(act->avatar).callout;
                act->field4_0x94c = 1;
                if (ppCVar2 != (CalloutDescriptor **)0x0) {
                  ::actor::executeCalloutInDescriptor
                            (*ppCVar2,Explode,(CalloutCallback *)0x0,0,act,
                             (entityBodyPlayer_0x924)0x0);
                }
              }
              if (((int)param_1 < *(int *)&act->field_0xaa8) && ((actor *)local_38[8] == param_1)) {
                if (*local_38 != -1) {
                  iVar11 = (&DAT_00506930)[*local_38];
                  if (cVar5 == '\0') {
                    *(float *)(iVar11 + 0x1c) = fVar17;
                    *(float *)(iVar11 + 0x20) = fVar20;
                    *(float *)(iVar11 + 0x24) = fVar19;
                  }
                  else {
                    *(byte *)(iVar11 + 0x18) = *(byte *)(iVar11 + 0x18) | 8;
                    *(float *)(iVar11 + 8) = -1.0;
                    *local_38 = -1;
                  }
                }
                local_3c = local_3c + 1;
                local_38 = local_38 + 1;
              }
              if (pbVar16[5] == 0) {
                param_1 = (actor *)((int)param_1 + 1);
              }
              iVar13 = iVar13 + 1;
            } while (iVar13 < (int)(uint)*pbVar16);
          }
          if (pbVar16[5] != 0) {
            param_1 = (actor *)((int)param_1 + 1);
          }
          pbVar16 = pbVar16 + 0xc;
          local_34 = local_34 - 1;
        } while (local_34 != 0);
      }
      if (act->field5_0x950 != (undefined4 *)0x0) {
        ::actor::createOnDeathObjects(&act->avatar,1);
        (act->avatar).hasActor_ = true;
        ::actor::createOnDeathObjects(&act->avatar,0);
      }
    }
  }
  else if (0.0 < (float)(param_1->node0x93c).prev) {
    if (runtime::dx_timer <= 0.0) {
      fVar17 = runtime::DeltaTime * runtime::TimeScale;
    }
    else {
      fVar17 = 0.0;
    }
    fVar20 = 0.0;
    if ((param_1->avatar).movementFreezeTimer <= 0.0) {
      fVar20 = (param_1->avatar).actionSpeed;
    }
    pNVar18 = (param_1->node0x93c).prev;
    if ((0.0 < (float)pNVar18) &&
       (pNVar18 = (actor_0x93c)((float)pNVar18 - fVar20 * fVar17),
       (param_1->node0x93c).prev = pNVar18, (float)pNVar18 <= 0.0)) {
      (param_1->node0x93c).prev = (actor_0x93c)0x0;
      FUN_0013af80(0x40000000,&param_1->field_0x9dc,0);
      avatar::destroy(&param_1->avatar);
      return;
    }
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names


undefined4 entityAvatarFxExplodeParts::func5(avatar *param_1,undefined4 param_2,undefined4 param_3)

{
  undefined4 uVar1;
  
  if (param_1->hasActor_ == false) {
    ::actor::createOnDeathObjects(param_1,0);
  }
  if (param_1[1].rotEuler.x == 3.57331e-43) {
    ModelInstance::draw(param_1->model,&param_1->drawAffine,param_3);
    return 1;
  }
  uVar1 = FUN_00068610();
  return uVar1;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void entityAvatarFxExplodeParts::update(entityAvatarFxBurnup *param_1,Message *param_2)

{
  ObjMsgID OVar1;
  DataForInfoFromBackground_conflict1 *pDVar2;
  
  avatar::onMessage(&param_1->avatar,param_2);
  OVar1 = (param_2->header).msgId;
  if (OVar1 == Avatar_SceneInsert) {
    FUN_0003e850(param_1);
    entityAvatarFxBurnup::checkCollision0x4(param_1);
    pDVar2 = (param_1->avatar).infoList.prev;
    while (pDVar2 != (DataForInfoFromBackground_conflict1 *)0x0) {
      pDVar2 = (DataForInfoFromBackground_conflict1 *)pDVar2->field1_0x4;
      FUN_0011bda0();
    }
  }
  else if ((OVar1 == Scene_AvatarRemoved) &&
          ((actor *)param_1->someFloat == (param_2->header).someActor)) {
    FUN_00041d90(param_1);
    param_1->someFloat = 0.0;
    return;
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void entityAvatarFxMotionBlur::getVTable(void)

{
  avatar::initVTable((AvatarVTable *)&DAT_00504a54);
  _DAT_00504a54 = &LAB_00069080;
  _DAT_00504a58 = FUN_000690f0;
  _DAT_00504a5c = &LAB_00069220;
  _DAT_00504a60 = entityAvatarFxAnimEmitter::onMessage;
  _DAT_00504a64 = &LAB_00069250;
  _DAT_00504a68 = &LAB_00069410;
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void entityAvatarFxAnimEmitter::onMessage(entityAvatarFxBurnup *param_1,Message *param_2)

{
  DataForInfoFromBackground_conflict1 *pDVar1;
  
  avatar::onMessage(&param_1->avatar,param_2);
  if ((param_2->header).msgId == Avatar_SceneInsert) {
    FUN_0003e850(param_1);
    entityAvatarFxBurnup::checkCollision0x4(param_1);
    pDVar1 = (param_1->avatar).infoList.prev;
    while (pDVar1 != (DataForInfoFromBackground_conflict1 *)0x0) {
      pDVar1 = (DataForInfoFromBackground_conflict1 *)pDVar1->field1_0x4;
      FUN_0011bda0();
    }
  }
  return;
}




void entityAvatarFxBurnup::onMessage(entityAvatarFxBurnup *param_1,Message *param_2)

{
  avatar::onMessage(&param_1->avatar,param_2);
  if ((param_2->header).msgId == Avatar_SceneInsert) {
    FUN_0003e850(param_1);
    checkCollision0x4(param_1);
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


undefined ** entityFxCustomDustUp::getVTable(void)

{
  vtable[3] = switchD_000d4179::EmptyFunction;
  vtable[0] = getAllocDetails;
  vtable[1] = ctor;
  vtable[2] = switchD_000d4179::EmptyFunction;
  vtable[4] = updateFixed_;
  vtable[5] = switchD_000d4179::EmptyFunction;
  return vtable;
}




bool entityFxCustomDustUp::ctor(int param_1,int param_2)

{
  char cVar1;
  char *pcVar2;
  int iVar3;
  
  pcVar2 = (char *)(param_2 + 0x8c);
  iVar3 = (param_1 + 0x18) - (int)pcVar2;
  do {
    cVar1 = *pcVar2;
    pcVar2[iVar3] = cVar1;
    pcVar2 = pcVar2 + 1;
  } while (cVar1 != '\0');
  FUN_000764e0();
  return *(int *)(param_1 + 0x9c) != 0;
}




void entityFxCustomDustUp::updateFixed_(void *param_1,int param_2)

{
  float fVar1;
  float fVar2;
  
  if (runtime::dx_timer <= 0.0) {
    fVar1 = runtime::DeltaTime * runtime::TimeScale;
  }
  else {
    fVar1 = 0.0;
  }
  *(float *)((int)param_1 + 0x10) = *(float *)((int)param_1 + 0x10) + fVar1;
  if (runtime::dx_timer <= 0.0) {
    fVar1 = runtime::DeltaTime * runtime::TimeScale;
  }
  else {
    fVar1 = 0.0;
  }
  fVar2 = 0.0;
  if (*(float *)(param_2 + 0x930) <= 0.0) {
    fVar2 = *(float *)(param_2 + 0x92c);
  }
  if (*(float *)((int)param_1 + 0xa0) <= 0.0) {
    *(float *)((int)param_1 + 0xa0) = 0.01;
    FUN_00076480();
    FUN_00076320();
    FUN_00076480();
    FUN_00076320();
    FUN_00076480();
    FUN_00076320();
  }
  else {
    *(float *)((int)param_1 + 0xa0) = *(float *)((int)param_1 + 0xa0) - fVar2 * fVar1;
  }
  if (*(int *)((int)param_1 + 0x98) == 0) {
    Assets::DeleteResource_(param_1);
    return;
  }
  return;
}




void entityFxCustomDustUp::getAllocDetails(undefined4 *param_1)

{
  *param_1 = 0xa8;
  param_1[1] = 0x10c;
  return;
}



// WARNING: Globals starting with '_' overlap smaller symbols at the same address


undefined ** fxCustom::getVTable(void)

{
  vtable[0] = actorState::getAllocDetails;
  vtable[1] = ctor;
  vtable[2] = dtor;
  vtable[3] = switchD_000d4179::EmptyFunction;
  vtable[4] = updateFixed_;
  vtable[5] = switchD_000d4179::EmptyFunction;
  return vtable;
}




undefined4 fxCustom::ctor(fxCustom *fx,fxCustomParams *params)

{
  int iVar1;
  int iVar2;
  
  iVar1 = params->field1_0x8;
  *(int *)&fx->params0x8 = iVar1;
  iVar2 = iVar1 + 0x1d4;
  iVar1 = *(int *)(iVar1 + 0x1d8);
  while (iVar1 != 0) {
    iVar2 = *(int *)(iVar2 + 4);
    iVar1 = *(int *)(iVar2 + 4);
  }
  *(undefined1 **)(iVar2 + 4) = &fx->field_0x8;
  *(int *)&fx->field_0x8 = iVar2;
  *(undefined4 *)&fx->field_0xc = 0;
  return 1;
}




void fxCustom::dtor(int param_1)

{
  if (*(int *)(param_1 + 8) != 0) {
    *(undefined4 *)(*(int *)(param_1 + 8) + 4) = *(undefined4 *)(param_1 + 0xc);
  }
  if (*(undefined4 **)(param_1 + 0xc) != (undefined4 *)0x0) {
    **(undefined4 **)(param_1 + 0xc) = *(undefined4 *)(param_1 + 8);
  }
  *(undefined4 *)(param_1 + 8) = 0;
  *(undefined4 *)(param_1 + 0xc) = 0;
  return;
}




void fxCustom::updateFixed_(fxCustom *fx)

{
  float elapsed;
  
  elapsed = 0.0;
  if (runtime::dx_timer <= 0.0) {
    elapsed = runtime::DeltaTime * runtime::TimeScale;
  }
  fx->elapsed = fx->elapsed + elapsed;
  return;
}




int UpdateFX(void)

{
  int iVar1;
  undefined4 *puVar2;
  int iVar3;
  float fVar4;
  
  puVar2 = &DAT_00506930;
  do {
    if ((astruct_46 *)*puVar2 != (astruct_46 *)0x0) {
      fVar4 = 0.0;
      if (runtime::dx_timer <= 0.0) {
        fVar4 = runtime::DeltaTime * runtime::TimeScale;
      }
      iVar1 = FUN_000ef2d0(fVar4,(astruct_46 *)*puVar2);
      if (iVar1 == 0) {
        FUN_000ed2e0();
        *puVar2 = 0;
      }
    }
    puVar2 = puVar2 + 1;
  } while ((int)puVar2 < 0x506c50);
  if (DAT_005068ec != 0) {
    iVar1 = 0;
    do {
      if (*(int *)(iVar1 + 0x68 + DAT_005068ec) == -2) {
        FUN_000ec0b0();
      }
      iVar1 = iVar1 + 0x74;
    } while (iVar1 < 0x16a8);
  }
  iVar1 = 0;
  if (DAT_005068d8 != 0) {
    iVar3 = 0;
    do {
      iVar1 = DAT_005068d8 + iVar3;
      if (*(int *)(DAT_005068d8 + 0x7c + iVar3) == -2) {
        iVar1 = FUN_000eb9f0();
      }
      iVar3 = iVar3 + 0x84;
    } while (iVar3 < 0x19c8);
  }
  return iVar1;
}




void fxParticleImpactFlash::deleteInitAssets(fxParticleImpactFlash *fx)

{
  void *pvVar1;
  
  if (fx->someAsset1 != (void *)0x0) {
    Assets::DestroyAssetOrDecrement(fx->someAsset1);
    fx->someAsset1 = (void *)0x0;
  }
  if (fx->someAsset2 != (Asset *)0x0) {
    pvVar1 = (void *)ModelResource::dropResource(fx->someAsset2);
    Assets::DestroyAssetOrDecrement(pvVar1);
    fx->someAsset2 = (void *)0x0;
  }
  fx->field184_0x13c = 1;
  return;
}



undefined4
FUN_000ed730(int *param_1,float param_2,float param_3,undefined4 param_4,int param_5,int param_6,
            int param_7)

{
  byte bVar1;
  int *piVar2;
  bool bVar3;
  void *pvVar4;
  int *piVar5;
  int unaff_EDI;
  
  piVar5 = param_1;
  bVar3 = false;
  if (*param_1 == 0x5f646961) {
    Assets::GetResourceBytes((char *)param_1,&param_1);
    piVar2 = param_1;
    param_1 = piVar2;
    if (param_1 == (int *)0x0) {
      runtime::ExitGame(2);
      param_1 = piVar2;
    }
  }
  else {
    param_1 = (int *)0x0;
  }
  piVar2 = *(int **)(unaff_EDI + 0x144);
  if (param_1 != piVar2) {
    if (piVar2 != (int *)0x0) {
      Assets::DestroyAssetOrDecrement(piVar2);
      *(undefined4 *)(unaff_EDI + 0x144) = 0;
    }
    if (*(Asset **)(unaff_EDI + 0x158) != (Asset *)0x0) {
      pvVar4 = (void *)ModelResource::dropResource(*(Asset **)(unaff_EDI + 0x158));
      Assets::DestroyAssetOrDecrement(pvVar4);
      *(undefined4 *)(unaff_EDI + 0x158) = 0;
    }
    FUN_000ef790();
    bVar3 = true;
  }
  Assets::DestroyAssetOrDecrement(param_1);
  if (bVar3) {
    if (*piVar5 == 0x5f646961) {
      Assets::GetResourceBytes((char *)piVar5,&param_1);
      piVar5 = param_1;
      if (param_1 == (int *)0x0) {
        runtime::ExitGame(2);
      }
    }
    else {
      piVar5 = (int *)0x0;
    }
    *(int **)(unaff_EDI + 0x144) = piVar5;
  }
  bVar1 = *(byte *)(*(int *)(unaff_EDI + 0x144) + 0x11);
  if (bVar1 == 0) {
    *(undefined4 *)(unaff_EDI + 0x148) = 0;
  }
  else {
    *(uint *)(unaff_EDI + 0x148) = bVar1 - 1;
  }
  *(float *)(unaff_EDI + 0x14c) = (1.0 - param_3) * param_2;
  *(float *)(unaff_EDI + 0x150) = (param_3 + 1.0) * param_2;
  *(undefined1 *)(unaff_EDI + 0x154) = 0;
  *(uint *)(unaff_EDI + 0x13c) = (param_7 != 0) - 1 & 2;
  *(undefined4 *)(unaff_EDI + 0x140) = param_4;
  if (param_5 == 1) {
    *(undefined1 *)(unaff_EDI + 0x154) = 4;
  }
  else if (param_5 == 2) {
    *(undefined1 *)(unaff_EDI + 0x154) = 8;
  }
  else if (param_5 == 3) {
    *(undefined1 *)(unaff_EDI + 0x154) = 0x10;
  }
  if (param_6 != 0) {
    *(byte *)(unaff_EDI + 0x154) = *(byte *)(unaff_EDI + 0x154) | 1;
  }
  return *(undefined4 *)(unaff_EDI + 0x148);
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names


BOOL GetFxName(char *outName,char *param_2,uint stringId,char *param_4,char *param_5)

{
  void *found;
  BOOL BVar1;
  
  Utils::SprintfToUpper
            (outName,"aid_fxemitter_%s_kickedup%s_%s_%s%s",g_GHOULIES,param_2,
             (&FxEmitterStringNone)[stringId & 0b11111111],param_5);
  found = Assets::newAssetInstance(Assets::LoadedResources,outName);
  if (found == (void *)0x0) {
    BVar1 = LoadResourceFromFiles((int)outName);
    if (BVar1 == 0) {
      Utils::SprintfToUpper
                (outName,"aid_fxemitter_%s_kickedup%s_%s_default",g_GHOULIES,param_2,
                 (&FxEmitterStringNone)[stringId & 0b11111111],param_4);
      found = Assets::newAssetInstance(Assets::LoadedResources,outName);
      if (found == (void *)0x0) {
        BVar1 = LoadResourceFromFiles((int)outName);
        if (BVar1 == 0) {
          *outName = '\0';
          return 0;
        }
      }
    }
  }
  return 1;
}



// WARNING: Globals starting with '_' overlap smaller symbols at the same address


