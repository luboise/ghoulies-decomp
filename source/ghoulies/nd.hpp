#pragma once

#include <cstdint>
#include <expected>
#include <span>
#include <string>

namespace ghoulies
{

class Nd
{
};

struct MeshHeader
{
  uint32_t var_size;
  uint32_t field1_0x4;
  struct NdNode** mesh_nodes;
  uint32_t num_nodes;
  struct KeyValueMap* attrib_map;
  void* some_ptr2;
  float field6_0x18;
  float field7_0x1c;
  float field8_0x20;
  float field9_0x24;
  uint32_t* next_ptr_maybe;
};

enum ModelSubresourceType : uint32_t
{
  kModel = 0,
  kUnknown0x2 = 2,
  kUnknown0x3 = 3,
  kMatrix = 5,
  kColliders = 6,
  kTexture = 7,
  kVertexBuffer = 18
};

class ModelBaseSubresource
{
};

struct ModelFooterEntry
{
  ModelSubresourceType subresource_type;
  ModelBaseSubresource* subresource;
};

struct ModelRuntimeContext
{
  uint32_t vertex_buffer_index;
  uint32_t colliders_index;
  uint32_t type0xc_index;
  uint32_t type0xd_index;
  uint32_t type0x11_index;
  uint32_t type0xe_index;
  uint32_t type0x10_index;
  uint32_t type0x15_index;
  uint32_t type10_index;
  MeshHeader* mesh_header;
  uint32_t textures_index;
  uint32_t type0x18_index;
};

struct ModelDescriptor
{
  ModelFooterEntry* footer_entries;
  uint32_t num_footer_entries;
  uint32_t field2_0x8;
  uint32_t field3_0xc;
  ModelRuntimeContext* runtime_ctx;
  uint32_t field5_0x14;

  static std::expected<ModelDescriptor, std::string> FromBytes(
      std::span<uint8_t> bytes);
};

struct NdNode
{
  char* subres_name;
  uint16_t callback_index;
  uint16_t field2_0x6;
  char* field3_0x8;
  char* some_ptr;
  struct BigBlockCallbackCtx* callback_ctx;
  NdNode* next_child;
  NdNode* next_sibling;
  NdNode* prev;
};

class MeshSubresource : public ModelBaseSubresource
{
  MeshHeader* header_;
  void* resource_offset_;
};

}  // namespace ghoulies
