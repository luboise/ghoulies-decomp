#pragma once

#include <cstdint>
#include <span>

#include "../ghoulies/model.hpp"
#include "../ghoulies/nd.hpp"

namespace graphics
{

class Model
{
public:
  /// Throws std::runtime_error on fail, creates Model otherwise
  explicit Model(const ghoulies::ModelAsset&);
  ~Model();
  Model& operator=(const Model&) = default;

  Model(const Model&) = delete;
  Model(Model&&) = delete;
  Model& operator=(Model&&) = delete;

private:
  ghoulies::ModelDescriptor descriptor_;
  std::span<uint8_t> span_;
};

}  // namespace graphics
