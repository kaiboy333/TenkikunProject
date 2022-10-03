#include "Collision.h"

Collision::Collision(Collider* collider)
{
	this->collider = collider;
	this->gameobject = collider->gameobject;
}
