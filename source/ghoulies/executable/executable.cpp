#include <expected>

#include "executable.hpp"

#include "utils/errors.hpp"

namespace ghoulies
{
using utils::errors::OrThrow;

std::expected<GhouliesExecutable, std::string>
ghoulies::GhouliesExecutable::FromXBEStream(utils::file::XBEStream& stream,
                                            const XBEConfig& config)
{
  GhouliesExecutable executable {};

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

}  // namespace ghoulies
