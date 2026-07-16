#pragma once

#include "world/ecs/system/System.hpp"

class RenderSystem : public System {
public:
  // Default Constructor for RenderSystem
  RenderSystem();
  // Defualt Destructor for RenderSystem, overrides virtual destructor from
  // System.
  ~RenderSystem() override;
  // Draws all entities with Mesh, Shader, and Transform onto the screen.
  void update(Registry &reg) override;
};
