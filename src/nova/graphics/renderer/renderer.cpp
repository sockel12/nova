#include <nova/graphics/renderer/renderer.h>

#include <nova/core/logger.h>

#include <nova/graphics/renderer/renderer_api.h>

namespace nova::graphics::renderer
{

std::shared_ptr<RendererAPI> Renderer::m_renderer_api = nullptr;

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

void Renderer::submit(const std::shared_ptr<Mesh>& mesh, const std::shared_ptr<Material>& material)
{
  if (!m_renderer_api || !m_renderer_api->initialized())
  {
    core::logger()->warn("RenderAPI is not initialized. Cannot submit draw call.");
    return;
  }

  material->bind();
  mesh->bind();
  m_renderer_api->draw_indexed(mesh->indices_count());
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