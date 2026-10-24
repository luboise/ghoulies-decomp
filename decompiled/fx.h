/* fx.h - Particle/FX avatars and impact effects
   From Ghidra decompilation of Grabbed by the Ghoulies default.xbe. */
#pragma once
#include "common.h"

/* ---- declarations ---- */
extern void Callout::DefaultCallback(CalloutDescriptor *descriptor,uint index,actor *param_3);
extern avatarCalloutId Callout::getByName(char *calloutId);
extern void entityAvatarFxBurnup::checkCollision0x4(entityAvatarFxBurnup *param_1);
extern avatarFxEmitter::ctor(avatarFxEmitter *emitter,int param_2,int param_3,char *impactFlashAID);
extern void entityAvatarFxAnimEmitter::getVTable(void);
extern void entityAvatarFxAnimEmitter::update(actor *param_1);
extern void entityAvatarFxBurnup::getAllocDetails(undefined4 *param_1);
extern void entityAvatarFxBurnup::getVTable(void);
extern undefined4 entityAvatarFxBurnup::ctor(entityAvatarFxBurnup *this,entityAvatarFxBurnupParams *params);
extern void entityAvatarFxBurnup::dtor(int param_1);
extern void entityAvatarFxBurnup::update(entityAvatarFxBurnup *param_1);
extern void entityAvatarFxExplode::getAllocDetails(undefined4 *param_1);
extern void entityAvatarFxExplode::getVTable(void);
extern entityAvatarFxExplode::ctor(entityAvatarFxExplode *fx,entityAvatarFxExplodeParams *param_2);
extern void entityAvatarFxExplode::dtor(int param_1);
extern void entityAvatarFxExplode::update(entityAvatarFxExplode *fx);
extern undefined4 entityAvatarFxExplode::func5(entityAvatarFxExplode *fx);
extern void entityAvatarFxExplode::onMessage(entityAvatarFxExplode *fx,Message *msg);
extern void entityAvatarFxExplodeParts::getAllocDetails(undefined4 *param_1);
extern void entityAvatarFxExplodeParts::getVTable(void);
extern void entityAvatarFxExplodeParts::dtor(int param_1);
extern void entityAvatarFxExplodeParts::updateFixed_(actor *param_1);
extern undefined4 entityAvatarFxExplodeParts::func5(avatar *param_1,undefined4 param_2,undefined4 param_3);
extern void entityAvatarFxExplodeParts::update(entityAvatarFxBurnup *param_1,Message *param_2);
extern void entityAvatarFxMotionBlur::getVTable(void);
extern void entityAvatarFxAnimEmitter::onMessage(entityAvatarFxBurnup *param_1,Message *param_2);
extern void entityAvatarFxBurnup::onMessage(entityAvatarFxBurnup *param_1,Message *param_2);
extern undefined ** entityFxCustomDustUp::getVTable(void);
extern bool entityFxCustomDustUp::ctor(int param_1,int param_2);
extern void entityFxCustomDustUp::updateFixed_(void *param_1,int param_2);
extern void entityFxCustomDustUp::getAllocDetails(undefined4 *param_1);
extern undefined ** fxCustom::getVTable(void);
extern undefined4 fxCustom::ctor(fxCustom *fx,fxCustomParams *params);
extern void fxCustom::dtor(int param_1);
extern void fxCustom::updateFixed_(fxCustom *fx);
extern int UpdateFX(void);
extern void fxParticleImpactFlash::deleteInitAssets(fxParticleImpactFlash *fx);
extern BOOL GetFxName(char *outName,char *param_2,uint stringId,char *param_4,char *param_5);
