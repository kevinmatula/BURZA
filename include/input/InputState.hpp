#pragma once
#include "input/KeyCode.hpp"
#include "input/MouseDelta.hpp"
#include <array>

// struct InputState - Represents a snapshot of all input at this tick (Keys
// currently pressed, mouse buttons currently clicked, pixels moved with mouse).
// This object is only valid for one frame.
struct InputState {
  std::array<bool, static_cast<size_t>(KeyCode::Max)> pressedKeys;
  MouseDelta mouseMovement;

  // Constructor - Takes in givenPressedKeys, givenMouseMovement & eventually
  // givenMouseClicks. Transforms givenPressedKeys pointer into local value.
  InputState(const bool *givenPressedKeys,
             const MouseDelta &givenMouseMovement);

  // Consumes a KeyCode enum and returns a boolean determining whether that key
  // has been pressed.
  bool isKeyPressed(KeyCode key) const;
};
