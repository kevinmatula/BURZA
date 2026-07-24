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
      renderSystems(std::move(givenRenderSystems)) {
  initDefaultResources();
}

Scene::Scene() { initDefaultResources(); }

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

void Scene::setInput(const InputState &inputSnapshot) {
  registry.setResource(inputSnapshot);
}

void Scene::setCamera(const Camera &givenCamera) {
  registry.setResource(givenCamera);
}

void Scene::initDefaultResources() {
  registry.addResource(Camera{});
  registry.addResource(InputState{});
}
