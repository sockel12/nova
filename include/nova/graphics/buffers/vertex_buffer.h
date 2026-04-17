#pragma once

#include <memory>

#include <nova/graphics/graphics_api.h>

#include <nova/graphics/buffers/buffer.h>
#include <nova/graphics/buffers/vertex_buffer_layout.h>

namespace nova::graphics::buffers
{

class VertexBuffer : public Buffer
{
public:
  virtual ~VertexBuffer() = default;

  virtual void data(const void* data, uint32_t size) = 0;

  void buffer_layout(const VertexBufferLayout& layout) { m_layout = layout; }
  const VertexBufferLayout& buffer_layout() const { return m_layout; }

  static std::shared_ptr<VertexBuffer> create(GraphicsAPI api);

protected:
  VertexBufferLayout m_layout;
};

}  // namespace nova::graphics::buffers
