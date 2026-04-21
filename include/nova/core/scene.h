#pragma once

#include <nova/common.h>

#include <nova/core/entity.h>
#include <nova/core/entity_manager.h>

#include <nova/core/systems/system.h>
#include "nova/core/systems/render_system.h"

namespace nova::core
{

class Scene
{
public:
  Scene();

  EntityManager& entity_manager() { return *m_entity_manager; }
  const EntityManager& entity_manager() const { return *m_entity_manager; }

  Entity add_entity(const std::string& name);
  Entity get_entity(const std::string& name);
  void remove_entity(const Entity& entity);

  template <typename System>
  void add_system(const Ref<System>& system)
  {
    m_systems.emplace_back(system);
  }

  template <typename System>
  void remove_system()
  {
    m_systems.erase(
        std::remove_if(m_systems.begin(), m_systems.end(), [](const Ref<systems::System>& s)
                       { return std::dynamic_pointer_cast<System>(s) != nullptr; }),
        m_systems.end());
  }

  void update(double delta_time);
  void draw();

private:
  Ref<EntityManager> m_entity_manager;
  std::vector<Ref<systems::System>> m_systems;
};

}  // namespace nova::core