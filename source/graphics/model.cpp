#include <cstring>

#include "model.hpp"

#include <SDL3/SDL_stdinc.h>

#include "../ghoulies/nd.hpp"

namespace graphics
{
using ghoulies::ModelDescriptor;

/*
Model::Model(ghoulies::ModelDescriptor descriptor, std::span<uint8_t> bytes)
: descriptor_(descriptor)
, span(bytes)
{
}
*/

std::expected<Model, std::string> Model::FromBytes(std::span<uint8_t> bytes)
{
  ModelDescriptor descriptor {};

  std::memcpy(&descriptor, bytes.data(), sizeof(ModelDescriptor));
}

Model::~Model()
{
  if (span_.data() != nullptr) {
    SDL_free(span_.data());
  }
}

}  // namespace graphics
