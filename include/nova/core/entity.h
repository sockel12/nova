#pragma once

#include <entt/entt.hpp>

#include <nova/core/entity_manager.h>

namespace nova::core
{

class Entity
{
public:
  Entity(const entt::entity& entity, EntityManager* entity_manager);

  template <typename T, typename... Args>
  T& add_component(Args&&... args);

  template <typename T>
  T& get_component()
  {
    return m_entity_manager->get<T>(m_handle);
  }

  template <typename... Components>
  auto get_components()
  {
    return m_entity_manager->view<Components...>();
  }

  template <typename T>
  bool has_component();

  operator bool() const { return m_handle != entt::null; }

  entt::entity handle() const { return m_handle; }

private:
  entt::entity m_handle;
  EntityManager* m_entity_manager;
};

template <typename T, typename... Args>
T& Entity::add_component(Args&&... args)
{
  return m_entity_manager->add_component<T>(m_handle, std::forward<Args>(args)...);
}

template <typename T>
bool Entity::has_component()
{
  return m_entity_manager->has_component<T>(m_handle);
}

}  // namespace nova::core