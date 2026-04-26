#pragma once

#include <array>

#include <nova/editor/editor_gui_context.h>
#include <nova/editor/editor_gui_window.h>

namespace nova::editor::windows
{

class StatisticsWindow : public EditorGUIWindow
{
public:
  StatisticsWindow(const std::string& name = "Statistics");

  void on_imgui_render(EditorGUIContext& context) override;

private:
  static constexpr std::size_t kFrameHistorySize = 240;

  std::array<float, kFrameHistorySize> m_frame_time_history = {};
  std::size_t m_history_sample_count = 0;
  std::size_t m_history_write_index = 0;

  bool m_pause_history = false;
};

}  // namespace nova::editor::windows
