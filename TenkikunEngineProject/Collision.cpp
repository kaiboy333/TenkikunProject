#include "Collision.h"

Collision::Collision(Collider* collider, Contact* contact)
{
	this->collider = collider;
	this->gameobject = collider->gameobject;
	this->transform = collider->transform;
	this->contact = contact;
}

bool Collision::operator==(const Collision& other) const
{
	return this->collider == other.collider;
}

bool Collision::operator!=(const Collision& other) const
{
	return !(*this == other);
}

bool Collision::operator<(const Collision& other) const
{
	return this->collider < other.collider;
}

bool Collision::operator>(const Collision& other) const
{
	return !(*this < other);
}
