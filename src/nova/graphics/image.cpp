#include <nova/graphics/image.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <nova/core/logger.h>

namespace nova::graphics
{

Image::~Image()
{
  if (m_data.data)
  {
    stbi_image_free(m_data.data);
  }
}

Ref<Image> Image::load(const std::string& path)
{
  Ref<Image> image = std::make_shared<Image>();

  // stbi_set_flip_vertically_on_load(1);
  image->m_data.data = stbi_load(path.c_str(), &image->m_data.width, &image->m_data.height,
                                 &image->m_data.channels, 0);

  if (!image->m_data.data)
  {
    core::logger()->error("Failed to load image: {}", path);
    return nullptr;
  }

  return image;
}

}  // namespace nova::graphics
