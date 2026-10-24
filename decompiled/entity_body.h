/* entity_body.h - Body entity subclasses (human/camera/player)
   From Ghidra decompilation of Grabbed by the Ghoulies default.xbe. */
#pragma once
#include "common.h"

/* ---- declarations ---- */
extern void entityBodyHuman::onActorBiteMessage(actorBody *param_1,Actor_BiteMessage *msg);
extern void entityBodyHuman::onHitByPropMessage(entityBodyHuman *body,Avatar_HitByPropMessage *msg);
extern void entityBodyHuman::onHitByFurnaceMessage(actorBody *param_1,Avatar_HitByFurnaceMessage *msg);
extern void avatarSetupBasic::spawnFromMarker(short index,int *param_2);
extern void entityBodyCamera::updatePosAndRot(entityBodyCamera *this);
extern void entityBodyCamera::updateRotation(entityBodyCamera *this);
extern bool entityBodyCamera::func7(entityBodyCamera *this);
extern void entityBodyCamera::getAllocDetails(ObjectAllocDetails *param_1);
extern void entityBodyCamera::getVTable(void);
extern undefined4 entityBodyCamera::ctor(entityBodyCamera *camera);
extern void entityBodyCamera::dtor(int param_1);
extern void entityBodyCamera::onMessage(actorBody *param_1,Message *param_2);
extern actorBodyVTable * entityBodyHuman::GetVTable(void);
extern undefined4 entityBodyHuman::ctor(entityBodyHuman *human,entityBodyHumanParams *params);
extern void entityBodyHuman::dtor(entityBodyHuman *param_1);
extern void entityBodyHuman::createRigidSkin(entityBodyHuman *human,entityBodyHumanParams *params);
extern void entityBodyHuman::destroyRigidBones(entityBodyHuman *param_1);
extern void entityBodyHuman::updateMentalFocus(entityBodyHuman *body);
extern uint32_t entityBodyHuman::getNumberRigidBones(entityBodyHuman *human,entityBodyHumanParams *params);
extern void entityBodyHuman::onMessage(entityBodyHuman *human,Message *msg);
extern void entityBodyHuman::update(entityBodyHuman *bodyHuman);
extern void entityBodyHuman::handlePushOut(entityBodyHuman *body);
extern undefined4 entityBodyHuman::computeMovementAndCollisions(entityBodyHuman *this);
extern void entityBodyHuman::loadCollisionFromSubres0x4(entityBodyHuman *human);
extern void entityBodyHuman::onMessage(entityBodyHuman *human,Message *msg);
extern void entityBodyPlayer::getAllocDetails(ObjectAllocDetails *param_1);
extern void entityBodyPlayer::getVTable(void);
extern void entityBodyPlayer::onMessage(entityBodyPlayer *body,Scene_PowerupActivatedMessage *param_2);
extern actorBodyStateId entityBodyPlayer::getStandingState(actorBody *body);
extern actorBodyStateId entityBodyPlayer::getWalkState(actorBody *param_1);
extern void entityBodyHuman::getAllocDetails(undefined4 *param_1);
extern void entityBodyHuman::onEscapeBackground(int param_1,actor *actor);
