#include <algorithm>
#include <cassert>
#include <cstddef>
#include <cstring>
#include <iostream>
#include <memory>
#include <numeric>

#include "model.hpp"

#include <SDL3/SDL_gpu.h>
#include <SDL3/SDL_stdinc.h>

#include "../ghoulies/nd.hpp"
#include "graphics.hpp"

namespace graphics
{
using ghoulies::ModelAsset;
using ghoulies::NdNode;
using ghoulies::NdVertexBuffer;
using std::shared_ptr;

struct ModelDrawData
{
  SDL_GPUPrimitiveType primitive_type;
  std::vector<Index> indices;
  uint32_t material_index;
};

namespace
{
void FindDrawsFromNodeRecursive(const NdNode& node,
                                std::vector<ModelDrawData>& draws)
{
  if (node.nd_type == ghoulies::NdType::kPushBuffer) {
    const auto* push_buffer {(const ghoulies::NdPushBuffer*)&node};

    for (const auto& draw_data : push_buffer->draw_commands) {
      ModelDrawData new_draw_data {.material_index = draw_data.material_index};

      switch (draw_data.primitive_type) {
        case d3d::D3DPrimitiveType::kPointList:
          new_draw_data.primitive_type = SDL_GPU_PRIMITIVETYPE_POINTLIST;
          break;
        case d3d::D3DPrimitiveType::kLineList:
          new_draw_data.primitive_type = SDL_GPU_PRIMITIVETYPE_LINELIST;
          break;
        case d3d::D3DPrimitiveType::kLineStrip:
          new_draw_data.primitive_type = SDL_GPU_PRIMITIVETYPE_LINESTRIP;
          break;
        case d3d::D3DPrimitiveType::kTriangleList:
          new_draw_data.primitive_type = SDL_GPU_PRIMITIVETYPE_TRIANGLELIST;
          break;
        case d3d::D3DPrimitiveType::kTriangleStrip:
          new_draw_data.primitive_type = SDL_GPU_PRIMITIVETYPE_TRIANGLESTRIP;
          break;

        case d3d::D3DPrimitiveType::kTriangleFan: {
          std::size_t num_triangles {draw_data.indices.size() - 2};
          std::size_t num_indices {num_triangles * 3};

          new_draw_data.primitive_type = SDL_GPU_PRIMITIVETYPE_TRIANGLELIST;
          new_draw_data.indices = std::vector<Index>(num_indices);
          new_draw_data.material_index = draw_data.material_index;

          Index root_index {draw_data.indices[0]};

          for (std::size_t i {1}; i < draw_data.indices.size() - 1; i++) {
            new_draw_data.indices[3 * (i - 1)] = root_index;
            new_draw_data.indices[(3 * (i - 1)) + 1] = draw_data.indices[i];
            new_draw_data.indices[(3 * (i - 1)) + 2] = draw_data.indices[i + 1];
          }

          draws.push_back(std::move(new_draw_data));
          continue;
        }
          // Unsupported primitive types
        case d3d::D3DPrimitiveType::kNone:
        case d3d::D3DPrimitiveType::kMax:
        case d3d::D3DPrimitiveType::kInvalid:
        case d3d::D3DPrimitiveType::kLineLoop:
        case d3d::D3DPrimitiveType::kQuadList:
        case d3d::D3DPrimitiveType::kQuadStrip:
        case d3d::D3DPrimitiveType::kPolygon:
        default:
          std::cerr << "Unsupported D3DPrimitive type found: "
                    << draw_data.primitive_type
                    << ". Using triangle list instead.\n";
          // TODO: Return std::unexpected
          new_draw_data.primitive_type = SDL_GPU_PRIMITIVETYPE_TRIANGLELIST;
          break;
      }

      new_draw_data.indices = draw_data.indices;
      draws.push_back(new_draw_data);
    }
  }

  if (node.next_child != nullptr) {
    FindDrawsFromNodeRecursive(*node.next_child, draws);
  }
  if (node.next_sibling != nullptr) {
    FindDrawsFromNodeRecursive(*node.next_sibling, draws);
  }
}

inline std::vector<ModelDrawData> FindDrawsFromNode(const NdNode& node)
{
  std::vector<ModelDrawData> draws;
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

  std::vector<ModelDrawData> draw_data {FindDrawsFromNode(*nd_vertex_buffer)};
  std::cout << "Found " << draw_data.size() << " sets of model draw data.\n";

  std::size_t total_index_count {
      std::accumulate(draw_data.begin(),
                      draw_data.end(),
                      std::size_t {0},
                      [](std::size_t acc, const ModelDrawData& draw_call)
                      { return acc + draw_call.indices.size(); })};

  std::vector<Index> indices(total_index_count);

  std::size_t cur {0};

  std::vector<DrawCommand> draw_commands(draw_data.size());
  for (std::size_t i {0}; i < draw_data.size(); i++) {
    const auto& draw_call {draw_data[i]};
    std::ranges::copy(draw_call.indices, &indices[cur]);

    draw_commands[i] = {
        .primitive_type = draw_call.primitive_type,
        .first_index = static_cast<Uint32>(cur),
        .num_indices = static_cast<Uint32>(draw_call.indices.size()),
        .material_index = draw_call.material_index};

    cur += draw_call.indices.size();
  }

  this->draw_commands_ = std::move(draw_commands);

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

  if (auto uv_buf_view {nd_vertex_buffer->GetBufferView(
          ghoulies::NdVertexBufferViewType::kUV)};
      uv_buf_view.has_value())
  {
    auto* uv_view {std::move(uv_buf_view).value()};
    assert(uv_view->stride == sizeof(float) * 2);

    const std::size_t values_per_uv {uv_view->stride / sizeof(float)};

    const std::size_t num_uv_vertices {uv_view->size / uv_view->stride};
    const std::size_t num_uv_floats {num_uv_vertices * values_per_uv};

    std::vector<float> uv_values(num_uv_floats);

    std::memcpy(uv_values.data(),
                &nd_vertex_buffer->vertex_buffer_bytes[uv_view->start_ptr],
                sizeof(float) * num_uv_floats);

    for (std::size_t i {0}; i < num_uv_vertices; i++) {
      for (int j {0}; j < values_per_uv; j++) {
        pbr_vertices[i].a_texcoords[j] = uv_values[(i * 2) + j];
      }
    }
  }

  std::cout << "Num processed vertices: " << pbr_vertices.size() << "\n";

  std::span<const PBRVertex> pbr_span {pbr_vertices};

  auto vertex_buffer {CreateVertexBuffer(device, pbr_span)};
  if (!vertex_buffer.has_value()) {
    throw std::runtime_error("Unable to create vertex buffer for model.");
  }

  this->vertex_buffer_ = std::move(vertex_buffer).value();

  auto index_buffer {CreateIndexBuffer(device, indices)};
  if (!index_buffer.has_value()) {
    throw std::runtime_error("Unable to create index buffer for model.");
  }
  this->index_buffer_ = std::move(index_buffer).value();

  // Allocate one big index buffer
  // Cache the draw call

  for (const TextureAsset& texture : asset.textures) {
    try {
      PBRMaterial new_material {device,
                                PBRMaterialParams {.diffuse_texture = texture}};

      this->materials_.push_back(std::move(new_material));

    } catch (std::runtime_error& e) {
      throw e;
    }
  }
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

  for (const auto& command : this->draw_commands_) {
    // TODO: Check the pipeline matches

    const auto& material {materials_[command.material_index]};

    const auto* diffuse {material.DiffuseTexture()};

    if (diffuse != nullptr) {
      std::array bindings {diffuse->SDLBinding()};
      SDL_BindGPUFragmentSamplers(
          render_pass, 0, bindings.data(), bindings.size());
    }

    SDL_DrawGPUIndexedPrimitives(
        render_pass, command.num_indices, 1, command.first_index, 0, 0);
  }
};

}  // namespace graphics
