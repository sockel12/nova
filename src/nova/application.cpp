#include <nova/application.h>

#include <nova/core/graphics_factory.h>
#include <memory>

namespace nova
{

Application::Application(ApplicationSpecification spec)
    : m_spec(spec), m_window(nullptr), m_context(nullptr)
{
}

Application::~Application() { shutdown(); }

bool Application::init()
{
  if (!glfwInit())
  {
    core::logger()->error("Failed to initialize GLFW");
    return false;
  }

  m_window = std::make_shared<core::Window>(m_spec.width, m_spec.height, m_spec.name);
  m_context =
      core::GraphicsFactory::create_graphics_context(m_window, core::ContextSpecification());

  m_context->setup_window_hints();
  if (!m_window->init())
  {
    core::logger()->error("Failed to initialize window");
    return false;
  }

  if (!m_context->init())
  {
    core::logger()->error("Failed to initialize graphics context");
    return false;
  }

  return true;
}

void Application::shutdown()
{
  if (m_context)
  {
    m_context->shutdown();
  }

  if (m_window)
  {
    m_window->shutdown();
  }

  glfwTerminate();
}

void Application::run()
{
  bool should_close = false;

  while (!glfwWindowShouldClose(m_window->native_window()))
  {
    m_window->poll_events();

    m_context->swap_buffers();
  }
}

}  // namespace nova