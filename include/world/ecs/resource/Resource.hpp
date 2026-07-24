#pragma once

// class Resource - Abstract Base Class for concrete Resource classes (i.e.,
// Input, ActiveCamera) that hold singleton data across the registry.
class Resource {
public:
  // Virtual Destructor - Frees Memory within Resource, called to proper
  // subclass.
  virtual ~Resource() = default;
};

// Class TypedResource - Templated, derived concrete class allowing
// for arbitrarily-typed resources to be created !
template <typename T> class TypedResource : public Resource {
public:
  TypedResource(const T &givenValue) : value(givenValue) {}
  ~TypedResource() override = default;

  // Returns stored resource value by const&.
  const T &fetchResource() const { return value; }

  // Returns stored resource value by reference.
  T &fetchResourceMut() { return value; }

  // Sets this objects T value to the given T resource value.
  void setResource(const T &givenValue) { value = givenValue; }

private:
  // Represents the underlying value of our resource.
  T value;
};
