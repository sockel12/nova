#pragma once

#include <nova/nova.h>

#include <nova/core/components/render_component.h>

struct RotationComponent
{
  float rotation_speed = 15.0f;
};

struct PulsatingComponent
{
  float pulse_speed = 1.0f;
};

class RotationSystem : public nova::core::systems::System
{
public:
  void on_update(double delta_time, nova::core::EntityManager& entity_manager) override
  {
    auto view =
        entity_manager.view<nova::core::components::TransformComponent, RotationComponent>();

    view.each(
        [delta_time](auto& transform, auto& rotation_component) {
          transform.rotation.z +=
              rotation_component.rotation_speed * static_cast<float>(delta_time);
        });
  }
};

class PulsatingSystem : public nova::core::systems::System
{
public:
  void on_update(double delta_time, nova::core::EntityManager& entity_manager) override
  {
    auto view =
        entity_manager.view<nova::core::components::TransformComponent, PulsatingComponent>();

    view.each(
        [delta_time](auto& transform, auto& pulsating_component)
        {
          transform.scale.x =
              0.5f + 0.125f * std::sin(glfwGetTime()) * pulsating_component.pulse_speed;
          transform.scale.y =
              0.5f + 0.125f * std::sin(glfwGetTime()) * pulsating_component.pulse_speed;
        });
  }
};
