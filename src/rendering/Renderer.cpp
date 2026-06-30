#include "rendering/Renderer.hpp"
#include <glad/glad.h>
#include <stdexcept>
#include <string>

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

void Renderer::draw(Window &window) {
  glClear(GL_COLOR_BUFFER_BIT);
  window.swap();
}

Renderer::~Renderer() {}
