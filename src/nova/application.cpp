#include <nova/application.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <nova/core/file_handler.h>

#include <nova/graphics/graphics_api.h>
#include <nova/graphics/shader.h>
#include <nova/graphics/mesh_data.h>
#include <nova/graphics/mesh.h>
#include <nova/graphics/material.h>

#include <nova/graphics/renderer/render_command.h>

#include <nova/graphics/buffers/vertex_buffer_layout.h>

namespace nova
{

namespace ngr = nova::graphics::renderer;
namespace nvb = nova::graphics::buffers;

Application* Application::s_instance = nullptr;

Application::Application(ApplicationSpecification spec)
    : m_spec(spec), m_window(nullptr), m_context(nullptr)
{
  if (s_instance)
  {
    core::logger()->error("Application instance already exists");
    throw std::runtime_error("Application instance already exists");
  }
  s_instance = this;
}

Application::~Application() { shutdown(); }

bool Application::init()
{
  if (!glfwInit())
  {
    core::logger()->error("Failed to initialize GLFW");
    return false;
  }

  m_window = std::make_shared<core::Window>(m_spec.width, m_spec.height, m_spec.name);
  m_context = graphics::GraphicsContext::create(m_window, graphics::ContextSpecification());

  m_context->setup_window_hints();
  if (!m_window->init())
  {
    core::logger()->error("Failed to initialize window");
    return false;
  }

  if (!m_context->init())
  {
    core::logger()->error("Failed to initialize graphics context");
    return false;
  }

  ngr::RenderCommand::init(graphics::GraphicsAPI::OPENGL);

  return true;
}

void Application::shutdown()
{
  ngr::RenderCommand::shutdown();

  if (m_context)
  {
    m_context->shutdown();
  }

  if (m_window)
  {
    m_window->shutdown();
  }

  glfwTerminate();
}

void Application::run()
{
  bool should_close = false;

  std::vector<glm::vec3> vertices = {
      glm::vec3(-0.5f, -0.5f, 0.0f),  // bottom left
      glm::vec3(0.5f, -0.5f, 0.0f),   // bottom right
      glm::vec3(-0.5f, 0.5f, 0.0f),   // top left
      glm::vec3(0.5f, 0.5f, 0.0f)     // top right
  };

  std::vector<uint32_t> indices = {0, 1, 2, 1, 3, 2};

  nvb::VertexBufferLayout layout({
      {"a_Position", graphics::ShaderDataType::FLOAT3, false},
  });

  std::shared_ptr<graphics::MeshData<glm::vec3>> mesh_data =
      std::make_shared<graphics::MeshData<glm::vec3>>(vertices, indices, layout);

  graphics::Mesh mesh(mesh_data);

  auto material = graphics::Material::create(
      graphics::ShaderSource(core::FileHandler::read_file("resources/basic_vertex.glsl"),
                             core::FileHandler::read_file("resources/basic_fragment.glsl")));

  material->set_uniform("u_Color", glm::vec3(0.2f, 0.3f, 0.8f));

  glm::mat4 model = glm::mat4(1.0f);

  ngr::RenderCommand::set_clear_color(0.1f, 0.1f, 0.1f, 1.0f);

  double last_time = glfwGetTime();
  double delta_time = 0.0;
  size_t frame_count = 0;

  while (!glfwWindowShouldClose(m_window->native_window()))
  {
    ngr::RenderCommand::clear();

    model = glm::rotate(model, glm::radians(15.0f * static_cast<float>(delta_time)),
                        glm::vec3(0.0f, 0.0f, 1.0f));

    material->bind();
    mesh.bind();
    material->set_uniform("u_Model", model);
    // ngr::RenderCommand::draw_arrays(ngr::PrimitiveType::TRIANGLES, 3);
    ngr::RenderCommand::draw_indexed(mesh.indices_count());
    mesh.unbind();
    material->unbind();

    m_window->poll_events();

    m_context->swap_buffers();

    // Update FPS every second
    double current_time = glfwGetTime();
    frame_count++;
    delta_time = current_time - last_time;
    last_time = current_time;
  }
}

Application* Application::instance()
{
  if (s_instance == nullptr)
  {
    core::logger()->error("Application instance is null");
    throw std::runtime_error("Application instance is null");
  }

  return s_instance;
}

}  // namespace nova