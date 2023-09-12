#include "ECS.h"

void Entity::addGroup(GroupID mGroup)
{
	groupBitset[mGroup] = true;
	manager.AddToGroup(this, mGroup);
}