#include "world/ecs/Registry.hpp"

Registry::Registry() : entityCounter(0) {}

EntityID Registry::createEntity() {
  unsigned int oldCounter = entityCounter;
  entityCounter++;
  return EntityID(oldCounter);
}

Registry::~Registry() {}
