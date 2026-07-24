#include "math/Transform.hpp"

Transform::Transform(glm::vec3 givenScale, RotationPair givenRotation,
                     glm::vec3 givenTranslation)
    : scale(givenScale), rotation(givenRotation), translation(givenTranslation),
      m_dirty(true) {
  getModel();
}

Transform::Transform()
    : scale(1.0f), rotation(RotationPair(0, glm::vec3(1.0f))),
      translation(0.0f), m_dirty(true) {
  getModel();
}

const glm::mat4 &Transform::getModel() const {
  if (m_dirty) {
    glm::mat4 modelMatrix = glm::mat4(1.0f);
    modelMatrix = glm::translate(modelMatrix, translation);
    modelMatrix = glm::rotate(modelMatrix, rotation.angle, rotation.axis);
    modelMatrix = glm::scale(modelMatrix, scale);
    m_dirty = false;
    model = modelMatrix;
  }
  return model;
}

void Transform::setScale(glm::vec3 givenScale) {
  scale = givenScale;
  m_dirty = true;
}

void Transform::setRotation(RotationPair givenRotation) {
  rotation = givenRotation;
  m_dirty = true;
}

void Transform::setTranslation(glm::vec3 givenTranslation) {
  translation = givenTranslation;
  m_dirty = true;
}
