#pragma once

#include <nova/common.h>
#include <vector>

#include <nova/graphics/graphics_api.h>

#include <nova/graphics/buffers/buffer.h>

namespace nova::graphics::buffers
{

class IndexBuffer : public Buffer
{
public:
  virtual ~IndexBuffer() = default;

  virtual void data(const uint32_t* data, size_t count) = 0;
  virtual void data(const std::vector<uint32_t>& data) = 0;

  virtual size_t count() const = 0;

  static Ref<IndexBuffer> create(GraphicsAPI api);
};

}  // namespace nova::graphics::buffers