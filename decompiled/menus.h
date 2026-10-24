/* menus.h - Menus & UI (pause, replay, challenge menus)
   From Ghidra decompilation of Grabbed by the Ghoulies default.xbe. */
#pragma once
#include "common.h"

/* ---- declarations ---- */
extern void GetText(ushort target,ushort param_2,vec2 *scale,float *outFloat1,float *outFloat2,uint index);
extern short * RecomputeLoctextFString(float *x,float *y,float *scale,wchar_t *param_4);
extern void SetSaveNameMenu::alloc(void);
extern BOOL BnousChallengesMenu::ctor(entitySceneControlGameSelect *param_1,BonusChallengesMenu *param_2);
extern void BonusChallengesMenu::update(BonusChallengesMenu *this);
extern void BonusChallengesMenu::draw(BonusChallengesMenu *param_1);
extern void BonusChallengesMenu::setState(BonusChallengesMenu *param_1,int state);
extern undefined4 SetSaveNameMenu::ctor(entitySceneControlGameSelect *control,MenuSceneResource *res);
extern void SetSaveNameMenu::func3(int param_1);
extern void SetSaveNameMenu::func4(int *param_1);
extern void SetSaveNameMenu::func5(int param_1);
extern void MainMenu::alloc(void);
extern undefined4 MainMenu::func2(undefined4 param_1,undefined4 *param_2);
extern void MainMenu::func3(int param_1);
extern void MainMenu::update(MainMenu *menu);
extern void MainMenu::draw(float *param_1);
extern void ReplayChapterMenu::alloc(void);
extern undefined4 ReplayChapterMenu::ctor(entitySceneControlGameSelect *gameSelect,ReplayChapterMenu *menu);
extern void ReplayChapterMenu::dtor(ReplayChapterMenu *param_1);
extern void ReplayChapterMenu::update(ReplayChapterMenu *param_1);
extern Malloced100 * ReplayChapterMenu::loadChapterNames(void);
extern void ReplayChapterMenu::load_text(ReplayChapterMenu *menu,int param_2);
extern undefined4 ReplaySceneMenu::ctor(entitySceneControlGameSelect *control,ReplaySceneMenu *menu);
extern void ReplaySceneMenu::func3(ReplaySceneMenu *menu);
extern void ReplaySceneMenu::update(ReplaySceneMenu *menu);
extern void ReplaySceneMenu::setState(ReplaySceneMenu *menu,MenuState newState);
extern void ReplayChapterMenu::draw(ReplaySceneMenu *menu);
extern void Menu12::alloc(void);
extern undefined4 Menu12::ctor(undefined4 param_1,astruct_18 *param_2);
extern void Menu12::dtor(int param_1);
extern void Menu12::update(Menu12 *param_1);
extern void Menu12::draw(float *param_1);
extern void FUN_000e6f10(Menu12 *menu);
extern void FUN_000e70e0(Menu12 *menu,uint param_2);
extern void UI::EnterPauseUI(void);
extern void runtime::UpdatePauseScreen(void);
extern void UI::UnloadSomeElements2_(void);
extern void UI::UnloadSomeElements_(void);
extern void __fastcall UI::LoadHealthTextures(actorBody *inAsset);
extern void UI::InitialiseVariables(void);
extern void __fastcall UI::DrawRandomiser(void);
extern void UI::UnloadElement(int *param_1);
extern void UI::Draw2DElements(int *param_1);
extern void UI::UnloadManyElements_(void);
extern void __fastcall HandleUIUpdate(void);
