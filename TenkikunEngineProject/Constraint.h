#pragma once
#include "Vector3.h"
class Constraint
{
	public:
		float jacDiagInv;
		float rhs;
		float lowerLimit;
		float upperLimit;
		Vector3 axis;

		Constraint(float jacDiagInv, float rhs, float lowerLimit, float upperLimit, Vector3 axis);
};

