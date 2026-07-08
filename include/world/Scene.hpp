#pragma once

#include "world/Camera.hpp"
#include "world/Entity.hpp"
#include <memory>
#include <vector>

class Scene {
public:
  // Constructor - Sets up a Scene w/ entities and a camera
  Scene(const std::vector<std::shared_ptr<Entity>> &givenEntities,
        const Camera &givenCamera);
  // Overloaded constructor - Sets up a Scene w/ entities and default camera
  Scene(const std::vector<std::shared_ptr<Entity>> &givenEntities);
  // Overloaded default constructor for initilization
  Scene();
  // Destructor - Frees Memory within Scene
  ~Scene();

  // Returns all entities present in scene, as a const reference.
  const std::vector<std::shared_ptr<Entity>> &getEntities() const;
  // Returns the camera, as a const reference.
  const Camera &getCamera() const;
  // Returns the camera by refrerence, for mutation purposes.
  Camera &getCamera();

private:
  // Represents all entities within the scene.
  std::vector<std::shared_ptr<Entity>> entities;
  // Represents the camera within the scene.
  Camera camera;
};
