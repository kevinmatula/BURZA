#pragma once

#include "input/InputState.hpp"
#include "world/ecs/Registry.hpp"
#include "world/ecs/system/System.hpp"
#include <memory>
#include <vector>

// class Scene - Uses ECS and holds a collection of systems and a registry
// connecting those system to entities.
class Scene {
public:
  // Constructor - Sets up a Scene w/ a Registry & corresponding Systems.
  Scene(Registry givenRegistry,
        std::vector<std::unique_ptr<System>> givenSystems);
  // Default Constructor - Sets up a completely blank scene.
  Scene();

  // Calls update() on all subsystems.
  void update();
  // Feeds InputState into Input Component.
  void provideInput(const InputState &inputState);

private:
  // Represents the scenes registry: the collection of components and entities.
  Registry registry;
  // Represents the collection of system for this scene.
  std::vector<std::unique_ptr<System>> systems;
};
