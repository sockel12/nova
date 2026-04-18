#include <nova/core/file_handler.h>

#include <fstream>

#include <nova/core/logger.h>

namespace nova::core
{

std::string FileHandler::read_file(const std::string& filepath)
{
  std::ifstream file(filepath);
  if (!file.is_open())
  {
    logger()->error("Failed to open file: " + filepath);
    return "";
  }

  std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
  return content;
}

}  // namespace nova::core