#include <nova/editor/windows/resource_manager_window.h>

#include <algorithm>
#include <array>
#include <imgui.h>
#include <vector>

#include <nova/io/resource_manager.h>

namespace nova::editor::windows
{
ResourceManagerWindow::ResourceManagerWindow(const std::string& name) : EditorGUIWindow(name) {}

namespace
{

const char* resource_type_label(core::ResourceType type)
{
  switch (type)
  {
    case core::ResourceType::TEXTURE_2D:
      return "Textures";
    case core::ResourceType::SHADER:
      return "Shaders";
    case core::ResourceType::MESH:
      return "Meshes";
    case core::ResourceType::MATERIAL:
      return "Materials";
    default:
      return "Unknown";
  }
}

}  // namespace

void ResourceManagerWindow::on_imgui_render(EditorGUIContext& context)
{
  std::array<std::vector<std::string>, 5> resources_by_type;

  for (const auto& [name, resource] : io::ResourceManager::resources())
  {
    const auto type = resource ? resource->type() : core::ResourceType::UNKNOWN;
    const auto type_index = static_cast<std::size_t>(type);

    if (type_index < resources_by_type.size())
    {
      resources_by_type[type_index].emplace_back(name);
    }
  }

  for (auto& resources : resources_by_type)
  {
    std::sort(resources.begin(), resources.end(),
              [](const auto& lhs, const auto& rhs) { return lhs < rhs; });
  }

  bool tree_node_expanded = false;

  for (std::size_t type_index = 0; type_index < resources_by_type.size(); ++type_index)
  {
    auto& resources = resources_by_type[type_index];

    if (resources.empty())
    {
      continue;
    }

    const auto type = static_cast<core::ResourceType>(type_index);

    if (ImGui::TreeNode(resource_type_label(type)))
    {
      tree_node_expanded = true;
      for (const auto& name : resources)
      {
        bool selected = context.selected_resource == name;

        if (ImGui::Selectable(name.c_str(), selected))
        {
          if (selected)
          {
            context.selected_resource = "";
          }
          else
          {
            context.selected_resource = name;
          }
        }
      }

      ImGui::TreePop();
    }
  }

  if (!tree_node_expanded)
  {
    context.selected_resource = "";
  }
}

}  // namespace nova::editor::windows