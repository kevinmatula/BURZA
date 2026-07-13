#include "math/Plane.hpp"
#include "world/Camera.hpp"

struct Frustum {
  // Representation of the different planes which make up a Frustum.
  Plane topFace;
  Plane bottomFace;

  Plane rightFace;
  Plane leftFace;

  Plane farFace;
  Plane nearFace;

  // Constructor & Destructor
  Frustum();
  ~Frustum();

  // Ingests a camera & aspect ratio as arguments and creates a Frustum for
  // culling in our rendering pipeline.
  static Frustum createFrustumFromCamera(const Camera &cam, float aspect);
};
