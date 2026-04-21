#pragma once

#include <nova/editor/editor_gui_context.h>
#include <nova/editor/editor_gui_window.h>

namespace nova::editor::windows
{

class InspectorWindow : public EditorGUIWindow
{
public:
  InspectorWindow(const std::string& name = "Inspector");

  void on_imgui_render(EditorGUIContext& context) override;
};

}  // namespace nova::editor::windows