#include <nova/graphics/opengl/gl_renderer_api.h>

#include <nova/graphics/opengl/opengl.h>

namespace nova::graphics::opengl
{

void GLRendererAPI::init()
{
  GL_CALL(glEnable(GL_BLEND));
  GL_CALL(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
  GL_CALL(glEnable(GL_DEPTH_TEST));
}

void GLRendererAPI::shutdown() {}

void GLRendererAPI::set_viewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
{
  GL_CALL(glViewport(x, y, width, height));
}

void GLRendererAPI::set_clear_color(float r, float g, float b, float a)
{
  GL_CALL(glClearColor(r, g, b, a));
}

void GLRendererAPI::clear() { GL_CALL(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)); }

void GLRendererAPI::draw_indexed(uint32_t indexCount)
{
  GL_CALL(glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, nullptr));
}

void GLRendererAPI::draw_arrays(graphics::renderer::PrimitiveType type, uint32_t count)
{
  GLenum glType = GL_TRIANGLES;
  switch (type)
  {
    case graphics::renderer::PrimitiveType::LINES:
      glType = GL_LINES;
      break;
    case graphics::renderer::PrimitiveType::TRIANGLES:
      glType = GL_TRIANGLES;
      break;
  }

  GL_CALL(glDrawArrays(glType, 0, count));
}

void GLRendererAPI::set_depth_test(bool enabled)
{
  if (enabled)
  {
    GL_CALL(glEnable(GL_DEPTH_TEST));
  }
  else
  {
    GL_CALL(glDisable(GL_DEPTH_TEST));
  }
}

void GLRendererAPI::set_blend(bool enabled)
{
  if (enabled)
  {
    GL_CALL(glEnable(GL_BLEND));
    GL_CALL(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
  }
  else
  {
    GL_CALL(glDisable(GL_BLEND));
  }
}

}  // namespace nova::graphics::opengl