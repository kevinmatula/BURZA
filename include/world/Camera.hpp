#pragma once

#include <glm/gtc/matrix_transform.hpp>

// class Camera - Represents the camera/player in BURZA. Games are meant to use
// this camera for first-person gameplay.
class Camera {
public:
  // Default Constructor - Sets up Camera
  Camera();
  // Overload Constructor - Takes in some values and sets up Camera accordingly.
  Camera(glm::vec3 position, glm::vec3 direction);

  // Returns a 4x4 matrix representing the view in the MVP matrix. Uses a cache
  // with invalidation pattern to lazy-load the view.
  const glm::mat4 &getView() const;
  // Returns a 4x4 matrix representing the projection in the MVP matrix. Uses a
  // cache with invalidation pattern to lazy-load the projection.
  const glm::mat4 &getProjection() const;
  // Returns the position member variable of the camera.
  const glm::vec3 getPosition() const;
  // Returns the direction member variable of the camera.
  const glm::vec3 getDirection() const;
  // Returns the up member variable of the camera.
  const glm::vec3 getUp() const;
  // Computes and returns the rightward vector of the camera.
  const glm::vec3 getRight() const;

  // Moves the player forward by the specified amount. Note that ingested
  // negative numbers will cause the player to move backwards.
  void moveForward(float amount);
  // Moves the player right by the specified amount. Note that ingested negative
  // numbers will cause the player to move backwards.
  void moveRight(float amount);
  // Sets the camera's direction using given yaw and pitch deltas.
  void setDirection(float yawDelta, float pitchDelta);
  // Sets the p_dirty member to true, indicating that the projection matrix must
  // be recomputed.
  void invalidateProjectionCache();

private:
  // Necessary vec3s representing different aspects of the camera.
  glm::vec3 position;
  glm::vec3 direction;
  glm::vec3 up;
  glm::vec3 right;

  // Represents the side-to-side direction the camera is looking
  float yaw;
  // Represents the up-and-down direction the camera is looking
  float pitch;

  // Cache with invalidation pattern.
  // NOTE: Re-evaluate this pattern when implementing parallelism, having these
  // mutable variables change in const functions will destroy any
  // multi-threading.

  // Cached view matrix as to not repeatedly compute.
  mutable glm::mat4 view;
  // Represents whether or not the view has changed from its previous state.
  mutable bool v_dirty = true;

  // Cached projection matrix
  mutable glm::mat4 projection;
  // Represents whether or not the projection has changed from previous state.
  mutable bool p_dirty = true;

  // Sets the rest of the basis vectors (the vectors that describe any point in
  // space). We only set direction in setDirection, and need to also set the up
  // and right vectors.
  void updateBasis();
};
