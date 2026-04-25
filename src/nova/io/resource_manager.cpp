#include <nova/common.h>

#include <memory>

#include <nova/core/logger.h>

#include <nova/io/resource_manager.h>

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

Ref<core::Resource> ResourceManager::create_texture(const std::string& name, uint32_t width,
                                                    uint32_t height, uint32_t channels)
{
  return instance().__create_texture(name, width, height, channels);
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
                                                   graphics::ShaderSource&& source)
{
  return instance().__load_shader(name, std::move(source));
}

Ref<graphics::Image> ResourceManager::load_image(const std::string& name, const std::string& path)
{
  return instance().__load_image(name, path);
}

Ref<graphics::Texture> ResourceManager::load_texture(const std::string& name,
                                                     const std::string& path)
{
  return instance().__load_texture(name, path);
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

Ref<core::Resource> ResourceManager::__create_texture(const std::string& name, uint32_t width,
                                                      uint32_t height, uint32_t channels)
{
  if (__exists(name))
  {
    core::logger()->warn("Resource with name '{}' already exists.", name);
    return nullptr;
  }

  auto texture = graphics::Texture::create(width, height, channels);
  auto res = m_resources.emplace(name, texture);

  if (res.second)
  {
    return texture;
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
                                                     graphics::ShaderSource&& source)
{
  if (__exists(name))
  {
    return std::dynamic_pointer_cast<graphics::Shader>(__load_resource(name));
  }

  auto shader = graphics::Shader::create(std::move(source));

  auto res = m_resources.emplace(name, shader);

  if (res.second)
  {
    return shader;
  }

  return nullptr;
}

Ref<graphics::Image> ResourceManager::__load_image(const std::string& name, const std::string& path)
{
  if (__exists(name))
  {
    return std::dynamic_pointer_cast<graphics::Image>(__load_resource(name));
  }

  auto image = graphics::Image::load(path);

  if (!image)
  {
    core::logger()->error("Failed to load image '{}' with path '{}'", name, path);
    return nullptr;
  }

  auto res = m_resources.emplace(name, image);

  if (res.second)
  {
    return image;
  }

  return nullptr;
}

Ref<graphics::Texture> ResourceManager::__load_texture(const std::string& name,
                                                       const std::string& path)
{
  if (__exists(name))
  {
    return std::dynamic_pointer_cast<graphics::Texture>(__load_resource(name));
  }

  auto image = __load_image(name + "_image", path);
  if (!image)
  {
    core::logger()->error("Failed to load image for texture '{}'", name);
    return nullptr;
  }

  auto texture = graphics::Texture::create(image->data().width, image->data().height,
                                           image->data().channels, image->data().data);
  if (!texture)
  {
    core::logger()->error("Failed to create texture for '{}'", name);
    return nullptr;
  }

  auto res = m_resources.emplace(name, texture);

  if (res.second)
  {
    return texture;
  }

  return nullptr;
}

}  // namespace nova::io