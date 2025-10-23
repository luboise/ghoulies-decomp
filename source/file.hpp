#pragma once

#include <cstdint>
#include <filesystem>
#include <optional>
#include <vector>

std::optional<std::vector<uint8_t>> ReadFile(
    const std::filesystem::path& shader_path);
