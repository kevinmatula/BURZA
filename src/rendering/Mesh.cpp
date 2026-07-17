#include "rendering/Mesh.hpp"
#include "rendering/VertexFormat.hpp"
#include <cstdint>

Mesh::Mesh(const MeshData &vertexData, VertexFormat format)
    : aabb(vertexData.min, vertexData.max) {
  // Generating Unique IDs for VAO & VBO.
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glGenBuffers(1, &EBO);
  bind();

  glBufferData(GL_ARRAY_BUFFER, (vertexData.vertices.size() * sizeof(float)),
               vertexData.vertices.data(), GL_STATIC_DRAW);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER,
               (vertexData.indices.size() * sizeof(unsigned int)),
               vertexData.indices.data(), GL_STATIC_DRAW);

  std::vector<VertexAttribute> attributes = getVertexAttributes(format);
  const int vertexSize = computeVertexSize(attributes);
  vertexCount = vertexData.indices.size();

  applyAndEnableAttributes(attributes, vertexSize);

  unbind();
}

void Mesh::bind() const {
  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
}

void Mesh::unbind() const {
  glBindVertexArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Mesh::draw() const {
  bind();
  glDrawElements(GL_TRIANGLES, vertexCount, GL_UNSIGNED_INT, 0);
  unbind();
}

void Mesh::applyAndEnableAttributes(
    const std::vector<VertexAttribute> &attributes, const int vertexSize) {
  int stride = vertexSize * sizeof(float);

  for (size_t i = 0; i < attributes.size(); i++) {
    uintptr_t offset = 0;
    for (size_t acc = 0; acc < i; acc++) {
      offset += (attributes[acc].size * sizeof(float));
    }
    glVertexAttribPointer(attributes[i].index, attributes[i].size,
                          attributes[i].type, attributes[i].normalized, stride,
                          (void *)offset);
    glEnableVertexAttribArray(attributes[i].index);
  }
}

int Mesh::computeVertexSize(const std::vector<VertexAttribute> &attributes) {
  int vertexSize = 0;

  for (size_t i = 0; i < attributes.size(); i++) {
    vertexSize += attributes[i].size;
  }

  return vertexSize;
}

const AABB &Mesh::getAABB() const { return aabb; }

Mesh::~Mesh() {
  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
  glDeleteBuffers(1, &EBO);
}
