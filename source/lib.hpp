#pragma once

#include <string>

class SDL_Window;
class SDL_GPUDevice;

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

  GhouliesLib(const GhouliesLib&) = default;
  GhouliesLib(GhouliesLib&&) = delete;
  GhouliesLib& operator=(const GhouliesLib&) = default;
  GhouliesLib& operator=(GhouliesLib&&) = delete;

  ~GhouliesLib();

  [[nodiscard]] bool Initialised() const { return this->initialised_; };

  [[nodiscard]] bool ShouldQuit() const { return this->quit_; }

  void UpdateFrame();

private:
  bool initialised_ {false};
  bool quit_ {false};

  std::string name_;
  SDL_Window* window_;
  SDL_GPUDevice* device_;
};
