#include <iostream>

#include <SDL3/SDL_gpu.h>

#include "file.hpp"
#include "ghoulies/bnl.hpp"
#include "ghoulies/script.hpp"
#include "graphics/graphics.hpp"
#include "graphics/model.hpp"
#include "lib.hpp"
#include "menu/menu.hpp"

using ghoulies::BNLFile, ghoulies::Bytes;
using ghoulies::utils::ReadFileBytes;

using ghoulies::Script;

auto main(int argc, char** argv) -> int
{
  auto lib = GhouliesLib {};

  if (!lib.Initialised()) {
    std::cerr << "Unable to initialise core library. Exiting now." << '\n';
    return 1;
  }

  if (argc == 0) {
    std::cerr << "No model available.\n";
    return 1;
  }

  auto& game_context {ghoulies::GameContext::Instance()};

  game_context.move_on = false;
  game_context.sdl_device = lib.GetSDLDevice();

  Bytes bytes {ReadFileBytes(argv[1]).value()};
  auto bnl_exp {BNLFile::FromBytes(bytes)};

  if (!bnl_exp.has_value()) {
    std::cerr << std::format("Unable to load BNL file. Error: {}\n",
                             bnl_exp.error());

    return 1;
  }

  game_context.bnl_files.emplace(argv[1], std::move(bnl_exp).value());

  const auto* tex_raw_asset {
      game_context.GetAsset("aid_texture_ghoulies_weapon_interacthand")};

  if (tex_raw_asset == nullptr) {
    std::cerr
        << "Failed to get asset " "aid_texture_ghoulies_weapon_interacthand.\n";
    return 1;
  }

  graphics::TextureAsset tex_asset {
      .format = SDL_GPU_TEXTUREFORMAT_BC1_RGBA_UNORM,
      .width = 128,
      .height = 128,
      .data = tex_raw_asset->resource};

  auto tex {lib.LoadTexture(tex_asset)};
  if (tex == nullptr) {
    std::cerr << "Failed to create texture.\n";
    return 1;
  }

  lib.SetDefaultTexture(std::move(tex));

  const auto* playcam_script {game_context.GetPlaycamScript()};

  if (playcam_script == nullptr) {
    std::cerr << "Failed to get playcam script.\n";
    return 1;
  }

  Script script {*playcam_script};

  script.Update(game_context);

  ghoulies::objects::Background::BackgroundParams params;
  params.model_aid = game_context.background_model_aid;

  std::cout << "Loading background " << params.model_aid.data() << ".\n";
  ghoulies::objects::Background bg {params};

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

    lib.Menu().NewFrame();
    auto draw_ctx {lib.NewDrawContext()};

    bg.Draw(draw_ctx);
    // skeletonbad->DrawBasic(draw_ctx.render_pass);

    lib.EndDrawContext(draw_ctx);

    lib.Menu().Render();
  }

  std::cout << "Exiting ghoulies launcher." << '\n';

  return 0;
}
