#pragma once

#include "Component.h"

class Script : public Component
{
	public:
		void Update() override;

		virtual void ScriptStart() = 0;
		virtual void ScriptUpdate() = 0;

	private:
		bool isFirstUpdate = true;	//Update‚ªÅ‰‚ÉŒÄ‚Î‚ê‚½‚©
};

