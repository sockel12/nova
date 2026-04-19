#include <nova/graphics/mesh.h>

#include <nova/application.h>

namespace nova::graphics
{

Mesh::Mesh(const std::shared_ptr<BaseMeshData>& data) : m_mesh_data(data)
{
  GraphicsAPI api = Application::app()->context()->api();

  m_vertex_buffer = buffers::VertexBuffer::create(api);
  m_index_buffer = buffers::IndexBuffer::create(api);

  update_mesh_data(data);
}

void Mesh::update_mesh_data(const std::shared_ptr<BaseMeshData>& data)
{
  m_mesh_data = data;

  m_vertex_buffer->data(m_mesh_data->vertex_data(),
                        m_mesh_data->vertex_count() * m_mesh_data->vertex_size());
  m_vertex_buffer->buffer_layout(m_mesh_data->vertex_buffer_layout());

  m_index_buffer->data(m_mesh_data->indices().data(), m_mesh_data->indices().size());

  m_vao = buffers::VertexArrayObject::create(Application::app()->context()->api());

  m_vao->add_vertex_buffer(m_vertex_buffer);
  m_vao->set_index_buffer(m_index_buffer);
}

void Mesh::bind() const { m_vao->bind(); }

void Mesh::unbind() const { m_vao->unbind(); }

}  // namespace nova::graphics