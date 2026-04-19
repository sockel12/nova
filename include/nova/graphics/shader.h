#pragma once

#include <memory>
#include <string>

#include <glm/glm.hpp>

#include <nova/graphics/graphics_api.h>

namespace nova::graphics
{

class ShaderSource
{
public:
  ShaderSource() = default;
  ShaderSource(const std::string& vertex, const std::string& fragment);

  const std::string& vertex_shader() const { return vertexShader; }
  const std::string& fragment_shader() const { return fragmentShader; }

private:
  std::string vertexShader;
  std::string fragmentShader;
};

class Shader
{
public:
  virtual ~Shader() = default;

  virtual bool valid() const = 0;

  virtual bool load(const ShaderSource& source);

  virtual void set_uniform_int(const std::string& name, int value) = 0;
  virtual void set_uniform_int2(const std::string& name, const glm::ivec2& value) = 0;
  virtual void set_uniform_int3(const std::string& name, const glm::ivec3& value) = 0;
  virtual void set_uniform_int4(const std::string& name, const glm::ivec4& value) = 0;

  virtual void set_uniform_float(const std::string& name, float value) = 0;
  virtual void set_uniform_float2(const std::string& name, const glm::vec2& value) = 0;
  virtual void set_uniform_float3(const std::string& name, const glm::vec3& value) = 0;
  virtual void set_uniform_float4(const std::string& name, const glm::vec4& value) = 0;

  virtual void set_uniform_mat3(const std::string& name, const glm::mat3& value) = 0;
  virtual void set_uniform_mat4(const std::string& name, const glm::mat4& value) = 0;

  virtual void bind() const = 0;
  virtual void unbind() const = 0;

  static std::shared_ptr<Shader> create(GraphicsAPI api);
  static std::shared_ptr<Shader> create(GraphicsAPI api, const ShaderSource& source);

protected:
  ShaderSource m_source;
};

}  // namespace nova::graphics
