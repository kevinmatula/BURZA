#pragma once

#include "VertexFormat.hpp"
#include <filesystem>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

// Custom representation for data needed to construct a mesh, as we will be
// using EBOs to reduce the total number of vertices needed.
// TODO: Separate definition into cpp.
struct MeshData {
  std::vector<float> vertices;
  std::vector<unsigned int> indices;
  glm::vec3 min;
  glm::vec3 max;

  // Constructor
  MeshData(const std::vector<float> &givenVertices,
           const std::vector<unsigned int> &givenIndices,
           const glm::vec3 &givenMin, const glm::vec3 &givenMax)
      : vertices(givenVertices), indices(givenIndices), min(givenMin),
        max(givenMax) {}
  // Destructor
  ~MeshData() {}
};

// Namespace to hold MeshLoader free functions that are always static.
namespace MeshLoader {
// Free function to take in a file path to obj files and return
MeshData load(const std::filesystem::path &fileSource, VertexFormat format);
}; // namespace MeshLoader
