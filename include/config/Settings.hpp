#pragma once

struct CameraSettings {
  // Represents the sensitivity of moving the mouse.
  float sensitivity = 0.05;
  // Represents the absolute lowest and highest the camera can look. Must be
  // < 90.0 in order to avoid matrices error.
  const float pitchClamp = 89.0;
  // Represents the speed of movement in the camera.
  const float movementSpeed = 5.0;

  CameraSettings(float givenSensitivity, float pitchClamp,
                 float givenMovementSpeed);
  CameraSettings();
  ~CameraSettings();
};

struct RendererSettings {
  // Represents the breadth of view from the camera (in degrees).
  float fov = 45.0;
  // Represents the maximum distance the camera can look.
  const float maxLookDistance = 100.0;
  // Represents the starting look distance from the camera.
  const float startingLookDistance = 0.1;

  RendererSettings(float givenFOV, float givenStartingLookDistance,
                   float givenMaxLookDistance);
  RendererSettings();
  ~RendererSettings();
};

struct ApplicationSettings {
  // Represents time passed between each frame (60 FPS).
  const double dt = 1.0 / 60.0;

  ApplicationSettings();
  ~ApplicationSettings();
};

struct WindowSettings {
  // Represents the default width and height of the game respectively.
  const int defaultWidth = 1500;
  const int defaultHeight = 1000;

  // Represents the current width and height of the game respectively.
  int currentWidth = defaultWidth;
  int currentHeight = defaultHeight;

  WindowSettings(int givenDefaultWidth, int givenDefaultHeight);
  WindowSettings();
  ~WindowSettings();
};

// class Settings - Meyers' Singleton design pattern - okay for config & will be
// enforced const across engine, only mutable in one menu in game.
class Settings {
public:
  // Delete copy constructor and assignment operators to prevent duplicates
  Settings(const Settings &) = delete;
  Settings &operator=(const Settings &) = delete;
  Settings(Settings &&) = delete;
  Settings &operator=(Settings &&) = delete;

  // Public static method to get the unique instance
  static const Settings &getReadInstance();

  // Getter for all settings. Setters for specific settings within each
  // individual struct.
  const CameraSettings &getCameraSettings() const;
  const RendererSettings &getRendererSettings() const;
  const ApplicationSettings &getApplicationSettings() const;
  const WindowSettings &getWindowSettings() const;

  // Renderer needs to update currentWidth & currentHeight on window resize.
  friend class Renderer;

private:
  // Constructor - Private for Singleton Pattern.
  Settings();
  // Destructor - Private for Singleton Pattern.
  ~Settings() = default;

  // Internal Instance represents the sole static instance of the settings
  // class. Read-and-write getters alike can call this and return the reference
  // of their choosing.
  static Settings &internalInstance();
  // Mutable Instance only offered to friends (renderer & eventual settings
  // page).
  static Settings &getMutableInstance();

  // Sets the current size of the width and height of the window.
  void setWindowCurrentSize(int width, int height);

  // Specific Groups of Settings.
  CameraSettings cameraSettings;
  RendererSettings rendererSettings;
  ApplicationSettings applicationSettings;
  WindowSettings windowSettings;
};
