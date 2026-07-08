#include "world/Camera.hpp"

Camera::Camera()
    : position(0.0f), direction(glm::vec3(0.0f, 0.0f, -1.0f)),
      up(glm::vec3(0.0f, 1.0f, 0.0f)) {}

Camera::Camera(glm::vec3 givenPosition, glm::vec3 givenDirection)
    : position(givenPosition), direction(givenDirection),
      up(glm::vec3(0.0f, 1.0f, 0.0f)) {}

const glm::mat4 Camera::getView() const {
  return glm::lookAt(position, position + direction, up);
}

void Camera::moveForward(float amount) { position += direction * amount; }

void Camera::moveRight(float amount) {
  // Cross product = perpendicular two vectors, gives us right vector
  position += glm::cross(direction, up) * amount;
}

Camera::~Camera() {}
