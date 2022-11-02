#pragma once

#include "MonoBehaviour.h"

class CreateShapeScript : public MonoBehaviour
{
	public:
		CreateShapeScript(GameObject* gameobject);

		virtual void OnColliderEnter(Collision* collision) override;
		virtual void OnTriggerEnter(Collider* collider) override;

		virtual void OnColliderStay(Collision* collision) override;
		virtual void OnTriggerStay(Collider* collider) override;

		virtual void OnColliderExit(Collision* collision) override;
		virtual void OnTriggerExit(Collider* collider) override;

	protected:
		virtual void MonoStart() override;
		virtual void MonoUpdate() override;

	private:
		//std::vector<GameObject*> balls;

		float makeDistance = 300;

		float ballSpeed = 200;

		float ballWeight = 1;

		float ballSizeMax = 0.5f;
};

