#pragma once

#include "ghoulies/loctext"
#include "ghoulies/types"

struct ResourceChunk {
	u32 ptr;
	u32 size;
	u8 res[size] @ ptr;
};

struct DemandFile
{
  s128 start = $;
  AssetChunkInfo chunkInfo;

  if (chunkInfo.descriptor_size > 0) {
  	// u8 resource[chunkInfo.resource_size] @ start + resource_view_ptr;

	u32 numResourceChunks @ chunkInfo.resource_view_ptr + 4;

	if (numResourceChunks) {
		ResourceChunk chunks[numResourceChunks] @ chunkInfo.resource_view_ptr + 8;
	}
  }
};
