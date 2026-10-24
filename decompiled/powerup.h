/* powerup.h - Powerups
   From Ghidra decompilation of Grabbed by the Ghoulies default.xbe. */
#pragma once
#include "common.h"

/* ---- declarations ---- */
extern void powerup::playSound(uint param_1,char *soundName);
extern void powerup::getAllocDetails(ObjectAllocDetails *param_1);
extern void powerup::getVTable(void);
extern undefined4 powerup::draw(powerup *param_1,undefined4 param_2,int param_3);
extern undefined4 powerup::ctor(powerup *this,powerupParams *params);
extern void powerup::onMessage(powerup *pwup,Avatar_AnimationEventMessage *msg);
extern void powerup::update(powerup *pwup);
