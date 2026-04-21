#include <nova/graphics/mesh_data.h>

namespace nova::graphics
{

MeshData MeshData::create_quad()
{
  MeshData mesh_data;

  // clang-format off
  mesh_data.vertices() = {
      {{-1.0f, -1.0f, 0.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}},
      {{1.0f, -1.0f, 0.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f}},
      {{-1.0f, 1.0f, 0.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f}},
      {{1.0f, 1.0f, 0.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f}}
  };
  // clang-format on

  mesh_data.indices() = {0, 1, 2, 1, 3, 2};

  buffers::VertexBufferLayout layout;
  layout.push<glm::vec3>("a_Position");  // position
  layout.push<glm::vec3>("a_Normal");    // normal
  layout.push<glm::vec2>("a_UV");        // uv
  layout.update();

  mesh_data.vertex_buffer_layout(layout);

  return mesh_data;
}

}  // namespace nova::graphics