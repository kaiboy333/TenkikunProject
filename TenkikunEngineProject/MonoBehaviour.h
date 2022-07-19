#pragma once

#include "Component.h"

class MonoBehaviour : public Component
{
	public:
		virtual void Update();

	private:
		bool isFirstUpdate = true;	//Update���ŏ��ɌĂ΂ꂽ��

	protected:
		virtual void MonoStart() = 0;
		virtual void MonoUpdate() = 0;
};
