#include <array>
#include <cassert>
#include <cstring>
#include <filesystem>
#include <format>
#include <iostream>
#include <memory>
#include <span>
#include <stdexcept>

#include "lib.hpp"

#include <SDL3/SDL.h>
#include <SDL3/SDL_error.h>
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_gpu.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_iostream.h>
#include <SDL3/SDL_log.h>
#include <SDL3/SDL_mouse.h>
#include <SDL3/SDL_oldnames.h>
#include <SDL3/SDL_stdinc.h>
#include <SDL3/SDL_surface.h>
#include <SDL3/SDL_video.h>
#include <backends/imgui_impl_sdl3.h>
#include <backends/imgui_impl_sdlgpu3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "file.hpp"
#include "ghoulies/nd.hpp"
#include "graphics/graphics.hpp"
#include "graphics/model.hpp"

// using std::filesystem::path;
// using ghoulies::ModelDescriptor;
//
using ghoulies::utils::ReadFile;
using graphics::Buffer;
using graphics::Index;
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

    this->key_states_ = nullptr;
    return;
  }

  int num_keys = 101;
  this->key_states_ = SDL_GetKeyboardState(&num_keys);

  if (key_states_ == nullptr) {
    std::cerr << std::format(
        "SDL is not able to retrieve the keyboard state. SDL_Error: {}\n",
        SDL_GetError());

    return;
  }

  window_ = SDL_CreateWindow(
      "Ghoulies Launcher", kWindowWidth, kWindowHeight, SDL_WINDOW_RESIZABLE);
  if (window_ == nullptr) {
    std::cerr << "Failed to create window.\n";
    return;
  }

  device_ = SDL_CreateGPUDevice(SDL_GPU_SHADERFORMAT_SPIRV, false, nullptr);
  if (device_ == nullptr) {
    std::cerr << "Failed to create SDL GPU device. Error: " << SDL_GetError()
              << "\n";
    return;
  }

  SDL_ClaimWindowForGPUDevice(device_, window_);

  /*

  // Get window surface
  SDL_Surface* surface {SDL_GetWindowSurface(window_)};

  if (surface == nullptr) {
    std::cerr << "Unable to acquire window surface.";
    return;
  }

  SDL_FillSurfaceRect(
      surface, nullptr, SDL_MapSurfaceRGB(surface, 0xFF, 0xFF, 0xFF));

  SDL_UpdateWindowSurface(window_);
  */

  auto vs_bytes = ReadFile("source/shaders/pbr_vert.spv").value();
  auto fs_bytes = ReadFile("source/shaders/pbr_frag.spv").value();

  const SDL_GPUShaderCreateInfo vs_create_info {
      .code_size = vs_bytes.size(),
      .code = vs_bytes.data(),
      .entrypoint = "main",
      .format = SDL_GPU_SHADERFORMAT_SPIRV,
      .stage = SDL_GPU_SHADERSTAGE_VERTEX,
      .num_samplers = 0,
      .num_storage_textures = 0,
      .num_storage_buffers = 0,
      .num_uniform_buffers = 1};

  const SDL_GPUShaderCreateInfo fs_create_info {
      .code_size = fs_bytes.size(),
      .code = fs_bytes.data(),
      .entrypoint = "main",
      .format = SDL_GPU_SHADERFORMAT_SPIRV,
      .stage = SDL_GPU_SHADERSTAGE_FRAGMENT,
      .num_samplers = 1,
      .num_storage_textures = 0,
      .num_storage_buffers = 0,
      .num_uniform_buffers = 0};

  pbr_vert_shader_ = SDL_CreateGPUShader(device_, &vs_create_info);
  if (pbr_vert_shader_ == nullptr) {
    std::cerr << std::format("Failed to create vertex shader! SDL_Error: {}\n",
                             SDL_GetError());
    return;
  }

  pbr_frag_shader_ = SDL_CreateGPUShader(device_, &fs_create_info);
  if (pbr_frag_shader_ == nullptr) {
    std::cerr << std::format(
        "Failed to create fragment shader! SDL_Error: {}\n", SDL_GetError());
    return;
  }

  std::array attributes = {
      SDL_GPUVertexAttribute {.location = 0,
                              .buffer_slot = 0,
                              .format = SDL_GPU_VERTEXELEMENTFORMAT_FLOAT3,
                              .offset = 0},

      SDL_GPUVertexAttribute {.location = 1,
                              .buffer_slot = 0,
                              .format = SDL_GPU_VERTEXELEMENTFORMAT_FLOAT3,
                              .offset = 12},

      SDL_GPUVertexAttribute {.location = 2,
                              .buffer_slot = 0,
                              .format = SDL_GPU_VERTEXELEMENTFORMAT_FLOAT3,
                              .offset = 24},

      SDL_GPUVertexAttribute {.location = 3,
                              .buffer_slot = 0,
                              .format = SDL_GPU_VERTEXELEMENTFORMAT_FLOAT2,
                              .offset = 36},

  };

  std::array vb_descriptions = {SDL_GPUVertexBufferDescription {
      .slot = 0,
      .pitch = sizeof(PBRVertex),
      .input_rate = SDL_GPU_VERTEXINPUTRATE_VERTEX}};

  SDL_GPUVertexInputState input_state {
      .vertex_buffer_descriptions = vb_descriptions.data(),
      .num_vertex_buffers = 1,
      .vertex_attributes = attributes.data(),
      .num_vertex_attributes = 4,
  };

  std::array color_target_descriptions = {SDL_GPUColorTargetDescription {
      .format = SDL_GPU_TEXTUREFORMAT_B8G8R8A8_UNORM,
      .blend_state {.enable_blend = false}}};

  SDL_GPUGraphicsPipelineCreateInfo pipeline_create_info {
      .vertex_shader = pbr_vert_shader_,
      .fragment_shader = pbr_frag_shader_,

      .vertex_input_state = input_state,

      // TODO: Make a pipeline for each
      .primitive_type = SDL_GPU_PRIMITIVETYPE_TRIANGLESTRIP,

      .rasterizer_state = SDL_GPURasterizerState {},

      .multisample_state =
          SDL_GPUMultisampleState {.sample_count = SDL_GPU_SAMPLECOUNT_1},

      .depth_stencil_state =
          SDL_GPUDepthStencilState {
              .enable_depth_test = false,
              .enable_stencil_test = false,
          },

      .target_info = SDL_GPUGraphicsPipelineTargetInfo {
          .color_target_descriptions = color_target_descriptions.data(),
          .num_color_targets = color_target_descriptions.size(),
          .has_depth_stencil_target = false,
      }};

  pbr_pipeline_ = SDL_CreateGPUGraphicsPipeline(device_, &pipeline_create_info);
  if (pbr_pipeline_ == nullptr) {
    std::cerr << std::format(
        "Failed to create pbr graphics pipeline! SDL_Error: {}\n",
        SDL_GetError());
    return;
  }

  camera_ = graphics::Camera {};

  camera_.position = {0, 0, -1};

  SDL_CaptureMouse(true);
  initialised_ = true;

  this->menu_ = std::make_unique<menu::Menu>(device_, window_);
}

GhouliesLib::~GhouliesLib()
{
  this->menu_.reset();

  // Destroy default texture before destroying the GPU device
  this->default_texture_.reset();

  SDL_ReleaseGPUShader(device_, pbr_vert_shader_);
  SDL_ReleaseGPUShader(device_, pbr_frag_shader_);

  SDL_ReleaseGPUGraphicsPipeline(device_, pbr_pipeline_);

  SDL_DestroyGPUDevice(device_);
  SDL_DestroyWindow(window_);
}

void GhouliesLib::UpdateEvents()
{
  // Hack to get window to stay up
  SDL_Event e;
  while (SDL_PollEvent(&e)) {
    menu_->ProcessEvent(&e);

    if (e.type == SDL_EVENT_QUIT) {
      this->quit_ = true;
    } else if (e.type == SDL_EVENT_MOUSE_MOTION) {
      camera_.rotation.y += e.motion.xrel * 0.001;
      camera_.rotation.x += e.motion.yrel * 0.001;
    }
  }

  const auto left = 0.01F * camera_.Left();
  const auto forwards = 0.01F * camera_.Forwards();

  if (key_states_[SDL_SCANCODE_A]) {
    camera_.position += left;
  } else if (key_states_[SDL_SCANCODE_D]) {
    camera_.position -= left;
  }

  if (key_states_[SDL_SCANCODE_W]) {
    camera_.position += forwards;
  } else if (key_states_[SDL_SCANCODE_S]) {
    camera_.position -= forwards;
  }
}

void GhouliesLib::DrawTestObjects(const graphics::Texture& texture)
{
  SDL_GPUBufferCreateInfo buffer_create_info {};

  /*
  PBRVertex f1 {.a_position = {-1, -1, 1}};
  PBRVertex f2 {.a_position = {1, -1, 1}};
  PBRVertex f3 {.a_position = {-1, 1, 1}};
  PBRVertex f4 {.a_position = {1, 1, 1}};

  PBRVertex b1 {.a_position = {-1, -1, -1}};
  PBRVertex b2 {.a_position = {1, -1, -1}};
  PBRVertex b3 {.a_position = {-1, 1, -1}};
  PBRVertex b4 {.a_position = {1, 1, -1}};

  std::array vertices {f1, f2, f3, f4, b1, b2, b3, b4};
  const Uint32 vertices_size = sizeof(PBRVertex) * vertices.size();
  */

  std::array vertices {
      PBRVertex {.a_position = {1, 1, 0}, .a_texcoords = {1, 1}},
      PBRVertex {.a_position = {1, -1, 0}, .a_texcoords = {1, 0}},
      PBRVertex {.a_position = {-1, 1, 0}, .a_texcoords = {0, 1}},
      PBRVertex {.a_position = {-1, -1, 0}, .a_texcoords = {0, 0}}};
  // const Uint32 vertices_size = sizeof(PBRVertex) * vertices.size();

  std::array<Uint16, 6> indices {0, 1, 2, 1, 2, 3};
  // const Uint32 indices_size = sizeof(Uint16) * indices.size();

  const std::span<const PBRVertex> span {vertices};

  auto* command_buffer {SDL_AcquireGPUCommandBuffer(this->device_)};

  // TODO: Replace this with proper error handling, even though this should
  // never really happen
  if (command_buffer == nullptr) {
    throw std::runtime_error("Bad ptr.");
  }

  // SDL_Log("Creating buffers.");

  auto vertex_buffer_result {graphics::CreateVertexBuffer(this->device_, span)};
  if (!vertex_buffer_result.has_value()) {
    std::cerr << "Unable to create temp vertex buffer.\n";
    return;
  }
  Buffer<PBRVertex> vertex_buffer {std::move(vertex_buffer_result.value())};
  if (auto result {vertex_buffer.Write(command_buffer, vertices)};
      !result.has_value())
  {
    std::cerr << "Unable to write vertex buffer. Error: " << SDL_GetError()
              << "\n";
    return;
  }

  auto index_buffer_result {
      graphics::CreateIndexBuffer(this->device_, indices)};
  if (!index_buffer_result.has_value()) {
    std::cerr << "Unable to create temp index buffer.\n";
    return;
  }

  Buffer<Index> index_buffer {std::move(index_buffer_result.value())};
  if (auto result {index_buffer.Write(command_buffer, indices)};
      !result.has_value())
  {
    std::cerr << "Unable to write index buffer. Error: " << SDL_GetError()
              << "\n";
    return;
  }

  SDL_GPUTexture* swapchain_texture {nullptr};

  Uint32 swapchain_width {};
  Uint32 swapchain_height {};

  // SDL_Log("Acquiring swapchain.");
  if (!SDL_WaitAndAcquireGPUSwapchainTexture(command_buffer,
                                             window_,
                                             &swapchain_texture,
                                             &swapchain_width,
                                             &swapchain_height)

  )
  {
    SDL_CancelGPUCommandBuffer(command_buffer);
    SDL_Log("Failed to acquire swapchain texture.");
    return;
  }

  // SDL_Log("Beginning render pass.");
  SDL_GPUColorTargetInfo color_target_info {
      .texture = swapchain_texture,
      .clear_color = {0.2F, 0.2F, 0.2F, 1.0F},
      .load_op = SDL_GPU_LOADOP_CLEAR,
      .store_op = SDL_GPU_STOREOP_STORE};

  // Create render pass and do commands
  SDL_GPURenderPass* render_pass =
      SDL_BeginGPURenderPass(command_buffer, &color_target_info, 1, nullptr);

  if (render_pass == nullptr) {
    throw std::runtime_error("Bad render pass.");
  }

  // SDL_Log("Binding Graphics Pipeline.");
  SDL_BindGPUGraphicsPipeline(render_pass, this->pbr_pipeline_);

  SDL_GPUViewport viewport {.x = 0,
                            .y = 0,
                            .w = static_cast<float>(swapchain_width),
                            .h = static_cast<float>(swapchain_height),
                            .min_depth = 0,
                            .max_depth = 1};

  // SDL_Log("Setting viewport.");
  SDL_SetGPUViewport(render_pass, &viewport);

  void* buffer = nullptr;

  // SDL_Log("Binding vertex buffers.");
  std::array<SDL_GPUBufferBinding, 1> vb_bindings {vertex_buffer.GetBinding()};
  SDL_BindGPUVertexBuffers(render_pass, 0, vb_bindings.data(), 1);

  auto ib_binding {index_buffer.GetBinding()};

  // SDL_Log("Binding index buffer.");
  SDL_BindGPUIndexBuffer(
      render_pass, &ib_binding, SDL_GPU_INDEXELEMENTSIZE_16BIT);

  const glm::mat4 identity(1.0F);

  const auto view {this->camera_.ModelMatrix()};
  const auto projection {this->camera_.ProjectionMatrix()};

  graphics::ViewUniforms uniforms {
      .model = identity, .view = view, .projection = projection};
  SDL_PushGPUVertexUniformData(command_buffer, 0, &uniforms, sizeof(uniforms));

  std::array bindings = {texture.SDLBinding()};
  SDL_BindGPUFragmentSamplers(render_pass, 0, bindings.data(), bindings.size());

  // SDL_Log("Drawing primitives.");
  SDL_DrawGPUIndexedPrimitives(render_pass, indices.size(), 1, 0, 0, 0);

  // SDL_Log("Ending render pass.");
  SDL_EndGPURenderPass(render_pass);

  SDL_SubmitGPUCommandBuffer(command_buffer);
}

std::unique_ptr<graphics::Texture> GhouliesLib::LoadTexture(
    graphics::TextureAsset asset)
{
  try {
    auto tex {
        std::make_unique<graphics::Texture>(this->device_, std::move(asset))};

    return tex;
  } catch (std::runtime_error& e) {
    std::cerr << e.what() << "\n";
  }

  return nullptr;
}

std::shared_ptr<graphics::Model> GhouliesLib::LoadModel(
    const ghoulies::Asset& asset)
{
  using namespace graphics;

  // std::span<uint8_t> span {static_cast<uint8_t*>(bytes), file_size};

  auto model_asset_exp {ghoulies::ModelAsset::FromAsset(asset)};

  if (!model_asset_exp.has_value()) {
    std::cerr << "Failed to load model "
              << asset.description.metadata.name.data()
              << "\nError: " << model_asset_exp.error() << "\n";
    return nullptr;
  }

  try {
    return std::make_unique<Model>(this->device_, model_asset_exp.value());
  } catch (std::runtime_error& e) {
    std::cerr << "Error loading model: " << e.what() << "\n";
  }

  return nullptr;
}

void GhouliesLib::DrawTestModel(graphics::Model& model,
                                const graphics::Texture& texture)
{
  auto* command_buffer {SDL_AcquireGPUCommandBuffer(this->device_)};

  // TODO: Replace this with proper error handling, even though this should
  // never really happen
  if (command_buffer == nullptr) {
    throw std::runtime_error("Bad ptr.");
  }

  // SDL_Log("Creating buffers.");
  SDL_GPUTexture* swapchain_texture {nullptr};

  Uint32 swapchain_width {};
  Uint32 swapchain_height {};

  // SDL_Log("Acquiring swapchain.");
  if (!SDL_WaitAndAcquireGPUSwapchainTexture(command_buffer,
                                             window_,
                                             &swapchain_texture,
                                             &swapchain_width,
                                             &swapchain_height)

  )
  {
    SDL_CancelGPUCommandBuffer(command_buffer);
    SDL_Log("Failed to acquire swapchain texture.");
    return;
  }

  // SDL_Log("Beginning render pass.");
  SDL_GPUColorTargetInfo color_target_info {
      .texture = swapchain_texture,
      .clear_color = {0.2F, 0.2F, 0.2F, 1.0F},
      .load_op = SDL_GPU_LOADOP_CLEAR,
      .store_op = SDL_GPU_STOREOP_STORE};

  // Create render pass and do commands
  SDL_GPURenderPass* render_pass {
      SDL_BeginGPURenderPass(command_buffer, &color_target_info, 1, nullptr)};

  if (render_pass == nullptr) {
    throw std::runtime_error("Bad render pass.");
  }

  // SDL_Log("Binding Graphics Pipeline.");
  SDL_BindGPUGraphicsPipeline(render_pass, this->pbr_pipeline_);

  SDL_GPUViewport viewport {.x = 0,
                            .y = 0,
                            .w = static_cast<float>(swapchain_width),
                            .h = static_cast<float>(swapchain_height),
                            .min_depth = 0,
                            .max_depth = 1};

  // SDL_Log("Setting viewport.");
  SDL_SetGPUViewport(render_pass, &viewport);

  const glm::mat4 identity(1.0F);

  const auto view {this->camera_.ModelMatrix()};
  const auto projection {this->camera_.ProjectionMatrix()};

  graphics::ViewUniforms uniforms {
      .model = identity, .view = view, .projection = projection};
  SDL_PushGPUVertexUniformData(command_buffer, 0, &uniforms, sizeof(uniforms));

  std::array bindings = {texture.SDLBinding()};
  SDL_BindGPUFragmentSamplers(render_pass, 0, bindings.data(), bindings.size());

  model.DrawBasic(render_pass);

  // SDL_Log("Ending render pass.");
  SDL_EndGPURenderPass(render_pass);

  SDL_SubmitGPUCommandBuffer(command_buffer);
};

graphics::DrawContext GhouliesLib::NewDrawContext()
{
  assert(this->default_texture_ != nullptr);

  auto* command_buffer {SDL_AcquireGPUCommandBuffer(this->device_)};

  // TODO: Replace this with proper error handling, even though this should
  // never really happen
  if (command_buffer == nullptr) {
    throw std::runtime_error("Bad ptr.");
  }

  // SDL_Log("Creating buffers.");
  SDL_GPUTexture* swapchain_texture {nullptr};

  Uint32 swapchain_width {};
  Uint32 swapchain_height {};

  // SDL_Log("Acquiring swapchain.");
  if (!SDL_WaitAndAcquireGPUSwapchainTexture(command_buffer,
                                             window_,
                                             &swapchain_texture,
                                             &swapchain_width,
                                             &swapchain_height)

  )
  {
    SDL_CancelGPUCommandBuffer(command_buffer);
    SDL_Log("Failed to acquire swapchain texture.");
    throw std::runtime_error("Failed to acquire swapchain texture.");
  }

  // SDL_Log("Beginning render pass.");
  SDL_GPUColorTargetInfo color_target_info {
      .texture = swapchain_texture,
      .clear_color = {0.2F, 0.2F, 0.2F, 1.0F},
      .load_op = SDL_GPU_LOADOP_CLEAR,
      .store_op = SDL_GPU_STOREOP_STORE};

  // Create render pass and do commands
  SDL_GPURenderPass* render_pass {
      SDL_BeginGPURenderPass(command_buffer, &color_target_info, 1, nullptr)};

  if (render_pass == nullptr) {
    throw std::runtime_error("Bad render pass.");
  }

  // SDL_Log("Binding Graphics Pipeline.");
  SDL_BindGPUGraphicsPipeline(render_pass, this->pbr_pipeline_);

  SDL_GPUViewport viewport {.x = 0,
                            .y = 0,
                            .w = static_cast<float>(swapchain_width),
                            .h = static_cast<float>(swapchain_height),
                            .min_depth = 0,
                            .max_depth = 1};

  // SDL_Log("Setting viewport.");
  SDL_SetGPUViewport(render_pass, &viewport);

  const glm::mat4 identity(1.0F);

  const auto view {this->camera_.ModelMatrix()};
  const auto projection {this->camera_.ProjectionMatrix()};

  graphics::ViewUniforms uniforms {
      .model = identity, .view = view, .projection = projection};
  SDL_PushGPUVertexUniformData(command_buffer, 0, &uniforms, sizeof(uniforms));

  std::array bindings = {this->default_texture_->SDLBinding()};
  SDL_BindGPUFragmentSamplers(render_pass, 0, bindings.data(), bindings.size());

  return graphics::DrawContext {.command_buffer = command_buffer,
                                .render_pass = render_pass};
}

void GhouliesLib::EndDrawContext(graphics::DrawContext ctx)
{
  // SDL_Log("Ending render pass.");
  SDL_EndGPURenderPass(ctx.render_pass);

  // TODO: Make sure this didn't fail
  SDL_SubmitGPUCommandBuffer(ctx.command_buffer);
}

void GhouliesLib::SetDefaultTexture(
    std::unique_ptr<graphics::Texture>&& texture)
{
  // TODO: Check move semantics and remove the reset
  this->default_texture_.reset();
  this->default_texture_ = std::move(texture);
}
