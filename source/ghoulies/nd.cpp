#include <cstring>
#include <expected>
#include <iostream>
#include <memory>
#include <stack>

#include "nd.hpp"

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
                            .indices = std::move(indices)};
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
    case NdType::kGroup:
    case NdType::kSkeleton:
    case NdType::kRigidSkinIdx:
    case NdType::kMtxArray:
    case NdType::kShader2:
    case NdType::kShaderParam2:
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
