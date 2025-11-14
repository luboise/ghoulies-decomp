#pragma once

#include <array>
#include <cstdint>

namespace physics
{

enum ColliderType : std::uint8_t
{
  Sphere = 0,
  Cylinder = 1,
  Box = 2,
  PartSphere = 3
};

enum CollisionMask : std::uint32_t
{
  CollisionBit0x1 = 0x1,
  CollisionBit0x2 = 0x2,
  CollisionBitWall = 0x4,
  CollisionBitGround = 0x8,

  /*
  mask = 0x10,
  mask = 0x20,
  mask = 0x40,
  mask = 0x80,

  mask = 0x100,
  mask = 0x200,
  mask = 0x400,
  mask = 0x800,
  mask = 0x1000,
  mask = 0x2000,
  mask = 0x4000,
  mask = 0x8000,

  mask = 0x10000,
  mask = 0x20000,
  mask = 0x40000,
  mask = 0x80000,
  mask = 0x100000,
  mask = 0x200000,
  mask = 0x400000,
  mask = 0x800000,

  mask = 0x1000000,
  mask = 0x2000000,
  mask = 0x4000000,
  mask = 0x8000000,
  mask = 0x10000000,
  mask = 0x20000000,
  mask = 0x40000000,
  mask = 0x80000000,
  */
  All = 0xffffffff,
};

struct Collider0x4
{
  ColliderType collider_type;
  std::uint8_t size;
  std::uint16_t blend_target_index;

  CollisionMask collision_mask;
  std::uint16_t short1;
  std::uint16_t short2;

  std::uint32_t pad_zero;
  float radius;
  std::array<float, 3> position;
  std::uint32_t group;
};

static_assert(sizeof(Collider0x4) == 36);

}  // namespace physics
