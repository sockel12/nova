#include <nova/core/window.h>

namespace nova::core
{

Window::Window() : m_width(800), m_height(600), m_title("") {}

Window::Window(size_t width, size_t height, const std::string& title)
    : m_width(width), m_height(height), m_title(title)
{
}

Window::~Window() { shutdown(); }

bool Window::init()
{
  m_window = glfwCreateWindow(m_width, m_height, m_title.c_str(), nullptr, nullptr);

  return true;
}

void Window::shutdown()
{
  if (m_window)
  {
    glfwDestroyWindow(m_window);
  }
}

void Window::poll_events() { glfwPollEvents(); }

}  // namespace nova::core
