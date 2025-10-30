#include <iostream>

#include "file.hpp"
#include "ghoulies/bnl.hpp"
#include "lib.hpp"

using ghoulies::BNLFile;
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

  auto bytes {ReadFileBytes(argv[1]).value()};

  auto bnl {BNLFile::FromBytes(bytes)};

  // lib.LoadModel(argv[0]);

  while (!lib.ShouldQuit()) {
    lib.UpdateEvents();

    lib.DrawRectangle();
  }

  std::cout << "Ghoulies launcher launched." << '\n';

  return 0;
}
