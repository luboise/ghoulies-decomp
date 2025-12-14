#pragma once

enum VertexBufferViewType : u8
{
  skin = 0x0,
  skinWeight = 0x8,
  vertex = 0x9,
  unknown_10 = 0xa,
  unknown_11 = 0xb,
  UV = 0xd,
  unknown_14 = 0xe,
  unknown_15 = 0xf,
  unknown_16 = 0x10,
};

struct VertexBufferResView
{
  u8 stride;
  VertexBufferViewType view_type;
  u16 idk1;
  u32 unknown2;
  u32 padding1;
  u32 padding2;

  u32 offset;
  u32 size;
};

struct NdVertexBufferDetails
{
  s128 model_root = parent.model_root;

  u32 views_ptr;
  u32 num_views;

  if (views_ptr != 0 && num_views > 0) {
    VertexBufferResView views[num_views] @model_root + views_ptr;
  }
};
