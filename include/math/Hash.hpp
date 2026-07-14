#pragma once

#include <vector>

// struct VectorHasher - Allows for vectors of any type to be hashed (primarily
// used for vector<float>). Typically an anti-pattern but helpful for graphics
// rendering because file inputs are safe.
template <typename T> struct VectorHasher {
  std::size_t operator()(const std::vector<T> &vec) const noexcept {
    std::size_t seed = vec.size();

    for (const auto &element : vec) {
      std::size_t element_hash = std::hash<T>{}(element);
      seed ^= element_hash + 0x9e3779b9 + (seed << 6) + (seed >> 2);
    }
    return seed;
  }
};
