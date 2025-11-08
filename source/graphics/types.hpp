#pragma once

#include <array>

namespace graphics
{
struct AffineTransform
{
  std::array<std::array<float, 4>, 3> values;
};

}  // namespace graphics
