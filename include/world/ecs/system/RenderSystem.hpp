#pragma once

#include "config/Settings.hpp"
#include "world/Camera.hpp"
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

private:
  // Draws all entities with Mesh, Shader, and Transform to the screen.
  void draw(Registry &reg, const std::vector<EntityID> &renderables,
            const Camera &camera) const;
  // Calculates and returns the projection matrix based on the current window
  // size, fov, and frustum size.
  glm::mat4 calculateProjection() const;

  // WindowSettings declaration. This is non-entity related and keeps
  // RenderSystem stateless. Only exists to reduce code duplication.
  const WindowSettings &ws;
  // RendererSettings declaration. This is non-entity related and keeps
  // RenderSystem stateless. Only exists to reduce code duplication.
  const RendererSettings &rs;
};
