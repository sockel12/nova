#pragma once

#include <nova/common.h>

#include <nova/core/resource.h>

#include <nova/graphics/image.h>

namespace nova::graphics
{

struct TextureData
{
  uint32_t width;
  uint32_t height;
  uint32_t channels;
};

class Texture : public core::Resource
{
public:
  Texture(uint32_t width, uint32_t height, uint32_t channels);
  virtual ~Texture() = default;

  core::ResourceType type() const override { return core::ResourceType::TEXTURE_2D; }

  float get_aspect_ratio() const
  {
    return static_cast<float>(m_data.width) / static_cast<float>(m_data.height);
  }

  virtual uint32_t texture_id() const = 0;

  const TextureData& data() const { return m_data; }

  virtual void bind(uint32_t slot = 0) const = 0;
  virtual void unbind() const = 0;

  virtual void resize(uint32_t width, uint32_t height, uint32_t channels = 4) = 0;

  static Ref<Texture> create(uint32_t width, uint32_t height, uint32_t channels = 4,
                             void* data = nullptr);

protected:
  TextureData m_data;
};

}  // namespace nova::graphics