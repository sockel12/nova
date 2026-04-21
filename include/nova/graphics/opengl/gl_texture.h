#pragma once

#include <nova/graphics/texture.h>

#include <nova/graphics/opengl/opengl.h>

namespace nova::graphics::opengl
{

class GLTexture : public Texture
{
public:
  GLTexture(uint32_t width, uint32_t height);

  void bind() const override;
  void unbind() const override;

private:
  GLuint m_texture_id;
};

}  // namespace nova::graphics::opengl