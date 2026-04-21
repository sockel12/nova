#include <nova/nova.h>
#include <nova/application.h>

#include <test_system.h>
namespace ng = nova::graphics;

int main()
{
  nova::ApplicationSpecification spec;
  spec.name = "Nova Test Application";
  spec.width = 1200;
  spec.height = 800;

  nova::Application app(spec);

  if (!app.init())
  {
    return -1;
  }

  std::vector<glm::vec3> vertices = {
      glm::vec3(-0.5f, -0.5f, 0.0f),  // bottom left
      glm::vec3(0.5f, -0.5f, 0.0f),   // bottom right
      glm::vec3(-0.5f, 0.5f, 0.0f),   // top left
      glm::vec3(0.5f, 0.5f, 0.0f)     // top right
  };

  std::vector<uint32_t> indices = {0, 1, 2, 1, 3, 2};

  ng::buffers::VertexBufferLayout layout({
      {"a_Position", ng::ShaderDataType::FLOAT3, false},
  });

  std::shared_ptr<ng::MeshData<glm::vec3>> mesh_data =
      std::make_shared<ng::MeshData<glm::vec3>>(vertices, indices, layout);

  ng::Mesh mesh(mesh_data);

  auto material = ng::Material::create(
      ng::ShaderSource(nova::core::FileHandler::read_file("resources/basic_vertex.glsl"),
                       nova::core::FileHandler::read_file("resources/basic_fragment.glsl")));

  material->set_uniform("u_Color", glm::vec3(0.2f, 0.3f, 0.8f));

  glm::mat4 model = glm::mat4(1.0f);

  app.run();

  return 0;
}
