#pragma once

#include "world/Scene.hpp"
#include <SDL3/SDL.h>

class Renderer {
public:
  // Constructor - Sets up Renderer
  Renderer();
  // Destructor - Frees Memory within Renderer
  ~Renderer();

  // Draws onto the window with GLAD using the given scene as reference.
  void draw(const Scene &scene);

private:
  // Private Function to Initialize & Check that Glad is Valid.
  void initializeGlad();
};
