#include "../nedolia/include/Nedolia.hpp"
#include "rendering/Mesh.hpp"
#include "rendering/MeshLoader.hpp"
#include "rendering/Shader.hpp"
#include "world/ecs/component/MeshComponent.hpp"
#include "world/ecs/component/ShaderComponent.hpp"
#include "world/ecs/system/RenderSystem.hpp"
#include <memory>

Nedolia::Nedolia() {}

void Nedolia::init() {
  MeshData vertexData =
      MeshLoader::load("assets/models/cube.obj", VertexFormat::Position);
  std::shared_ptr<Mesh> sharedMesh =
      std::make_shared<Mesh>(vertexData, VertexFormat::Position);
  MeshComponent meshComp(sharedMesh);

  std::shared_ptr<Shader> sharedShader = std::make_shared<Shader>(
      "assets/shaders/vertex.vert", "assets/shaders/fragment.frag");
  ShaderComponent shaderComp(sharedShader);

  Transform transform(glm::vec3(0.5f),
                      RotationPair(0, glm::vec3(1.0f, 1.0f, 1.0f)),
                      glm::vec3(0.0f));

  Camera camera(glm::vec3(0.0f, 0.0f, 6.0f), glm::vec3(0.0f, 0.0f, -1.0f));

  Registry reg;
  EntityID camEntity = reg.createEntity();
  EntityID e1 = reg.createEntity();

  reg.addComponent(camEntity, camera);

  reg.addComponent(e1, meshComp);
  reg.addComponent(e1, shaderComp);
  reg.addComponent(e1, transform);

  std::vector<std::unique_ptr<System>> systems;
  systems.push_back(std::make_unique<RenderSystem>());
  scenes.push_back(Scene(std::move(reg), std::move(systems)));
}
