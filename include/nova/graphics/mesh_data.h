#pragma once

#include <vector>

#include <glm/glm.hpp>

#include <nova/graphics/buffers/vertex_buffer_layout.h>

namespace nova::graphics
{

struct Vertex
{
  glm::vec3 position = glm::vec3(0.0f);
  glm::vec3 normal = glm::vec3(0.0f);
  glm::vec2 uv = glm::vec2(0.0f);
};

class MeshData
{
public:
  MeshData() = default;

  std::vector<Vertex>& vertices() { return m_vertices; }
  const std::vector<Vertex>& vertices() const { return m_vertices; }

  std::vector<uint32_t>& indices() { return m_indices; }
  const std::vector<uint32_t>& indices() const { return m_indices; }

  void vertex_buffer_layout(const buffers::VertexBufferLayout& layout)
  {
    m_vertex_buffer_layout = layout;
  }
  const buffers::VertexBufferLayout& vertex_buffer_layout() const { return m_vertex_buffer_layout; }

public:
  static MeshData create_quad();

private:
  std::vector<Vertex> m_vertices;
  std::vector<uint32_t> m_indices;
  buffers::VertexBufferLayout m_vertex_buffer_layout;
};

}  // namespace nova::graphics