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
		static std::vector<Vector2> GetContactPoints(Collider* c1, Collider* c2);	//“ñ‚Â‚Ì}Œ`‚ÌÅ’Z‹——£‚©‚çÕ“Ë“_‚ğ‹‚ß‚é(c1‚ÌÕ“Ë“_)

		static std::vector<Vector2> GetContactPoints(VertexCollider* c1, VertexCollider* c2);
		static std::vector<Vector2> GetContactPoints(CircleCollider* c1, VertexCollider* c2);
		static std::vector<Vector2> GetContactPoints(CircleCollider* c1, CircleCollider* c2);
};

