#pragma once

#include <nova/editor/editor_gui_context.h>
#include <nova/editor/editor_gui_window.h>

namespace nova::editor::windows
{

class ResourceManagerWindow : public EditorGUIWindow
{
public:
  ResourceManagerWindow(const std::string& name = "Resource Manager");

  void on_imgui_render(EditorGUIContext& context) override;

private:
  entt::entity m_selected_entity = entt::null;
};

}  // namespace nova::editor::windows