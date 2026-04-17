#pragma once

#include <nova/core/window.h>
#include <nova/opengl/gl.h>

namespace nova::opengl
{

class GLWindow : public core::Window
{
public:
  GLWindow();
  GLWindow(size_t width, size_t height, const std::string& title);
  ~GLWindow() override;

private:
};

} // namespace nova::opengl