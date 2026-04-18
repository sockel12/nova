#include <nova/graphics/buffers/index_buffer.h>

#include <nova/graphics/opengl/gl_index_buffer.h>

namespace nova::graphics::buffers
{

std::shared_ptr<IndexBuffer> IndexBuffer::create(GraphicsAPI api)
{
  switch (api)
  {
    case GraphicsAPI::OPENGL:
      return std::make_shared<opengl::GLIndexBuffer>();
    default:
      core::logger()->error("Unsupported graphics API");
      return nullptr;
  }
}

}  // namespace nova::graphics::buffers
