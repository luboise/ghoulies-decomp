/* cutscene.h - Cutscenes, playcams, transitions, storybook
   From Ghidra decompilation of Grabbed by the Ghoulies default.xbe. */
#pragma once
#include "common.h"

/* ---- declarations ---- */
extern void UpdateCutscenes_(void);
extern void Cutscene::freeEvents(CutsceneEvents *events);
extern Cutscene * Cutscene::ctor(float length,uint flags,uint numAnims,CutsceneDescriptor *descriptor);
extern void Cutscene::dtor(Cutscene *buf);
extern float Cutscene::updateCameraFromCutscene(Cutscene *cutscene,Camera *camera);
extern void FUN_0004dbd0(Cutscene *param_1);
extern void Cutscene::loadAnimations(Cutscene *cutscene,CutsceneDescriptor *desc,BOOL flag1,BOOL flag2);
extern void Cutscene::loadEvents(Cutscene *cutscene,char *cutsceneName,int eventName);
extern void Cutscene::freeCameraEvents(Cutscene *csb);
extern void Cutscene::PosAndRotAtT(Cutscene *cutscene,vec3 *pos,Quaternion *q,float cutsceneProgress);
extern void Cutscene::update(Cutscene *cutscene,float delta,float sampleRotation,int param_4);
extern void CloseDoorAndUpdateState(int param_1,Cutscene *csb);
extern void Cutscene::doSomething(Cutscene *csb,int param_2,uchar index);
extern void Cutscene::freeAnimations(Cutscene *param_1);
extern uint Cutscene::getEventIdFromModelName(Cutscene *csb,char *modelName);
extern void UpdateCutsceneProgress(void);
extern void Cutscene::SetCutsceneCam(void);
extern Cutscene * Cutscene::LoadFromLevel(char *ctscAID,BOOL someFlag,BOOL someOtherFlag);
extern void __fastcall FUN_0004eea0(Cutscene *param_1);
extern void Cutscene::RerenderFromEulerAngles(vec3 *eulers);
extern BOOL Cutscene::InACutscene(void);
extern void Cutscene::drop(Cutscene *cutscene);
extern void Assets::CutsceneResource::processDescriptor(CutsceneDescriptor *desc,uint resourceBase);
extern void Assets::CutsceneResource::InitLoader(void);
extern void CreateTrophyAttacksCutscene(void *this,undefined4 param_2,int headIndex);
extern void CutsceneResource::alloc(void);
extern void UpdateStorybookPosition_(void);
extern void runtime::UpdateNewEntities(GameState *param_1);
extern void LoadCutsceneSkip(void);
extern int RegularLoadInTransition(GiantLoctextStruct *gls);
extern void FUN_0012b5a0(TransitionData *param_1);
extern void StartLoadingRegularTransition(GiantLoctextStruct *gsl);
extern void UpdateStorybook(void);
extern void CheckEndOfCutscene(void);
