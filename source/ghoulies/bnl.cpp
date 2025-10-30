#include <algorithm>
#include <cstring>
#include <expected>
#include <iostream>
#include <utility>

#include "bnl.hpp"

namespace ghoulies
{

std::expected<BNLFile, std::string> BNLFile::FromBytes(
    std::span<std::byte> bytes_span)
{
  if (bytes_span.size() < sizeof(BNLHeader)) {
    return std::unexpected("Not enough bytes to parse BNLHeader.");
  }

  Bytes bytes(sizeof(BNLHeader));

  BNLHeader header {};

  std::memcpy(&header, bytes_span.data(), sizeof(header));

  std::cout << "File count: " << header.file_count << "\n";

  std::size_t max_offset = std::max({header.asset_desc_loc.MaxOffset(),
                                     header.buffer_views_loc.MaxOffset(),
                                     header.descriptor_loc.MaxOffset(),
                                     header.buffer_loc.MaxOffset()});

  auto subspan {bytes_span.subspan(sizeof(BNLHeader))};
  Bytes compressed_bytes {subspan.begin(), subspan.end()};

  Bytes decompressed_bytes {
      utils::ZLibDecompress(
          compressed_bytes,
          max_offset + 500)  // 500 is just extra chunk to make sure a second
                             // allocation isn't made
          .value_or({})};  // Default to empty if failed

  if (decompressed_bytes.empty()) {
    std::cerr << "Failed to decompress BNL bytes.\n";
    return {};
  }

  if (decompressed_bytes.size() < max_offset) {
    return std::unexpected(
        std::format(
            "BNL file reads up to size {}, but the " "decompressed " "file " "i" "s" " " "o" "n" "l" "y" " " "{} bytes " "long.",
            max_offset,
            decompressed_bytes.size()));
  }

  bytes.resize(sizeof(BNLHeader) + decompressed_bytes.size());

  // Consolidate into one vector called bytes
  std::memcpy(&bytes[sizeof(BNLHeader)],
              std::move(decompressed_bytes).data(),
              decompressed_bytes.size());

  std::vector<AssetDescription> asset_descriptions(header.file_count);

  std::memcpy(asset_descriptions.data(),
              &bytes[header.asset_desc_loc.offset],
              header.file_count * sizeof(AssetDescription));

  std::ranges::for_each(asset_descriptions,
                        [](const auto& desc)
                        { std::cout << desc.metadata.name.data() << "\n"; });

  BNLFile bnl {};

  return bnl;
}

BNLFile::BNLFile(std::unordered_map<std::string, Asset> assets)
    : assets_(std::move(assets))
{
}

}  // namespace ghoulies
