#pragma once

#include "Collider.h"
#include "CircleCollider.h"
#include "BoxCollider.h"

class HitChecker
{
	public:
		static bool IsHit(Collider* c1, Collider* c2);

	private:
		static bool IsHitCC(CircleCollider* c1, CircleCollider* c2);

		static bool IsHitBB(BoxCollider* c1, BoxCollider* c2);

		static bool IsHitCB(CircleCollider* c1, BoxCollider* c2);
};

