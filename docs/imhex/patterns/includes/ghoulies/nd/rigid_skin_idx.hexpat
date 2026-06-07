#pragma once

struct NdRigidSkinIdxDetails
{
  u32 indices_ptr;
  u32 num_indices;

  if (indices_ptr != 0 && num_indices > 0) {
    u8 indices[num_indices] @indices_ptr;
  }
};
