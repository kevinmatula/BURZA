#include "world/Entity.hpp"
#include "math/Transform.hpp"

Entity::Entity(std::shared_ptr<Mesh> givenMesh,
               std::shared_ptr<Shader> givenShader,
               const Transform &givenTransform)
    : mesh(givenMesh), shader(givenShader), transform(givenTransform) {}

Entity::Entity(std::shared_ptr<Mesh> givenMesh,
               std::shared_ptr<Shader> givenShader)
    : mesh(givenMesh), shader(givenShader), transform() {}

void Entity::draw() {
  glm::mat4 model = transform.returnModel();
  shader->use();
  shader->applyMatrix(model, MVP::Model);
  mesh->draw();
}

Entity::~Entity() {}
