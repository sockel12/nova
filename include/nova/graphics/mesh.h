#pragma once

#include <vector>

#include <nova/graphics/mesh_data.h>

#include <nova/graphics/buffers/vertex_array_object.h>
#include <nova/graphics/buffers/vertex_buffer.h>
#include <nova/graphics/buffers/index_buffer.h>

namespace nova::graphics
{

class Mesh
{
public:
  Mesh(const std::shared_ptr<BaseMeshData>& data);

  void update_mesh_data(const std::shared_ptr<BaseMeshData>& data);
  const std::shared_ptr<BaseMeshData>& mesh_data() const { return m_mesh_data; }

  size_t indices_count() const { return m_mesh_data->indices().size(); }

  void bind() const;
  void unbind() const;

  static std::shared_ptr<Mesh> create(const std::shared_ptr<BaseMeshData>& data);

private:
private:
  std::shared_ptr<BaseMeshData> m_mesh_data;
  std::shared_ptr<buffers::VertexArrayObject> m_vao;
  std::shared_ptr<buffers::VertexBuffer> m_vertex_buffer;
  std::shared_ptr<buffers::IndexBuffer> m_index_buffer;
};

}  // namespace nova::graphics