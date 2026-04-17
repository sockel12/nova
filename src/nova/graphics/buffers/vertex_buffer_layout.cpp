#include <nova/graphics/buffers/vertex_buffer_layout.h>

namespace nova::graphics::buffers
{

VertexBufferElement::VertexBufferElement(const std::string& name, ShaderDataType type,
                                         bool normalized)
    : m_name(name), m_type(type), m_normalized(normalized)
{
}

uint32_t shader_data_type_size(ShaderDataType type)
{
  switch (type)
  {
    case ShaderDataType::FLOAT:
      return 4;
    case ShaderDataType::FLOAT2:
      return 4 * 2;
    case ShaderDataType::FLOAT3:
      return 4 * 3;
    case ShaderDataType::FLOAT4:
      return 4 * 4;
    case ShaderDataType::MAT3:
      return 4 * 3 * 3;
    case ShaderDataType::MAT4:
      return 4 * 4 * 4;
    case ShaderDataType::INT:
      return 4;
    case ShaderDataType::INT2:
      return 4 * 2;
    case ShaderDataType::INT3:
      return 4 * 3;
    case ShaderDataType::INT4:
      return 4 * 4;
    default:
      return 0;
  }
}

uint32_t shader_data_type_component_count(ShaderDataType type)
{
  switch (type)
  {
    case ShaderDataType::FLOAT:
      return 1;
    case ShaderDataType::FLOAT2:
      return 2;
    case ShaderDataType::FLOAT3:
      return 3;
    case ShaderDataType::FLOAT4:
      return 4;
    case ShaderDataType::MAT3:
      return 3 * 3;
    case ShaderDataType::MAT4:
      return 4 * 4;
    case ShaderDataType::INT:
      return 1;
    case ShaderDataType::INT2:
      return 2;
    case ShaderDataType::INT3:
      return 3;
    case ShaderDataType::INT4:
      return 4;
    default:
      return 0;
  }
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