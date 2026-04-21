#pragma once

#include <nova/core/entity_manager.h>

#include <nova/core/systems/system.h>

namespace nova::core::systems
{

class RenderSystem : public System
{
public:
  RenderSystem() = default;

  void update(float delta_time, EntityManager& entity_manager);

private:
};

}  // namespace nova::core::systems