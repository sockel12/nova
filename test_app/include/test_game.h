#pragma once

#include <nova/common.h>
#include <nova/nova.h>
#include <nova/application.h>

#include <test_system.h>

class TestGame : public nova::Game
{
public:
  TestGame(const Ref<nova::core::Scene>& first_scene) : m_scene(first_scene) {}

  void on_init() {}
  void on_update(double delta_time) {}
  void on_shutdown() {}

  const Ref<nova::core::Scene>& current_scene() const { return m_scene; };

private:
  Ref<nova::core::Scene> m_scene;
};
