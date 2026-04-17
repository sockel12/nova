#pragma once

namespace nova::graphics::buffers
{

class Buffer
{
public:
  virtual ~Buffer() = default;

  virtual void bind() const = 0;
  virtual void unbind() const = 0;
};

}  // namespace nova::graphics::buffers