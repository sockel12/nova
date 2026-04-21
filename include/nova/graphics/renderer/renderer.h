#pragma once

#include <memory>

#include <nova/graphics/graphics_api.h>

#include <nova/graphics/mesh.h>
#include <nova/graphics/material.h>

#include <nova/graphics/renderer/renderer_api.h>

namespace nova::graphics::renderer
{

class Renderer
{
public:
  Renderer() = delete;

  static void init(GraphicsAPI graphics_api);
  static void shutdown();

  static void submit(const std::shared_ptr<Mesh>& mesh, const std::shared_ptr<Material>& material);

  static void clear();
  static void set_clear_color(const glm::vec4& color);
  static void set_clear_color(float r, float g, float b, float a);

private:
  static std::shared_ptr<RendererAPI> m_renderer_api;
};

}  // namespace nova::graphics::renderer