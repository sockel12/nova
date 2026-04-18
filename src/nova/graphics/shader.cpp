#include <nova/graphics/shader.h>

#include <nova/graphics/opengl/gl_shader.h>

namespace nova::graphics
{

ShaderSource::ShaderSource(const std::string& vertex, const std::string& fragment)
    : vertexShader(vertex), fragmentShader(fragment)
{
}

bool Shader::load(const ShaderSource& source)
{
  m_source = source;
  return true;
}

std::shared_ptr<Shader> Shader::create(GraphicsAPI api)
{
  switch (api)
  {
    case GraphicsAPI::OPENGL:
      return std::make_shared<opengl::GLShader>();
    default:
      core::logger()->error("Unsupported graphics API");
      return nullptr;
  }
}

std::shared_ptr<Shader> Shader::create(GraphicsAPI api, const ShaderSource& source)
{
  switch (api)
  {
    case GraphicsAPI::OPENGL:
      return std::make_shared<opengl::GLShader>(source);
    default:
      core::logger()->error("Unsupported graphics API");
      return nullptr;
  }
}

}  // namespace nova::graphics