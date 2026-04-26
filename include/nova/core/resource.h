#pragma once

#include <atomic>
#include <cstdint>
#include <string>

namespace nova::core
{

using ResourceId = std::uint64_t;

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
public:
  virtual ~Resource() = default;

  const std::string& name() const { return m_name; }
  ResourceId id() const { return m_id; }
  virtual ResourceType type() const = 0;

  void set_name(const std::string& name) { m_name = name; }

protected:
  Resource() : m_id(next_id()) {}

protected:
  static ResourceId next_id()
  {
    static std::atomic<ResourceId> id{1};
    return id.fetch_add(1, std::memory_order_relaxed);
  }

  std::string m_name;
  const ResourceId m_id;
};

}  // namespace nova::core