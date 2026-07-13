#include "config/Settings.hpp"

// Camera Settings
CameraSettings::CameraSettings(float givenSensitivity, float givenPitchClamp)
    : sensitivity(givenSensitivity), pitchClamp(givenPitchClamp) {}

CameraSettings::CameraSettings() {}

CameraSettings::~CameraSettings() {}
//

// Renderer Settings
RendererSettings::RendererSettings(float givenFOV, float givenLookDistance)
    : fov(givenFOV), lookDistance(givenLookDistance) {}

RendererSettings::RendererSettings() {}

RendererSettings::~RendererSettings() {}
//

// Application Settings
ApplicationSettings::ApplicationSettings(float givenMovementVelocity)
    : movementVelocity(givenMovementVelocity) {}

ApplicationSettings::ApplicationSettings() {}

ApplicationSettings::~ApplicationSettings() {}
//

// Window Settings
WindowSettings::WindowSettings(int givenDefaultWidth, int givenDefaultHeight)
    : defaultWidth(givenDefaultWidth), defaultHeight(givenDefaultHeight) {}

WindowSettings::WindowSettings() {}

WindowSettings::~WindowSettings() {}
//

// Overall Settings, encapsulates all child settings classes.
// NOTE: Eventually create init() func w/ builder pattern, to allow for devs to
// instantiate custom settings.
Settings::Settings()
    : cameraSettings(), rendererSettings(), applicationSettings(),
      windowSettings() {}

const Settings &Settings::getInstance() {
  static Settings instance;
  return instance;
}

const CameraSettings &Settings::getCameraSettings() const {
  return cameraSettings;
}

const RendererSettings &Settings::getRendererSettings() const {
  return rendererSettings;
}

const ApplicationSettings &Settings::getApplicationSettings() const {
  return applicationSettings;
}

const WindowSettings &Settings::getWindowSettings() const {
  return windowSettings;
}
