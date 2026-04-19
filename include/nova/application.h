#pragma once

#include <memory>

#include <nova/core/logger.h>
#include <nova/core/window.h>

#include <nova/graphics/graphics_context.h>

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

  const ApplicationSpecification& spec() const { return m_spec; }
  const std::shared_ptr<core::Window>& window() const { return m_window; }
  const std::shared_ptr<graphics::GraphicsContext>& context() const { return m_context; }

public:
  static Application* app();

private:
  ApplicationSpecification m_spec;
  std::shared_ptr<core::Window> m_window;
  std::shared_ptr<graphics::GraphicsContext> m_context;

private:
  static Application* s_instance;
};

}  // namespace nova