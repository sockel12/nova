#include <nova/application.h>

#include <nova/io/resource_manager.h>

#include <nova/core/scene.h>
#include <nova/core/file_handler.h>

#include <nova/graphics/graphics_api.h>

#include <nova/graphics/renderer/renderer.h>

#include <nova/editor/editor_gui.h>

#include <thread>
#include <chrono>

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
  m_render_pass = std::make_shared<graphics::renderer::RenderPass>();

  if (!m_render_pass->init(m_spec.width, m_spec.height))
  {
    core::logger()->error("Failed to initialize render pass");
    return false;
  }

  editor::EditorGUI::init();

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
  if (m_shutdown)
    return;

  m_shutdown = true;

  if (m_game)
  {
    /** Tell the game to shut down */
    m_game->on_shutdown();

    /** Reset the game pointer */
    m_game.reset();
  }

  editor::EditorGUI::shutdown();

  io::ResourceManager::shutdown();

  graphics::renderer::Renderer::shutdown();

  if (m_context)
  {
    m_context->shutdown();
    m_context.reset();
  }

  if (m_window)
  {
    m_window->shutdown();
    m_window.reset();
  }

  glfwTerminate();
  s_instance = nullptr;
}

void Application::run()
{
  bool should_close = false;

  double last_time = glfwGetTime();
  double delta_time = m_spec.target_fps > 0 ? 1.0 / m_spec.target_fps : 0.0;
  size_t frame_count = 0;

  // Calculate target frame time (in seconds)
  double target_frame_time = 1.0 / m_spec.target_fps;

  while (!glfwWindowShouldClose(m_window->native_window()))
  {
    double frame_start_time = glfwGetTime();

    /** Poll events */
    m_window->poll_events();

    /** Update the game */
    game().on_update(delta_time);

    game().current_scene()->update(delta_time);

    /** Start per-frame renderer statistics before scene rendering. */
    graphics::renderer::Renderer::begin_frame(delta_time);

    /** Render the active scene through the render pass. */
    m_render_pass->begin(*game().current_scene());
    m_render_pass->render(*game().current_scene());
    m_render_pass->end();

    /** End per-frame renderer statistics after scene rendering. */
    graphics::renderer::Renderer::end_frame();

    editor::EditorGUI::context()->frame_buffer = m_render_pass->frame_buffer();

    /** Render editor GUI */
    editor::EditorGUI::render(game().current_scene());

    /** Swap buffers */
    m_context->swap_buffers();

    /** Calculate delta time and frame rate limiting */
    double current_time = glfwGetTime();
    frame_count++;
    delta_time = current_time - last_time;
    last_time = current_time;

    // Frame rate limiting: sleep if frame finished too early
    double frame_time = current_time - frame_start_time;
    if (frame_time < target_frame_time)
    {
      double sleep_time = target_frame_time - frame_time - 0.00009;
      std::this_thread::sleep_for(std::chrono::duration<double>(sleep_time));

      // Update delta_time to reflect actual frame time
      current_time = glfwGetTime();
      delta_time = current_time - (last_time - delta_time);
      last_time = current_time;
    }
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