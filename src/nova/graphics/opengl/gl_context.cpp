#include <nova/graphics/opengl/gl_context.h>

#include "nova/graphics/opengl/opengl.h"
#include <nova/graphics/graphics_context.h>

namespace nova::graphics::opengl
{

void APIENTRY opengl_debug_callback(GLenum source, GLenum type, GLuint id, GLenum severity,
                                    GLsizei length, const GLchar* message, const void* user_param)
{
  switch (severity)
  {
    case GL_DEBUG_SEVERITY_HIGH:
      logger()->error("OpenGL: {0}", message);
      break;
    case GL_DEBUG_SEVERITY_MEDIUM:
      logger()->warn("OpenGL: {0}", message);
      break;
    case GL_DEBUG_SEVERITY_LOW:
      logger()->info("OpenGL: {0}", message);
      break;
    case GL_DEBUG_SEVERITY_NOTIFICATION:
      logger()->trace("OpenGL: {0}", message);
      break;
    default:
      logger()->error("OpenGL: {0}", message);
      break;
  }
}

OpenGLContext::OpenGLContext(const Ref<core::Window>& window, graphics::ContextSpecification spec)
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

  GLint extension_count;
  GL_CALL(glGetIntegerv(GL_NUM_EXTENSIONS, &extension_count));

  logger()->info("OpenGL");
  logger()->info("\tVersion: {0}", reinterpret_cast<const char*>(glGetString(GL_VERSION)));
  logger()->info("\tVendor: {0}", reinterpret_cast<const char*>(glGetString(GL_VENDOR)));
  logger()->info("\tRenderer: {0}", reinterpret_cast<const char*>(glGetString(GL_RENDERER)));
  logger()->info("Extensions:");
  for (GLint i = 0; i < extension_count; i++)
  {
    const char* extension = reinterpret_cast<const char*>(glGetStringi(GL_EXTENSIONS, i));
    m_active_extensions.insert(extension);
    logger()->info("\t{0}", extension);
  }

  if (m_spec.debug)
  {
    if (m_active_extensions.count("GL_KHR_debug") != 0 ||
        m_active_extensions.count("GL_ARB_debug_output") != 0)
    {
      logger()->info("Enabling OpenGL debug output");
      GL_CALL(glEnable(GL_DEBUG_OUTPUT));
      GL_CALL(glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS));
      GL_CALL(glDebugMessageCallback(opengl_debug_callback, nullptr));
    }
  }

  this->vsync(m_spec.vsync);

  return true;
}

void OpenGLContext::shutdown() { glfwMakeContextCurrent(nullptr); }

void OpenGLContext::swap_buffers() { glfwSwapBuffers(m_window->native_window()); }

void OpenGLContext::vsync(bool enabled)
{
  m_spec.vsync = enabled;
  glfwSwapInterval(enabled ? 1 : 0);
}

}  // namespace nova::graphics::opengl