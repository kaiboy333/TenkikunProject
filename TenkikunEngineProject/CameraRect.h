#pragma once

#include "ComponentRect.h"
#include "Camera.h"

class CameraRect : public ComponentRect
{
public:
	CameraRect(float startX, float startY, Component* component);

	virtual void Update() override;

	virtual void PreparationLibrate() override;
};

