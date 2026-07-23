#include "world/Scene.hpp"
#include <memory>

Scene::Scene(Registry givenRegistry,
             std::vector<std::unique_ptr<System>> givenSystems)
    : registry(std::move(givenRegistry)), systems(std::move(givenSystems)),
      inputEntity(registry.createEntity()) {
  initBlankInputState();
}

Scene::Scene() : inputEntity(registry.createEntity()) { initBlankInputState(); }

void Scene::update() {
  for (std::unique_ptr<System> &system : systems) {
    system->update(registry);
  }
}

void Scene::provideInput(const InputState &inputSnapshot) {
  registry.setComponent<InputState>(inputEntity, inputSnapshot);
}

void Scene::initBlankInputState() {
  InputState blankInputState;
  registry.addComponent(inputEntity, blankInputState);
}
