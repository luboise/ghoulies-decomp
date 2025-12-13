#pragma once

struct vec3 {
    float x;
    float y;
    float z;
};

struct quat {
    float x;
    float y;
    float z;
    float w;
};

enum AssetType : u32
{
  LocText = 0x10,
};

struct AssetChunkInfo
{
  AssetType asset_type;
  u32 idk1;
  u32 idk2;
  u32 numChunks;
  u32 descriptor_ptr;
  u32 descriptor_size;
  u32 resource_view_ptr;
  u32 resource_size;
};
