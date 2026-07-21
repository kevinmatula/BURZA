#pragma once

#include "rendering/Mesh.hpp"
#include <memory>

struct MeshComponent {
  // Standard Constructor - Takes in a shared_ptr Mesh and copies it into this
  // object's reference, increasing count.
  MeshComponent(const std::shared_ptr<Mesh> &givenMesh) : mesh(givenMesh) {}
  // Represent a Mesh. Shared_ptr so we can have multiple entities share the
  // same mesh overhead.
  std::shared_ptr<Mesh> mesh;
};
