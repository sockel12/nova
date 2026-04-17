#pragma once

#include <string>

namespace nova::core
{

class Window
{
public:
  Window();
  Window(size_t width, size_t height, const std::string& title);
  virtual ~Window() = 0;

  void start_frame();
  void end_frame();

private:
  size_t m_width;
  size_t m_height;
  std::string m_title;
};

}  // namespace nova::core