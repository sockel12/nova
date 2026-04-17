#pragma once

#include <memory>
#include <cstdint>

#include <nova/graphics/graphics_api.h>

namespace nova::graphics::renderer
{

enum class PrimitiveType
{
  LINES,
  TRIANGLES
};

class RendererAPI
{
public:
  virtual ~RendererAPI() = default;

  virtual void init() = 0;
  virtual void shutdown() = 0;

  virtual void set_viewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) = 0;

  virtual void set_clear_color(float r, float g, float b, float a) = 0;
  virtual void clear() = 0;

  virtual void draw_indexed(uint32_t indexCount) = 0;
  virtual void draw_arrays(PrimitiveType type, uint32_t count) = 0;

  virtual void set_depth_test(bool enabled) = 0;
  virtual void set_blend(bool enabled) = 0;

  static std::shared_ptr<RendererAPI> create(graphics::GraphicsAPI api);
};

}  // namespace nova::graphics::renderer