#pragma once

#include "Physics.h"
#include "RigidBody.h"

class HitInfo
{
	public:
		int colliderID1;
		int colliderID2;
		Contact contact;

		HitInfo(int colliderID1, int colliderID2, Contact contact);
};

