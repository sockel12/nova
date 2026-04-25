#pragma once

#include <nova/editor/editor_gui_context.h>
#include <nova/editor/editor_gui_window.h>

namespace nova::editor::windows
{

class GraphicsWindow : public EditorGUIWindow
{
public:
  GraphicsWindow(const std::string& name = "Graphics");

  void on_imgui_render(EditorGUIContext& context) override;

private:
  entt::entity m_selected_entity = entt::null;
};

}  // namespace nova::editor::windows