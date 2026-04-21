#pragma once

#include <nova/common.h>

#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>

namespace nova::core
{

Ref<spdlog::logger> logger();

inline Ref<spdlog::logger> get_logger(const std::string& name)
{
  return spdlog::stdout_color_st(name);
}

}  // namespace nova::core