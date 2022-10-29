#pragma once

#include "Collider.h"
#include "Physics.h"
#include "RigidBody.h"

class HitInfo
{
	public:
		Collider* c1 = nullptr;
		Collider* c2 = nullptr;
		Contact contact;

		HitInfo(Collider* c1, Collider* c2, Contact contact);
};

