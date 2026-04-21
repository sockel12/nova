#pragma once

#include <nova/common.h>

#include <nova/core/scene.h>

namespace nova::editor
{

struct EditorGUIContext
{
  Ref<core::Scene> active_scene;
  entt::entity selected_entity = entt::null;
};

}  // namespace nova::editor