#pragma once

enum ModelSubresourceType : u32
{
  ModelSubres = 0x0,
  Unknown0x2Subres = 0x2,
  Unknown0x3Subres = 0x3,
  RigidSkinSubres = 0x4,
  MatrixSubres = 0x5,
  CollidersSubres = 0x6,
  TexturesSubres = 0x7,
  Unknown0x9Subres = 0x9,
  VertexBufferSubres = 0x12
};

struct Mesh
{
  u32 mesh_data;
};

struct ModelSubresource
{
  s128 start = $;

  u32 ptr1;
  u32 idk2;
  u32 nd_nodes_ptr;
  u32 num_nd_nodes;
  // ModelKeyValueSet* keyValues : u32 [[pointer_base("section1innersptr")]];
  // u32* somePtr : u32 [[pointer_base("section1innersptr")]];
  // float float1;
  // float float2;
  // float float3;
  // float float4;
  // u32* nextPtr : u32 [[pointer_base("section1innersptr")]];
  // u32 model_start;

  if (ptr1 != 0) {
    u32 unknown_u32_1 @start + ptr1;
  }

  if (nd_nodes_ptr != 0 && num_nd_nodes > 0) {
    NdHeader* nodes[] : u32 @start + nd_nodes_ptr;
  }
};

struct ModelFooterEntry
{
  ModelSubresourceType subres_type;
  u32 offset;

  if (offset != 0) {
    // Model subresource
    if (subres_type == ModelSubresourceType::ModelSubres) {
      u32 model_start_ptr @parent.start + offset;
      if (model_start_ptr != 0) {
        ModelSubresource subres @parent.start + model_start_ptr;
      }
    }
    // Other subresources here
  }
};

struct ModelDescriptor
{
  s128 start = $;

  u32 footer_ptr;
  u32 num_footer_entries;
  u32 flags;
  u32 unknown_u32_1;
  u32 model_runtime_context;
  u32 unknown_u32_2;

  if (footer_ptr != 0 && num_footer_entries > 0) {
    ModelFooterEntry footer_entries[num_footer_entries] @start + footer_ptr;
  }
};
