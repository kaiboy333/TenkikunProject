#pragma once
#include "GameObject.h"
#include "Collider.h"

class Collision
{
	public:
		GameObject* gameobject = nullptr;

		Collider* collider = nullptr;

		Vector2 contactPoint;

		Collision(Collider* collider);
};

