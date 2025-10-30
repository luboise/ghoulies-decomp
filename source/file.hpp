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

std::optional<Bytes> ReadFileBytes(const std::filesystem::path& file_path);

}  // namespace ghoulies::utils
