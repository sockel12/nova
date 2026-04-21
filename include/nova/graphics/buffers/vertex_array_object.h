#pragma once

#include <nova/common.h>
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
  VertexArrayObject(VertexArrayObject& other) = delete;
  virtual ~VertexArrayObject() = default;

  VertexArrayObject& operator=(VertexArrayObject& other) = delete;

  virtual void add_vertex_buffer(const Ref<VertexBuffer>& vertex_buffer) = 0;
  const std::vector<Ref<VertexBuffer>>& vertex_buffers() const { return m_vertex_buffers; }

  virtual void set_index_buffer(const Ref<IndexBuffer>& index_buffer) = 0;
  const Ref<IndexBuffer>& index_buffer() const { return m_index_buffer; }

  static Ref<VertexArrayObject> create(GraphicsAPI api);

protected:
  std::vector<Ref<VertexBuffer>> m_vertex_buffers;
  Ref<IndexBuffer> m_index_buffer;
};

}  // namespace nova::graphics::buffers