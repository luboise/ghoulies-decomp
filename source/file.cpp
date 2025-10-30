#include <cstdint>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <optional>
#include <vector>

#include "file.hpp"

namespace fs = std::filesystem;

using std::byte, std::ios;

using ghoulies::utils::Bytes;

namespace ghoulies
{

std::optional<std::vector<uint8_t>> utils::ReadFile(const fs::path& file_path)
{
  std::ifstream vs_stream {file_path};

  std::size_t file_size = fs::file_size(file_path);

  std::vector<uint8_t> bytes(file_size);

  auto* char_ptr = reinterpret_cast<char*>(bytes.data());

  vs_stream.read(char_ptr, static_cast<std::streamsize>(file_size));

  return bytes;
}

std::optional<Bytes> utils::ReadFileBytes(const fs::path& file_path)
{
  std::ifstream vs_stream {file_path, ios::binary};

  // If failed to open
  if (!vs_stream) {
    std::cerr << "Unable to open file " << file_path << "\n";
    return std::nullopt;
  }

  std::size_t file_size = fs::file_size(file_path);

  std::vector<byte> bytes(file_size);

  vs_stream.read(reinterpret_cast<char*>(bytes.data()),
                 static_cast<std::streamsize>(bytes.size()));

  return bytes;
}

}  // namespace ghoulies
