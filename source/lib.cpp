#include <format>
#include <iostream>

#include "lib.hpp"

#include <SDL3/SDL.h>
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_gpu.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_log.h>
#include <SDL3/SDL_surface.h>
#include <SDL3/SDL_video.h>
#include <fmt/core.h>

constexpr auto kWindowWidth = 1280;
constexpr auto kWindowHeight = 720;

GhouliesLib::GhouliesLib()
{
  if (!SDL_Init(SDL_INIT_VIDEO)) {
    std::cerr << std::format("SDL could not initialize! SDL_Error: {}",
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

  this->window_ = window;
  this->device_ = device;

  this->initialised_ = true;
}

GhouliesLib::~GhouliesLib()
{
  SDL_DestroyGPUDevice(this->device_);
  SDL_DestroyWindow(this->window_);

  SDL_Quit();

  this->initialised_ = false;
};

void GhouliesLib::UpdateFrame()
{
  // Hack to get window to stay up
  SDL_Event e;
  while (SDL_PollEvent(&e)) {
    if (e.type == SDL_EVENT_QUIT) {
      this->quit_ = true;
    }
  }
}
