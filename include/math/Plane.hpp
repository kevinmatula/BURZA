#include <glm/gtc/matrix_transform.hpp>

struct Plane {
  // Represents the direction of the normal vector on the Plane.
  glm::vec3 normal;
  // Represents the distance between the plane and the origin, along the normal
  // vector.
  float distance;

  // Default Constructor - sets up default plane (floor).
  Plane();
  // Custom overloaded constructor - takes in an arbitrary point and the given
  // normal and constructs a Plane object.
  Plane(const glm::vec3 &givenPoint, const glm::vec3 &givenNormal);
  // Destructor - frees memory within Plane.
  ~Plane();
};
