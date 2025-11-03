#include "graphics.hpp"

#include <SDL3/SDL.h>
#include <SDL3/SDL_error.h>
#include <SDL3/SDL_gpu.h>
#include <SDL3/SDL_render.h>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/glm.hpp>
#include <glm/matrix.hpp>

#include "bits/stdc++.h"

namespace graphics
{

glm::mat4 Camera::ModelMatrix() const
{
  glm::mat4 matrix(1.0F);

  matrix = glm::scale(matrix, this->scale);

  matrix = this->RotationMatrix() * matrix;

  matrix = glm::translate(matrix, this->position);

  return matrix;
}

glm::mat4 Camera::ViewMatrix() const
{
  return glm::inverse(this->ModelMatrix());
}

glm::vec3 Camera::Left() const
{
  return this->RotationMatrix() * glm::vec4 {glm::vec3 {-1, 0, 0}, 1};
  // return glm::vec4 {0, 0, 1, 1};
}

glm::vec3 Camera::Forwards() const
{
  return this->ViewMatrix() * glm::vec4 {glm::vec3 {0, 0, 1}, 1};
  // return glm::vec4 {0, 0, 1, 1};
}

glm::mat4 Camera::ProjectionMatrix() const
{
  const float fov_v =
      2 * std::atan(1 / this->AspectRatio() * std::tan(this->fov_h / 2));

  return glm::perspectiveFov(fov_v,
                             static_cast<float>(this->viewport_width),
                             static_cast<float>(this->viewport_height),
                             this->near,
                             this->far);
}

glm::float32_t Camera::AspectRatio() const
{
  return static_cast<glm::float32_t>(this->viewport_width)
      / static_cast<glm::float32_t>(this->viewport_height);
}

glm::mat4 Camera::RotationMatrix() const
{
  glm::mat4 matrix(1.0F);

  matrix = glm::rotate(matrix, this->rotation[0], {1, 0, 0});
  matrix = glm::rotate(matrix, this->rotation[1], {0, 1, 0});
  matrix = glm::rotate(matrix, this->rotation[2], {0, 0, 1});

  return matrix;
};

Texture::Texture(SDL_GPUDevice* device, TextureParams params)
    : device_(nullptr)
    , texture_(nullptr)
    , sampler_(nullptr)
{
  SDL_GPUTextureCreateInfo texture_info {
      .type = SDL_GPU_TEXTURETYPE_2D,
      .format = SDL_GPU_TEXTUREFORMAT_BC3_RGBA_UNORM,

      .usage = SDL_GPU_TEXTUREUSAGE_SAMPLER,
      .width = params.width,
      .height = params.height,
      .layer_count_or_depth = 1,
      .num_levels = 1};

  SDL_GPUTexture* texture {SDL_CreateGPUTexture(device, &texture_info)};

  if (texture == nullptr) {
    throw std::runtime_error(std::format("Failed to create SDL texture: {}",
                                         std::string(SDL_GetError())));
  }

  SDL_GPUSamplerCreateInfo sampler_info {
      .min_filter = SDL_GPU_FILTER_LINEAR,
      .mag_filter = SDL_GPU_FILTER_LINEAR,
      .mipmap_mode = SDL_GPU_SAMPLERMIPMAPMODE_NEAREST,
      .address_mode_u = SDL_GPU_SAMPLERADDRESSMODE_REPEAT,
      .address_mode_v = SDL_GPU_SAMPLERADDRESSMODE_REPEAT,
      .address_mode_w = SDL_GPU_SAMPLERADDRESSMODE_REPEAT,
      .mip_lod_bias = 0,
      .max_anisotropy = 8,
      .compare_op = SDL_GPU_COMPAREOP_GREATER,
      .enable_anisotropy = true,
  };

  SDL_GPUSampler* sampler {SDL_CreateGPUSampler(device, &sampler_info)};
  if (sampler == nullptr) {
    throw std::runtime_error(std::format("Failed to create SDL sampler: {}",
                                         std::string(SDL_GetError())));
  }

  this->params_ = std::move(params);
  this->device_ = device;
  this->texture_ = texture;
  this->sampler_ = sampler;

  this->Write(params_.data);
  params_.data.clear();
}

Texture::~Texture()
{
  if (device_ != nullptr && texture_ != nullptr) {
    SDL_ReleaseGPUTexture(device_, texture_);
  }
}

SDL_GPUTextureSamplerBinding Texture::SDLBinding() const
{
  return {.texture = texture_, .sampler = sampler_};
}

bool Texture::Write(const ghoulies::Bytes& bytes)
{
  SDL_GPUCommandBuffer* command_buffer {SDL_AcquireGPUCommandBuffer(device_)};

  if (command_buffer == nullptr) {
    std::cerr << "Unable to acquire command buffer.\n";
    return false;
  }

  SDL_GPUTransferBufferCreateInfo transfer_buffer_info {
      .usage = SDL_GPU_TRANSFERBUFFERUSAGE_UPLOAD,
      .size = static_cast<Uint32>(bytes.size()),
  };

  SDL_GPUTransferBuffer* transfer_buffer {
      SDL_CreateGPUTransferBuffer(device_, &transfer_buffer_info)};

  if (transfer_buffer == nullptr) {
    std::cerr << "Failed to create SDL transfer buffer.\n";
    SDL_CancelGPUCommandBuffer(command_buffer);
    return false;
  }

  auto* buf {SDL_MapGPUTransferBuffer(device_, transfer_buffer, false)};

  if (buf == nullptr) {
    std::cerr << "Failed to map GPU transfer buffer.\n";
    SDL_ReleaseGPUTransferBuffer(device_, transfer_buffer);
    SDL_CancelGPUCommandBuffer(command_buffer);

    return false;
  }

  std::memcpy(buf, bytes.data(), bytes.size());

  SDL_GPUCopyPass* copy_pass {SDL_BeginGPUCopyPass(command_buffer)};

  if (copy_pass == nullptr) {
    std::cerr << "Failed to retrieve copy pass when writing texture.\n";

    SDL_ReleaseGPUTransferBuffer(device_, transfer_buffer);
    SDL_CancelGPUCommandBuffer(command_buffer);
    return false;
  }

  SDL_GPUTextureTransferInfo transfer_info {
      .transfer_buffer = transfer_buffer,
      .offset = 0,
  };

  SDL_GPUTextureRegion destination {.texture = texture_,
                                    .mip_level = 0,
                                    .layer = 0,
                                    .x = 0,
                                    .y = 0,
                                    .w = params_.width,
                                    .h = params_.height,
                                    .d = 1};

  SDL_UploadToGPUTexture(copy_pass, &transfer_info, &destination, false);

  SDL_EndGPUCopyPass(copy_pass);

  bool success = true;

  if (!SDL_SubmitGPUCommandBuffer(command_buffer)) {
    std::cerr << "Failed to submit command buffer. Error: " << SDL_GetError()
              << "\n";

    success = false;
  }

  SDL_UnmapGPUTransferBuffer(this->device_, transfer_buffer);
  SDL_ReleaseGPUTransferBuffer(device_, transfer_buffer);

  return success;
}

std::expected<Buffer<Index>, std::string> CreateIndexBuffer(
    SDL_GPUDevice* device, const std::span<const Index>& data)
{
  const auto index_buffer_size {data.size() * sizeof(Index)};

  SDL_GPUBufferCreateInfo buffer_info {};
  buffer_info.usage = SDL_GPU_BUFFERUSAGE_INDEX;
  buffer_info.size = index_buffer_size;

  auto* index_buffer {SDL_CreateGPUBuffer(device, &buffer_info)};

  if (index_buffer == nullptr) {
    return std::unexpected(
        std::format("Unable to create buffer. Error: {}", SDL_GetError()));
  }

  return Buffer<Index> {device, BufferType::kIndex, data.size(), index_buffer};
}

}  // namespace graphics
