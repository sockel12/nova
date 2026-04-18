#pragma once

#include <string>

namespace nova::core
{

class FileHandler
{
public:
  static std::string read_file(const std::string& filepath);
};

}  // namespace nova::core