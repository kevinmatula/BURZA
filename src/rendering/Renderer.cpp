#include "rendering/Renderer.hpp"
#include "rendering/Shader.hpp"
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
  Shader shader("assets/shaders/vertex.vert", "assets/shaders/fragment.frag");
  shader.use();

  // VAO STUFF
  unsigned int VAO;
  glGenVertexArrays(1, &VAO);
  glBindVertexArray(VAO);
  //

  // VBO STUFF
  float vertices[] = {-0.5f, -0.5f, 0.0f, 0.5f, -0.5f, 0.0f, 0.0f, 0.5f, 0.0f};
  unsigned int VBO;
  glGenBuffers(1, &VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  //

  // Linking Vertex Attributes
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);
  //

  // Drawing
  glDrawArrays(GL_TRIANGLES, 0, 3);
  glBindVertexArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  //

  window.swap();
}

Renderer::~Renderer() {}
