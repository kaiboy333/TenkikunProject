#pragma once

#include "Component.h"

class MonoBehaviour : public Component
{
	public:
		virtual void Update();

	private:
		bool isFirstUpdate = true;	//Updateが最初に呼ばれたか

	protected:
		virtual void MonoStart() = 0;
		virtual void MonoUpdate() = 0;
};

