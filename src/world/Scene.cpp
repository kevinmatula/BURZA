#include "world/Scene.hpp"
#include <memory>

Scene::Scene(Registry givenRegistry,
             std::vector<std::unique_ptr<System>> givenSystems)
    : registry(std::move(givenRegistry)), systems(std::move(givenSystems)) {}

Scene::Scene() {}

void Scene::update() {
  for (std::unique_ptr<System> &system : systems) {
    system->update(registry);
  }
}
