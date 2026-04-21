#include <nova/graphics/opengl/gl_texture.h>

#include <nova/graphics/opengl/opengl.h>

namespace nova::graphics::opengl
{

GLTexture::GLTexture(uint32_t width, uint32_t height)
{
  GL_CALL(glGenTextures(1, &m_texture_id));
  GL_CALL(glBindTexture(GL_TEXTURE_2D, m_texture_id));

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
  GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
  GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
  GL_CALL(glBindTexture(GL_TEXTURE_2D, 0));
}

void GLTexture::bind() const { GL_CALL(glBindTexture(GL_TEXTURE_2D, m_texture_id)); }

void GLTexture::unbind() const { GL_CALL(glBindTexture(GL_TEXTURE_2D, 0)); }
}  // namespace nova::graphics::opengl