#pragma once

#include <nova/graphics/texture.h>

#include <nova/graphics/opengl/opengl.h>

namespace nova::graphics::opengl
{

class GLTexture : public Texture
{
public:
  GLTexture(uint32_t width, uint32_t height, uint32_t channels = 4, void* data = nullptr);
  ~GLTexture() override;

  uint32_t texture_id() const override { return m_texture_id; }

  void resize(uint32_t width, uint32_t height, uint32_t channels = 4) override;

  void bind(uint32_t slot = 0) const override;
  void unbind() const override;

private:
  GLuint m_texture_id;
};

}  // namespace nova::graphics::opengl