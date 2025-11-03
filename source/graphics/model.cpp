#include <cstring>
#include <memory>

#include "model.hpp"

#include <SDL3/SDL_stdinc.h>

namespace graphics
{
using ghoulies::kVertexBuffer;
using ghoulies::ModelAsset;
using ghoulies::NdNode;
using ghoulies::NdVertexBuffer;
using std::shared_ptr;

/*
Model::Model(ghoulies::ModelDescriptor descriptor, std::span<uint8_t> bytes)
: descriptor_(descriptor)
, span(bytes)
{
}
*/

Model::Model(SDL_GPUDevice* device, const ModelAsset& asset)
{
  // Transform vertices

  shared_ptr<NdNode> next_child {asset.root_nodes[0]->next_child};
  shared_ptr<NdVertexBuffer> nd_vertex_buffer {
      std::static_pointer_cast<NdVertexBuffer>(std::move(next_child))};

  // auto vb {std::shared_ptr<NdVertexBuffer> {next_child}};

  if (nd_vertex_buffer == nullptr) {
    throw std::runtime_error("No vertex buffer available.");
  }

  if (nd_vertex_buffer->nd_type != ghoulies::NdType::kVertexBuffer) {
    throw std::runtime_error(
        "Nd vertex buffer node does not have vertex buffer type.");
  }

  // auto vertex_buffer {CreateVertexBuffer(device, )};

  // TODO: Check command buffer is not null
  // auto* command_buffer = SDL_AcquireGPUCommandBuffer(this->device_);

  // Allocate one big index buffer
  // Cache the draw call

  // TODO: Materials
}

Model::~Model() {}

}  // namespace graphics
