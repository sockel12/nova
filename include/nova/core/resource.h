#pragma once

namespace nova::io
{
class ResourceManager;
}

namespace nova::core
{

enum class ResourceType
{
  TEXTURE_2D,
  SHADER,
  MESH,
  MATERIAL,
  UNKNOWN
};

class Resource
{
  friend class io::ResourceManager;

public:
  virtual ~Resource() = default;

  const std::string& name() const { return m_name; }
  virtual ResourceType type() const = 0;

protected:
  Resource() = default;

protected:
  std::string m_name;
};

}  // namespace nova::core