#include "core/Application.hpp"
#include "SDL3/SDL_scancode.h"
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
    // TODO: once entities & rendering calculations must be done, add alpha
    // property to timestep.
    while (accumulator >= appSettings.dt) {
      update();
      accumulator -= appSettings.dt;
    }

    renderer.draw(scene);
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

void Application::loadScene(const Scene &givenScene) { scene = givenScene; }

// TODO: These update functions should not be in application, eventually move
// them to scene, so like scene.update(InputManager)
void Application::update() {
  // TODO: Fix hardcoded 5.0f with eventual constant/scalable number that can
  // be used in timestep.
  double cameraVel = appSettings.movementVelocity * appSettings.dt;
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
}

bool Application::pollInput() {
  inputManager.pollEvent();
  if (inputManager.isQuitRequested()) {
    return false;
  }
  if (inputManager.isResized()) {
    renderer.resize(window.getWindowSize());
  }
  if (inputManager.isMouseClicked()) {
    window.setRelativeMouseMode(true);
  }
  if (inputManager.isKeyPressed(SDL_SCANCODE_ESCAPE)) {
    window.setRelativeMouseMode(false);
  }

  MouseDelta md = inputManager.getMouseDelta();
  scene.getCamera().setDirection(md.dx, md.dy);
  return true;
}

Application::~Application() {}
