#pragma once

#include <string>

#include "graphics/graphics.hpp"
#include "graphics/model.hpp"

class SDL_Window;
class SDL_GPUDevice;
class SDL_GPUShader;
class SDL_CommandBuffer;
class SDL_GPUGraphicsPipeline;

/**
 * @brief The core implementation of the executable
 *
 * This class makes up the library part of the executable, which means that the
 * main logic is implemented here. This kind of separation makes it easy to
 * test the implementation for the executable, because the logic is nicely
 * separated from the command-line logic implemented in the main function.
 */
struct GhouliesLib
{
  GhouliesLib();

  GhouliesLib(const GhouliesLib&) = delete;
  GhouliesLib(GhouliesLib&&) = delete;
  GhouliesLib& operator=(const GhouliesLib&) = delete;
  GhouliesLib& operator=(GhouliesLib&&) = delete;

  ~GhouliesLib();

  [[nodiscard]] bool Initialised() const { return this->initialised_; }

  [[nodiscard]] bool ShouldQuit() const { return this->quit_; }

  void UpdateEvents();

  [[nodiscard]] graphics::DrawContext NewDrawContext();
  void EndDrawContext(graphics::DrawContext ctx);

  void DrawTestObjects(const graphics::Texture& texture);
  void DrawTestModel(graphics::Model& model, const graphics::Texture& texture);

  void SetDefaultTexture(std::unique_ptr<graphics::Texture>&& texture);

  std::shared_ptr<graphics::Model> LoadModel(const ghoulies::Asset&);
  std::unique_ptr<graphics::Texture> LoadTexture(graphics::TextureAsset asset);

  [[nodiscard]] SDL_GPUDevice* GetSDLDevice() const { return this->device_; }

private:
  bool initialised_;
  bool quit_;

  std::string name_;

  SDL_Window* window_;

  SDL_GPUDevice* device_;
  SDL_GPUShader* pbr_vert_shader_;
  SDL_GPUShader* pbr_frag_shader_;
  SDL_GPUGraphicsPipeline* pbr_pipeline_;

  graphics::Camera camera_;

  const bool* key_states_;

  std::unique_ptr<graphics::Texture> default_texture_;

  // SDL_CommandBuffer* command_buffer_;
};
