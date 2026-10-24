/* avatar.c - Avatar base type and parameters */
#include "avatar.h"

void avatar::onAnimEvent(actor *av,Avatar_AnimationEventMessage *msg)

{
  float fVar1;
  byte bVar2;
  AnimEventEntry *pAVar3;
  bool bVar4;
  BOOL BVar5;
  undefined4 uVar6;
  undefined3 extraout_var;
  int iVar7;
  float fVar8;
  undefined4 uVar9;
  vec3 local_c;
  AnimEventResource *event;
  
  pAVar3 = msg->animEvent->events;
  switch(pAVar3->animEventType) {
  case DisableVolume:
    if (msg->field4_0x10 != Null) {
      updateBlendTarget((short)pAVar3->field7_0x10,(uint)pAVar3->field8_0x14,&av->avatar);
      return;
    }
    FUN_000426b0();
    return;
  case FadeOutStream:
  case FootDown:
  case Invulnerability:
  case LookAtDisable:
  case VelocityBoost:
  case VelocityBoostToYaw:
  case WeaponAttackVolume1:
  case SetActorFlag:
  case BodyImpactFloor:
  case BodyImpactWall:
  case CreateAndAttachProjectile:
  case Breath:
  case DeleteWeapon:
  case CreateAndAttachWeapon:
  case WeaponSwing:
  case InsertFright:
  case ActorLimbChange:
  case ActorProjectileThrow:
  case ActorWeaponPlace:
  case PinataTime_SetFlag:
  case PinataTime_SetFlagDuration:
  case KickedUp:
  case TriggerWeaponCallout:
  case TriggerProjectileCallout:
  case CreateAndAttachProjectileToLocator:
  case DisableInput:
    break;
  case FxNextGen_CreateEmitter:
  case FxNextGen_CreateEmitterVolumeMask:
    if ((msg->field4_0x10 == Null) &&
       (BVar5 = Random::thresholdCheck(&runtime::rand,pAVar3->field121_0xa0), BVar5 != 0)) {
      int32_t_00506914 = pAVar3->field117_0x90;
      _DAT_0050690c = 0;
      uVar6 = pAVar3->field120_0x9c;
      uVar9 = pAVar3->field119_0x98;
LAB_0003a4d7:
      fxAvatar = &av->avatar;
      uVar6 = FUN_0003a8b0(&DAT_0050690c,uVar9,uVar6);
      iVar7 = spawnFxAndAID(&pAVar3->field7_0x10,uVar6);
      if (iVar7 != 0) {
        FUN_0003a9a0(av);
        FUN_0013e750();
      }
      if (pAVar3->field126_0xa8 != '\0') {
        FUN_00041d00();
        return;
      }
    }
    break;
  case FxNextGen_CreateEmitterLocatorId:
    if ((msg->field4_0x10 == Null) &&
       (BVar5 = Random::thresholdCheck(&runtime::rand,pAVar3->field121_0xa0), BVar5 != 0)) {
      _DAT_0050690c = 1;
      int32_t_00506914 = CONCAT22(int32_t_00506914._2_2_,(short)pAVar3->field117_0x90);
      uVar6 = pAVar3->field120_0x9c;
      uVar9 = pAVar3->field119_0x98;
      goto LAB_0003a4d7;
    }
    break;
  case InsertScare:
    if (msg->field4_0x10 == Null) {
      FUN_0013b3a0(av->mind,av->body,0,0);
      return;
    }
    break;
  case InsertCameraShake:
    if (pAVar3->field16_0x28 == 0) {
      fVar8 = (av->avatar).scale.z;
    }
    else {
      fVar8 = (av->avatar).uniformScale * (av->avatar).scale.x;
    }
    uVar6 = *(undefined4 *)&pAVar3->field9_0x18;
    fVar1 = pAVar3->field8_0x14;
    iVar7 = FUN_000494b0(pAVar3->field7_0x10);
    *(float *)(iVar7 + 0x30) = fVar1 * fVar8;
    *(undefined4 *)(iVar7 + 0x24) = uVar6;
    if (pAVar3->field13_0x1c != 0) {
      getWorldPosition(&av->avatar,&local_c);
      *(float *)(iVar7 + 8) = local_c.x;
      *(float *)(iVar7 + 0xc) = local_c.y;
      *(float *)(iVar7 + 0x10) = local_c.z;
      *(undefined1 *)(iVar7 + 0x82) = 1;
      fVar1 = pAVar3->field15_0x24;
      *(float *)(iVar7 + 0x14) = pAVar3->field14_0x20 * fVar8;
      *(float *)(iVar7 + 0x18) = fVar1 * fVar8;
      return;
    }
    break;
  case PlayCue_Impact:
  case PlayCue_Looping:
  case PlayCue_Vocal:
  case PlayCue_Vocal2:
  case PlayCue_FootStep:
switchD_0003a3a3_caseD_1c:
    FUN_0003a830(pAVar3,&av->avatar);
    return;
  case KillCue_Looping:
    FUN_00041e10();
    return;
  case ExecAsset:
    spawnFxAndAID(&pAVar3->field7_0x10,0);
    return;
  case InsertMotionBlur:
    if (msg->field4_0x10 == Null) {
      *(undefined4 *)&(av->avatar).field_0x1dc = 0;
      return;
    }
    if (msg->field4_0x10 == General_Deactivate) {
      if (pAVar3->field8_0x14 != 0.0) {
        bVar2 = pAVar3->field9_0x18;
        FUN_00040d90((uint)bVar2);
        FUN_00040d50(av,(uint)bVar2);
      }
      FUN_0013b1b0(pAVar3->field7_0x10,&(av->avatar).field_0x1dc);
      if (pAVar3->field8_0x14 != 0.0) {
        FUN_00040d50(av,(uint)(byte)pAVar3->field9_0x18);
        return;
      }
    }
    break;
  case FxNextGen_CreateEmitterJointId:
    if ((msg->field4_0x10 == Null) &&
       (BVar5 = Random::thresholdCheck(&runtime::rand,pAVar3->field121_0xa0), BVar5 != 0)) {
      int32_t_00506914 = pAVar3->field117_0x90;
      _DAT_0050690c = 2;
      uVar6 = pAVar3->field120_0x9c;
      uVar9 = pAVar3->field119_0x98;
      goto LAB_0003a4d7;
    }
    break;
  case InsertRumble:
    if (msg->field4_0x10 == Null) {
      if (pAVar3->field117_0x90 == 0) {
        fVar8 = (av->avatar).scale.z;
      }
      else {
        fVar8 = (av->avatar).uniformScale * (av->avatar).scale.x;
      }
      if (pAVar3->field7_0x10 == 0x5f646961) {
        getWorldPosition(&av->avatar,&local_c);
        FUN_000fb120(&local_c,fVar8,(char *)&pAVar3->field7_0x10);
        return;
      }
    }
    break;
  case InsertFxCustom:
    if (pAVar3->field7_0x10 == 0x5f646961) {
      CreateFxFromAID((astruct_38 *)av,(char *)&pAVar3->field7_0x10);
      return;
    }
    break;
  case PlayCue_VocalIfNotActive:
    bVar4 = FUN_00041c80(1,&av->avatar);
    if (CONCAT31(extraout_var,bVar4) == 0) goto switchD_0003a3a3_caseD_1c;
    break;
  case PlayCue_MultiChannel:
    iVar7 = FUN_00038050();
    if (iVar7 != 0) {
      Audio::PlaySoundWithFlags(&pAVar3->field8_0x14,1);
    }
    break;
  case SetSwitch:
    FUN_00040d50(av,(uint)(byte)pAVar3->field7_0x10);
    return;
  default:
    goto switchD_0003a3a3_default;
  }
switchD_0003a3a3_default:
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void avatar::activateAnimation(avatar *av,AnimEventMapping *param_2)

{
  AnimEventMapping *pAVar1;
  KFCParams local_b0;
  
  pAVar1 = FUN_000322a0(param_2,av->needsAnimMapping,&local_b0);
  setKFFromAnimAID(av,&local_b0,(int)*(char *)((int)&pAVar1->field7_0x114 + 3),pAVar1->animAID);
  av->needsAnimMapping = 0;
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void avatar::LoadAnimTable(avatar *avatar,char *param_2)

{
  AnimtableResource *local_4;
  
  if (avatar->animTable != (AnimtableResource *)0x0) {
    if (avatar->animTableHandled != 0) {
      Assets::DestroyAssetOrDecrement(avatar->animTable);
    }
    avatar->animTable = (AnimtableResource *)0x0;
  }
  if (*(int *)param_2 != 0x5f646961) {
    avatar->animTable = (AnimtableResource *)0x0;
    avatar->animTableHandled = 1;
    return;
  }
  Assets::GetResourceBytes(param_2,&local_4);
  if (local_4 == (AnimtableResource *)0x0) {
    runtime::ExitGame(2);
  }
  avatar->animTable = local_4;
  avatar->animTableHandled = 1;
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


AnimEventMapping * avatar::getAnimEventByName(avatar *act,char *animName,BOOL someFlag)

{
  AnimtableEntry *pAVar3;
  AnimEventMapping *pAVar4;
  char *pcVar5;
  uint uVar1;
  float numAnims;
  AnimtableResource *anim_table;
  float iVar2;
  char *name;
  
  if ((act->animTable == (AnimtableResource *)0x0) || (animName == (char *)0x0)) {
    return (AnimEventMapping *)0x0;
  }
  if (someFlag != 0) {
    _sprintf(currentAnim,"%s_[%s]",animName,someFlag);
    anim_table = act->animTable;
    pAVar3 = AnimtableResource::getEntry(anim_table,currentAnim);
    if (pAVar3 == (AnimtableEntry *)0x0) {
      pAVar4 = AnimtableResource::getEventMapping(anim_table,currentAnim);
      return pAVar4;
    }
    pAVar4 = AnimtableResource::getEventMapping(anim_table,pAVar3->field1_0x4);
    return pAVar4;
  }
  pcVar5 = _strchr(animName,0x3f);
  if (pcVar5 != (char *)0x0) {
    memcpy(currentAnim,animName,(int)pcVar5 - (int)animName);
    pcVar5 = currentAnim + ((int)pcVar5 - (int)animName);
    iVar2 = 0.0;
    do {
      numAnims = iVar2;
      *pcVar5 = '\0';
      FUN_000fbea0((float)((int)numAnims + 1),pcVar5);
      anim_table = act->animTable;
      pAVar3 = AnimtableResource::getEntry(anim_table,currentAnim);
      if (pAVar3 == (AnimtableEntry *)0x0) {
        name = currentAnim;
      }
      else {
        name = pAVar3->field1_0x4;
      }
      pAVar4 = AnimtableResource::getEventMapping(anim_table,name);
      iVar2 = (float)((int)numAnims + 1);
    } while (pAVar4 != (AnimEventMapping *)0x0);
    if (numAnims == 0.0) {
      return (AnimEventMapping *)0x0;
    }
    runtime::rand = runtime::rand * 0x19660d + 0x3c6ef35f;
    uVar1 = runtime::rand & 0x7fffff;
    *pcVar5 = '\0';
                    // Pick random animation
    FUN_000fbea0((float)((int)(((float)(uVar1 | 0x3f800000) - 1.0) * (float)(int)numAnims) + 1),
                 pcVar5);
    anim_table = act->animTable;
    pAVar3 = AnimtableResource::getEntry(anim_table,currentAnim);
    if (pAVar3 == (AnimtableEntry *)0x0) {
      pAVar4 = AnimtableResource::getEventMapping(anim_table,currentAnim);
      return pAVar4;
    }
    pAVar4 = AnimtableResource::getEventMapping(anim_table,pAVar3->field1_0x4);
    return pAVar4;
  }
  pAVar4 = AnimTableResource::getEventMappingBySomething(act->animTable,animName);
  return pAVar4;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void avatar::clearAnimation(avatar *av)

{
  Skeleton *skeleton_instance;
  Model *instance;
  
  if (av->keyframeContext != (KeyframeContext *)0x0) {
    ::KeyFrameContext::dtor(av->keyframeContext,0);
    av->keyframeContext = (KeyframeContext *)0x0;
  }
  if (av->boneList != (BoneList *)0x0) {
    if ((av->field_0x60 & 1) != 0) {
      BoneList::removeBoneById(av->boneToRemove,av->boneList2);
    }
    BoneList::dtor(av->boneList);
    av->boneList = (BoneList *)0x0;
  }
  instance = av->model;
  if (instance == (Model *)0x0) {
    skeleton_instance = (Skeleton *)0x0;
  }
  else {
    skeleton_instance = instance->skeleton;
    if (skeleton_instance == (Skeleton *)0x0) {
      skeleton_instance = instance->skeleton2;
    }
  }
                    // If no standing animation, reset the bones?
  if (skeleton_instance != (Skeleton *)0x0) {
    SkeletonInstance::resetBoneAffines(skeleton_instance);
    return;
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


KeyframeContext * avatar::getKFC(avatar *av)

{
  KeyframeContext *kfc;
  
  if (av->keyframeContext == (KeyframeContext *)0x0) {
    kfc = KeyframeContext::ctor(4);
    av->keyframeContext = kfc;
    kfc->animEventCallback = triggerAnimationEvent;
    kfc->avatar = av;
  }
  return av->keyframeContext;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


BOOL avatar::setInitialAnimation(avatar *av,char *animName)

{
  KeyframeContext *kfc;
  BOOL BVar1;
  KFCParams cfg;
  
  cfg.playbackSpeed_ = 0.0;
  cfg.someFloat = 0.0;
  cfg.MixP = 0x4d697850;
  cfg.someIdOrCount = 0x21;
  cfg.length = 0.2;
  cfg.someFloat3 = -10.0;
  cfg.someUshort = 0;
  cfg.someValue4 = 0x31;
  cfg.someFloat2 = 0.2;
  cfg.animEventAID[0] = '\0';
  cfg.someValue5 = (void *)0x0;
  cfg.animResource = (AnimResource *)0x0;
  cfg.animEvent = (AnimEventResource *)0x0;
  if (av->keyframeContext == (KeyframeContext *)0x0) {
    kfc = KeyframeContext::ctor(4);
    av->keyframeContext = kfc;
    kfc->animEventCallback = triggerAnimationEvent;
    kfc->avatar = av;
  }
  BVar1 = KeyframeContext::setFromAnimName(av->keyframeContext,0,&cfg,animName,(AnimResource *)0x0);
  return BVar1;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


uint avatar::setKFFromAnimAID(avatar *av,KFCParams *param_2,uint channelIndex,char *animAID)

{
  KeyframeContext *pKVar1;
  uint uVar2;
  
  if (av->keyframeContext == (KeyframeContext *)0x0) {
    pKVar1 = KeyframeContext::ctor(4);
    av->keyframeContext = pKVar1;
    pKVar1->animEventCallback = triggerAnimationEvent;
    pKVar1->avatar = av;
  }
  if (param_2->animResource != (AnimResource *)0x0) {
    uVar2 = KeyframeContext::setFromAnimName
                      (av->keyframeContext,channelIndex,param_2,(char *)0x0,param_2->animResource);
    return uVar2;
  }
  uVar2 = KeyframeContext::setFromAnimName
                    (av->keyframeContext,channelIndex,param_2,animAID,(AnimResource *)0x0);
  return uVar2;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void avatar::onScenePrepare(avatar *av)

{
  if (av->keyframeContext != (KeyframeContext *)0x0) {
    KeyframeContext::updateFromAvatar
              (av->keyframeContext,av->model,(uint)(av->preventAnimChannelAdvancing == 0),0.0);
  }
  if (av->keyframeContext != (KeyframeContext *)0x0) {
    KeyframeContext::updateSkeletonAndBlendTargets
              ((uint)(av->preventAnimChannelAdvancing == 0),av->keyframeContext,av->model,
               av->boneList);
  }
  updateBaseTransform(av);
  getMaxScaleFromBasis(av);
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


BOOL avatar::updateKeyframes(avatar *this,int channelIndex)

{
  AnimInstance *pAVar1;
  bool bVar2;
  
  if ((this->keyframeContext == (KeyframeContext *)0x0) ||
     (pAVar1 = this->keyframeContext->kfcAnims[channelIndex].animInstance,
     pAVar1 == (AnimInstance *)0x0)) {
    return 1;
  }
  if (pAVar1->loopMode == Mode1) {
    if (pAVar1->invDuration <= 0.0 && pAVar1->invDuration != 0.0) {
      bVar2 = 0.0 < pAVar1->t;
    }
    else {
      bVar2 = pAVar1->t < 1.0;
    }
    if (!bVar2) {
      return 1;
    }
  }
  return 0;
}




void avatar::normaliseMatrixAndPhysics(avatar *av)

{
  BoneAffineSubresourceEntry *pBVar1;
  Model *pMVar2;
  actor *paVar3;
  avatar *pAVar3;
  Skeleton *skeleton;
  uchar cVar1;
  AvatarPhysicsContext *pt;
  AvatarPhysicsContext *physCtx;
  
  physCtx = av->physicsCtx;
  if (physCtx->actor == (actor *)0x0) {
    cVar1 = physCtx->mode1;
  }
  else {
    cVar1 = physCtx->mode2;
  }
  if (cVar1 == '\x01') {
    pAVar3 = &GetPhysicsInner(av)->avatar;
    (physCtx->affine).m[0][0] = (pAVar3->drawAffine).m[0][0];
    (physCtx->affine).m[0][1] = (pAVar3->drawAffine).m[0][1];
    (physCtx->affine).m[0][2] = (pAVar3->drawAffine).m[0][2];
    (physCtx->affine).m[0][3] = (pAVar3->drawAffine).m[0][3];
    (physCtx->affine).m[1][0] = (pAVar3->drawAffine).m[1][0];
    (physCtx->affine).m[1][1] = (pAVar3->drawAffine).m[1][1];
    (physCtx->affine).m[1][2] = (pAVar3->drawAffine).m[1][2];
    (physCtx->affine).m[1][3] = (pAVar3->drawAffine).m[1][3];
    (physCtx->affine).m[2][0] = (pAVar3->drawAffine).m[2][0];
    (physCtx->affine).m[2][1] = (pAVar3->drawAffine).m[2][1];
    (physCtx->affine).m[2][2] = (pAVar3->drawAffine).m[2][2];
    (physCtx->affine).m[2][3] = (pAVar3->drawAffine).m[2][3];
  }
  else if (cVar1 == '\x02') {
    FUN_0003bab0(av,&physCtx->affine,physCtx->valueFromModelRes);
  }
  else if (cVar1 == '\x03') {
    pBVar1 = (BoneAffineSubresourceEntry *)physCtx->valueFromModelRes;
    paVar3 = GetPhysicsInner(av);
    pMVar2 = (paVar3->avatar).model;
    skeleton = pMVar2->skeleton;
    if (skeleton == (Skeleton *)0x0) {
      skeleton = pMVar2->skeleton2;
    }
    Skeleton::getBoneAndWriteAffine(skeleton,pBVar1,&(paVar3->avatar).drawAffine,&physCtx->affine);
  }
  if ((physCtx->someFlag & 1U) == 0) {
                    // Normalise knockback when flying?
    Math::NormaliseAndScale(1.0,(float *)&physCtx->affine);
  }
  Maths::InvertAffineMatrix((D3DXMATRIX *)&physCtx->affine,(D3DMATRIX *)&physCtx->xRow);
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


actor * avatar::GetPhysicsInner(avatar *param_1)

{
  avatar_0x918 pEVar1;
  int update_type;
  AvatarPhysicsContext *ptr;
  
  ptr = param_1->physicsCtx;
  if (ptr != (AvatarPhysicsContext *)0x0) {
    if (ptr->actor != (actor *)0x0) {
      update_type = 1;
      goto LAB_0003b8f2;
    }
    pEVar1 = (param_1->node0x918).prev;
    if ((pEVar1 != (avatar_0x918)0x0) && (pEVar1->prev != (avatar_0x918)0x0)) {
      update_type = 2;
      goto LAB_0003b8f2;
    }
    free(ptr);
    param_1->physicsCtx = (AvatarPhysicsContext *)0x0;
  }
  update_type = 0;
LAB_0003b8f2:
  if (update_type == 1) {
    return ptr->actor;
  }
  if (update_type != 2) {
    return (actor *)0x0;
  }
  return (actor *)ADJ((param_1->node0x918).prev);
}




AvatarPhysicsContext * avatar::getOrCreatePhysicsCtx(avatar *av)

{
  AvatarPhysicsContext *ctx;
  int iVar2;
  
  if (av->physicsCtx == (AvatarPhysicsContext *)0x0) {
    ctx = malloc_(0x6c);
    av->physicsCtx = ctx;
    if (ctx != (AvatarPhysicsContext *)0x0) {
      for (iVar2 = 0x1b; iVar2 != 0; iVar2 = iVar2 + -1) {
        ctx->mode1 = '\0';
        ctx->mode2 = '\0';
        ctx->someFlag = false;
        ctx->field_0x3 = 0;
        ctx = (AvatarPhysicsContext *)&ctx->valueFromModelRes;
      }
      ctx = av->physicsCtx;
      (ctx->affine).m[0][0] = 1.0;
      (ctx->affine).m[0][1] = 0.0;
      (ctx->affine).m[0][2] = 0.0;
      (ctx->affine).m[0][3] = 0.0;
      (ctx->affine).m[1][0] = 0.0;
      (ctx->affine).m[1][1] = 1.0;
      (ctx->affine).m[1][2] = 0.0;
      (ctx->affine).m[1][3] = 0.0;
      (ctx->affine).m[2][0] = 0.0;
      (ctx->affine).m[2][1] = 0.0;
      (ctx->affine).m[2][2] = 1.0;
      (ctx->affine).m[2][3] = 0.0;
      ctx = av->physicsCtx;
      (ctx->xRow).x = 1.0;
      (ctx->xRow).y = 0.0;
      (ctx->xRow).z = 0.0;
      ctx->xOffset = 0.0;
      (ctx->yRow).x = 0.0;
      (ctx->yRow).y = 1.0;
      (ctx->yRow).z = 0.0;
      ctx->yOffset = 0.0;
      (ctx->zRow).x = 0.0;
      (ctx->zRow).y = 0.0;
      (ctx->zRow).z = 1.0;
      ctx->zOffset = 0.0;
    }
    return av->physicsCtx;
  }
  return av->physicsCtx;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void __thiscall avatar::FUN_0003bab0(void *this,AffineTransform *aff,int param_3)

{
  actor *pAVar1;
  AffineTransform *puVar2;
  int iVar1;
  int iVar3;
  astruct_49 *iVar2;
  
  pAVar1 = GetPhysicsInner(this);
  iVar2 = (astruct_49 *)(pAVar1->avatar).model;
  iVar1 = iVar2->field357_0x168;
  if (iVar1 == 0) {
    iVar1 = iVar2->field356_0x164;
  }
  if ((iVar2->field438_0x1bc == 0) || (iVar3 = *(int *)(iVar2->field438_0x1bc + 0x24), iVar3 == 0))
  {
    iVar3 = 0;
  }
  else {
    iVar3 = param_3 * 0x20 + iVar3;
  }
  puVar2 = FUN_000316b0((float *)&(pAVar1->avatar).drawAffine,iVar3,param_3,iVar1);
  aff->m[0][0] = puVar2->m[0][0];
  aff->m[0][1] = puVar2->m[0][1];
  aff->m[0][2] = puVar2->m[0][2];
  aff->m[0][3] = puVar2->m[0][3];
  aff->m[1][0] = puVar2->m[1][0];
  aff->m[1][1] = puVar2->m[1][1];
  aff->m[1][2] = puVar2->m[1][2];
  aff->m[1][3] = puVar2->m[1][3];
  aff->m[2][0] = puVar2->m[2][0];
  aff->m[2][1] = puVar2->m[2][1];
  aff->m[2][2] = puVar2->m[2][2];
  aff->m[2][3] = puVar2->m[2][3];
  return;
}



// WARNING: Variable defined which should be unmapped: param_2
// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void avatar::loadCalloutResource(CalloutDescriptor **callout,char *calloutAID)

{
  char cVar1;
  int iVar2;
  CalloutDescriptor *new_desc;
  
  if (*callout != (CalloutDescriptor *)0x0) {
    Assets::DestroyAssetOrDecrement(*callout);
    *callout = (CalloutDescriptor *)0x0;
  }
  if (calloutAID == (char *)0x0) {
    *(undefined1 *)(callout + 1) = 0;
    return;
  }
  if (*(int *)calloutAID == 0x5f646961) {
    Assets::GetResourceBytes(calloutAID,&new_desc);
    if (new_desc == (CalloutDescriptor *)0x0) {
      runtime::ExitGame(2);
    }
  }
  else {
    new_desc = (CalloutDescriptor *)0x0;
  }
  *callout = new_desc;
  iVar2 = 4 - (int)calloutAID;
  do {
    cVar1 = *calloutAID;
    calloutAID[(int)callout + iVar2] = cVar1;
    calloutAID = calloutAID + 1;
  } while (cVar1 != '\0');
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void avatar::getVTable(void)

{
  initVTable(&g_AvatarVTable);
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void avatar::initVTable(AvatarVTable *table)

{
  table->getAllocDetails = getAllocDetails;
  table->ctor = ctor;
  table->dtor = avatar::dtor;
  table->onMessage = onMessage;
  table->update = update;
  table->draw = draw;
  table->func6 = func6;
  table->runPhysics = runPhysics;
  table->runDeltaPhysics = runDeltaPhysics;
  table->handleWallCollisions = handleWallCollisions;
  table->checkForHitByWeapon = checkForHitByWeapon;
  table->checkCollisions2 = checkCollisions2;
  table->func12 = func12;
  table->updatePositionsAndAnimations = updatePositionsAndAnimations;
  table->func14 = (void *)0x0;
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields

undefined4
avatar::updatePositionsAndAnimations
          (avatar *param_1,avatar *param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5,
          undefined4 param_6,vec3 *param_7)

{
  ModelDescriptor *pMVar1;
  Model *pMVar2;
  bool bVar3;
  avatar *av;
  undefined4 uVar4;
  int iVar5;
  CollisionMask CVar6;
  ModelFooterEntry *pMVar7;
  AnimCollisionSubresourceEntry *pAVar8;
  bool bVar9;
  short sVar10;
  float local_3c;
  vec3 v;
  float local_2c;
  float local_28;
  float local_24;
  SomeActorBodyList local_20;
  uint i;
  
  av = param_1;
  if ((param_1->model != (Model *)0x0) &&
     (pMVar1 = param_1->model->descriptor, pMVar1 != (ModelDescriptor *)0x0)) {
    i = 0;
    if (pMVar1->numFooterEntries != 0) {
      pMVar7 = pMVar1->footerEntries;
      do {
        if (pMVar7->subresourceType == AnimColliders) {
          i = pMVar1->footerEntries[i].offset;
          if (i == 0) {
            return 0;
          }
          v.z = 0.0;
          v.y = 0.0;
          v.x = 0.0;
          if (param_2 == (avatar *)0x0) {
            bVar9 = false;
          }
          else {
            bVar9 = *(avatar **)&param_2->field_0x11c == param_1;
          }
          bVar3 = false;
          sVar10 = 0;
          if (bVar9 == false) {
            if ((param_2 != (avatar *)0x0) &&
               (*(int *)&param_1->damageFlag_ < *(int *)&param_2->damageFlag_)) {
              return 0;
            }
          }
          else {
            iVar5 = FUN_0003c470(param_1,param_2,&v,param_4);
            if (iVar5 != 0) {
              bVar3 = true;
            }
          }
          getHealthPos(av,(float *)&param_1,&local_3c,&local_2c);
          local_20.pos.x = local_2c;
          local_20.pos.y = local_28;
          local_20.pos.z = local_24;
          local_20.someYScale = 0.0;
          local_20._24_4_ = 0;
          local_20.field0_0x0 = '\x04';
          local_20.field1_0x1 = ' ';
          local_20.field2_0x2 = '\x01';
          local_20.someFloat = (float)param_1;
          local_20.field11_0x1c = local_3c;
          iVar5 = FUN_001205f0((int)&local_20,param_4);
          uVar4 = param_6;
          if (iVar5 != 0) {
            if (!bVar3) {
              return 0;
            }
            sVar10 = 0;
            goto LAB_0003c362;
          }
          pMVar2 = av->model;
          local_3c = (float)av->has0x4CollisionFlag;
          if (pMVar2 == (Model *)0x0) {
            param_1 = (avatar *)0x0;
          }
          else {
            param_1 = (avatar *)pMVar2->skeleton;
            if (param_1 == (avatar *)0x0) {
              param_1 = (avatar *)pMVar2->skeleton2;
            }
          }
          pAVar8 = (AnimCollisionSubresourceEntry *)(i + 8);
          goto joined_r0x0003c289;
        }
        i = i + 1;
        pMVar7 = pMVar7 + 1;
      } while (i < pMVar1->numFooterEntries);
    }
  }
  return 0;
joined_r0x0003c289:
  if (pAVar8 == (AnimCollisionSubresourceEntry *)0x0) {
LAB_0003c351:
    if (!bVar3) {
      return 0;
    }
LAB_0003c362:
    param_7->x = v.x;
    param_7->y = v.y;
    param_7->z = v.z;
    FUN_0003c5d0(sVar10);
    return 1;
  }
  if (av->model == (Model *)0x0) {
    CVar6 = Everything;
  }
  else {
    CVar6 = av->model->boneIndices[pAVar8->blendTargetIndex];
  }
  if (((uint)local_3c & pAVar8->collisionMask & CVar6) != Nothing) {
    if (pAVar8->colliderType == Sphere) {
      SomeActorBodyList::accumulateCollisionsFromSkeletonAndAnim
                (&local_20,(Skeleton *)param_1,pAVar8,&av->drawAffine);
    }
    else {
      if (pAVar8->colliderType != Cylinder) goto LAB_0003c33f;
      FUN_00055aa0(&local_20);
    }
    iVar5 = FUN_0003c3a0(av,param_2,param_3,uVar4,bVar9);
    if (iVar5 != 0) {
      sVar10 = pAVar8->blendTargetIndex;
      bVar3 = true;
    }
  }
LAB_0003c33f:
  if (pAVar8->size == 0) goto LAB_0003c351;
  pAVar8 = (AnimCollisionSubresourceEntry *)(&pAVar8->colliderType + (byte)pAVar8->size);
  goto joined_r0x0003c289;
}



undefined4 __fastcall
FUN_0003c3a0(undefined4 param_1,int param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5
            ,int param_6,int param_7)

{
  CollisionContext *in_EAX;
  int iVar1;
  CollisionContext *pCVar2;
  vec3 *unaff_ESI;
  vec3 local_c;
  
  iVar1 = FUN_001206a0();
  if (iVar1 == 0) {
    pCVar2 = in_EAX + param_6;
    if (param_7 == 0) {
      if (in_EAX < pCVar2) {
        while (iVar1 = runCollisionTest(unaff_ESI,&local_c,in_EAX,param_2), iVar1 == 0) {
          in_EAX = in_EAX + 1;
          if (pCVar2 <= in_EAX) {
            return 0;
          }
        }
LAB_0003c427:
        unaff_ESI->x = unaff_ESI->x + local_c.x;
        unaff_ESI->y = unaff_ESI->y + local_c.y;
        unaff_ESI->z = unaff_ESI->z + local_c.z;
        return 1;
      }
    }
    else {
      for (; in_EAX < pCVar2; in_EAX = in_EAX + 1) {
        iVar1 = FUN_00120950(param_3,param_2,param_4,in_EAX,param_5);
        if (iVar1 != 0) goto LAB_0003c427;
      }
    }
  }
  return 0;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void avatar::modelHasSpecificCollider(avatar *param_1)

{
  ModelDescriptor *pMVar1;
  uint uVar2;
  ModelSubresource0x4Value *value;
  ModelFooterEntry *pMVar3;
  uint32_t flags;
  int num_values;
  ModelSubresource0x4 *piVar2;
  uint8_t value_size;
  
  *(undefined4 *)&param_1->damageFlag_ = 2;
  if ((param_1->model != (Model *)0x0) &&
     (pMVar1 = param_1->model->descriptor, pMVar1 != (ModelDescriptor *)0x0)) {
    uVar2 = 0;
    if (pMVar1->numFooterEntries != 0) {
      pMVar3 = pMVar1->footerEntries;
      while (pMVar3->subresourceType != AnimColliders) {
        uVar2 = uVar2 + 1;
        pMVar3 = pMVar3 + 1;
        if (pMVar1->numFooterEntries <= uVar2) {
          return;
        }
      }
      piVar2 = (ModelSubresource0x4 *)pMVar1->footerEntries[uVar2].offset;
      if (piVar2 != (ModelSubresource0x4 *)0x0) {
        value = piVar2->values;
        num_values = piVar2->numValues;
        flags = 0;
        if (0 < num_values) {
          do {
            flags = flags | value->flags;
            value_size = value->valueSize;
            if (value_size == '\0') {
              value = (ModelSubresource0x4Value *)0x0;
            }
            else {
              value = (ModelSubresource0x4Value *)(&value->field0_0x0 + value_size);
            }
            num_values = num_values + -1;
          } while (num_values != 0);
        }
        if ((flags & 4) != 0) {
          param_1->has0x4CollisionFlag = 4;
        }
      }
    }
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void avatar::updateMorphTargetsOrSomething(avatar *this)

{
  ModelDescriptor *pMVar1;
  avatar_0x110 pEVar2;
  EmbeddedNode<>_conflict *pEVar3;
  ModelSubresource0x4Value *pMVar4;
  avatar_0x110 pEVar5;
  ModelFooterEntry *pMVar6;
  uint flags;
  int num_values;
  ModelSubresource0x4 *subres0x4;
  EmbeddedNode<> *node;
  
  node = &this->node0x110;
  if ((this->model != (Model *)0x0) &&
     (pMVar1 = this->model->descriptor, pMVar1 != (ModelDescriptor *)0x0)) {
    flags = 0;
    if (pMVar1->numFooterEntries != 0) {
      pMVar6 = pMVar1->footerEntries;
      do {
        if (pMVar6->subresourceType == AnimColliders) {
          subres0x4 = (ModelSubresource0x4 *)pMVar1->footerEntries[flags].offset;
          if (subres0x4 != (ModelSubresource0x4 *)0x0) {
            pMVar4 = subres0x4->values;
            num_values = subres0x4->numValues;
            flags = 0;
            if (0 < num_values) {
              do {
                flags = flags | pMVar4->flags;
                if (pMVar4->valueSize == 0) {
                  pMVar4 = (ModelSubresource0x4Value *)0x0;
                }
                else {
                  pMVar4 = (ModelSubresource0x4Value *)(&pMVar4->field0_0x0 + pMVar4->valueSize);
                }
                num_values = num_values + -1;
              } while (num_values != 0);
            }
            if ((this->has0x4CollisionFlag & flags) != 0) {
              if (node->prev != (avatar_0x110)0x0) {
                return;
              }
                    // Add avatar to 0x110 list
              pEVar5 = (avatar_0x110)&Game::SceneInfo.avatars_0x110;
              pEVar2 = Game::SceneInfo.avatars_0x110.sentinel;
              while (pEVar2 != (avatar_0x110)0x0) {
                pEVar5 = pEVar5->prev;
                pEVar2 = pEVar5->prev;
              }
              pEVar3 = (EmbeddedNode<>_conflict *)pEVar5->next;
              pEVar5->next = node;
              node->prev = pEVar5;
              (this->node0x110).next = (avatar_0x110)pEVar3;
              if (pEVar3 == (EmbeddedNode<>_conflict *)0x0) {
                return;
              }
              pEVar3->prev = (avatar_0x110_conflict)node;
              return;
            }
          }
          break;
        }
        flags = flags + 1;
        pMVar6 = pMVar6 + 1;
      } while (flags < pMVar1->numFooterEntries);
    }
  }
                    // If it failed, remove itself from the list
  if (node->prev != (avatar_0x110)0x0) {
    node->prev->next = (this->node0x110).next;
  }
  pEVar5 = (this->node0x110).next;
  if (pEVar5 != (avatar_0x110)0x0) {
    pEVar5->prev = node->prev;
  }
  node->prev = (avatar_0x110)0x0;
  (this->node0x110).next = (avatar_0x110)0x0;
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


BOOL avatar::func6(avatar *inAv,int param_2,int param_3)

{
  Model *pMVar1;
  ModelDescriptor *pMVar2;
  avatar *av;
  int iVar3;
  CollisionMask CVar4;
  AnimCollisionSubresourceEntry *entry;
  uint uVar5;
  ModelFooterEntry *pMVar6;
  float10 extraout_ST0;
  avatar *paVar7;
  Skeleton *local_20;
  vec3 local_18;
  vec3 local_c;
  
  av = inAv;
  getWorldPosition(inAv,&local_18);
  paVar7 = (avatar *)getCalculatedRadius(av);
  inAv = paVar7;
  if ((0 < av->numTransforms) && (FUN_00040550(), (float)inAv < (float)paVar7)) {
    inAv = paVar7;
  }
  if (((float)inAv != 0.0) &&
     (iVar3 = FUN_00159ad0(&Graphics::CurrentCameraStruct->field_0x138,&local_18,inAv,
                           av->calloutAID + param_3 + param_2 * 4 + 0xf4), iVar3 != 0)) {
    return 1;
  }
  CVar4 = getCollisionMaskFromModel(av);
  if ((CVar4 & 0x200) != Nothing) {
    pMVar1 = av->model;
    if (pMVar1 == (Model *)0x0) {
      local_20 = (Skeleton *)0x0;
    }
    else {
      local_20 = pMVar1->skeleton;
      if (local_20 == (Skeleton *)0x0) {
        local_20 = pMVar1->skeleton2;
      }
    }
    entry = (AnimCollisionSubresourceEntry *)FUN_00042560(0x200);
    inAv = (avatar *)((uint)inAv & 0xffffff00);
    if (entry != (AnimCollisionSubresourceEntry *)0x0) {
      do {
        checkCollisionAgainstSkeleton(entry,local_20,&local_c,&av->drawAffine);
        iVar3 = FUN_00159ad0(&Graphics::CurrentCameraStruct->field_0x138,&local_c,
                             (float)extraout_ST0,&inAv);
        if (iVar3 != 0) {
          return 1;
        }
        if ((av->model != (Model *)0x0) &&
           (pMVar2 = av->model->descriptor, pMVar2 != (ModelDescriptor *)0x0)) {
          uVar5 = 0;
          if (pMVar2->numFooterEntries != 0) {
            pMVar6 = pMVar2->footerEntries;
            do {
              if (pMVar6->subresourceType == AnimColliders) break;
              uVar5 = uVar5 + 1;
              pMVar6 = pMVar6 + 1;
            } while (uVar5 < pMVar2->numFooterEntries);
          }
        }
        if (entry->size == 0) {
          return 0;
        }
        entry = (AnimCollisionSubresourceEntry *)(&entry->colliderType + (byte)entry->size);
        while( true ) {
          if (entry == (AnimCollisionSubresourceEntry *)0x0) {
            return 0;
          }
          if (((entry->collisionMask & 0x200) != Nothing) && (entry->colliderType == Sphere)) break;
          if (entry->size == 0) {
            return 0;
          }
          entry = (AnimCollisionSubresourceEntry *)(&entry->colliderType + (byte)entry->size);
        }
      } while( true );
    }
  }
  return 0;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


undefined4 avatar::draw(avatar *av,undefined4 param_2,BOOL someFlag)

{
  Model *instance;
  uint32_t uVar1;
  uint8_t uVar2;
  uint8_t uVar3;
  uint8_t uVar4;
  uint8_t uVar5;
  int is_black;
  
  if (av->field_0x197 != '\0') {
    return 0;
  }
  update0x1d8s(av);
  instance = av->model;
  if (instance == (Model *)0x0) {
    return 0;
  }
  if (someFlag == 0) {
                    // Requires subres 10
    if ((instance->descriptor->flags & 0x10) == 0) {
      return 0;
    }
  }
  else if ((someFlag == 2) && ((instance->descriptor->flags & 8) == 0)) {
    return 0;
  }
  if (av->hasActor_ == false) {
    ::actor::createOnDeathObjects(av,0);
  }
  is_black = Colour::areEqual(av->someColour,(Colour)0xff000000);
  if (is_black == 0) {
    uVar2 = (av->someColour).r;
    uVar3 = (av->someColour).g;
    uVar4 = (av->someColour).b;
    uVar5 = (av->someColour).a;
    uVar1 = av->someInt32;
    instance->field351_0x1c0 = 1;
    instance->field352_0x1c4 = uVar1;
    instance->field_0x1c8 = uVar2;
    instance->field_0x1c9 = uVar3;
    instance->field_0x1ca = uVar4;
    instance->field_0x1cb = uVar5;
  }
  else {
    instance->field351_0x1c0 = 0;
  }
  if (av->preDrawCallback != (code *)0x0) {
                    // Reacts when cooper gets scared
    (*av->preDrawCallback)(av,someFlag,av->preDrawData);
  }
                    // Draw the model with the actors affine matrix
  ModelInstance::draw(instance,&av->drawAffine,someFlag);
                    // Disabling this seriously breaks post cutscene events and puts the game into
                    // hyper fast mode. The game does survive for a little bit but eventually starts
                    // losing it
  if (av->textureCallback != (code *)0x0) {
    (*av->textureCallback)(av,someFlag,av->preDrawData);
  }
  return 1;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void avatar::onDrawListAdd(avatar *av)

{
  bool bVar1;
  int *piVar2;
  int iVar3;
  undefined4 local_4;
  
  bVar1 = false;
  piVar2 = (int *)&av->field_0x140;
  iVar3 = 2;
  do {
    if (piVar2[-7] != 0) {
      *(int *)(piVar2[-7] + 4) = piVar2[-6];
      if ((int *)piVar2[-6] != (int *)0x0) {
        *(int *)piVar2[-6] = piVar2[-7];
      }
      piVar2[-7] = 0;
      piVar2[-6] = 0;
      bVar1 = true;
    }
    if (piVar2[-4] != 0) {
      *(int *)(piVar2[-4] + 4) = piVar2[-3];
      if ((int *)piVar2[-3] != (int *)0x0) {
        *(int *)piVar2[-3] = piVar2[-4];
      }
      piVar2[-4] = 0;
      piVar2[-3] = 0;
      bVar1 = true;
    }
    if (piVar2[-1] != 0) {
      *(int *)(piVar2[-1] + 4) = *piVar2;
      if ((int *)*piVar2 != (int *)0x0) {
        *(int *)*piVar2 = piVar2[-1];
      }
      piVar2[-1] = 0;
      *piVar2 = 0;
      bVar1 = true;
    }
    if (piVar2[2] != 0) {
      *(int *)(piVar2[2] + 4) = piVar2[3];
      if ((int *)piVar2[3] != (int *)0x0) {
        *(int *)piVar2[3] = piVar2[2];
      }
      piVar2[2] = 0;
      piVar2[3] = 0;
      bVar1 = true;
    }
    piVar2 = piVar2 + 0xc;
    iVar3 = iVar3 + -1;
  } while (iVar3 != 0);
  if (*(int *)&av->field_0x18c != 0) {
    *(undefined4 *)(*(int *)&av->field_0x18c + 4) = *(undefined4 *)&av->field_0x190;
  }
  if (*(undefined4 **)&av->field_0x190 != (undefined4 *)0x0) {
    **(undefined4 **)&av->field_0x190 = *(undefined4 *)&av->field_0x18c;
  }
  *(undefined4 *)&av->field_0x18c = 0;
  *(undefined4 *)&av->field_0x190 = 0;
  if (bVar1) {
    local_4 = 0x12;
    (*av->vtable->onMessage)(av,&local_4);
  }
  return;
}




void avatar::updateFx(avatar *param_1)

{
  int *mem;
  avatarFxEmitter *paVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  HeapTableEntry *pHVar5;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  undefined4 local_8;
  undefined4 local_4;
  
  mem = (param_1->fxEmitterImpactFlash).field12_0xc;
  while (mem != (int *)0x0) {
    if (*mem != 0) {
      *(int *)(*mem + 4) = mem[1];
    }
    if ((int *)mem[1] != (int *)0x0) {
      *(int *)mem[1] = *mem;
    }
    *mem = 0;
    mem[1] = 0;
    iVar4 = FUN_0003d3a0();
    if (iVar4 == 0) {
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
      runtime::CurrentHeapToAllocateFrom = uVar3;
    }
    else {
      paVar1 = &param_1->fxEmitterImpactFlash;
      iVar4 = *(int *)&(param_1->fxEmitterImpactFlash).field_0x4;
      while (iVar4 != 0) {
        paVar1 = *(avatarFxEmitter **)&paVar1->field_0x4;
        iVar4 = *(int *)&paVar1->field_0x4;
      }
      *(int **)&paVar1->field_0x4 = mem;
      *mem = (int)paVar1;
      mem[1] = 0;
    }
    mem = (param_1->fxEmitterImpactFlash).field12_0xc;
  }
  for (iVar4 = *(int *)&(param_1->fxEmitterImpactFlash).field_0x4; iVar4 != 0;
      iVar4 = *(int *)(iVar4 + 4)) {
    iVar2 = (&DAT_00506930)[*(int *)(iVar4 + 8)];
    FUN_0003d510(param_1,&local_c);
    if ((*(byte *)(iVar4 + 0x20) & 1) != 0) {
      *(undefined4 *)(iVar2 + 0x1c) = local_18;
      *(undefined4 *)(iVar2 + 0x20) = local_14;
      *(undefined4 *)(iVar2 + 0x24) = local_10;
    }
    if ((*(byte *)(iVar4 + 0x20) & 2) != 0) {
      *(undefined4 *)(iVar2 + 0x50) = local_c;
      *(undefined4 *)(iVar2 + 0x54) = local_8;
      *(undefined4 *)(iVar2 + 0x58) = local_4;
    }
  }
  return;
}




void avatar::loadValuesFromModelMatrix(avatar *this)

{
  ModelDescriptor *pMVar1;
  uint uVar2;
  ModelFooterEntry *pMVar3;
  MatrixSubresource *matrix_subres;
  
  if ((this->model != (Model *)0x0) &&
     (pMVar1 = this->model->descriptor, pMVar1 != (ModelDescriptor *)0x0)) {
    uVar2 = 0;
    if (pMVar1->numFooterEntries != 0) {
      pMVar3 = pMVar1->footerEntries;
      while (pMVar3->subresourceType != ModelMatrix) {
        uVar2 = uVar2 + 1;
        pMVar3 = pMVar3 + 1;
        if (pMVar1->numFooterEntries <= uVar2) {
          this->maxScaleFromBasis = 1.0;
          return;
        }
      }
      matrix_subres = (MatrixSubresource *)pMVar1->footerEntries[uVar2].offset;
      if (matrix_subres != (MatrixSubresource *)0x0) {
        this->field193_0x1cc = 0.0;
        this->fromModelMatrix1 = matrix_subres->field29_0x20;
        this->fromModelMatrix2 = matrix_subres->field30_0x24;
      }
    }
  }
  this->maxScaleFromBasis = 1.0;
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void avatar::getMaxScaleFromBasis(avatar *av)

{
  ModelDescriptor *pMVar1;
  byte bone_indexx;
  uint bone_index;
  AffineTransform *bone_affine;
  ModelFooterEntry *pMVar2;
  vec3 scaleBases;
  Model *instance;
  
  instance = av->model;
  if ((instance != (Model *)0x0) &&
     (pMVar1 = instance->descriptor, pMVar1 != (ModelDescriptor *)0x0)) {
    bone_index = 0;
    if (pMVar1->numFooterEntries != 0) {
      pMVar2 = pMVar1->footerEntries;
      while (pMVar2->subresourceType != ModelMatrix) {
        bone_index = bone_index + 1;
        pMVar2 = pMVar2 + 1;
        if (pMVar1->numFooterEntries <= bone_index) {
          return;
        }
      }
      if (((pMVar1->footerEntries[bone_index].offset != 0) && (instance != (Model *)0x0)) &&
         (instance->descriptor != (ModelDescriptor *)0x0)) {
                    // Get bone index for rigid 0
        bone_indexx = ModelDescriptor::getBoneIdxFromRigid(instance->descriptor,0);
        if (((bone_indexx != 0xff) && (bone_indexx != 0xffffffff)) &&
           ((instance != (Model *)0x0 && (instance->descriptor != (ModelDescriptor *)0x0)))) {
          bone_indexx = ModelDescriptor::getBoneIdxFromRigid(instance->descriptor,0);
          bone_index = (uint)bone_indexx;
          if (((bone_index != 0xff) && (bone_index != 0xffffffff)) &&
             (bone_affine = getBoneAffineByIndex(av,bone_index),
             bone_affine != (AffineTransform *)0x0)) {
            AffineTransform::getScaleBases(bone_affine,&scaleBases);
            if (scaleBases.y < scaleBases.z) {
              scaleBases.y = scaleBases.z;
            }
            if (scaleBases.y <= scaleBases.x) {
              scaleBases.y = scaleBases.x;
            }
            av->maxScaleFromBasis = scaleBases.y;
          }
        }
      }
    }
  }
  return;
}




float avatar::getCalculatedRadius(avatar *av)

{
  float fVar1;
  ModelDescriptor *pMVar2;
  uint uVar3;
  ModelSubresourceType *piVar4;
  float10 fVar4;
  float fVar5;
  MatrixSubresource *pfVar3;
  
  if ((av->model != (Model *)0x0) &&
     (pMVar2 = av->model->descriptor, pMVar2 != (ModelDescriptor *)0x0)) {
    uVar3 = 0;
    if (pMVar2->numFooterEntries != 0) {
      piVar4 = &pMVar2->footerEntries->subresourceType;
      do {
        if (*piVar4 == ModelMatrix) {
          pfVar3 = (MatrixSubresource *)pMVar2->footerEntries[uVar3].offset;
          if (pfVar3 == (MatrixSubresource *)0x0) {
            return 0.0;
          }
          fVar5 = av->uniformScale * (av->scale).z;
          fVar4 = abs_float(pfVar3->field0_0x0 * fVar5);
          fVar5 = av->someMagnitude * fVar5;
          fVar1 = (float)(fVar4 * (float10)av->maxScaleFromBasis);
          if (fVar5 <= fVar1) {
            return fVar1;
          }
          return fVar5;
        }
        uVar3 = uVar3 + 1;
        piVar4 = piVar4 + 2;
      } while (uVar3 < pMVar2->numFooterEntries);
    }
  }
  return 0.0;
}




void avatar::pos1FromMatrix(avatar *av,vec3 *v)

{
  float fVar1;
  float fVar2;
  float fVar3;
  uint i;
  ModelSubresourceType *subres_type;
  MatrixSubresource *matrix;
  ModelDescriptor *footer_entries;
  
  if ((av->model != (Model *)0x0) &&
     (footer_entries = av->model->descriptor, footer_entries != (ModelDescriptor *)0x0)) {
    i = 0;
    if (footer_entries->numFooterEntries != 0) {
      subres_type = &footer_entries->footerEntries->subresourceType;
      do {
        if (*subres_type == ModelMatrix) {
          matrix = (MatrixSubresource *)footer_entries->footerEntries[i].offset;
          if (matrix != (MatrixSubresource *)0x0) {
            v->x = (matrix->pos1).x;
            v->y = (matrix->pos1).y;
            v->z = (matrix->pos1).z;
            fVar1 = av->uniformScale;
            fVar2 = (av->scale).y;
            fVar3 = (av->scale).z;
            v->x = v->x * (av->scale).x * fVar1;
            v->y = v->y * fVar2 * fVar1;
            v->z = v->z * fVar3 * fVar1;
            return;
          }
          break;
        }
        i = i + 1;
        subres_type = subres_type + 2;
      } while (i < footer_entries->numFooterEntries);
    }
  }
  v->y = 0.0;
  v->x = 0.0;
  v->z = 0.0;
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


vec3 * avatar::pos2FromMatrix(avatar *av,vec3 *v)

{
  float fVar1;
  float fVar2;
  ModelDescriptor *pMVar3;
  uint uVar4;
  ModelFooterEntry *pMVar5;
  MatrixSubresource *matrix;
  float baseScale;
  
  if ((av->model != (Model *)0x0) &&
     (pMVar3 = av->model->descriptor, pMVar3 != (ModelDescriptor *)0x0)) {
    uVar4 = 0;
    if (pMVar3->numFooterEntries != 0) {
      pMVar5 = pMVar3->footerEntries;
      do {
        if (pMVar5->subresourceType == ModelMatrix) {
          matrix = (MatrixSubresource *)pMVar3->footerEntries[uVar4].offset;
          if (matrix != (MatrixSubresource *)0x0) {
            v->x = (matrix->pos2).x;
            v->y = (matrix->pos2).y;
            v->z = (matrix->pos2).z;
            baseScale = av->uniformScale;
            fVar1 = (av->scale).y;
            fVar2 = (av->scale).z;
            v->x = v->x * (av->scale).x * baseScale;
            v->y = v->y * fVar1 * baseScale;
            v->z = v->z * fVar2 * baseScale;
            return v;
          }
          break;
        }
        uVar4 = uVar4 + 1;
        pMVar5 = pMVar5 + 1;
      } while (uVar4 < pMVar3->numFooterEntries);
    }
  }
  v->y = 0.0;
  v->x = 0.0;
  v->z = 0.0;
  return v;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void avatar::getHealthPos(avatar *av,float *param_2,float *param_3,vec3 *worldPos)

{
  float10 fVar1;
  
  getWorldPosition(av,worldPos);
  worldPos->y = (av->scale).y * av->field193_0x1cc + worldPos->y;
  fVar1 = abs_float((av->fromModelMatrix1 - av->field193_0x1cc) * (av->scale).y);
  *param_2 = (float)fVar1;
  fVar1 = abs_float((av->scale).z * av->fromModelMatrix2);
  *param_3 = (float)fVar1;
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void avatar::update0x1d8s(avatar *av)

{
  int iVar1;
  int iVar2;
  
  iVar2 = *(int *)&av->field_0x1d8;
  while (iVar2 != 0) {
    iVar1 = *(int *)(iVar2 + 4);
    (**(code **)(*(int *)(iVar2 + -8) + 0x14))(iVar2 + -8,av);
    iVar2 = iVar1;
  }
  return;
}




avatar::func12(avatar *av,vec3 *pos,float radius,CollisionMask collisionMask,undefined4 param_5)

{
  ModelDescriptor *pMVar1;
  Model *pMVar2;
  uint uVar4;
  BOOL BVar5;
  Skeleton *skeleton;
  undefined4 uVar6;
  ModelFooterEntry *pMVar7;
  CollisionMask CVar8;
  Model_0x16c ppvVar9;
  AnimCollisionSubresource *uVar3;
  
  if ((av->model != (Model *)0x0) &&
     (pMVar1 = av->model->descriptor, pMVar1 != (ModelDescriptor *)0x0)) {
    uVar4 = 0;
    if (pMVar1->numFooterEntries != 0) {
      pMVar7 = pMVar1->footerEntries;
      while (pMVar7->subresourceType != AnimColliders) {
        uVar4 = uVar4 + 1;
        pMVar7 = pMVar7 + 1;
        if (pMVar1->numFooterEntries <= uVar4) {
          return 0;
        }
      }
      uVar3 = (AnimCollisionSubresource *)pMVar1->footerEntries[uVar4].offset;
      if ((uVar3 != (AnimCollisionSubresource *)0x0) &&
         (CVar8 = collisionMask & av->collisionMask, CVar8 != Nothing)) {
        BVar5 = notSphereColliding(av,pos,radius);
        if (BVar5 == 0) {
          if (av->model == (Model *)0x0) {
            ppvVar9 = (Model_0x16c)0x0;
          }
          else {
            ppvVar9 = (Model_0x16c)av->model->boneIndices;
          }
          pMVar2 = av->model;
          if (pMVar2 == (Model *)0x0) {
            skeleton = (Skeleton *)0x0;
          }
          else {
            skeleton = pMVar2->skeleton;
            if (skeleton == (Skeleton *)0x0) {
              skeleton = pMVar2->skeleton2;
            }
          }
          uVar6 = FUN_00056be0(uVar3,&av->drawAffine,&av->baseTransform,skeleton,pos,radius,CVar8,
                               ppvVar9,param_5);
          return uVar6;
        }
      }
    }
  }
  return 0;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


BOOL avatar::notCollidingWithSphereFromEndpoints(avatar *av,vec3 *sphereStart,vec3 *sphereEnd)

{
  BOOL BVar1;
  float radius1;
  float halfy;
  float halfz;
  float halfx;
  vec3 midPoint;
  vec3 worldPos;
  
  radius1 = getCalculatedRadius(av);
  getWorldPosition(av,&worldPos);
  midPoint.x = (sphereEnd->x - sphereStart->x) * 0.5 + sphereStart->x;
  midPoint.y = (sphereEnd->y - sphereStart->y) * 0.5 + sphereStart->y;
  midPoint.z = (sphereEnd->z - sphereStart->z) * 0.5 + sphereStart->z;
                    // Radius
  halfx = sphereStart->x - midPoint.x;
  halfy = sphereStart->y - midPoint.y;
  halfz = sphereStart->z - midPoint.z;
  BVar1 = Math::SpheresAreColliding
                    (&worldPos,radius1,&midPoint,SQRT(halfx * halfx + halfy * halfy + halfz * halfz)
                    );
  return (uint)(BVar1 == 0);
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


BOOL avatar::broadPhaseSphereCheck(vec3 *param_1,float param_2,avatar *param_3,vec3 *param_4)

{
  BOOL BVar1;
  float radius1;
  float fVar2;
  float fVar3;
  float fVar4;
  vec3 local_18;
  vec3 local_c;
  
  radius1 = getCalculatedRadius(param_3);
  getWorldPosition(param_3,&local_c);
  local_18.x = (param_1->x - param_4->x) * 0.5 + param_4->x;
  local_18.y = (param_1->y - param_4->y) * 0.5 + param_4->y;
  local_18.z = (param_1->z - param_4->z) * 0.5 + param_4->z;
  fVar4 = param_4->x - local_18.x;
  fVar2 = param_4->y - local_18.y;
  fVar3 = param_4->z - local_18.z;
  BVar1 = Math::SpheresAreColliding
                    (&local_c,radius1,&local_18,
                     SQRT(fVar4 * fVar4 + fVar2 * fVar2 + fVar3 * fVar3) + param_2);
  return (uint)(BVar1 == 0);
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


BOOL avatar::notSphereColliding(avatar *av,vec3 *pos2,float radius2)

{
  BOOL BVar1;
  float radius1;
  vec3 pos1;
  
  radius1 = getCalculatedRadius(av);
  getWorldPosition(av,&pos1);
  BVar1 = Math::SpheresAreColliding(&pos1,radius1,pos2,radius2);
  return (uint)(BVar1 == 0);
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void avatar::initialiseCollisionMasks(avatar *av)

{
  BOOL BVar1;
  ColliderSetDescriptor *world_colliders;
  uint i;
  ColliderSet *collider;
  AnimCollisionSubresourceEntry *pAVar2;
  ModelFooterEntry *footer_entry;
  CollisionMask CVar3;
  int iVar4;
  AnimCollisionSubresource *anim_colliders;
  uint32_t uVar5;
  Model *instance;
  ModelDescriptor *model_desc;
  ColliderSetDescriptor *world_colliders_pre;
  
  instance = av->model;
  if ((instance == (Model *)0x0) || (instance->descriptor == (ModelDescriptor *)0x0)) {
    world_colliders = (ColliderSetDescriptor *)0x0;
  }
  else {
    world_colliders_pre = instance->descriptor->runtimeCtx->colliders;
    if (world_colliders_pre == (ColliderSetDescriptor *)0x0) {
      world_colliders = (ColliderSetDescriptor *)0x0;
    }
    else {
      BVar1 = ColliderSetDescriptor::hasCollision0x1235_(world_colliders_pre);
      world_colliders = (ColliderSetDescriptor *)(-(uint)(BVar1 != 0) & (uint)world_colliders_pre);
    }
  }
  if ((instance == (Model *)0x0) ||
     (model_desc = instance->descriptor, model_desc == (ModelDescriptor *)0x0)) {
    anim_colliders = (AnimCollisionSubresource *)0x0;
  }
  else {
    i = 0;
    if (model_desc->numFooterEntries != 0) {
      footer_entry = model_desc->footerEntries;
      do {
        if (footer_entry->subresourceType == AnimColliders) {
          anim_colliders = (AnimCollisionSubresource *)model_desc->footerEntries[i].offset;
          goto LAB_0003e73f;
        }
        i = i + 1;
        footer_entry = footer_entry + 1;
      } while (i < model_desc->numFooterEntries);
    }
    anim_colliders = (AnimCollisionSubresource *)0x0;
  }
LAB_0003e73f:
  if (world_colliders != (ColliderSetDescriptor *)0x0) {
    iVar4 = world_colliders->numColliderSets;
    CVar3 = Nothing;
    collider = world_colliders->colliderSets;
    if (0 < iVar4) {
      do {
        CVar3 = CVar3 | collider->collisionMask;
        collider = (ColliderSet *)(&collider->colliderType + collider->size);
        iVar4 = iVar4 + -1;
      } while (iVar4 != 0);
    }
    av->collisionMask = av->collisionMask | CVar3;
  }
                    // Disabling this makes combat not work
                    // 
                    // Build collision mask
                    // 
                    // Animation driven collision
  if (anim_colliders != (AnimCollisionSubresource *)0x0) {
    uVar5 = anim_colliders->numTargets;
    CVar3 = Nothing;
    pAVar2 = anim_colliders->entries;
    if (0 < (int)uVar5) {
      do {
        CVar3 = CVar3 | pAVar2->collisionMask;
        if (pAVar2->size == 0) {
          pAVar2 = (AnimCollisionSubresourceEntry *)0x0;
        }
        else {
          pAVar2 = (AnimCollisionSubresourceEntry *)(&pAVar2->colliderType + (byte)pAVar2->size);
        }
        uVar5 = uVar5 - 1;
      } while (uVar5 != 0);
    }
    av->collisionMask = av->collisionMask | CVar3;
  }
  return;
}




void avatar::onSceneInsert(avatar *av)

{
  EmbeddedNode<> *next;
  EmbeddedNode<> *pLVar2;
  
  if (av->collisionMask != Nothing) {
    next = (EmbeddedNode<> *)&Game::SceneInfo.avatarsWithCollision;
    if (Game::SceneInfo.avatarsWithCollision.head != (avatar_0x1e0)0x0) {
      next = (EmbeddedNode<> *)&Game::SceneInfo.avatarsWithCollision;
      do {
        pLVar2 = (EmbeddedNode<> *)&next->next;
        next = pLVar2->prev;
      } while (next->next != (avatar_0x1e0)0x0);
    }
    next->next = &av->avatarCollider;
    (av->avatarCollider).prev = next;
    (av->avatarCollider).next = (avatar_0x1e0)0x0;
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


undefined4 avatar::ctor(avatar *this,avatarParams *params)

{
  float fVar1;
  float fVar2;
  BOOL BVar3;
  impactFlashFxEmitterData *new_emitter;
  avatar_0x900 tail;
  BOOL has_shadow;
  uint impact_id;
  
  (this->pos).x = (params->pos).x;
  (this->pos).y = (params->pos).y;
  (this->pos).z = (params->pos).z;
  this->anglesCalculated = 0;
  Maths::NormaliseAngles2PI(&params->rotEuler,&this->rotEuler);
  fVar1 = (this->scale).x;
  this->anglesCalculated = 0;
  fVar2 = params->scale;
  if (((fVar1 != fVar2) || ((this->scale).y != fVar2)) || ((this->scale).z != fVar2)) {
    (this->scale).x = fVar2;
    (this->scale).y = fVar2;
    (this->scale).z = fVar2;
    this->anglesCalculated = 0;
  }
  (this->rotQuat).x = 0.0;
  (this->rotQuat).y = 0.0;
  (this->rotQuat).z = 0.0;
  (this->rotQuat).w = 1.0;
  this->actionSpeed = 1.0;
  this->anglesCalculated = 0;
  this->uniformScale = params->field4_0x24;
  if (*(int *)params->modelAID == 0x5f646961) {
    setModel(this,params->modelAID);
  }
  this->transforms = (AvatarMatrix *)0x0;
  this->numTransforms = 0;
  this->field234_0x29c = 0;
  this->field235_0x2a0 = 0;
  loadValuesFromModelMatrix(this);
  if (*(int *)params->animtableAID == 0x5f646961) {
    LoadAnimTable(this,params->animtableAID);
  }
  if (*(int *)params->standAnimationAID == 0x5f646961) {
    BVar3 = setInitialAnimation(this,params->standAnimationAID);
    if (BVar3 == 0) {
      clearAnimation(this);
    }
  }
  initialiseCollisionMasks(this);
  loadBoneIndices(this);
  modelHasSpecificCollider(this);
  has_shadow = params->hasShadow;
  this->hasShadow = has_shadow;
  this->field_0x330 = 0;
  this->field_0x331 = 0;
  if (has_shadow != 0) {
    setShadowModel(this,params->shadowModelAID);
  }
  this->someInt32 = -1;
  (this->someColour).r = '\0';
  (this->someColour).g = '\0';
  (this->someColour).b = '\0';
  (this->someColour).a = 0xff;
  this->preventAnimChannelAdvancing = 0xffff;
  loadCalloutResource(&this->callout,params->calloutAID);
  this->field218_0x1fc = *(ushort *)((int)&params->impactId + 2);
  this->someUshort = params->ghoulyboxId2;
  if (*(int *)params->fxEmitterImpactFlashAID == 0x5f646961) {
    impact_id = params->impactId;
    new_emitter = (impactFlashFxEmitterData *)
                  avatarFxEmitter::ctor
                            (&this->fxEmitterImpactFlash,0,3,params->fxEmitterImpactFlashAID);
    if (new_emitter != (impactFlashFxEmitterData *)0x0) {
      new_emitter->impactId = (short)impact_id;
    }
  }
  tail = (avatar_0x900)0x511b08;
                    // Set up avatar to be inserted later
  if (Game::SceneInfo.newAvatars.next != (avatar_0x900_conflict6)0x0) {
    tail = (avatar_0x900)&Game::SceneInfo.newAvatars;
    do {
      tail = tail->next;
    } while (tail->next != (avatar_0x900)0x0);
  }
  tail->next = &this->node0x900;
  (this->node0x900).prev = tail;
  (this->node0x900).next = (avatar_0x900)0x0;
  updateBaseTransform(this);
  return 1;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void avatar::avatar::dtor(avatar *param_1)

{
  avatar_0x900 pEVar1;
  avatar_0x110 pEVar2;
  DataForInfoFromBackground_conflict1 *pDVar3;
  astruct_23 *paVar4;
  astruct_23 *paVar5;
  undefined4 extraout_ECX;
  undefined4 uVar6;
  astruct_25 *paVar7;
  int iVar8;
  
  if (param_1->physicsCtx != (AvatarPhysicsContext *)0x0) {
    free(param_1->physicsCtx);
    param_1->physicsCtx = (AvatarPhysicsContext *)0x0;
  }
  pEVar1 = (param_1->node0x900).prev;
  if (pEVar1 != (avatar_0x900)0x0) {
    pEVar1->next = (param_1->node0x900).next;
  }
  pEVar1 = (param_1->node0x900).next;
  if (pEVar1 != (avatar_0x900)0x0) {
    pEVar1->prev = (param_1->node0x900).prev;
  }
  (param_1->node0x900).prev = (avatar_0x900)0x0;
  (param_1->node0x900).next = (avatar_0x900)0x0;
  onDrawListAdd(param_1);
  uVar6 = extraout_ECX;
  if (param_1->skipUpdate != 0) {
    uVar6 = *(undefined4 *)&param_1->field_0x90c;
    *(undefined4 *)(param_1->skipUpdate + 4) = uVar6;
  }
  if (*(uint **)&param_1->field_0x90c != (uint *)0x0) {
    **(uint **)&param_1->field_0x90c = param_1->skipUpdate;
  }
  param_1->skipUpdate = 0;
  *(undefined4 *)&param_1->field_0x90c = 0;
  FUN_0002cd00(uVar6,(SceneTreeNode *)&param_1->node0x918);
  FUN_0003de90(param_1);
  if (param_1->callout != (CalloutDescriptor *)0x0) {
    Assets::DestroyAssetOrDecrement(param_1->callout);
    param_1->callout = (CalloutDescriptor *)0x0;
  }
  param_1->calloutAID[0] = '\0';
  if (*(void **)&param_1->field_0x8fc != (void *)0x0) {
    free(*(void **)&param_1->field_0x8fc);
    *(undefined4 *)&param_1->field_0x8fc = 0;
  }
  setShadowModel(param_1,g_GlobalAssetName);
  if (param_1->numTransforms != 0) {
    free(param_1->transforms);
    param_1->transforms = (AvatarMatrix *)0x0;
    param_1->numTransforms = 0;
  }
  setModel(param_1,g_GlobalAssetName);
  if (param_1->animTable != (AnimtableResource *)0x0) {
    if (param_1->animTableHandled != 0) {
      Assets::DestroyAssetOrDecrement(param_1->animTable);
    }
    param_1->animTable = (AnimtableResource *)0x0;
  }
  clearAnimation(param_1);
  pEVar2 = (param_1->node0x110).prev;
  if (pEVar2 != (avatar_0x110)0x0) {
    pEVar2->next = (param_1->node0x110).next;
  }
  pEVar2 = (param_1->node0x110).next;
  if (pEVar2 != (avatar_0x110)0x0) {
    pEVar2->prev = (param_1->node0x110).prev;
  }
  (param_1->node0x110).prev = (avatar_0x110)0x0;
  (param_1->node0x110).next = (avatar_0x110)0x0;
  FUN_0003e7a0();
  paVar7 = (astruct_25 *)&param_1->field_0x334;
  iVar8 = 8;
  do {
    FUN_0012a3d0(paVar7);
    paVar7 = (astruct_25 *)&paVar7[1].field1_0x4;
    iVar8 = iVar8 + -1;
  } while (iVar8 != 0);
  pDVar3 = (param_1->infoList).prev;
  while (pDVar3 != (DataForInfoFromBackground_conflict1 *)0x0) {
    pDVar3 = (DataForInfoFromBackground_conflict1 *)pDVar3->field1_0x4;
    FUN_0011bda0();
  }
  paVar5 = param_1->as23ptr;
  while (paVar5 != (astruct_23 *)0x0) {
    paVar4 = *(astruct_23 **)&paVar5->field_0x4;
    FUN_0012b0b0((int)paVar5);
    paVar5 = paVar4;
  }
  FUN_0003d0a0(param_1);
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void avatar::register_0x900(avatar *av)

{
  EmbeddedNode<> *pEVar1;
  
  pEVar1 = (EmbeddedNode<> *)&Game::SceneInfo.newAvatars;
  if (Game::SceneInfo.newAvatars.next != (avatar_0x900_conflict6)0x0) {
    pEVar1 = (EmbeddedNode<> *)&Game::SceneInfo.newAvatars;
    do {
      pEVar1 = pEVar1->next;
    } while (pEVar1->next != (avatar_0x900)0x0);
  }
  pEVar1->next = &av->node0x900;
  (av->node0x900).prev = pEVar1;
  (av->node0x900).next = (avatar_0x900)0x0;
  return;
}




void avatar::onMessage(avatar *av,Message *msg)

{
  actor *paVar1;
  KeyframeContext *new_kfc;
  Message *pMVar2;
  
  switch((msg->header).msgId) {
  case Avatar_AnimationEvent:
    onAnimEvent(av,(Avatar_AnimationEventMessage *)msg);
    return;
  case Avatar_BreakableHit:
  case Avatar_CutScene_Begin:
  case Avatar_CutScene_End:
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
  case Actor_AStarLayerChanged:
  case Actor_AbortState:
  case Actor_ActionBegin:
  case Actor_ActionEnd:
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
  case Actor_NoLongerInvulnerable:
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
  case Scene_Begin:
  case Scene_CutsceneAlloc:
  case Scene_CutsceneFree:
  case Scene_EventBegin:
  case Scene_EventComplete:
  case Scene_EventEnd:
  case Scene_EventFailed:
  case Scene_LookAtRemoved:
  case Scene_PowerupActivated:
  case Scene_PowerupDeactivated:
  case Scene_Sfx_Started:
  case Scene_Sfx_Finished:
    break;
  case Avatar_CutScene_SetAnim:
    pMVar2 = msg + 0x17;
    new_kfc = getKFC(av);
    KeyframeContext::setAnim
              (new_kfc,(KFCParams *)(msg + 1),(uint)(msg->header).someActor,(char *)pMVar2);
    return;
  case Avatar_CutScene_SetPos:
    setPosition(av,(vec3 *)&(msg->header).someActor);
    return;
  case Avatar_CutScene_SetRot:
    Maths::NormaliseAngles2PI((vec3 *)&(msg->header).someActor,&av->rotEuler);
    av->anglesCalculated = 0;
    return;
  case Avatar_SceneInsert:
    onSceneInsert(av);
    updateMorphTargetsOrSomething(av);
    FUN_0003eeb0();
    if ((av->node0x918).prev == (avatar_0x918)0x0) {
                    // Sets newEntities
      FUN_0002ccd0(&Game::SceneInfo.field13_0x70,(int *)&av->node0x918);
    }
    if (av->model != (Model *)0x0) {
      FUN_0003cae0(av);
    }
    FUN_0003b420();
    ::actor::executeCallout((actor *)av,0,PermanentEffect);
    return;
  case Scene_AvatarRemoved:
    paVar1 = (msg->header).someActor;
    if (*(actor **)&av->field_0x11c == paVar1) {
      *(undefined4 *)&av->field_0x11c = 0;
    }
    if (paVar1 == (actor *)av) {
      FUN_0003b560();
      return;
    }
    break;
  case Scene_End:
    removeavatarfromsomelistsshit(av);
    FUN_00042040();
    return;
  case Scene_Prepare:
    onScenePrepare(av);
    return;
  case Scene_Sfx_UpdatePos:
    FUN_00041e30((msg->header).someActor);
    break;
  default:
    goto LAB_0003f0b0;
  }
LAB_0003f0b0:
  return;
}




BOOL avatar::loadTransforms(avatar *av)

{
  Model *pMVar1;
  ModelSubresource *pMVar2;
  AvatarMatrix *pAVar3;
  ndMtxArray *ndMtxArray;
  uint32_t num_matrices;
  AvatarMatrix *pvVar2;
  uint uVar4;
  int i;
  int a_mat;
  
  pMVar1 = av->model;
  if ((((pMVar1 != (Model *)0x0) && (pMVar1->descriptor != (ModelDescriptor *)0x0)) &&
      (pMVar1->descriptor->runtimeCtx->subres0x11 != (Subresource0x11 *)0x0)) &&
     (pMVar1 != (Model *)0x0)) {
    pMVar2 = pMVar1->descriptor->runtimeCtx->modelSubresource;
    *(ModelVariableData **)&av->field_0x294 = &pMVar1->varData;
    ndMtxArray = (ndMtxArray *)MeshHeader::getFirstDescendantByType(pMVar2,0,"ndMtxArray");
    av->ndMtxArray = ndMtxArray;
    if (ndMtxArray != (ndMtxArray *)0x0) {
      num_matrices = ::ndMtxArray::getNumMatrices(ndMtxArray);
      av->numTransforms = num_matrices;
      pvVar2 = malloc_(num_matrices * 0x48);
      av->transforms = pvVar2;
      i = 0;
      if (0 < av->numTransforms) {
        a_mat = 0;
        do {
          pAVar3 = av->transforms;
          *(undefined4 *)((int)&(pAVar3->pos).z + a_mat) = 0;
          *(undefined4 *)((int)&(pAVar3->pos).y + a_mat) = 0;
          *(undefined4 *)((int)&(pAVar3->pos).x + a_mat) = 0;
          *(undefined4 *)((int)&(pAVar3->rotEuler).z + a_mat) = 0;
          *(undefined4 *)((int)&(pAVar3->rotEuler).y + a_mat) = 0;
          *(undefined4 *)((int)&(pAVar3->rotEuler).x + a_mat) = 0;
          *(float *)((int)&(pAVar3->scale).x + a_mat) = 1.0;
          *(float *)((int)&(pAVar3->scale).y + a_mat) = 1.0;
          *(float *)((int)&(pAVar3->scale).z + a_mat) = 1.0;
          *(undefined4 *)((int)&(pAVar3->field4_0x28).z + a_mat) = 0;
          *(undefined4 *)((int)&(pAVar3->field4_0x28).y + a_mat) = 0;
          *(undefined4 *)((int)&(pAVar3->field4_0x28).x + a_mat) = 0;
          av->field234_0x29c = 0;
          av->field235_0x2a0 = 0;
          *(undefined4 *)((int)&av->transforms->field9_0x44 + a_mat) = 0;
          uVar4 = ::ndMtxArray::getSomeFlagValue(av->ndMtxArray,i);
          *(uint *)((int)&av->transforms->matrixFlagVal + a_mat) = uVar4;
          *(undefined4 *)((int)&av->transforms->importantFloat + a_mat) = 0;
          i = i + 1;
          a_mat = a_mat + 0x48;
        } while (i < av->numTransforms);
      }
      return 1;
    }
  }
  return 0;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


AffineTransform * avatar::getBoneAffineByIndex(avatar *param_1,int affineIndex)

{
  Model *pMVar1;
  AffineTransform *pAVar2;
  Skeleton *skeleton;
  
  pMVar1 = param_1->model;
  if (pMVar1 == (Model *)0x0) {
    skeleton = (Skeleton *)0x0;
  }
  else {
    skeleton = pMVar1->skeleton;
    if (skeleton != (Skeleton *)0x0) goto LAB_00040b65;
    skeleton = pMVar1->skeleton2;
  }
  if (skeleton == (Skeleton *)0x0) {
    return (AffineTransform *)0x0;
  }
LAB_00040b65:
  pAVar2 = Skeleton::getBoneAffineIntoGlobal(skeleton,affineIndex);
  return pAVar2;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


BOOL avatar::setModel(avatar *this,char *name)

{
  void *pvVar4;
  Model *model_res;
  int iVar7;
  char *asset_name_ptr;
  avatar *ava;
  char cVar2;
  
  asset_name_ptr = this->modelAID;
  *asset_name_ptr = '\0';
  if (this->model != (Model *)0x0) {
    pvVar4 = (void *)ModelResource::dropResource((Asset *)this->model);
    Assets::DestroyAssetOrDecrement(pvVar4);
    this->model = (Model *)0x0;
  }
  ava = this;
  if ((name != (char *)0x0) && (*(int *)name == 0x5f646961)) {
    Assets::GetResourceBytes(name,&this);
    if (this == (avatar *)0x0) {
      runtime::ExitGame(2);
      return 0;
    }
    iVar7 = (int)asset_name_ptr - (int)name;
    do {
      cVar2 = *name;
      name[iVar7] = cVar2;
      name = name + 1;
                    // Write the model name into the avatar
    } while (cVar2 != '\0');
    model_res = Model::ctor((ModelDescriptor *)this,1,1);
    ava->model = model_res;
  }
  return 1;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void avatar::updateBaseTransform(avatar *avatar)

{
  avatar_0x918 pEVar1;
  vec3 rot_v;
  vec3 pos_v;
  vec3 scale_v;
  AffineTransform local_30;
  AvatarPhysicsContext *render_mats;
  float scale;
  
  render_mats = avatar->physicsCtx;
  if (render_mats != (AvatarPhysicsContext *)0x0) {
    if ((render_mats->actor != (actor *)0x0) ||
       ((pEVar1 = (avatar->node0x918).prev, pEVar1 != (avatar_0x918)0x0 &&
        (pEVar1->prev != (avatar_0x918)0x0)))) {
      pos_v.x = (avatar->pos).x;
      pos_v.y = (avatar->pos).y;
      pos_v.z = (avatar->pos).z;
      rot_v.x = (avatar->rotEuler).x;
      rot_v.y = (avatar->rotEuler).y;
      rot_v.z = (avatar->rotEuler).z;
      scale = avatar->uniformScale;
      scale_v.x = (avatar->scale).x * scale;
      scale_v.y = (avatar->scale).y * scale;
      scale_v.z = (avatar->scale).z * scale;
      Maths::TransformMatrixFromPosRot(&pos_v,&rot_v,&scale_v,&local_30,(AffineTransform *)0x0);
      normaliseMatrixAndPhysics(avatar);
      Graphics::leftCombineTransforms(&avatar->drawAffine,&avatar->physicsCtx->affine,&local_30);
      Maths::InvertAffineMatrix
                ((D3DXMATRIX *)&avatar->drawAffine,(D3DMATRIX *)&avatar->baseTransform);
      return;
    }
    free(render_mats);
    avatar->physicsCtx = (AvatarPhysicsContext *)0x0;
  }
  if (avatar->anglesCalculated == 0) {
    pos_v.x = (avatar->pos).x;
    pos_v.y = (avatar->pos).y;
    pos_v.z = (avatar->pos).z;
    scale_v.x = (avatar->rotEuler).x;
    scale_v.y = (avatar->rotEuler).y;
    scale_v.z = (avatar->rotEuler).z;
    scale = avatar->uniformScale;
    rot_v.x = (avatar->scale).x * scale;
    rot_v.y = (avatar->scale).y * scale;
    rot_v.z = (avatar->scale).z * scale;
    Maths::TransformMatrixFromPosRot
              (&pos_v,&scale_v,&rot_v,&avatar->drawAffine,&avatar->baseTransform);
    avatar->anglesCalculated = 1;
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void avatar::updateAndGetAffine(avatar *av,AffineTransform *outAffine,vec3 *targetPos)

{
  AvatarPhysicsContext *ptr;
  avatar_0x918 pEVar1;
  vec3 pos;
  vec3 local_48;
  vec3 local_3c;
  AffineTransform someAffine;
  
  ptr = av->physicsCtx;
  if (ptr != (AvatarPhysicsContext *)0x0) {
    if ((ptr->actor != (actor *)0x0) ||
       ((pEVar1 = (av->node0x918).prev, pEVar1 != (avatar_0x918)0x0 &&
        (pEVar1->prev != (avatar_0x918)0x0)))) {
      if (targetPos == (vec3 *)0x0) {
        pos.x = (av->pos).x;
        pos.y = (av->pos).y;
        pos.z = (av->pos).z;
      }
      else {
        pos.x = targetPos->x;
        pos.y = targetPos->y;
        pos.z = targetPos->z;
      }
      local_48.x = (av->rotEuler).x;
      local_48.y = (av->rotEuler).y;
      local_48.z = (av->rotEuler).z;
      local_3c.z = av->uniformScale;
      local_3c.x = local_3c.z * (av->scale).x;
      local_3c.y = (av->scale).y * local_3c.z;
      local_3c.z = (av->scale).z * local_3c.z;
      Maths::TransformMatrixFromPosRot(&pos,&local_48,&local_3c,&someAffine,(AffineTransform *)0x0);
      normaliseMatrixAndPhysics(av);
      Graphics::leftCombineTransforms(outAffine,&av->physicsCtx->affine,&someAffine);
      return;
    }
    free(ptr);
    av->physicsCtx = (AvatarPhysicsContext *)0x0;
  }
  getAffines(av,targetPos,outAffine,0);
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields

void avatar::getAffines(avatar *av,vec3 *pos,AffineTransform *affine1Out,AffineTransform *affine2Out
                       )

{
  vec3 someVec;
  vec3 eulers;
  vec3 scale;
  
  if (pos == (vec3 *)0x0) {
    someVec.x = (av->pos).x;
    someVec.y = (av->pos).y;
    someVec.z = (av->pos).z;
  }
  else {
    someVec.x = pos->x;
    someVec.y = pos->y;
    someVec.z = pos->z;
  }
  eulers.x = (av->rotEuler).x;
  eulers.y = (av->rotEuler).y;
  eulers.z = (av->rotEuler).z;
  scale.z = av->uniformScale;
  scale.x = scale.z * (av->scale).x;
  scale.y = (av->scale).y * scale.z;
  scale.z = (av->scale).z * scale.z;
  Maths::TransformMatrixFromPosRot(&someVec,&eulers,&scale,affine1Out,affine2Out);
  return;
}




avatarParams * avatarParams::init(avatarParams *param_1)

{
  char *pcVar2;
  char cVar1;
  
  (param_1->objParams).paramsSize = 0x334;
  (param_1->objParams).objInitValue = 0x3e;
  (param_1->objParams).typeIndex = 2;
  (param_1->pos).z = 0.0;
  (param_1->pos).y = 0.0;
  (param_1->pos).x = 0.0;
  (param_1->rotEuler).z = 0.0;
  (param_1->rotEuler).y = 0.0;
  (param_1->rotEuler).x = 0.0;
  pcVar2 = g_GlobalAssetName;
  param_1->scale = 1.0;
  param_1->field4_0x24 = 1.0;
  do {
    cVar1 = *pcVar2;
    (param_1[-0x1a58].modelAID + 0x58)[(int)pcVar2] = cVar1;
    pcVar2 = pcVar2 + 1;
  } while (cVar1 != '\0');
  pcVar2 = g_GlobalAssetName;
  do {
    cVar1 = *pcVar2;
    pcVar2[(int)(param_1[-0x1a58].modelAID + -0x28)] = cVar1;
    pcVar2 = pcVar2 + 1;
  } while (cVar1 != '\0');
  pcVar2 = g_GlobalAssetName;
  do {
    cVar1 = *pcVar2;
    (param_1[-0x1a58].animtableAID + 0x58)[(int)pcVar2] = cVar1;
    pcVar2 = pcVar2 + 1;
  } while (cVar1 != '\0');
  pcVar2 = g_GlobalAssetName;
  do {
    cVar1 = *pcVar2;
    (param_1[-0x1a58].standAnimationAID + 0x58)[(int)pcVar2] = cVar1;
    pcVar2 = pcVar2 + 1;
  } while (cVar1 != '\0');
  pcVar2 = g_GlobalAssetName;
  do {
    cVar1 = *pcVar2;
    (param_1[-0x1a58].calloutAID + 0x58)[(int)pcVar2] = cVar1;
    pcVar2 = pcVar2 + 1;
  } while (cVar1 != '\0');
  pcVar2 = g_GlobalAssetName;
  *(undefined2 *)&param_1->impactId = 0xffff;
  param_1->hasShadow = 0;
  do {
    cVar1 = *pcVar2;
    (param_1[-0x1a58].fxEmitterImpactFlashAID + 100)[(int)pcVar2] = cVar1;
    pcVar2 = pcVar2 + 1;
  } while (cVar1 != '\0');
  *(undefined2 *)((int)&param_1->impactId + 2) = 0;
  param_1->ghoulyboxId2 = 0;
  return param_1;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void avatar::getWorldPosition(avatar *av,vec3 *outVec3)

{
  float fVar1;
  float fVar2;
  AvatarPhysicsContext *ptr;
  avatar_0x918 pEVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  
  ptr = av->physicsCtx;
  if (ptr != (AvatarPhysicsContext *)0x0) {
    if ((ptr->actor != (actor *)0x0) ||
       ((pEVar3 = (av->node0x918).prev, pEVar3 != (avatar_0x918)0x0 &&
        (pEVar3->prev != (avatar_0x918)0x0)))) {
      fVar5 = (av->drawAffine).m[1][2] * Game::someGlobalPos.z;
      fVar4 = (av->drawAffine).m[1][1] * Game::someGlobalPos.y;
      fVar6 = (av->drawAffine).m[1][0] * Game::someGlobalPos.x;
      fVar1 = (av->drawAffine).m[1][3];
      fVar7 = (av->drawAffine).m[2][1] * Game::someGlobalPos.y;
      fVar8 = (av->drawAffine).m[2][2] * Game::someGlobalPos.z;
      fVar9 = (av->drawAffine).m[2][0] * Game::someGlobalPos.x;
      fVar2 = (av->drawAffine).m[2][3];
      outVec3->x = (av->drawAffine).m[0][1] * Game::someGlobalPos.y +
                   (av->drawAffine).m[0][2] * Game::someGlobalPos.z +
                   (av->drawAffine).m[0][0] * Game::someGlobalPos.x + (av->drawAffine).m[0][3];
      outVec3->y = fVar4 + fVar5 + fVar6 + fVar1;
      outVec3->z = fVar7 + fVar8 + fVar9 + fVar2;
      return;
    }
                    // Invalid sound pos
    free(ptr);
    av->physicsCtx = (AvatarPhysicsContext *)0x0;
  }
  outVec3->x = (av->pos).x;
  outVec3->y = (av->pos).y;
  outVec3->z = (av->pos).z;
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


float10 avatar::distanceBetweenAvatars(avatar *param_1,avatar *param_2)

{
  vec3 local_18;
  vec3 local_c;
  
  getWorldPosition(param_1,&local_18);
  getWorldPosition(param_2,&local_c);
  return SQRT(((float10)local_18.y - (float10)local_c.y) *
              ((float10)local_18.y - (float10)local_c.y) +
              ((float10)local_18.x - (float10)local_c.x) *
              ((float10)local_18.x - (float10)local_c.x) +
              ((float10)local_18.z - (float10)local_c.z) *
              ((float10)local_18.z - (float10)local_c.z));
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void avatar::setPosition(avatar *av,vec3 *newPos)

{
  avatar_0x918 pEVar1;
  float ax;
  float ay;
  float az;
  float bx;
  float fVar2;
  AvatarPhysicsContext *ptr;
  float py;
  float pz;
  float yOffset;
  float yrx;
  float yry;
  float yrz;
  float zOffset;
  float zry;
  float zrz;
  
  ptr = av->physicsCtx;
  if (ptr != (AvatarPhysicsContext *)0x0) {
    if ((ptr->actor != (actor *)0x0) ||
       ((pEVar1 = (av->node0x918).prev, pEVar1 != (avatar_0x918)0x0 &&
        (pEVar1->prev != (avatar_0x918)0x0)))) {
      yrx = (ptr->yRow).x;
      ax = newPos->x;
      fVar2 = (ptr->zRow).x;
      bx = newPos->x;
      yrz = (ptr->yRow).z;
      az = newPos->z;
      yry = (ptr->yRow).y;
      ay = newPos->y;
      zrz = (ptr->zRow).z;
      pz = newPos->z;
      yOffset = ptr->yOffset;
      zry = (ptr->zRow).y;
      py = newPos->y;
      zOffset = ptr->zOffset;
      (av->pos).x = (ptr->xRow).z * newPos->z + (ptr->xRow).y * newPos->y +
                    (ptr->xRow).x * newPos->x + ptr->xOffset;
      (av->pos).y = yrz * az + yrx * ax + yry * ay + yOffset;
      (av->pos).z = zrz * pz + fVar2 * bx + zry * py + zOffset;
      av->anglesCalculated = 0;
      return;
    }
    free(ptr);
    av->physicsCtx = (AvatarPhysicsContext *)0x0;
  }
  (av->pos).x = newPos->x;
  (av->pos).y = newPos->y;
  (av->pos).z = newPos->z;
  av->anglesCalculated = 0;
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void avatar::getWorldRotation(avatar *this,vec3 *v3)

{
  avatar_0x918 pEVar1;
  vec3 local_vec;
  AvatarPhysicsContext *p_ctx;
  
  p_ctx = this->physicsCtx;
  if (p_ctx != (AvatarPhysicsContext *)0x0) {
    if ((p_ctx->actor != (actor *)0x0) ||
       ((pEVar1 = (this->node0x918).prev, pEVar1 != (avatar_0x918)0x0 &&
        (pEVar1->prev != (avatar_0x918)0x0)))) {
      Math::GetEulerAngles((D3DXMATRIX *)&p_ctx->affine,&local_vec);
      v3->x = (this->rotEuler).x + local_vec.x;
      v3->y = (this->rotEuler).y + local_vec.y;
      v3->z = (this->rotEuler).z + local_vec.z;
      return;
    }
    free(p_ctx);
    this->physicsCtx = (AvatarPhysicsContext *)0x0;
  }
  v3->x = (this->rotEuler).x;
  v3->y = (this->rotEuler).y;
  v3->z = (this->rotEuler).z;
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void __thiscall avatar::setScaleUniform(avatar *this,float scale)

{
  if ((((this->scale).x != scale) || ((this->scale).y != scale)) || ((this->scale).z != scale)) {
    (this->scale).x = scale;
    (this->scale).y = scale;
    (this->scale).z = scale;
    this->anglesCalculated = 0;
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void avatar::loadBoneIndices(avatar *this)

{
  ModelDescriptor *pMVar1;
  ushort bone_index;
  uint uVar2;
  ModelFooterEntry *pMVar3;
  avatarModel0x9_ptr_138_undefined instance9;
  ModelSubresource0x9Lookup_ptr_5_undefined1 lookup;
  ModelSubresource0x9 *subres_0x9;
  uint32_t lookupIndex;
  
  lookup = &ModelSubres0x9::lut[0].field2_0x5;
  instance9 = &this->model0x9s[0].someU8;
  do {
    ADJ(instance9)->someU8 = '\x01';
    bone_index = 0xffff;
    ADJ(instance9).indexValue = 0xffff;
    ADJ(instance9)->val0x4 = ADJ(lookup)->field1_0x4;
    ADJ(instance9)->field_0xad = ADJ(lookup)->field2_0x5;
    lookupIndex = ADJ(lookup).lookupIndex;
    if (lookupIndex != 0xffffffff) {
      if ((this->model != (Model *)0x0) &&
         (pMVar1 = this->model->descriptor, pMVar1 != (ModelDescriptor *)0x0)) {
        uVar2 = 0;
        if (pMVar1->numFooterEntries != 0) {
          pMVar3 = pMVar1->footerEntries;
          do {
            if (pMVar3->subresourceType == RigidBoneIndices) {
              subres_0x9 = (ModelSubresource0x9 *)pMVar1->footerEntries[uVar2].offset;
              if (subres_0x9 != (ModelSubresource0x9 *)0x0) {
                bone_index = (ushort)subres_0x9->indices[(short)lookupIndex];
                goto LAB_00041c42;
              }
              break;
            }
            uVar2 = uVar2 + 1;
            pMVar3 = pMVar3 + 1;
          } while (uVar2 < pMVar1->numFooterEntries);
        }
        bone_index = 0xff;
LAB_00041c42:
        if (bone_index != 0xff) goto ValidIndex;
      }
      bone_index = 0xffff;
    }
ValidIndex:
    ADJ(instance9)->boneIndex = bone_index;
    lookup = lookup + 8;
    instance9 = instance9 + 0xb8;
    if (0x2fd204 < (int)lookup) {
      return;
    }
  } while( true );
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void avatar::setShadowModel(avatar *this,char *shadowAID)

{
  Model *pMVar1;
  char *name;
  void *pvVar2;
  Model *shadow_model;
  Skeleton *pSVar3;
  
  name = shadowAID;
  if (this->shadowModel != (Model *)0x0) {
    pvVar2 = (void *)ModelResource::dropResource((Asset *)this->shadowModel);
    Assets::DestroyAssetOrDecrement(pvVar2);
    this->shadowModel = (Model *)0x0;
  }
  if (*(int *)name == 0x5f646961) {
    Assets::GetResourceBytes(name,&shadowAID);
    if (shadowAID == (char *)0x0) {
      shadowAID = (char *)0x2;
      runtime::ExitGame(2);
      return;
    }
    shadow_model = Model::ctor((ModelDescriptor *)shadowAID,0,0);
    this->shadowModel = shadow_model;
    pMVar1 = this->model;
    if (pMVar1 == (Model *)0x0) {
      pSVar3 = (Skeleton *)0x0;
    }
    else {
      pSVar3 = pMVar1->skeleton;
      if (pSVar3 == (Skeleton *)0x0) {
        pSVar3 = pMVar1->skeleton2;
      }
    }
    shadow_model->skeleton = pSVar3;
    this->shadowModel->initialised = 1;
  }
  return;
}




void avatar::update(avatar *av)

{
  int iVar1;
  DataForInfoFromBackground_conflict1 *node;
  ModelSubresource *pMVar2;
  int iVar3;
  float delta;
  float delta2;
  float speed;
  float newVz;
  float newVy;
  float newVx;
  float v1z;
  
  speed = 0.0;
  if (runtime::dx_timer <= 0.0) {
    delta = runtime::DeltaTime * runtime::TimeScale;
  }
  else {
    delta = 0.0;
  }
  if (av->movementFreezeTimer <= 0.0) {
    speed = av->actionSpeed;
  }
  if (av->keyframeContext != (KeyframeContext *)0x0) {
    KeyframeContext::updateFromAvatar
              (av->keyframeContext,av->model,(uint)(av->preventAnimChannelAdvancing == 0),
               speed * delta);
  }
  if (av->keyframeContext != (KeyframeContext *)0x0) {
                    // Updates door position and green question mark
    KeyframeContext::updateSkeletonAndBlendTargets
              ((uint)(av->preventAnimChannelAdvancing == 0),av->keyframeContext,av->model,
               av->boneList);
  }
  iVar3 = *(int *)&av->field_0x1d8;
  while (iVar3 != 0) {
    iVar1 = *(int *)(iVar3 + 4);
    (**(code **)(*(int *)(iVar3 + -8) + 0x10))(iVar3 + -8,av);
    iVar3 = iVar1;
  }
  updateFx(av);
  for (node = (av->infoList).prev; node != (DataForInfoFromBackground_conflict1 *)0x0;
      node = (DataForInfoFromBackground_conflict1 *)node->field1_0x4) {
    FUN_0011be40((AvatarInfoNode *)node);
  }
  newVz = (av->smoothedTargetPos).z;
  newVy = (av->smoothedTargetPos).y;
  newVx = (av->smoothedTargetPos).x;
  if (Game::UseMovementSmoothing != 0) {
    delta = (av->smoothedCurrentPos).x;
    delta2 = (av->smoothedCurrentPos).y;
    v1z = (av->smoothedCurrentPos).z;
    newVx = (newVx - delta) * 0.1 + delta;
    newVy = (newVy - delta2) * 0.1 + delta2;
    newVz = (newVz - v1z) * 0.1 + v1z;
  }
  (av->smoothedCurrentPos).x = newVx;
  (av->smoothedCurrentPos).y = newVy;
  (av->smoothedCurrentPos).z = newVz;
  if ((av->model != (Model *)0x0) &&
     (pMVar2 = av->model->modelPassedToBG, pMVar2 != (ModelSubresource *)0x0)) {
    background::updateModelChildren_(pMVar2,1.0);
  }
  if ((ShouldntDroneBools[1] == 0) && ("\x01"[Game::CheckMoveOn] != '\0')) {
    if (runtime::dx_timer <= 0.0) {
      delta = runtime::DeltaTime * runtime::TimeScale;
    }
    else {
      delta = 0.0;
    }
    if ((0.0 < av->movementFreezeTimer) &&
       (delta = av->movementFreezeTimer - delta, av->movementFreezeTimer = delta, delta <= 0.0)) {
      av->movementFreezeTimer = 0.0;
    }
  }
  delta = 0.0;
  if (runtime::dx_timer <= 0.0) {
    delta2 = runtime::DeltaTime * runtime::TimeScale;
  }
  else {
    delta2 = 0.0;
  }
  if (av->movementFreezeTimer <= 0.0) {
    delta = av->actionSpeed;
  }
  av->timeAlive = delta * delta2 + av->timeAlive;
  av->timesUpdated = av->timesUpdated + 1;
  return;
}




BOOL avatar::decreaseTimer(avatar *av,float *timer)

{
  float delta;
  float speed;
  
  if (runtime::dx_timer <= 0.0) {
    delta = runtime::DeltaTime * runtime::TimeScale;
  }
  else {
    delta = 0.0;
  }
  speed = 0.0;
  if (av->movementFreezeTimer <= 0.0) {
    speed = av->actionSpeed;
  }
  if ((0.0 < *timer) && (delta = *timer - speed * delta, *timer = delta, delta <= 0.0)) {
    *timer = 0.0;
    return 1;
  }
  return 0;
}




CollisionMask avatar::getCollisionMaskFromModel(avatar *this)

{
  ModelDescriptor *pMVar1;
  uint uVar2;
  uint32_t uVar3;
  ModelFooterEntry *pMVar4;
  AnimCollisionSubresourceEntry *pAVar5;
  CollisionMask CVar6;
  AnimCollisionSubresource *piVar3;
  
  if ((this->model != (Model *)0x0) &&
     (pMVar1 = this->model->descriptor, pMVar1 != (ModelDescriptor *)0x0)) {
    uVar2 = 0;
    if (pMVar1->numFooterEntries != 0) {
      pMVar4 = pMVar1->footerEntries;
      do {
        if (pMVar4->subresourceType == AnimColliders) {
          piVar3 = (AnimCollisionSubresource *)pMVar1->footerEntries[uVar2].offset;
          if (piVar3 == (AnimCollisionSubresource *)0x0) {
            return Nothing;
          }
          pAVar5 = piVar3->entries;
          uVar3 = piVar3->numTargets;
          CVar6 = Nothing;
          if (0 < (int)uVar3) {
            do {
              CVar6 = CVar6 | pAVar5->collisionMask;
              if (pAVar5->size == 0) {
                pAVar5 = (AnimCollisionSubresourceEntry *)0x0;
              }
              else {
                pAVar5 = (AnimCollisionSubresourceEntry *)
                         (&pAVar5->colliderType + (byte)pAVar5->size);
              }
              uVar3 = uVar3 - 1;
            } while (uVar3 != 0);
          }
          return CVar6;
        }
        uVar2 = uVar2 + 1;
        pMVar4 = pMVar4 + 1;
      } while (uVar2 < pMVar1->numFooterEntries);
    }
  }
  return Nothing;
}




void avatar::updateBlendTarget(short index,uint newFlags,avatar *av)

{
  uint32_t *puVar1;
  
  if (av->model != (Model *)0x0) {
    puVar1 = av->model->boneIndices + index;
    *puVar1 = *puVar1 | newFlags;
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields

int recalculatePunchAndCollisionStuff
              (avatar *av,SomeActorBodyList *param_2,CollisionMask param_3,int param_4)

{
  float fVar1;
  ModelDescriptor *pMVar2;
  Model *pMVar3;
  void *pvVar4;
  undefined1 *puVar5;
  ushort *puVar6;
  char *pcVar7;
  avatar *av_00;
  uint uVar8;
  undefined4 uVar9;
  Buffer *pBVar10;
  int iVar11;
  ModelFooterEntry *pMVar12;
  float *pfVar13;
  AnimCollisionSubresourceEntry *entry;
  char *pcVar14;
  float10 fVar15;
  float10 fVar16;
  float10 extraout_ST0;
  float fVar17;
  float local_30;
  float local_2c;
  float local_28;
  float local_24;
  float local_20;
  float local_1c;
  vec3 local_18;
  vec3 local_c;
  
  av_00 = av;
  avatar::getWorldPosition(av,&local_18);
  if ((av->model != (Model *)0x0) &&
     (pMVar2 = av->model->descriptor, pMVar2 != (ModelDescriptor *)0x0)) {
    uVar8 = 0;
    if (pMVar2->numFooterEntries != 0) {
      pMVar12 = pMVar2->footerEntries;
      do {
        if (pMVar12->subresourceType == AnimColliders) {
          uVar8 = pMVar2->footerEntries[uVar8].offset;
          if (uVar8 != 0) {
            pMVar3 = av->model;
            if (pMVar3 == (Model *)0x0) {
              av = (avatar *)0x0;
            }
            else {
              av = (avatar *)pMVar3->skeleton;
              if (av == (avatar *)0x0) {
                av = (avatar *)pMVar3->skeleton2;
              }
            }
            iVar11 = *(int *)&av_00->field_0x8fc;
            if (iVar11 == 0) {
              FUN_00042640();
              uVar9 = FUN_00066260(0x28);
              *(undefined4 *)&av_00->field_0x8fc = uVar9;
            }
            else {
              *(undefined4 *)(iVar11 + 8) = *(undefined4 *)(iVar11 + 4);
            }
            entry = (AnimCollisionSubresourceEntry *)(uVar8 + 8);
            local_1c = 0.0;
            local_20 = 0.0;
            local_24 = 0.0;
            goto joined_r0x00042811;
          }
          break;
        }
        uVar8 = uVar8 + 1;
        pMVar12 = pMVar12 + 1;
      } while (uVar8 < pMVar2->numFooterEntries);
    }
  }
  fVar15 = (float10)FUN_0003db30();
  fVar16 = (float10)FUN_0003db90();
  param_2->field0_0x0 = '\x04';
  param_2->field1_0x1 = ' ';
  param_2->field2_0x2 = '\x01';
  (param_2->pos).x = local_18.x;
  (param_2->pos).y = local_18.y;
  (param_2->pos).z = local_18.z;
  param_2->someFloat = (float)fVar16;
  param_2->someYScale = 0.0;
  *(undefined4 *)&param_2->field_0x18 = 0;
  param_2->field11_0x1c = (float)fVar15;
  return 0;
joined_r0x00042811:
  if (entry == (AnimCollisionSubresourceEntry *)0x0) goto LAB_00042963;
  if ((entry->collisionMask & param_3) != Nothing) {
    if (entry->colliderType == Sphere) {
      pBVar10 = *(Buffer **)&av_00->field_0x8fc;
      if (pBVar10->tail == pBVar10->end) {
        pBVar10 = runtime::ExtendArray(pBVar10);
        *(Buffer **)&av_00->field_0x8fc = pBVar10;
      }
      puVar5 = pBVar10->tail;
      pBVar10->tail = puVar5 + pBVar10->valueSize;
      checkCollisionAgainstSkeleton(entry,(Skeleton *)av,&local_c,&av_00->drawAffine);
      *puVar5 = 1;
      puVar5[1] = 0x14;
      puVar5[2] = 1;
      *(float *)(puVar5 + 4) = local_c.x;
      *(float *)(puVar5 + 8) = local_c.y;
      *(float *)(puVar5 + 0xc) = local_c.z;
      *(float *)(puVar5 + 0x10) = (float)extraout_ST0;
      fVar17 = *(float *)(puVar5 + 4);
      local_20 = *(float *)(puVar5 + 8) + local_20;
      fVar1 = *(float *)(puVar5 + 0xc);
    }
    else {
      if (entry->colliderType != Cylinder) goto LAB_00042951;
      pBVar10 = *(Buffer **)&av_00->field_0x8fc;
      if (pBVar10->tail == pBVar10->end) {
        pBVar10 = runtime::ExtendArray(pBVar10);
        *(Buffer **)&av_00->field_0x8fc = pBVar10;
      }
      pvVar4 = pBVar10->tail;
      pBVar10->tail = (void *)((uint)pBVar10->valueSize + (int)pvVar4);
      FUN_00055aa0(pvVar4);
      fVar17 = *(float *)((int)pvVar4 + 4);
      fVar1 = *(float *)((int)pvVar4 + 0xc);
      local_20 = *(float *)((int)pvVar4 + 0x14) + *(float *)((int)pvVar4 + 8) + local_20;
    }
    local_1c = fVar1 + local_1c;
    local_24 = fVar17 + local_24;
  }
LAB_00042951:
  if (entry->size == 0) goto LAB_00042963;
  entry = (AnimCollisionSubresourceEntry *)(&entry->colliderType + (byte)entry->size);
  goto joined_r0x00042811;
LAB_00042963:
  puVar6 = *(ushort **)&av_00->field_0x8fc;
  if ((*(int *)(puVar6 + 4) - *(int *)(puVar6 + 2)) / (int)(uint)*puVar6 == 0) {
    return 0;
  }
  if (param_4 == 0) {
    avatar::getWorldPosition(av_00,&local_18);
  }
  else {
    iVar11 = (*(int *)(puVar6 + 4) - *(int *)(puVar6 + 2)) / (int)(uint)*puVar6;
    local_18.z = (float)iVar11;
    if (iVar11 < 0) {
      local_18.z = local_18.z + 4.2949673e+09;
    }
    local_18.z = 1.0 / local_18.z;
    local_18.x = local_24 * local_18.z;
    local_18.y = local_20 * local_18.z;
    local_18.z = local_1c * local_18.z;
  }
  pcVar14 = *(char **)(*(int *)&av_00->field_0x8fc + 4);
  pcVar7 = *(char **)(*(int *)&av_00->field_0x8fc + 8);
  local_28 = 0.0;
  local_2c = local_18.y;
  local_30 = local_18.y;
  if (pcVar14 < pcVar7) {
    pfVar13 = (float *)(pcVar14 + 0xc);
    do {
      if (*pcVar14 == '\x01') {
        fVar15 = scaled_invsqrt((*pfVar13 - local_18.z) * (*pfVar13 - local_18.z) +
                                (pfVar13[-2] - local_18.x) * (pfVar13[-2] - local_18.x));
        if (local_28 < (float)(fVar15 + (float10)pfVar13[1])) {
          local_28 = (float)(fVar15 + (float10)pfVar13[1]);
        }
        if (pfVar13[-1] - pfVar13[1] <= local_2c) {
          local_2c = pfVar13[-1] - pfVar13[1];
        }
        fVar17 = pfVar13[1];
LAB_00042b03:
        if (local_30 < fVar17 + pfVar13[-1]) {
          local_30 = fVar17 + pfVar13[-1];
        }
      }
      else if (*pcVar14 == '\x04') {
        fVar15 = scaled_invsqrt((*pfVar13 - local_18.z) * (*pfVar13 - local_18.z) +
                                (pfVar13[-2] - local_18.x) * (pfVar13[-2] - local_18.x));
        if (local_28 < (float)(fVar15 + (float10)pfVar13[4])) {
          local_28 = (float)(fVar15 + (float10)pfVar13[4]);
        }
        if (pfVar13[-1] <= local_2c) {
          local_2c = pfVar13[-1];
        }
        fVar17 = pfVar13[2];
        goto LAB_00042b03;
      }
      pcVar14 = pcVar14 + 0x28;
      pfVar13 = pfVar13 + 10;
    } while (pcVar14 < pcVar7);
  }
  param_2->field0_0x0 = '\x04';
  param_2->field1_0x1 = ' ';
  param_2->field2_0x2 = '\x01';
  (param_2->pos).x = local_18.x;
  (param_2->pos).y = local_2c;
  (param_2->pos).z = local_18.z;
  param_2->someYScale = 0.0;
  *(undefined4 *)&param_2->field_0x18 = 0;
  param_2->someFloat = local_30 - local_2c;
  param_2->field11_0x1c = local_28;
  puVar6 = *(ushort **)&av_00->field_0x8fc;
  return (*(int *)(puVar6 + 4) - *(int *)(puVar6 + 2)) / (int)(uint)*puVar6;
}




BOOL avatar::extractCollider(avatar *av,uint32_t param_2,InfoFromBackground *info,ushort *param_4)

{
  float fVar1;
  ushort uVar2;
  Model *pMVar3;
  bool bVar4;
  uint uVar5;
  ModelDescriptor *pMVar6;
  ModelFooterEntry *pMVar7;
  Skeleton *skeleton;
  AnimCollisionSubresourceEntry *entry;
  float10 extraout_ST0;
  float10 fVar8;
  background *pbVar9;
  float local_24;
  float local_20;
  float local_1c;
  float local_18;
  float local_14;
  float local_10;
  vec3 local_c;
  
  if ((av->model != (Model *)0x0) &&
     (pMVar6 = av->model->descriptor, pMVar6 != (ModelDescriptor *)0x0)) {
    uVar5 = 0;
    if (pMVar6->numFooterEntries != 0) {
      pMVar7 = pMVar6->footerEntries;
      while (pMVar7->subresourceType != AnimColliders) {
        uVar5 = uVar5 + 1;
        pMVar7 = pMVar7 + 1;
        if (pMVar6->numFooterEntries <= uVar5) {
          return 0;
        }
      }
      uVar5 = pMVar6->footerEntries[uVar5].offset;
      if (uVar5 != 0) {
        pMVar3 = av->model;
        if (pMVar3 == (Model *)0x0) {
          skeleton = (Skeleton *)0x0;
        }
        else {
          skeleton = pMVar3->skeleton;
          if (skeleton == (Skeleton *)0x0) {
            skeleton = pMVar3->skeleton2;
          }
        }
        entry = (AnimCollisionSubresourceEntry *)(uVar5 + 8);
        bVar4 = false;
        if (entry != (AnimCollisionSubresourceEntry *)0x0) {
          do {
            if ((((entry->collisionMask & Mask0x40) != Nothing) &&
                (entry->colliderType == PartSphere)) && (entry->groupOrIndex == param_2)) {
              checkCollisionAgainstSkeleton(entry,skeleton,&local_c,&av->drawAffine);
              fVar1 = (float)extraout_ST0;
              if (bVar4) {
                if (local_c.x - fVar1 <= local_18) {
                  local_18 = local_c.x - fVar1;
                }
                if (local_c.y - fVar1 <= local_14) {
                  local_14 = local_c.y - fVar1;
                }
                if (local_c.z - fVar1 <= local_10) {
                  local_10 = local_c.z - fVar1;
                }
                if (local_24 < local_c.x + fVar1) {
                  local_24 = local_c.x + fVar1;
                }
                if (local_20 < local_c.y + fVar1) {
                  local_20 = local_c.y + fVar1;
                }
                if (local_1c < local_c.z + fVar1) {
                  local_1c = local_c.z + fVar1;
                }
              }
              else {
                local_14 = local_c.y - fVar1;
                local_10 = local_c.z - fVar1;
                local_24 = local_c.x + fVar1;
                local_20 = local_c.y + fVar1;
                local_18 = local_c.x - fVar1;
                bVar4 = true;
                local_1c = local_c.z + fVar1;
              }
            }
          } while ((entry->size != 0) &&
                  (entry = (AnimCollisionSubresourceEntry *)
                           (&entry->colliderType + (byte)entry->size),
                  entry != (AnimCollisionSubresourceEntry *)0x0));
          if (bVar4) {
            if (av->model == (Model *)0x0) {
              pMVar6 = (ModelDescriptor *)0x0;
            }
            else {
              pMVar6 = av->model->descriptor;
            }
            uVar2 = *(ushort *)(&pMVar6->runtimeCtx->subres0x11[1].names + param_2 * 3);
            *param_4 = uVar2;
            if ((uVar2 != 0) && ((uVar2 < 3000 || (0xc37 < uVar2)))) {
              *param_4 = 0;
            }
            local_c.x = (local_24 - local_18) * 0.5 + local_18;
            local_c.z = (local_1c - local_10) * 0.5 + local_10;
            av = (avatar *)0x0;
            fVar8 = abs_float(local_c.x - local_18);
            if ((float10)0.0 < fVar8) {
              av = (avatar *)(float)fVar8;
            }
            fVar8 = abs_float(local_c.z - local_10);
            if ((float10)(float)av < fVar8) {
              av = (avatar *)(float)fVar8;
            }
            fVar8 = abs_float(local_c.x - local_24);
            if ((float10)(float)av < fVar8) {
              av = (avatar *)(float)fVar8;
            }
            fVar8 = abs_float(local_c.z - local_1c);
            pbVar9 = (background *)(float)fVar8;
            if (fVar8 <= (float10)(float)av) {
              pbVar9 = (background *)av;
            }
            info->field0_0x0 = 4;
            info->field1_0x1 = 0x20;
            info->field2_0x2 = 1;
            (info->someVec).x = local_c.x;
            (info->someVec).z = local_c.z;
            (info->someVec).y = local_14;
            info->xScale = 0.0;
            info->yScale = local_20 - local_14;
            info->zScale = 0.0;
            info->field8_0x1c = pbVar9;
            return 1;
          }
        }
        return 0;
      }
    }
  }
  return 0;
}




void avatar::callback0x1a0(avatar *param_1)

{
  BOOL BVar1;
  undefined4 unaff_ESI;
  vec2 v2_2;
  vec2 v2_1;
  vec3 local_c;
  
  if (DAT_0051120c == 0) {
    getHealthPos(param_1,&v2_2.x,&v2_1.x,&local_c);
    BVar1 = testPosition(v2_2.x,&local_c,&v2_1,&v2_2,unaff_ESI);
    if (BVar1 == 0) {
      FUN_00062220((vec2 *)0x0,(vec2 *)0x0);
      return;
    }
    FUN_00062220(&v2_1,&v2_2);
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void avatar::destroyFx_(avatar *param_1)

{
  float *pfVar1;
  short sVar2;
  Model *pMVar3;
  AvatarVTable *count;
  AvatarVTable *pAVar4;
  ndSkeletonBone *pnVar5;
  ModelFooterEntry *pMVar6;
  avatar *av;
  fxParticleImpactFlash *target;
  void *pvVar7;
  D3DXMATRIX *pDVar8;
  uint uVar9;
  uint uVar10;
  ModelFooterEntry *pMVar11;
  int iVar12;
  int iVar13;
  int local_34;
  int local_30;
  vec3 local_18;
  vec3 local_c;
  
  av = param_1;
  pMVar3 = param_1->model;
  if (pMVar3 == (Model *)0x0) {
    param_1 = (avatar *)0x0;
  }
  else {
    param_1 = (avatar *)pMVar3->skeleton;
    if (param_1 == (avatar *)0x0) {
      param_1 = (avatar *)pMVar3->skeleton2;
    }
  }
  count = param_1->vtable;
  pMVar3 = av->model;
  getWorldPosition(av,&local_c);
  getWorldRotation(av,&local_18);
  av->anglesCalculated = 0;
  updateBaseTransform(av);
  target = Assets::CreateFxParticleImpactFlash((char *)0x0,(uint)count,&local_c,&local_18);
  av[1].vtable = (AvatarVTable *)target;
  Assets::LoadAndExecuteScript(target,(uint *)0x0,"aid_fxemitter_ghoulies_weapon_bits_explodeone");
  pAVar4 = av[1].vtable;
  if (pAVar4[5].func6 != (void *)0x0) {
    Assets::DestroyAssetOrDecrement(pAVar4[5].func6);
    pAVar4[5].func6 = (void *)0x0;
  }
  if (pAVar4[5].checkForHitByWeapon != (Asset *)0x0) {
    pvVar7 = (void *)ModelResource::dropResource(pAVar4[5].checkForHitByWeapon);
    Assets::DestroyAssetOrDecrement(pvVar7);
    pAVar4[5].checkForHitByWeapon = (void *)0x0;
  }
  pAVar4[5].update = (void *)0x1;
  pvVar7 = malloc_((int)count * 0xc);
  iVar13 = 0;
  av[1].pos.y = (float)pvVar7;
  if (0 < (int)count) {
    local_30 = 0;
    local_34 = 0;
    do {
      if ((pMVar3->ndSkeleton == (ndSkeleton *)0x0) ||
         (pnVar5 = pMVar3->ndSkeleton->bonesStart, pnVar5 == (ndSkeletonBone *)0x0)) {
        iVar12 = 0;
      }
      else {
        iVar12 = (int)&pnVar5->parentBone + local_34;
      }
      pDVar8 = (D3DXMATRIX *)FUN_000316b0((float *)&av->drawAffine,iVar12,iVar13,(int)param_1);
      local_c.x = pDVar8->m[0][3];
      local_c.y = pDVar8->m[1][3];
      local_c.z = pDVar8->m[2][3];
      Math::GetEulerAngles(pDVar8,&local_18);
      AffineTransform::getScaleBases
                ((AffineTransform *)&pDVar8->field1,(vec3 *)((int)av[1].pos.y + local_30));
      pAVar4 = av[1].vtable;
      sVar2 = *(short *)((int)&pAVar4->ctor + 2);
      pvVar7 = pAVar4[5].dtor;
      if (sVar2 != -1) {
        iVar12 = (int)sVar2;
        *(undefined2 *)((int)&pAVar4->ctor + 2) =
             *(undefined2 *)((int)pAVar4 + (iVar12 * 0xa8 + 0x1f5) * 2);
        *(undefined2 *)((int)pAVar4 + (iVar12 * 0xa8 + 0x1f5) * 2) = 0xfffe;
        *(AvatarVTable **)((int)pAVar4 + (iVar12 * 0xa8 + 0x26c) * 2) = pAVar4;
        *(void **)((int)pAVar4 + (iVar12 * 0xa8 + 0x26e) * 2) = pvVar7;
        *(short *)&pAVar4->getAllocDetails = *(short *)&pAVar4->getAllocDetails + 1;
        FUN_000ef8c0();
        if ((pAVar4[5].update == (void *)0x0) || (pAVar4[5].update == (void *)0x2)) {
          FUN_000efb20();
        }
      }
      pAVar4 = av[1].vtable;
      iVar12 = (short)iVar13 * 0x150;
      *(float *)(iVar12 + 0x390 + (int)pAVar4) = local_c.x;
      *(float *)(iVar12 + 0x394 + (int)pAVar4) = local_c.y;
      *(float *)(iVar12 + 0x398 + (int)pAVar4) = local_c.z;
      *(float *)(iVar12 + 0x39c + (int)pAVar4) = local_18.x;
      *(float *)((int)pAVar4 + iVar12 + 0x3a0) = local_18.y;
      *(float *)((int)pAVar4 + iVar12 + 0x3a4) = local_18.z;
      pAVar4 = av[1].vtable;
      *(undefined4 *)(iVar12 + 0x3b4 + (int)pAVar4) = 0x40490fdb;
      *(undefined4 *)(iVar12 + 0x3b8 + (int)pAVar4) = 0x40490fdb;
      *(undefined4 *)(iVar12 + 0x3bc + (int)pAVar4) = 0;
      uVar9 = runtime::rand * 0x19660d + 0x3c6ef35f;
      uVar10 = uVar9 * 0x19660d + 0x3c6ef35f;
      runtime::rand = uVar10 * 0x19660d + 0x3c6ef35f;
      local_18.z = 0.0;
      local_18.x = 3.1415927;
      local_18.y = 3.1415927;
      pfVar1 = (float *)(iVar12 + 0x3a8 + (int)av[1].vtable);
      *pfVar1 = ((float)(runtime::rand & 0x7fffff | 0x3f800000) - 1.0) * 20.0 - 10.0;
      pfVar1[1] = ((float)(uVar10 & 0x7fffff | 0x3f800000) - 1.0) * 40.0 + 40.0;
      pfVar1[2] = ((float)(uVar9 & 0x7fffff | 0x3f800000) - 1.0) * 20.0 - 10.0;
      iVar13 = iVar13 + 1;
      local_34 = local_34 + 0x20;
      local_30 = local_30 + 0xc;
    } while (iVar13 < (int)count);
  }
  uVar9 = pMVar3->descriptor->numFooterEntries;
  uVar10 = 0;
  if (uVar9 != 0) {
    pMVar6 = pMVar3->descriptor->footerEntries;
    pMVar11 = pMVar6;
    do {
      if (pMVar11->subresourceType == ModelFlags) {
        uVar9 = pMVar6[uVar10].offset;
        goto LAB_00067dee;
      }
      uVar10 = uVar10 + 1;
      pMVar11 = pMVar11 + 1;
    } while (uVar10 < uVar9);
  }
  uVar9 = 0;
LAB_00067dee:
  if ((int)uVar9 < 0) {
    if (av->model != (Model *)0x0) {
      ModelInstance::searchForValueWithFlags(3,av->model,0x1f);
    }
    if (av->shadowModel != (Model *)0x0) {
      ModelInstance::searchForValueWithFlags(3,av->shadowModel,0x1f);
    }
  }
  pMVar3->initialised = 1;
  return;
}




void avatar::getAllocDetails(ObjectAllocDetails *param_1)

{
  param_1->entitySize = 0x934;
  param_1->paramsSize = 0x334;
  return;
}



// WARNING: Globals starting with '_' overlap smaller symbols at the same address
// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void avatar::draw(avatar *av,undefined4 param_2,BOOL someFlag)

{
  draw(av,param_2,someFlag);
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void avatar::updateSkeletonBeforeScare(avatar *param_1)

{
  ModelDescriptor *modelRes;
  Model *pMVar1;
  byte bVar2;
  uint index;
  Skeleton *skeleton;
  
  if ((param_1->model == (Model *)0x0) ||
     (modelRes = param_1->model->descriptor, modelRes == (ModelDescriptor *)0x0)) {
LAB_00070434:
    index = 0xffffffff;
  }
  else {
    bVar2 = ModelDescriptor::getBoneIdxFromRigid(modelRes,0);
    index = (uint)bVar2;
    if (index == 0xff) goto LAB_00070434;
  }
  pMVar1 = param_1->model;
  if (pMVar1 == (Model *)0x0) {
    skeleton = (Skeleton *)0x0;
  }
  else {
    skeleton = pMVar1->skeleton;
    if (skeleton != (Skeleton *)0x0) goto LAB_0007045d;
    skeleton = pMVar1->skeleton2;
  }
  if (skeleton == (Skeleton *)0x0) {
    return;
  }
LAB_0007045d:
  Skeleton::getBoneAffineIntoGlobal(skeleton,index);
  return;
}



// WARNING: Globals starting with '_' overlap smaller symbols at the same address


void avatar::destroy(avatar *param_1)

{
  ObjMsgID local_4;
  
  pickup::DetachFromActor(param_1->statePickUp,(actor *)param_1);
  if (param_1->skipUpdate == 0) {
    local_4 = Scene_End;
    (*param_1->vtable->onMessage)(param_1,&local_4);
    if (param_1->skipUpdate == 0) {
      removeavatarfromsomelistsshit(param_1);
    }
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


AvatarInfoNode * avatar::newInfoNode(avatar *av,uint someUint)

{
  AvatarInfo *pAVar1;
  AvatarInfoNode *new_node;
  AvatarInfoOffsetLL *offset_node;
  int iVar2;
  AvatarInfoNode *node;
  AvatarInfo *info;
  int *llnext;
  AvatarInfoNode *next;
  
  new_node = malloc_(0x38);
  next = new_node;
  for (iVar2 = 0xe; iVar2 != 0; iVar2 = iVar2 + -1) {
    next->next = (AvatarInfoNode *)0x0;
    next = (AvatarInfoNode *)&next->prev;
  }
  (new_node->info).someUint = someUint;
  node = (AvatarInfoNode *)&av->infoList;
  (new_node->info).avatar = av;
  next = node->next;
  while (next != (AvatarInfoNode *)0x0) {
    node = node->next;
    next = node->next;
  }
  next = node->prev;
  node->prev = new_node;
  new_node->next = node;
  new_node->prev = next;
  if (next != (AvatarInfoNode *)0x0) {
    next->next = new_node;
  }
  info = &new_node->info;
  offset_node = &AvatarInfoOffsetLL;
  llnext = AvatarInfoOffsetLL.nextInfo;
  while (llnext != (int *)0x0) {
    offset_node = (AvatarInfoOffsetLL *)offset_node->nextInfo;
    llnext = offset_node->nextInfo;
  }
  pAVar1 = offset_node->prevInfo;
  offset_node->prevInfo = info;
  info->offsetInfo = offset_node;
  (new_node->info).field1_0x4 = &pAVar1->offsetInfo;
  if (pAVar1 != (AvatarInfo *)0x0) {
    pAVar1->offsetInfo = (AvatarInfoOffsetLL *)info;
  }
  return new_node;
}




void avatar::updateShadows(void)

{
  float fVar1;
  undefined4 *puVar2;
  int iVar3;
  undefined4 *puVar4;
  Camera *pCVar5;
  int iVar6;
  float *extraout_ECX;
  float *extraout_EDX;
  actor_conflict5 *local_4;
  
  pCVar5 = Camera::ActiveConfigs[0];
  iVar3 = (int)&Graphics::CurrentCameraStruct[-0x2a8c].transformMat / 0x1e4;
  puVar2 = Game::SceneInfo.bruhs + iVar3 * 2;
  for (puVar4 = (undefined4 *)Game::SceneInfo.bruhs[iVar3 * 2 + 1]; puVar4 != (undefined4 *)0x0;
      puVar4 = (undefined4 *)puVar4[1]) {
    puVar2 = puVar4;
  }
  iVar6 = FUN_000489e0(Camera::ActiveConfigs[0]);
  if (iVar6 != 0) {
    Graphics::RecalculateWorldAndViews();
    FUN_0013c490(&pCVar5->float5,&pCVar5->field5_0x28,&Graphics::CurrentCameraStruct->affineT);
    fVar1 = *extraout_ECX;
    Graphics::CurrentCameraStruct->near = *extraout_EDX;
    Graphics::CurrentCameraStruct->far = fVar1;
    Graphics::UpdatePerspectiveProj();
    Graphics::UpdateViewport2();
  }
  if (Game::SceneInfo.playerActors.prev == (actor_0x93c_conflict5)0x0) {
    local_4 = (actor_conflict5 *)0x0;
  }
  else {
    local_4 = ADJ(Game::SceneInfo.playerActors.prev);
  }
  for (; puVar2 != Game::SceneInfo.bruhs + iVar3 * 2; puVar2 = (undefined4 *)*puVar2) {
    if (puVar2[iVar3 * -3 + 0x38] != 0) {
      FUN_00120fe0();
      FUN_001211e0((uint)((actor_conflict5 *)(puVar2 + iVar3 * -3 + -0x49) == local_4),
                   (actor_conflict5 *)(puVar2 + iVar3 * -3 + -0x49));
    }
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void avatar::updateRecursive(avatar_0x918 root)

{
  avatar *av;
  
  for (; root != (avatar_0x918)0x0; root = root->next) {
    av = ADJ(root);
    if (ADJ(root)->skipUpdate == 0) {
                    // Disabling this greatly affects the position of many objects in the game
                    // world, including doors, cooper (who seems to just become invisible) and all
                    // ghoulies spawned. Menu items are usually black. I also got stuck in an
                    // infinite loop loading scullery.
      (*av->vtable->update)(av);
                    // This updates some entities visually (eg. pots)
                    // 
                    // Seems to mostly affect objects when they aren't in an active physics
                    // calculation
      updateBaseTransform(av);
                    // Validate model????
      getMaxScaleFromBasis(av);
    }
                    // If avatar has child???
                    // 
    if (ADJ(root)->statePickUp != (entityStatePickup *)0x0) {
                    // Patching this prevents children of an entity from acting. For example, any
                    // weapons cooper is holding will not follow him and will not connect with
                    // enemies, but they CAN still be broken.
      updateRecursive((avatar_0x918)ADJ(root)->statePickUp);
    }
  }
  return;
}



// WARNING: Unable to use type for symbol av_to_insert
// WARNING: Unable to use type for symbol new_av@0x900
// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void avatar::processNew(void)

{
  sceneControlObj_0x8 puVar1;
  sceneControlObj_0x8 puVar2;
  EmbeddedNode<> *tail;
  avatar_0x910 tail0x910;
  Avatar_SceneInsertMessage scene_insert_msg;
  avatar_conflict13 *av_to_insert;
  void *node0;
  avatar_0x900_conflict6 new_av_0x900;
  avatar_conflict13 *av_ptr;
  avatar_conflict13 *av_ptr2;
  avatar_0x900_conflict6 tail0x0;
  
  if (Game::SceneInfo.newAvatars.next != (avatar_0x900_conflict6)0x0) {
    scene_insert_msg.msgId = Avatar_SceneInsert;
    scene_insert_msg.avatarInserted = (avatar *)0x0;
    scene_insert_msg.idk1 = 0x7b;
    do {
      new_av_0x900 = Game::SceneInfo.newAvatars.next;
                    // Remove from avatars@0x900 
      av_to_insert = ADJ(Game::SceneInfo.newAvatars.next);
      (*(ADJ(Game::SceneInfo.newAvatars.next).object.vtable)->onMessage)
                (av_to_insert,&scene_insert_msg);
      if (new_av_0x900->prev != (avatar_0x900_conflict6)0x0) {
        new_av_0x900->prev->next = new_av_0x900->next;
      }
      if (new_av_0x900->next != (avatar_0x900_conflict6)0x0) {
        new_av_0x900->next->prev = new_av_0x900->prev;
      }
      new_av_0x900->prev = (avatar_0x900_conflict6)0x0;
      new_av_0x900->next = (avatar_0x900_conflict6)0x0;
      tail = (EmbeddedNode<> *)&Game::SceneInfo;
      node0 = Game::SceneInfo.avatars.prev;
      while (node0 != (void *)0x0) {
        tail = tail->prev;
        node0 = tail->prev;
      }
      tail0x0 = tail->next;
      tail->next = new_av_0x900;
      new_av_0x900->prev = (avatar_0x900_conflict6)tail;
      new_av_0x900->next = tail0x0;
      if (tail0x0 != (avatar_0x900_conflict6)0x0) {
        tail0x0->prev = new_av_0x900;
      }
                    // Add to list of newly added avatars to update this frame
      tail0x910 = (avatar_0x910)0x511b5c;
      if (Game::SceneInfo.newlyAddedAvatars.next != (avatar_0x910)0x0) {
        tail0x910 = (avatar_0x910)&Game::SceneInfo.newlyAddedAvatars;
        do {
          tail0x910 = tail0x910->next;
        } while (tail0x910->next != (avatar_0x910)0x0);
      }
      tail0x910->next = (avatar_0x910)&ADJ(new_av_0x900)->node0x910;
      (ADJ(new_av_0x900)->node0x910).prev = tail0x910;
      (ADJ(new_av_0x900)->node0x910).next = (avatar_0x910)0x0;
      scene_insert_msg.avatarInserted = (avatar *)av_to_insert;
      tail0x0 = Game::SceneInfo.avatars.next;
                    // Alert all avatars that a new avatar has been inserted
      while (puVar2 = Game::SceneControls.next, tail0x0 != (avatar_0x900_conflict6)0x0) {
        av_ptr = ADJ(tail0x0);
        av_ptr2 = ADJ(tail0x0);
        tail0x0 = tail0x0->next;
                    // background::onMessage
                    // entityAvatarMiscProp::onMessage
                    // actor::onMessage
        (*((av_ptr->object).vtable)->onMessage)(av_ptr2,&scene_insert_msg.idk1);
      }
                    // Alert all scene control objects that a new avatar was added
      while (puVar2 != (sceneControlObj_0x8)0x0) {
        puVar1 = *(sceneControlObj_0x8 *)(puVar2 + 4);
                    // sceneControlObj::onMessage
        (*(code *)((*(sceneControlObj **)(puVar2 + -8))->obj_0x8).next)
                  (puVar2 + -8,&scene_insert_msg.idk1);
        puVar2 = puVar1;
      }
    } while (Game::SceneInfo.newAvatars.next != (avatar_0x900_conflict6)0x0);
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void avatar::BeginScene(void)

{
  avatar_0x910 pEVar1;
  ObjMsgID local_4;
  
  if (Game::SceneInfo.newlyAddedAvatars.next != (avatar_0x910)0x0) {
    local_4 = Scene_Begin;
    pEVar1 = Game::SceneInfo.newlyAddedAvatars.next;
    do {
      (*(ADJ(pEVar1).vtable)->onMessage)(ADJ(pEVar1),&local_4);
      pEVar1 = pEVar1->next;
    } while (pEVar1 != (avatar_0x910)0x0);
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void avatar::UpdateNewAvatars(void)

{
  avatar *avatar;
  avatar_0x910 pEVar1;
  
  pEVar1 = Game::SceneInfo.newlyAddedAvatars.next;
  while (pEVar1 != (avatar_0x910)0x0) {
    avatar = ADJ(pEVar1);
    Game::SceneInfo.newlyAddedAvatars.next = pEVar1;
    if (pEVar1->prev != (avatar_0x910)0x0) {
      pEVar1->prev->next = pEVar1->next;
    }
    if (pEVar1->next != (avatar_0x910)0x0) {
      pEVar1->next->prev = pEVar1->prev;
    }
    pEVar1->prev = (avatar_0x910)0x0;
    pEVar1->next = (avatar_0x910)0x0;
    (*avatar->vtable->update)(avatar);
    updateBaseTransform(avatar);
    pEVar1 = Game::SceneInfo.newlyAddedAvatars.next;
  }
  Game::SceneInfo.newlyAddedAvatars.next = pEVar1;
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void avatar::destroyStaleAvatars(void)

{
  int *piVar1;
  avatar_conflict13 *paVar2;
  avatar_conflict13 *paVar3;
  avatar_0x900_conflict6 pEVar4;
  sceneControlObj_0x8 puVar5;
  sceneControlObj_0x8 puVar6;
  int *piVar7;
  undefined4 local_10;
  int *local_c;
  
  if (Game::SceneInfo.field27_0xb8 != (int *)0x0) {
    local_10 = 0x7c;
    do {
      piVar7 = Game::SceneInfo.field27_0xb8;
      piVar1 = Game::SceneInfo.field27_0xb8 + -0x242;
      local_c = piVar1;
      pEVar4 = Game::SceneInfo.avatars.next;
      while (puVar6 = Game::SceneControls.next, pEVar4 != (avatar_0x900_conflict6)0x0) {
        paVar2 = ADJ(pEVar4);
        paVar3 = ADJ(pEVar4);
        pEVar4 = pEVar4->next;
        (*((paVar2->object).vtable)->onMessage)(paVar3,&local_10);
      }
      while (puVar6 != (sceneControlObj_0x8)0x0) {
        puVar5 = *(sceneControlObj_0x8 *)(puVar6 + 4);
        (*(code *)((*(sceneControlObj **)(puVar6 + -8))->obj_0x8).next)(puVar6 + -8,&local_10);
        puVar6 = puVar5;
      }
      FUN_000ed5b0();
      FUN_000f4970();
      FUN_00123e00();
      if (*piVar7 != 0) {
        *(int *)(*piVar7 + 4) = piVar7[1];
      }
      if ((int *)piVar7[1] != (int *)0x0) {
        *(int *)piVar7[1] = *piVar7;
      }
      *piVar7 = 0;
      piVar7[1] = 0;
      Assets::DeleteResource_(piVar1);
    } while (Game::SceneInfo.field27_0xb8 != (int *)0x0);
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


undefined4 avatar::canTargetBody(avatar *av,int param_2,actorBody *target,uint param_4)

{
  float fVar1;
  float __x;
  int iVar2;
  float10 extraout_ST0;
  float10 fVar3;
  float local_28;
  float local_24;
  float local_20;
  float local_1c;
  vec3 local_18;
  vec3 local_c;
  
  if ((param_4 & 0x20) != 0) {
    local_24 = (target->worldPosition).z;
    local_1c = (target->worldPos).y;
    local_20 = (target->worldPos).x;
    getWorldPosition(av,&local_18);
    local_c.x = (target->worldPosition).z - local_18.x;
    local_c.y = (target->worldPos).x - local_18.y;
    local_c.z = (target->worldPos).y - local_18.z;
    vec3::getTurnAngle(&local_c,&local_28);
    __x = local_28 + 3.1415927;
    fVar1 = *(float *)&target->farRangeThreshold;
    local_28 = __x;
    sin(__x);
    local_28 = (float)extraout_ST0;
    local_24 = local_28 * fVar1 + local_24;
    fVar3 = (float10)cos(__x);
    local_1c = (float)(fVar3 * (float10)fVar1 + (float10)local_1c);
    getWorldPosition(av,&local_c);
    iVar2 = FUN_0012cc50(&local_24,0,param_4 >> 6 & 1,param_4 >> 8 & 1,0,param_2,&local_28,av->tag);
    if (iVar2 == 0) {
      return 0;
    }
  }
  if (((((char)param_4 < '\0') && (*(char *)&target->largeProjectile == '\0')) &&
      (iVar2 = *(int *)&target->currentWeapon->field_0xca8, iVar2 != 0)) &&
     ((iVar2 != param_2 &&
      (((av->tag == Null || (*(objTag *)(iVar2 + 0x1c) == Null)) ||
       (*(objTag *)(iVar2 + 0x1c) == av->tag)))))) {
    return 0;
  }
  return 1;
}




void avatar::loadFromParent(avatar *avatar,AvatarParent *parent)

{
  float fVar1;
  float fVar2;
  float fVar3;
  char cVar4;
  int iVar5;
  char *pcVar6;
  int *in_stack_00000008;
  vec3 local_8c;
  char callout_aid [128];
  
  getWorldPosition(&parent->avatar,&local_8c);
  setPosition(avatar,&local_8c);
  getWorldRotation(&parent->avatar,&local_8c);
  Maths::NormaliseAngles2PI(&local_8c,&avatar->rotEuler);
  avatar->anglesCalculated = 0;
  fVar1 = (parent->avatar).scale.x;
  fVar2 = (parent->avatar).scale.y;
  fVar3 = (parent->avatar).scale.z;
  if (((fVar1 != (avatar->scale).x) || (fVar2 != (avatar->scale).y)) || (fVar3 != (avatar->scale).z)
     ) {
    (avatar->scale).x = fVar1;
    (avatar->scale).y = fVar2;
    (avatar->scale).z = fVar3;
    avatar->anglesCalculated = 0;
  }
  fVar1 = (parent->avatar).uniformScale;
  if (avatar->uniformScale != fVar1) {
    avatar->uniformScale = fVar1;
    avatar->anglesCalculated = 0;
  }
  SetModelInParent(parent,avatar,in_stack_00000008);
  *(undefined1 *)((int)&avatar->someInt32 + 3) =
       *(undefined1 *)((int)&(parent->avatar).someInt32 + 3);
  avatar->fromModelMatrix1 = (parent->avatar).fromModelMatrix1;
  avatar->field193_0x1cc = (parent->avatar).field193_0x1cc;
  avatar->fromModelMatrix2 = (parent->avatar).fromModelMatrix2;
  avatar->someMagnitude = (parent->avatar).someMagnitude;
  avatar->maxScaleFromBasis = (parent->avatar).maxScaleFromBasis;
  pcVar6 = (parent->avatar).calloutAID;
  iVar5 = -(int)pcVar6;
  do {
    cVar4 = *pcVar6;
    pcVar6[(int)(callout_aid + iVar5)] = cVar4;
    pcVar6 = pcVar6 + 1;
  } while (cVar4 != '\0');
  if (callout_aid._0_4_ == 0x5f646961) {
    loadCalloutResource(&avatar->callout,callout_aid);
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


BOOL avatar::testPosition(float param_1,vec3 *someV3,vec2 *param_3,vec2 *param_4,undefined4 param_5)

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
  int iVar10;
  int iVar11;
  float *pfVar12;
  float fVar13;
  float fVar14;
  float fVar15;
  float fVar16;
  float fVar17;
  float fVar18;
  float fVar19;
  float in_XMM4_Da;
  float fVar20;
  float local_58;
  float local_54;
  float local_50;
  float local_4c;
  float local_48;
  float local_44;
  float local_40;
  float local_3c;
  float local_38;
  float local_34;
  float local_30;
  float local_2c;
  float local_28;
  float local_24;
  float local_20;
  float local_1c;
  float local_18;
  float local_14;
  float local_10;
  float local_c;
  float local_8;
  float local_4;
  
  local_44 = someV3->y;
  local_48 = someV3->x + in_XMM4_Da;
  local_30 = local_48;
  local_54 = someV3->x - in_XMM4_Da;
  local_50 = someV3->y;
  local_4c = someV3->z + in_XMM4_Da;
  fVar15 = Graphics::CurrentCameraStruct->computedFov_;
  fVar16 = Graphics::CurrentCameraStruct->field16_0x5c;
  local_58 = someV3->z - in_XMM4_Da;
  fVar9 = Graphics::CurrentCameraStruct->calculatedHeight__unused;
  local_2c = local_44 + param_1;
  local_20 = local_2c;
  local_14 = local_2c;
  local_8 = local_2c;
  fVar17 = Graphics::CurrentCameraStruct->ratioDiff_;
  fVar1 = Graphics::CurrentCameraStruct->cotangentOffset_;
  local_1c = local_4c;
  iVar10 = Graphics::CurrentCameraStruct->calculatedWidth_;
  local_40 = local_4c;
  local_18 = local_48;
  local_10 = local_4c;
  fVar13 = (float)((int)fVar15 + iVar10);
  param_4->x = fVar13;
  fVar14 = (float)((int)fVar16 + (int)fVar9);
  param_4->y = fVar14;
  fVar15 = (float)(int)fVar15;
  param_3->x = fVar15;
  fVar16 = (float)(int)fVar16;
  local_3c = local_54;
  local_38 = local_44;
  local_34 = local_58;
  local_28 = local_58;
  local_24 = local_54;
  local_c = local_54;
  local_4 = local_58;
  param_3->y = fVar16;
  pfVar12 = &local_58;
  iVar11 = 8;
  do {
    fVar19 = (Graphics::CurrentCameraStruct->affineT).m[0][2];
    fVar18 = (Graphics::CurrentCameraStruct->affineT).m[0][1];
    fVar20 = pfVar12[-1];
    fVar2 = (Graphics::CurrentCameraStruct->affineT).m[2][0];
    fVar3 = pfVar12[-2];
    fVar4 = (Graphics::CurrentCameraStruct->affineT).m[0][0];
    fVar5 = (Graphics::CurrentCameraStruct->affineT).m[0][3];
    fVar6 = (Graphics::CurrentCameraStruct->affineT).m[2][2];
    fVar7 = (Graphics::CurrentCameraStruct->affineT).m[2][1];
    fVar8 = pfVar12[-1];
    pfVar12[-1] = (Graphics::CurrentCameraStruct->affineT).m[1][2] * *pfVar12 +
                  (Graphics::CurrentCameraStruct->affineT).m[1][0] * pfVar12[-2] +
                  (Graphics::CurrentCameraStruct->affineT).m[1][1] * pfVar12[-1] +
                  (Graphics::CurrentCameraStruct->affineT).m[1][3];
    pfVar12[-2] = fVar19 * *pfVar12 + fVar18 * fVar20 + fVar4 * pfVar12[-2] + fVar5;
    fVar18 = fVar6 * *pfVar12 + fVar2 * fVar3 + fVar7 * fVar8 +
             (Graphics::CurrentCameraStruct->affineT).m[2][3];
    *pfVar12 = fVar18;
    fVar18 = fVar1 / fVar18;
    fVar19 = (float)iVar10 * 0.5 - pfVar12[-2] * fVar18 * fVar17;
    fVar18 = pfVar12[-1] * fVar18 + (float)(int)fVar9 * 0.5;
    fVar20 = modf(fVar19,4.0);
    fVar19 = fVar19 - fVar20;
    if (fVar19 < param_4->x) {
      param_4->x = fVar19;
    }
    if (param_3->x <= fVar19 && fVar19 != param_3->x) {
      param_3->x = fVar19;
    }
    if (fVar18 < param_4->y) {
      param_4->y = fVar18;
    }
    if (param_3->y <= fVar18 && fVar18 != param_3->y) {
      param_3->y = fVar18;
    }
    pfVar12 = pfVar12 + 3;
    iVar11 = iVar11 + -1;
  } while (iVar11 != 0);
  if (param_4->x <= fVar15 && fVar15 != param_4->x) {
    if (param_3->x <= fVar15 && fVar15 != param_3->x) {
      return 0;
    }
    param_4->x = fVar15;
  }
  if (fVar13 <= param_3->x) {
    if (fVar13 <= param_4->x) {
      return 0;
    }
    param_3->x = fVar13;
  }
  if (param_4->y <= fVar16 && fVar16 != param_4->y) {
    if (param_3->y <= fVar16 && fVar16 != param_3->y) {
      return 0;
    }
    param_4->y = fVar16;
  }
  if (fVar14 <= param_3->y) {
    if (fVar14 <= param_4->y) {
      return 0;
    }
    param_3->y = fVar14;
  }
  if (param_3->x - param_4->x < 4.0) {
    fVar17 = param_3->x - 4.0;
    if (fVar17 <= fVar15) {
      param_3->x = param_4->x + 4.0;
    }
    else {
      param_4->x = fVar17;
    }
  }
  if (param_3->y - param_4->y < 2.0) {
    if (param_3->y - 4.0 <= fVar16) {
      param_3->y = param_4->y + 2.0;
    }
    else {
      param_4->y = param_3->y - 2.0;
    }
  }
  if ((param_4->x != param_3->x) && (param_4->y != param_3->y)) {
    return 1;
  }
  return 0;
}




actorBodyAllocd * avatar::initSomething(avatar *param_1)

{
  ModelDescriptor *pMVar1;
  uint uVar2;
  char *pcVar3;
  actorBodyAllocd *paVar4;
  ModelFooterEntry *pMVar5;
  int iVar6;
  char *pcVar7;
  char cVar8;
  int iVar9;
  actorBodyAllocd *paVar10;
  
  if ((param_1->model != (Model *)0x0) &&
     (pMVar1 = param_1->model->descriptor, pMVar1 != (ModelDescriptor *)0x0)) {
    uVar2 = 0;
    if (pMVar1->numFooterEntries != 0) {
      pMVar5 = pMVar1->footerEntries;
      do {
        if (pMVar5->subresourceType == AnimColliders) {
          uVar2 = pMVar1->footerEntries[uVar2].offset;
          if (uVar2 == 0) {
            return (actorBodyAllocd *)0x0;
          }
          pcVar7 = (char *)(uVar2 + 8);
          iVar9 = 0;
          pcVar3 = pcVar7;
          if (pcVar7 == (char *)0x0) {
            return (actorBodyAllocd *)0x0;
          }
          do {
            if ((*pcVar3 == '\0') && ((pcVar3[4] & 1U) != 0)) {
              iVar9 = iVar9 + 1;
            }
          } while ((pcVar3[1] != 0) && (pcVar3 = pcVar3 + (byte)pcVar3[1], pcVar3 != (char *)0x0));
          if (iVar9 == 0) {
            return (actorBodyAllocd *)0x0;
          }
          paVar4 = malloc_((iVar9 + 1U) * 0x20);
          if (paVar4 == (actorBodyAllocd *)0x0) {
            return (actorBodyAllocd *)0x0;
          }
          paVar10 = paVar4;
          for (iVar6 = (iVar9 + 1U & 0x7ffffff) << 3; iVar6 != 0; iVar6 = iVar6 + -1) {
            *(undefined4 *)paVar10 = 0;
            paVar10 = (actorBodyAllocd *)&paVar10->field_0x4;
          }
          for (iVar6 = 0; iVar6 != 0; iVar6 = iVar6 + -1) {
            *(undefined1 *)paVar10 = 0;
            paVar10 = (actorBodyAllocd *)&paVar10->field_0x1;
          }
          cVar8 = '\0';
          *(actorBodyAllocd **)&paVar4->field_0x4 = paVar4 + 1;
          *(int *)paVar4 = iVar9;
          if (pcVar7 != (char *)0x0) {
            iVar9 = 0;
            do {
              if ((*pcVar7 == '\0') && ((pcVar7[4] & 1U) != 0)) {
                iVar6 = *(int *)&paVar4->field_0x4 + iVar9;
                *(char *)(iVar6 + 0x16) = cVar8;
                cVar8 = cVar8 + '\x01';
                *(char **)(iVar6 + 0x1c) = pcVar7;
                *(undefined2 *)(iVar6 + 0x14) = 0;
                *(undefined1 *)(iVar6 + 0x17) = 1;
                *(float *)(iVar6 + 0x18) = 1.0;
                iVar9 = iVar9 + 0x20;
              }
            } while ((pcVar7[1] != 0) && (pcVar7 = pcVar7 + (byte)pcVar7[1], pcVar7 != (char *)0x0))
            ;
          }
          return paVar4;
        }
        uVar2 = uVar2 + 1;
        pMVar5 = pMVar5 + 1;
      } while (uVar2 < pMVar1->numFooterEntries);
    }
  }
  return (actorBodyAllocd *)0x0;
}




void avatar::hitOtherThings(avatar *hitter,actorBodyAllocd *aAllocd,void *someCallback)

{
  byte bVar1;
  Model *pMVar2;
  Buffer<> *pBVar3;
  int numHittees;
  undefined4 uVar4;
  int iVar5;
  void *pvVar6;
  HeapTableEntry *pHVar7;
  int iVar8;
  float10 extraout_ST0;
  float fVar9;
  uint local_c8;
  int i;
  Skeleton *skeleton;
  vec3 local_b8;
  vec3 local_a8;
  vec3 local_9c;
  actorAllocdValue *local_90;
  float local_8c;
  float local_88;
  float local_84;
  undefined4 auStack_80 [32];
  actorAllocdValue *iVar6;
  
  pMVar2 = hitter->model;
  if (pMVar2 == (Model *)0x0) {
    skeleton = (Skeleton *)0x0;
  }
  else {
    skeleton = pMVar2->skeleton;
    if (skeleton == (Skeleton *)0x0) {
      skeleton = pMVar2->skeleton2;
    }
  }
  iVar6 = (actorAllocdValue *)aAllocd->field13_0x10;
  if (iVar6 == (actorAllocdValue *)0x0) {
    return;
  }
  do {
    iVar8 = 0;
    local_90 = (actorAllocdValue *)iVar6->field4_0x4;
    checkCollisionAgainstSkeleton(iVar6->field11_0x1c,skeleton,&local_9c,&hitter->drawAffine);
    if ((float)extraout_ST0 != 0.0) {
      fVar9 = iVar6->field10_0x18 * (float)extraout_ST0;
      local_b8.x = (iVar6->pos).x;
      local_b8.y = (iVar6->pos).y;
      local_b8.z = (iVar6->pos).z;
      (iVar6->pos).x = local_9c.x;
      (iVar6->pos).y = local_9c.y;
      (iVar6->pos).z = local_9c.z;
      bVar1 = iVar6->field9_0x17;
      local_c8 = 0;
      if ((bVar1 & 1) != 0) {
        local_c8 = 0x220002;
      }
      if ((bVar1 & 2) != 0) {
        local_c8 = local_c8 | 0x40;
      }
      if ((bVar1 & 4) != 0) {
        local_c8 = local_c8 | 0x100;
      }
      local_8c = local_9c.x - local_b8.x;
      local_88 = local_9c.y - local_b8.y;
      local_84 = local_9c.z - local_b8.z;
      numHittees = FUN_00122b00(&local_b8,fVar9,local_c8);
      if (0 < numHittees) {
        if (0 < numHittees) {
          do {
            pBVar3 = Physics::CollisionContexts[iVar8].ctx;
            auStack_80[iVar8 * 2] = Physics::CollisionContexts[iVar8].collidingAvatar;
            uVar4 = FUN_000fcc90(pBVar3);
            auStack_80[iVar8 * 2 + 1] = uVar4;
            iVar8 = iVar8 + 1;
          } while (iVar8 < numHittees);
        }
        i = 0;
        if (0 < numHittees) {
          do {
            pvVar6 = (void *)auStack_80[i * 2 + 1];
            FUN_000fc6c0();
            iVar8 = reactToAvatarCollision
                              (auStack_80[i * 2],&local_8c,hitter,aAllocd,someCallback,iVar6,fVar9,
                               &local_a8,pvVar6);
            iVar5 = FindHeapOf(pvVar6);
            uVar4 = runtime::CurrentHeapToAllocateFrom;
            if (g_HeapTableBase[iVar5].heapHandle == (HANDLE)0x0) {
              pHVar7 = (HeapTableEntry *)0x0;
            }
            else {
              pHVar7 = g_HeapTableBase + iVar5;
            }
            runtime::CurrentHeapToAllocateFrom = iVar5;
            XAPILIB::HeapFree(pHVar7->heapHandle,0,pvVar6);
            runtime::CurrentHeapToAllocateFrom = uVar4;
            if ((iVar8 != 0) || (aAllocd->field13_0x10 == 0)) {
              while (i = i + 1, i < numHittees) {
                pvVar6 = (void *)auStack_80[i * 2 + 1];
                iVar8 = FindHeapOf(pvVar6);
                uVar4 = runtime::CurrentHeapToAllocateFrom;
                if (g_HeapTableBase[iVar8].heapHandle == (HANDLE)0x0) {
                  pHVar7 = (HeapTableEntry *)0x0;
                }
                else {
                  pHVar7 = g_HeapTableBase + iVar8;
                }
                runtime::CurrentHeapToAllocateFrom = iVar8;
                XAPILIB::HeapFree(pHVar7->heapHandle,0,pvVar6);
                runtime::CurrentHeapToAllocateFrom = uVar4;
              }
              return;
            }
            i = i + 1;
          } while (i < numHittees);
        }
      }
      local_a8.x = local_9c.x;
      local_a8.y = local_9c.y;
      local_a8.z = local_9c.z;
      iVar8 = FUN_001229f0(&local_b8,fVar9,local_c8);
      if (iVar8 != 0) {
        pvVar6 = (void *)FUN_000fcc90(Physics::CollisionContexts[0].ctx);
        iVar8 = reactToAvatarCollision
                          (Physics::CollisionContexts[0].collidingAvatar,&local_8c,hitter,aAllocd,
                           someCallback,iVar6,fVar9,&local_a8,pvVar6);
        numHittees = FindHeapOf(pvVar6);
        uVar4 = runtime::CurrentHeapToAllocateFrom;
        if (g_HeapTableBase[numHittees].heapHandle == (HANDLE)0x0) {
          pHVar7 = (HeapTableEntry *)0x0;
        }
        else {
          pHVar7 = g_HeapTableBase + numHittees;
        }
        runtime::CurrentHeapToAllocateFrom = numHittees;
        XAPILIB::HeapFree(pHVar7->heapHandle,0,pvVar6);
        if (iVar8 != 0) {
          runtime::CurrentHeapToAllocateFrom = uVar4;
          return;
        }
        runtime::CurrentHeapToAllocateFrom = uVar4;
        if (aAllocd->field13_0x10 == 0) {
          return;
        }
      }
    }
    iVar6 = local_90;
    if (local_90 == (actorAllocdValue *)0x0) {
      return;
    }
  } while( true );
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields

undefined4
reactToAvatarCollision
          (avatar *hittee,undefined4 param_2,avatar *hitter,actorBodyAllocd *aAllocd,
          undefined *callback,actorAllocdValue *param_6,undefined4 param_7,vec3 *param_8,
          undefined4 param_9)

{
  vec3 *unaff_EBX;
  undefined4 uVar1;
  vec3 local_34;
  undefined1 local_28;
  undefined1 local_27;
  undefined1 local_26;
  float local_24;
  float local_20;
  float local_1c;
  undefined4 local_18;
  
  avatar::getWorldPosition(hittee,&local_34);
  uVar1 = 0;
  if (callback != (undefined *)0x0) {
    local_24 = param_8->x;
    local_20 = param_8->y;
    local_1c = param_8->z;
    local_18 = param_7;
    local_34.x = unaff_EBX->x * 60.0;
    local_34.y = unaff_EBX->y * 60.0;
    local_34.z = unaff_EBX->z * 60.0;
    local_28 = 1;
    local_26 = 1;
    local_27 = 0x28;
    uVar1 = (*(code *)callback)(hitter,hittee,param_8,param_9,&local_28,&local_34,
                                param_6->field11_0x1c->blendTargetIndex);
    if (aAllocd->field13_0x10 == 0) {
      return 1;
    }
  }
  InitEDB2Entry(&aAllocd->edb2Buffer,hittee,1);
  return uVar1;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


