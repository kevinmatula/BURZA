#include "rendering/Mesh.hpp"
#include "rendering/VertexFormat.hpp"
#include <cstdint>

Mesh::Mesh(const std::vector<float> &vertexData, VertexFormat format) {

  // Generating Unique IDs for VAO & VBO.
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  bind();

  // For now using GL_STATIC_DRAW but can probably make
  // modular in future ?
  glBufferData(GL_ARRAY_BUFFER, (vertexData.size() * sizeof(float)),
               vertexData.data(), GL_STATIC_DRAW);

  std::vector<VertexAttribute> attributes = getVertexAttributes(format);
  const int vertexSize = findVertexSize(attributes);
  vertexCount = vertexData.size() / vertexSize;

  applyAndEnableAttributes(attributes, vertexSize);

  // Unbinding
  unbind();
}

void Mesh::bind() {
  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
}

void Mesh::unbind() {
  glBindVertexArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Mesh::draw() {
  bind();
  glDrawArrays(GL_TRIANGLES, 0, vertexCount);
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

int Mesh::findVertexSize(const std::vector<VertexAttribute> &attributes) {
  int vertexSize = 0;

  for (size_t i = 0; i < attributes.size(); i++) {
    vertexSize += attributes[i].size;
  }

  return vertexSize;
}

Mesh::~Mesh() {
  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
}
