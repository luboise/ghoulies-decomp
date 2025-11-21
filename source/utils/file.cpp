#include <cstdint>
#include <expected>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <optional>
#include <utility>
#include <vector>

#include "./file.hpp"

#include "file.hpp"
#include "libdeflate.h"
#include "utils/errors.hpp"

namespace fs = std::filesystem;
using std::byte, std::ios;

namespace utils
{

using errors::OrThrow;
using std::unexpected;
using utils::file::Bytes;

std::optional<std::vector<uint8_t>> file::ReadFile(const fs::path& file_path)
{
  std::ifstream vs_stream {file_path};

  std::size_t file_size = fs::file_size(file_path);

  std::vector<uint8_t> bytes(file_size);

  auto* char_ptr = reinterpret_cast<char*>(bytes.data());

  vs_stream.read(char_ptr, static_cast<std::streamsize>(file_size));

  return bytes;
}

std::optional<Bytes> file::ReadFileBytes(const fs::path& file_path)
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

std::optional<Bytes> file::ZLibDecompress(const Bytes& bytes,
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

}  // namespace utils

namespace utils::file
{

struct XBEHeaderSection
{
  std::uint32_t flags;
  std::uint32_t virtual_offset;
  std::uint32_t virtual_size;
  std::uint32_t file_offset;
  std::uint32_t file_size;
  std::uint32_t name_ptr;
  std::uint32_t reference;
  std::uint32_t head_ref_ptr;
  std::uint32_t tail_ref_ptr;
  std::array<std::byte, 20> checksum;
};

static_assert(sizeof(XBEHeaderSection) == (sizeof(std::uint32_t) * 9) + 20);

XBEStream::XBEStream(Bytes bytes)
    : Stream(0)
    , bytes_(std::move(bytes))
{
  ByteStream stream {bytes_};

  // Seek to image base in header
  OrThrow(stream.Seek(0x104));

  std::uint32_t image_base {stream.Read<std::uint32_t>().value_or(0)};

  // Seek to section count in header
  OrThrow(stream.Seek(0x11c));

  std::uint32_t section_count {stream.Read<std::uint32_t>().value_or(0)};

  std::uint32_t section_header_ptr = {stream.Read<std::uint32_t>().value_or(0)};

  this->memory_map_.mappings.reserve(section_count);

  OrThrow(stream.Seek(section_header_ptr - image_base));

  for (std::uint32_t i {0}; i < section_count; i++) {
    XBEHeaderSection header = stream.Read<XBEHeaderSection>().value_or({});
    memory_map_.mappings.emplace_back(MemoryMap<std::uint32_t>::Mapping {
        .file_offset = header.file_offset,
        .virtual_offset = header.virtual_offset,
        .mapping_size = header.virtual_size,
    });
  }
}

std::expected<XBEStream, std::string> XBEStream::FromBytes(Bytes bytes)
{
  try {
    XBEStream stream {std::move(bytes)};

    return stream;
  } catch (std::exception& e) {
    return unexpected(e.what());
  }
}

VoidResult XBEStream::ReadBytes(std::span<std::byte> bytes)
{
  auto virtual_offset {this->GetCursor()};

  auto file_offset_opt {memory_map_.GetFileOffset(virtual_offset)};
  if (!file_offset_opt.has_value()) {
    return unexpected(errors::kNoValueError);
  }
  auto file_offset {std::move(file_offset_opt).value()};

  if (auto end_offset {memory_map_.GetFileOffset(
          static_cast<std::uint32_t>(virtual_offset + bytes.size()))};
      !end_offset.has_value())
  {
    return unexpected(errors::kOffsetOutOfBounds);
  }

  std::memcpy(bytes.data(), &this->bytes_[file_offset], bytes.size());

  this->AdvanceCursor(static_cast<std::uint32_t>(bytes.size()));

  return {};
}

VoidResult XBEStream::Seek(std::uint32_t offset)
{
  auto file_offset {memory_map_.GetFileOffset(offset)};
  if (!file_offset.has_value()) {
    return unexpected(errors::kOffsetOutOfBounds);
  }

  SetCursor(file_offset.value());

  return {};
}

}  // namespace utils::file
