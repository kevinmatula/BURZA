#include "world/Camera.hpp"

Camera::Camera() : position(0.0f), direction(glm::vec3(0.0f, 0.0f, -1.0f)) {}

Camera::Camera(glm::vec3 givenPosition, glm::vec3 givenDirection)
    : position(givenPosition), direction(givenDirection) {}

glm::mat4 Camera::returnView() {
  return glm::lookAt(position, position + direction,
                     glm::vec3(0.0f, 1.0f, 0.0f));
}

Camera::~Camera() {}
