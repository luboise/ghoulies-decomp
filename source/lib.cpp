#include <array>
#include <filesystem>
#include <format>
#include <iostream>

#include "lib.hpp"

#include <SDL3/SDL.h>
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_gpu.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_log.h>
#include <SDL3/SDL_stdinc.h>
#include <SDL3/SDL_surface.h>
#include <SDL3/SDL_video.h>

#include "file.hpp"
#include "graphics.hpp"

using std::filesystem::path;

using graphics::PBRVertex;

constexpr auto kWindowWidth = 1280;
constexpr auto kWindowHeight = 720;

GhouliesLib::GhouliesLib()
    : window_ {nullptr}
    , device_ {nullptr}
    , pbr_vert_shader_ {nullptr}
    , pbr_frag_shader_ {nullptr}
    , initialised_ {false}
    , quit_ {false}
    , pbr_pipeline_ {nullptr}
{
  if (!SDL_Init(SDL_INIT_VIDEO)) {
    std::cerr << std::format("SDL could not initialize! SDL_Error: {}\n",
                             SDL_GetError());
    return;
  }

  SDL_Window* window = SDL_CreateWindow(
      "Ghoulies Launcher", kWindowWidth, kWindowHeight, SDL_WINDOW_RESIZABLE);

  SDL_GPUDevice* device =
      SDL_CreateGPUDevice(SDL_GPU_SHADERFORMAT_SPIRV, false, nullptr);

  SDL_ClaimWindowForGPUDevice(device, window);

  // Get window surface
  SDL_Surface* surface = SDL_GetWindowSurface(window);

  SDL_FillSurfaceRect(
      surface, nullptr, SDL_MapSurfaceRGB(surface, 0xFF, 0xFF, 0xFF));

  SDL_UpdateWindowSurface(window);

  auto vs_bytes = ReadFile("source/shaders/pbr.vert").value();
  auto fs_bytes = ReadFile("source/shaders/pbr.frag").value();

  const SDL_GPUShaderCreateInfo vs_create_info {
      .code_size = vs_bytes.size(),
      .code = vs_bytes.data(),
      .entrypoint = "main",
      .format = SDL_GPU_SHADERFORMAT_SPIRV,
      .stage = SDL_GPU_SHADERSTAGE_VERTEX,
      .num_samplers = 0,
      .num_storage_textures = 0,
      .num_storage_buffers = 0,
      .num_uniform_buffers = 0,
      .props = 0};

  const SDL_GPUShaderCreateInfo fs_create_info {
      .code_size = fs_bytes.size(),
      .code = fs_bytes.data(),
      .entrypoint = "main",
      .format = SDL_GPU_SHADERFORMAT_SPIRV,
      .stage = SDL_GPU_SHADERSTAGE_FRAGMENT,
      .num_samplers = 0,
      .num_storage_textures = 0,
      .num_storage_buffers = 0,
      .num_uniform_buffers = 0,
      .props = 0};

  auto* pbr_vert_shader = SDL_CreateGPUShader(device, &vs_create_info);
  if (pbr_vert_shader == nullptr) {
    std::cerr << std::format("Failed to create vertex shader! SDL_Error: {}\n",
                             SDL_GetError());
    return;
  }

  auto* pbr_frag_shader = SDL_CreateGPUShader(device, &fs_create_info);
  if (pbr_frag_shader == nullptr) {
    std::cerr << std::format(
        "Failed to create fragment shader! SDL_Error: {}\n", SDL_GetError());
    return;
  }

  SDL_GPUGraphicsPipelineCreateInfo pipeline_create_info {
      .vertex_shader = this->pbr_vert_shader_,
      .fragment_shader = this->pbr_frag_shader_,

      .rasterizer_state = SDL_GPURasterizerState {},

      .multisample_state = SDL_GPUMultisampleState {},

      .depth_stencil_state = SDL_GPUDepthStencilState {},

      .target_info = SDL_GPUGraphicsPipelineTargetInfo {},
  };

  SDL_GPUGraphicsPipeline* graphics_pipeline {
      SDL_CreateGPUGraphicsPipeline(device, &pipeline_create_info)};

  if (graphics_pipeline == nullptr) {
    std::cerr << std::format(
        "Failed to create pbr graphics pipeline! SDL_Error: {}\n",
        SDL_GetError());
    return;
  }

  this->window_ = window;
  this->device_ = device;

  this->pbr_vert_shader_ = pbr_vert_shader;
  this->pbr_frag_shader_ = pbr_frag_shader;

  this->pbr_pipeline_ = graphics_pipeline;

  this->quit_ = false;

  this->initialised_ = true;
}

GhouliesLib::~GhouliesLib()
{
  SDL_ReleaseGPUShader(this->device_, this->pbr_vert_shader_);
  SDL_ReleaseGPUShader(this->device_, this->pbr_frag_shader_);

  SDL_ReleaseGPUGraphicsPipeline(this->device_, this->pbr_pipeline_);

  SDL_DestroyGPUDevice(device_);
  SDL_DestroyWindow(window_);
}

void GhouliesLib::UpdateEvents()
{
  // Hack to get window to stay up
  SDL_Event e;
  while (SDL_PollEvent(&e)) {
    if (e.type == SDL_EVENT_QUIT) {
      this->quit_ = true;
    }
  }
}

void GhouliesLib::DrawRectangle()
{
  auto* command_buffer = SDL_AcquireGPUCommandBuffer(this->device_);
  // Create buffers

  std::vector<PBRVertex> vertices {PBRVertex {.a_position = {-1, -1, 0}},
                                   PBRVertex {.a_position = {0, 1, 0}},
                                   PBRVertex {.a_position = {1, -1, 0}}};

  SDL_GPUBufferCreateInfo buffer_info {
      .usage = SDL_GPU_BUFFERUSAGE_VERTEX,
      .size = static_cast<Uint32>(sizeof(PBRVertex) * vertices.size())};

  auto* vertex_buffer = SDL_CreateGPUBuffer(this->device_, &buffer_info);

  buffer_info.usage = SDL_GPU_BUFFERUSAGE_INDEX;
  buffer_info.size = sizeof(Uint32) * 3;

  auto* index_buffer = SDL_CreateGPUBuffer(this->device_, &buffer_info);

  SDL_GPUColorTargetInfo color_target_info {};
  SDL_GPUDepthStencilTargetInfo depth_stencil_target_info {};

  // Create render pass and do commands
  SDL_GPURenderPass* render_pass = SDL_BeginGPURenderPass(
      command_buffer, &color_target_info, 1, &depth_stencil_target_info);

  SDL_BindGPUGraphicsPipeline(render_pass, this->pbr_pipeline_);

  SDL_GPUViewport viewport {.x = 0,
                            .y = 0,
                            .w = kWindowWidth,
                            .h = kWindowHeight,
                            .min_depth = 0,
                            .max_depth = 1};

  SDL_SetGPUViewport(render_pass, &viewport);

  void* buffer = nullptr;

  std::array<SDL_GPUBufferBinding, 1> vb_bindings {
      SDL_GPUBufferBinding {.buffer = vertex_buffer, .offset = 0}};
  SDL_BindGPUVertexBuffers(render_pass, 0, vb_bindings.data(), 1);

  SDL_GPUBufferBinding ib_binding {.buffer = index_buffer, .offset = 0};

  SDL_BindGPUIndexBuffer(
      render_pass, &ib_binding, SDL_GPU_INDEXELEMENTSIZE_16BIT);

  // SDL_BindGPUVertexSamplers()

  SDL_DrawGPUPrimitives(render_pass, vertices.size(), 0, 0, 0);

  SDL_EndGPURenderPass(render_pass);

  SDL_SubmitGPUCommandBuffer(command_buffer);

  SDL_ReleaseGPUBuffer(this->device_, vertex_buffer);
  SDL_ReleaseGPUBuffer(this->device_, index_buffer);
};
