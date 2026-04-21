#pragma once

#include <nova/editor/editor_gui_context.h>

namespace nova::editor
{

class EditorGUIWindow
{
public:
  EditorGUIWindow(const std::string& name);
  virtual ~EditorGUIWindow() = default;

  void begin();
  void render(EditorGUIContext& context);
  void end();

protected:
  virtual void on_imgui_render(EditorGUIContext& context) = 0;

protected:
  std::string m_name;
};

}  // namespace nova::editor