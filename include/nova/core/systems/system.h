#pragma once

#include <nova/core/entity_manager.h>

namespace nova::core::systems
{

class System
{
public:
  virtual ~System() = default;

  virtual void on_update(double delta_time, EntityManager& entity_manager) {}
  virtual void on_draw(EntityManager& entity_manager) {}
};

}  // namespace nova::core::systems