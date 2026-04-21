#include <nova/graphics/opengl/opengl.h>

namespace nova::graphics::opengl
{

Ref<spdlog::logger> logger()
{
  static Ref<spdlog::logger> logger = core::get_logger("opengl");
  return logger;
}

}  // namespace nova::graphics::opengl