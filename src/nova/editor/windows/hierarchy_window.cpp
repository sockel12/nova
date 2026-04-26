#include <nova/editor/windows/hierarchy_window.h>

#include <nova/core/components/tag_component.h>

#include <imgui.h>

namespace nova::editor::windows
{
HierarchyWindow::HierarchyWindow(const std::string& name) : EditorGUIWindow(name) {}

void HierarchyWindow::on_imgui_render(EditorGUIContext& context)
{
  auto view =
      context.active_scene->entity_manager().registry().view<core::components::TagComponent>();

  auto storage = view.storage<core::components::TagComponent>();

  for (auto [entity, tag_component] : view->reach())
  {
    bool selected = (context.selected_entity == entity);

    if (ImGui::Selectable(tag_component.tag.c_str(), selected))
    {
      if (selected)
      {
        context.selected_entity = entt::null;
      }
      else
      {
        context.selected_entity = entity;
      }
    }
  }
}

}  // namespace nova::editor::windows