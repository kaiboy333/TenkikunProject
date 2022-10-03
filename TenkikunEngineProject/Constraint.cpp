#include "Constraint.h"

Constraint::Constraint(float jacDiagInv, float rhs, float lowerLimit, float upperLimit, Vector3 axis)
{
	this->jacDiagInv = jacDiagInv;
	this->rhs = rhs;
	this->lowerLimit = lowerLimit;
	this->upperLimit = upperLimit;
	this->axis = axis;
}
