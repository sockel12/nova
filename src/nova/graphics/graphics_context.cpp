
#include <nova/graphics/graphics_context.h>

#include <nova/graphics/opengl/gl_context.h>

namespace nova::graphics
{
Ref<GraphicsContext> GraphicsContext::create(const Ref<core::Window>& window,
                                             ContextSpecification spec)
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