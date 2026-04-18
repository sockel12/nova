#pragma once

#include <nova/graphics/buffers/vertex_array_object.h>

#include <nova/graphics/opengl/opengl.h>

namespace nova::graphics::opengl
{

class GLVertexArrayObject : public buffers::VertexArrayObject
{
public:
  GLVertexArrayObject();
  ~GLVertexArrayObject() override;

  void add_vertex_buffer(const std::shared_ptr<buffers::VertexBuffer>& vertex_buffer) override;
  void set_index_buffer(const std::shared_ptr<buffers::IndexBuffer>& index_buffer) override;

  void bind() const override;
  void unbind() const override;

private:
  GLuint m_array_id = 0;
};

}  // namespace nova::graphics::opengl