#include <nova/graphics/opengl/gl_context.h>

#include "GLFW/glfw3.h"
#include "glad/gl.h"
#include <nova/graphics/graphics_context.h>

namespace nova::graphics::opengl
{

void APIENTRY opengl_debug_callback(GLenum source, GLenum type, GLuint id, GLenum severity,
                                    GLsizei length, const GLchar* message, const void* user_param)
{
  switch (severity)
  {
    case GL_DEBUG_SEVERITY_HIGH:
      logger()->error("OpenGL Debug: {0}", message);
      break;
    case GL_DEBUG_SEVERITY_MEDIUM:
      logger()->warn("OpenGL Debug: {0}", message);
      break;
    case GL_DEBUG_SEVERITY_LOW:
      logger()->info("OpenGL Debug: {0}", message);
      break;
    case GL_DEBUG_SEVERITY_NOTIFICATION:
      logger()->trace("OpenGL Debug: {0}", message);
      break;
    default:
      logger()->error("OpenGL Debug: {0}", message);
      break;
  }
}

OpenGLContext::OpenGLContext(const std::shared_ptr<core::Window>& window,
                             graphics::ContextSpecification spec)
    : graphics::GraphicsContext(window, spec)
{
}

OpenGLContext::~OpenGLContext() {}

void OpenGLContext::setup_window_hints()
{
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#else
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
#endif
}

bool OpenGLContext::init()
{
  glfwMakeContextCurrent(m_window->native_window());

  if (!gladLoadGL(glfwGetProcAddress))
  {
    logger()->error("Failed to initialize OpenGL context");
    return false;
  }

  if (m_spec.debug)
  {
    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);

#ifndef __APPLE__
    glDebugMessageCallback(opengl_debug_callback, nullptr);
#endif
  }

  return true;
}

void OpenGLContext::shutdown() { glfwMakeContextCurrent(nullptr); }

void OpenGLContext::swap_buffers() { glfwSwapBuffers(m_window->native_window()); }

void OpenGLContext::vsync(bool enabled) { m_spec.vsync = enabled; }

}  // namespace nova::graphics::opengl