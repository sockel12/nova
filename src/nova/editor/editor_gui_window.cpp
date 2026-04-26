#include <nova/editor/editor_gui_window.h>

#include <imgui.h>

namespace nova::editor
{

EditorGUIWindow::EditorGUIWindow(const std::string& name, bool menu_bar)
    : m_name(name), m_menu_bar(menu_bar)
{
}

void EditorGUIWindow::begin()
{
  ImGuiWindowFlags flags = 0;
  if (m_menu_bar)
    flags |= ImGuiWindowFlags_MenuBar;

  ImGui::Begin(m_name.c_str(), nullptr, flags);
}

void EditorGUIWindow::render(EditorGUIContext& context)
{
  begin();
  on_imgui_render(context);
  end();
}

void EditorGUIWindow::end() { ImGui::End(); }

}  // namespace nova::editor