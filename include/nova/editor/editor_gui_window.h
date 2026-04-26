#pragma once

#include <nova/editor/editor_gui_context.h>

namespace nova::editor
{

class EditorGUIWindow
{
public:
  EditorGUIWindow(const std::string& name, bool menu_bar = false);
  virtual ~EditorGUIWindow() = default;

  const std::string& name() const { return m_name; }

  void visible(bool visible) { m_visible = visible; }
  bool visible() const { return m_visible; }

  void begin();
  void render(EditorGUIContext& context);
  void end();

protected:
  virtual void on_imgui_render(EditorGUIContext& context) = 0;

protected:
  std::string m_name;
  bool m_visible = true;
  bool m_menu_bar = false;
};

}  // namespace nova::editor