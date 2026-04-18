#pragma once

#include <memory>
#include <vector>

#include <nova/graphics/graphics_api.h>

#include <nova/graphics/buffers/index_buffer.h>
#include <nova/graphics/buffers/vertex_buffer.h>

namespace nova::graphics::buffers
{

class VertexArrayObject : public Buffer
{
public:
  VertexArrayObject() = default;
  virtual ~VertexArrayObject() = default;

  virtual void add_vertex_buffer(const std::shared_ptr<VertexBuffer>& vertex_buffer) = 0;
  const std::vector<std::shared_ptr<VertexBuffer>>& vertex_buffers() const
  {
    return m_vertex_buffers;
  }

  virtual void set_index_buffer(const std::shared_ptr<IndexBuffer>& index_buffer) = 0;
  const std::shared_ptr<IndexBuffer>& index_buffer() const { return m_index_buffer; }

  static std::shared_ptr<VertexArrayObject> create(GraphicsAPI api);

protected:
  std::vector<std::shared_ptr<VertexBuffer>> m_vertex_buffers;
  std::shared_ptr<IndexBuffer> m_index_buffer;
};

}  // namespace nova::graphics::buffers