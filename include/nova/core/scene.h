#pragma once

#include <memory>

#include <nova/core/entity.h>
#include <nova/core/entity_manager.h>

#include <nova/core/systems/system.h>

namespace nova::core
{

class Scene
{
public:
  Scene();

  Entity add_entity(const std::string& name);

  Entity get_entity(const std::string& name);

  void remove_entity(const Entity& entity);

  template <typename System>
  void add_system(const std::shared_ptr<System>& system)
  {
    m_systems.emplace_back(system);
  }

  template <typename System>
  void remove_system()
  {
    m_systems.erase(std::remove_if(m_systems.begin(), m_systems.end(),
                                   [](const std::shared_ptr<systems::System>& s)
                                   { return std::dynamic_pointer_cast<System>(s) != nullptr; }),
                    m_systems.end());
  }

  void update(float delta_time);

private:
  std::shared_ptr<EntityManager> m_entity_manager;
  std::vector<std::shared_ptr<systems::System>> m_systems;
};

}  // namespace nova::core