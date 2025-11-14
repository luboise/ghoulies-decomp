#include <algorithm>
#include <cassert>
#include <cstddef>
#include <cstring>
#include <expected>
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
using ghoulies::Bytes;
using ghoulies::ModelAsset;
using ghoulies::NdNode;
using ghoulies::NdVertexBuffer;
using std::shared_ptr;

struct ModelDrawData
{
  SDL_GPUPrimitiveType primitive_type;
  std::vector<Index> indices;
  uint32_t material_index;

  std::size_t vertices_index {0};
  std::size_t indices_index {0};
};

namespace
{

void FindDrawsFromNodeRecursive(const NdNode& node,
                                std::vector<ModelDrawData>& draws,
                                const ModelParams& params)
{
  // TODO: Separate out BG push buffer
  if (node.nd_type == ghoulies::NdType::PushBuffer
      || node.nd_type == ghoulies::NdType::BGPushBuffer)
  {
    const auto* push_buffer {(const ghoulies::NdPushBuffer*)&node};

    for (const auto& push_buffer_draw : push_buffer->draws) {
      ModelDrawData new_draw_data {
          .primitive_type = SDL_GPU_PRIMITIVETYPE_TRIANGLELIST,
          .indices {},
          .material_index = push_buffer_draw.material_index,
          .vertices_index = params.current_vertex_count,
          .indices_index = params.current_index_count};

      switch (push_buffer_draw.primitive_type) {
        case d3d::D3DPrimitiveType::PointList:
          new_draw_data.primitive_type = SDL_GPU_PRIMITIVETYPE_POINTLIST;
          break;
        case d3d::D3DPrimitiveType::LineList:
          new_draw_data.primitive_type = SDL_GPU_PRIMITIVETYPE_LINELIST;
          break;
        case d3d::D3DPrimitiveType::LineStrip:
          new_draw_data.primitive_type = SDL_GPU_PRIMITIVETYPE_LINESTRIP;
          break;
        case d3d::D3DPrimitiveType::TriangleList:
          new_draw_data.primitive_type = SDL_GPU_PRIMITIVETYPE_TRIANGLELIST;
          break;
        case d3d::D3DPrimitiveType::TriangleStrip: {
          std::size_t num_triangles {push_buffer_draw.indices.size() - 2};
          std::size_t num_indices {num_triangles * 3};

          new_draw_data.primitive_type = SDL_GPU_PRIMITIVETYPE_TRIANGLELIST;
          new_draw_data.indices = std::vector<Index>(num_indices);
          new_draw_data.material_index = push_buffer_draw.material_index;

          for (std::size_t i {0}; i < push_buffer_draw.indices.size() - 2; i++)
          {
            // Reverse winding for odd triangles
            const std::size_t offset = (i % 2 == 1) ? 1 : 0;

            new_draw_data.indices[3 * i] = push_buffer_draw.indices[i + offset];
            new_draw_data.indices[(3 * i) + 1] =
                push_buffer_draw.indices[i + 1 - offset];
            new_draw_data.indices[(3 * i) + 2] =
                push_buffer_draw.indices[i + 2];
          }

          draws.push_back(std::move(new_draw_data));
          continue;
        }

        case d3d::D3DPrimitiveType::TriangleFan: {
          std::size_t num_triangles {push_buffer_draw.indices.size() - 2};
          std::size_t num_indices {num_triangles * 3};

          new_draw_data.primitive_type = SDL_GPU_PRIMITIVETYPE_TRIANGLELIST;
          new_draw_data.indices = std::vector<Index>(num_indices);
          new_draw_data.material_index = push_buffer_draw.material_index;

          Index root_index {push_buffer_draw.indices[0]};

          for (std::size_t i {1}; i < push_buffer_draw.indices.size() - 1; i++)
          {
            new_draw_data.indices[3 * (i - 1)] = root_index;
            new_draw_data.indices[(3 * (i - 1)) + 1] =
                push_buffer_draw.indices[i];
            new_draw_data.indices[(3 * (i - 1)) + 2] =
                push_buffer_draw.indices[i + 1];
          }

          draws.push_back(std::move(new_draw_data));
          continue;
        }
          // Unsupported primitive types
        case d3d::D3DPrimitiveType::None:
        case d3d::D3DPrimitiveType::Max:
        case d3d::D3DPrimitiveType::Invalid:
        case d3d::D3DPrimitiveType::LineLoop:
        case d3d::D3DPrimitiveType::QuadList:
        case d3d::D3DPrimitiveType::QuadStrip:
        case d3d::D3DPrimitiveType::Polygon:
        default:
          std::cerr << "Unsupported D3DPrimitive type found: "
                    << push_buffer_draw.primitive_type
                    << ". Using triangle list instead.\n";
          // TODO: Return std::unexpected
          new_draw_data.primitive_type = SDL_GPU_PRIMITIVETYPE_TRIANGLELIST;
          break;
      }

      new_draw_data.indices = push_buffer_draw.indices;
      draws.push_back(new_draw_data);
    }
  }

  if (node.next_child != nullptr) {
    FindDrawsFromNodeRecursive(*node.next_child, draws, params);
  }
  if (node.next_sibling != nullptr) {
    FindDrawsFromNodeRecursive(*node.next_sibling, draws, params);
  }
}

inline std::vector<ModelDrawData> FindDrawsFromNode(const NdNode& node,
                                                    const ModelParams& params)
{
  std::vector<ModelDrawData> draws;
  FindDrawsFromNodeRecursive(node, draws, params);

  return draws;
}

}  // namespace

void NdNodeToModelParams(std::shared_ptr<NdNode> root_node, ModelParams& params)
{
  if (root_node->nd_type == ghoulies::NdType::VertexBuffer) {
    std::cout << "Found new vertex buffer.\n";

    auto nd_vertex_buffer {
        std::static_pointer_cast<const NdVertexBuffer>(root_node)};
    if (nd_vertex_buffer == nullptr) {
      throw std::runtime_error("No vertex buffer available.");
    }

    auto vertices_opt {nd_vertex_buffer->GetBufferView(
        ghoulies::NdVertexBufferViewType::Vertex)};
    if (!vertices_opt.has_value()) {
      throw std::runtime_error("No vertices in model resource views.");
    }

    const ghoulies::NdVertexBufferView* vertices_view =
        std::move(vertices_opt).value();

    // 12 = sizeof packed vec3
    if (vertices_view->stride != 12) {
      throw std::runtime_error(
          "Vertices exist, but don't have a stride of 12.");
    }

    auto num_vertices {vertices_view->size / vertices_view->stride};

    // Create vertices
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
            ghoulies::NdVertexBufferViewType::UV)};
        uv_buf_view.has_value())
    {
      const auto* uv_view {std::move(uv_buf_view).value()};
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

      std::cout << "Vertex buffer size: "
                << nd_vertex_buffer->vertex_buffer_bytes.size() << "\n";

      std::vector<ModelDrawData> draw_data {
          FindDrawsFromNode(*nd_vertex_buffer, params)};
      std::cout << "Found " << draw_data.size()
                << " sets of model draw data.\n";

      std::size_t total_index_count {
          std::accumulate(draw_data.begin(),
                          draw_data.end(),
                          std::size_t {0},
                          [](std::size_t acc, const ModelDrawData& draw_call)
                          { return acc + draw_call.indices.size(); })};

      std::vector<Index> indices(total_index_count);

      // Create the draw commands
      {
        auto first_vertex {static_cast<Uint32>(params.current_vertex_count)};
        std::size_t cur {params.current_index_count};

        for (std::size_t i {0}; i < draw_data.size(); i++) {
          const auto& draw_call {draw_data[i]};
          std::ranges::copy(draw_call.indices, &indices[cur]);

          params.draw_commands.emplace_back(DrawCommand {
              .primitive_type = draw_call.primitive_type,
              .first_vertex = first_vertex,
              .first_index = static_cast<Uint32>(cur),
              .num_indices = static_cast<Uint32>(draw_call.indices.size()),
              .material_index = draw_call.material_index});

          cur += draw_call.indices.size();
        }
      }

      params.pbr_vertices.insert(
          params.pbr_vertices.end(), pbr_vertices.begin(), pbr_vertices.end());
      params.current_vertex_count += pbr_vertices.size();

      params.current_index_count += indices.size();
      params.pbr_indices.insert(
          params.pbr_indices.end(), indices.begin(), indices.end());
    }
  } else {
    if (root_node->next_child != nullptr) {
      NdNodeToModelParams(root_node->next_child, params);
      // std::cout << "Parsing child.\n";
    }
  }
  if (root_node->next_sibling != nullptr) {
    // std::cout << "Parsing sibling.\n";
    NdNodeToModelParams(root_node->next_sibling, params);
  }
}

Model::Model(SDL_GPUDevice* device, const ModelAsset& asset)
{
  // Transform vertices

  std::cout << "Loading model \"" << asset.model_aid << "\".\n";

  if (asset.root_nodes.empty()) {
    throw std::runtime_error("Unable to create model from 0 root nodes.");
  }

  ModelParams new_model_params {};

  for (auto root_node : asset.root_nodes) {
    NdNodeToModelParams(std::move(root_node), new_model_params);
  }

  this->draw_commands_ = std::move(new_model_params.draw_commands);

  // std::cout << "Num processed vertices: " << pbr_vertices.size() << "\n";

  // Create all of the resources here

  std::span<const PBRVertex> vert_span {new_model_params.pbr_vertices};

  auto vertex_buffer {CreateVertexBuffer(device, vert_span)};
  if (!vertex_buffer.has_value()) {
    throw std::runtime_error("Unable to create vertex buffer for model.");
  }
  this->vertex_buffer_ = std::move(vertex_buffer).value();

  auto index_buffer {CreateIndexBuffer(device, new_model_params.pbr_indices)};
  if (!index_buffer.has_value()) {
    throw std::runtime_error("Unable to create index buffer for model.");
  }
  this->index_buffer_ = std::move(index_buffer).value();

  for (const TextureAsset& texture : asset.textures) {
    try {
      this->materials_.emplace_back(std::make_shared<PBRMaterial>(
          device,
          PBRMaterialParams {.base_colour = glm::vec4 {1.0F, 1.0F, 1.0F, 1.0F},
                             .diffuse_texture = texture}));

    } catch (std::runtime_error& e) {
      throw e;
    }
  }

  // TODO: Process this once more information is known
  this->collider0x4s_float_ = asset.colliders_0x4_float;
  this->collider0x4s_ = asset.colliders_0x4;
}

Model::Model(SDL_GPUDevice* device,
             const ModelParams& params,
             std::span<std::shared_ptr<PBRMaterial>> materials)
    : device_(device)
    , descriptor_({})
    , draw_commands_(params.draw_commands)
{
  this->materials_ = std::vector(materials.begin(), materials.end());

  // std::cout << "Num processed vertices: " << pbr_vertices.size() << "\n";

  // Create all of the resources here

  std::span<const PBRVertex> vert_span {params.pbr_vertices};

  auto vertex_buffer {CreateVertexBuffer(device, vert_span)};
  if (!vertex_buffer.has_value()) {
    throw std::runtime_error("Unable to create vertex buffer for model.");
  }
  this->vertex_buffer_ = std::move(vertex_buffer).value();

  auto index_buffer {CreateIndexBuffer(device, params.pbr_indices)};
  if (!index_buffer.has_value()) {
    throw std::runtime_error("Unable to create index buffer for model.");
  }
  this->index_buffer_ = std::move(index_buffer).value();
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
    // TODO: Check that material is in bounds
    materials_[command.material_index]->Bind(render_pass);

    SDL_DrawGPUIndexedPrimitives(render_pass,
                                 command.num_indices,
                                 command.first_vertex,
                                 command.first_index,
                                 0,
                                 0);
  }
}

void Model::DrawWithTransform(DrawContext& ctx,
                              const Transform& transform) const
{
  std::array<SDL_GPUBufferBinding, 1> vb_bindings {vertex_buffer_.GetBinding()};

  SDL_BindGPUVertexBuffers(ctx.render_pass, 0, vb_bindings.data(), 1);

  auto ib_binding {index_buffer_.GetBinding()};

  // SDL_Log("Binding index buffer.");
  SDL_BindGPUIndexBuffer(
      ctx.render_pass, &ib_binding, SDL_GPU_INDEXELEMENTSIZE_16BIT);

  ModelUniforms uniforms {.model = transform.ModelMatrix()};
  ctx.SetModelUniforms(uniforms);

  assert(!this->draw_commands_.empty());

  for (const auto& command : this->draw_commands_) {
    assert(!materials_.empty());

    if (command.material_index >= materials_.size()) {
      throw std::runtime_error(std::format(
          "Material at index {} out of bounds (only {} materials available)",
          command.material_index,
          materials_.size()));
    }

    assert(!materials_.empty());
    const auto& material {materials_[command.material_index]};

    const auto* diffuse {material->DiffuseTexture()};

    if (diffuse != nullptr) {
      std::array bindings {diffuse->SDLBinding()};
      SDL_BindGPUFragmentSamplers(
          ctx.render_pass, 0, bindings.data(), bindings.size());
    }

    SDL_DrawGPUIndexedPrimitives(
        ctx.render_pass, command.num_indices, 1, command.first_index, 0, 0);
  }

  if (ctx.draw_colliders) {
    if (!this->collider0x4s_.empty()) {
      std::cout << "Drawing colliders for model.\n";

      for (const auto& collider : this->collider0x4s_) {
        graphics::DrawSphere(
            ctx,
            {collider.position[0], collider.position[1], collider.position[2]},
            collider.radius);
      }
    }
  }
}

}  // namespace graphics
