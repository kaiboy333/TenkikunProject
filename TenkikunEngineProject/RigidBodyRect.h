#pragma once

#include "ComponentRect.h"

class RigidBodyRect : public ComponentRect
{
public:
	RigidBodyRect(float startX, float startY, Component* component);

	virtual void Update() override;

	virtual void PreparationLibrate() override;
};

