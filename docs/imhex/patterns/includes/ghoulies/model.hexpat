#pragma once
#include "ghoulies/nd/all"
#include "ghoulies/collision"

enum ModelSubresourceType : u32
{
  ModelSubres = 0x0,
  Unknown0x2Subres = 0x2,
  Unknown0x3Subres = 0x3,
  RigidSkinSubres = 0x4,
  MatrixSubres = 0x5,
  CollidersSubres = 0x6,
  TexturesSubres = 0x7,
  BoneIndexSubres = 0x9,
  VertexBufferSubres = 0x12
};

struct Subres0x4Value
{
  s128 start = $;

  CollisionObjectType setType;
  u8 size;
  u16 blendTargetIndex;

  CollisionMask collisionMask;
  u16 short1;
  u16 short2;

  u32 padZero;
  float f1;
  vec3 v;
  u32 group;

  s128 end = $;

  padding[std::math::max(0, 36 - (end - start))];
};

struct Subres0x4
{
  u32 numValues;
  u32 idk1;
  Subres0x4Value values[numValues];
};



struct Mesh
{
  u32 mesh_data;
};

struct SizedCollection<T>
{
  s128 model_root = parent.model_root;

  u32 numValues;
  u32 dataStart;
  T values[numValues];
};

struct SubresourcePtr
{
  u32* ptr : u32 [[pointer_base("section1innersptr")]];
};

struct KeyValue
{
  s128 model_root = parent.model_root;

  NdPtr<std::string::NullString> key;
  u32 value_ptr;
  u32 value_size;

  if (value_size > 0 && value_ptr != 0) {
    u8 data[value_size] @model_root + value_ptr;
  }
};

using ModelKeyValueSet = SizedCollection<KeyValue>;

struct ModelSubresource
{
  s128 model_root = $;

  u32 ptr1;
  u32 idk2;
  u32 nd_nodes_ptr;
  u32 num_nd_nodes;
  NdPtr<ModelKeyValueSet> keyValues;
  // u32* somePtr : u32 [[pointer_base("section1innersptr")]];
  // float float1;
  // float float2;
  // float float3;
  // float float4;
  // u32* nextPtr : u32 [[pointer_base("section1innersptr")]];
  // u32 model_model_root;

  if (ptr1 != 0) {
    u32 unknown_u32_1 @model_root + ptr1;
  }

  if (nd_nodes_ptr != 0 && num_nd_nodes > 0) {
    NdHeaderPtr nd_header_ptrs[num_nd_nodes] @model_root + nd_nodes_ptr;
  }
};

struct TexturesSubresource
{
  s128 start = parent.start;
  s128 model_root = start;

  u32 num_textures;
  u32 textures_ptr;

  if (textures_ptr != 0 && num_textures > 0) {
    NdPtr<TEXTURE_HEADER> texture_headers[num_textures] @model_root
        + textures_ptr;
  }
};


struct CollidersSubres
{
  u32 numObjects;
  u16 minFlagMaybe;
  u16 maxFlagMaybe;
  u32 numVertices;
  u32 verticesPtr;
  CollisionObject objects[numObjects];

  if (numVertices > 0 && verticesPtr != 0) {
  	vec3 vertices[numVertices] @ verticesPtr;
  }
};

struct BoneIndexSubres
{
  u8 indices[32];
};

struct ModelFooterEntry
{
  s128 start = parent.start;

  ModelSubresourceType subres_type;
  u32 offset;

  if (offset != 0) {
    // Model subresource
    if (subres_type == ModelSubresourceType::ModelSubres) {
      u32 model_start_ptr @parent.start + offset;
      if (model_start_ptr != 0) {
        ModelSubresource subres @parent.start + model_start_ptr;
      }
    } else if (subres_type == ModelSubresourceType::TexturesSubres) {
      TexturesSubresource subres @parent.start + offset;
    } else if (subres_type == ModelSubresourceType::BoneIndexSubres) {
      BoneIndexSubres subres @parent.start + offset;
    } else if (subres_type == ModelSubresourceType::CollidersSubres) {
      CollidersSubres subres @parent.start + offset;
    }
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
