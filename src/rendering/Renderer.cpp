#include "rendering/Renderer.hpp"
#include "config/Settings.hpp"
#include <glad/glad.h>
#include <memory>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <vector>

Renderer::Renderer(const WindowSize &givenSize) {
  initializeGlad();
  glEnable(GL_CULL_FACE);
  glClearColor(0.7f, 0.9f, 0.1f, 1.0f);
  resize(givenSize);
}

void Renderer::initializeGlad() {
  if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
    SDL_Log("Glad Failed to Initialize.");
    throw std::runtime_error(std::string("Glad Failed to Initialize."));
  }
}

void Renderer::draw(const Scene &scene) {
  glClear(GL_COLOR_BUFFER_BIT);
  Frustum frustum = Frustum::createFrustumFromCamera(scene.getCamera(), aspect);
  const std::vector<std::shared_ptr<Entity>> &entities = scene.getEntities();
  std::unordered_map<MVP, glm::mat4> mvpMatrices = {
      {MVP::View, scene.getCamera().getView()}, {MVP::Projection, projection}};
  for (size_t i = 0; i < entities.size(); i++) {
    if (entities[i]->isOnFrustum(frustum)) {
      entities[i]->bindShader();
      entities[i]->matrixToShader(mvpMatrices);
      entities[i]->draw();
    }
  }
}

void Renderer::resize(const WindowSize &givenSize) {
  Settings &mutableSettings = Settings::getMutableInstance();

  glViewport(0, 0, givenSize.width, givenSize.height);
  mutableSettings.setWindowCurrentSize(givenSize.width, givenSize.height);

  const RendererSettings &rs =
      Settings::getReadInstance().getRendererSettings();
  projection = glm::perspective(
      glm::radians(rs.fov), float(givenSize.width) / float(givenSize.height),
      rs.startingLookDistance, rs.maxLookDistance);
  aspect = static_cast<float>(givenSize.width) / givenSize.height;
}

Renderer::~Renderer() {}
