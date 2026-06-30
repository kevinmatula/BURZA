#include "core/Application.hpp"
#include <chrono>
using namespace std;

Application::Application() : window(), renderer(), inputManager() {}

void Application::run() {
  bool isRunning = true;
  while (isRunning) {
    auto start = chrono::high_resolution_clock::now();

    inputManager.pollEvent();
    if (inputManager.isQuitRequested()) {
      isRunning = false;
    }

    renderer.draw(window);

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = end - start;
    double frameTime = elapsed.count();
    if (frameTime > 0.25) {
      frameTime = 0.25;
    }
    if (timePerFrame >= frameTime) {
      SDL_Delay(
          static_cast<uint32_t>((timePerFrame * 1000) - (frameTime * 1000)));
    }
  }
}

Application::~Application() {}
