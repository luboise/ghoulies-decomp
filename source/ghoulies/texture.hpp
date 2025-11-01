#pragma once

#include <array>
#include <cstdint>

#include <SDL3/SDL_gpu.h>

#include "../file.hpp"

enum class D3DTextureType : uint32_t
{
  kDXT1 = 0x0000000C,
  kDXT2 = 0x0000000E,
  kDXT3 = 0x0000000E,
  kA8R8G8B8 = 0x00000012,
};

struct TextureDescriptor
{
  D3DTextureType format;
  std::uint32_t header_size;  // 28
  std::uint16_t width;
  std::uint16_t height;
  std::uint32_t flags;  // 0x00000001
  std::uint32_t unknown_3a;
  std::uint32_t tile_count;
  std::uint32_t texture_offset;
  std::uint32_t data_size;

  std::array<std::uint8_t, 12> unknown_12;
};

struct TextureAsset
{
  SDL_GPUTextureFormat format;
  std::uint16_t width;
  std::uint16_t height;
  std::uint32_t tile_count;

  ghoulies::utils::Bytes data;
};
