#include <nova/graphics/renderer/renderer_api.h>

#include <nova/graphics/opengl/gl_renderer_api.h>

namespace nova::graphics::renderer
{

Ref<RendererAPI> RendererAPI::create(graphics::GraphicsAPI api)
{
  switch (api)
  {
    case graphics::GraphicsAPI::OPENGL:
      return std::make_shared<opengl::GLRendererAPI>();
    default:
      return nullptr;
  }
}

}  // namespace nova::graphics::renderer