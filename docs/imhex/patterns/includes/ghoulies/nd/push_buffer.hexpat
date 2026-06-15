#include <std/array>

#include "ghoulies/nd/types"


struct PushData {
	u32 ptr;
	if (ptr != 0) {
		u16 data[parent.vertex_counts[std::core::array_index()]] @ ptr;
	}
};

struct NdPushBufferDetails
{
  u32 num_draws;
  u32 idk1;
  u32 idk2;
  u32 idk3;
  u32 push_data_ptrs_ptr;
  std::ptr::NullablePtr<std::Array<u32, num_draws>, u32> primitives_ptr;
  u32 vertex_counts_ptr;

  u8 doNotCull;  // Bool
  u8 flag1;
  u8 flag2;
  u8 flag3;

  if (vertex_counts_ptr != 0) {
	  u32 vertex_counts[num_draws] @ vertex_counts_ptr;
  }

  if (push_data_ptrs_ptr != 0) {
	  PushData push_data[num_draws] @ push_data_ptrs_ptr;
  }
};

struct NdBGPushBufferDetails
{
  NdPushBufferDetails base;
  u32 idk1;
  u32 idk2;
  float floats[6];
};
