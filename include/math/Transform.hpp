#pragma once

#include <SDL3/SDL.h>
#include <glm/gtc/matrix_transform.hpp>

// Custom representation for data needed to represent rotation.
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
  // Destructor
  ~RotationPair() {}
};

class Transform {
public:
  // Constructor - Sets up Transform
  Transform(glm::vec3 givenScale, RotationPair givenRotation,
            glm::vec3 givenTranslation);
  // Overload Constructor - Sets up default Transform
  Transform();
  // Destructor - Frees Memory within Transform
  ~Transform();

  // Computes and returns the model as a mat4 using local scale, rot, and trans.
  glm::mat4 getModel();
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
};
