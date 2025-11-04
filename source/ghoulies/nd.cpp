#include <cassert>
#include <cstring>
#include <expected>
#include <iostream>
#include <limits>
#include <memory>
#include <stack>

#include "nd.hpp"

#include <SDL3/SDL_surface.h>

#include "bnl.hpp"
#include "d3d.hpp"

using d3d::D3DPrimitiveType;
using std::unexpected;

namespace ghoulies
{
/*
std::expected<ghoulies::ModelDescriptor, std::string>
ModelDescriptor::FromBytes(const Bytes& bytes)
{
const void* descriptor_base {bytes.data()};

auto* descriptor {reinterpret_cast<ModelDescriptor*>(bytes.data())};

RebasePointer(descriptor->footer_entries_ptr, descriptor_base);

return ModelDescriptor {descriptor, bytes};
}
*/

std::ostream& operator<<(std::ostream& os, ModelSubresourceType subres_type)
{
  switch (subres_type) {
    case kModel:
      os << "Model";
      break;
    case kUnknown0x2:
      os << "Unknown0x2";
      break;
    case kUnknown0x3:
      os << "Unknown0x3";
      break;
    case kMatrices:
      os << "Matrix";
      break;
    case kColliders:
      os << "Colliders";
      break;
    case kTextures:
      os << "Textures";
      break;
    case kVertexBuffer:
      os << "VertexBuffer";
      break;
  }

  return os;
}

struct NdParseContext
{
  std::shared_ptr<NdNode> root {nullptr};
  std::stack<std::shared_ptr<NdNode>> tree;

  std::vector<std::shared_ptr<NdShaderParam2>> materials;

  std::size_t current_material_index {std::numeric_limits<std::size_t>::max()};

  [[nodiscard]] bool HasCurrentMaterial() const
  {
    return current_material_index != std::numeric_limits<std::size_t>::max();
  }

  [[nodiscard]] NdShaderParam2& CurrentMaterial() const
  {
    return *materials.back();
  }
};

namespace
{
std::expected<std::shared_ptr<NdNode>, std::string> ParseNdNode(
    const std::span<const std::byte>& bytes,
    const std::span<const std::byte>& resource_bytes,
    uint32_t node_offset,
    NdParseContext& ctx)
{
  if (node_offset + sizeof(NdHeader) > bytes.size()) {
    return unexpected(
        std::format(
            "NdHeader at offset {} is out of range of " "model " "subresour" "c" "e" " " "des" "cri" "pto" "r " "of size {}.",
            node_offset,
            bytes.size()));
  }

  NdHeader header {};

  std::memcpy(&header, &bytes[node_offset], sizeof(NdHeader));

  // TODO: Validate NDHeader
  std::shared_ptr<NdNode> node {nullptr};
  switch (header.nd_type) {
    case NdType::kVertexBuffer: {
      std::array<uint32_t, 2> reads {};

      std::memcpy(
          reads.data(), &bytes[node_offset + sizeof(NdHeader)], sizeof(reads));

      const auto [vb_views_ptr, num_views] = reads;

      // TODO: Validate views and num_views

      std::vector<NdVertexBufferView> buffer_views(num_views);

      std::memcpy(buffer_views.data(),
                  &bytes[vb_views_ptr],
                  sizeof(NdVertexBufferView) * num_views);

      Bytes res_bytes(resource_bytes.begin(), resource_bytes.end());

      // TODO: Make this only grab the relevant bytes from the resource instead
      node = std::shared_ptr<NdVertexBuffer> {
          new NdVertexBuffer {header.nd_type,
                              nullptr,
                              nullptr,
                              nullptr,
                              buffer_views,
                              static_cast<Bytes>(res_bytes)}};
      break;
    }
    case NdType::kPushBuffer: {
      std::array<uint32_t, 7> values {};

      std::memcpy(values.data(),
                  &bytes[node_offset + sizeof(NdHeader)],
                  sizeof(values));

      const auto [num_draws,
                  idk1,
                  idk2,
                  idk3,
                  data_ptrs_ptr,
                  primitive_types_ptr,
                  index_counts_ptr] = values;

      bool skip_culling {};

      std::memcpy(&skip_culling,
                  &bytes[node_offset + sizeof(NdHeader) + sizeof(values)],
                  1);

      std::array<uint8_t, 3> pad {};  // TODO: Implement for serialisation

      std::vector<uint32_t> data_ptrs(num_draws);
      std::memcpy(data_ptrs.data(),
                  &bytes[data_ptrs_ptr],
                  sizeof(uint32_t) * num_draws);

      std::vector<D3DPrimitiveType> primitive_types(num_draws);
      std::memcpy(primitive_types.data(),
                  &bytes[primitive_types_ptr],
                  sizeof(uint32_t) * num_draws);

      std::vector<uint32_t> index_counts(num_draws);
      std::memcpy(index_counts.data(),
                  &bytes[index_counts_ptr],
                  sizeof(uint32_t) * num_draws);

      if (!ctx.HasCurrentMaterial()) {
        return unexpected("No material available when parsing push buffer.");
      }

      auto& current_material {ctx.CurrentMaterial()};
      uint32_t diffuse_texture_index {
          current_material.GetDiffuseTextureIndex().value_or(0)};

      std::vector<NdPushBufferDraw> draw_commands(num_draws);

      for (std::size_t i = 0; i < num_draws; i++) {
        const auto data_ptr {data_ptrs[i]};
        const auto index_count {index_counts[i]};
        const auto primitive_type {primitive_types[i]};

        std::vector<uint16_t> indices(index_count);

        if (index_count > 67108864) {
          return unexpected(
              std::format(
                  "Too many indices to allocate " "(attempted " "{} " "bytes." " " "Ma" "x " "al" "lo" "we" "d " "is {}, or " "64MB)",
                  index_count,
                  67108864));
        }

        std::memcpy(
            indices.data(), &bytes[data_ptr], index_count * sizeof(uint16_t));

        draw_commands[i] = {.primitive_type = primitive_type,
                            .indices = std::move(indices),
                            .material_index = diffuse_texture_index};
      }

      node = std::shared_ptr<NdPushBuffer> {new NdPushBuffer {header.nd_type,
                                                              nullptr,
                                                              nullptr,
                                                              nullptr,
                                                              num_draws,
                                                              idk1,
                                                              idk2,
                                                              idk3,
                                                              skip_culling,
                                                              draw_commands}};

      break;
    }
    case NdType::kShaderParam2: {
      std::array<uint32_t, 2> values {};

      std::memcpy(values.data(),
                  &bytes[node_offset + sizeof(NdHeader)],
                  sizeof(values));

      const auto [payload1_ptr, payload2_ptr] = values;

      if (payload1_ptr == 0) {
        return unexpected(
            "Unable to parse NdShaderParam2 with null main payload in model.");
      }

      NdShaderParam2 param2 {
          header.nd_type,
          nullptr,
          nullptr,
          nullptr,
      };

      RawNdShaderParam2Payload raw_main_payload {};
      std::memcpy(
          &raw_main_payload, &bytes[payload1_ptr], sizeof(raw_main_payload));
      auto main_payload {
          NdShaderParam2Payload::FromRaw(raw_main_payload, bytes)};
      if (!main_payload.has_value()) {
        return unexpected("Unable to parse NdShaderParam2 main payload.");
      }

      param2.main_payload = std::move(main_payload).value();

      if (payload2_ptr != 0) {
        RawNdShaderParam2Payload raw_sub_payload {};
        std::memcpy(
            &raw_sub_payload, &bytes[payload2_ptr], sizeof(raw_sub_payload));
        auto sub_payload {
            NdShaderParam2Payload::FromRaw(raw_sub_payload, bytes)};
        if (!sub_payload.has_value()) {
          return unexpected("Unable to parse NdShaderParam2 sub payload.");
        }

        param2.secondary_payload = std::move(sub_payload).value();
      }

      auto new_param2 {std::make_shared<NdShaderParam2>(std::move(param2))};

      node = new_param2;

      ctx.materials.push_back(new_param2);

      ctx.current_material_index = ctx.materials.size() - 1;

      break;
    }
    case NdType::kGroup:
    case NdType::kSkeleton:
    case NdType::kRigidSkinIdx:
    case NdType::kMtxArray:
    case NdType::kShader2:
    case NdType::kVertexShader:
    case NdType::kBGPushBuffer:
    case NdType::kBlendShape:
    default:
      node = std::make_shared<NdNode>(NdNode {.nd_type = header.nd_type});
  }

  if (node == nullptr) {
    return unexpected("Unhandled NDNode (node is nullptr).");
  }

  std::cout << node->nd_type << "\n";

  if (ctx.root == nullptr) {
    ctx.root = node;
  }

  if (header.next_child_ptr != 0) {
    ctx.tree.push(node);

    auto result {
        ParseNdNode(bytes, resource_bytes, header.next_child_ptr, ctx)};
    if (!result.has_value()) {
      return unexpected(result.error());
    }
    node->next_child = result.value();

    ctx.tree.pop();
  }

  if (header.next_sibling_ptr != 0) {
    auto result {
        ParseNdNode(bytes, resource_bytes, header.next_sibling_ptr, ctx)};
    if (!result.has_value()) {
      return unexpected(result.error());
    }
    node->next_sibling = result.value();
  }

  return node;
}

}  // namespace

namespace
{

}  // namespace

std::ostream& operator<<(std::ostream& os, NdType nd_type)
{
  switch (nd_type) {
    case NdType::kGroup:
      os << "Group";
      break;
    case NdType::kSkeleton:
      os << "Skeleton";
      break;
    case NdType::kRigidSkinIdx:
      os << "RigidSkinIdx";
      break;
    case NdType::kMtxArray:
      os << "MtxArray";
      break;
    case NdType::kShader2:
      os << "Shader2";
      break;
    case NdType::kShaderParam2:
      os << "ShaderParam2";
      break;
    case NdType::kVertexBuffer:
      os << "VertexBuffer";
      break;
    case NdType::kPushBuffer:
      os << "PushBuffer";
      break;
    case NdType::kVertexShader:
      os << "VertexShader";
      break;
    case NdType::kBGPushBuffer:
      os << "BGPushBuffer";
      break;
    case NdType::kBlendShape:
      os << "BlendShape";
      break;
    default:
      os << "Unknown Nd Type";
      break;
  }

  return os;
}

std::optional<NdVertexBufferView*> NdVertexBuffer::GetBufferView(
    NdVertexBufferViewType view_type)
{
  if (auto found {
          std::ranges::find_if(this->resource_views,
                               [view_type](const NdVertexBufferView& view)
                               { return view.type == view_type; })

      };
      found != this->resource_views.end())
  {
    return found.base();
  }

  return nullptr;
}

std::optional<NdShaderParam2Payload> NdShaderParam2Payload::FromRaw(
    const RawNdShaderParam2Payload& raw, std::span<const std::byte> bytes)
{
  // Pixel shader constants
  std::vector<PixelShaderConstant> pixel_shader_constants {};
  if (raw.num_pixel_shader_constants > 0) {
    pixel_shader_constants.resize(raw.num_pixel_shader_constants);
    std::memcpy(pixel_shader_constants.data(),
                &bytes[raw.pixel_shader_constants_ptr],
                sizeof(PixelShaderConstant) * raw.num_pixel_shader_constants);
  }

  // Vertex shader constants
  std::vector<VertexShaderConstant> vertex_shader_constants {};

  if (raw.num_pixel_shader_constants > 0) {
    vertex_shader_constants.resize(raw.num_vertex_shader_constants);
    std::memcpy(vertex_shader_constants.data(),
                &bytes[raw.vertex_shader_constants_ptr],
                sizeof(VertexShaderConstant) * raw.num_vertex_shader_constants);
  }

  // Texture assignments
  std::vector<TextureAssignment> texture_assignments {};

  if (raw.num_texture_assignments > 0) {
    texture_assignments.resize(raw.num_texture_assignments);

    std::memcpy(texture_assignments.data(),
                &bytes[raw.texture_assignments_ptr],
                sizeof(TextureAssignment) * raw.num_texture_assignments);
  }

  // Shader assignments
  std::vector<RawShaderParamAssignment> raw_assignments(
      raw.num_shader_assignments);

  std::memcpy(raw_assignments.data(),
              &bytes[raw.shader_assignments_start],
              sizeof(RawShaderParamAssignment) * raw.num_shader_assignments);

  std::vector<ShaderParamAssignment> shader_assignments(raw_assignments.size());

  for (std::size_t i {0}; i < raw_assignments.size(); i++) {
    const auto& raw_assignment {raw_assignments[i]};

    const char* str_ptr {
        reinterpret_cast<const char*>(&bytes[raw_assignment.name_ptr])};

    shader_assignments[i] = {
        .param_name = std::string {str_ptr},
        .some_val1 = raw_assignment.some_val1,
        .natural_texture_slot = raw_assignment.texture_slot,
        .base_colour = raw_assignment.base_colour};
  }

  // Returning
  std::optional<TextureAssignment> texture_assignment_0 {};
  std::optional<TextureAssignment> texture_assignment_1 {};

  if (texture_assignments.size() >= 1) {
    texture_assignment_0 = texture_assignments[0];
  }

  if (texture_assignments.size() >= 2) {
    texture_assignment_1 = texture_assignments[1];
  }

  return NdShaderParam2Payload {
      .vertex_shader_constants = vertex_shader_constants,

      .pixel_shader_constants = pixel_shader_constants,

      .texture_assignment_0 = texture_assignment_0,
      .texture_assignment_1 = texture_assignment_1,

      .shader_assignments = shader_assignments,
  };
}

std::optional<uint32_t> NdShaderParam2::GetDiffuseTextureIndex() const
{
  const auto lambda =
      [](const NdShaderParam2Payload& payload) -> std::optional<uint32_t>
  {
    // Check if any assignments map to colour0
    const ShaderParamAssignment* assignment {payload.GetAssignment("colour0")};

    if (assignment != nullptr) {
      std::cout << "Found colour0.\n";

      assert(assignment->natural_texture_slot != 0);  // Should be 1 or 2

      // Get the texture slot of the assignment which colour0 uses
      auto slot {assignment->natural_texture_slot};

      // Get the assignment for that slot and return it
      const auto* texture_assignment {
          payload.GetTextureAssignmentForSlot(slot)};
      if (texture_assignment != nullptr) {
        return texture_assignment->texture_bank_index;
      }
    };

    return std::nullopt;
  };

  if (std::optional<uint32_t> index {lambda(this->main_payload)};
      index.has_value())
  {
    return index;
  }

  if (this->secondary_payload.has_value()) {
    if (std::optional<uint32_t> index {lambda(this->secondary_payload.value())};
        index.has_value())
    {
      return index;
    }
  }

  return std::nullopt;
}

const ShaderParamAssignment* NdShaderParam2Payload::GetAssignment(
    std::string_view key) const
{
  for (const auto& assignment : this->shader_assignments) {
    if (assignment.param_name == key) {
      return &assignment;
    }
  }

  return nullptr;
}

const TextureAssignment* NdShaderParam2Payload::GetTextureAssignmentForSlot(
    std::uint32_t slot) const
{
  assert(slot == 0 || slot == 1);

  if (slot == 0) {
    return this->texture_assignment_0.has_value()
        ? &(this->texture_assignment_0.value())
        : nullptr;
  }

  if (slot == 1) {
    return this->texture_assignment_1.has_value()
        ? &(this->texture_assignment_1.value())
        : nullptr;
  }

  return nullptr;
}

}  // namespace ghoulies

std::expected<std::shared_ptr<ghoulies::NdNode>, std::string>
ghoulies::ParseNdTree(std::span<const std::byte> bytes,
                      std::span<const std::byte> resource_bytes,
                      uint32_t node_offset)
{
  NdParseContext ctx {};

  if (auto result {ParseNdNode(bytes, resource_bytes, node_offset, ctx)};
      !result.has_value())
  {
    return unexpected(result.error());
  }

  if (ctx.root == nullptr) {
    return unexpected("Unable to retrieve any nodes from root Nd node.");
  }

  return ctx.root;
}
