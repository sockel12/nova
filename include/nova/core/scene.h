#pragma once

#include <nova/common.h>

#include <nova/core/entity.h>
#include <nova/core/scene_settings.h>
#include <nova/core/entity_manager.h>

#include <nova/core/systems/system.h>

namespace nova::core
{

class Scene
{
public:
  Scene();

  EntityManager& entity_manager() { return *m_entity_manager; }
  const EntityManager& entity_manager() const { return *m_entity_manager; }

  SceneSettings& settings() { return m_settings; }
  const SceneSettings& settings() const { return m_settings; }

  Entity add_entity(const std::string& name);
  Entity get_entity(const std::string& name);
  void remove_entity(const Entity& entity);

  template <typename System>
  void add_system(const Ref<System>& system)
  {
    m_systems.emplace_back(system);
  }

  void update(double delta_time);

  void draw() const;

private:
  Ref<EntityManager> m_entity_manager;
  std::vector<Ref<systems::System>> m_systems;
  SceneSettings m_settings;
};

}  // namespace nova::core