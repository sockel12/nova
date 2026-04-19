#pragma once

#include <vector>

#include <glm/glm.hpp>

#include <nova/graphics/buffers/vertex_buffer_layout.h>

namespace nova::graphics
{

struct Vertex
{
  Vertex() = default;
  Vertex(const glm::vec3& pos);
  Vertex(const glm::vec3& pos, const glm::vec2& uv);
  Vertex(const glm::vec3& pos, const glm::vec3& normal, const glm::vec2& uv);

  glm::vec3 position = glm::vec3(0.0f);
  glm::vec3 normal = glm::vec3(0.0f);
  glm::vec2 uv = glm::vec2(0.0f);
};

class BaseMeshData
{
public:
  BaseMeshData() = default;
  virtual ~BaseMeshData() = default;

  virtual const void* vertex_data() const = 0;
  virtual size_t vertex_count() const = 0;
  virtual size_t vertex_size() const = 0;
  virtual const buffers::VertexBufferLayout& vertex_buffer_layout() const = 0;

  virtual const std::vector<uint32_t>& indices() const = 0;
};

template <typename T>
class MeshData : public BaseMeshData
{
public:
  MeshData() = default;
  MeshData(const std::vector<T>& vertices) : m_vertices(vertices) {}
  MeshData(const std::vector<T>& vertices, const std::vector<uint32_t>& indices)
      : m_vertices(vertices), m_indices(indices)
  {
  }
  MeshData(const std::vector<T>& vertices, const std::vector<uint32_t>& indices,
           const buffers::VertexBufferLayout& layout)
      : m_vertices(vertices), m_indices(indices), m_vertex_buffer_layout(layout)
  {
  }

  void vertices(const std::vector<T>& vertices) { m_vertices = vertices; }

  const void* vertex_data() const override { return m_vertices.data(); }
  size_t vertex_count() const override { return m_vertices.size(); }
  size_t vertex_size() const override { return sizeof(T); }

  void vertex_buffer_layout(const buffers::VertexBufferLayout& layout)
  {
    m_vertex_buffer_layout = layout;
  }
  const buffers::VertexBufferLayout& vertex_buffer_layout() const override
  {
    return m_vertex_buffer_layout;
  }

  void indices(const std::vector<uint32_t>& indices) { m_indices = indices; }
  const std::vector<uint32_t>& indices() const override { return m_indices; }

private:
  std::vector<T> m_vertices;
  std::vector<uint32_t> m_indices;
  buffers::VertexBufferLayout m_vertex_buffer_layout;
};

}  // namespace nova::graphics