#pragma once

#include <nova/opengl/opengl.h>

#include <nova/core/graphics_context.h>

namespace nova::opengl
{

class OpenGLContext : public core::GraphicsContext
{
public:
  OpenGLContext(const std::shared_ptr<core::Window>& window, core::ContextSpecification spec);
  ~OpenGLContext();

  void setup_window_hints() override;
  bool init() override;
  void shutdown() override;

  void swap_buffers() override;

  void vsync(bool enabled) override;

  core::GraphicsAPI api() const override { return core::GraphicsAPI::OPENGL; }

private:
};

}  // namespace nova::opengl