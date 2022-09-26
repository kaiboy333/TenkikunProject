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

		//void SetRadiousFromImageRenderer(ImageRenderer* imageRenderer);
};

