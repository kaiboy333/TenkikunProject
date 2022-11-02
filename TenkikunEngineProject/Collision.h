#pragma once
#include "GameObject.h"
#include "Collider.h"
#include "Physics.h"

class Collision
{
	public:
		GameObject* gameobject = nullptr;

		Collider* collider = nullptr;

		Transform* transform = nullptr;

		Contact* contact = nullptr;

		Collision(Collider* collider, Contact* contact);

		bool operator==(const Collision& other) const;
		bool operator<(const Collision& other) const;
};

