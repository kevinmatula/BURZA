#pragma once
#include "input/KeyCode.hpp"
#include "input/MouseDelta.hpp"
#include <array>

// struct InputState - Represents a snapshot of all input at this tick (Keys
// currently pressed, mouse buttons currently clicked, pixels moved with mouse).
// This object is only valid for one frame.
struct InputState {
  // Represents a boolean array, identical to that of SDLs Library, representing
  // the status of each key on a keyboard.
  std::array<bool, static_cast<size_t>(KeyCode::Max)> pressedKeys;
  // Represents the x and y movement of the mouse.
  MouseDelta mouseMovement;

  // Constructor - Takes in givenPressedKeys, givenMouseMovement & eventually
  // givenMouseClicks. Transforms givenPressedKeys pointer into local value.
  InputState(const bool *givenPressedKeys,
             const MouseDelta &givenMouseMovement);

  // Default Constructor for InputState.
  InputState();
};
