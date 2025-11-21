#include "file.hpp"
#define STB_IMAGE_IMPLEMENTATION

#include <cstddef>

#include "images.hpp"
#include "stb_image.h"

using std::filesystem::path;

using utils::file::Bytes;

std::optional<ghoulies::TextureAsset> utils::LoadTexture(
    std::string_view image_path)
{
  auto file_bytes_opt {
      ::utils::file::ReadFileBytes(static_cast<path>(image_path))};

  if (!file_bytes_opt.has_value()) {
    return std::nullopt;
  }

  int x {};
  int y {};
  int channels_in_file {};
  int desired_channels {4};

  auto* image_data {stbi_load_from_memory(
      reinterpret_cast<stbi_uc*>(file_bytes_opt.value().data()),
      static_cast<int>(file_bytes_opt.value().size()),
      &x,
      &y,
      &channels_in_file,
      desired_channels)};

  // Failed to load image
  if (image_data == nullptr) {
    return std::nullopt;
  }

  std::size_t data_size {static_cast<size_t>(x * y * desired_channels)};

  ghoulies::TextureAsset new_tex_asset {
      .format = SDL_GPU_TEXTUREFORMAT_R8G8B8A8_UNORM,
      .width = static_cast<uint16_t>(x),
      .height = static_cast<uint16_t>(y),
      .tile_count {},
      .data = Bytes(data_size)};

  std::memcpy(new_tex_asset.data.data(), image_data, data_size);

  stbi_image_free(image_data);

  return new_tex_asset;
}
