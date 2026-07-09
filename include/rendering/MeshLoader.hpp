#pragma once

#include "VertexFormat.hpp"
#include <filesystem>
#include <vector>

// Namespace to hold MeshLoader free functions that are always static.
namespace MeshLoader {
// Free function to take in a file path to obj files and return
std::vector<float> load(const std::filesystem::path &fileSource,
                        VertexFormat format);
}; // namespace MeshLoader
