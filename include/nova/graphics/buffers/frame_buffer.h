#pragma once

#include <nova/common.h>

#include <nova/graphics/texture.h>

namespace nova::graphics::buffers
{

class FrameBuffer
{
public:
  virtual ~FrameBuffer() = default;

  virtual const Ref<Texture>& color_texture() const = 0;

  virtual void bind() const = 0;
  virtual void unbind() const = 0;

  virtual void resize(uint32_t width, uint32_t height) = 0;

  static Ref<FrameBuffer> create(uint32_t width, uint32_t height);

private:
};

}  // namespace nova::graphics::buffers