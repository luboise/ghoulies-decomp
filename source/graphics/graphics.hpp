#pragma once

#include <cstring>
#include <iostream>

#include <SDL3/SDL_error.h>
#include <SDL3/SDL_gpu.h>
#include <SDL3/SDL_stdinc.h>
#include <glm/glm.hpp>

#include "../ghoulies/bnl.hpp"

namespace graphics
{

using std::unexpected;

using ghoulies::Asset;

using Index = uint16_t;

struct PBRVertex
{
  glm::vec3 a_position {0, 0, 0};
  glm::vec3 a_colour {0, 0, 1};
  glm::vec3 a_normal {0, 1, 0};
  glm::vec2 a_texcoords {0, 0};
};

struct ViewUniforms
{
  glm::mat4 view;
  glm::mat4 projection;
};

struct ModelUniforms
{
  glm::mat4 model;
};

struct LightingUniforms
{
  float ambient_brightness {1.0F};
  glm::vec3 room_lighting_colour {1.0F, 1.0F, 1.0F};
};

struct Transform
{
  glm::vec3 position;
  glm::vec3 rotation;
  glm::vec3 scale;

  Transform& RotateX(float degrees);
  Transform& RotateY(float degrees);
  Transform& RotateZ(float degrees);

  [[nodiscard]] glm::mat4 ModelMatrix() const;
  [[nodiscard]] glm::mat4 RotationMatrix() const;

  [[nodiscard]] glm::vec3 Left() const;
  [[nodiscard]] glm::vec3 Forwards() const;
  [[nodiscard]] glm::vec3 Up() const;
};

struct Camera
{
  Transform transform;

  glm::float32_t fov_h;
  glm::float32_t near;
  glm::float32_t far;

  glm::uint32_t viewport_width;
  glm::uint32_t viewport_height;

  [[nodiscard]] glm::mat4 ViewMatrix() const;

  [[nodiscard]] glm::mat4 ProjectionMatrix() const;

  [[nodiscard]] glm::float32_t AspectRatio() const;

  Camera()
      : Camera({0, 0, 0}, {0, 0, 0}, {1, 1, 1})
  {
  }

  Camera(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
      : transform(Transform {
            .position = position, .rotation = rotation, .scale = scale})
      , fov_h(90)
      , near(0.1F)
      , far(1000.0F)
      , viewport_width(1280)
      , viewport_height(720)
  {
  }

  Camera& RotateX(float degrees)
  {
    this->transform.RotateX(degrees);
    return *this;
  }

  Camera& RotateY(float degrees)
  {
    this->transform.RotateY(degrees);
    return *this;
  }

  Camera& RotateZ(float degrees)
  {
    this->transform.RotateZ(degrees);
    return *this;
  }

  Camera& RotateLeanForwards(float degrees)
  {
    RotateX(degrees);
    return *this;
  }

  Camera& RotateSpinClockwise(float degrees)
  {
    RotateY(degrees);
    return *this;
  }

  Camera& RollClockwise(float degrees)
  {
    RotateZ(-degrees);
    return *this;
  }

  [[nodiscard]] glm::vec3 Left() const { return this->transform.Left(); }

  [[nodiscard]] glm::vec3 Forwards() const
  {
    return this->transform.Forwards();
  }

  [[nodiscard]] glm::vec3 Up() const { return this->transform.Up(); }
};

struct TextureAsset
{
  SDL_GPUTextureFormat format;
  std::uint16_t width;
  std::uint16_t height;
  std::uint32_t tile_count {1};

  ghoulies::utils::Bytes data;
};

class Texture
{
public:
  /// Throws std::runtime_error on failure, creates a texture otherwise.
  Texture(struct SDL_GPUDevice* device, TextureAsset asset);
  ~Texture();

  Texture(const Texture&) = delete;
  Texture& operator=(const Texture&) = delete;

  Texture(Texture&&) noexcept;
  Texture& operator=(Texture&&) noexcept = delete;

  /// Returns true if the texture was successfully updated, and false otherwise
  bool Write(const ghoulies::Bytes& bytes);

  [[nodiscard]] auto Width() const { return asset_.width; }

  [[nodiscard]] auto Height() const { return asset_.height; }

  [[nodiscard]] const auto& Params() const { return this->asset_; }

  [[nodiscard]] SDL_GPUTextureSamplerBinding SDLBinding() const;

private:
  TextureAsset asset_;

  SDL_GPUDevice* device_;
  SDL_GPUTexture* texture_;
  SDL_GPUSampler* sampler_;
};

struct DrawCommand
{
  SDL_GPUPrimitiveType primitive_type;
  Uint32 first_vertex;
  Uint32 first_index;
  Uint32 num_indices;
  uint32_t material_index;
};

struct DrawContext
{
  SDL_GPUCommandBuffer* command_buffer;
  SDL_GPURenderPass* render_pass;
  bool draw_colliders {false};

  void SetModelUniforms(const ModelUniforms& uniforms);
};

enum class BufferType
{
  kVertex,
  kIndex,
};

template<typename T>
struct Buffer
{
  SDL_GPUDevice* device;
  BufferType buffer_type;
  std::size_t count;
  SDL_GPUBuffer* handle;

  std::size_t Size() { return this->count * sizeof(T); }

  Buffer()
      : device(nullptr)
      , buffer_type(BufferType::kVertex)
      , count(0)
      , handle(nullptr)
  {
  }

  Buffer(SDL_GPUDevice* device,
         BufferType buffer_type,
         std::size_t count,
         SDL_GPUBuffer* handle)
      : device(device)
      , handle(handle)
      , count(count)
      , buffer_type(buffer_type)
  {
  }

  Buffer(Buffer&& other) noexcept
      : device(other.device)
      , buffer_type(other.buffer_type)
      , count(other.count)
      , handle(other.handle)
  {
    other.device = nullptr;
    other.handle = nullptr;
    other.count = 0;
  }

  Buffer& operator=(Buffer&& other) noexcept
  {
    this->device = other.device;

    this->handle = other.handle;
    other.handle = nullptr;

    this->count = other.count;

    return *this;
  }

  ~Buffer()
  {
    if (this->handle != nullptr) {
      if (this->device == nullptr) {
        std::cerr << "Buffer has a non-null handle, but no device pointer.\n";
        return;
      }

      SDL_ReleaseGPUBuffer(this->device, this->handle);
    }
  }

  std::expected<void, std::string> Write(SDL_GPUCommandBuffer* command_buffer,
                                         const std::span<const T>& data,
                                         std::size_t offset = 0)
  {
    if (data.size() > this->Size() || data.size() + offset > this->Size()) {
      return unexpected("Bad buffer write.");
    }

    {  // Transfer data
      auto* copy_pass {SDL_BeginGPUCopyPass(command_buffer)};

      if (copy_pass == nullptr) {
        return unexpected("Bad copy pass.");
      }

      Uint32 write_size(data.size() * sizeof(T));

      SDL_GPUBufferRegion transfer_region {
          .buffer = this->handle,
          .offset = static_cast<Uint32>(offset),
          .size = write_size};

      SDL_GPUTransferBufferCreateInfo tb_info {
          .usage = SDL_GPU_TRANSFERBUFFERUSAGE_UPLOAD, .size = write_size};
      auto* transfer_buffer {
          SDL_CreateGPUTransferBuffer(this->device, &tb_info)};

      SDL_GPUTransferBufferLocation tb_location {
          .transfer_buffer = transfer_buffer, .offset = 0};

      auto* ptr {
          SDL_MapGPUTransferBuffer(this->device, transfer_buffer, false)};

      std::memcpy(ptr, data.data(), write_size);

      SDL_UploadToGPUBuffer(copy_pass, &tb_location, &transfer_region, false);
      SDL_UnmapGPUTransferBuffer(this->device, transfer_buffer);
      SDL_ReleaseGPUTransferBuffer(this->device, transfer_buffer);
    }

    return {};
  }

  SDL_GPUBufferBinding GetBinding(Uint32 offset = 0)
  {
    return SDL_GPUBufferBinding {.buffer = this->handle, .offset = offset};
  }
};

template<typename T>
std::expected<Buffer<T>, std::string> CreateVertexBuffer(
    SDL_GPUDevice* device, const std::span<const T> data)
{
  if (data.size() == 0) {
    return unexpected("Unable to create vertex buffer of size 0.");
  }

  const auto vertex_buffer_size {data.size() * sizeof(T)};

  SDL_GPUBufferCreateInfo buffer_info {};
  buffer_info.usage = SDL_GPU_BUFFERUSAGE_VERTEX;
  buffer_info.size = vertex_buffer_size;

  auto* vertex_buffer {SDL_CreateGPUBuffer(device, &buffer_info)};

  if (vertex_buffer == nullptr) {
    return std::unexpected(
        std::format("Unable to create buffer. Error: {}", SDL_GetError()));
  }

  Buffer<T> buffer {device, BufferType::kVertex, data.size(), vertex_buffer};

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

std::expected<Buffer<Index>, std::string> CreateIndexBuffer(
    SDL_GPUDevice* device, const std::span<const Index>& data);

}  // namespace graphics
