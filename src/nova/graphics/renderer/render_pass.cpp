#include <nova/graphics/renderer/render_pass.h>

#include <nova/graphics/renderer/renderer.h>

namespace nova::graphics::renderer
{

RenderPass::RenderPass() = default;

RenderPass::~RenderPass() = default;

bool RenderPass::init(uint32_t width, uint32_t height)
{
  m_frame_buffer = buffers::FrameBuffer::create(width, height);
  m_frame_buffer->unbind();
  m_valid = true;
  return true;
}

void RenderPass::begin(const core::Scene& scene)
{
  m_frame_buffer->bind();

  graphics::renderer::Renderer::set_clear_color(scene.settings().clear_color);

  graphics::renderer::Renderer::clear();
}

void RenderPass::render(const core::Scene& scene) { scene.draw(); }

void RenderPass::end() { m_frame_buffer->unbind(); }

}  // namespace nova::graphics::renderer