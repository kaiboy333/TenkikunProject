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
		static Vector2 GetContactPoint(Collider* c1, Collider* c2);	//��̐}�`�̍ŒZ��������Փ˓_�����߁ACollision�ɓ����
		static Vector2 GetContactPoint(VertexCollider* c1, VertexCollider* c2);
		static Vector2 GetContactPoint(CircleCollider* c1, VertexCollider* c2);
		static Vector2 GetContactPoint(CircleCollider* c1, CircleCollider* c2);
};

