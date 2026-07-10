#include "core/Application.hpp"
#include "SDL3/SDL_scancode.h"
#include <chrono>
using namespace std;

Application::Application()
    : window(), renderer(window.getWindowSize()), inputManager(), scene() {}

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

    // TODO: once entities & rendering calculations must be done, add alpha
    // property to timestep.
    while (accumulator >= dt) {
      isRunning = update();

      accumulator -= dt;
    }
    renderer.resize(window.getWindowSize());
    renderer.draw(scene);
    window.swap();

    auto endTime = chrono::high_resolution_clock::now();
    chrono::duration<double> endTimeElapsed = endTime - newTime;
    double endTimeCount = endTimeElapsed.count();
    if (dt >= endTimeCount) {
      SDL_Delay(static_cast<uint32_t>((dt * 1000) - (endTimeCount * 1000)));
    }
  }
}

void Application::loadScene(const Scene &givenScene) { scene = givenScene; }

bool Application::update() {
  inputManager.pollEvent();
  if (inputManager.isQuitRequested()) {
    return false;
  }
  if (inputManager.isMouseClicked()) {
    window.setRelativeMouseMode(true);
  }

  MouseDelta md = inputManager.getMouseDelta();
  scene.getCamera().setDirection(md.dx, md.dy);

  // TODO: Fix hardcoded 5.0f with eventual constant/scalable number that can
  // be used in timestep.
  double cameraVel = 5.0 * dt;
  if (inputManager.isKeyHeld(SDL_SCANCODE_W)) {
    scene.getCamera().moveForward(cameraVel);
  }
  if (inputManager.isKeyHeld(SDL_SCANCODE_S)) {
    scene.getCamera().moveForward(-cameraVel);
  }
  if (inputManager.isKeyHeld(SDL_SCANCODE_D)) {
    scene.getCamera().moveRight(cameraVel);
  }
  if (inputManager.isKeyHeld(SDL_SCANCODE_A)) {
    scene.getCamera().moveRight(-cameraVel);
  }
  if (inputManager.isKeyPressed(SDL_SCANCODE_ESCAPE)) {
    window.setRelativeMouseMode(false);
  }
  return true;
}

Application::~Application() {}
