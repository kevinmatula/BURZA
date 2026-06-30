#pragma once

#include "core/Window.hpp"
#include <SDL3/SDL.h>

class Renderer {
public:
  // Constructor - Sets up Renderer
  Renderer();
  // Destructor - Frees Memory within Renderer
  ~Renderer();

  // Draws onto the window with GLAD.
  void draw(Window &window);

private:
  // Private Function to Initialize & Check that Glad is Valid.
  void initializeGlad();
};
