#pragma once

#include "world/Entity.hpp"
#include <memory>
#include <vector>

class Scene {
public:
  // Constructor - Sets up a Scene
  Scene(const std::vector<std::shared_ptr<Entity>> &givenEntities);
  // Overloaded default constructor for initilization
  Scene();
  // Destructor - Frees Memory within Scene
  ~Scene();

  // Returns all entities present in scene
  const std::vector<std::shared_ptr<Entity>> &getEntities() const;

private:
  // Represents all entities within the scene.
  std::vector<std::shared_ptr<Entity>> entities;
};
