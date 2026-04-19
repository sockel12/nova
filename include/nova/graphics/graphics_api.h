#pragma once

#include <cstdint>

namespace nova::graphics
{

enum class GraphicsAPI
{
  OPENGL = 1
};

enum class ShaderDataType
{
  FLOAT,
  FLOAT2,
  FLOAT3,
  FLOAT4,

  MAT3,
  MAT4,

  INT,
  INT2,
  INT3,
  INT4,
};

uint32_t shader_data_type_size(ShaderDataType type);
uint32_t shader_data_type_component_count(ShaderDataType type);

}  // namespace nova::graphics