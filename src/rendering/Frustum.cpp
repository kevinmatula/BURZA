#include "rendering/Frustum.hpp"
#include "config/Settings.hpp"

Frustum::Frustum() {}

Frustum Frustum::createFrustumFromCamera(const Camera &cam, float aspect) {
  Frustum frustum;

  glm::vec3 camDirection = cam.getDirection();
  glm::vec3 camPosition = cam.getPosition();
  glm::vec3 camUp = cam.getUp();
  glm::vec3 camRight = cam.getRight();

  const RendererSettings &rs = Settings::getInstance().getRendererSettings();

  const float halfBackHeight =
      rs.maxLookDistance * tanf(glm::radians(rs.fov) * 0.5f);
  const float halfBackWidth = halfBackHeight * aspect;
  const glm::vec3 camToFarRect = rs.maxLookDistance * camDirection;

  frustum.nearFace = {camPosition + rs.startingLookDistance * camDirection,
                      camDirection};
  frustum.farFace = {camPosition + camToFarRect, -camDirection};
  frustum.rightFace = {
      camPosition, glm::cross(camToFarRect - camRight * halfBackWidth, camUp)};
  frustum.leftFace = {
      camPosition, glm::cross(camUp, camToFarRect + camRight * halfBackWidth)};
  frustum.topFace = {
      camPosition, glm::cross(camRight, camToFarRect - camUp * halfBackHeight)};
  frustum.bottomFace = {
      camPosition, glm::cross(camToFarRect + camUp * halfBackHeight, camRight)};

  return frustum;
}

Frustum::~Frustum() {}
