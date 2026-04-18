#include <nova/graphics/opengl/gl_index_buffer.h>

namespace nova::graphics::opengl
{

GLIndexBuffer::GLIndexBuffer() { GL_CALL(glGenBuffers(1, &m_buffer_id)); }

GLIndexBuffer::GLIndexBuffer(const uint32_t* data, size_t count)
{
  GL_CALL(glGenBuffers(1, &m_buffer_id));
  this->data(data, count);
}

GLIndexBuffer::~GLIndexBuffer() { GL_CALL(glDeleteBuffers(1, &m_buffer_id)); }

void GLIndexBuffer::data(const uint32_t* data, size_t count)
{
  GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_buffer_id));
  GL_CALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(size_t), data, GL_STATIC_DRAW));
  m_count = count;
}

void GLIndexBuffer::data(const std::vector<uint32_t>& data)
{
  this->data(data.data(), data.size());
  m_count = data.size();
}

void GLIndexBuffer::bind() const { GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_buffer_id)); }

void GLIndexBuffer::unbind() const { GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0)); }

}  // namespace nova::graphics::opengl