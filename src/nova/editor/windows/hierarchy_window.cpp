#include <nova/editor/windows/hierarchy_window.h>

#include <nova/core/components/tag_component.h>

#include <imgui.h>

namespace nova::editor::windows
{
HierarchyWindow::HierarchyWindow(const std::string& name) : EditorGUIWindow(name) {}

void HierarchyWindow::on_imgui_render(EditorGUIContext& context)
{
  auto view = context.active_scene->entity_manager().view<core::components::TagComponent>();

  view.each(
      [&](entt::entity entity, const core::components::TagComponent& tag)
      {
        bool selected = (context.selected_entity == entity);

        if (ImGui::Selectable(tag.tag.c_str(), selected))
        {
          context.selected_entity = entity;
        }
      });
}

}  // namespace nova::editor::windows