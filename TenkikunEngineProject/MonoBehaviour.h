#pragma once

#include "Component.h"
#include "Collision.h"
#include "Collider.h"

class MonoBehaviour : public Component
{
	public:
		MonoBehaviour(GameObject* gameobject);

		virtual void Update();

	private:
		bool isFirstUpdate = true;	//Update‚ªÅ‰‚ÉŒÄ‚Î‚ê‚½‚©

	protected:
		virtual void MonoStart() = 0;
		virtual void MonoUpdate() = 0;

		virtual void PreparationLibrate() override;

		virtual void OnColliderStay(Collision* collision) = 0;
		virtual void OnTriggerStay(Collider* collider) = 0;
};
