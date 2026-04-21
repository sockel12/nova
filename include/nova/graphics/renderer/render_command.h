#pragma once

#include <nova/common.h>

#include <nova/graphics/graphics_api.h>

#include <nova/graphics/renderer/renderer_api.h>

namespace nova::graphics::renderer
{

class RenderCommand
{
public:
  static void init(graphics::GraphicsAPI api);
  static void shutdown();

  static void begin_frame();
  static void end_frame();

  static void set_viewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height);

  static void set_clear_color(float r, float g, float b, float a);
  static void clear();

  static void draw_indexed(uint32_t indexCount);
  static void draw_arrays(PrimitiveType type, uint32_t count);

  static void set_depth_test(bool enabled);
  static void set_blend(bool enabled);

private:
  static Ref<RendererAPI> s_renderer_api;
};

}  // namespace nova::graphics::renderer