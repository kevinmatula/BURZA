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
        std::vector<std::unique_ptr<System>> givenFixedUpdateSystems,
        std::vector<std::unique_ptr<System>> givenFrameUpdateSystems,
        std::vector<std::unique_ptr<System>> givenRenderSystems);
  // Default Constructor - Sets up a completely blank scene.
  Scene();

  // Calls run() on all fixed update subsystems.
  void fixedUpdate();
  // calls run() on all frame update subsystems.
  void frameUpdate();
  // Calls run() on all rendering subsystems.
  void render();
  // Feeds given InputState into our scene's native InputState.
  void provideInput(const InputState &inputState);

private:
  // Represents the scenes registry: the collection of components and entities.
  Registry registry;
  // Represents the collection of fixed update systems (run multiple times per
  // frame, depending on timestep) for this scene.
  std::vector<std::unique_ptr<System>> fixedUpdateSystems;
  // Represents the collection of update systems (runs once per frame) for this
  // scene.
  std::vector<std::unique_ptr<System>> frameUpdateSystems;
  // Represents the collection of render systems (run once per frame) for this
  // scene.
  std::vector<std::unique_ptr<System>> renderSystems;
  // The EntityID for this scene's single Input Entity.
  EntityID inputEntity;

  // Private function to initialize blank InputState. Primary use is to reduce
  // code-duplication within our Scene constructors.
  void initBlankInputState();
};
