#include <std/array>

#include "ghoulies/nd/types"

struct NdPushBufferDetails
{
  s128 model_root = parent.model_root;

  u32 num_draws;
  u32 idk1;
  u32 idk2;
  u32 idk3;
  // Pointer lists
  u32 push_data_ptrs;
  u32 primitives_ptr;
  u32 vertex_counts_ptr;
  u8 doNotCull;  // Bool
  u8 pad[3];

  if (vertex_counts_ptr != 0) {
    std::Array<u32, num_draws> vertex_counts @model_root + vertex_counts_ptr;
  }

  if (primitives_ptr != 0) {
    std::Array<u32, num_draws> primitive_types @model_root + primitives_ptr;
  }

  if (push_data_ptrs != 0) {
    NdPtr<std::Array<u16, 2>> push_data_ptrs[num_draws] @model_root
        + push_data_ptrs;
  }
};

struct NdBGPushBufferDetails
{
  s128 model_root = parent.model_root;
  NdPushBufferDetails base;
};
