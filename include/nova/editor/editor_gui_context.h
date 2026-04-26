#pragma once

#include <nova/common.h>

#include <nova/core/scene.h>

#include <nova/graphics/buffers/frame_buffer.h>

namespace nova::editor
{

struct EditorGUIContext
{
  Ref<core::Scene> active_scene;
  Ref<graphics::buffers::FrameBuffer> frame_buffer;
  std::string selected_resource = "";
  entt::entity selected_entity = entt::null;
};

}  // namespace nova::editor