#pragma once

#include <string>
#include <vector>
#include <cstdint>

#include <nova/graphics/graphics_api.h>

namespace nova::graphics::buffers
{

class VertexBufferElement
{
public:
  VertexBufferElement(const std::string& name, ShaderDataType type, bool normalized = false);

  const std::string& name() const { return m_name; }
  ShaderDataType type() const { return m_type; }
  bool normalized() const { return m_normalized; }

  void offset(uint32_t offset) { m_offset = offset; }
  uint32_t offset() const { return m_offset; }

private:
  std::string m_name;
  ShaderDataType m_type;
  bool m_normalized;
  uint32_t m_offset = 0;
};

class VertexBufferLayout
{
public:
  VertexBufferLayout();
  VertexBufferLayout(std::initializer_list<VertexBufferElement> elements);

  void update();

  template <typename T>
  void push(const std::string& name, bool normalized = false);

  uint32_t stride() const { return m_stride; }

  const std::vector<VertexBufferElement>& elements() const { return m_elements; }

private:
  std::vector<VertexBufferElement> m_elements;
  uint32_t m_stride = 0;
};

}  // namespace nova::graphics::buffers