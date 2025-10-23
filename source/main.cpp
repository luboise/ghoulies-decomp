#include <iostream>
#include <string>

#include "lib.hpp"

auto main() -> int
{
  auto lib = GhouliesLib {};

  if (!lib.Initialised()) {
    std::cerr << "Unable to initialise core library. Exiting now." << '\n';
    return 1;
  }

  while (!lib.ShouldQuit()) {
    lib.UpdateEvents();

    lib.DrawRectangle();
  }

  std::cout << "Ghoulies launcher launched." << '\n';

  return 0;
}
