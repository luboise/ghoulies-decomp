#include <expected>

#include "executable.hpp"

#include "utils/errors.hpp"

namespace ghoulies
{
using utils::errors::OrThrow;

std::expected<GhouliesExecutableData, std::string>
ghoulies::GhouliesExecutableData::FromXBEStream(utils::file::XBEStream& stream,
                                                const XBEConfig& config)
{
  GhouliesExecutableData executable {};

  const auto get_xbe_resources =
      [&stream](const XBEConfig::ResourceLocator& locator)
      -> std::expected<std::vector<XBEResource>, std::string>
  {
    if (auto result {stream.Seek(locator.virtual_offset)}; !result.has_value())
    {
      return std::unexpected(std::format(
          "Failed to read at offset {} in XBEStream.", locator.virtual_offset));
    }

    std::vector<XBEResource> resources(locator.count);

    AssetHeader header {};
    for (std::uint32_t i {0}; i < locator.count; i++) {
      if (auto opt {stream.Read<AssetHeader>()}; opt.has_value()) {
        header = std::move(opt).value();
      } else {
        return std::unexpected("Failed to read AssetHeader from XBEStream.");
      }

      if (header.data_ptr == 0) {
        return std::unexpected(
            std::format("Invalid pointer in AssetHeader: {}", header.data_ptr));
      }
      if (header.data_size == 0) {
        return std::unexpected(std::format(
            "Invalid data size in AssetHeader: {}", header.data_size));
      }

      Bytes data(header.data_size);
      if (auto result {stream.ReadBytesAt(data, header.data_ptr)};
          !result.has_value())
      {
        return std::unexpected("Failed to read XBEStream bytes.");
      }

      // TODO: Implement type hash
      resources[i] = {.name = std::string(header.asset_name.data()),
                      .data = data,
                      .type_hash = 0};
    }

    return resources;
  };

  try {
    executable.anim_tables = OrThrow(get_xbe_resources(config.anim_table));
    executable.attack_data = OrThrow(get_xbe_resources(config.attack_data));
    executable.hit_reactions = OrThrow(get_xbe_resources(config.hit_reaction));
    executable.main_objparams =
        OrThrow(get_xbe_resources(config.main_objparams));
    executable.script_tables = OrThrow(get_xbe_resources(config.script_table));
    executable.move_state_objparams =
        OrThrow(get_xbe_resources(config.move_state_objparams));
    executable.state_tables = OrThrow(get_xbe_resources(config.state_table));
  } catch (std::runtime_error& e) {
    return std::unexpected(e.what());
  }

  return executable;
}

[[nodiscard]] const XBEResource* GhouliesExecutableData::GetResource(
    std::string_view objparams_aid) const
{
  const auto search = [&objparams_aid](std::span<const XBEResource> values)
      -> const XBEResource*
  {
    for (const auto& header : values) {
      if (header.name == objparams_aid) {
        return &header;
      }
    }

    return nullptr;
  };

  const XBEResource* ptr {nullptr};

  ptr = (ptr == nullptr) ? search(this->anim_tables) : ptr;
  ptr = (ptr == nullptr) ? search(this->attack_data) : ptr;
  ptr = (ptr == nullptr) ? search(this->hit_reactions) : ptr;
  ptr = (ptr == nullptr) ? search(this->main_objparams) : ptr;
  ptr = (ptr == nullptr) ? search(this->script_tables) : ptr;
  ptr = (ptr == nullptr) ? search(this->move_state_objparams) : ptr;
  ptr = (ptr == nullptr) ? search(this->state_tables) : ptr;

  return ptr;
}

}  // namespace ghoulies
