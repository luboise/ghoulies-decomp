/* ai_strategy.h - Actor strategies (enemy behaviours)
   From Ghidra decompilation of Grabbed by the Ghoulies default.xbe. */
#pragma once
#include "common.h"

/* ---- declarations ---- */
extern void actorStrategy::getAllocDetails(ObjectAllocDetails *param_1);
extern actorStrategyVTable * actorStrategy::getVTable(void);
extern undefined4 actorStrategy::ctor(actorStrategy *strategy,actorStrategyParams *params);
extern BOOL actorStrategy::shouldBeDroning(actorStrategy *strategy);
extern void actorStrategy::setStrategy(actorStrategy *strategy,actorStrategyOffsetId param_2);
extern void actorStrategy::enterState(actorStrategy *strategy,actorStrategyOffsetId id);
extern void actorStrategy::onMessage(actorStrategy *actorStrategy,Message *msg);
extern void actorStrategy::update(actorStrategy *strategy);
extern void actorStrategy::leaveState(actorStrategy *strategy,actorStrategyOffsetId newState);
extern BOOL actorStrategy::setDroneAction(actorStrategy *strategy,Actor_SetDroneActionMessage *msg);
extern void actorStrategy::onInCutscene(actorStrategy *strategy);
extern undefined4 actorStrategy::updateDuringCutscene(actorStrategy *strategy);
extern void actorStrategy::onActivate(actorStrategy *param_1);
extern void actorStrategy::onActorHitInvulnerable(actorStrategy *strat,actor *inAct,actor *param_3);
extern undefined4 actorStrategy::onEventCompleted(actorStrategy *param_1);
extern undefined4 actorStrategy::onEventFailed(actorStrategy *param_1);
extern BOOL actorStrategy::updateAndGetTarget(actorStrategy *strat,actorBody **targetBody,BOOL someFlag);
extern BOOL actorStrategy::canPlayIntro(actorStrategy *strategy,uint param_2);
extern BOOL actorStrategy::checkAndSetDying(actorStrategy *strategy);
extern void actorStrategy::forceIntro(actorStrategy *strategy,undefined4 param_2);
