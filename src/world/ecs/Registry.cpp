#include "world/ecs/Registry.hpp"

Registry::Registry() : allEntities() {}

EntityID Registry::createEntity() {
  EntityID newEntity =
      allEntities.empty() ? EntityID(0) : EntityID(allEntities.back().id + 1);
  allEntities.push_back(newEntity);
  return newEntity;
}

Registry::~Registry() {}
