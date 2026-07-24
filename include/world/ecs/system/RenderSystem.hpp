#pragma once

#include "config/Settings.hpp"
#include "world/Camera.hpp"
#include "world/ecs/system/System.hpp"

class RenderSystem : public System {
public:
  // Default Constructor for RenderSystem
  RenderSystem();
  // Draws all entities with Mesh, Shader, and Transform onto the screen.
  void run(Registry &reg) override;

private:
  // Draws all entities with Mesh, Shader, and Transform to the screen.
  void draw(Registry &reg, const std::vector<EntityID> &renderables,
            const Camera &camera) const;

  // WindowSettings declaration. This is non-entity related and keeps
  // RenderSystem stateless. Only exists to reduce code duplication.
  const WindowSettings &ws;
};
