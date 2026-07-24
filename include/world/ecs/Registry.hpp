#pragma once

#include "EntityID.hpp"
#include "world/ecs/component/ComponentContainer.hpp"
#include "world/ecs/resource/Resource.hpp"
#include <cassert>
#include <memory>
#include <typeindex>

// class Registry - Hub for all ECS systems, holds all ComponentContainers and
// deals with lookup logic.
// TODO: Make Component Functions use similar "Mut" keyword on mutable getters.
class Registry {
public:
  // Constructor - Sets up Registry
  Registry();

  // Creates a new entity by allocating a new EntityID (side effect of
  // increasing counter).
  EntityID createEntity();

  // Adds a new component to our registry. If the component does not already
  // exist, creates new ComponentContainer and adds itself to it.
  template <typename T>
  void addComponent(const EntityID &givenId, const T &givenValue) {
    // If the ComponentContainer already exists in this registry, add the
    // component to the ComponentContainer.
    if (typeToContainer.count(typeid(T))) {
      TypedComponentContainer<T> *rawTypedContainer = getTypedContainer<T>();
      rawTypedContainer->addComponent(givenId, givenValue);
    }
    // If the ComponentContainer does not exist in the registry, create the new
    // ComponentContainer and add the component.
    else {
      std::unique_ptr<TypedComponentContainer<T>> newContainer =
          std::make_unique<TypedComponentContainer<T>>();
      newContainer->addComponent(givenId, givenValue);
      typeToContainer[typeid(T)] = std::move(newContainer);
    }
  }

  // Fetches a const Component from our map of different ComponentContainers.
  template <typename T> const T &fetchComponent(const EntityID &givenId) const {
    assert(typeToContainer.count(typeid(T)));
    const TypedComponentContainer<T> *rawTypedContainer =
        getTypedContainer<T>();
    return rawTypedContainer->fetchComponent(givenId);
  }

  // Fetches a non-const Component from our map of different
  // ComponentContainers.
  template <typename T> T &fetchComponent(const EntityID &givenId) {
    assert(typeToContainer.count(typeid(T)));
    TypedComponentContainer<T> *rawTypedContainer = getTypedContainer<T>();
    return rawTypedContainer->fetchComponent(givenId);
  }

  template <typename T> const T &fetchSingleComponent() const {
    assert(typeToContainer.count(typeid(T)));
    const TypedComponentContainer<T> *rawTypedContainer =
        getTypedContainer<T>();
    return rawTypedContainer->fetchSingleComponent();
  }

  template <typename T> T &fetchSingleComponent() {
    assert(typeToContainer.count(typeid(T)));
    TypedComponentContainer<T> *rawTypedContainer = getTypedContainer<T>();
    return rawTypedContainer->fetchSingleComponent();
  }

  // Fetches all EntityIDs that are tied to the given components.
  // Uses Variadic Template. Users are meant to pass in an arbitrary amount of
  // component types.
  template <typename... Args> std::vector<EntityID> fetchEntitiesWith() const {
    std::vector<EntityID> entities = allEntities;
    (filterByComponent<Args>(entities), ...);
    return entities;
  }

  // Sets a given EntityID of Component type T to the given T value.
  template <typename T>
  void setComponent(const EntityID &givenId, const T &givenValue) {
    assert(typeToContainer.count(typeid(T)));
    TypedComponentContainer<T> *rawTypedContainer = getTypedContainer<T>();
    rawTypedContainer->setComponent(givenId, givenValue);
  }

  // Retrieves a const& of resource by type.
  template <typename T> const T &fetchResource() const {
    assert(typeToResource.count(typeid(T)));
    const TypedResource<T> *rawTypedResource = getTypedResource<T>();
    return rawTypedResource->fetchResource();
  }

  // Retrieves a reference of resource by type.
  template <typename T> T &fetchResourceMut() {
    assert(typeToResource.count(typeid(T)));
    TypedResource<T> *rawTypedResource = getTypedResourceMut<T>();
    return rawTypedResource->fetchResourceMut();
  }

  // Adds the given resource to our Registry.
  template <typename T> void addResource(const T &givenResource) {
    // There should only be unique resource types.
    assert(!typeToResource.count(typeid(T)));

    std::unique_ptr<TypedResource<T>> newResource =
        std::make_unique<TypedResource<T>>(givenResource);

    typeToResource[typeid(T)] = std::move(newResource);
  }

  // Sets the entire resource variable to the given resource variable. This
  // function is specifically for re-assignment.
  template <typename T> void setResource(const T &givenResource) {
    assert(typeToResource.count(typeid(T)));
    TypedResource<T> *rawTypedResource = getTypedResourceMut<T>();
    rawTypedResource->setResource(givenResource);
  }

private:
  // Vector corresponding to total Entities in each scene. EntityID starts at
  // 0.
  std::vector<EntityID> allEntities;
  // Hashmap that maps type_indexes (defined at runtime since abstract) to
  // pointers of our ComponentContainers.
  std::unordered_map<std::type_index, std::unique_ptr<ComponentContainer>>
      typeToContainer;
  // Hashmap that maps type_indexes (defined at runtime since abstract) to
  // pointers of our Resources
  std::unordered_map<std::type_index, std::unique_ptr<Resource>> typeToResource;

  // Retrieves the raw pointer for a TypedComponentContainer<T> via
  // downcasting.
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
    const ComponentContainer *rawContainer =
        typeToContainer.at(componentIndex).get();

    const TypedComponentContainer<T> *rawTypedContainer =
        dynamic_cast<const TypedComponentContainer<T> *>(rawContainer);

    assert(rawTypedContainer != nullptr);
    return rawTypedContainer;
  }

  // Sets the given argument to a subset of givenEntities representing
  // the list of all givenEntities that have components of type T.
  template <typename T>
  void filterByComponent(std::vector<EntityID> &givenEntities) const {
    std::vector<EntityID> newEntities;
    const TypedComponentContainer<T> *rawTypedContainer =
        getTypedContainer<T>();

    for (EntityID entity : givenEntities) {
      if (rawTypedContainer->hasComponent(entity)) {
        newEntities.push_back(entity);
      }
    }

    givenEntities = newEntities;
  }

  // Retrieves the raw pointer for a TypedResource<T> via
  // downcasting.
  template <typename T> TypedResource<T> *getTypedResourceMut() {
    std::type_index resourceIndex = typeid(T);
    Resource *rawResource = typeToResource.at(resourceIndex).get();

    TypedResource<T> *rawTypedResource =
        dynamic_cast<TypedResource<T> *>(rawResource);

    assert(rawTypedResource != nullptr);
    return rawTypedResource;
  }

  // Retrieves the const, raw pointer for a TypedResource<T> via
  // downcasting.
  template <typename T> const TypedResource<T> *getTypedResource() const {
    std::type_index resourceIndex = typeid(T);
    const Resource *rawResource = typeToResource.at(resourceIndex).get();

    const TypedResource<T> *rawTypedResource =
        dynamic_cast<const TypedResource<T> *>(rawResource);

    assert(rawTypedResource != nullptr);
    return rawTypedResource;
  }
};
