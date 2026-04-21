#pragma once

#include <memory>

namespace nova::grapgics
{

class Texture
{
public:
  virtual ~Texture() = default;

  virtual void bind() const = 0;
  virtual void unbind() const = 0;

  virtual void resize(uint32_t width, uint32_t height) = 0;

  static std::shared_ptr<Texture> create(uint32_t width, uint32_t height);

protected:
  Texture() = default;
};

}  // namespace nova::grapgics