#pragma once

struct InputComponent {
  InputComponent(M)
      // Represent a Mesh. Shared_ptr so we can have multiple entities share the
      // same mesh overhead.
      std::shared_ptr<Mesh> mesh;
};
