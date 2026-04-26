#include <nova/editor/windows/statistics_window.h>

#include <algorithm>

#include <imgui.h>

#include <nova/graphics/renderer/renderer.h>

namespace nova::editor::windows
{

StatisticsWindow::StatisticsWindow(const std::string& name) : EditorGUIWindow(name) {}

void StatisticsWindow::on_imgui_render(EditorGUIContext& context)
{
  (void)context;

  const auto& stats = graphics::renderer::Renderer::statistics();
  const float frame_time_ms = static_cast<float>(stats.frame_time_ms);

  if (!m_pause_history)
  {
    m_frame_time_history[m_history_write_index] = frame_time_ms;
    m_history_write_index = (m_history_write_index + 1) % kFrameHistorySize;
    m_history_sample_count = std::min(m_history_sample_count + 1, kFrameHistorySize);
  }

  ImGui::Text("FPS: %.1f", stats.fps);
  ImGui::Text("Frame Time: %.2f ms", stats.frame_time_ms);

  ImGui::Separator();

  ImGui::Text("Frame Time (Min/Avg/Max): %.2f / %.2f / %.2f ms", stats.min_frame_time_ms,
              stats.avg_frame_time_ms, stats.max_frame_time_ms);

  ImGui::Separator();

  ImGui::Text("Draw Calls: %u", stats.draw_calls);
  ImGui::Text("Submitted Meshes: %u", stats.submitted_meshes);
  ImGui::Text("Submitted Indices: %llu",
              static_cast<unsigned long long>(stats.submitted_indices));
  ImGui::Text("Submitted Vertices: %llu",
              static_cast<unsigned long long>(stats.submitted_vertices));

  ImGui::Separator();

  if (ImGui::Button(m_pause_history ? "Resume History" : "Pause History"))
  {
    m_pause_history = !m_pause_history;
  }

  ImGui::SameLine();

  if (ImGui::Button("Clear History"))
  {
    m_frame_time_history.fill(0.0f);
    m_history_sample_count = 0;
    m_history_write_index = 0;
  }

  std::array<float, kFrameHistorySize> ordered_frame_time_history = {};
  for (std::size_t i = 0; i < m_history_sample_count; ++i)
  {
    std::size_t source_index = i;
    if (m_history_sample_count == kFrameHistorySize)
    {
      source_index = (m_history_write_index + i) % kFrameHistorySize;
    }

    ordered_frame_time_history[i] = m_frame_time_history[source_index];
  }

  const float max_frame_time = std::max(33.0f, frame_time_ms * 1.25f);

  ImGui::PlotLines("Frame Time (ms)", ordered_frame_time_history.data(),
                   static_cast<int>(m_history_sample_count), 0, nullptr, 0.0f,
                   max_frame_time, ImVec2(0.0f, 110.0f));
}

}  // namespace nova::editor::windows
