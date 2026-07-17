#include "world/Camera.hpp"
#include "config/Settings.hpp"
#include <algorithm>
#include <cmath>

Camera::Camera()
    : position(0.0f), direction(glm::vec3(0.0f, 0.0f, -1.0f)), yaw(-90.0),
      pitch(0) {
  updateBasis();
}

Camera::Camera(glm::vec3 givenPosition, glm::vec3 givenDirection)
    : position(givenPosition), direction(givenDirection) {
  yaw = glm::degrees(atan2(direction.z, direction.x));
  pitch = glm::degrees(asin(direction.y));
  updateBasis();
}

const glm::mat4 Camera::getView() const {
  return glm::lookAt(position, position + direction, up);
}

const glm::vec3 Camera::getPosition() const { return position; }

const glm::vec3 Camera::getDirection() const { return direction; }

const glm::vec3 Camera::getUp() const { return up; }

const glm::vec3 Camera::getRight() const { return right; }

// NOTE: Camera is currently able to free-fly in dev mode. Fix: bind position.y.
void Camera::moveForward(float amount) { position += direction * amount; }

void Camera::moveRight(float amount) { position += right * amount; }

void Camera::setDirection(float yawDelta, float pitchDelta) {
  const CameraSettings &cs = Settings::getReadInstance().getCameraSettings();
  float sensitivity = cs.sensitivity;
  float pitchClamp = cs.pitchClamp;

  yaw += yawDelta * sensitivity;
  // SDL coordinate system thinks that moving mouse down = positive yrel.
  float newPitch = pitch - (pitchDelta * sensitivity);
  pitch = std::clamp(newPitch, -pitchClamp, pitchClamp);

  direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
  direction.y = sin(glm::radians(pitch));
  direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

  updateBasis();
}

void Camera::updateBasis() {
  glm::vec3 worldUp = {0.0f, 1.0f, 0.0f};
  // Cross product = perpendicular two vectors, gives us right vector
  right = glm::normalize(glm::cross(direction, worldUp));
  up = glm::normalize(glm::cross(right, direction));
}

Camera::~Camera() {}
