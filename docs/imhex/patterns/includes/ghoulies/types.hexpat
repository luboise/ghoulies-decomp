#pragma once

struct vec3 {
    float x;
    float y;
    float z;
};

struct vec4
{
  float x;
  float y;
  float z;
  float w;
};

struct mat4
{
  vec4 r1;
  vec4 r2;
  vec4 r3;
  vec4 r4;
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
