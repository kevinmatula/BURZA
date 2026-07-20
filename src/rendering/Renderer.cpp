#include "rendering/Renderer.hpp"
#include "config/Settings.hpp"
#include <glad/glad.h>
#include <stdexcept>
#include <string>

Renderer::Renderer(const WindowSize &givenSize) {
  initializeGlad();
  glEnable(GL_CULL_FACE);
  glEnable(GL_DEPTH_TEST);
  glClearColor(0.7f, 0.9f, 0.1f, 1.0f);
  resize(givenSize);
}

void Renderer::initializeGlad() {
  if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
    SDL_Log("Glad Failed to Initialize.");
    throw std::runtime_error(std::string("Glad Failed to Initialize."));
  }
}

void Renderer::clear() { glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); }

void Renderer::resize(const WindowSize &givenSize) {
  Settings &mutableSettings = Settings::getMutableInstance();

  glViewport(0, 0, givenSize.width, givenSize.height);
  mutableSettings.setWindowCurrentSize(givenSize.width, givenSize.height);

  // TODO: remove once ECS commit is created.
  const RendererSettings &rs =
      Settings::getReadInstance().getRendererSettings();
  projection = glm::perspective(
      glm::radians(rs.fov), float(givenSize.width) / float(givenSize.height),
      rs.startingLookDistance, rs.maxLookDistance);
  aspect = static_cast<float>(givenSize.width) / givenSize.height;
}

Renderer::~Renderer() {}
