#include "world/Scene.hpp"

Scene::Scene(const std::vector<std::shared_ptr<Entity>> &givenEntities)
    : entities(givenEntities), camera() {}

Scene::Scene(const std::vector<std::shared_ptr<Entity>> &givenEntities,
             const Camera &givenCamera)
    : entities(givenEntities), camera(givenCamera) {}

Scene::Scene() {}

const std::vector<std::shared_ptr<Entity>> &Scene::getEntities() const {
  return entities;
}

const Camera &Scene::getCamera() const { return camera; }

Camera &Scene::getCamera() { return camera; }

Scene::~Scene() {}
