#pragma once

#include "interface/Game.hpp"

class Nedolia : public Game {
public:
  // Default Constructor for Nedolia - Creates entire game.
  Nedolia();
  // Destructor for Nedolia - Frees memory for entire game.
  ~Nedolia();
  // Initializes all game assets, overrides init() method in Game class.
  void init() override;
};
