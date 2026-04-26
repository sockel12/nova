#include <nova/editor/editor_utils.h>

#include <format>

#include <imgui.h>

namespace nova::editor
{

void EditorUtils::display_resource(const Ref<core::Resource>& resource)
{
  switch (resource->type())
  {
    case core::ResourceType::TEXTURE_2D:
      display_texture(std::dynamic_pointer_cast<graphics::Texture>(resource));
      break;
    case core::ResourceType::MATERIAL:
      display_material(std::dynamic_pointer_cast<graphics::Material>(resource));
      break;
    case core::ResourceType::MESH:
      display_mesh(std::dynamic_pointer_cast<graphics::Mesh>(resource));
      break;
    case core::ResourceType::SHADER:
      display_shader(std::dynamic_pointer_cast<graphics::Shader>(resource));
      break;
    default:
      ImGui::Text("Unsupported resource type.");
      break;
  }
}

void EditorUtils::display_texture(const Ref<graphics::Texture>& texture)
{
  ImGui::Text("Texture Resource:");
  ImGui::Text("Width: %d", texture->data().width);
  ImGui::Text("Height: %d", texture->data().height);
  ImGui::Text("Channels: %d", texture->data().channels);
  ImGui::Image(texture->texture_id(), ImGui::GetContentRegionAvail());
}

void EditorUtils::display_material(const Ref<graphics::Material>& material)
{
  ImGui::Text("Material Resource:");
  ImGui::Text("Shader: %s", material->shader() ? material->shader()->name().c_str() : "None");
  ImGui::Text("Uniforms:");
  for (auto& [name, value] : material->uniforms())
  {
    if (ImGui::TreeNode(name.c_str()))
    {
      display_uniform_value(name, value);
      ImGui::TreePop();
    }
  }
}

void EditorUtils::display_shader(const Ref<graphics::Shader>& shader)
{
  ImGui::Text("Shader Resource:");
  ImGui::Text("Name: %s", shader->name().c_str());
}

void EditorUtils::display_mesh(const Ref<graphics::Mesh>& mesh)
{
  ImGui::Text("Mesh Resource:");
  ImGui::Text("Vertex Count: %zu", mesh->mesh_data().vertices().size());
  ImGui::Text("Index Count: %zu", mesh->mesh_data().indices().size());
}

void EditorUtils::display_uniform_value(const std::string& name, graphics::UniformValue& value)
{
  std::visit(
      [name](auto& val)
      {
        using T = std::decay_t<decltype(val)>;
        if constexpr (std::is_same_v<T, float>)
        {
          ImGui::InputFloat("##float", &val);
        }
        else if constexpr (std::is_same_v<T, int>)
        {
          ImGui::InputInt("##int", &val);
        }
        else if constexpr (std::is_same_v<T, glm::vec2>)
        {
          ImGui::InputFloat2("##vec2", &val.x);
        }
        else if constexpr (std::is_same_v<T, glm::vec3>)
        {
          ImGui::InputFloat3("##vec3", &val.x);
        }
        else if constexpr (std::is_same_v<T, glm::vec4>)
        {
          ImGui::InputFloat4("##vec4", &val.x);
        }
        else if constexpr (std::is_same_v<T, glm::ivec2>)
        {
          ImGui::InputInt2("##ivec2", &val.x);
        }
        else if constexpr (std::is_same_v<T, glm::ivec3>)
        {
          ImGui::InputInt3("##ivec3", &val.x);
        }
        else if constexpr (std::is_same_v<T, glm::ivec4>)
        {
          ImGui::InputInt4("##ivec4", &val.x);
        }
        else if constexpr (std::is_same_v<T, glm::mat3>)
        {
          ImGui::DragFloat3("##mat3_1", &val[0].x);
          ImGui::DragFloat3("##mat3_2", &val[1].x);
          ImGui::DragFloat3("##mat3_3", &val[2].x);
        }
        else if constexpr (std::is_same_v<T, glm::mat4>)
        {
          ImGui::DragFloat4("##mat4_1", &val[0].x);
          ImGui::DragFloat4("##mat4_2", &val[1].x);
          ImGui::DragFloat4("##mat4_3", &val[2].x);
          ImGui::DragFloat4("##mat4_4", &val[3].x);
        }
        else if constexpr (std::is_same_v<T, Ref<graphics::Texture>>)
        {
          if (val)
          {
            float aspect_ratio = val->get_aspect_ratio();
            ImVec2 image_size = ImGui::GetContentRegionAvail();

            if (image_size.x / image_size.y > aspect_ratio)
            {
              image_size.x = image_size.y * aspect_ratio;
            }
            else
            {
              image_size.y = image_size.x / aspect_ratio;
            }

            ImGui::Image(val->texture_id(), image_size);
          }
          else
          {
            ImGui::Text("None");
          }
        }
        else
        {
          ImGui::Text("Unsupported uniform type.");
        }
      },
      value);
}

}  // namespace nova::editor