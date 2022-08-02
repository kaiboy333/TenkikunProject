#pragma once
#include "Component.h"

class DrawComponent : public Component
{
	public:
		DrawComponent(GameObject* gameobject);

		virtual void Update() override;

		virtual void Draw();

		Vector3 GetDrawPos(Vector3 pos);
};

