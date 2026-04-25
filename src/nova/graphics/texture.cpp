#include <nova/graphics/texture.h>

#include <nova/application.h>

#include <nova/graphics/opengl/gl_texture.h>

namespace nova::graphics
{

Texture::Texture(uint32_t width, uint32_t height, uint32_t channels)
    : m_data{width, height, channels}
{
}

Ref<Texture> Texture::create(uint32_t width, uint32_t height, uint32_t channels, void* data)
{
  switch (Application::graphics_api())
  {
    case GraphicsAPI::OPENGL:
      return std::make_shared<opengl::GLTexture>(width, height, channels, data);
    default:
      core::logger()->error("Unsupported graphics API");
      throw std::runtime_error("Unsupported graphics API");
  }
}

}  // namespace nova::graphics