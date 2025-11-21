#pragma once

#include <cstdint>
#include <cstring>
#include <expected>
#include <filesystem>
#include <optional>
#include <span>
#include <string>
#include <type_traits>
#include <vector>

#include "utils/errors.hpp"

namespace utils::file
{

using errors::VoidResult;

using Bytes = std::vector<std::byte>;

std::optional<std::vector<uint8_t>> ReadFile(
    const std::filesystem::path& file_path);

[[nodiscard]] std::optional<Bytes> ReadFileBytes(
    const std::filesystem::path& file_path);

[[nodiscard]] std::optional<Bytes> ZLibDecompress(
    const Bytes& bytes,
    /// The minimum decompressed size
    uint32_t decompressed_size = 0);

/// MemoryMap of an executable. Uses O as the type of a pointer in that
/// executable's memory space. For example, an XBOX XBE is 32-bit, and should
/// use std::uint32_t as its pointer type.
template<typename O = std::size_t>
  requires std::is_trivially_copyable_v<O>
struct MemoryMap
{
  struct Mapping
  {
    O file_offset;
    O virtual_offset;
    O mapping_size;

    [[nodiscard]] std::optional<O> GetFileOffset(O v_offset) const
    {
      if (v_offset < this->virtual_offset
          || v_offset >= this->virtual_offset + this->mapping_size)
      {
        return std::nullopt;
      }

      return v_offset - this->virtual_offset + this->file_offset;
    }
  };

  std::vector<Mapping> mappings;

  [[nodiscard]] std::optional<O> GetFileOffset(O v_offset) const
  {
    for (const Mapping& mapping : mappings) {
      if (auto file_offset {mapping.GetFileOffset(v_offset)};
          file_offset.has_value())
      {
        return file_offset.value();
      }
    }

    return std::nullopt;
  }
};

template<typename O>
  requires std::is_trivially_copyable_v<O>
class Stream
{
public:
  // Must be implemented by subclass
  virtual VoidResult ReadBytes(std::span<std::byte> bytes) = 0;
  virtual VoidResult Seek(O offset) = 0;

  explicit Stream(O cursor = 0)
      : cursor_(cursor)
  {
  }

  virtual ~Stream() = default;

  template<typename T>
    requires std::is_default_constructible_v<T>
  std::optional<T> Read()
  {
    std::array<std::byte, sizeof(T)> bytes;

    if (auto success {ReadBytes(bytes)}; !success.has_value()) {
      return std::nullopt;
    };

    return std::bit_cast<T>(bytes);
  }

  [[nodiscard]] auto GetCursor() const { return cursor_; }

  Stream(Stream&& other) noexcept = default;
  Stream& operator=(Stream&&) = default;

  Stream(const Stream&) = delete;
  Stream& operator=(const Stream&) = delete;

protected:
  void SetCursor(O cursor) { this->cursor_ = cursor; }

  void AdvanceCursor(O amount) { SetCursor(GetCursor() + amount); }

private:
  O cursor_;
};

class ByteStream : public Stream<std::size_t>
{
public:
  explicit ByteStream(std::span<const std::byte> span)
      : bytes_(span)
  {
  }

  VoidResult ReadBytes(std::span<std::byte> bytes) override
  {
    // TODO: Put bounds check here
    auto copy_start {GetCursor()};

    auto copy_size {bytes.size()};

    std::memcpy(bytes.data(), &this->bytes_[copy_start], copy_size);

    AdvanceCursor(copy_size);

    return {};
  }

  VoidResult Seek(std::size_t offset) override
  {
    // TODO: Put bounds check here
    SetCursor(offset);

    return {};
  }

private:
  std::span<const std::byte> bytes_;
};

class XBEStream : public Stream<std::uint32_t>
{
public:
  static std::expected<XBEStream, std::string> FromBytes(Bytes bytes);
  ~XBEStream() override = default;

  VoidResult ReadBytes(std::span<std::byte> bytes) override;
  VoidResult Seek(std::uint32_t offset) override;

  XBEStream(XBEStream&&) = default;
  XBEStream& operator=(XBEStream&&) = default;

  XBEStream(const XBEStream&) = delete;
  XBEStream& operator=(const XBEStream&) = delete;

private:
  explicit XBEStream(Bytes bytes);

  MemoryMap<std::uint32_t> memory_map_;
  Bytes bytes_;
};

}  // namespace utils::file
