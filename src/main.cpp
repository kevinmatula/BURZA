#include "core/Application.hpp"
#include <memory>

int main() {
  // TODO: Rip this out of main.cpp and separate the scene creation into a Game
  // class that is a peer of Application. Once that is done, make sure to figure
  // out how to add initilization of OpenGL and other startup tasks in
  // ApplicationInit so Game can use shaders and mesh and pass them into
  // Application without worrying about initilized OpenGL context and stuff.
  // This is currently ugly for demo and dev purposes but will be altered once
  // engine becomes more game-ready. Tasks for this fix include: Fixing empty
  // constructor for scene, investigating purpose of loadScene, fixing
  // inconsistent screen state during initilization, considering whether or not
  // application needs a scene.
  Application application = Application();

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

  Camera camera(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, -1.0f));
  Scene scene(entities, camera);
  application.loadScene(scene);
  application.run();
}
