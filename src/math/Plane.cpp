#include "math/Plane.hpp"

Plane::Plane() : normal({0.0f, 1.0f, 0.0f}), distance(0.0f) {}

Plane::Plane(const glm::vec3 &givenPoint, const glm::vec3 &givenNorm)
    : normal(glm::normalize(givenNorm)),
      distance(glm::dot(normal, givenPoint)) {}

float Plane::getSignedDistanceToPlane(const glm::vec3 &givenPoint) const {
  return glm::dot(normal, givenPoint) - distance;
}
