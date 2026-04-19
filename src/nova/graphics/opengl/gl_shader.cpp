#include <nova/graphics/opengl/gl_shader.h>

#include <nova/core/logger.h>

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

void GLShader::set_uniform_int(const std::string& name, int value)
{
  GLint location = get_uniform_location(name);
  if (location != -1)
    GL_CALL(glUniform1i(location, value));
}

void GLShader::set_uniform_int2(const std::string& name, const glm::ivec2& value)
{
  GLint location = get_uniform_location(name);
  if (location != -1)
    GL_CALL(glUniform2i(location, value.x, value.y));
}

void GLShader::set_uniform_int3(const std::string& name, const glm::ivec3& value)
{
  GLint location = get_uniform_location(name);
  if (location != -1)
    GL_CALL(glUniform3i(location, value.x, value.y, value.z));
}

void GLShader::set_uniform_int4(const std::string& name, const glm::ivec4& value)
{
  GLint location = get_uniform_location(name);
  if (location != -1)
    GL_CALL(glUniform4i(location, value.x, value.y, value.z, value.w));
}

void GLShader::set_uniform_float(const std::string& name, float value)
{
  GLint location = get_uniform_location(name);
  if (location != -1)
    GL_CALL(glUniform1f(location, value));
}

void GLShader::set_uniform_float2(const std::string& name, const glm::vec2& value)
{
  GLint location = get_uniform_location(name);
  if (location != -1)
    GL_CALL(glUniform2f(location, value.x, value.y));
}

void GLShader::set_uniform_float3(const std::string& name, const glm::vec3& value)
{
  GLint location = get_uniform_location(name);
  if (location != -1)
    GL_CALL(glUniform3f(location, value.x, value.y, value.z));
}

void GLShader::set_uniform_float4(const std::string& name, const glm::vec4& value)
{
  GLint location = get_uniform_location(name);
  if (location != -1)
    GL_CALL(glUniform4f(location, value.x, value.y, value.z, value.w));
}

void GLShader::set_uniform_mat3(const std::string& name, const glm::mat3& value)
{
  GLint location = get_uniform_location(name);
  if (location != -1)
    GL_CALL(glUniformMatrix3fv(location, 1, GL_FALSE, &value[0][0]));
}

void GLShader::set_uniform_mat4(const std::string& name, const glm::mat4& value)
{
  GLint location = get_uniform_location(name);
  if (location != -1)
    GL_CALL(glUniformMatrix4fv(location, 1, GL_FALSE, &value[0][0]));
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

GLint GLShader::get_uniform_location(const std::string& name)
{
  if (m_uniform_location_cache.find(name) != m_uniform_location_cache.end())
    return m_uniform_location_cache[name];

  GLint location;
  GL_CALL(location = glGetUniformLocation(m_program_id, name.c_str()));
  if (location == -1)
  {
    core::logger()->warn("Uniform '{}' not found in shader", name);
    return -1;
  }
  m_uniform_location_cache[name] = location;
  return location;
}

}  // namespace nova::graphics::opengl