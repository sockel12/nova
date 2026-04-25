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
    __set_uniform(name, value);
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
    uint32_t texture_slot = 0;
    for (const auto& [name, value] : m_uniforms)
    {
      __set_uniform(name, value, texture_slot);
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

void Material::__set_uniform(const std::string& name, const UniformValue& value) const
{
  m_shader->set_uniform(name, value);
}

void Material::__set_uniform(const std::string& name, const UniformValue& value,
                             uint32_t& texture_slot) const
{
  if (std::holds_alternative<Ref<Texture>>(value))
  {
    const auto& texture = std::get<Ref<Texture>>(value);
    if (texture)
    {
      texture->bind(texture_slot);
      __set_uniform(name, static_cast<int>(texture_slot));
      texture_slot++;
    }
  }
  else
  {
    m_shader->set_uniform(name, value);
  }
}

}  // namespace nova::graphics
