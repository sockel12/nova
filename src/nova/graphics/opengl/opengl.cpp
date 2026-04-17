#include <nova/graphics/opengl/opengl.h>

#include <memory>

namespace nova::graphics::opengl
{

std::shared_ptr<spdlog::logger> logger()
{
  static std::shared_ptr<spdlog::logger> logger = core::get_logger("opengl");
  return logger;
}

}  // namespace nova::graphics::opengl