#pragma once

#include <memory>
#include <string>

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

  virtual void bind() const = 0;
  virtual void unbind() const = 0;

  static std::shared_ptr<Shader> create(GraphicsAPI api);
  static std::shared_ptr<Shader> create(GraphicsAPI api, const ShaderSource& source);

protected:
  ShaderSource m_source;
};

}  // namespace nova::graphics
