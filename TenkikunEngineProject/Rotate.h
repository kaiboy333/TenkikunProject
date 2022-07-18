#pragma once

#include "MonoBehaviour.h"
#include "Transform.h"

class Rotate : public MonoBehaviour
{
	protected:
		virtual void MonoStart();
		virtual void MonoUpdate();

	private:
		float rotateSpeed = 1.0f;
};

