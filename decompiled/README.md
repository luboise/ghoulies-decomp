# Grabbed by the Ghoulies - decompiled (`default.xbe`)

Re-organised output of a Ghidra decompilation of the Xbox `default.xbe`
(_Grabbed by the Ghoulies_, MS-083, Rest of World). The original Ghidra dump
(`recompiled/default.xbe.cpp` + `default.xbe.h`, ~675k lines, 7389 functions)
has been split, grouped, and declared into a module-based layout **without
losing any functions**.

## Origin

- Binary: `.. /ghoulies_uncapped/default.xbe` (4.5 MB, DDoS-signed Xbox XBE, x86).
- Decompiler: Ghidra. Function/label bodies, types, enums, and globals were
  taken verbatim; only the *grouping* is mine.
- This is reverse-engineered output, **not** the original source. Symbol
  recovery is partial: ~2260 functions have meaningful names, the rest are
  `FUN_<addr>` / `LAB_<addr>` stubs or thunks.

## Files

- `types.h`          - full type / enum / struct catalogue (verbatim from the
  original `.h`). ~300k lines. Every struct, the `objTag`/`actorBodyStateId`/
  `animEventId` enums, D3D format enum, etc.
- `common.h`         - global variable declarations + `#include` list for all
  module headers.
- `xbox_types.h`     - tiny shim re-exporting platform constants from `types.h`.
- `<module>.c/.h`    - one pair per module (see map below). `.c` holds the
  function bodies; `.h` holds the `extern` declarations and `#include "common.h"`.
- `catchall_0x<addr>.c/.h` - anonymous `FUN_`/`LAB_`/`thunk_` functions, in a
  separate file each, **ordered by virtual address** (the binary layout).
- `CMakeLists.txt`   - skeleton build (see below).

## Module map

| Module | What's in it |
|---|---|
| `system` | Entry point (`entry`, `main`, `BigInitXBEFunction`), init/teardown, `GameLoop`, state wipe |
| `xapilib` | XAPILIB wrappers — XGetLaunchInfo, XMemAlloc, XOpenFile, QueryFile, etc. |
| `xgraphics_d3d` | XGRAPHICS / D3D8 / D3DX8 driver wrappers |
| `audio` | XACT, X3DAudio, DirectSound (DSOUND), cues, wavebanks, rumble |
| `input` | Input handlers, gamepad/controller polling, virtual keyboard, dpad |
| `assets` | BNL / bundle asset loading, objParams, AID tables, model data |
| `fileio` | FileContext, bundle streaming, zlib (`z_stream`), Bink movie, save |
| `crypto` | Xbox PKCS1/SHA1 signature verification (`XcSHA*`, `XcVerifyPKCS1Signature`) |
| `math` | Trig, vectors/matrices (`vec3`/`vec4`/`D3DXMATRIX`), `float10`, random |
| `animation` | Keyframes, attack instances, bone affines, attack-data |
| `graphics` | Textures, pixel/vertex shaders, XGBuffers, burnups, camera mgmt |
| `background` | Background rendering, `GhoulyBox`, background collision things, doors |
| `camera` | Camera configs (`CameraDescriptor`, `MainCameraStruct`, playcam/director) |
| `modelsnd` | Models & nd-tree: mesh, skeleton, nd-shaders, model subresources |
| `collision` | EDB2 broadphase, colliders, physics, A* paths |
| `ai_actor` | `actorBody`/`actor`/`actorMind` base, hit reactions, body states |
| `ai_strategy` | `actorStrategy` enemy behaviours |
| `entity_body` | Body subclasses: `entityBodyHuman`/`Camera`/`Player` |
| `entity_state` | Actor state machines (walk/hit/scoop/pickup/fly/stand, ...) |
| `actor_move` | Movement: crane, XZ-gravity, alert |
| `avatar` | `avatar` base type and parameters |
| `entities` | Avatar & strategy entity subclasses |
| `fx` | Particle/FX avatars, impact emitters, burnups |
| `weapon` | Weapons, projectiles, extinguishers, wield logic, melee attack handlers |
| `powerup` | Powerups |
| `scripting` | Script engine: parse / run / free scripts (`Scripting`, `Script*`) |
| `events` | Event loops / markers / challenge triggers (`EventLoop`, `Events`) |
| `cutscene` | Cutscenes, playcams, transitions, storybook |
| `marker` | Spawn / scene markers (`Marker::*`) |
| `scene_control` | Scene controllers (chapters, game-select, super-scary, doors) |
| `menus` | Menus & UI (pause, replay, challenge menus, `UI::*`) |
| `game_core` | Core game state, world update, save game |
| `runtime` | Runtime data structures: `BigBlock`, EDB2, buffers, loctext, fonts, heaps |
| `msvc_runtime` | MSVC C++ runtime / CRT / math intrinsics — **external, keep as-is** |
| `catchall_0x*` | Anonymous `FUN_`/`LAB_`/`thunk_` stubs, grouped by address range |

## Build

The sources are x86 Xbox code referencing the Xbox SDK
(XAPILIB, XGRAPHICS/D3D8, XACT/X3DAudio, XSound, plus zlib and Bink video)
and MS's `__`-prefixed CRT — none of which are portable to a host, so this
**will not link or compile on a modern host** without reimplementing those
interfaces. `CMakeLists.txt` is a skeleton documenting the module
boundaries; you'll want to:

1. Provide the Xbox SDK shims (`xapilib`, `xgraphics`, `xact`, `xsound`).
2. Provide `zlib` and `bink` video decoders (referenced in `fileio`).
3. Decide whether to compile as C++ (it uses C++ exceptions and vtables —
   e.g. `std::basic_string`, `std::__throw_*`, vtable dispatch) or to C-ify
   the bodies yourself.

## Notes

- `common.h` declares every global variable from the original and includes all
  module headers, so a module `.c` can call into any other module.
- `msvc_runtime` and `crypto` hold the parts that came from external/standard
  libraries — left in place but not part of the game logic.
- Anonymous functions (`catchall_*`) are address-ordered so they mirror the
  original binary layout, which is the only signal available for them.
