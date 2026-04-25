#pragma once

#include <nova/common.h>

#include <nova/core/resource.h>

namespace nova::graphics
{

struct ImageData
{
  int width;
  int height;
  int channels;
  unsigned char* data;
};

class Image : public core::Resource
{
public:
  Image() = default;
  ~Image();

  const ImageData& data() const { return m_data; }

  static Ref<Image> load(const std::string& path);

private:
  ImageData m_data;
};

}  // namespace nova::graphics