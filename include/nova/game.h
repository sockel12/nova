#pragma once

#include <nova/common.h>
#include <nova/core/scene.h>

namespace nova
{

class Game
{
public:
  virtual ~Game() = default;

  virtual void on_init() = 0;
  virtual void on_update(double delta_time) = 0;
  virtual void on_shutdown() = 0;

  virtual const Ref<core::Scene>& current_scene() const = 0;

protected:
};

}  // namespace nova