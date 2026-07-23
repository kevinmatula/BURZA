#include "world/ecs/system/DefaultMovementSystem.hpp"
#include "input/InputState.hpp"
#include "world/Camera.hpp"

DefaultMovementSystem::DefaultMovementSystem()
    : cs(Settings::getReadInstance().getCameraSettings()),
      as(Settings::getReadInstance().getApplicationSettings()) {}

void DefaultMovementSystem::run(Registry &reg) {
  const InputState &input = reg.fetchSingleComponent<InputState>();
  Camera &camera = reg.fetchSingleComponent<Camera>();
  double cameraVel = cs.movementSpeed * as.dt;
  if (isKeyHeld(input, KeyCode::W)) {
    camera.moveForward(cameraVel);
  }
  if (isKeyHeld(input, KeyCode::S)) {
    camera.moveForward(-cameraVel);
  }
  if (isKeyHeld(input, KeyCode::D)) {
    camera.moveRight(cameraVel);
  }
  if (isKeyHeld(input, KeyCode::A)) {
    camera.moveRight(-cameraVel);
  }
}

bool DefaultMovementSystem::isKeyHeld(const InputState &input, KeyCode key) {
  return input.pressedKeys[static_cast<size_t>(key)];
}
