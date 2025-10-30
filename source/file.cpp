#include <cstdint>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <optional>
#include <vector>

#include "file.hpp"

#include "libdeflate.h"

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

std::optional<Bytes> utils::ZLibDecompress(const Bytes& bytes,
                                           uint32_t decompressed_size)
{
  if (bytes.size() == 0) {
    std::cerr << std::format(
        "Unable to decompress empty ZLib stream (expected {} bytes "
        "decompressed).\n", decompressed_size);
    return {};
  }

  if (decompressed_size == 0) {
    decompressed_size = bytes.size() * 4;
  }

  std::optional<Bytes> ret {};

  auto* decompressor = libdeflate_alloc_decompressor();

  Bytes out_bytes;

  while (true) {
    out_bytes.resize(decompressed_size);

    std::size_t out_size {};
    auto result = libdeflate_zlib_decompress(decompressor,
                                             bytes.data(),
                                             bytes.size(),
                                             out_bytes.data(),
                                             out_bytes.size(),
                                             &out_size);

    if (result == libdeflate_result::LIBDEFLATE_INSUFFICIENT_SPACE) {
      out_bytes.resize(0);  /// Resize and clear the memory
      libdeflate_free_decompressor(decompressor);

      decompressed_size *= 2;
      continue;
    }

    if (result == libdeflate_result::LIBDEFLATE_SHORT_OUTPUT) {
      // Success
      out_bytes.resize(out_size);
    }

    else if (result != libdeflate_result::LIBDEFLATE_SUCCESS)
    {
      std::cerr << std::format("Failed to decompress file of size {}.\n",
                               bytes.size());
      break;
    }

    ret = out_bytes;
    break;
  }

  libdeflate_free_decompressor(decompressor);

  return ret;
}

}  // namespace ghoulies
