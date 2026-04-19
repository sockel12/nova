#include <nova/graphics/graphics_api.h>

namespace nova::graphics
{

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

}  // namespace nova::graphics