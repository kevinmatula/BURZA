#pragma once

#include "math/Transform.hpp"
#include "rendering/Mesh.hpp"
#include "rendering/Shader.hpp"
#include <memory>
#include <unordered_map>

class Entity {
public:
  // Constructor - Sets up an Entity
  Entity(std::shared_ptr<Mesh> givenMesh, std::shared_ptr<Shader> givenShader,
         const Transform &givenTransform);
  // Overload Constructor for case of no transform given.
  Entity(std::shared_ptr<Mesh> givenMesh, std::shared_ptr<Shader> givenShader);
  // Destructor - Frees Memory within Entity
  ~Entity();

  // Draws an entity by enabling its native shader program and using the native
  // draw method on a Mesh.
  void draw();
  // Binds entity shader for rendering
  void bindShader();
  // Sends dictionary of mat4 matrices and enum type to shader uniform.
  void matrixToShader(const std::unordered_map<MVP, glm::mat4> &givenMatrices);
  // Boolean function to check if this Entity is on the given frustum; uses
  // Delegation design pattern.
  bool isOnFrustum(const Frustum &givenFrustum) const;

private:
  // Represents the mesh of an entity (shape, surface, etc). Must be compatible
  // with shader.
  std::shared_ptr<Mesh> mesh;
  // Represents the shader for an entity. Must be compatible with mesh.
  std::shared_ptr<Shader> shader;
  // Represents the way in which an object's position is scaled, rotated, and
  // translated.
  Transform transform;
};
