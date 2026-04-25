#include <nova/graphics/buffers/frame_buffer.h>

#include <nova/application.h>

#include <nova/graphics/opengl/gl_frame_buffer.h>

namespace nova::graphics::buffers
{

Ref<FrameBuffer> FrameBuffer::create(uint32_t width, uint32_t height)
{
  switch (Application::graphics_api())
  {
    case graphics::GraphicsAPI::OPENGL:
      return std::make_shared<opengl::GLFrameBuffer>(width, height);
    default:
      core::logger()->error("Unsupported graphics API");
      throw std::runtime_error("Unsupported graphics API");
  }
}

}  // namespace nova::graphics::buffers