#include <nova/graphics/buffers/vertex_array_object.h>

#include <nova/graphics/opengl/gl_vertex_array_object.h>

namespace nova::graphics::buffers
{

std::shared_ptr<VertexArrayObject> VertexArrayObject::create(GraphicsAPI api)
{
  switch (api)
  {
    case GraphicsAPI::OPENGL:
      return std::make_shared<opengl::GLVertexArrayObject>();
    default:
      return nullptr;
  }
}

}  // namespace nova::graphics::buffers