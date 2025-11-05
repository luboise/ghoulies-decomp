#pragma once

#include <cstdint>
#include <variant>

#include "../file.hpp"
#include "types.hpp"

namespace ghoulies
{

using utils::Bytes;

enum ScriptOpcode : uint32_t
{
  kEndScript = 0,
  kSetBackground = 1,
  kAddSceneControl = 2,
  kSetSomething0x4 = 4,
  kU0x5 = 5,
  kSetNumSuperScaryInputs = 6,
  kSetSomething0x7 = 7,
  kUpdateSomethingByTag0x8 = 8,
  kSetNoAttackTimer = 9,
  kSetSceneName = 10,
  kU0xb = 11,
  kU0xc = 12,
  kSetPlayState = 14,
  kWaitForMoveOn = 15,
  kMoveOn = 17,
  kU0x12 = 18,
  kPlayCutscene = 19,
  kShowDialogByName = 20,
  kPlayEventIntro = 23,
  kEndDescribingChallenge = 24,
  kCreateSomeChallenge = 25,
  kCreateTimeLimitChallenge = 26,
  kCreateXChallenge = 27,
  kCreateKillAllByTagChallenge = 28,
  kCreateKillNByTagChallenge = 29,
  kCreateFindTheGhoulieKeyChallenge = 31,
  kCreateDontKillByTagChallenge = 33,
  kCreateWeaponsOnlyChallenge = 35,
  kCreateNextOneDifferentChallenge = 37,
  kCreateFindTheKeyChallenge = 39,
  kCreateNoBreakHouseChallenge = 40,
  kUpdateDoor = 41,
  kSpawnGhoulyWithBox = 42,
  kExecuteGhoulyspawn = 43,
  kSetPlayerWorried = 47,
  kSignal0x30 = 48,
  kGroup10x32 = 50,
  kGroup10x33 = 51,
  kGroup10x34 = 52,
  kGroup10x35 = 53,
  kGroup10x36 = 54,
  kGroup10x37 = 55,
  kGroup10x38 = 56,
  kU0x39 = 57,
  kSignal0x3b = 59,
  kEndCondition = 60,
  kTimeoutCondition = 61,
  kNumberGhouliesAliveCondition = 62,
  kScareSourceProximityCondition = 63,
  kObjectPickedUpCondition = 64,
  kNumberGhouliesKilledCondition = 65,
  kNumberOfKnockdownsCondition = 66,
  kPlayerApproachesDoorCondition = 67,
  kHauntedObjectActivatedCondition = 68,
  kSignal0x45 = 69,
  kPlayerEntersRegionCondition = 71,
  kPlayerLeavesRegionCondition = 72,
  kSetGlobalFlag1 = 73,
  kSetGlobalFlag2 = 74,
  kU0x4b = 75,
  kU0x4f = 79,
  kU0x52 = 82,
  kPlayWalkinCutscene = 83,
  kPlayMusicByActorTag = 85,
  kU0x56 = 86,
  kU0x59 = 89,
  kSpecificGhouliesAliveCondition = 90,
  kSpecificGhouliesKilledCondition = 91,
  kSetCameraProperties = 97,
  kObjectByMarkerRemovedCondition = 101,
  kPlayerDeflectionContactCondition = 102,
  kPlayerHitGhoulyCondition = 104,
  kGhoulyTriggeredCondition = 106,
  kGhoulyExistsInSceneCondition = 108,
  kAddGhoulyByTag = 109,
  kObjectByMarkerBrokenCondition = 114,
  kActorHasNoEnergyCondition = 117,
  kSetChallengeId = 122,
  kGroup20x7b = 123,
  kGroup20x7c = 124,
  kGroup20x7d = 125,
  kGroup20x7e = 126,
  kGroup20x7f = 127,
  kGroup20x80 = 128,
  kGroup20x81 = 129,
  kGroup20x82 = 130,
  kGroup20x83 = 131,
  kGroup20x84 = 132,
  kGroup20x85 = 133,
  kGroup20x86 = 134,
  kEveryNthKillCondition = 139,
  kNoGhoulySpawnsActiveCondition = 140,
  kPlaySound = 141,
  kRotateSomethingByNDegrees = 143,
  kU0x90 = 144,
  kU0x91 = 145,
  kChallenge21ActiveCondition = 146,
  kChallenge21NotActiveCondition = 147,
  kGhoulyEntersRegionCondition = 148,
  kGhoulySignalCondition = 153,
  kU0x9f = 159,
  kObjectByMarkerNotBrokenCondition = 163,
};

struct RawScriptOperation
{
  ScriptOpcode opcode;
  Bytes operand_bytes;
};

struct IScriptOperation
{
  [[nodiscard]] RawScriptOperation AsRawOperation() const;
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

MakeSignalOperation(EndScriptOperation, kEndScript);

struct SetBackgroundOperation : public ScriptOperationBase<kSetBackground>
{
  explicit SetBackgroundOperation(AssetAID background_aid)
      : background_aid(background_aid)
  {
  }

  AssetAID background_aid;
};

MakeSignalOperation(WaitForMoveOnOperation, kWaitForMoveOn);

#undef MakeSignalOperation

using ScriptOperation = std::variant<EndScriptOperation,
                                     SetBackgroundOperation,
                                     WaitForMoveOnOperation,
                                     RawScriptOperation>;
}  // namespace ghoulies
