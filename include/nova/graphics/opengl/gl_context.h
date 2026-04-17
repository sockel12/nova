#pragma once

#include <nova/graphics/opengl/opengl.h>

#include <nova/graphics/graphics_context.h>

namespace nova::graphics::opengl
{

class OpenGLContext : public graphics::GraphicsContext
{
public:
  OpenGLContext(const std::shared_ptr<core::Window>& window, graphics::ContextSpecification spec);
  ~OpenGLContext();

  void setup_window_hints() override;
  bool init() override;
  void shutdown() override;

  void swap_buffers() override;

  void vsync(bool enabled) override;

  graphics::GraphicsAPI api() const override { return graphics::GraphicsAPI::OPENGL; }

private:
};

}  // namespace nova::graphics::opengl