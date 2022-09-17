#pragma once

#include "MonoBehaviour.h"

class CreateBallScript : public MonoBehaviour
{
	public:
		CreateBallScript(GameObject* gameobject);

	protected:
		virtual void MonoStart() override;
		virtual void MonoUpdate() override;

	private:
		//std::vector<GameObject*> balls;

		float makeDistance = 300;

		float ballSpeed = 300;

		float ballWeight = 20;

		float ballSizeMax = 0.5f;
};

