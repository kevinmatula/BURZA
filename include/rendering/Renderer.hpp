#pragma once

#include "core/Window.hpp"
#include <SDL3/SDL.h>
#include <glm/gtc/matrix_transform.hpp>

// class Renderer - Deals with all concepts related to rendering pixels onto the
// screen. Orchestrates most OpenGL concepts together.
class Renderer {
public:
  // Constructor - Sets up Renderer
  Renderer(const WindowSize &givenSize);

  // Clears OpenGL Variables for each tick. Unrelated to Entity Rendering but
  // paramount to actual rendering pipeline.
  void clear();
  // Resizes the window & updates the projection matrix based on that new size.
  void resize(const WindowSize &givenSize);

private:
  // Private Function to Initialize & Check that Glad is Valid.
  void initializeGlad();
};
