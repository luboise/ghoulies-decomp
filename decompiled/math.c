/* math.c - Math helpers: trig, vectors/matrices, floats, random */
#include "math.h"

BOOL Random::thresholdCheck(uint *param_1,float threshold)

{
  uint uVar1;
  
  uVar1 = *param_1 * 0x19660d + 0x3c6ef35f;
  *param_1 = uVar1;
  if ((float)(uVar1 & 0x7fffff | 0x3f800000) - 1.0 <= threshold) {
    return 1;
  }
  return 0;
}



// WARNING: Removing unreachable block (ram,0x0001925d)
// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void __fastcall FUN_0001f240(undefined4 param_1,int param_2,vec3 *param_3,int param_4)

{
  void *this;
  int in_EAX;
  int unaff_EDI;
  bool bVar1;
  float fVar2;
  
  this = *(void **)(param_2 + 8);
  if (param_4 != 0) {
    FUN_0013ad60(this,(unaff_EDI != 0) + 4,param_3);
    return;
  }
  if (in_EAX == 0) {
    bVar1 = *(short *)((int)this + 0xcdc) == 1;
  }
  else {
    bVar1 = true;
    if ((*(short *)((int)this + 0xcdc) != 1) || (*(short *)(in_EAX + 0xcdc) == 1)) {
      bVar1 = false;
    }
  }
  if (*(int *)(param_2 + 0x268) == 0) {
    fVar2 = 1.0;
  }
  else {
    fVar2 = *(float *)(*(int *)(param_2 + 0x268) + 400);
  }
  if (bVar1) {
    FUN_0013adc0((unaff_EDI != 0) + '\x06',fVar2);
    return;
  }
  FUN_0013adc0((unaff_EDI != 0) + '\x02',fVar2);
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void FUN_000244e0(vec3 *param_1)

{
  float fVar1;
  int in_EAX;
  float10 fVar2;
  float fVar3;
  float local_c;
  float local_4;
  
  fVar1 = *(float *)(in_EAX + 0x18);
  vec3::getTurnAngle(param_1,&local_4);
  fVar3 = modf(local_4 + 3.1415927,6.2831855);
  if (fVar3 < -3.1415927) {
    fVar3 = fVar3 + 6.2831855;
  }
  if (3.1415927 <= fVar3) {
    fVar3 = fVar3 - 6.2831855;
  }
  local_c = modf(fVar3 - fVar1,6.2831855);
  if (local_c < -3.1415927) {
    local_c = local_c + 6.2831855;
  }
  if (3.1415927 <= local_c) {
    local_c = local_c - 6.2831855;
  }
  local_4 = local_c;
  fVar2 = abs_float(local_c);
  if (((0.05235988 <= (float)fVar2) && ((float)fVar2 < 0.7853982)) && (local_c <= 0.0)) {
    return;
  }
  return;
}




int GetMatchesInScriptTable___(char *param_1,ScripttableResource *param_2)

{
  int iVar1;
  byte bVar2;
  byte bVar3;
  byte *pbVar4;
  int i;
  int iVar5;
  int max_index;
  
  max_index = param_2->numEntries - 1;
  i = 0;
  if (-1 < max_index) {
    do {
      iVar1 = max_index + i >> 1;
      pbVar4 = (byte *)param_2->entries[iVar1].goalName;
      iVar5 = (int)param_1 - (int)pbVar4;
      while( true ) {
        bVar2 = *pbVar4;
        if (0x20 < bVar2) {
          bVar2 = bVar2 & 0xdf;
        }
        bVar3 = pbVar4[iVar5];
        if (0x20 < bVar3) {
          bVar3 = bVar3 & 0xdf;
        }
        if (bVar2 != bVar3) break;
        pbVar4 = pbVar4 + 1;
        if (bVar2 == 0) goto LAB_0002a7da;
      }
      iVar5 = (uint)bVar2 - (uint)bVar3;
      if (iVar5 < 0) {
        i = iVar1 + 1;
      }
      else {
        if ((uint)bVar2 == (uint)bVar3 || iVar5 < 0) {
LAB_0002a7da:
          return (int)(param_2->entries + iVar1);
        }
        max_index = iVar1 + -1;
      }
    } while (i <= max_index);
  }
  return 0;
}




void vec3::normalise(vec3 *v)

{
  float10 fVar1;
  float fVar2;
  
  fVar2 = v->x * v->x + v->y * v->y + v->z * v->z;
  if (fVar2 != 0.0) {
    fVar1 = (float10)invsqrt(fVar2);
    v->x = (float)(fVar1 * (float10)v->x);
    v->y = (float)(fVar1 * (float10)v->y);
    v->z = (float)(fVar1 * (float10)v->z);
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void Quaternion::slerpIntoQ1(Quaternion *q1,Quaternion *q2,float slerpT,byte changeMask)

{
  float10 fVar1;
  float fVar2;
  float fVar3;
  
                    // If rotation not present in this keyframe, return identity
  if ((changeMask & 0b11100000) == 0) {
    q1->w = 1.0;
    return;
  }
                    // If none of the channels are to be inferred, then just calculate w from the
                    // new real value and use it
  if ((changeMask & 0b00011100) == 0b00011100) {
    fVar3 = 0.0;
    fVar2 = 1.0 - (q1->x * q1->x + q1->y * q1->y + q1->z * q1->z);
    if (0.0 < fVar2) {
      fVar1 = scaled_invsqrt(fVar2);
      fVar3 = (float)fVar1;
    }
    q1->w = fVar3;
    return;
  }
  fVar3 = 1.0 - (q1->x * q1->x + q1->y * q1->y + q1->z * q1->z);
  if (fVar3 <= 0.0) {
    fVar3 = 0.0;
  }
  else {
    fVar1 = scaled_invsqrt(fVar3);
    fVar3 = (float)fVar1;
  }
  fVar2 = 0.0;
  q1->w = fVar3;
                    // Always reconstruct w for q2
  fVar3 = 1.0 - (q2->x * q2->x + q2->y * q2->y + q2->z * q2->z);
  if (0.0 < fVar3) {
    fVar1 = scaled_invsqrt(fVar3);
    fVar2 = (float)fVar1;
  }
  q2->w = fVar2;
                    // Slerp into q1
  SLERP(q1,q2,q1,slerpT);
  return;
}



void ParsedAnimVal::getQuat
               (ParsedAnimVal *parsed,KFTransform *kft,uint channelMask,float unsignedScaler,
               float defaultVal)

{
  short sVar1;
  byte numBitsToRead;
  uint flags;
  Quaternion *q;
  float *f_ptr;
  bool bVar2;
  uint delta1;
  uint delta2;
  uint i_mask;
  byte local_18;
  undefined3 uStack_17;
  uint flagss;
  Quaternion local_10;
  short *short;
  
                    // Bottom byte only
  flags = channelMask & 0xff;
  q = &local_10;
                    // 6 iterations
  i_mask = 0b10000000;
  f_ptr = (float *)kft;
  flagss = flags;
  do {
    if ((i_mask & flags) == 0) {
                    // Cursor not advanced when skipping channel
      q->x = defaultVal;
      *f_ptr = defaultVal;
    }
    else {
      short = parsed->shorts;
                    // If bit 6 not set (if positive number???)
                    // 
                    // 6, 5, 4
      if ((flags & i_mask >> 3) == 0) {
        sVar1 = *short;
        parsed->shorts = short + 1;
        numBitsToRead =
             ((parsed->nibbleMask & *parsed->section2) >> ((parsed->oddBitSize & 0b00000111) << 2))
             + 1;
        bVar2 = parsed->oddBitSize == '\0';
        parsed->section2 = parsed->section2 + parsed->oddBitSize;
        _local_18 = CONCAT31(uStack_17,numBitsToRead);
        parsed->oddBitSize = bVar2;
        delta2 = 0;
        delta1 = 0;
        parsed->nibbleMask = 0b00001111 << (bVar2 << 2);
        ReadQuatFromKeyframes
                  (parsed->startKeyframe,parsed->endKeyframe,&parsed->curByte,&parsed->curBit,
                   &delta1,&delta2,numBitsToRead);
                    // Write a different value to the transform compared to teh local quat?
        *f_ptr = (float)(int)(delta1 + (int)sVar1) * unsignedScaler;
        q->x = (float)(int)(delta2 + (int)sVar1) * unsignedScaler;
        flags = flagss;
      }
      else {
        sVar1 = *short;
        parsed->shorts = short + 1;
        q->x = (float)(int)sVar1 * unsignedScaler;
        *f_ptr = (float)(int)sVar1 * unsignedScaler;
      }
    }
    i_mask = i_mask >> 1;
    f_ptr = f_ptr + 1;
    q = (Quaternion *)&q->y;
                    // 3 times
  } while (i_mask != 0b00010000);
                    // Goes to 0x2e3a0, which slerps 2 quaternions together
  (*(code *)parsed->slerpCallback)(kft,&local_10,parsed->slerpT,channelMask);
  return;
}




undefined4 FUN_00039580(char *param_1,uint param_2,vec3 *param_3)

{
  i16 soundSourceIndex;
  undefined2 extraout_var;
  undefined2 extraout_var_00;
  undefined2 uVar1;
  
  soundSourceIndex = Audio::CreateSoundSourceAndReturnIndex(AudioType1);
  uVar1 = extraout_var;
  if (soundSourceIndex != -1) {
    Audio::SoundSources[soundSourceIndex].flags = param_2;
    if (Audio::SoundSources[soundSourceIndex].soundSource != (soundSource *)0x0) {
      Audio::SetSoundSourcePosition(Audio::SoundSources[soundSourceIndex].soundSource,param_3);
    }
    Audio::FindBySoundbankStrAndPlay(param_1,soundSourceIndex);
    uVar1 = extraout_var_00;
  }
  return CONCAT22(uVar1,soundSourceIndex);
}




void __fastcall FUN_00039b10(vec3 *param_1)

{
  short in_AX;
  
  if (Audio::SoundSources[in_AX].soundSource != (soundSource *)0x0) {
    Audio::SetSoundSourcePosition(Audio::SoundSources[in_AX].soundSource,param_1);
  }
  return;
}




undefined4 __fastcall FUN_0003ae60(undefined4 param_1,int param_2,vec3 *param_3)

{
  Model *pMVar1;
  ModelDescriptor *modelRes;
  byte bVar2;
  actor *unaff_ESI;
  
  if (((param_2 != -1) && (pMVar1 = (unaff_ESI->avatar).model, pMVar1 != (Model *)0x0)) &&
     (modelRes = pMVar1->descriptor, modelRes != (ModelDescriptor *)0x0)) {
    bVar2 = ModelDescriptor::getBoneIdxFromRigid(modelRes,(short)param_2);
    if ((bVar2 != 0xff) && (bVar2 != 0xffffffff)) {
      actor::getTransformedBonePos(unaff_ESI,&Game::someGlobalPos,(ushort)bVar2,param_3);
      return 1;
    }
  }
  return 0;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields

void actor::getTransformedBonePos
               (actor *rootActor,vec3 *localPos,uint16_t boneIndex,vec3 *transformed)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  Model *pMVar6;
  AffineTransform *affine;
  Skeleton *skeleton;
  ndSkeletonBone *bone;
  float lx;
  float lx2;
  float ly;
  float ly2;
  float lz;
  float lz2;
  float normalization_term;
  float ty;
  float tz;
  WeirdTransform *weird;
  
  pMVar6 = (rootActor->avatar).model;
  if (pMVar6 == (Model *)0x0) {
    skeleton = (Skeleton *)0x0;
  }
  else {
    skeleton = pMVar6->skeleton;
    if (skeleton == (Skeleton *)0x0) {
      skeleton = pMVar6->skeleton2;
    }
  }
  if ((pMVar6->ndSkeleton == (ndSkeleton *)0x0) ||
     (bone = pMVar6->ndSkeleton->bonesStart, bone == (ndSkeletonBone *)0x0)) {
    bone = (ndSkeletonBone *)0x0;
  }
  else {
    bone = bone + boneIndex;
  }
  graphics::bone_acc = (WeirdTransform *)&g_affine;
  g_affine.m[0][0] = (rootActor->avatar).drawAffine.m[0][0];
  g_affine.m[0][1] = (rootActor->avatar).drawAffine.m[0][1];
  g_affine.m[0][2] = (rootActor->avatar).drawAffine.m[0][2];
  g_affine.m[0][3] = (rootActor->avatar).drawAffine.m[0][3];
  g_affine.m[1][0] = (rootActor->avatar).drawAffine.m[1][0];
  g_affine.m[1][1] = (rootActor->avatar).drawAffine.m[1][1];
  g_affine.m[1][2] = (rootActor->avatar).drawAffine.m[1][2];
  g_affine.m[1][3] = (rootActor->avatar).drawAffine.m[1][3];
  g_affine.m[2][0] = (rootActor->avatar).drawAffine.m[2][0];
  g_affine.m[2][1] = (rootActor->avatar).drawAffine.m[2][1];
  g_affine.m[2][2] = (rootActor->avatar).drawAffine.m[2][2];
  g_affine.m[2][3] = (rootActor->avatar).drawAffine.m[2][3];
  affine = Skeleton::getBoneAffineIntoGlobal(skeleton,(uint)boneIndex);
  Graphics::leftCombineTransforms(&graphics::bone_acc->affine1,&graphics::bone_acc->affine1,affine);
  weird = graphics::bone_acc;
  fVar1 = (bone->globalTransform).z;
  lx = (bone->globalTransform).y;
  normalization_term = (bone->globalTransform).x;
  (graphics::bone_acc->affine2).m[0][0] = 1.0;
  (weird->affine2).m[0][1] = 0.0;
  (weird->affine2).m[0][2] = 0.0;
  (weird->affine2).m[0][3] = normalization_term;
  (weird->affine2).m[1][0] = 0.0;
  (weird->affine2).m[1][1] = 1.0;
  (weird->affine2).m[1][2] = 0.0;
  (weird->affine2).m[1][3] = lx;
  (weird->affine2).m[2][0] = 0.0;
  (weird->affine2).m[2][1] = 0.0;
  (weird->affine2).m[2][2] = 1.0;
  (weird->affine2).m[2][3] = fVar1;
  Graphics::leftCombineTransforms
            (&graphics::bone_acc->affine1,&graphics::bone_acc->affine1,&graphics::bone_acc->affine2)
  ;
  fVar1 = (graphics::bone_acc->affine1).m[1][0];
  lx = localPos->x;
  normalization_term = (graphics::bone_acc->affine1).m[2][0];
  lx2 = localPos->x;
  fVar2 = (graphics::bone_acc->affine1).m[1][2];
  lz = localPos->z;
  fVar3 = (graphics::bone_acc->affine1).m[1][1];
  ly = localPos->y;
  fVar4 = (graphics::bone_acc->affine1).m[2][2];
  lz2 = localPos->z;
  ty = (graphics::bone_acc->affine1).m[1][3];
  fVar5 = (graphics::bone_acc->affine1).m[2][1];
  ly2 = localPos->y;
  tz = (graphics::bone_acc->affine1).m[2][3];
  transformed->x =
       (graphics::bone_acc->affine1).m[0][2] * localPos->z +
       (graphics::bone_acc->affine1).m[0][1] * localPos->y +
       localPos->x * (graphics::bone_acc->affine1).m[0][0] + (graphics::bone_acc->affine1).m[0][3];
  transformed->y = fVar2 * lz + fVar1 * lx + fVar3 * ly + ty;
  transformed->z = fVar4 * lz2 + normalization_term * lx2 + fVar5 * ly2 + tz;
  return;
}




void __fastcall FUN_0003b050(undefined4 param_1,int param_2,ushort param_3,vec3 *param_4)

{
  float fVar1;
  float fVar2;
  float fVar3;
  WeirdTransform *pWVar4;
  AffineTransform *m2;
  Skeleton *skeleton;
  int iVar5;
  
  iVar5 = *(int *)(param_2 + 0x204);
  if (iVar5 == 0) {
    skeleton = (Skeleton *)0x0;
  }
  else {
    skeleton = *(Skeleton **)(iVar5 + 0x168);
    if (skeleton == (Skeleton *)0x0) {
      skeleton = *(Skeleton **)(iVar5 + 0x164);
    }
  }
  if ((*(int *)(iVar5 + 0x1bc) == 0) ||
     (iVar5 = *(int *)(*(int *)(iVar5 + 0x1bc) + 0x24), iVar5 == 0)) {
    iVar5 = 0;
  }
  else {
    iVar5 = (uint)param_3 * 0x20 + iVar5;
  }
  graphics::bone_acc = (WeirdTransform *)&g_affine;
  g_affine.m[0][0] = *(float *)(param_2 + 0x2ac);
  g_affine.m[0][1] = *(float *)(param_2 + 0x2b0);
  g_affine.m[0][2] = *(float *)(param_2 + 0x2b4);
  g_affine.m[0][3] = *(float *)(param_2 + 0x2b8);
  g_affine.m[1][0] = *(float *)(param_2 + 700);
  g_affine.m[1][1] = *(float *)(param_2 + 0x2c0);
  g_affine.m[1][2] = *(float *)(param_2 + 0x2c4);
  g_affine.m[1][3] = *(float *)(param_2 + 0x2c8);
  g_affine.m[2][0] = *(float *)(param_2 + 0x2cc);
  g_affine.m[2][1] = *(float *)(param_2 + 0x2d0);
  g_affine.m[2][2] = *(float *)(param_2 + 0x2d4);
  g_affine.m[2][3] = *(float *)(param_2 + 0x2d8);
  m2 = Skeleton::getBoneAffineIntoGlobal(skeleton,(uint)param_3);
  Graphics::leftCombineTransforms(&graphics::bone_acc->affine1,&graphics::bone_acc->affine1,m2);
  pWVar4 = graphics::bone_acc;
  fVar1 = *(float *)(iVar5 + 0x18);
  fVar2 = *(float *)(iVar5 + 0x14);
  fVar3 = *(float *)(iVar5 + 0x10);
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
  Math::GetEulerAngles((D3DXMATRIX *)graphics::bone_acc,param_4);
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names


undefined4 FUN_0003c470(avatar *av,avatar *param_2,vec3 *param_3,int param_4)

{
  float10 fVar1;
  float fVar2;
  float fVar3;
  vec3 local_24;
  vec3 local_18;
  vec3 local_c;
  
  fVar3 = *(float *)(param_4 + 0x1c);
  avatar::getWorldPosition(av,&local_c);
  avatar::getWorldPosition(param_2,&local_18);
  local_24.x = local_18.x - local_c.x;
  local_24.z = local_18.z - local_c.z;
  fVar2 = local_24.z * local_24.z + local_24.x * local_24.x;
  local_24.y = 0.0;
  if (fVar2 != 0.0) {
    fVar1 = (float10)invsqrt(fVar2);
    local_24.x = (float)((float10)local_24.x * fVar1);
    local_24.y = (float)((float10)0.0 * fVar1);
    local_24.z = (float)((float10)local_24.z * fVar1);
  }
  avatar::getWorldPosition(av,&local_18);
  fVar2 = (*(float *)(param_4 + 0xc) * local_24.z + *(float *)(param_4 + 8) * local_24.y +
          *(float *)(param_4 + 4) * local_24.x) -
          (local_18.z * local_24.z + local_18.y * local_24.y + local_24.x * local_18.x);
  if (fVar2 < fVar3) {
    fVar3 = fVar3 - fVar2;
    param_3->x = local_24.x * fVar3 + param_3->x;
    param_3->y = local_24.y * fVar3 + param_3->y;
    param_3->z = local_24.z * fVar3 + param_3->z;
    return 1;
  }
  return 0;
}




void __thiscall FUN_0003d510(int param_1,actor *param_2,vec3 *param_3)

{
  Model *pMVar1;
  vec3 *in_EAX;
  Skeleton *pSVar2;
  Skeleton *skeleton;
  
  if (*(int *)(param_1 + 0x1c) == 0) {
    if (*(short *)(param_1 + 0xc) != -1) {
      FUN_0003ae60();
      if ((*(byte *)(param_1 + 0x20) & 4) != 0) {
        FUN_0003b160(param_3);
        return;
      }
      goto LAB_0003d5cf;
    }
  }
  else if (*(int *)(param_1 + 0x1c) == 1) {
    pMVar1 = (param_2->avatar).model;
    if (pMVar1 == (Model *)0x0) {
      pSVar2 = (Skeleton *)0x0;
    }
    else {
      pSVar2 = pMVar1->skeleton;
      if (pSVar2 == (Skeleton *)0x0) {
        pSVar2 = pMVar1->skeleton2;
      }
    }
    FUN_00051ce0((int)pSVar2,*(undefined4 *)(param_1 + 0x10),in_EAX,&(param_2->avatar).drawAffine);
    if ((*(byte *)(param_1 + 0x20) & 4) != 0) {
      actor::getEulers(param_3,skeleton,param_2,*(undefined4 *)(param_1 + 0x10));
      return;
    }
    goto LAB_0003d5cf;
  }
  avatar::getWorldPosition(&param_2->avatar,in_EAX);
  if ((*(byte *)(param_1 + 0x20) & 4) != 0) {
    avatar::getWorldRotation(&param_2->avatar,param_3);
    return;
  }
LAB_0003d5cf:
  param_3->z = 0.0;
  param_3->y = 0.0;
  param_3->x = 0.0;
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


float10 FUN_0003d9a0(avatar *param_1)

{
  ModelDescriptor *pMVar1;
  uint uVar2;
  ModelFooterEntry *pMVar3;
  float10 fVar4;
  
  if ((param_1->model != (Model *)0x0) &&
     (pMVar1 = param_1->model->descriptor, pMVar1 != (ModelDescriptor *)0x0)) {
    uVar2 = 0;
    if (pMVar1->numFooterEntries != 0) {
      pMVar3 = pMVar1->footerEntries;
      do {
        if (pMVar3->subresourceType == ModelMatrix) {
          uVar2 = pMVar1->footerEntries[uVar2].offset;
          if (uVar2 != 0) {
            fVar4 = abs_float(param_1->uniformScale * *(float *)(uVar2 + 0x10) * (param_1->scale).z)
            ;
            return fVar4;
          }
          break;
        }
        uVar2 = uVar2 + 1;
        pMVar3 = pMVar3 + 1;
      } while (uVar2 < pMVar1->numFooterEntries);
    }
  }
  return (float10)0.0;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


float10 FUN_0003db30(void)

{
  int *piVar1;
  int iVar2;
  uint uVar3;
  int *piVar4;
  int unaff_EDI;
  float10 fVar5;
  
  if ((*(int **)(unaff_EDI + 0x204) != (int *)0x0) &&
     (piVar1 = (int *)**(int **)(unaff_EDI + 0x204), piVar1 != (int *)0x0)) {
    uVar3 = 0;
    if (piVar1[1] != 0) {
      piVar4 = (int *)*piVar1;
      do {
        if (*piVar4 == 5) {
          iVar2 = ((int *)*piVar1)[uVar3 * 2 + 1];
          if (iVar2 != 0) {
            fVar5 = abs_float(*(float *)(unaff_EDI + 0x200) * *(float *)(iVar2 + 0x24) *
                              *(float *)(unaff_EDI + 0x38));
            return fVar5;
          }
          break;
        }
        uVar3 = uVar3 + 1;
        piVar4 = piVar4 + 2;
      } while (uVar3 < (uint)piVar1[1]);
    }
  }
  return (float10)0.0;
}




float10 FUN_0003db90(void)

{
  int *piVar1;
  int iVar2;
  uint uVar3;
  int *piVar4;
  int unaff_EDI;
  float10 fVar5;
  
  if ((*(int **)(unaff_EDI + 0x204) != (int *)0x0) &&
     (piVar1 = (int *)**(int **)(unaff_EDI + 0x204), piVar1 != (int *)0x0)) {
    uVar3 = 0;
    if (piVar1[1] != 0) {
      piVar4 = (int *)*piVar1;
      do {
        if (*piVar4 == 5) {
          iVar2 = ((int *)*piVar1)[uVar3 * 2 + 1];
          if (iVar2 != 0) {
            fVar5 = abs_float(*(float *)(unaff_EDI + 0x200) * *(float *)(iVar2 + 0x20) *
                              *(float *)(unaff_EDI + 0x38));
            return fVar5;
          }
          break;
        }
        uVar3 = uVar3 + 1;
        piVar4 = piVar4 + 2;
      } while (uVar3 < (uint)piVar1[1]);
    }
  }
  return (float10)0.0;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void FUN_00040640(avatar *param_1,float *param_2,vec3 *param_3,int param_4)

{
  AvatarMatrix *pAVar1;
  float fVar2;
  float fVar3;
  Model *pMVar4;
  int in_EAX;
  AffineTransform *m2;
  float *pfVar5;
  Skeleton *skeleton;
  float fVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  float fVar10;
  float fVar11;
  vec3 local_3c;
  AffineTransform local_30;
  
  pAVar1 = param_1->transforms + in_EAX;
  if (pAVar1->field9_0x44 == 0.0) {
    graphics::bone_acc = (WeirdTransform *)&g_affine;
    g_affine.m[0][0] = (param_1->drawAffine).m[0][0];
    g_affine.m[0][1] = (param_1->drawAffine).m[0][1];
    g_affine.m[0][2] = (param_1->drawAffine).m[0][2];
    g_affine.m[0][3] = (param_1->drawAffine).m[0][3];
    g_affine.m[1][0] = (param_1->drawAffine).m[1][0];
    g_affine.m[1][1] = (param_1->drawAffine).m[1][1];
    g_affine.m[1][2] = (param_1->drawAffine).m[1][2];
    g_affine.m[1][3] = (param_1->drawAffine).m[1][3];
    g_affine.m[2][0] = (param_1->drawAffine).m[2][0];
    g_affine.m[2][1] = (param_1->drawAffine).m[2][1];
    g_affine.m[2][2] = (param_1->drawAffine).m[2][2];
    g_affine.m[2][3] = (param_1->drawAffine).m[2][3];
    if (pAVar1->matrixFlagVal != 0xffffffff) {
      pMVar4 = param_1->model;
      if (pMVar4 == (Model *)0x0) {
        skeleton = (Skeleton *)0x0;
      }
      else {
        skeleton = pMVar4->skeleton;
        if (skeleton == (Skeleton *)0x0) {
          skeleton = pMVar4->skeleton2;
        }
      }
      if (skeleton == (Skeleton *)0x0) {
        m2 = (AffineTransform *)0x0;
      }
      else {
        m2 = Skeleton::getBoneAffineIntoGlobal(skeleton,pAVar1->matrixFlagVal);
      }
      Graphics::leftCombineTransforms(&graphics::bone_acc->affine1,&graphics::bone_acc->affine1,m2);
    }
    pfVar5 = (float *)FUN_00155ff0(param_1->ndMtxArray);
    local_30.m[0][0] = *pfVar5;
    local_30.m[0][1] = pfVar5[4];
    local_30.m[0][2] = pfVar5[8];
    local_30.m[0][3] = pfVar5[0xc];
    local_30.m[1][0] = pfVar5[1];
    local_30.m[1][1] = pfVar5[5];
    local_30.m[1][2] = pfVar5[9];
    local_30.m[1][3] = pfVar5[0xd];
    local_30.m[2][0] = pfVar5[2];
    local_30.m[2][1] = pfVar5[6];
    local_30.m[2][2] = pfVar5[10];
    local_30.m[2][3] = pfVar5[0xe];
    Graphics::leftCombineTransforms
              (&graphics::bone_acc->affine1,&graphics::bone_acc->affine1,&local_30);
    local_30.m[0][0] = (graphics::bone_acc->affine1).m[0][0];
    local_30.m[0][1] = (graphics::bone_acc->affine1).m[0][1];
    local_30.m[0][2] = (graphics::bone_acc->affine1).m[0][2];
    local_30.m[0][3] = (graphics::bone_acc->affine1).m[0][3];
    local_30.m[1][0] = (graphics::bone_acc->affine1).m[1][0];
    local_30.m[1][1] = (graphics::bone_acc->affine1).m[1][1];
    local_30.m[1][2] = (graphics::bone_acc->affine1).m[1][2];
    local_30.m[1][3] = (graphics::bone_acc->affine1).m[1][3];
    local_30.m[2][0] = (graphics::bone_acc->affine1).m[2][0];
    local_30.m[2][1] = (graphics::bone_acc->affine1).m[2][1];
    local_30.m[2][2] = (graphics::bone_acc->affine1).m[2][2];
    local_30.m[2][3] = (graphics::bone_acc->affine1).m[2][3];
    fVar7 = (graphics::bone_acc->affine1).m[1][2] * Game::someGlobalPos.z;
    fVar6 = (graphics::bone_acc->affine1).m[1][1] * Game::someGlobalPos.y;
    fVar8 = (graphics::bone_acc->affine1).m[1][0] * Game::someGlobalPos.x;
    fVar2 = (graphics::bone_acc->affine1).m[1][3];
    fVar9 = (graphics::bone_acc->affine1).m[2][1] * Game::someGlobalPos.y;
    fVar10 = (graphics::bone_acc->affine1).m[2][2] * Game::someGlobalPos.z;
    fVar11 = (graphics::bone_acc->affine1).m[2][0] * Game::someGlobalPos.x;
    fVar3 = (graphics::bone_acc->affine1).m[2][3];
    *param_2 = (graphics::bone_acc->affine1).m[0][1] * Game::someGlobalPos.y +
               (graphics::bone_acc->affine1).m[0][2] * Game::someGlobalPos.z +
               (graphics::bone_acc->affine1).m[0][0] * Game::someGlobalPos.x +
               (graphics::bone_acc->affine1).m[0][3];
    param_2[1] = fVar6 + fVar7 + fVar8 + fVar2;
    param_2[2] = fVar9 + fVar10 + fVar11 + fVar3;
    AffineTransform::getScaleBases(&local_30,&pAVar1->scale);
    Math::GetEulerAngles((D3DXMATRIX *)&local_30,param_3);
    if ((param_4 != 0) &&
       (avatar::getWorldPosition(param_1,&local_3c),
       param_2[1] <= local_3c.y && local_3c.y != param_2[1])) {
      param_2[1] = local_3c.y;
      (pAVar1->pos).y = local_3c.y;
    }
    return;
  }
  *param_2 = (pAVar1->pos).x;
  param_2[1] = (pAVar1->pos).y;
  param_2[2] = (pAVar1->pos).z;
  param_3->x = (pAVar1->rotEuler).x;
  param_3->y = (pAVar1->rotEuler).y;
  param_3->z = (pAVar1->rotEuler).z;
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


float10 FUN_000413b0(void)

{
  float *unaff_EBX;
  avatar *unaff_ESI;
  vec3 local_c;
  
  avatar::getWorldPosition(unaff_ESI,&local_c);
  return SQRT(((float10)local_c.y - (float10)unaff_EBX[1]) *
              ((float10)local_c.y - (float10)unaff_EBX[1]) +
              ((float10)local_c.x - (float10)*unaff_EBX) *
              ((float10)local_c.x - (float10)*unaff_EBX) +
              ((float10)local_c.z - (float10)unaff_EBX[2]) *
              ((float10)local_c.z - (float10)unaff_EBX[2]));
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


float10 FUN_00041560(void)

{
  int unaff_EBX;
  avatar *unaff_ESI;
  float10 fVar1;
  float10 fVar2;
  float10 fVar3;
  vec3 local_c;
  
  avatar::getWorldPosition(unaff_ESI,&local_c);
  fVar1 = (float10)local_c.x - (float10)*(float *)(unaff_EBX + 0x20);
  fVar2 = (float10)local_c.y - (float10)*(float *)(unaff_EBX + 0x24);
  fVar3 = (float10)local_c.z - (float10)*(float *)(unaff_EBX + 0x28);
  return SQRT(fVar2 * fVar2 + fVar1 * fVar1 + fVar3 * fVar3);
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void __fastcall FUN_000415f0(uint16_t param_1,actor *param_2,vec3 *param_3)

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
  float fVar12;
  float fVar13;
  float fVar14;
  vec3 *in_EAX;
  
  if (param_1 == 0xffff) {
    fVar1 = (param_2->avatar).drawAffine.m[1][0];
    fVar2 = param_3->x;
    fVar3 = (param_2->avatar).drawAffine.m[2][0];
    fVar4 = param_3->x;
    fVar5 = (param_2->avatar).drawAffine.m[1][2];
    fVar6 = param_3->z;
    fVar7 = (param_2->avatar).drawAffine.m[1][1];
    fVar8 = param_3->y;
    fVar9 = (param_2->avatar).drawAffine.m[2][2];
    fVar10 = param_3->z;
    fVar11 = (param_2->avatar).drawAffine.m[1][3];
    fVar12 = (param_2->avatar).drawAffine.m[2][1];
    fVar13 = param_3->y;
    fVar14 = (param_2->avatar).drawAffine.m[2][3];
    in_EAX->x = (param_2->avatar).drawAffine.m[0][2] * param_3->z +
                (param_2->avatar).drawAffine.m[0][1] * param_3->y +
                (param_2->avatar).drawAffine.m[0][0] * param_3->x +
                (param_2->avatar).drawAffine.m[0][3];
    in_EAX->y = fVar5 * fVar6 + fVar1 * fVar2 + fVar7 * fVar8 + fVar11;
    in_EAX->z = fVar9 * fVar10 + fVar3 * fVar4 + fVar12 * fVar13 + fVar14;
    return;
  }
  actor::getTransformedBonePos(param_2,param_3,param_1,in_EAX);
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void FUN_00041ae0(avatar *param_1,vec3 *param_2)

{
  float local_1c;
  vec3 local_18;
  vec3 local_c;
  
  avatar::getWorldPosition(param_1,&local_18);
  local_c.x = param_2->x - local_18.x;
  local_c.y = param_2->y - local_18.y;
  local_c.z = param_2->z - local_18.z;
  vec3::getTurnAngle(&local_c,&local_1c);
  local_1c = local_1c - (param_1->rotEuler).y;
  modf(local_1c,6.2831855);
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


FUN_00041d40(int param_1,actor *param_2,vec3 *param_3,vec3 *param_4,float param_5)

{
  char *in_EAX;
  
  if (*in_EAX != '\0') {
    FUN_0012a260((uint)AnimEventPlayCueTypes[param_1],param_2,(short)param_1,param_3,param_4,param_5
                 ,(astruct_25 *)&(param_2->avatar).model0x9s[param_1 + -1].field_0xb0,in_EAX);
    return 1;
  }
  return 0;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void FUN_00044ef0(actor *param_1,int param_2,undefined4 param_3,vec3 *param_4)

{
  CalloutDescriptor **ppCVar1;
  short sVar2;
  int iVar3;
  actor *act;
  BOOL BVar4;
  vec3 *pvVar5;
  int iVar6;
  Message local_30;
  InfoFromBackground local_20;
  
  pvVar5 = param_4;
  act = param_1;
  iVar6 = param_2 * 0x9c;
  if (*(int *)(iVar6 + 0x14 + param_1->field4_0x94c) == 0) {
    BVar4 = avatar::extractCollider(&param_1->avatar,param_2,&local_20,&param_1);
    pvVar5 = param_4;
    if (BVar4 != 0) {
      param_4->x = local_20.someVec.x;
      param_4->z = local_20.someVec.z;
      param_4->y = local_20.yScale * 0.5 + local_20.someVec.y;
    }
  }
  else {
    iVar3 = *(int *)(iVar6 + 0x14 + param_1->field4_0x94c);
    param_4->x = *(float *)(iVar3 + 0x20);
    param_4->y = *(float *)(iVar3 + 0x24);
    param_4->z = *(float *)(iVar3 + 0x28);
    param_4->y = *(float *)(iVar3 + 0x30) * 0.5 + param_4->y;
    FUN_0012b0b0(*(int *)(iVar6 + 0x14 + param_1->field4_0x94c));
    *(undefined4 *)(iVar6 + 0x14 + act->field4_0x94c) = 0;
  }
  if (*(int *)(iVar6 + 0x18 + act->field4_0x94c) != 0) {
    FUN_0011bda0();
    *(undefined4 *)(iVar6 + 0x18 + act->field4_0x94c) = 0;
  }
  sVar2 = *(short *)(iVar6 + 0x10 + act->field4_0x94c);
  if (sVar2 != 0) {
    FUN_001117e0(sVar2);
    pvVar5 = param_4;
  }
  local_30.header.msgId = Background_PartExploded;
  local_30.header.someActor = act;
  EventLoop::DispatchMessage((ObjMsgID *)&local_30);
  Collision::RunColliderCallbackOnAllAvatars((char)param_2 + '\x01',Collider::removeFlags,0xc);
  someFxPos.x = pvVar5->x;
  someFxPos.y = pvVar5->y;
  ppCVar1 = &(act->avatar).callout;
  someFxPos.z = pvVar5->z;
  DAT_004e1c5c = 1;
  if (ppCVar1 != (CalloutDescriptor **)0x0) {
    actor::executeCalloutInDescriptor
              (*ppCVar1,Break,(CalloutCallback *)0x0,0x4e1c5c,act,(entityBodyPlayer_0x924)0x0);
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names

void __thiscall

void FUN_00045d70(background *bg,int innersIndex)

{
  BOOL success;
  Actor0x68 *pAVar1;
  AvatarInfoNode *new_node;
  undefined2 local_30 [4];
  float local_28;
  InfoFromBackground info;
  
  success = avatar::extractCollider(&bg->avatar,innersIndex,&info,local_30);
  if (success != 0) {
    pAVar1 = actor::createActor0x68((actor *)bg,1,0,0,&info);
    local_28 = info.yScale * 0.666 + info.someVec.y;
    *(Actor0x68 **)&bg->breakables[innersIndex].field_0x14 = pAVar1;
    new_node = avatar::newInfoNode(&bg->avatar,2);
    (new_node->info).somePos.x = info.someVec.x;
    (new_node->info).somePos.y = local_28;
    (new_node->info).somePos.z = info.someVec.z;
    *(undefined4 *)&(new_node->info).field_0x10 = 0xffffffff;
    FUN_0011be40(new_node);
    *(AvatarInfoNode **)&bg->breakables[innersIndex].field_0x18 = new_node;
    *(undefined2 *)&bg->breakables[innersIndex].field_0x10 = local_30[0];
    if (*(int *)&bg->breakables[innersIndex].field_0x18 != 0) {
      *(background **)(*(int *)&bg->breakables[innersIndex].field_0x18 + 0x34) = info.field8_0x1c;
    }
  }
  return;
}




void FUN_00049560(vec3 *param_1,float param_2)

{
  float *unaff_EDI;
  vec3 local_c;
  
  FUN_00106770(0.0,param_2,0.0,param_1,&local_c);
  *unaff_EDI = *unaff_EDI + local_c.x;
  unaff_EDI[1] = unaff_EDI[1] + local_c.y;
  unaff_EDI[2] = unaff_EDI[2] + local_c.z;
  return;
}




void FUN_000495b0(vec3 *param_1,float param_2)

{
  float *unaff_EDI;
  vec3 local_c;
  
  FUN_00106770(0.0,0.0,param_2,param_1,&local_c);
  *unaff_EDI = *unaff_EDI + local_c.x;
  unaff_EDI[1] = unaff_EDI[1] + local_c.y;
  unaff_EDI[2] = unaff_EDI[2] + local_c.z;
  return;
}




void FUN_00049600(vec3 *param_1,float param_2)

{
  float *unaff_EDI;
  vec3 local_c;
  
  FUN_00106770(param_2,0.0,0.0,param_1,&local_c);
  *unaff_EDI = *unaff_EDI + local_c.x;
  unaff_EDI[1] = unaff_EDI[1] + local_c.y;
  unaff_EDI[2] = unaff_EDI[2] + local_c.z;
  return;
}




float10 FUN_0004c1b0(void)

{
  float *pfVar1;
  float *pfVar2;
  float *pfVar3;
  float *pfVar4;
  float *pfVar5;
  float *pfVar6;
  float *pfVar7;
  float *pfVar8;
  float *pfVar9;
  float *pfVar10;
  float *pfVar11;
  float *pfVar12;
  float *pfVar13;
  float *pfVar14;
  float *pfVar15;
  float *pfVar16;
  float *pfVar17;
  float *pfVar18;
  float *pfVar19;
  float *pfVar20;
  float *pfVar21;
  float *pfVar22;
  float fVar23;
  float fVar24;
  uint uVar25;
  float *pfVar26;
  float *pfVar27;
  int iVar28;
  uint *unaff_EBX;
  uint uVar29;
  float10 fVar30;
  float fVar31;
  float local_8;
  
  uVar25 = *unaff_EBX;
  if (uVar25 == 0) {
    return (float10)0.0;
  }
  fVar31 = 0.0;
  uVar29 = 0;
  local_8 = 0.0;
  if (3 < (int)uVar25) {
    pfVar27 = (float *)(unaff_EBX[1] + 4);
    pfVar26 = (float *)(unaff_EBX[1] + 0x14);
    iVar28 = (uVar25 - 4 >> 2) + 1;
    uVar29 = iVar28 * 4;
    do {
      pfVar1 = pfVar27 + -1;
      pfVar2 = pfVar27 + 2;
      fVar23 = *pfVar27;
      pfVar3 = pfVar26 + -1;
      pfVar4 = pfVar27 + 1;
      fVar24 = *pfVar26;
      pfVar5 = pfVar27 + 0xb;
      pfVar6 = pfVar27 + 0xe;
      pfVar7 = pfVar26 + 9;
      pfVar8 = pfVar26 + 0xc;
      pfVar9 = pfVar26 + 8;
      pfVar10 = pfVar26 + 0xb;
      pfVar11 = pfVar26 + 0x14;
      pfVar12 = pfVar26 + 0x17;
      pfVar13 = pfVar27 + 0x17;
      pfVar14 = pfVar27 + 0x1a;
      pfVar15 = pfVar26 + 0x15;
      pfVar16 = pfVar26 + 0x18;
      pfVar17 = pfVar26 + 0x21;
      pfVar18 = pfVar26 + 0x24;
      pfVar19 = pfVar26 + 0x20;
      pfVar20 = pfVar26 + 0x23;
      pfVar21 = pfVar27 + 0x23;
      pfVar22 = pfVar27 + 0x26;
      pfVar26 = pfVar26 + 0x30;
      pfVar27 = pfVar27 + 0x30;
      iVar28 = iVar28 + -1;
      fVar31 = (*pfVar17 - *pfVar18) * (*pfVar17 - *pfVar18) +
               (*pfVar21 - *pfVar22) * (*pfVar21 - *pfVar22) +
               (*pfVar19 - *pfVar20) * (*pfVar19 - *pfVar20) +
               (*pfVar15 - *pfVar16) * (*pfVar15 - *pfVar16) +
               (*pfVar13 - *pfVar14) * (*pfVar13 - *pfVar14) +
               (*pfVar11 - *pfVar12) * (*pfVar11 - *pfVar12) +
               (*pfVar7 - *pfVar8) * (*pfVar7 - *pfVar8) + (*pfVar5 - *pfVar6) * (*pfVar5 - *pfVar6)
               + (*pfVar9 - *pfVar10) * (*pfVar9 - *pfVar10) +
               (*pfVar4 - fVar24) * (*pfVar4 - fVar24) + (*pfVar1 - *pfVar2) * (*pfVar1 - *pfVar2) +
               (fVar23 - *pfVar3) * (fVar23 - *pfVar3) + fVar31;
      local_8 = fVar31;
    } while (iVar28 != 0);
  }
  if (uVar29 < uVar25) {
    pfVar26 = (float *)(unaff_EBX[1] + uVar29 * 0x30);
    pfVar27 = pfVar26 + 5;
    iVar28 = uVar25 - uVar29;
    do {
      pfVar1 = pfVar27 + -3;
      fVar31 = *pfVar27;
      fVar23 = *pfVar26;
      pfVar2 = pfVar27 + -2;
      pfVar3 = pfVar27 + -4;
      pfVar4 = pfVar27 + -1;
      pfVar26 = pfVar26 + 0xc;
      pfVar27 = pfVar27 + 0xc;
      iVar28 = iVar28 + -1;
      local_8 = (*pfVar1 - fVar31) * (*pfVar1 - fVar31) + (fVar23 - *pfVar2) * (fVar23 - *pfVar2) +
                (*pfVar3 - *pfVar4) * (*pfVar3 - *pfVar4) + local_8;
    } while (iVar28 != 0);
  }
  fVar30 = (float10)(int)uVar25;
  if ((int)uVar25 < 0) {
    fVar30 = fVar30 + (float10)4.2949673e+09;
  }
  return (float10)local_8 / fVar30;
}




entityAvatarMiscProp * CreateMiscProp(int param_1,vec3 *param_2,char *assetName,char *param_4)

{
  char cVar1;
  int iVar2;
  avatarParams *inners;
  char *pcVar3;
  entityAvatarMiscProp *peVar4;
  
  inners = (avatarParams *)Assets::GetObjParams(param_4);
  if (inners == (avatarParams *)0x0) {
    return (entityAvatarMiscProp *)0x0;
  }
  (inners->pos).x = param_2->x;
  (inners->pos).y = param_2->y;
  (inners->pos).z = param_2->z;
  if (*(int *)assetName == 0x5f646961) {
    pcVar3 = assetName;
    do {
      cVar1 = *pcVar3;
      pcVar3[(int)inners + (0x28 - (int)assetName)] = cVar1;
      pcVar3 = pcVar3 + 1;
    } while (cVar1 != '\0');
  }
  if (param_1 != 0) {
    inners->hasShadow = 1;
    iVar2 = 0x2b4 - (int)assetName;
    do {
      cVar1 = *assetName;
      assetName[(int)inners + iVar2] = cVar1;
      assetName = assetName + 1;
    } while (cVar1 != '\0');
  }
  peVar4 = (entityAvatarMiscProp *)Assets::CreateEntityFromParams((objParams *)inners);
                    // Triggers on pause
  free(inners);
  return peVar4;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void FUN_0004ef20(vec3 *param_1)

{
  float progress1;
  Cutscene *cur_ctsc;
  
  cur_ctsc = Cutscene::LoadedCutscenes[Cutscene::CurrentCutsceneIndex];
  progress1 = cur_ctsc->t / cur_ctsc->length;
  (cur_ctsc->v2).x = param_1->x;
  (cur_ctsc->v2).y = param_1->y;
  (cur_ctsc->v2).z = param_1->z;
  Cutscene::updateAvatarsAndAnims(cur_ctsc,-1.0,progress1,progress1);
  Cutscene::updateCameraFromCutscene
            (Cutscene::LoadedCutscenes[Cutscene::CurrentCutsceneIndex],&Cutscene::CutsceneCam);
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


int vec3::CmpYDescending(float *param_1,float *param_2)

{
  if (param_1[1] == param_2[1]) {
    return 0;
  }
  if (param_2[1] <= param_1[1] && param_1[1] != param_2[1]) {
    return -1;
  }
  return 1;
}




float FloatSet::interpolateAtT(FloatSet *floatSet,float t,float *out1,float *out2)

{
  uint uVar1;
  uint uVar2;
  float index;
  uint64_t uVar3;
  
  if (floatSet->numFloats == 1) {
    index = *floatSet->floats;
    *out2 = index;
    *out1 = index;
    return 0.0;
  }
  uVar2 = (uint)floatSet->numFloats;
  index = (t / floatSet->length) * (float)uVar2;
  if (index < 1.0) {
    *out1 = *floatSet->floats;
    *out2 = floatSet->floats[1];
    return index;
  }
  uVar3 = float10::to_uint64_t((float10)index);
  uVar1 = (uint)uVar3;
  if (uVar2 - 1 <= uVar1) {
    *out1 = floatSet->floats[uVar2 - 2];
    *out2 = floatSet->floats[floatSet->numFloats - 1];
    return 1.0;
  }
  *out1 = floatSet->floats[uVar1];
  *out2 = floatSet->floats[uVar1 + 1];
  index = modf(index,1.0);
  return index;
}



void InterpolateQuaternionFromAnimTracks
               (FloatSet *track1,FloatSet *track2,FloatSet *track3,FloatSet *track4,
               float cutsceneProgress,Quaternion *outQ)

{
  float t;
  Quaternion q2;
  Quaternion q1;
  
                    // Interpolate x,y,z,w into q1 and q2
  t = FloatSet::interpolateAtT(track1,cutsceneProgress,&q1.x,&q2.x);
  FloatSet::interpolateAtT(track2,cutsceneProgress,&q1.y,&q2.y);
  FloatSet::interpolateAtT(track3,cutsceneProgress,&q1.z,&q2.z);
  FloatSet::interpolateAtT(track4,cutsceneProgress,&q1.w,&q2.w);
  Quaternion::SLERP(&q1,&q2,outQ,t);
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names


float10 FUN_00066940(void)

{
  float fVar1;
  int in_EAX;
  float10 extraout_ST0;
  float10 extraout_ST0_00;
  float fVar2;
  
  if (*(int *)(in_EAX + 0x944) == 3) {
    fVar1 = *(float *)(in_EAX + 0x938);
    fVar2 = 1.0;
    if ((fVar1 <= 1.0) && (fVar2 = 0.0, 0.0 <= fVar1)) {
      fVar2 = fVar1;
    }
    sin(fVar2 * 3.1415927 - 1.5707964);
    sin((float)((extraout_ST0 + (float10)1.0) * (float10)0.5 * (float10)3.1415927 -
               (float10)1.5707964));
    return (extraout_ST0_00 + (float10)1.0) * (float10)0.5;
  }
  return (float10)1.0;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


undefined4 FUN_000697d0(avatar *param_1,float *param_2,vec3 *param_3,vec3 *param_4,vec3 *param_5)

{
  int *piVar1;
  BOOL BVar2;
  int extraout_EAX;
  int iVar3;
  float *pfVar4;
  undefined4 local_3c;
  float local_38 [4];
  float local_28;
  float local_24;
  float fStack_1c;
  float fStack_18;
  float fStack_14;
  float fStack_10;
  float fStack_c;
  float fStack_8;
  int local_4;
  
  if ((*(short *)&param_1[1].pos.x == 0) && (*(int *)(param_1[1].modelAID + 0x10) == 0)) {
    BVar2 = 1;
  }
  else {
    BVar2 = 0;
  }
  FUN_00069e00(param_2,param_1,BVar2,param_3);
  if (extraout_EAX != 0) {
    piVar1 = *(int **)(param_1[1].modelAID + 4);
    if (piVar1 == (int *)0x0) {
      param_4->x = *param_2;
      param_4->y = param_2[1];
      param_4->z = param_2[2];
      param_5->x = param_3->x;
      param_5->y = param_3->y;
      param_5->z = param_3->z;
      return 1;
    }
    local_38[0] = *param_2;
    pfVar4 = local_38;
    for (iVar3 = 0xe; iVar3 != 0; iVar3 = iVar3 + -1) {
      *pfVar4 = 0.0;
      pfVar4 = pfVar4 + 1;
    }
    local_38[1] = param_2[1];
    local_38[2] = param_2[2];
    local_38[3] = param_3->x;
    local_28 = param_3->y;
    local_24 = param_3->z;
    local_3c = 0xa6;
    local_4 = 0;
    (**(code **)(*piVar1 + 0xc))(piVar1,&local_3c);
    if (local_4 != 0) {
      param_4->x = fStack_1c;
      param_4->y = fStack_18;
      param_4->z = fStack_14;
      param_5->x = fStack_10;
      param_5->y = fStack_c;
      param_5->z = fStack_8;
      return 1;
    }
  }
  return 0;
}




BOOL FUN_00069e00(vec3 *param_1,avatar *param_2,BOOL param_3,vec3 *param_4)

{
  bool bVar1;
  int iVar2;
  undefined3 extraout_var;
  AvatarVTable *local_1c;
  vec3 local_18;
  vec3 local_c;
  
  avatar::getWorldPosition(param_2,&local_18);
  if (param_3 == 0) {
    FUN_00106670();
    param_3 = 1;
  }
  else {
    iVar2 = FUN_00110bf0(&local_18,-1,0);
    local_1c = param_2[1].vtable;
    param_3 = SpawnThingFromMarker
                        (param_1,0,&local_18,iVar2,local_1c,*(float *)&param_2[1].field_0x4,0,0,0,0)
    ;
    if (param_3 == 0) {
      param_3 = 0;
      return param_3;
    }
  }
  avatar::getWorldRotation(param_2,param_4);
  local_c.x = local_18.x - param_1->x;
  local_c.y = local_18.y - param_1->y;
  local_c.z = local_18.z - param_1->z;
  bVar1 = vec3::getTurnAngle(&local_c,(float *)&local_1c);
  if (CONCAT31(extraout_var,bVar1) != 0) {
    if (*(int *)(param_2[1].modelAID + 0xc) != 1) {
      if (*(int *)(param_2[1].modelAID + 0xc) != 2) {
        return param_3;
      }
      local_1c = (AvatarVTable *)((float)local_1c - 3.1415927);
    }
    param_4->x = 0.0;
    param_4->y = (float)local_1c;
    param_4->z = 0.0;
  }
  return param_3;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


BOOL FUN_0006ae10(avatar *param_1,float param_2,float param_3,vec3 *param_4)

{
  bool bVar1;
  vec3 *in_EAX;
  int iVar2;
  BOOL BVar3;
  undefined3 extraout_var;
  vec3 local_18;
  vec3 local_c;
  
  avatar::getWorldPosition(param_1,&local_18);
  if (param_2 == 0.0) {
    FUN_00106670();
    BVar3 = 1;
  }
  else {
    iVar2 = FUN_00110bf0(&local_18,-1,0);
    BVar3 = SpawnThingFromMarker(in_EAX,0,&local_18,iVar2,0,param_3,0,0,0,0);
    if (BVar3 == 0) {
      return 0;
    }
  }
  if (param_3 != 0.0) {
    local_c.x = local_18.x - in_EAX->x;
    local_c.y = local_18.y - in_EAX->y;
    local_c.z = local_18.z - in_EAX->z;
    bVar1 = vec3::getTurnAngle(&local_c,&param_2);
    if (CONCAT31(extraout_var,bVar1) != 0) {
      param_4->x = 0.0;
      param_4->y = param_2;
      param_4->z = 0.0;
      return BVar3;
    }
  }
  avatar::getWorldRotation(param_1,param_4);
  return BVar3;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


BOOL FUN_0006b9c0(avatar *param_1,int param_2,vec3 *param_3)

{
  vec3 *in_EAX;
  int iVar1;
  BOOL BVar2;
  vec3 local_c;
  
  avatar::getWorldPosition(param_1,&local_c);
  if (param_2 != 0) {
    iVar1 = FUN_00110bf0(&local_c,-1,0);
    BVar2 = SpawnThingFromMarker(in_EAX,0,&local_c,iVar1,0,0.0,0,0,0,0);
    if (BVar2 != 0) {
      avatar::getWorldRotation(param_1,param_3);
    }
    return BVar2;
  }
  in_EAX->x = local_c.x;
  in_EAX->y = local_c.y;
  in_EAX->z = local_c.z;
  avatar::getWorldRotation(param_1,param_3);
  return 1;
}



void FUN_0006ba70(entityAvatarGhoulieSetupCutsceneParams *this,char *param_2,vec3 *param_3,
                 vec3 *rotEuler,undefined2 param_5,ushort param_6,undefined4 param_7,ushort param_8,
                 undefined4 param_9,undefined4 param_10)

{
  char cVar1;
  int iVar2;
  avatarParams *paVar3;
  
  paVar3 = avatarParams::init(&this->avatarParams);
  (paVar3->pos).x = param_3->x;
  (paVar3->pos).y = param_3->y;
  (paVar3->pos).z = param_3->z;
  (paVar3->rotEuler).x = rotEuler->x;
  (paVar3->rotEuler).y = rotEuler->y;
  (paVar3->rotEuler).z = rotEuler->z;
  *(undefined2 *)((int)&paVar3->impactId + 2) = param_5;
  paVar3->ghoulyboxId2 = param_6;
  paVar3[1].objParams.paramsSize = (undefined2)param_7;
  paVar3[1].objParams.objInitValue = param_7._2_2_;
  (paVar3->objParams).paramsSize = 0x3c4;
  (paVar3->objParams).objInitValue = 0x6e;
  (paVar3->objParams).typeIndex = 0x25;
  paVar3[1].objParams.typeIndex = param_8;
  iVar2 = 0x33a - (int)param_2;
  do {
    cVar1 = *param_2;
    param_2[(int)paVar3 + iVar2] = cVar1;
    param_2 = param_2 + 1;
  } while (cVar1 != '\0');
  *(undefined4 *)(paVar3[1].modelAID + 0x60) = param_9;
  *(undefined4 *)(paVar3[1].modelAID + 100) = param_10;
  return;
}




undefined4 FUN_0006bca0(int param_1,vec3 *param_2,float *param_3,float *param_4)

{
  int *piVar1;
  int iVar2;
  vec3 *unaff_EBX;
  float *pfVar3;
  undefined4 local_3c;
  float local_38 [4];
  float local_28;
  float local_24;
  undefined4 local_20;
  float fStack_1c;
  float fStack_18;
  float fStack_14;
  float fStack_10;
  float fStack_c;
  float fStack_8;
  int local_4;
  
  avatar::getWorldPosition(*(avatar **)(param_1 + 0x93c),param_2);
  avatar::getWorldRotation(*(avatar **)(param_1 + 0x93c),unaff_EBX);
  piVar1 = *(int **)(param_1 + 0x934);
  if (piVar1 == (int *)0x0) {
    *param_3 = param_2->x;
    param_3[1] = param_2->y;
    param_3[2] = param_2->z;
    *param_4 = unaff_EBX->x;
    param_4[1] = unaff_EBX->y;
    param_4[2] = unaff_EBX->z;
    return 1;
  }
  local_38[0] = param_2->x;
  pfVar3 = local_38;
  for (iVar2 = 0xe; iVar2 != 0; iVar2 = iVar2 + -1) {
    *pfVar3 = 0.0;
    pfVar3 = pfVar3 + 1;
  }
  local_38[1] = param_2->y;
  local_38[2] = param_2->z;
  local_38[3] = unaff_EBX->x;
  local_28 = unaff_EBX->y;
  local_24 = unaff_EBX->z;
  local_3c = 0xa6;
  local_20 = 1;
  local_4 = 0;
  (**(code **)(*piVar1 + 0xc))(piVar1,&local_3c);
  if (local_4 == 0) {
    return 0;
  }
  *param_3 = fStack_1c;
  param_3[1] = fStack_18;
  param_3[2] = fStack_14;
  *param_4 = fStack_10;
  param_4[1] = fStack_c;
  param_4[2] = fStack_8;
  return 1;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


avatar * FUN_0006ddf0(avatar *param_1,int param_2,vec3 *param_3)

{
  float fVar1;
  avatar *this;
  bool bVar2;
  float *in_EAX;
  int iVar3;
  undefined3 extraout_var;
  float local_1c;
  vec3 local_18;
  vec3 local_c;
  
  this = param_1;
  avatar::getWorldPosition(param_1,&local_18);
  if ((param_1[1].pos.x == 0.0) ||
     ((0x7fffffff < (uint)Cutscene::CurrentCutsceneIndex && (iVar3 = FUN_0005b830(), iVar3 == 0))))
  {
    if (param_2 == 0) {
      FUN_00106670();
      param_1 = (avatar *)0x1;
    }
    else {
      param_1 = (avatar *)FUN_0006dcc0(&local_18);
      if (param_1 == (avatar *)0x0) {
        return (avatar *)0;
      }
    }
  }
  else {
    *in_EAX = local_18.x;
    in_EAX[1] = local_18.y;
    in_EAX[2] = local_18.z;
    param_1 = (avatar *)0x1;
  }
  if (this[1].pos.z != 0.0) {
    in_EAX[1] = local_18.y;
  }
  avatar::getWorldRotation(this,param_3);
  local_c.x = local_18.x - *in_EAX;
  local_c.y = local_18.y - in_EAX[1];
  local_c.z = local_18.z - in_EAX[2];
  bVar2 = vec3::getTurnAngle(&local_c,&local_1c);
  if (CONCAT31(extraout_var,bVar2) != 0) {
    fVar1 = this[1].pos.y;
    if (fVar1 != 1.4013e-45) {
      if (fVar1 != 2.8026e-45) {
        return (avatar *)(int)param_1;
      }
      local_1c = local_1c - 3.1415927;
    }
    param_3->x = 0.0;
    param_3->y = local_1c;
    param_3->z = 0.0;
  }
  return param_1;
}




undefined4 FUN_0006df50(vec3 *param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  BackgroundCollisionThing *pBVar1;
  int iVar2;
  uint uVar3;
  vec3 *in_EAX;
  Buffer<Idk0xc> *ptr;
  int iVar4;
  float fVar5;
  float fVar6;
  
  pBVar1 = BackgroundCollisionThings[param_2];
  ptr = FUN_0010f7f0(0,param_1,param_3,param_4,0,0,0,0,param_2);
  if (ptr != (Buffer<Idk0xc> *)0x0) {
    runtime::rand = runtime::rand * 0x19660d + 0x3c6ef35f;
    iVar2 = pBVar1->field10_0x10;
    uVar3 = ptr->head[(int)(((float)(runtime::rand & 0x7fffff | 0x3f800000) - 1.0) *
                           (float)(((int)ptr->tail - (int)ptr->head) / (int)(uint)ptr->valueSize))].
            field0_0x0;
    iVar4 = iVar2 + uVar3 * 0x12;
    in_EAX->x = (float)(int)*(short *)(iVar2 + uVar3 * 0x12);
    in_EAX->y = (float)(int)*(short *)(iVar4 + 2);
    in_EAX->z = (float)(int)*(short *)(iVar4 + 4);
    free(ptr);
    if (BackgroundCollisionThings[0] == (BackgroundCollisionThing *)0x0) {
      fVar5 = 0.0;
    }
    else {
      fVar5 = (float)(int)BackgroundCollisionThings[0]->someF * 0.5;
    }
    fVar5 = fVar5 * 0.4;
    runtime::rand = runtime::rand * 0x19660d + 0x3c6ef35f;
    fVar6 = 0.0 - fVar5;
    in_EAX->x = (fVar5 - fVar6) * ((float)(runtime::rand & 0x7fffff | 0x3f800000) - 1.0) + in_EAX->x
                + fVar6;
    runtime::rand = runtime::rand * 0x19660d + 0x3c6ef35f;
    in_EAX->z = (fVar5 - fVar6) * ((float)(runtime::rand & 0x7fffff | 0x3f800000) - 1.0) + in_EAX->z
                + fVar6;
    iVar4 = Background::isCollisionThings(param_2,in_EAX);
    if (iVar4 != -1) {
      in_EAX->y = (float)(int)*(short *)(pBVar1->field10_0x10 + 2 + iVar4 * 0x12);
      return 1;
    }
  }
  return 0;
}



void FUN_0006e110(undefined2 param_1,ushort param_2,undefined4 param_3,undefined4 param_4,
                 float param_5,float param_6,float param_7)

{
  avatarParams *in_EAX;
  avatarParams *paVar1;
  float *unaff_ESI;
  float *unaff_EDI;
  
  paVar1 = avatarParams::init(in_EAX);
  (paVar1->pos).x = *unaff_EDI;
  (paVar1->pos).y = unaff_EDI[1];
  (paVar1->pos).z = unaff_EDI[2];
  (paVar1->rotEuler).x = *unaff_ESI;
  (paVar1->rotEuler).y = unaff_ESI[1];
  (paVar1->rotEuler).z = unaff_ESI[2];
  *(undefined2 *)((int)&paVar1->impactId + 2) = param_1;
  paVar1->ghoulyboxId2 = param_2;
  paVar1[1].pos.x = param_5;
  paVar1[1].objParams.paramsSize = (undefined2)param_3;
  paVar1[1].objParams.objInitValue = param_3._2_2_;
  (paVar1->objParams).paramsSize = 0x348;
  (paVar1->objParams).objInitValue = 0x6e;
  (paVar1->objParams).typeIndex = 0x1f;
  paVar1[1].objParams.typeIndex = (undefined2)param_4;
  paVar1[1].objParams.field3_0x6 = param_4._2_2_;
  paVar1[1].pos.y = param_6;
  paVar1[1].pos.z = param_7;
  return;
}



// WARNING: Globals starting with '_' overlap smaller symbols at the same address
// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


FUN_000790b0(entityMindCinema *mind,vec3 *param_2,float *param_3,int param_4,vec3 *param_5)

{
  actorBody *body;
  vec3 *in_EAX;
  undefined1 *collisionFunction;
  int iVar1;
  BOOL BVar2;
  int i;
  vec3 pos;
  
  pos.x = param_5->x;
  body = ((mind->mind).actor)->body;
  pos.y = param_5->y;
  pos.z = param_5->z;
  i = 0;
  if (0 < param_4) {
    while( true ) {
      collisionFunction = actorBody::getCollisionDrone(body);
      iVar1 = Collision::checkAvatarsWithCollisionInScene(param_2,&pos,Walls,collisionFunction);
      if (iVar1 == 0) break;
      if (i == 0) {
        param_5->x = pos.x;
        param_5->y = pos.y;
        param_5->z = pos.z;
      }
      BVar2 = actorMind::isSomething
                        (&mind->mind,param_2,param_3,&pos,
                         &(Physics::CollisionContexts[0].ctx)->head->velocity,param_5,in_EAX);
      if (BVar2 == 1) {
        return 1;
      }
      if (BVar2 == 0) {
        return 0;
      }
      i = i + 1;
      if (param_4 <= i) {
        return 0;
      }
    }
  }
  return 0;
}



void FUN_000791a0(float param_1,undefined4 param_2,int param_3,undefined4 param_4,undefined4 param_5
                 )

{
  int iVar1;
  int unaff_ESI;
  float10 fVar2;
  float10 fVar3;
  float fVar4;
  float fVar5;
  float local_8;
  float local_4;
  
  local_8 = modf(*(float *)(unaff_ESI + 0xb4) - *(float *)(unaff_ESI + 0xb8),6.2831855);
  if (local_8 < -3.1415927) {
    local_8 = local_8 + 6.2831855;
  }
  if (3.1415927 <= local_8) {
    local_8 = local_8 - 6.2831855;
  }
  local_4 = modf(param_1 - *(float *)(unaff_ESI + 0xb8),6.2831855);
  if (local_4 < -3.1415927) {
    local_4 = local_4 + 6.2831855;
  }
  if (3.1415927 <= local_4) {
    local_4 = local_4 - 6.2831855;
  }
  if ((param_3 != 0) && (*(int *)(unaff_ESI + 0xac) != 0)) {
    fVar5 = 1.0;
    if (local_8 < 0.0) {
      fVar5 = -1.0;
    }
    fVar4 = 1.0;
    if (local_4 < 0.0) {
      fVar4 = -1.0;
    }
    if (fVar5 != fVar4) {
      return;
    }
    fVar2 = abs_float(local_8);
    fVar3 = abs_float(local_4);
    if ((float10)(float)fVar2 <= fVar3) {
      return;
    }
  }
  iVar1 = *(int *)(unaff_ESI + 0xac);
  *(float *)(unaff_ESI + 0xb4) = param_1;
  *(undefined4 *)(unaff_ESI + 0xbc) = param_2;
  *(undefined4 *)(unaff_ESI + 0xac) = 1;
  *(undefined4 *)(unaff_ESI + 0xd0) = param_4;
  *(uint *)(unaff_ESI + 0xb0) = (uint)(iVar1 == 0);
  *(undefined4 *)(unaff_ESI + 0xd4) = param_5;
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


FUN_00079450(int param_1,actorBody *param_2,vec3 *param_3,actor *param_4,undefined4 param_5)

{
  uint index;
  undefined1 *puVar1;
  BOOL BVar2;
  BOOL BVar3;
  int iVar4;
  vec3 *unaff_ESI;
  vec3 *unaff_EDI;
  float10 fVar5;
  float10 fVar6;
  float fVar7;
  float fVar8;
  undefined4 local_24;
  vec3 local_18;
  vec3 local_c;
  
  local_18.x = unaff_EDI->x;
  fVar7 = unaff_ESI->y;
  local_18.z = unaff_EDI->z;
  local_18.y = fVar7;
  puVar1 = actorBody::getCollisionDrone(param_2);
  BVar2 = Collision::runCollisionFunctionWithAllAvatars
                    (&local_18,unaff_EDI,FLOAT_004274b8,Walls,puVar1);
  if (BVar2 != 0) {
    fVar7 = local_18.y;
  }
  local_c.x = unaff_EDI->x;
  local_18.x = unaff_ESI->x;
  local_18.y = unaff_ESI->y;
  local_c.z = unaff_EDI->z;
  fVar8 = unaff_ESI->z;
  local_18.z = fVar8;
  local_c.y = fVar7;
  puVar1 = actorBody::getCollisionDrone(param_2);
  BVar3 = Collision::runCollisionFunctionWithAllAvatars
                    (&local_18,&local_c,FLOAT_004274b8,Walls,puVar1);
  if (BVar3 == 0) {
LAB_0007970c:
    local_24 = 0;
  }
  else {
    resolveCollision((Physics::CollisionContexts[0].ctx)->head,param_5);
    if (((*(int *)(param_1 + 0xac) == 0) || (*(int *)(param_1 + 0xd4) == 0)) &&
       (fVar7 = FUN_0013dc40(param_4,fVar8), fVar7 == 0.0)) {
      index = param_4->backgroundCollisionIndex;
      iVar4 = Background::isCollisionThings(index,unaff_ESI);
      if ((iVar4 != -1) &&
         (iVar4 = FUN_000368c0(BackgroundCollisionThings[index],iVar4), iVar4 == 0)) {
        puVar1 = actorBody::getCollisionDrone(param_2);
        BVar3 = Collision::runCollisionFunctionWithAllAvatars
                          (&local_c,param_3,FLOAT_004274b8,Walls,puVar1);
        if (BVar3 != 0) {
          local_18.x = unaff_ESI->x;
          local_18.y = unaff_ESI->y;
          local_18.z = unaff_ESI->z;
          puVar1 = actorBody::getCollisionDrone(param_2);
          BVar3 = Collision::runCollisionFunctionWithAllAvatars
                            (&local_18,&local_c,FLOAT_004274b8,Walls,puVar1);
          if (BVar3 == 0) goto LAB_0007970c;
          resolveCollision((Physics::CollisionContexts[0].ctx)->head,param_5);
        }
      }
    }
    local_24 = 1;
    unaff_ESI->x = local_18.x;
    unaff_ESI->y = local_18.y;
    unaff_ESI->z = local_18.z;
  }
  if (BVar2 != 0) {
    fVar8 = unaff_ESI->z - unaff_EDI->z;
    fVar7 = unaff_ESI->x - unaff_EDI->x;
    fVar5 = scaled_invsqrt(fVar8 * fVar8 + fVar7 * fVar7);
    fVar8 = param_3->z - unaff_EDI->z;
    fVar7 = param_3->x - unaff_EDI->x;
    fVar6 = scaled_invsqrt(fVar8 * fVar8 + fVar7 * fVar7);
    if ((((float)fVar5 < 20.0) && ((float)fVar6 < 20.0)) && ((float)fVar5 < (float)fVar6)) {
      unaff_ESI->x = param_3->x;
      unaff_ESI->y = param_3->y;
      unaff_ESI->z = param_3->z;
    }
  }
  return local_24;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields

void FUN_00079720(entityMindCinema *mind,actor *act,actorBody *param_3,float *param_4,vec3 *param_5,
                 actor *param_6,float param_7)

{
  bool bVar1;
  float *in_EAX;
  int iVar2;
  undefined3 extraout_var;
  undefined1 *collisionFunction;
  BOOL BVar3;
  float10 fVar4;
  float fVar5;
  float fVar6;
  vec3 local_84;
  float local_78;
  float local_74;
  vec3 local_70;
  float local_64;
  float local_60;
  float local_5c;
  float local_58;
  vec3 local_48 [6];
  
  iVar2 = FUN_00079450(mind,param_3);
  if (iVar2 == 0) {
    local_60 = (param_3->somePhysicsWalkPos).x;
    local_5c = (param_3->somePhysicsWalkPos).y;
    local_58 = (param_3->somePhysicsWalkPos).z;
    avatar::getWorldRotation(&act->avatar,&local_70);
    local_84.z = 0.0;
    local_84.y = 0.0;
    local_84.x = 0.0;
    Math::MovePointForwards(&local_84,local_70.x,local_70.y,1.0);
    local_78 = local_84.y * local_84.y + local_84.z * local_84.z + local_84.x * local_84.x;
    if (local_78 != 0.0) {
      fVar4 = (float10)invsqrt(local_78);
      local_84.x = (float)((float10)local_84.x * fVar4);
      local_84.y = (float)((float10)local_84.y * fVar4);
      local_84.z = (float)((float10)local_84.z * fVar4);
    }
    fVar5 = 0.0;
    if (((param_3->flagSet->flags->flag1 & 0x200000) == Null) ||
       (local_84.z * local_58 + local_84.y * local_5c + local_84.x * local_60 <= FLOAT_0042750c)) {
      *(undefined4 *)&mind->field_0xc0 = 0;
    }
    else {
      if (runtime::dx_timer <= 0.0) {
        fVar6 = runtime::DeltaTime * runtime::TimeScale;
      }
      else {
        fVar6 = 0.0;
      }
      if ((act->avatar).movementFreezeTimer <= 0.0) {
        fVar5 = (act->avatar).actionSpeed;
      }
      *(float *)&mind->field_0xc0 = fVar6 * fVar5 + *(float *)&mind->field_0xc0;
    }
    if (FLOAT_00427500 < *(float *)&mind->field_0xc0) {
      local_84.x = *in_EAX;
      local_84.y = in_EAX[1];
      local_84.z = in_EAX[2];
      collisionFunction = actorBody::getCollisionDrone(param_3);
      BVar3 = Collision::runCollisionFunctionWithAllAvatars
                        (&local_84,param_5,FLOAT_004274b8,Walls,collisionFunction);
      if ((BVar3 != 0) &&
         (fVar6 = param_5->z - local_84.z, fVar5 = param_5->x - local_84.x,
         fVar4 = scaled_invsqrt(fVar6 * fVar6 + fVar5 * fVar5), fVar5 = FLOAT_00427508,
         (float10)FLOAT_00427504 * (float10)param_7 < fVar4)) {
        *param_4 = local_84.x;
        param_4[1] = local_84.y;
        param_4[2] = local_84.z;
        local_70.y = (local_84.x - param_5->x) * fVar5 + param_5->x;
        local_70.z = (local_84.y - param_5->y) * fVar5 + param_5->y;
        local_64 = (local_84.z - param_5->z) * fVar5 + param_5->z;
        local_70.x = 4.76441e-44;
        (*param_3->vtable->onMessage)(param_3,&local_70);
        *(undefined4 *)&mind->field_0xc0 = 0;
      }
    }
  }
  else {
    fVar6 = in_EAX[2] - param_5->z;
    fVar5 = *in_EAX - param_5->x;
    fVar4 = scaled_invsqrt(fVar6 * fVar6 + fVar5 * fVar5);
    local_78 = (float)fVar4;
    if (((FLOAT_004274c4 != 0.0) && (param_6 != (actor *)0x0)) &&
       (fVar5 = FUN_0013dc40(param_6,fVar5), fVar5 != 0.0)) {
      return;
    }
    if ((local_78 < FLOAT_004274c0) &&
       (bVar1 = vec3::getTurnAngle(local_48,&local_74), CONCAT31(extraout_var,bVar1) != 0)) {
      fVar5 = local_74;
      FUN_00100e40(*(undefined4 *)&mind->field_0xb8);
      local_78 = 1.0;
      if (fVar5 < 0.0) {
        local_78 = -1.0;
      }
      local_74 = local_74 - (1.5707964 - FLOAT_00427510 * 0.017453292) * local_78;
      FUN_000791a0(local_74,FLOAT_00427514 * 2.0,1,FLOAT_004274f4,1);
      return;
    }
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


undefined4 FUN_0007acb0(int param_1,int param_2,vec3 *param_3,vec3 *param_4)

{
  undefined4 index;
  int iVar1;
  int iVar2;
  int iVar3;
  ushort *puVar4;
  int iVar5;
  bool bVar6;
  undefined4 in_XMM0_Da;
  
  iVar5 = *(int *)(param_1 + 0x1c);
  if (iVar5 == 0) {
    return 0;
  }
  index = *(undefined4 *)(param_2 + 0xcec);
  iVar1 = Background::isCollisionThings(index,param_3);
  iVar2 = Background::isCollisionThings(index,param_4);
  if (iVar1 == -1) {
    return 0;
  }
  if (iVar2 == -1) {
    return 0;
  }
  if (DAT_00427598 == 0) {
    bVar6 = true;
  }
  else {
    iVar3 = FUN_00037980(iVar5,iVar1,iVar2);
    bVar6 = iVar3 == 0;
  }
  puVar4 = *(ushort **)(iVar5 + 0x14);
  if (((puVar4 == (ushort *)0x0) || (bVar6)) || (iVar3 = FUN_00036e90(), iVar3 == 0)) {
    iVar3 = FUN_00036600(*(undefined4 *)(iVar5 + 0x10));
    if (iVar3 != 0) {
      return 0;
    }
    FUN_00036c80(iVar1,iVar2);
    FUN_00042320();
    FUN_00036ca0(0,in_XMM0_Da);
    if (*(int *)(iVar5 + 0x28) != 3) {
      return 0;
    }
    if (*(int *)(iVar5 + 0x2c) == 0) {
      return 0;
    }
    puVar4 = (ushort *)FUN_00036e50(param_3,param_4);
  }
  else {
    FUN_000376f0();
  }
  if (puVar4 != (ushort *)0x0) {
    iVar5 = (*(int *)(puVar4 + 4) - *(int *)(puVar4 + 2)) / (int)(uint)*puVar4;
    iVar1 = 0;
    if (0 < iVar5) {
      do {
        iVar2 = FUN_0012c9c0(param_4,0,1,1);
        if (iVar2 != 0) {
          FUN_0007ab00();
          return 1;
        }
        iVar1 = iVar1 + 1;
      } while (iVar1 < iVar5);
    }
  }
  return 0;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields

void __thiscall
FUN_0007ae70(avatar *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
            undefined4 param_5)

{
  int iVar1;
  undefined1 local_10 [4];
  vec3 local_c;
  
  FUN_0007ab00();
  avatar::getWorldPosition(param_1,&local_c);
  iVar1 = FUN_0012cc50(param_5,1,0,0,0,0,local_10,param_1->tag);
  if (iVar1 == 0) {
    FUN_0007acb0(param_2,param_1,param_3);
  }
  FUN_0013d110();
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void FUN_00081650(vec3 *param_1)

{
  avatar_0x900_conflict6 pEVar1;
  int in_EAX;
  avatar *av;
  
  pEVar1 = Game::SceneInfo.avatars.next;
  if (*(ushort *)(in_EAX + 0x1fe) != 0) {
    for (; pEVar1 != (avatar_0x900_conflict6)0x0; pEVar1 = pEVar1->next) {
      av = (avatar *)ADJ(pEVar1);
      if (ADJ(pEVar1)->field237_0x1fc == *(ushort *)(in_EAX + 0x1fe)) goto LAB_00081688;
    }
  }
  av = (avatar *)0x0;
LAB_00081688:
  avatar::getWorldPosition(av,param_1);
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


actor_conflict5 * FUN_00086e80(vec3 *param_1)

{
  weapon *pwVar1;
  WeaponProjectilesContext *pWVar2;
  int in_EAX;
  actor_conflict5 *av;
  float local_2c [2];
  vec3 local_24;
  vec3 local_18;
  vec3 local_c;
  
  if (Game::SceneInfo.playerActors.prev == (actor_0x93c_conflict5)0x0) {
    av = (actor_conflict5 *)0x0;
  }
  else {
    av = ADJ(Game::SceneInfo.playerActors.prev);
  }
  pwVar1 = ((actorBody *)av->body)->weapon;
  if (((pwVar1 != (weapon *)0x0) && (pwVar1->field12_0x93f != '\x01')) &&
     ((pwVar1->field12_0x93f != '\x02' ||
      ((pWVar2 = pwVar1->projectilesCtx, pWVar2 != (WeaponProjectilesContext *)0x0 &&
       ((*(short *)&pWVar2[1].field_0x37c == 2 || (*(int *)&pWVar2->field_0x93c != 0)))))))) {
    FUN_0001b810((actorBody *)av->body,0,0);
  }
  Events::UpdateActionBeginEnds(0xff,0);
  if (*(int *)(in_EAX + 0x270) != 0) {
    avatar::setPosition((avatar *)av,param_1);
    avatar::getWorldPosition((avatar *)av->body->actor,&av->body->currentPos);
  }
  avatar::getWorldPosition(*(avatar **)(in_EAX + 0x2c),&local_24);
  avatar::getWorldPosition((avatar *)av,&local_18);
  local_c.x = local_24.x - local_18.x;
  local_c.y = local_24.y - local_18.y;
  local_c.z = local_24.z - local_18.z;
  vec3::getTurnAngle(&local_c,local_2c);
  local_c.x = 0.0;
  local_c.y = local_2c[0];
  local_c.z = 0.0;
  Maths::NormaliseAngles2PI(&local_c,&(av->avatar).rotEuler);
  (av->avatar).scaleIsCalculated = 0;
  local_2c[1] = 1.26117e-44;
  (*((av->avatar).object.vtable)->onMessage)(av,local_2c + 1);
  return av;
}




void FUN_0009a330(vec3 *param_1)

{
  Model *pMVar1;
  actor *in_EAX;
  uint32_t uVar2;
  undefined4 uVar3;
  Skeleton *pSVar4;
  int iVar5;
  
  iVar5 = DAT_00428684;
  uVar2 = actor::getSubres0x2EntryById(in_EAX,4);
  uVar3 = 0;
  if (uVar2 != 0) {
    if ((int)(uVar2 - 1) < iVar5) {
      iVar5 = uVar2 - 1;
    }
    uVar3 = FUN_000409d0(4,iVar5);
  }
  pMVar1 = (in_EAX->avatar).model;
  if (pMVar1 == (Model *)0x0) {
    pSVar4 = (Skeleton *)0x0;
  }
  else {
    pSVar4 = pMVar1->skeleton;
    if (pSVar4 == (Skeleton *)0x0) {
      pSVar4 = pMVar1->skeleton2;
    }
  }
  FUN_00051ce0((int)pSVar4,uVar3,param_1,&(in_EAX->avatar).drawAffine);
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


float10 FUN_000a6950(void)

{
  float fVar1;
  float fVar2;
  float fVar3;
  int in_EAX;
  vec3 local_c;
  
  fVar1 = *(float *)(in_EAX + 0x3c);
  fVar2 = *(float *)(in_EAX + 0x40);
  fVar3 = *(float *)(in_EAX + 0x44);
  avatar::getWorldPosition(*(avatar **)(in_EAX + 8),&local_c);
  local_c.x = local_c.x - fVar1;
  local_c.y = local_c.y - fVar2;
  local_c.z = local_c.z - fVar3;
  return SQRT((float10)local_c.x * (float10)local_c.x +
              (float10)local_c.y * (float10)local_c.y + (float10)local_c.z * (float10)local_c.z);
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


undefined4 FUN_000c8590(entityWeaponExtinguisher *param_1,vec3 *param_2,vec3 *param_3)

{
  entityWeaponExtinguisher *peVar1;
  Buffer<> **ppBVar2;
  undefined4 local_4;
  
  peVar1 = param_1;
  local_4 = 0;
  if (param_1->particles != (Buffer<> *)0x0) {
    FUN_000c8610(param_2,param_1,param_1->particles,param_3,&local_4);
  }
  ppBVar2 = param_1->particleLists;
  param_1 = (entityWeaponExtinguisher *)0x8;
  do {
    if (*ppBVar2 != (Buffer<> *)0x0) {
      FUN_000c8610(param_2,peVar1,*ppBVar2,param_3,&local_4);
    }
    ppBVar2 = ppBVar2 + 1;
    param_1 = (entityWeaponExtinguisher *)
              ((int)&param_1[-1].somebullshitprojectileairresistance + 3);
  } while (param_1 != (entityWeaponExtinguisher *)0x0);
  return local_4;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields

void FUN_000c8610(vec3 *param_1,entityWeaponExtinguisher *param_2,int param_3,vec3 *param_4,
                 int *param_5)

{
  ushort *puVar1;
  undefined2 *puVar2;
  Collision0x54 *pCVar3;
  float *pfVar4;
  undefined4 *puVar5;
  int iVar6;
  int iVar7;
  float *pfVar8;
  int iVar9;
  undefined2 *puVar10;
  int iVar11;
  ushort *puVar12;
  undefined4 uVar13;
  uint uVar14;
  float *pfVar15;
  uint uVar16;
  HeapTableEntry *pHVar17;
  int iVar18;
  float fVar19;
  float fVar20;
  float fVar21;
  float fVar22;
  int local_44;
  vec3 local_30;
  float local_24;
  float local_20;
  float local_1c;
  float local_18;
  float local_14;
  float local_10;
  vec3 local_c;
  
  fVar22 = param_2->field143_0xee8 * 0.7 + 0.3;
  fVar20 = 0.0;
  iVar6 = 0;
  do {
    fVar19 = (float)iVar6 * 0.2 * 5.0 + 3.0;
    if (fVar19 <= 8.0) {
      if (fVar19 < 3.0) {
        fVar19 = 3.0;
      }
    }
    else {
      fVar19 = 8.0;
    }
    iVar6 = iVar6 + 1;
    fVar20 = fVar19 * fVar22 * 2.0 + fVar20;
  } while (iVar6 < 5);
  fVar20 = param_2->somebullshitprojectileairresistance * fVar20;
  local_30.y = param_4->y * -12.0 + param_1->y;
  local_30.z = param_4->z * -12.0 + param_1->z;
  local_30.x = param_1->x + param_4->x * -12.0;
  local_c.y = param_4->y * fVar20 + param_1->y;
  local_c.z = param_4->z * fVar20 + param_1->z;
  local_c.x = param_1->x + param_4->x * fVar20;
  iVar6 = Collision::checkAvatarsWithCollisionInScene(&local_30,&local_c,Walls,FUN_000c4000);
  if (iVar6 != 0) {
    pCVar3 = (Physics::CollisionContexts[0].ctx)->head;
    local_24 = (pCVar3->velocity).x;
    local_20 = (pCVar3->velocity).y;
    local_1c = (pCVar3->velocity).z;
  }
  iVar7 = FUN_001228f0(&local_30,2);
  if (iVar7 == 0) {
    if (iVar6 == 0) goto LAB_000c893c;
  }
  else {
    pCVar3 = (Physics::CollisionContexts[0].ctx)->head;
    local_24 = (pCVar3->velocity).x;
    local_20 = (pCVar3->velocity).y;
    local_1c = (pCVar3->velocity).z;
  }
  pfVar15 = *(float **)(param_3 + 4);
  pfVar4 = *(float **)(param_3 + 8);
  if (pfVar15 < pfVar4) {
    pfVar8 = pfVar15 + 5;
    do {
      if ((*(char *)((int)pfVar8 + 0xf) == '\0') &&
         ((local_30.z - local_c.z) * (local_30.z - local_c.z) +
          (local_30.y - local_c.y) * (local_30.y - local_c.y) +
          (local_30.x - local_c.x) * (local_30.x - local_c.x) <=
          (local_30.z - pfVar8[-3]) * (local_30.z - pfVar8[-3]) +
          (local_30.y - pfVar8[-4]) * (local_30.y - pfVar8[-4]) +
          (local_30.x - *pfVar15) * (local_30.x - *pfVar15))) {
        fVar20 = (*pfVar8 * -1.0 * local_1c + pfVar8[-1] * -1.0 * local_20 +
                 pfVar8[-2] * -1.0 * local_24) * 2.0;
        fVar19 = fVar20 * local_24 - pfVar8[-2] * -1.0;
        pfVar8[-1] = local_20 * fVar20 - pfVar8[-1] * -1.0;
        pfVar8[-2] = fVar19;
        *pfVar8 = local_1c * fVar20 - *pfVar8 * -1.0;
        pfVar8[-2] = fVar19 * 0.9;
        pfVar8[-1] = pfVar8[-1] * 0.9;
        *pfVar8 = *pfVar8 * 0.9;
        *(undefined1 *)((int)pfVar8 + 0xf) = 1;
      }
      pfVar15 = pfVar15 + 0xe;
      pfVar8 = pfVar8 + 0xe;
    } while (pfVar15 < pfVar4);
  }
LAB_000c893c:
  local_14 = param_4->y * -8.0 + param_1->y;
  local_1c = param_2->field143_0xee8 * 70.0 + 30.0;
  local_10 = param_4->z * -8.0 + param_1->z;
  local_18 = param_1->x + param_4->x * -8.0;
  local_24 = param_4->x * local_1c;
  local_20 = param_4->y * local_1c;
  local_1c = param_4->z * local_1c;
  iVar6 = 0;
  fVar20 = 0.0;
  local_30.x = local_18;
  local_30.y = local_14;
  local_30.z = local_10;
  do {
    fVar19 = (float)iVar6 * 0.2 * 5.0 + 3.0;
    if (fVar19 <= 8.0) {
      fVar21 = 3.0;
      if (3.0 <= fVar19) {
        fVar21 = fVar19;
      }
    }
    else {
      fVar21 = 8.0;
    }
    fVar19 = param_2->somebullshitprojectileairresistance * fVar21 * fVar22;
    fVar20 = fVar19 + fVar20;
    local_18 = param_4->x * fVar20 + local_18;
    local_14 = param_4->y * fVar20 + local_14;
    local_10 = param_4->z * fVar20 + local_10;
    iVar7 = Collision::runWeaponCollision(&local_18,fVar19,Walls,FUN_000c4000);
    iVar9 = FUN_00122b00(&local_18,fVar19,0x802);
    local_44 = 0;
    if (iVar9 != 0) {
      if (*param_5 == 0) {
        if (g_HeapTableBase[runtime::CurrentHeapToAllocateFrom].heapHandle == (HANDLE)0x0) {
          pHVar17 = (HeapTableEntry *)0x0;
        }
        else {
          pHVar17 = g_HeapTableBase + runtime::CurrentHeapToAllocateFrom;
        }
        puVar10 = (undefined2 *)runtime::AllocateOnHeap(pHVar17->heapHandle,0,0x114);
        if (puVar10 != (undefined2 *)0x0) {
          iVar6 = FUN_0014ded0(pHVar17->heapHandle,0,puVar10);
          puVar2 = (undefined2 *)(iVar6 + -4 + (int)puVar10);
          *puVar2 = 0x1234;
          *(undefined1 *)(puVar2 + 1) = *(undefined1 *)&pHVar17->field32_0x20;
        }
        *(undefined2 **)(puVar10 + 2) = puVar10 + 8;
        *(undefined2 **)(puVar10 + 4) = puVar10 + 8;
        *puVar10 = 0x20;
        puVar10[1] = 8;
        *(undefined2 **)(puVar10 + 6) = puVar10 + 0x88;
        *param_5 = (int)puVar10;
      }
      iVar6 = 0;
      if (0 < iVar9) {
        do {
          puVar12 = (ushort *)*param_5;
          if (*(int *)(puVar12 + 4) == *(int *)(puVar12 + 6)) {
            iVar11 = (*(int *)(puVar12 + 4) - *(int *)(puVar12 + 2)) / (int)(uint)*puVar12;
            iVar18 = (uint)puVar12[1] + iVar11;
            puVar12 = (ushort *)AllocateMoreAStruct_33((uint)*puVar12 * iVar18 + 0x10,puVar12);
            puVar1 = puVar12 + 8;
            *(ushort **)(puVar12 + 2) = puVar1;
            *(ushort **)(puVar12 + 6) = (ushort *)((uint)*puVar12 * iVar18 + (int)puVar1);
            *(ushort **)(puVar12 + 4) = (ushort *)((uint)*puVar12 * iVar11 + (int)puVar1);
            *param_5 = (int)puVar12;
          }
          puVar5 = *(undefined4 **)(puVar12 + 4);
          *(uint *)(puVar12 + 4) = (uint)*puVar12 + (int)puVar5;
          *puVar5 = Physics::CollisionContexts[iVar6].collidingAvatar;
          uVar13 = FUN_000fcc90(Physics::CollisionContexts[iVar6].ctx);
          puVar5[1] = uVar13;
          puVar5[2] = local_18;
          puVar5[3] = local_14;
          puVar5[4] = local_10;
          puVar5[5] = local_24;
          puVar5[6] = local_20;
          puVar5[7] = local_1c;
          uVar16 = 0;
          for (uVar14 = *(uint *)(puVar5[1] + 4); uVar14 < *(uint *)(puVar5[1] + 8);
              uVar14 = uVar14 + 0x54) {
            uVar16 = uVar16 | *(uint *)(uVar14 + 0x20);
          }
          if ((uVar16 & 0x800) == 0) {
            local_44 = local_44 + 1;
          }
          iVar6 = iVar6 + 1;
        } while (iVar6 < iVar9);
      }
    }
  } while (((iVar7 < 1) && (local_44 == 0)) && (iVar6 = iVar6 + 1, fVar20 = fVar19, iVar6 < 5));
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void thunk_FUN_000c8ef0(actor *param_1,avatar *param_2,vec3 *param_3,float *param_4)

{
  CalloutDescriptor **ppCVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  avatar_0x918 pEVar5;
  actor *act;
  float *pfVar6;
  vec3 *v;
  int *piVar7;
  avatar *paVar8;
  float10 fVar9;
  avatar_0x1e0 pEVar10;
  float fVar11;
  float fStack_28;
  float fStack_24;
  float fStack_20;
  float fStack_1c;
  vec3 vStack_18;
  vec3 vStack_c;
  
  pfVar6 = (float *)param_2;
  pEVar5 = (param_1->avatar).node0x918.prev;
  if ((pEVar5 == (avatar_0x918)0x0) || (pEVar5->prev == (avatar_0x918)0x0)) {
    param_2 = (avatar *)0x0;
  }
  else {
    param_2 = ADJ(pEVar5);
  }
  FUN_00105e20(param_3,&fStack_24,&fStack_28);
  fStack_20 = 0.0;
  vStack_18.x = *pfVar6;
  vStack_18.y = pfVar6[1];
  vStack_18.z = pfVar6[2];
  avatar::getWorldPosition(param_2,&vStack_c);
  vStack_c.y = pfVar6[1];
  Collision::checkAvatarsWithCollisionInScene(&vStack_c,&vStack_18,Walls,FUN_000c4000);
  act = param_1;
  piVar7 = (int *)FUN_00112c50(0x3f800000);
  if (piVar7 != (int *)0x0) {
    fStack_24 = param_4[1] - pfVar6[1];
    fStack_20 = param_4[2] - pfVar6[2];
    fStack_28 = *param_4 - *pfVar6;
    param_1 = (actor *)(fStack_20 * fStack_20 + fStack_24 * fStack_24 + fStack_28 * fStack_28);
    if ((float)param_1 != 0.0) {
      fVar9 = (float10)invsqrt(param_1);
      fStack_28 = (float)((float10)fStack_28 * fVar9);
      fStack_24 = (float)((float10)fStack_24 * fVar9);
      fStack_20 = (float)((float10)fStack_20 * fVar9);
    }
    v = param_3;
    if (param_3->z * fStack_20 + param_3->y * fStack_24 + param_3->x * fStack_28 < 0.0) {
      fStack_28 = param_3->x;
      fStack_24 = param_3->y;
      fStack_20 = param_3->z;
    }
    fVar2 = *pfVar6;
    fVar3 = pfVar6[1];
    fVar4 = pfVar6[2];
    piVar7[0x363] = (int)param_2;
    fVar11 = fStack_24 * 30.0;
    fStack_1c = fStack_20 * 30.0;
    fStack_24 = fStack_28 * 30.0 + fVar2;
    fStack_20 = fVar11 + fVar3;
    fStack_1c = fStack_1c + fVar4;
    fStack_28 = 2.31214e-43;
    (**(code **)(*piVar7 + 0xc))(piVar7,&fStack_28);
    FUN_00105e20(v,&fStack_24,&fStack_28);
    someFxPos.x = vStack_18.x;
    someFxPos.y = vStack_18.y;
    someFxPos.z = vStack_18.z;
    _DAT_004e1c6c = fStack_28;
    ppCVar1 = &(act->avatar).callout;
    _DAT_004e1c70 = fStack_24;
    _DAT_004e1c74 = 0;
    DAT_004e1c5c = 5;
    if (ppCVar1 != (CalloutDescriptor **)0x0) {
      actor::executeCalloutInDescriptor
                (*ppCVar1,FireGun,(CalloutCallback *)0x0,0x4e1c5c,act,(entityBodyPlayer_0x924)0x0);
    }
    pEVar10 = (avatar_0x1e0)((float)act[1].avatar.avatarCollider.prev - 0.15);
    act[1].avatar.avatarCollider.prev = pEVar10;
    if ((float)pEVar10 < 0.0) {
      FUN_000cae00(pfVar6,v);
    }
    pEVar5 = (act->avatar).node0x918.prev;
    param_1 = (actor *)0x3e;
    if ((pEVar5 == (avatar_0x918)0x0) || (pEVar5->prev == (avatar_0x918)0x0)) {
      paVar8 = (avatar *)0x0;
    }
    else {
      paVar8 = ADJ(pEVar5);
    }
    (*paVar8->vtable->onMessage)(paVar8,&param_1);
  }
  return;
}



// WARNING: Globals starting with '_' overlap smaller symbols at the same address
// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void FUN_000c8ef0(actor *param_1,avatar *param_2,vec3 *param_3,float *param_4)

{
  CalloutDescriptor **ppCVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  avatar_0x918 pEVar5;
  actor *act;
  float *pfVar6;
  vec3 *v;
  int *piVar7;
  avatar *paVar8;
  float10 fVar9;
  avatar_0x1e0 pEVar10;
  float fVar11;
  float local_28;
  float local_24;
  float local_20;
  float local_1c;
  vec3 local_18;
  vec3 local_c;
  
  pfVar6 = (float *)param_2;
  pEVar5 = (param_1->avatar).node0x918.prev;
  if ((pEVar5 == (avatar_0x918)0x0) || (pEVar5->prev == (avatar_0x918)0x0)) {
    param_2 = (avatar *)0x0;
  }
  else {
    param_2 = ADJ(pEVar5);
  }
  FUN_00105e20(param_3,&local_24,&local_28);
  local_20 = 0.0;
  local_18.x = *pfVar6;
  local_18.y = pfVar6[1];
  local_18.z = pfVar6[2];
  avatar::getWorldPosition(param_2,&local_c);
  local_c.y = pfVar6[1];
  Collision::checkAvatarsWithCollisionInScene(&local_c,&local_18,Walls,FUN_000c4000);
  act = param_1;
  piVar7 = (int *)FUN_00112c50(0x3f800000);
  if (piVar7 != (int *)0x0) {
    local_24 = param_4[1] - pfVar6[1];
    local_20 = param_4[2] - pfVar6[2];
    local_28 = *param_4 - *pfVar6;
    param_1 = (actor *)(local_20 * local_20 + local_24 * local_24 + local_28 * local_28);
    if ((float)param_1 != 0.0) {
      fVar9 = (float10)invsqrt(param_1);
      local_28 = (float)((float10)local_28 * fVar9);
      local_24 = (float)((float10)local_24 * fVar9);
      local_20 = (float)((float10)local_20 * fVar9);
    }
    v = param_3;
    if (param_3->z * local_20 + param_3->y * local_24 + param_3->x * local_28 < 0.0) {
      local_28 = param_3->x;
      local_24 = param_3->y;
      local_20 = param_3->z;
    }
    fVar2 = *pfVar6;
    fVar3 = pfVar6[1];
    fVar4 = pfVar6[2];
    piVar7[0x363] = (int)param_2;
    fVar11 = local_24 * 30.0;
    local_1c = local_20 * 30.0;
    local_24 = local_28 * 30.0 + fVar2;
    local_20 = fVar11 + fVar3;
    local_1c = local_1c + fVar4;
    local_28 = 2.31214e-43;
    (**(code **)(*piVar7 + 0xc))(piVar7,&local_28);
    FUN_00105e20(v,&local_24,&local_28);
    someFxPos.x = local_18.x;
    someFxPos.y = local_18.y;
    someFxPos.z = local_18.z;
    _DAT_004e1c6c = local_28;
    ppCVar1 = &(act->avatar).callout;
    _DAT_004e1c70 = local_24;
    _DAT_004e1c74 = 0;
    DAT_004e1c5c = 5;
    if (ppCVar1 != (CalloutDescriptor **)0x0) {
      actor::executeCalloutInDescriptor
                (*ppCVar1,FireGun,(CalloutCallback *)0x0,0x4e1c5c,act,(entityBodyPlayer_0x924)0x0);
    }
    pEVar10 = (avatar_0x1e0)((float)act[1].avatar.avatarCollider.prev - 0.15);
    act[1].avatar.avatarCollider.prev = pEVar10;
    if ((float)pEVar10 < 0.0) {
      FUN_000cae00(pfVar6,v);
    }
    pEVar5 = (act->avatar).node0x918.prev;
    param_1 = (actor *)0x3e;
    if ((pEVar5 == (avatar_0x918)0x0) || (pEVar5->prev == (avatar_0x918)0x0)) {
      paVar8 = (avatar *)0x0;
    }
    else {
      paVar8 = ADJ(pEVar5);
    }
    (*paVar8->vtable->onMessage)(paVar8,&param_1);
  }
  return;
}




void FUN_000c9410(int param_1,float *param_2,vec3 *param_3)

{
  byte *pbVar1;
  short sVar2;
  undefined2 *puVar3;
  int iVar4;
  float local_c;
  float local_8 [2];
  
  puVar3 = malloc_(0x510);
  *puVar3 = 0x28;
  puVar3[1] = 0x20;
  *(undefined2 **)(puVar3 + 2) = puVar3 + 8;
  *(undefined2 **)(puVar3 + 4) = puVar3 + 8;
  *(undefined2 **)(puVar3 + 6) = puVar3 + 0x288;
  *(undefined2 **)(param_1 + 0xf34) = puVar3;
  *(undefined4 *)(param_1 + 0xf38) = 0;
  someFxPos.x = *param_2;
  someFxPos.y = param_2[1];
  someFxPos.z = param_2[2];
  DAT_004e1c5c = 1;
  if (param_3 != (vec3 *)0x0) {
    FUN_00105e20(param_3,local_8,&local_c);
    _DAT_004e1c6c = local_c;
    _DAT_004e1c70 = local_8[0];
    DAT_004e1c5c = DAT_004e1c5c | 4;
    _DAT_004e1c74 = 0;
  }
  iVar4 = spawnFxAndAID(param_1 + 0x10c0,&DAT_004e1c5c);
  if (iVar4 != 0) {
    sVar2 = (short)int32_t_0042a434;
    int32_t_0042a434 = -1;
    if (sVar2 != -1) {
      iVar4 = (&DAT_00506930)[sVar2];
      pbVar1 = (byte *)(iVar4 + 0x18);
      *pbVar1 = *pbVar1 & 0xf7;
      *(int *)(param_1 + 0xefc) = iVar4;
      return;
    }
  }
  *(undefined4 *)(param_1 + 0xefc) = 0;
  return;
}




undefined4 FUN_000cb330(vec3 *param_1,void *this,vec3 *param_3)

{
  AffineTransform *pAVar1;
  int iVar2;
  AffineTransform *pAVar3;
  int iVar4;
  Skeleton *skeleton;
  float10 fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  float fVar10;
  
  if (*(int *)((int)this + 0xeec) == 0) {
    return 0;
  }
  iVar2 = *(int *)((int)this + 0x204);
  if (iVar2 == 0) {
    iVar4 = 0;
  }
  else {
    iVar4 = *(int *)(iVar2 + 0x168);
    if (iVar4 == 0) {
      iVar4 = *(int *)(iVar2 + 0x164);
    }
  }
  pAVar1 = (AffineTransform *)((int)this + 0x2ac);
  FUN_00051ce0(iVar4,*(int *)((int)this + 0xeec),param_1,pAVar1);
  iVar2 = *(int *)((int)this + 0xef0);
  iVar4 = *(int *)((int)this + 0x204);
  if (iVar4 == 0) {
    skeleton = (Skeleton *)0x0;
  }
  else {
    skeleton = *(Skeleton **)(iVar4 + 0x168);
    if (skeleton == (Skeleton *)0x0) {
      skeleton = *(Skeleton **)(iVar4 + 0x164);
    }
  }
  fVar7 = *(float *)(iVar2 + 0x10);
  fVar9 = *(float *)(iVar2 + 0x20);
  fVar10 = *(float *)(iVar2 + 0x30);
  fVar6 = fVar7;
  fVar8 = fVar9;
  if (-1 < *(short *)(iVar2 + 2)) {
    pAVar3 = Skeleton::getBoneAffineIntoGlobal(skeleton,(int)*(short *)(iVar2 + 2));
    fVar6 = pAVar3->m[0][2] * fVar10 + pAVar3->m[0][1] * fVar9 + pAVar3->m[0][0] * fVar7 +
            pAVar3->m[0][3];
    fVar8 = pAVar3->m[1][0] * fVar7 + pAVar3->m[1][2] * fVar10 + pAVar3->m[1][1] * fVar9 +
            pAVar3->m[1][3];
    fVar10 = pAVar3->m[2][0] * fVar7 + pAVar3->m[2][2] * fVar10 + pAVar3->m[2][1] * fVar9 +
             pAVar3->m[2][3];
  }
  fVar7 = fVar6;
  fVar9 = fVar8;
  if (pAVar1 != (AffineTransform *)0x0) {
    fVar7 = *(float *)((int)this + 0x2b4) * fVar10 + *(float *)((int)this + 0x2b0) * fVar8 +
            pAVar1->m[0][0] * fVar6 + *(float *)((int)this + 0x2b8);
    fVar9 = *(float *)((int)this + 700) * fVar6 + *(float *)((int)this + 0x2c4) * fVar10 +
            *(float *)((int)this + 0x2c0) * fVar8 + *(float *)((int)this + 0x2c8);
    fVar10 = *(float *)((int)this + 0x2cc) * fVar6 + *(float *)((int)this + 0x2d4) * fVar10 +
             *(float *)((int)this + 0x2d0) * fVar8 + *(float *)((int)this + 0x2d8);
  }
  param_3->x = fVar7 - param_1->x;
  fVar9 = fVar9 - param_1->y;
  param_3->y = fVar9;
  fVar10 = fVar10 - param_1->z;
  fVar7 = param_3->x * param_3->x + fVar9 * fVar9 + fVar10 * fVar10;
  param_3->z = fVar10;
  if (fVar7 != 0.0) {
    fVar5 = (float10)invsqrt(fVar7);
    param_3->x = (float)(fVar5 * (float10)param_3->x);
    param_3->y = (float)(fVar5 * (float10)param_3->y);
    param_3->z = (float)(fVar5 * (float10)param_3->z);
  }
  return 1;
}




void __thiscall FUN_000cc010(avatar *param_1,vec3 *param_2)

{
  ndSkeleton *pnVar1;
  Model *pMVar2;
  vec3 *in_EAX;
  int num_bones;
  AffineTransform *pAVar3;
  Skeleton *skeleton;
  vec3 local_30;
  float local_24;
  float local_20;
  float local_1c;
  vec3 local_18;
  vec3 local_c;
  
  if ((param_1->model != (Model *)0x0) &&
     (pnVar1 = param_1->model->ndSkeleton, pnVar1 != (ndSkeleton *)0x0)) {
    num_bones = ndSkeleton::getNumBones(pnVar1);
    if (num_bones != 0) {
      FUN_0003b050(0,&local_18);
      avatar::getWorldPosition(param_1,&local_c);
      in_EAX->x = local_18.x;
      in_EAX->y = local_18.y;
      in_EAX->z = local_18.z;
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
      pAVar3 = Skeleton::getBoneAffineIntoGlobal(skeleton,0);
      local_30.x = pAVar3->m[0][1] * Game::someGlobalPos.y + pAVar3->m[0][2] * Game::someGlobalPos.z
                   + pAVar3->m[0][0] * Game::someGlobalPos.x + pAVar3->m[0][3];
      local_30.y = pAVar3->m[1][1] * Game::someGlobalPos.y + pAVar3->m[1][2] * Game::someGlobalPos.z
                   + pAVar3->m[1][0] * Game::someGlobalPos.x + pAVar3->m[1][3];
      local_30.z = pAVar3->m[2][1] * Game::someGlobalPos.y + pAVar3->m[2][2] * Game::someGlobalPos.z
                   + pAVar3->m[2][0] * Game::someGlobalPos.x + pAVar3->m[2][3];
      local_24 = local_30.x;
      local_20 = local_30.y;
      local_1c = local_30.z;
      FUN_00106770(local_30.x,local_30.y,local_30.z,&local_18,&local_30);
      param_2->x = local_c.x - local_30.x;
      param_2->y = local_c.y - local_30.y;
      param_2->z = local_c.z - local_30.z;
      return;
    }
  }
  avatar::getWorldPosition(param_1,param_2);
  Math::GetEulerAngles((D3DXMATRIX *)&param_1->drawAffine,in_EAX);
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


undefined4 __thiscall FUN_000ce290(vec3 *param_1,vec3 *param_2,float param_3)

{
  char cVar1;
  int in_EAX;
  int iVar2;
  void *ptr;
  BOOL BVar3;
  float10 extraout_ST0;
  vec3 local_c;
  
  cVar1 = *(char *)(in_EAX + 0xe86);
  *(undefined1 *)(in_EAX + 0xe86) = 1;
  if (cVar1 == '\0') {
    if (*(avatar **)(in_EAX + 0xd8c) != (avatar *)0x0) {
      avatar::getWorldPosition(*(avatar **)(in_EAX + 0xd8c),&local_c);
      local_c.y = param_1->y;
      Collision::checkAvatarsWithCollisionInScene(&local_c,param_1,Ground|Walls,FUN_000c4000);
    }
    iVar2 = Collision::runWeaponCollision(param_1,param_3,Ground|Walls,FUN_000c4000);
    if (0 < iVar2) {
      ptr = (void *)FUN_00122310();
      FUN_000fc3f0(ptr,param_1,param_3);
      free(ptr);
      return 3;
    }
  }
  BVar3 = Collision::runCollisionFunctionWithAllAvatars
                    (param_2,param_1,param_3,Ground|Walls,FUN_000c4000);
  if (BVar3 != 1) {
    return 1;
  }
  local_c.y = ((Physics::CollisionContexts[0].ctx)->head->velocity).y;
  sin(0.87266463);
  if ((float10)local_c.y < extraout_ST0) {
    return 3;
  }
  return 2;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void __thiscall FUN_000ec830(vec3 *param_1,avatar *param_2,float *param_3)

{
  Model *pMVar1;
  AnimCollisionSubresourceEntry *entry;
  Skeleton *skeleton;
  undefined4 *unaff_EBX;
  float10 extraout_ST0;
  vec3 local_c;
  
  if (param_2 == (avatar *)0x0) {
    param_1->z = 0.0;
    param_1->y = 0.0;
    param_1->x = 0.0;
    return;
  }
  entry = (AnimCollisionSubresourceEntry *)FUN_000ec750(param_2);
  if (entry != (AnimCollisionSubresourceEntry *)0x0) {
    *unaff_EBX = entry;
    pMVar1 = param_2->model;
    if (pMVar1 == (Model *)0x0) {
      skeleton = (Skeleton *)0x0;
    }
    else {
      skeleton = pMVar1->skeleton;
      if (skeleton == (Skeleton *)0x0) {
        skeleton = pMVar1->skeleton2;
      }
    }
    checkCollisionAgainstSkeleton(entry,skeleton,&local_c,&param_2->drawAffine);
    param_1->x = local_c.x;
    param_1->y = local_c.y;
    param_1->z = local_c.z;
    *param_3 = (float)extraout_ST0;
    return;
  }
  avatar::getWorldPosition(param_2,param_1);
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void __fastcall FUN_000ec8e0(vec3 *param_1,actor *param_2,vec3 *param_3,int *param_4)

{
  AffineTransform *pAVar1;
  Model *pMVar2;
  undefined2 in_AX;
  int iVar3;
  BoneAffineSubresourceEntry *pBVar4;
  Skeleton *pSVar5;
  AffineTransform local_30;
  
  if (param_2 == (actor *)0x0) {
    param_1->z = 0.0;
    param_1->y = 0.0;
    param_1->x = 0.0;
    return;
  }
  if ((*param_4 == 0) || (iVar3 = FUN_00040930(param_4), iVar3 == 0)) {
    pBVar4 = actor::getModelBoneAffineByBone1(param_2,in_AX);
  }
  else {
    pBVar4 = (BoneAffineSubresourceEntry *)*param_4;
  }
  if (pBVar4 == (BoneAffineSubresourceEntry *)0x0) {
    avatar::getWorldPosition(&param_2->avatar,param_1);
    return;
  }
  pMVar2 = (param_2->avatar).model;
  if (pMVar2 == (Model *)0x0) {
    pSVar5 = (Skeleton *)0x0;
  }
  else {
    pSVar5 = pMVar2->skeleton;
    if (pSVar5 == (Skeleton *)0x0) {
      pSVar5 = pMVar2->skeleton2;
    }
  }
  pAVar1 = &(param_2->avatar).drawAffine;
  FUN_00051ce0((int)pSVar5,pBVar4,param_1,pAVar1);
  pMVar2 = (param_2->avatar).model;
  if (pMVar2 == (Model *)0x0) {
    pSVar5 = (Skeleton *)0x0;
  }
  else {
    pSVar5 = pMVar2->skeleton;
    if (pSVar5 == (Skeleton *)0x0) {
      pSVar5 = pMVar2->skeleton2;
    }
  }
  Skeleton::getBoneAndWriteAffine(pSVar5,pBVar4,pAVar1,&local_30);
  Math::GetEulerAngles((D3DXMATRIX *)&local_30,param_3);
  *param_4 = (int)pBVar4;
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


int FUN_000ed550(char *param_1,uint param_2,vec3 *param_3,int param_4)

{
  int iVar1;
  fxParticleImpactFlash *pfVar2;
  int iVar3;
  vec3 *in_stack_00000010;
  
  iVar3 = (&DAT_0042a41c)[param_4 * 2];
  iVar1 = (&uint32_t_0042a420)[param_4 * 2] + iVar3;
  if (iVar3 < iVar1) {
    while ((&DAT_00506930)[iVar3] != 0) {
      iVar3 = iVar3 + 1;
      if (iVar1 <= iVar3) {
        return -1;
      }
    }
    if (iVar3 != -1) {
      pfVar2 = Assets::CreateFxParticleImpactFlash(param_1,param_2,param_3,in_stack_00000010);
      (&DAT_00506930)[iVar3] = pfVar2;
      return iVar3;
    }
  }
  return -1;
}




BOOL FUN_000f4f80(vec3 *v1,undefined4 param_2,int param_3)

{
  ushort *puVar1;
  undefined4 uVar2;
  int iVar3;
  uint boxId;
  char *pcVar4;
  undefined4 extraout_ECX;
  undefined4 *puVar5;
  int local_4;
  
  if (((*(int *)(param_3 + 0x14) == 0) || (*(int *)(param_3 + 8) == 0)) ||
     (*(int *)(param_3 + 0x10) == 0)) {
    return 0;
  }
  if (*(int *)(param_3 + 0x20) == 0) {
    uVar2 = FUN_000f3840();
    *(undefined4 *)(param_3 + 0x20) = uVar2;
  }
  if (*(int *)(param_3 + 0x20) == 0) {
    return 1;
  }
  iVar3 = FUN_000f5200(param_2,*(int *)(param_3 + 0x20));
  if (iVar3 == 0) goto LAB_000f5086;
  puVar5 = (undefined4 *)(param_3 + 0x24);
  for (iVar3 = 0x40; iVar3 != 0; iVar3 = iVar3 + -1) {
    *puVar5 = 0;
    puVar5 = puVar5 + 1;
  }
  puVar1 = (ushort *)**(undefined4 **)(param_3 + 0x10);
  local_4 = (*(int *)(puVar1 + 4) - *(int *)(puVar1 + 2)) / (int)(uint)*puVar1;
  if (local_4 < 0x15) {
    local_4 = 0x14;
  }
  if (local_4 == 0) {
    boxId = 0;
LAB_000f5066:
    if (boxId == 0) goto LAB_000f506a;
  }
  else {
    do {
      boxId = FUN_000f5410(v1,*(int *)(param_3 + 0x10));
      if (boxId == 0) break;
      pcVar4 = (char *)(boxId + param_3 + 0x24);
      *pcVar4 = *pcVar4 + '\x01';
      if (*(int *)(param_3 + 0xc) == 0) {
        pcVar4 = (char *)0x0;
        uVar2 = 0;
      }
      else {
        pcVar4 = (char *)FUN_000f36c0();
        uVar2 = extraout_ECX;
      }
      iVar3 = Assets::OpenBoxFromAid(uVar2,*(char **)(param_3 + 0x20),boxId,pcVar4);
      if (iVar3 != 0) {
        if (0 < *(int *)(param_3 + 0x18)) {
          *(int *)(param_3 + 0x18) = *(int *)(param_3 + 0x18) + -1;
        }
        goto LAB_000f5066;
      }
      local_4 = local_4 + -1;
    } while (local_4 != 0);
LAB_000f506a:
    if ((*(int *)(param_3 + 0x18) == -2) &&
       (iVar3 = FUN_000f50d0(), iVar3 == *(int *)(*(int *)(param_3 + 0x10) + 0x10))) {
      return 1;
    }
  }
  *(undefined4 *)(param_3 + 0x20) = 0;
LAB_000f5086:
  if (*(int *)(param_3 + 0x18) != -3) {
    return (uint)(*(int *)(param_3 + 0x18) == 0);
  }
  if ((g_pauseMenuState_ == Paused) && (DAT_0050653c == 0)) {
    return 0;
  }
  return 1;
}




void FUN_000fb120(vec3 *this,float param_2,char *param_3)

{
  float fVar1;
  float fVar2;
  int iVar3;
  vec3 *pvVar4;
  int iVar5;
  float *pfVar6;
  int iVar7;
  vec3 *local_4;
  
  if (*(int *)param_3 == 0x5f646961) {
    local_4 = this;
    Assets::GetResourceBytes(param_3,&local_4);
    pvVar4 = local_4;
    if (local_4 == (vec3 *)0x0) {
      runtime::ExitGame(2);
    }
    else {
      iVar5 = FUN_000fb7c0();
      if (iVar5 != 0) {
        *(float *)(iVar5 + 0x44) = this->x;
        *(float *)(iVar5 + 0x48) = this->y;
        *(float *)(iVar5 + 0x4c) = this->z;
        *(float *)(iVar5 + 0x50) = param_2;
        *(vec3 **)(iVar5 + 0x40) = pvVar4;
        iVar7 = 0;
        pfVar6 = (float *)(iVar5 + 0x18);
        do {
          iVar3 = *(int *)(iVar5 + 0x40);
          pfVar6[1] = (*(float *)(iVar3 + 0x24 + iVar7) - *(float *)(iVar3 + 0x20 + iVar7)) * 0.5 +
                      *(float *)(iVar3 + iVar7 + 0x20);
          fVar1 = *(float *)(*(int *)(iVar5 + 0x40) + 0x24 + iVar7);
          fVar2 = *(float *)(*(int *)(iVar5 + 0x40) + 0x20 + iVar7);
          pfVar6[-2] = 0.0;
          *pfVar6 = (fVar1 - fVar2) * 0.5;
          pfVar6[-1] = *(float *)(*(int *)(iVar5 + 0x40) + 0x2c + iVar7);
          iVar3 = *(int *)(iVar5 + 0x40);
          pfVar6[-6] = 0.0;
          fVar1 = *(float *)(iVar3 + iVar7);
          pfVar6[-5] = fVar1;
          pfVar6[-4] = fVar1;
          pfVar6[-3] = 0.0;
          iVar7 = iVar7 + 0x3c;
          pfVar6 = pfVar6 + 8;
        } while (iVar7 < 0x78);
        return;
      }
      Assets::DestroyAssetOrDecrement(pvVar4);
    }
  }
  return;
}




void FUN_000fca60(vec3 *param_1,ushort *param_2)

{
  float *pfVar1;
  uint uVar2;
  float *pfVar3;
  uint uVar4;
  vec3 *unaff_ESI;
  int iVar5;
  float10 fVar6;
  float fVar7;
  
  uVar2 = *(uint *)(param_2 + 4);
  uVar4 = *(uint *)(param_2 + 2);
  param_1->z = 0.0;
  param_1->y = 0.0;
  param_1->x = 0.0;
  if (3 < (int)((uVar2 - uVar4) + 0x53) / 0x54) {
    iVar5 = ((uVar2 - uVar4) - 0xfd) / 0x150 + 1;
    pfVar3 = (float *)(uVar4 + 0x14);
    uVar4 = uVar4 + iVar5 * 0x150;
    do {
      param_1->x = pfVar3[-2] + param_1->x;
      param_1->y = pfVar3[-1] + param_1->y;
      param_1->z = param_1->z + *pfVar3;
      param_1->x = pfVar3[0x13] + param_1->x;
      param_1->y = pfVar3[0x14] + param_1->y;
      param_1->z = pfVar3[0x15] + param_1->z;
      param_1->x = pfVar3[0x28] + param_1->x;
      param_1->y = pfVar3[0x29] + param_1->y;
      param_1->z = pfVar3[0x2a] + param_1->z;
      param_1->x = pfVar3[0x3d] + param_1->x;
      param_1->y = pfVar3[0x3e] + param_1->y;
      pfVar1 = pfVar3 + 0x3f;
      pfVar3 = pfVar3 + 0x54;
      iVar5 = iVar5 + -1;
      param_1->z = *pfVar1 + param_1->z;
    } while (iVar5 != 0);
  }
  if (uVar4 < uVar2) {
    pfVar3 = (float *)(uVar4 + 0x14);
    iVar5 = ((uVar2 - uVar4) - 1) / 0x54 + 1;
    do {
      param_1->x = pfVar3[-2] + param_1->x;
      param_1->y = pfVar3[-1] + param_1->y;
      fVar7 = *pfVar3;
      pfVar3 = pfVar3 + 0x15;
      iVar5 = iVar5 + -1;
      param_1->z = fVar7 + param_1->z;
    } while (iVar5 != 0);
  }
  iVar5 = (*(int *)(param_2 + 4) - *(int *)(param_2 + 2)) / (int)(uint)*param_2;
  if (iVar5 != 0) {
    fVar7 = (float)iVar5;
    if (iVar5 < 0) {
      fVar7 = fVar7 + 4.2949673e+09;
    }
    fVar7 = 1.0 / fVar7;
    param_1->x = fVar7 * param_1->x;
    param_1->y = fVar7 * param_1->y;
    param_1->z = fVar7 * param_1->z;
  }
  fVar7 = param_1->z * param_1->z + param_1->y * param_1->y + param_1->x * param_1->x;
  if (fVar7 != 0.0) {
    fVar6 = (float10)invsqrt(fVar7);
    param_1->x = (float)(fVar6 * (float10)param_1->x);
    param_1->y = (float)(fVar6 * (float10)param_1->y);
    param_1->z = (float)(fVar6 * (float10)param_1->z);
  }
  return;
}




float Math::AddAnglesUnwrapped(float a,float b)

{
  modf(b + a,6.2831855);
  return 6.2831855;
}




bool Colour::areEqual(Colour param_1,Colour param_2)

{
  uint8_t uVar1;
  uint8_t uVar2;
  uint8_t uVar3;
  uint8_t uVar4;
  
  uVar1 = param_1.r;
  uVar3 = param_1.g;
  uVar2 = param_1.b;
  uVar4 = param_1.a;
  param_1._0_2_ = CONCAT11(param_2.b,param_2.a);
  return CONCAT31(CONCAT21(CONCAT11(uVar1,uVar3),uVar2),uVar4) ==
         CONCAT22(CONCAT11(param_2.r,param_2.g),param_1._0_2_);
}




undefined4 FUN_00103400(vec3 *param_1,vec3 *p1,vec3 *p0,float *param_4,vec3 *p2,vec3 *param_6)

{
  float e1_y;
  float fVar1;
  float e1_z;
  float fVar2;
  float fVar3;
  float magSqrd;
  float fVar4;
  float fVar5;
  float e1_x;
  float fVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  float fVar10;
  
  e1_y = p1->y - p0->y;
  e1_z = p1->z - p0->z;
  e1_x = p1->x - p0->x;
  fVar4 = p2->x - p0->x;
  fVar9 = p2->z - p0->z;
  fVar8 = p2->y - p0->y;
  fVar6 = param_1->y * e1_z - param_1->z * e1_y;
  fVar7 = param_1->z * e1_x - param_1->x * e1_z;
  fVar2 = param_1->x * e1_y - param_1->y * e1_x;
  magSqrd = fVar7 * fVar8 + fVar2 * fVar9 + fVar4 * fVar6;
  if (2e-07 <= magSqrd) {
    fVar3 = param_6->z - p0->z;
    fVar5 = param_6->y - p0->y;
    fVar1 = param_6->x - p0->x;
    fVar2 = fVar3 * fVar2 + fVar5 * fVar7 + fVar1 * fVar6;
    if ((0.0 <= fVar2) && (fVar2 <= magSqrd)) {
      fVar10 = fVar5 * fVar9 - fVar3 * fVar8;
      fVar6 = fVar1 * fVar8 - fVar5 * fVar4;
      fVar7 = fVar3 * fVar4 - fVar1 * fVar9;
      fVar4 = param_1->y * fVar7 + param_1->z * fVar6 + param_1->x * fVar10;
      if ((0.0 <= fVar4) && (fVar4 + fVar2 <= magSqrd)) {
        magSqrd = (fVar6 * e1_z + fVar7 * e1_y + e1_x * fVar10) / magSqrd;
        *param_4 = magSqrd;
        if ((0.0 <= magSqrd) && (magSqrd <= 1.0)) {
          return 1;
        }
      }
    }
  }
  return 0;
}



void __fastcall

float10 FUN_00103850(void)

{
  float10 extraout_ST0;
  float in_XMM0_Da;
  
  sin(in_XMM0_Da * 3.1415927 - 1.5707964);
  return (extraout_ST0 + (float10)1.0) * (float10)0.5;
}



void calculatePhysicsWithCallbacks
               (EntityMoveContext *ctx,vec3 *inPos,vec3 *inAccumulator,vec3 *outPos,
               vec3 *outAccumulator,float tickLength,uint tickCount,
               UpdatePhysicsCallback1 *callback1,undefined *callback2,undefined *callback3)

{
  float halfDelta;
  vec3 pos;
  vec3 acc;
  vec3 nextPos;
  vec3 nextAcc;
  vec3 velocity;
  
  if ((tickCount != 0) && (tickLength != 0.0)) {
    pos.x = inPos->x;
    halfDelta = tickLength * 0.5;
    pos.y = inPos->y;
    pos.z = inPos->z;
    acc.x = inAccumulator->x;
    acc.y = inAccumulator->y;
    acc.z = inAccumulator->z;
                    // Process the ticks
    do {
      (*callback1)(ctx,&pos,&acc,&velocity);
      nextPos.x = velocity.x * tickLength + pos.x;
      nextPos.y = velocity.y * tickLength + pos.y;
      nextPos.z = velocity.z * tickLength + pos.z;
      (*(code *)callback2)(ctx,&pos,&nextPos);
      nextAcc.x = (nextPos.x + pos.x) * halfDelta + acc.x;
      nextAcc.y = (nextPos.y + pos.y) * halfDelta + acc.y;
      nextAcc.z = (nextPos.z + pos.z) * halfDelta + acc.z;
      (*(code *)callback3)(ctx,&acc,&nextAcc);
      tickCount = tickCount - 1;
      pos.x = nextPos.x;
      pos.y = nextPos.y;
      pos.z = nextPos.z;
      acc.x = nextAcc.x;
      acc.y = nextAcc.y;
      acc.z = nextAcc.z;
    } while (tickCount != 0);
    outPos->x = nextPos.x;
    outPos->y = nextPos.y;
    outPos->z = nextPos.z;
    outAccumulator->x = nextAcc.x;
    outAccumulator->y = nextAcc.y;
    outAccumulator->z = nextAcc.z;
    return;
  }
                    // Fallback to just returning same pos and acc
  outPos->x = inPos->x;
  outPos->y = inPos->y;
  outPos->z = inPos->z;
  outAccumulator->x = inAccumulator->x;
  outAccumulator->y = inAccumulator->y;
  outAccumulator->z = inAccumulator->z;
  return;
}



// Trust this is correct, theres some weird pointer stuff going on.
// 
// It rips out <xx,xy,xz>  <yx,yy,yz>  <zx,zy,zz>, and returns a vec3 with the magnitude of each
// one.
// 
// xx   yx   zx   tx
// xy   yy   zy   ty
// xz   yz   zz   yz


void AffineTransform::getScaleBases(AffineTransform *param_1,vec3 *scales)

{
  float fVar1;
  float fVar2;
  AffineTransform_ptr_32_undefined1 pfVar1;
  int i;
  float10 fVar3;
  float basis_size;
  
  i = 0;
  pfVar1 = (AffineTransform_ptr_32_undefined1)(param_1->m + 2);
  do {
    basis_size = ADJ(pfVar1).m[1][0];
    fVar1 = ADJ(pfVar1).m[0][0];
    fVar2 = ADJ(pfVar1).m[2][0];
    basis_size = fVar2 * fVar2 + basis_size * basis_size + fVar1 * fVar1;
    (&scales->x)[i] = basis_size;
    if (basis_size != 0.0) {
      fVar3 = scaled_invsqrt(basis_size);
      (&scales->x)[i] = (float)fVar3;
    }
    i = i + 1;
    pfVar1 = (AffineTransform_ptr_32_undefined1)(ADJ(pfVar1).m[2] + 1);
  } while (i < 3);
  return;
}




void Math::NormaliseAndScale(float param_1,float *param_2)

{
  float *pfVar1;
  int iVar1;
  float *pfVar2;
  float10 fVar3;
  float fVar4;
  vec3 afStack_c;
  
  iVar1 = 0;
  pfVar1 = param_2 + 8;
  pfVar2 = pfVar1;
  do {
    fVar4 = *pfVar2 * *pfVar2 + pfVar2[-4] * pfVar2[-4] + pfVar2[-8] * pfVar2[-8];
    if (fVar4 == 0.0) {
      fVar4 = 1.0;
LAB_00103b7e:
      (&afStack_c.x)[iVar1] = fVar4;
    }
    else {
      fVar3 = (float10)invsqrt(fVar4);
      fVar4 = (float)fVar3;
      (&afStack_c.x)[iVar1] = fVar4;
      if (fVar4 != 0.0) {
        fVar4 = fVar4 * param_1;
        goto LAB_00103b7e;
      }
    }
    iVar1 = iVar1 + 1;
    pfVar2 = pfVar2 + 1;
    if (2 < iVar1) {
      iVar1 = 0;
      do {
        pfVar1[-8] = pfVar1[-8] * (&afStack_c.x)[iVar1];
        pfVar1[-4] = pfVar1[-4] * (&afStack_c.x)[iVar1];
        *pfVar1 = *pfVar1 * (&afStack_c.x)[iVar1];
        iVar1 = iVar1 + 1;
        pfVar1 = pfVar1 + 1;
      } while (iVar1 < 3);
      return;
    }
  } while( true );
}




void Math::RotatePointUsingAffine(vec3 *point,AffineTransform *inAffine,vec3 *rotated)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  AffineTransform affine;
  
  affine.m[0][0] = inAffine->m[0][0];
  affine.m[0][1] = inAffine->m[0][1];
  affine.m[0][2] = inAffine->m[0][2];
  affine.m[0][3] = inAffine->m[0][3];
  affine.m[1][0] = inAffine->m[1][0];
  affine.m[1][1] = inAffine->m[1][1];
  affine.m[1][2] = inAffine->m[1][2];
  affine.m[1][3] = inAffine->m[1][3];
  affine.m[2][0] = inAffine->m[2][0];
  affine.m[2][1] = inAffine->m[2][1];
  affine.m[2][2] = inAffine->m[2][2];
  affine.m[2][3] = inAffine->m[2][3];
  NormaliseAndScale(1.0,(float *)&affine);
  fVar1 = point->y;
  fVar2 = point->y;
  fVar3 = point->x;
  fVar4 = point->z;
  fVar5 = point->x;
  fVar6 = point->z;
  rotated->x = point->x * affine.m[0][0] + affine.m[0][1] * point->y + affine.m[0][2] * point->z;
  rotated->y = fVar3 * affine.m[1][0] + affine.m[1][1] * fVar1 + affine.m[1][2] * fVar4;
  rotated->z = fVar5 * affine.m[2][0] + affine.m[2][1] * fVar2 + affine.m[2][2] * fVar6;
  return;
}



void Maths::TransformMatrixFromPosRot
               (vec3 *pos,vec3 *euler,vec3 *scale,AffineTransform *outMatrix,AffineTransform *m2)

{
  float fVar1;
  float fVar2;
  float10 extraout_ST0;
  float10 fVar3;
  float10 extraout_ST0_00;
  float10 extraout_ST0_01;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  float fVar10;
  float fVar11;
  
  fVar6 = euler->x;
  sin(fVar6);
  fVar5 = (float)extraout_ST0;
  fVar3 = (float10)cos(fVar6);
  fVar6 = (float)fVar3;
  fVar9 = euler->y;
  sin(fVar9);
  fVar7 = (float)extraout_ST0_00;
  fVar3 = (float10)cos(fVar9);
  fVar9 = (float)fVar3;
  fVar2 = euler->z;
  sin(fVar2);
  fVar1 = (float)extraout_ST0_01;
  fVar3 = (float10)cos(fVar2);
  fVar2 = (float)fVar3;
  outMatrix->m[1][0] = fVar1 * fVar6;
  fVar11 = fVar1 * fVar9 * fVar5 - fVar2 * fVar7;
  fVar10 = fVar7 * fVar5 * fVar1 + fVar2 * fVar9;
  fVar4 = fVar7 * fVar5 * fVar2 - fVar1 * fVar9;
  fVar8 = fVar1 * fVar7 + fVar2 * fVar9 * fVar5;
  outMatrix->m[0][1] = fVar4;
  outMatrix->m[2][2] = fVar9 * fVar6;
  outMatrix->m[0][0] = fVar10;
  outMatrix->m[2][0] = fVar11;
  outMatrix->m[1][1] = fVar2 * fVar6;
  outMatrix->m[2][1] = fVar8;
  outMatrix->m[0][2] = fVar7 * fVar6;
  outMatrix->m[1][2] = 0.0 - fVar5;
  if (scale->x != 1.0) {
    outMatrix->m[0][0] = fVar10 * scale->x;
    outMatrix->m[1][0] = fVar1 * fVar6 * scale->x;
    outMatrix->m[2][0] = fVar11 * scale->x;
  }
  if (scale->y != 1.0) {
    outMatrix->m[0][1] = fVar4 * scale->y;
    outMatrix->m[1][1] = fVar2 * fVar6 * scale->y;
    outMatrix->m[2][1] = fVar8 * scale->y;
  }
  if (scale->z != 1.0) {
    outMatrix->m[0][2] = fVar7 * fVar6 * scale->z;
    outMatrix->m[1][2] = (0.0 - fVar5) * scale->z;
    outMatrix->m[2][2] = fVar9 * fVar6 * scale->z;
  }
  outMatrix->m[0][3] = pos->x;
  outMatrix->m[1][3] = pos->y;
  outMatrix->m[2][3] = pos->z;
  if (m2 != (AffineTransform *)0x0) {
    if (((scale->x == 1.0) && (scale->y == 1.0)) && (scale->z == 1.0)) {
      m2->m[0][0] = outMatrix->m[0][0];
      m2->m[0][1] = outMatrix->m[1][0];
      m2->m[0][2] = outMatrix->m[2][0];
      m2->m[1][0] = outMatrix->m[0][1];
      m2->m[1][1] = outMatrix->m[1][1];
      m2->m[1][2] = outMatrix->m[2][1];
      m2->m[2][0] = outMatrix->m[0][2];
      m2->m[2][1] = outMatrix->m[1][2];
      m2->m[2][2] = outMatrix->m[2][2];
    }
    else {
      fVar5 = 1.0 / (scale->x * scale->x);
      m2->m[0][0] = outMatrix->m[0][0] * fVar5;
      m2->m[0][1] = outMatrix->m[1][0] * fVar5;
      m2->m[0][2] = fVar5 * outMatrix->m[2][0];
      fVar5 = 1.0 / (scale->y * scale->y);
      m2->m[1][0] = fVar5 * outMatrix->m[0][1];
      m2->m[1][1] = outMatrix->m[1][1] * fVar5;
      m2->m[1][2] = fVar5 * outMatrix->m[2][1];
      fVar5 = 1.0 / (scale->z * scale->z);
      m2->m[2][0] = outMatrix->m[0][2] * fVar5;
      m2->m[2][1] = outMatrix->m[1][2] * fVar5;
      m2->m[2][2] = outMatrix->m[2][2] * fVar5;
    }
    fVar6 = 0.0 - pos->x;
    fVar7 = 0.0 - pos->y;
    fVar9 = 0.0 - pos->z;
    fVar5 = m2->m[1][0];
    m2->m[0][3] = m2->m[0][1] * fVar7 + m2->m[0][0] * fVar6 + m2->m[0][2] * fVar9;
    m2->m[1][3] = m2->m[1][2] * fVar9 + fVar5 * fVar6 + m2->m[1][1] * fVar7;
    m2->m[2][3] = m2->m[2][1] * fVar7 + m2->m[2][2] * fVar9 + m2->m[2][0] * fVar6;
  }
  return;
}




void Math::GetEulerAngles(D3DXMATRIX *param_1,vec3 *euler)

{
  float10 x10;
  float x;
  D3DXMATRIX *ptr;
  float fStack_2c;
  float local_28;
  float fStack_24;
  float local_20;
  float zog;
  float xog;
  float fStack_14;
  float fStack_10;
  float local_c;
  float yog;
  float fStack_4;
  
  ptr = (D3DXMATRIX *)param_1->m[0][0];
  fStack_2c = param_1->m[0][1];
  local_28 = param_1->m[0][2];
  fStack_24 = param_1->m[0][3];
  local_20 = param_1->m[1][0];
  zog = param_1->m[1][1];
  xog = param_1->m[1][2];
  fStack_14 = param_1->m[1][3];
  fStack_10 = param_1->m[2][0];
  local_c = param_1->m[2][1];
  yog = param_1->m[2][2];
  fStack_4 = param_1->m[2][3];
  NormaliseAndScale(1.0,(float *)&ptr);
  xog = 0.0 - xog;
  if (xog < 1.0) {
    if (-1.0 < xog) {
      x10 = (float10)arcsin(xog);
      x = (float)x10;
    }
    else {
      x = -1.5707964;
    }
  }
  else {
    x = 1.5707964;
  }
  euler->x = x;
  if ((local_28 == 0.0) && (yog == 0.0)) {
    local_28 = fStack_2c;
    yog = local_c;
  }
  x10 = atan2(yog,local_28);
  euler->y = (float)x10;
  if ((local_20 == 0.0) && (zog == 0.0)) {
    euler->z = 0.0;
    return;
  }
  x10 = atan2(zog,local_20);
  euler->z = (float)x10;
  return;
}




BOOL Maths::InvertAffineMatrix(D3DXMATRIX *this,D3DMATRIX *outMat)

{
  float fVar1;
  D3DMATRIX *pfVar1;
  float fVar2;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  undefined4 local_8;
  undefined4 local_4;
  
  pfVar1 = outMat;
  if (this == outMat) {
    pfVar1 = (D3DMATRIX *)&stack0xffffffd0;
  }
  fVar2 = (((this->m[1][1] * this->m[0][0] * this->m[2][2] +
             this->m[0][1] * this->m[1][2] * this->m[2][0] +
            this->m[1][0] * this->m[2][1] * this->m[0][2]) -
           this->m[1][1] * this->m[2][0] * this->m[0][2]) -
          this->m[0][1] * this->m[1][0] * this->m[2][2]) -
          this->m[2][1] * this->m[1][2] * this->m[0][0];
  if (fVar2 == 0.0) {
    return 0;
  }
  fVar2 = 1.0 / fVar2;
  pfVar1->m[0][0] = (this->m[1][1] * this->m[2][2] - this->m[2][1] * this->m[1][2]) * fVar2;
  pfVar1->m[0][1] = 0.0 - (this->m[0][1] * this->m[2][2] - this->m[2][1] * this->m[0][2]) * fVar2;
  pfVar1->m[0][2] = (this->m[0][1] * this->m[1][2] - this->m[1][1] * this->m[0][2]) * fVar2;
  pfVar1->m[1][0] = 0.0 - (this->m[1][0] * this->m[2][2] - this->m[1][2] * this->m[2][0]) * fVar2;
  pfVar1->m[1][1] = (this->m[0][0] * this->m[2][2] - this->m[2][0] * this->m[0][2]) * fVar2;
  pfVar1->m[1][2] = 0.0 - (this->m[1][2] * this->m[0][0] - this->m[1][0] * this->m[0][2]) * fVar2;
  pfVar1->m[2][0] = (this->m[1][0] * this->m[2][1] - this->m[1][1] * this->m[2][0]) * fVar2;
  pfVar1->m[2][1] = 0.0 - (this->m[2][1] * this->m[0][0] - this->m[0][1] * this->m[2][0]) * fVar2;
  fVar1 = pfVar1->m[0][0];
  pfVar1->m[2][2] = (this->m[1][1] * this->m[0][0] - this->m[0][1] * this->m[1][0]) * fVar2;
  fVar2 = pfVar1->m[1][0];
  pfVar1->m[0][3] =
       ((0.0 - fVar1 * this->m[0][3]) - this->m[1][3] * pfVar1->m[0][1]) -
       pfVar1->m[0][2] * this->m[2][3];
  fVar1 = pfVar1->m[2][0];
  pfVar1->m[1][3] =
       ((0.0 - fVar2 * this->m[0][3]) - this->m[1][3] * pfVar1->m[1][1]) -
       this->m[2][3] * pfVar1->m[1][2];
  pfVar1->m[2][3] =
       ((0.0 - fVar1 * this->m[0][3]) - pfVar1->m[2][1] * this->m[1][3]) -
       pfVar1->m[2][2] * this->m[2][3];
  if (pfVar1 == (D3DMATRIX *)&stack0xffffffd0) {
    outMat->m[0][0] = (float)local_30;
    outMat->m[0][1] = (float)local_2c;
    outMat->m[0][2] = (float)local_28;
    outMat->m[0][3] = (float)local_24;
    outMat->m[1][0] = (float)local_20;
    outMat->m[1][1] = (float)local_1c;
    outMat->m[1][2] = (float)local_18;
    outMat->m[1][3] = (float)local_14;
    outMat->m[2][0] = (float)local_10;
    outMat->m[2][1] = (float)local_c;
    outMat->m[2][2] = (float)local_8;
    outMat->m[2][3] = (float)local_4;
  }
  return 1;
}




void Math::GetRotationMatrix(vec3 *axis,float angle,AffineTransform *affine)

{
  float fVar1;
  float fVar2;
  float10 sint;
  float10 ct;
  float fVar3;
  float fVar4;
  float fVar5;
  vec3 norm;
  
  sin(angle);
  fVar1 = (float)sint;
  ct = (float10)cos(angle);
  fVar2 = (float)ct;
  fVar3 = 1.0 - fVar2;
  D3DX8::D3DXVec3Normalize(&norm,axis);
  affine->m[0][0] = norm.x * norm.x * fVar3 + fVar2;
  fVar5 = norm.y * norm.x * fVar3;
  affine->m[1][0] = norm.z * fVar1 + fVar5;
  fVar4 = norm.z * norm.x * fVar3;
  affine->m[0][1] = fVar5 - norm.z * fVar1;
  affine->m[1][1] = norm.y * norm.y * fVar3 + fVar2;
  affine->m[2][0] = fVar4 - norm.y * fVar1;
  fVar5 = norm.z * norm.y * fVar3;
  affine->m[0][2] = norm.y * fVar1 + fVar4;
  affine->m[0][3] = 0.0;
  affine->m[1][2] = fVar5 - norm.x * fVar1;
  affine->m[1][3] = 0.0;
  affine->m[2][1] = norm.x * fVar1 + fVar5;
  affine->m[2][2] = norm.z * norm.z * fVar3 + fVar2;
  affine->m[2][3] = 0.0;
  return;
}




void AffineTransform::fromQuaternion(AffineTransform *param_1,Quaternion *param_2)

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
  
  fVar2 = 2.0 / (param_2->x * param_2->x + param_2->y * param_2->y + param_2->z * param_2->z +
                param_2->w * param_2->w);
  fVar1 = param_2->z * fVar2;
  fVar7 = param_2->x * fVar2;
  fVar2 = param_2->y * fVar2;
  fVar3 = fVar2 * param_2->w;
  fVar4 = fVar1 * param_2->w;
  fVar5 = param_2->x * fVar7;
  fVar6 = param_2->x * fVar2;
  fVar9 = param_2->z * fVar1;
  fVar2 = param_2->y * fVar2;
  fVar8 = param_2->y * fVar1;
  fVar7 = fVar7 * param_2->w;
  fVar1 = param_2->x * fVar1;
  param_1->m[0][1] = fVar6 - fVar4;
  param_1->m[1][0] = fVar6 + fVar4;
  param_1->m[0][2] = fVar1 + fVar3;
  param_1->m[1][1] = 1.0 - (fVar9 + fVar5);
  param_1->m[0][0] = 1.0 - (fVar9 + fVar2);
  param_1->m[0][3] = 0.0;
  param_1->m[1][2] = fVar8 - fVar7;
  param_1->m[1][3] = 0.0;
  param_1->m[2][0] = fVar1 - fVar3;
  param_1->m[2][1] = fVar8 + fVar7;
  param_1->m[2][2] = 1.0 - (fVar2 + fVar5);
  param_1->m[2][3] = 0.0;
  return;
}




void Maths::EulerToQuaternion(vec3 *v3,Quaternion *param_2)

{
  float fVar1;
  float10 shx;
  float10 cs_x;
  float10 shy;
  float10 cs_y;
  float10 fVar3;
  float10 cs_z;
  float fVar4;
  float fVar5;
  float fVar2;
  float fVar6;
  float hx;
  
  fVar1 = v3->x * 0.5;
  sin(fVar1);
  cs_x = (float10)cos(fVar1);
  fVar1 = v3->y * 0.5;
  sin(fVar1);
  cs_y = (float10)cos(fVar1);
  hx = v3->z * 0.5;
  sin(hx);
  fVar1 = (float)fVar3;
  cs_z = (float10)cos(hx);
  hx = (float)cs_z;
  fVar4 = (float)shy * (float)cs_x;
  fVar5 = (float)cs_y * (float)cs_x;
  fVar6 = (float)cs_y * (float)shx;
  fVar2 = (float)shy * (float)shx;
  param_2->y = fVar4 * hx - fVar6 * fVar1;
  param_2->x = fVar4 * fVar1 + fVar6 * hx;
  param_2->z = fVar5 * fVar1 - fVar2 * hx;
  param_2->w = fVar2 * fVar1 + fVar5 * hx;
  return;
}




void Math::WrapAnglesRad(vec3 *param_1)

{
  float fVar1;
  
  fVar1 = modf(param_1->x,6.2831855);
  if (fVar1 < -3.1415927) {
    fVar1 = fVar1 + 6.2831855;
  }
  if (3.1415927 <= fVar1) {
    fVar1 = fVar1 - 6.2831855;
  }
  param_1->x = fVar1;
  fVar1 = modf(param_1->y,6.2831855);
  if (fVar1 < -3.1415927) {
    fVar1 = fVar1 + 6.2831855;
  }
  if (3.1415927 <= fVar1) {
    fVar1 = fVar1 - 6.2831855;
  }
  param_1->y = fVar1;
  fVar1 = modf(param_1->z,6.2831855);
  if (fVar1 < -3.1415927) {
    fVar1 = fVar1 + 6.2831855;
  }
  if (3.1415927 <= fVar1) {
    fVar1 = fVar1 - 6.2831855;
  }
  param_1->z = fVar1;
  return;
}




void Maths::NormaliseAngles2PI(vec3 *v1,vec3 *v2)

{
  float fVar1;
  
  fVar1 = modf(v1->x,6.2831855);
  if (fVar1 < -3.1415927) {
    fVar1 = fVar1 + 6.2831855;
  }
  if (3.1415927 <= fVar1) {
    fVar1 = fVar1 - 6.2831855;
  }
  v2->x = fVar1;
  fVar1 = modf(v1->y,6.2831855);
  if (fVar1 < -3.1415927) {
    fVar1 = fVar1 + 6.2831855;
  }
  if (3.1415927 <= fVar1) {
    fVar1 = fVar1 - 6.2831855;
  }
  v2->y = fVar1;
  fVar1 = modf(v1->z,6.2831855);
  if (fVar1 < -3.1415927) {
    fVar1 = fVar1 + 6.2831855;
  }
  if (3.1415927 <= fVar1) {
    fVar1 = fVar1 - 6.2831855;
  }
  v2->z = fVar1;
  return;
}




float10 __fastcall FUN_00105d90(float *param_1)

{
  float10 fVar1;
  
  if ((*param_1 == 0.0) && (param_1[1] == 0.0)) {
    return (float10)0.0;
  }
  fVar1 = atan2(*param_1,param_1[1]);
  return fVar1;
}




undefined4 FUN_00105e20(vec3 *v,float *this,float *param_3)

{
  undefined4 uVar1;
  float10 fVar2;
  float local_8;
  float vx;
  float vy;
  float vz;
  
  vx = v->x;
  local_8 = 0.0;
  vy = v->y;
  vz = v->z;
  uVar1 = 1;
  fVar2 = abs_float(vx);
  if ((float10)2e-07 < fVar2) {
LAB_00105e9b:
    fVar2 = scaled_invsqrt(vz * vz + vx * vx);
    local_8 = (float)fVar2;
  }
  else {
    fVar2 = abs_float(vz);
    if ((float10)2e-07 < fVar2) goto LAB_00105e9b;
    *this = 0.0;
    *param_3 = 0.0;
    uVar1 = 0;
  }
  fVar2 = abs_float(vx);
  if (fVar2 <= (float10)2e-07) {
    fVar2 = abs_float(vz);
    if (fVar2 <= (float10)2e-07) {
      *this = 0.0;
      uVar1 = 0;
      goto LAB_00105f18;
    }
  }
  fVar2 = atan2(vz,vx);
  *this = (float)fVar2;
LAB_00105f18:
  fVar2 = abs_float(vy);
  if (fVar2 <= (float10)2e-07) {
    fVar2 = abs_float(local_8);
    if (fVar2 <= (float10)2e-07) {
      *param_3 = 0.0;
      return 0;
    }
  }
  fVar2 = atan2(local_8,0.0 - vy);
  *param_3 = (float)fVar2;
  return uVar1;
}




bool vec3::getTurnAngle(vec3 *param_1,float *outAngle)

{
  float10 fVar1;
  float x;
  float z;
  
  x = param_1->x;
  z = param_1->z;
  fVar1 = abs_float(x);
                    // If |x| == 0
  if (fVar1 <= (float10)2e-07) {
    fVar1 = abs_float(z);
                    // if |z| == 0
    if (fVar1 <= (float10)2e-07) {
      *outAngle = 0.0;
      return false;
    }
  }
                    // Gets angle between point (x,z) and origin (0,0)
  fVar1 = atan2(z,x);
  *outAngle = (float)fVar1;
  return true;
}




void Math::MovePointForwards(vec3 *v,float angle1,float angle2,float cameraPos)

{
  float10 s1;
  float10 c1;
  float10 s2;
  float10 c2;
  
  sin(angle1);
  c1 = (float10)cos(angle1);
  sin(angle2);
  c2 = (float10)cos(angle2);
  v->y = v->y - (float)s1 * cameraPos;
  v->x = (float)c1 * cameraPos * (float)s2 + v->x;
  v->z = (float)c1 * cameraPos * (float)c2 + v->z;
  return;
}




void FUN_00106770(float param_1,float angle1,float angle2,vec3 *param_4,vec3 *outV3)

{
  float10 sx;
  float10 cx;
  float10 extraout_ST0;
  float10 extraout_ST0_00;
  float ax;
  float ay;
  float az;
  
  ax = param_4->x;
  ay = param_4->y;
  az = param_4->z;
  sin(ax);
  cx = (float10)cos(ax);
  ax = (float)sx * angle1 + (float)cx * angle2;
  outV3->y = (float)cx * angle1 - (float)sx * angle2;
  sin(ay);
  cx = (float10)cos(ay);
  outV3->x = ax * (float)extraout_ST0 + (float)cx * param_1;
  outV3->z = ax * (float)cx - (float)extraout_ST0 * param_1;
  sin(az);
  cx = (float10)cos(az);
  az = outV3->x;
  outV3->x = outV3->x * (float)cx - outV3->y * (float)extraout_ST0_00;
  outV3->y = (float)cx * outV3->y + (float)extraout_ST0_00 * az;
  return;
}




int FUN_001068e0(float *param_1,float *param_2,vec3 *param_3,float param_4)

{
  int iVar1;
  bool bVar2;
  bool bVar3;
  float10 fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  float local_c;
  float local_8 [2];
  
  *param_2 = 0.0;
  *param_1 = 0.0;
  iVar1 = FUN_00105e20(param_3,&local_c,local_8);
  if (iVar1 == 0) {
    return 0;
  }
  local_c = modf(local_c - param_4,6.2831855);
  if (local_c < -3.1415927) {
    local_c = local_c + 6.2831855;
  }
  if (3.1415927 <= local_c) {
    local_c = local_c - 6.2831855;
  }
  fVar4 = abs_float(local_c);
  fVar5 = (float)fVar4;
  local_8[0] = local_8[0] + 1.5707964;
  fVar8 = 0.0 - local_8[0];
  fVar6 = (fVar8 - local_8[0]) * fVar5 * 0.31830987 + local_8[0];
  fVar7 = fVar8;
  if (fVar8 <= local_8[0]) {
    if (fVar8 <= fVar6) {
      bVar2 = fVar6 < local_8[0];
      goto LAB_001069d6;
    }
  }
  else if (fVar6 <= fVar8) {
    bVar2 = local_8[0] < fVar6;
LAB_001069d6:
    fVar7 = fVar6;
    if (!bVar2 && local_8[0] != fVar6) {
      fVar7 = local_8[0];
    }
  }
  *param_1 = fVar7;
  if (1.5707964 <= fVar5) {
    fVar5 = (fVar5 - 1.5707964) * 0.63661975 * fVar8 + local_8[0];
    if (0.0 <= local_8[0]) {
      if (fVar5 < 0.0) {
        local_8[0] = 0.0;
        goto LAB_00106a4d;
      }
      bVar2 = fVar5 == local_8[0];
      bVar3 = fVar5 < local_8[0];
      goto LAB_00106a48;
    }
    if (0.0 < fVar5) {
      local_8[0] = 0.0;
      goto LAB_00106a4d;
    }
    if (fVar5 < local_8[0]) goto LAB_00106a4d;
  }
  else {
    fVar5 = fVar5 * 0.63661975 * local_8[0];
    if (local_8[0] <= 0.0) {
      if (fVar5 < local_8[0]) goto LAB_00106a4d;
      bVar2 = fVar5 == 0.0;
      bVar3 = fVar5 < 0.0;
      local_8[0] = 0.0;
LAB_00106a48:
      if (!bVar3 && !bVar2) goto LAB_00106a4d;
    }
    else {
      if (local_8[0] < fVar5) goto LAB_00106a4d;
      if (fVar5 < 0.0) {
        local_8[0] = 0.0;
        goto LAB_00106a4d;
      }
    }
  }
  local_8[0] = fVar5;
LAB_00106a4d:
  *param_2 = local_8[0];
  if (local_c <= 0.0) {
    return iVar1;
  }
  *param_2 = 0.0 - *param_2;
  return iVar1;
}




void __fastcall FUN_00106b90(vec3 *param_1,vec3 *param_2,undefined1 param_3)

{
  if (((param_1->x == 0.0) && (param_1->y == 0.0)) && (param_1->z == 0.0)) {
    switch(param_3) {
    case 0x58:
    case 0x78:
      param_2->x = 1.0;
      param_2->y = 0.0;
      param_2->z = 0.0;
      return;
    case 0x59:
    case 0x79:
      param_2->x = 0.0;
      param_2->y = 1.0;
      param_2->z = 0.0;
      return;
    case 0x5a:
    case 0x7a:
      param_2->x = 0.0;
      param_2->y = 0.0;
      param_2->z = 1.0;
      return;
    default:
      param_2->z = 0.0;
      param_2->y = 0.0;
      param_2->x = 0.0;
      return;
    }
  }
  D3DX8::D3DXVec3Normalize(param_2,param_1);
  return;
}




float10 FUN_001077d0(void)

{
  uint uVar1;
  LARGE_INTEGER local_8;
  
  XAPILIB::QueryPerformanceCounter(&local_8);
  uVar1 = (local_8.s.HighPart - DAT_0050e0dc) - (uint)(local_8.s.LowPart < g_PERFORMANCE_COUNTER);
  return (-(float10)(longlong)(((ulonglong)uVar1 & 0x80000000) << 0x20) +
         (float10)(CONCAT44(uVar1,local_8.s.LowPart - g_PERFORMANCE_COUNTER) & 0x7fffffffffffffff))
         / (float10)_g_PERFORMANCE_FREQUENCY;
}




undefined4 FUN_0010beb0(vec3 *param_1)

{
  vec3 *in_EAX;
  float *unaff_ESI;
  float fVar1;
  float fVar2;
  float fVar3;
  vec3 local_18;
  vec3 local_c;
  
  unaff_ESI[0xe] = 0.0;
  unaff_ESI[0xd] = 0.0;
  unaff_ESI[0xc] = 0.0;
  unaff_ESI[0xb] = 0.0;
  unaff_ESI[9] = 0.0;
  unaff_ESI[8] = 0.0;
  unaff_ESI[7] = 0.0;
  unaff_ESI[6] = 0.0;
  unaff_ESI[4] = 0.0;
  unaff_ESI[3] = 0.0;
  unaff_ESI[2] = 0.0;
  unaff_ESI[1] = 0.0;
  unaff_ESI[0xf] = 1.0;
  unaff_ESI[10] = 1.0;
  unaff_ESI[5] = 1.0;
  *unaff_ESI = 1.0;
  D3DX8::D3DXVec3Normalize(&local_c,in_EAX);
  D3DX8::D3DXVec3Normalize(&local_18,param_1);
  fVar1 = local_c.y * local_18.z - local_18.y * local_c.z;
  fVar2 = local_c.z * local_18.x - local_c.x * local_18.z;
  fVar3 = local_18.y * local_c.x - local_18.x * local_c.y;
  if (fVar3 * fVar3 + fVar2 * fVar2 + fVar1 * fVar1 <= 1e-05) {
    if (local_c.x * local_18.x + local_18.y * local_c.y + local_c.z * local_18.z < 0.0) {
      return 0;
    }
  }
  else {
    FUN_00153a00();
  }
  return 1;
}



undefined4
FUN_0010c100(vec3 *param_1,undefined1 *param_2,undefined4 *param_3,float *param_4,int param_5,
            int param_6,undefined4 *param_7)

{
  vec3 *p2;
  undefined1 *in_EAX;
  undefined4 *puVar1;
  int iVar2;
  vec3 *unaff_EBX;
  float local_24;
  undefined4 *local_20;
  int local_1c;
  vec3 local_18;
  vec3 local_c;
  
  *in_EAX = 0;
  *param_7 = 0;
  local_1c = 0;
  if (0 < param_6) {
    puVar1 = (undefined4 *)(param_5 + 0x14);
    do {
      local_18.x = param_1->x - unaff_EBX->x;
      p2 = (vec3 *)puVar1[-4];
      local_18.y = param_1->y - unaff_EBX->y;
      local_18.z = param_1->z - unaff_EBX->z;
      local_c.x = unaff_EBX->x - param_1->x;
      local_c.y = unaff_EBX->y - param_1->y;
      local_20 = puVar1 + -5;
      local_c.z = unaff_EBX->z - param_1->z;
      iVar2 = FUN_00103400(&local_18,(vec3 *)puVar1[-3],(vec3 *)*local_20,&local_24,p2,unaff_EBX);
      if (iVar2 != 0) {
        *param_4 = local_18.x * local_24;
        param_4[1] = local_18.y * local_24;
        param_4[2] = local_18.z * local_24;
        *param_4 = local_18.x * local_24 + unaff_EBX->x;
        param_4[1] = unaff_EBX->y + local_18.y * local_24;
        param_4[2] = unaff_EBX->z + local_18.z * local_24;
        *param_3 = puVar1[-2];
        param_3[1] = puVar1[-1];
        param_3[2] = *puVar1;
        *param_2 = 0;
        *param_7 = local_20;
        return 1;
      }
      iVar2 = FUN_00103400(&local_c,(vec3 *)puVar1[-3],(vec3 *)*local_20,&local_24,p2,param_1);
      if (iVar2 != 0) {
        *param_4 = local_c.x * local_24;
        param_4[1] = local_c.y * local_24;
        param_4[2] = local_c.z * local_24;
        *param_4 = local_c.x * local_24 + param_1->x;
        param_4[1] = param_1->y + local_c.y * local_24;
        param_4[2] = local_c.z * local_24 + param_1->z;
        *param_3 = puVar1[-2];
        param_3[1] = puVar1[-1];
        param_3[2] = *puVar1;
        *param_2 = 1;
        *param_7 = local_20;
        return 1;
      }
      local_1c = local_1c + 1;
      puVar1 = puVar1 + 10;
    } while (local_1c < param_6);
  }
  return 0;
}




int FUN_00110bf0(vec3 *param_1,int param_2,int param_3)

{
  BackgroundCollisionThing *pBVar1;
  int iVar2;
  int index;
  int iVar3;
  float fVar4;
  
  pBVar1 = BackgroundCollisionThings[4];
  iVar3 = 0;
  index = 0;
  if (0 < (int)BackgroundCollisionThings[4]) {
    fVar4 = 2.0;
    do {
      if (index == param_2) {
        if (param_3 != 0) {
          iVar2 = Background::isCollisionThings(index,param_1);
          if (iVar2 == -1) {
            return index;
          }
          if ((*(byte *)(BackgroundCollisionThings[index]->field10_0x10 + 7 + iVar2 * 0x12) & 2) ==
              0) {
            return index;
          }
        }
        if (((float)BackgroundCollisionThings[index + 5] <= param_1->y) &&
           (param_1->y <= (float)BackgroundCollisionThings[index + 7] + fVar4)) {
          return index;
        }
      }
      if ((float)BackgroundCollisionThings[index + 5] <= param_1->y &&
          param_1->y != (float)BackgroundCollisionThings[index + 5]) {
        iVar3 = index;
      }
      index = index + 1;
    } while (index < (int)pBVar1);
  }
  return iVar3;
}



BOOL checkAStarLayerChanged
               (int param_1,void *this,undefined4 param_3,int *param_4,undefined4 param_5,
               astruct_32 *param_6)

{
  int iVar1;
  uint uVar2;
  
  iVar1 = FUN_00110bf0(param_3,(int)this,param_1);
  uVar2 = (uint)(iVar1 != *param_4);
  if (uVar2 == 0) {
    *param_4 = iVar1;
    return 0;
  }
  FUN_001108b0();
  if (param_6 != (astruct_32 *)0x0) {
    XSoundbankResource::UpdateOffsets(0,BackgroundCollisionThings[iVar1],param_6);
    *param_4 = iVar1;
    return uVar2;
  }
  *param_4 = iVar1;
  return uVar2;
}




BOOL FUN_00110f50(int param_1,vec3 *param_2)

{
  int iVar1;
  bool bVar2;
  int iVar3;
  ushort *ptr;
  int iVar4;
  void *pvVar5;
  BOOL BVar6;
  float fVar7;
  float fVar8;
  void *local_44;
  void *local_40;
  float local_38;
  
  if (*(short *)(param_1 + 8) == 0) {
    iVar3 = FUN_00110bf0(param_1 + 0x20,-1,0);
    BVar6 = SpawnThingFromMarker
                      (param_2,0,param_1 + 0x20,iVar3,0,*(float *)(param_1 + 0x2c),0,0,0,0);
    return BVar6;
  }
  if (*(short *)(param_1 + 8) == 1) {
    bVar2 = *(float *)(param_1 + 0x34) != 0.0;
    if (bVar2) {
      FUN_00106880(*(undefined4 *)(param_1 + 0x34));
      FUN_00106880(*(undefined4 *)(param_1 + 0x34));
      FUN_00106880(*(undefined4 *)(param_1 + 0x34));
      FUN_00106880(*(undefined4 *)(param_1 + 0x34));
    }
    iVar3 = FUN_00110bf0(param_1 + 0x20,-1,0);
    ptr = (ushort *)FUN_0010fbe0();
    if (ptr != (ushort *)0x0) {
      if (bVar2) {
        local_44 = *(void **)(ptr + 2);
        local_40 = *(void **)(ptr + 4);
        if (BackgroundCollisionThings[0] == (BackgroundCollisionThing *)0x0) {
          fVar7 = 0.0;
        }
        else {
          fVar7 = (float)(int)BackgroundCollisionThings[0]->someF * 0.5;
        }
        if (local_44 < local_40) {
          do {
            iVar4 = FUN_001244d0();
            if ((iVar4 != 0) || (local_38 <= fVar7 * 0.75)) {
              local_44 = (void *)((int)local_44 + 0xc);
            }
            else {
              pvVar5 = (void *)(*(int *)(ptr + 4) - (uint)*ptr);
              if (local_44 < pvVar5) {
                _memmove(local_44,(void *)((uint)*ptr + (int)local_44),(int)pvVar5 - (int)local_44);
              }
              local_40 = (void *)((int)local_40 - 0xc);
              *(uint *)(ptr + 4) = *(int *)(ptr + 4) - (uint)*ptr;
            }
          } while (local_44 < local_40);
        }
      }
      iVar4 = (*(int *)(ptr + 4) - *(int *)(ptr + 2)) / (int)(uint)*ptr;
      if (iVar4 != 0) {
        runtime::rand = runtime::rand * 0x19660d + 0x3c6ef35f;
        iVar1 = *(int *)(*(int *)(ptr + 2) +
                        (int)(((float)(runtime::rand & 0x7fffff | 0x3f800000) - 1.0) * (float)iVar4)
                        * 0xc);
        iVar4 = BackgroundCollisionThings[iVar3]->field10_0x10 + iVar1 * 0x12;
        param_2->x = (float)(int)*(short *)(BackgroundCollisionThings[iVar3]->field10_0x10 +
                                           iVar1 * 0x12);
        param_2->y = (float)(int)*(short *)(iVar4 + 2);
        param_2->z = (float)(int)*(short *)(iVar4 + 4);
        free(ptr);
        if (BackgroundCollisionThings[0] == (BackgroundCollisionThing *)0x0) {
          fVar7 = 0.0;
        }
        else {
          fVar7 = (float)(int)BackgroundCollisionThings[0]->someF * 0.5;
        }
        runtime::rand = runtime::rand * 0x19660d + 0x3c6ef35f;
        fVar8 = 0.0 - fVar7;
        param_2->x = (fVar7 - fVar8) * ((float)(runtime::rand & 0x7fffff | 0x3f800000) - 1.0) +
                     fVar8 + param_2->x;
        runtime::rand = runtime::rand * 0x19660d + 0x3c6ef35f;
        param_2->z = (fVar7 - fVar8) * ((float)(runtime::rand & 0x7fffff | 0x3f800000) - 1.0) +
                     fVar8 + param_2->z;
        BVar6 = FUN_00111b40();
        return BVar6;
      }
      free(ptr);
    }
  }
  return 0;
}



BOOL SpawnThingFromMarker
               (vec3 *outV,undefined4 param_2,vec3 *param_3,int param_4,undefined4 param_5,
               float param_6,undefined4 param_7,undefined4 param_8,undefined4 param_9,BOOL canFail)

{
  uint uVar1;
  undefined4 uVar2;
  Buffer<Idk0xc> *somethingInstance;
  int iVar3;
  HeapTableEntry *pHVar4;
  float fVar5;
  float fVar6;
  
  somethingInstance =
       FUN_0010f7f0(param_2,param_3,param_5,param_6,param_7,param_8,(byte)canFail | 1,param_9,
                    param_4);
  if (somethingInstance == (Buffer<Idk0xc> *)0x0) {
    if ((canFail & 1U) != 0) {
      return 0;
    }
    somethingInstance =
         FUN_0010f7f0(param_2,param_3,param_5,param_6,param_7,param_8,(byte)canFail,param_9,param_4)
    ;
    if (somethingInstance == (Buffer<Idk0xc> *)0x0) {
      return 0;
    }
  }
  runtime::rand = runtime::rand * 0x19660d + 0x3c6ef35f;
  uVar1 = somethingInstance->head
          [(int)(((float)(runtime::rand & 0x7fffff | 0x3f800000) - 1.0) *
                (float)(((int)somethingInstance->tail - (int)somethingInstance->head) /
                       (int)(uint)somethingInstance->valueSize))].field0_0x0;
  iVar3 = BackgroundCollisionThings[param_4]->field10_0x10 + uVar1 * 0x12;
  outV->x = (float)(int)*(short *)(BackgroundCollisionThings[param_4]->field10_0x10 + uVar1 * 0x12);
  outV->y = (float)(int)*(short *)(iVar3 + 2);
  outV->z = (float)(int)*(short *)(iVar3 + 4);
  iVar3 = FindHeapOf(somethingInstance);
  uVar2 = runtime::CurrentHeapToAllocateFrom;
  if (g_HeapTableBase[iVar3].heapHandle == (HANDLE)0x0) {
    pHVar4 = (HeapTableEntry *)0x0;
  }
  else {
    pHVar4 = g_HeapTableBase + iVar3;
  }
  runtime::CurrentHeapToAllocateFrom = iVar3;
  XAPILIB::HeapFree(pHVar4->heapHandle,0,somethingInstance);
  if (BackgroundCollisionThings[0] == (BackgroundCollisionThing *)0x0) {
    fVar5 = 0.0;
  }
  else {
    fVar5 = (float)(int)BackgroundCollisionThings[0]->someF * 0.5;
  }
  fVar5 = fVar5 * (float)0x3f733333;
  runtime::rand = runtime::rand * 0x19660d + 0x3c6ef35f;
  fVar6 = 0.0 - fVar5;
  runtime::CurrentHeapToAllocateFrom = uVar2;
  outV->x = (fVar5 - fVar6) * ((float)(runtime::rand & 0x7fffff | 0x3f800000) - 1.0) + outV->x +
            fVar6;
  runtime::rand = runtime::rand * 0x19660d + 0x3c6ef35f;
  outV->z = (fVar5 - fVar6) * ((float)(runtime::rand & 0x7fffff | 0x3f800000) - 1.0) + outV->z +
            fVar6;
  iVar3 = Background::isCollisionThings(param_4,outV);
  if (iVar3 == -1) {
    return 0;
  }
  outV->y = (float)(int)*(short *)(BackgroundCollisionThings[param_4]->field10_0x10 + 2 +
                                  iVar3 * 0x12);
  return 1;
}




obj * __thiscall FUN_00112c50(vec3 *param_1,undefined4 param_2)

{
  char *in_EAX;
  objParams *params;
  obj *poVar1;
  AffineTransform **unaff_EBX;
  
  params = Assets::GetObjParams(in_EAX);
  if (params == (objParams *)0x0) {
    return (obj *)0x0;
  }
  if (param_1 == (vec3 *)0x0) {
    param_1 = &Game::someGlobalPos;
  }
  *(float *)(params + 1) = param_1->x;
  *(float *)&params[1].typeIndex = param_1->y;
  *(float *)(params + 2) = param_1->z;
  if (unaff_EBX == (AffineTransform **)0x0) {
    unaff_EBX = &PTR_0050dd74;
  }
  *(AffineTransform **)&params[2].typeIndex = *unaff_EBX;
  *(AffineTransform **)(params + 3) = unaff_EBX[1];
  *(AffineTransform **)&params[3].typeIndex = unaff_EBX[2];
  params[4].paramsSize = (undefined2)param_2;
  params[4].objInitValue = param_2._2_2_;
  poVar1 = Assets::CreateEntityFromParams(params);
  free(params);
  return poVar1;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


int GetReaperSomethingsIndex(void)

{
  int iVar1;
  
  iVar1 = ReaperSomethingsIndex;
  while( true ) {
    if (0x1f < iVar1) {
      ReaperSomethingsIndex = 0xffffffff;
      return iVar1;
    }
    if (GrimReaperFloatsArray[iVar1].active == 0) break;
    iVar1 = iVar1 + 1;
  }
  ReaperSomethingsIndex = iVar1;
  return iVar1;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


int CreateReaperSomethingsIndex(vec3 *this,float param_2,float param_3)

{
  float fVar1;
  int index;
  
  index = ReaperSomethingsIndex;
  if (((DAT_0050ef18 != 0) && (NumReaperSomethings < 0x20)) && (-1 < ReaperSomethingsIndex)) {
    GrimReaperFloatsArray[ReaperSomethingsIndex].pos.x = this->x;
    GrimReaperFloatsArray[index].pos.y = this->y;
    fVar1 = this->z;
    GrimReaperFloatsArray[index].field1_0xc = param_3;
    GrimReaperFloatsArray[index].pos.z = fVar1;
    GrimReaperFloatsArray[index].field2_0x10 = param_2;
    GrimReaperFloatsArray[index].active = 1;
    GetReaperSomethingsIndex();
    NumReaperSomethings = NumReaperSomethings + 1;
    return index;
  }
  return -1;
}




void FUN_00120250(float a,vec3 *param_2)

{
  float10 fVar1;
  float fVar2;
  
  fVar2 = param_2->x * param_2->x + param_2->y * param_2->y + param_2->z * param_2->z;
  if (fVar2 != 0.0) {
    fVar1 = (float10)invsqrt(fVar2);
    fVar1 = fVar1 * (float10)a;
    param_2->x = (float)(fVar1 * (float10)param_2->x);
    param_2->y = (float)(fVar1 * (float10)param_2->y);
    param_2->z = (float)(fVar1 * (float10)param_2->z);
  }
  return;
}




void FUN_00120ba0(undefined4 param_1,undefined4 param_2,vec3 *param_3)

{
  undefined4 *in_EAX;
  int iVar1;
  float *unaff_ESI;
  float *unaff_EDI;
  float local_34;
  float local_30;
  float local_2c;
  float local_28;
  float local_24;
  float local_20;
  float local_1c;
  vec3 local_18;
  undefined4 local_c;
  undefined4 local_8;
  undefined4 local_4;
  
  local_30 = *unaff_ESI;
  local_28 = unaff_ESI[2];
  local_c = *in_EAX;
  local_4 = in_EAX[2];
  local_8 = 0;
  local_2c = 0.0;
  D3DX8::D3DXVec3Normalize(&local_18,param_3);
  local_30 = local_18.x * 50.0 + local_30;
  local_2c = local_18.y * 50.0 + local_2c;
  local_28 = local_18.z * 50.0 + local_28;
  local_24 = local_18.x * -50.0;
  local_20 = local_18.y * -50.0;
  local_1c = local_18.z * -50.0;
  iVar1 = FUN_0015ab50(&local_30,param_1,&local_24,&local_c,param_2,&Game::someGlobalPos,0x3f800000,
                       &local_34);
  if ((iVar1 != 0) && (0.0 < local_34)) {
    *unaff_EDI = (local_24 * local_34 + local_30) - *unaff_ESI;
    unaff_EDI[1] = (local_20 * local_34 + local_2c) - unaff_ESI[1];
    unaff_EDI[2] = (local_1c * local_34 + local_28) - unaff_ESI[2];
    unaff_EDI[1] = 0.0;
    return;
  }
  unaff_EDI[2] = 0.0;
  *unaff_EDI = 0.0;
  unaff_EDI[1] = 0.0;
  return;
}




void ScareActorsWithinScareRadius(float scareRadius,Message *param_2,vec3 *point)

{
  actor_conflict5 *av;
  actor_0x934_conflict5 pNVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  vec3 local_c;
  
  pNVar1 = Game::SceneInfo.actors_0x934.head;
  while (pNVar1 != (actor_0x934_conflict5)0x0) {
    av = ADJ(pNVar1);
    pNVar1 = pNVar1->next;
    avatar::getWorldPosition((avatar *)av,&local_c);
    fVar4 = local_c.z - point->z;
    fVar2 = local_c.x - point->x;
    fVar3 = local_c.y - point->y;
    if (fVar4 * fVar4 + fVar2 * fVar2 + fVar3 * fVar3 < scareRadius * scareRadius) {
      (*((av->avatar).object.vtable)->onMessage)(av,param_2);
    }
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


avatar * FUN_00129d70(vec3 *param_1,undefined4 param_2,float *param_3,undefined4 param_4)

{
  int *piVar1;
  avatar *av;
  int iVar2;
  int iVar3;
  avatar *paVar4;
  float10 fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  avatar *local_18;
  float local_14;
  vec3 local_c;
  
  paVar4 = (avatar *)0x0;
  local_18 = (avatar *)0x0;
  local_14 = 3.4028235e+38;
  iVar3 = Game::SceneInfo.sceneTree_;
  if (Game::SceneInfo.sceneTree_ == 0) {
    return (avatar *)0x0;
  }
  do {
    av = (avatar *)(iVar3 + -0x934);
    iVar2 = FUN_00129c50(param_4);
    if ((((iVar2 != 0) &&
         (avatar::getWorldPosition(av,&local_c), fVar6 = param_1->y - local_c.y, paVar4 = local_18,
         fVar6 * fVar6 <= 625.0)) &&
        (fVar6 = param_1->x - local_c.x, fVar7 = param_1->y - local_c.y,
        fVar8 = param_1->z - local_c.z, fVar6 = fVar6 * fVar6 + fVar8 * fVar8 + fVar7 * fVar7,
        fVar6 < local_14)) && (iVar2 = FUN_00129cd0(param_4), iVar2 != 0)) {
      paVar4 = av;
      local_18 = av;
      local_14 = fVar6;
    }
    piVar1 = (int *)(iVar3 + 4);
    iVar3 = *piVar1;
  } while (*piVar1 != 0);
  if ((paVar4 != (avatar *)0x0) && (param_3 != (float *)0x0)) {
    fVar5 = scaled_invsqrt(local_14);
    *param_3 = (float)fVar5;
  }
  return paVar4;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void FUN_0012ef60(float *param_1,vec3 *param_2)

{
  float10 extraout_ST0;
  float fVar1;
  
  if (param_1[0xc] == 0.0) {
    param_1[0xb] = param_2->x;
  }
  else {
    sin((param_1[0xc] / param_2->z) * 3.1415927 - 1.5707964);
    param_1[0xb] = (float)((float10)param_2->y * (float10)param_2->x *
                           (extraout_ST0 + (float10)1.0) * (float10)0.5 + (float10)param_2->x);
    if (runtime::dx_timer <= 0.0) {
      fVar1 = runtime::DeltaTime * runtime::TimeScale;
    }
    else {
      fVar1 = 0.0;
    }
    if ((0.0 < param_1[0xc]) && (fVar1 = param_1[0xc] - fVar1, param_1[0xc] = fVar1, fVar1 <= 0.0))
    {
      param_1[0xc] = 0.0;
      return;
    }
  }
  return;
}




FUN_00135b60(avatar *param_1,undefined4 param_2,undefined4 param_3,float param_4,vec3 *param_5)

{
  ushort markerId;
  uint uVar1;
  int iVar2;
  BOOL BVar3;
  undefined4 uVar4;
  Marker *pMVar5;
  Marker *pMVar6;
  int iVar7;
  float10 fVar8;
  float fVar9;
  float fVar10;
  float fVar11;
  float fVar12;
  float fVar13;
  float fVar14;
  float fVar15;
  int local_34;
  Marker *local_30;
  int local_2c;
  vec3 local_24;
  float local_18;
  float local_14;
  float local_10;
  float local_c;
  float local_8;
  float local_4;
  
  fVar15 = param_1[1].rotQuat.y;
  if ((fVar15 == 0.0) || (iVar7 = *(int *)((int)fVar15 + 0x10), iVar7 == 0)) {
    return 0;
  }
  avatar::getWorldPosition(param_1,&local_24);
  local_2c = Marker::getCountOfMarkerType(0x1b);
  pMVar6 = (Marker *)0x0;
  if (local_2c == 0) goto LAB_00135ec2;
  local_14 = *(float *)(iVar7 + 0x24) - local_24.y;
  fVar15 = *(float *)(iVar7 + 0x28) - local_24.z;
  local_18 = *(float *)(iVar7 + 0x20) - local_24.x;
  fVar9 = local_14 * local_14 + fVar15 * fVar15 + local_18 * local_18;
  local_30 = (Marker *)0x0;
  if (fVar9 != 0.0) {
    local_10 = fVar15;
    fVar8 = (float10)invsqrt(fVar9);
    local_18 = (float)((float10)local_18 * fVar8);
    local_14 = (float)((float10)local_14 * fVar8);
    fVar15 = (float)((float10)local_10 * fVar8);
  }
  local_34 = 0;
  local_10 = fVar15;
  markerId = Marker::nextIdOfNextMarkerOfType(0x1b,1,0);
  if (local_2c < 1) {
LAB_00135e98:
    pMVar6 = local_30;
  }
  else {
    do {
      pMVar5 = (Game::GameState.markerInstance)->marker;
      uVar1 = 0;
      if ((Game::GameState.markerInstance)->numMarkers != 0) {
        do {
          if (pMVar5->id == markerId) goto LAB_00135c90;
          pMVar5 = (Marker *)((int)&pMVar5->size + pMVar5->size);
          uVar1 = uVar1 + 1;
        } while (uVar1 < (Game::GameState.markerInstance)->numMarkers);
      }
      pMVar5 = (Marker *)0x0;
LAB_00135c90:
      if ((local_30 == (Marker *)0x0) ||
         (fVar11 = (pMVar5->pos).z - *(float *)(iVar7 + 0x28),
         fVar10 = (pMVar5->pos).y - *(float *)(iVar7 + 0x24),
         fVar9 = (pMVar5->pos).x - *(float *)(iVar7 + 0x20),
         fVar13 = (local_30->pos).y - *(float *)(iVar7 + 0x24),
         fVar14 = (local_30->pos).z - *(float *)(iVar7 + 0x28),
         fVar12 = (local_30->pos).x - *(float *)(iVar7 + 0x20),
         fVar14 * fVar14 + fVar13 * fVar13 + fVar12 * fVar12 <
         fVar11 * fVar11 + fVar10 * fVar10 + fVar9 * fVar9)) {
        local_30 = pMVar5;
      }
      local_8 = (pMVar5->pos).y - local_24.y;
      local_4 = (pMVar5->pos).z - local_24.z;
      local_c = (pMVar5->pos).x - local_24.x;
      fVar9 = local_4 * local_4 + local_8 * local_8 + local_c * local_c;
      if (fVar9 != 0.0) {
        fVar8 = (float10)invsqrt(fVar9);
        local_c = (float)((float10)local_c * fVar8);
        local_8 = (float)((float10)local_8 * fVar8);
        local_4 = (float)((float10)local_4 * fVar8);
        fVar15 = local_10;
      }
      if ((local_8 * local_14 + local_4 * fVar15 + local_c * local_18 < 0.0) &&
         ((local_34 = local_34 + 1, pMVar6 == (Marker *)0x0 ||
          (fVar11 = (pMVar5->pos).z - *(float *)(iVar7 + 0x28),
          fVar10 = (pMVar5->pos).y - *(float *)(iVar7 + 0x24),
          fVar9 = (pMVar5->pos).x - *(float *)(iVar7 + 0x20),
          fVar13 = (pMVar6->pos).y - *(float *)(iVar7 + 0x24),
          fVar14 = (pMVar6->pos).z - *(float *)(iVar7 + 0x28),
          fVar12 = (pMVar6->pos).x - *(float *)(iVar7 + 0x20),
          fVar14 * fVar14 + fVar13 * fVar13 + fVar12 * fVar12 <
          fVar11 * fVar11 + fVar10 * fVar10 + fVar9 * fVar9)))) {
        pMVar6 = pMVar5;
      }
      markerId = Marker::nextIdOfNextMarkerOfType(0x1b,0,markerId);
      local_2c = local_2c + -1;
    } while (local_2c != 0);
    if ((pMVar6 == (Marker *)0x0) || (local_34 == 1)) goto LAB_00135e98;
  }
  if (pMVar6 != (Marker *)0x0) {
    param_5->x = (pMVar6->pos).x;
    param_5->y = (pMVar6->pos).y;
    param_5->z = (pMVar6->pos).z;
    return 1;
  }
LAB_00135ec2:
  iVar7 = *(int *)(param_1[1].model0x9s[0].audioID + 0x74);
  iVar2 = Background::isCollisionThings(iVar7,&local_24);
  if ((iVar2 == -1) ||
     ((*(ushort *)(BackgroundCollisionThings[iVar7]->field10_0x10 + 6 + iVar2 * 0x12) >> 0xb & 1) !=
      0)) {
    iVar7 = 0;
    do {
      BVar3 = SpawnThingFromMarker
                        (param_5,0,&local_24,*(int *)(param_1[1].model0x9s[0].audioID + 0x74),0,
                         (float)iVar7 * param_4 * 0.5 + param_4,0,
                         *(undefined4 *)(param_1[1].model0x9s[0].audioID + 0x2c),(uint)param_1->tag,
                         0xe);
      if (BVar3 != 0) {
        return 1;
      }
      iVar7 = iVar7 + 1;
    } while (iVar7 < 5);
    local_24.x = *(float *)(param_1[1].model0x9s[0].audioID + 0x48);
    local_24.y = *(float *)(param_1[1].model0x9s[0].audioID + 0x4c);
    local_24.z = *(float *)(param_1[1].model0x9s[0].audioID + 0x50);
    BVar3 = SpawnThingFromMarker
                      (param_5,0,&local_24,*(int *)(param_1[1].model0x9s[0].audioID + 0x74),0,
                       param_4,0,*(undefined4 *)(param_1[1].model0x9s[0].audioID + 0x2c),
                       (uint)param_1->tag,0xe);
    uVar4 = 0;
    if (BVar3 != 0) {
      return 1;
    }
  }
  else {
    uVar4 = FUN_0013aa50(param_2,iVar7,0x3e851eb8,0xc,param_3,param_4 + 0.5,0,
                         *(undefined4 *)(param_1[1].model0x9s[0].audioID + 0x2c),param_5,1,0xe,
                         param_1->tag);
  }
  return uVar4;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


undefined4 FUN_001373f0(actorMind *param_1,vec3 *param_2)

{
  actorBody *body;
  int iVar1;
  int local_c;
  float local_8;
  undefined1 local_4 [4];
  
  body = param_1->actor->body;
  iVar1 = Background::isCollisionThings(param_1->actor->backgroundCollisionIndex,param_2);
  if (iVar1 != -1) {
    iVar1 = FUN_00137460(body,local_4,&local_c,&local_8);
    if (iVar1 == 0) {
      return 0;
    }
    if ((local_c == 0) && (iVar1 = FUN_00137790(body), iVar1 == 0)) {
      return 0;
    }
  }
  return 1;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void FUN_00138220(int param_1,float param_2,vec3 *param_3)

{
  float fVar1;
  float fVar2;
  avatar *paVar3;
  char cVar4;
  avatar *in_EAX;
  float10 fVar5;
  float fVar6;
  float fVar7;
  vec3 local_c;
  
  fVar2 = in_EAX[1].rotQuat.z;
  avatar::getWorldPosition(in_EAX,&local_c);
  fVar7 = *(float *)(*(int *)((int)fVar2 + 8) + 0x38);
  paVar3 = *(avatar **)((int)fVar2 + 0x48);
  fVar1 = *(float *)((int)fVar2 + 0x78);
  if (paVar3 == (avatar *)0x0) {
    cVar4 = '\0';
  }
  else {
    cVar4 = *(char *)((int)&paVar3[1].pos.x + 1);
  }
  if (((cVar4 == '\x01') && (paVar3->model != (Model *)0x0)) &&
     (paVar3->model->descriptor != (ModelDescriptor *)0x0)) {
    fVar5 = FUN_0003d9a0(paVar3);
    fVar6 = (float)fVar5;
  }
  else {
    fVar6 = 0.0;
  }
  fVar7 = *(float *)(*(int *)(*(int *)(param_1 + 0x95c) + 8) + 0x38) *
          *(float *)(*(int *)(param_1 + 0x95c) + 0x888) +
          *(float *)((int)fVar2 + 0x888) * fVar7 + fVar6 + fVar1 * fVar7;
  SpawnThingFromMarker(param_3,0,&local_c,*(int *)(param_1 + 0xcec),fVar7,fVar7 + param_2,0,0,0,0);
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void __thiscall FUN_0013ad60(void *this,undefined4 param_2,vec3 *param_3)

{
  someFxPos.x = param_3->x;
  someFxPos.y = param_3->y;
  someFxPos.z = param_3->z;
  DAT_004e1c5c = 1;
  if ((undefined4 *)((int)this + 0x8c) == (undefined4 *)0x0) {
    return;
  }
  actor::executeCalloutInDescriptor
            (*(CalloutDescriptor **)((int)this + 0x8c),(avatarCalloutId)param_2,
             (CalloutCallback *)0x0,0x4e1c5c,this,(entityBodyPlayer_0x924)0x0);
  return;
}



// WARNING: Globals starting with '_' overlap smaller symbols at the same address
// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void __thiscall FUN_0013d110(vec3 *param_1,int param_2,float param_3)

{
  int iVar1;
  int in_EAX;
  int iVar2;
  int iVar3;
  float fVar4;
  float fVar5;
  
  iVar3 = *(int *)(in_EAX + 0xcec);
  iVar2 = Background::isCollisionThings(iVar3,param_1);
  if (iVar2 != -1) {
    iVar1 = BackgroundCollisionThings[iVar3]->field10_0x10;
    fVar5 = (float)(int)*(short *)(iVar1 + 2 + iVar2 * 0x12);
    iVar3 = Background::isCollisionThings(iVar3,param_1);
    if ((iVar3 == -1) ||
       (fVar4 = (float)(int)*(short *)(iVar1 + 0xe + iVar3 * 0x12), fVar4 < *(float *)(param_2 + 4))
       ) {
      fVar4 = fVar5 - 1.0;
    }
    if ((fVar5 < fVar4) && (fVar4 - fVar5 < param_3 * 2.0)) {
      return;
    }
  }
  return;
}




void FUN_0013d250(vec3 *param_1,vec3 *param_2)

{
  avatar_0x900_conflict6 *ppEVar1;
  avatar_conflict13 *av;
  ObjectFullVTable *pOVar2;
  avatar_0x900_conflict6 pEVar3;
  undefined4 local_4;
  
  pEVar3 = Game::SceneInfo.avatars.next;
  if (Game::SceneInfo.avatars.next != (avatar_0x900_conflict6)0x0) {
    while (av = ADJ(pEVar3), ADJ(pEVar3).object.tag != Actor_Cameron) {
      ppEVar1 = &pEVar3->next;
      pEVar3 = *ppEVar1;
      if (*ppEVar1 == (avatar_0x900_conflict6)0x0) {
        return;
      }
    }
    if (av != (avatar_conflict13 *)0x0) {
      avatar::setPosition((avatar *)av,param_1);
      Maths::NormaliseAngles2PI(param_2,&ADJ(pEVar3)->rotEuler);
      pOVar2 = (av->object).vtable;
      ADJ(pEVar3)->scaleIsCalculated = 0;
      local_4 = 3;
      (*pOVar2->onMessage)(av,&local_4);
    }
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void __fastcall FUN_001405e0(undefined4 param_1,vec3 *param_2,undefined4 param_3)

{
  undefined4 *in_EAX;
  vec3 local_1c;
  undefined4 local_10;
  undefined4 local_c;
  undefined4 local_8;
  undefined4 local_4;
  
  local_10 = *in_EAX;
  local_c = in_EAX[1];
  local_8 = in_EAX[2];
  local_4 = param_3;
  local_1c.z = 0.0;
  local_1c.y = 0.0;
  local_1c.x = 0.0;
  calculatePhysicsWithCallbacks
            (&local_10,param_2,&local_1c,param_2,&local_1c,0.0033333334,g_ticksToRun,FUN_00140700,
             FUN_00140770,switchD_000d4179::EmptyFunction);
  return;
}




void FUN_00140700(EntityMoveContext *ctx,vec3 *pos,vec3 *acc,vec3 *outPos)

{
  outPos->x = (ctx->pos).x - pos->x;
  outPos->y = (ctx->pos).y - pos->y;
  outPos->z = (ctx->pos).z - pos->z;
  outPos->x = (ctx->velocity).x * outPos->x;
  outPos->y = (ctx->velocity).x * outPos->y;
  outPos->z = (ctx->velocity).x * outPos->z;
  return;
}




void FUN_00140770(vec3 *pos1,vec3 *pos2,vec3 *outPos)

{
  float fVar1;
  float10 fVar2;
  float fVar3;
  
  fVar1 = outPos->x;
  fVar3 = pos1->x;
  if (((fVar3 <= pos2->x) || (fVar1 <= fVar3)) && ((pos2->x <= fVar3 || (fVar3 <= fVar1)))) {
    fVar2 = abs_float(fVar1 - fVar3);
    if ((float10)1e-05 <= fVar2) {
      fVar3 = fVar1;
    }
  }
  fVar1 = outPos->y;
  outPos->x = fVar3;
  fVar3 = pos1->y;
  if (((fVar3 <= pos2->y) || (fVar1 <= fVar3)) && ((pos2->y <= fVar3 || (fVar3 <= fVar1)))) {
    fVar2 = abs_float(fVar1 - fVar3);
    if ((float10)1e-05 <= fVar2) {
      fVar3 = fVar1;
    }
  }
  fVar1 = outPos->z;
  outPos->y = fVar3;
  fVar3 = pos1->z;
  if (((fVar3 <= pos2->z) || (fVar1 <= fVar3)) && ((pos2->z <= fVar3 || (fVar3 <= fVar1)))) {
    fVar2 = abs_float(fVar1 - fVar3);
    if ((float10)1e-05 <= fVar2) {
      fVar3 = fVar1;
    }
  }
  outPos->z = fVar3;
  return;
}




float10 __fastcall FUN_00146ce0(float *param_1)

{
  float *in_EAX;
  
  return SQRT(((float10)param_1[1] - (float10)in_EAX[1]) *
              ((float10)param_1[1] - (float10)in_EAX[1]) +
              ((float10)*param_1 - (float10)*in_EAX) * ((float10)*param_1 - (float10)*in_EAX) +
              ((float10)param_1[2] - (float10)in_EAX[2]) *
              ((float10)param_1[2] - (float10)in_EAX[2]));
}



// WARNING: Type propagation algorithm not settling
// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


undefined4 FUN_001476d0(float *param_1,int *param_2,vec3 *param_3,vec3 *param_4,weapon *wpn)

{
  int iVar1;
  float10 extraout_ST0;
  float10 extraout_ST0_00;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  Skeleton *local_18;
  undefined4 *local_14;
  vec3 some_v;
  Model *instance;
  
  if (wpn->field378_0xac4 != 0) {
    instance = (wpn->avatar).model;
    if (instance == (Model *)0x0) {
      local_18 = (Skeleton *)0x0;
    }
    else {
      local_18 = instance->skeleton;
      if (local_18 == (Skeleton *)0x0) {
        local_18 = instance->skeleton2;
      }
    }
    *param_2 = 0;
    checkCollisionAgainstSkeleton
              (*(AnimCollisionSubresourceEntry **)&wpn->field_0xac8,local_18,param_3,
               &(wpn->avatar).drawAffine);
    *param_1 = (float)extraout_ST0;
    iVar1 = 1;
    if (1 < wpn->field378_0xac4) {
      local_14 = (undefined4 *)&wpn->field_0xacc;
      do {
        checkCollisionAgainstSkeleton
                  ((AnimCollisionSubresourceEntry *)*local_14,local_18,&some_v,
                   &(wpn->avatar).drawAffine);
        fVar2 = param_4->x - param_3->x;
        fVar4 = param_4->z - param_3->z;
        fVar3 = param_4->y - param_3->y;
        fVar6 = param_4->y - some_v.y;
        fVar7 = param_4->z - some_v.z;
        fVar5 = param_4->x - some_v.x;
        if (fVar7 * fVar7 + fVar6 * fVar6 + fVar5 * fVar5 <
            fVar2 * fVar2 + fVar4 * fVar4 + fVar3 * fVar3) {
          *param_2 = iVar1;
          *param_1 = (float)extraout_ST0_00;
          param_3->y = some_v.y;
          param_3->x = some_v.x;
          param_3->z = some_v.z;
        }
        iVar1 = iVar1 + 1;
        local_14 = local_14 + 1;
      } while (iVar1 < wpn->field378_0xac4);
    }
    return 1;
  }
  return 0;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


undefined4 FUN_001478b0(float *param_1,vec3 *param_2,float *param_3)

{
  AffineTransform *pAVar1;
  int iVar2;
  AffineTransform *pAVar3;
  int unaff_EBX;
  int iVar4;
  int *piVar5;
  float10 fVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  float fVar10;
  float fVar11;
  float fVar12;
  Skeleton *local_10;
  
  if (*(int *)(unaff_EBX + 0xab4) != 0) {
    iVar4 = *(int *)(unaff_EBX + 0x204);
    pAVar1 = (AffineTransform *)(unaff_EBX + 0x2ac);
    if (iVar4 == 0) {
      local_10 = (Skeleton *)0x0;
    }
    else {
      local_10 = *(Skeleton **)(iVar4 + 0x168);
      if (local_10 == (Skeleton *)0x0) {
        local_10 = *(Skeleton **)(iVar4 + 0x164);
      }
    }
    FUN_00051ce0((int)local_10,*(undefined4 *)(unaff_EBX + 0xab8),param_2,pAVar1);
    iVar4 = 1;
    if (1 < *(int *)(unaff_EBX + 0xab4)) {
      piVar5 = (int *)(unaff_EBX + 0xabc);
      do {
        iVar2 = *piVar5;
        fVar8 = *(float *)(iVar2 + 0x10);
        fVar10 = *(float *)(iVar2 + 0x20);
        fVar11 = *(float *)(iVar2 + 0x30);
        fVar7 = fVar8;
        fVar9 = fVar10;
        if (-1 < *(short *)(iVar2 + 2)) {
          pAVar3 = Skeleton::getBoneAffineIntoGlobal(local_10,(int)*(short *)(iVar2 + 2));
          fVar7 = pAVar3->m[0][2] * fVar11 + pAVar3->m[0][1] * fVar10 + pAVar3->m[0][0] * fVar8 +
                  pAVar3->m[0][3];
          fVar9 = pAVar3->m[1][0] * fVar8 + pAVar3->m[1][2] * fVar11 + pAVar3->m[1][1] * fVar10 +
                  pAVar3->m[1][3];
          fVar11 = pAVar3->m[2][0] * fVar8 + pAVar3->m[2][2] * fVar11 + pAVar3->m[2][1] * fVar10 +
                   pAVar3->m[2][3];
        }
        fVar8 = fVar7;
        fVar10 = fVar9;
        if (pAVar1 != (AffineTransform *)0x0) {
          fVar8 = *(float *)(unaff_EBX + 0x2b4) * fVar11 + *(float *)(unaff_EBX + 0x2b0) * fVar9 +
                  pAVar1->m[0][0] * fVar7 + *(float *)(unaff_EBX + 0x2b8);
          fVar10 = *(float *)(unaff_EBX + 700) * fVar7 + *(float *)(unaff_EBX + 0x2c4) * fVar11 +
                   *(float *)(unaff_EBX + 0x2c0) * fVar9 + *(float *)(unaff_EBX + 0x2c8);
          fVar11 = *(float *)(unaff_EBX + 0x2cc) * fVar7 + *(float *)(unaff_EBX + 0x2d4) * fVar11 +
                   *(float *)(unaff_EBX + 0x2d0) * fVar9 + *(float *)(unaff_EBX + 0x2d8);
        }
        fVar9 = param_1[1] - param_2->y;
        fVar7 = *param_1 - param_2->x;
        fVar12 = param_1[2] - param_2->z;
        if ((param_1[2] - fVar11) * (param_1[2] - fVar11) +
            (param_1[1] - fVar10) * (param_1[1] - fVar10) + (*param_1 - fVar8) * (*param_1 - fVar8)
            < fVar12 * fVar12 + fVar9 * fVar9 + fVar7 * fVar7) {
          param_2->x = fVar8;
          param_2->y = fVar10;
          param_2->z = fVar11;
        }
        iVar4 = iVar4 + 1;
        piVar5 = piVar5 + 1;
      } while (iVar4 < *(int *)(unaff_EBX + 0xab4));
    }
    fVar6 = (float10)FUN_0003db30();
    *param_3 = (float)fVar6;
    return 1;
  }
  return 0;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


float10 FUN_00151c08(float *param_1)

{
  float fVar1;
  float fVar2;
  
  fVar1 = (float)*(undefined8 *)(param_1 + 1);
  fVar2 = (float)((ulonglong)*(undefined8 *)(param_1 + 1) >> 0x20);
  return (float10)(*param_1 * *param_1 + fVar1 * fVar1 + fVar2 * fVar2);
}




void multMatWithVec4(vec4 *out,vec4 *v,D3DXMATRIX *mat)

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
  float fVar12;
  float fVar13;
  float fVar14;
  float fVar15;
  float fVar16;
  
  fVar1 = v->x;
  fVar2 = v->y;
  fVar3 = v->z;
  fVar4 = v->w;
  fVar5 = mat->m[0][1];
  fVar6 = mat->m[0][2];
  fVar7 = mat->m[0][3];
  fVar8 = mat->m[1][1];
  fVar9 = mat->m[1][2];
  fVar10 = mat->m[1][3];
  fVar11 = mat->m[2][1];
  fVar12 = mat->m[2][2];
  fVar13 = mat->m[2][3];
  fVar14 = mat->m[3][1];
  fVar15 = mat->m[3][2];
  fVar16 = mat->m[3][3];
  out->x = fVar1 * mat->m[0][0] + fVar2 * mat->m[1][0] + fVar3 * mat->m[2][0] + fVar4 * mat->m[3][0]
  ;
  out->y = fVar1 * fVar5 + fVar2 * fVar8 + fVar3 * fVar11 + fVar4 * fVar14;
  out->z = fVar1 * fVar6 + fVar2 * fVar9 + fVar3 * fVar12 + fVar4 * fVar15;
  out->w = fVar1 * fVar7 + fVar2 * fVar10 + fVar3 * fVar13 + fVar4 * fVar16;
  return;
}




D3DXMATRIX * Maths::MultiplyMat4s(D3DXMATRIX *outMatrix,D3DXMATRIX *inA,D3DXMATRIX *inB)

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
  float fVar12;
  float fVar13;
  float fVar14;
  float fVar15;
  float fVar16;
  float fVar17;
  float fVar18;
  float fVar19;
  float fVar20;
  float fVar21;
  float fVar22;
  float fVar23;
  float fVar24;
  float fVar25;
  float fVar26;
  float fVar27;
  float fVar28;
  float fVar29;
  float fVar30;
  float fVar31;
  float fVar32;
  float fVar33;
  float fVar34;
  float fVar35;
  float fVar36;
  float fVar37;
  float fVar38;
  float fVar39;
  float fVar40;
  float fVar41;
  float fVar42;
  float fVar43;
  float fVar44;
  float fVar45;
  float fVar46;
  float fVar47;
  float fVar48;
  float fVar49;
  float fVar50;
  float fVar51;
  float fVar52;
  float fVar53;
  float fVar54;
  float fVar55;
  float fVar56;
  float fVar57;
  float fVar58;
  float fVar59;
  float fVar60;
  float fVar61;
  float fVar62;
  float fVar63;
  float fVar64;
  float fVar65;
  float fVar66;
  float fVar67;
  float fVar68;
  float fVar69;
  float fVar70;
  float fVar71;
  float fVar72;
  float fVar73;
  float fVar74;
  float fVar75;
  float fVar76;
  
  fVar1 = inA->m[0][0];
  fVar2 = inB->m[0][1];
  fVar3 = inB->m[0][2];
  fVar4 = inB->m[0][3];
  fVar5 = inA->m[0][1];
  fVar6 = inB->m[1][1];
  fVar7 = inB->m[1][2];
  fVar8 = inB->m[1][3];
  fVar9 = inA->m[0][2];
  fVar10 = inB->m[2][1];
  fVar11 = inB->m[2][2];
  fVar12 = inB->m[2][3];
  fVar13 = inA->m[0][3];
  fVar14 = inB->m[3][1];
  fVar15 = inB->m[3][2];
  fVar16 = inB->m[3][3];
  fVar17 = inA->m[1][0];
  fVar18 = inB->m[0][0];
  fVar19 = inB->m[0][1];
  fVar20 = inB->m[0][2];
  fVar21 = inB->m[0][3];
  fVar22 = inA->m[1][1];
  fVar23 = inB->m[1][0];
  fVar24 = inB->m[1][1];
  fVar25 = inB->m[1][2];
  fVar26 = inB->m[1][3];
  fVar27 = inA->m[1][2];
  fVar28 = inB->m[2][0];
  fVar29 = inB->m[2][1];
  fVar30 = inB->m[2][2];
  fVar31 = inB->m[2][3];
  fVar32 = inA->m[1][3];
  fVar33 = inB->m[3][0];
  fVar34 = inB->m[3][1];
  fVar35 = inB->m[3][2];
  fVar36 = inB->m[3][3];
  fVar37 = inA->m[2][0];
  fVar38 = inB->m[0][0];
  fVar39 = inB->m[0][1];
  fVar40 = inB->m[0][2];
  fVar41 = inB->m[0][3];
  fVar42 = inA->m[2][1];
  fVar43 = inB->m[1][0];
  fVar44 = inB->m[1][1];
  fVar45 = inB->m[1][2];
  fVar46 = inB->m[1][3];
  fVar47 = inA->m[2][2];
  fVar48 = inB->m[2][0];
  fVar49 = inB->m[2][1];
  fVar50 = inB->m[2][2];
  fVar51 = inB->m[2][3];
  fVar52 = inA->m[2][3];
  fVar53 = inB->m[3][0];
  fVar54 = inB->m[3][1];
  fVar55 = inB->m[3][2];
  fVar56 = inB->m[3][3];
  fVar57 = inA->m[3][0];
  fVar58 = inB->m[0][0];
  fVar59 = inB->m[0][1];
  fVar60 = inB->m[0][2];
  fVar61 = inB->m[0][3];
  fVar62 = inA->m[3][1];
  fVar63 = inB->m[1][0];
  fVar64 = inB->m[1][1];
  fVar65 = inB->m[1][2];
  fVar66 = inB->m[1][3];
  fVar67 = inA->m[3][2];
  fVar68 = inB->m[2][0];
  fVar69 = inB->m[2][1];
  fVar70 = inB->m[2][2];
  fVar71 = inB->m[2][3];
  fVar72 = inA->m[3][3];
  fVar73 = inB->m[3][0];
  fVar74 = inB->m[3][1];
  fVar75 = inB->m[3][2];
  fVar76 = inB->m[3][3];
  outMatrix->m[0][0] =
       fVar1 * inB->m[0][0] + fVar5 * inB->m[1][0] + fVar9 * inB->m[2][0] + fVar13 * inB->m[3][0];
  outMatrix->m[0][1] = fVar1 * fVar2 + fVar5 * fVar6 + fVar9 * fVar10 + fVar13 * fVar14;
  outMatrix->m[0][2] = fVar1 * fVar3 + fVar5 * fVar7 + fVar9 * fVar11 + fVar13 * fVar15;
  outMatrix->m[0][3] = fVar1 * fVar4 + fVar5 * fVar8 + fVar9 * fVar12 + fVar13 * fVar16;
  outMatrix->m[1][0] = fVar17 * fVar18 + fVar22 * fVar23 + fVar27 * fVar28 + fVar32 * fVar33;
  outMatrix->m[1][1] = fVar17 * fVar19 + fVar22 * fVar24 + fVar27 * fVar29 + fVar32 * fVar34;
  outMatrix->m[1][2] = fVar17 * fVar20 + fVar22 * fVar25 + fVar27 * fVar30 + fVar32 * fVar35;
  outMatrix->m[1][3] = fVar17 * fVar21 + fVar22 * fVar26 + fVar27 * fVar31 + fVar32 * fVar36;
  outMatrix->m[2][0] = fVar37 * fVar38 + fVar42 * fVar43 + fVar47 * fVar48 + fVar52 * fVar53;
  outMatrix->m[2][1] = fVar37 * fVar39 + fVar42 * fVar44 + fVar47 * fVar49 + fVar52 * fVar54;
  outMatrix->m[2][2] = fVar37 * fVar40 + fVar42 * fVar45 + fVar47 * fVar50 + fVar52 * fVar55;
  outMatrix->m[2][3] = fVar37 * fVar41 + fVar42 * fVar46 + fVar47 * fVar51 + fVar52 * fVar56;
  outMatrix->m[3][0] = fVar57 * fVar58 + fVar62 * fVar63 + fVar67 * fVar68 + fVar72 * fVar73;
  outMatrix->m[3][1] = fVar57 * fVar59 + fVar62 * fVar64 + fVar67 * fVar69 + fVar72 * fVar74;
  outMatrix->m[3][2] = fVar57 * fVar60 + fVar62 * fVar65 + fVar67 * fVar70 + fVar72 * fVar75;
  outMatrix->m[3][3] = fVar57 * fVar61 + fVar62 * fVar66 + fVar67 * fVar71 + fVar72 * fVar76;
  return outMatrix;
}




float10 atan(float x)

{
  float10 fVar1;
  float fVar2;
  float fVar3;
  
  fVar2 = x * x;
  if (fVar2 <= 1.0) {
    return (((((((float10)fVar2 * (float10)0.0066582896 - (float10)0.03310525) * (float10)fVar2 +
               (float10)0.07899983) * (float10)fVar2 - (float10)0.13195902) * (float10)fVar2 +
             (float10)0.19796892) * (float10)fVar2 - (float10)0.33316) * (float10)fVar2 +
           (float10)0.99999565) * (float10)x;
  }
  fVar2 = 1.0 / x;
  fVar3 = fVar2 * fVar2;
  fVar1 = (((((((float10)fVar3 * (float10)0.0066582896 - (float10)0.03310525) * (float10)fVar3 +
              (float10)0.07899983) * (float10)fVar3 - (float10)0.13195902) * (float10)fVar3 +
            (float10)0.19796892) * (float10)fVar3 - (float10)0.33316) * (float10)fVar3 +
          (float10)0.99999565) * (float10)fVar2;
  if (1.0 < x) {
    return (float10)1.5707964 - fVar1;
  }
  return -(fVar1 + (float10)1.5707964);
}




float10 FastCotangent(float angle)

{
  bool bVar1;
  float10 clamped10;
  float fVar2;
  float uStack_4;
  float clamped;
  
  clamped10 = (float10)ClampAngle(angle);
  clamped = (float)clamped10;
  if (clamped < 0.0) {
    if (-1.5707964 <= clamped) {
      if (clamped < -0.7853982) {
        clamped = clamped + 1.5707964;
        bVar1 = true;
        goto LAB_0015292d;
      }
    }
    else {
      clamped = 3.1415927 - clamped;
      if (0.7853982 < clamped) {
        clamped = clamped - 1.5707964;
        bVar1 = true;
        goto LAB_0015292d;
      }
    }
  }
  else if (clamped <= 1.5707964) {
    if (0.7853982 < clamped) {
      clamped = clamped - 1.5707964;
      bVar1 = true;
      goto LAB_0015292d;
    }
  }
  else {
    clamped = clamped - 3.1415927;
    if (clamped < -0.7853982) {
      clamped = clamped + 1.5707964;
      bVar1 = true;
      goto LAB_0015292d;
    }
  }
  bVar1 = false;
LAB_0015292d:
  fVar2 = clamped * clamped;
  uStack_4 = ((((fVar2 * 0.047132045 + 0.035827976) * fVar2 + 0.13861623) * fVar2 + 0.33272377) *
              fVar2 + 1.0000194) * clamped;
  if (bVar1) {
    uStack_4 = 0.0 - 1.0 / uStack_4;
  }
  return (float10)uStack_4;
}




float10 FUN_001529a0(float param_1,float param_2)

{
  int iVar1;
  bool bVar2;
  float fVar3;
  
  if (param_1 != 0.0) {
    fVar3 = (float)((uint)param_1 & 0x7fffff | 0x3f800000) - 1.0;
    fVar3 = ((((((((0.05027751 - fVar3 * 0.008874697) * fVar3 - 0.13453425) * fVar3 + 0.23923166) *
                 fVar3 - 0.34599602) * fVar3 + 0.47832355) * fVar3 - 0.72111464) * fVar3 + 1.4426868
             ) * fVar3 + 4.886358e-08 +
            (float)(int)(short)(((ushort)((uint)param_1 >> 0x17) & 0xff) - 0x7f)) * param_2;
    iVar1 = (int)(short)(int)fVar3;
    fVar3 = fVar3 - (float)iVar1;
    if (fVar3 == 0.0) {
      fVar3 = 1.0;
    }
    else {
      fVar3 = ((((fVar3 * 0.0018951073 + 0.008946215) * fVar3 + 0.055863284) * fVar3 + 0.24014077) *
               fVar3 + 0.69315463) * fVar3 + 0.9999999;
    }
    bVar2 = (int)param_1 < 0;
    param_1 = fVar3;
    if ((bVar2) && (((int)param_2 & 1U) != 0)) {
      param_1 = 0.0 - fVar3;
    }
    return (float10)(float)((int)param_1 + iVar1 * 0x800000);
  }
  if (param_2 != 0.0) {
    return (float10)0.0;
  }
  return (float10)1.0;
}




float10 scaled_invsqrt(float x)

{
  float10 inv_sqrt;
  float fVar1;
  
  inv_sqrt = (float10)invsqrt(x);
  fVar1 = (float)inv_sqrt;
  fVar1 = (1.5 - x * 0.5 * fVar1 * fVar1) * fVar1;
                    // If x is positive
  if (0.0 - x < 0.0) {
    x = (1.5 - x * 0.5 * fVar1 * fVar1) * fVar1 * x;
  }
  return (float10)x;
}




float10 abs_float(float param_1)

{
  if (0.0 <= param_1) {
    return (float10)param_1;
  }
  return (float10)(0.0 - param_1);
}




float modf(float x,float div)

{
  float f1;
  float f2;
  
  f2 = div;
  if (div < 0.0) {
    f2 = 0.0 - div;
  }
  f1 = x;
  if (x < 0.0) {
    f1 = 0.0 - x;
  }
  if (f2 <= f1) {
    return x - (float)(int)(x / div) * div;
  }
  return x;
}




float10 FUN_00152c40(float param_1)

{
  float10 fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  
  fVar2 = param_1 * param_1;
  if (fVar2 <= 0.25) {
    return (float10)(1.5707964 -
                    ((((fVar2 * 0.053164963 + 0.03822511) * fVar2 + 0.0757453) * fVar2 + 0.16663216)
                     * fVar2 + 1.0000005) * param_1);
  }
  if (param_1 <= 0.5) {
    fVar3 = (param_1 + 1.0) * 0.5;
    fVar1 = (float10)invsqrt(fVar3);
    fVar2 = (float)fVar1;
    fVar2 = (1.5 - fVar3 * 0.5 * fVar2 * fVar2) * fVar2;
    fVar4 = fVar3;
    if (0.0 - fVar3 < 0.0) {
      fVar4 = (1.5 - fVar3 * 0.5 * fVar2 * fVar2) * fVar2 * fVar3;
    }
    return (float10)(3.1415927 -
                    ((((fVar3 * 0.053164963 + 0.03822511) * fVar3 + 0.0757453) * fVar3 + 0.16663216)
                     * fVar3 + 1.0000005) * fVar4 * 2.0);
  }
  fVar3 = 0.5 - param_1 * 0.5;
  fVar1 = (float10)invsqrt(fVar3);
  fVar2 = (float)fVar1;
  fVar2 = (1.5 - fVar3 * 0.5 * fVar2 * fVar2) * fVar2;
  fVar4 = fVar3;
  if (0.0 - fVar3 < 0.0) {
    fVar4 = (1.5 - fVar3 * 0.5 * fVar2 * fVar2) * fVar2 * fVar3;
  }
  return (float10)(((((fVar3 * 0.053164963 + 0.03822511) * fVar3 + 0.0757453) * fVar3 + 0.16663216)
                    * fVar3 + 1.0000005) * fVar4 * 2.0);
}




float10 arcsin(float theta)

{
  float10 fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  
  fVar2 = theta * theta;
  if (fVar2 <= 0.25) {
    return (float10)(((((fVar2 * 0.053164963 + 0.03822511) * fVar2 + 0.0757453) * fVar2 + 0.16663216
                      ) * fVar2 + 1.0000005) * theta);
  }
  if (theta <= 0.5) {
    fVar3 = (theta + 1.0) * 0.5;
    fVar1 = (float10)invsqrt(fVar3);
    fVar2 = (float)fVar1;
    fVar2 = (1.5 - fVar3 * 0.5 * fVar2 * fVar2) * fVar2;
    fVar4 = fVar3;
    if (0.0 - fVar3 < 0.0) {
      fVar4 = (1.5 - fVar3 * 0.5 * fVar2 * fVar2) * fVar2 * fVar3;
    }
    return (float10)(((((fVar3 * 0.053164963 + 0.03822511) * fVar3 + 0.0757453) * fVar3 + 0.16663216
                      ) * fVar3 + 1.0000005) * fVar4 * 2.0 - 1.5707964);
  }
  fVar3 = 0.5 - theta * 0.5;
  fVar1 = (float10)invsqrt(fVar3);
  fVar2 = (float)fVar1;
  fVar2 = (1.5 - fVar3 * 0.5 * fVar2 * fVar2) * fVar2;
  fVar4 = fVar3;
  if (0.0 - fVar3 < 0.0) {
    fVar4 = (1.5 - fVar3 * 0.5 * fVar2 * fVar2) * fVar2 * fVar3;
  }
  return (float10)(1.5707964 -
                  ((((fVar3 * 0.053164963 + 0.03822511) * fVar3 + 0.0757453) * fVar3 + 0.16663216) *
                   fVar3 + 1.0000005) * fVar4 * 2.0);
}




float10 atan2(float x,float y)

{
  float fVar1;
  float fVar2;
  float fVar3;
  
  fVar1 = y;
  if (y < 0.0) {
    y = 0.0 - y;
  }
  fVar2 = x;
  if (x < 0.0) {
    fVar2 = 0.0 - x;
  }
  if (fVar2 <= y) {
    fVar2 = fVar2 / y;
    fVar3 = fVar2 * fVar2;
    y = 1.5707964 -
        ((((((fVar3 * 0.0066582896 - 0.03310525) * fVar3 + 0.07899983) * fVar3 - 0.13195902) * fVar3
          + 0.19796892) * fVar3 - 0.33316) * fVar3 + 0.99999565) * fVar2;
  }
  else {
    fVar2 = y / fVar2;
    fVar3 = fVar2 * fVar2;
    y = ((((((fVar3 * 0.0066582896 - 0.03310525) * fVar3 + 0.07899983) * fVar3 - 0.13195902) * fVar3
          + 0.19796892) * fVar3 - 0.33316) * fVar3 + 0.99999565) * fVar2;
  }
  if (0.0 <= x) {
    if (0.0 <= fVar1) {
      return (float10)y;
    }
    return -(float10)y;
  }
  if (0.0 <= fVar1) {
    return (float10)3.1415927 - (float10)y;
  }
  return (float10)y - (float10)3.1415927;
}




float10 cos(float angle)

{
  float10 fVar1;
  float fVar2;
  float clamped;
  
  fVar1 = (float10)ClampAngle(angle);
  clamped = (float)fVar1;
  fVar2 = clamped;
  if (clamped < 0.0) {
    fVar2 = 0.0 - clamped;
  }
  if (fVar2 <= 0.7853982) {
    fVar1 = (float10)clamped * (float10)clamped;
    return (((float10)0.041655023 - (float10)0.0013585844 * fVar1) * fVar1 - (float10)0.49999857) *
           fVar1 + (float10)1.0;
  }
  if (fVar2 <= 2.3561945) {
    fVar2 = 1.5707964 - fVar2;
    return (((float10)(fVar2 * fVar2) * (float10)0.008121493 - (float10)0.16660157) *
            (float10)(fVar2 * fVar2) + (float10)0.999995) * (float10)fVar2;
  }
  clamped = (fVar2 - 3.1415927) * (fVar2 - 3.1415927);
  return -((((float10)0.041655023 - (float10)clamped * (float10)0.0013585844) * (float10)clamped -
           (float10)0.49999857) * (float10)clamped + (float10)1.0);
}




float sin(float __x)

{
  float fVar1;
  float fVar3;
  float10 fVar2;
  float fVar4;
  
  fVar3 = (float)ClampAngle(__x);
  fVar1 = (float)fVar2;
  fVar4 = fVar1;
  if (fVar1 < 0.0) {
    fVar4 = 0.0 - fVar1;
  }
  if (fVar4 <= 0.7853982) {
    return fVar3;
  }
  if (fVar4 <= 2.3561945) {
    if (fVar1 < 0.0) {
      return fVar3;
    }
    return fVar3;
  }
  if (fVar1 < 0.0) {
    return fVar3;
  }
  return fVar3;
}




float10 invsqrt(float param_1)

{
  uint uVar1;
  float fVar2;
  float10 fVar3;
  float fVar4;
  
  fVar4 = param_1 * 0.5;
  fVar2 = (float)((0x7f000000U - (int)param_1 >> 1) + 0x1fc00000);
  uVar1 = (uint)param_1 & 0x8000000;
  param_1 = fVar2;
  if (uVar1 == 0) {
    param_1 = fVar2 * 0.70710677;
  }
  fVar3 = ((float10)1.5 - (float10)param_1 * (float10)param_1 * (float10)fVar4) * (float10)param_1;
  return ((float10)1.5 - fVar3 * fVar3 * (float10)fVar4) * fVar3;
}




float10 invsqrt(float param_1)

{
  float10 f10;
  float f;
  
  f10 = (float10)invsqrt(param_1);
  f = (float)f10;
  f = (1.5 - param_1 * 0.5 * f * f) * f;
  return ((float10)1.5 - (float10)(param_1 * 0.5) * (float10)f * (float10)f) * (float10)f;
}




float10 ClampAngle(float x)

{
  if (-3.1415927 <= x) {
    for (; 3.1415927 < x; x = x - 6.2831855) {
    }
  }
  else {
    x = x + 6.2831855;
    if (x < -3.1415927) {
      do {
        x = x + 6.2831855;
      } while (x < -3.1415927);
      return (float10)x;
    }
  }
  return (float10)x;
}




void AffineTransform::getEulers(AffineTransform *param_1,vec3 *param_2)

{
  float fVar1;
  float10 fVar2;
  
  param_2->x = 0.0;
  param_2->y = 0.0;
  param_2->z = 0.0;
  fVar1 = param_1->m[0][0];
  param_2->x = fVar1 * fVar1 + param_2->x;
  fVar1 = param_1->m[0][1];
  param_2->y = fVar1 * fVar1 + param_2->y;
  fVar1 = param_1->m[0][2];
  param_2->z = fVar1 * fVar1 + param_2->z;
  fVar1 = param_1->m[1][0];
  param_2->x = fVar1 * fVar1 + param_2->x;
  fVar1 = param_1->m[1][1];
  param_2->y = fVar1 * fVar1 + param_2->y;
  fVar1 = param_1->m[1][2];
  param_2->z = fVar1 * fVar1 + param_2->z;
  fVar1 = param_1->m[2][0];
  param_2->x = fVar1 * fVar1 + param_2->x;
  fVar1 = param_1->m[2][1];
  param_2->y = fVar1 * fVar1 + param_2->y;
  fVar1 = param_1->m[2][2];
  param_2->z = fVar1 * fVar1 + param_2->z;
  fVar2 = scaled_invsqrt(param_2->x);
  param_2->x = (float)fVar2;
  fVar2 = scaled_invsqrt(param_2->y);
  param_2->y = (float)fVar2;
  fVar2 = scaled_invsqrt(param_2->z);
  param_2->z = (float)fVar2;
  return;
}



void FUN_00153be0(D3DXMATRIX *param_1,float param_2,float param_3,float param_4,float param_5,
                 float param_6,float param_7,float param_8,float param_9,float param_10,
                 float param_11)

{
  DirectXShaderConstant local_10;
  
  if (param_8 == 1.0) {
    param_1->m[3][2] = 0.0;
    param_1->m[3][1] = 0.0;
    param_1->m[3][0] = 0.0;
    param_1->m[2][3] = 0.0;
    param_1->m[2][1] = 0.0;
    param_1->m[2][0] = 0.0;
    param_1->m[1][3] = 0.0;
    param_1->m[1][2] = 0.0;
    param_1->m[1][0] = 0.0;
    param_1->m[0][3] = 0.0;
    param_1->m[0][2] = 0.0;
    param_1->m[0][1] = 0.0;
    param_1->m[3][3] = 1.0;
    param_1->m[2][2] = 1.0;
    param_1->m[1][1] = 1.0;
    param_1->m[0][0] = 1.0;
  }
  else {
    DirectXShaderConstant::write(&local_10,param_5,param_6,param_7,param_8);
    D3DX8::D3DXMatrixRotationQuaternion(param_1,&local_10);
  }
  param_1->m[3][0] = param_9;
  param_1->m[3][1] = param_10;
  param_1->m[3][2] = param_11;
  if (param_2 != 1.0) {
    param_1->m[0][0] = param_1->m[0][0] * param_2;
    param_1->m[0][1] = param_1->m[0][1] * param_2;
    param_1->m[0][2] = param_1->m[0][2] * param_2;
  }
  if (param_3 != 1.0) {
    param_1->m[1][0] = param_1->m[1][0] * param_3;
    param_1->m[1][1] = param_1->m[1][1] * param_3;
    param_1->m[1][2] = param_1->m[1][2] * param_3;
  }
  if (param_4 != 1.0) {
    param_1->m[2][0] = param_1->m[2][0] * param_4;
    param_1->m[2][1] = param_1->m[2][1] * param_4;
    param_1->m[2][2] = param_1->m[2][2] * param_4;
  }
  param_1->m[0][3] = 0.0;
  param_1->m[1][3] = 0.0;
  param_1->m[2][3] = 0.0;
  param_1->m[3][3] = 1.0;
  return;
}




void Quaternion::Multiply(Quaternion *q1,Quaternion *q2,Quaternion *outQ)

{
  float fVar1;
  float fVar10;
  float fVar11;
  float fVar12;
  float fVar13;
  float fVar14;
  float fVar15;
  float fVar16;
  float fVar17;
  float fVar18;
  float fVar19;
  float fVar2;
  float fVar20;
  float fVar21;
  float fVar22;
  float fVar23;
  float fVar24;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  
  fVar1 = q1->z;
  fVar2 = q2->x;
  fVar3 = q2->w;
  fVar4 = q1->y;
  fVar5 = q1->z;
  fVar6 = q2->w;
  fVar7 = q1->x;
  fVar8 = q2->x;
  fVar9 = q2->y;
  fVar10 = q1->w;
  fVar11 = q1->x;
  fVar12 = q2->z;
  fVar13 = q1->x;
  fVar14 = q2->y;
  fVar15 = q2->z;
  fVar16 = q1->w;
  fVar17 = q2->x;
  fVar18 = q1->y;
  fVar19 = q2->w;
  fVar20 = q1->w;
  fVar21 = q2->y;
  fVar22 = q1->y;
  fVar23 = q1->z;
  fVar24 = q2->z;
  outQ->x = (q1->x * q2->w + q2->z * q1->y + q2->x * q1->w) - q1->z * q2->y;
  outQ->y = (fVar1 * fVar2 + fVar3 * fVar4 + fVar9 * fVar10) - fVar11 * fVar12;
  outQ->z = (fVar13 * fVar14 + fVar5 * fVar6 + fVar15 * fVar16) - fVar17 * fVar18;
  outQ->w = ((fVar19 * fVar20 - fVar7 * fVar8) - fVar21 * fVar22) - fVar23 * fVar24;
  return;
}




void Quaternion::fromAToB(vec3 *a,vec3 *b,Quaternion *quat)

{
  float10 fVar14;
  float fVar15;
  float fVar1;
  float fVar10;
  float fVar11;
  float fVar12;
  float fVar13;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  
  fVar13 = b->y * a->y + b->z * a->z + a->x * b->x + 1.0;
  fVar14 = abs_float(fVar13);
  if ((float10)1e-06 <= fVar14) {
    fVar1 = b->z;
    fVar2 = a->y;
    fVar3 = b->y;
    fVar4 = a->z;
    fVar5 = a->x;
    fVar6 = b->z;
    fVar7 = b->x;
    fVar8 = a->z;
    fVar9 = b->x;
    fVar10 = a->y;
    fVar11 = a->x;
    fVar12 = b->y;
    fVar14 = (float10)invsqrt(fVar13);
    fVar15 = (float)fVar14 * 0.70710677;
    quat->x = fVar15 * (fVar1 * fVar2 - fVar3 * fVar4);
    quat->y = fVar15 * (fVar7 * fVar8 - fVar5 * fVar6);
    quat->z = fVar15 * (fVar11 * fVar12 - fVar9 * fVar10);
    quat->w = fVar15 * fVar13;
    return;
  }
  fVar14 = abs_float(a->x);
  if ((float10)0.5 < fVar14) {
    quat->x = a->z;
    quat->y = 0.0;
    quat->z = 0.0 - a->x;
    quat->w = 0.0;
    return;
  }
  quat->x = 0.0;
  quat->y = 0.0 - a->z;
  quat->z = a->y;
  quat->w = 0.0;
  return;
}




void Quaternion::SLERP(Quaternion *q1,Quaternion *q2,Quaternion *outQ,float t)

{
  float10 fVar1;
  float10 fVar2;
  float10 extraout_ST0;
  float10 extraout_ST0_00;
  float fVar3;
  float fVar4;
  
  fVar3 = q2->y * q1->y + q1->x * q2->x + q2->w * q1->w + q2->z * q1->z;
  fVar4 = 1.0 - t;
  if (fVar3 < 0.0) {
    fVar3 = 0.0 - fVar3;
    t = 0.0 - t;
  }
  if (fVar3 < 0.99999) {
    fVar1 = (float10)FUN_00152c40(fVar3);
    fVar2 = (float10)invsqrt(1.0 - fVar3 * fVar3);
    sin((float)fVar1 * fVar4);
    fVar4 = (float)(extraout_ST0 * (float10)(float)fVar2);
    sin((float)fVar1 * t);
    t = (float)(extraout_ST0_00 * (float10)(float)fVar2);
  }
  outQ->x = q1->x * fVar4 + q2->x * t;
  outQ->y = q2->y * t + q1->y * fVar4;
  outQ->z = q2->z * t + q1->z * fVar4;
  outQ->w = q2->w * t + q1->w * fVar4;
  return;
}




void vec3::Copy1Into2(vec3 *from,vec3 *to)

{
  if (from != to) {
    to->x = from->x;
    to->y = from->y;
    to->z = from->z;
  }
  return;
}




void FUN_00155d20(D3DXMATRIX *param_1,uint32_t param_2)

{
  Graphics::SomeMatrices = (SomeMatrices *)&param_1->field1;
  Graphics::SomeMatricesSize = param_2;
  Graphics::SomeMatricesAlt = param_1;
  return;
}



// WARNING: This is an inlined function


void FUN_00156010(astruct_24 *param_1,int param_2,uint index,D3DXMATRIX param_4)

{
  int i;
  float *puVar1;
  
  puVar1 = (float *)(index * 0x40 + param_2 + 4 + param_1->field12_0xc);
                    // Copy the matrix into puVar1
  for (i = 0x10; i != 0; i = i + -1) {
    *puVar1 = *(float *)param_4.m[0][0];
    param_4.m[0][0] = (float)(float *)((int)param_4.m[0][0] + 4);
    puVar1 = puVar1 + 1;
  }
                    // Set dirty byte
  *(undefined1 *)(param_1->field45_0x30 * 0x40 + param_2 + index + 4 + param_1->field12_0xc) = 1;
  return;
}




uint stackPushProjMatrix(void)

{
  int iVar1;
  DisplayMatrices *pDVar2;
  float *pfVar3;
  
  pDVar2 = &Graphics::DisplayMatrices + Graphics::DisplayMatrixIndex;
  pfVar3 = (float *)(&DAT_00439374 + Graphics::DisplayMatrixIndex * 0xc4);
  for (iVar1 = 0x31; iVar1 != 0; iVar1 = iVar1 + -1) {
    *pfVar3 = (pDVar2->projMatrix).m[0][0];
    pDVar2 = (DisplayMatrices *)((int)&pDVar2->projMatrix + 4);
    pfVar3 = pfVar3 + 1;
  }
  Graphics::DisplayMatrixIndex = Graphics::DisplayMatrixIndex + 1;
  return Graphics::DisplayMatrixIndex;
}




void FUN_00158f20(vec3 *param_1)

{
  uint uVar1;
  uint uVar2;
  DirectXShaderConstant *pDVar3;
  int iVar4;
  int iVar5;
  uint64_t uVar6;
  int local_70;
  vec3 v;
  DirectXShaderConstant DStack_60;
  undefined1 local_50 [4];
  undefined4 local_4c [3];
  undefined1 auStack_40 [64];
  
  if ((Graphics::SomeFlag1) || (param_1 != (vec3 *)0x0)) {
    DirectXShaderConstant::write(&DStack_60,0.0,0.0,0.0,1.0);
    D3D8::D3DDevice_SetVertexShaderConstant1(0xbf,&DStack_60);
    D3D8::D3DDevice_SetVertexShaderConstant1(0xbe,(DirectXShaderConstant *)&Graphics::RoomLighting);
    ModelInstance::BinaryEntry::getPtr(0x443998,&local_70);
    if (local_70 != 0) {
      iVar4 = 0xbd;
      do {
        if (*(int *)(local_70 + 8) != 0) {
          D3D8::D3DDevice_SetVertexShaderConstant1(iVar4,(DirectXShaderConstant *)(local_70 + 0xc));
          uVar2 = *(uint *)(local_70 + 8) & 3;
          iVar5 = iVar4 + -1;
          if (uVar2 == 1) {
            v.x = *(float *)(local_70 + 0x1c) * -1.0;
            v.y = *(float *)(local_70 + 0x20) * -1.0;
            v.z = *(float *)(local_70 + 0x24) * -1.0;
            if (Graphics::SomeFlag1 == false) {
              D3DX8::D3DXVec3TransformNormal
                        ((D3DXVECTOR3 *)&v,(D3DXVECTOR3 *)&v,(D3DXVECTOR3 *)param_1);
              D3DX8::D3DXVec3Normalize(&v,&v);
            }
LAB_001590ea:
            pDVar3 = (DirectXShaderConstant *)&v;
LAB_001590ee:
            D3D8::D3DDevice_SetVertexShaderConstant1(iVar5,pDVar3);
            iVar5 = iVar5 + -1;
          }
          else {
            if (uVar2 == 2) {
              if (Graphics::SomeFlag1 == false) {
                D3DX8::D3DXVec3TransformCoord
                          ((D3DXVECTOR3 *)&v,(D3DXVECTOR3 *)(local_70 + 0x28),(D3DXVECTOR3 *)param_1
                          );
                goto LAB_001590ea;
              }
              pDVar3 = (DirectXShaderConstant *)(local_70 + 0x28);
              goto LAB_001590ee;
            }
            if (uVar2 == 3) {
              if (Graphics::SomeFlag1 == false) {
                D3DX8::D3DXVec3TransformCoord
                          ((D3DXVECTOR3 *)&v,(D3DXVECTOR3 *)(local_70 + 0x28),(D3DXVECTOR3 *)param_1
                          );
                pDVar3 = (DirectXShaderConstant *)&v;
              }
              else {
                pDVar3 = (DirectXShaderConstant *)(local_70 + 0x28);
              }
              D3D8::D3DDevice_SetVertexShaderConstant1(iVar5,pDVar3);
              v.x = *(float *)(local_70 + 0x1c) * -1.0;
              v.y = *(float *)(local_70 + 0x20) * -1.0;
              v.z = *(float *)(local_70 + 0x24) * -1.0;
              if (Graphics::SomeFlag1 == false) {
                D3DX8::D3DXVec3TransformNormal
                          ((D3DXVECTOR3 *)&v,(D3DXVECTOR3 *)&v,(D3DXVECTOR3 *)param_1);
                D3DX8::D3DXVec3Normalize(&v,&v);
              }
              D3D8::D3DDevice_SetVertexShaderConstant1(iVar4 + -2,(DirectXShaderConstant *)&v);
              iVar5 = iVar4 + -3;
              pDVar3 = (DirectXShaderConstant *)(local_70 + 0x40);
              goto LAB_001590ee;
            }
          }
          iVar4 = iVar5;
          if ((*(byte *)(local_70 + 8) & 0xc) != 0) {
            D3D8::D3DDevice_SetVertexShaderConstant1
                      (iVar4,(DirectXShaderConstant *)(local_70 + 0x34));
            iVar4 = iVar4 + -1;
          }
        }
        ModelInstance::BinaryEntry::getPtr(local_70,&local_70);
      } while (local_70 != 0);
    }
    uVar2 = 0;
    ModelInstance::BinaryEntry::getPtr(0x443998,&local_70);
    iVar4 = local_70;
    while ((iVar4 != 0 && ((ushort)uVar2 < 4))) {
      local_70 = iVar4;
      if (*(int *)(iVar4 + 8) == 1) {
        uVar1 = uVar2 & 0xffff;
        iVar5 = uVar1 * 0x14;
        *(undefined4 *)(local_50 + iVar5 + 4) = *(undefined4 *)(iVar4 + 0x1c);
        local_4c[uVar1 * 5 + 1] = *(undefined4 *)(iVar4 + 0x20);
        local_4c[uVar1 * 5 + 2] = *(undefined4 *)(iVar4 + 0x24);
        uVar6 = float10::to_uint64_t((float10)*(float *)(iVar4 + 0xc) * (float10)255.0);
        local_50[iVar5] = (char)uVar6;
        uVar6 = float10::to_uint64_t((float10)*(float *)(iVar4 + 0x10) * (float10)255.0);
        local_50[iVar5 + 1] = (char)uVar6;
        uVar6 = float10::to_uint64_t((float10)*(float *)(iVar4 + 0x14) * (float10)255.0);
        local_50[iVar5 + 2] = (char)uVar6;
        uVar6 = float10::to_uint64_t((float10)*(float *)(iVar4 + 0x18) * (float10)255.0);
        local_50[iVar5 + 3] = (char)uVar6;
        auStack_40[iVar5] = 1;
        auStack_40[iVar5 + 1] = 1;
        uVar2 = uVar2 + 1;
      }
      ModelInstance::BinaryEntry::getPtr(iVar4,&local_70);
      iVar4 = local_70;
    }
    FUN_001564f0(local_50,uVar2);
    FUN_0015aca0(Graphics::SomeFlag1);
  }
  return;
}




BOOL Math::SpheresAreColliding(vec3 *p1,float radius1,vec3 *p2,float radius2)

{
  float dx;
  float dy;
  float dz;
  
  dx = p1->x - p2->x;
  dz = p1->z - p2->z;
  dy = p1->y - p2->y;
  if ((radius1 + radius2) * (radius1 + radius2) < dx * dx + dz * dz + dy * dy) {
                    // Sum of radii < distance between
                    // -> they aren't close enough
                    // -> They aren't colliding
    return 0;
  }
  return 1;
}




void Maths::RotateMatrixAroundAxis(D3DXMATRIX *this,float angle,char axis)

{
  switch(axis) {
  case 'X':
  case 'x':
    D3DX8::D3DXMatrixRotationX(this,angle);
    return;
  case 'Y':
  case 'y':
    D3DX8::D3DXMatrixRotationY(this,angle);
    return;
  case 'Z':
  case 'z':
    D3DX8::D3DXMatrixRotationZ(this,angle);
  }
  return;
}




float10 FUN_00166b9d(byte *param_1)

{
  byte bVar1;
  uint uVar2;
  byte *pbVar3;
  int iVar4;
  undefined1 local_1c [24];
  
  while( true ) {
    if (DAT_00338188 < 2) {
      uVar2 = (byte)PTR_DAT_00338180[(uint)*param_1 * 2] & 8;
    }
    else {
      uVar2 = FUN_0016ae1f((uint)*param_1,8);
    }
    if (uVar2 == 0) break;
    param_1 = param_1 + 1;
  }
  pbVar3 = param_1;
  do {
    bVar1 = *pbVar3;
    pbVar3 = pbVar3 + 1;
  } while (bVar1 != 0);
  iVar4 = FUN_0016ad9a(local_1c,param_1,(int)pbVar3 - (int)(param_1 + 1),0,0);
  return (float10)*(double *)(iVar4 + 0x10);
}




uint64_t float10::to_uint64_t(float10 param_1)

{
  ulonglong uVar1;
  uint uVar2;
  float fVar3;
  uint local_20;
  undefined4 uStack_1c;
  
  uVar1 = (ulonglong)ROUND(param_1);
  local_20 = (uint)uVar1;
  uStack_1c = (float)(uVar1 >> 32);
  fVar3 = (float)param_1;
  if ((local_20 != 0) || (fVar3 = uStack_1c, (uVar1 & 0x7fffffff00000000) != 0)) {
    if ((int)fVar3 < 0) {
      uVar1 = uVar1 + (0x80000000 < (uint)-(float)(param_1 - (float10)(longlong)uVar1));
    }
    else {
      uVar2 = (uint)(0x80000000 < (uint)(float)(param_1 - (float10)(longlong)uVar1));
      uVar1 = CONCAT44((int)uStack_1c - (uint)(local_20 < uVar2),local_20 - uVar2);
    }
  }
  return uVar1;
}




float10 FUN_0016751d(int param_1,uint param_2)

{
  uint in_EAX;
  bool in_ZF;
  short in_FPUControlWord;
  float10 in_ST0;
  float10 extraout_ST0;
  float10 fVar1;
  
  if (in_ZF) {
    if (((in_EAX & 0xfffff) != 0) || (fVar1 = _DAT_003381b8, param_1 != 0)) {
      fVar1 = (float10)FUN_0016b78c();
    }
LAB_001675ac:
    if (DAT_004dd0d0 == 0) {
      fVar1 = (float10)__startOneArgErrorHandling();
      return fVar1;
    }
  }
  else {
    if (in_FPUControlWord != 0x27f) {
      in_EAX = FUN_0016b775();
      in_ST0 = extraout_ST0;
    }
    if (in_EAX < 0x3ff00000) {
      fVar1 = (float10)fpatan(SQRT(((float10)1 - in_ST0) * ((float10)1 + in_ST0)),in_ST0);
    }
    else {
      fVar1 = _DAT_003381b8;
      if ((0x3ff00000 < in_EAX) || ((param_2 & 0xfffff) != 0 || param_1 != 0)) goto LAB_001675ac;
      if ((param_2 & 0x80000000) == 0) {
        fVar1 = (float10)0;
      }
      else {
        fVar1 = (float10)3.141592653589793;
      }
    }
    if (DAT_004dd0d0 == 0) {
      fVar1 = (float10)__math_exit();
      return fVar1;
    }
  }
  return fVar1;
}



// Library Function - Single Match
//  ?_JumpToContinuation@@YGXPAXPAUEHRegistrationNode@@@Z
// 
// Library: Visual Studio 2003 Release


float10 FUN_001686a8(double param_1)

{
  return (float10)ROUND(param_1);
}



// Library Function - Single Match
//  __set_exp
// 
// Libraries: Visual Studio 2003 Release, Visual Studio 2005 Release


float10 __set_exp(undefined8 param_1,short param_2)

{
  undefined8 local_c;
  
  local_c = (double)CONCAT26((param_2 + 0x3fe) * 0x10 | param_1._6_2_ & 0x800f,(undefined6)param_1);
  return (float10)local_c;
}



// Library Function - Single Match
//  __sptype
// 
// Library: Visual Studio 2003 Release


float10 FUN_0016873e(uint param_1,uint param_2,int *param_3)

{
  bool bVar1;
  int iVar2;
  int extraout_EDX;
  float10 fVar3;
  
  if ((double)CONCAT17(param_2._3_1_,CONCAT16(param_2._2_1_,CONCAT24((ushort)param_2,param_1))) ==
      0.0) {
    fVar3 = (float10)0;
    iVar2 = 0;
  }
  else if (((param_2 & 0x7ff00000) == 0) && (((param_2 & 0xfffff) != 0 || (param_1 != 0)))) {
    if (0.0 <= (double)CONCAT17(param_2._3_1_,
                                CONCAT16(param_2._2_1_,CONCAT24((ushort)param_2,param_1)))) {
      bVar1 = false;
    }
    else {
      bVar1 = true;
    }
    while ((param_2._2_1_ & 0x10) == 0) {
      iVar2 = CONCAT13(param_2._3_1_,CONCAT12(param_2._2_1_,(ushort)param_2)) << 1;
      param_2._0_2_ = (ushort)iVar2;
      param_2._2_1_ = (byte)((uint)iVar2 >> 0x10);
      param_2._3_1_ = (byte)((uint)iVar2 >> 0x18);
      if ((param_1 & 0x80000000) != 0) {
        param_2._0_2_ = (ushort)param_2 | 1;
      }
      param_1 = param_1 << 1;
    }
    if (bVar1) {
      param_2._3_1_ = param_2._3_1_ | 0x80;
    }
    fVar3 = (float10)__set_exp(CONCAT17(param_2._3_1_,
                                        CONCAT16(param_2._2_1_,CONCAT24((ushort)param_2,param_1))) &
                               0xffefffffffffffff,0);
    iVar2 = extraout_EDX;
  }
  else {
    fVar3 = (float10)__set_exp(CONCAT17(param_2._3_1_,
                                        CONCAT16(param_2._2_1_,CONCAT24((ushort)param_2,param_1))),0
                              );
    iVar2 = ((param_2 >> 0x10 & 0x7ff0) >> 4) - 0x3fe;
  }
  *param_3 = iVar2;
  return fVar3;
}




void __fastcall __trandisp1(undefined4 param_1,int param_2)

{
  float10 fVar1;
  byte bVar2;
  undefined2 uVar3;
  int unaff_EBP;
  float10 in_ST0;
  
  if (*(char *)(param_2 + 0xe) == '\x05') {
    uVar3 = (undefined2)
            CONCAT31((uint3)((byte)((ushort)*(undefined2 *)(unaff_EBP + -0xa4) >> 8) & 0xfe | 2),
                     0x3f);
  }
  else {
    uVar3 = 0x133f;
  }
  *(undefined2 *)(unaff_EBP + -0xa2) = uVar3;
  fVar1 = (float10)0;
  *(int *)(unaff_EBP + -0x94) = param_2;
  *(ushort *)(unaff_EBP + -0xa0) =
       (ushort)NAN(in_ST0) << 8 | (ushort)(in_ST0 < fVar1) << 9 | (ushort)(in_ST0 != fVar1) << 10 |
       (ushort)(in_ST0 == fVar1) << 0xe;
  *(undefined1 *)(unaff_EBP + -0x90) = 0;
  bVar2 = (char)(*(char *)(unaff_EBP + -0x9f) << 1) >> 1;
                    // WARNING: Could not recover jumptable at 0x0016b5a5. Too many branches
                    // WARNING: Treating indirect jump as call
  (**(code **)(param_2 + (char)(&DAT_003381d4)[(byte)((bVar2 & 7) << 1 | (char)bVar2 < '\0')] + 0x10
              ))();
  return;
}



// Library Function - Single Match
//  __trandisp2
// 
// Libraries: Visual Studio 1998, Visual Studio 2003, Visual Studio 2005, Visual Studio 2008


void __fastcall __trandisp2(undefined4 param_1,int param_2)

{
  float10 fVar1;
  char cVar2;
  byte bVar3;
  undefined2 uVar4;
  int unaff_EBP;
  float10 in_ST0;
  float10 in_ST1;
  
  if (*(char *)(param_2 + 0xe) == '\x05') {
    uVar4 = (undefined2)
            CONCAT31((uint3)((byte)((ushort)*(undefined2 *)(unaff_EBP + -0xa4) >> 8) & 0xfe | 2),
                     0x3f);
  }
  else {
    uVar4 = 0x133f;
  }
  *(undefined2 *)(unaff_EBP + -0xa2) = uVar4;
  fVar1 = (float10)0;
  *(int *)(unaff_EBP + -0x94) = param_2;
  *(ushort *)(unaff_EBP + -0xa0) =
       (ushort)NAN(in_ST0) << 8 | (ushort)(in_ST0 < fVar1) << 9 | (ushort)(in_ST0 != fVar1) << 10 |
       (ushort)(in_ST0 == fVar1) << 0xe;
  *(undefined1 *)(unaff_EBP + -0x90) = 0;
  fVar1 = (float10)0;
  *(ushort *)(unaff_EBP + -0xa0) =
       (ushort)NAN(in_ST1) << 8 | (ushort)(in_ST1 < fVar1) << 9 | (ushort)(in_ST1 != fVar1) << 10 |
       (ushort)(in_ST1 == fVar1) << 0xe;
  bVar3 = (char)(*(char *)(unaff_EBP + -0x9f) << 1) >> 1;
  cVar2 = (char)(*(char *)(unaff_EBP + -0x9f) << 1) >> 1;
                    // WARNING: Could not recover jumptable at 0x0016b631. Too many branches
                    // WARNING: Treating indirect jump as call
  (**(code **)(param_2 + (char)((&DAT_003381d4)[(byte)(cVar2 << 1 | cVar2 < '\0') & 0xf] |
                               (&DAT_003381d4)[(byte)((bVar3 & 7) << 1 | (char)bVar3 < '\0')] << 2)
              + 0x10))();
  return;
}



float10 __fastcall
FUN_0016b70c(undefined4 param_1,undefined4 param_2,undefined2 param_3,undefined4 param_4,
            undefined4 param_5,undefined4 param_6,undefined4 param_7,undefined4 param_8)

{
  float10 in_ST0;
  undefined1 local_24 [8];
  undefined4 uStack_1c;
  undefined4 uStack_18;
  undefined4 local_14;
  undefined4 local_10;
  double dStack_c;
  
  local_14 = param_7;
  local_10 = param_8;
  dStack_c = (double)in_ST0;
  uStack_1c = param_5;
  uStack_18 = param_6;
  FUN_0016f095(param_2,local_24,&param_3);
  return (float10)dStack_c;
}



// Library Function - Single Match
//  __startOneArgErrorHandling
// 
// Library: Visual Studio

float10 __fastcall
__startOneArgErrorHandling
          (undefined4 param_1,undefined4 param_2,undefined2 param_3,undefined4 param_4,
          undefined4 param_5,undefined4 param_6)

{
  float10 in_ST0;
  undefined1 local_24 [8];
  undefined4 local_1c;
  undefined4 local_18;
  double local_c;
  
  local_c = (double)in_ST0;
  local_1c = param_5;
  local_18 = param_6;
  FUN_0016f095(param_2,local_24,&param_3);
  return (float10)local_c;
}




void __ctrandisp2(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  __fload(param_1,param_2);
  __fload(param_3,param_4);
  __trandisp2();
  FUN_00170523();
  return;
}




void __ctrandisp1(undefined4 param_1,undefined4 param_2)

{
  __fload(param_1,param_2);
  __trandisp1();
  FUN_00170523();
  return;
}



// Library Function - Single Match
//  __fload
// 
// Libraries: Visual Studio 1998, Visual Studio 2003, Visual Studio 2005, Visual Studio 2008


float10 __fload(uint param_1,int param_2)

{
  float10 fVar1;
  
  if ((param_2._2_2_ & 0x7ff0) == 0x7ff0) {
    fVar1 = (float10)CONCAT28(param_2._2_2_ | 0x7fff,
                              CONCAT44(param_2 << 0xb | param_1 >> 0x15,param_1));
  }
  else {
    fVar1 = (float10)(double)CONCAT26(param_2._2_2_,CONCAT24((undefined2)param_2,param_1));
  }
  return fVar1;
}




void getfovfy(void)

{
  float10 in_ST0;
  
  FUN_0016b7e8(SUB84((double)in_ST0,0),(uint)((ulonglong)(double)in_ST0 >> 0x20));
  FUN_001706fd();
  return;
}



// WARNING: Globals starting with '_' overlap smaller symbols at the same address


float10 FUN_001706fd(int param_1,uint param_2)

{
  uint in_EAX;
  bool in_ZF;
  short in_FPUControlWord;
  float10 in_ST0;
  float10 extraout_ST0;
  float10 fVar1;
  
  if (in_ZF) {
    if (((in_EAX & 0xfffff) != 0) || (fVar1 = _DAT_003381b8, param_1 != 0)) {
      fVar1 = (float10)FUN_0016b78c();
    }
LAB_0017078c:
    if (DAT_004dd0d0 == 0) {
      fVar1 = (float10)__startOneArgErrorHandling();
      return fVar1;
    }
  }
  else {
    if (in_FPUControlWord != 0x27f) {
      in_EAX = FUN_0016b775();
      in_ST0 = extraout_ST0;
    }
    if (in_EAX < 0x3ff00000) {
      fVar1 = (float10)fpatan(in_ST0,SQRT(((float10)1 - in_ST0) * ((float10)1 + in_ST0)));
    }
    else {
      fVar1 = _DAT_003381b8;
      if ((0x3ff00000 < in_EAX) || ((param_2 & 0xfffff) != 0 || param_1 != 0)) goto LAB_0017078c;
      fVar1 = _DAT_003381c2;
      if ((param_2 & 0x80000000) != 0) {
        fVar1 = -_DAT_003381c2;
      }
    }
    if (DAT_004dd0d0 == 0) {
      fVar1 = (float10)__math_exit();
      return fVar1;
    }
  }
  return fVar1;
}




float10 FUN_00177cc0(float param_1)

{
  float fVar1;
  
  fVar1 = (float)(-0x41800000 - (int)param_1 >> 1);
  fVar1 = ABS(fVar1 * (_DAT_0032cfc4 - _DAT_0032cfc0 * param_1 * fVar1 * fVar1));
  return ((float10)3.0 - (float10)fVar1 * (float10)fVar1 * (float10)param_1) * (float10)fVar1 *
         (float10)0.5;
}




float10 FUN_001782d0(float param_1)

{
  float10 fVar1;
  float10 fVar2;
  float10 fVar3;
  
  fVar1 = ROUND((float10)1.4426950408889634 * (float10)param_1);
  fVar2 = (float10)1.4426950408889634 * (float10)param_1 - fVar1;
  fVar3 = (float10)f2xm1(ABS(fVar2));
  fVar3 = (float10)1 + fVar3;
  if (fVar2 < (float10)0) {
    fVar3 = (float10)1 / fVar3;
  }
  if (fVar1 != (float10)0) {
    fVar3 = (float10)fscale(fVar3,fVar1);
  }
  return fVar3;
}




float10 FUN_00178330(float param_1)

{
  float10 fVar1;
  
  fVar1 = (float10)log2((float10)param_1);
  return (float10)0.6931471805599453 * fVar1;
}




float10 __thiscall FUN_00185750(int param_1,undefined4 *param_2)

{
  float fVar1;
  int iVar2;
  float10 fVar3;
  undefined4 local_8;
  
  if (*(char *)(param_1 + 0x10) == '\0') {
    fVar3 = (float10)18.0;
    *param_2 = 0x4b;
  }
  else {
    local_8 = 0.0;
    *param_2 = 0x20;
    fVar3 = (float10)0;
    iVar2 = 0;
    do {
      if (*(char *)(iVar2 + param_1) != '\0') {
        local_8 = local_8 + 1.0;
      }
      iVar2 = iVar2 + 1;
    } while (iVar2 < 0x10);
    if (*(float *)(param_1 + 0x14) < local_8) {
      fVar3 = (float10)local_8 - (float10)*(float *)(param_1 + 0x14);
      *param_2 = 0x4a;
    }
    if ((*(float *)(param_1 + 0x14) < 2.2) &&
       (fVar1 = 2.2 - *(float *)(param_1 + 0x14), fVar3 < (float10)fVar1)) {
      *param_2 = 0x4c;
      fVar3 = (float10)fVar1;
    }
  }
  return fVar3;
}




float10 __thiscall FUN_0018b1ee(int param_1,byte *param_2,int param_3,undefined4 param_4)

{
  float10 fVar1;
  undefined4 in_stack_00000024;
  undefined4 in_stack_00000028;
  undefined4 in_stack_0000002c;
  undefined4 *in_stack_00000030;
  
  *in_stack_00000030 = 0x20;
  if (param_3 == 1) {
    fVar1 = (float10)FUN_00189723(param_2,in_stack_00000024,param_4,in_stack_00000028,
                                  in_stack_0000002c,in_stack_00000030);
  }
  else if (((param_3 == 2) || (param_3 != 3)) || ((*param_2 & 2) == 0)) {
    fVar1 = (float10)0.0;
  }
  else {
    *in_stack_00000030 = *(undefined4 *)(param_1 + 0x610);
    fVar1 = (float10)*(float *)(param_1 + 0x290);
  }
  return fVar1;
}



undefined4 __thiscall
FUN_0018b243(int param_1,undefined4 param_2,undefined1 param_3,uint param_4,byte param_5,int param_6
            )

{
  byte bVar1;
  char cVar2;
  int iVar3;
  
  iVar3 = 0;
  while( true ) {
    bVar1 = '\x01' << ((byte)iVar3 & 0x1f);
    if ((((param_5 & bVar1) != 0) &&
        (param_6 < *(int *)(param_1 + (iVar3 + 8 + (param_4 & 0xff) * 4) * 4))) &&
       (cVar2 = FUN_001897a3(param_2,param_3,param_4,bVar1,param_6), cVar2 == '\0')) break;
    iVar3 = iVar3 + 1;
    if (3 < iVar3) {
      return 1;
    }
  }
  return 0;
}




float10 __thiscall FUN_0018bf95(int param_1,undefined4 param_2,int *param_3)

{
  int *piVar1;
  undefined1 extraout_AL;
  undefined1 extraout_AL_00;
  undefined4 uVar2;
  uint uVar3;
  int iVar4;
  float10 fVar5;
  uint64_t uVar6;
  undefined1 local_14 [2];
  undefined2 uStack_12;
  undefined1 uStack_10;
  undefined1 uStack_f;
  float local_c;
  float local_8;
  
  piVar1 = param_3;
  uVar3 = 0;
  *param_3 = 0x20;
  if (*(char *)(param_1 + 0x10) == '\0') {
    iVar4 = 0;
    do {
      D3D8::D3D_KickOffAndWaitForIdle();
      local_14[iVar4] = extraout_AL_00;
      iVar4 = iVar4 + 1;
    } while (iVar4 < 3);
    do {
      fVar5 = (float10)(int)uVar3;
      if ((int)uVar3 < 0) {
        fVar5 = fVar5 + (float10)4.2949673e+09;
      }
      param_3 = (int *)uVar3;
      uVar6 = float10::to_uint64_t(fVar5 + (float10)*(float *)(param_1 + 0x14));
      uVar2 = (undefined4)uVar6;
      iVar4 = FUN_0018be49(param_2,CONCAT22(uStack_12,CONCAT11(local_14[1],local_14[0])),uVar2);
    } while ((((iVar4 == 0) ||
              (iVar4 = FUN_0018bea8(param_2,CONCAT13(uStack_10,CONCAT21(uStack_12,local_14[1])),
                                    uVar2), iVar4 == 0)) ||
             (iVar4 = FUN_0018bf0b(param_2,CONCAT13(uStack_f,CONCAT12(uStack_10,uStack_12)),uVar2),
             iVar4 == 0)) && (uVar3 = uVar3 + 1, uVar3 < 5));
    fVar5 = (float10)(int)uVar3;
    if ((int)uVar3 < 0) {
      fVar5 = fVar5 + (float10)4.2949673e+09;
    }
  }
  else {
    do {
      D3D8::D3D_KickOffAndWaitForIdle();
      local_14[uVar3] = extraout_AL;
      uVar3 = uVar3 + 1;
    } while ((int)uVar3 < 3);
    param_3 = (int *)0x20;
    fVar5 = (float10)FUN_0018b9c9(param_2,CONCAT22(uStack_12,CONCAT11(local_14[1],local_14[0])),
                                  *(undefined4 *)(param_1 + 0x14),&param_3);
    local_c = (float)fVar5;
    local_8 = (float)fVar5;
    *piVar1 = (int)param_3;
    fVar5 = (float10)FUN_0018ba2d(param_2,CONCAT13(uStack_10,CONCAT21(uStack_12,local_14[1])),
                                  *(undefined4 *)(param_1 + 0x14),&param_3);
    if (((float10)local_c < fVar5) || (*piVar1 == 0x20)) {
      local_8 = (float)fVar5;
      *piVar1 = (int)param_3;
    }
    fVar5 = (float10)FUN_0018ba95(param_2,CONCAT13(uStack_f,CONCAT12(uStack_10,uStack_12)),
                                  *(undefined4 *)(param_1 + 0x14),&param_3);
    if (((float10)local_8 < fVar5) || (*piVar1 == 0x20)) {
      local_8 = (float)fVar5;
      *piVar1 = (int)param_3;
    }
    fVar5 = (float10)local_8;
  }
  return fVar5;
}



// WARNING: Removing unreachable block (ram,0x0018c195)

undefined4 __thiscall

float10 __fastcall FUN_001c4fe7(int param_1)

{
  return (float10)*(ushort *)(&LAB_001c557a + (param_1 / -0x32) * 4) * (float10)0.0001;
}




float10 FUN_001c8d5e(float *param_1)

{
  return SQRT((float10)param_1[2] * (float10)param_1[2] +
              (float10)param_1[1] * (float10)param_1[1] + (float10)*param_1 * (float10)*param_1);
}




float10 FUN_001ce3ff(int param_1)

{
  float10 fVar1;
  float10 fVar2;
  
  fVar1 = ROUND((float10)3.321928 * (float10)((float)param_1 * 0.0005));
  fVar2 = (float10)fscale((float10)1,fVar1);
  fVar1 = (float10)f2xm1((float10)3.321928 * (float10)((float)param_1 * 0.0005) -
                         (float10)(float)fVar1);
  return (float10)(float)((fVar1 + (float10)1.0) * fVar2);
}




float10 FUN_001e8854(int param_1)

{
  float10 fVar1;
  
  if (param_1 < 0x12) {
    if (param_1 < 0) {
      fVar1 = (float10)0.38294387 / (float10)(1 << ((char)(-param_1 >> 3) + 1U & 0x1f));
    }
    else {
      fVar1 = (float10)(1 << ((char)(param_1 >> 3) + 1U & 0x1f)) * (float10)0.8694398;
    }
  }
  else if (param_1 < 0x92) {
    fVar1 = (float10)*(float *)(&DAT_001f7b68 + param_1 * 4) *
            (float10)*(float *)(&DAT_001f7db0 + (param_1 >> 3) * 4);
  }
  else {
    fVar1 = (float10)thunk_FUN_00167cba();
  }
  return fVar1;
}




float10 FUN_001e88c5(float *param_1,int param_2,int param_3)

{
  int iVar1;
  
  iVar1 = *(int *)(param_2 + 0x34) - *(int *)(*(int *)(param_2 + 4) + param_3 * 4);
  if (0x47 < iVar1) {
    iVar1 = 0x47;
  }
  return ((float10)*(float *)(&DAT_001f79c8 + iVar1 * 4) /
         (float10)(1 << ((byte)(iVar1 >> 2) & 0x1f))) * (float10)*param_1;
}




float SeedRandAndReturn(void)

{
  runtime::rand = runtime::rand * 0x19660d + 0x3c6ef35f;
  return (float)(runtime::rand & 0x7fffff | 0x3f800000);
}



// WARNING: Unknown calling convention


uint RandRange(void)

{
  float fVar1;
  float fVar2;
  
                    // Randrange into xmm0
  fVar2 = (float)(int)NumGhoulieBoxNames;
  fVar1 = SeedRandAndReturn();
  return (int)(fVar2 * (fVar1 - 1.0));
}



// WARNING: Unable to track spacebase fully for stack
// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


