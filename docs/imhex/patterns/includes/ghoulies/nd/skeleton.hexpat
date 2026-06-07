#pragma once

#include "ghoulies/nd/types"
#include "ghoulies/types"

struct Bone
{
  u16 parent_id;
  u16 id;
  vec3 local_transform;
  vec3 global_transform;
  u16 sentinel;
  u8 unknown_u8_1;
  u8 unknown_u8_2;
};

struct NdSkeletonDetails
{
  u32 num_bones;
  u32 bones_ptr;

  if (bones_ptr != 0) {
    Bone bones[num_bones] @bones_ptr;
  }
};
