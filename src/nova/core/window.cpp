#include <nova/core/window.h>

#include <nova/core/logger.h>

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
  if (!m_window)
  {
    const char* description;
    glfwGetError(&description);
    core::logger()->error("Failed to create GLFW window: {}", description);
    return false;
  }

  auto size_callback = [](GLFWwindow* window, int width, int height)
  { core::logger()->info("Window resize: ({}/{})", width, height); };
  auto fb_callback = [](GLFWwindow* window, int width, int height)
  { core::logger()->info("Framebuffer resize: ({}/{})", width, height); };
  auto key_callback = [](GLFWwindow* window, int key, int scancode, int action, int mods) {};

  glfwSetWindowSizeCallback(m_window, size_callback);
  glfwSetFramebufferSizeCallback(m_window, fb_callback);
  glfwSetKeyCallback(m_window, key_callback);

  return true;
}

void Window::shutdown()
{
  if (m_window)
  {
    glfwDestroyWindow(m_window);
    m_window = nullptr;
  }
}

void Window::poll_events() { glfwPollEvents(); }

}  // namespace nova::core
