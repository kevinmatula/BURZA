#pragma once
#include <SDL3/SDL.h>

// This class exists so SDL can be initialized before any other member variables
// of Application.
class ApplicationInit {
protected:
  // Constructor - Sets up ApplicationInit, more specifically, instantiates SDL
  // before all other member constructors.
  ApplicationInit();
  // Destructor - Frees ApplicationInit, more specifically, kills SDL.
  ~ApplicationInit();

  // Protect against double-free
  ApplicationInit(const ApplicationInit &) = delete;
  ApplicationInit &operator=(const ApplicationInit &) = delete;
  ApplicationInit(ApplicationInit &&) = delete;
  ApplicationInit &operator=(ApplicationInit &&) = delete;

private:
  // Private Function to Initialize & Check that SDL is valid.
  void initializeSDL();
};
