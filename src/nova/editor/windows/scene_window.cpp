#include <nova/editor/windows/scene_window.h>

#include <nova/core/components/tag_component.h>

#include <imgui.h>
#include "nova/graphics/texture.h"

namespace nova::editor::windows
{
SceneWindow::SceneWindow(const std::string& name) : EditorGUIWindow(name) {}

void SceneWindow::on_imgui_render(EditorGUIContext& context)
{
  const auto& scene = context.active_scene;

  const Ref<graphics::Texture>& color_texture = context.frame_buffer->color_texture();

  auto content_region = ImGui::GetContentRegionAvail();

  ImGui::Image(color_texture->texture_id(), content_region);
}

}  // namespace nova::editor::windows