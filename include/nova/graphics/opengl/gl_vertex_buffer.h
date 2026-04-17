#pragma once

#include <nova/graphics/opengl/opengl.h>

#include <nova/graphics/buffers/vertex_buffer.h>

namespace nova::graphics::opengl
{

class GLVertexBuffer : public buffers::VertexBuffer
{
public:
  GLVertexBuffer();
  ~GLVertexBuffer() override;

  void data(const void* data, uint32_t size) override;

  void bind() const override;
  void unbind() const override;

private:
  GLuint m_buffer_id = 0;
};

}  // namespace nova::graphics::opengl