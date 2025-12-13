#pragma once

#include "ghoulies/loctext"
#include "ghoulies/types"

struct DemandFile
{
  s128 start = $;
  AssetChunkInfo chunk_info;

  if (chunk_info.descriptor_size > 0) {
    LoctextDescriptor @start + chunk_info.descriptor_ptr;
  }
};
