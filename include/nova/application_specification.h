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
};
}  // namespace nova