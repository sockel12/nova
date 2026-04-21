#pragma once

#include <nova/graphics/shader.h>

namespace nova::graphics
{

class Material
{
public:
  Material() = default;
  Material(const std::shared_ptr<Shader>& shader);

  void set_uniform(const std::string& name, const UniformValue& value);
  std::vector<std::pair<std::string, UniformValue>> uniforms() const;

  void bind() const;
  void unbind() const;

  static std::shared_ptr<Material> create(const std::shared_ptr<Shader>& shader);
  static std::shared_ptr<Material> create(const graphics::ShaderSource& source);

private:
  std::shared_ptr<Shader> m_shader;
  std::unordered_map<std::string, UniformValue> m_uniforms;
};

}  // namespace nova::graphics