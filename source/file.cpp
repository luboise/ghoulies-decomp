#include <cstdint>
#include <filesystem>
#include <fstream>
#include <optional>
#include <vector>

namespace fs = std::filesystem;

std::optional<std::vector<uint8_t>> ReadFile(const fs::path& shader_path)
{
  std::ifstream vs_stream {shader_path};

  std::size_t file_size = fs::file_size(shader_path);

  std::vector<uint8_t> bytes(file_size);

  auto* char_ptr = reinterpret_cast<char*>(bytes.data());

  vs_stream.read(char_ptr, static_cast<std::streamsize>(file_size));

  return bytes;
}
