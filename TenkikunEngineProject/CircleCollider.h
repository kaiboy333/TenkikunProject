#pragma once

#include "Collider.h"
#include "ImageRenderer.h"
#include <cmath>

class CircleCollider : public Collider
{
	public:
		CircleCollider(GameObject* gameobject);

		float radious = 5;

		virtual void Draw() override;

		float GetActualRadious();

		virtual Rect GetBoundingBox() override;	//�o�E���f�B���O�{�b�N�X��Ԃ�

		virtual float GetI();	//�������[�����g���擾
};

