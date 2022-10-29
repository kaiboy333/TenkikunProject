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
	float inertiaInv;
	float massInv;
};

struct Constraint {
	Vector3 axis;
	float jacDiagInv;
	float rhs;
	float upperLimit;
	float lowerLimit;
	float accumImpulse;
};

struct ContactPoint {
	Vector3 pointA;
	Vector3 pointB;
	Vector3 normal;
	float distance;
	Constraint constraints[3];
};

struct Contact {
	float friction;
	std::vector<ContactPoint> contactPoints;
};
