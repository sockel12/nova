#pragma once

#include <string>

#include <nova/core/resource.h>

#include <nova/graphics/texture.h>
#include <nova/graphics/graphics_api.h>

namespace nova::graphics
{

struct ShaderSource
{
  std::string vertex_shader;
  std::string fragment_shader;
};

using UniformValue = std::variant<int, glm::ivec2, glm::ivec3, glm::ivec4, float, glm::vec2,
                                  glm::vec3, glm::vec4, glm::mat3, glm::mat4, Ref<Texture>>;

class Shader : public core::Resource
{
public:
  virtual ~Shader() = default;

  virtual bool valid() const = 0;

  virtual bool load(const ShaderSource& source);

  void set_uniform(const std::string& name, const UniformValue& value)
  {
    std::visit([&](auto&& arg) { set_uniform(name, arg); }, value);
  }

  virtual void set_uniform(const std::string& name, int value) = 0;
  virtual void set_uniform(const std::string& name, const glm::ivec2& value) = 0;
  virtual void set_uniform(const std::string& name, const glm::ivec3& value) = 0;
  virtual void set_uniform(const std::string& name, const glm::ivec4& value) = 0;
  virtual void set_uniform(const std::string& name, float value) = 0;
  virtual void set_uniform(const std::string& name, const glm::vec2& value) = 0;
  virtual void set_uniform(const std::string& name, const glm::vec3& value) = 0;
  virtual void set_uniform(const std::string& name, const glm::vec4& value) = 0;
  virtual void set_uniform(const std::string& name, const glm::mat3& value) = 0;
  virtual void set_uniform(const std::string& name, const glm::mat4& value) = 0;
  virtual void set_uniform(const std::string& name, const Ref<Texture>& texture) = 0;

  virtual void bind() const = 0;
  virtual void unbind() const = 0;

  static Ref<Shader> create();
  static Ref<Shader> create(const ShaderSource& source);

protected:
  ShaderSource m_source;
};

}  // namespace nova::graphics
