#pragma once

#include "world/Scene.hpp"

// class Game - Parent class/Main interface for game child classes to inherit.
class Game {
public:
  // Default Constructor.
  Game();
  // Virtual Destructor - Frees Memory within Game, called to proper subclass.
  virtual ~Game() = default;

  // Initializes all Game scenes & assets, subclasses must provide init method.
  virtual void init() = 0;
  // Returns write-access Scene, universal implementation in Game.cpp
  Scene getScene(size_t givenIndex);

protected:
  // Represents all scenes within Game.
  std::vector<Scene> scenes;
};
