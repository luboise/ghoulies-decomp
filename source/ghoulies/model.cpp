#include <bit>
#include <cstddef>
#include <cstring>
#include <expected>
#include <iostream>

#include "model.hpp"

#include "bnl.hpp"
#include "nd.hpp"

namespace ghoulies
{
using std::unexpected;

std::expected<ModelAsset, std::string> ModelAsset::FromAsset(const Asset& asset)
{
  const Bytes& descriptor_bytes = asset.descriptor;

  ModelDescriptor descriptor {};

  ModelAsset new_model {};

  std::memcpy(&descriptor, &asset.descriptor[0], sizeof(descriptor));

  if (descriptor.num_footer_entries > 0) {
    // Footer out of bounds
    if (descriptor.footer_entries_ptr >= descriptor_bytes.size()) {
      return unexpected {
          std::format(
              "Footer at offset {:#0x} is out of bounds " "for descriptor " "of" " s" "iz" "e " "{:" "#0" "x}" ".",
              (descriptor.footer_entries_ptr),
              descriptor_bytes.size())};
    }

    auto end_ptr {descriptor.footer_entries_ptr
                  + (static_cast<uint64_t>(8) * descriptor.num_footer_entries)};

    // End of footer out of bounds
    if (end_ptr > descriptor_bytes.size()) {
      return unexpected("Model footer entries would read out of range.");
    }

    // Get the footer entries out of the descriptor
    std::vector<ModelFooterEntry> entries(descriptor.num_footer_entries);
    std::memcpy(entries.data(),
                &descriptor_bytes[descriptor.footer_entries_ptr],
                descriptor.num_footer_entries * sizeof(ModelFooterEntry));

    uint32_t found_subresources {0};

    for (const auto& entry : entries) {
      if ((found_subresources & (1U << entry.subresource_type)) != 0) {
        std::cout << std::
                format(
                    "Subresource of type {} has already been found in model "
                    "{}. Ignoring this and continuing to unpack the model.",
                    entry.subresource_type,
                    asset.description.metadata.name);
        continue;
      }

      switch (entry.subresource_type) {
        case kModel: {
          if ((static_cast<std::size_t>(entry.subresource_ptr) + 4U)
              > descriptor_bytes.size())
          {
            return unexpected(
                std::format(
                    "Model subresource pointer {:#0x} out " "of " "range " "of " "de" "sc" "ri" "pt" "or" " w" "it" "h " "size {}.",
                    entry.subresource_ptr,
                    descriptor_bytes.size()));
          }

          std::array<std::byte, 4> ptr_bytes {};

          std::memcpy(ptr_bytes.data(),
                      &descriptor_bytes[entry.subresource_ptr],
                      sizeof(ptr_bytes));

          std::uint32_t model_ptr {std::bit_cast<std::uint32_t>(ptr_bytes)};

          // TODO: Bounds check model_ptr

          auto bytes {std::span {descriptor_bytes}.subspan(model_ptr)};

          if (bytes.size() < sizeof(MeshHeader)) {
            return unexpected(
                "Model subresource isn't large enough to have a mesh header.");
          }

          MeshHeader mesh_header {};
          std::memcpy(&mesh_header, &bytes[0], sizeof(MeshHeader));

          if (mesh_header.num_root_nodes == 0) {
            return unexpected(
                "Unable to parse model subresource with 0 root nodes.");
          }

          if (mesh_header.root_nodes_ptr > bytes.size()) {
            return unexpected(
                std::format(
                    "Root node pointer {:#0x} out of " "range " "for model " "s" "u" "b" "r" "e" "s" "o" "u" "r" "c" "e" " " "descriptor of " "size {:#0x}.",
                    mesh_header.root_nodes_ptr,
                    bytes.size()));
          }

          std::vector<uint32_t> root_node_ptrs(mesh_header.num_root_nodes);

          std::memcpy(root_node_ptrs.data(),
                      &bytes[mesh_header.root_nodes_ptr],
                      mesh_header.num_root_nodes * sizeof(uint32_t));

          std::vector<std::shared_ptr<NdNode>> root_nodes;

          for (const auto ptr : root_node_ptrs) {
            if (ptr > bytes.size()) {
              return unexpected(
                  std::format(
                      "Root node pointer {:#0x} out of " "range " "for " "model" " " "s" "u" "b" "r" "e" "s" "o" "u" "r" "c" "e" " " "descriptor " "of size {:#0x}.",
                      ptr,
                      bytes.size()));
            }

            auto root_node_exp {ParseNdTree(bytes, asset.resource, ptr)};

            if (!root_node_exp.has_value()) {
              return unexpected(root_node_exp.error());
            }

            root_nodes.emplace_back(std::move(root_node_exp).value());
          }

          new_model.root_nodes = root_nodes;
          break;
        }
        case kTextures:
          break;
        case kUnknown0x2:
        case kUnknown0x3:
        case kMatrices:
        case kColliders:
        case kVertexBuffer:
          break;
      }

      /*
  if (found_subresources == 0) {
    std::cout << std::format("Subres Ptr: {:#0x}   Subres Type: {}\n",
                             entry.subresource_ptr,
                             static_cast<uint32_t>(entry.subresource_type));
  }
      */

      found_subresources |= (1U << entry.subresource_type);
    }

    /*
  struct ModelDescriptor
  {
  ModelFooterEntry* footer_entries;
  uint32_t num_footer_entries;
  uint32_t field2_0x8;
  uint32_t field3_0xc;
  ModelRuntimeContext* runtime_ctx;
  uint32_t field5_0x14;
  */
  }

  return new_model;
}

}  // namespace ghoulies
