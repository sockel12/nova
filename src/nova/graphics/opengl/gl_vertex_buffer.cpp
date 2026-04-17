#include <nova/graphics/opengl/gl_vertex_buffer.h>

namespace nova::graphics::opengl
{

GLVertexBuffer::GLVertexBuffer()
{
  GL_CALL(glGenBuffers(1, &m_buffer_id));
  bind();
}

GLVertexBuffer::~GLVertexBuffer() { GL_CALL(glDeleteBuffers(1, &m_buffer_id)); }

void GLVertexBuffer::data(const void* data, uint32_t size)
{
  bind();
  GL_CALL(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}

void GLVertexBuffer::bind() const { GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, m_buffer_id)); }

void GLVertexBuffer::unbind() const { GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, 0)); }

}  // namespace nova::graphics::opengl