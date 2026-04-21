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
    m_elements.emplace_back(element);
  }

  update();
}

void VertexBufferLayout::update()
{
  m_stride = 0;
  for (auto& element : m_elements)
  {
    element.offset(m_stride);
    m_stride += shader_data_type_size(element.type());
  }
}

template <>
void VertexBufferLayout::push<float>(const std::string& name, bool normalized)
{
  m_elements.emplace_back(name, ShaderDataType::FLOAT, normalized);
}

template <>
void VertexBufferLayout::push<glm::vec2>(const std::string& name, bool normalized)
{
  m_elements.emplace_back(name, ShaderDataType::FLOAT2, normalized);
}

template <>
void VertexBufferLayout::push<glm::vec3>(const std::string& name, bool normalized)
{
  m_elements.emplace_back(name, ShaderDataType::FLOAT3, normalized);
}

template <>
void VertexBufferLayout::push<glm::vec4>(const std::string& name, bool normalized)
{
  m_elements.emplace_back(name, ShaderDataType::FLOAT4, normalized);
}

template <>
void VertexBufferLayout::push<int>(const std::string& name, bool normalized)
{
  m_elements.emplace_back(name, ShaderDataType::INT, normalized);
}

template <>
void VertexBufferLayout::push<glm::ivec2>(const std::string& name, bool normalized)
{
  m_elements.emplace_back(name, ShaderDataType::INT2, normalized);
}

template <>
void VertexBufferLayout::push<glm::ivec3>(const std::string& name, bool normalized)
{
  m_elements.emplace_back(name, ShaderDataType::INT3, normalized);
}

template <>
void VertexBufferLayout::push<glm::ivec4>(const std::string& name, bool normalized)
{
  m_elements.emplace_back(name, ShaderDataType::INT4, normalized);
}

template <>
void VertexBufferLayout::push<glm::mat3>(const std::string& name, bool normalized)
{
  m_elements.emplace_back(name, ShaderDataType::MAT3, normalized);
}

template <>
void VertexBufferLayout::push<glm::mat4>(const std::string& name, bool normalized)
{
  m_elements.emplace_back(name, ShaderDataType::MAT4, normalized);
}

}  // namespace nova::graphics::buffers