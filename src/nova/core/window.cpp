#include <nova/core/window.h>

namespace nova::core
{

Window::Window() : m_width(0), m_height(0), m_title("") {}

Window::Window(size_t width, size_t height, const std::string& title)
    : m_width(width), m_height(height), m_title(title)
{
}

}  // namespace nova::core
