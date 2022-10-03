#pragma once
#include "Collider.h"
#include "Vector2.h"
#include "Constraint.h"

class ContactPoint
{
	public:
		Collider* thisCollider = nullptr;
		Collider* otherCollider = nullptr;

		Vector2 point;
		Vector2 depthPoint;

		std::vector<Constraint> constraints;

		ContactPoint(Collider* thisCollider, Collider* otherCollider, Vector2 point, Vector2 depthPoint);
};

