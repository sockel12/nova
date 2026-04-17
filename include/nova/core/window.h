#pragma once

#include <string>

#include <GLFW/glfw3.h>

namespace nova::core
{

class Window
{
public:
  Window();
  Window(size_t width, size_t height, const std::string& title);
  ~Window();

  bool init();
  void shutdown();

  void poll_events();

  GLFWwindow* native_window() const { return m_window; }

private:
  size_t m_width;
  size_t m_height;
  std::string m_title;
  GLFWwindow* m_window;
};

}  // namespace nova::core