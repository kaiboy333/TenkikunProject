#pragma once

#include "Vector2.h"
#include "Collider.h"
#include "VertexCollider.h"
#include "CircleCollider.h"

class GJK
{
	public:
		static bool IsHit(Collider* c1, Collider* c2);

		static Vector2 Support(Collider* c1, Collider* c2, Vector2 d);	//�~�R���t�X�L�[���̃T�|�[�g�ʑ����擾

	private:
		static Vector2 Support(Collider* c, Vector2 d);	//�T�|�[�g�ʑ����擾

		static Vector2 Support(VertexCollider* c, Vector2 d);	//�����}�`�̃T�|�[�g�ʑ����擾
		static Vector2 Support(CircleCollider* c, Vector2 d);	//�~�̃T�|�[�g�ʑ����擾

		static bool IsPointInTriangle(Vector2 point, std::vector<Vector2> vertexes);	//�O�p�`�̒��ɓ_�����邩
};

