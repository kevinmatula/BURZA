#include "interface/Game.hpp"

Game::Game() {}

Scene Game::getScene(size_t givenIndex) {
  assert(scenes.size() > givenIndex);
  return std::move(scenes[givenIndex]);
}

Game::~Game() {}
