#include <cstring>
#include <expected>
#include <iostream>
#include <utility>

#include "bnl.hpp"

namespace ghoulies
{

std::expected<BNLFile, std::string> BNLFile::FromBytes(
    std::span<std::byte> bytes)
{
  if (bytes.size() < sizeof(BNLHeader)) {
    return std::unexpected("Not enough bytes to parse BNLHeader.");
  }

  BNLHeader header {};

  std::memcpy(&header, bytes.data(), sizeof(header));

  std::cout << "File count: " << header.file_count << "\n";

  BNLFile bnl {};

  return bnl;
}

BNLFile::BNLFile(std::unordered_map<std::string, Asset> assets)
    : assets_(std::move(assets))
{
}

}  // namespace ghoulies
