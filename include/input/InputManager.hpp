#pragma once

#include <SDL3/SDL.h>

class InputManager {
public:
  // Constructor - Sets up InputManager
  InputManager();
  // Destructor - Frees Memory within InputManager
  ~InputManager();

  // Called by Application to check for Polled Event
  void pollEvent();
  // Getter - Returns the boolean status of quitRequested
  bool isQuitRequested();

private:
  // Represents whether or not a user wants to quit
  bool quitRequested;
};
