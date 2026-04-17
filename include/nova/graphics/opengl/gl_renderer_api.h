#pragma once

#include <nova/graphics/renderer/renderer_api.h>

namespace nova::graphics::opengl
{

class GLRendererAPI : public graphics::renderer::RendererAPI
{
public:
  GLRendererAPI() = default;
  ~GLRendererAPI() override = default;

  void init() override;
  void shutdown() override;

  void set_viewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) override;

  void set_clear_color(float r, float g, float b, float a) override;
  void clear() override;

  void draw_indexed(uint32_t indexCount) override;
  void draw_arrays(graphics::renderer::PrimitiveType type, uint32_t count) override;

  void set_depth_test(bool enabled) override;
  void set_blend(bool enabled) override;

private:
};

}  // namespace nova::graphics::opengl
