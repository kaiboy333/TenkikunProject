#pragma once

#include "Component.h"
#include "Collision.h"
#include "Collider.h"

class MonoBehaviour : public Component
{
	public:
		MonoBehaviour(GameObject* gameobject);

		void Update();

		virtual void OnColliderEnter(Collision* collision) = 0;
		virtual void OnTriggerEnter(Collider* collider) = 0;

		virtual void OnColliderStay(Collision* collision) = 0;
		virtual void OnTriggerStay(Collider* collider) = 0;

		virtual void OnColliderExit(Collision* collision) = 0;
		virtual void OnTriggerExit(Collider* collider) = 0;

	private:
		bool isFirstUpdate = true;	//UpdateÇ™ç≈èâÇ…åƒÇŒÇÍÇΩÇ©

	protected:
		virtual void MonoStart() = 0;
		virtual void MonoUpdate() = 0;

		virtual void PreparationLibrate() override;
};
