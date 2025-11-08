#include <iostream>
#include <memory>

#include <SDL3/SDL_gpu.h>

#include "file.hpp"
#include "ghoulies/assets/marker.hpp"
#include "ghoulies/bnl.hpp"
#include "ghoulies/script.hpp"
#include "graphics/graphics.hpp"
#include "graphics/model.hpp"
#include "lib.hpp"
#include "menu/menu.hpp"

using ghoulies::BNLFile, ghoulies::Bytes;
using ghoulies::utils::ReadFileBytes;

using ghoulies::GhouliesLibParams;
using ghoulies::Script, ghoulies::Marker, ghoulies::GhouliesLib;

auto main(int argc, char** argv) -> int
{
  if (argc != 2) {
    std::cerr << "Expected playcam script in CLI args. eg. ghoulies_launcher "
                 "aid_model_script_chapter2a_scene2_1playcam.bnl";
    return 1;
  }

  // Initialise the application
  GhouliesLibParams params {};

  if (auto result {GhouliesLib::Initialise(std::move(params))};
      !result.has_value())
  {
    std::cerr << "Unable to initialise GhouliesLib. Error: " << result.error()
              << "\n";
    return 1;
  }

  auto& lib {GhouliesLib::Instance()};

  // Set the play script

  if (auto result {lib.SetPlaycamScript(argv[1])}; !result.has_value()) {
    std::cerr << "Failed to execute level from BNL file " << argv[1]
              << ". Error: " << result.error() << "\n";
    return 1;
  }

  /*
  std::cout << "Loading skeletonbad.\n";
  const auto* raw_skeletonbad {
      game_context.GetAsset("aid_model_ghoulies_actor_skeletonbad")};
  auto skeletonbad {lib.LoadModel(*raw_skeletonbad)};
  */

  std::cout << "Ghoulies launcher launched." << '\n';

  // lib.DrawTestObjects(*tex);
  while (!lib.ShouldQuit()) {
    lib.UpdateEvents();

    // TODO:
    // - Begin one command buffer
    // - Begin new render pass
    // - Draw scene
    // - End render pass
    // - Render Imgui
    // - Begin new render pass
    // - Render to the screen
    // - End render pass
    // - Submit command buffer all together

    // lib.Menu().NewFrame();

    // Draw everything
    auto draw_ctx {lib.NewDrawContext()};
    lib.DrawScene(draw_ctx);
    lib.EndDrawContext(draw_ctx);

    // lib.Menu().Render();
  }

  std::cout << "Exiting ghoulies launcher." << '\n';

  return 0;
}
