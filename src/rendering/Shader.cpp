#include "rendering/Shader.hpp"
#include <fstream>
#include <glad/glad.h>

Shader::Shader(const std::filesystem::path &vertexShaderSource,
               const std::filesystem::path &fragmentShaderSource) {
  unsigned int vertexShader = initializeShader(vertexShaderSource);
  unsigned int fragmentShader = initializeShader(fragmentShaderSource);
  shaderProgram = buildShaderProgram(vertexShader, fragmentShader);
  mvpMatrices[MVP::Model] = glGetUniformLocation(shaderProgram, "model");
  mvpMatrices[MVP::View] = glGetUniformLocation(shaderProgram, "view");
  mvpMatrices[MVP::Projection] =
      glGetUniformLocation(shaderProgram, "projection");
}

unsigned int
Shader::initializeShader(const std::filesystem::path &givenShaderFile) {
  unsigned int shader;

  std::string ext = givenShaderFile.extension().string();
  if (ext == ".vert") {
    shader = glCreateShader(GL_VERTEX_SHADER);
  } else if (ext == ".frag") {
    shader = glCreateShader(GL_FRAGMENT_SHADER);
  } else {
    SDL_Log("Shader Failed to Initialize. Incorrect File Extension Provided.");
    throw std::runtime_error(std::string(
        "Shader Failed to Initialize. Incorrect File Extension Provided."));
  }

  std::string shaderSourceStr = readFile(givenShaderFile);
  const char *shaderSourceChar = shaderSourceStr.c_str();

  glShaderSource(shader, 1, &shaderSourceChar, NULL);
  glCompileShader(shader);

  checkShaderCompilation(shader);
  return shader;
}

unsigned int Shader::buildShaderProgram(unsigned int vertexShader,
                                        unsigned int fragmentShader) {
  unsigned int program;
  program = glCreateProgram();

  glAttachShader(program, vertexShader);
  glAttachShader(program, fragmentShader);

  glLinkProgram(program);
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);

  checkProgramCompilation(program);
  return program;
}

void Shader::checkShaderCompilation(unsigned int givenShader) {
  int success;
  char infoLog[512];
  glGetShaderiv(givenShader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(givenShader, 512, NULL, infoLog);
    std::string errorMessage =
        "ERROR::SHADER::COMPILATION_FAILED: " + std::string(infoLog);
    throw std::runtime_error(std::string(errorMessage));
  }
}

void Shader::checkProgramCompilation(unsigned int givenProgram) {
  int success;
  char infoLog[512];
  glGetProgramiv(givenProgram, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(givenProgram, 512, NULL, infoLog);
    std::string errorMessage =
        "ERROR::SHADER::PROGRAM::COMPILATION_FAILED: " + std::string(infoLog);
    throw std::runtime_error(std::string(errorMessage));
  }
}

std::string Shader::readFile(const std::filesystem::path &givenShaderFile) {
  std::string fileContent;
  std::ifstream file(givenShaderFile);

  if (!file.is_open()) {
    throw std::runtime_error(std::string("Shader File Failed to Open."));
  }

  std::string line;
  while (std::getline(file, line)) {
    fileContent += line;
    fileContent += "\n";
  }
  return fileContent;
}

void Shader::use() { glUseProgram(shaderProgram); }

void Shader::applyMatrix(glm::mat4 matrix, MVP matrixName) {
  // DEV ONLY - Check that program is being used before assigning uniform.
  int currentProgram = 0;
  glGetIntegerv(GL_CURRENT_PROGRAM, &currentProgram);
  assert(shaderProgram == currentProgram);
  //

  glUniformMatrix4fv(mvpMatrices[matrixName], 1, GL_FALSE,
                     glm::value_ptr(matrix));
}

Shader::~Shader() { glDeleteProgram(shaderProgram); }
