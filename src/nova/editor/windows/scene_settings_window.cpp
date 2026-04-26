#include <nova/editor/windows/scene_settings_window.h>

#include <imgui.h>

namespace nova::editor::windows
{
SceneSettingsWindow::SceneSettingsWindow(const std::string& name) : EditorGUIWindow(name) {}

void SceneSettingsWindow::on_imgui_render(EditorGUIContext& context)
{
  ImGui::ColorEdit3("Clear Color", &context.active_scene->settings().clear_color[0]);
}

}  // namespace nova::editor::windows