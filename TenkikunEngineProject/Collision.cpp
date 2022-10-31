#include "Collision.h"

Collision::Collision(Collider* collider, Contact* contact)
{
	this->collider = collider;
	this->gameobject = collider->gameobject;
	this->transform = collider->transform;
	this->contact = contact;
}
