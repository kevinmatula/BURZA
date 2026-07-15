#include "world/ecs/EntityID.hpp"

EntityID::EntityID(unsigned int givenId) : id(givenId) {}

bool EntityID::operator==(const EntityID &rhs) const { return (id == rhs.id); }

EntityID::~EntityID() {}
