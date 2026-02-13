#include <algorithm>

#include "logic.hpp"

#include "../lib.hpp"
#include "../runtime/runtime.hpp"

void game::RunUpdate(graphics::DrawContext& draw_ctx, GameState& state)
{
  /*
  if ((((state.preventStateChanges == 0)
        &&
                        ghoulies::IsValidAssetAID(state.playcamAID)

       && (EventLoop::SetGameplayState(state, BEGUN_LOADING_TRANSITION),
           g_GiantLoctextStruct.g_someGlobalVar != 1))
      && (g_GiantLoctextStruct.g_someGlobalVar != 2))
  {
    EventLoop::CreateTransitionCameraAndText();
  }
  state.prevState = state.gameplay_state;
  if (((state.newState != state.gameplay_state) && (state.preventStateChanges ==
  0)) && (g_paused? == 0)) { EventLoop::SetGameplayState(state, state.newState);
  }
  FUN_00109470(*(ScriptType2 **)((int)&state.loctext? + 1));
  UpdatePauseScreen();
  */
  switch (state.gameplay_state) {
    case State2:
      state.new_gameplay_state = Unknown0x0;
      UpdateEntities(draw_ctx, state);
      UpdateBookTransition();
      return;
    case BegunLoadingTransition:
      if (state.loaded_cutscene != 0) {
        SetGameplayState(state, Loading);
      }
      state.loaded_cutscene = 1;
      UpdateBookTransition();
      return;
    case Loading:
      /*
  // Audio::Loading = 1;
  success = loadNewBNL(unaff_EDI);

  if (success) {
    FUN_0012c770();
    state.preventStateChanges = 0;
    RunPostLoadSetupScripts(state);
    state.newState = FinishedLoadingTransition;
    UpdateBookTransition();
    return;
  }
  break;
      */
      return;
    case FinishedLoadingTransition:
      /*
  if (g_GiantLoctextStruct.g_someGlobalVar == 0) {
    state.newState = state.newChapterState;
    UpdateBookTransition();
    return;
  }
  if (state.currentChapter == 0) {
    break;
  }
      */
      return;
    case Normal:
      UpdateEntities(draw_ctx, state);
      break;
    case Unknown0x0:
    case Paused:
      break;
  }

  UpdateBookTransition();
}

void game::UpdateEntities(graphics::DrawContext& draw_ctx, GameState& state)
{
  // BOOL matches;
  // Buffer<>* piVar2;

  /*
  iVar3 = *(int*)((int)&state.field79_0x22b + 1);
  if (iVar3 != 0) {
    iVar3 += -1;
    *(int*)((int)&state.field79_0x22b + 1) = iVar3;
    if (iVar3 == 2) {
      // Audio::Loading = 0;
    }
    // UpdateVolumes(); If done loading, unmute the game
  }
        */

  runtime::DecrementTimerByDelta(runtime::dx_timer);

  float delta = (runtime::delta_time * runtime::time_scale * 300.0F)
      + runtime::total_ticks_updated;

  runtime::ticks_to_run = static_cast<std::uint32_t>(delta);

  /* Disabling this causes weird animation effects and stiffness */
  runtime::total_ticks_updated =
      delta - static_cast<float>(runtime::ticks_to_run);
  // UpdateCutsceneProgress();
  // UpdateCutsceneAndDraws();
  // UpdateDialogEvents();
  /* If in dialogs */
  /*
  if (Game::UpdateActionType == 3) {
    FUN_0013ffd0();
  }
  */
  // CheckLevelExitTriggers();
  // RunChallengeSetupTriggers();
  // RunEndOfScaryShockEvents();
  // CheckLevelExitTriggers();

  /*
  pvVar2 = Game::ActiveSceneControlObjects.next;
  if (g_shouldExecuteGhoulieIntro == 1) {
    EventLoop::ExecuteGhoulieIntro();
    pvVar2 = Game::ActiveSceneControlObjects.next;
  }
  // Update scene controls
  while (pvVar2 != NULL) {
    pvVar1 = *(void**)((int)pvVar2 + 4);
  (**(code**)(*(int*)((int)pvVar2 + -8) + 0x10))((int)pvVar2 + -8);
  pvVar2 = pvVar1;
}

*/

  EmbeddedNode<Avatar*>& scene_head {state.scene_info.scene_tree};

  if (scene_head.next != nullptr) {
    scene_head.next->UpdateRecursive();
  }

  /*
  Background::updateViews();
  UpdatePerSecondTimers();
  UpdateGhoulyBoxes();
  Scripting::RunScriptConditionsCallback2();
  ExecuteGhoulieIntroLoctext();
  UpdateActionsAndDialog();
  */
  delta = 0.0;
  if (runtime::dx_timer <= 0.0F) {
    delta = std::min(0.016666668F, runtime::delta_time * runtime::time_scale);
  }

  // UpdateTextureMaybeSomethings(delta * 7.2);
  // Graphics::CleanupResources();
  /*
 if ((DAT_00510580 != 0) && (DAT_00510650 == 0)) {
   DAT_00510648 = DAT_00510648 + 0.002;
   DAT_0051064c = DAT_0051064c + 0.002;
   Graphics::InitialiseScreenSpaceQuads();
 }
 */
  // UpdateDeltaAngles();
  // FUN_001185e0();
  // FUN_000fdda0();
  // Graphics::UpdateFog();
  /* Run input handlers */
  /*
    if ((((((int)Input::InputHandlers->tail - (int)Input::InputHandlers->head)
               / (int)(uint)Input::InputHandlers->valueSize
           != 0)
          && (piVar2 = *(Buffer<>**)(Input::InputHandlers->head->name
                                     + (Input::NumInputHandlers - 1)
                                         * (uint)Input::InputHandlers->valueSize
                                     + -4),
              piVar2 != NULL))
         && (matches = Input::ContextHasButton(START, (InputContext*)piVar2),
             matches != 0))
        && (Game::NotAllowedToPause == 0))
    {
       CurrentChapterState.newState =
              (-(uint)(g_paused? != 0) & 0b11111111111111111111111111111011) +
    PAUSED;
    }
    */

  auto& lib {ghoulies::GhouliesLib::Instance()};
  auto& game_context {lib.GameContext()};

  if (game_context.draw_backgrounds) {
    for (auto& bg : lib.GameState().scene_info.backgrounds) {
      bg->Draw(draw_ctx);
    }
  }

  for (auto& weapon : game_context.weapons) {
    weapon->Draw(draw_ctx);
  }

  for (auto& powerup : game_context.powerups) {
    powerup->Draw(draw_ctx);
  }

  if (game_context.player) {
    game_context.player->Draw(draw_ctx);
  }
}

void game::UpdateBookTransition() {}

void game::SetGameplayState(GameState& state, GameplayState new_state)
{
  if (state.gameplay_state != new_state) {
    /* Cleanup current state first */
    switch (state.gameplay_state) {
      case Normal:
      case State2:
        // g_stateStack += 1;
        // FUN_00106e90();
        break;
      case Loading:
        // Game::NotAllowedToPause += -1;
        // GlobalCounter2 += -1;
        break;
      case FinishedLoadingTransition:
        // System::FinaliseLoad();
        break;
      case Paused:
		break;
        /* If the new state isn't PAUSED, then we should unpause the game */
        // UnpauseGame();
    }

    switch (new_state) {
      case Normal:
      case State2:
        /*
g_stateStack += -1;
if (g_stateStack < 0) {
g_stateStack = 0;
}
      */
        // UpdateDrawingData???();
        break;
      case BegunLoadingTransition:
        state.prevent_state_changes = 1;
        state.field10_0x120 = 0;
        state.loaded_cutscene = 0;
        break;
      case Loading:
        EndScene(state);
        /*
Game::NotAllowedToPause += 1;
GlobalCounter2 += 1;
        */
        /*
pcVar1 = state.playcamAID;
pcVar3 = pcVar1;
do {
  cVar2 = *pcVar3;
  pcVar3[(int)state - (int)pcVar1] = cVar2;
  pcVar3 = pcVar3 + 1;
} while (cVar2 != '\0');
*pcVar1 = '\0';
        */
        // Get script asset header from name and set it
        // SetCurrentPlaycamScript();
        /*
*(undefined4*)((int)&state.field79_0x22b + 1) = 4;
UpdateVolumes();
InitPlaycamScriptAndGlobals();
state.field10_0x120 = 1;
        */
        break;
      case Paused:
        /* Pause is entered here */
        // EnterPauseUI();
        break;
      case FinishedLoadingTransition:
        break;
    }
    state.gameplay_state = new_state;
  }
}

void game::EndScene(GameState& state)
{
  /*
_DAT_0051065c = 1;
if (SkipBackgroundDraw != 0) {
Events::CheckDialogAllocations(0);
}
  Cutscene::SetCutsceneCam();
  FUN_00049ef0();
  FUN_0005b1e0();
  DAT_0050d780 = 0;
  DAT_0050d770 = 0;
  DAT_0050d774 = 0;
  _DAT_0050d778 = 0;
  _DAT_0050d77c = 0;
  FUN_00115f00();
  local_8.header.msgId = Scene_End;
  EventLoop::DispatchMessage(&local_8);
  FUN_001232d0();
  FUN_001222a0();
  FUN_00110ab0();
  FUN_001143a0();
  FUN_00123640();
  FUN_001199f0();
  FUN_0011f610();
  if (g_wavyTexture != NULL) {
    D3D8::D3DResource_Release((D3DResource*)g_wavyTexture);
    g_wavyTexture = NULL;
  }
  DAT_00510580 = 0;
  FUN_001133b0();
  Background::HasBounds = 0;
  BackgroundHasCollision = false;
  Background::MinVector.z = 0.0;
  Background::MinVector.y = 0.0;
  Background::MinVector.x = 0.0;
  Background::MaxVector.z = 0.0;
  Background::MaxVector.y = 0.0;
  Background::MaxVector.x = 0.0;
  BackgroundAABB.aabb.maxZ = 0;
  BackgroundAABB.aabb.maxY = 0;
  BackgroundAABB.aabb.maxX = 0;
  BackgroundAABB.aabb.minZ = 0;
  BackgroundAABB.aabb.minY = 0;
  BackgroundAABB.aabb.minX = 0;
  BackgroundAABB.matrixPtr = 0;
  FUN_000fd710();
  local_8.header.someActor = (actor*)(g_globalFlagset >> 8 & 1);
  DAT_0050ea98 = 0;
  g_globalFlagset = 0;
  if (local_8.header.someActor != NULL) {
    g_globalFlagset = 0x100;
  }
  *(undefined4*)(param_1 + 0x118) = 0;
  FUN_000ed450();
  DAT_00504330 = 0;
  FUN_00129f70();
  FUN_0003a1f0();
  FUN_00118560();
  if (DAT_00512344 != NULL) {
    free(DAT_00512344);
    DAT_00512344 = NULL;
  }
  _DAT_00512348 = 0;
  DAT_00545d20 = 1;
  DAT_00545d28 = 0;
  actorMind::NumObjectTypes = 0;
  NumFrozenAttackTimers = 0;
  Assets::NumSomethingBodies = 0;
  g_AssetBodySearchList[8] = 0;
  g_AssetBodySearchList[9] = 0;
  g_AssetBodySearchList[0x3a] = 0;
  g_AssetBodySearchList[0x3b] = 0;
  FUN_000f44b0();
  UpdateActionType = 0;
  DAT_00545b3c = 0;
  DAT_00545b44 = 0;
  DAT_00545bc4 = 0;
  FUN_0012a9b0();
  FUN_00123b30();
  FUN_001163d0();
  UI::UnloadManyElements ? ();
  Events::EventCount2 = 0;
  FUN_000fae40();
  FUN_0011b630();
  if (CurrentChapterState.markerInstance != NULL) {
    free(CurrentChapterState.markerInstance);
    CurrentChapterState.markerInstance = NULL;
  }
  InvertChallengeStatusGraphics();
  FUN_001272b0();
  g_timeSpentInCurrentLevel = 0.0;
  TimeInCurrentLevel = 0.0;
  g_ticksInCurrentLevel = 0;
  DAT_004312d4 = 0;
  System::TimeScale = 1.0;
  System::Clear_g_itemsToClear();
  FUN_00057dc0();
  FUN_0011cd90();
  FUN_00106e30();
  DAT_00511a10 = 0;
  FUN_0011aea0();
  Subres0x14Instances[0].subres = NULL;
  Subres0x14Instances[1].subres = NULL;
  Subres0x14Instances[2].subres = NULL;
  Subres0x14Instances[3].subres = NULL;
  Subres0x14Instances[4].subres = NULL;
  Subres0x14Instances[5].subres = NULL;
  Subres0x14Instances[6].subres = NULL;
  Subres0x14Instances[7].subres = NULL;
  NumSubres0x14s = 0;
  D3D8::D3D_KickOffAndWaitForIdle();
  FUN_001593d0();
  FUN_000f97f0();
  do {
    iVar1 = FUN_00035d30();
    FUN_00036180();
    FUN_00036180();
  } while (iVar1 != 0);
  FUN_00034880();
  _DAT_0051065c = 0;
*/
}
