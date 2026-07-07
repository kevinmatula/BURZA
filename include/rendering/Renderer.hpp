#pragma once

#include "core/Window.hpp"
#include "world/Scene.hpp"
#include <SDL3/SDL.h>

class Renderer {
public:
  // Constructor - Sets up Renderer
  Renderer(WindowSize givenSize);
  // Destructor - Frees Memory within Renderer
  ~Renderer();

  // Draws onto the window with GLAD using the given scene as reference.
  void draw(const Scene &scene);

private:
  // Private Function to Initialize & Check that Glad is Valid.
  void initializeGlad();

  // Member variable representing the mat4 projection matrix.
  glm::mat4 projection;
};
