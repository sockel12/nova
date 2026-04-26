#pragma once

#include <nova/common.h>

#include <nova/graphics/buffers/frame_buffer.h>
#include "nova/core/scene.h"

namespace nova::graphics::renderer
{

class RenderPass
{
public:
  RenderPass();
  ~RenderPass();

  const Ref<buffers::FrameBuffer>& frame_buffer() const { return m_frame_buffer; }

  bool init(uint32_t width, uint32_t height);

  void begin(const core::Scene& scene);
  void render(const core::Scene& scene);
  void end();

private:
  Ref<buffers::FrameBuffer> m_frame_buffer;
  bool m_valid = false;
};

}  // namespace nova::graphics::renderer