#pragma once

#include "Component.h"

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
};
