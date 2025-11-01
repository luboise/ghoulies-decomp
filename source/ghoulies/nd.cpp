#include <cstring>
#include <expected>
#include <iostream>
#include <stack>

#include "nd.hpp"

#include "bnl.hpp"

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
std::expected<void, std::string> ParseNdNode(
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
  auto node {std::make_shared<NdNode>()};
  switch (header.nd_type) {
    case NdType::kVertexBuffer:
    case NdType::kGroup:
    case NdType::kSkeleton:
    case NdType::kRigidSkinIdx:
    case NdType::kMtxArray:
    case NdType::kShader2:
    case NdType::kShaderParam2:
    case NdType::kPushBuffer:
    case NdType::kVertexShader:
    case NdType::kBGPushBuffer:
    case NdType::kBlendShape:
    default:
  }

  if (ctx.root == nullptr) {
    ctx.root = node;
  }

  if (header.next_child_ptr != 0) {
    ctx.tree.push(node);

    if (auto result {
            ParseNdNode(bytes, resource_bytes, header.next_child_ptr, ctx)};
        !result.has_value())
    {
      return unexpected(result.error());
    }

    ctx.tree.pop();
  }

  if (header.next_sibling_ptr != 0) {
    if (auto result {
            ParseNdNode(bytes, resource_bytes, header.next_sibling_ptr, ctx)};
        !result.has_value())
    {
      return unexpected(result.error());
    }
  }

  return {};
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
