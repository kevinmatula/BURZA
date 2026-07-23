#include "input/InputState.hpp"
#include <cstring>

InputState::InputState(const bool *givenPressedKeys,
                       const MouseDelta &givenMouseMovement)
    : pressedKeys(), mouseMovement(givenMouseMovement) {
  memcpy(pressedKeys.data(), givenPressedKeys,
         sizeof(bool) * static_cast<size_t>(KeyCode::Max));
}

InputState::InputState() : pressedKeys(), mouseMovement() {}
