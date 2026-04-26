#include <nova/editor/windows/scene_window.h>

#include <imgui.h>

#include <nova/graphics/texture.h>

namespace nova::editor::windows
{
SceneWindow::SceneWindow(const std::string& name) : EditorGUIWindow(name, true) {}

void SceneWindow::on_imgui_render(EditorGUIContext& context)
{
  const auto& scene = context.active_scene;

  if (ImGui::BeginMenuBar())
  {
    if (ImGui::BeginMenu("Scene"))
    {
      ImGui::MenuItem("Keep Aspect Ratio", nullptr, &m_keep_aspect_ratio, true);

      ImGui::EndMenu();
    }
    ImGui::EndMenuBar();
  }

  const Ref<graphics::Texture>& color_texture = context.frame_buffer->color_texture();

  ImVec2 image_size = ImGui::GetContentRegionAvail();
  if (m_keep_aspect_ratio)
  {
    float aspect_ratio = color_texture->get_aspect_ratio();
    if (image_size.x / image_size.y > aspect_ratio)
    {
      image_size.x = image_size.y * aspect_ratio;
    }
    else
    {
      image_size.y = image_size.x / aspect_ratio;
    }
  }

  ImGui::Image(color_texture->texture_id(), image_size);
}

}  // namespace nova::editor::windows