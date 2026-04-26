#pragma once

#include <nova/core/resource.h>

#include <nova/graphics/texture.h>
#include <nova/graphics/material.h>
#include <nova/graphics/image.h>
#include <nova/graphics/shader.h>
#include <nova/graphics/mesh.h>

namespace nova::editor
{

class EditorUtils
{
public:
  static void display_resource(const Ref<core::Resource>& resource);
  static void display_texture(const Ref<graphics::Texture>& texture);
  static void display_material(const Ref<graphics::Material>& material);
  static void display_mesh(const Ref<graphics::Mesh>& mesh);
  static void display_shader(const Ref<graphics::Shader>& shader);
  static void display_uniform_value(const std::string& name, graphics::UniformValue& value);
};

}  // namespace nova::editor