#include <test_game.h>
#include <test_system.h>

#include <nova/graphics/shader.h>

#include <nova/io/resource_manager.h>

nova::ApplicationSpecification create_application_specification()
{
  nova::ApplicationSpecification spec;
  spec.name = "Nova Test Application";
  spec.width = 1600;
  spec.height = 900;
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

  auto image = nova::io::ResourceManager::load_image("smiley", "resources/textures/smiley.png");
  auto texture =
      nova::io::ResourceManager::load_texture("smiley_texture", "resources/textures/smiley.png");
  auto mesh = nova::io::ResourceManager::create_mesh("quad", MeshPrimitive::QUAD);
  auto shader = nova::io::ResourceManager::load_shader(
      "basic", nova::graphics::ShaderSource{.vertex_shader = nova::core::FileHandler::read_file(
                                                "resources/shaders/basic_vertex.glsl"),
                                            .fragment_shader = nova::core::FileHandler::read_file(
                                                "resources/shaders/basic_fragment.glsl")});
  auto material = nova::io::ResourceManager::create_material("test_material");

  // material->set_uniform("u_Color", glm::vec3(0.2f, 0.3f, 0.8f));
  material->set_uniform("u_Texture", texture);

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
