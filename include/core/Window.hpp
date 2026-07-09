#pragma once

#include <SDL3/SDL.h>

struct WindowSize {
  int width;
  int height;
};

class Window {
public:
  // Constructor - Sets up Window & OpenGL Context
  Window();
  // Destructor - Frees Window & OpenGL Context
  ~Window();

  // Swaps the Window with the next Buffer.
  void swap();
  // Gets a reference of the SDL window.
  WindowSize getWindowSize() const;
  // Sets the relative mouse mode to the given bool status.
  void setRelativeMouseMode(bool status);

  // Protect against double-free
  Window(const Window &) = delete;
  Window &operator=(const Window &) = delete;
  Window(Window &&) = delete;
  Window &operator=(Window &&) = delete;

private:
  // Private Function to Initialize & Check that GlContext is Valid.
  void initializeGlContext();
  // Private Function to Intialize & Check that Window is valid.
  void initializeWindow();
  // Private Function to set up OpenGL-specific attributes in our SDL Window.
  void setGlAttributes();

  SDL_Window *window;
  SDL_GLContext glContext;
};
