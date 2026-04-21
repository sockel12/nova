#include <nova/graphics/renderer/renderer.h>

#include <nova/core/logger.h>

#include <nova/graphics/renderer/renderer_api.h>

namespace nova::graphics::renderer
{

Ref<RendererAPI> Renderer::m_renderer_api = nullptr;

void Renderer::init(GraphicsAPI graphics_api)
{
  m_renderer_api = RendererAPI::create(graphics_api);
  m_renderer_api->init();

  if (!m_renderer_api || !m_renderer_api->initialized())
  {
    core::logger()->error("Failed to initialize RendererAPI.");
  }
}

void Renderer::shutdown()
{
  if (!m_renderer_api || !m_renderer_api->initialized())
  {
    core::logger()->warn("RendererAPI is not initialized. Cannot shutdown.");
    return;
  }

  m_renderer_api->shutdown();
}

void Renderer::submit(const Ref<Mesh>& mesh, const Ref<Material>& material)
{
  if (!m_renderer_api || !m_renderer_api->initialized())
  {
    core::logger()->warn("RenderAPI is not initialized. Cannot submit draw call.");
    return;
  }

  if (!material || !material->shader())
  {
    core::logger()->warn("Material or shader is null. Cannot submit draw call.");
    return;
  }

  if (!mesh)
  {
    core::logger()->warn("Mesh is null. Cannot submit draw call.");
    return;
  }

  material->bind();
  mesh->bind();
  m_renderer_api->draw_indexed(mesh->mesh_data().indices().size());
  mesh->unbind();
  material->unbind();
}

void Renderer::clear()
{
  if (!m_renderer_api || !m_renderer_api->initialized())
  {
    core::logger()->warn("RenderAPI is not initialized. Cannot clear screen.");
    return;
  }

  m_renderer_api->clear();
}

void Renderer::set_clear_color(const glm::vec4& color)
{
  set_clear_color(color.r, color.g, color.b, color.a);
}

void Renderer::set_clear_color(float r, float g, float b, float a)
{
  if (!m_renderer_api || !m_renderer_api->initialized())
  {
    core::logger()->warn("RenderAPI is not initialized. Cannot set clear color.");
    return;
  }

  m_renderer_api->set_clear_color(r, g, b, a);
}

}  // namespace nova::graphics::renderer