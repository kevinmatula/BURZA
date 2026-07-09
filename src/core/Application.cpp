#include "core/Application.hpp"
#include "SDL3/SDL_scancode.h"
#include <chrono>
using namespace std;

Application::Application()
    : window(), renderer(window.getWindowSize()), inputManager(), scene() {}

void Application::run() {
  bool isRunning = true;
  while (isRunning) {
    auto start = chrono::high_resolution_clock::now();

    isRunning = update();
    renderer.resize(window.getWindowSize());
    renderer.draw(scene);
    window.swap();

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

  // TODO: Fix hardcoded 0.01f with eventual constant/scalable number that can
  // be used in timestep.
  if (inputManager.isKeyHeld(SDL_SCANCODE_W)) {
    scene.getCamera().moveForward(0.02f);
  }
  if (inputManager.isKeyHeld(SDL_SCANCODE_S)) {
    scene.getCamera().moveForward(-0.02f);
  }
  if (inputManager.isKeyHeld(SDL_SCANCODE_D)) {
    scene.getCamera().moveRight(0.02f);
  }
  if (inputManager.isKeyHeld(SDL_SCANCODE_A)) {
    scene.getCamera().moveRight(-0.02f);
  }
  if (inputManager.isKeyPressed(SDL_SCANCODE_ESCAPE)) {
    window.setRelativeMouseMode(false);
  }
  return true;
}

Application::~Application() {}
