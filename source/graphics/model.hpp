#pragma once

#include <cstdint>
#include <span>

#include "../ghoulies/nd.hpp"

namespace graphics
{

class Model
{
public:
  // Model(const Model&) = default;
  // Model(ghoulies::ModelDescriptor descriptor, std::span<uint8_t> span);

  ~Model();
  Model(Model&&) = delete;
  Model& operator=(const Model&) = default;
  Model& operator=(Model&&) = delete;

  static std::expected<Model, std::string> FromBytes(std::span<uint8_t> bytes);

private:
  ghoulies::ModelDescriptor descriptor_;
  std::span<uint8_t> span_;
};

}  // namespace graphics
