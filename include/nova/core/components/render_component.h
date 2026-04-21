#pragma once

#include <nova/graphics/mesh.h>
#include <nova/graphics/material.h>

namespace nova::core::components
{

class RenderComponent
{
public:
  RenderComponent(const std::shared_ptr<graphics::Mesh>& mesh,
                  const std::shared_ptr<graphics::Material>& material)
      : mesh(mesh), material(material)
  {
  }

  std::shared_ptr<graphics::Mesh> mesh;
  std::shared_ptr<graphics::Material> material;
};

}  // namespace nova::core::components