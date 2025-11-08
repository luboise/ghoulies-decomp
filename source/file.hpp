#pragma once

#include <cstdint>
#include <filesystem>
#include <optional>
#include <vector>

namespace ghoulies::utils
{

using Bytes = std::vector<std::byte>;

std::optional<std::vector<uint8_t>> ReadFile(
    const std::filesystem::path& file_path);

[[nodiscard]] std::optional<Bytes> ReadFileBytes(
    const std::filesystem::path& file_path);

[[nodiscard]] std::optional<Bytes> ZLibDecompress(
    const Bytes& bytes,
    /// The minimum decompressed size
    uint32_t decompressed_size = 0);

}  // namespace ghoulies::utils
