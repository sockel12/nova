#pragma once

#include "nova/core/window.h"
namespace nova::core
{

enum class GraphicsAPI
{
  OPENGL
};

struct ContextSpecification
{
  GraphicsAPI api = GraphicsAPI::OPENGL;
  bool vsync = true;
  bool debug = true;
};

class GraphicsContext
{
public:
  GraphicsContext(const std::shared_ptr<Window>& window, ContextSpecification spec)
      : m_window(window), m_spec(spec)
  {
  }

  virtual ~GraphicsContext() = default;

  virtual void setup_window_hints() {}
  virtual bool init() = 0;
  virtual void shutdown() = 0;

  virtual void swap_buffers() = 0;

  virtual void vsync(bool enabled) = 0;
  bool vsync() const { return m_spec.vsync; }

  virtual GraphicsAPI api() const = 0;

protected:
  std::shared_ptr<Window> m_window;
  ContextSpecification m_spec;
};

}  // namespace nova::core