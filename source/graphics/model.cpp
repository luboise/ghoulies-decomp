#include <cassert>
#include <cstring>
#include <iostream>
#include <memory>

#include "model.hpp"

#include <SDL3/SDL_gpu.h>
#include <SDL3/SDL_stdinc.h>

#include "graphics.hpp"

namespace graphics
{
using ghoulies::kVertexBuffer;
using ghoulies::ModelAsset;
using ghoulies::NdNode;
using ghoulies::NdVertexBuffer;
using std::shared_ptr;

struct ModelDrawCall
{
  SDL_GPUPrimitiveType primitive_type;
  std::vector<Index> indices;
};

namespace
{
void FindDrawsFromNodeRecursive(const NdNode& node,
                                std::vector<ModelDrawCall>& draws)
{
  if (node.nd_type == ghoulies::NdType::kPushBuffer) {
    const auto* push_buffer {(const ghoulies::NdPushBuffer*)&node};

    for (const auto& draw_command : push_buffer->draw_commands) {
      SDL_GPUPrimitiveType primitive_type {};

      switch (draw_command.primitive_type) {
        case d3d::D3DPrimitiveType::kPointList:
          primitive_type = SDL_GPU_PRIMITIVETYPE_POINTLIST;
          break;
        case d3d::D3DPrimitiveType::kLineList:
          primitive_type = SDL_GPU_PRIMITIVETYPE_LINELIST;
          break;
        case d3d::D3DPrimitiveType::kLineStrip:
          primitive_type = SDL_GPU_PRIMITIVETYPE_LINESTRIP;
          break;
        case d3d::D3DPrimitiveType::kTriangleList:
          primitive_type = SDL_GPU_PRIMITIVETYPE_TRIANGLELIST;
          break;
        case d3d::D3DPrimitiveType::kTriangleStrip:
          primitive_type = SDL_GPU_PRIMITIVETYPE_TRIANGLESTRIP;
          break;

          // Unsupported primitive types
        case d3d::D3DPrimitiveType::kNone:
        case d3d::D3DPrimitiveType::kMax:
        case d3d::D3DPrimitiveType::kInvalid:
        case d3d::D3DPrimitiveType::kLineLoop:
        case d3d::D3DPrimitiveType::kTriangleFan:
        case d3d::D3DPrimitiveType::kQuadList:
        case d3d::D3DPrimitiveType::kQuadStrip:
        case d3d::D3DPrimitiveType::kPolygon:
        default:
          // TODO: Return std::unexpected
          primitive_type = SDL_GPU_PRIMITIVETYPE_TRIANGLELIST;
          break;
      }

      draws.emplace_back(primitive_type, draw_command.indices);
    }
  }

  if (node.next_child != nullptr) {
    FindDrawsFromNodeRecursive(*node.next_child, draws);
  }
  if (node.next_sibling != nullptr) {
    FindDrawsFromNodeRecursive(*node.next_sibling, draws);
  }
}

inline std::vector<ModelDrawCall> FindDrawsFromNode(const NdNode& node)
{
  std::vector<ModelDrawCall> draws;
  FindDrawsFromNodeRecursive(node, draws);

  return draws;
}
}  // namespace

Model::Model(SDL_GPUDevice* device, const ModelAsset& asset)
{
  // Transform vertices

  shared_ptr<NdNode> next_child {asset.root_nodes[0]->next_child};

  shared_ptr<NdVertexBuffer> nd_vertex_buffer {
      std::static_pointer_cast<NdVertexBuffer>(std::move(next_child))};

  std::cout << "Vertex buffer size: "
            << nd_vertex_buffer->vertex_buffer_bytes.size() << "\n";

  // auto vb {std::shared_ptr<NdVertexBuffer> {next_child}};

  std::vector<ModelDrawCall> draw_calls {FindDrawsFromNode(*nd_vertex_buffer)};

  std::cout << "Found " << draw_calls.size() << " draw calls.\n";

  if (nd_vertex_buffer == nullptr) {
    throw std::runtime_error("No vertex buffer available.");
  }

  if (nd_vertex_buffer->nd_type != ghoulies::NdType::kVertexBuffer) {
    throw std::runtime_error(
        "Nd vertex buffer node does not have vertex buffer type.");
  }

  auto vertices_opt {nd_vertex_buffer->GetBufferView(
      ghoulies::NdVertexBufferViewType::kVertex)};

  if (!vertices_opt.has_value()) {
    throw std::runtime_error("No vertices in model resource views.");
  }

  ghoulies::NdVertexBufferView* vertices_view = std::move(vertices_opt).value();

  // 12 = sizeof packed vec3
  if (vertices_view->stride != 12) {
    throw std::runtime_error("Vertices exist, but don't have a stride of 12.");
  }

  auto num_vertices {vertices_view->size / vertices_view->stride};

  std::vector<PBRVertex> pbr_vertices {};

  for (std::size_t i {0}; i < num_vertices; i++) {
    std::array<float, 3> pos {};

    std::memcpy(
        pos.data(),
        &nd_vertex_buffer->vertex_buffer_bytes[vertices_view->start_ptr
                                               + (i * 3 * sizeof(float))],
        sizeof(pos));

    pbr_vertices.emplace_back(glm::vec3 {pos[0], pos[1], pos[2]});
  }

  std::cout << "Num processed vertices: " << pbr_vertices.size() << "\n";

  std::span<const PBRVertex> pbr_span {pbr_vertices};

  auto vertex_buffer {CreateVertexBuffer(device, pbr_span)};
  if (!vertex_buffer.has_value()) {
    throw std::runtime_error("Unable to create vertex buffer for model.");
  }

  this->vertex_buffer_ = std::move(vertex_buffer).value();

  const std::vector<Index> indices {0, 1, 2};

  auto index_buffer {CreateIndexBuffer(device, indices)};
  if (!index_buffer.has_value()) {
    throw std::runtime_error("Unable to create index buffer for model.");
  }
  this->index_buffer_ = std::move(index_buffer).value();

  // Allocate one big index buffer
  // Cache the draw call

  // TODO: Materials
}

Model::~Model() = default;

void Model::DrawBasic(SDL_GPURenderPass* render_pass)
{
  // SDL_Log("Binding vertex buffers.");
  std::array<SDL_GPUBufferBinding, 1> vb_bindings {vertex_buffer_.GetBinding()};

  SDL_BindGPUVertexBuffers(render_pass, 0, vb_bindings.data(), 1);

  auto ib_binding {index_buffer_.GetBinding()};

  // SDL_Log("Binding index buffer.");
  SDL_BindGPUIndexBuffer(
      render_pass, &ib_binding, SDL_GPU_INDEXELEMENTSIZE_16BIT);

  // SDL_DrawGPUIndexedPrimitives(
  // render_pass, this->index_buffer_.count, 1, 0, 0, 0);

  SDL_DrawGPUIndexedPrimitives(render_pass, 3, 1, 0, 0, 0);
};

}  // namespace graphics
