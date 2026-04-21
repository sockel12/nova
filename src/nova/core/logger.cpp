#include <nova/core/logger.h>

namespace nova::core
{

Ref<spdlog::logger> logger()
{
  static Ref<spdlog::logger> instance = get_logger("nova");
  return instance;
}

}  // namespace nova::core