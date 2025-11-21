#pragma once

#include <expected>
#include <iostream>
#include <string>
#include <type_traits>

#include "../../utils/file.hpp"
#include "ghoulies/types.hpp"

namespace ghoulies
{

using utils::file::Bytes;

struct XBEConfig
{
  struct ResourceLocator
  {
    std::uint32_t virtual_offset;
    std::uint32_t count;
  };

  ResourceLocator anim_table;
  ResourceLocator attack_data;
  ResourceLocator hit_reaction;
  ResourceLocator main_objparams;
  ResourceLocator script_table;
  ResourceLocator move_state_objparams;
  ResourceLocator state_table;
};

constexpr XBEConfig kXbeConfigPalv1v0 {
    .anim_table = {.virtual_offset = 0x33ac88, .count = 0x56},
    .attack_data = {.virtual_offset = 0x33e100, .count = 0x1d},
    .hit_reaction = {.virtual_offset = 0x343800, .count = 0x27},
    .main_objparams = {.virtual_offset = 0x3d7928, .count = 0x1f1},
    .script_table = {.virtual_offset = 0x3e8a10, .count = 0x23},
    .move_state_objparams = {.virtual_offset = 0x402ca0, .count = 0x35c},
    .state_table = {.virtual_offset = 0x4202f0, .count = 0x29},
};

struct AssetHeader
{
  AssetAID asset_name;
  std::uint32_t data_ptr;
  std::uint32_t data_size;
  std::uint32_t asset_hash;
};

static_assert(sizeof(AssetHeader) == 0x8c);

struct XBEResource
{
  std::string name;
  Bytes data;
  std::uint32_t type_hash;

  template<typename OP>
    requires std::is_default_constructible_v<OP>
  std::optional<OP> AsType() const
  {
    if (this->data.size() <= sizeof(OP)) {
      return std::nullopt;
    }
    if (this->data.size() > sizeof(OP)) {
      std::cout << "Warning: Constructing objparams of size " << sizeof(OP)
                << " from data of size " << this->data.size()
                << ". There may be an ObjectParams type mismatch between the "
                   "asset and its instance.";
    }

    OP op {};
    std::memcpy(&op, this->data.data(), sizeof(OP));
    return op;
  }
};

struct GhouliesExecutableData
{
  std::vector<XBEResource> anim_tables;
  std::vector<XBEResource> attack_data;
  std::vector<XBEResource> hit_reactions;
  std::vector<XBEResource> main_objparams;
  std::vector<XBEResource> script_tables;
  std::vector<XBEResource> move_state_objparams;
  std::vector<XBEResource> state_tables;

  static std::expected<GhouliesExecutableData, std::string> FromXBEStream(
      utils::file::XBEStream& stream, const XBEConfig& config);

  [[nodiscard]] const XBEResource* GetResource(
      std::string_view objparams_aid) const;

  std::expected<GhouliesExecutableData, std::string> GetExecutable();
};

}  // namespace ghoulies
