#pragma once

#include <array>
#include <cstddef>
#include <cstdint>
#include <expected>
#include <optional>
#include <span>
#include <string>
#include <string_view>
#include <unordered_map>

#include "../file.hpp"

namespace ghoulies
{

using utils::Bytes;

struct Locator
{
  uint32_t offset;
  uint32_t size;
};

static_assert(sizeof(Locator) == 8);

struct BNLHeader
{
  uint16_t file_count;
  uint8_t flags;
  std::array<std::byte, 5> unknown_2;

  Locator asset_desc_loc;
  Locator buffer_views_loc;
  Locator buffer_loc;
  Locator descriptor_loc;
};

static_assert(sizeof(BNLHeader) == 40);

struct Asset
{
  /// Bytes which form the descriptor of the asset
  Bytes descriptor;
  /// Bytes which form the resource of the asset
  Bytes resource;
};

class BNLFile
{
public:
  std::optional<Asset> GetAsset(std::string_view asset_name);

  /// Reads a BNLFile from a byte stream
  static std::expected<BNLFile, std::string> FromBytes(std::span<std::byte>);

  /// Construct with empty assets list
  BNLFile() = default;

  /// Construct from list of assets
  explicit BNLFile(std::unordered_map<std::string, Asset> assets);

private:
  std::unordered_map<std::string, Asset> assets_;
};

}  // namespace ghoulies
