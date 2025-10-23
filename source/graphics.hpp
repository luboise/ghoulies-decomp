#pragma once

namespace graphics
{

using Vec2 = float[2];
using Vec3 = float[3];
using Vec4 = float[4];

using Mat2 = Vec2[2];
using Mat3 = Vec3[3];
using Mat4 = Vec4[4];

struct PBRVertex
{
  Vec3 a_position {0, 0, 0};
  Vec3 a_colour {0, 0, 1};
  Vec3 a_normal {0, 1, 0};
  Vec2 a_texcoords {0, 0};
};

}  // namespace graphics
