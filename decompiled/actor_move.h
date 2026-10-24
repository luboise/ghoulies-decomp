/* actor_move.h - Actor movement (crane, XZ gravity, alert)
   From Ghidra decompilation of Grabbed by the Ghoulies default.xbe. */
#pragma once
#include "common.h"

/* ---- declarations ---- */
extern ObjectFullVTable * actorMove::GetVTable(void);
extern void actorMove::update(actorMove *move);
extern void actorMove::updateLaunchedPos(actorMove *this);
extern void actorMove::processMovement(entityMoveXZGravity *move,int param_2,int alert);
extern void actorMove::getAllocDetails(ObjectAllocDetails *param_1);
extern void entityMoveXZGravity::update(entityMoveXZGravity *move);
extern void entityMoveAlert::func5(entityMoveXZGravity *param_1);
extern void entityMoveCrane::getAllocDetails(undefined4 *param_1);
extern undefined ** entityMoveCrane::getVTable(void);
extern void entityMoveCrane::ctor(entityMoveCrane *param_1);
extern void entityMoveCrane::onMessage(entityMoveCrane *param_1,Message *param_2);
extern void entityMoveCrane::update(entityMoveCrane *move);
extern void entityMoveCrane::func5(entityMoveCrane *param_1);
extern actorMoveVTable * entityMoveXZGravity::getVTable(void);
extern void entityMoveXZGravity::applyMovement(entityMoveXZGravity *param_1);
extern void EntityMoveContext::updateXY(EntityMoveContext *ctx,vec3 *velocity);
