#include "world/Scene.hpp"
#include <memory>
#include <vector>

Scene::Scene(Registry givenRegistry,
             std::vector<std::unique_ptr<System>> givenFixedUpdateSystems,
             std::vector<std::unique_ptr<System>> givenFrameUpdateSystems,
             std::vector<std::unique_ptr<System>> givenRenderSystems)
    : registry(std::move(givenRegistry)),
      fixedUpdateSystems(std::move(givenFixedUpdateSystems)),
      frameUpdateSystems(std::move(givenFrameUpdateSystems)),
      renderSystems(std::move(givenRenderSystems)),
      inputEntity(registry.createEntity()) {
  initBlankInputState();
}

Scene::Scene() : inputEntity(registry.createEntity()) { initBlankInputState(); }

void Scene::fixedUpdate() {
  for (std::unique_ptr<System> &system : fixedUpdateSystems) {
    system->run(registry);
  }
}

void Scene::frameUpdate() {
  for (std::unique_ptr<System> &system : frameUpdateSystems) {
    system->run(registry);
  }
}

void Scene::render() {
  for (std::unique_ptr<System> &system : renderSystems) {
    system->run(registry);
  }
}

void Scene::provideInput(const InputState &inputSnapshot) {
  registry.setComponent<InputState>(inputEntity, inputSnapshot);
}

void Scene::initBlankInputState() {
  InputState blankInputState;
  registry.addComponent(inputEntity, blankInputState);
}
