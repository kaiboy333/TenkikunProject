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

		virtual Rect GetBoundingBox() const override;	//バウンディングボックスを返す

		virtual float GetI() const override;	//慣性モーメントを取得
};

