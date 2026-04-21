#include <nova/core/scene.h>

#include <nova/core/systems/render_system.h>
#include "nova/core/components/tag_component.h"

namespace nova::core
{

Scene::Scene() : m_entity_manager(std::make_shared<EntityManager>())
{
  add_system(std::make_shared<systems::RenderSystem>());
}

Entity Scene::add_entity(const std::string& name) { return m_entity_manager->create_entity(name); }

Entity Scene::get_entity(const std::string& name)
{
  auto view = m_entity_manager->view<components::TagComponent>();

  for (const auto& entity : view)
  {
    if (view.get<components::TagComponent>(entity).tag == name)
    {
      return Entity(entity, m_entity_manager.get());
    }
  }

  return Entity(entt::null, m_entity_manager.get());
}

void Scene::remove_entity(const Entity& entity) { m_entity_manager->remove_entity(entity); }

void Scene::update(float delta_time)
{
  for (auto& system : m_systems)
  {
    system->update(delta_time, *m_entity_manager);
  }
}

}  // namespace nova::core