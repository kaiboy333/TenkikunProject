#pragma once

#include "ComponentRect.h"
#include "Rect.h"
#include "TextBox.h"

class TransformRect : public ComponentRect
{
	public:
		TransformRect(float startX, float startY, Component* component);

		virtual void Update() override;

		virtual void PreparationLibrate() override;
};

