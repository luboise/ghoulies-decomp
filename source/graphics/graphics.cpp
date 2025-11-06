#ifndef GLM_FORCE_LEFT_HANDED
#  error RIGHT HANDED SYSTEM is active. All matrix math will not align with world views.
#endif

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

  matrix = glm::translate(matrix, this->position);
  matrix = matrix * this->RotationMatrix();
  matrix = glm::scale(matrix, this->scale);

  return matrix;
}

glm::mat4 Camera::ViewMatrix() const
{
  return glm::inverse(this->ModelMatrix());
}

glm::vec3 Camera::Left() const
{
  return this->RotationMatrix() * glm::vec4 {glm::vec3 {-1, 0, 0}, 0};
}

glm::vec3 Camera::Forwards() const
{
  return this->RotationMatrix() * glm::vec4 {glm::vec3 {0, 0, 1}, 0};
}

glm::vec3 Camera::Up() const
{
  return this->RotationMatrix() * glm::vec4 {glm::vec3 {0, 1, 0}, 0};
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

  matrix = glm::rotate(matrix, this->rotation[1], {0, 1, 0});
  matrix = glm::rotate(matrix, this->rotation[0], {1, 0, 0});
  matrix = glm::rotate(matrix, this->rotation[2], {0, 0, 1});

  return matrix;
}

Camera& Camera::RotateX(float degrees)
{
  this->rotation.x += glm::pi<float>() * degrees / 180.0F;
  return *this;
}

Camera& Camera::RotateY(float degrees)
{
  // Inverted for left handed SDL coordinates
  this->rotation.y += glm::pi<float>() * degrees / 180.0F;
  ;
  return *this;
}

Camera& Camera::RotateZ(float degrees)
{
  this->rotation.z += glm::pi<float>() * degrees / 180.0F;

  return *this;
}

Texture::Texture(SDL_GPUDevice* device, TextureAsset asset)
    : device_(nullptr)
    , texture_(nullptr)
    , sampler_(nullptr)
{
  SDL_GPUTextureCreateInfo texture_info {.type = SDL_GPU_TEXTURETYPE_2D,
                                         .format = asset.format,

                                         .usage = SDL_GPU_TEXTUREUSAGE_SAMPLER,
                                         .width = asset.width,
                                         .height = asset.height,
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

  this->asset_ = std::move(asset);
  this->device_ = device;
  this->texture_ = texture;
  this->sampler_ = sampler;

  this->Write(asset_.data);
  asset_.data.clear();
}

Texture::~Texture()
{
  if (device_ != nullptr && texture_ != nullptr) {
    SDL_ReleaseGPUTexture(device_, texture_);
  }

  if (device_ != nullptr && sampler_ != nullptr) {
    SDL_ReleaseGPUSampler(device_, sampler_);
  }
}

SDL_GPUTextureSamplerBinding Texture::SDLBinding() const
{
  return {.texture = texture_, .sampler = sampler_};
}

bool Texture::Write(const ghoulies::Bytes& bytes)
{
  assert(bytes.size() > 0);

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
                                    .w = asset_.width,
                                    .h = asset_.height,
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

  Buffer<Index> buffer {device, BufferType::kIndex, data.size(), index_buffer};

  auto* command_buffer {SDL_AcquireGPUCommandBuffer(device)};

  if (command_buffer == nullptr) {
    return unexpected(
        std::format(
            "Unable to acquire new command buffer when " "initialising " "buffe" "r. " "Error" ": {}",
            SDL_GetError()));
  }

  if (auto result {buffer.Write(command_buffer, data)}; !result.has_value()) {
    return unexpected(std::format(
        "Failed to write data to vertex buffer. Error: {}", result.error()));
  }

  if (!SDL_SubmitGPUCommandBuffer(command_buffer)) {
    return unexpected(
        std::format(
            "Failed to submit command buffer when " "initialising " "vertex" " " "bu" "ff" "er" ". " "Error: " "{}",
            SDL_GetError()));
  }
  return buffer;
}

/*
Texture& Texture::operator=(Texture&& other) noexcept
{



  if (this->texture_ != nullptr && this->device_ != nullptr) {
    SDL_ReleaseGPUTexture(device_, texture_);
    this->texture_ = nullptr;
  }

  if (device_ != nullptr && sampler_ != nullptr) {
    SDL_ReleaseGPUSampler(device_, sampler_);
  }

  this->texture_ = other.texture_;
  other.texture_ = nullptr;

  this->sampler_ = other.sampler_;
  other.sampler_ = nullptr;

  this->asset_ = std::move(other.asset_);
  this->device_ = other.device_;

  return *this;
}
*/

Texture::Texture(Texture&& other) noexcept
{
  assert(this->texture_ != other.texture_);

  this->texture_ = other.texture_;
  other.texture_ = nullptr;

  this->sampler_ = other.sampler_;
  other.sampler_ = nullptr;

  this->asset_ = std::move(other.asset_);
  this->device_ = other.device_;
}

}  // namespace graphics
