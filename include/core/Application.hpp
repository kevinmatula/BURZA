#pragma once

#include "core/ApplicationInit.hpp"
#include "core/Window.hpp"
#include "input/InputManager.hpp"
#include "rendering/Renderer.hpp"
#include <SDL3/SDL.h>

class Application : private ApplicationInit {
public:
  // Constructor - Sets up Application
  Application();
  // Destructor - Frees all data within Application
  ~Application();

  // Spins up the engine & runs the main game loop.
  void run();

private:
  // Our Application is built off the following system-critical classes. These
  // must be instantiated within this given order as renderer relies on window
  // being established.
  Window window;
  Renderer renderer;
  InputManager inputManager;

  // Represents time passed between each frame (60 FPS).
  static constexpr double timePerFrame = 1.0 / 60.0;
};
