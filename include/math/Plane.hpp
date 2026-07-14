#pragma once
#include <glm/gtc/matrix_transform.hpp>

// Struct Plane - Represents a plane in 3D space.
struct Plane {
  // Default Constructor - sets up default plane (floor).
  Plane();
  // Custom overloaded constructor - takes in an arbitrary point and the given
  // normal and constructs a Plane object.
  Plane(const glm::vec3 &givenPoint, const glm::vec3 &givenNormal);
  // Destructor - frees memory within Plane.
  ~Plane();

  // This function returns the distance between the given point and the plane.
  float getSignedDistanceToPlane(const glm::vec3 &givenPoint) const;

  // Represents the direction of the normal vector on the Plane.
  glm::vec3 normal;
  // Represents the distance between the plane and the origin, along the normal
  // vector.
  float distance;
};
