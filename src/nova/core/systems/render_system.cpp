#include <nova/core/systems/render_system.h>

#include <nova/core/components/render_component.h>

#include <nova/graphics/renderer/renderer.h>

namespace nova::core::systems
{

void RenderSystem::update(float delta_time, EntityManager& entity_manager)
{
  auto view = entity_manager.view<components::RenderComponent>();

  for (const auto& entity : view)
  {
    const auto& rc = view.get<components::RenderComponent>(entity);

    graphics::renderer::Renderer::submit(rc.mesh, rc.material);
  }
}

}  // namespace nova::core::systems