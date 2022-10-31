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
		static std::vector<Vector2> GetContactPoints(Collider* c1, Collider* c2);	//��̐}�`�̍ŒZ��������Փ˓_�����߂�(c1�̏Փ˓_)

		static std::vector<Vector2> GetContactPoints(VertexCollider* c1, VertexCollider* c2);
		static std::vector<Vector2> GetContactPoints(CircleCollider* c1, VertexCollider* c2);
		static std::vector<Vector2> GetContactPoints(CircleCollider* c1, CircleCollider* c2);
};

