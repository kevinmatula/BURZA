#include "world/ecs/system/RenderSystem.hpp"
#include "config/Settings.hpp"
#include "math/Transform.hpp"
#include "rendering/Mesh.hpp"
#include "world/ecs/component/MeshComponent.hpp"
#include "world/ecs/component/ShaderComponent.hpp"

RenderSystem::RenderSystem()
    : ws(Settings::getReadInstance().getWindowSettings()),
      rs(Settings::getReadInstance().getRendererSettings()) {}

void RenderSystem::update(Registry &reg) {
  std::vector<EntityID> renderables =
      reg.fetchEntitiesWith<MeshComponent, ShaderComponent, Transform>();
  const Camera &camera = reg.fetchSingleComponent<Camera>();
  draw(reg, renderables, camera);
}

void RenderSystem::draw(Registry &reg, const std::vector<EntityID> &renderables,
                        const Camera &camera) const {
  float aspect = static_cast<float>(ws.currentWidth) / ws.currentHeight;
  Frustum frustum = Frustum::createFrustumFromCamera(camera, aspect);

  glm::mat4 view = camera.getView();
  glm::mat4 projection = calculateProjection();

  for (EntityID entity : renderables) {
    const Mesh &mesh = *reg.fetchComponent<MeshComponent>(entity).mesh;
    Transform &transform = reg.fetchComponent<Transform>(entity);

    if (mesh.getAABB().isOnFrustum(frustum, transform)) {
      const Shader &shader =
          *reg.fetchComponent<ShaderComponent>(entity).shader;
      shader.use();

      shader.applyMatrix(MVP::Model, transform.computeModel());
      shader.applyMatrix(MVP::View, view);
      shader.applyMatrix(MVP::Projection, projection);

      mesh.draw();
    }
  }
}

// TODO: Remove this method and dynamically reload projection matrix in camera
// class.
glm::mat4 RenderSystem::calculateProjection() const {
  glm::mat4 projection = glm::perspective(
      glm::radians(rs.fov), float(ws.currentWidth) / float(ws.currentHeight),
      rs.startingLookDistance, rs.maxLookDistance);
  return projection;
}
