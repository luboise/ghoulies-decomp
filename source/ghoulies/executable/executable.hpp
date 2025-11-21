#pragma once

#include <expected>
#include <string>

#include "../../utils/file.hpp"

namespace ghoulies
{

struct GhouliesExecutable
{
  Bytes executable_bytes;
};

std::expected<GhouliesExecutable, std::string> GetExecutable();

}  // namespace ghoulies
