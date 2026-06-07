#include <std/array>

#include "ghoulies/nd/types"

struct NdPushBufferDetails
{
  u32 num_draws;
  u32 idk1;
  u32 idk2;
  u32 idk3;
  // Pointer lists
  u32 push_data_ptrs;
  std::ptr::NullablePtr<std::Array<u32, num_draws>, u32> primitives_ptr;
  std::ptr::NullablePtr<std::Array<u32, num_draws>, u32> vertex_counts;
  u8 doNotCull;  // Bool
  u8 pad[3];

  if (push_data_ptrs != 0) {
    NdPtr<std::Array<u16, 2>> push_data_ptrs[num_draws] @ push_data_ptrs;
  }
};

struct NdBGPushBufferDetails
{
  NdPushBufferDetails base;
  u32 idk1;
  u32 idk2;
  float floats[6];
};
