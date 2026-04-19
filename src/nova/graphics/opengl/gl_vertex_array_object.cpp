#include <nova/graphics/opengl/gl_vertex_array_object.h>

namespace nova::graphics::opengl
{

GLVertexArrayObject::GLVertexArrayObject()
{
  GL_CALL(glGenVertexArrays(1, &m_array_id));
  bind();
}

GLVertexArrayObject::~GLVertexArrayObject() { GL_CALL(glDeleteVertexArrays(1, &m_array_id)); }

void GLVertexArrayObject::add_vertex_buffer(
    const std::shared_ptr<buffers::VertexBuffer>& vertex_buffer)
{
  bind();
  vertex_buffer->bind();

  const auto& layout = vertex_buffer->buffer_layout();
  uint32_t index = 0;
  for (const auto& element : layout.elements())
  {
    /** TODO: Implement matrix support */
    GL_CALL(glEnableVertexAttribArray(index));
    GL_CALL(glVertexAttribPointer(index, shader_data_type_component_count(element.type()), GL_FLOAT,
                                  element.normalized() ? GL_TRUE : GL_FALSE, layout.stride(),
                                  reinterpret_cast<const void*>(element.offset())));
    index++;
  }

  m_vertex_buffers.push_back(vertex_buffer);
}

void GLVertexArrayObject::set_index_buffer(
    const std::shared_ptr<buffers::IndexBuffer>& index_buffer)
{
  bind();
  index_buffer->bind();

  m_index_buffer = index_buffer;
}

void GLVertexArrayObject::bind() const { GL_CALL(glBindVertexArray(m_array_id)); }

void GLVertexArrayObject::unbind() const { GL_CALL(glBindVertexArray(0)); }

}  // namespace nova::graphics::opengl