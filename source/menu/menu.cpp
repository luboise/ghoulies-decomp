#include "menu.hpp"

#include <backends/imgui_impl_sdl3.h>
#include <backends/imgui_impl_sdlgpu3.h>
#include <imgui.h>

namespace menu
{
Menu::Menu(SDL_GPUDevice* device, SDL_Window* window)
    : window_(window)
    , device_(device)
{
  // Setup Dear ImGui context
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO& io = ImGui::GetIO();
  io.ConfigFlags |=
      ImGuiConfigFlags_NavEnableKeyboard;  // Enable Keyboard Controls
  io.ConfigFlags |=
      ImGuiConfigFlags_NavEnableGamepad;  // Enable Gamepad Controls
  // io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;  // IF using Docking
  // Branch

  // Setup Platform/Renderer backends
  ImGui_ImplSDL3_InitForSDLGPU(window);
  ImGui_ImplSDLGPU3_InitInfo init_info = {};
  init_info.Device = device;
  init_info.ColorTargetFormat =
      SDL_GetGPUSwapchainTextureFormat(device, window);
  init_info.MSAASamples =
      SDL_GPU_SAMPLECOUNT_1;  // Only used in multi-viewports mode.
  init_info.SwapchainComposition =
      SDL_GPU_SWAPCHAINCOMPOSITION_SDR;  // Only used in multi-viewports mode.
  init_info.PresentMode = SDL_GPU_PRESENTMODE_VSYNC;
  ImGui_ImplSDLGPU3_Init(&init_info);
}

Menu::~Menu()
{
  ImGui_ImplSDL3_Shutdown();
  ImGui_ImplSDLGPU3_Shutdown();
  ImGui::DestroyContext();
}

void Menu::Render()
{
  // Rendering
  // (Your code clears your framebuffer, renders your other stuff etc.)
  ImGui::Render();

  SDL_GPUTexture* swapchain_texture {nullptr};

  SDL_GPUCommandBuffer* command_buffer = SDL_AcquireGPUCommandBuffer(device_);
  SDL_WaitAndAcquireGPUSwapchainTexture(
      command_buffer, window_, &swapchain_texture, nullptr, nullptr);

  ImDrawData* draw_data = ImGui::GetDrawData();
  ImGui_ImplSDLGPU3_PrepareDrawData(draw_data, command_buffer);

  // Setup and start a render pass
  SDL_GPUColorTargetInfo target_info = {};
  target_info.texture = swapchain_texture;
  target_info.clear_color = SDL_FColor {0, 0, 0, 0};
  target_info.load_op = SDL_GPU_LOADOP_CLEAR;
  target_info.store_op = SDL_GPU_STOREOP_STORE;
  target_info.mip_level = 0;
  target_info.layer_or_depth_plane = 0;
  target_info.cycle = false;
  SDL_GPURenderPass* render_pass =
      SDL_BeginGPURenderPass(command_buffer, &target_info, 1, nullptr);

  // Render ImGui
  ImGui_ImplSDLGPU3_RenderDrawData(draw_data, command_buffer, render_pass);

  SDL_EndGPURenderPass(render_pass);
}
}  // namespace menu
