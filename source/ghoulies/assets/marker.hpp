#pragma once

#include <cstdint>
#include <variant>

#include <glm/glm.hpp>

#include "../bnl.hpp"
#include "ghoulies/types.hpp"

namespace ghoulies
{

enum class MarkerType : std::uint16_t
{
  Player = 0x02,
  GhoulyBoxGhouly = 0x04,
  Weapon = 0x05,
  Powerup = 0x06,
  FxEmitter = 0x0a,
  Unknown0x0b = 0x0b,
  Unknown0x0c = 0x0c,
  GhoulyBoxItem = 0x0D,
};

struct MarkerHeader
{
  uint32_t size;
  MarkerType marker_type;
  uint16_t marker_id;
  uint32_t idk1;
  glm::vec3 pos;
  glm::vec3 rot_euler;
  float scale;
};

static_assert(sizeof(MarkerHeader) == 40);

struct RawMarkerEntry
{
  MarkerHeader header;
  Bytes data;
};

struct WeaponMarker
{
  MarkerHeader header;
  AssetAID objparams_aid;
  AssetAID unknown_aid1;
  AssetAID unknown_aid2;
  AssetAID unknown_aid3;
  std::array<float, 12> floats;
};

struct PowerupMarker
{
  MarkerHeader header;
  AssetAID objparams_aid;
};

static_assert(sizeof(WeaponMarker) == 0x258);

using MarkerEntry = std::variant<RawMarkerEntry, WeaponMarker, PowerupMarker>;

class Marker
{
public:
  /// throws std::runtime_error on failure, initialises a script otherwise
  explicit Marker(const Asset& asset);

  [[nodiscard]] auto Size() const { return entries_.size(); }

  [[nodiscard]] const auto& Entries() const { return entries_; }

private:
  std::vector<MarkerEntry> entries_;
};

}  // namespace ghoulies
