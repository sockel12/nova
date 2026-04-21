#include <nova/editor/editor_gui_window.h>

#include <imgui.h>

namespace nova::editor
{

EditorGUIWindow::EditorGUIWindow(const std::string& name) : m_name(name) {}

void EditorGUIWindow::begin() { ImGui::Begin(m_name.c_str()); }

void EditorGUIWindow::render(EditorGUIContext& context)
{
  begin();
  on_imgui_render(context);
  end();
}

void EditorGUIWindow::end() { ImGui::End(); }

}  // namespace nova::editor