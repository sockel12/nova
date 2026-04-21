#include <nova/graphics/material.h>

#include <nova/application.h>

namespace nova::graphics
{

void Material::set_uniform(const std::string& name, const UniformValue& value)
{
  m_uniforms[name] = value;
  if (m_shader && m_shader->valid())
  {
    m_shader->bind();
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

Ref<Material> Material::create() { return std::make_shared<Material>(); }

}  // namespace nova::graphics
