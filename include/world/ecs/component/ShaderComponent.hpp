#pragma once

#include "rendering/Shader.hpp"
#include <memory>

struct ShaderComponent {
  // Standard Constructor - Takes in a shared_ptr Shader and copies it into this
  // object's reference, increasing count.
  ShaderComponent(const std::shared_ptr<Shader> &givenShader)
      : shader(givenShader) {}
  // Represent a Shader. Shared_ptr so we can have multiple entities share the
  // same shader overhead.
  std::shared_ptr<Shader> shader;
};
