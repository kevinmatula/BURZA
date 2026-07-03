#include "rendering/Renderer.hpp"
#include <glad/glad.h>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

Renderer::Renderer() {
  initializeGlad();
  glClearColor(0.7f, 0.9f, 0.1f, 1.0f);
}

void Renderer::initializeGlad() {
  if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
    SDL_Log("Glad Failed to Initialize.");
    throw std::runtime_error(std::string("Glad Failed to Initialize."));
  }
}

void Renderer::draw(const Scene &scene) {
  glClear(GL_COLOR_BUFFER_BIT);
  const std::vector<std::shared_ptr<Entity>> &entities = scene.getEntities();
  for (size_t i = 0; i < entities.size(); i++) {
    entities[i]->draw();
  }
}

Renderer::~Renderer() {}
