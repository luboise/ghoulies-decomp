/* animation.h - Animation: keyframes, attack instances, bone affines
   From Ghidra decompilation of Grabbed by the Ghoulies default.xbe. */
#pragma once
#include "common.h"

/* ---- declarations ---- */
extern void FUN_0001afa0(AnimEventMapping *mapping,actorBody *body);
extern undefined4 GetValueFromLoadedAttackDataResources(AttackDataResource *res,int *param_2);
extern ushort * FUN_0001c400(uint param_1,AttackDataListOfAttacks *param_2);
extern AttackDataResource::getAttackByStateId(AttackDataResource *param_1,actorBodyStateId param_2);
extern AttackDataResource::getAttack4ById(AttackDataResource *param_1,actorBodyStateId param_2);
extern void KeyframeAllocdValue::initialise(CombinedAnimChannel *allocdValue);
extern CombinedAnimChannel * FUN_0002d3f0(void);
extern AnimInstance * AnimInstance::ctor(void);
extern void AnimInstance::dtor(void *this,AnimInstance *allocd);
extern void AnimInstance::update(AnimInstance *this,float delta,BOOL ignoreErrors);
extern void Assets::AnimResource::InitLoader(void);
extern float10 Animation::PickLinearKeyframe(float progress,undefined4 unused,int v1,int v2);
extern float10 Animation::PickCubicHardKeyframes(float t,int prev,int start,int end,int next);
extern void FUN_0002e750(vec3 *param_1,AnimInstance *param_2);
extern void BoneList::dtor(BoneList *param_1);
extern void BoneList::addRigidByBoneIndex(BoneList *bs,ushort id,void *transformCallback,RigidBone *ptr0x9);
extern uint32_t BoneList::ctor(BoneList *param_1);
extern int BoneList::resizeForSize(BoneList *bs,ushort id);
extern void BoneList::removeBoneById(uint16_t boneId,BoneList *param_2);
extern void WriteAffinesIntoBones(AffineTransform *affines,int numBones,ndSkeletonBone *bones);
extern KeyframeContext * KeyframeContext::ctor(uint numChannels);
extern void KeyFrameContext::dtor(KeyframeContext *kfc,int param_2);
extern BOOL KeyframeContext::hasValAtIndexInAnyChannel(KeyframeContext *kfc,int index);
extern void KeyframeContext::collapseChannelsIntoCombined(KeyframeContext *kfc);
extern void KeyframeContext::deleteAnimationByIndex(int param_1,uint channelIndex,KeyframeContext *kfc);
extern AffineTransform * SetGlobalAffineFromBone(Skeleton *skeleton,int index);
extern AffineTransform * FUN_000316b0(float *param_1,int param_2,int param_3,int param_4);
extern void AnimInstanceHeader::updateFaceAndEvents(AnimInstance *header);
extern AnimTableResource::getEventMappingBySomething(AnimtableResource *param_1,char *param_2);
extern AnimEventMapping * AnimtableResource::getEventMapping(AnimtableResource *res,char *name);
extern AnimtableEntry * AnimtableResource::getEntry(AnimtableResource *param_1,char *name);
extern AnimEventMapping * FUN_000322a0(AnimEventMapping *mapping,int param_2,KFCParams *param_3);
extern void Assets::AnimTableResource::InitLoader(void);
extern undefined4 CheckAnimKfcThreshold(void *this,actor *act,float param_3);
extern GetAnimMiscPropFromCutscene_(CutsceneDescriptor *descriptor,int param_2,uint animIndex);
extern void FUN_00051430(CutsceneDescriptor *cutsceneDesc,vec3 *param_2,char animIndex,float param_4);
extern void FUN_00051ce0(int param_1,int param_2,vec3 *param_3,AffineTransform *param_4);
extern AttackInstance * AttackInstance::ctor(int rawSize);
extern void GetVFromSubres0x8ModelName(char *modelAid,float *outx,float *outy,float *outz);
extern FUN_00120480(vec3 *inPos,avatar *av,HumanAnimColliderData *param_3,undefined4 num0x4s,vec3 *outPos);
extern void __fastcall FUN_0013c490(float *param_1,float *param_2,AffineTransform *param_3);
