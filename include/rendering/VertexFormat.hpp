#pragma once

#include <glad/glad.h>
#include <stdexcept>
#include <vector>

// enum class VertexFormat - Represents the different combinations of Vertices
// we can have.
enum class VertexFormat { Position };

// struct VertexAttribute - Holds all pre-defined values for vertices.
struct VertexAttribute {
  GLuint index;
  GLint size;
  GLenum type;
  GLboolean normalized;
};

// Ingests a VertexFormat and returns a list of different attributes and their
// respective fields that define them.
inline std::vector<VertexAttribute> getVertexAttributes(VertexFormat format) {
  std::vector<VertexAttribute> attributes;
  switch (format) {
    case VertexFormat::Position:
      attributes.push_back({0, 3, GL_FLOAT, GL_FALSE});
      break;
    default:
      throw std::runtime_error(
          std::string("Incorrect Vertex Format Provided."));
  }
  return attributes;
}
