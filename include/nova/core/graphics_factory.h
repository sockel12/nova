#pragma once

#include <memory>

#include <nova/core/window.h>
#include <nova/core/graphics_context.h>

namespace nova::core
{

class GraphicsFactory
{
public:
  static std::shared_ptr<GraphicsContext> create_graphics_context(
      const std::shared_ptr<Window>& window, ContextSpecification spec = ContextSpecification());
};

}  // namespace nova::core