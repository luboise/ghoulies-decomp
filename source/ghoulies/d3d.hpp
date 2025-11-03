#pragma once

#include <cstdint>
#include <ostream>

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

inline std::ostream& operator<<(std::ostream& os, D3DPrimitiveType d3d_type)
{
  switch (d3d_type) {
    case D3DPrimitiveType::kNone:
      os << "D3DNone";
      break;
    case D3DPrimitiveType::kPointList:
      os << "D3DPointList";
      break;
    case D3DPrimitiveType::kLineList:
      os << "D3DLineList";
      break;
    case D3DPrimitiveType::kLineLoop:
      os << "D3DLineLoop";
      break;
    case D3DPrimitiveType::kLineStrip:
      os << "D3DLineStrip";
      break;
    case D3DPrimitiveType::kTriangleList:
      os << "D3DTriangleList";
      break;
    case D3DPrimitiveType::kTriangleStrip:
      os << "D3DTriangleStrip";
      break;
    case D3DPrimitiveType::kTriangleFan:
      os << "D3DTriangleFan";
      break;
    case D3DPrimitiveType::kQuadList:
      os << "D3DQuadList";
      break;
    case D3DPrimitiveType::kQuadStrip:
      os << "D3DQuadStrip";
      break;
    case D3DPrimitiveType::kPolygon:
      os << "D3DPolygon";
      break;
    case D3DPrimitiveType::kMax:
      os << "D3DMax";
      break;
    case D3DPrimitiveType::kInvalid:
      os << "D3DInvalid";
      break;
  }

  return os;
}

enum class D3DTextureType : uint32_t
{
  kDXT1 = 0x0000000C,
  kDXT2 = 0x0000000E,
  kDXT3 = 0x0000000E,
  kA8R8G8B8 = 0x00000012,
};

inline std::ostream& operator<<(std::ostream& os, D3DTextureType d3d_type)
{
  switch (d3d_type) {
    case D3DTextureType::kDXT1:
      os << "DXT1";
      break;
    case D3DTextureType::kDXT2:
      os << "DXT2";
      break;
    case D3DTextureType::kA8R8G8B8:
      os << "A8R8G8B8";
      break;
  }

  return os;
}

}  // namespace d3d
