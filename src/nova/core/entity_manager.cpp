#include <nova/core/entity_manager.h>

#include <nova/core/entity.h>

#include <nova/core/components/tag_component.h>
#include <nova/core/components/transform_component.h>

namespace nova::core
{

EntityManager::EntityManager() = default;

Entity EntityManager::create_entity(const std::string& name)
{
  entt::entity entity = m_registry.create();
  m_registry.emplace<components::TagComponent>(entity, name);
  m_registry.emplace<components::TransformComponent>(entity);
  return Entity(entity, this);
}

void EntityManager::remove_entity(const Entity& entity) { m_registry.destroy(entity.handle()); }

}  // namespace nova::core