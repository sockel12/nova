#include <nova/graphics/renderer/render_command.h>

#include <nova/graphics/renderer/renderer_api.h>

namespace nova::graphics::renderer
{

Ref<RendererAPI> RenderCommand::s_renderer_api = nullptr;

void RenderCommand::init(graphics::GraphicsAPI api)
{
  s_renderer_api = RendererAPI::create(api);
  s_renderer_api->init();
}

void RenderCommand::shutdown() { s_renderer_api->shutdown(); }

void RenderCommand::begin_frame() {}

void RenderCommand::end_frame() {}

void RenderCommand::set_viewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
{
  s_renderer_api->set_viewport(x, y, width, height);
}

void RenderCommand::set_clear_color(float r, float g, float b, float a)
{
  s_renderer_api->set_clear_color(r, g, b, a);
}

void RenderCommand::clear() { s_renderer_api->clear(); }

void RenderCommand::draw_indexed(uint32_t indexCount) { s_renderer_api->draw_indexed(indexCount); }

void RenderCommand::draw_arrays(PrimitiveType type, uint32_t count)
{
  s_renderer_api->draw_arrays(type, count);
}

void RenderCommand::set_depth_test(bool enabled) { s_renderer_api->set_depth_test(enabled); }

void RenderCommand::set_blend(bool enabled) { s_renderer_api->set_blend(enabled); }

}  // namespace nova::graphics::renderer