#pragma once

struct NdRigidSkinIdxDetails
{
  s128 model_root = parent.model_root;

  u32 indices_ptr;
  u32 num_indices;

  if (indices_ptr != 0 && num_indices > 0) {
    u8 indices[num_indices] @model_root + indices_ptr;
  }
};
