#pragma once

#include "Vector3.h"
#include <vector>

class Physics
{
	public:
		static const float g;	//èdóÕâ¡ë¨ìx
};

struct Constraint {
	Vector3 axis;
	float jacDiagInv = 0;
	float rhs = 0;
	float upperLimit = 0;
	float lowerLimit = 0;
	float accumImpulse = 0;
};

struct ContactPoint {
	Vector3 pointA;
	Vector3 pointB;
	Vector3 normal;
	float distance = 0;
	Constraint constraints[3];
};

struct Contact {
	float friction = 0;
	std::vector<ContactPoint*> contactPoints;
};

struct SupportInfo {
	std::vector<Vector2> supports;
	int colliderID1;
	int colliderID2;
};

struct HitInfo {
	int colliderID1;
	int colliderID2;
	Contact* contact = nullptr;
};

struct SolverBody {
	Vector3 deltaLinearVelocity;
	Vector3 deltaAngularVelocity;
	float inertiaInv = 0;
	float massInv = 0;
};