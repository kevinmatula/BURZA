#pragma once

#include "math/MVP.hpp"
#include <SDL3/SDL.h>
#include <filesystem>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <unordered_map>

class Shader {
public:
  // Constructor - Sets up Vertex Shader & Fragment Shader
  // Takes in two file paths which represent valid shader files in .glsl
  Shader(const std::filesystem::path &vertexShaderSource,
         const std::filesystem::path &fragmentShaderSource);
  // Destructor - Frees Memory within Shader
  ~Shader();

  // Calls glUseProgram on this local shaderProgram
  void use();
  // Ingests a mat4 in MVP matrix & a corresponding MVP type, and transforms
  // coordinates in vertexShader. Must be using this shader program.
  void applyMatrix(MVP matrixType, glm::mat4 matrix);

  // Protect against double-free
  Shader(const Shader &) = delete;
  Shader &operator=(const Shader &) = delete;
  Shader(Shader &&) = delete;
  Shader &operator=(Shader &&) = delete;

private:
  // Consumes a file path and returns the contents of the file in a string.
  std::string readFile(const std::filesystem::path &shaderSource);
  // Consumes a given shader and checks compilation status to verify success.
  // Throws error if compilation unsuccessful.
  void checkShaderCompilation(unsigned int givenShader);
  // Consumes a given program and checks compilation status to verify success.
  // Throws error if compilation unsuccessful.
  void checkProgramCompilation(unsigned int givenProgram);
  // Consumes a file path and initializes an arbitrary shader with OpenGL
  // (vertex or fragment)
  unsigned int initializeShader(const std::filesystem::path &shaderSource);
  // Consumes two shaders (represented by unsigned integers). Attaches, links,
  // deletes shaders.
  unsigned int buildShaderProgram(unsigned int vertexShader,
                                  unsigned int fragmentShader);

  // OpenGL Shader Program Object. Represents final linked version of multiple
  // shaders combined.
  unsigned int shaderProgram;
  // Map to store the different uniform locations for model, view, and
  // projection matrices.
  std::unordered_map<MVP, int> mvpMatrices;
};
