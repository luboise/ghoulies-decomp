#pragma once

#include <cstdint>
#include <list>

#include "../ghoulies/objects/avatar.hpp"
#include "../ghoulies/types.hpp"
#include "ghoulies/objects/actor.hpp"
#include "ghoulies/objects/avatar/background.hpp"
#include "graphics/graphics.hpp"

namespace game
{

using ghoulies::objects::Actor, ghoulies::objects::Avatar,
    ghoulies::objects::Background;

using ghoulies::AssetAID;
using ghoulies::EmbeddedNode;
using ghoulies::objects::Avatar;

enum GameplayState : std::uint32_t
{
  Unknown0x0 = 0,
  Normal = 1,
  State2 = 2,
  BegunLoadingTransition = 3,
  Loading = 4,
  FinishedLoadingTransition = 5,
  Paused = 6
};

struct SceneInfo
{
  int field0_0x0;
  int field1_0x4;
  std::array<std::uint32_t, 8> bruhs;
  std::array<std::uint32_t, 8> bruhs2;
  int field4_0x48;
  int field5_0x4c;
  /// avatar@0x1e0
  EmbeddedNode<Avatar*> avatar_colliders;
  std::uint32_t unknown_0x58;
  int field11_0x5c;
  int field12_0x60;
  int field13_0x64;
  EmbeddedNode<Avatar*> avatars_to_insert;
  int field16_0x70;
  EmbeddedNode<Avatar*> scene_tree;
  std::list<std::shared_ptr<Background>> backgrounds;
  int field20_0x84;
  // std::uint32_t sceneTree ;
  // int field22_0x8c;
  std::uint32_t field23_0x90;
  EmbeddedNode<Actor*> actors_0x934;
  EmbeddedNode<Actor*> actors_0x93c;
  std::uint32_t field26_0xa4;
  std::uint32_t field27_0xa8;
  std::uint32_t field28_0xac;
  std::uint32_t field29_0xb0;
  int field30_0xb4;
  int field31_0xb8;
  EmbeddedNode<Avatar*> avatars_0x910;
};

struct GameState
{
  AssetAID current_scene_script;
  AssetAID playcam_aid;
  int field2_0x100;
  GameplayState gameplay_state {GameplayState::Normal};
  GameplayState new_gameplay_state;
  int prev_state;
  int prevent_state_changes;
  int loaded_cutscene;
  struct actor* actor;
  int field9_0x11c;
  int field10_0x120;
  int current_chapter;
  int current_scene;
  int field13_0x12c;
  int field14_0x130;
  int field15_0x134;
  int field16_0x138;
  int field17_0x13c;
  int field18_0x140;
  int field19_0x144;
  int field20_0x148;
  int field21_0x14c;
  int field22_0x150;
  int field23_0x154;
  int something_state;
  void* unknown_ptr;
  UNKNOWN_FIELD(0x160, 0x208);
  std::uint8_t field69_0x20c;
  std::uint8_t field70_0x20d;
  std::uint8_t field71_0x20e;
  UNKNOWN_FIELD(0x20f, 0x227);
  struct ScriptType2* field79_0x22b;
  struct ScriptType2* loctext;
  std::uint8_t field81_0x233;
  struct MarkerInstance* marker_instance;
  std::uint8_t field83_0x238;
  std::uint8_t field84_0x239;
  std::uint8_t field85_0x23a;
  struct AssetGroup* asset_group;
  struct TwoPositions* heap_mem1;
  int field88_0x243;
  struct D3DResource* field89_0x247;
  struct D3DResource* d3dr1;
  struct D3DResource* d3dr2;
  struct D3DResource* d3dr3;
  struct D3DResource* d3dr4;
  int rendering_enabled;  // bool
  UNKNOWN_FIELD(0x25f, 0x28f);
  char field108_0x293;
  UNKNOWN_FIELD(0x294, 0x300);
  std::uint8_t field137_0x304;
  std::uint8_t field138_0x305;

  SceneInfo scene_info;
};

void RunUpdate(graphics::DrawContext& draw_ctx, GameState& state);

void UpdateEntities(graphics::DrawContext& draw_ctx, GameState& state);
void UpdateBookTransition();

void SetGameplayState(GameState& state, GameplayState new_state);

void EndScene(GameState& state);

void UpdateAvatarRecursive(ghoulies::objects::Avatar* avatarl);

}  // namespace game
