#pragma once

#include "math/Hash.hpp"
#include "world/ecs/EntityID.hpp"
#include <cassert>
#include <unordered_map>
#include <vector>

// Class ComponentContainer - Represents an abstract base class for all
// ComponentContainer in our ECS system.
class ComponentContainer {
public:
  // Virtual Destructor - Frees Memory within ComponentContainer, called to
  // proper subclass.
  virtual ~ComponentContainer() = default;
};

// Class TypedComponentContainer - Templated, derived abstract class allowing
// for arbitrarily-typed containers to be created !
template <typename T>
class TypedComponentContainer : public ComponentContainer {
public:
  TypedComponentContainer() : typedComponentStore() {}
  ~TypedComponentContainer() override = default;

  // This function fetches a given entities component according to its Id.
  const T &fetchComponent(const EntityID &givenId) const {
    assert(typeToStoreIndex.count(givenId));
    return typedComponentStore.at(typeToStoreIndex.at(givenId));
  }

  // This function sets the given entity to hold the given value T.
  void setComponent(const EntityID &givenId, const T &givenValue) {
    assert(typeToStoreIndex.count(givenId));
    typedComponentStore.at(typeToStoreIndex.at(givenId)) = givenValue;
  }

  // This function ingests an ID and T value and adds a component to our
  // container.
  void addComponent(const EntityID &givenId, const T &givenValue) {
    assert(!typeToStoreIndex.count(givenId));
    typedComponentStore.push_back(givenValue);
    int valueAtIndex = typedComponentStore.size() - 1;
    typeToStoreIndex.emplace(givenId, valueAtIndex);
  }

private:
  std::vector<T> typedComponentStore;
  std::unordered_map<EntityID, int, EntityIDHash> typeToStoreIndex;
};
