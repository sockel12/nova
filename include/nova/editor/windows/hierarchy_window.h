#pragma once

#include <nova/editor/editor_gui_context.h>
#include <nova/editor/editor_gui_window.h>

namespace nova::editor::windows
{

class HierarchyWindow : public EditorGUIWindow
{
public:
  HierarchyWindow(const std::string& name = "Hierarchy");

  void on_imgui_render(EditorGUIContext& context) override;
};

}  // namespace nova::editor::windows