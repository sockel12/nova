#include <nova/core/graphics_factory.h>

#include <memory>

#include <nova/opengl/gl_context.h>

namespace nova::core
{

std::shared_ptr<GraphicsContext> GraphicsFactory::create_graphics_context(
    const std::shared_ptr<Window>& window, ContextSpecification spec)
{
  switch (spec.api)
  {
    case GraphicsAPI::OPENGL:
      return std::make_shared<opengl::OpenGLContext>(window, spec);
    default:
      return nullptr;
  }
}

}  // namespace nova::core