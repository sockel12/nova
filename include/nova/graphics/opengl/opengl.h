#pragma once

#include <nova/common.h>

#include <nova/core/logger.h>

// clang-format off
#include <glad/gl.h>
#include <GLFW/glfw3.h>
// clang-format on

namespace nova::graphics::opengl
{

Ref<spdlog::logger> logger();

}

namespace
{

#define GL_CALL(x)                                                                       \
  do                                                                                     \
  {                                                                                      \
    x;                                                                                   \
    GLenum err = glGetError();                                                           \
    if (err != GL_NO_ERROR)                                                              \
    {                                                                                    \
      nova::graphics::opengl::logger()->error("OpenGL error {} at {}:{}", err, __FILE__, \
                                              __LINE__);                                 \
    }                                                                                    \
  } while (0)

}  // namespace
