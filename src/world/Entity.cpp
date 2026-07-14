#include "world/Entity.hpp"
#include "math/Transform.hpp"

Entity::Entity(std::shared_ptr<Mesh> givenMesh,
               std::shared_ptr<Shader> givenShader,
               const Transform &givenTransform)
    : mesh(givenMesh), shader(givenShader), transform(givenTransform) {}

Entity::Entity(std::shared_ptr<Mesh> givenMesh,
               std::shared_ptr<Shader> givenShader)
    : mesh(givenMesh), shader(givenShader), transform() {}

void Entity::draw() { mesh->draw(); }

void Entity::matrixToShader(
    const std::unordered_map<MVP, glm::mat4> &mvpMatrices) {
  // Apply model manually because it is native to Entity class.
  shader->applyMatrix(MVP::Model, transform.computeModel());
  for (const auto &matrixPair : mvpMatrices) {
    shader->applyMatrix(matrixPair.first, matrixPair.second);
  }
}

void Entity::bindShader() { shader->use(); }

bool Entity::isOnFrustum(const Frustum &givenFrustum) {
  return mesh->getAABB().isOnFrustum(givenFrustum, transform);
}

Entity::~Entity() {}
