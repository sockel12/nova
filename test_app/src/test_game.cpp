#include <test_game.h>
#include <test_system.h>

#include <nova/graphics/shader.h>

#include <nova/io/resource_manager.h>

nova::ApplicationSpecification create_application_specification()
{
  nova::ApplicationSpecification spec;
  spec.name = "Nova Test Application";
  spec.width = 1200;
  spec.height = 800;
  return spec;
}

Ref<nova::Game> create_game()
{
  auto scene = std::make_shared<nova::core::Scene>();

  scene->add_system(std::make_shared<TestSystem>());

  scene->add_entity("Test Entity [1]");
  scene->add_entity("Test Entity [2]");

  auto test_entity = scene->add_entity("Test Entity");
  auto& rc = test_entity.add_component<nova::core::components::RenderComponent>();
  auto transform = test_entity.get_component<nova::core::components::TransformComponent>();

  transform.scale = glm::vec3(0.5f, 0.5f, 0.5f);

  auto mesh = nova::io::ResourceManager::create_mesh("quad", MeshPrimitive::QUAD);
  auto shader = nova::io::ResourceManager::load_shader(
      "basic",
      nova::graphics::ShaderSource{
          .vertex_shader = nova::core::FileHandler::read_file("resources/basic_vertex.glsl"),
          .fragment_shader = nova::core::FileHandler::read_file("resources/basic_fragment.glsl")});
  auto material = nova::io::ResourceManager::create_material("test_material");

  material->set_uniform("u_Color", glm::vec3(0.2f, 0.3f, 0.8f));

  if (!mesh || !shader || !material)
  {
    nova::core::logger()->error("Failed to create render resources for test entity.");
    return std::make_shared<TestGame>(scene);
  }

  material->shader(shader);

  rc.material = material;
  rc.mesh = mesh;

  return std::make_shared<TestGame>(scene);
};

// namespace ng = nova::graphics;

// int main()
// {
//   nova::ApplicationSpecification spec;
//   spec.name = "Nova Test Application";
//   spec.width = 1200;
//   spec.height = 800;

//   nova::Application app(spec);

//   if (!app.init())
//   {
//     return -1;
//   }

//   std::vector<glm::vec3> vertices = {
//       glm::vec3(-0.5f, -0.5f, 0.0f),  // bottom left
//       glm::vec3(0.5f, -0.5f, 0.0f),   // bottom right
//       glm::vec3(-0.5f, 0.5f, 0.0f),   // top left
//       glm::vec3(0.5f, 0.5f, 0.0f)     // top right
//   };

//   std::vector<uint32_t> indices = {0, 1, 2, 1, 3, 2};

//   ng::buffers::VertexBufferLayout layout({
//       {"a_Position", ng::ShaderDataType::FLOAT3, false},
//   });

//   std::shared_ptr<ng::MeshData<glm::vec3>> mesh_data =
//       std::make_shared<ng::MeshData<glm::vec3>>(vertices, indices, layout);

//   ng::Mesh mesh(mesh_data);

//   auto material = ng::Material::create(
//       ng::ShaderSource(nova::core::FileHandler::read_file("resources/basic_vertex.glsl"),
//                        nova::core::FileHandler::read_file("resources/basic_fragment.glsl")));

//   material->set_uniform("u_Color", glm::vec3(0.2f, 0.3f, 0.8f));

//   glm::mat4 model = glm::mat4(1.0f);

//   app.run();

//   return 0;
// }
