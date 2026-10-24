/* scripting.h - Script engine: parse, run, free scripts
   From Ghidra decompilation of Grabbed by the Ghoulies default.xbe. */
#pragma once
#include "common.h"

/* ---- declarations ---- */
extern BOOL Scripting::GetSetupAIDFromChapter(char *scriptName,char *outAssetName);
extern void __fastcall Scripting::RunSetupScriptFromScriptAID(char *aid);
extern BOOL ScriptInstance::seekToOp(Script *instance,ScriptOpcode op);
extern BOOL ScriptOperation::nothingMoreToRun(ScriptOperation *param_1);
extern void __fastcall Scripting::AddGhoulySpawnToList(GhoulyBox *box,GhoulyBoxLLHead *list);
extern void Scripting::CreateScriptType1(InputHandlerType1 **script);
extern void Scripting::CreateScriptType4(ScriptType4 **scriptSet);
extern void Scripting::FreeScript4(ScriptType4 *script);
extern void Scripting::CreateScriptType5(InputHandlerType5 **script);
extern void Scripting::FreeScript5(ScriptType4 *param_1);
extern void Scripting::CreateScriptType2(InputHandlerType4 **script);
extern void Scripting::FreeScript123(InputHandlerBase *param_1);
extern void Scripting::CreateInputHandler3(InputHandlerType3 **script);
extern void Scripting::CreateScript(void **param_1,InputHandlerType scriptType);
extern void Scripting::FreeScriptInner(InputHandlerBase *param_1);
extern void ScriptType1::getControllerXY(InputHandlerType1 *param_1,vec2 *param_2);
extern void Scripting::PopInputHandler(void);
extern Script2TypeNode * runtime::GetInputHandlerByName(char *param_1);
extern int Scripting::ScriptHeaderIndexFromAID(char *name);
extern void Scripting::SetCurrentPlaycamScript(void);
extern void Events::Scripting::RunScriptConditionsCallback2(void);
extern void Scripting::updateLevelScript(void);
extern undefined4 Scripting::SetBackground(char *param_1);
extern void Scripting::SetPlayerObjParams(uint32_t param_1,char *param_2);
extern void Scripting::CheckScriptConditions(void);
extern ScriptCondition * Scripting::newScriptCondition(ScriptCondition *cond);
extern ScriptReturnCode Scripting::Handler::handler2(Script *instance);
extern ScriptReturnCode Scripting::Handler::handle_0x32_0x38(Script *param_1);
extern ScriptReturnCode Scripting::Handler::handle_0x5d_0x71(int *param_1);
extern undefined4 Scripting::Handler::handler0x98(Script *instance,BOOL flag);
extern undefined4 Scripting::Handler::CheckChallengeLogic0x7a_0x86(Script *instance);
extern ScriptReturnCode Scripting::Handler::addCondition(Script *instance);
extern ScriptReturnCode Scripting::Handler::updateRoom(Script *instance,BOOL flag1,BOOL flag2);
extern ScriptReturnCode Scripting::Handler::newChallenge(Script *instance,BOOL b1,BOOL b2);
extern undefined4 Scripting::Handler::SetGlobalFlag(Script *param_1);
extern ScriptReturnCode Scripting::Handler::SpawnGhoulieWithBox(Script *instance);
extern undefined4 Scripting::Handler::SetPositions_(Script *param_1,BOOL param_2);
extern undefined4 Scripting::Handler::AudioHandlers(Script *param_1);
extern Scripting::Handler::runCutscenes(Script *instance,undefined4 param_2,int inACutscene_);
extern void Scripting::FreeScript(void);
extern undefined4 Scripting::Handler::UpdatePlayer_(Script *param_1,int param_2,int param_3);
extern ScriptReturnCode Scripting::Handler::Setup(Script *instance,BOOL param_2,BOOL gameIsLoading);
extern undefined4 Scripting::Handler::finalHandler(Script *instance);
extern BOOL Scripting::RunScripts(void);
extern BOOL Script::update(Script *this);
extern ScriptReturnCode Scripting::Handler::ScriptPosHandlers(Script *instance,BOOL param_2,BOOL param_3);
extern void Scripting::SeekScriptToBookmark(ScriptResource *res,int preBookmark,int bookmark);
extern undefined4 ScriptConditionCallback::checkPlayerApproachesDoor(PlayerApproachesDoorCondition *cond);
