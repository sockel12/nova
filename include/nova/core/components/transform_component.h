#pragma once

#include <glm/glm.hpp>

namespace nova::core::components
{

class TransformComponent
{
public:
  TransformComponent() = default;

  glm::vec3 position{0.0f, 0.0f, 0.0f};
  glm::vec3 rotation{0.0f, 0.0f, 0.0f};
  glm::vec3 scale{1.0f, 1.0f, 1.0f};
};

}  // namespace nova::core::components