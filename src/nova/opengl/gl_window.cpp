#include <nova/opengl/gl_window.h>

namespace nova::opengl
{

GLWindow::GLWindow() : core::Window() {}

GLWindow::GLWindow(size_t width, size_t height, const std::string& title)
    : core::Window(width, height, title)
{
}

GLWindow::~GLWindow() = default;

}  // namespace nova::opengl