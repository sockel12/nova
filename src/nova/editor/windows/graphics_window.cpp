#include <nova/editor/windows/graphics_window.h>

#include <nova/core/components/render_component.h>
#include <nova/core/components/tag_component.h>

#include <imgui.h>

namespace nova::editor::windows
{
GraphicsWindow::GraphicsWindow(const std::string& name) : EditorGUIWindow(name) {}

void GraphicsWindow::on_imgui_render(EditorGUIContext& context)
{
  auto view = context.active_scene->entity_manager()
                  .registry()
                  .view<core::components::TagComponent, core::components::RenderComponent>();

  if (m_selected_entity != entt::null)
  {
    auto [tag, render] =
        context.active_scene->entity_manager()
            .registry()
            .get<core::components::TagComponent, core::components::RenderComponent>(
                m_selected_entity);

    ImGui::Text("Selected Entity: %s", tag.tag.c_str());
    if (render.mesh)
    {
      ImGui::Text("Vertices: %zu", render.mesh->mesh_data().vertices().size());
      ImGui::Text("Indices: %zu", render.mesh->mesh_data().indices().size());
    }
    else
    {
      ImGui::Text("Vertices: N/A");
      ImGui::Text("Indices: N/A");
    }

    if (render.material)
    {
      ImGui::Text("Uniforms:");
      for (const auto& [name, value] : render.material->uniforms())
      {
        ImGui::BulletText("%s", name.c_str());
      }
    }
    else
    {
      ImGui::Text("Uniforms: N/A");
    }
  }
  else
  {
    ImGui::Text("No entity selected");
  }

  ImGui::Separator();

  view.each(
      [&](entt::entity entity, const core::components::TagComponent& tag,
          const core::components::RenderComponent& render)
      {
        bool selected = (m_selected_entity == entity);

        if (ImGui::Selectable(tag.tag.c_str(), selected))
        {
          if (selected)
          {
            m_selected_entity = entt::null;
          }
          else
          {
            m_selected_entity = entity;
          }
        }
      });
}

}  // namespace nova::editor::windows