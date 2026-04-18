#include <nova/graphics/opengl/gl_shader.h>
#include "nova/core/logger.h"

namespace nova::graphics::opengl
{

GLShader::GLShader() : m_program_id(0) {}

GLShader::GLShader(const ShaderSource& source) : m_program_id(0) { load(source); }

GLShader::~GLShader()
{
  if (m_program_id != 0)
    GL_CALL(glDeleteProgram(m_program_id));
  if (m_vertex_shader_id != 0)
    GL_CALL(glDeleteShader(m_vertex_shader_id));
  if (m_fragment_shader_id != 0)
    GL_CALL(glDeleteShader(m_fragment_shader_id));
}

bool GLShader::valid() const { return m_program_id != 0; }

bool GLShader::load(const ShaderSource& source)
{
  Shader::load(source);

  m_vertex_shader_id = compile_shader(m_source.vertex_shader(), GlShaderType::VERTEX_SHADER);
  if (m_vertex_shader_id == 0)
  {
    return false;
  }

  m_fragment_shader_id = compile_shader(m_source.fragment_shader(), GlShaderType::FRAGMENT_SHADER);
  if (m_fragment_shader_id == 0)
  {
    GL_CALL(glDeleteShader(m_vertex_shader_id));
    return false;
  }

  m_program_id = link_program(m_vertex_shader_id, m_fragment_shader_id);
  if (m_program_id == 0)
  {
    GL_CALL(glDeleteShader(m_vertex_shader_id));
    GL_CALL(glDeleteShader(m_fragment_shader_id));
    return false;
  }

  return true;
}

void GLShader::bind() const { GL_CALL(glUseProgram(m_program_id)); }

void GLShader::unbind() const { GL_CALL(glUseProgram(0)); }

GLuint GLShader::compile_shader(const std::string& source, GlShaderType type)
{
  GLuint shader_id;
  GL_CALL(shader_id = glCreateShader(static_cast<GLenum>(type)));

  const char* source_cstr = source.c_str();
  GL_CALL(glShaderSource(shader_id, 1, &source_cstr, nullptr));
  GL_CALL(glCompileShader(shader_id));

  GLint success;
  GL_CALL(glGetShaderiv(shader_id, GL_COMPILE_STATUS, &success));
  if (!success)
  {
    GLchar info_log[512];
    GL_CALL(glGetShaderInfoLog(shader_id, 512, nullptr, info_log));
    core::logger()->error("Failed to compile {} shader: {}",
                          type == GlShaderType::VERTEX_SHADER ? "vertex" : "fragment", info_log);
    core::logger()->error("Source:\n{}", source);
    GL_CALL(glDeleteShader(shader_id));
    return 0;
  }

  return shader_id;
}

GLuint GLShader::link_program(GLuint vertex_shader_id, GLuint fragment_shader_id)
{
  GLuint program_id;
  GL_CALL(program_id = glCreateProgram());
  GL_CALL(glAttachShader(program_id, vertex_shader_id));
  GL_CALL(glAttachShader(program_id, fragment_shader_id));
  GL_CALL(glLinkProgram(program_id));

  GLint success;
  GL_CALL(glGetProgramiv(program_id, GL_LINK_STATUS, &success));
  if (!success)
  {
    GLchar info_log[512];
    GL_CALL(glGetProgramInfoLog(program_id, 512, nullptr, info_log));
    core::logger()->error("Failed to link shader program: {}", info_log);
    GL_CALL(glDeleteProgram(program_id));
    return 0;
  }

  return program_id;
}

}  // namespace nova::graphics::opengl