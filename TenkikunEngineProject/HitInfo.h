#pragma once

#include "Physics.h"
#include "RigidBody.h"

class HitInfo
{
	public:
		int colliderID1;
		int colliderID2;
		Contact* contact = nullptr;

		HitInfo(int colliderID1, int colliderID2, Contact* contact);
};

