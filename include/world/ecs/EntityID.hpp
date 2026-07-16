#pragma once

// struct EntityID - Represents the ID number for any given entity.
struct EntityID {
  // Constructor & Destructor
  EntityID(unsigned int givenId);
  ~EntityID();

  // Operator overload for == so we can check equivalency.
  bool operator==(const EntityID &rhs) const;

  // unchangeable id number for the entity.
  const unsigned int id;
};
