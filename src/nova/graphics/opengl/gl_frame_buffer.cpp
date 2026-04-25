#include <nova/graphics/opengl/gl_frame_buffer.h>

namespace nova::graphics::opengl
{

GLFrameBuffer::GLFrameBuffer(uint32_t width, uint32_t height)
{
  GL_CALL(glGenFramebuffers(1, &m_frame_buffer_id));

  bind();

  m_color_texture = Texture::create(width, height);

  m_color_texture->bind();

  GL_CALL(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D,
                                 m_color_texture->texture_id(), 0));

  GLenum result;

  GL_CALL(result = glCheckFramebufferStatus(GL_FRAMEBUFFER));
  if (result != GL_FRAMEBUFFER_COMPLETE)
  {
    logger()->error("Failed to create framebuffer");
  }
}

GLFrameBuffer::~GLFrameBuffer()
{
  if (m_frame_buffer_id)
  {
    GL_CALL(glDeleteFramebuffers(1, &m_frame_buffer_id));
  }
}

void GLFrameBuffer::resize(uint32_t width, uint32_t height)
{
  m_color_texture->resize(width, height);
}

void GLFrameBuffer::bind() const { GL_CALL(glBindFramebuffer(GL_FRAMEBUFFER, m_frame_buffer_id)); }

void GLFrameBuffer::unbind() const { GL_CALL(glBindFramebuffer(GL_FRAMEBUFFER, 0)); }

}  // namespace nova::graphics::opengl