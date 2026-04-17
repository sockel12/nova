#pragma once

#include <memory>

#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>

namespace nova::core
{

std::shared_ptr<spdlog::logger> logger();

inline std::shared_ptr<spdlog::logger> get_logger(const std::string& name)
{
  return spdlog::stdout_color_st(name);
}

}  // namespace nova::core