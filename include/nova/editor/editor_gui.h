#pragma once

#include <nova/common.h>

#include <nova/core/scene.h>

#include <nova/editor/editor_gui_context.h>
#include <nova/editor/editor_gui_window.h>

namespace nova::editor
{

class EditorGUI
{
public:
  static void init();
  static void shutdown();

  static void render(const Ref<core::Scene>& current_scene);

  template <typename T, typename... Args>
  static void register_window(Args&&... args)
  {
    s_windows.emplace_back(std::make_shared<T>(std::forward<Args>(args)...));
  }

  template <typename T, typename... Args>
  static void unregister_window(Args&&... args)
  {
    s_windows.erase(
        std::remove_if(s_windows.begin(), s_windows.end(), [&](const Ref<EditorGUIWindow>& w)
                       { return std::dynamic_pointer_cast<T>(w) != nullptr; }),
        s_windows.end());
  }

private:
  static void begin();
  static void end();

private:
  static Ref<EditorGUIContext> s_context;
  static std::vector<Ref<EditorGUIWindow>> s_windows;
};

}  // namespace nova::editor