#include "../sarkofah/include/Sarkofah.hpp"
#include "core/Application.hpp"
#include "interface/Game.hpp"

// This main.cpp file is temporary for BURZA and will be deleted upon 1.0. This
// file only exists for testing purposes.
int main() {
  Application application;
  std::unique_ptr<Game> sarkofah = std::make_unique<Sarkofah>();
  sarkofah->init();
  application.loadScene(sarkofah->getScenes().at(0));
  application.run();
}
