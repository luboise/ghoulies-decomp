#include <algorithm>

#include "game.hpp"

namespace ghoulies
{

[[nodiscard]] const Asset* GameContext::GetPlaycamScript() const
{
  const auto& playcam {std::ranges::find_if(
      this->bnl_files,
      [](const auto& pair) { return pair.first.contains("playcam"); })};

  if (playcam == this->bnl_files.end()) {
    return nullptr;
  }

  return playcam->second.GetFirstAssetByType(AssetType::ResScript);
}

std::expected<void, std::string> GameContext::InitialiseFromMarker(
    const Marker& marker)
{
  static const auto kVisitor = Overload {
      [this](const WeaponMarker& weapon_marker)
      {
        auto model_name {std::string(weapon_marker.objparams_aid.data())};

        std::cout << "Loading weapon \"" << model_name << "\" from marker.\n";

        auto objparams_index {model_name.find("objparams")};

        if (objparams_index == std::string::npos) {
          std::cerr << "Objparams asset ID \"" << model_name.data()
                    << "\" does not contain objparams. Unable to get model.\n";
          return;
        }

        model_name.replace(objparams_index, 9, "model");

        const auto* model_asset {this->GetAsset(model_name)};

        if (model_asset == nullptr) {
          std::cerr << "Failed to get model from objparams \""
                    << weapon_marker.objparams_aid.data() << "\".\n";
          return;
        }

        try {
          objects::Weapon::WeaponParams params {};
          params.model_aid = model_name;

          this->weapons.push_back(std::make_shared<objects::Weapon>(params));
        } catch (std::runtime_error& e) {
          std::cerr << "Failed to create weapon from AID " << model_name
                    << ". Error: " << e.what() << "\n";
        }
      },
      [](const RawMarkerEntry&) {},
  };

  for (const MarkerEntry& entry : marker.Entries()) {
    std::visit(kVisitor, entry);
  }

  return {};
}

}  // namespace ghoulies
