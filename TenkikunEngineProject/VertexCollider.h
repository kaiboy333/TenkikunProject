#pragma once

#include "Collider.h"
#include <vector>

class VertexCollider : public Collider
{
	public:
		VertexCollider(GameObject* gameobject);
		//�e���_���擾
		virtual std::vector<Vector2> GetVertexes() = 0;

		virtual void Draw() override;

		virtual Rect GetBoundingBox() override;	//�o�E���f�B���O�{�b�N�X��Ԃ�

	protected:
		std::vector<Vector2> GetVertexes(std::vector<Vector2> toVertexVecs);
};

