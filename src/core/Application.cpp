#include "core/Application.hpp"
#include "config/Settings.hpp"
#include <chrono>
using namespace std;

Application::Application()
    : window(), renderer(window.getWindowSize()), inputManager(), scene(),
      appSettings(Settings::getReadInstance().getApplicationSettings()) {}

void Application::run() {
  bool isRunning = true;
  double accumulator = 0.0;
  auto startTime = chrono::high_resolution_clock::now();
  while (isRunning) {
    auto newTime = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = newTime - startTime;
    double frameTime = elapsed.count();
    // Cap frameTime if outrageous
    if (frameTime > 0.25) {
      frameTime = 0.25;
    }
    startTime = newTime;

    accumulator += frameTime;

    isRunning = pollInput();
    scene.setInput(inputManager.getInputState());
    //  TODO: once entities & rendering calculations done, add alpha to
    //  timestep.
    while (accumulator >= appSettings.dt) {
      scene.fixedUpdate();
      accumulator -= appSettings.dt;
    }

    renderer.clear();
    scene.frameUpdate();
    scene.render();
    window.swap();

    auto endTime = chrono::high_resolution_clock::now();
    chrono::duration<double> endTimeElapsed = endTime - newTime;
    double endTimeCount = endTimeElapsed.count();
    if (appSettings.dt >= endTimeCount) {
      SDL_Delay(static_cast<uint32_t>((appSettings.dt * 1000) -
                                      (endTimeCount * 1000)));
    }
  }
}

void Application::loadScene(Scene givenScene) { scene = std::move(givenScene); }

bool Application::pollInput() {
  inputManager.pollEvent();
  if (inputManager.isQuitRequested()) {
    return false;
  }
  if (inputManager.isResized()) {
    renderer.resize(window.getWindowSize());
    // Call scene.recomputeProjection();
  }
  if (inputManager.isMouseClicked()) {
    window.setRelativeMouseMode(true);
  }
  if (inputManager.isKeyPressed(KeyCode::Escape)) {
    window.setRelativeMouseMode(false);
  }
  return true;
}
