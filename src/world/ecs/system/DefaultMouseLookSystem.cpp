#include "world/ecs/system/DefaultMouseLookSystem.hpp"
#include "input/InputState.hpp"
#include "world/Camera.hpp"

DefaultMouseLookSystem::DefaultMouseLookSystem() {}

void DefaultMouseLookSystem::run(Registry &reg) {
  const InputState &input = reg.fetchSingleComponent<InputState>();
  Camera &camera = reg.fetchSingleComponent<Camera>();
  const MouseDelta &md = input.mouseMovement;
  camera.setDirection(md.dx, md.dy);
}
