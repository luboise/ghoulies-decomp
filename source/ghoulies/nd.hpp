#pragma once

#include <cstdint>
#include <expected>
#include <ostream>
#include <span>
#include <sstream>
#include <string>

#include "bnl.hpp"

namespace ghoulies
{

template<typename T1, typename T2>
void RebasePointer(T1*& ptr, T2* base)
{
  ptr = static_cast<T1*>(static_cast<uint64_t>(ptr)
                         + reinterpret_cast<uint64_t>(base));
}

struct MeshHeader
{
  uint32_t var_size;
  uint32_t field1_0x4;
  uint32_t root_nodes_ptr;
  uint32_t num_root_nodes;
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
  kMatrices = 5,
  kColliders = 6,
  kTextures = 7,
  kVertexBuffer = 18,
};

std::ostream& operator<<(std::ostream&, ModelSubresourceType);

struct ModelFooterEntry
{
  ModelSubresourceType subresource_type;
  uint32_t subresource_ptr;
};

static_assert(sizeof(ModelFooterEntry) == 8);

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
  uint32_t footer_entries_ptr;
  uint32_t num_footer_entries;
  uint32_t field2_0x8;
  uint32_t field3_0xc;

  /// Written at runtime, doesn't exist serialised
  ModelRuntimeContext* runtime_ctx;
  uint32_t field5_0x14;

  /*
  static std::expected<ModelDescriptor, std::string> FromBytes(
      std::span<uint8_t> bytes);
          */
};

enum class NdType : uint16_t
{
  kGroup = 0x01,
  kSkeleton = 0x02,

  kRigidSkinIdx = 0x0b,
  kMtxArray = 0x0c,

  kShader2 = 0x11,
  kShaderParam2 = 0x12,
  kVertexBuffer = 0x13,
  kPushBuffer = 0x14,
  kVertexShader = 0x15,
  kBGPushBuffer = 0x16,
  kBlendShape = 0x17,
};

std::ostream& operator<<(std::ostream&, NdType);

struct NdHeader
{
  uint32_t subres_name_ptr;
  NdType nd_type;
  uint16_t unknown_u16;
  uint32_t unknown_str;
  uint32_t unknown_str2;
  uint32_t unused_callback_ctx;  // Used by original game
  uint32_t next_child_ptr;
  uint32_t next_sibling_ptr;
  uint32_t prev_node_ptr;  // Previous node or parent if no previous siblings
};

struct NdNode
{
  NdType nd_type;

  char* subres_name;
  char* some_ptr;

  std::shared_ptr<NdNode> next_child {nullptr};
  std::shared_ptr<NdNode> next_sibling {nullptr};
  std::shared_ptr<NdNode> prev_node {nullptr};
};

enum class VertexBufferViewType : uint8_t
{
  kSkin = 0x0,
  kSkinWeight = 0x8,
  kVertex = 0x9,
  kUnknown10 = 0xa,
  kUnknown11 = 0xb,
  kUV = 0xd,
  kUnknown14 = 0xe,
  kUnknown15 = 0xf,
  kUnknown16 = 0x10,
  kKnknownFf = 0xff,
};

struct VertexBufferResourceView
{
  uint8_t stride;
  VertexBufferViewType res_type;
  uint16_t unknown_u16;

  uint32_t unknown_u32_1;

  // 0x8
  uint32_t unknown_u32_2;
  uint32_t unknown_u32_3;

  // 0x16
  uint32_t view_start;
  uint32_t view_size;
};

struct NdVertexBuffer
{
  uint32_t resource_views_ptr;
  uint32_t num_resource_views;
};

std::expected<std::shared_ptr<NdNode>, std::string> ParseNdTree(
    std::span<const std::byte> bytes,
    std::span<const std::byte> resource_bytes,
    uint32_t node_offset);

}  // namespace ghoulies

template<>
struct std::formatter<ghoulies::ModelSubresourceType>
    : std::formatter<std::string>
{
  auto format(ghoulies::ModelSubresourceType p, format_context& ctx) const
  {
    std::stringstream ss;
    ss << p;

    return formatter<string>::format(ss.str(), ctx);
  }
};
