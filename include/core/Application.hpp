#pragma once

#include "config/Settings.hpp"
#include "core/ApplicationInit.hpp"
#include "core/Window.hpp"
#include "input/InputManager.hpp"
#include "rendering/Renderer.hpp"
#include "world/Scene.hpp"

// Class Application - Orchestrates all subsystems to work together and make
// engine run.
class Application : private ApplicationInit {
public:
  // Constructor - Sets up Application
  Application();

  // Spins up the engine & runs the main game loop.
  void run();
  // Loads a given scene onto the application.
  void loadScene(Scene givenScene);

private:
  // Our Application is built off the following system-critical classes. These
  // must be instantiated within this given order as renderer relies on window
  // being established.
  Window window;
  Renderer renderer;
  InputManager inputManager;
  Scene scene;
  // Member variable that represents Application's Settings
  const ApplicationSettings &appSettings;

  // Updates the game state by one frame. Specifically, moves the camera and
  // associated matrices by one frame tick.
  void update();

  // Polls for events by pinging the InputManager and returns the state of the
  // game (quit or no-quit).
  bool pollInput();
};
