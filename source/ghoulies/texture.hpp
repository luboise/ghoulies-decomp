#pragma once

#include <array>
#include <cstdint>

#include <SDL3/SDL_gpu.h>

#include "d3d.hpp"

struct TextureDescriptor
{
  d3d::D3DTextureType format;
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

struct ModelTextureDescriptor
{
  d3d::D3DTextureType format;
  std::uint32_t header_size;  // 28
  std::uint16_t width;
  std::uint16_t height;
  std::uint32_t flags;  // 0x00000001
  std::uint32_t resource_index;
  std::uint32_t texture_offset;
  std::uint32_t data_size;
  std::array<std::uint8_t, 12> unknown_12;
};
