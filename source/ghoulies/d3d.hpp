#pragma once

#include <cstdint>
#include <ostream>

namespace d3d
{

enum class D3DPrimitiveType : uint32_t
{
  None = 0,
  PointList = 1,
  LineList = 2,
  LineLoop = 3,
  LineStrip = 4,
  TriangleList = 5,
  TriangleStrip = 6,
  TriangleFan = 7,
  QuadList = 8,
  QuadStrip = 9,
  Polygon = 10,
  Max = 11,
  Invalid = 0x7ffffff,
};

inline std::ostream& operator<<(std::ostream& os, D3DPrimitiveType d3d_type)
{
  switch (d3d_type) {
    case D3DPrimitiveType::None:
      os << "D3DNone";
      break;
    case D3DPrimitiveType::PointList:
      os << "D3DPointList";
      break;
    case D3DPrimitiveType::LineList:
      os << "D3DLineList";
      break;
    case D3DPrimitiveType::LineLoop:
      os << "D3DLineLoop";
      break;
    case D3DPrimitiveType::LineStrip:
      os << "D3DLineStrip";
      break;
    case D3DPrimitiveType::TriangleList:
      os << "D3DTriangleList";
      break;
    case D3DPrimitiveType::TriangleStrip:
      os << "D3DTriangleStrip";
      break;
    case D3DPrimitiveType::TriangleFan:
      os << "D3DTriangleFan";
      break;
    case D3DPrimitiveType::QuadList:
      os << "D3DQuadList";
      break;
    case D3DPrimitiveType::QuadStrip:
      os << "D3DQuadStrip";
      break;
    case D3DPrimitiveType::Polygon:
      os << "D3DPolygon";
      break;
    case D3DPrimitiveType::Max:
      os << "D3DMax";
      break;
    case D3DPrimitiveType::Invalid:
      os << "D3DInvalid";
      break;
  }

  return os;
}

enum class D3DTextureType : uint32_t
{
  DXT1 = 0x0000000C,
  DXT2 = 0x0000000E,
  DXT3 = 0x0000000E,
  A8R8G8B8 = 0x00000012,
};

inline std::ostream& operator<<(std::ostream& os, D3DTextureType d3d_type)
{
  switch (d3d_type) {
    case D3DTextureType::DXT1:
      os << "DXT1";
      break;
    case D3DTextureType::DXT2:
      os << "DXT2";
      break;
    case D3DTextureType::A8R8G8B8:
      os << "A8R8G8B8";
      break;
  }

  return os;
}

}  // namespace d3d
