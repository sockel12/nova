#pragma once

#include <nova/core/resource.h>

#include <nova/graphics/shader.h>
#include <nova/graphics/material.h>
#include <nova/graphics/mesh.h>
#include <nova/graphics/image.h>
#include <nova/graphics/texture.h>

namespace nova::io
{

class ResourceManager
{
public:
  static void shutdown();

  static bool exists(const std::string& name);

  static auto begin() { return instance().m_resources.begin(); }
  static auto end() { return instance().m_resources.end(); }

  /** CREATE */

  static Ref<graphics::Material> create_material(const std::string& name);

  static Ref<graphics::Mesh> create_mesh(const std::string& name);
  static Ref<graphics::Mesh> create_mesh(const std::string& name, MeshPrimitive primitive);

  static Ref<core::Resource> create_texture(const std::string& name, uint32_t width,
                                            uint32_t height, uint32_t channels = 4);

  /** LOAD */
  static Ref<core::Resource> load_resource(const std::string& name);

  static Ref<graphics::Shader> load_shader(const std::string& name,
                                           const graphics::ShaderSource& source);
  static Ref<graphics::Shader> load_shader(const std::string& name,
                                           graphics::ShaderSource&& source);

  static Ref<graphics::Texture> load_texture(const std::string& name, const std::string& path);

private:
  ResourceManager() = default;
  static ResourceManager& instance();

  bool __exists(const std::string& name) const;

  /** CREATE */
  Ref<graphics::Material> __create_material(const std::string& name);

  Ref<graphics::Mesh> __create_mesh(const std::string& name);
  Ref<graphics::Mesh> __create_mesh(const std::string& name, MeshPrimitive primitive);

  Ref<core::Resource> __create_texture(const std::string& name, uint32_t width, uint32_t height,
                                       uint32_t channels = 4);

  /** LOAD */
  Ref<core::Resource> __load_resource(const std::string& name);

  Ref<graphics::Shader> __load_shader(const std::string& name,
                                      const graphics::ShaderSource& source);
  Ref<graphics::Shader> __load_shader(const std::string& name, graphics::ShaderSource&& source);

  Ref<graphics::Texture> __load_texture(const std::string& name, const std::string& path);

private:
  std::unordered_map<std::string, Ref<core::Resource>> m_resources;
};

}  // namespace nova::io