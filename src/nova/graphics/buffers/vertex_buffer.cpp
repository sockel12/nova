#include <nova/graphics/buffers/vertex_buffer.h>

#include <nova/graphics/opengl/gl_vertex_buffer.h>

namespace nova::graphics::buffers
{

std::shared_ptr<VertexBuffer> VertexBuffer::create(GraphicsAPI api)
{
  switch (api)
  {
    case GraphicsAPI::OPENGL:
      return std::make_shared<opengl::GLVertexBuffer>();
    default:
      return nullptr;
  }
}

}  // namespace nova::graphics::buffers