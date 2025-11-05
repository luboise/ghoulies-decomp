#pragma once

#include <array>

namespace ghoulies::graphics
{
struct AffineTransform
{
  std::array<std::array<float, 4>, 3> values;
};

}  // namespace ghoulies::graphics
