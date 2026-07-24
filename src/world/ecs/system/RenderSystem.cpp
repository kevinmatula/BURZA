#include "world/ecs/system/RenderSystem.hpp"
#include "config/Settings.hpp"
#include "math/Transform.hpp"
#include "rendering/Mesh.hpp"
#include "world/ecs/component/MeshComponent.hpp"
#include "world/ecs/component/ShaderComponent.hpp"

RenderSystem::RenderSystem()
    : ws(Settings::getReadInstance().getWindowSettings()) {}

void RenderSystem::run(Registry &reg) {
  std::vector<EntityID> renderables =
      reg.fetchEntitiesWith<MeshComponent, ShaderComponent, Transform>();
  const Camera &camera = reg.fetchResource<Camera>();
  draw(reg, renderables, camera);
}

void RenderSystem::draw(Registry &reg, const std::vector<EntityID> &renderables,
                        const Camera &camera) const {
  float aspect = static_cast<float>(ws.currentWidth) / ws.currentHeight;
  Frustum frustum = Frustum::createFrustumFromCamera(camera, aspect);

  const glm::mat4 &view = camera.getView();
  const glm::mat4 &projection = camera.getProjection();

  for (EntityID entity : renderables) {
    const Mesh &mesh = *reg.fetchComponent<MeshComponent>(entity).mesh;
    const Transform &transform = reg.fetchComponent<Transform>(entity);

    if (mesh.getAABB().isOnFrustum(frustum, transform)) {
      const Shader &shader =
          *reg.fetchComponent<ShaderComponent>(entity).shader;
      shader.use();

      shader.applyMatrix(MVP::Model, transform.getModel());
      shader.applyMatrix(MVP::View, view);
      shader.applyMatrix(MVP::Projection, projection);

      mesh.draw();
    }
  }
}
