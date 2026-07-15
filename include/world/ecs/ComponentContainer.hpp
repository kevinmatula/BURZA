#pragma once

#include "math/Hash.hpp"
#include "world/ecs/EntityID.hpp"
#include <unordered_map>
#include <vector>

// Class ComponentContainer - Represents an abstract base class for all
// ComponentContainer in our ECS system.
class ComponentContainer {
public:
  // Virtual Destructor - Frees Memory within ComponentContainer, called to
  // proper subclass.
  virtual ~ComponentContainer();
};

// Class TypedComponentContainer - Templated, derived abstract class allowing
// for arbitrarily-typed containers to be created !
template <typename T>
class TypedComponentContainer : public ComponentContainer {
public:
  TypedComponentContainer() : typedComponentStore() {}

private:
  std::vector<T> typedComponentStore;
  std::unordered_map<EntityID, int, EntityIDHash> typeToStoreIndex;
};
