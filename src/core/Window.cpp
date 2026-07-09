#include "core/Window.hpp"
#include "SDL3/SDL_mouse.h"
#include <stdexcept>
#include <string>

Window::Window() {
  setGlAttributes();
  initializeWindow();
  initializeGlContext();
}

void Window::initializeGlContext() {
  glContext = SDL_GL_CreateContext(window);
  if (glContext == NULL) {
    SDL_Log("OpenGL Context Failed to Initialize.");
    throw std::runtime_error(
        std::string("OpenGL Context Failed to Initialize."));
  }
}

void Window::initializeWindow() {
  window = SDL_CreateWindow("BURZA", 1500, 1000,
                            SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
  if (window == NULL) {
    SDL_Log("Window Failed to Initialize.");
    throw std::runtime_error(std::string("Window Failed to Initialize."));
  }
}

void Window::setGlAttributes() {
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
}

void Window::swap() { SDL_GL_SwapWindow(window); }

WindowSize Window::getWindowSize() const {
  int width;
  int height;
  SDL_GetWindowSize(window, &width, &height);
  return {width, height};
}

void Window::setRelativeMouseMode(bool status) {
  SDL_SetWindowRelativeMouseMode(window, status);
}

Window::~Window() {
  SDL_GL_DestroyContext(glContext);
  SDL_DestroyWindow(window);
}
