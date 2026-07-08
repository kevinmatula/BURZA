#pragma once

#include "world/Scene.hpp"

class Game {
public:
  // Default Constructor - Sets up Game class.
  Game();
  // Virtual Destructor - Frees Memory within Game, called to proper subclass.
  virtual ~Game();

  // Initializes all Game scenes & assets, subclasses must provide init method.
  virtual void init() = 0;
  // Returns const reference to std::vector<Scene>, universal implementation in
  // Game.cpp
  const std::vector<Scene> &getScenes();

protected:
  // Represents all scenes within Game.
  std::vector<Scene> scenes;
};
