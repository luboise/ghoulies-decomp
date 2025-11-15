#pragma once

#include <SDL3/SDL.h>

namespace graphics
{
struct DrawContext;
}  // namespace graphics

namespace menu
{

class Menu
{
public:
  Menu(SDL_GPUDevice* device, SDL_Window* window);
  ~Menu();
  void Render(graphics::DrawContext&);

  void NewFrame();

  void ProcessEvent(SDL_Event* event);

private:
  SDL_Window* window_;
  SDL_GPUDevice* device_;
};

};  // namespace menu
