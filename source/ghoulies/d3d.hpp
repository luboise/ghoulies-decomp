#pragma once

#include <cstdint>

namespace d3d
{

enum class D3DPrimitiveType : uint32_t
{
  kNone = 0,
  kPointList = 1,
  kLineList = 2,
  kLineLoop = 3,
  kLineStrip = 4,
  kTriangleList = 5,
  kTriangleStrip = 6,
  kTriangleFan = 7,
  kQuadList = 8,
  kQuadStrip = 9,
  kPolygon = 10,
  kMax = 11,
  kInvalid = 0x7ffffff,
};

enum class D3DTextureType : uint32_t
{
  kDXT1 = 0x0000000C,
  kDXT2 = 0x0000000E,
  kDXT3 = 0x0000000E,
  kA8R8G8B8 = 0x00000012,
};

}  // namespace d3d
