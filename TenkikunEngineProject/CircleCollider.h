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

		float GetActualRadious() const;

		virtual Rect GetBoundingBox() const override;	//�o�E���f�B���O�{�b�N�X��Ԃ�

		virtual float GetI() const override;	//�������[�����g���擾
};

