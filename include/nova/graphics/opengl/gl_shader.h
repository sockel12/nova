#pragma once

#include <string>
#include <unordered_map>

#include <nova/graphics/shader.h>

#include <nova/graphics/opengl/opengl.h>

namespace nova::graphics::opengl
{

enum class GlShaderType
{
  VERTEX_SHADER = GL_VERTEX_SHADER,
  FRAGMENT_SHADER = GL_FRAGMENT_SHADER
};

class GLShader : public Shader
{
public:
  GLShader();
  GLShader(const ShaderSource& source);
  ~GLShader() override;

  bool valid() const override;

  bool load(const ShaderSource& source) override;

  void set_uniform_int(const std::string& name, int value) override;
  void set_uniform_int2(const std::string& name, const glm::ivec2& value) override;
  void set_uniform_int3(const std::string& name, const glm::ivec3& value) override;
  void set_uniform_int4(const std::string& name, const glm::ivec4& value) override;
  void set_uniform_float(const std::string& name, float value) override;
  void set_uniform_float2(const std::string& name, const glm::vec2& value) override;
  void set_uniform_float3(const std::string& name, const glm::vec3& value) override;
  void set_uniform_float4(const std::string& name, const glm::vec4& value) override;
  void set_uniform_mat3(const std::string& name, const glm::mat3& value) override;
  void set_uniform_mat4(const std::string& name, const glm::mat4& value) override;

  void bind() const override;
  void unbind() const override;

private:
  GLuint compile_shader(const std::string& source, GlShaderType type);
  GLuint link_program(GLuint vertex_shader_id, GLuint fragment_shader_id);

  GLint get_uniform_location(const std::string& name);

private:
  GLuint m_program_id;
  GLuint m_vertex_shader_id;
  GLuint m_fragment_shader_id;

  std::unordered_map<std::string, GLint> m_uniform_location_cache;
};

}  // namespace nova::graphics::opengl