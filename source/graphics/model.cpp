#include <cstring>

#include "model.hpp"

#include <SDL3/SDL_stdinc.h>

namespace graphics
{
using ghoulies::ModelAsset;

/*
Model::Model(ghoulies::ModelDescriptor descriptor, std::span<uint8_t> bytes)
: descriptor_(descriptor)
, span(bytes)
{
}
*/

Model::Model(const ModelAsset& asset)
{
  // ModelDescriptor descriptor {};

  // std::memcpy(&descriptor, bytes.data(), sizeof(ModelDescriptor));
}

Model::~Model() {}

}  // namespace graphics
