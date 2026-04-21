#include <nova/graphics/mesh.h>

#include <nova/application.h>

namespace nova::graphics
{

Mesh::Mesh() { init(); }

Mesh::Mesh(const MeshData& data) : m_mesh_data(data)
{
  init();
  update();
}

void Mesh::update()
{
  m_vertex_buffer->data(m_mesh_data.vertices().data(),
                        m_mesh_data.vertices().size() * sizeof(Vertex));
  m_vertex_buffer->buffer_layout(m_mesh_data.vertex_buffer_layout());

  m_index_buffer->data(m_mesh_data.indices().data(), m_mesh_data.indices().size());

  m_vao = buffers::VertexArrayObject::create(Application::instance()->context()->api());

  m_vao->add_vertex_buffer(m_vertex_buffer);
  m_vao->set_index_buffer(m_index_buffer);
}

void Mesh::bind() const { m_vao->bind(); }

void Mesh::unbind() const { m_vao->unbind(); }

Ref<Mesh> Mesh::create() { return std::make_shared<Mesh>(); }

Ref<Mesh> Mesh::create(MeshPrimitive primitive)
{
  switch (primitive)
  {
    case MeshPrimitive::QUAD:
      return std::make_shared<Mesh>(MeshData::create_quad());
    default:
      core::logger()->error("Unsupported mesh primitive");
      break;
  }
  return nullptr;
}

void Mesh::init()
{
  GraphicsAPI api = Application::instance()->context()->api();

  m_vertex_buffer = buffers::VertexBuffer::create(api);
  m_index_buffer = buffers::IndexBuffer::create(api);
}

}  // namespace nova::graphics