#pragma once

#include <nova/core/resource.h>

#include <nova/graphics/shader.h>
#include <nova/graphics/material.h>
#include <nova/graphics/mesh.h>

namespace nova::io
{

class ResourceManager
{
public:
  static void shutdown();

  static bool exists(const std::string& name);

  static Ref<graphics::Material> create_material(const std::string& name);

  static Ref<graphics::Mesh> create_mesh(const std::string& name);
  static Ref<graphics::Mesh> create_mesh(const std::string& name, MeshPrimitive primitive);

  static Ref<core::Resource> load_resource(const std::string& name);

  static Ref<graphics::Shader> load_shader(const std::string& name,
                                           const graphics::ShaderSource& source);
  static Ref<graphics::Shader> load_shader(const std::string& name,
                                           const graphics::ShaderSource&& source);

private:
  ResourceManager() = default;
  static ResourceManager& instance();

  bool __exists(const std::string& name) const;

  /** Create resources */
  Ref<graphics::Material> __create_material(const std::string& name);

  Ref<graphics::Mesh> __create_mesh(const std::string& name);
  Ref<graphics::Mesh> __create_mesh(const std::string& name, MeshPrimitive primitive);

  /** Load resources */
  Ref<core::Resource> __load_resource(const std::string& name);

  Ref<graphics::Shader> __load_shader(const std::string& name,
                                      const graphics::ShaderSource& source);
  Ref<graphics::Shader> __load_shader(const std::string& name,
                                      const graphics::ShaderSource&& source);

private:
  std::unordered_map<std::string, Ref<core::Resource>> m_resources;
};

}  // namespace nova::io