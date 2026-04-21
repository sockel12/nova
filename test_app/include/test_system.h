#pragma once

#include <nova/nova.h>

#include <nova/core/components/render_component.h>

class TestSystem : public nova::core::systems::System
{
public:
  void on_update(double delta_time, nova::core::EntityManager& entity_manager) override
  {
    auto view = entity_manager.view<nova::core::components::TransformComponent,
                                    nova::core::components::RenderComponent>();

    view.each(
        [delta_time](auto& transform, auto& render_component)
        {
          transform.scale.x = 0.5f + 0.125f * std::sin(glfwGetTime());
          transform.scale.y = 0.5f + 0.125f * std::sin(glfwGetTime());
          transform.rotation.z += 15.0f * static_cast<float>(delta_time);
        });
  }
};
