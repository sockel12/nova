#pragma once

#include <nova/graphics/texture.h>
#include <nova/graphics/material.h>

#include <nova/editor/editor_gui_context.h>
#include <nova/editor/editor_gui_window.h>

namespace nova::editor::windows
{

class ResourceViewerWindow : public EditorGUIWindow
{
public:
  ResourceViewerWindow(const std::string& name = "Resource Viewer");

  void on_imgui_render(EditorGUIContext& context) override;

private:
  void display_resource(const Ref<core::Resource>& resource);
  void display_texture(const Ref<graphics::Texture>& texture);
  void display_material(const Ref<graphics::Material>& material);

  entt::entity m_selected_entity = entt::null;
};

}  // namespace nova::editor::windows