#pragma once

#include <nova/common.h>

#include <nova/core/resource.h>

#include <nova/graphics/shader.h>

namespace nova::graphics
{

class Material : public core::Resource
{
public:
  Material() = default;

  core::ResourceType type() const override { return core::ResourceType::MATERIAL; }

  void shader(const Ref<Shader>& shader) { m_shader = shader; }
  const Ref<Shader>& shader() const { return m_shader; }

  void set_uniform(const std::string& name, const UniformValue& value);
  std::vector<std::pair<std::string, UniformValue>> uniforms() const;

  void bind() const;
  void unbind() const;

  static Ref<Material> create();

private:
  void __set_uniform(const std::string& name, const UniformValue& value) const;
  void __set_uniform(const std::string& name, const UniformValue& value,
                     uint32_t& texture_slot) const;

private:
  Ref<Shader> m_shader;
  std::unordered_map<std::string, UniformValue> m_uniforms;
};

}  // namespace nova::graphics