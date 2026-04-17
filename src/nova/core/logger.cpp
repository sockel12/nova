#include <nova/core/logger.h>

namespace nova::core
{

std::shared_ptr<spdlog::logger> logger()
{
  static std::shared_ptr<spdlog::logger> instance = get_logger("nova");
  return instance;
}

}  // namespace nova::core