#pragma once

#include "world/ecs/Registry.hpp"

// class System - Abstract Base Class for concrete System classes (i.e.,
// MovementSystem) that does logic on select components. Cornerstone of ECS
// system in BURZA.
class System {
public:
  // Virtual Destructor - Frees Memory within System, called to proper subclass.
  virtual ~System() = default;

  // Pure virtual function to update system and game state depending on values
  // in container registry.
  virtual void run(Registry &reg) = 0;
};
