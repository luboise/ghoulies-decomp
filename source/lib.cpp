#include <array>
#include <cassert>
#include <expected>
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
#include <SDL3/SDL_scancode.h>
#include <SDL3/SDL_stdinc.h>
#include <SDL3/SDL_surface.h>
#include <SDL3/SDL_video.h>
#include <backends/imgui_impl_sdl3.h>
#include <backends/imgui_impl_sdlgpu3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "file.hpp"
#include "ghoulies/bnl.hpp"
#include "ghoulies/game.hpp"
#include "ghoulies/script.hpp"
#include "graphics/graphics.hpp"
#include "graphics/model.hpp"
#include "utils/images.hpp"

// using std::filesystem::path;
// using ghoulies::ModelDescriptor;
//
using ghoulies::Bytes;
using ghoulies::utils::ReadFile;
using ghoulies::utils::ReadFileBytes;

using graphics::Texture;

using graphics::Index;
using graphics::PBRVertex;
using std::unexpected;
using std::filesystem::path;
using std::filesystem::recursive_directory_iterator;

namespace ghoulies
{

std::unique_ptr<GhouliesLib> GhouliesLib::instance {nullptr};

constexpr auto kWindowWidth = 1280;
constexpr auto kWindowHeight = 720;

std::expected<void, std::string> GhouliesLib::Initialise(
    GhouliesLibParams params)
{
  if (GhouliesLib::Initialised()) {}

  try {
    // Can't use std::make_unique because the constructor is private
    std::unique_ptr<GhouliesLib> lib {new GhouliesLib(params)};
    GhouliesLib::instance = std::move(lib);

    return {};
  } catch (std::runtime_error& e) {
    return unexpected(
        std::format("Failed to create GhouliesLib instance: {}", e.what()));
  }

  return unexpected("Failed to create GhouliesLib instance.");
}

GhouliesLib::~GhouliesLib()
{
  this->game_context_.Clear();

  this->menu_.reset();

  // Destroy default texture before destroying the GPU device
  this->default_texture_.reset();

  SDL_ReleaseGPUShader(device_, pbr_vert_shader_);
  SDL_ReleaseGPUShader(device_, pbr_frag_shader_);

  SDL_ReleaseGPUGraphicsPipeline(device_, pbr_pipeline_);

  SDL_DestroyGPUDevice(device_);
  SDL_DestroyWindow(window_);
}

GhouliesLib::GhouliesLib(const GhouliesLibParams& params)
    : quit_ {false}
    , window_ {nullptr}
    , device_ {nullptr}
    , pbr_vert_shader_ {nullptr}
    , pbr_frag_shader_ {nullptr}
    , pbr_pipeline_ {nullptr}
{
  path game_directory {params.game_directory.empty()
                           ? std::filesystem::current_path() / "gbtg"
                           : params.game_directory};

  if (!std::filesystem::is_directory(game_directory)) {
    throw std::runtime_error(
        std::format(
            "No directory {} exists. Make sure to " "extract " "the game " "fil" "es " "and" " pl" "ace" " th" "em " "here.",
            game_directory.string()));
  }

  this->game_directory_ = std::move(game_directory);

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

  auto vs_bytes = ReadFile("resources/shaders/pbr_vert.spv").value();
  auto fs_bytes = ReadFile("resources/shaders/pbr_frag.spv").value();

  const SDL_GPUShaderCreateInfo vs_create_info {
      .code_size = vs_bytes.size(),
      .code = vs_bytes.data(),
      .entrypoint = "main",
      .format = SDL_GPU_SHADERFORMAT_SPIRV,
      .stage = SDL_GPU_SHADERSTAGE_VERTEX,
      .num_samplers = 0,
      .num_storage_textures = 0,
      .num_storage_buffers = 0,
      .num_uniform_buffers = 2,
      .props = 0};

  const SDL_GPUShaderCreateInfo fs_create_info {
      .code_size = fs_bytes.size(),
      .code = fs_bytes.data(),
      .entrypoint = "main",
      .format = SDL_GPU_SHADERFORMAT_SPIRV,
      .stage = SDL_GPU_SHADERSTAGE_FRAGMENT,
      .num_samplers = 1,
      .num_storage_textures = 0,
      .num_storage_buffers = 0,
      .num_uniform_buffers = 1,
      .props = 0};

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
      .input_rate = SDL_GPU_VERTEXINPUTRATE_VERTEX,
      .instance_step_rate = {}}};

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
      .primitive_type = SDL_GPU_PRIMITIVETYPE_TRIANGLELIST,

      .rasterizer_state = SDL_GPURasterizerState {},

      .multisample_state =
          SDL_GPUMultisampleState {.sample_count = SDL_GPU_SAMPLECOUNT_1},

      .depth_stencil_state =
          SDL_GPUDepthStencilState {
              .compare_op = SDL_GPU_COMPAREOP_LESS,
              .enable_depth_test = true,
              .enable_depth_write = true,
              .enable_stencil_test = false,
          },

      .target_info = SDL_GPUGraphicsPipelineTargetInfo {
          .color_target_descriptions = color_target_descriptions.data(),
          .num_color_targets = color_target_descriptions.size(),
          .depth_stencil_format = SDL_GPU_TEXTUREFORMAT_D32_FLOAT,
          .has_depth_stencil_target = true,
          .padding1 = {},
          .padding2 = {},
          .padding3 = {},
      }};

  pbr_pipeline_ = SDL_CreateGPUGraphicsPipeline(device_, &pipeline_create_info);
  if (pbr_pipeline_ == nullptr) {
    std::cerr << std::format(
        "Failed to create pbr graphics pipeline! SDL_Error: {}\n",
        SDL_GetError());
    return;
  }

  this->menu_ = std::make_unique<menu::Menu>(device_, window_);

  {
    SDL_GPUTextureCreateInfo depth_info {
        .type = SDL_GPU_TEXTURETYPE_2D,
        .format = SDL_GPU_TEXTUREFORMAT_D32_FLOAT,
        .usage = SDL_GPU_TEXTUREUSAGE_DEPTH_STENCIL_TARGET,

        .width = 3840,
        .height = 2160,
        .layer_count_or_depth = 1,
        .num_levels = 1,
        .sample_count = SDL_GPU_SAMPLECOUNT_1,
        .props = {}};

    this->depth_texture_ = SDL_CreateGPUTexture(device_, &depth_info);
  }
  if (this->depth_texture_ == nullptr) {
    std::cerr << std::format("Failed to create depth texture. SDL_Error: {}",
                             SDL_GetError());
    return;
  }

  camera_ = graphics::Camera {};

  camera_.transform.position = {0, 0, -1};

  auto default_texture_opt {
      ghoulies::utils::LoadTexture("resources/textures/default_texture.png")};

  auto tex {this->LoadTexture(default_texture_opt.value())};
  if (tex == nullptr) {
    throw std::runtime_error("Failed to create default texture.\n");
  }

  this->SetDefaultTexture(std::move(tex));
}

void GhouliesLib::UpdateEvents()
{
  static float movement_speed {1};

  constexpr float kMaxMovementSpeed {100.0F};
  constexpr float kMinMovementSpeed {0.2F};

  // Hack to get window to stay up
  SDL_Event e;
  while (SDL_PollEvent(&e)) {
    menu_->ProcessEvent(&e);

    if (e.type == SDL_EVENT_QUIT) {
      this->quit_ = true;
    } else if (e.type == SDL_EVENT_MOUSE_MOTION) {
      constexpr float kMouseSensitivity {0.1F};

      camera_.RotateSpinClockwise(e.motion.xrel * kMouseSensitivity);
      camera_.RotateLeanForwards(e.motion.yrel * kMouseSensitivity);
    }
  }

  bool hyperspeed {key_states_[SDL_SCANCODE_LSHIFT]};

  const auto left = (static_cast<float>(hyperspeed ? 2 : 1)) * 0.01F
      * movement_speed * camera_.Left();
  const auto forwards = (static_cast<float>(hyperspeed ? 2 : 1)) * 0.01F
      * movement_speed * camera_.Forwards();
  const auto up = (static_cast<float>(hyperspeed ? 2 : 1)) * 0.01F
      * movement_speed * camera_.Up();

  if (key_states_[SDL_SCANCODE_B]) {
    game_context_.draw_backgrounds = !key_states_[SDL_SCANCODE_LSHIFT];
  }

  if (key_states_[SDL_SCANCODE_A]) {
    camera_.transform.position += left;
  } else if (key_states_[SDL_SCANCODE_D]) {
    camera_.transform.position -= left;
  }

  if (key_states_[SDL_SCANCODE_W]) {
    camera_.transform.position += forwards;
  } else if (key_states_[SDL_SCANCODE_S]) {
    camera_.transform.position -= forwards;
  }

  if (key_states_[SDL_SCANCODE_SPACE]) {
    camera_.transform.position += up;
  } else if (key_states_[SDL_SCANCODE_LCTRL]) {
    camera_.transform.position -= up;
  }

  if (key_states_[SDL_SCANCODE_EQUALS]) {
    movement_speed = std::min(kMaxMovementSpeed, movement_speed * 1.03F);
  }

  if (key_states_[SDL_SCANCODE_MINUS]) {
    movement_speed = std::max(kMinMovementSpeed, movement_speed / 1.03F);
  }

  if (key_states_[SDL_SCANCODE_0]) {
    this->lighting_uniforms_.ambient_brightness =
        std::min(1.0F, this->lighting_uniforms_.ambient_brightness + 0.005F);
  } else if (key_states_[SDL_SCANCODE_9]) {
    this->lighting_uniforms_.ambient_brightness =
        std::max(0.1F, this->lighting_uniforms_.ambient_brightness - 0.005F);
  }
}

std::unique_ptr<::graphics::Texture> GhouliesLib::LoadTexture(
    ::graphics::TextureAsset asset)
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
  // std::span<uint8_t> span {static_cast<uint8_t*>(bytes), file_size};

  auto model_asset_exp {ghoulies::ModelAsset::FromAsset(asset)};

  if (!model_asset_exp.has_value()) {
    std::cerr << "Failed to load model "
              << asset.description.metadata.name.data()
              << "\nError: " << model_asset_exp.error() << "\n";
    return nullptr;
  }

  try {
    return std::make_unique<graphics::Model>(this->device_,
                                             model_asset_exp.value());
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

  SDL_GPUDepthStencilTargetInfo depth_target_info {
      .texture = depth_texture_,
      .clear_depth = 0.0F,
      .load_op = SDL_GPU_LOADOP_CLEAR,
      .store_op = SDL_GPU_STOREOP_STORE,

      .stencil_load_op = SDL_GPU_LOADOP_DONT_CARE,
      .stencil_store_op = SDL_GPU_STOREOP_DONT_CARE,
      .cycle = false,

      .clear_stencil = {},
      .padding1 = {},
      .padding2 = {},
      // .clear_stencil=
  };

  // Create render pass and do commands
  SDL_GPURenderPass* render_pass {SDL_BeginGPURenderPass(
      command_buffer, &color_target_info, 1, &depth_target_info)};

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

  const auto view {this->camera_.ViewMatrix()};
  const auto projection {this->camera_.ProjectionMatrix()};

  graphics::ViewUniforms uniforms {.view = view, .projection = projection};
  SDL_PushGPUVertexUniformData(command_buffer, 0, &uniforms, sizeof(uniforms));

  graphics::ModelUniforms model_uniforms {.model = identity};
  SDL_PushGPUVertexUniformData(
      command_buffer, 1, &model_uniforms, sizeof(model_uniforms));

  std::array bindings = {texture.SDLBinding()};
  SDL_BindGPUFragmentSamplers(render_pass, 0, bindings.data(), bindings.size());

  model.DrawBasic(render_pass);

  // SDL_Log("Ending render pass.");
  SDL_EndGPURenderPass(render_pass);

  SDL_SubmitGPUCommandBuffer(command_buffer);
}

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

  SDL_GPUDepthStencilTargetInfo depth_target_info {
      .texture = depth_texture_,
      .clear_depth = 1.0F,
      .load_op = SDL_GPU_LOADOP_CLEAR,
      .store_op = SDL_GPU_STOREOP_STORE,

      .stencil_load_op = SDL_GPU_LOADOP_DONT_CARE,
      .stencil_store_op = SDL_GPU_STOREOP_DONT_CARE,
      .cycle = false,

      .clear_stencil = {},
      .padding1 = {},
      .padding2 = {},
      // .clear_stencil=
  };

  // Create render pass and do commands
  SDL_GPURenderPass* render_pass {SDL_BeginGPURenderPass(
      command_buffer, &color_target_info, 1, &depth_target_info)};

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

  const auto view {this->camera_.ViewMatrix()};
  const auto projection {this->camera_.ProjectionMatrix()};

  graphics::ViewUniforms uniforms {.view = view, .projection = projection};
  SDL_PushGPUVertexUniformData(command_buffer, 0, &uniforms, sizeof(uniforms));

  graphics::ModelUniforms model_uniforms {.model = identity};
  SDL_PushGPUVertexUniformData(
      command_buffer, 1, &model_uniforms, sizeof(model_uniforms));

  std::array bindings = {this->default_texture_->SDLBinding()};
  SDL_BindGPUFragmentSamplers(render_pass, 0, bindings.data(), bindings.size());

  SDL_PushGPUFragmentUniformData(command_buffer,
                                 0,
                                 &this->lighting_uniforms_,
                                 sizeof(this->lighting_uniforms_));

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

void GhouliesLib::SetLighting(graphics::LightingUniforms&& uniforms)
{
  this->lighting_uniforms_ = std::move(uniforms);
}

void GhouliesLib::DrawScene(graphics::DrawContext& ctx)
{
  if (game_context_.draw_backgrounds) {
    for (auto& bg : game_context_.backgrounds) {
      bg->Draw(ctx);
    }
  }

  for (auto& weapon : game_context_.weapons) {
    weapon->Draw(ctx);
  }
}

std::expected<void, std::string> GhouliesLib::SetPlaycamScript(
    std::string_view playcam_aid)
{
  // TODO: Clear current background/context

  // Load BNL file for new playcam
  auto bnl_path {FindGameFile(std::string {playcam_aid} + ".bnl")};
  if (!bnl_path.has_value()) {
    return unexpected("No BNL file exists for asset ID "
                      + std::string(playcam_aid));
  }

  if (auto result {this->LoadBNLFile(bnl_path.value())}; !result.has_value()) {
    return unexpected(
        std::format("Failed to load BNL file. Error: {}", result.error()));
  }

  // Load new playcam script
  const auto* playcam_script {this->FindPlaycamScript()};

  if (playcam_script == nullptr) {
    return unexpected(std::format(
        "Failed to get playcam script. Error: {}\n",
        "Unable to find the playcam script in the open BNL files."));
  }
  ghoulies::Script script {*playcam_script};

  script.Update(game_context_);

  // Run initial script commands
  //
  ghoulies::objects::Background::BackgroundParams bg_params;
  bg_params.model_aid = std::string(game_context_.background_model_aid);

  std::cout << "Loading background " << bg_params.model_aid.data() << ".\n";

  try {
    auto bg {std::make_shared<objects::Background>(bg_params)};
    game_context_.backgrounds.push_back(bg);

  } catch (std::runtime_error& e) {
    return unexpected(
        std::format("Failed to load new background. Error: {}", e.what()));
  }

  game_context_.move_on = false;

  const auto* marker_asset {
      this->GetFirstAssetByType(ghoulies::AssetType::ResMarker)};

  if (marker_asset != nullptr) {
    Marker marker {*marker_asset};

    std::cout << "Num marker entries: " << marker.Size() << ".\n";

    if (auto result {game_context_.InitialiseFromMarker(marker)};
        !result.has_value())
    {
      return unexpected(
          std::format("Failed to initialise game state from marker. Error: {}",
                      result.error()));
    }
  }

  return {};
}

std::optional<std::filesystem::path> GhouliesLib::FindGameFile(
    std::string_view filename)
{
  for (const auto& entry : recursive_directory_iterator(game_directory_)) {
    if (entry.is_regular_file() && entry.path().filename() == filename) {
      return entry.path();
    }
  }

  return std::nullopt;
}

[[nodiscard]] const Asset* GhouliesLib::FindPlaycamScript() const
{
  const auto& playcam {std::ranges::find_if(
      this->bnl_files_,
      [](const auto& pair) { return pair.first.contains("playcam"); })};

  if (playcam == this->bnl_files_.end()) {
    return nullptr;
  }

  return playcam->second.GetFirstAssetByType(AssetType::ResScript);
}

std::expected<void, std::string> GhouliesLib::LoadBNLFile(
    std::filesystem::path bnl_path)
{
  if (this->bnl_files_.contains(bnl_path)) {
    std::cout << "BNL file " << bnl_path
              << " has already been loaded. Skipping reload request.\n";
    return {};
  }

  std::optional<Bytes> bytes_opt {ReadFileBytes(bnl_path)};

  if (!bytes_opt.has_value()) {
    return unexpected(std::string("Failed to read bytes of ")
                      + bnl_path.string());
  }

  auto bnl_exp {ghoulies::BNLFile::FromBytes(bytes_opt.value())};
  if (!bnl_exp.has_value()) {
    return unexpected {
        std::format("Unable to load BNL file. Error: {}\n", bnl_exp.error())};
  }

  bnl_files_.emplace(bnl_path, std::move(bnl_exp).value());

  return {};
}

}  // namespace ghoulies
