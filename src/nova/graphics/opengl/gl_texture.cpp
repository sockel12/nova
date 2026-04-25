#include <nova/graphics/opengl/gl_texture.h>

#include <nova/graphics/opengl/opengl.h>

namespace nova::graphics::opengl
{

GLenum internal_format_from_channels(uint32_t channels)
{
  switch (channels)
  {
    case 1:
      return GL_RED;
    case 2:
      return GL_RG;
    case 3:
      return GL_RGB;
    case 4:
      return GL_RGBA;
    default:
      core::logger()->error("Unsupported number of channels: {}", channels);
      throw std::runtime_error("Unsupported number of channels");
  }
}

GLTexture::GLTexture(uint32_t width, uint32_t height, uint32_t channels, void* data)
    : Texture(width, height, channels)
{
  GL_CALL(glGenTextures(1, &m_texture_id));
  bind();

  GL_CALL(glTexImage2D(GL_TEXTURE_2D, 0, internal_format_from_channels(channels), width, height, 0,
                       internal_format_from_channels(channels), GL_UNSIGNED_BYTE, data));
  GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
  GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));

  unbind();
}

GLTexture::~GLTexture() { GL_CALL(glDeleteTextures(1, &m_texture_id)); }

void GLTexture::resize(uint32_t width, uint32_t height, uint32_t channels)
{
  m_data.width = width;
  m_data.height = height;
  m_data.channels = channels;

  bind();

  GL_CALL(glTexImage2D(GL_TEXTURE_2D, 0, internal_format_from_channels(channels), width, height, 0,
                       internal_format_from_channels(channels), GL_UNSIGNED_BYTE, nullptr));

  unbind();
}

void GLTexture::bind(uint32_t slot) const
{
  GL_CALL(glActiveTexture(GL_TEXTURE0 + slot));
  GL_CALL(glBindTexture(GL_TEXTURE_2D, m_texture_id));
}

void GLTexture::unbind() const { GL_CALL(glBindTexture(GL_TEXTURE_2D, 0)); }

}  // namespace nova::graphics::opengl