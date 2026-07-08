#pragma once

#include <glm/gtc/matrix_transform.hpp>

class Camera {
public:
  // Default Constructor - Sets up Camera
  Camera();
  // Overload Constructor - Takes in some values and sets up Camera accordingly.
  Camera(glm::vec3 position, glm::vec3 direction);
  // Destructor - Frees up memory within Renderer.
  ~Camera();

  // Returns a 4x4 matrix representing the view in the MVP matrix.
  const glm::mat4 getView() const;
  // Moves the player forward by the specified amount. Note that ingested
  // negative numbers will cause the player to move backwards.
  void moveForward(float amount);
  // Moves the player right by the specified amount. Note that ingested negative
  // numbers will cause the player to move backwards.
  void moveRight(float amount);

private:
  glm::vec3 position;
  glm::vec3 direction;
  glm::vec3 up;
};
