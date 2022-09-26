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

		float ballSpeed = 200;

		float ballWeight = 100;

		float ballSizeMax = 0.5f;
};

