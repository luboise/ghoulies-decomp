#include <iostream>

#include "file.hpp"
#include "ghoulies/bnl.hpp"
#include "graphics/graphics.hpp"
#include "lib.hpp"

using ghoulies::BNLFile, ghoulies::Bytes;
using ghoulies::utils::ReadFileBytes;

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

  Bytes bytes {ReadFileBytes(argv[1]).value()};
  auto bnl_exp {BNLFile::FromBytes(bytes)};

  if (!bnl_exp.has_value()) {
    std::cerr << std::format("Unable to load BNL file. Error: {}\n",
                             bnl_exp.error());

    return 1;
  }

  BNLFile bnl {std::move(bnl_exp).value()};

  const auto* asset {
      bnl.GetAsset("aid_texture_ghoulies_powerups_knockdownmania")};

  if (asset == nullptr) {
    std::cerr << "Failed to get asset "
                 "aid_texture_ghoulies_powerups_knockdownmania.\n";
    return 1;
  }

  std::cout << std::format("Descriptor size: {}     Resource size: {}\n",
                           asset->descriptor.size(),
                           asset->resource.size());

  graphics::TextureParams params {
      .width = 128, .height = 128, .data = asset->resource};

  auto tex {lib.LoadTexture(params)};

  if (tex == nullptr) {
    std::cerr << "Failed to create texture.\n";
    return 1;
  }

  std::cout << "Ghoulies launcher launched." << '\n';

  while (!lib.ShouldQuit()) {
    lib.UpdateEvents();
    lib.DrawRectangle();
  }

  return 0;
}
