#pragma once

#include <string>

#include <entt/entt.hpp>

namespace nova::core
{
class Entity;

class EntityManager
{
  friend class Entity;

public:
  EntityManager();

  Entity create_entity(const std::string& name);
  void remove_entity(const Entity& entity);

  entt::registry& registry() { return m_registry; }
  const entt::registry& registry() const { return m_registry; }

  template <typename T, typename... Args>
  T& add_component(const entt::entity& entity, Args&&... args)
  {
    return m_registry.emplace<T>(entity, std::forward<Args>(args)...);
  }

  template <typename... Components>
  auto& get(entt::entity entity)
  {
    return m_registry.get<Components...>(entity);
  }

  template <typename... Components>
  auto view()
  {
    return m_registry.view<Components...>();
  }

  template <typename T>
  bool has_component(const entt::entity& entity)
  {
    return m_registry.all_of<T>(entity);
  }

  template <typename... Components>
  bool has_components(const entt::entity& entity)
  {
    return m_registry.all_of<Components...>(entity);
  }

private:
  entt::registry m_registry;
};

}  // namespace nova::core