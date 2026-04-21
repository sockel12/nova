#include <nova/graphics/material.h>
#include "nova/application.h"

namespace nova::graphics
{

Material::Material(const std::shared_ptr<Shader>& shader) : m_shader(shader) {}

void Material::set_uniform(const std::string& name, const UniformValue& value)
{
  m_uniforms[name] = value;
  if (m_shader && m_shader->valid())
  {
    m_shader->set_uniform(name, value);
  }
}

std::vector<std::pair<std::string, UniformValue>> Material::uniforms() const
{
  std::vector<std::pair<std::string, UniformValue>> uniform_vector;
  for (const auto& [name, value] : m_uniforms)
  {
    uniform_vector.emplace_back(name, value);
  }
  return uniform_vector;
}

void Material::bind() const
{
  if (m_shader && m_shader->valid())
  {
    m_shader->bind();
    for (const auto& [name, value] : m_uniforms)
    {
      m_shader->set_uniform(name, value);
    }
  }
}

void Material::unbind() const
{
  if (m_shader && m_shader->valid())
  {
    m_shader->unbind();
  }
}

std::shared_ptr<Material> Material::create(const std::shared_ptr<Shader>& shader)
{
  if (!shader || !shader->valid())
  {
    core::logger()->error("Failed to create material: invalid shader");
    return nullptr;
  }
  return std::make_shared<Material>(shader);
}

std::shared_ptr<Material> Material::create(const graphics::ShaderSource& source)
{
  std::shared_ptr<Shader> shader = Shader::create(Application::graphics_api(), source);
  if (!shader || !shader->valid())
  {
    core::logger()->error("Failed to create shader for material");
    return nullptr;
  }
  return std::make_shared<Material>(shader);
}

}  // namespace nova::graphics
