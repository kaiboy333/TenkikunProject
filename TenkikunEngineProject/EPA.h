#pragma once
#include <vector>
#include "HitInfo.h"
#include "SupportInfo.h"
#include "GJK.h"

class EPA
{
	public:
		static HitInfo* GetHitInfo(std::vector<Collider*> colliders, SupportInfo* supportInfo);

	private:
		static Vector2 GetContactPoint(Collider* c1, Collider* c2);	//“ñ‚Â‚Ì}Œ`‚ÌÅ’Z‹——£‚©‚çÕ“Ë“_‚ğ‹‚ßACollision‚É“ü‚ê‚é
		static Vector2 GetContactPoint(VertexCollider* c1, VertexCollider* c2);
		static Vector2 GetContactPoint(CircleCollider* c1, VertexCollider* c2);
		static Vector2 GetContactPoint(CircleCollider* c1, CircleCollider* c2);
};

