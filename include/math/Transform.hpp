#pragma once

#include <SDL3/SDL.h>
#include <glm/gtc/matrix_transform.hpp>

// struct RotationPair - Custom representation for data needed to represent
// rotation.
struct RotationPair {
  // Represents angle in which we rotate an entity.
  float angle;
  // Represents axis to be rotated.
  glm::vec3 axis;

  // Constructor
  RotationPair(float givenAngle, glm::vec3 givenAxis)
      : angle(givenAngle), axis(givenAxis) {}
  // Overload Constructor - Defualt
  RotationPair() {}
};

// class Transform - Represents the transformation applied to Meshes. Attached
// to an Entity and primarily used to compute model matrix.
class Transform {
public:
  // Constructor - Sets up Transform
  Transform(glm::vec3 givenScale, RotationPair givenRotation,
            glm::vec3 givenTranslation);
  // Overload Constructor - Sets up default Transform
  Transform();

  // Computes and returns the model as a mat4 using local scale, rot, and trans.
  // Only computes if transform has been changed, will alter m_dirty and model
  // as side effect.
  const glm::mat4 &getModel() const;
  // Updates the Transform scale vec3 using the given scale.
  void setScale(glm::vec3 givenScale);
  // Updates the Transform rotation pair using the given rotation.
  void setRotation(RotationPair givenRotation);
  // Updates the Transform translation vec3 using the given translation.
  void setTranslation(glm::vec3 givenTranslation);

private:
  // Represents the amount to alter scale as a 3-point vector
  glm::vec3 scale;
  // Represents the rotation in which we alter an entity as a custom struct, see
  // signature.
  RotationPair rotation;
  // Represents the translation on an entity as a 3-point vector.
  glm::vec3 translation;

  // Cache with invalidation pattern.
  // NOTE: Re-evaluate this pattern when implementing parallelism, having these
  // mutable variables change in const functions will destroy any
  // multi-threading. Consider just re-computing upon every "set" call & keep
  // getModel const.

  // Cached model matrix as to not repeatedly compute.
  mutable glm::mat4 model;
  // Represents whether or not the model has changed from its previous state.
  mutable bool m_dirty = true;
};
