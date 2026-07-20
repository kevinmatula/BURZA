#include "world/ecs/EntityID.hpp"

EntityID::EntityID(unsigned int givenId) : id(givenId) {}

unsigned int EntityID::getID() const { return id; }

bool EntityID::operator==(const EntityID &rhs) const { return (id == rhs.id); }

EntityID::~EntityID() {}
