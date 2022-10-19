#pragma once

#include "Vector2.h"
#include "Collider.h"
#include "VertexCollider.h"
#include "CircleCollider.h"
#include "Collision.h"
#include "SupportInfo.h"

class GJK
{
	public:
		static SupportInfo* IsHit(Collider* c1, Collider* c2);

		static Vector2 Support(Collider* c1, Collider* c2, Vector2 v);	//�~�R���t�X�L�[���̃T�|�[�g�ʑ����擾

		static Vector2 Support(Collider* c, Vector2 d);	//�T�|�[�g�ʑ����擾
		static Vector2 Support(VertexCollider* c, Vector2 d);	//�����}�`�̃T�|�[�g�ʑ����擾
		static Vector2 Support(CircleCollider* c, Vector2 d);	//�~�̃T�|�[�g�ʑ����擾

		static float GetShortestDistanceToShape(Vector2 targetPoint, std::vector<Vector2> vertexes, Vector2& crossPoint, int& minSideIndex);

	private:

		static bool IsPointInTriangle(Vector2 point, std::vector<Vector2> vertexes);	//�O�p�`�̒��ɓ_�����邩

		//static void CollisionResponce(ContactPoint* contactPoint);
};

