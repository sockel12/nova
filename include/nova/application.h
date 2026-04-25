#pragma once

#include <nova/common.h>

#include <nova/application_specification.h>
#include <nova/game.h>

#include <nova/core/scene.h>
#include <nova/core/logger.h>
#include <nova/core/window.h>

#include <nova/graphics/graphics_api.h>
#include <nova/graphics/graphics_context.h>

/** This function must be overriden by the game enable custom application specification
 * (e.g. window size, title, etc.). This will be called *BEFORE* the application and graphics
 * context have been initialized, so the game should *not* attempt to access the application in this
 * function. */
extern nova::ApplicationSpecification create_application_specification();

/** This function must be overriden by the game to actually create the game instance. This
 * will be called *AFTER* the application and graphics context have been initialized, so
 * the game can safely access the application. */
extern Ref<nova::Game> create_game();

namespace nova
{

class Application
{
public:
  Application(ApplicationSpecification spec = ApplicationSpecification());
  ~Application();

  bool init();
  void shutdown();

  void run();

  const ApplicationSpecification& spec() const { return m_spec; }
  const Ref<core::Window>& window() const { return m_window; }
  const Ref<graphics::GraphicsContext>& context() const { return m_context; }

  Game& game() { return *m_game; }
  const Game& game() const { return *m_game; }

public:
  static Application* instance();
  static graphics::GraphicsAPI graphics_api() { return instance()->context()->api(); }

private:
  ApplicationSpecification m_spec;
  Ref<core::Window> m_window;
  Ref<graphics::GraphicsContext> m_context;
  Ref<Game> m_game;
  bool m_shutdown = false;

private:
  static Application* s_instance;
};

}  // namespace nova