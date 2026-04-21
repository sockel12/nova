#include <nova/common.h>

#include <nova/core/logger.h>

#include <nova/io/resource_manager.h>
#include <memory>

namespace nova::io
{

void ResourceManager::shutdown() { instance().m_resources.clear(); }

bool ResourceManager::exists(const std::string& name) { return instance().__exists(name); }

Ref<graphics::Material> ResourceManager::create_material(const std::string& name)
{
  return instance().__create_material(name);
}

Ref<graphics::Mesh> ResourceManager::create_mesh(const std::string& name)
{
  return instance().__create_mesh(name);
}

Ref<graphics::Mesh> ResourceManager::create_mesh(const std::string& name, MeshPrimitive primitive)
{
  return instance().__create_mesh(name, primitive);
}

Ref<core::Resource> ResourceManager::load_resource(const std::string& name)
{
  return instance().__load_resource(name);
}

Ref<graphics::Shader> ResourceManager::load_shader(const std::string& name,
                                                   const graphics::ShaderSource& source)
{
  return instance().__load_shader(name, source);
}

Ref<graphics::Shader> ResourceManager::load_shader(const std::string& name,
                                                   const graphics::ShaderSource&& source)
{
  return instance().__load_shader(name, std::move(source));
}

ResourceManager& ResourceManager::instance()
{
  static ResourceManager instance;
  return instance;
}

/** Internal functions */

bool ResourceManager::__exists(const std::string& name) const
{
  return m_resources.find(name) != m_resources.end();
}

Ref<graphics::Material> ResourceManager::__create_material(const std::string& name)
{
  if (__exists(name))
  {
    core::logger()->warn("Resource with name '{}' already exists.", name);
    return nullptr;
  }

  auto material = graphics::Material::create();
  auto res = m_resources.emplace(name, material);

  if (res.second)
  {
    return material;
  }
  return nullptr;
}

Ref<graphics::Mesh> ResourceManager::__create_mesh(const std::string& name)
{
  if (__exists(name))
  {
    core::logger()->warn("Resource with name '{}' already exists.", name);
    return nullptr;
  }

  auto mesh = graphics::Mesh::create();
  auto res = m_resources.emplace(name, mesh);

  if (res.second)
  {
    return mesh;
  }
  return nullptr;
}

Ref<graphics::Mesh> ResourceManager::__create_mesh(const std::string& name, MeshPrimitive primitive)
{
  if (__exists(name))
  {
    core::logger()->warn("Resource with name '{}' already exists.", name);
    return nullptr;
  }

  auto mesh = graphics::Mesh::create(primitive);
  auto res = m_resources.emplace(name, mesh);

  if (res.second)
  {
    return mesh;
  }
  return nullptr;
}

Ref<core::Resource> ResourceManager::__load_resource(const std::string& name)
{
  if (__exists(name))
  {
    return m_resources[name];
  }
  core::logger()->warn("Resource with name '{}' does not exist.", name);
  return nullptr;
}

Ref<graphics::Shader> ResourceManager::__load_shader(const std::string& name,
                                                     const graphics::ShaderSource& source)
{
  if (__exists(name))
  {
    return std::dynamic_pointer_cast<graphics::Shader>(__load_resource(name));
  }

  auto shader = graphics::Shader::create(source);

  auto res = m_resources.emplace(name, shader);

  if (res.second)
  {
    return shader;
  }

  return nullptr;
}

Ref<graphics::Shader> ResourceManager::__load_shader(const std::string& name,
                                                     const graphics::ShaderSource&& source)
{
  if (__exists(name))
  {
    return std::dynamic_pointer_cast<graphics::Shader>(__load_resource(name));
  }

  auto shader = graphics::Shader::create(source);

  auto res = m_resources.emplace(name, shader);

  if (res.second)
  {
    return shader;
  }

  return nullptr;
}

}  // namespace nova::io