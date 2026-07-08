#include "input/InputManager.hpp"
#include "SDL3/SDL_keyboard.h"

InputManager::InputManager() : quitRequested(false) {}

void InputManager::pollEvent() {
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    switch (event.type) {
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

bool InputManager::isQuitRequested() { return quitRequested; }

InputManager::~InputManager() {}
