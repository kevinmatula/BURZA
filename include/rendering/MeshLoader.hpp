#pragma once

#include "VertexFormat.hpp"
#include <filesystem>
#include <vector>

// Custom representation for data needed to construct a mesh, as we will be
// using EBOs to reduce the total number of vertices needed.
struct MeshData {
  std::vector<float> vertices;
  std::vector<unsigned int> indices;

  // Constructor
  MeshData(const std::vector<float> &givenVertices,
           const std::vector<unsigned int> &givenIndices)
      : vertices(givenVertices), indices(givenIndices) {}
  // Destructor
  ~MeshData() {}
};

// Namespace to hold MeshLoader free functions that are always static.
namespace MeshLoader {
// Free function to take in a file path to obj files and return
MeshData load(const std::filesystem::path &fileSource, VertexFormat format);
}; // namespace MeshLoader
