#pragma once
#include "Collider.h"
class HitInfo
{
	public:
		Collider* c1 = nullptr;
		Collider* c2 = nullptr;
		Vector3 n;
		float sink;
		Vector3 contactPoint;

		HitInfo(Collider* c1, Collider* c2, Vector3 n, float sink, Vector3 contactPoint);
};

