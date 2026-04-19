#include <nova/graphics/buffers/vertex_buffer_layout.h>

namespace nova::graphics::buffers
{

VertexBufferElement::VertexBufferElement(const std::string& name, ShaderDataType type,
                                         bool normalized)
    : m_name(name), m_type(type), m_normalized(normalized)
{
}

VertexBufferLayout::VertexBufferLayout() {}

VertexBufferLayout::VertexBufferLayout(std::initializer_list<VertexBufferElement> elements)
{
  for (const auto& element : elements)
  {
    emplace_back(element);
  }
}

void VertexBufferLayout::emplace_back(VertexBufferElement element)
{
  element.offset(m_stride);
  m_stride += shader_data_type_size(element.type());
  m_elements.emplace_back(element);
}

void VertexBufferLayout::emplace_back(const std::string& name, ShaderDataType type, bool normalized)
{
  VertexBufferElement element(name, type, normalized);
  element.offset(m_stride);
  m_stride += shader_data_type_size(type);
  m_elements.emplace_back(element);
}

}  // namespace nova::graphics::buffers