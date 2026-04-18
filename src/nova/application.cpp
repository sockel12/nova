#include <nova/application.h>

#include <nova/core/file_handler.h>

#include <nova/graphics/shader.h>

#include <nova/graphics/renderer/render_command.h>

#include <nova/graphics/buffers/vertex_buffer.h>
#include <nova/graphics/buffers/vertex_array_object.h>

namespace nova
{

namespace ngr = nova::graphics::renderer;
namespace nvb = nova::graphics::buffers;

Application::Application(ApplicationSpecification spec)
    : m_spec(spec), m_window(nullptr), m_context(nullptr)
{
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

  float vertices[12] = {
      -0.5f, -0.5f, 0.0f,  // bottom left
      0.5f,  -0.5f, 0.0f,  // bottom right
      0.0f,  0.5f,  0.0f   // top center
  };

  nvb::VertexBufferLayout layout;
  layout.emplace_back("a_position", graphics::buffers::ShaderDataType::FLOAT3, false);

  auto vertex_buffer = nvb::VertexBuffer::create(m_context->api());
  vertex_buffer->data(vertices, sizeof(vertices));
  vertex_buffer->buffer_layout(layout);

  auto vertex_array_object = nvb::VertexArrayObject::create(m_context->api());
  vertex_array_object->add_vertex_buffer(vertex_buffer);

  auto shader = graphics::Shader::create(
      m_context->api(),
      graphics::ShaderSource(core::FileHandler::read_file("resources/basic_vertex.glsl"),
                             core::FileHandler::read_file("resources/basic_fragment.glsl")));
  if (!shader || !shader->valid())
  {
    core::logger()->error("Failed to create shader");
    return;
  }

  ngr::RenderCommand::set_clear_color(0.1f, 0.1f, 0.1f, 1.0f);

  while (!glfwWindowShouldClose(m_window->native_window()))
  {
    ngr::RenderCommand::clear();

    shader->bind();
    vertex_array_object->bind();
    ngr::RenderCommand::draw_arrays(ngr::PrimitiveType::TRIANGLES, 3);
    vertex_array_object->unbind();
    shader->unbind();

    m_window->poll_events();

    m_context->swap_buffers();
  }
}

}  // namespace nova