#include "core/ApplicationInit.hpp"
#include <stdexcept>
#include <string>

ApplicationInit::ApplicationInit() { initializeSDL(); }

void ApplicationInit::initializeSDL() {
  if (!SDL_Init(SDL_INIT_VIDEO)) {
    SDL_Log("SDL Failed to Initialize.");
    throw std::runtime_error(std::string("SDL Failed to Initialize."));
  }
}

ApplicationInit::~ApplicationInit() { SDL_Quit(); }
