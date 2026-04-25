#pragma once

#include <nova/common.h>

#include <nova/graphics/texture.h>

#include <nova/graphics/buffers/frame_buffer.h>

#include <nova/graphics/opengl/opengl.h>

namespace nova::graphics::opengl
{

class GLFrameBuffer : public buffers::FrameBuffer
{
public:
  GLFrameBuffer(uint32_t width, uint32_t height);
  ~GLFrameBuffer();

  const Ref<Texture>& color_texture() const override { return m_color_texture; }

  void resize(uint32_t width, uint32_t height) override;

  void bind() const override;
  void unbind() const override;

private:
  GLuint m_frame_buffer_id = 0;

  Ref<Texture> m_color_texture;
};

}  // namespace nova::graphics::opengl