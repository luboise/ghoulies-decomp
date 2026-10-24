cmake_minimum_required(VERSION 3.16)
project(ghoulies_decompiled CXX)

# NOTE: This is a skeleton. The sources are Ghidra decompilation of a
# Xbox (x86) XBE. They reference the Xbox SDK (XAPILIB, XGRAPHICS,
# XACT, XSound, zlib, Bink) which are not portable, so this will not
# link on a normal host. It documents the module boundaries.

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


# Core library modules (game logic + xbox wrappers)
add_library(ghoulies STATIC
  actor_move.c
  ai_actor.c
  ai_strategy.c
  animation.c
  assets.c
  audio.c
  avatar.c
  background.c
  camera.c
  catchall_0x11000.c
  catchall_0x17af20.c
  catchall_0xceec0.c
  collision.c
  crypto.c
  cutscene.c
  entities.c
  entity_body.c
  entity_state.c
  events.c
  fileio.c
  fx.c
  game_core.c
  graphics.c
  input.c
  marker.c
  math.c
  menus.c
  modelsnd.c
  msvc_runtime.c
  powerup.c
  runtime.c
  scene_control.c
  scripting.c
  system.c
  weapon.c
  xapilib.c
  xgraphics_d3d.c
)

set_target_properties(ghoulies PROPERTIES LINKER_LANGUAGE CXX)

target_include_directories(ghoulies PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Xbox-specific dependencies you would provide yourself:
#   XAPILIB, XGRAPHICS/D3D8, XACT/X3DAudio, XSound, zlib, Bink
# Link them via: target_link_libraries(ghoulies PUBLIC xapilib xgraphics xact xsound z bink)
