#include "math/AABB.hpp"

AABB::AABB() : center({0.0f, 0.0f, 0.0f}), extents({0.0f, 0.0f, 0.0f}) {}

AABB::AABB(const glm::vec3 &min, const glm::vec3 &max)
    : center((max + min) * 0.5f),
      extents({max.x - center.x, max.y - center.y, max.z - center.z}) {}

AABB::AABB(const glm::vec3 &givenCenter, float givenIx, float givenIy,
           float givenIz)
    : center(givenCenter), extents({givenIx, givenIy, givenIz}) {}

bool AABB::isOnFrustum(const Frustum &frustum, Transform &transform) const {
  const glm::mat4 model = transform.computeModel();

  // Transform local center to global
  const glm::vec3 globalCenter{model * glm::vec4(center, 1.0f)};

  // Scaled orientation of right, up, and forward
  const glm::vec3 right = model[0] * extents.x;
  const glm::vec3 up = model[1] * extents.y;
  const glm::vec3 forward = -(model[2] * extents.z);

  const float newIx =
      std::abs(glm::dot(glm::vec3({1.0f, 0.0f, 0.0f}), right)) +
      std::abs(glm::dot(glm::vec3({1.0f, 0.0f, 0.0f}), up)) +
      std::abs(glm::dot(glm::vec3({1.0f, 0.0f, 0.0f}), forward));

  const float newIy =
      std::abs(glm::dot(glm::vec3({0.0f, 1.0f, 0.0f}), right)) +
      std::abs(glm::dot(glm::vec3({0.0f, 1.0f, 0.0f}), up)) +
      std::abs(glm::dot(glm::vec3({0.0f, 1.0f, 0.0f}), forward));

  const float newIz =
      std::abs(glm::dot(glm::vec3({0.0f, 0.0f, 1.0f}), right)) +
      std::abs(glm::dot(glm::vec3({0.0f, 0.0f, 1.0f}), up)) +
      std::abs(glm::dot(glm::vec3({0.0f, 0.0f, 1.0f}), forward));

  const AABB globalAABB(globalCenter, newIx, newIy, newIz);

  return (globalAABB.isOnOrForwardPlane(frustum.leftFace) &&
          globalAABB.isOnOrForwardPlane(frustum.rightFace) &&
          globalAABB.isOnOrForwardPlane(frustum.topFace) &&
          globalAABB.isOnOrForwardPlane(frustum.bottomFace) &&
          globalAABB.isOnOrForwardPlane(frustum.nearFace) &&
          globalAABB.isOnOrForwardPlane(frustum.farFace));
}

bool AABB::isOnOrForwardPlane(const Plane &plane) const {
  const float r = (extents.x * std::abs(plane.normal.x)) +
                  (extents.y * std::abs(plane.normal.y)) +
                  (extents.z * std::abs(plane.normal.z));
  return -r <= plane.getSignedDistanceToPlane(center);
}

AABB::~AABB() {}
