#pragma once

#include <nova/core/entity_manager.h>

namespace nova::core::systems
{

class System
{
public:
  virtual ~System() = default;

  virtual void update(float delta_time, EntityManager& entity_manager) = 0;
};

}  // namespace nova::core::systems