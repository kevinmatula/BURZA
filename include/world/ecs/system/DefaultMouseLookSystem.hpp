#pragma once

#include "world/ecs/system/System.hpp"

// class DefaultMouseLookSystem - Pre-packaged input system for basic mouse
// movement (dx, dy).
class DefaultMouseLookSystem : public System {
public:
  // Default Constructor for DefaultMouseLookSystem
  DefaultMouseLookSystem();
  // Updates world visualization based on given mouse input.
  void run(Registry &reg) override;
};
