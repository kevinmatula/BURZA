#pragma once

#include "VertexFormat.hpp"
#include "math/AABB.hpp"
#include "rendering/MeshLoader.hpp"
#include <glad/glad.h>
#include <vector>

// class Mesh - Represents a collection of vertex data points and works closely
// with OpenGL.
class Mesh {
public:
  // Constructor - Sets up VAO & VBO, as well as VertexAttributes
  Mesh(const MeshData &vertexData, VertexFormat format);
  // Destructor - Frees Memory within Mesh, destroying VAO, VBO, etc.
  ~Mesh();

  // Draws this Mesh onto the screen.
  void draw() const;
  // Getter - Returns the AABB as a const reference.
  const AABB &getAABB() const;

  // Protect against double-free
  Mesh(const Mesh &) = delete;
  Mesh &operator=(const Mesh &) = delete;
  Mesh(Mesh &&) = delete;
  Mesh &operator=(Mesh &&) = delete;

private:
  // Binds the Vertex Array Object and the Vertex Buffer Object.
  void bind() const;
  // Unbinds the VAO & VBO.
  void unbind() const;
  // Applies all attributes to the vertex buffer and enables them.
  void applyAndEnableAttributes(const std::vector<VertexAttribute> &attributes,
                                const int vertexSize);
  // Finds the vertex size - the amount of values stored per vertex.
  int computeVertexSize(const std::vector<VertexAttribute> &attributes);

  // Represents OpenGL Vertex Array Object & OpenGL Vertex Buffer Object &
  // OpenGL Element Buffer Object.
  unsigned int VAO, VBO, EBO;
  // Represents the amount of vertices in each mesh.
  int vertexCount;
  // Represents the AABB that surrounds the mesh. Uses the extent of the entire
  // mesh to construct the AABB.
  AABB aabb;
};
