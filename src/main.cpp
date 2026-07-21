#include "../nedolia/include/Nedolia.hpp"
#include "core/Application.hpp"
#include "interface/Game.hpp"

// This main.cpp file is temporary for BURZA and will be deleted upon 1.0. This
// file only exists for testing purposes.
int main() {
  Application application;
  std::unique_ptr<Game> nedolia = std::make_unique<Nedolia>();
  nedolia->init();
  application.loadScene(nedolia->getScene(0));
  application.run();
}
