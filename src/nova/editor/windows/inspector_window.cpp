#include <nova/editor/windows/inspector_window.h>

#include <nova/core/components/tag_component.h>

#include <imgui.h>
#include "nova/core/components/transform_component.h"

namespace nova::editor::windows
{
InspectorWindow::InspectorWindow(const std::string& name) : EditorGUIWindow(name) {}

void InspectorWindow::on_imgui_render(EditorGUIContext& context)
{
  if (context.selected_entity == entt::null)
  {
    ImGui::Text("No entity selected");
    return;
  }

  auto [tag_component, transform_component] =
      context.active_scene->entity_manager()
          .registry()
          .get<core::components::TagComponent, core::components::TransformComponent>(
              context.selected_entity);

  ImGui::Text("Tag: %s", tag_component.tag.c_str());
  ImGui::Separator();
  ImGui::InputFloat3("Position", &transform_component.position.x);
  ImGui::InputFloat3("Rotation", &transform_component.rotation.x);
  ImGui::InputFloat3("Scale", &transform_component.scale.x);

  ImGui::Separator();
}

}  // namespace nova::editor::windows