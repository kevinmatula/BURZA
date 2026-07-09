#pragma once

#include "core/Window.hpp"
#include "world/Scene.hpp"
#include <SDL3/SDL.h>

class Renderer {
public:
  // Constructor - Sets up Renderer
  Renderer(const WindowSize &givenSize);
  // Destructor - Frees Memory within Renderer
  ~Renderer();

  // Draws onto the window with GLAD using the given scene as reference.
  void draw(const Scene &scene);
  // Resizes the window & updates the projection matrix based on that new size.
  void resize(const WindowSize &givenSize);

private:
  // Private Function to Initialize & Check that Glad is Valid.
  void initializeGlad();

  // Member variable representing the mat4 projection matrix.
  glm::mat4 projection;
};
