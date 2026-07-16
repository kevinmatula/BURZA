#pragma once

#include "EntityID.hpp"
#include "world/ecs/ComponentContainer.hpp"
#include <cassert>
#include <memory>
#include <typeindex>

// class Registry - Hub for all ECS systems, holds all ComponentContainers and
// deals with lookup logic.
class Registry {
public:
  // Constructor - Sets up Registry
  Registry();
  // Destructor - Frees Memory within Registry
  ~Registry();

  // Creates a new entity by allocating a new EntityID (side effect of
  // increasing counter).
  EntityID createEntity();

  // Adds a new component to our registry. If the component does not already
  // exist, creates new ComponentContainer and adds itself to it.
  template <typename T>
  void addComponent(const EntityID &givenId, const T &givenComponent) {
    // If the ComponentContainer already exists in this registry, add the
    // component to the ComponentContainer.
    if (typeToContainer.count(typeid(T))) {
      TypedComponentContainer<T> *rawTypedContainer = getTypedContainer<T>();
      rawTypedContainer->addComponent(givenId, givenComponent);
    }
    // If the ComponentContainer does not exist in the registry, create the new
    // ComponentContainer and add the component.
    else {
      std::unique_ptr<TypedComponentContainer<T>> newContainer =
          std::make_unique<TypedComponentContainer<T>>();
      newContainer->addComponent(givenId, givenComponent);
      typeToContainer[typeid(T)] = std::move(newContainer);
    }
  }

  // Fetches a givenComponent from our map of different ComponentContainers.
  template <typename T> const T &fetchComponent(const EntityID &givenId) const {
    assert(typeToContainer.count(typeid(T)));
    TypedComponentContainer<T> *rawTypedContainer = getTypedContainer<T>();
    return rawTypedContainer->fetchComponent(givenId);
  }

private:
  // Total counter value corresponds to total Entities in each scene. Starts at
  // 0.
  unsigned int entityCounter;
  // Hashmap that maps type_indexes (defined at runtime since abstract) to
  // pointers of our ComponentContainers.
  std::unordered_map<std::type_index, std::unique_ptr<ComponentContainer>>
      typeToContainer;

  // Retrieves the raw pointer for a TypedComponentContainer<T> via downcasting.
  template <typename T> TypedComponentContainer<T> *getTypedContainer() {
    std::type_index componentIndex = typeid(T);
    ComponentContainer *rawContainer = typeToContainer.at(componentIndex).get();

    TypedComponentContainer<T> *rawTypedContainer =
        dynamic_cast<TypedComponentContainer<T> *>(rawContainer);

    assert(rawTypedContainer != nullptr);
    return rawTypedContainer;
  }

  // Retrieves the raw, const pointer for a TypedComponentContainer<T> via
  // downcasting.
  template <typename T>
  const TypedComponentContainer<T> *getTypedContainer() const {
    std::type_index componentIndex = typeid(T);
    ComponentContainer *rawContainer = typeToContainer.at(componentIndex).get();

    TypedComponentContainer<T> *rawTypedContainer =
        dynamic_cast<TypedComponentContainer<T> *>(rawContainer);

    assert(rawTypedContainer != nullptr);
    return rawTypedContainer;
  }
};
