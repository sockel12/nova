#include <nova/core/entity.h>

namespace nova::core
{

Entity::Entity(const entt::entity& entity, EntityManager* entity_manager)
    : m_handle(entity), m_entity_manager(entity_manager)
{
}

}  // namespace nova::core