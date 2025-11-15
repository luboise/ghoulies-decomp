#pragma once

#include <SDL3/SDL.h>

namespace ghoulies
{
struct GameContext;
}  // namespace ghoulies

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
  void Render(graphics::DrawContext& draw_ctx, ghoulies::GameContext& game_ctx);

  void NewFrame();

  void ProcessEvent(SDL_Event* event);

private:
  SDL_Window* window_;
  SDL_GPUDevice* device_;
};

};  // namespace menu
