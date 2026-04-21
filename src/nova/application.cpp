#include <nova/application.h>

#include <nova/io/resource_manager.h>

#include <nova/core/scene.h>
#include <nova/core/file_handler.h>

#include <nova/graphics/graphics_api.h>

#include <nova/graphics/renderer/renderer.h>

namespace nova
{

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

  graphics::renderer::Renderer::init(graphics_api());

  try
  {
    m_game = create_game();
    game().on_init();
  }
  catch (const std::exception& e)
  {
    core::logger()->error("Failed to initialize game: {}", e.what());
    return false;
  }

  return true;
}

void Application::shutdown()
{
  if (m_game)
  {
    /** Tell the game to shut down */
    m_game->on_shutdown();

    /** Reset the game pointer */
    m_game.reset();
  }

  io::ResourceManager::shutdown();

  graphics::renderer::Renderer::shutdown();

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

  double last_time = glfwGetTime();
  double delta_time = 0.0;
  size_t frame_count = 0;

  while (!glfwWindowShouldClose(m_window->native_window()))
  {
    /** Update the game */
    game().on_update(delta_time);

    game().current_scene()->update(delta_time);

    /** Start drawing */
    graphics::renderer::Renderer::clear();

    game().current_scene()->draw();

    /** Poll events */
    m_window->poll_events();

    /** Swap buffers */
    m_context->swap_buffers();

    /** Calculate delta time */
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