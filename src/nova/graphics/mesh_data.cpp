#include <nova/graphics/mesh_data.h>

namespace nova::graphics
{

Vertex::Vertex(const glm::vec3& pos) : Vertex(pos, glm::vec3(0.0f), glm::vec2(0.0f)) {}

Vertex::Vertex(const glm::vec3& pos, const glm::vec2& uv) : Vertex(pos, glm::vec3(0.0f), uv) {}

Vertex::Vertex(const glm::vec3& pos, const glm::vec3& normal, const glm::vec2& uv)
    : position(pos), normal(normal), uv(uv)
{
}

}  // namespace nova::graphics