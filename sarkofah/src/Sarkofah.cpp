#include "../sarkofah/include/Sarkofah.hpp"

Sarkofah::Sarkofah() {}

void Sarkofah::init() {
  std::vector<float> vertexData = {-0.5f, -0.5f, 0.0f, 0.5f, -0.5f,
                                   0.0f,  0.0f,  0.5f, 0.0f};
  std::shared_ptr<Mesh> sharedMesh =
      std::make_shared<Mesh>(vertexData, VertexFormat::Position);
  std::shared_ptr<Shader> sharedShader = std::make_shared<Shader>(
      "assets/shaders/vertex.vert", "assets/shaders/fragment.frag");
  Transform transform(glm::vec3(0.5f),
                      RotationPair(70, glm::vec3(1.0f, 1.0f, 1.0f)),
                      glm::vec3(0.0f));
  std::shared_ptr<Entity> sharedEntity =
      std::make_shared<Entity>(sharedMesh, sharedShader, transform);
  std::vector<std::shared_ptr<Entity>> entities;
  entities.push_back(sharedEntity);

  Camera camera(glm::vec3(0.0f, 1.0f, 6.0f), glm::vec3(0.2f, 0.0f, -1.0f));
  Scene scene(entities, camera);
  scenes.push_back(scene);
}

Sarkofah::~Sarkofah() {}
