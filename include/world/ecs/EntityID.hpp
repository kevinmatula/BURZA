#pragma once

// class EntityID - Represents the ID number for any given entity.
class EntityID {
public:
  // Constructor & Destructor
  EntityID(unsigned int givenId);
  ~EntityID();

  // Operator overload for == so we can check equivalency.
  bool operator==(const EntityID &rhs) const;

  // Getter - Gets the EntityID's ID.
  unsigned int getID() const;

private:
  // ID number for the entity. Default is 0. Not supposed to be changed.
  unsigned int id = 0;
};
