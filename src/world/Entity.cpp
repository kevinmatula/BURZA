#include "world/Entity.hpp"

Entity::Entity(std::shared_ptr<Mesh> givenMesh,
               std::shared_ptr<Shader> givenShader)
    : mesh(givenMesh), shader(givenShader) {}

void Entity::draw() {
  shader->use();
  mesh->draw();
}

Entity::~Entity() {}
