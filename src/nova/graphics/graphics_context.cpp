
#include <nova/graphics/graphics_context.h>

#include <nova/graphics/opengl/gl_context.h>

namespace nova::graphics
{
std::shared_ptr<GraphicsContext> GraphicsContext::create(
    const std::shared_ptr<core::Window>& window, ContextSpecification spec)
{
  switch (spec.api)
  {
    case GraphicsAPI::OPENGL:
      return std::make_shared<opengl::OpenGLContext>(window, spec);
    default:
      return nullptr;
  }
}

}  // namespace nova::graphics