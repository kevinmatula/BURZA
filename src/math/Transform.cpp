#include "math/Transform.hpp"

Transform::Transform(glm::vec3 givenScale, RotationPair givenRotation,
                     glm::vec3 givenTranslation)
    : scale(givenScale), rotation(givenRotation),
      translation(givenTranslation) {}

Transform::Transform()
    : scale(1.0f), rotation(RotationPair(0, glm::vec3(0.0f))),
      translation(1.0f) {}

glm::mat4 Transform::returnModel() {
  glm::mat4 modelMatrix = glm::mat4(1.0f);
  modelMatrix = glm::translate(modelMatrix, translation);
  modelMatrix = glm::rotate(modelMatrix, rotation.angle, rotation.axis);
  modelMatrix = glm::scale(modelMatrix, scale);
  return modelMatrix;
}

void Transform::setScale(glm::vec3 givenScale) { scale = givenScale; }

void Transform::setRotation(RotationPair givenRotation) {
  rotation = givenRotation;
}

void Transform::setTranslation(glm::vec3 givenTranslation) {
  translation = givenTranslation;
}

Transform::~Transform() {}
