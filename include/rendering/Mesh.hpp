#pragma once

#include "VertexFormat.hpp"
#include <glad/glad.h>
#include <vector>

class Mesh {
public:
  // Constructor - Sets up VAO & VBO, as well as
  Mesh(const std::vector<float> &vertices, VertexFormat format);
  // Destructor - Frees Memory within Mesh, destroying VAO, VBO, etc.
  ~Mesh();

  // Draws this Mesh onto the screen.
  void draw();

  // Protect against double-free
  Mesh(const Mesh &) = delete;
  Mesh &operator=(const Mesh &) = delete;
  Mesh(Mesh &&) = delete;
  Mesh &operator=(Mesh &&) = delete;

private:
  // Binds the Vertex Array Object and the Vertex Buffer Object.
  void bind();
  // Unbinds the VAO & VBO.
  void unbind();
  // Applies all attributes to the vertex buffer and enables them.
  void applyAndEnableAttributes(const std::vector<VertexAttribute> &attributes,
                                const int vertexSize);
  // Finds the vertex size - the amount of values stored per vertex.
  int findVertexSize(const std::vector<VertexAttribute> &attributes);

  // Represents OpenGL Vertex Array Object & OpenGL Vertex Buffer Object.
  unsigned int VAO, VBO;
  // Represents the amount of vertices in each mesh.
  int vertexCount;
};
