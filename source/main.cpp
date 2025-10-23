#include <iostream>
#include <string>

#include "lib.hpp"

auto main() -> int
{
  auto lib = GhouliesLib {};

  if (!lib.Initialised()) {
    std::cerr << "Unable to initialise core library. Exiting now." << '\n';
  }

  while (!lib.ShouldQuit()) {
    lib.UpdateFrame();
  }

  std::cout << "Ghoulies launcher launched." << '\n';

  return 0;
}
