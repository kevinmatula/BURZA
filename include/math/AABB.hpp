#pragma once

#include "math/Transform.hpp"
#include "rendering/Frustum.hpp"
#include <glm/gtc/matrix_transform.hpp>

// struct AABB - Represents an axis-aligned bounding box, which surrounds the
// mesh of each entity and is crucial to the Frustum culling system.
struct AABB {
  // Default constructor for AABB
  AABB();

  // Constructor for AABB that takes in a minimum and maximum vector of the
  // mesh.
  AABB(const glm::vec3 &min, const glm::vec3 &max);

  // Constructor for AABB that ingests the center of the mesh, and the extent of
  // X, Y, and Z.
  AABB(const glm::vec3 &center, float givenIx, float givenIy, float givenIz);

  // Checks if this AABB exists on the given Frustum by transforming local
  // position to global and checking that it is within each plane in the
  // frustum.
  bool isOnFrustum(const Frustum &frustum, Transform &transform) const;

  // Checks if the AABB is on or in front of the given plane.
  // NOTE: This function uses complex math I found in an article !
  bool isOnOrForwardPlane(const Plane &plane) const;

  // Member Variables
  glm::vec3 center;
  glm::vec3 extents;
};
