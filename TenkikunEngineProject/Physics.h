#pragma once

#include "Vector3.h"
#include <vector>

class Physics
{
	public:
		static const float g;	//d—Í‰Á‘¬“x
		static const float k;
		static const float e;	//’e—Í’è”
};

struct SolverBody {
	Vector3 deltaLinearVelocity;
	Vector3 deltaAngularVelocity;
	float inertiaInv = 0;
	float massInv = 0;
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
