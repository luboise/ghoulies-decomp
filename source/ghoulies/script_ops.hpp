#pragma once

#include <cstdint>
#include <type_traits>
#include <variant>

#include "../utils/file.hpp"
#include "types.hpp"

namespace ghoulies
{

using utils::file::Bytes;

enum ScriptOpcode : uint32_t
{
  EndScript = 0,
  SetBackground = 1,
  AddSceneControl = 2,
  SetSomething0x4 = 4,
  U0x5 = 5,
  SetNumSuperScaryInputs = 6,
  SetSomething0x7 = 7,
  UpdateSomethingByTag0x8 = 8,
  SetNoAttackTimer = 9,
  SetSceneName = 10,
  U0xb = 11,
  U0xc = 12,
  SetPlayState = 14,
  WaitForMoveOn = 15,
  MoveOn = 17,
  U0x12 = 18,
  PlayCutscene = 19,
  ShowDialogByName = 20,
  PlayEventIntro = 23,
  EndDescribingChallenge = 24,
  CreateSomeChallenge = 25,
  CreateTimeLimitChallenge = 26,
  CreateXChallenge = 27,
  CreateKillAllByTagChallenge = 28,
  CreateKillNByTagChallenge = 29,
  CreateFindTheGhoulieKeyChallenge = 31,
  CreateDontKillByTagChallenge = 33,
  CreateWeaponsOnlyChallenge = 35,
  CreateNextOneDifferentChallenge = 37,
  CreateFindTheKeyChallenge = 39,
  CreateNoBreakHouseChallenge = 40,
  UpdateDoor = 41,
  SpawnGhoulyWithBox = 42,
  ExecuteGhoulyspawn = 43,
  SetPlayerWorried = 47,
  Signal0x30 = 48,
  Group10x32 = 50,
  Group10x33 = 51,
  Group10x34 = 52,
  Group10x35 = 53,
  Group10x36 = 54,
  Group10x37 = 55,
  Group10x38 = 56,
  U0x39 = 57,
  Signal0x3b = 59,
  EndCondition = 60,
  TimeoutCondition = 61,
  NumberGhouliesAliveCondition = 62,
  ScareSourceProximityCondition = 63,
  ObjectPickedUpCondition = 64,
  NumberGhouliesKilledCondition = 65,
  NumberOfKnockdownsCondition = 66,
  PlayerApproachesDoorCondition = 67,
  HauntedObjectActivatedCondition = 68,
  Signal0x45 = 69,
  PlayerEntersRegionCondition = 71,
  PlayerLeavesRegionCondition = 72,
  SetGlobalFlag1 = 73,
  SetGlobalFlag2 = 74,
  U0x4b = 75,
  U0x4f = 79,
  U0x52 = 82,
  PlayWalkinCutscene = 83,
  PlayMusicByActorTag = 85,
  U0x56 = 86,
  U0x59 = 89,
  SpecificGhouliesAliveCondition = 90,
  SpecificGhouliesKilledCondition = 91,
  SetCameraProperties = 97,
  ObjectByMarkerRemovedCondition = 101,
  PlayerDeflectionContactCondition = 102,
  PlayerHitGhoulyCondition = 104,
  GhoulyTriggeredCondition = 106,
  GhoulyExistsInSceneCondition = 108,
  AddGhoulyByTag = 109,
  ObjectByMarkerBrokenCondition = 114,
  ActorHasNoEnergyCondition = 117,
  SetChallengeId = 122,
  Group20x7b = 123,
  Group20x7c = 124,
  Group20x7d = 125,
  Group20x7e = 126,
  Group20x7f = 127,
  Group20x80 = 128,
  Group20x81 = 129,
  Group20x82 = 130,
  Group20x83 = 131,
  Group20x84 = 132,
  Group20x85 = 133,
  Group20x86 = 134,
  EveryNthKillCondition = 139,
  NoGhoulySpawnsActiveCondition = 140,
  PlaySound = 141,
  RotateSomethingByNDegrees = 143,
  U0x90 = 144,
  U0x91 = 145,
  Challenge21ActiveCondition = 146,
  Challenge21NotActiveCondition = 147,
  GhoulyEntersRegionCondition = 148,
  GhoulySignalCondition = 153,
  U0x9f = 159,
  ObjectByMarkerNotBrokenCondition = 163,
};

struct RawScriptOperation
{
  ScriptOpcode opcode;
  Bytes operand_bytes;
};

template<ScriptOpcode Op>
struct ScriptOperationBase
{
  [[nodiscard]] constexpr ScriptOpcode Opcode() const { return Op; }

  // Default is operand has no bytes
  [[nodiscard]] Bytes OperandBytes() const { return {}; }

  [[nodiscard]] RawScriptOperation AsRawOperation() const
  {
    return RawScriptOperation {.opcode = Op,
                               .operand_bytes = this->OperandBytes()};
  }
};

/// Macro for defining a script operation which takes no operands
#define MakeSignalOperation(StructName, enumVal) \
  struct StructName : public ScriptOperationBase<enumVal> \
  { \
  };

MakeSignalOperation(EndScriptOperation, EndScript);

struct SetBackgroundOperation : public ScriptOperationBase<SetBackground>
{
  explicit SetBackgroundOperation(AssetAID background_aid)
      : background_aid(background_aid)
  {
  }

  AssetAID background_aid;
};

MakeSignalOperation(WaitForMoveOnOperation, WaitForMoveOn);

#undef MakeSignalOperation

using ScriptOperation = std::variant<EndScriptOperation,
                                     SetBackgroundOperation,
                                     WaitForMoveOnOperation,
                                     RawScriptOperation>;

static_assert(std::is_nothrow_move_constructible_v<ScriptOperation>,
              "ScriptOperation is not nothrow-move-constructible!");

}  // namespace ghoulies
