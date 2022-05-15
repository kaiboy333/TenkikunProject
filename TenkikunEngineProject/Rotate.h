#pragma once

#include "Script.h"
#include "Transform.h"

class Rotate : public Script
{
	public:
		void ScriptStart() override;

		void ScriptUpdate() override;

	private:
		float rotateSpeed = 1.0f;

		Transform* firstParent;
};

