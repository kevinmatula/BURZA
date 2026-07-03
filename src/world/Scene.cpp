#include "world/Scene.hpp"

Scene::Scene(const std::vector<std::shared_ptr<Entity>> &givenEntities)
    : entities(givenEntities) {}

Scene::Scene() {}

const std::vector<std::shared_ptr<Entity>> &Scene::getEntities() const {
  return entities;
}

Scene::~Scene() {}
