#include <nova/graphics/shader.h>

#include <nova/application.h>

#include <nova/graphics/opengl/gl_shader.h>

namespace nova::graphics
{

bool Shader::load(const ShaderSource& source)
{
  m_source = source;
  return true;
}

Ref<Shader> Shader::create()
{
  switch (Application::graphics_api())
  {
    case GraphicsAPI::OPENGL:
      return std::make_shared<opengl::GLShader>();
    default:
      core::logger()->error("Unsupported graphics API");
      return nullptr;
  }
}

Ref<Shader> Shader::create(const ShaderSource& source)
{
  auto shader = create();
  if (shader && shader->load(source))
  {
    return shader;
  }
  core::logger()->error("Failed to create and load shader");
  return nullptr;
}

}  // namespace nova::graphics