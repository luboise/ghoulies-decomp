#include <iostream>

#include <SDL3/SDL_gpu.h>

#include "lib.hpp"

using ghoulies::GhouliesLibParams;

auto main(int argc, char** argv) -> int
{
  if (argc != 2) {
    std::cerr << "Expected playcam script in CLI args. eg. ghoulies_launcher "
                 "aid_model_script_chapter2a_scene2_1playcam.bnl";
    return 1;
  }

  // Initialise the application
  GhouliesLibParams params {};

  if (auto result {ghoulies::GhouliesLib::Initialise(std::move(params))};
      !result.has_value())
  {
    std::cerr << "Unable to initialise GhouliesLib. Error: " << result.error()
              << "\n";
    return 1;
  }

  auto& lib {ghoulies::GhouliesLib::Instance()};

  // Set the play script

  if (auto result {lib.SetPlaycamScript(argv[1])}; !result.has_value()) {
    std::cerr << "Failed to execute level from BNL file " << argv[1]
              << ". Error: " << result.error() << "\n";
    return 1;
  }

  std::cout << "Ghoulies launcher launched." << '\n';

  while (!lib.ShouldQuit()) {
    lib.BeginFrame();
    lib.UpdateEvents();

    lib.UpdateScene();

    // Draw everything
    auto draw_ctx {lib.NewDrawContext()};
    lib.GameLoop(draw_ctx);
    lib.EndDrawContext(std::move(draw_ctx));
    lib.EndFrame();
  }

  if (auto result {ghoulies::GhouliesLib::Destroy()}; !result.has_value()) {
    std::cout << "Failed to destroy GhouliesLib. Error: " << result.error();
  }

  std::cout << "Exiting ghoulies launcher." << '\n';

  return 0;
}
