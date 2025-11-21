#pragma once

#include <filesystem>
#include <map>
#include <string>

#include "game/logic.hpp"
#include "ghoulies/game.hpp"
#include "graphics/graphics.hpp"
#include "graphics/model.hpp"
#include "menu/menu.hpp"
#include "utils/file.hpp"

class SDL_Window;
class SDL_GPUDevice;
class SDL_GPUShader;
class SDL_CommandBuffer;
class SDL_GPUGraphicsPipeline;

namespace ghoulies
{
struct GhouliesExecutableData;

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
  static std::expected<void, std::string> Destroy();

  [[nodiscard]] static bool Initialised() { return instance != nullptr; }

  ~GhouliesLib();

  auto& Menu() { return *this->menu_; }

  [[nodiscard]] bool ShouldQuit() const { return this->quit_; }

  void UpdateEvents();

  [[nodiscard]] const Asset* GetAsset(std::string_view asset_name) const;
  [[nodiscard]] const Asset* GetFirstAssetByType(AssetType asset_type) const;

  // void UpdateMenu();

  void BeginFrame();
  void EndFrame();

  [[nodiscard]] ::graphics::DrawContext NewDrawContext();
  void EndDrawContext(::graphics::DrawContext&& ctx);
  void UpdateScene();

  void GameLoop(graphics::DrawContext& draw_ctx);

  void DrawTestModel(::graphics::Model& model,
                     const ::graphics::Texture& texture);

  void SetDefaultTexture(std::shared_ptr<::graphics::Texture>&& texture);
  void SetDefaultMaterial(std::shared_ptr<graphics::PBRMaterial>&& material);

  [[nodiscard]] const graphics::Model& GetSphereModel() const;

  void SetLighting(::graphics::LightingUniforms&& uniforms);

  std::expected<void, std::string> SetPlaycamScript(
      std::string_view playcam_aid);

  std::shared_ptr<::graphics::Model> LoadModel(const Asset&);
  std::shared_ptr<::graphics::Texture> LoadTexture(
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

  [[nodiscard]] auto& GameState() { return this->game_state_; }

  [[nodiscard]] const GhouliesExecutableData& ExecutableData();

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

  bool menu_active_ {false};
  bool toggle_menu_ {false};
  std::unique_ptr<menu::Menu> menu_;

  SDL_Window* window_;

  SDL_GPUDevice* device_;
  SDL_GPUShader* pbr_vert_shader_;
  SDL_GPUShader* pbr_frag_shader_;
  SDL_GPUGraphicsPipeline* pbr_pipeline_;

  ::graphics::LightingUniforms lighting_uniforms_;

  const bool* key_states_;

  std::shared_ptr<::graphics::Texture> default_texture_;
  std::shared_ptr<graphics::PBRMaterial> default_material_;

  SDL_GPUTexture* depth_texture_;

  std::filesystem::path game_directory_;
  ghoulies::GameContext game_context_;
  game::GameState game_state_;

  std::map<std::string, BNLFile> bnl_files_;

  std::unique_ptr<graphics::Model> sphere_model_;

  std::unique_ptr<utils::file::XBEStream> xbe_stream_;
  std::unique_ptr<GhouliesExecutableData> executable_data_;
};

}  // namespace ghoulies
