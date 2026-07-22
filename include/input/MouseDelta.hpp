#pragma once

// struct MouseDelta - Custom representation for data needed to represent
// rotation.
struct MouseDelta {
  // Represents the difference in motion for the x axis.
  int dx;
  // Represents the difference in motion for the y axis.
  int dy;

  // Constructor
  MouseDelta(int dxGiven, int dyGiven);
  // Overload Constructor - Defualt
  MouseDelta();
};
