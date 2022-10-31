#pragma once

#include "MonoBehaviour.h"

class CreateShapeScript : public MonoBehaviour
{
	public:
		CreateShapeScript(GameObject* gameobject);

	protected:
		virtual void MonoStart() override;
		virtual void MonoUpdate() override;

		virtual void OnColliderStay(Collision* collision);
		virtual void OnTriggerStay(Collider* collider);

	private:
		//std::vector<GameObject*> balls;

		float makeDistance = 300;

		float ballSpeed = 200;

		float ballWeight = 1;

		float ballSizeMax = 0.5f;
};

