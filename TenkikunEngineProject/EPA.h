#pragma once
#include <vector>
#include "HitInfo.h"
#include "SupportInfo.h"
#include "GJK.h"

class EPA
{
	public:
		static HitInfo* GetHitInfo(SupportInfo* supportInfo);

	private:
		static Vector2 GetContactPoint(Collider* c1, Collider* c2);	//二つの図形の最短距離から衝突点を求め、Collisionに入れる
		static Vector2 GetContactPoint(VertexCollider* c1, VertexCollider* c2);
		static Vector2 GetContactPoint(CircleCollider* c1, VertexCollider* c2);
		static Vector2 GetContactPoint(CircleCollider* c1, CircleCollider* c2);
};

