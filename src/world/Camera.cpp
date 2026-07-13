#include "world/Camera.hpp"
#include "config/Settings.hpp"
#include <algorithm>
#include <cmath>

Camera::Camera()
    : position(0.0f), direction(glm::vec3(0.0f, 0.0f, -1.0f)),
      up(glm::vec3(0.0f, 1.0f, 0.0f)), yaw(-90.0), pitch(0) {}

Camera::Camera(glm::vec3 givenPosition, glm::vec3 givenDirection)
    : position(givenPosition), direction(givenDirection),
      up(glm::vec3(0.0f, 1.0f, 0.0f)), yaw(0), pitch(0) {
  yaw = glm::degrees(atan2(direction.z, direction.x));
  pitch = glm::degrees(asin(direction.y));
}

const glm::mat4 Camera::getView() const {
  return glm::lookAt(position, position + direction, up);
}

// NOTE: Camera is currently able to free-fly in dev mode. Fix: bind position.y.
void Camera::moveForward(float amount) { position += direction * amount; }

void Camera::moveRight(float amount) {
  // Cross product = perpendicular two vectors, gives us right vector
  position += glm::cross(direction, up) * amount;
}

void Camera::setDirection(float yawDelta, float pitchDelta) {
  const CameraSettings &cs = Settings::getInstance().getCameraSettings();
  float sensitivity = cs.sensitivity;
  float pitchClamp = cs.pitchClamp;

  yaw += yawDelta * sensitivity;
  // SDL coordinate system thinks that moving mouse down = positive yrel.
  float newPitch = pitch - (pitchDelta * sensitivity);
  pitch = std::clamp(newPitch, -pitchClamp, pitchClamp);

  direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
  direction.y = sin(glm::radians(pitch));
  direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
}

Camera::~Camera() {}
