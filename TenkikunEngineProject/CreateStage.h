#pragma once
#include "MonoBehaviour.h"
class CreateStage : public MonoBehaviour
{
	public:
		CreateStage(GameObject* gameobject);

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
		GameObject* player;
};

