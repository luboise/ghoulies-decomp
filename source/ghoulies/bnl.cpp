#include <algorithm>
#include <bit>
#include <cstring>
#include <expected>
#include <iostream>
#include <numeric>
#include <ranges>
#include <utility>

#include "bnl.hpp"

namespace ghoulies
{
using std::accumulate;

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
      utils::file::ZLibDecompress(
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

  std::vector<Asset> assets =
      asset_descriptions
      | std::views::transform(
          [&bytes, &header](const AssetDescription& description)
          {
            Bytes descriptor(description.descriptor_size);

            // TODO: Add bounds check here for descriptor
            std::memcpy(
                descriptor.data(),
                &bytes[static_cast<std::size_t>(header.descriptor_loc.offset)
                       + description.descriptor_ptr],
                description.descriptor_size);

            Bytes resource;

            // If the asset has a resource
            if (description.resource_size > 0) {
              auto list_opt {LocatorList::FromSpan(std::span {bytes}.subspan(
                  static_cast<std::size_t>(header.buffer_views_loc.offset)
                  + description.locator_list_ptr))};

              if (!list_opt.has_value()) {
                resource.resize(0);
              } else {
                resource = list_opt.value()
                               .GetResource(std::span {bytes}.subspan(
                                   header.buffer_loc.offset))
                               .value_or({});
              }

              if (resource.empty()) {
                std::cerr
                    << std::format(
                           "Failed to parse locator list for asset {}. "
                           "Continuing with no resource for this asset.\n", description.metadata.name.data());
              }
            }

            return Asset {.description = description,
                          .descriptor = descriptor,
                          .resource = resource};
          })
      | std::views::filter([](const auto& val)
                           { return !val.descriptor.empty(); })
      | std::ranges::to<std::vector>();

  BNLFile bnl {assets};

  return bnl;
}

BNLFile::BNLFile(std::span<Asset> assets)
    : assets_(assets.begin(), assets.end())
{
}

std::optional<LocatorList> LocatorList::FromSpan(std::span<std::byte> span)
{
  // 8 is minimum size of LocatorList
  if (span.size() < 8) {
    std::cerr
        << std::format(
               "Unable to create LocatorList from span of less than 8 bytes "
               "(received " "{}).\n",
               span.size());
    return {};
  }

  std::array<std::byte, 4> size_bytes {};

  std::memcpy(size_bytes.data(), &span[0], sizeof(size_bytes));
  auto list_size {std::bit_cast<uint32_t>(size_bytes)};

  std::memcpy(size_bytes.data(), &span[4], sizeof(size_bytes));
  auto declared_count {std::bit_cast<uint32_t>(size_bytes)};

  std::size_t max_count = (span.size() - 8) / sizeof(Locator);

  if (declared_count > max_count) {
    std::cerr
        << std::format(
               "Locator list declares {} locators, but the BNL file actually "
               "has {}. " "\nUnable to create LocatorList.\n",
               declared_count,
               max_count);
    return {};
  }

  if (span.size() < list_size) {
    std::cerr << std::format(
        "Locator List of size {} can't be created from span of size {}.\n",
        list_size,
        span.size());

    return {};
  }

  std::vector<Locator> views(declared_count);

  std::memcpy(views.data(), &span[8], views.size() * sizeof(views[0]));

  return LocatorList {
      .size = list_size, .num_views = declared_count, .views = views};
}

std::optional<Bytes> LocatorList::GetResource(std::span<std::byte> span)
{
  Bytes bytes(this->Size());

  if (bytes.empty()) {
    return bytes;
  }

  std::size_t cursor {0};

  for (const auto& view : this->views) {
    // Locator reads out of bounds
    if (view.MaxOffset() > span.size()) {
      std::cerr
          << std::
                 format(
                     "Resource locator reads to offset {}, but the resource "
                     "span " "has size {}.\n",
                     view.MaxOffset(),
                     span.size());

      return {};
    }

    std::memcpy(&bytes[cursor], &span[view.offset], view.size);

    cursor += view.size;
  }

  if (cursor != bytes.size()) {
    std::cerr << std::format(
        "Locator list cursor ended at offset {}, but {} was expected.\n",
        cursor,
        bytes.size());
    return {};
  }

  return bytes;
}

std::size_t LocatorList::Size() const
{
  return accumulate(this->views.begin(),
                    this->views.end(),
                    0,
                    [](const std::size_t acc, const auto& loc)
                    { return acc + loc.size; });
}

const Asset* BNLFile::GetAsset(std::string_view asset_name) const
{
  auto found = std::ranges::find_if(
      this->assets_,
      [&asset_name](const Asset& asset)
      {
        return strncmp(asset.description.metadata.name.data(),
                       asset_name.data(),
                       sizeof(asset.description.metadata.name))
            == 0;
      });

  return found == this->assets_.end() ? nullptr : found.base();
}

const Asset* BNLFile::GetFirstAssetByType(AssetType asset_type) const
{
  auto found = std::ranges::find_if(
      this->assets_,
      [asset_type](const Asset& asset)
      { return asset.description.metadata.asset_type == asset_type; });

  return found == this->assets_.end() ? nullptr : found.base();
}

}  // namespace ghoulies
