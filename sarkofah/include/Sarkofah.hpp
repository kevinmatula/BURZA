#pragma once

#include "interface/Game.hpp"

class Sarkofah : public Game {
public:
  // Default Constructor for Sarkofah - Creates entire game.
  Sarkofah();
  // Destructor for Sarkofah - Frees memory for entire game.
  ~Sarkofah();
  // Initializes all game assets, overrides init() method in Game class.
  void init() override;
};
