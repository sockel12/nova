#pragma once

#include <nova/graphics/buffers/index_buffer.h>

#include <nova/graphics/opengl/opengl.h>

namespace nova::graphics::opengl
{

class GLIndexBuffer : public buffers::IndexBuffer
{
public:
  GLIndexBuffer();
  GLIndexBuffer(const uint32_t* data, size_t count);
  ~GLIndexBuffer() override;

  void data(const uint32_t* data, size_t count) override;
  void data(const std::vector<uint32_t>& data) override;

  size_t count() const override { return m_count; }

  void bind() const override;
  void unbind() const override;

private:
  GLuint m_buffer_id = 0;
  size_t m_count = 0;
};

}  // namespace nova::graphics::opengl