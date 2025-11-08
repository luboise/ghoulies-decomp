#pragma once

#include <filesystem>
#include <string>

#include "ghoulies/game.hpp"
#include "graphics/graphics.hpp"
#include "graphics/model.hpp"
#include "menu/menu.hpp"

class SDL_Window;
class SDL_GPUDevice;
class SDL_GPUShader;
class SDL_CommandBuffer;
class SDL_GPUGraphicsPipeline;

namespace ghoulies
{

struct GhouliesLibParams
{
  /// The directory which the game files are located in. If unspecified,
  /// cwd/gbtg will be used. eg. ghoulies_launcher/gbtg/bundles/whatever.bnl
  std::filesystem::path game_directory;
};

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
  static std::expected<void, std::string> Initialise(GhouliesLibParams params);

  [[nodiscard]] static bool Initialised() { return instance != nullptr; }

  ~GhouliesLib();

  auto& Menu() { return *this->menu_; }

  [[nodiscard]] bool ShouldQuit() const { return this->quit_; }

  void UpdateEvents();

  [[nodiscard]] const Asset* GetAsset(std::string_view asset_name) const
  {
    for (const auto& [filename, bnl_file] : this->bnl_files_) {
      if (const auto* ptr {bnl_file.GetAsset(asset_name)}; ptr != nullptr) {
        return ptr;
      }
    }

    return nullptr;
  }

  [[nodiscard]] const Asset* GetFirstAssetByType(AssetType asset_type) const
  {
    for (const auto& [filename, bnl_file] : this->bnl_files_) {
      if (const auto* ptr {bnl_file.GetFirstAssetByType(asset_type)};
          ptr != nullptr)
      {
        return ptr;
      }
    }

    return nullptr;
  }

  // void UpdateMenu();

  [[nodiscard]] ::graphics::DrawContext NewDrawContext();
  void EndDrawContext(::graphics::DrawContext ctx);

  void DrawScene(::graphics::DrawContext& ctx);
  void DrawTestModel(::graphics::Model& model,
                     const ::graphics::Texture& texture);

  void SetDefaultTexture(std::unique_ptr<::graphics::Texture>&& texture);

  void SetLighting(::graphics::LightingUniforms&& uniforms);

  std::expected<void, std::string> SetPlaycamScript(
      std::string_view playcam_aid);

  std::shared_ptr<::graphics::Model> LoadModel(const Asset&);
  std::unique_ptr<::graphics::Texture> LoadTexture(
      ::graphics::TextureAsset asset);

  [[nodiscard]] SDL_GPUDevice* SDLDevice() const { return this->device_; }

  /// Throws std::runtime_error if the instance is not initialised yet.
  static auto& Instance()
  {
    if (!GhouliesLib::Initialised()) {
      throw std::
          runtime_error(
              "Attempted to get GhouliesLib instance which hasn't been "
              "initialised " "yet.");
    }
    return *instance;
  }

  [[nodiscard]] auto& GameContext() { return this->game_context_; }

  GhouliesLib(const GhouliesLib&) = delete;
  GhouliesLib(GhouliesLib&&) = delete;
  GhouliesLib& operator=(const GhouliesLib&) = delete;
  GhouliesLib& operator=(GhouliesLib&&) = delete;

private:
  explicit GhouliesLib(const GhouliesLibParams& params);

  static std::unique_ptr<GhouliesLib> instance;

  [[nodiscard]] std::optional<std::filesystem::path> FindGameFile(
      std::string_view filename);
  [[nodiscard]] const Asset* FindPlaycamScript() const;

  std::expected<void, std::string> LoadBNLFile(std::filesystem::path bnl_path);

  bool quit_;

  std::string name_;

  std::unique_ptr<menu::Menu> menu_;

  SDL_Window* window_;

  SDL_GPUDevice* device_;
  SDL_GPUShader* pbr_vert_shader_;
  SDL_GPUShader* pbr_frag_shader_;
  SDL_GPUGraphicsPipeline* pbr_pipeline_;

  ::graphics::Camera camera_;
  ::graphics::LightingUniforms lighting_uniforms_;

  const bool* key_states_;

  std::unique_ptr<::graphics::Texture> default_texture_;
  SDL_GPUTexture* depth_texture_;

  std::filesystem::path game_directory_;
  ghoulies::GameContext game_context_;

  std::map<std::string, BNLFile> bnl_files_;
};

}  // namespace ghoulies
