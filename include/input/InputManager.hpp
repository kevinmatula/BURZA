#pragma once

#include <SDL3/SDL.h>
#include <unordered_set>

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
};

// class InputManager - Deals with all keyboard, mouse, and overall hardware
// input.
class InputManager {
public:
  // Constructor - Sets up InputManager
  InputManager();

  // Called by Application to check for Polled Event
  void pollEvent();
  // Checks if a key is being held on the keyboard, returns a bool.
  bool isKeyHeld(SDL_Scancode scancode);
  // Checks if a key has been pressed on the keyboard, returns a bool. This
  // function is specific to "1 and done" keypresses like escape.
  bool isKeyPressed(SDL_Scancode scancode);
  // Getter - Returns the boolean status of quitRequested
  bool isQuitRequested();
  // Getter - Returns the boolean status of mouseClicked
  bool isMouseClicked();
  // Getter - Returns the boolean status of resized;
  bool isResized();
  // Getter - Returns the MouseDelta accumulated after each PollEvent.
  MouseDelta getMouseDelta();

private:
  // Represents whether or not a user wants to quit
  bool quitRequested;
  // Represents if a mouse button has been pressed.
  bool mouseClicked;
  // Represents if a user attempted to resize the window.
  bool resized;
  // Represents the total difference of the mouses coordinates, for x & y.
  MouseDelta md;
  // Represents an unorded set of keys that were pressed during event polling.
  std::unordered_set<SDL_Scancode> keysPressed;
};
