#pragma once

#include "rendering/Mesh.hpp"
#include "rendering/Shader.hpp"
#include <memory>

class Entity {
public:
  // Constructor - Sets up an Entity
  Entity(std::shared_ptr<Mesh> givenMesh, std::shared_ptr<Shader> givenShader);
  // Destructor - Frees Memory within Entity
  ~Entity();

  // Draws an entity by enabling its native shader program and using the native
  // draw method on a Mesh.
  void draw();

private:
  // Represents the mesh of an entity (shape, surface, etc). Must be compatible
  // with shader.
  std::shared_ptr<Mesh> mesh;
  // Represents the shader for an entity. Must be compatible with mesh.
  std::shared_ptr<Shader> shader;
};
