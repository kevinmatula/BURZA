#include "input/InputManager.hpp"
#include "SDL3/SDL_events.h"
#include "SDL3/SDL_keyboard.h"
#include "SDL3/SDL_scancode.h"

InputManager::InputManager()
    : quitRequested(false), mouseClicked(false), md(MouseDelta()),
      keysPressed() {}

void InputManager::pollEvent() {
  SDL_Event event;
  md.dx = 0;
  md.dy = 0;
  keysPressed.clear();
  mouseClicked = false;
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
      case SDL_EVENT_MOUSE_BUTTON_DOWN:
        mouseClicked = true;
        break;
      case SDL_EVENT_KEY_DOWN:
        keysPressed.insert(event.key.scancode);
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

bool InputManager::isKeyPressed(SDL_Scancode scancode) {
  return keysPressed.count(scancode);
}

MouseDelta InputManager::getMouseDelta() { return md; }

bool InputManager::isQuitRequested() { return quitRequested; }

bool InputManager::isMouseClicked() { return mouseClicked; }

InputManager::~InputManager() {}
