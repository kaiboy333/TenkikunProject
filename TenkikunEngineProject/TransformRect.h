#pragma once

#include "ComponentRect.h"

class TransformRect : public ComponentRect
{
	public:
		TransformRect(float startX, float startY, Component* component);

		virtual void Draw() override;
};

