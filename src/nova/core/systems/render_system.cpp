#include <nova/core/systems/render_system.h>

#include <nova/core/components/render_component.h>
#include <nova/core/components/transform_component.h>

#include <nova/graphics/renderer/renderer.h>

namespace nova::core::systems
{

void RenderSystem::on_draw(EntityManager& entity_manager)
{
  auto view = entity_manager.view<components::RenderComponent, components::TransformComponent>();

  view.each(
      [&](const auto& rc, const auto& transform)
      {
        if (!rc.material || !rc.mesh || !rc.material->shader())
        {
          return;
        }

        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, transform.position);
        model = glm::rotate(model, glm::radians(transform.rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
        model = glm::rotate(model, glm::radians(transform.rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::rotate(model, glm::radians(transform.rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
        model = glm::scale(model, transform.scale);

        rc.material->set_uniform("u_Model", model);
        graphics::renderer::Renderer::submit(rc.mesh, rc.material);
      });
}

}  // namespace nova::core::systems