#pragma once

#include <nova/graphics/graphics_context.h>
#include <nova/core/logger.h>
#include <nova/core/window.h>

namespace nova
{

struct ApplicationSpecification
{
  uint32_t width = 1280;
  uint32_t height = 720;
  std::string name = "";
};

class Application
{
public:
  Application(ApplicationSpecification spec = ApplicationSpecification());
  ~Application();

  bool init();
  void shutdown();

  void run();

private:
  ApplicationSpecification m_spec;
  std::shared_ptr<core::Window> m_window;
  std::shared_ptr<graphics::GraphicsContext> m_context;
};

}  // namespace nova