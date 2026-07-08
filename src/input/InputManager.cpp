#include "input/InputManager.hpp"
#include "SDL3/SDL_keyboard.h"

InputManager::InputManager() : quitRequested(false), md(MouseDelta()) {}

void InputManager::pollEvent() {
  SDL_Event event;
  md.dx = 0;
  md.dy = 0;
  while (SDL_PollEvent(&event)) {
    switch (event.type) {
      case SDL_EVENT_MOUSE_MOTION:
        md.dx += event.motion.xrel;
        md.dy += event.motion.yrel;
        break;
      case SDL_EVENT_WINDOW_CLOSE_REQUESTED:
      case SDL_EVENT_QUIT:
        quitRequested = true;
        break;
      case SDL_EVENT_KEY_DOWN:
        if (event.key.key == SDLK_ESCAPE) {
          quitRequested = true;
        }
        break;
      default:
        break;
    }
  }
}

bool InputManager::isKeyHeld(SDL_Scancode scancode) {
  const bool *keyboardState = SDL_GetKeyboardState(NULL);
  return keyboardState[scancode];
}

MouseDelta InputManager::getMouseDelta() { return md; }

bool InputManager::isQuitRequested() { return quitRequested; }

InputManager::~InputManager() {}
