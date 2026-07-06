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
  glm::mat4 returnView();

private:
  glm::vec3 position;
  glm::vec3 direction;
};
