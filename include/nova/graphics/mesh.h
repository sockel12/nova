#pragma once

#include <nova/common.h>

#include <nova/core/resource.h>

#include <nova/graphics/mesh_data.h>

#include <nova/graphics/buffers/vertex_array_object.h>
#include <nova/graphics/buffers/vertex_buffer.h>
#include <nova/graphics/buffers/index_buffer.h>

enum class MeshPrimitive
{
  QUAD
};

namespace nova::graphics
{

class Mesh : public core::Resource
{
public:
  Mesh();
  Mesh(const MeshData& mesh_data);

  core::ResourceType type() const override { return core::ResourceType::MESH; }

  void update();

  void bind() const;
  void unbind() const;

  static Ref<Mesh> create();
  static Ref<Mesh> create(MeshPrimitive primitive);

  MeshData& mesh_data() { return m_mesh_data; }
  const MeshData& mesh_data() const { return m_mesh_data; }

private:
  void init();

private:
  MeshData m_mesh_data;
  Ref<buffers::VertexArrayObject> m_vao;
  Ref<buffers::VertexBuffer> m_vertex_buffer;
  Ref<buffers::IndexBuffer> m_index_buffer;
};

}  // namespace nova::graphics