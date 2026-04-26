#include <nova/editor/windows/resource_viewer_window.h>

#include <imgui.h>

#include <nova/io/resource_manager.h>

#include <nova/editor/editor_utils.h>

namespace nova::editor::windows
{
ResourceViewerWindow::ResourceViewerWindow(const std::string& name) : EditorGUIWindow(name) {}

void ResourceViewerWindow::on_imgui_render(EditorGUIContext& context)
{
  if (context.selected_resource.empty())
  {
    ImGui::Text("No resource selected.");
    return;
  }

  const auto& resource = io::ResourceManager::load_resource(context.selected_resource);

  if (!resource)
  {
    ImGui::Text("Failed to load resource '%s'.", context.selected_resource.c_str());
    return;
  }

  ImGui::Text("Resource Name: %s", context.selected_resource.c_str());
  EditorUtils::display_resource(resource);
}

}  // namespace nova::editor::windows