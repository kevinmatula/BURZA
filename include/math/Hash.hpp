#pragma once

#include "world/ecs/EntityID.hpp"
#include <vector>

// struct VectorHasher - Allows for vectors of any type to be hashed (primarily
// used for vector<float>). Typically an anti-pattern but helpful for graphics
// rendering because file inputs are safe.
template <typename T> struct VectorHash {
  std::size_t operator()(const std::vector<T> &vec) const noexcept {
    std::size_t seed = vec.size();

    for (const auto &element : vec) {
      std::size_t element_hash = std::hash<T>{}(element);
      seed ^= element_hash + 0x9e3779b9 + (seed << 6) + (seed >> 2);
    }
    return seed;
  }
};

struct EntityIDHash {
  std::size_t operator()(const EntityID &givenId) const noexcept {
    return std::hash<unsigned int>{}(givenId.id);
  }
};
