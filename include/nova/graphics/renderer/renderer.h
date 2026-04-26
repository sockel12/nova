#pragma once

#include <nova/common.h>

#include <nova/graphics/graphics_api.h>

#include <nova/graphics/mesh.h>
#include <nova/graphics/material.h>

#include <nova/graphics/renderer/renderer_api.h>

namespace nova::graphics::renderer
{

struct RendererStatistics
{
  uint32_t draw_calls = 0;
  uint32_t submitted_meshes = 0;
  uint64_t submitted_indices = 0;
  uint64_t submitted_vertices = 0;
  double delta_time_s = 0.0;
  double frame_time_ms = 0.0;
  double fps = 0.0;

  double min_frame_time_ms = 0.0;
  double avg_frame_time_ms = 0.0;
  double max_frame_time_ms = 0.0;
};

class Renderer
{
public:
  Renderer() = delete;

  static void init(GraphicsAPI graphics_api);
  static void shutdown();

  static void begin_frame(double delta_time_s);
  static void end_frame();

  static const RendererStatistics& statistics();

  static void submit(const Ref<Mesh>& mesh, const Ref<Material>& material);

  static void clear();
  static void set_clear_color(const glm::vec3& color) { set_clear_color(glm::vec4(color, 1.0f)); }
  static void set_clear_color(const glm::vec4& color);
  static void set_clear_color(float r, float g, float b, float a);

private:
  static Ref<RendererAPI> m_renderer_api;
  static RendererStatistics m_statistics;
};

}  // namespace nova::graphics::renderer