#pragma once

#include <SDL3/SDL.h>

// Custom representation for data needed to represent rotation.
struct MouseDelta {
  // Represents the difference in motion for the x axis.
  int dx;
  // Represents the difference in motion for the y axis.
  int dy;

  // Constructor
  MouseDelta(int dxGiven, int dyGiven) : dx(dxGiven), dy(dyGiven) {}
  // Overload Constructor - Defualt
  MouseDelta() : dx(0), dy(0) {}
  // Destructor
  ~MouseDelta() {}
};

class InputManager {
public:
  // Constructor - Sets up InputManager
  InputManager();
  // Destructor - Frees Memory within InputManager
  ~InputManager();

  // Called by Application to check for Polled Event
  void pollEvent();
  // Used to update alter view matrix.
  bool isKeyHeld(SDL_Scancode scancode);
  // Getter - Returns the boolean status of quitRequested
  bool isQuitRequested();
  // Getter - Returns the MouseDelta accumulated after each PollEvent.
  MouseDelta getMouseDelta();

private:
  // Represents whether or not a user wants to quit
  bool quitRequested;
  // Represents the total difference of the mouses coordinates, for x & y.
  MouseDelta md;
};
