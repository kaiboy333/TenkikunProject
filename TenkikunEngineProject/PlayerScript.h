#pragma once

#include "Script.h"
#include "Image.h"
#include "ImageRenderer.h"
#include "GameObject.h"
#include "Transform.h"
#include "Animation.h"
#include "Animator.h"
#include "AnimatorController.h"
#include <vector>
#include <iostream>
#include <sstream>

class PlayerScript : public Script {
	public:
		void ScriptStart() override;

		void ScriptUpdate() override;

	private:
		float speed = 3.0f;

		Transform* firstChild = nullptr;
};
