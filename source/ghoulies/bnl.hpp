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

// Taken from project_grabbed
// https://github.com/x1nixmzeng/project-grabbed
enum class AssetType
{
  ResTexture = 1,
  ResAnim = 2,
  ResUnknown3 = 3,
  ResModel = 4,
  ResAnimEvents = 5,

  ResCutscene = 7,
  ResCutsceneEvents = 8,

  ResMisc = 10,
  ResActorGoals = 11,
  ResMarker = 12,
  ResFxCallout = 13,
  ResAidList = 14,

  ResLoctext = 16,

  ResXSoundbank = 18,
  ResXDSP = 19,
  ResXCueList = 20,
  ResFont = 21,
  ResGhoulybox = 22,
  ResGhoulyspawn = 23,
  ResScript = 24,
  ResActorAttribs = 25,
  ResEmitter = 26,
  ResParticle = 27,
  ResRumble = 28,
  ResShakeCam = 29,

  ResCount,  // This will automatically take the next value (30)
};

// Prevent packing of these types
#pragma pack(push, 1)

struct Locator
{
  uint32_t offset;
  uint32_t size;

  [[nodiscard]] std::size_t Offset() const { return offset; }

  [[nodiscard]] std::size_t MaxOffset() const
  {
    return static_cast<std::size_t>(offset) + size;
  }
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

struct AssetMetadata
{
  std::array<char, 128> name;
  AssetType asset_type;
  uint32_t unk_1;
  uint32_t unk_2;
};

struct AssetDescription

{
  AssetMetadata metadata;
  uint32_t chunk_count;
  uint32_t descriptor_ptr;
  uint32_t descriptor_size;
  uint32_t locator_list_ptr;
  uint32_t resource_size;  // The total size needed for this asset, including
                           // its descriptor list
};

static_assert(sizeof(AssetDescription) == 160);

struct LocatorList
{
  uint32_t size;
  uint32_t num_views;
  std::vector<Locator> views;

  /// Gets the resource specified by this locator list from a span elsewhere.
  /// This span must begin at the start of the buffer section of the BNL file
  std::optional<Bytes> GetResource(std::span<std::byte> span);

  [[nodiscard]] std::size_t Size() const;

  static std::optional<LocatorList> FromSpan(std::span<std::byte> span);
};

#pragma pack(pop)

struct Asset
{
  AssetDescription description;

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
  explicit BNLFile(std::span<Asset> assets);

private:
  std::vector<Asset> assets_;
};

}  // namespace ghoulies
