#pragma once

#include <string>
#include <cstdint>

namespace nova
{

struct ApplicationSpecification
{
  uint32_t width = 1280;
  uint32_t height = 720;
  std::string name = "";
  uint32_t target_fps = 60;
};
}  // namespace nova