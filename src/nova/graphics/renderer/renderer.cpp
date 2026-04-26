#include <nova/graphics/renderer/renderer.h>

#include <nova/core/logger.h>

#include <nova/graphics/renderer/renderer_api.h>

#include <algorithm>
#include <array>
#include <numeric>

namespace nova::graphics::renderer
{

Ref<RendererAPI> Renderer::m_renderer_api = nullptr;
RendererStatistics Renderer::m_statistics = {};

constexpr std::size_t kFrameTimeWindowSize = 60;
std::array<double, kFrameTimeWindowSize> g_frame_time_window = {};
std::size_t g_frame_time_window_index = 0;
std::size_t g_frame_time_window_count = 0;

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

void Renderer::begin_frame(double delta_time_s)
{
  m_statistics.draw_calls = 0;
  m_statistics.submitted_meshes = 0;
  m_statistics.submitted_indices = 0;
  m_statistics.submitted_vertices = 0;

  m_statistics.delta_time_s = delta_time_s;
  m_statistics.frame_time_ms = delta_time_s * 1000.0;
  m_statistics.fps = delta_time_s > 0.0 ? 1.0 / delta_time_s : 0.0;

  g_frame_time_window[g_frame_time_window_index] = m_statistics.frame_time_ms;
  g_frame_time_window_index = (g_frame_time_window_index + 1) % kFrameTimeWindowSize;
  g_frame_time_window_count = std::min(g_frame_time_window_count + 1, kFrameTimeWindowSize);

  if (g_frame_time_window_count > 0)
  {
    auto [min_it, max_it] = std::minmax_element(g_frame_time_window.begin(),
                                                 g_frame_time_window.begin() + g_frame_time_window_count);
    m_statistics.min_frame_time_ms = *min_it;
    m_statistics.max_frame_time_ms = *max_it;
    m_statistics.avg_frame_time_ms = std::accumulate(g_frame_time_window.begin(),
                                                      g_frame_time_window.begin() + g_frame_time_window_count, 0.0) /
                                    g_frame_time_window_count;
  }
}

void Renderer::end_frame() {}

const RendererStatistics& Renderer::statistics() { return m_statistics; }

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

  const auto index_count = mesh->mesh_data().indices().size();
  m_renderer_api->draw_indexed(index_count);

  m_statistics.draw_calls++;
  m_statistics.submitted_meshes++;
  m_statistics.submitted_indices += index_count;
  m_statistics.submitted_vertices += mesh->mesh_data().vertices().size();

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