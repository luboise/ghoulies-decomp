#pragma once

#include <cstdint>
#include <expected>
#include <ostream>
#include <span>
#include <sstream>
#include <string>

#include "bnl.hpp"
#include "d3d.hpp"

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
  Model = 0,
  Unknown0x2 = 2,
  Unknown0x3 = 3,
  Colliders0x4 = 4,
  Matrices = 5,
  Colliders = 6,
  Textures = 7,
  VertexBuffer = 18,
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
  Group = 0x01,
  Skeleton = 0x02,

  RigidSkinIdx = 0x0b,
  MtxArray = 0x0c,

  Shader2 = 0x11,
  ShaderParam2 = 0x12,
  VertexBuffer = 0x13,
  PushBuffer = 0x14,
  VertexShader = 0x15,
  BGPushBuffer = 0x16,
  BlendShape = 0x17,
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

  std::shared_ptr<NdNode> next_child {nullptr};
  std::shared_ptr<NdNode> next_sibling {nullptr};
  std::shared_ptr<NdNode> prev_node {nullptr};

  /// Find the first occurence within this node and its children by a function

  NdNode* FindBy(const auto f)
  {
    if (f(*this)) {
      return this;
    }

    if (this->next_child != nullptr) {
      if (this->next_child->FindBy(f) != nullptr) {
        return this->next_child.get();
      };
    }

    if (this->next_sibling != nullptr) {
      if (this->next_sibling->FindBy(f) != nullptr) {
        return this->next_sibling.get();
      };
    }

    return nullptr;
  }
};

enum class NdVertexBufferViewType : uint8_t
{
  kSkin = 0x0,
  kSkinWeight = 0x8,
  Vertex = 0x9,
  kUnknown10 = 0xa,
  kUnknown11 = 0xb,
  UV = 0xd,
  kUnknown14 = 0xe,
  kUnknown15 = 0xf,
  kUnknown16 = 0x10,
};

struct NdVertexBufferView
{
  uint8_t stride;
  NdVertexBufferViewType type;
  uint16_t idk1;

  uint32_t unknown_u32_1;
  uint32_t unknown_u32_2;
  uint32_t unknown_u32_3;

  uint32_t start_ptr;
  uint32_t size;
};

static_assert(sizeof(NdVertexBufferView) == 24);

struct Colour
{
  uint8_t r;
  uint8_t g;
  uint8_t b;
  uint8_t a;
};

static_assert(sizeof(Colour) == 4);

struct TextureAssignment
{
  uint32_t texture_bank_index;
  uint8_t flag1;
  uint8_t flag2;
  uint8_t flag3;
  bool skip_diffuse_texture;
  uint32_t unknown3;
  uint32_t unknown4;
  uint32_t unknown5;
  uint32_t unknown6;
  uint32_t unknown7;
};

static_assert(sizeof(TextureAssignment) == 0x1c);

struct RawShaderParamAssignment
{
  uint32_t name_ptr;
  uint32_t some_val1;
  uint32_t texture_slot;
  Colour base_colour;
};

static_assert(sizeof(RawShaderParamAssignment) == 16);

struct RawNdShaderParam2Payload
{
  uint32_t pixel_shader_constants_ptr;
  uint32_t vertex_shader_constants_ptr;
  uint32_t texture_assignments_ptr;

  uint32_t num_texture_assignments;
  uint32_t num_vertex_shader_constants;
  uint32_t num_pixel_shader_constants;

  // 0x18
  uint8_t alpha_reference;
  uint8_t flag1;
  uint8_t flag2;
  uint8_t some_count;

  uint32_t unknown_uint32;

  // 0x20
  uint32_t maybe_child_ptr;

  uint32_t shader_assignments_start;
  uint32_t num_shader_assignments;
};

struct ShaderParamAssignment
{
  std::string param_name;
  uint32_t some_val1;

  /// The index of the texture assignment used by this param. This can be
  /// followed to retrieve the index of the texture in the texture bank
  uint32_t texture_assignment_index;
  Colour base_colour;
};

using VertexShaderConstant = std::array<float, 4>;
using PixelShaderConstant = Colour;

struct NdShaderParam2Payload
{
  std::vector<VertexShaderConstant> vertex_shader_constants;
  std::vector<Colour> pixel_shader_constants;

  std::vector<TextureAssignment> texture_assignments;

  std::vector<ShaderParamAssignment> shader_assignments;

  static std::optional<NdShaderParam2Payload> FromRaw(
      const RawNdShaderParam2Payload& raw, std::span<const std::byte> bytes);

  /// Searches for a ShaderParamAssignment by name, returning a pointer to one
  /// if found and nullptr otherwise
  [[nodiscard]] const ShaderParamAssignment* GetAssignment(
      std::string_view key) const;

  [[nodiscard]] const TextureAssignment* GetTextureAssignment(
      std::uint32_t slot) const;

  /*
  uint8_t alpha_reference;
  uint8_t flag1;
  uint8_t flag2;
  uint8_t some_count;

  uint32_t unknown_uint32;


  // 0x20
  uint32_t maybe_child_ptr;
  */
};

static_assert(sizeof(RawNdShaderParam2Payload) == 0x2c);

struct NdVertexBuffer : public NdNode
{
  std::vector<NdVertexBufferView> resource_views;
  Bytes vertex_buffer_bytes;

  std::optional<const NdVertexBufferView*> GetBufferView(
      NdVertexBufferViewType view_type) const;
};

struct NdShaderParam2 : public NdNode
{
  NdShaderParam2Payload main_payload;
  std::optional<NdShaderParam2Payload> secondary_payload;

  [[nodiscard]] std::optional<uint32_t> GetDiffuseTextureIndex() const;
};

std::expected<std::shared_ptr<NdNode>, std::string> ParseNdTree(
    std::span<const std::byte> bytes,
    std::span<const std::byte> resource_bytes,
    uint32_t node_offset);

struct NdPushBufferDraw
{
  d3d::D3DPrimitiveType primitive_type;
  std::vector<uint16_t> indices;
  uint32_t material_index;
};

struct NdPushBuffer : public NdNode
{
  uint32_t num_draws;
  uint32_t idk1;
  uint32_t idk2;
  uint32_t idk3;
  bool skip_culling;

  // DO NOT SERIALISE

  std::vector<NdPushBufferDraw> draws;
};

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
