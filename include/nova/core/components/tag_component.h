#pragma once

#include <string>

namespace nova::core::components
{

class TagComponent
{
public:
  TagComponent(const std::string& tag) : tag(tag) {}

  std::string tag;
};

}  // namespace nova::core::components