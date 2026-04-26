#include <test_game.h>
#include <test_system.h>

#include <nova/graphics/shader.h>

#include <nova/io/resource_manager.h>

nova::ApplicationSpecification create_application_specification(int argc, char** argv)
{
  nova::ApplicationSpecification spec;
  spec.name = "Nova Test Application";
  spec.width = 1600;
  spec.height = 900;
  spec.target_fps = 60;
  return spec;
}

Ref<nova::Game> create_game()
{
  auto scene = std::make_shared<nova::core::Scene>();

  scene->add_system(std::make_shared<RotationSystem>());
  scene->add_system(std::make_shared<PulsatingSystem>());

  auto test_entity = scene->add_entity("Test Entity [1]");
  auto test_entity_2 = scene->add_entity("Test Entity [2]");
  scene->add_entity("Test Entity [3]");

  auto& rc = test_entity.add_component<nova::core::components::RenderComponent>();
  auto& transform = test_entity.get_component<nova::core::components::TransformComponent>();

  test_entity.add_component<RotationComponent>();
  test_entity_2.add_component<PulsatingComponent>();

  auto& rc_2 = test_entity_2.add_component<nova::core::components::RenderComponent>();
  auto& transform_2 = test_entity_2.get_component<nova::core::components::TransformComponent>();

  transform.position = glm::vec3(0.5, 0.0f, 0.0f);
  transform.scale = glm::vec3(0.25f, 0.25f, 0.5f);

  transform_2.position = glm::vec3(-0.5, 0.0f, 0.0f);
  transform_2.scale = glm::vec3(0.25f, 0.25f, 0.5f);

  auto texture = nova::io::ResourceManager::load_texture("smiley", "resources/textures/smiley.png");
  auto mesh = nova::io::ResourceManager::create_mesh("quad", MeshPrimitive::QUAD);
  auto shader = nova::io::ResourceManager::load_shader(
      "basic", nova::graphics::ShaderSource{.vertex_shader = nova::core::FileHandler::read_file(
                                                "resources/shaders/basic_vertex.glsl"),
                                            .fragment_shader = nova::core::FileHandler::read_file(
                                                "resources/shaders/basic_fragment.glsl")});

  auto material = nova::io::ResourceManager::create_material("test_material");
  auto material_2 = nova::io::ResourceManager::create_material("test_material_2");

  // material->set_uniform("u_Color", glm::vec3(0.2f, 0.3f, 0.8f));
  material->set_uniform("u_Texture", texture);

  material_2->set_uniform("u_Texture", texture);

  material->shader(shader);
  material_2->shader(shader);

  rc.material = material;
  rc.mesh = mesh;

  rc_2.material = material_2;
  rc_2.mesh = mesh;

  return std::make_shared<TestGame>(scene);
};
