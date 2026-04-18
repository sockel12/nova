#pragma once

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

  void bind() const override;
  void unbind() const override;

private:
  GLuint compile_shader(const std::string& source, GlShaderType type);
  GLuint link_program(GLuint vertex_shader_id, GLuint fragment_shader_id);

private:
  GLuint m_program_id;
  GLuint m_vertex_shader_id;
  GLuint m_fragment_shader_id;
};

}  // namespace nova::graphics::opengl