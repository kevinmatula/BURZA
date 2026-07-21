#pragma once

#include "interface/Game.hpp"

// class Nedolia - Inherits from public Game parent class, meant to create game
// assets and logic.
class Nedolia : public Game {
public:
  // Default Constructor for Nedolia - Creates entire game.
  Nedolia();
  // Initializes all game assets, overrides init() method in Game class.
  void init() override;
};
