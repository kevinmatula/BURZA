#pragma once

#include "config/Settings.hpp"
#include "input/InputState.hpp"
#include "input/KeyCode.hpp"
#include "world/ecs/system/System.hpp"

// class DefaultMovementSystem - Pre-packaged input system for basic keyboard
// movement.
class DefaultMovementSystem : public System {
public:
  // Default Constructor for DefaultMovementSystem
  DefaultMovementSystem();
  // Updates world visualization based on given keyboard input.
  void run(Registry &reg) override;

private:
  // CameraSettings declaration. This is non-entity related and keeps
  // DefaultMovementSystem stateless. Only exists to reduce code duplication.
  const CameraSettings &cs;
  // ApplicationSettings declaration. This is non-entity related and keeps
  // DefaultMovementSystem stateless. Only exists to reduce code duplication.
  const ApplicationSettings &as;

  // Checks if a given key (represented by KeyCode) is being held using the
  // given input snapshot.
  static bool isKeyHeld(const InputState &input, KeyCode key);
};
