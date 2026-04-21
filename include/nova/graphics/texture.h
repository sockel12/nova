#pragma once

#include <nova/common.h>

namespace nova::graphics
{

class Texture
{
public:
  virtual ~Texture() = default;

  virtual void bind() const = 0;
  virtual void unbind() const = 0;

  virtual void resize(uint32_t width, uint32_t height) = 0;

  static Ref<Texture> create(uint32_t width, uint32_t height);

protected:
  Texture() = default;
};

}  // namespace nova::graphics