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

		virtual Rect GetBoundingBox() override;	//バウンディングボックスを返す

		virtual float GetI();	//慣性モーメントを取得
};

